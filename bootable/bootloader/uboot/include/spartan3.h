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
 * (C) Copyright 2002
 * Rich Ireland, Enterasys Networks, rireland@enterasys.com.
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

#ifndef _SPARTAN3_H_
#define _SPARTAN3_H_

#include <xilinx.h>

extern int Spartan3_load( Xilinx_desc *desc, void *image, size_t size );
extern int Spartan3_dump( Xilinx_desc *desc, void *buf, size_t bsize );
extern int Spartan3_info( Xilinx_desc *desc );

/* Slave Parallel Implementation function table */
typedef struct {
	Xilinx_pre_fn	pre;
	Xilinx_pgm_fn	pgm;
	Xilinx_init_fn	init;
	Xilinx_err_fn	err;
	Xilinx_done_fn	done;
	Xilinx_clk_fn	clk;
	Xilinx_cs_fn	cs;
	Xilinx_wr_fn	wr;
	Xilinx_rdata_fn	rdata;
	Xilinx_wdata_fn	wdata;
	Xilinx_busy_fn	busy;
	Xilinx_abort_fn	abort;
	Xilinx_post_fn	post;
} Xilinx_Spartan3_Slave_Parallel_fns;

/* Slave Serial Implementation function table */
typedef struct {
	Xilinx_pre_fn	pre;
	Xilinx_pgm_fn	pgm;
	Xilinx_clk_fn	clk;
	Xilinx_init_fn	init;
	Xilinx_done_fn	done;
	Xilinx_wr_fn	wr;
	Xilinx_post_fn	post;
	Xilinx_bwr_fn	bwr; /* block write function */
} Xilinx_Spartan3_Slave_Serial_fns;

/* Device Image Sizes
 *********************************************************************/
/* Spartan-III (1.2V) */
#define XILINX_XC3S50_SIZE	439264/8
#define XILINX_XC3S200_SIZE	1047616/8
#define XILINX_XC3S400_SIZE	1699136/8
#define XILINX_XC3S1000_SIZE	3223488/8
#define XILINX_XC3S1500_SIZE	5214784/8
#define XILINX_XC3S2000_SIZE	7673024/8
#define XILINX_XC3S4000_SIZE	11316864/8
#define XILINX_XC3S5000_SIZE	13271936/8

/* Spartan-3E (v3.4) */
#define	XILINX_XC3S100E_SIZE	581344/8
#define	XILINX_XC3S250E_SIZE	1353728/8
#define	XILINX_XC3S500E_SIZE	2270208/8
#define	XILINX_XC3S1200E_SIZE	3841184/8
#define	XILINX_XC3S1600E_SIZE	5969696/8

/* Descriptor Macros
 *********************************************************************/
/* Spartan-III devices */
#define XILINX_XC3S50_DESC(iface, fn_table, cookie) \
{ Xilinx_Spartan3, iface, XILINX_XC3S50_SIZE, fn_table, cookie }

#define XILINX_XC3S200_DESC(iface, fn_table, cookie) \
{ Xilinx_Spartan3, iface, XILINX_XC3S200_SIZE, fn_table, cookie }

#define XILINX_XC3S400_DESC(iface, fn_table, cookie) \
{ Xilinx_Spartan3, iface, XILINX_XC3S400_SIZE, fn_table, cookie }

#define XILINX_XC3S1000_DESC(iface, fn_table, cookie) \
{ Xilinx_Spartan3, iface, XILINX_XC3S1000_SIZE, fn_table, cookie }

#define XILINX_XC3S1500_DESC(iface, fn_table, cookie) \
{ Xilinx_Spartan3, iface, XILINX_XC3S1500_SIZE, fn_table, cookie }

#define XILINX_XC3S2000_DESC(iface, fn_table, cookie) \
{ Xilinx_Spartan3, iface, XILINX_XC3S2000_SIZE, fn_table, cookie }

#define XILINX_XC3S4000_DESC(iface, fn_table, cookie) \
{ Xilinx_Spartan3, iface, XILINX_XC3S4000_SIZE, fn_table, cookie }

#define XILINX_XC3S5000_DESC(iface, fn_table, cookie) \
{ Xilinx_Spartan3, iface, XILINX_XC3S5000_SIZE, fn_table, cookie }

/* Spartan-3E devices */
#define XILINX_XC3S100E_DESC(iface, fn_table, cookie) \
{ Xilinx_Spartan3, iface, XILINX_XC3S100E_SIZE, fn_table, cookie }

#define XILINX_XC3S250E_DESC(iface, fn_table, cookie) \
{ Xilinx_Spartan3, iface, XILINX_XC3S250E_SIZE, fn_table, cookie }

#define XILINX_XC3S500E_DESC(iface, fn_table, cookie) \
{ Xilinx_Spartan3, iface, XILINX_XC3S500E_SIZE, fn_table, cookie }

#define XILINX_XC3S1200E_DESC(iface, fn_table, cookie) \
{ Xilinx_Spartan3, iface, XILINX_XC3S1200E_SIZE, fn_table, cookie }

#define XILINX_XC3S1600E_DESC(iface, fn_table, cookie) \
{ Xilinx_Spartan3, iface, XILINX_XC3S1600E_SIZE, fn_table, cookie }

#endif /* _SPARTAN3_H_ */
