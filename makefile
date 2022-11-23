p2: p2.c lista.h lista.o MemList.h MemList.o aux.h aux.o comandos.h comandos.o
	gcc -g -o p2 p2.c lista.o MemList.o aux.o comandos.o
	
aux.o: 
	gcc -g -c aux.h aux.c	
		
dynList.o:
	gcc -g -c lista.h lista.c	
	
MemList.o:
	gcc -g -c MemList.h MemList.c

comandos.o:
	gcc -g -c comandos.h comandos.c	
	
limpiar:
	rm p2 lista.o MemList.o
