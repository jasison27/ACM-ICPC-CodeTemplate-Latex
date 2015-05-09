template.pdf: template.tex main
	main
	pdflatex template.tex
	pdflatex template.tex
main: main.cpp
	cc main.cpp -o main