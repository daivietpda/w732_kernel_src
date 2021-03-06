
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

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#ifndef __MTK_MAU_REG_H__
#define __MTK_MAU_REG_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


#define REG_SMI_MAU_ENTR0_START      0x0300
#define REG_SMI_MAU_ENTR0_END        0x0304
#define REG_SMI_MAU_ENTR0_GID_0      0x0308
#define REG_SMI_MAU_ENTR1_START      0x0310
#define REG_SMI_MAU_ENTR1_END        0x0314
#define REG_SMI_MAU_ENTR1_GID_0      0x0318
#define REG_SMI_MAU_ENTR2_START      0x0320
#define REG_SMI_MAU_ENTR2_END        0x0324
#define REG_SMI_MAU_ENTR2_GID_0      0x0328


#define REG_SMI_MAU_ENTR0_STAT       0x0500
#define REG_SMI_MAU_ENTR1_STAT       0x0504
#define REG_SMI_MAU_ENTR2_STAT       0x0508





typedef struct {
    unsigned STR    : 30;
    unsigned RD     : 1;
    unsigned WR     : 1;
} MAU_REG_RANGE_START, *PMAU_REG_RANGE_START;

typedef struct {
    unsigned END        : 30;
    unsigned VP_CTRL    : 1;  // 0:SYSRAM PA 1: MVA
    unsigned rsv        : 1;  // no use
} MAU_REG_RANGE_END, *PMAU_REG_RANGE_END;





// MAU0 ASSERT ID bit: Entyr 0: 4 Entyr 1: 7 Entyr 2: 7
// MAU1 ASSERT ID bit: Entyr 0: 5 Entyr 1: 7 Entyr 2: 7
// MAU2 ASSERT ID bit: Entyr 0: 3 Entyr 1: 7 Entyr 2: 7
// MAU2 ASSERT ID bit: Entyr 0: 2 Entyr 1: 7 Entyr 2: 7



typedef struct {
    unsigned ASSERT_ID : 7;
    unsigned ASSERT    : 1;
    unsigned rsv_8     : 24;
} MAU_REG_ENT_STATUS, *PMAU_REG_ENT_STATUS;





#define MAU0_SMI_LARB_CON        0xF2081010 //MAU_IRQ_EN bit:10 RO
#define MAU0_SMI_LARB_CON_SET    0xF2081014 //MAU_IRQ_EN bit:10 WO
#define MAU0_SMI_LARB_CON_RESET  0xF2081018 //MAU_IRQ_EN bit:10 WO

#define MAU1_SMI_LARB_CON        0xF2082010 //MAU_IRQ_EN bit:10 RO
#define MAU1_SMI_LARB_CON_SET    0xF2082014 //MAU_IRQ_EN bit:10 WO
#define MAU1_SMI_LARB_CON_RESET  0xF2082018 //MAU_IRQ_EN bit:10 WO

#define MAU2_SMI_LARB_CON        0xF2083010 //MAU_IRQ_EN bit:10 RO
#define MAU2_SMI_LARB_CON_SET    0xF2083014 //MAU_IRQ_EN bit:10 WO
#define MAU2_SMI_LARB_CON_RESET  0xF2083018 //MAU_IRQ_EN bit:10 WO

#define MAU3_SMI_LARB_CON        0xF20C1010 //MAU_IRQ_EN bit:10 RO
#define MAU3_SMI_LARB_CON_SET    0xF20C1014 //MAU_IRQ_EN bit:10 WO
#define MAU3_SMI_LARB_CON_RESET  0xF20C1018 //MAU_IRQ_EN bit:10 WO

#define MAU0_REG_BASE            0xF2081300
#define MAU1_REG_BASE            0xF2082300
#define MAU2_REG_BASE            0xF2083300
#define MAU3_REG_BASE            0xF20C1300



typedef struct {
    MAU_REG_RANGE_START  ENT0_STR;   //+00
    MAU_REG_RANGE_END    ENT0_END;   //+04
    unsigned int         ENT0_GID;   //+08
    unsigned int         rsv_0C;

    MAU_REG_RANGE_START  ENT1_STR;   //10
    unsigned int         ENT1_END;   //14
    unsigned int         ENT1_GID;   //18
    unsigned int         rsv_1C;

    MAU_REG_RANGE_START  ENT2_STR;   //20
    unsigned int         ENT2_END;   //24
    unsigned int         ENT2_GID;   //28
    unsigned int         rsv_2C[117];     //2c

    MAU_REG_ENT_STATUS   ENT0_STATUS;      //+200
    MAU_REG_ENT_STATUS   ENT1_STATUS;      //+204
    MAU_REG_ENT_STATUS   ENT2_STATUS;      //+208

    unsigned int         rsv_20C[5];

    unsigned int         INTERRUPT;       //+220
} volatile MAU_REGS, *PMAU_REGS;



extern PMAU_REGS const MAU0_REG;
extern PMAU_REGS const MAU1_REG;
extern PMAU_REGS const MAU2_REG;
extern PMAU_REGS const MAU3_REG;


#ifdef __cplusplus
}
#endif

#endif // __MTK_MAU_REG_H__






