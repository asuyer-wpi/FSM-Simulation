#
# Copyright (C) 2026
# Created by AndrewSuyer, andrew.suyer@icloud.com
# 

plan.pdf: planning.md
	# TODO: Use Obsidian instead
	pandoc planning.md -o plan.pdf --pdf-engine=xelatex -f markdown-implicit_figures --template eisvogel

.PHONY: clean
clean: 
	rm -f plan.pdf

