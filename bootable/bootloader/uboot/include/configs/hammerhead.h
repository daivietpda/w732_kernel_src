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
 * Copyright (C) 2008 Miromico AG
 *
 * Configuration settings for the Miromico Hammerhead AVR32 board
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
#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_AVR32			1
#define CONFIG_AT32AP			1
#define CONFIG_AT32AP7000		1
#define CONFIG_HAMMERHEAD		1

#define CONFIG_SYS_HZ				1000

/*
 * Set up the PLL to run at 125 MHz, the CPU to run at the PLL
 * frequency, the HSB and PBB busses to run at 1/2 the PLL frequency
 * and the PBA bus to run at 1/4 the PLL frequency.
 */
#define CONFIG_PLL			1
#define CONFIG_SYS_POWER_MANAGER		1
#define CONFIG_SYS_OSC0_HZ			25000000
#define CONFIG_SYS_PLL0_DIV			1
#define CONFIG_SYS_PLL0_MUL			5
#define CONFIG_SYS_PLL0_SUPPRESS_CYCLES	16
#define CONFIG_SYS_CLKDIV_CPU			0
#define CONFIG_SYS_CLKDIV_HSB			1
#define CONFIG_SYS_CLKDIV_PBA			2
#define CONFIG_SYS_CLKDIV_PBB			1

/*
 * The PLLOPT register controls the PLL like this:
 *   icp = PLLOPT<2>
 *   ivco = PLLOPT<1:0>
 *
 * We want icp=1 (default) and ivco=0 (80-160 MHz) or ivco=2 (150-240MHz).
 */
#define CONFIG_SYS_PLL0_OPT			0x04

#define CONFIG_USART1			1

#define CONFIG_HOSTNAME			hammerhead

/* User serviceable stuff */
#define CONFIG_DOS_PARTITION		1

#define CONFIG_CMDLINE_TAG		1
#define CONFIG_SETUP_MEMORY_TAGS	1
#define CONFIG_INITRD_TAG		1

#define CONFIG_STACKSIZE		(2048)

#define CONFIG_BAUDRATE			115200
#define CONFIG_BOOTARGS							\
	"console=ttyS0 root=mtd1 rootfstype=jffs2"
#define CONFIG_BOOTCOMMAND						\
	"fsload; bootm"

/*
 * Only interrupt autoboot if <space> is pressed. Otherwise, garbage
 * data on the serial line may interrupt the boot sequence.
 */
#define CONFIG_BOOTDELAY		1
#define CONFIG_AUTOBOOT			1
#define CONFIG_AUTOBOOT_KEYED		1
#define CONFIG_AUTOBOOT_PROMPT				\
	"Press SPACE to abort autoboot in %d seconds\n", bootdelay
#define CONFIG_AUTOBOOT_DELAY_STR	"d"
#define CONFIG_AUTOBOOT_STOP_STR	" "

/*
 * After booting the board for the first time, new ethernet address
 * should be generated and assigned to the environment variables
 * "ethaddr". This is normally done during production.
 */
#define CONFIG_OVERWRITE_ETHADDR_ONCE	1
#define CONFIG_NET_MULTI		1

/*
 * BOOTP/DHCP options
 */
#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY

/*
 * Command line configuration.
 */
#include <config_cmd_default.h>

#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_MMC
#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_SETGETDCR

#define CONFIG_ATMEL_USART		1
#define CONFIG_MACB			1
#define CONFIG_PORTMUX_PIO		1
#define CONFIG_SYS_NR_PIOS			5
#define CONFIG_SYS_HSDRAMC			1
#define CONFIG_MMC			1
#define CONFIG_ATMEL_MCI		1

#define CONFIG_SYS_DCACHE_LINESZ		32
#define CONFIG_SYS_ICACHE_LINESZ		32

#define CONFIG_NR_DRAM_BANKS		1

#define CONFIG_SYS_FLASH_CFI			1
#define CONFIG_FLASH_CFI_DRIVER		1

#define CONFIG_SYS_FLASH_BASE			0x00000000
#define CONFIG_SYS_FLASH_SIZE			0x800000
#define CONFIG_SYS_MAX_FLASH_BANKS		1
#define CONFIG_SYS_MAX_FLASH_SECT		135

#define CONFIG_SYS_MONITOR_BASE		CONFIG_SYS_FLASH_BASE

#define CONFIG_SYS_INTRAM_BASE			0x24000000
#define CONFIG_SYS_INTRAM_SIZE			0x8000

#define CONFIG_SYS_SDRAM_BASE			0x10000000

#define CONFIG_ENV_IS_IN_FLASH		1
#define CONFIG_ENV_SIZE			65536
#define CONFIG_ENV_ADDR			(CONFIG_SYS_FLASH_BASE + CONFIG_SYS_FLASH_SIZE - CONFIG_ENV_SIZE)

#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_INTRAM_BASE + CONFIG_SYS_INTRAM_SIZE)

#define CONFIG_SYS_MALLOC_LEN			(256*1024)

#define CONFIG_SYS_DMA_ALLOC_LEN		(16384)

/* Allow 4MB for the kernel run-time image */
#define CONFIG_SYS_LOAD_ADDR			(CONFIG_SYS_SDRAM_BASE + 0x00400000)
#define CONFIG_SYS_BOOTPARAMS_LEN		(16 * 1024)

/* Other configuration settings that shouldn't have to change all that often */
#define CONFIG_SYS_PROMPT			"Hammerhead> "
#define CONFIG_SYS_CBSIZE			256
#define CONFIG_SYS_MAXARGS			16
#define CONFIG_SYS_PBSIZE			(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_LONGHELP			1

#define CONFIG_SYS_MEMTEST_START		CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END			(CONFIG_SYS_MEMTEST_START + 0x1f00000)

#define CONFIG_SYS_BAUDRATE_TABLE { 115200, 38400, 19200, 9600, 2400 }

#endif /* __CONFIG_H */
