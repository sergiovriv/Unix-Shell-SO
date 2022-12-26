#ifndef CLION_PROCLIST_H
#define CLION_PROCLIST_H

#include <stdbool.h>
#include <bits/types/time_t.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/resource.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>

/* INFORMACION DE LA LISTA
• PID
• Fecha de creacion
• STATUS (FINISHED, STOPPED, SIGNALED or ACTIVE)
• Comando
· Prioridad
 */

typedef struct PNode* PPos;
typedef struct Process {
    int pid; // PID
    char time[20];  // Fecha
    char status[20]; // Status
    int valor;
    char comando[40];  // Comando
    int prio;  // Prioridad

} Process;

struct PNode {
    Process data;
    PPos next;
};

typedef PPos ProcList;

/* Funciones */
void createProcList (ProcList *L);

bool createPNode(PPos *p);

PPos firstP(ProcList L);

bool insertar_proceso(int pid, char *cmd, int prio, ProcList *L);

void actualizar_proceso(PPos proceso);

char *status(int estado);

PPos findProc(int pid, ProcList L);

void printProcList(ProcList *L);

void deleteProcList(ProcList *L);

void deleteProc(ProcList *L, PPos p);

#endif //CLION_PROCLIST_H