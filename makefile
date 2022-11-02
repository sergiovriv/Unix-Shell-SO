
EXECUTABLE = p1
CFLAGS = -Wall

shell: shell.c
	gcc $(CFLAGS) -o $(EXECUTABLE) p1.c comandos.c comandos.h lista.c lista.h