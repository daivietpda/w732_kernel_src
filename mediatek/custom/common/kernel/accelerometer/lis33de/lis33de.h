/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
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

/* linux/drivers/hwmon/lis33de.c
 *
 * (C) Copyright 2008 
 * MediaTek <www.mediatek.com>
 *
 * LIS33DE driver for MT6516
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef LIS33DE_H
#define LIS33DE_H
	 
#include <linux/ioctl.h>

#define LIS33DE_I2C_SLAVE_ADDR		0x38//0x38<-> SD0=GND;0x3A<-> SD0=High
	 
	 /* LIS33DE Register Map  (Please refer to LIS33DE Specifications) */
#define LIS33DE_REG_CTL_REG1		0x20
#define LIS33DE_REG_CTL_REG2		0x21
#define LIS33DE_REG_CTL_REG3		0x22
#define LIS33DE_REG_DATAX0		    0x28
#define LIS33DE_REG_OUT_X		    0x29
#define LIS33DE_REG_OUT_Y		    0x2B
#define LIS33DE_REG_OUT_Z		    0x2D

/*
#define LIS33DE_REG_DEVID			0x00
#define LIS33DE_REG_THRESH_TAP		0x1D
#define LIS33DE_REG_OFSX			0x1E
#define LIS33DE_REG_OFSY			0x1F
#define LIS33DE_REG_OFSZ			0x20
#define LIS33DE_REG_DUR				0x21
#define LIS33DE_REG_THRESH_ACT		0x24
#define LIS33DE_REG_THRESH_INACT	0x25
#define LIS33DE_REG_TIME_INACT		0x26
#define LIS33DE_REG_ACT_INACT_CTL	0x27
#define LIS33DE_REG_THRESH_FF		0x28
#define LIS33DE_REG_TIME_FF			0x29
#define LIS33DE_REG_TAP_AXES		0x2A
#define LIS33DE_REG_ACT_TAP_STATUS	0x2B
#define	LIS33DE_REG_BW_RATE			0x2C
#define LIS33DE_REG_POWER_CTL		0x2D
#define LIS33DE_REG_INT_ENABLE		0x2E
#define LIS33DE_REG_INT_MAP			0x2F
#define LIS33DE_REG_INT_SOURCE		0x30
#define LIS33DE_REG_DATA_FORMAT		0x31
#define LIS33DE_REG_DATAX0			0x32
#define LIS33DE_REG_FIFO_CTL		0x38
#define LIS33DE_REG_FIFO_STATUS		0x39
*/

#define LIS33DE_FIXED_DEVID			0xE5
	 
//#define LIS33DE_BW_200HZ			0x0C
#define LIS33DE_BW_400HZ			0x80 //400 or 100 on other choise //changed
//#define LIS33DE_BW_50HZ				0x0A

#define	LIS33DE_FULLRANG_LSB		0XFF
	 
#define LIS33DE_MEASURE_MODE		0x40	//changed 
#define LIS33DE_DATA_READY			0x07    //changed
	 
//#define LIS33DE_FULL_RES			0x08
//#define LIS33DE_RANGE_2G			0x00
//#define LIS33DE_RANGE_4G			0x01
#define LIS33DE_RANGE_8G			0x20 //8g or 2g no ohter choise//changed
//#define LIS33DE_RANGE_16G			0x03
#define LIS33DE_SELF_TEST           0x10 //changed
	 
#define LIS33DE_STREAM_MODE			0x80
#define LIS33DE_SAMPLES_15			0x0F
	 
#define LIS33DE_FS_8G_LSB_G			64
#define LIS33DE_FS_4G_LSB_G			128
#define LIS33DE_FS_2G_LSB_G			256
	 
#define LIS33DE_LEFT_JUSTIFY		0x04
#define LIS33DE_RIGHT_JUSTIFY		0x00
	 
	 
#define LIS33DE_SUCCESS						0
#define LIS33DE_ERR_I2C						-1
#define LIS33DE_ERR_STATUS					-3
#define LIS33DE_ERR_SETUP_FAILURE			-4
#define LIS33DE_ERR_GETGSENSORDATA			-5
#define LIS33DE_ERR_IDENTIFICATION			-6
	 
	 
	 
#define LIS33DE_BUFSIZE				256
	 
#endif

