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

#ifndef __BOARD_CPU87__
#define __BOARD_CPU87__

#include <config.h>

#define REG8(x)			(*(volatile unsigned char *)(x))

/* CPU86 register definitions */
#define CPU86_VME_EAC		REG8(CONFIG_SYS_BCRS_BASE + 0x00)
#define CPU86_VME_SAC		REG8(CONFIG_SYS_BCRS_BASE + 0x01)
#define CPU86_VME_MAC		REG8(CONFIG_SYS_BCRS_BASE + 0x02)
#define CPU86_BCR		REG8(CONFIG_SYS_BCRS_BASE + 0x03)
#define CPU86_BSR		REG8(CONFIG_SYS_BCRS_BASE + 0x04)
#define CPU86_WDOG_RPORT	REG8(CONFIG_SYS_BCRS_BASE + 0x05)
#define CPU86_MBOX_IRQ		REG8(CONFIG_SYS_BCRS_BASE + 0x04)
#define CPU86_REV		REG8(CONFIG_SYS_BCRS_BASE + 0x07)
#define CPU86_VME_IRQMASK	REG8(CONFIG_SYS_BCRS_BASE + 0x80)
#define CPU86_VME_IRQSTATUS	REG8(CONFIG_SYS_BCRS_BASE + 0x81)
#define CPU86_LOCAL_IRQMASK	REG8(CONFIG_SYS_BCRS_BASE + 0x82)
#define CPU86_LOCAL_IRQSTATUS	REG8(CONFIG_SYS_BCRS_BASE + 0x83)
#define CPU86_PMCL_IRQSTATUS	REG8(CONFIG_SYS_BCRS_BASE + 0x84)

/* Board Control Register bits */
#define CPU86_BCR_FWPT		0x01
#define CPU86_BCR_FWRE		0x02

#endif /* __BOARD_CPU87__ */
