all: trab2

trablib.o: trablib.c
	gcc -c trablib.c
	
trabmain.o: trabmain.c
	gcc -c trabmain.c
	
trab2: trablib.o trabmain.o
	gcc -o trab2 trablib.o trabmain.o -lm
