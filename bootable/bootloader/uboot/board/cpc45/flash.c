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
 * (C) Copyright 2001-2003
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <mpc824x.h>
#include <asm/processor.h>

#if defined(CONFIG_ENV_IS_IN_FLASH)
# ifndef  CONFIG_ENV_ADDR
#  define CONFIG_ENV_ADDR	(CONFIG_SYS_FLASH_BASE + CONFIG_ENV_OFFSET)
# endif
# ifndef  CONFIG_ENV_SIZE
#  define CONFIG_ENV_SIZE	CONFIG_ENV_SECT_SIZE
# endif
# ifndef  CONFIG_ENV_SECT_SIZE
#  define CONFIG_ENV_SECT_SIZE  CONFIG_ENV_SIZE
# endif
#endif

#define FLASH_BANK_SIZE 0x800000
#define MAIN_SECT_SIZE  0x40000
#define PARAM_SECT_SIZE 0x8000

flash_info_t flash_info[CONFIG_SYS_MAX_FLASH_BANKS];

static int write_data (flash_info_t * info, ulong dest, ulong * data);
static void write_via_fpu (vu_long * addr, ulong * data);
static __inline__ unsigned long get_msr (void);
static __inline__ void set_msr (unsigned long msr);

/*---------------------------------------------------------------------*/
#undef	DEBUG_FLASH

/*---------------------------------------------------------------------*/
#ifdef DEBUG_FLASH
#define DEBUGF(fmt,args...) printf(fmt ,##args)
#else
#define DEBUGF(fmt,args...)
#endif
/*---------------------------------------------------------------------*/

/*-----------------------------------------------------------------------
 */

unsigned long flash_init (void)
{
	int i, j;
	ulong size = 0;
	uchar tempChar;
	vu_long *tmpaddr;

	/* Enable flash writes on CPC45 */

	tempChar = BOARD_CTRL;

	tempChar |= (B_CTRL_FWPT_1 | B_CTRL_FWRE_1);

	tempChar &= ~(B_CTRL_FWPT_0 | B_CTRL_FWRE_0);

	BOARD_CTRL = tempChar;

	__asm__ volatile ("sync\n eieio");

	for (i = 0; i < CONFIG_SYS_MAX_FLASH_BANKS; i++) {
		vu_long *addr = (vu_long *) (CONFIG_SYS_FLASH_BASE + i * FLASH_BANK_SIZE);

		addr[0] = 0x00900090;

		__asm__ volatile ("sync\n eieio");

		udelay (100);

		DEBUGF ("Flash bank # %d:\n"
			"\tManuf. ID @ 0x%08lX: 0x%08lX\n"
			"\tDevice ID @ 0x%08lX: 0x%08lX\n",
			i,
			(ulong) (&addr[0]), addr[0],
			(ulong) (&addr[2]), addr[2]);


		if ((addr[0] == addr[1]) && (addr[0] == INTEL_MANUFACT) &&
		    (addr[2] == addr[3]) && (addr[2] == INTEL_ID_28F160F3T)) {

			flash_info[i].flash_id =
				(FLASH_MAN_INTEL & FLASH_VENDMASK) |
				(INTEL_ID_28F160F3T & FLASH_TYPEMASK);

		} else if ((addr[0] == addr[1]) && (addr[0] == INTEL_MANUFACT)
			 && (addr[2] == addr[3])
			 && (addr[2] == INTEL_ID_28F160C3T)) {

			flash_info[i].flash_id =
				(FLASH_MAN_INTEL & FLASH_VENDMASK) |
				(INTEL_ID_28F160C3T & FLASH_TYPEMASK);

		} else {
			flash_info[i].flash_id = FLASH_UNKNOWN;
			addr[0] = 0xFFFFFFFF;
			goto Done;
		}

		DEBUGF ("flash_id = 0x%08lX\n", flash_info[i].flash_id);

		addr[0] = 0xFFFFFFFF;

		flash_info[i].size = FLASH_BANK_SIZE;
		flash_info[i].sector_count = CONFIG_SYS_MAX_FLASH_SECT;
		memset (flash_info[i].protect, 0, CONFIG_SYS_MAX_FLASH_SECT);
		for (j = 0; j < flash_info[i].sector_count; j++) {
			if (j > 30) {
				flash_info[i].start[j] = CONFIG_SYS_FLASH_BASE +
					i * FLASH_BANK_SIZE +
					(MAIN_SECT_SIZE * 31) + (j -
								 31) *
					PARAM_SECT_SIZE;
			} else {
				flash_info[i].start[j] = CONFIG_SYS_FLASH_BASE +
					i * FLASH_BANK_SIZE +
					j * MAIN_SECT_SIZE;
			}
		}

		/* unlock sectors, if 160C3T */

		for (j = 0; j < flash_info[i].sector_count; j++) {
			tmpaddr = (vu_long *) flash_info[i].start[j];

			if ((flash_info[i].flash_id & FLASH_TYPEMASK) ==
			    (INTEL_ID_28F160C3T & FLASH_TYPEMASK)) {
				tmpaddr[0] = 0x00600060;
				tmpaddr[0] = 0x00D000D0;
				tmpaddr[1] = 0x00600060;
				tmpaddr[1] = 0x00D000D0;
			}
		}

		size += flash_info[i].size;

		addr[0] = 0x00FF00FF;
		addr[1] = 0x00FF00FF;
	}

	/* Protect monitor and environment sectors
	 */
#if CONFIG_SYS_MONITOR_BASE >= CONFIG_SYS_FLASH_BASE + FLASH_BANK_SIZE
	flash_protect (FLAG_PROTECT_SET,
		       CONFIG_SYS_MONITOR_BASE,
		       CONFIG_SYS_MONITOR_BASE + monitor_flash_len - 1,
		       &flash_info[1]);
#else
	flash_protect (FLAG_PROTECT_SET,
		       CONFIG_SYS_MONITOR_BASE,
		       CONFIG_SYS_MONITOR_BASE + monitor_flash_len - 1,
		       &flash_info[0]);
#endif

#if defined(CONFIG_ENV_IS_IN_FLASH) && defined(CONFIG_ENV_ADDR)
#if CONFIG_ENV_ADDR >= CONFIG_SYS_FLASH_BASE + FLASH_BANK_SIZE
	flash_protect (FLAG_PROTECT_SET,
		       CONFIG_ENV_ADDR,
		       CONFIG_ENV_ADDR + CONFIG_ENV_SIZE - 1, &flash_info[1]);
#else
	flash_protect (FLAG_PROTECT_SET,
		       CONFIG_ENV_ADDR,
		       CONFIG_ENV_ADDR + CONFIG_ENV_SIZE - 1, &flash_info[0]);
#endif
#endif

Done:
	return size;
}

/*-----------------------------------------------------------------------
 */
void flash_print_info (flash_info_t * info)
{
	int i;

	switch ((i = info->flash_id & FLASH_VENDMASK)) {
	case (FLASH_MAN_INTEL & FLASH_VENDMASK):
		printf ("Intel: ");
		break;
	default:
		printf ("Unknown Vendor 0x%04x ", i);
		break;
	}

	switch ((i = info->flash_id & FLASH_TYPEMASK)) {
	case (INTEL_ID_28F160F3T & FLASH_TYPEMASK):
		printf ("28F160F3T (16Mbit)\n");
		break;

	case (INTEL_ID_28F160C3T & FLASH_TYPEMASK):
		printf ("28F160C3T (16Mbit)\n");
		break;

	default:
		printf ("Unknown Chip Type 0x%04x\n", i);
		goto Done;
		break;
	}

	printf ("  Size: %ld MB in %d Sectors\n",
		info->size >> 20, info->sector_count);

	printf ("  Sector Start Addresses:");
	for (i = 0; i < info->sector_count; i++) {
		if ((i % 5) == 0) {
			printf ("\n   ");
		}
		printf (" %08lX%s", info->start[i],
			info->protect[i] ? " (RO)" : "     ");
	}
	printf ("\n");

Done:
	return;
}

/*-----------------------------------------------------------------------
 */

int flash_erase (flash_info_t * info, int s_first, int s_last)
{
	int flag, prot, sect;
	ulong start, now, last;

	DEBUGF ("Erase flash bank %d sect %d ... %d\n",
		info - &flash_info[0], s_first, s_last);

	if ((s_first < 0) || (s_first > s_last)) {
		if (info->flash_id == FLASH_UNKNOWN) {
			printf ("- missing\n");
		} else {
			printf ("- no sectors to erase\n");
		}
		return 1;
	}

	if ((info->flash_id & FLASH_VENDMASK) !=
	    (FLASH_MAN_INTEL & FLASH_VENDMASK)) {
		printf ("Can erase only Intel flash types - aborted\n");
		return 1;
	}

	prot = 0;
	for (sect = s_first; sect <= s_last; ++sect) {
		if (info->protect[sect]) {
			prot++;
		}
	}

	if (prot) {
		printf ("- Warning: %d protected sectors will not be erased!\n", prot);
	} else {
		printf ("\n");
	}

	start = get_timer (0);
	last = start;
	/* Start erase on unprotected sectors */
	for (sect = s_first; sect <= s_last; sect++) {
		if (info->protect[sect] == 0) {	/* not protected */
			vu_long *addr = (vu_long *) (info->start[sect]);

			DEBUGF ("Erase sect %d @ 0x%08lX\n",
				sect, (ulong) addr);

			/* Disable interrupts which might cause a timeout
			 * here.
			 */
			flag = disable_interrupts ();

			addr[0] = 0x00500050;	/* clear status register */
			addr[0] = 0x00200020;	/* erase setup */
			addr[0] = 0x00D000D0;	/* erase confirm */

			addr[1] = 0x00500050;	/* clear status register */
			addr[1] = 0x00200020;	/* erase setup */
			addr[1] = 0x00D000D0;	/* erase confirm */

			/* re-enable interrupts if necessary */
			if (flag)
				enable_interrupts ();

			/* wait at least 80us - let's wait 1 ms */
			udelay (1000);

			while (((addr[0] & 0x00800080) != 0x00800080) ||
			       ((addr[1] & 0x00800080) != 0x00800080)) {
				if ((now = get_timer (start)) >
				    CONFIG_SYS_FLASH_ERASE_TOUT) {
					printf ("Timeout\n");
					addr[0] = 0x00B000B0;	/* suspend erase */
					addr[0] = 0x00FF00FF;	/* to read mode  */
					return 1;
				}

				/* show that we're waiting */
				if ((now - last) > 1000) {	/* every second  */
					putc ('.');
					last = now;
				}
			}

			addr[0] = 0x00FF00FF;
		}
	}
	printf (" done\n");
	return 0;
}

/*-----------------------------------------------------------------------
 * Copy memory to flash, returns:
 * 0 - OK
 * 1 - write timeout
 * 2 - Flash not erased
 * 4 - Flash not identified
 */

#define	FLASH_WIDTH	8	/* flash bus width in bytes */

int write_buff (flash_info_t * info, uchar * src, ulong addr, ulong cnt)
{
	ulong wp, cp, msr;
	int l, rc, i;
	ulong data[2];
	ulong *datah = &data[0];
	ulong *datal = &data[1];

	DEBUGF ("Flash write_buff: @ 0x%08lx, src 0x%08lx len %ld\n",
		addr, (ulong) src, cnt);

	if (info->flash_id == FLASH_UNKNOWN) {
		return 4;
	}

	msr = get_msr ();
	set_msr (msr | MSR_FP);

	wp = (addr & ~(FLASH_WIDTH - 1));	/* get lower aligned address */

	/*
	 * handle unaligned start bytes
	 */
	if ((l = addr - wp) != 0) {
		*datah = *datal = 0;

		for (i = 0, cp = wp; i < l; i++, cp++) {
			if (i >= 4) {
				*datah = (*datah << 8) |
					((*datal & 0xFF000000) >> 24);
			}

			*datal = (*datal << 8) | (*(uchar *) cp);
		}
		for (; i < FLASH_WIDTH && cnt > 0; ++i) {
			char tmp = *src++;

			if (i >= 4) {
				*datah = (*datah << 8) |
					((*datal & 0xFF000000) >> 24);
			}

			*datal = (*datal << 8) | tmp;
			--cnt;
			++cp;
		}

		for (; cnt == 0 && i < FLASH_WIDTH; ++i, ++cp) {
			if (i >= 4) {
				*datah = (*datah << 8) |
					((*datal & 0xFF000000) >> 24);
			}

			*datal = (*datah << 8) | (*(uchar *) cp);
		}

		if ((rc = write_data (info, wp, data)) != 0) {
			set_msr (msr);
			return (rc);
		}

		wp += FLASH_WIDTH;
	}

	/*
	 * handle FLASH_WIDTH aligned part
	 */
	while (cnt >= FLASH_WIDTH) {
		*datah = *(ulong *) src;
		*datal = *(ulong *) (src + 4);
		if ((rc = write_data (info, wp, data)) != 0) {
			set_msr (msr);
			return (rc);
		}
		wp += FLASH_WIDTH;
		cnt -= FLASH_WIDTH;
		src += FLASH_WIDTH;
	}

	if (cnt == 0) {
		set_msr (msr);
		return (0);
	}

	/*
	 * handle unaligned tail bytes
	 */
	*datah = *datal = 0;
	for (i = 0, cp = wp; i < FLASH_WIDTH && cnt > 0; ++i, ++cp) {
		char tmp = *src++;

		if (i >= 4) {
			*datah = (*datah << 8) | ((*datal & 0xFF000000) >>
						  24);
		}

		*datal = (*datal << 8) | tmp;
		--cnt;
	}

	for (; i < FLASH_WIDTH; ++i, ++cp) {
		if (i >= 4) {
			*datah = (*datah << 8) | ((*datal & 0xFF000000) >>
						  24);
		}

		*datal = (*datal << 8) | (*(uchar *) cp);
	}

	rc = write_data (info, wp, data);
	set_msr (msr);

	return (rc);
}

/*-----------------------------------------------------------------------
 * Write a word to Flash, returns:
 * 0 - OK
 * 1 - write timeout
 * 2 - Flash not erased
 */
static int write_data (flash_info_t * info, ulong dest, ulong * data)
{
	vu_long *addr = (vu_long *) dest;
	ulong start;
	int flag;

	/* Check if Flash is (sufficiently) erased */
	if (((addr[0] & data[0]) != data[0]) ||
	    ((addr[1] & data[1]) != data[1])) {
		return (2);
	}
	/* Disable interrupts which might cause a timeout here */
	flag = disable_interrupts ();

	addr[0] = 0x00400040;	/* write setup */
	write_via_fpu (addr, data);

	/* re-enable interrupts if necessary */
	if (flag)
		enable_interrupts ();

	start = get_timer (0);

	while (((addr[0] & 0x00800080) != 0x00800080) ||
	       ((addr[1] & 0x00800080) != 0x00800080)) {
		if (get_timer (start) > CONFIG_SYS_FLASH_WRITE_TOUT) {
			addr[0] = 0x00FF00FF;	/* restore read mode */
			return (1);
		}
	}

	addr[0] = 0x00FF00FF;	/* restore read mode */

	return (0);
}

/*-----------------------------------------------------------------------
 */
static void write_via_fpu (vu_long * addr, ulong * data)
{
	__asm__ __volatile__ ("lfd  1, 0(%0)"::"r" (data));
	__asm__ __volatile__ ("stfd 1, 0(%0)"::"r" (addr));
}

/*-----------------------------------------------------------------------
 */
static __inline__ unsigned long get_msr (void)
{
	unsigned long msr;

	__asm__ __volatile__ ("mfmsr %0":"=r" (msr):);

	return msr;
}

static __inline__ void set_msr (unsigned long msr)
{
	__asm__ __volatile__ ("mtmsr %0"::"r" (msr));
}
