#include <stdio.h>
#include <string.h>
#include "comandos.h"
#include "lista.h"
#define MAX_TROZOS 50

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

int leerEntrada(char *cadena, int terminado){
    fgets(cadena, MAX_TROZOS, stdin);

    char *trozos[MAX_TROZOS];
    int ntrozos;
    ntrozos = TrocearCadena(cadena, trozos);

    if(ntrozos == 0)
        terminado = 0;

    return terminado;
}

void procesarEntrada(char *trozos[]){
    if(strcmp(trozos[0], "autores") == 0)  // Autores
        autores(&trozos[MAX_TROZOS]);

    else if(strcmp(trozos[0], "pid") == 0) //Pid
        pid(&trozos[MAX_TROZOS]);

    else if(strcmp(trozos[0], "carpeta") == 0) // Carpeta
        carpeta(&trozos[MAX_TROZOS]);

    else if(strcmp(trozos[0], "fecha") == 0)  // Fecha
        fecha(&trozos[MAX_TROZOS]);

    else if(strcmp(trozos[0], "infosis") == 0)  // Infosis
        infosis(&trozos[MAX_TROZOS]);

    else if(strcmp(trozos[0], "carpeta") == 0)  // Carpeta
        carpeta(&trozos[MAX_TROZOS]);

    else if(strcmp(trozos[0], "ayuda") == 0)  // Ayuda
        ayuda(&trozos[MAX_TROZOS]);

    else if(strcmp(trozos[0], "comandoN") == 0)  // ComandoN
        comandoN(&trozos[MAX_TROZOS]);

    else if(strcmp(trozos[0], "salir") == 0) // Ayuda
        ayuda(&trozos[MAX_TROZOS]);;
}

int main(){
    char *comando;
    int terminado;

    while (!terminado){
        imprimirPrompt();
        terminado = leerEntrada(comando, terminado);

        char *trozos[MAX_TROZOS];
        TrocearCadena(comando, trozos);
        procesarEntrada(trozos);
    }

    return 0;
}
