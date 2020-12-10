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
	RobotTVDistortionPlugin.cpp

FILES_UI  = \
	RobotTVDistortionArtwork.cpp \
	RobotTVDistortionUI.cpp

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
endif


# Use c++ 17

#CXXFLAGS += -std=c++17

all: $(TARGETS)

# --------------------------------------------------------------
