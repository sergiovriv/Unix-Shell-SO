//
// Created by claudia on 20/09/22.
//

#ifndef CLION_LISTA_H
#define CLION_LISTA_H

#endif //CLION_LISTA_H

#include <stdio.h>

typedef struct Node *Pos;
typedef struct Node *List;

struct Node {
    char *data; // Elementos de la lista
    struct Node *next;  // Siguiente de la lista
};

/* Funciones */
void createlist (List *L);
int insertItem (char *data, List *head);
