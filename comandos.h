/* Claudia Maciel Montero */
/* c.maciel  */
/* Sergio Vila Riveira */
/* sergio.vila1 */

#ifndef CLION_COMANDOS_H
#define CLION_COMANDOS_H

#include "lista.h"
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
#define BUF 1024

void autores(char trozos[1], int ntrozos);

void fecha(char trozos[1], int ntrozos);

void pid(char trozos[1], int ntrozos);

void infosis(char trozos[1]);

void hist(char trozos[1], int ntrozos, List *head);

void carpeta(char *trozos[], int ntrozos);

void ayuda(char trozos[1], int ntrozos);

void salir(char trozos[0]);

void comandoN(char trozos[1], int ntrozos, List *head);
int leerEntrada(char *cadena, int terminado, List *head);

void create(char *trozos[], int ntrozos);

void stats(char *trozos[], int ntrozos);

int list(char *trozos[], int ntrozos);
bool list_dir(char *name, int op[]);

int delete(char *trozos[], int ntrozos);

int deltree(char *trozos[], int ntrozos);

#endif //CLION_COMANDOS_H