cc= gcc
cflags= -Wextra -Wall

debogueur.o: debogueur.c stack.h array2D.h ensemble.h
	$(cc) -c debogueur.c $(cflags)

interpreteur.o: interpreteur.c stack.h array2D.h ensemble.h
	$(cc) -c interpreteur.c $(cflags)

debogueur: debogueur.o
	$(cc) -o debogueur debogueur.o

intepreteur: interpreteur.o
	$(cc) -o interpreteur interpreteur.o

