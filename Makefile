#
# Copyright (C) 2026
# Created by asuyer-wpi, asuyer@wpi.edu
# 

# C compiler options
# Add -DDEBUG to CFLAGS to enable debug messages
CC      := gcc
CFLAGS  := -Wall -g -DDEBUG

simulation: simulation.c
	$(CC) $(CFLAGS) simulation.c -o simulation -lncurses 

.PHONY: clean
clean: 
	rm -f simulation

