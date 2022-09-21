//
// Created by claudia on 20/09/22.
//

#include "comandos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include "lista.h"

/* struct cmd cmd[]{
        {"autores", autores},
        {"pid", pid},
        {"carpeta", carpeta},
        {"fecha", fecha},
        {"hist", hist},
        {"comandoN", comandoN},
        {"infosis", infosis},
        {"ayuda", ayuda},
        {"salir", salir}
}; */

/* Mostrar autores */
void autores(char *trozos[]){
    if(strcmp(trozos[1], "-n") == 0)  // (-n) Imprimir nombres
        printf("Claudia, Sergio");

    else if(strcmp(trozos[1],"-l") == 0)  // (-l) Imprimir logins
        printf("c.maciel, sergio.vila1");

    else  // Imprimir las 2 cosas
        printf("Claudia, Sergio / c.maciel, sergio.vila1");
}

/*imprimir PID*/
void pid(char *trozos[]){
    int pid, parent;
    if(strcmp(trozos[1], "-p") ==0) { // (-p) Imprimir proceso padre de la shell
        parent= getppid();
        printf("el pid padre de la shell es: %d/n", parent);

    }else{ //Imprimir proceso actual de la shell
        pid= getpid();
        printf("El pid del proceso actual es: %d/n", pid);
    }
}

/* Mostrar fecha y hora de hoy */
 void fecha(char *trozos[]){
    time_t t= time(NULL);
    struct tm *fecha = localtime(&t);
    char datepr[100];
    
    
    if(strcmp(trozos[1], "-d") == 0) { // (-d) Imprimir ano/mes/dia
        strftime(datepr, 100, "%d/%m/%Y", fecha);
        printf("Current date: %s ", datepr);
    }

    else if(strcmp(trozos[1], "-h") == 0) { // (-h) Imprimir hora/min/seg
        strftime(datepr, 100, "%H:%M:%S", fecha);
        printf("Current time: %s", datepr);
    }

    else {  // Imprimir las dos cosas
        strftime(datepr, 100, "%d/%m/%Y %H:%M:%S", fecha);
        printf("Current date & time: %s ", datepr);
    }

} 

/* Mostrar informacion de la maquina */
void infosis(char *tokens[]){
    struct utsname unameData;
    uname(&unameData);
    
    if(uname(&unameData) < 0) { //control de errores
        printf("Command infosis failed");
    }
    printf("%s %s %s %s %s/n", unameData.nodename, unameData.machine, unameData.sysname,
           unameData.release, unameData.version); //imprimimos datos sistema
}

int carpeta(char *trozos[]){
    if(strcmp(trozos[1], "-direct") == 0)  // (-direct) - cambiar de directorio a direct
        chdir(trozos[1]);

    else {  // Mostrar directorio actual
        char cwd[MAX];

        getcwd(cwd, MAX);
        printf("Directorio actual: %s\n", cwd);

        return 0;
    }
}

/* Ayuda */
void ayuda(char *trozos[]){
    printf("autores[-l|-n] / pid[-p] / carpeta[direct] / fecha[-d|-h] / hist[-c|-N]");
    printf("comando N / infosis / ayuda[cmd] / fin / salir / bye");
}

/* Salir del shell */
void salir(char *trozos[]){
    if(strcmp(trozos[0], "salir") == 0)
        exit(0);

    else if(strcmp(trozos[0], "fin") == 0)
        exit(0);

    else if(strcmp(trozos[0], "bye") == 0)
        exit(0);
}

/* Repetir el comando numero N */
void comandoN(char *trozos[]){
    //find(N);
}

