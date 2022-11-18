#ifndef CLION_AUX_H
#define CLION_AUX_H

#include "comandos.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
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
#include <sys/mman.h>
#include <sys/shm.h>

#define TAMANO 2048
#define MAX 100

char LetraTF (mode_t m);

/* Funcion de permisos */
char * ConvierteModo2 (mode_t m);

/* Funcion para mostrar info de archivos */
bool list_file(char *file, const int op[]);

/* Funcion para mostrar info de directorios */
bool list_dir(char *name, int op[]);

/* Funcion auxiliar para list [-reca] */
int list_dirA(char *name, int op[]);

/* Funcion auxiliar para list [-recb] */
bool list_dirB(char *name, int op[]);

/* Funcion auxiliar para deltree */
int pimplarDir(char *name);

void *ObtenerMemoriaShmget (key_t clave, size_t tam, MemList *L);

/* Funciones para allocate */
void do_AllocateCreateshared (char *tr[], MemList L);
void do_AllocateMmap(char *arg[], MemList *MP);
void *MapearFichero (char * fichero, int protection, MemList *MP);

/* Funciones para deallocate */
void do_DeallocateDelkey (char *args[]);

/* Funciones i-o */
ssize_t LeerFichero (char *f, void *p, size_t cont);
void do_I_O_read (char *ar[]);
ssize_t EscribirFichero (char *f, void *p, size_t cont,int overwrite);

void Recursiva (int n);

void Do_pmap (void);
#endif //CLION_AUX_H