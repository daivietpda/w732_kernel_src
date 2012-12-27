/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*
 * (C) Copyright 2006
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <lcd.h>
#include <mpc5xxx.h>

#ifdef CONFIG_LCD

#undef SWAPPED_LCD /* For the previous h/w version */
/*
 *  The name of the device used for communication
 * with the PSoC.
 */
#define PSOC_PSC	MPC5XXX_PSC2
#define PSOC_BAUD	230400UL

#define RTS_ASSERT	1
#define RTS_NEGATE	0
#define CTS_ASSERT	1
#define CTS_NEGATE	0

/*
 * Dimensions in pixels
 */
#define LCD_WIDTH	160
#define LCD_HEIGHT	100

/*
 * Dimensions in bytes
 */
#define LCD_BUF_SIZE	((LCD_WIDTH*LCD_HEIGHT)>>3)

#if LCD_BPP != LCD_MONOCHROME
#error "MCC200 support only monochrome displays (1 bpp)!"
#endif

#define PSOC_RETRIES	10	/* each of PSOC_WAIT_TIME */
#define PSOC_WAIT_TIME	10	/* usec */

DECLARE_GLOBAL_DATA_PTR;

/*
 * LCD information
 */
vidinfo_t panel_info = {
	LCD_WIDTH, LCD_HEIGHT, LCD_BPP
};

int lcd_line_length;

int lcd_color_fg;
int lcd_color_bg;

/*
 * Frame buffer memory information
 */
void *lcd_base;			/* Start of framebuffer memory  */
void *lcd_console_address;	/* Start of console buffer      */

short console_col = 0;
short console_row = 0;

/*
 *  The device we use to communicate with PSoC
 */
int serial_inited = 0;

/*
 * Exported functions
 */
void lcd_initcolregs (void);
void lcd_ctrl_init (void *lcdbase);
void lcd_enable (void);

/*
 *  Imported functions to support the PSoC protocol
 */
extern int serial_init_dev (unsigned long dev_base);
extern void serial_setrts_dev (unsigned long dev_base, int s);
extern int serial_getcts_dev (unsigned long dev_base);
extern void serial_putc_raw_dev(unsigned long dev_base, const char c);

/*
 *  Just stubs for our driver, needed for compiling compabilty with
 * the common LCD driver code.
 */
void lcd_initcolregs (void)
{
}

void lcd_ctrl_init (void *lcdbase)
{
}

/*
 * Function sends the contents of the frame-buffer to the LCD
 */
void lcd_enable (void)
{
	int i, retries, fb_size;

	if (!serial_inited) {
		unsigned long baud;

		baud = gd->baudrate;
		gd->baudrate = PSOC_BAUD;
		serial_init_dev(PSOC_PSC);
		gd->baudrate = baud;
		serial_setrts_dev (PSOC_PSC, RTS_ASSERT);
		serial_inited = 1;
	}

	/*
	 *  Implement PSoC communication protocol:
	 * 1. Assert RTS, wait CTS assertion
	 * 2. Transmit data
	 * 3. Negate RTS, wait CTS negation
	 */

	/* 1 */
	serial_setrts_dev (PSOC_PSC, RTS_ASSERT);
	for (retries = PSOC_RETRIES; retries; retries--) {
		if (serial_getcts_dev(PSOC_PSC) == CTS_ASSERT)
			break;
		udelay (PSOC_WAIT_TIME);
	}
	if (!retries) {
		printf ("%s Error: PSoC doesn't respond on "
			"RTS ASSERT\n",	__FUNCTION__);
	}

	/* 2 */
	fb_size = panel_info.vl_row * (panel_info.vl_col >> 3);

#if !defined(SWAPPED_LCD)
	for (i=0; i<fb_size; i++) {
		serial_putc_raw_dev (PSOC_PSC, ((char *)lcd_base)[i]);
	}
#else
    {
	int x, y, pwidth;
	char *p = (char *)lcd_base;

	pwidth = ((panel_info.vl_col+7) >> 3);
	for (y=0; y<panel_info.vl_row; y++) {
		i = y * pwidth;
		for (x=0; x<pwidth; x+=5) {
			serial_putc_raw_dev (PSOC_PSC, (p[i+x+2]<<4 & 0xF0) | (p[i+x+3]>>4 & 0x0F));
			serial_putc_raw_dev (PSOC_PSC, (p[i+x+3]<<4 & 0xF0) | (p[i+x+4]>>4 & 0x0F));
			serial_putc_raw_dev (PSOC_PSC, (p[i+x+4]<<4 & 0xF0) | (p[i+x]>>4 & 0x0F));
			serial_putc_raw_dev (PSOC_PSC, (p[i+x]<<4 & 0xF0) | (p[i+x+1]>>4 & 0x0F));
			serial_putc_raw_dev (PSOC_PSC, (p[i+x+1]<<4 & 0xF0) | (p[i+x+2]>>4 & 0x0F));
		}
	}
    }
#endif

	/* 3 */
	serial_setrts_dev (PSOC_PSC, RTS_NEGATE);
	for (retries = PSOC_RETRIES; retries; retries--) {
		if (serial_getcts_dev(PSOC_PSC) == CTS_NEGATE)
			break;
		udelay (PSOC_WAIT_TIME);
	}

	return;
}
#ifdef CONFIG_PROGRESSBAR

#define FONT_WIDTH      8 /* the same as VIDEO_FONT_WIDTH in video_font.h */
void show_progress (int size, int tot)
{
	int cnt;
	int i;
	static int rc = 0;

	rc += size;

	cnt = ((LCD_WIDTH/FONT_WIDTH) * rc) / tot;

	rc -= (cnt * tot) / (LCD_WIDTH/FONT_WIDTH);

	for (i = 0; i < cnt; i++) {
		lcd_putc(0xdc);
	}

	if (cnt) {
		lcd_enable(); /* MCC200-specific - send the framebuffer to PSoC */
	}
}

#endif
#endif /* CONFIG_LCD */
