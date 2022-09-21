//
// Created by claudia on 20/09/22.
//

#include "lista.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Crear la lista */
void createlist (List *head){
    *head = NULL;
}

bool createNode(Pos *p){
    *p = malloc(sizeof(struct Node));

    return (p != NULL);
}

/* Insertar en la lista */
int insertItem (char *data, List *head){
    Pos q;

    if(!createNode(q))
        return 0;

    else{
        q = *head;
        *head = q -> next;

        q -> data = data;
        q -> next = *head;
        *head = q;
    }
    return 0;
}

/* Buscar el elemento numero n */
Pos find_n(int n, List *head){
    Pos p;
    int aux = 0;

    while(p != NULL){
        for(p = *head; p != NULL; p = p->next, aux++){
            if(aux == n)
                return p;
        }
    }
    return 0;
}

/* Vaciar la lista */
void deleteList(List *head){
    Pos aux;

    for(aux = *head; aux->next != NULL; aux = aux->next)
        aux -> data = NULL;
}
