//
// Created by claud on 22/09/2022.
//

#ifndef SO_LISTA_H
#define SO_LISTA_H

//
// Created by claudia on 20/09/22.
//

#ifndef CLION_LISTA_H
#define CLION_LISTA_H

#endif //CLION_LISTA_H

#include <stdio.h>
#include <stdbool.h>

typedef struct Node* Pos;
typedef struct Item {
       char comando[20];
       int n;
} Item;

struct Node {
    Item data;
    Pos next;
};

typedef Pos List;

/* Funciones */
void createlist (List *head);

Pos first(List head);

bool insertItem (char *com, List *head);

char *find_n (int n, List *head);

void deleteList(List *head);

int getItem(int N, List head);

#endif //SO_LISTA_H