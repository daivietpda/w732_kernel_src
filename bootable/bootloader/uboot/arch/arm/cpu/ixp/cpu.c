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
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Alex Zuepke <azu@sysgo.de>
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

/*
 * CPU specific code
 */

#include <common.h>
#include <command.h>
#include <netdev.h>
#include <asm/arch/ixp425.h>
#include <asm/system.h>

ulong loops_per_jiffy;

static void cache_flush(void);

#if defined(CONFIG_DISPLAY_CPUINFO)
int print_cpuinfo (void)
{
	unsigned long id;
	int speed = 0;

	asm ("mrc p15, 0, %0, c0, c0, 0":"=r" (id));

	puts("CPU:   Intel IXP425 at ");
	switch ((id & 0x000003f0) >> 4) {
	case 0x1c:
		loops_per_jiffy = 887467;
		speed = 533;
		break;

	case 0x1d:
		loops_per_jiffy = 666016;
		speed = 400;
		break;

	case 0x1f:
		loops_per_jiffy = 442901;
		speed = 266;
		break;
	}

	if (speed)
		printf("%d MHz\n", speed);
	else
		puts("unknown revision\n");

	return 0;
}
#endif /* CONFIG_DISPLAY_CPUINFO */

int cleanup_before_linux (void)
{
	/*
	 * this function is called just before we call linux
	 * it prepares the processor for linux
	 *
	 * just disable everything that can disturb booting linux
	 */

	disable_interrupts ();

	/* turn off I-cache */
	icache_disable();
	dcache_disable();

	/* flush I-cache */
	cache_flush();

	return 0;
}

/* flush I/D-cache */
static void cache_flush (void)
{
	unsigned long i = 0;

	asm ("mcr p15, 0, %0, c7, c5, 0": :"r" (i));
}

/* FIXME */
/*
void pci_init(void)
{
	return;
}
*/

#ifdef CONFIG_BOOTCOUNT_LIMIT

void bootcount_store (ulong a)
{
	volatile ulong *save_addr = (volatile ulong *)(CONFIG_SYS_BOOTCOUNT_ADDR);

	save_addr[0] = a;
	save_addr[1] = BOOTCOUNT_MAGIC;
}

ulong bootcount_load (void)
{
	volatile ulong *save_addr = (volatile ulong *)(CONFIG_SYS_BOOTCOUNT_ADDR);

	if (save_addr[1] != BOOTCOUNT_MAGIC)
		return 0;
	else
		return save_addr[0];
}

#endif /* CONFIG_BOOTCOUNT_LIMIT */

int cpu_eth_init(bd_t *bis)
{
#ifdef CONFIG_IXP4XX_NPE
	npe_initialize(bis);
#endif
	return 0;
}