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
 * (C) Copyright 2008 Dmitry Rakhchev, EmCraft Systems, rda@emcraft.com
 *
 * Developed for DENX Software Engineering GmbH
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

/* This test performs testing of FPGA SCRATCH register,
 * gets FPGA version and run get_ram_size() on FPGA memory
 */

#include <post.h>

#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

#define FPGA_SCRATCH_REG	0xC4000050
#define FPGA_VERSION_REG	0xC4000040
#define FPGA_RAM_START		0xC4200000
#define FPGA_RAM_END		0xC4203FFF
#define FPGA_STAT		0xC400000C

#if CONFIG_POST & CONFIG_SYS_POST_BSPEC3

/* Testpattern for fpga memorytest */
static uint pattern[] = {
	0x55555555,
	0xAAAAAAAA,
	0xAA5555AA,
	0x55AAAA55,
	0x0
};

static int one_scratch_test(uint value)
{
	uint read_value;
	int ret = 0;

	out_be32((void *)FPGA_SCRATCH_REG, value);
	/* read other location (protect against data lines capacity) */
	ret = in_be16((void *)FPGA_VERSION_REG);
	/* verify test pattern */
	read_value = in_be32((void *)FPGA_SCRATCH_REG);
	if (read_value != value) {
		post_log("FPGA SCRATCH test failed write %08X, read %08X\n",
			value, read_value);
		ret = 1;
	}

	return ret;
}

/* FPGA Memory-pattern-test */
static int fpga_mem_test(void * address)
{
	int ret = 1;
	uint read_value;
	uint old_value;
	uint i = 0;
	/* save content */
	old_value = in_be32(address);

	while (pattern[i] != 0) {
		out_be32(address, pattern[i]);
		/* read other location (protect against data lines capacity) */
		ret = in_be16((void *)FPGA_VERSION_REG);
		/* verify test pattern */
		read_value = in_be32(address);

		if (read_value != pattern[i]) {
			post_log("FPGA Memory test failed.");
			post_log(" write %08X, read %08X at address %08X\n",
				pattern[i], read_value, address);
			ret = 1;
			goto out;
		}
		i++;
	}

	ret = 0;
out:
	out_be32(address, old_value);
	return ret;
}
/* Verify FPGA, get version & memory size */
int fpga_post_test(int flags)
{
	uint   address;
	uint   old_value;
	ushort version;
	uint   read_value;
	int    ret = 0;

	post_log("\n");
	old_value = in_be32((void *)FPGA_SCRATCH_REG);

	if (one_scratch_test(0x55555555))
		ret = 1;
	if (one_scratch_test(0xAAAAAAAA))
		ret = 1;

	out_be32((void *)FPGA_SCRATCH_REG, old_value);

	version = in_be16((void *)FPGA_VERSION_REG);
	post_log("FPGA : version %u.%u\n",
		(version >> 8) & 0xFF, version & 0xFF);

	/* Enable write to FPGA RAM */
	out_be32((void *)FPGA_STAT, in_be32((void *)FPGA_STAT) | 0x1000);

	read_value = get_ram_size((void *)CONFIG_SYS_FPGA_BASE_1, 0x4000);
	post_log("FPGA RAM size: %d bytes\n", read_value);

	for (address = 0; address < 0x1000; address++) {
		if (fpga_mem_test((void *)(FPGA_RAM_START + 4*address)) == 1) {
			ret = 1;
			goto out;
		}
	}

out:
	return ret;
}

#endif /* CONFIG_POST & CONFIG_SYS_POST_BSPEC3 */
