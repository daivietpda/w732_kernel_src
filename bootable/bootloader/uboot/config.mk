# Copyright Statement:
#
# This software/firmware and related documentation ("MediaTek Software") are
# protected under relevant copyright laws. The information contained herein
# is confidential and proprietary to MediaTek Inc. and/or its licensors.
# Without the prior written permission of MediaTek inc. and/or its licensors,
# any reproduction, modification, use or disclosure of MediaTek Software,
# and information contained herein, in whole or in part, shall be strictly prohibited.
#
# MediaTek Inc. (C) 2010. All rights reserved.
#
# BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
# THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
# RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
# AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
# NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
# SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
# SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
# THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
# THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
# CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
# SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
# STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
# CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
# AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
# OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
# MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
#
# The following software/firmware and/or related documentation ("MediaTek Software")
# have been modified by MediaTek Inc. All revisions are subject to any receiver's
# applicable license agreements with MediaTek Inc.


#
# (C) Copyright 2000-2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

#########################################################################
# Purpose:
#	Specify compile tool chain and compile options
#
# History:
# 2010/03/29	Shu-Hsin: according to specified platform, adding custom related header files
#
#

#########################################################################

#ifeq (,$(MTK_ROOT))
include $(abspath $(TOPDIR)/../../../mediatek/build/Makefile)
$(call codebase-path,uboot)
#endif

ifneq ($(OBJTREE),$(SRCTREE))
ifeq ($(CURDIR),$(SRCTREE))
dir :=
else
dir := $(subst $(SRCTREE)/,,$(CURDIR))
endif

obj := $(if $(dir),$(OBJTREE)/$(dir)/,$(OBJTREE)/)
src := $(if $(dir),$(SRCTREE)/$(dir)/,$(SRCTREE)/)

$(shell mkdir -p $(obj))
else
obj :=
src :=
endif

# clean the slate ...
PLATFORM_RELFLAGS = -ffunction-sections
PLATFORM_CPPFLAGS =
PLATFORM_LDFLAGS = --gc-sections 

#########################################################################

HOSTCFLAGS	= -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer \
		  $(HOSTCPPFLAGS)
HOSTSTRIP	= strip

#
# Mac OS X / Darwin's C preprocessor is Apple specific.  It
# generates numerous errors and warnings.  We want to bypass it
# and use GNU C's cpp.  To do this we pass the -traditional-cpp
# option to the compiler.  Note that the -traditional-cpp flag
# DOES NOT have the same semantics as GNU C's flag, all it does
# is invoke the GNU preprocessor in stock ANSI/ISO C fashion.
#
# Apple's linker is similar, thanks to the new 2 stage linking
# multiple symbol definitions are treated as errors, hence the
# -multiply_defined suppress option to turn off this error.
#

ifeq ($(HOSTOS),darwin)
# get major and minor product version (e.g. '10' and '6' for Snow Leopard)
DARWIN_MAJOR_VERSION	= $(shell sw_vers -productVersion | cut -f 1 -d '.')
DARWIN_MINOR_VERSION	= $(shell sw_vers -productVersion | cut -f 2 -d '.')

before-snow-leopard	= $(shell if [ $(DARWIN_MAJOR_VERSION) -le 10 -a \
	$(DARWIN_MINOR_VERSION) -le 5 ] ; then echo "$(1)"; else echo "$(2)"; fi ;)

# Snow Leopards build environment has no longer restrictions as described above
HOSTCC		 = $(call before-snow-leopard, "cc", "gcc")
HOSTCFLAGS	+= $(call before-snow-leopard, "-traditional-cpp")
HOSTLDFLAGS	+= $(call before-snow-leopard, "-multiply_defined suppress")
else
HOSTCC		= gcc
endif

ifeq ($(HOSTOS),cygwin)
HOSTCFLAGS	+= -ansi
endif

# We build some files with extra pedantic flags to try to minimize things
# that won't build on some weird host compiler -- though there are lots of
# exceptions for files that aren't complaint.

HOSTCFLAGS_NOPED = $(filter-out -pedantic,$(HOSTCFLAGS))
HOSTCFLAGS	+= -pedantic

#########################################################################
#
# Option checker (courtesy linux kernel) to ensure
# only supported compiler options are used
#
cc-option = $(shell if $(CC) $(CFLAGS) $(1) -S -o /dev/null -xc /dev/null \
		> /dev/null 2>&1; then echo "$(1)"; else echo "$(2)"; fi ;)

#
# Include the make variables (CC, etc...)
#
AS	= $(CROSS_COMPILE)as
# Todo: for arm-eabi-4.4.3 tool-chain,
# set $(LD) back to $(CROSS_COMPILE)ld once "internal error in relocation" bug fixed
LD	= $(CROSS_COMPILE)ld.bfd
CC	= $(CROSS_COMPILE)gcc
CPP	= $(CC) -E
AR	= $(CROSS_COMPILE)ar
NM	= $(CROSS_COMPILE)nm
LDR	= $(CROSS_COMPILE)ldr
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
RANLIB	= $(CROSS_COMPILE)RANLIB

#########################################################################

# Load generated board configuration
sinclude $(OBJTREE)/include/autoconf.mk

# Some architecture config.mk files need to know what CPUDIR is set to,
# so calculate CPUDIR before including ARCH/SOC/CPU config.mk files.
# Check if arch/$ARCH/cpu/$CPU exists, otherwise assume arch/$ARCH/cpu contains
# CPU-specific code.
CPUDIR=arch/$(ARCH)/cpu/$(CPU)
ifneq ($(SRCTREE)/$(CPUDIR),$(wildcard $(SRCTREE)/$(CPUDIR)))
CPUDIR=arch/$(ARCH)/cpu
endif

sinclude $(TOPDIR)/arch/$(ARCH)/config.mk	# include architecture dependend rules
sinclude $(TOPDIR)/$(CPUDIR)/config.mk		# include  CPU	specific rules

ifdef	SOC
sinclude $(TOPDIR)/$(CPUDIR)/$(SOC)/config.mk	# include  SoC	specific rules
endif
ifdef	VENDOR
BOARDDIR = $(VENDOR)/$(BOARD)
else
BOARDDIR = $(BOARD)
endif
ifdef	BOARD
sinclude $(TOPDIR)/board/$(BOARDDIR)/config.mk	# include board specific rules
endif

include $(MTK_PATH_PLATFORM)/config.mk
include $(MTK_PATH_CUSTOM)/config.mk
#########################################################################

ifneq (,$(findstring s,$(MAKEFLAGS)))
ARFLAGS = cr
else
ARFLAGS = crv
endif
RELFLAGS= $(PLATFORM_RELFLAGS)
DBGFLAGS= -g # -DDEBUG
OPTFLAGS= -Os #-fomit-frame-pointer
ifndef LDSCRIPT
#LDSCRIPT := $(TOPDIR)/board/$(BOARDDIR)/u-boot.lds.debug
ifeq ($(CONFIG_NAND_U_BOOT),y)
LDSCRIPT := $(TOPDIR)/board/$(BOARDDIR)/u-boot-nand.lds
else
LDSCRIPT := $(TOPDIR)/board/$(BOARDDIR)/u-boot.lds
endif
endif
OBJCFLAGS += --gap-fill=0xff

gccincdir := $(shell $(CC) -print-file-name=include)

CPPFLAGS := $(DBGFLAGS) $(OPTFLAGS) $(RELFLAGS)		\
	-D__KERNEL__
ifneq ($(TEXT_BASE),)
CPPFLAGS += -DTEXT_BASE=$(TEXT_BASE)
endif

ifneq ($(RESET_VECTOR_ADDRESS),)
CPPFLAGS += -DRESET_VECTOR_ADDRESS=$(RESET_VECTOR_ADDRESS)
endif

ifneq ($(OBJTREE),$(SRCTREE))
CPPFLAGS += -I$(OBJTREE)/include2 -I$(OBJTREE)/include
endif


##############################################################
# according to specified platform, adding custom related header files
# Hong-Rong: past from old-version and modify the include-path

CUSTOM_HEADER := include/asm/arch/custom/$(_TMP_MTK_PROJECT)/
CFLAGS += -I$(TOPDIR)/include/asm/arch/custom/inc/
CFLAGS += -I$(TOPDIR)/include/asm/arch/custom/$(_TMP_MTK_PROJECT)/

CPPFLAGS += -I$(TOPDIR)/include/asm/arch/custom/inc/
CPPFLAGS += -I$(TOPDIR)/include/asm/arch/custom/$(_TMP_MTK_PROJECT)/

#CUSTOM_HEADER := include/asm-$(ARCH)/arch-$(CPU)/custom/$(_TMP_MTK_PROJECT)/
#CFLAGS += -I$(TOPDIR)/include/asm-$(ARCH)/arch-$(CPU)/custom/inc/
#CFLAGS += -I$(TOPDIR)/include/asm-$(ARCH)/arch-$(CPU)/custom/$(_TMP_MTK_PROJECT)/

#CPPFLAGS += -I$(TOPDIR)/include/asm-$(ARCH)/arch-$(CPU)/custom/inc/
#CPPFLAGS += -I$(TOPDIR)/include/asm-$(ARCH)/arch-$(CPU)/custom/$(_TMP_MTK_PROJECT)/

##############################################################


CPPFLAGS += -I$(TOPDIR)/include
CPPFLAGS += -fno-builtin -ffreestanding -nostdinc	\
	-isystem $(gccincdir) -pipe $(PLATFORM_CPPFLAGS)

ifdef BUILD_TAG
CFLAGS := $(CPPFLAGS) -Wall -Wstrict-prototypes \
	-DBUILD_TAG='"$(BUILD_TAG)"'
else
CFLAGS := $(CPPFLAGS) -Wall -Wstrict-prototypes
endif

CFLAGS += $(call cc-option,-fno-stack-protector)

# avoid trigraph warnings while parsing pci.h (produced by NIOS gcc-2.9)
# this option have to be placed behind -Wall -- that's why it is here
ifeq ($(ARCH),nios)
ifeq ($(findstring 2.9,$(shell $(CC) --version)),2.9)
CFLAGS := $(CPPFLAGS) -Wall -Wno-trigraphs
endif
endif

# $(CPPFLAGS) sets -g, which causes gcc to pass a suitable -g<format>
# option to the assembler.
AFLAGS_DEBUG :=

# turn jbsr into jsr for m68k
ifeq ($(ARCH),m68k)
ifeq ($(findstring 3.4,$(shell $(CC) --version)),3.4)
AFLAGS_DEBUG := -Wa,-gstabs,-S
endif
endif

AFLAGS := $(AFLAGS_DEBUG) -D__ASSEMBLY__ $(CPPFLAGS)

LDFLAGS += -Bstatic -T $(obj)u-boot.lds $(PLATFORM_LDFLAGS)
ifneq ($(TEXT_BASE),)
LDFLAGS += -Ttext $(TEXT_BASE)
endif

# Location of a usable BFD library, where we define "usable" as
# "built for ${HOST}, supports ${TARGET}".  Sensible values are
# - When cross-compiling: the root of the cross-environment
# - Linux/ppc (native): /usr
# - NetBSD/ppc (native): you lose ... (must extract these from the
#   binutils build directory, plus the native and U-Boot include
#   files don't like each other)
#
# So far, this is used only by tools/gdb/Makefile.

ifeq ($(HOSTOS),darwin)
BFD_ROOT_DIR =		/usr/local/tools
else
ifeq ($(HOSTARCH),$(ARCH))
# native
BFD_ROOT_DIR =		/usr
else
#BFD_ROOT_DIR =		/LinuxPPC/CDK		# Linux/i386
#BFD_ROOT_DIR =		/usr/pkg/cross		# NetBSD/i386
BFD_ROOT_DIR =		/opt/powerpc
endif
endif

# Hong-Rong: Add config to identufy USER BUILD
ifeq ($(TARGET_BUILD_VARIANT),user)
 CFLAGS += -DUSER_BUILD
endif
CFLAGS   += $(MTK_CFLAGS) $(MTK_CDEFS) $(MTK_INC) -DBUILD_UBOOT
CPPFLAGS += $(MTK_CPPFLAGS) $(MTK_CPPDEFS) $(MTK_INC) -DBUILD_UBOOT
CPPFLAGS += -I$(TOPDIR)/../../../mediatek/custom/out/$(MTK_PROJECT)/kernel/dct/
AFLAGS   += $(MTK_AFLAGS) $(MTK_ADEFS)
#########################################################################

export	HOSTCC HOSTCFLAGS HOSTLDFLAGS PEDCFLAGS HOSTSTRIP CROSS_COMPILE \
	AS LD CC CPP AR NM STRIP OBJCOPY OBJDUMP MAKE
export	TEXT_BASE PLATFORM_CPPFLAGS PLATFORM_RELFLAGS CPPFLAGS CFLAGS AFLAGS CUSTOM_HEADER

#Added by Hong-Rong: Change arm-linx- to arm-eabi-
export USE_PRIVATE_LIBGCC = yes
#########################################################################

# Allow boards to use custom optimize flags on a per dir/file basis
BCURDIR = $(subst $(SRCTREE)/,,$(CURDIR:$(obj)%=%))
$(obj)%.s:	%.S
	$(CPP) $(AFLAGS) $(AFLAGS_$(BCURDIR)/$(@F)) $(AFLAGS_$(BCURDIR)) \
		-o $@ $<
$(obj)%.o:	%.S
	$(CC)  $(AFLAGS) $(AFLAGS_$(BCURDIR)/$(@F)) $(AFLAGS_$(BCURDIR)) \
		-o $@ $< -c
$(obj)%.o:	%.c
	$(CC)  $(CFLAGS) $(CFLAGS_$(BCURDIR)/$(@F)) $(CFLAGS_$(BCURDIR)) \
		-o $@ $< -c
$(obj)%.i:	%.c
	$(CPP) $(CFLAGS) $(CFLAGS_$(BCURDIR)/$(@F)) $(CFLAGS_$(BCURDIR)) \
		-o $@ $< -c
$(obj)%.s:	%.c
	$(CC)  $(CFLAGS) $(CFLAGS_$(BCURDIR)/$(@F)) $(CFLAGS_$(BCURDIR)) \
		-o $@ $< -c -S

include $(SRCTREE)/mtk-config.mk
#########################################################################
