all: resultados_schro.txt plot_onda.py
	python plot_onda.py

resultados_schro.txt: schro.x
	./schro.x

schro.x: schrodinger.c
	cc schrodinger.c -lm -o schro.x

clean: 
	rm *.txt *.x *~
