all: resultados_onda.txt plot_onda.py
	python plot_onda.py

resultados_onda.txt: cuerda.x
	./cuerda.x

cuerda.x: onda_cuerda.c
	cc onda_cuerda.c -lm -o cuerda.x

clean: 
	rm *.txt *.x *~
