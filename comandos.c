#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comandos.h"
#include "aux.h"

extern char **environ;

/* Variables globales para memory */
int xg = 0, yg = 0, zg = 0;

/* Mostrar autores */
void autores(char trozos[1], int ntrozos){
    if(ntrozos > 1) {
        if (strcmp(trozos, "-n") == 0) // (-n) Imprimir nombres
            printf("Claudia, Sergio\n");

        else if (strcmp(trozos, "-l") == 0)  // (-l) Imprimir logins
            printf("c.maciel, sergio.vila1\n");
    }
    else
        // Imprimir las 2 cosas
        printf("Claudia, Sergio / c.maciel, sergio.vila1\n");
}

/* Imprimir PID */
void pid(char trozos[1], int ntrozos) {
    int pid, parent;

    if (ntrozos > 1) {
        if (strcmp(trozos, "-p") == 0) { // (-p) Imprimir proceso padre de la shell
            parent = getppid();
            printf("El pid padre de la shell es: %d\n", parent);
        }
    } else {    //Imprimir proceso actual de la shell
            pid = getpid();
            printf("El pid del proceso actual es: %d\n", pid);
        }
}

/* Mostrar fecha y hora actuales */
void fecha(char trozos[1], int ntrozos) {
    time_t t = time(NULL);
    struct tm *fecha = localtime(&t);
    char datepr[100];

    if(ntrozos > 1) {
        if (strcmp(trozos, "-d") == 0) { // (-d) Imprimir ano/mes/dia
            strftime(datepr, 100, "%d/%m/%Y\n", fecha);
            printf("Current date: %s", datepr);

        } else if (strcmp(trozos, "-h") == 0) { // (-h) Imprimir hora/min/seg
            strftime(datepr, 100, "%H:%M:%S\n", fecha);
            printf("Current time: %s", datepr);
        }
    } else {
        // Imprimir las dos cosas
        strftime(datepr, 100, "%d/%m/%Y %H:%M:%S\n", fecha);
        printf("Current date & time: %s", datepr);
    }
}

/* Mostrar informacion de la maquina */
void infosis(){
    struct utsname unameData;
    uname(&unameData);

    if(uname(&unameData) < 0)  // Control de errores
        printf("Command infosis failed\n");

    printf("%s %s %s %s %s\n", unameData.nodename, unameData.machine, unameData.sysname,
           unameData.release, unameData.version); // Imprimir datos del sistema
}

/* Cambiar de directorio / Mostrar directorio actual */
void carpeta(char *trozos[], int ntrozos){
    if(ntrozos > 1) { // (-direct) cambiar de directorio a direct
        strcat(trozos[1], "/");
        chdir(trozos[1]);
    }
    else {  // Mostrar directorio actual
        char cwd[MAX];

        getcwd(cwd, MAX);
        printf("Directorio actual: %s\n", cwd);
    }
}

/* Mostrar historial */
void hist(char trozos[1], int ntrozos, List *head) {
    Pos p;
    int i = 0;

    if (ntrozos > 1) {
        if (strcmp(trozos, "-c") == 0)  // (-c) Borrar historial
            deleteList(head);  // Borramos la lista

        else {  // (-N) Imprimir el historial desde el principio hasta N
            char *aux[3];
            aux[0] = strtok(trozos, "-");

            int n = atoi(aux[0]);  // Convertir a int

            for (p = first(*head); (p->next != NULL) && (i <= n); p = p->next, i++)
                printf("%d) %s\n", i, p->data.comando);
        }

    } else {  // Imprimir historial
        for (p = first(*head); p != NULL; p = p->next, i++)
            printf("%d) %s\n", i, p->data.comando);
    }
}

/* Ayuda */
void ayuda(char trozos[1], int ntrozos) {
    if (ntrozos > 1) {
        // ayuda [cmd]
        if (strcmp(trozos, "autores") == 0)  // Autores
            printf(" Imprime nombres y login de los autores\n * [-l] Imprime solo logins\n * [-n] Imprime solo los nombres\n");

        else if (strcmp(trozos, "pid") == 0)  //Pid
            printf(" Muestra el pid del shell \n * [-p] Muestra el pid del proceso padre\n");

        else if (strcmp(trozos, "fecha") == 0) {  // Fecha
            printf(" Imprime la fecha y hora actuales\n * [-d] Imprime la fecha actual en el formato: DD/MM/YYYY\n");
            printf(" * [-h] Imprime la hora actual en el formato: hh:mm:ss\n");

        } else if (strcmp(trozos, "hist") == 0) {  // hist
            printf(" Muestra / Borra el historial de comandos\n * hist Muestra el historial de comandos");
            printf(" * [-c] Borra el historial de comandos\n * [-N] Imprime los primeros N comandos\n");

        } else if (strcmp(trozos, "infosis") == 0)   // Infosis
            printf(" Muestra informacion de la maquina ejecuntando esta shell\n");

        else if (strcmp(trozos, "carpeta") == 0)   // Carpeta
            printf(" Muestra el directorio actual \n * carpeta (direct) Cambia el directorio a direct\n");

        else if (strcmp(trozos, "ayuda") == 0)  // Ayuda
            printf(" Muestra la lista de los comandos disponibles\n * [cmd] Muestra la ayuda del comando cmd\n");

        else if (strcmp(trozos, "comandoN") == 0) // ComandoN
            printf(" Repite el comando numero N\n");

        else if (strcmp(trozos, "salir") == 0 || strcmp(trozos, "bye") == 0 || strcmp(trozos, "fin") == 0)  // Salir
            printf(" Termina la ejecucion del shell\n");

        else if (strcmp(trozos, "create") == 0)  // Create
            printf(" Crea un archivo o directorio\n * create -f [name] Crea un fichero\n * create [name] Crea un directorio\n");

        else if (strcmp(trozos, "stat") == 0) { // Stat
            printf(" stat [-long][-acc][-link] name1 name2... Muestra informacion de arhivos y directorios\n");
            printf(" * stat [-long] Muestra mas informacion\n * stat [-acc] Muestra ultimo acceso\n");
            printf(" * stat [-link] Si tiene links simbolicos\n");

        } else if (strcmp(trozos, "delete") == 0)  // Delete
            printf(" delete name1 name2... Borra archivos y/o directorios vacios\n");

        else if (strcmp(trozos, "list") == 0) { // List
            printf(" list [-reca][-recb][-hid][-long][-link][-acc] n1 n2 ... Muestra archivos y directorios\n");
            printf(" * [-hid] Muestra directorios ocultos\n * [-reca] Muestra de forma recursiva (antes)\n * [-recb] Muestra de forma recursiva (despues)\n");
            printf(" * [-long][-link][-acc] Igual que stat. Ver 'ayuda stat' para mas info\n");

        } else if (strcmp(trozos, "deltree") == 0)  // DeleteTree
            printf(" delete name1 name2... Borra archivos y/o directorios no vacios de forma recursiva\n");

        else if (strcmp(trozos, "allocate") == 0) {  // Allocate
            printf(" allocate [-malloc|-createshared|-shared|-mmap] Asigna un bloque de memoria\n");
            printf(" * [-malloc] tam: asigna un bloque malloc de tamano tam \n\tallocate -malloc muestra la lista de bloques malloc asignados\n");
            printf(" * [-createshared] cl tam: asigna (creando) un bloque de memoria compartida de clave cl y tamano tam \n\tallocate -createshared muestra la lista de bloques shared asignados\n");
            printf(" * [-shared] cl: asigna el bloque de memoria compartida (ya existente) de clave cl \n\tallocate -shared muestra la lista de bloques shared asignados\n");
            printf(" * [-mmap] fich perm: mapea el fichero fich, perm son los permisos \n\tallocate -mmap muestra la lista de bloques mmap asignados\n");

        } else if (strcmp(trozos, "deallocate") == 0) {  // Deallocate
            printf(" deallocate [-malloc|-shared|-delkey|-mmap|addr] Desasigna un bloque de memoria\n");
            printf(" * [-malloc] tam: desasigna un bloque malloc de tamano tam \n\tdeallocate -malloc muestra la lista de bloques malloc asignados\n");
            printf(" * [-shared] cl: desasigna (desmapea) el bloque de memoria compartida de clave cl \n\tdeallocate -shared muestra la lista de bloques shared asignados\n");
            printf(" * [-delkey] cl: elimina del sistema (sin desmapear) la clave de memoria cl\n");
            printf(" * [-mmap] fich perm: mdesapea el fichero fich \n\tdeallocate -mmap muestra la lista de bloques mmap asignados\n");
            printf(" * addr: desasigna el bloque de memoria en la direccion addr\n");

        } else if (strcmp(trozos, "recursiva") == 0)  // Recursiva
            printf(" recursiva [n] Ejecuta la funcion recursiva n veces\n");

        else if (strcmp(trozos, "i-o") == 0) {  // i-o
            printf("i-o [read|write] [-o] fich addr cont\n");
            printf(" * [read] fich addr cont: lee cont bytes desde fich a addr\n");
            printf(" * [write] [-o] fich addr cont: escribe cont bytes desde addr a fich [-o] para sobreescribir\n");

        } else if (strcmp(trozos, "memdump") == 0)  // memdump
            printf("memdump addr cont Vuelca en pantalla el contenido (cont es el numero de bytes) de la direccion de memoria addr\n");

        else if (strcmp(trozos, "memfill") == 0)  // memfill
            printf("memfill addr cont byte Llena cont bytes de la direccion de memoria addr con byte\n");

        else if (strcmp(trozos, "memory") == 0) {  // memory
            printf("memory [-blocks|-funcs|-vars|-all|-pmap] Muestra muestra detalles de la memoria del proceso\n");
            printf(" * [blocks] muestra los bloques de memoria asignados\n");
            printf(" * [funcs] muestra las direcciones de las funciones\n");
            printf(" * [vars] muestra las direcciones de las variables\n");
            printf(" * [all] muestra todo\n");
            printf(" * [pmap] muestra la salida del comando pmap (o similar)\n");

        } else if (strcmp(trozos, "priority") == 0)  // priority
                printf("priority [pid][valor] Muestra o cambia la prioridad del proceso pid a valoro\n");

        else if (strcmp(trozos, "showvar") == 0) // showvar
            printf("showvar var Muestra el valor y las direcciones de la variable de entorno var\n");

        else if (strcmp(trozos, "showenv") == 0) { // showenv
            printf("showenv [-environ|-addr] Mustra el entorno del proceso\n");
            printf(" * [-environ] usando environ\n * [-addr] muestra donde se almacenan environ y el 3er arg main\n");
        }

        else if (strcmp(trozos, "changevar") == 0) { // changevar
            printf("changevar [-a|-e|-p] var valor Cambia el valor de una variable de entorno\n");
            printf(" * [-a] accede por el 3er arg main\n * [-e] accede por environ\n");
            printf(" * [-p] accede por putenv\n");
        }

        else if (strcmp(trozos, "fork") == 0)  // fork
            printf("fork El shell hace fork y queda en espera a que su hijo termine\n");

        else if (strcmp(trozos, "execute") == 0) { // execute
            printf("execute [VAR1 VAR2..] prog args [@pri] Ejecuta, sin crear un proceso, prog con los arguementos args\n");
            printf("en un entorno solo con las variables VAR1 VAR2..\n");
        }

        else if (strcmp(trozos, "listjobs") == 0)  // listjobs
            printf("listjobs Muestra la lista de procesos en segundo plano\n");

        else if (strcmp(trozos, "deljobs") == 0) {  // deljobs
            printf("deljobs [-term][-sig] Elimina los procesos de la lista de procesos en segundo plano\n");
            printf(" * [-term] Elimina los procesos terminados\n");
            printf(" * [-sig] Elimina los procesos terminados por senal\n");
        }

        else if (strcmp(trozos, "job") == 0) {  // job
            printf("job [-fg] pid\tMuestra informacion del proceso pid.\n");
            printf(" * [-fg] Lo pasa a primer plano\n");
        }
    }

    else {  // Mostrar todos los comandos
        printf(" Comandos disponibles:\nautores [-l|-n] / pid [-p] / carpeta (direct) / fecha [-d|-h] / hist [-c|-N] / ");
        printf("comando N / infosis / ayuda [cmd] / fin / salir / bye\ncreate [-f][name] / stat [-long][-acc][-link] name1 name2... / delete name1, name2... / ");
        printf("list [-long][-link][-acc][-reca][-recb][-hid] name1, name2... / deltree name1, name2...\nallocate [-malloc|-createshared|-shared|-mmap] / ");
        printf("deallocate [-malloc|-shared|-delkey|-mmap|addr] / i-o [read|write] [-o] fich addr cont / memdump addr cont / memfill addr cont byte\n");
        printf("memory [-blocks|-funcs|-vars|-all|-pmap] / recursiva [n] / priority [pid][valor] / fork / showvar var / \n");
        printf("showenv [-environ|-addr] / changevar [-a|-e|-p] var valor / execute [VAR1 VAR2..] prog args [@pri] / listjobs / deljobs [-term][-sig] / job\n");
    }
}

/* Salir del shell */
void salir(char trozos[0]){
    if(strcmp(trozos, "salir") == 0)
        exit(0);

    else if(strcmp(trozos, "fin") == 0)
        exit(0);

    else if(strcmp(trozos, "bye") == 0)
        exit(0);
}

/* Repetir el comando numero N */
void comandoN(char trozos[1], int ntrozos, int argc, char* argv[], char* envp[],
              List *head, MemList *M, MemList *S, MemList *MP, ProcList *L) {
    int N;
    char *comando;

    if(ntrozos > 1) {
        N = atoi(trozos);  // Convertir a int
        comando = find_n(N, head);

        printf("%s\n", comando);
        leerEntrada(comando, ntrozos, argc, argv, envp, head, M, S, MP, L);  // Repetir el comando
    }
}

/* Create */
void create(char *trozos[], int ntrozos) {
    if (ntrozos > 1) {
        if (strcmp(trozos[1], "-f") == 0) { // Crear un fichero de texto
            if (creat(trozos[2], 0775) == -1)
                printf(" * Error: %s\n", strerror(errno));
        }

        else {  // Crear directorio
            if (mkdir(trozos[1], 0775) == -1)
                printf(" * Error: %s\n", strerror(errno));
        }

    } else  // Mostrar el directorio actual
        carpeta(trozos, ntrozos);
}

/* Stat */
void stats(char *trozos[], int ntrozos){
    int op[] = {0, 0, 0, 0, 0, 0};  // opciones [-long][-link][-acc]
    int aux = 0;
    char cwd[MAX];

    if(ntrozos > 1) {
        for (int i = 1; i < ntrozos; i++) {  // Ver que opcion se eligio
            if (strcmp(trozos[i], "-long") == 0)
                op[0] = 1;

            if (strcmp(trozos[i], "-link") == 0)
                op[1] = 1;

            if (strcmp(trozos[i], "-acc") == 0)
                op[2] = 1;
        }

        for (int i = 1; trozos[i] != NULL; i++) {  // Si hay varios archivos (stat [name1][name2]...)
            if (strcmp(trozos[i], "-long") != 0 && strcmp(trozos[i], "-acc") != 0 && strcmp(trozos[i], "-link") != 0) {
                list_file(trozos[i], op);
                printf("\n");
                aux++;
            }
        }
        if(aux == 0) {
            getcwd(cwd, MAX);
            printf("%s\n", cwd);
        }
    }
    else { // No se mostro nada
        getcwd(cwd, MAX);
        printf("%s\n", cwd);    }
}

/* List */
int list(char *trozos[], int ntrozos) {
    int op[] = {0, 0, 0, 0, 0, 0, 0};  // Opciones del comando [-long][-link][-acc][-reca][-recb][-hid] aux
    char cwd[MAX];
    int aux = 0;

    if (ntrozos > 1) {
        for (int i = 1; i < ntrozos; i++) {  // Ver que opciones se eligieron
            if (strcmp(trozos[i], "-reca") == 0)
                op[3] = 1;

            else if (strcmp(trozos[i], "-recb") == 0)
                op[4] = 1;

            else if (strcmp(trozos[i], "-hid") == 0)
                op[5] = 1;

            else if (strcmp(trozos[i], "-long") == 0)
                op[0] = 1;

            else if (strcmp(trozos[i], "-link") == 0)
                op[1] = 1;

            else if (strcmp(trozos[i], "-acc") == 0)
                op[2] = 1;
        }

        for (int i = 1; trozos[i] != NULL; i++) {
            if (strcmp(trozos[i], "-long") != 0 && strcmp(trozos[i], "-acc") != 0 && strcmp(trozos[i], "-link") != 0
                && strcmp(trozos[i], "-hid") != 0 && strcmp(trozos[i], "-reca") != 0 && strcmp(trozos[i], "-recb") != 0) {

                if(!list_dir(trozos[i], op)) // Mostrar informacion
                    printf(" * Error: %s\n", strerror(errno));
                aux++;
            }
        }
    }
    if (aux == 0) {  // NO se mostro nada
        getcwd(cwd, MAX);
        printf("%s\n", cwd);
    }
    return 0;
}

/* Delete */
int delete(char *trozos[], int ntrozos){
    struct stat st_buf;

    if(ntrozos > 1){
        int tipo;
        tipo = stat(trozos[1], &st_buf);

        if(tipo != 0){
            printf("* Error, errno=%d\n",errno);

        }else if(S_ISREG (st_buf.st_mode)){

            FILE* fp = fopen(trozos[1],"r");
            fseek(fp, 0L, SEEK_END);
            long int size= ftell(fp);
            fclose(fp);

            if(size == 0){
                if(remove(trozos[1]) == -1) // Borrar fichero vacio
                    printf(" * Error: %s\n", strerror(errno));
            }else{
                printf("El archivo no esta vacio\n");
            }
        }else if(S_ISDIR (st_buf.st_mode)){
            if(remove(trozos[1]) == -1)  // Borrar fichero o directorio vacio
                printf(" * Error: %s\n", strerror(errno));
        }

    } else {  // Mostrar directorio actual
        char cwd[MAX];

        getcwd(cwd, MAX);
        printf("%s\n", cwd);
    }
    return 0;
}

/* Deltree */
int deltree(char *trozos[], int ntrozos) {
    struct stat buf;
    DIR *dir;
    struct dirent *entry;
    char aux[MAX];

    if(ntrozos > 1) {
        for (int i = 1; i < ntrozos; i++) {
            if((dir = opendir(trozos[i])) == NULL)
                return false;

            if (dir == NULL) {
                return false;
            }

            while((entry = readdir(dir)) != NULL) {
                strcpy(aux, trozos[i]);

                stat(trozos[i], &buf);

                if (S_ISDIR(buf.st_mode)) {
                    pimplarDir(aux);
                    remove(aux);
                }
            }
         }
    } else { //muestra el directorio actual
        char cwd[MAX];

        getcwd(cwd, MAX);
        printf("%s\n", cwd);
    }
    return 0;
}

/* Allocate */
int allocate(char *trozos[], MemList *M, MemList *S, MemList *MP){
    MPos p, aux;
    size_t tam;
    key_t cl;

    if(trozos[1] != NULL) {
        /* allocate -malloc */
        if (strcmp(trozos[1], "-malloc") == 0) {  // Crear un bloque malloc
            if(*M == NULL)
                createMemList(M);  // Si no se creo la lista

            if (trozos[2] != NULL) {
                tam = (size_t) strtoul(trozos[2], NULL, 10);  // Tamaño del bloque

                if (tam == 0) {
                    printf("No se asignan bloques de 0 bytes\n");
                    return 0;
                }

                struct MNode *block;  // Creamos el bloque
                if(!createMNode(&block))
                    return -1;

                time_t t = time(NULL);
                char date[20];

                struct tm *fecha = localtime(&t);
                strftime(date, 100, "%d/%m/%Y %H:%M:%S\n", fecha);

                strcpy(block->data.time, date); // Fecha de creacion
                block->data.size = tam;  // Tamaño
                block->data.dir = malloc(tam); // Direccion de memoria
                strcpy(block->data.type, "malloc");  // Tipo (malloc)

                InsertarNodoMalloc(M, block);  // Insertar en la lista de direcciones malloc
                LlenarMemoria(block->data.dir, 24, 0, 0);

                printf("Asignados %zu bytes en %p\n", tam, block->data.dir);

            } else  // Mostrar lista de direcciones (allocate -malloc)
                printMemList(*M, 0);

            /* allocate -createshared */
        } else if (strcmp(trozos[1], "-createshared") == 0) {  // Crear direccion de memoria compratida a partir de la clave
            if(*S == NULL)
                createMemList(S);

            if (trozos[2] != NULL)
                do_AllocateCreateshared(trozos, *S);
            else
                printMemList(*S, 1);  // Mostrar la lista de direcciones memoria compartida

            /* allocate -shared */
        } else if (strcmp(trozos[1], "-shared") == 0) {
            if (trozos[2] != NULL) {
                cl = (key_t) strtoul(trozos[2], NULL, 10);  // Clave
                aux = findKeyBlock(cl, *S); // Ver si existe esa clave

                if (aux == NULL) {
                    printf("Imposible asignar memoria a la clave compartida %d\n", cl);
                    return 0;
                }

                p = ObtenerMemoriaShmget(cl, 0, S);
                printf("Memoria compartida de clave %d en %p\n", cl, p);

            } else
                printMemList(*S, 1);  // Mostrar la lista de direcciones memoria compartida

            /* allocate -mmap */
        } else if (strcmp(trozos[1], "-mmap") == 0) {
            if(*MP == NULL)
                createMemList(MP);

            if (trozos[2] != NULL)
                do_AllocateMmap(trozos, MP);
            else
                printMemList(*MP, 2);
        }
    }
    else  /* allocate */
        printMemList2(*M, *S, *MP);  // Mostrar todas las listas

    return 0;
}

/* Deallocate */
int deallocate(char *trozos[], MemList *M, MemList *S, MemList *MP){
    MPos p;

    if(trozos[1] != NULL) {
        if (strcmp(trozos[1], "-malloc") == 0) {
            if (trozos[2] != NULL) {
                int tam = atoi(trozos[2]);  // Tamaño del bloque

                if (tam == 0) {
                    printf("No puede ser un bloque de 0 bytes\n");
                    return 0;
                }

                if (tam < 0) {  // Si es negativo (no se puede hacer malloc)
                    printf("No es posible hacer malloc\n");
                    return 0;
                }

                p = findBlock(tam, *M);  // Buscar la posicion del bloque
                deleteAtPosition(p, M);  // Eliminar de la lista

            } else  // Mostrar lista de direcciones (deallocate -malloc)
                printMemList(*M, 0);

        } else if (strcmp(trozos[1], "-shared") == 0) {
            if (trozos[2] != NULL) {
                do_DeallocateDelkey(trozos);

            } else
                printMemList(*S, 1);

        } else if (strcmp(trozos[1], "-delkey") == 0) {
            if (trozos[2] != NULL)
                do_DeallocateDelkey(trozos);

        } else if (strcmp(trozos[1], "-mmap") == 0) {
            if (trozos[2] != NULL) {
                p = findMmapBlock(trozos[2], *MP);
                deleteAtPosition(p, MP);

            } else
                printMemList(*MP, 2);

        } else if (trozos[1] != NULL) {  // addr
            if (deleteAddr(trozos[1], *M, *S, *MP) == -1)
                printf("No se ha podido borrar en la direccion %s\n", trozos[1]);
        }
    }
    else
        printMemList2(*M, *S, *MP);  // Mostrar todas las listas

    return 0;
}

/* i-o*/
int i_o(char *trozos[]){
    int op = 0;
    size_t cont;
    char *ptr;
    void *addr;

    if(trozos[1] != NULL){
        if(strcmp(trozos[1], "read") == 0) // i-o read
            do_I_O_read(trozos);

        else if(strcmp(trozos[1], "write") == 0) {  // i-o write
            if (trozos[3] != NULL && strcmp(trozos[3], "-o") == 0) {  // sobreescribir
                op = 1;  // Sobreescribir

                addr = (void *) strtol(trozos[4], &ptr, 16);
                cont = (size_t) strtol(trozos[5],&ptr,10);

                if(EscribirFichero(trozos[3], addr, cont, op) == -1)
                    perror("Error write");

                printf("Escritos %zu bytes en %s desde %p\n", cont, trozos[2], addr);
            }

            else if (trozos[2] != NULL && trozos[3] != NULL) {
                addr = (void *) strtol(trozos[3], &ptr, 16);
                cont = (size_t) strtol(trozos[4],&ptr,10);

                if(EscribirFichero(trozos[2], addr, cont, op) == -1)
                    perror("Error write");

                printf("Escritos %zu bytes en %s desde %p\n", cont, trozos[2], addr);
            }
            else
                printf("Faltan parametros\n");
        }
    }
    return 0;
}

/* Llenar direcciones de memoria */
int memfill(char *trozos[], int ntrozos) {
    unsigned char byte;
    char *ptr;

    if(ntrozos == 3) {
        long addr = strtoul(trozos[1], &ptr, 16);

        if (trozos[3] != NULL) { // trozos[3] = byte, si es NULL llenar con A(41)
            if (trozos[3][0] + '0' == 87)
                byte = trozos[3][1];
            else
                byte = atoi(trozos[3]);

            LlenarMemoria((void *) addr, atoi(trozos[2]), byte, 1);
        }
    }
    else {   // Llenar con A(41)
        long addr = strtoul(trozos[1], &ptr, 16);
        if (trozos[2] == NULL || trozos[3] == NULL)  // Llenar 128 bytes con 'A'
            LlenarMemoria((void *) addr, 128, 'A', 1);
        else{
            if(trozos[3][0] + '0' == 87)
                byte = trozos[3][1];
            else {
                byte = atoi(trozos[3]);
                LlenarMemoria((void *) addr, atoi(trozos[2]), byte, 1);
            }
        }
    }
    return 0;
}

/* Volcar direcciones de memoria */
int memdump(char *trozos[], int ntrozos){
    int cont = 25, i = 0, j;
    void *addr;

    if(ntrozos >= 2) {
        if(trozos[1] == NULL)  // No hay direccion de memoria
            return -1;

        addr = (void *) strtol(trozos[1], NULL, 16);

        if(trozos[2] != NULL)  // Se ha introducido el valor de cont
            cont = atoi(trozos[2]);
        // Si trozos[2] == NULL, entonces cont = 25

        printf("Volcando %d bytes desde la direccion de memoria %p\n", cont, addr);

        unsigned char *ad = (unsigned char*) addr;
        unsigned char aux[25];

        while (i < cont) {  // Imprimir valor del contenido de la direccion de memoria
            for (j = 0; j < cont; j++) {
                aux[j] = ad[i];

                if (ad[i] == 10)
                    printf("/");

                else if((ad[i] < 31) || (ad[i] > 126))
                    printf("   ");

                else
                    printf(" %c ", aux[i]);
                i++;
            }
            printf("\n");
            for (int k = 0; k < i; ++k) {
                printf("%02x ", aux[k]);  // Imprimir contenido de la direccion de memoria
            }
            printf("\n\n");
        }
    }
    return 0;
}

/* memory */
void memory(char *trozos[], MemList M, MemList S, MemList MP){
    auto int ia = 0, ja = 0, ka = 0;
    static int is = 0, js = 0, ks = 0;

    if (trozos[1] == NULL  || strcmp(trozos[1], "-all") == 0) {  //printea blocks funcs y vars
        printf("Funciones Locales:\t%p, %p, %p\n", fecha, pimplarDir, stat);
        printf("Funciones Globales:\t%p, %p, %p\n", malloc, strtoul, scanf);
        printf("Variables Globales:\t%p, %p, %p\n", &xg, &yg, &zg);
        printf("Variables Locales:\t%p, %p, %p\n", &ia, &ja, &ka);
        printf("Variables Estáticas: %p, %p, %p\n", &is, &js, &ks);
        printMemList2(M, S, MP);
    }

    else if (strcmp(trozos[1], "-blocks") == 0)  // printea bloques memoria de un proceso
        printMemList2(M, S, MP);

    else if (strcmp(trozos[1], "-funcs") == 0) {   //printea dir memoria de funciones propias y globales
        printf("Funciones Locales:\t%p, %p, %p\n", fecha, pimplarDir, stat);
        printf("Funciones Globales:\t %p, %p, %p\n", malloc, strtoul, scanf);

    } else if (strcmp(trozos[1], "-vars") == 0) {  //printea dir memoria de 9 variables cada 3 de distinto tipo
        printf("Variables Globales:\t%p, %p, %p\n", &xg, &yg, &zg);
        printf("Variables Locales:\t%p, %p, %p\n", &ia, &ja, &ka);
        printf("Variables Estáticas: %p, %p, %p\n", &is, &js, &ks);

    } else if (strcmp(trozos[1], "-pmap") == 0)  //hace pmap de codigo de ayuda
        Do_pmap();
}

/* Recursiva */
void recursiva(char trozos[1]){
    int N = atoi(trozos);  // Convertir de char a int

    Recursiva(N);
}

/* Priority */
int priority(char *trozos[], int ntrozos){
    int proceso = 0;
    int pidshell = getpid();
    int pshell = getpriority(0, PRIO_PROCESS);

    if(ntrozos == 1)
        printf("La prioridad de esta shell (PID=%d) es %d\n", pidshell, pshell);

    else if(ntrozos >= 2) {
        if (trozos[2] == NULL) {
            int prior = atoi(trozos[1]);
            if (prior > -20 && prior < 19) {  // Cambiar prioridad
                if (setpriority(proceso, PRIO_PROCESS, prior) == -1) {
                    printf("Imposible obtener la prioridad del proceso %d\n", proceso);
                    return -1;
                }
                printf("Prioridad del PID=%d actualizada a %d\n", proceso, prior);
            }
            else
                printf("La prioridad de esta shell (PID=%d) es %d\n", pidshell, pshell);
        }
        else { // se indica pid y valor
            int prior = atoi(trozos[2]);
            if (prior > -20 && prior < 19) {  // Cambiar prioridad
                if (setpriority(proceso, PRIO_PROCESS, prior) == -1) {
                    printf("Imposible obtener la prioridad del proceso %d\n", proceso);
                    return -1;
                }
            }
            printf("Prioridad del PID=%d actualizada a %d\n", proceso, prior);
        }
    }
    return 0;
}

/* Showenv */
int showenv(char *trozos[], char * envp[]){
    int t=0;

    if(trozos[1] != NULL){
        if(strcmp(trozos[1],"-environ")== 0){
            while(environ[t] != NULL){
              printf("%p -> environ[%d]=(%p) %s\n", &environ[t], t,environ[t],environ[t]);
              t++;
            }
        } else if(strcmp(trozos[1],"-addr") == 0) {
            printf("environ: %p (almacenado en %p)\n", &environ, &environ);
            printf("environ: %p (almacenado en %p)\n", &envp, &envp);
        }
    } else {
        while (envp[t] != NULL) {
            printf("%p -> main[%d]=(%p) %s\n", &environ[t], t, environ[t], environ[t]);
            t++;
        }
    }
    return 0;
}

/* Showvar */
int showvar(char *trozos[],  char *envp[]){
    int j=0; //contador
    int m,e; //del main y del environ
    char *get; //pal getenv

    if(trozos[1] != NULL){
        m= BuscarVariable(trozos[1], envp);
        e= BuscarVariable(trozos[1], environ);
        get = getenv(trozos[1]);

        printf("Con arg3 main %s(%p) @%p\n", envp[m], envp[m], &envp[m]);
        printf("Con environ %s(%p) @%p\n",environ[e],environ[e],&environ[e]);
        printf("Con getenv %s(%p)\n", get, get);

    }else{
        while (envp[j] != NULL){
            printf("%p->main arg3 [%d]=(%p) %s\n",&envp[j], j, envp[j], envp[j]);
            j++;
        }
    }
    return 0;
}

/* Changevar */
int changevar(char *trozos[], int ntrozos, char *envp[]){
    char *varname = malloc(MAX);

    if(ntrozos < 3)
        printf("Uso: changevar [-a|-e|-p] var valor\n");
    else {
        if (ntrozos == 4) {
            if (strcmp(trozos[1], "-a") == 0) {
                //usando envp
                CambiarVariable(trozos[2], trozos[3], envp);
            } else if (strcmp(trozos[1], "-e") == 0) {
                //usando environ
                CambiarVariable(trozos[2], trozos[3], environ);
            } else if (strcmp(trozos[1], "-p") == 0) {
                //formamos la VAR con la estructura conocida
                strcpy(varname, trozos[2]);
                strcat(varname, "=");
                strcat(varname, (trozos[3]));
                //llamamos a la función con nuestra variable
                putenv(varname);
            }
        }
    }
    return 0;
}

/* Fork */
int forkin(ProcList *L){
    int proc;

    if((proc = fork()) == 0){
        deleteProcList(L);
        printf("Ejecutando proceso %d\n", getpid()); //se hace fork y en el
        //print pilla nuevo pid
    }else if(proc == -1){
        perror("fork: no se puede crear fork\n"); //error
        return 0;

    }else{
        waitpid(proc, NULL, 0); //con opcion 0 vuelve al anterior
    }
    return 0;
}

/* Ejecutar en primer plano */
int primer_plano(char *argv[], char *envp[], char *trozos[]) {
    int pid = fork();
    int j = 0, i, k = 0;
    char *var[50] = {};
    char *ejecutable[50] = {};

    if (trozos[0] != NULL) {
        for (i = 0; trozos[i] != NULL; i++) {
            if ((var[i] = envp[BuscarVariable(trozos[i], __environ)]) != NULL) {   // Variables
                j++;
                continue;
            }

            if (trozos[i][0] == '@') {  // Prioridad
                if (setpriority(PRIO_PROCESS, getpid(), atoi(&trozos[i][1])) == -1) {
                    perror("setpriority: error\n");
                    return -1;
                }
                continue;
            }

            ejecutable[k] = trozos[i];
            k++;
            }
        }
        if (pid == 0) {
            if (j == 0) {  // No se indican variables
                if (OurExecvpe(ejecutable[0], ejecutable, envp) == -1)
                    perror("no ejecutado\n");
            }
            else {
                if(OurExecvpe(ejecutable[0], ejecutable, var) == -1) // Variables
                    perror("no ejecutado\n");
            }
        } else
            waitpid(pid, NULL, 0);
    return 0;
}

/* Ejecutar en segundo plano */
int segundo_plano(char *argv[], char *envp[], char *trozos[], ProcList *L) {
    int pid = fork();
    int j = 0, i, k = 0;
    char *var[50] = {};
    char *ejecutable[50] = {};
    int prioridad;

    if (trozos[0] != NULL) {
        ejecutable[0] = trozos[0];  // Comando
        for (i = 0; trozos[i] != NULL; i++) {
            if ((var[i] = envp[BuscarVariable(trozos[i], __environ)]) != NULL) {  // Variables
                j++;
                continue;
            }

            if (trozos[i][0] == '@') {  // Prioridad
                if (setpriority(PRIO_PROCESS, getpid(), atoi(&trozos[i][1])) == -1) {
                    perror("setpriority: error\n");
                    return -1;
                }
                continue;
            }
            if(i > 0) {
                ejecutable[k] = trozos[i];  // Comando
                k++;
            }
        }

        if((prioridad = getpriority(PRIO_PROCESS, pid)) == -1)
            perror("getpriority: error\n");

        if (pid == 0) {
            if (j == 0)  // No se indican variables
                execvp(trozos[0], trozos);
            else
                OurExecvpe(*ejecutable, argv, var); // Variables
        }
        else
            insertar_proceso(pid, *ejecutable, prioridad, L);
    }
    return 0;
}

/* Execute */
int execute(char *trozos[], char *argv[], char *envp[]) {
    int i, j = 0, k = 0;
    char *var[50] = {}; // Variables
    char *ejecutable[50] = {};

    if (trozos[1] != NULL) {
        for (i = 1; trozos[i] != NULL; i++) {
            if (BuscarVariable(trozos[i], envp) != -1) {   // Variable
                var[j] = trozos[i];
                j++;
                continue;
            }

            if (i > 1 && trozos[i][0] == '@') {  // Prioridad
                if (setpriority(PRIO_PROCESS, getpid(), atoi(trozos[i] + 1)) == -1) {
                    perror("setpriority: error\n");
                    return -1;
                }
                continue;
            }
            ejecutable[k] = trozos[i];
            k++;
        }
        if(j == 0)
            OurExecvpe(ejecutable[0], argv + 1, envp);
        else
            OurExecvpe(ejecutable[0], argv + 1, var);

        perror("execute: error\n");
    }
    return 0;
}

/* Listjobs */
void listjobs(ProcList *L){
    printProcList(L);
}

/* Deljobs */
void deljobs(char *trozos[], ProcList *L){
    PPos aux;

    if(trozos[1] != NULL) {
        if (strcmp(trozos[1], "-sig") == 0) {
            do {
                for (aux = *L; aux->next != NULL; aux = aux->next) {
                    if (strcmp(aux->next->data.status, "SIGNALED") == 0) {
                        deleteProc(L, aux);
                        break;
                    }
                }
            } while (aux != NULL);

        } else if (strcmp(trozos[1], "-term") == 0) {
            do {
                for (aux = *L; aux != NULL; aux = aux->next) {
                    if (strcmp(aux->data.status, "TERMINADO") == 0) {
                        deleteProc(L, aux);
                        break;
                    }
                }
            } while (aux != NULL);
        }
    }
    else
        printProcList(L);
}

/* Job */
void job(char *trozos[], ProcList L){
    PPos aux;
    int pid;

    if(trozos[1] != NULL){
        if(strcmp(trozos[1], "-fg") == 0) {  // Pasar a primer plano
            pid = atoi(trozos[2]);
            aux = findProc(pid, L);

            if(strcmp(aux->data.status, "TERMINADO") == 0)
                printf("El proceso %d ya esta finalizado\n", pid);

            else {
                waitpid(pid, NULL, 0);
                printf("Proceso %d terminado normalmente\n", pid);
            }
            deleteProc(&L, aux);
        }
        else {
            aux = findProc(atoi(trozos[1]), L);

            if(aux == NULL)
                printf("Proceso no encontrado\n");
            else
                printf(" %d  p=%d %s %s %s\n", aux->data.pid, aux->data.prio, aux->data.time,
                       aux->data.status, aux->data.comando);
        }
    }
    else
        printProcList(&L);
}
