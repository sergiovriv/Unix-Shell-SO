/* Claudia Maciel Montero */
/* c.maciel  */
/* Sergio Vila Riveira */
/* sergio.vila1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comandos.h"

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

        if (strcmp(trozos, "pid") == 0)  //Pid
            printf(" Muestra el pid del shell \n * [-p] Muestra el pid del proceso padre\n");

        if (strcmp(trozos, "fecha") == 0) {  // Fecha
            printf(" Imprime la fecha y hora actuales\n * [-d] Imprime la fecha actual en el formato: DD/MM/YYYY\n");
            printf(" * [-h] Imprime la hora actual en el formato: hh:mm:ss\n");
        }

        if (strcmp(trozos, "hist") == 0) {  // hist
            printf(" Muestra / Borra el historial de comandos\n * hist Muestra el historial de comandos");
            printf(" * [-c] Borra el historial de comandos\n * [-N] Imprime los primeros N comandos\n");
        }

        if(strcmp(trozos, "infosis") == 0)   // Infosis
            printf(" Muestra informacion de la maquina ejecuntando esta shell\n");

        if (strcmp(trozos, "carpeta") == 0)   // Carpeta
            printf(" Muestra el directorio actual \n * carpeta (direct) Cambia el directorio a direct\n");

        if(strcmp(trozos, "ayuda") == 0)  // Ayuda
            printf(" Muestra la lista de los comandos disponibles\n * [cmd] Muestra la ayuda del comando cmd\n");

        if (strcmp(trozos, "comandoN") == 0) // ComandoN
            printf(" Repite el comando numero N\n");

        if (strcmp(trozos, "salir") == 0)  // Salir (salir)
            printf(" Termina la ejecucion del shell\n");

        if (strcmp(trozos, "bye") == 0)  // Salir (bye)
            printf(" Termina la ejecucion del shell\n");

        if (strcmp(trozos, "fin") == 0)  // Salir (fin)
            printf(" Termina la ejecucion del shell\n");

        if (strcmp(trozos, "create") == 0)  // Create
            printf(" Crea un archivo o directorio\n * create -f [name] Crea un fichero\n * create [name] Crea un directorio\n");

        if (strcmp(trozos, "stat") == 0) { // Stat
            printf(" stat [-long][-acc][-link] name1 name2... Muestra informacion de arhivos y directorios\n");
            printf(" * stat [-long] Muestra mas informacion\n * stat [-acc] Muestra ultimo acceso\n");
            printf(" * stat [-link] Si tiene links simbolicos\n");
        }

        if (strcmp(trozos, "delete") == 0)  // Delete
            printf(" delete name1 name2... Borra archivos y/o directorios vacios\n");

        if (strcmp(trozos, "list") == 0) { // List
            printf(" list [-reca][-recb][-hid][-long][-link][-acc] n1 n2 ... Muestra archivos y directorios\n");
            printf(" * [-hid] Muestra directorios ocultos\n * [-reca] Muestra de forma recursiva (antes)\n * [-recb] Muestra de forma recursiva (despues)\n");
            printf(" * [-long][-link][-acc] Igual que stat. Ver 'ayuda stat' para mas info\n");
        }

        if (strcmp(trozos, "deltree") == 0) { // DeleteTree
            printf(" delete name1 name2... Borra archivos y/o directorios no vacios de forma recursiva\n");
        }

    } else {  // Mostrar todos los comandos
        printf(" Comandos disponibles: autores [-l|-n] / pid [-p] / carpeta (direct) / fecha [-d|-h] / hist [-c|-N] / ");
        printf("comando N / infosis / ayuda [cmd] / fin / salir / bye \n / create [-f][name] / stat [-long][-acc][-link] name1 name2... / delete name1, name2... / ");
        printf("list [-long][-link][-acc][-reca][-recb][-hid] / deltree\n");
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
void comandoN(char trozos[1], int ntrozos, List *head) {
    int N;
    char *comando;

    if(ntrozos > 1) {
        N = atoi(trozos);  // Convertir a int
        comando = find_n(N, head);

        printf("%s\n", comando);
        leerEntrada(comando, ntrozos, head);  // Repetir el comando
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

/* Funciones de ayuda */
char LetraTF (mode_t m) {
    switch (m&S_IFMT) { /* And bit a bit con los bits de formato, 0170000 */
        case S_IFSOCK: return 's'; /* socket */
        case S_IFLNK: return 'l'; /* symbolic link */
        case S_IFREG: return '-'; /* fichero normal */
        case S_IFBLK: return 'b'; /* block device */
        case S_IFDIR: return 'd'; /* directorio */
        case S_IFCHR: return 'c'; /* char device */
        case S_IFIFO: return 'p'; /* pipe */
        default: return '?'; /* desconocido, no deberia aparecer */
    }
}

/* Funcion de permisos */
char * ConvierteModo2 (mode_t m) {
    static char permisos[12];
    strcpy (permisos,"---------- ");

    permisos[0]=LetraTF(m);
    if (m&S_IRUSR) permisos[1]='r';    /* propietario */
    if (m&S_IWUSR) permisos[2]='w';
    if (m&S_IXUSR) permisos[3]='x';
    if (m&S_IRGRP) permisos[4]='r';    /* grupo */
    if (m&S_IWGRP) permisos[5]='w';
    if (m&S_IXGRP) permisos[6]='x';
    if (m&S_IROTH) permisos[7]='r';    /* resto */
    if (m&S_IWOTH) permisos[8]='w';
    if (m&S_IXOTH) permisos[9]='x';
    if (m&S_ISUID) permisos[3]='s';    /* setuid, setgid y stickybit */
    if (m&S_ISGID) permisos[6]='s';
    if (m&S_ISVTX) permisos[9]='t';

    return permisos;
}

/* Mostrar informacion de un fichero */
bool list_file(char *file, const int op[]){
    struct stat buf;

    if (stat(file, &buf) == -1) {
        printf(" * Error: %s\n", strerror(errno));
        return false;
    }

    else if(op[0] == 1) {  // stat [-long]
        char *permisos;
        struct passwd *p;
        struct group *g;

        if((p = getpwuid(buf.st_uid)) == NULL)  // Usuario
            return -1;
        if((g = getgrgid(buf.st_gid)) == NULL)  // Grupo
            return -1;

        permisos = ConvierteModo2(buf.st_mode);  // Obtener permisos

        printf(" %s %lu (%lu)   User name: %s  GID: %s   %s   %ld %s\n",
               ctime(&buf.st_mtime), buf.st_nlink, buf.st_ino, p->pw_name,
               g->gr_name, permisos, buf.st_size, file);

        if(op[1] == 1) {  // stat [-link]
            if (buf.st_mode &S_IFLNK)
                printf(" Symbolic link = true\n");
            else
                printf(" Symbolic link = false\n");
        }

        if(op[2] == 1)  // stat [-acc]
            printf(" Last access: %s\n", ctime(&buf.st_atime));

    } else
        printf("\t%ld %s\n", buf.st_size, file);

    return true;
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

/* Funcion auxiliar para list [-reca] */
int list_dirA(char *name, int op[]){
    DIR *dir;
    struct dirent *entry;
    struct stat buf;
    stat(name, &buf);
    char aux[MAX];

    dir = opendir(name);

    if (op[0] == 0 && op[1] == 0 && op[2] == 0)
        printf("\t%ld %s\n", buf.st_size, name);

    printf("\n************ %s\n", name);

    if (dir == NULL) {
        printf(" * Error: %s\n", strerror(errno));
        return false;
    }

    else {
        while ((entry = readdir(dir)) != NULL) {  // Recorrer archivos del directorio
            strcpy(aux, name);
            strcat(strcat(aux, "/"), entry->d_name);

            stat(aux, &buf);

            if (entry->d_name[0] == '.' && op[5] == 1) {  // [-hid] Mostrar directorios / archivos ocultos
                if (!list_file(aux, op))
                    return false;
            }
            if (S_ISDIR(buf.st_mode) && entry->d_name[0] != '.' && op[3] == 1) {  // Si es un directorio y [-reca]
                if (!list_dirA(aux, op))
                    return false;
            }
            if (entry->d_name[0] != '.' && (op[3] == 1 || op[4] == 1) && !S_ISDIR(buf.st_mode)) {
                if (!list_file(aux, op))
                    return false;
            }
        }
    }
    closedir(dir);  // Cerrar directorio
    return true;
}

/* Funcion auxiliar para list [-recb] */
bool list_dirB(char *name, int op[]){
    DIR *dir;
    struct dirent *entry;
    struct stat buf;
    stat(name, &buf);
    char aux[MAX];
    int i = 0;

    dir = opendir(name);

    if (dir == NULL) {
        perror("opendir() error");
        return false;
    }

    else {
        while ((entry = readdir(dir)) != NULL) {  // Recorrer archivos del directorio
            strcpy(aux, name);
            strcat(strcat(aux, "/"), entry->d_name);

            stat(aux, &buf);

            if (entry->d_name[0] != '.' && op[4] == 1) {  // Si es un directorio y [-recb]
                if (S_ISDIR(buf.st_mode)) {
                    i++;
                    list_dirB(aux, op);

                    op[4] = 0;  // Desactivar [-recb] para que no sea un bucle infinito
                    op[6] = 1;  // opcion aux
                    printf("************* %s\n", name);
                    list_dir(name, op);
                }
                if (entry->d_name[0] == '.' && op[5] == 1) {  // [-hid]
                    if (!list_file(aux, op))
                        return false;
                }
            } else {
                    if (entry->d_name[0] != '.')
                        printf("\t%ld %s\n", buf.st_size, entry->d_name);
            }
        }
        if(i == 0) {   // Ultima entrada
            printf("************* %s\n", name);
            op[4] = 0;
            op[6] = 1;
            list_dir(name, op);
        }
    }
    closedir(dir);  // Cerrar directorio
    return true;
}

/* Mostrar informacion de directorios */
bool list_dir(char *name, int op[]) {
    DIR *dir;
    struct dirent *entry;
    char aux[MAX];
    struct stat buf;

    dir = opendir(name);

    if((dir = opendir(name)) == NULL)
        return false;

    if (dir == NULL) {
        perror("opendir() error");
        return false;
    }

    if(op[4] == 1 && op[3] == 1)  // Si es [-reca] y [-recb] entonces [-recb] tiene prefencia
        op[3] = 0;

    if(op[4] == 1){  // [-recb] Mostrar archivos despues (desde el final hasta donde estoy)
        if(!list_dirB(name, op))
            return -1;
    }

    else {
        if(op [6] == 0)
            printf("************* %s\n", name);

        while ((entry = readdir(dir)) != NULL) {  // Recorrer archivos del directorio
            strcpy(aux, name);
            strcat(strcat(aux, "/"), entry->d_name);

            stat(aux, &buf);

            if (entry->d_name[0] == '.' && op[5] == 1) {  // [-hid] Mostrar directorios / archivos ocultos
                if (!list_file(aux, op))
                    return false;

            }  else if (entry -> d_name[0] != '.' && op[3] == 0 && op[4] == 0) {
                if (!list_file(aux, op))
                    return false;

            }  else if (S_ISDIR(buf.st_mode) && entry->d_name[0] != '.' && op[3] == 1) {  // Si es un directorio y [-reca]
                if (entry -> d_name[0] != '.' && (op[0] == 1 || op[1] == 1 || op[2] == 1)) {
                    if (!list_file(aux, op))
                        return false;
                }
                if (!list_dirA(aux, op))  // [-reca] Mostrar archivos antes (desde donde estoy hasta el final)
                    return false;

            } else {
                if (entry -> d_name[0] != '.')
                    printf("\t%ld %s\n", buf.st_size, entry -> d_name);
            }
        }
    }
    closedir(dir);  // Cerrar directorio
    return true;
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

int pimplarDir(char *name){
    DIR *dir;
    struct dirent *entry;
    struct stat buf;
    stat(name, &buf);
    char aux[MAX];

    dir = opendir(name);

    if (dir == NULL) {
        return false;
    }

    else {
        while ((entry = readdir(dir)) != NULL) {  // Recorrer archivos del directorio
            strcpy(aux, name);
            strcat(strcat(aux, "/"), entry->d_name);

            stat(aux, &buf);

            if (entry->d_name[0] != '.') {
                    pimplarDir(aux);
                    if(buf.st_size != 0){  // Si no esta vacio -> vaciar
                        stat(entry -> d_name, &buf);
                        remove(entry -> d_name);
                    }
                    remove(aux);
            }
        }
    }
    return true;
}

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

