#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include "comandos.h"

/* Mostrar autores */
int autores(char trozos[1], int ntrozos){
    if(ntrozos > 1) {
        if (strcmp(trozos, "-n") == 0) { // (-n) Imprimir nombres
            printf("Claudia, Sergio\n");
            return 0;
        }

        else if (strcmp(trozos, "-l") == 0) {  // (-l) Imprimir logins
            printf("c.maciel, sergio.vila1\n");
            return 0;
        }
    }
    // Imprimir las 2 cosas
    printf("Claudia, Sergio / c.maciel, sergio.vila1\n");
    return 0;
}

/* Imprimir PID */
int pid(char trozos[1], int ntrozos) {

    int pid, parent;
    if (ntrozos > 1) {
        if (strcmp(trozos, "-p") == 0) { // (-p) Imprimir proceso padre de la shell
            parent = getppid();
            printf("el pid padre de la shell es: %d\n", parent);
            return 0;

        }
    } else { //Imprimir proceso actual de la shell
            pid = getpid();
            printf("El pid del proceso actual es: %d\n", pid);
            return 0;
        }
}


/* Mostrar fecha y hora de hoy */
int fecha(char trozos[1], int ntrozos) {
    time_t t = time(NULL);
    struct tm *fecha = localtime(&t);
    char datepr[100];

    if(ntrozos > 1) { // Imprimir fecha y hora
        if (strcmp(trozos, "-d") == 0) { // (-d) Imprimir ano/mes/dia
            strftime(datepr, 100, "%d/%m/%Y\n", fecha);
            printf("Current date: %s", datepr);
            return 0;

        } else if (strcmp(trozos, "-h") == 0) { // (-h) Imprimir hora/min/seg
            strftime(datepr, 100, "%H:%M:%S\n", fecha);
            printf("Current time: %s", datepr);
            return 0;
        }
    }
    // Imprimir las dos cosas
    strftime(datepr, 100, "%d/%m/%Y %H:%M:%S\n", fecha);
    printf("Current date & time: %s", datepr);
    return 0;
}

/* Mostrar informacion de la maquina */
int infosis(char trozos[1]){
    struct utsname unameData;
    uname(&unameData);

    if(uname(&unameData) < 0) { //control de errores
        printf("Command infosis failed\n");
    }
    printf("%s %s %s %s %s\n", unameData.nodename, unameData.machine, unameData.sysname,
           unameData.release, unameData.version); //imprimimos datos sistema
    return 0;
}

int carpeta(char trozos[1], int ntrozos){
    if(ntrozos > 1) {   // (-direct) cambiar de directorio a direct
        chdir(&trozos[1]);
        return 0;
    }

    else {  // Mostrar directorio actual
        char cwd[MAX];

        getcwd(cwd, MAX);
        printf("Directorio actual: %s\n", cwd);

        return 0;
    }
}

int hist(char trozos[1], int ntrozos, List *head) {
    Pos p;
    int i = 0;

        if (ntrozos > 1) {
            if (strcmp(trozos, "-c") == 0)  // (-c) Borrar historial
                deleteList(head);

            else {  // (-N) Imprimir el historial hasta -N
                char *aux[3];
                aux[0] = strtok(trozos, "-");

                int n = atoi(aux[0]);

                for (p = first(*head); (p->next != NULL) && (i <= n); p = p->next, i++)
                    printf("%d) %s\n", i, p->data.comando);

                return 0;
            }
        } else {  // Imprimir historial
            for (p = first(*head); p != NULL; p = p->next, i++)
                printf("%d) %s\n", i, p->data.comando);
            return 0;
        }
        return 0;
}

/* Ayuda */
int ayuda(char trozos[1], int ntrozos) {
    if (ntrozos > 1) {
        // ayuda [cmd]
        if (strcmp(trozos, "autores") == 0) {  // Autores
            printf(" Prints the names and logins of the program authors\n * authors -l prints only the logins\n * authors -n prints only the names\n");
            return 0;
        }

        if (strcmp(trozos, "pid") == 0) { //Pid
            printf(" Prints the pid of the process executing the shell\n * pid -p prints the pid of the shell’s parent process\n");
            return 0;
        }

        if (strcmp(trozos, "fecha") == 0) {  // Fecha
            printf(" Without arguments it prints both the current date and the current time\n * fecha -d prints the current date in the format DD/MM/YYYY\n");
            printf(" * fecha -h prints the current time in the format hh:mm:ss\n");
            return 0;
        }

        if (strcmp(trozos, "hist") == 0) {  // hist
            printf(" Shows/clears the historic of commands executed by this shell\n * hist Prints all the comands that have been input with their order\n");
            printf(" * hist -c Clears (empties) the list of historic commands\n * hist -N Prints the first N comands\n");
            return 0;
        }

        if(strcmp(trozos, "infosis") == 0) {  // Infosis
            printf(" Prints information on the machine running the shell\n");
            return 0;
        }

        if (strcmp(trozos, "carpeta") == 0) {  // Carpeta
            printf(" Changes the current working directory of the shell to direct. When invoked without arguments it prints the current working directory\n");
            return 0;
        }

        if(strcmp(trozos, "ayuda") == 0) {  // Ayuda
            printf(" Displays a list of available commands\n * ayuda cmd gives a brief  0help on the usage of comand cmd\n");
            return 0;
        }

        if (strcmp(trozos, "comandoN") == 0) {  // ComandoN
            printf(" Repeats command number N\n");
            return 0;
        }

        if (strcmp(trozos, "salir") == 0) { // Salir (salir)
            printf(" Ends the shell\n");
            return 0;
        }

        if (strcmp(trozos, "bye") == 0) { // Salir (bye)
            printf(" Ends the shell\n");
            return 0;
        }

        if (strcmp(trozos, "fin") == 0) { // Salir (fin)
            printf(" Ends the shell\n");
            return 0;
        }

        if (strcmp(trozos, "create") == 0) { // Create
            printf(" Creates a file or directory\n * create -f [name] Creates a file\n * create [name] Createsa directory\n");
            return 0;
        }

        if (strcmp(trozos, "stat") == 0) { // Stat
            printf(" stat [-long][-acc][-link] name1 name2... Gives information on files or directories\n * stat [-long] Displays more information\n * stat [-acc] Displays access time\n");
            printf(" * stat [-link] Shows the path\n");
            return 0;
        }
    }
    printf(" autores[-l|-n] / pid[-p] / carpeta[direct] / fecha[-d|-h] / hist[-c|-N] / ");
    printf("comando N / infosis / ayuda[cmd] / fin / salir / bye / create [-f][name] \n");
    return 0;
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
int comandoN(char trozos[1], int ntrozos, List *head) {
    int N;
    char *comando;

    if(ntrozos != 0) {
        N = atoi(trozos);
        comando = find_n(N, head);

        printf("%s", comando);
        leerEntrada(comando, ntrozos, head);
        return 0;
    }
    return 0;
}

/* Create */
int create(char *trozos[], int ntrozos){
    if(ntrozos >= 1){
        if(strcmp(trozos[1], "-f") == 0) { // Crear un fichero de texto
            creat(trozos[2], 0775);
            return 0;
        }
        else
            mkdir(trozos[1], 0775);
        return 0;
    }

    else {  // Mostrar el directorio actual
        char cwd[MAX];

        getcwd(cwd, MAX);
        printf("%s\n", cwd);

        return 0;
    }
}

char LetraTF (mode_t m)
{
    switch (m&S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK: return 's'; /*socket */
        case S_IFLNK: return 'l'; /*symbolic link*/
        case S_IFREG: return '-'; /* fichero normal*/
        case S_IFBLK: return 'b'; /*block device*/
        case S_IFDIR: return 'd'; /*directorio */
        case S_IFCHR: return 'c'; /*char device*/
        case S_IFIFO: return 'p'; /*pipe*/
        default: return '?'; /*desconocido, no deberia aparecer*/
    }
}

char *ConvierteModo (mode_t m, char *permisos)
{
    strcpy (permisos,"---------- ");

    permisos[0] = LetraTF(m);
    if (m&S_IRUSR) permisos[1]='r';    /*propietario*/
    if (m&S_IWUSR) permisos[2]='w';
    if (m&S_IXUSR) permisos[3]='x';
    if (m&S_IRGRP) permisos[4]='r';    /*grupo*/
    if (m&S_IWGRP) permisos[5]='w';
    if (m&S_IXGRP) permisos[6]='x';
    if (m&S_IROTH) permisos[7]='r';    /*resto*/
    if (m&S_IWOTH) permisos[8]='w';
    if (m&S_IXOTH) permisos[9]='x';
    if (m&S_ISUID) permisos[3]='s';    /*setuid, setgid y stickybit*/
    if (m&S_ISGID) permisos[6]='s';
    if (m&S_ISVTX) permisos[9]='t';

    return permisos;
}
/* Stat */
int stats(char *trozos[], int ntrozos){
    struct stat buf;

        if(ntrozos > 2){
            if(strcmp(trozos[1], "-long") == 0){  // stat -long name1 name2...
                char permisos[10];

                stat(trozos[2], &buf);
                struct passwd *p;

                p = getpwuid(buf.st_uid);

                printf(" Last access: %s Number of links: %lu (Inode: %ld)   User name: %s  GID: %s   %s   %ld %s\n", ctime(&buf.st_mtime), buf.st_nlink, buf.st_ino, p->pw_name,
                       p->pw_name, ConvierteModo(buf.st_mode, permisos), buf.st_size, trozos[2]);
                return 0;
            }

            if(strcmp(trozos[1], "-acc") == 0){  // stat -acc name1 name2...
                stat(trozos[2], &buf);
                printf(" Last access: %s \t %ld %s\n", ctime(&buf.st_mtime), buf.st_size, trozos[2]);
                return 0;
            }

            if(strcmp(trozos[1], "-link") == 0){  // stat -link name1 name2...
                stat(trozos[2], &buf);

                    if(buf.st_mode&S_IFLNK)
                        printf("Symbolic link = true ");
                    else
                        printf("Symbolic link = false ");

                printf(" %ld %s\n", buf.st_size, trozos[2]);
                return 0;
            }
    }

    else if(ntrozos > 1) {  // Mostrar el directorio actual
            stat(trozos[1], &buf);
            printf("\t%ld %s\n", buf.st_size, trozos[1]);

            return 0;

        } else {
        char cwd[MAX];

        getcwd(cwd, MAX);
        printf("%s\n", cwd);

        return 0;
    }
}

