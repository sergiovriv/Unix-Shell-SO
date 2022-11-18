#ifndef CLION_MEMLIST_H
#define CLION_MEMLIST_H

#include <stdbool.h>
#include <bits/types/time_t.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>

/* INFORMACION DE LA LISTA
• Its memory address
• Its size
• Time of allocation
• Type of allocation (malloc memory, shared memory, mapped file)
• Other info: key for shared memory blocks, name of file and file descriptor for mapped files
 */

typedef struct MNode* MPos;
typedef struct Block {
    void *dir; // Direccion de memoria
    size_t size;  // Tamaño del bloque de memoria
    char time[20];  // Time of allocation
    char type[20];  // Type of allocation
    int key;  // Key (shared)
    char name[50];  // Nombre del fichero (mmap)
    int df;  // File descrptor (mmap)

} Block;

struct MNode {
    Block data;
    MPos next;
};

typedef MPos MemList;

/* Funciones */
void createMemList (MemList *L);

/*
MPos first(MemList head);
MPos last(MemList head); */

bool createMNode(MPos *p);

bool InsertarNodoMalloc(MemList *L, struct MNode *block);

bool InsertarNodoShared(MemList *L, MPos *p, size_t size, key_t clave);

bool InsertarNodoMmap(MemList *MP, MPos *p, size_t size, int df, char *fichero);

void deleteAtPosition(MPos p, MemList *L);

int deleteAddr(char *dir, MemList M, MemList S, MemList MP);

void deleteMemList(MemList *L);

void printMemList(MemList L, int op);

MPos findKeyBlock(int clave, MemList L);
MPos findBlock(int tam, MemList L);
MPos findMmapBlock(char *name, MemList L);

#endif //CLION_MEMLIST_H