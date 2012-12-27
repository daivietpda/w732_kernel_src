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
 * AX88796L(NE2000) support
 *
 * (c) 2007 Nobuhiro Iwamatsu <iwamatsu@nigauri.org>
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

#ifndef __DRIVERS_AX88796L_H__
#define __DRIVERS_AX88796L_H__

#define DP_DATA		(0x10 << 1)
#define START_PG	0x40	/* First page of TX buffer */
#define START_PG2	0x48
#define STOP_PG		0x80	/* Last page +1 of RX ring */
#define TX_PAGES	12
#define RX_START	(START_PG+TX_PAGES)
#define RX_END		STOP_PG

#define AX88796L_BASE_ADDRESS	CONFIG_DRIVER_NE2000_BASE
#define AX88796L_BYTE_ACCESS	0x00001000
#define AX88796L_OFFSET		0x00000400
#define AX88796L_ADDRESS_BYTE	AX88796L_BASE_ADDRESS + \
		AX88796L_BYTE_ACCESS + AX88796L_OFFSET
#define AX88796L_REG_MEMR	AX88796L_ADDRESS_BYTE + (0x14<<1)
#define AX88796L_REG_CR		AX88796L_ADDRESS_BYTE + (0x00<<1)

#define AX88796L_CR		(*(vu_short *)(AX88796L_REG_CR))
#define AX88796L_MEMR		(*(vu_short *)(AX88796L_REG_MEMR))

#define EECS_HIGH		(AX88796L_MEMR |= 0x10)
#define EECS_LOW		(AX88796L_MEMR &= 0xef)
#define EECLK_HIGH		(AX88796L_MEMR |= 0x80)
#define EECLK_LOW		(AX88796L_MEMR &= 0x7f)
#define EEDI_HIGH		(AX88796L_MEMR |= 0x20)
#define EEDI_LOW		(AX88796L_MEMR &= 0xdf)
#define EEDO			((AX88796L_MEMR & 0x40)>>6)

#define PAGE0_SET		(AX88796L_CR &= 0x3f)
#define PAGE1_SET		(AX88796L_CR = (AX88796L_CR & 0x3f) | 0x40)

#define BIT_DUMMY	0
#define MAC_EEP_READ	1
#define MAC_EEP_WRITE	2
#define MAC_EEP_ERACE	3
#define MAC_EEP_EWEN	4
#define MAC_EEP_EWDS	5

/* R7780MP Specific code */
#if defined(CONFIG_R7780MP)
#define ISA_OFFSET	0x1400
#define DP_IN(_b_, _o_, _d_)	(_d_) = \
	*( (vu_short *) ((_b_) + ((_o_) * 2) + ISA_OFFSET))
#define DP_OUT(_b_, _o_, _d_) \
	*((vu_short *)((_b_) + ((_o_) * 2) + ISA_OFFSET)) = (_d_)
#define DP_IN_DATA(_b_, _d_)	(_d_) = *( (vu_short *) ((_b_) + ISA_OFFSET))
#define DP_OUT_DATA(_b_, _d_)	*( (vu_short *) ((_b_)+ISA_OFFSET)) = (_d_)
#else
/* Please change for your target boards */
#define ISA_OFFSET	0x0000
#define DP_IN(_b_, _o_, _d_)	(_d_) = *( (vu_short *)((_b_)+(_o_ )+ISA_OFFSET))
#define DP_OUT(_b_, _o_, _d_)	*((vu_short *)((_b_)+(_o_)+ISA_OFFSET)) = (_d_)
#define DP_IN_DATA(_b_, _d_)	(_d_) = *( (vu_short *) ((_b_)+ISA_OFFSET))
#define DP_OUT_DATA(_b_, _d_)	*( (vu_short *) ((_b_)+ISA_OFFSET)) = (_d_)
#endif

#endif /* __DRIVERS_AX88796L_H__ */
