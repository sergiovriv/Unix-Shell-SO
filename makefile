
EXECUTABLE = p1
CFLAGS = -Wall

shell: p1.c
	gcc $(CFLAGS) -o $(EXECUTABLE) p1.c comandos.c comandos.h lista.c lista.h