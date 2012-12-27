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
 * (C) Copyright 2008
 * Sergei Poselenov, Emcraft Systems, sposelenov@emcraft.com.
 *
 * Copyright 2004, 2007 Freescale Semiconductor, Inc.
 * (C) Copyright 2003 Motorola Inc.
 * Xianghua Xiao, (X.Xiao@motorola.com)
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.         See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __UPM_TABLE_H
#define __UPM_TABLE_H

/* UPM Table Configuration Code for FPGA access */
static const unsigned int UPMTableA[] =
{
	0x00fcec00,  0x00fcec00,  0x00fcec00,  0x00fcec00, /* Words 0 to 3	*/
	0x00fcec00,  0x00fcfc00,  0x00fcfc00,  0x00fcec05, /* Words 4 to 7	*/
	0x00fcec00,  0x00fcec00,  0x00fcec04,  0x00fcec04, /* Words 8 to 11	*/
	0x00fcec04,  0x00fcec04,  0x00fcec04,  0x00fcec04, /* Words 12 to 15	*/
	0x00fcec04,  0x00fcec04,  0x0fffec00,  0xffffec00, /* Words 16 to 19	*/
	0xffffec00,  0xffffec00,  0xffffec00,  0xffffec01, /* Words 20 to 23	*/
	0x00ffec00,  0x00ffec00,  0x00f3ec00,  0x0fffec00, /* Words 24 to 27	*/
	0x0ffffc04,  0xffffec00,  0xffffec00,  0xffffec01, /* Words 28 to 31	*/
	0x00ffec00,  0x00ffec00,  0x00f3ec04,  0x00f3ec04, /* Words 32 to 35	*/
	0x00f3ec04,  0x00f3ec04,  0x00f3ec04,  0x00f3ec04, /* Words 36 to 39	*/
	0x00f3ec04,  0x00f3ec04,  0x0fffec00,  0xffffec00, /* Words 40 to 43	*/
	0xffffec00,  0xffffec00,  0xffffec00,  0xffffec01, /* Words 44 to 47	*/
	0xffffec00,  0xffffec00,  0xffffec00,  0xffffec00, /* Words 48 to 51	*/
	0xffffec00,  0xffffec00,  0xffffec00,  0xffffec00, /* Words 52 to 55	*/
	0xffffec00,  0xffffec00,  0xffffec00,  0xffffec01, /* Words 56 to 59	*/
	0xffffec00,  0xffffec00,  0xffffec00,  0xffffec01  /* Words 60 to 63	*/
};

/* LIME UPM B Table Configuration Code */
static unsigned int UPMTableB[] =
{
	0x0ffefc00,  0x0ffcfc00,  0x0ffcfc00,  0x0ffcfc00, /* Words 0 to 3	*/
	0x0ffcfc00,  0x0ffcfc00,  0x0ffcfc04,  0x0ffffc01, /* Words 4 to 7	*/
	0x0ffefc00,  0x0ffcfc00,  0x0ffcfc00,  0x0ffcfc00, /* Words 8 to 11	*/
	0x0ffcfc00,  0x0ffcfc00,  0x0ffcfc04,  0x0ffcfc04, /* Words 12 to 15	*/
	0x0ffcfc04,  0x0ffcfc04,  0x0ffcfc04,  0x0ffcfc04, /* Words 16 to 19	*/
	0x0ffcfc04,  0x0ffcfc04,  0x0ffffc00,  0xfffffc01, /* Words 20 to 23	*/
	0x0cfffc00,  0x00fffc00,  0x00fffc00,  0x00fffc00, /* Words 24 to 27	*/
	0x00fffc00,  0x00fffc00,  0x00fffc04,  0x0ffffc01, /* Words 28 to 31	*/
	0x0cfffc00,  0x00fffc00,  0x00fffc00,  0x00fffc00, /* Words 32 to 35	*/
	0x00fffc00,  0x00fffc00,  0x00fffc04,  0x00fffc04, /* Words 36 to 39	*/
	0x00fffc04,  0x00fffc04,  0x00fffc04,  0x00fffc04, /* Words 40 to 43	*/
	0x00fffc04,  0x00fffc04,  0x0ffffc00,  0xfffffc01, /* Words 44 to 47	*/
	0xfffffc00,  0xfffffc00,  0xfffffc00,  0xfffffc00, /* Words 48 to 51	*/
	0xfffffc00,  0xfffffc00,  0xfffffc00,  0xfffffc00, /* Words 52 to 55	*/
	0xfffffc00,  0xfffffc00,  0xfffffc00,  0xfffffc01, /* Words 56 to 59	*/
	0xfffffc00,  0xfffffc00,  0xfffffc00,  0xfffffc01  /* Words 60 to 63	*/
};
#endif
