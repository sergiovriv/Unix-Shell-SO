#include "lista.h"
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

/* Primero de la lista */
Pos first(List head){
    return head->next;
}

/* Ultimo de la lista */
Pos last(List head){
    Pos aux;
    for (aux = head; aux -> next != NULL; aux = aux -> next);
    return aux;
}

/* Insertar en la lista */
bool insertItem (char *com, List *head){
    Pos q, aux;
    int i = 1;

    if(*head == NULL)  // No se puede insertar
        return false;

    if(!createNode(&q))
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

    for(p = *head; p->data.n != n; p = p -> next);
    return (p -> data.comando);
}

/* Borrar la lista */
void deleteList(List *head){
    Pos p;

    while(*head != NULL){  // Vamos borrando cada elemento uno a uno
        p = *head;
        *head = (*head)->next;  // Vamos desplazando p
        free(p);  // Liberamos memoria de p
    }
}