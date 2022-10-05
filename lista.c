//
// Created by claud on 22/09/2022.
//

#include "lista.h"
//
// Created by claudia on 20/09/22.
//

#include "lista.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool createNode(Pos *p){
    *p = malloc(sizeof(struct Node));

    return (*p != NULL);
}

/* Crear la lista */
void createlist (List *head){
    Pos p;
    if(createNode(&p)){
        *head = p;
        p->next = NULL;
    }
}

Pos first(List head){
    return head->next;
}

Pos last(List head){
    Pos aux;
    for (aux = head; aux -> next != NULL; aux = aux -> next);
    return aux;
}

/* Insertar en la lista */
bool insertItem (char *com, List *head){
    Pos q, aux;
    int i = 0;

    if(!createNode(&q))
        return false;

    if(*head == NULL)  // No se puede insertar
        return false;

    else {
        strcpy(q->data.comando, com);
        q->next = NULL;

        for (aux = *head; aux -> next != NULL; aux = aux -> next, i++);  // Insertar al final de la lista
        aux -> next = q;
        q -> data.n = i;
    }
    return true;
}

/* Buscar el elemento numero n */
char *find_n(int n, List *head){
    Pos p;
    int aux = 0;

    for(p = *head; p->data.n != n; p = p -> next);
    return (p -> data.comando);
}

/* Vaciar la lista */
void deleteList(List *head){
    Pos p;

    while(*head != NULL){  // Vamos borrando cada elemento uno a uno
        p = *head;
        *head = (*head)->next;  // Vamos desplazando p
        free(p);  // Liberamos memoria de p
    }
}

