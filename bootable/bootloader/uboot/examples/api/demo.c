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
 * (C) Copyright 2007-2008 Semihalf
 *
 * Written by: Rafal Jaworowski <raj@semihalf.com>
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
 *
 */

#include <common.h>
#include <linux/types.h>
#include <api_public.h>

#include "glue.h"

#define errf(fmt, args...) do { printf("ERROR @ %s(): ", __func__); printf(fmt, ##args); } while (0)

#define BUF_SZ		2048
#define WAIT_SECS	5

void	test_dump_buf(void *, int);
void	test_dump_di(int);
void	test_dump_si(struct sys_info *);
void	test_dump_sig(struct api_signature *);

static char buf[BUF_SZ];

int main(int argc, char *argv[])
{
	int rv = 0, h, i, j, devs_no;
	struct api_signature *sig = NULL;
	ulong start, now;
	struct device_info *di;
	lbasize_t rlen;

	if (!api_search_sig(&sig))
		return -1;

	syscall_ptr = sig->syscall;
	if (syscall_ptr == NULL)
		return -2;

	if (sig->version > API_SIG_VERSION)
		return -3;

	printf("API signature found @%x\n", (unsigned int)sig);
	test_dump_sig(sig);

	printf("\n*** Consumer API test ***\n");
	printf("syscall ptr 0x%08x@%08x\n", (unsigned int)syscall_ptr,
		(unsigned int)&syscall_ptr);

	/* console activities */
	ub_putc('B');

	printf("*** Press any key to continue ***\n");
	printf("got char 0x%x\n", ub_getc());

	/* system info */
	test_dump_si(ub_get_sys_info());

	/* timing */
	printf("\n*** Timing - wait a couple of secs ***\n");
	start = ub_get_timer(0);
	printf("\ntime: start %lu\n\n", start);
	for (i = 0; i < WAIT_SECS; i++)
		for (j = 0; j < 1000; j++)
			ub_udelay(1000);	/* wait 1 ms */

	/* this is the number of milliseconds that passed from ub_get_timer(0) */
	now = ub_get_timer(start);
	printf("\ntime: now %lu\n\n", now);

	/* enumerate devices */
	printf("\n*** Enumerate devices ***\n");
	devs_no = ub_dev_enum();

	printf("Number of devices found: %d\n", devs_no);
	if (devs_no == 0)
		return -1;

	printf("\n*** Show devices ***\n");
	for (i = 0; i < devs_no; i++) {
		test_dump_di(i);
		printf("\n");
	}

	printf("\n*** Operations on devices ***\n");

	/* test opening a device already opened */
	h = 0;
	if ((rv = ub_dev_open(h)) != 0) {
		errf("open device %d error %d\n", h, rv);
		return -1;
	}
	if ((rv = ub_dev_open(h)) != 0)
		errf("open device %d error %d\n", h, rv);

	ub_dev_close(h);

	/* test storage */
	printf("Trying storage devices...\n");
	for (i = 0; i < devs_no; i++) {
		di = ub_dev_get(i);

		if (di->type & DEV_TYP_STOR)
			break;

	}
	if (i == devs_no)
		printf("No storage devices available\n");
	else {
		memset(buf, 0, BUF_SZ);

		if ((rv = ub_dev_open(i)) != 0)
			errf("open device %d error %d\n", i, rv);

		else if ((rv = ub_dev_read(i, buf, 1, 0, &rlen)) != 0)
			errf("could not read from device %d, error %d\n", i, rv);
		else {
			printf("Sector 0 dump (512B):\n");
			test_dump_buf(buf, 512);
		}

		ub_dev_close(i);
	}

	/* test networking */
	printf("Trying network devices...\n");
	for (i = 0; i < devs_no; i++) {
		di = ub_dev_get(i);

		if (di->type == DEV_TYP_NET)
			break;

	}
	if (i == devs_no)
		printf("No network devices available\n");
	else {
		if ((rv = ub_dev_open(i)) != 0)
			errf("open device %d error %d\n", i, rv);
		else if ((rv = ub_dev_send(i, &buf, 2048)) != 0)
			errf("could not send to device %d, error %d\n", i, rv);

		ub_dev_close(i);
	}

	if (ub_dev_close(h) != 0)
		errf("could not close device %d\n", h);

	printf("\n*** Env vars ***\n");

	printf("ethact = %s\n", ub_env_get("ethact"));
	printf("old fileaddr = %s\n", ub_env_get("fileaddr"));
	ub_env_set("fileaddr", "deadbeef");
	printf("new fileaddr = %s\n", ub_env_get("fileaddr"));

	const char *env = NULL;

	while ((env = ub_env_enum(env)) != NULL)
		printf("%s = %s\n", env, ub_env_get(env));

	/* reset */
	printf("\n*** Resetting board ***\n");
	ub_reset();
	printf("\nHmm, reset returned...?!\n");

	return rv;
}

void test_dump_sig(struct api_signature *sig)
{
	printf("signature:\n");
	printf("  version\t= %d\n", sig->version);
	printf("  checksum\t= 0x%08x\n", sig->checksum);
	printf("  sc entry\t= 0x%08x\n", (unsigned int)sig->syscall);
}

void test_dump_si(struct sys_info *si)
{
	int i;

	printf("sys info:\n");
	printf("  clkbus\t= 0x%08x\n", (unsigned int)si->clk_bus);
	printf("  clkcpu\t= 0x%08x\n", (unsigned int)si->clk_cpu);
	printf("  bar\t\t= 0x%08x\n", (unsigned int)si->bar);

	printf("---\n");
	for (i = 0; i < si->mr_no; i++) {
		if (si->mr[i].flags == 0)
			break;

		printf("  start\t= 0x%08lx\n", si->mr[i].start);
		printf("  size\t= 0x%08lx\n", si->mr[i].size);

		switch(si->mr[i].flags & 0x000F) {
			case MR_ATTR_FLASH:
				printf("  type FLASH\n");
				break;
			case MR_ATTR_DRAM:
				printf("  type DRAM\n");
				break;
			case MR_ATTR_SRAM:
				printf("  type SRAM\n");
				break;
			default:
				printf("  type UNKNOWN\n");
		}
		printf("---\n");
	}
}

static char *test_stor_typ(int type)
{
	if (type & DT_STOR_IDE)
		return "IDE";

	if (type & DT_STOR_MMC)
		return "MMC";

	if (type & DT_STOR_SATA)
		return "SATA";

	if (type & DT_STOR_SCSI)
		return "SCSI";

	if (type & DT_STOR_USB)
		return "USB";

	return "Unknown";
}

void test_dump_buf(void *buf, int len)
{
	int i;
	int line_counter = 0;
	int sep_flag = 0;
	int addr = 0;

	printf("%07x:\t", addr);

	for (i = 0; i < len; i++) {
		if (line_counter++ > 15) {
			line_counter = 0;
			sep_flag = 0;
			addr += 16;
			i--;
			printf("\n%07x:\t", addr);
			continue;
		}

		if (sep_flag++ > 1) {
			sep_flag = 1;
			printf(" ");
		}

		printf("%02x", *((char *)buf++));
	}

	printf("\n");
}

void test_dump_di(int handle)
{
	int i;
	struct device_info *di = ub_dev_get(handle);

	printf("device info (%d):\n", handle);
	printf("  cookie\t= 0x%08x\n", (uint32_t)di->cookie);
	printf("  type\t\t= 0x%08x\n", di->type);

	if (di->type == DEV_TYP_NET) {
		printf("  hwaddr\t= ");
		for (i = 0; i < 6; i++)
			printf("%02x ", di->di_net.hwaddr[i]);

		printf("\n");

	} else if (di->type & DEV_TYP_STOR) {
		printf("  type\t\t= %s\n", test_stor_typ(di->type));
		printf("  blk size\t\t= %d\n", (unsigned int)di->di_stor.block_size);
		printf("  blk count\t\t= %d\n", (unsigned int)di->di_stor.block_count);
	}
}
