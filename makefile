p3: p3.c lista.h lista.o MemList.h MemList.o ProcList.o ProcList.h aux.h aux.o comandos.h comandos.o
	gcc -g -o p3 p3.c lista.o MemList.o ProcList.o aux.o comandos.o
	
aux.o: 
	gcc -g -c aux.h aux.c	
		
dynList.o:
	gcc -g -c lista.h lista.c	
	
MemList.o:
	gcc -g -c MemList.h MemList.c

ProcList.o:
	gcc -g -c ProcList.h ProcList.c
	
comandos.o:
	gcc -g -c comandos.h comandos.c	
	
limpiar:
	rm p3 lista.o MemList.o ProcList.o aux.o comandos.o 
