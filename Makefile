#
# Copyright (C) 2026
# Created by asuyer-wpi, asuyer@wpi.edu
# 

# C compiler options
CC      := gcc
CFLAGS  := -Wall -g -DDEBUG 

simulation: simulation.c
	$(CC) $(CFLAGS) simulation.c -o simulation -lncurses 

plan.pdf: planning.md
	# TODO: Use Obsidian instead
	pandoc planning.md -o plan.pdf --pdf-engine=xelatex -f markdown-implicit_figures --template eisvogel

.PHONY: clean
clean: 
	rm -f plan.pdf simulation

