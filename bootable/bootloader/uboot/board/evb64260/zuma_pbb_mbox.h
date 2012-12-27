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

#define IN_VALID 1
#define OUT_PENDING 2

enum {
	ZUMA_MBOXMSG_DONE,
	ZUMA_MBOXMSG_MACL,
	ZUMA_MBOXMSG_MACH,
	ZUMA_MBOXMSG_IP,
	ZUMA_MBOXMSG_SLOT,
	ZUMA_MBOXMSG_RESET,
	ZUMA_MBOXMSG_BAUD,
	ZUMA_MBOXMSG_START,
	ZUMA_MBOXMSG_ENG_PRV_MACL,
	ZUMA_MBOXMSG_ENG_PRV_MACH,

	MBOXMSG_LAST
};

struct zuma_mailbox_info {
	unsigned char acc_mac[6];
	unsigned char prv_mac[6];
	unsigned int ip;
	unsigned int slot_bac;
	unsigned int console_baud;
	unsigned int debug_baud;
};

struct _zuma_mbox_dev {
	pci_dev_t dev;
	PBB_DMA_REG_MAP *sip;
	struct zuma_mailbox_info mailbox;
};

#define zuma_prv_mac		zuma_mbox_dev.mailbox.prv_mac
#define zuma_acc_mac		zuma_mbox_dev.mailbox.acc_mac
#define zuma_ip                 zuma_mbox_dev.mailbox.ip
#define zuma_slot_bac		zuma_mbox_dev.mailbox.slot_bac
#define zuma_console_baud	zuma_mbox_dev.mailbox.console_baud
#define zuma_debug_baud		zuma_mbox_dev.mailbox.debug_baud


extern struct _zuma_mbox_dev zuma_mbox_dev;
extern int zuma_mbox_init (void);
