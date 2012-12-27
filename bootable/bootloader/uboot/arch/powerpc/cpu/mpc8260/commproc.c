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
 * This file is based on "arch/powerpc/8260_io/commproc.c" - here is it's
 * copyright notice:
 *
 * General Purpose functions for the global management of the
 * 8260 Communication Processor Module.
 * Copyright (c) 1999 Dan Malek (dmalek@jlc.net)
 * Copyright (c) 2000 MontaVista Software, Inc (source@mvista.com)
 *	2.3.99 Updates
 *
 * In addition to the individual control of the communication
 * channels, there are a few functions that globally affect the
 * communication processor.
 *
 * Buffer descriptors must be allocated from the dual ported memory
 * space.  The allocator for that is here.  When the communication
 * process is reset, we reclaim the memory available.  There is
 * currently no deallocator for this memory.
 */
#include <common.h>
#include <asm/cpm_8260.h>

DECLARE_GLOBAL_DATA_PTR;

void
m8260_cpm_reset(void)
{
	volatile immap_t *immr = (immap_t *)CONFIG_SYS_IMMR;
	volatile ulong count;

	/* Reclaim the DP memory for our use.
	*/
	gd->dp_alloc_base = CPM_DATAONLY_BASE;
	gd->dp_alloc_top = gd->dp_alloc_base + CPM_DATAONLY_SIZE;

	/*
	 * Reset CPM
	 */
	immr->im_cpm.cp_cpcr = CPM_CR_RST;
	count = 0;
	do {			/* Spin until command processed		*/
		__asm__ __volatile__ ("eieio");
	} while ((immr->im_cpm.cp_cpcr & CPM_CR_FLG) && ++count < 1000000);

#ifdef CONFIG_HARD_I2C
	*((unsigned short*)(&immr->im_dprambase[PROFF_I2C_BASE])) = 0;
#endif
}

/* Allocate some memory from the dual ported ram.
 * To help protocols with object alignment restrictions, we do that
 * if they ask.
 */
uint
m8260_cpm_dpalloc(uint size, uint align)
{
	volatile immap_t *immr = (immap_t *)CONFIG_SYS_IMMR;
	uint	retloc;
	uint	align_mask, off;
	uint	savebase;

	align_mask = align - 1;
	savebase = gd->dp_alloc_base;

	if ((off = (gd->dp_alloc_base & align_mask)) != 0)
		gd->dp_alloc_base += (align - off);

	if ((off = size & align_mask) != 0)
		size += align - off;

	if ((gd->dp_alloc_base + size) >= gd->dp_alloc_top) {
		gd->dp_alloc_base = savebase;
		panic("m8260_cpm_dpalloc: ran out of dual port ram!");
	}

	retloc = gd->dp_alloc_base;
	gd->dp_alloc_base += size;

	memset((void *)&immr->im_dprambase[retloc], 0, size);

	return(retloc);
}

/* We also own one page of host buffer space for the allocation of
 * UART "fifos" and the like.
 */
uint
m8260_cpm_hostalloc(uint size, uint align)
{
	/* the host might not even have RAM yet - just use dual port RAM */
	return (m8260_cpm_dpalloc(size, align));
}

/* Set a baud rate generator.  This needs lots of work.  There are
 * eight BRGs, which can be connected to the CPM channels or output
 * as clocks.  The BRGs are in two different block of internal
 * memory mapped space.
 * The baud rate clock is the system clock divided by something.
 * It was set up long ago during the initial boot phase and is
 * is given to us.
 * Baud rate clocks are zero-based in the driver code (as that maps
 * to port numbers).  Documentation uses 1-based numbering.
 */
#define BRG_INT_CLK	gd->brg_clk
#define BRG_UART_CLK	(BRG_INT_CLK / 16)

/* This function is used by UARTs, or anything else that uses a 16x
 * oversampled clock.
 */
void
m8260_cpm_setbrg(uint brg, uint rate)
{
	volatile immap_t *immr = (immap_t *)CONFIG_SYS_IMMR;
	volatile uint	*bp;
	uint cd = BRG_UART_CLK / rate;

	if ((BRG_UART_CLK % rate) < (rate / 2))
		cd--;
	if (brg < 4) {
		bp = (uint *)&immr->im_brgc1;
	}
	else {
		bp = (uint *)&immr->im_brgc5;
		brg -= 4;
	}
	bp += brg;
	*bp = (cd << 1) | CPM_BRG_EN;
}

/* This function is used to set high speed synchronous baud rate
 * clocks.
 */
void
m8260_cpm_fastbrg(uint brg, uint rate, int div16)
{
	volatile immap_t *immr = (immap_t *)CONFIG_SYS_IMMR;
	volatile uint	*bp;

	/* This is good enough to get SMCs running.....
	*/
	if (brg < 4) {
		bp = (uint *)&immr->im_brgc1;
	}
	else {
		bp = (uint *)&immr->im_brgc5;
		brg -= 4;
	}
	bp += brg;
	*bp = (((((BRG_INT_CLK+rate-1)/rate)-1)&0xfff)<<1)|CPM_BRG_EN;
	if (div16)
		*bp |= CPM_BRG_DIV16;
}

/* This function is used to set baud rate generators using an external
 * clock source and 16x oversampling.
 */

void
m8260_cpm_extcbrg(uint brg, uint rate, uint extclk, int pinsel)
{
	volatile immap_t *immr = (immap_t *)CONFIG_SYS_IMMR;
	volatile uint	*bp;

	if (brg < 4) {
		bp = (uint *)&immr->im_brgc1;
	}
	else {
		bp = (uint *)&immr->im_brgc5;
		brg -= 4;
	}
	bp += brg;
	*bp = ((((((extclk/16)+rate-1)/rate)-1)&0xfff)<<1)|CPM_BRG_EN;
	if (pinsel == 0)
		*bp |= CPM_BRG_EXTC_CLK3_9;
	else
		*bp |= CPM_BRG_EXTC_CLK5_15;
}

#if defined(CONFIG_POST) || defined(CONFIG_LOGBUFFER)

void post_word_store (ulong a)
{
	volatile ulong *save_addr =
		(volatile ulong *)(CONFIG_SYS_IMMR + CPM_POST_WORD_ADDR);

	*save_addr = a;
}

ulong post_word_load (void)
{
	volatile ulong *save_addr =
		(volatile ulong *)(CONFIG_SYS_IMMR + CPM_POST_WORD_ADDR);

	return *save_addr;
}

#endif	/* CONFIG_POST || CONFIG_LOGBUFFER*/
