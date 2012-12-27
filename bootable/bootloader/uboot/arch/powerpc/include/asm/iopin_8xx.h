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
 */

/*
 * MPC8xx I/O port pin manipulation functions
 * Roughly based on iopin_8260.h
 */

#ifndef _ASM_IOPIN_8XX_H_
#define _ASM_IOPIN_8XX_H_

#include <linux/types.h>
#include <asm/8xx_immap.h>

#ifdef __KERNEL__

typedef struct {
	u_char port:2;	/* port number (A=0, B=1, C=2, D=3) */
	u_char pin:5;	/* port pin (0-31) */
	u_char flag:1;	/* for whatever */
} iopin_t;

#define IOPIN_PORTA	0
#define IOPIN_PORTB	1
#define IOPIN_PORTC	2
#define IOPIN_PORTD	3

extern __inline__ void
iopin_set_high(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_padat;
		*datp |= (1 << (15 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTB) {
		volatile uint *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbdat;
		*datp |= (1 << (31 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTC) {
		volatile ushort *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcdat;
		*datp |= (1 << (15 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTD) {
		volatile ushort *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pddat;
		*datp |= (1 << (15 - iopin->pin));
	}
}

extern __inline__ void
iopin_set_low(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_padat;
		*datp &= ~(1 << (15 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTB) {
		volatile uint *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbdat;
		*datp &= ~(1 << (31 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTC) {
		volatile ushort *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcdat;
		*datp &= ~(1 << (15 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTD) {
		volatile ushort *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pddat;
		*datp &= ~(1 << (15 - iopin->pin));
	}
}

extern __inline__ uint
iopin_is_high(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_padat;
		return (*datp >> (15 - iopin->pin)) & 1;
	} else if (iopin->port == IOPIN_PORTB) {
		volatile uint *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbdat;
		return (*datp >> (31 - iopin->pin)) & 1;
	} else if (iopin->port == IOPIN_PORTC) {
		volatile ushort *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcdat;
		return (*datp >> (15 - iopin->pin)) & 1;
	} else if (iopin->port == IOPIN_PORTD) {
		volatile ushort *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pddat;
		return (*datp >> (15 - iopin->pin)) & 1;
	}
	return 0;
}

extern __inline__ uint
iopin_is_low(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_padat;
		return ((*datp >> (15 - iopin->pin)) & 1) ^ 1;
	} else if (iopin->port == IOPIN_PORTB) {
		volatile uint *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbdat;
		return ((*datp >> (31 - iopin->pin)) & 1) ^ 1;
	} else if (iopin->port == IOPIN_PORTC) {
		volatile ushort *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcdat;
		return ((*datp >> (15 - iopin->pin)) & 1) ^ 1;
	} else if (iopin->port == IOPIN_PORTD) {
		volatile ushort *datp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pddat;
		return ((*datp >> (15 - iopin->pin)) & 1) ^ 1;
	}
	return 0;
}

extern __inline__ void
iopin_set_out(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_padir;
		*dirp |= (1 << (15 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTB) {
		volatile uint *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbdir;
		*dirp |= (1 << (31 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTC) {
		volatile ushort *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcdir;
		*dirp |= (1 << (15 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTD) {
		volatile ushort *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pddir;
		*dirp |= (1 << (15 - iopin->pin));
	}
}

extern __inline__ void
iopin_set_in(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_padir;
		*dirp &= ~(1 << (15 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTB) {
		volatile uint *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbdir;
		*dirp &= ~(1 << (31 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTC) {
		volatile ushort *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcdir;
		*dirp &= ~(1 << (15 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTD) {
		volatile ushort *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pddir;
		*dirp &= ~(1 << (15 - iopin->pin));
	}
}

extern __inline__ uint
iopin_is_out(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_padir;
		return (*dirp >> (15 - iopin->pin)) & 1;
	} else if (iopin->port == IOPIN_PORTB) {
		volatile uint *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbdir;
		return (*dirp >> (31 - iopin->pin)) & 1;
	} else if (iopin->port == IOPIN_PORTC) {
		volatile ushort *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcdir;
		return (*dirp >> (15 - iopin->pin)) & 1;
	} else if (iopin->port == IOPIN_PORTD) {
		volatile ushort *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pddir;
		return (*dirp >> (15 - iopin->pin)) & 1;
	}
	return 0;
}

extern __inline__ uint
iopin_is_in(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_padir;
		return ((*dirp >> (15 - iopin->pin)) & 1) ^ 1;
	} else if (iopin->port == IOPIN_PORTB) {
		volatile uint *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbdir;
		return ((*dirp >> (31 - iopin->pin)) & 1) ^ 1;
	} else if (iopin->port == IOPIN_PORTC) {
		volatile ushort *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcdir;
		return ((*dirp >> (15 - iopin->pin)) & 1) ^ 1;
	} else if (iopin->port == IOPIN_PORTD) {
		volatile ushort *dirp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pddir;
		return ((*dirp >> (15 - iopin->pin)) & 1) ^ 1;
	}
	return 0;
}

extern __inline__ void
iopin_set_odr(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *odrp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_paodr;
		*odrp |= (1 << (15 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTB) {
		volatile ushort *odrp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbodr;
		*odrp |= (1 << (31 - iopin->pin));
	}
}

extern __inline__ void
iopin_set_act(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *odrp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_paodr;
		*odrp &= ~(1 << (15 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTB) {
		volatile ushort *odrp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbodr;
		*odrp &= ~(1 << (31 - iopin->pin));
	}
}

extern __inline__ uint
iopin_is_odr(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *odrp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_paodr;
		return (*odrp >> (15 - iopin->pin)) & 1;
	} else if (iopin->port == IOPIN_PORTB) {
		volatile ushort *odrp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbodr;
		return (*odrp >> (31 - iopin->pin)) & 1;
	}
	return 0;
}

extern __inline__ uint
iopin_is_act(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *odrp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_paodr;
		return ((*odrp >> (15 - iopin->pin)) & 1) ^ 1;
	} else if (iopin->port == IOPIN_PORTB) {
		volatile ushort *odrp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbodr;
		return ((*odrp >> (31 - iopin->pin)) & 1) ^ 1;
	}
	return 0;
}

extern __inline__ void
iopin_set_ded(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_papar;
		*parp |= (1 << (15 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTB) {
		volatile uint *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbpar;
		*parp |= (1 << (31 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTC) {
		volatile ushort *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcpar;
		*parp |= (1 << (15 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTD) {
		volatile ushort *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pdpar;
		*parp |= (1 << (15 - iopin->pin));
	}
}

extern __inline__ void
iopin_set_gen(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_papar;
		*parp &= ~(1 << (15 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTB) {
		volatile uint *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbpar;
		*parp &= ~(1 << (31 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTC) {
		volatile ushort *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcpar;
		*parp &= ~(1 << (15 - iopin->pin));
	} else if (iopin->port == IOPIN_PORTD) {
		volatile ushort *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pdpar;
		*parp &= ~(1 << (15 - iopin->pin));
	}
}

extern __inline__ uint
iopin_is_ded(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_papar;
		return (*parp >> (15 - iopin->pin)) & 1;
	} else if (iopin->port == IOPIN_PORTB) {
		volatile uint *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbpar;
		return (*parp >> (31 - iopin->pin)) & 1;
	} else if (iopin->port == IOPIN_PORTC) {
		volatile ushort *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcpar;
		return (*parp >> (15 - iopin->pin)) & 1;
	} else if (iopin->port == IOPIN_PORTD) {
		volatile ushort *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pdpar;
		return (*parp >> (15 - iopin->pin)) & 1;
	}
	return 0;
}

extern __inline__ uint
iopin_is_gen(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTA) {
		volatile ushort *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_papar;
		return ((*parp >> (15 - iopin->pin)) & 1) ^ 1;
	} else if (iopin->port == IOPIN_PORTB) {
		volatile uint *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_cpm.cp_pbpar;
		return ((*parp >> (31 - iopin->pin)) & 1) ^ 1;
	} else if (iopin->port == IOPIN_PORTC) {
		volatile ushort *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcpar;
		return ((*parp >> (15 - iopin->pin)) & 1) ^ 1;
	} else if (iopin->port == IOPIN_PORTD) {
		volatile ushort *parp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pdpar;
		return ((*parp >> (15 - iopin->pin)) & 1) ^ 1;
	}
	return 0;
}

extern __inline__ void
iopin_set_opt2(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTC) {
		volatile ushort *sorp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcso;
		*sorp |= (1 << (15 - iopin->pin));
	}
}

extern __inline__ void
iopin_set_opt1(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTC) {
		volatile ushort *sorp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcso;
		*sorp &= ~(1 << (15 - iopin->pin));
	}
}

extern __inline__ uint
iopin_is_opt2(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTC) {
		volatile ushort *sorp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcso;
		return (*sorp >> (15 - iopin->pin)) & 1;
	}
	return 0;
}

extern __inline__ uint
iopin_is_opt1(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTC) {
		volatile ushort *sorp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcso;
		return ((*sorp >> (15 - iopin->pin)) & 1) ^ 1;
	}
	return 0;
}

extern __inline__ void
iopin_set_falledge(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTC) {
		volatile ushort *intp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcint;
		*intp |= (1 << (15 - iopin->pin));
	}
}

extern __inline__ void
iopin_set_anyedge(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTC) {
		volatile ushort *intp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcint;
		*intp &= ~(1 << (15 - iopin->pin));
	}
}

extern __inline__ uint
iopin_is_falledge(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTC) {
		volatile ushort *intp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcint;
		return (*intp >> (15 - iopin->pin)) & 1;
	}
	return 0;
}

extern __inline__ uint
iopin_is_anyedge(iopin_t *iopin)
{
	if (iopin->port == IOPIN_PORTC) {
		volatile ushort *intp = &((immap_t *)CONFIG_SYS_IMMR)->im_ioport.iop_pcint;
		return ((*intp >> (15 - iopin->pin)) & 1) ^ 1;
	}
	return 0;
}

#endif /* __KERNEL__ */

#endif /* _ASM_IOPIN_8XX_H_ */
