#ifndef CLION_COMANDOS_H
#define CLION_COMANDOS_H

#include "lista.h"
#include "MemList.h"

#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <errno.h>
#include <dirent.h>
#include <grp.h>

#define MAX 100

void autores(char trozos[1], int ntrozos);

void fecha(char trozos[1], int ntrozos);

void pid(char trozos[1], int ntrozos);

void infosis();

void hist(char trozos[1], int ntrozos, List *head);

void carpeta(char *trozos[], int ntrozos);

void ayuda(char trozos[1], int ntrozos);

void salir(char trozos[0]);

void comandoN(char trozos[1], int ntrozos, List *head, MemList *M, MemList *S, MemList *MP);
int leerEntrada(char *cadena, int terminado, List *head, MemList *M, MemList *S, MemList *MP);

void create(char *trozos[], int ntrozos);

void stats(char *trozos[], int ntrozos);

int list(char *trozos[], int ntrozos);

int delete(char *trozos[], int ntrozos);

int deltree(char *trozos[], int ntrozos);

int allocate(char *trozos[], MemList *M, MemList *S, MemList *MP);

int deallocate(char *trozos[], MemList *M, MemList *S, MemList *MP);

int i_o(char *trozos[]);

int memdump(char *trozos[], int ntrozos);

int memfill(char *trozos[], int ntrozos);

void memory(char *trozos[], MemList M, MemList S, MemList MP);

void recursiva(char trozos[1]);

#endif //CLION_COMANDOS_H
