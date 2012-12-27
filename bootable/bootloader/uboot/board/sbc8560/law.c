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
 * Copyright 2008 Freescale Semiconductor, Inc.
 *
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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
#include <asm/fsl_law.h>
#include <asm/mmu.h>

/* LAW(Local Access Window) configuration:
 * 0000_0000-0800_0000: DDR(512M) -or- larger
 * c000_0000-cfff_ffff: PCI(256M)
 * d000_0000-dfff_ffff: RapidIO(256M)
 * e000_0000-ffff_ffff: localbus(512M)
 *   e000_0000-e3ff_ffff: LBC 64M, 32-bit flash on CS6
 *   e400_0000-e7ff_ffff: LBC 64M, 32-bit flash on CS1
 *   e800_0000-efff_ffff: LBC 128M, nothing here
 *   f000_0000-f3ff_ffff: LBC 64M, SDRAM on CS3
 *   f400_0000-f7ff_ffff: LBC 64M, SDRAM on CS4
 *   f800_0000-fdff_ffff: LBC 64M, nothing here
 *   fc00_0000-fcff_ffff: LBC 16M, CSR,RTC,UART,etc on CS5
 *   fd00_0000-fdff_ffff: LBC 16M, nothing here
 *   fe00_0000-feff_ffff: LBC 16M, nothing here
 *   ff00_0000-ff6f_ffff: LBC 7M, nothing here
 *   ff70_0000-ff7f_ffff: CCSRBAR 1M
 *   ff80_0000-ffff_ffff: LBC 8M, 8-bit flash on CS0
 * Note: CCSRBAR and L2-as-SRAM don't need configure Local Access
 *       Window.
 * Note: If flash is 8M at default position(last 8M),no LAW needed.
 */

struct law_entry law_table[] = {
#ifndef CONFIG_SPD_EEPROM
	SET_LAW(CONFIG_SYS_DDR_SDRAM_BASE, LAW_SIZE_512M, LAW_TRGT_IF_DDR),
#endif
	SET_LAW(CONFIG_SYS_PCI_MEM_PHYS, LAW_SIZE_256M, LAW_TRGT_IF_PCI),
	SET_LAW(CONFIG_SYS_LBC_SDRAM_BASE, LAW_SIZE_512M, LAW_TRGT_IF_LBC),
};

int num_law_entries = ARRAY_SIZE(law_table);
