#ifndef SO_LISTA_H
#define SO_LISTA_H

#include <stdio.h>
#include <stdbool.h>

typedef struct Node* Pos;
typedef struct Item {
    char comando[20];  // Nombre del comando
    int n;  // Numero del comando (para funciones hist, comandoN...)
} Item;

struct Node {
    Item data;
    Pos next;
};

typedef Pos List;

/* Funciones */
void createlist (List *head);

Pos first(List head);
Pos last(List head);

bool insertItem (char *com, List *head);

char *find_n (int n, List *head);

void deleteList(List *head);

#endif //SO_LISTA_H
