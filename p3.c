/* Claudia Maciel Montero */
/* c.maciel  */
/* Sergio Vila Riveira */
/* sergio.vila1 */

#include <stdio.h>
#include <string.h>
#include "comandos.h"

#define MAX_TROZOS 1024
#define MAX_COM 1024

int TrocearCadena(char *cadena, char *trozos[]){
    int i = 1;

    if((trozos[0] = strtok(cadena, " \n\t")) == NULL)
        return 0;

    while((trozos[i] = strtok(NULL, " \n\t")) != NULL)
        i++;
    return i;
}

void imprimirPrompt(){
    printf("$ ");
}

void procesarEntrada(char *trozos[], int ntrozos, int argc, char* argv[], char* envp[],
                     List *head, MemList *M, MemList *S, MemList *MP, ProcList *L){
    int i;
    char *ejecutable[50] = {};

    if(strcmp(trozos[0], "autores") == 0)  // Autores
        autores(trozos[1], ntrozos);

    else if(strcmp(trozos[0], "pid") == 0) //Pid
           pid(trozos[1], ntrozos);

    else if(strcmp(trozos[0], "fecha") == 0)  // Fecha
        fecha(trozos[1], ntrozos);

    else if(strcmp(trozos[0], "infosis") == 0)  // Infosis
            infosis();

    else if(strcmp(trozos[0], "hist") == 0)  // Hist
        hist(trozos[1], ntrozos, head);

    else if(strcmp(trozos[0], "carpeta") == 0)  // Carpeta
        carpeta(trozos, ntrozos);

    else if(strcmp(trozos[0], "comando") == 0)   // ComandoN
        comandoN(trozos[1], ntrozos, argc, argv, envp, head, M, S, MP, L);

    else if(strcmp(trozos[0], "salir") == 0 || strcmp(trozos[0], "bye") == 0 || strcmp(trozos[0], "fin") == 0) // Salir (salir, bye, fin)
        salir(trozos[0]);

    else if(strcmp(trozos[0], "ayuda") == 0) // Ayuda
        ayuda(trozos[1], ntrozos);

    else if(strcmp(trozos[0], "create") == 0) // Create
        create(trozos, ntrozos);

    else if(strcmp(trozos[0], "stat") == 0) // Stat
        stats(trozos, ntrozos);

    else if(strcmp(trozos[0], "list") == 0) // List
        list(trozos, ntrozos);

    else if(strcmp(trozos[0], "delete") == 0) // Delete
        delete(trozos, ntrozos);

    else if(strcmp(trozos[0], "deltree") == 0) // DelTree
        deltree(trozos, ntrozos);

    else if(strcmp(trozos[0], "allocate") == 0)  // Allocate
        allocate(trozos, M, S, MP);

    else if(strcmp(trozos[0], "deallocate") == 0)  // Deallocate
        deallocate(trozos, M, S, MP);

    else if(strcmp(trozos[0], "i-o") == 0)  // i-o
        i_o(trozos);

    else if(strcmp(trozos[0], "memdump") == 0)  // Memdump
        memdump(trozos, ntrozos);

    else if(strcmp(trozos[0], "memfill") == 0)  // Memfill
        memfill(trozos, ntrozos);

    else if(strcmp(trozos[0], "memory") == 0)  // Memory
        memory(trozos, *M, *S, *MP);

    else if(strcmp(trozos[0], "recursiva") == 0)  // Recursiva
        recursiva(trozos[1]);

    else if(strcmp(trozos[0], "priority") == 0)  // Priority
        priority(trozos, ntrozos);

    else if(strcmp(trozos[0], "showvar") == 0)  // Showvar
        showvar(trozos, envp);

    else if(strcmp(trozos[0], "changevar") == 0)  // Changevar
        changevar(trozos, ntrozos, envp);

    else if(strcmp(trozos[0], "showenv") == 0)  // Showenv
        showenv(trozos, envp);

    else if(strcmp(trozos[0], "fork") == 0)  // Fork
        forkin(L);

    else if(strcmp(trozos[0], "listjobs") == 0)  // Listjobs
        listjobs(L);

    else if(strcmp(trozos[0], "deljobs") == 0)  // Deljobs
        deljobs(trozos, L);

    else if(strcmp(trozos[0], "job") == 0)  // Job
        job(trozos, *L);

    else if(strcmp(trozos[0], "execute") == 0)  // Execute
        execute(trozos, argv, envp);

    else {
        for(i = 0; trozos[i] != NULL; i++) {
            if(strcmp(trozos[i], "&") != 0)
                ejecutable[i] = trozos[i];
        }
        if(strcmp(trozos[i-1], "&") == 0) {
            if (segundo_plano(argv, envp, ejecutable, L) == -1)
                printf(" No se ha encontrado el comando\n");
        }

        else if(primer_plano(argv, envp, trozos) == -1)
            printf(" No se ha encontrado el comando\n");
    }
}

int leerEntrada(char *cadena, int terminado, int argc, char* argv[], char* envp[],
                List *head, MemList *M, MemList *S, MemList *MP, ProcList *L){
    char *trozos[MAX_TROZOS];
    int ntrozos;

    ntrozos = TrocearCadena(cadena, trozos); // Numero de trozos

    if(ntrozos != 0) {
        terminado = -1;

        procesarEntrada(trozos, ntrozos, argc, argv, envp, head, M, S, MP, L);
    }
    else // Si no se escribio nada salir
        terminado = 0;

    return terminado;
}

int main(int argc, char *argv[], char *envp[]){
    char comando[MAX_COM];
    int terminado = -1;

    List head;
    createlist(&head);

    MemList mallocList;
    MemList sharedList;
    MemList mapList;

    ProcList procList;
    createProcList(&procList); // Crear la lista de procesos

    while (terminado != 0){
        imprimirPrompt();

        fgets(comando, MAX_COM, stdin);
        if (insertItem(comando, &head))  // Añadir el comando a la lista
        terminado = leerEntrada(comando, terminado, argc, argv, envp,
                                &head, &mallocList, &sharedList, &mapList, &procList);

        else {
            printf(" * Error: lista vacia\n");  // No se pudo insertar (se borro la lista...)
            createlist(&head);  // Crear la lista
        }
    }
    deleteList(&head);
    if(mallocList != NULL)
        deleteMemList(&mallocList);

    if(sharedList != NULL)
         deleteMemList(&sharedList);

    if(mapList != NULL)
        deleteMemList(&mapList);

    if(procList != NULL)
        deleteProcList(&procList);

    return 0;
}
