#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comandos.h"
#include "aux.h"

int xg=0, yg=0, zg=0;

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
void infosis(char trozos[1]){
    struct utsname unameData;
    uname(&unameData);

    if(uname(&unameData) < 0)  // Control de errores
        printf("Command infosis failed\n");

    printf("%s %s %s %s %s\n", unameData.nodename, unameData.machine, unameData.sysname,
           unameData.release, unameData.version); // Imprimir datos del sistema
}

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
        } else if (strcmp(trozos, "memdump") == 0) { // memdump
            printf("memdump addr cont Vuelva en pantalla el contenido (cont es el numero de bytes) de la direccion de memoria adrr\n");

        } else if(strcmp(trozos,"memory") == 0){ // memory
            printf("memory [-blocks|-funcs|-vars|-all|-pmap]\nMuestra muestra detalles de la memoria del proceso\n-blocks: los bloques de memoria asignados\n-funcs: las direcciones de las funciones\n");
		    printf("-vars: las direcciones de las variables\n-all: todo\n-pmap: muestra la salida del comando pmap(o similar)");
        
        } else {  // Mostrar todos los comandos
            printf(" Comandos disponibles:\nautores [-l|-n] / pid [-p] / carpeta (direct) / fecha [-d|-h] / hist [-c|-N] / ");
            printf("comando N / infosis / ayuda [cmd] / fin / salir / bye\ncreate [-f][name] / stat [-long][-acc][-link] name1 name2... / delete name1, name2... / ");
            printf("list [-long][-link][-acc][-reca][-recb][-hid] name1, name2... / deltree name1, name2...\nallocate [-malloc|-createshared|-shared|-mmap] / ");
            printf("deallocate [-malloc|-shared|-delkey|-mmap|addr] / i-o [read|write] [-o] fich addr cont / memdump addr cont / recursiva [n] /memory [-blocks|-funcs|-vars|-all|-pmap]\n");
        }
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
void comandoN(char trozos[1], int ntrozos, List *head, MemList *M, MemList *S, MemList *MP) {
    int N;
    char *comando;

    if(ntrozos > 1) {
        N = atoi(trozos);  // Convertir a int
        comando = find_n(N, head);

        printf("%s\n", comando);
        leerEntrada(comando, ntrozos, head, M, S, MP);  // Repetir el comando
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

    if (strcmp(trozos[1], "-malloc") == 0){
        if(trozos[2] != NULL) {
            tam = (size_t) strtoul(trozos[2], NULL, 10);  // Tamaño del bloque

            if(tam == 0){
                printf("No se asignan bloques de 0 bytes\n");
                return 0;
            }

            struct MNode *block;  // Creamos el bloque
            createMNode(&block);

            time_t t = time(NULL);
            char date[20];

            struct tm *fecha = localtime(&t);
            strftime(date, 100, "%d/%m/%Y %H:%M:%S\n", fecha);

            strcpy(block->data.time, date); // Fecha de creacion
            block->data.size = tam;  // Tamaño
            block->data.dir = malloc(tam); // Direccion de memoria
            strcpy(block->data.type, "malloc");  // Tipo (malloc)

            InsertarNodoMalloc(M, block);

            printf("Asignados %zu bytes en %p\n", tam, block->data.dir);
        }

        else  // Mostrar lista de direcciones (allocate -malloc)
            printMemList(*M, 0);
    }

    else if (strcmp(trozos[1], "-createshared") == 0){
        if(trozos[2] != NULL)
            do_AllocateCreateshared(trozos, *S);
        else
            printMemList(*S, 1);
    }

    else if (strcmp(trozos[1], "-shared") == 0) {
        if (trozos[2] != NULL) {
            cl = (key_t) strtoul(trozos[2],NULL,10);  // Clave
            aux = findKeyBlock(cl, *S); // Ver si existe esa clave

            if(aux == NULL) {
                printf("Imposible asignar memoria a la clave compartida %d\n", cl);
                return 0;
            }

            p = ObtenerMemoriaShmget(cl, 0, S);
            printf("Memoria compartida de clave %d en %p\n", cl, p);
        }
        else
            printMemList(*S, 1);
    }

    else if (strcmp(trozos[1], "-mmap") == 0) {
        if(trozos[2] != NULL)
            do_AllocateMmap(trozos, MP);
        else
             printMemList(*MP, 2);
    }
    return 0;
}

/* Deallocate */
int deallocate(char *trozos[], MemList *M, MemList *S, MemList *MP){
    MPos p;
    key_t cl;

    if (strcmp(trozos[1], "-malloc") == 0){
        if(trozos[2] != NULL) {
            int tam = atoi(trozos[2]);  // Tamaño del bloque

            if(tam == 0){
                printf("No puede ser un bloque de 0 bytes\n");
                return 0;
            }

            if(tam < 0){  // Si es negativo (no se puede hacer malloc)
                printf("No es posible hacer malloc\n");
                return 0;
            }

            p = findBlock(tam, *M);  // Buscar la posicion del bloque
            deleteAtPosition(p, M);  // Eliminar de la lista
        }

        else  // Mostrar lista de direcciones (deallocate -malloc)
            printMemList(*M, 0);
    }

    else if (strcmp(trozos[1], "-shared") == 0){
        if(trozos[2] != NULL) {
            cl = (key_t) strtoul(trozos[2], NULL, 10);  // Clave
            p = findKeyBlock(cl, *S);

            deleteAtPosition(p, S);
        }
        else
            printMemList(*S, 1);
    }

    else if (strcmp(trozos[1], "-delkey") == 0) {
        if(trozos[2] != NULL)
            do_DeallocateDelkey(trozos);
    }

    else if (strcmp(trozos[1], "-mmap") == 0) {
        if(trozos[2] != NULL) {
            p = findMmapBlock(trozos[2], *MP);
            deleteAtPosition(p, MP);
        }

        else
            printMemList(*MP, 2);
    }

    else if (trozos[1] != NULL)  // addr
        if(deleteAddr(trozos[1], *M, *S, *MP) == -1)
            printf("No se ha podido borrar en la direccion %s\n", trozos[1]);

    return 0;
}

int i_o(char *trozos[], MemList *M, MemList *S, MemList *MP){
    int op = 0;

    if(trozos[1] != NULL){
        if(strcmp(trozos[1], "read") == 0) {  // i-o read
            do_I_O_read(trozos);
        }

        else if(strcmp(trozos[1], "write") == 0){
            if(trozos[5] != NULL && strcmp(trozos[5], "-o") == 0)
                op = 1;  // Sobreescribir

            EscribirFichero(trozos[2], trozos[3], atoi(trozos[4]), op);
        }
    }
}

int memdump(char *trozos[], int ntrozos){
    if(ntrozos == 3) {  // memdump addr cont
        char *ptr;
        long addr = strtoul(trozos[1], &ptr, 16);

        int cont = atoi(trozos[2]);

    }
    return 0;
}

/* Recurse */
void recursiva(char trozos[1]){
    int N = atoi(trozos);  // Convertir de char a int

    Recursiva(N);
}

void memory(char *trozos[], int ntrozos){
    
    if(strcmp(trozos[1],"-blocks") == 0 ){// printea bloques memoria de unn proceso
         printf("*****Lista de bloques asignados para el proceso %d\n", getpid());
         //printMemList(, 3);

    }else if(strcmp(trozos[1],"-funcs") == 0){//printea dir memoria de funciones propias y globales
        printf("Funciones Locales:\t%p, %p, %p",fecha ,pimplarDir ,stat);
        printf("Funciones Globales:\t %p, %p, %p",malloc ,strtoul , scanf);

    }else if(strcmp(trozos[1],"-vars") == 0){//printea dir memoria de 9 variables cada 3 de distinto tipo
        auto int ia=0, ja=0, ka=0;
        static int is=0, js=0, ks=0;

        printf("Variables Globales:\t%p, %p, %p\n",&xg, &yg, &zg);
        printf("Variables Locales:\t%p, %p, %p\n",&ia, &ja, &ka);
        printf("Variables Estáticas:\t%p, %p, %p\n",&is, &js, &ks);

    }else if(strcmp(trozos[1],"-all") == 0){//printea blocks funcs y vars
        memory("-blocks",1);
        memory("-funcs",1);
        memory("-vars",1);

    }else if(strcmp(trozos[1],"-pmap") == 0){//hace pmap de codigo de ayuda
        Do_pmap();

    }

}