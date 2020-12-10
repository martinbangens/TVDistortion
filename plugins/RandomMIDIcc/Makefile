#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by Martin Bångens
#
# Edited

# --------------------------------------------------------------
# Project name, used for binaries

NAME = RandomMIDIcc

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	RobotRandomMIDIccPlugin.cpp


# --------------------------------------------------------------
# Do some magic

include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Enable all possible plugin types

#GUI Not present
#ifeq ($(HAVE_JACK),true)
#TARGETS += jack
#endif

TARGETS += vst

ifeq ($(HAVE_DGL),true)
TARGETS += lv2_sep
else
TARGETS += lv2_dsp
endif

all: $(TARGETS)

# --------------------------------------------------------------
