# #  Copyright (c) 2012, Texas Instruments Incorporated #  All rights reserved.  # #  Redistribution and use in source and binary forms, with or without #  modification, are permitted provided that the following conditions #  are met: # #  *  Redistributions of source code must retain the above copyright #     notice, this list of conditions and the following disclaimer.  # #  *  Redistributions in binary form must reproduce the above copyright #     notice, this list of conditions and the following disclaimer in the #     documentation and/or other materials provided with the distribution.  # #  *  Neither the name of Texas Instruments Incorporated nor the names of #     its contributors may be used to endorse or promote products derived #     from this software without specific prior written permission.  # #  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" #  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, #  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR #  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR #  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, #  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, #  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; #  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

#
#  ======== makefile ========
#


EXBASE = .
include ../products.mak


ifeq (,$(APP_INSTALL_BASE))
APP_INSTALL_BASE=/home/qwc/workdir/nfsroot
endif

#
#your application parameter

RMTHOST			= qwc@192.168.1.109
RMTPSWD			= 123456
LOCALPSWD		= 123456
REMOTE_INSTALL_ROOT 	= $(APP_INSTALL_BASE)/ti_tisdk_rootfs/syslink_test/
REMOTE_INSTALL_DIR  	= syslink

INSTALL_DIR		= /home/qwc/workdir/nfsroot/ti_tisdk_rootfs/syslink_test/syslink
#srcs 			= main_dsp.c syslink.c object.c syslink_notifier.c syslink_messageq.c syslink_ringpipe.c
goal 			= server_dsp

#srcs := $(patsubst %,dsc/%,$srcs)
#srcs 			:= $(srcs) syslink.c object.c syslink_notifier.c syslink_messageq.c syslink_ringpipe.c  

DIR_SRC =./app
srcs=$(wildcard $(DIR_SRC)/*.c)
incs= ./inc ./inc/codec2 ./inc/mcbsp ./inc/syslink ./inc/utils

ifeq (,$(VPATH))
	#VPATH = ../shared
	VPATH = app:../shared
endif
#vpath %.c app
#vpath %.c syslink

ifeq (,$(PROJECT_LOC))
	PROJECT_LOC = /mnt/hgfs/vmshare/test/haotdmr/dsp
endif
objs = $(addprefix bin/$(PROFILE)/obj/,$(patsubst %.c,%.oe674,$(notdir $(srcs))))
libs = configuro/linker.cmd


all: configuro/linker.cmd
#	$(MAKE) PROFILE=debug $(goal).x
	$(MAKE) PROFILE=release $(goal).x

$(goal).x: bin/$(PROFILE)/$(goal).xe674
bin/$(PROFILE)/$(goal).xe674: $(objs) $(libs)
	@$(ECHO) "#"
	@$(ECHO) "# Making $@ ..."
	$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

bin/$(PROFILE)/obj/%.oe674: %.h
bin/$(PROFILE)/obj/%.oe674: %.c
	@$(ECHO) "#"
	@$(ECHO) "# Making $@ ..."
	$(CC) $(CPPFLAGS) $(CFLAGS) --output_file=$@ -fc $<

configuro/linker.cmd: Dsp.cfg config.bld
	@$(ECHO) "#"
	@$(ECHO) "# Making $@ ..."
	$(XDC_INSTALL_DIR)/xs --xdcpath="$(subst +,;,$(PKGPATH))" \
            xdc.tools.configuro -o configuro \
            -t ti.targets.elf.C674 -c $(CGT_C674_ELF_INSTALL_DIR) \
            -p sylink_test \
            -r release Dsp.cfg

install:
	@$(ECHO) "#"
	@$(ECHO) "# Making $@ ..."
	@$(MKDIR) $(INSTALL_DIR)/debug
	$(CP) bin/debug/$(goal).xe674 $(INSTALL_DIR)/debug
	@$(MKDIR) $(INSTALL_DIR)/release
	$(CP) bin/release/$(goal).xe674 $(INSTALL_DIR)/release

commit:
#	@echo "topdir:$(TOPDIR),scriptsdir:$(SCRIPTS_DIR)"
	@$(ECHO) "#"
	@$(ECHO) "# Making $@ ..."
	@scpto.sh . $(REMOTE_INSTALL_DIR) 
#	@$(SCRIPTS_DIR)/autoscp.sh bin/debug/$(goal).xe674 $(REMOTE_INSTALL_DIR)/ $(RMTPSWD) $(LOCALPSWD)
#	@$(SCRIPTS_DIR)/autoscp.sh bin/release/$(goal).xe674 $(REMOTE_INSTALL_DIR)/ $(RMTPSWD) $(LOCALPSWD)
sync:
	@echo "#"
	@echo "# Synchronizing exec to windows..."
	@mvtowin.sh bin

help:
	@$(ECHO) "make                   # build executable"
	@$(ECHO) "make clean             # clean everything"

clean::
	$(RMDIR) configuro bin

PKGPATH := $(SYSLINK_INSTALL_DIR)/packages
PKGPATH := $(PKGPATH)+$(BIOS_INSTALL_DIR)/packages
PKGPATH := $(PKGPATH)+$(IPC_INSTALL_DIR)/packages
PKGPATH := $(PKGPATH)+$(XDC_INSTALL_DIR)/packages
PKGPATH := $(PKGPATH)+$(PDK_INSTALL_DIR)/packages
PKGPATH := $(PKGPATH)+$(EDMA3_INSTALL_DIR)/packages
PKGPATH := $(PKGPATH)+$(PROJECT_LOC)/packages
#ifneq (,$(SHARED_DIR))
#PKGPATH := $(PKGPATH)+$(SHARED_DIR)
#endif
#$(warning $(PKGPATH))

#  ======== install validation ========
ifeq (install,$(MAKECMDGOALS))
ifeq (,$(EXEC_DIR))
$(error must specify EXEC_DIR)
endif
endif

#  ======== toolchain macros ========
CGTOOLS = $(CGT_C674_ELF_INSTALL_DIR)

CC = $(CGTOOLS)/bin/cl6x -c --gcc
AR = $(CGTOOLS)/bin/ar6x rq
LD = $(CGTOOLS)/bin/lnk6x --abi=eabi
ST = $(CGTOOLS)/bin/strip6x

CPPFLAGS =
CFLAGS = -qq $(CCPROFILE_$(PROFILE)) -I. $(COMPILER_OPTS)\
		 -I ./inc -I ./inc/codec2 -I ./inc/mcbsp -I ./inc/syslink -I ./inc/utils\
		 -D=CHIP_OMPL138 -D=MCBSP_LOOP_PING_PONG -D=MCBSP_LOOPLOB_ENABLE

LDFLAGS = -w -q -c -m $(@D)/obj/$(@F).map --reread_libs
LDLIBS = -l $(CGTOOLS)/lib/rts6740_elf.lib\
		 -l $(PROJECT_LOC)/lib/codec2.lib \
		 -l $(PROJECT_LOC)/lib/mcbsplib.lib \
		 -l $(PROJECT_LOC)/lib/syslinklib.lib \
		 -l $(PROJECT_LOC)/lib/utils.lib \
		 -l $(PROJECT_LOC)/mcbsp.cmd

CCPROFILE_debug = -D_DEBUG_=1 --symdebug:dwarf
CCPROFILE_release = -O2
COMPILER_OPTS = $(shell cat configuro/compiler.opt)

#  ======== standard macros ========
ifneq (,$(wildcard $(XDC_INSTALL_DIR)/bin/echo.exe))
    # use these on Windows
    CP      = $(XDC_INSTALL_DIR)/bin/cp
    ECHO    = $(XDC_INSTALL_DIR)/bin/echo
    MKDIR   = $(XDC_INSTALL_DIR)/bin/mkdir -p
    RM      = $(XDC_INSTALL_DIR)/bin/rm -f
    RMDIR   = $(XDC_INSTALL_DIR)/bin/rm -rf
else
    # use these on Linux
    CP      = cp
    ECHO    = echo
    MKDIR   = mkdir -p
    RM      = rm -f
    RMDIR   = rm -rf
endif

#  ======== create output directories ========
ifneq (clean,$(MAKECMDGOALS))
ifneq (,$(PROFILE))
ifeq (,$(wildcard bin/$(PROFILE)/obj))
    $(shell $(MKDIR) -p bin/$(PROFILE)/obj)
endif
endif
endif
