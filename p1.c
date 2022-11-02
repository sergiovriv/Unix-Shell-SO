/* Claudia Maciel Montero */
/* c.maciel  */
/* Sergio Vila Riveira */
/* sergio.vila1 */

#include <stdio.h>
#include <string.h>
#include "comandos.h"

#define MAX_TROZOS 10
#define MAX_COM 100

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

void procesarEntrada(char *trozos[], int ntrozos, List *head){
    if(strcmp(trozos[0], "autores") == 0)  // Autores
        autores(trozos[1], ntrozos);

    else if(strcmp(trozos[0], "pid") == 0) //Pid
           pid(trozos[1], ntrozos);

    else if(strcmp(trozos[0], "fecha") == 0)  // Fecha
        fecha(trozos[1], ntrozos);

    else if(strcmp(trozos[0], "infosis") == 0)  // Infosis
            infosis(trozos[1]);

    else if(strcmp(trozos[0], "hist") == 0)  // Hist
        hist(trozos[1], ntrozos, head);

    else if(strcmp(trozos[0], "carpeta") == 0)  // Carpeta
        carpeta(trozos, ntrozos);

    else if(strcmp(trozos[0], "comando") == 0)   // ComandoN
        comandoN(trozos[1], ntrozos, head);

    else if(strcmp(trozos[0], "salir") == 0) // Salir (salir)
        salir(trozos[0]);

    else if(strcmp(trozos[0], "bye") == 0) // Salir (bye)
        salir(trozos[0]);

    else if(strcmp(trozos[0], "fin") == 0) // Salir (fin)
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

    else
        printf(" No se ha encontrado el comando\n");
}

int leerEntrada(char *cadena, int terminado, List *head){
    char *trozos[MAX_TROZOS];
    int ntrozos;

    ntrozos = TrocearCadena(cadena, trozos); // Numero de trozos

    if(ntrozos != 0) {
        terminado = -1;

        procesarEntrada(trozos, ntrozos, head);
    }
    else // Si no se escribio nada salir
        terminado = 0;

    return terminado;
}

int main(){
    char comando[MAX_COM];
    int terminado = -1;

    List head;
    createlist(&head);  // Crear la lista nodo cabeza

    while (terminado != 0){
        imprimirPrompt();

        fgets(comando, MAX_COM, stdin);
        if (insertItem(comando, &head))  // Añadir el comando a la lista
        terminado = leerEntrada(comando, terminado, &head);

        else {
            printf(" * Error: lista vacia\n");  // No se pudo insertar (se borro la lista...)
            createlist(&head);  // Crear la lista
        }
    }

    return 0;
}