# **********************************************************************
#
# Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

top_srcdir	= .

!include $(top_srcdir)/config/Make.rules.mak.cs

SUBDIRS		= src test config

INSTALL_SUBDIRS	= "$(install_bindir)" "$(install_assembliesdir)" "$(install_configdir)"

install:: install-common
	@for %i in ( $(INSTALL_SUBDIRS) ) do \
	    @if not exist %i \
		@echo "Creating %i..." && \
		mkdir %i

$(EVERYTHING_EXCEPT_INSTALL)::
	@for %i in ( $(SUBDIRS) ) do \
	    @echo "making $@ in %i" && \
	    cmd /c "cd %i && $(MAKE) -nologo -f Makefile.mak $@" || exit 1

test::
	@python $(top_srcdir)/allTests.py


SRC_FULL_PATH	= $(MAKEDIR:\.\=\)

registrykey=$(DOTNET_ASSEMBLIES_KEY)
registerpath=$(SRC_FULL_PATH)\Assemblies
installpath=$(prefix)\Assemblies

install::
	@for %i in ( src config ) do \
	    @echo "making $@ in %i" && \
	    cmd /c "cd %i && $(MAKE) -nologo -f Makefile.mak $@" || exit 1
	@echo Adding key "$(registrykey)" in Windows registry && \
	@reg ADD "$(registrykey)" /ve /d "$(installpath)" /f || \
	echo Could not add registry keyword "$(registrykey)" && exit 1
