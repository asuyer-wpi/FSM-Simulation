#
# Copyright (C) 2026
# Created by asuyer-wpi, asuyer@wpi.edu
# 

# C compiler options
CC      := gcc
CFLAGS  := -Wall -g

# Debug toggle (can be overridden from command line)
DEBUG_ENABLED ?= 0

ifeq ($(DEBUG_ENABLED),1)
CFLAGS += -DDEBUG
endif

simulation: simulation.c
	$(CC) $(CFLAGS) simulation.c -o simulation -lncurses 

.PHONY: clean
clean: 
	rm -f simulation

