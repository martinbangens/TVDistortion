#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by Martin Bångens
#
# Edited

include dpf/Makefile.base.mk

all: dgl plugins gen

# --------------------------------------------------------------

PREFIX  ?= /usr/local
DESTDIR ?=

# --------------------------------------------------------------

HAVE_PROJM = $(shell pkg-config --exists libprojectM && echo true)

# --------------------------------------------------------------

dgl:
ifeq ($(HAVE_CAIRO_OR_OPENGL),true)
	$(MAKE) -C dpf/dgl
endif

plugins: dgl

	$(MAKE) all -C plugins/TVDistortion
	$(MAKE) all -C plugins/RandomMIDIcc


ifneq ($(CROSS_COMPILING),true)
gen: plugins dpf/utils/lv2_ttl_generator
	@$(CURDIR)/dpf/utils/generate-ttl.sh
ifeq ($(MACOS),true)
	@$(CURDIR)/dpf/utils/generate-vst-bundles.sh
endif

dpf/utils/lv2_ttl_generator:
	$(MAKE) -C dpf/utils/lv2-ttl-generator
else
gen:
endif

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf/dgl
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator
	$(MAKE) clean -C plugins/TVDistortion
	$(MAKE) clean -C plugins/RandomMIDIcc


# --------------------------------------------------------------

install:
	install -d $(DESTDIR)$(PREFIX)/lib/ladspa/
	install -d $(DESTDIR)$(PREFIX)/lib/dssi/
	install -d $(DESTDIR)$(PREFIX)/lib/lv2/
	install -d $(DESTDIR)$(PREFIX)/lib/vst/
	install -d $(DESTDIR)$(PREFIX)/bin/

	install -m 644 bin/*-ladspa.* $(DESTDIR)$(PREFIX)/lib/ladspa/
	install -m 644 bin/*-dssi.*   $(DESTDIR)$(PREFIX)/lib/dssi/
	install -m 644 bin/*-vst.*    $(DESTDIR)$(PREFIX)/lib/vst/

ifeq ($(HAVE_CAIRO_OR_OPENGL),true)
	cp -r bin/*-dssi  $(DESTDIR)$(PREFIX)/lib/dssi/
endif # HAVE_CAIRO_OR_OPENGL
	cp -r bin/*.lv2   $(DESTDIR)$(PREFIX)/lib/lv2/

ifeq ($(HAVE_JACK),true)
	install -m 755 bin/TVDistortion             $(DESTDIR)$(PREFIX)/bin/
#GUI Not present	install -m 755 bin/RandomMIDIcc             $(DESTDIR)$(PREFIX)/bin/
endif # HAVE_JACK

# --------------------------------------------------------------

.PHONY: plugins
