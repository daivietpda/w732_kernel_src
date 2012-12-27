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
 * Boot ROM Entry Points and such
 */

/* These Blackfins all have a Boot ROM that is not reusable (at all):
 *  BF531 / BF532 / BF533
 *  BF538 / BF539
 *  BF561
 * So there is nothing for us to export ;(
 *
 * These Blackfins started to roll with the idea that the Boot ROM can
 * provide useful functions, but still only a few (and not really useful):
 *  BF534 / BF536 / BF537
 *
 * Looking forward, Boot ROM's on newer Blackfins have quite a few
 * nice entry points that are usable at runtime and beyond.  We'll
 * only define known legacy parts (listed above) and otherwise just
 * assume it's a newer part.
 *
 * These entry points are accomplished by placing a small jump table at
 * the start of the Boot ROM.  This way the addresses are fixed forever.
 */

#ifndef __BFIN_PERIPHERAL_BOOTROM__
#define __BFIN_PERIPHERAL_BOOTROM__

/* All Blackfin's have the Boot ROM entry point at the same address */
#define _BOOTROM_RESET 0xEF000000

#if defined(__ADSPBF531__) || defined(__ADSPBF532__) || defined(__ADSPBF533__) || \
    defined(__ADSPBF538__) || defined(__ADSPBF539__) || \
    defined(__ADSPBF561__)

	/* Nothing to export */

#elif defined(__ADSPBF534__) || defined(__ADSPBF536__) || defined(__ADSPBF537__)

	/* The BF537 family */

#define _BOOTROM_FINAL_INIT            0xEF000002
/*       reserved                      0xEF000004 */
#define _BOOTROM_DO_MEMORY_DMA         0xEF000006
#define _BOOTROM_BOOT_DXE_FLASH        0xEF000008
#define _BOOTROM_BOOT_DXE_SPI          0xEF00000A
#define _BOOTROM_BOOT_DXE_TWI          0xEF00000C
/*       reserved                      0xEF00000E */
#define _BOOTROM_GET_DXE_ADDRESS_FLASH 0xEF000010
#define _BOOTROM_GET_DXE_ADDRESS_SPI   0xEF000012
#define _BOOTROM_GET_DXE_ADDRESS_TWI   0xEF000014
/*       reserved                      0xEF000016 */
/*       reserved                      0xEF000018 */

	/* Glue to newer Boot ROMs */
#define _BOOTROM_MDMA                  _BOOTROM_DO_MEMORY_DMA
#define _BOOTROM_MEMBOOT               _BOOTROM_BOOT_DXE_FLASH
#define _BOOTROM_SPIBOOT               _BOOTROM_BOOT_DXE_FLASH
#define _BOOTROM_TWIBOOT               _BOOTROM_BOOT_DXE_TWI

#else

	/* All the newer Boot ROMs */

#define _BOOTROM_FINAL_INIT            0xEF000002
#define _BOOTROM_PDMA                  0xEF000004
#define _BOOTROM_MDMA                  0xEF000006
#define _BOOTROM_MEMBOOT               0xEF000008
#define _BOOTROM_SPIBOOT               0xEF00000A
#define _BOOTROM_TWIBOOT               0xEF00000C
/*       reserved                      0xEF00000E */
/*       reserved                      0xEF000010 */
/*       reserved                      0xEF000012 */
/*       reserved                      0xEF000014 */
/*       reserved                      0xEF000016 */
#define _BOOTROM_OTP_COMMAND           0xEF000018
#define _BOOTROM_OTP_READ              0xEF00001A
#define _BOOTROM_OTP_WRITE             0xEF00001C
#define _BOOTROM_ECC_TABLE             0xEF00001E
#define _BOOTROM_BOOTKERNEL            0xEF000020
#define _BOOTROM_GETPORT               0xEF000022
#define _BOOTROM_NMI                   0xEF000024
#define _BOOTROM_HWERROR               0xEF000026
#define _BOOTROM_EXCEPTION             0xEF000028
#define _BOOTROM_CRC32                 0xEF000030
#define _BOOTROM_CRC32POLY             0xEF000032
#define _BOOTROM_CRC32CALLBACK         0xEF000034
#define _BOOTROM_CRC32INITCODE         0xEF000036
#define _BOOTROM_SYSCONTROL            0xEF000038
#define _BOOTROM_REV                   0xEF000040
#define _BOOTROM_SESR                  0xEF001000

#define BOOTROM_FOLLOWS_C_ABI 1

#define BOOTROM_CAPS_ADI_BOOT_STRUCTS 1

#endif

#ifndef BOOTROM_FOLLOWS_C_ABI
#define BOOTROM_FOLLOWS_C_ABI 0
#endif
#ifndef BOOTROM_CAPS_ADI_BOOT_STRUCTS
#define BOOTROM_CAPS_ADI_BOOT_STRUCTS 0
#endif

/* Possible syscontrol action flags */
#define SYSCTRL_READ        0x00000000    /* read registers */
#define SYSCTRL_WRITE       0x00000001    /* write registers */
#define SYSCTRL_SYSRESET    0x00000002    /* perform system reset */
#define SYSCTRL_CORERESET   0x00000004    /* perform core reset */
#define SYSCTRL_SOFTRESET   0x00000006    /* perform core and system reset */
#define SYSCTRL_VRCTL       0x00000010    /* read/write VR_CTL register */
#define SYSCTRL_EXTVOLTAGE  0x00000020    /* VDDINT supplied externally */
#define SYSCTRL_INTVOLTAGE  0x00000000    /* VDDINT generated by on-chip regulator */
#define SYSCTRL_OTPVOLTAGE  0x00000040    /* For Factory Purposes Only */
#define SYSCTRL_PLLCTL      0x00000100    /* read/write PLL_CTL register */
#define SYSCTRL_PLLDIV      0x00000200    /* read/write PLL_DIV register */
#define SYSCTRL_LOCKCNT     0x00000400    /* read/write PLL_LOCKCNT register */
#define SYSCTRL_PLLSTAT     0x00000800    /* read/write PLL_STAT register */

#ifndef __ASSEMBLY__

#if BOOTROM_FOLLOWS_C_ABI
# define BOOTROM_CALLED_FUNC_ATTR
#else
# define BOOTROM_CALLED_FUNC_ATTR __attribute__((saveall))
#endif

/* Structures for the syscontrol() function */
typedef struct ADI_SYSCTRL_VALUES {
	uint16_t uwVrCtl;
	uint16_t uwPllCtl;
	uint16_t uwPllDiv;
	uint16_t uwPllLockCnt;
	uint16_t uwPllStat;
} ADI_SYSCTRL_VALUES;

#ifndef _BOOTROM_SYSCONTROL
#define _BOOTROM_SYSCONTROL 0
#endif
static uint32_t (* const bfrom_SysControl)(uint32_t action_flags, ADI_SYSCTRL_VALUES *power_settings, void *reserved) = (void *)_BOOTROM_SYSCONTROL;

/* We need a dedicated function since we need to screw with the stack pointer
 * when resetting.  The on-chip ROM will save/restore registers on the stack
 * when doing a system reset, so the stack cannot be outside of the chip.
 */
__attribute__((__noreturn__))
static inline void bfrom_SoftReset(void *new_stack)
{
	while (1)
		__asm__ __volatile__(
			"sp = %[stack];"
			"jump (%[bfrom_syscontrol]);"
			: : [bfrom_syscontrol] "p"(bfrom_SysControl),
				"q0"(SYSCTRL_SOFTRESET),
				"q1"(0),
				"q2"(NULL),
				[stack] "p"(new_stack)
		);
}

/* Structures for working with LDRs and boot rom callbacks */
typedef struct ADI_BOOT_HEADER {
	int32_t dBlockCode;
	void    *pTargetAddress;
	int32_t dByteCount;
	int32_t dArgument;
} ADI_BOOT_HEADER;

typedef struct ADI_BOOT_BUFFER {
	void    *pSource;
	int32_t dByteCount;
} ADI_BOOT_BUFFER;

typedef struct ADI_BOOT_DATA {
	void    *pSource;
	void    *pDestination;
	int16_t *pControlRegister;
	int16_t *pDmaControlRegister;
	int32_t dControlValue;
	int32_t dByteCount;
	int32_t dFlags;
	int16_t uwDataWidth;
	int16_t uwSrcModifyMult;
	int16_t uwDstModifyMult;
	int16_t uwHwait;
	int16_t uwSsel;
	int16_t uwUserShort;
	int32_t dUserLong;
	int32_t dReserved2;
	void    *pErrorFunction;
	void    *pLoadFunction;
	void    *pCallBackFunction;
	ADI_BOOT_HEADER *pHeader;
	void    *pTempBuffer;
	void    *pTempCurrent;
	int32_t dTempByteCount;
	int32_t dBlockCount;
	int32_t dClock;
	void    *pLogBuffer;
	void    *pLogCurrent;
	int32_t dLogByteCount;
} ADI_BOOT_DATA;

typedef void ADI_BOOT_HOOK_FUNC (ADI_BOOT_DATA *);

#ifndef _BOOTROM_MEMBOOT
#define _BOOTROM_MEMBOOT 0
#endif
static uint32_t (* const bfrom_MemBoot)(void *pBootStream, int32_t dFlags, int32_t dBlockCount, ADI_BOOT_HOOK_FUNC *pCallHook) = (void *)_BOOTROM_MEMBOOT;

#ifndef _BOOTROM_TWIBOOT
#define _BOOTROM_TWIBOOT 0
#endif
static uint32_t (* const bfrom_TwiBoot)(int32_t dTwiAddress, int32_t dFlags, int32_t dBlockCount, ADI_BOOT_HOOK_FUNC *pCallHook) = (void *)_BOOTROM_TWIBOOT;

#ifndef _BOOTROM_SPIBOOT
#define _BOOTROM_SPIBOOT 0
#endif
static uint32_t (* const bfrom_SpiBoot)(int32_t dSpiAddress, int32_t dFlags, int32_t dBlockCount, ADI_BOOT_HOOK_FUNC *pCallHook) = (void *)_BOOTROM_SPIBOOT;

#ifndef _BOOTROM_OTPBOOT
#define _BOOTROM_OTPBOOT 0
#endif
static uint32_t (* const bfrom_OtpBoot)(int32_t dOtpAddress, int32_t dFlags, int32_t dBlockCount, ADI_BOOT_HOOK_FUNC *pCallHook) = (void *)_BOOTROM_OTPBOOT;

#ifndef _BOOTROM_NANDBOOT
#define _BOOTROM_NANDBOOT 0
#endif
static uint32_t (* const bfrom_NandBoot)(int32_t dNandAddress, int32_t dFlags, int32_t dBlockCount, ADI_BOOT_HOOK_FUNC *pCallHook) = (void *)_BOOTROM_NANDBOOT;

#endif /* __ASSEMBLY__ */

/* Bit defines for ADI_BOOT_DATA->dFlags */
#define BFLAG_DMACODE_MASK 0x0000000F
#define BFLAG_SAFE         0x00000010
#define BFLAG_AUX          0x00000020
#define BFLAG_FILL         0x00000100
#define BFLAG_QUICKBOOT    0x00000200
#define BFLAG_CALLBACK     0x00000400
#define BFLAG_INIT         0x00000800
#define BFLAG_IGNORE       0x00001000
#define BFLAG_INDIRECT     0x00002000
#define BFLAG_FIRST        0x00004000
#define BFLAG_FINAL        0x00008000
#define BFLAG_HOOK         0x00400000
#define BFLAG_HDRINDIRECT  0x00800000
#define BFLAG_TYPE_MASK    0x00300000
#define BFLAG_TYPE_1       0x00000000
#define BFLAG_TYPE_2       0x00100000
#define BFLAG_TYPE_3       0x00200000
#define BFLAG_TYPE_4       0x00300000
#define BFLAG_FASTREAD     0x00400000
#define BFLAG_NOAUTO       0x01000000
#define BFLAG_PERIPHERAL   0x02000000
#define BFLAG_SLAVE        0x04000000
#define BFLAG_WAKEUP       0x08000000
#define BFLAG_NEXTDXE      0x10000000
#define BFLAG_RETURN       0x20000000
#define BFLAG_RESET        0x40000000
#define BFLAG_NONRESTORE   0x80000000

#endif
