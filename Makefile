# Build the tutorial PDF (pdflatex must run twice for a correct TOC).
MAIN = urlget_tutorial

.PHONY: all clean pdf

all: pdf

pdf:
	pdflatex -interaction=nonstopmode $(MAIN).tex
	pdflatex -interaction=nonstopmode $(MAIN).tex

clean:
	rm -f $(MAIN).aux $(MAIN).log $(MAIN).out $(MAIN).toc \
	      $(MAIN).lof $(MAIN).lot step*.aux
