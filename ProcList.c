#include "ProcList.h"
#include "aux.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool createPNode(PPos *p){
    *p = malloc(sizeof(struct PNode));

    return (*p != NULL);
}

/* Crear la lista */
void createProcList (ProcList *L){
    PPos p;
    if(createPNode(&p)){
        *L = p;
        p->next = NULL;
    }
}

PPos firstP(ProcList L) {
    return L->next;
}

char *status(int estado){
    if (WIFEXITED(estado))
        return "TERMINADO";

    else if (WIFCONTINUED(estado))
        return "ACTIVO";

    else if (WIFSIGNALED(estado))
        return "SIGNALED";
}

/* Insertar en la lista */
bool insertar_proceso(int pid, char *cmd, int prio, ProcList *L){
    PPos aux, p;

    if(*L == NULL)  // No se puede insertar
        return false;

    if(!createPNode(&p))
        return -1;

    else {
        time_t t = time(NULL);
        char date[20];

        struct tm *fecha = localtime(&t);
        strftime(date, 100, "%d/%m/%Y %H:%M:%S\n", fecha);

        p->data.pid = pid;
        strcpy(p->data.time, date);
        strcpy(p->data.status, "ACTIVO");
        p->data.valor = 000;
        strcpy(p->data.comando, cmd);
        p->data.prio = prio;

        for (aux = *L; aux -> next != NULL; aux = aux -> next);  // Insertar al final de la lista
        aux -> next = p;
        p->next = NULL;
    }
    return true;
}

/* Actualizar info de un proceso */
void actualizar_proceso(PPos proceso){
    int estado;

    waitpid(proceso->data.pid, &estado, WNOHANG | WUNTRACED | WCONTINUED);
    strcpy(proceso->data.status, status(estado));

    if(strcmp(proceso->data.status, "SIGNALED") == 0)
        ValorSenal(proceso->data.status);

    if(strcmp(proceso->data.status, "TERMINADO") == 0)
        proceso->data.prio = -1;
}

/* Imprimir la lista */
void printProcList(ProcList *L){
    PPos aux;

    if(L != NULL) {
        for(aux = firstP(*L); aux != NULL; aux = aux->next) {
            printf(" %d  p=%d %s %s (%d) %s\n", aux->data.pid, aux->data.prio, aux->data.time,
                   aux->data.status, aux->data.valor, aux->data.comando);
            actualizar_proceso(aux);
        }
    }
}
/* Buscar un proceso por su PID */
PPos findProc(int pid, ProcList L){
    PPos aux;

    for (aux = L->next; aux -> next != NULL && aux->data.pid != pid; aux = aux -> next);  // Recorrer la lista
    if(aux->data.pid == pid)
        return aux;
    else
        return NULL;
}

/* Borrar la lista */
void deleteProcList(ProcList *L){
    PPos p;

    while(*L != NULL){  // Vamos borrando cada elemento uno a uno
        p = *L;
        *L = (*L)->next;  // Vamos desplazando p
        free(p);  // Liberamos memoria de p
    }
}

/* Elimina de la lista el elemento que ocupa la posición indicada */
void deleteProc(ProcList *L, PPos p) {  // op = 1 terminados, op = 0 signal
    PPos aux;

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

