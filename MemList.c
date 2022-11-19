#include "MemList.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool createMNode(MPos *p){
    *p = malloc(sizeof(struct MNode));

    return (*p != NULL);
}

/* Crear la lista */
void createMemList (MemList *L){
    MPos p;
    if(createMNode(&p)){
        *L = p;
        p->next = NULL;
    }
}

/*
/* Primero de la lista
MPos first(MemList L){
    return L->next;
}

/* Ultimo de la lista
MPos last(MemList L){
    MPos aux;

    for (aux = L; aux -> next != NULL; aux = aux -> next);
    return aux;
} */

/* Insertar en la lista de direcciones malloc */
bool InsertarNodoMalloc(MemList *L, struct MNode *block){
    MPos aux;

    if(*L == NULL)  // No se puede insertar
        return false;

    else {
        for (aux = *L; aux -> next != NULL; aux = aux -> next);  // Insertar al final de la lista
        aux -> next = block;
        block -> next = NULL;
    }
    return true;
}

/* Insertar en la lista de direcciones shared */
bool InsertarNodoShared(MemList *L, MPos *p, unsigned long size, key_t clave){
    MPos aux;

    if(*L == NULL)  // No se puede insertar
        return false;

    else {
        struct MNode *block;
        createMNode(&block);

        time_t t = time(NULL);
        char date[20];

        struct tm *fecha = localtime(&t);
        strftime(date, 100, "%d/%m/%Y %H:%M:%S\n", fecha);

        strcpy(block->data.time, date);
        block->data.size = size;
        block->data.dir = p;
        strcpy(block->data.type, "shared");
        block->data.key = clave;

        for (aux = *L; aux -> next != NULL; aux = aux -> next);  // Insertar al final de la lista
        aux -> next = block;
        block -> next = NULL;
    }
    return true;
}

bool InsertarNodoMmap(MemList *MP, MPos *p, size_t size, int df, char *fichero){ // Insertar en la lista
    MPos aux;

    if(*MP == NULL)  // No se puede insertar
        return false;

    else {
        struct MNode *block;
        createMNode(&block);

        time_t t = time(NULL);
        char date[20];

        struct tm *fecha = localtime(&t);
        strftime(date, 100, "%d/%m/%Y %H:%M:%S\n", fecha);

        strcpy(block->data.time, date);
        block->data.size = size;
        block->data.dir = p;
        strcpy(block->data.type, "mmap");
        block->data.df = df;
        strcpy(block->data.name, fichero);

        for (aux = *MP; aux -> next != NULL; aux = aux -> next);  // Insertar al final de la lista
        aux -> next = block;
        block -> next = NULL;
    }
    return true;
}

/* Elimina de la lista el elemento que ocupa la posición indicada */
void deleteAtPosition(MPos p, MemList *L){
    MPos aux;

    if (p->next == NULL){   // Borrar el ultimo elemento
        for (aux = *L; aux->next != p; aux = aux->next);
        aux->next = NULL;
    } else {     // Borrar por el medio
        aux = p->next;
        p->data = aux->data;
        p->next = aux->next;
        p = aux;
    }
    free(p);
}

/* Borrar un bloque de memoria a partir de su direccion */
int deleteAddr(char *dir, MemList M, MemList S, MemList MP){
    MPos aux;
    char *ptr;
    long addr = strtoul(dir,&ptr,16);

    // Recorrer la lista malloc
    for (aux = M; aux -> next != NULL && aux->data.dir != dir; aux = aux -> next);  // Recorrer la lista
    if(aux->data.dir == (long *) addr) {
        deleteAtPosition(aux, &M);
        return 0;
    }

     // Si no esta en la lista malloc, recorrer lista shared
     for (aux = S; aux -> next != NULL && aux->data.dir != dir; aux = aux -> next);  // Recorrer la lista
     if(aux->data.dir == (long *) addr) {
         deleteAtPosition(aux, &S);
         return 0;
     }

     // Si no esta en la lista shared, recorrer la lista mmap
     for (aux = MP; aux -> next != NULL && aux->data.dir != dir; aux = aux -> next);  // Recorrer la lista
     if(aux->data.dir == (long *) addr) {
         deleteAtPosition(aux, &MP);
         return 0;
     }
     return -1;
}

/* Borrar la lista */
void deleteMemList(MemList *L){
    MPos p;

    while(*L != NULL){  // Vamos borrando cada elemento uno a uno
        p = *L;
        *L = (*L)->next;  // Vamos desplazando p
        free(p);  // Liberamos memoria de p
    }
}

/* Imprimir la lista */
void printMemList(MemList L, int op){  // -malloc = 0, -shared/-createshared = 1, -mmap = 2, all= 3
    MPos aux;

    if(op == 0) {   // Lista malloc
        printf("----- Lista de bloques asignados malloc para el proceso %d -----\n", getpid());
        for(aux = L -> next; aux != NULL; aux = aux -> next)
            printf("\t %p \t %lu \t %s\n", aux->data.dir, aux->data.size, aux->data.time);
    }

    else if(op == 1) { // Lista shared
        printf("----- Lista de bloques asignados shared para el proceso %d -----\n", getpid());
        for(aux = L -> next; aux != NULL; aux = aux -> next)
            printf("\t %p \t %lu \t %s (key %d)\n", aux->data.dir, aux->data.size, aux->data.time, aux->data.key);
    }

    else if(op == 2) { // Lista mmap
        printf("----- Lista de bloques asignados mmap para el proceso %d -----\n", getpid());
        for(aux = L -> next; aux != NULL; aux = aux -> next)
            printf("\t %p \t %lu \t %s  %s (descriptor %d)\n", aux->data.dir, aux->data.size, aux->data.time, aux->data.name, aux->data.df);
    }

    else if(op ==3) {
        printf("----- Lista de bloques asignados para el proceso %d -----\n",getpid()); //hace falta para memory block y hay que hacerlo asi
                                                                                        //para q imprima todo por orden
        for(aux = L -> next; aux != NULL; aux = aux -> next)
            printf("\t %p \t %lu \t %s\n", aux->data.dir, aux->data.size, aux->data.time);

        for(aux = L -> next; aux != NULL; aux = aux -> next)
            printf("\t %p \t %lu \t %s (key %d)\n", aux->data.dir, aux->data.size, aux->data.time, aux->data.key);

        for(aux = L -> next; aux != NULL; aux = aux -> next)
            printf("\t %p \t %lu \t %s  %s (descriptor %d)\n", aux->data.dir, aux->data.size, aux->data.time, aux->data.name, aux->data.df);

    }
}

/* Buscar un bloque de memoria a partir de su clave */
MPos findKeyBlock(int clave, MemList L){
    MPos aux;

    for (aux = L; aux -> next != NULL && aux->data.key != clave; aux = aux -> next);  // Recorrer la lista
        if(aux->data.key == clave)
            return aux;
        else
            return NULL;
}

/* Buscar un bloque de memoria malloc por su tamaño */
MPos findBlock(int tam, MemList L){
    MPos aux;

    for (aux = L->next; aux -> next != NULL && aux->data.size != tam && strcmp(aux->data.type, "malloc") == 0; aux = aux -> next);  // Recorrer la lista
    if(aux->data.size == tam)
        return aux;
    else
        return NULL;
}

/* Buscar un bloque de memoria mmap a partir de su nombre */
MPos findMmapBlock(char *name, MemList L){
    MPos aux;

    for (aux = L; aux -> next != NULL && strcmp(aux->data.name, name) != 0; aux = aux -> next);  // Recorrer la lista
    if(strcmp(aux->data.name, name) == 0)
        return aux;
    else
        return NULL;
}

