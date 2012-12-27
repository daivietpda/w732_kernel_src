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
 * (C) Copyright 2008
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Prafulla Wadaskar <prafulla@marvell.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef _KWBIMAGE_H_
#define _KWBIMAGE_H_

#include <stdint.h>

#define KWBIMAGE_MAX_CONFIG	((0x1dc - 0x20)/sizeof(struct reg_config))
#define MAX_TEMPBUF_LEN		32

/* NAND ECC Mode */
#define IBR_HDR_ECC_DEFAULT		0x00
#define IBR_HDR_ECC_FORCED_HAMMING	0x01
#define IBR_HDR_ECC_FORCED_RS  		0x02
#define IBR_HDR_ECC_DISABLED  		0x03

/* Boot Type - block ID */
#define IBR_HDR_I2C_ID			0x4D
#define IBR_HDR_SPI_ID			0x5A
#define IBR_HDR_NAND_ID			0x8B
#define IBR_HDR_SATA_ID			0x78
#define IBR_HDR_PEX_ID			0x9C
#define IBR_HDR_UART_ID			0x69
#define IBR_DEF_ATTRIB	 		0x00

enum kwbimage_cmd {
	CMD_INVALID,
	CMD_BOOT_FROM,
	CMD_NAND_ECC_MODE,
	CMD_NAND_PAGE_SIZE,
	CMD_SATA_PIO_MODE,
	CMD_DDR_INIT_DELAY,
	CMD_DATA
};

enum kwbimage_cmd_types {
	CFG_INVALID = -1,
	CFG_COMMAND,
	CFG_DATA0,
	CFG_DATA1
};

/* typedefs */
typedef struct bhr_t {
	uint8_t blockid;		/*0     */
	uint8_t nandeccmode;		/*1     */
	uint16_t nandpagesize;		/*2-3   */
	uint32_t blocksize;		/*4-7   */
	uint32_t rsvd1;			/*8-11  */
	uint32_t srcaddr;		/*12-15 */
	uint32_t destaddr;		/*16-19 */
	uint32_t execaddr;		/*20-23 */
	uint8_t satapiomode;		/*24    */
	uint8_t rsvd3;			/*25    */
	uint16_t ddrinitdelay;		/*26-27 */
	uint16_t rsvd2;			/*28-29 */
	uint8_t ext;			/*30    */
	uint8_t checkSum;		/*31    */
} bhr_t, *pbhr_t;

struct reg_config {
	uint32_t raddr;
	uint32_t rdata;
};

typedef struct extbhr_t {
	uint32_t dramregsoffs;
	uint8_t rsrvd1[0x20 - sizeof(uint32_t)];
	struct reg_config rcfg[KWBIMAGE_MAX_CONFIG];
	uint8_t rsrvd2[7];
	uint8_t checkSum;
} extbhr_t, *pextbhr_t;

struct kwb_header {
	bhr_t kwb_hdr;
	extbhr_t kwb_exthdr;
};

/*
 * functions
 */
void init_kwb_image_type (void);

#endif /* _KWBIMAGE_H_ */
