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

/* This test verifies if the reason of last reset was an abnormal voltage
 * condition, than it performs watchdog test, measuing time required to
 * trigger watchdog reset.
 */

#include <post.h>

#if CONFIG_POST & CONFIG_SYS_POST_WATCHDOG

#include <watchdog.h>
#include <asm/gpio.h>
#include <asm/io.h>

static uint watchdog_magic_read(void)
{
	return in_be32((void *)CONFIG_SYS_WATCHDOG_FLAGS_ADDR) &
		CONFIG_SYS_WATCHDOG_MAGIC_MASK;
}

static void watchdog_magic_write(uint value)
{
	out_be32((void *)CONFIG_SYS_WATCHDOG_FLAGS_ADDR, value |
		(in_be32((void *)CONFIG_SYS_WATCHDOG_FLAGS_ADDR) &
			~CONFIG_SYS_WATCHDOG_MAGIC_MASK));
}

int sysmon1_post_test(int flags)
{
	if (gpio_read_in_bit(CONFIG_SYS_GPIO_SYSMON_STATUS) == 0) {
		/*
		 * 3.1. GPIO62 is low
		 * Assuming system voltage failure.
		 */
		post_log("Abnormal voltage detected (GPIO62)\n");
		return 1;
	}

	return 0;
}

int lwmon5_watchdog_post_test(int flags)
{
	/* On each reset scratch register 1 should be tested,
	 * but first test GPIO62:
	 */
	if (!(flags & POST_MANUAL) && sysmon1_post_test(flags)) {
		/* 3.1. GPIO62 is low
		 * Assuming system voltage failure.
		 */
		/* 3.1.1. Set scratch register 1 to 0x0000xxxx */
		watchdog_magic_write(0);
		/* 3.1.2. Mark test as failed due to voltage?! */
		return 1;
	}

	if (watchdog_magic_read() != CONFIG_SYS_WATCHDOG_MAGIC) {
		/* 3.2. Scratch register 1 differs from magic value 0x1248xxxx
		 * Assuming PowerOn
		 */
		int ints;
		ulong base;
		ulong time;

		/* 3.2.1. Set magic value to scratch register */
		watchdog_magic_write(CONFIG_SYS_WATCHDOG_MAGIC);

		ints = disable_interrupts ();
		/* 3.2.2. strobe watchdog once */
		WATCHDOG_RESET();
		out_be32((void *)CONFIG_SYS_WATCHDOG_TIME_ADDR, 0);
		/* 3.2.3. save time of strobe in scratch register 2 */
		base = post_time_ms (0);

		/* 3.2.4. Wait for 150 ms (enough for reset to happen) */
		while ((time = post_time_ms (base)) < 150)
			out_be32((void *)CONFIG_SYS_WATCHDOG_TIME_ADDR, time);
		if (ints)
			enable_interrupts ();

		/* 3.2.5. Reset didn't happen. - Set 0x0000xxxx
		 * into scratch register 1
		 */
		watchdog_magic_write(0);
		/* 3.2.6. Mark test as failed. */
		post_log("hw watchdog time : %u ms, failed ", time);
		return 2;
	} else {
		/* 3.3. Scratch register matches magic value 0x1248xxxx
		 * Assume this is watchdog-initiated reset
		 */
		ulong time;
		/* 3.3.1. So, the test succeed, save measured time to syslog. */
		time = in_be32((void *)CONFIG_SYS_WATCHDOG_TIME_ADDR);
		post_log("hw watchdog time : %u ms, passed ", time);
		/* 3.3.2. Set scratch register 1 to 0x0000xxxx */
		watchdog_magic_write(0);
		return 0;
	}
	return -1;
}

#endif /* CONFIG_POST & CONFIG_SYS_POST_WATCHDOG */