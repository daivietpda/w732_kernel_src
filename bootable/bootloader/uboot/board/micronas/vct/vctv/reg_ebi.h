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
 * (C) Copyright 2008 Stefan Roese <sr@denx.de>, DENX Software Engineering
 *
 * Copyright (C) 2006 Micronas GmbH
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

#ifndef _REG_EBI_PLATINUMAVC_H_
#define _REG_EBI_PLATINUMAVC_H_

#define EBI_BASE			0x00014000

/*  Relative offsets of the register adresses */

#define EBI_CPU_IO_ACCS_OFFS		0x00000000
#define EBI_CPU_IO_ACCS(base)		((base) + EBI_CPU_IO_ACCS_OFFS)
#define EBI_IO_ACCS_DATA_OFFS		0x00000004
#define EBI_IO_ACCS_DATA(base)		((base) + EBI_IO_ACCS_DATA_OFFS)
#define EBI_CPU_IO_ACCS2_OFFS		0x00000008
#define EBI_CPU_IO_ACCS2(base)		((base) + EBI_CPU_IO_ACCS2_OFFS)
#define EBI_IO_ACCS2_DATA_OFFS		0x0000000C
#define EBI_IO_ACCS2_DATA(base)		((base) + EBI_IO_ACCS2_DATA_OFFS)
#define EBI_CTRL_OFFS			0x00000010
#define EBI_CTRL(base)			((base) + EBI_CTRL_OFFS)
#define EBI_IRQ_MASK_OFFS		0x00000018
#define EBI_IRQ_MASK(base)		((base) + EBI_IRQ_MASK_OFFS)
#define EBI_IRQ_MASK2_OFFS		0x0000001C
#define EBI_IRQ_MASK2(base)		((base) + EBI_IRQ_MASK2_OFFS)
#define EBI_TAG1_SYS_ID_OFFS		0x00000030
#define EBI_TAG1_SYS_ID(base)		((base) + EBI_TAG1_SYS_ID_OFFS)
#define EBI_TAG2_SYS_ID_OFFS		0x00000040
#define EBI_TAG2_SYS_ID(base)		((base) + EBI_TAG2_SYS_ID_OFFS)
#define EBI_TAG3_SYS_ID_OFFS		0x00000050
#define EBI_TAG3_SYS_ID(base)		((base) + EBI_TAG3_SYS_ID_OFFS)
#define EBI_TAG4_SYS_ID_OFFS		0x00000060
#define EBI_TAG4_SYS_ID(base)		((base) + EBI_TAG4_SYS_ID_OFFS)
#define EBI_GEN_DMA_CTRL_OFFS		0x00000070
#define EBI_GEN_DMA_CTRL(base)		((base) + EBI_GEN_DMA_CTRL_OFFS)
#define EBI_STATUS_OFFS			0x00000080
#define EBI_STATUS(base)		((base) + EBI_STATUS_OFFS)
#define EBI_STATUS_DMA_CNT_OFFS		0x00000084
#define EBI_STATUS_DMA_CNT(base)	((base) + EBI_STATUS_DMA_CNT_OFFS)
#define EBI_SIG_LEVEL_OFFS		0x00000088
#define EBI_SIG_LEVEL(base)		((base) + EBI_SIG_LEVEL_OFFS)
#define EBI_CTRL_SIG_ACTLV_OFFS		0x0000008C
#define EBI_CTRL_SIG_ACTLV(base)	((base) + EBI_CTRL_SIG_ACTLV_OFFS)
#define EBI_CRC_GEN_OFFS		0x00000090
#define EBI_CRC_GEN(base)		((base) + EBI_CRC_GEN_OFFS)
#define EBI_EXT_ADDR_OFFS		0x000000A0
#define EBI_EXT_ADDR(base)		((base) + EBI_EXT_ADDR_OFFS)
#define EBI_IRQ_STATUS_OFFS		0x000000B0
#define EBI_IRQ_STATUS(base)		((base) + EBI_IRQ_STATUS_OFFS)
#define EBI_IRQ_STATUS2_OFFS		0x000000B4
#define EBI_IRQ_STATUS2(base)		((base) + EBI_IRQ_STATUS2_OFFS)
#define EBI_EXT_MASTER_SRAM_HIGH_OFFS	0x000000C0
#define EBI_EXT_MASTER_SRAM_HIGH(base)	((base) + EBI_EXT_MASTER_SRAM_HIGH_OFFS)
#define EBI_EXT_MASTER_SRAM_LOW_OFFS	0x000000C4
#define EBI_EXT_MASTER_SRAM_LOW(base)	((base) + EBI_EXT_MASTER_SRAM_LOW_OFFS)
#define EBI_ECC0_OFFS			0x000000D0
#define EBI_ECC0(base)			((base) + EBI_ECC0_OFFS)
#define EBI_ECC1_OFFS			0x000000D4
#define EBI_ECC1(base)			((base) + EBI_ECC1_OFFS)
#define EBI_ECC2_OFFS			0x000000D8
#define EBI_ECC2(base)			((base) + EBI_ECC2_OFFS)
#define EBI_ECC3_OFFS			0x000000DC
#define EBI_ECC3(base)			((base) + EBI_ECC3_OFFS)
#define EBI_DEV1_DMA_EXT_ADDR_OFFS	0x00000100
#define EBI_DEV1_DMA_EXT_ADDR(base)	((base) + EBI_DEV1_DMA_EXT_ADDR_OFFS)
#define EBI_DEV1_EXT_ACC_OFFS		0x00000104
#define EBI_DEV1_EXT_ACC(base)		((base) + EBI_DEV1_EXT_ACC_OFFS)
#define EBI_DEV1_CONFIG1_OFFS		0x00000108
#define EBI_DEV1_CONFIG1(base)		((base) + EBI_DEV1_CONFIG1_OFFS)
#define EBI_DEV1_CONFIG2_OFFS		0x0000010C
#define EBI_DEV1_CONFIG2(base)		((base) + EBI_DEV1_CONFIG2_OFFS)
#define EBI_DEV1_FIFO_CONFIG_OFFS	0x00000110
#define EBI_DEV1_FIFO_CONFIG(base)	((base) + EBI_DEV1_FIFO_CONFIG_OFFS)
#define EBI_DEV1_FLASH_CONF_ST_OFFS	0x00000114
#define EBI_DEV1_FLASH_CONF_ST(base)	((base) + EBI_DEV1_FLASH_CONF_ST_OFFS)
#define EBI_DEV1_DMA_CONFIG1_OFFS	0x00000118
#define EBI_DEV1_DMA_CONFIG1(base)	((base) + EBI_DEV1_DMA_CONFIG1_OFFS)
#define EBI_DEV1_DMA_CONFIG2_OFFS	0x0000011C
#define EBI_DEV1_DMA_CONFIG2(base)	((base) + EBI_DEV1_DMA_CONFIG2_OFFS)
#define EBI_DEV1_DMA_ECC_CTRL_OFFS	0x00000120
#define EBI_DEV1_DMA_ECC_CTRL(base)	((base) + EBI_DEV1_DMA_ECC_CTRL_OFFS)
#define EBI_DEV1_TIM1_RD1_OFFS		0x00000124
#define EBI_DEV1_TIM1_RD1(base)		((base) + EBI_DEV1_TIM1_RD1_OFFS)
#define EBI_DEV1_TIM1_RD2_OFFS		0x00000128
#define EBI_DEV1_TIM1_RD2(base)		((base) + EBI_DEV1_TIM1_RD2_OFFS)
#define EBI_DEV1_TIM1_WR1_OFFS		0x0000012C
#define EBI_DEV1_TIM1_WR1(base)		((base) + EBI_DEV1_TIM1_WR1_OFFS)
#define EBI_DEV1_TIM1_WR2_OFFS		0x00000130
#define EBI_DEV1_TIM1_WR2(base)		((base) + EBI_DEV1_TIM1_WR2_OFFS)
#define EBI_DEV1_TIM_EXT_OFFS		0x00000134
#define EBI_DEV1_TIM_EXT(base)		((base) + EBI_DEV1_TIM_EXT_OFFS)
#define EBI_DEV1_TIM2_CFI_RD1_OFFS	0x00000138
#define EBI_DEV1_TIM2_CFI_RD1(base)	((base) + EBI_DEV1_TIM2_CFI_RD1_OFFS)
#define EBI_DEV1_TIM2_CFI_RD2_OFFS	0x0000013C
#define EBI_DEV1_TIM2_CFI_RD2(base)	((base) + EBI_DEV1_TIM2_CFI_RD2_OFFS)
#define EBI_DEV1_TIM3_DMA1_OFFS		0x00000140
#define EBI_DEV1_TIM3_DMA1(base)	((base) + EBI_DEV1_TIM3_DMA1_OFFS)
#define EBI_DEV1_TIM3_DMA2_OFFS		0x00000144
#define EBI_DEV1_TIM3_DMA2(base)	((base) + EBI_DEV1_TIM3_DMA2_OFFS)
#define EBI_DEV1_TIM4_UDMA1_OFFS	0x00000148
#define EBI_DEV1_TIM4_UDMA1(base)	((base) + EBI_DEV1_TIM4_UDMA1_OFFS)
#define EBI_DEV1_TIM4_UDMA2_OFFS	0x0000014C
#define EBI_DEV1_TIM4_UDMA2(base)	((base) + EBI_DEV1_TIM4_UDMA2_OFFS)
#define EBI_DEV1_ACK_RM_CNT_OFFS	0x00000150
#define EBI_DEV1_ACK_RM_CNT(base)	((base) + EBI_DEV1_ACK_RM_CNT_OFFS)
#define EBI_DEV2_DMA_EXT_ADDR_OFFS	0x00000200
#define EBI_DEV2_DMA_EXT_ADDR(base)	((base) + EBI_DEV2_DMA_EXT_ADDR_OFFS)
#define EBI_DEV2_EXT_ACC_OFFS		0x00000204
#define EBI_DEV2_EXT_ACC(base)		((base) + EBI_DEV2_EXT_ACC_OFFS)
#define EBI_DEV2_CONFIG1_OFFS		0x00000208
#define EBI_DEV2_CONFIG1(base)		((base) + EBI_DEV2_CONFIG1_OFFS)
#define EBI_DEV2_CONFIG2_OFFS		0x0000020C
#define EBI_DEV2_CONFIG2(base)		((base) + EBI_DEV2_CONFIG2_OFFS)
#define EBI_DEV2_FIFO_CONFIG_OFFS	0x00000210
#define EBI_DEV2_FIFO_CONFIG(base)	((base) + EBI_DEV2_FIFO_CONFIG_OFFS)
#define EBI_DEV2_FLASH_CONF_ST_OFFS	0x00000214
#define EBI_DEV2_FLASH_CONF_ST(base)	((base) + EBI_DEV2_FLASH_CONF_ST_OFFS)
#define EBI_DEV2_DMA_CONFIG1_OFFS	0x00000218
#define EBI_DEV2_DMA_CONFIG1(base)	((base) + EBI_DEV2_DMA_CONFIG1_OFFS)
#define EBI_DEV2_DMA_CONFIG2_OFFS	0x0000021C
#define EBI_DEV2_DMA_CONFIG2(base)	((base) + EBI_DEV2_DMA_CONFIG2_OFFS)
#define EBI_DEV2_DMA_ECC_CTRL_OFFS	0x00000220
#define EBI_DEV2_DMA_ECC_CTRL(base)	((base) + EBI_DEV2_DMA_ECC_CTRL_OFFS)
#define EBI_DEV2_TIM1_RD1_OFFS		0x00000224
#define EBI_DEV2_TIM1_RD1(base)		((base) + EBI_DEV2_TIM1_RD1_OFFS)
#define EBI_DEV2_TIM1_RD2_OFFS		0x00000228
#define EBI_DEV2_TIM1_RD2(base)		((base) + EBI_DEV2_TIM1_RD2_OFFS)
#define EBI_DEV2_TIM1_WR1_OFFS		0x0000022C
#define EBI_DEV2_TIM1_WR1(base)		((base) + EBI_DEV2_TIM1_WR1_OFFS)
#define EBI_DEV2_TIM1_WR2_OFFS		0x00000230
#define EBI_DEV2_TIM1_WR2(base)		((base) + EBI_DEV2_TIM1_WR2_OFFS)
#define EBI_DEV2_TIM_EXT_OFFS		0x00000234
#define EBI_DEV2_TIM_EXT(base)		((base) + EBI_DEV2_TIM_EXT_OFFS)
#define EBI_DEV2_TIM2_CFI_RD1_OFFS	0x00000238
#define EBI_DEV2_TIM2_CFI_RD1(base)	((base) + EBI_DEV2_TIM2_CFI_RD1_OFFS)
#define EBI_DEV2_TIM2_CFI_RD2_OFFS	0x0000023C
#define EBI_DEV2_TIM2_CFI_RD2(base)	((base) + EBI_DEV2_TIM2_CFI_RD2_OFFS)
#define EBI_DEV2_TIM3_DMA1_OFFS		0x00000240
#define EBI_DEV2_TIM3_DMA1(base)	((base) + EBI_DEV2_TIM3_DMA1_OFFS)
#define EBI_DEV2_TIM3_DMA2_OFFS		0x00000244
#define EBI_DEV2_TIM3_DMA2(base)	((base) + EBI_DEV2_TIM3_DMA2_OFFS)
#define EBI_DEV2_TIM4_UDMA1_OFFS	0x00000248
#define EBI_DEV2_TIM4_UDMA1(base)	((base) + EBI_DEV2_TIM4_UDMA1_OFFS)
#define EBI_DEV2_TIM4_UDMA2_OFFS	0x0000024C
#define EBI_DEV2_TIM4_UDMA2(base)	((base) + EBI_DEV2_TIM4_UDMA2_OFFS)
#define EBI_DEV2_ACK_RM_CNT_OFFS	0x00000250
#define EBI_DEV2_ACK_RM_CNT(base)	((base) + EBI_DEV2_ACK_RM_CNT_OFFS)
#define EBI_DEV3_DMA_EXT_ADDR_OFFS	0x00000300
#define EBI_DEV3_DMA_EXT_ADDR(base)	((base) + EBI_DEV3_DMA_EXT_ADDR_OFFS)
#define EBI_DEV3_EXT_ACC_OFFS		0x00000304
#define EBI_DEV3_EXT_ACC(base)		((base) + EBI_DEV3_EXT_ACC_OFFS)
#define EBI_DEV3_CONFIG1_OFFS		0x00000308
#define EBI_DEV3_CONFIG1(base)		((base) + EBI_DEV3_CONFIG1_OFFS)
#define EBI_DEV3_CONFIG2_OFFS		0x0000030C
#define EBI_DEV3_CONFIG2(base)		((base) + EBI_DEV3_CONFIG2_OFFS)
#define EBI_DEV3_FIFO_CONFIG_OFFS	0x00000310
#define EBI_DEV3_FIFO_CONFIG(base)	((base) + EBI_DEV3_FIFO_CONFIG_OFFS)
#define EBI_DEV3_FLASH_CONF_ST_OFFS	0x00000314
#define EBI_DEV3_FLASH_CONF_ST(base)	((base) + EBI_DEV3_FLASH_CONF_ST_OFFS)
#define EBI_DEV3_DMA_CONFIG1_OFFS	0x00000318
#define EBI_DEV3_DMA_CONFIG1(base)	((base) + EBI_DEV3_DMA_CONFIG1_OFFS)
#define EBI_DEV3_DMA_CONFIG2_OFFS	0x0000031C
#define EBI_DEV3_DMA_CONFIG2(base)	((base) + EBI_DEV3_DMA_CONFIG2_OFFS)
#define EBI_DEV3_DMA_ECC_CTRL_OFFS	0x00000320
#define EBI_DEV3_DMA_ECC_CTRL(base)	((base) + EBI_DEV3_DMA_ECC_CTRL_OFFS)
#define EBI_DEV3_TIM1_RD1_OFFS		0x00000324
#define EBI_DEV3_TIM1_RD1(base)		((base) + EBI_DEV3_TIM1_RD1_OFFS)
#define EBI_DEV3_TIM1_RD2_OFFS		0x00000328
#define EBI_DEV3_TIM1_RD2(base)		((base) + EBI_DEV3_TIM1_RD2_OFFS)
#define EBI_DEV3_TIM1_WR1_OFFS		0x0000032C
#define EBI_DEV3_TIM1_WR1(base)		((base) + EBI_DEV3_TIM1_WR1_OFFS)
#define EBI_DEV3_TIM1_WR2_OFFS		0x00000330
#define EBI_DEV3_TIM1_WR2(base)		((base) + EBI_DEV3_TIM1_WR2_OFFS)
#define EBI_DEV3_TIM_EXT_OFFS		0x00000334
#define EBI_DEV3_TIM_EXT(base)		((base) + EBI_DEV3_TIM_EXT_OFFS)
#define EBI_DEV3_TIM2_CFI_RD1_OFFS	0x00000338
#define EBI_DEV3_TIM2_CFI_RD1(base)	((base) + EBI_DEV3_TIM2_CFI_RD1_OFFS)
#define EBI_DEV3_TIM2_CFI_RD2_OFFS	0x0000033C
#define EBI_DEV3_TIM2_CFI_RD2(base)	((base) + EBI_DEV3_TIM2_CFI_RD2_OFFS)
#define EBI_DEV3_TIM3_DMA1_OFFS		0x00000340
#define EBI_DEV3_TIM3_DMA1(base)	((base) + EBI_DEV3_TIM3_DMA1_OFFS)
#define EBI_DEV3_TIM3_DMA2_OFFS		0x00000344
#define EBI_DEV3_TIM3_DMA2(base)	((base) + EBI_DEV3_TIM3_DMA2_OFFS)
#define EBI_DEV3_TIM4_UDMA1_OFFS	0x00000348
#define EBI_DEV3_TIM4_UDMA1(base)	((base) + EBI_DEV3_TIM4_UDMA1_OFFS)
#define EBI_DEV3_TIM4_UDMA2_OFFS	0x0000034C
#define EBI_DEV3_TIM4_UDMA2(base)	((base) + EBI_DEV3_TIM4_UDMA2_OFFS)
#define EBI_DEV3_ACK_RM_CNT_OFFS	0x00000350
#define EBI_DEV3_ACK_RM_CNT(base)	((base) + EBI_DEV3_ACK_RM_CNT_OFFS)
#define EBI_DEV4_DMA_EXT_ADDR_OFFS	0x00000400
#define EBI_DEV4_DMA_EXT_ADDR(base)	((base) + EBI_DEV4_DMA_EXT_ADDR_OFFS)
#define EBI_DEV4_EXT_ACC_OFFS		0x00000404
#define EBI_DEV4_EXT_ACC(base)		((base) + EBI_DEV4_EXT_ACC_OFFS)
#define EBI_DEV4_CONFIG1_OFFS		0x00000408
#define EBI_DEV4_CONFIG1(base)		((base) + EBI_DEV4_CONFIG1_OFFS)
#define EBI_DEV4_CONFIG2_OFFS		0x0000040C
#define EBI_DEV4_CONFIG2(base)		((base) + EBI_DEV4_CONFIG2_OFFS)
#define EBI_DEV4_FIFO_CONFIG_OFFS	0x00000410
#define EBI_DEV4_FIFO_CONFIG(base)	((base) + EBI_DEV4_FIFO_CONFIG_OFFS)
#define EBI_DEV4_FLASH_CONF_ST_OFFS	0x00000414
#define EBI_DEV4_FLASH_CONF_ST(base)	((base) + EBI_DEV4_FLASH_CONF_ST_OFFS)
#define EBI_DEV4_DMA_CONFIG1_OFFS	0x00000418
#define EBI_DEV4_DMA_CONFIG1(base)	((base) + EBI_DEV4_DMA_CONFIG1_OFFS)
#define EBI_DEV4_DMA_CONFIG2_OFFS	0x0000041C
#define EBI_DEV4_DMA_CONFIG2(base)	((base) + EBI_DEV4_DMA_CONFIG2_OFFS)
#define EBI_DEV4_DMA_ECC_CTRL_OFFS	0x00000420
#define EBI_DEV4_DMA_ECC_CTRL(base)	((base) + EBI_DEV4_DMA_ECC_CTRL_OFFS)
#define EBI_DEV4_TIM1_RD1_OFFS		0x00000424
#define EBI_DEV4_TIM1_RD1(base)		((base) + EBI_DEV4_TIM1_RD1_OFFS)
#define EBI_DEV4_TIM1_RD2_OFFS		0x00000428
#define EBI_DEV4_TIM1_RD2(base)		((base) + EBI_DEV4_TIM1_RD2_OFFS)
#define EBI_DEV4_TIM1_WR1_OFFS		0x0000042C
#define EBI_DEV4_TIM1_WR1(base)		((base) + EBI_DEV4_TIM1_WR1_OFFS)
#define EBI_DEV4_TIM1_WR2_OFFS		0x00000430
#define EBI_DEV4_TIM1_WR2(base)		((base) + EBI_DEV4_TIM1_WR2_OFFS)
#define EBI_DEV4_TIM_EXT_OFFS		0x00000434
#define EBI_DEV4_TIM_EXT(base)		((base) + EBI_DEV4_TIM_EXT_OFFS)
#define EBI_DEV4_TIM2_CFI_RD1_OFFS	0x00000438
#define EBI_DEV4_TIM2_CFI_RD1(base)	((base) + EBI_DEV4_TIM2_CFI_RD1_OFFS)
#define EBI_DEV4_TIM2_CFI_RD2_OFFS	0x0000043C
#define EBI_DEV4_TIM2_CFI_RD2(base)	((base) + EBI_DEV4_TIM2_CFI_RD2_OFFS)
#define EBI_DEV4_TIM3_DMA1_OFFS		0x00000440
#define EBI_DEV4_TIM3_DMA1(base)	((base) + EBI_DEV4_TIM3_DMA1_OFFS)
#define EBI_DEV4_TIM3_DMA2_OFFS		0x00000444
#define EBI_DEV4_TIM3_DMA2(base)	((base) + EBI_DEV4_TIM3_DMA2_OFFS)
#define EBI_DEV4_TIM4_UDMA1_OFFS	0x00000448
#define EBI_DEV4_TIM4_UDMA1(base)	((base) + EBI_DEV4_TIM4_UDMA1_OFFS)
#define EBI_DEV4_TIM4_UDMA2_OFFS	0x0000044C
#define EBI_DEV4_TIM4_UDMA2(base)	((base) + EBI_DEV4_TIM4_UDMA2_OFFS)
#define EBI_DEV4_ACK_RM_CNT_OFFS	0x00000450
#define EBI_DEV4_ACK_RM_CNT(base)	((base) + EBI_DEV4_ACK_RM_CNT_OFFS)
#define EBI_INTERLEAVE_CNT_OFFS		0x00000900
#define EBI_INTERLEAVE_CNT(base)	((base) + EBI_INTERLEAVE_CNT_OFFS)
#define EBI_CNT_FL_PROGR_OFFS		0x00000904
#define EBI_CNT_FL_PROGR(base)		((base) + EBI_CNT_FL_PROGR_OFFS)
#define EBI_CNT_EXT_PAGE_SZ_OFFS	0x0000090C
#define EBI_CNT_EXT_PAGE_SZ(base)	((base) + EBI_CNT_EXT_PAGE_SZ_OFFS)
#define EBI_CNT_WAIT_RDY_OFFS		0x00000914
#define EBI_CNT_WAIT_RDY(base)		((base) + EBI_CNT_WAIT_RDY_OFFS)
#define EBI_CNT_ACK_OFFS		0x00000918
#define EBI_CNT_ACK(base)		((base) + EBI_CNT_ACK_OFFS)
#define EBI_GENIO1_CONFIG1_OFFS		0x00000A00
#define EBI_GENIO1_CONFIG1(base)	((base) + EBI_GENIO1_CONFIG1_OFFS)
#define EBI_GENIO1_CONFIG2_OFFS		0x00000A04
#define EBI_GENIO1_CONFIG2(base)	((base) + EBI_GENIO1_CONFIG2_OFFS)
#define EBI_GENIO1_CONFIG3_OFFS		0x00000A08
#define EBI_GENIO1_CONFIG3(base)	((base) + EBI_GENIO1_CONFIG3_OFFS)
#define EBI_GENIO2_CONFIG1_OFFS		0x00000A10
#define EBI_GENIO2_CONFIG1(base)	((base) + EBI_GENIO2_CONFIG1_OFFS)
#define EBI_GENIO2_CONFIG2_OFFS		0x00000A14
#define EBI_GENIO2_CONFIG2(base)	((base) + EBI_GENIO2_CONFIG2_OFFS)
#define EBI_GENIO2_CONFIG3_OFFS		0x00000A18
#define EBI_GENIO2_CONFIG3(base)	((base) + EBI_GENIO2_CONFIG3_OFFS)
#define EBI_GENIO3_CONFIG1_OFFS		0x00000A20
#define EBI_GENIO3_CONFIG1(base)	((base) + EBI_GENIO3_CONFIG1_OFFS)
#define EBI_GENIO3_CONFIG2_OFFS		0x00000A24
#define EBI_GENIO3_CONFIG2(base)	((base) + EBI_GENIO3_CONFIG2_OFFS)
#define EBI_GENIO3_CONFIG3_OFFS		0x00000A28
#define EBI_GENIO3_CONFIG3(base)	((base) + EBI_GENIO3_CONFIG3_OFFS)
#define EBI_GENIO4_CONFIG1_OFFS		0x00000A30
#define EBI_GENIO4_CONFIG1(base)	((base) + EBI_GENIO4_CONFIG1_OFFS)
#define EBI_GENIO4_CONFIG2_OFFS		0x00000A34
#define EBI_GENIO4_CONFIG2(base)	((base) + EBI_GENIO4_CONFIG2_OFFS)
#define EBI_GENIO4_CONFIG3_OFFS		0x00000A38
#define EBI_GENIO4_CONFIG3(base)	((base) + EBI_GENIO4_CONFIG3_OFFS)
#define EBI_GENIO5_CONFIG1_OFFS		0x00000A40
#define EBI_GENIO5_CONFIG1(base)	((base) + EBI_GENIO5_CONFIG1_OFFS)
#define EBI_GENIO5_CONFIG2_OFFS		0x00000A44
#define EBI_GENIO5_CONFIG2(base)	((base) + EBI_GENIO5_CONFIG2_OFFS)
#define EBI_GENIO5_CONFIG3_OFFS		0x00000A48
#define EBI_GENIO5_CONFIG3(base)	((base) + EBI_GENIO5_CONFIG3_OFFS)

#endif
