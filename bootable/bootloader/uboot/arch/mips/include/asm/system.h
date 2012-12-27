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
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1994 - 1999 by Ralf Baechle
 * Copyright (C) 1996 by Paul M. Antoine
 * Copyright (C) 1994 - 1999 by Ralf Baechle
 *
 * Changed set_except_vector declaration to allow return of previous
 * vector address value - necessary for "borrowing" vectors.
 *
 * Kevin D. Kissell, kevink@mips.org and Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2000 MIPS Technologies, Inc.
 */
#ifndef _ASM_SYSTEM_H
#define _ASM_SYSTEM_H

#include <linux/config.h>
#include <asm/sgidefs.h>
#include <asm/ptrace.h>
#if 0
#include <linux/kernel.h>
#endif

extern __inline__ void
__sti(void)
{
	__asm__ __volatile__(
		".set\tpush\n\t"
		".set\treorder\n\t"
		".set\tnoat\n\t"
		"mfc0\t$1,$12\n\t"
		"ori\t$1,0x1f\n\t"
		"xori\t$1,0x1e\n\t"
		"mtc0\t$1,$12\n\t"
		".set\tpop\n\t"
		: /* no outputs */
		: /* no inputs */
		: "$1", "memory");
}

/*
 * For cli() we have to insert nops to make shure that the new value
 * has actually arrived in the status register before the end of this
 * macro.
 * R4000/R4400 need three nops, the R4600 two nops and the R10000 needs
 * no nops at all.
 */
extern __inline__ void
__cli(void)
{
	__asm__ __volatile__(
		".set\tpush\n\t"
		".set\treorder\n\t"
		".set\tnoat\n\t"
		"mfc0\t$1,$12\n\t"
		"ori\t$1,1\n\t"
		"xori\t$1,1\n\t"
		".set\tnoreorder\n\t"
		"mtc0\t$1,$12\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		".set\tpop\n\t"
		: /* no outputs */
		: /* no inputs */
		: "$1", "memory");
}

#define __save_flags(x)							\
__asm__ __volatile__(							\
	".set\tpush\n\t"						\
	".set\treorder\n\t"						\
	"mfc0\t%0,$12\n\t"						\
	".set\tpop\n\t"							\
	: "=r" (x))

#define __save_and_cli(x)						\
__asm__ __volatile__(							\
	".set\tpush\n\t"						\
	".set\treorder\n\t"						\
	".set\tnoat\n\t"						\
	"mfc0\t%0,$12\n\t"						\
	"ori\t$1,%0,1\n\t"						\
	"xori\t$1,1\n\t"						\
	".set\tnoreorder\n\t"						\
	"mtc0\t$1,$12\n\t"						\
	"nop\n\t"							\
	"nop\n\t"							\
	"nop\n\t"							\
	".set\tpop\n\t"							\
	: "=r" (x)							\
	: /* no inputs */						\
	: "$1", "memory")

#define __restore_flags(flags)						\
do {									\
	unsigned long __tmp1;						\
									\
	__asm__ __volatile__(						\
		".set\tnoreorder\t\t\t# __restore_flags\n\t"		\
		".set\tnoat\n\t"					\
		"mfc0\t$1, $12\n\t"					\
		"andi\t%0, 1\n\t"					\
		"ori\t$1, 1\n\t"					\
		"xori\t$1, 1\n\t"					\
		"or\t%0, $1\n\t"					\
		"mtc0\t%0, $12\n\t"					\
		"nop\n\t"						\
		"nop\n\t"						\
		"nop\n\t"						\
		".set\tat\n\t"						\
		".set\treorder"						\
		: "=r" (__tmp1)						\
		: "0" (flags)						\
		: "$1", "memory");					\
} while(0)

#ifdef CONFIG_SMP

extern void __global_sti(void);
extern void __global_cli(void);
extern unsigned long __global_save_flags(void);
extern void __global_restore_flags(unsigned long);
#  define sti() __global_sti()
#  define cli() __global_cli()
#  define save_flags(x) do { x = __global_save_flags(); } while (0)
#  define restore_flags(x) __global_restore_flags(x)
#  define save_and_cli(x) do { save_flags(x); cli(); } while(0)

#else /* Single processor */

#  define sti() __sti()
#  define cli() __cli()
#  define save_flags(x) __save_flags(x)
#  define save_and_cli(x) __save_and_cli(x)
#  define restore_flags(x) __restore_flags(x)

#endif /* SMP */

/* For spinlocks etc */
#define local_irq_save(x)	__save_and_cli(x);
#define local_irq_restore(x)	__restore_flags(x);
#define local_irq_disable()	__cli();
#define local_irq_enable()	__sti();

/*
 * These are probably defined overly paranoid ...
 */
#ifdef CONFIG_CPU_HAS_WB

#include <asm/wbflush.h>
#define rmb()	do { } while(0)
#define wmb()	wbflush()
#define mb()	wbflush()

#else /* CONFIG_CPU_HAS_WB  */

#define mb()						\
__asm__ __volatile__(					\
	"# prevent instructions being moved around\n\t"	\
	".set\tnoreorder\n\t"				\
	"# 8 nops to fool the R4400 pipeline\n\t"	\
	"nop;nop;nop;nop;nop;nop;nop;nop\n\t"		\
	".set\treorder"					\
	: /* no output */				\
	: /* no input */				\
	: "memory")
#define rmb() mb()
#define wmb() mb()

#endif /* CONFIG_CPU_HAS_WB  */

#ifdef CONFIG_SMP
#define smp_mb()	mb()
#define smp_rmb()	rmb()
#define smp_wmb()	wmb()
#else
#define smp_mb()	barrier()
#define smp_rmb()	barrier()
#define smp_wmb()	barrier()
#endif

#define set_mb(var, value) \
do { var = value; mb(); } while (0)

#define set_wmb(var, value) \
do { var = value; wmb(); } while (0)

#if !defined (_LANGUAGE_ASSEMBLY)
/*
 * switch_to(n) should switch tasks to task nr n, first
 * checking that n isn't the current task, in which case it does nothing.
 */
#if 0
extern asmlinkage void *resume(void *last, void *next);
#endif
#endif /* !defined (_LANGUAGE_ASSEMBLY) */

#define prepare_to_switch()	do { } while(0)
#define switch_to(prev,next,last) \
do { \
	(last) = resume(prev, next); \
} while(0)

/*
 * For 32 and 64 bit operands we can take advantage of ll and sc.
 * FIXME: This doesn't work for R3000 machines.
 */
extern __inline__ unsigned long xchg_u32(volatile int * m, unsigned long val)
{
#ifdef CONFIG_CPU_HAS_LLSC
	unsigned long dummy;

	__asm__ __volatile__(
		".set\tnoreorder\t\t\t# xchg_u32\n\t"
		".set\tnoat\n\t"
		"ll\t%0, %3\n"
		"1:\tmove\t$1, %2\n\t"
		"sc\t$1, %1\n\t"
		"beqzl\t$1, 1b\n\t"
		" ll\t%0, %3\n\t"
		".set\tat\n\t"
		".set\treorder"
		: "=r" (val), "=o" (*m), "=r" (dummy)
		: "o" (*m), "2" (val)
		: "memory");

	return val;
#else
	unsigned long flags, retval;

	save_flags(flags);
	cli();
	retval = *m;
	*m = val;
	restore_flags(flags);
	return retval;
#endif /* Processor-dependent optimization */
}

#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
#define tas(ptr) (xchg((ptr),1))

static __inline__ unsigned long
__xchg(unsigned long x, volatile void * ptr, int size)
{
	switch (size) {
		case 4:
			return xchg_u32(ptr, x);
	}
	return x;
}

extern void *set_except_vector(int n, void *addr);

extern void __die(const char *, struct pt_regs *, const char *where,
	unsigned long line) __attribute__((noreturn));
extern void __die_if_kernel(const char *, struct pt_regs *, const char *where,
	unsigned long line);

#define die(msg, regs)							\
	__die(msg, regs, __FILE__ ":"__FUNCTION__, __LINE__)
#define die_if_kernel(msg, regs)					\
	__die_if_kernel(msg, regs, __FILE__ ":"__FUNCTION__, __LINE__)

#endif /* _ASM_SYSTEM_H */
