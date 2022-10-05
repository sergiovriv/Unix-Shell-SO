//
// Created by claudia on 20/09/22.
//

#ifndef CLION_COMANDOS_H
#define CLION_COMANDOS_H

#include "lista.h"
#define MAX 50

int autores(char trozos[1], int ntrozos);

int fecha(char trozos[1], int ntrozos);

int pid(char trozos[1], int ntrozos);

int infosis(char trozos[1]);

int hist(char trozos[1], int ntrozos, List *head);

int carpeta(char trozos[1], int ntrozos);

int ayuda(char trozos[1], int ntrozos);

void salir(char trozos[0]);

int comandoN(char trozos[1], int ntrozos, List *head);
int leerEntrada(char *cadena, int terminado, List *head);

int create(char *trozos[], int ntrozos);

int stats(char *trozos[], int ntrozos);


#endif //CLION_COMANDOS_H