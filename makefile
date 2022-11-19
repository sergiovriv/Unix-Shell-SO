main.out: p1.c lista.h lista.o MemList.h MemList.o aux.h aux.o comandos.h comandos.o
	gcc -g -o main.out p1.c lista.o MemList.o aux.o comandos.o
comandos.o:
	gcc -g -c comandos.c comandos.h
aux.o:
	gcc -g -c aux.h aux.c
dynList.o:
	gcc -g -c lista.h lista.c	
MemList.o:
	gcc -g -c MemList.h MemList.c
limpiar:
	rm main.out lista.o MemList.o