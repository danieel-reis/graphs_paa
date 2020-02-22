all:run

# Executaveis
run:	main.o	TPilha.o	TGrafo.o	TListaNave.o
	gcc	-o	run	main.o	TPilha.o	TGrafo.o	TListaNave.o

# Objetos
main.o:	main.c	TGrafo.h
	gcc -c -g main.c	TGrafo.c

TPilha.o:	TPilha.c	TPilha.h
	gcc -c -g TPilha.c

TListaNave.o:	TListaNave.c	TListaNave.h
	gcc -c -g TListaNave.c

TGrafo.o:	TGrafo.c	TGrafo.h	TPilha.h	TListaNave.h
	gcc -c -g TGrafo.c	TPilha.c	TListaNave.c

# Auxiliares
clean:
	rm -rf *o run

compile:
	make clean; clear; make
