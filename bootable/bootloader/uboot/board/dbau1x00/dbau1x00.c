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
 * (C) Copyright 2003
 * Thomas.Lange@corelatus.se
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

#include <common.h>
#include <command.h>
#include <asm/au1x00.h>
#include <asm/mipsregs.h>
#include <asm/io.h>

phys_size_t initdram(int board_type)
{
	/* Sdram is setup by assembler code */
	/* If memory could be changed, we should return the true value here */
	return MEM_SIZE*1024*1024;
}

#define BCSR_PCMCIA_PC0DRVEN		0x0010
#define BCSR_PCMCIA_PC0RST		0x0080

/* In arch/mips/cpu/cpu.c */
void write_one_tlb( int index, u32 pagemask, u32 hi, u32 low0, u32 low1 );

int checkboard (void)
{
#ifdef CONFIG_IDE_PCMCIA
	u16 status;
	volatile u32 *pcmcia_bcsr = (u32*)(DB1XX0_BCSR_ADDR+0x10);
#endif	/* CONFIG_IDE_PCMCIA */
	volatile u32 *phy = (u32*)(DB1XX0_BCSR_ADDR+0xC);
	volatile u32 *sys_counter = (volatile u32*)SYS_COUNTER_CNTRL;
	u32 proc_id;

	*sys_counter = 0x100; /* Enable 32 kHz oscillator for RTC/TOY */

	proc_id = read_c0_prid();

	switch (proc_id >> 24) {
	case 0:
		puts ("Board: Merlot (DbAu1000)\n");
		printf ("CPU: Au1000 396 MHz, id: 0x%02x, rev: 0x%02x\n",
			(proc_id >> 8) & 0xFF, proc_id & 0xFF);
		break;
	case 1:
		puts ("Board: DbAu1500\n");
		printf ("CPU: Au1500, id: 0x%02x, rev: 0x%02x\n",
			(proc_id >> 8) & 0xFF, proc_id & 0xFF);
		break;
	case 2:
		puts ("Board: DbAu1100\n");
		printf ("CPU: Au1100, id: 0x%02x, rev: 0x%02x\n",
			(proc_id >> 8) & 0xFF, proc_id & 0xFF);
		break;
	case 3:
		puts ("Board: DbAu1550\n");
		printf ("CPU: Au1550, id: 0x%02x, rev: 0x%02x\n",
			(proc_id >> 8) & 0xFF, proc_id & 0xFF);
		break;
	default:
		printf ("Unsupported cpu %d, proc_id=0x%x\n", proc_id >> 24, proc_id);
	}

	set_io_port_base(0);

#ifdef CONFIG_IDE_PCMCIA
	/* Enable 3.3 V on slot 0 ( VCC )
	   No 5V */
	status = 4;
	*pcmcia_bcsr = status;

	status |= BCSR_PCMCIA_PC0DRVEN;
	*pcmcia_bcsr = status;
	au_sync();

	udelay(300*1000);

	status |= BCSR_PCMCIA_PC0RST;
	*pcmcia_bcsr = status;
	au_sync();

	udelay(100*1000);

	/* PCMCIA is on a 36 bit physical address.
	   We need to map it into a 32 bit addresses */

#if 0
	/* We dont need theese unless we run whole pcmcia package */
	write_one_tlb(20,                 /* index */
		      0x01ffe000,         /* Pagemask, 16 MB pages */
		      CONFIG_SYS_PCMCIA_IO_BASE, /* Hi */
		      0x3C000017,         /* Lo0 */
		      0x3C200017);        /* Lo1 */

	write_one_tlb(21,                   /* index */
		      0x01ffe000,           /* Pagemask, 16 MB pages */
		      CONFIG_SYS_PCMCIA_ATTR_BASE, /* Hi */
		      0x3D000017,           /* Lo0 */
		      0x3D200017);          /* Lo1 */
#endif	/* 0 */
	write_one_tlb(22,                   /* index */
		      0x01ffe000,           /* Pagemask, 16 MB pages */
		      CONFIG_SYS_PCMCIA_MEM_ADDR,  /* Hi */
		      0x3E000017,           /* Lo0 */
		      0x3E200017);          /* Lo1 */
#endif	/* CONFIG_IDE_PCMCIA */

	/* Release reset of ethernet PHY chips */
	/* Always do this, because linux does not know about it */
	*phy = 3;

	return 0;
}
