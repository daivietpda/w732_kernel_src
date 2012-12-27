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
 * Copyright (C) 2004-2006 Atmel Corporation
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
#include <image.h>
#include <u-boot/zlib.h>
#include <asm/byteorder.h>
#include <asm/arch/addrspace.h>
#include <asm/io.h>
#include <asm/setup.h>
#include <asm/arch/clk.h>

DECLARE_GLOBAL_DATA_PTR;

/* CPU-specific hook to allow flushing of caches, etc. */
extern void prepare_to_boot(void);

static struct tag *setup_start_tag(struct tag *params)
{
	params->hdr.tag = ATAG_CORE;
	params->hdr.size = tag_size(tag_core);

	params->u.core.flags = 0;
	params->u.core.pagesize = 4096;
	params->u.core.rootdev = 0;

	return tag_next(params);
}

static struct tag *setup_memory_tags(struct tag *params)
{
	bd_t *bd = gd->bd;
	int i;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		params->hdr.tag = ATAG_MEM;
		params->hdr.size = tag_size(tag_mem_range);

		params->u.mem_range.addr = bd->bi_dram[i].start;
		params->u.mem_range.size = bd->bi_dram[i].size;

		params = tag_next(params);
	}

	return params;
}

static struct tag *setup_commandline_tag(struct tag *params, char *cmdline)
{
	if (!cmdline)
		return params;

	/* eat leading white space */
	while (*cmdline == ' ') cmdline++;

	/*
	 * Don't include tags for empty command lines; let the kernel
	 * use its default command line.
	 */
	if (*cmdline == '\0')
		return params;

	params->hdr.tag = ATAG_CMDLINE;
	params->hdr.size =
		(sizeof (struct tag_header) + strlen(cmdline) + 1 + 3) >> 2;
	strcpy(params->u.cmdline.cmdline, cmdline);

	return tag_next(params);
}

static struct tag *setup_ramdisk_tag(struct tag *params,
				     unsigned long rd_start,
				     unsigned long rd_end)
{
	if (rd_start == rd_end)
		return params;

	params->hdr.tag = ATAG_RDIMG;
	params->hdr.size = tag_size(tag_mem_range);

	params->u.mem_range.addr = rd_start;
	params->u.mem_range.size = rd_end - rd_start;

	return tag_next(params);
}

static struct tag *setup_clock_tags(struct tag *params)
{
	params->hdr.tag = ATAG_CLOCK;
	params->hdr.size = tag_size(tag_clock);
	params->u.clock.clock_id = ACLOCK_BOOTCPU;
	params->u.clock.clock_flags = 0;
	params->u.clock.clock_hz = gd->cpu_hz;

#ifdef CONFIG_AT32AP7000
	/*
	 * New kernels don't need this, but we should be backwards
	 * compatible for a while...
	 */
	params = tag_next(params);

	params->hdr.tag = ATAG_CLOCK;
	params->hdr.size = tag_size(tag_clock);
	params->u.clock.clock_id = ACLOCK_HSB;
	params->u.clock.clock_flags = 0;
	params->u.clock.clock_hz = get_hsb_clk_rate();
#endif

	return tag_next(params);
}

static struct tag *setup_ethernet_tag(struct tag *params,
				      char *addr, int index)
{
	char *s, *e;
	int i;

	params->hdr.tag = ATAG_ETHERNET;
	params->hdr.size = tag_size(tag_ethernet);

	params->u.ethernet.mac_index = index;
	params->u.ethernet.mii_phy_addr = gd->bd->bi_phy_id[index];

	s = addr;
	for (i = 0; i < 6; i++) {
		params->u.ethernet.hw_address[i] = simple_strtoul(s, &e, 16);
		s = e + 1;
	}

	return tag_next(params);
}

static struct tag *setup_ethernet_tags(struct tag *params)
{
	char name[16] = "ethaddr";
	char *addr;
	int i = 0;

	do {
		addr = getenv(name);
		if (addr)
			params = setup_ethernet_tag(params, addr, i);
		sprintf(name, "eth%daddr", ++i);
	} while (i < 4);

	return params;
}

static void setup_end_tag(struct tag *params)
{
	params->hdr.tag = ATAG_NONE;
	params->hdr.size = 0;
}

int do_bootm_linux(int flag, int argc, char *argv[], bootm_headers_t *images)
{
	void	(*theKernel)(int magic, void *tagtable);
	struct	tag *params, *params_start;
	char	*commandline = getenv("bootargs");

	if ((flag != 0) && (flag != BOOTM_STATE_OS_GO))
		return 1;

	theKernel = (void *)images->ep;

	show_boot_progress (15);

	params = params_start = (struct tag *)gd->bd->bi_boot_params;
	params = setup_start_tag(params);
	params = setup_memory_tags(params);
	if (images->rd_start) {
		params = setup_ramdisk_tag(params,
					   PHYSADDR(images->rd_start),
					   PHYSADDR(images->rd_end));
	}
	params = setup_commandline_tag(params, commandline);
	params = setup_clock_tags(params);
	params = setup_ethernet_tags(params);
	setup_end_tag(params);

	printf("\nStarting kernel at %p (params at %p)...\n\n",
	       theKernel, params_start);

	prepare_to_boot();

	theKernel(ATAG_MAGIC, params_start);
	/* does not return */

	return 1;
}
