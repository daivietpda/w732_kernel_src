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
 * (C) Copyright 2003, Psyent Corporation <www.psyent.com>
 * Scott McNutt <smcnutt@psyent.com>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */


#include <config.h>
#include <timestamp.h>
#include <version.h>

#if !defined(CONFIG_IDENT_STRING)
#define CONFIG_IDENT_STRING ""
#endif

#define STATUS_INIT	0x8600		/* IE=1, IPRI=2 */

/*************************************************************************
 * RESTART
 ************************************************************************/

	.text
	.global _start

_start:
	bsr	0f
	nop
	.long	_start

	/* GERMS -- The "standard-32" configuration GERMS monitor looks
	 * for the string "Nios" at flash_base + 0xc (actually it only
	 * tests for 'N', 'i'). You can leave support for this in place
	 * as it's only a few words.
	 */
	. = _start + 0x000c
	.string "Nios"

	.align 4
0:
	/*
	 * Early setup -- set cwp = HI_LIMIT, IPRI = 2, IE = 1 to
	 * enable underflow exceptions. Disable cache.
	 * NOTE: %o7 has return addr -- save in %g7 use later.
	 */
	mov	%g7, %o7

	pfx	2			/* WVALID */
	rdctl	%g0
	lsri	%g0, 1
	pfx	%hi(STATUS_INIT)
	or	%g0, %lo(STATUS_INIT)
	wrctl	%g0			/* update status */
	nop

	/*
	 * STACK
	 */
	pfx	%hi(CONFIG_SYS_INIT_SP)
	movi	%sp, %lo(CONFIG_SYS_INIT_SP)
	pfx	%xhi(CONFIG_SYS_INIT_SP)
	movhi	%sp, %xlo(CONFIG_SYS_INIT_SP)
	mov	%fp, %sp

	pfx	%hi(4*16)
	subi	%sp, %lo(4*16)		/* Space for reg window mgmt */

	/*
	 * RELOCATE -- %g7 has return addr from bsr at _start.
	 */
	pfx	%hi(__u_boot_cmd_end)
	movi	%g5, %lo(__u_boot_cmd_end)
	pfx	%xhi(__u_boot_cmd_end)
	movhi	%g5, %xlo(__u_boot_cmd_end) /* %g5 <- end address */

	lsli	%g7, 1			/* mem = retaddr << 1 */
	mov	%g6, %g7
	subi	%g6, 4			/* %g6 <- src addr */
	ld	%g7, [%g7]		/* %g7 <- dst addr */

	/* No need to move text sections if we're already located
	 * at the proper address.
	 */
	cmp	%g7, %g6
	ifs	cc_z
	br	reloc
	nop				/* delay slot */

1:	cmp	%g7, %g5
	skps	cc_nz
	br	2f
	nop				/* delay slot */

	ld	%g0, [%g6]
	addi	%g6, 4			/* src++ */
	st	[%g7], %g0
	addi	%g7, 4			/* dst++ */
	br	1b
	nop				/* delay slot */
2:

	/*
	 * Jump to relocation address
	 */
	 pfx	%hi(reloc@h)
	 movi	%g0, %lo(reloc@h)
	 pfx	%xhi(reloc@h)
	 movhi	%g0, %xlo(reloc@h)
	 jmp	%g0
	 nop				/* delay slot */
reloc:

	/*
	 * CLEAR BSS
	 */
	pfx	%hi(__bss_end)
	movi	%g5, %lo(__bss_end)
	pfx	%xhi(__bss_end)
	movhi	%g5, %xlo(__bss_end)	/* %g5 <- end address */
	pfx	%hi(__bss_start)
	movi	%g7, %lo(__bss_start)
	pfx	%xhi(__bss_start)
	movhi	%g7, %xlo(__bss_start)	/* %g7 <- end address */

	movi	%g0, 0
3:	cmp	%g7, %g5
	skps	cc_nz
	br	4f
	nop				/* delay slot */

	st	[%g7], %g0
	addi	%g7, 4			/* (delay slot) dst++ */
	br	3b
	nop				/* delay slot */
4:

	/*
	 * INIT VECTOR TABLE
	 */
	pfx	%hi(CONFIG_SYS_VECT_BASE)
	movi	%g0, %lo(CONFIG_SYS_VECT_BASE)
	pfx	%xhi(CONFIG_SYS_VECT_BASE)
	movhi	%g0, %xlo(CONFIG_SYS_VECT_BASE)	/* dst */
	mov	%l0, %g0

	pfx	%hi(_vectors)
	movi	%g1, %lo(_vectors)
	pfx	%xhi(_vectors)
	movhi	%g1, %xlo(_vectors)	/* src */
	bgen	%g2, 6			/* cnt = 64 */

	ldp	%g3, [%l0, 3]		/* bkpt vector */
	ldp	%g4, [%l0, 4]		/* single step vector */

5:	ld	%g7, [%g1]
	addi	%g1, 4			/* src++ */
	st	[%g0], %g7
	addi	%g0, 4			/* dst++ */

	subi	%g2, 1			/* cnt-- */
	ifrnz	%g2
	br	5b
	nop				/* delay slot */

#if defined(CONFIG_ROM_STUBS)
	/* Restore the breakpoint and single step exception
	 * vectors to their original values.
	 */
	stp	[%l0,3], %g3		/* breakpoint */
	stp	[%l0,4], %g4		/* single step */
#endif

	/* For debug startup convenience ... software breakpoints
	 * set prior to this point may not succeed ;-)
	 */
	.global __start
__start:

	/*
	 * Call board_init -- never returns
	 */
	pfx	%hi(board_init@h)
	movi	%g1, %lo(board_init@h)
	pfx	%xhi(board_init@h)
	movhi	%g1, %xlo(board_init@h)
	call	%g1
	nop				/* Delaly slot */
	/* NEVER RETURNS */

/*
 * dly_clks -- Nios doesn't have a time/clk reference for simple
 * delay loops, so we do our best by counting instruction cycles.
 * A control register that counts system clock cycles would be
 * a handy feature -- hint for Altera ;-)
 */
	.globl dly_clks
	/* Each loop is 4 instructions as delay slot is always
	 * executed. Each instruction is approximately 4 clocks
	 * (according to some lame info from Altera). So ...
	 * ... each loop is about 16 clocks.
	 */

dly_clks:
	lsri	%o0, 4			/* cnt/16 */

8:	skprnz	%o0
	br	9f
	subi	%o0, 1			/* cnt--, Delay slot */
	br	8b
	nop

9:	lret
	nop				/* Delay slot */


	.data
	.globl	version_string

version_string:
	.ascii U_BOOT_VERSION
	.ascii " (", U_BOOT_DATE, " - ", U_BOOT_TIME, ")"
	.ascii CONFIG_IDENT_STRING, "\0"
