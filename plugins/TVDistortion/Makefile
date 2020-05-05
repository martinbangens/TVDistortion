#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by Martin Bångens
#
# Edited

# --------------------------------------------------------------
# Project name, used for binaries

NAME = TVDistortion

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	DistoTVPlugin.cpp

FILES_UI  = \
	DistoTVArtwork.cpp \
	DistoTVUI.cpp

# --------------------------------------------------------------
# Do some magic

include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(HAVE_JACK),true)
TARGETS += jack
endif

TARGETS += vst

ifeq ($(HAVE_DGL),true)
ifeq ($(HAVE_LIBLO),true)
TARGETS += dssi
endif
endif

ifeq ($(HAVE_DGL),true)
TARGETS += lv2_sep
else
TARGETS += lv2_dsp
endif

all: $(TARGETS)

# --------------------------------------------------------------
