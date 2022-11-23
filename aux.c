#include "aux.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <errno.h>
#include <dirent.h>
#include <grp.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define TAMANO 2048
#define MAX 100


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

/* Mostrar informacion de directorios */
bool list_dir(char *name, int op[]) {
    DIR *dir;
    struct dirent *entry;
    char aux[MAX];
    struct stat buf;

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

void *ObtenerMemoriaShmget (key_t clave, size_t tam, MemList *L) {
    void *p;
    int aux,id,flags = 0777;
    struct shmid_ds s;

    if (tam)     /* tam distinto de 0 indica crear */
        flags = flags | IPC_CREAT | IPC_EXCL;

    if (clave == IPC_PRIVATE) {  /*no nos vale*/
        errno = EINVAL;
        return NULL;
    }

    if ((id = shmget(clave, tam, flags)) == -1)
        return (NULL);

    if ((p = shmat(id,NULL,0)) == (void*) -1) {
        aux = errno;

        if (tam)
            shmctl(id,IPC_RMID,NULL);

        errno = aux;
        return (NULL);
    }
    shmctl (id,IPC_STAT,&s);

    InsertarNodoShared (L, p, s.shm_segsz, clave);
    return (p);
}

void do_AllocateCreateshared (char *tr[], MemList L) {
    key_t cl;
    size_t tam;
    void *p;

    if (tr[2] == NULL || tr[3] == NULL) {
        printMemList(L, 1);
        return;
    }

    cl = (key_t) strtoul(tr[2],NULL,10);
    tam = (size_t) strtoul(tr[3],NULL,10);

    if (tam == 0) {
        printf ("No se asignan bloques de 0 bytes\n");
        return;
    }
    if ((p = ObtenerMemoriaShmget(cl, tam, &L)) != NULL) {
        printf("Asignados %lu bytes en %p\n", (unsigned long) tam, p);
        LlenarMemoria(p, 26, 0, 0);
    }
    else
        printf ("Imposible asignar memoria compartida clave %lu: %s\n",(unsigned long) cl,strerror(errno));
}

void *MapearFichero (char *fichero, int protection, MemList *MP) {
    int df, map = MAP_PRIVATE, modo = O_RDONLY;
    struct stat s;
    void *p;

    if (protection &PROT_WRITE)
        modo = O_RDWR;

    if (stat(fichero,&s) == -1 || (df = open(fichero, modo)) == -1)
        return NULL;

    if ((p = mmap(NULL,s.st_size, protection,map,df,0)) == MAP_FAILED)
        return NULL;

    InsertarNodoMmap(MP, p, s.st_size, df, fichero); // Insertar en la lista
    return p;
}

void do_AllocateMmap(char *arg[], MemList *MP) {
    char *perm;
    void *p;
    int protection = 0;

    if (arg[2] == NULL){
        printMemList(*MP, 2);
        return;
    }

    if ((perm = arg[3]) != NULL && strlen(perm) < 4) {
        if (strchr(perm,'r') != NULL) protection|=PROT_READ;
        if (strchr(perm,'w') != NULL) protection|=PROT_WRITE;
        if (strchr(perm,'x') != NULL) protection|=PROT_EXEC;
    }

    if ((p = MapearFichero(arg[2], protection, MP)) == NULL)
        perror("Imposible mapear fichero\n");

    else
        printf("Fichero %s mapeado en %p\n", arg[2], p);
}

void do_DeallocateDelkey (char *args[]) {
    key_t clave;
    int id;
    char *key = args[2];

    if (key == NULL || (clave = (key_t) strtoul(key,NULL,10)) == IPC_PRIVATE){
        printf ("delkey necesita clave_valida\n");
        return;
    }
    if ((id = shmget(clave,0,0666)) == -1){
        perror ("shmget: imposible obtener memoria compartida");
        return;
    }
    if (shmctl(id,IPC_RMID,NULL) == -1)
        perror ("shmctl: imposible eliminar memoria compartida\n");
}

ssize_t LeerFichero (char *f, void *p, size_t cont) {
    struct stat s;
    ssize_t  n;
    int df,aux;

    if (stat(f,&s) == -1 || (df = open(f,O_RDONLY)) == -1)
        return -1;

    if (cont == -1)   /* si pasamos -1 como bytes a leer lo leemos entero*/
        cont=s.st_size;

    if ((n = read(df,p,cont)) == -1){
        aux = errno;
        close(df);
        errno = aux;
        return -1;
    }
    close (df);
    return n;
}

void *cadtop(char *c){
    void *p;

    sscanf(c, "%p", &p);
    return p;
}

void do_I_O_read (char *ar[]) {
    void *p;
    size_t cont = -1;
    ssize_t n;

    if (ar[2] == NULL || ar[3] == NULL){
        printf ("Faltan parametros\n");
        return;
    }

    p = cadtop(ar[3]);  /*convertimos de cadena a puntero*/
    if (ar[3] != NULL)
        cont = (size_t) atoll(ar[4]);

    if ((n = LeerFichero(ar[2], p, cont)) == -1)
        perror("Imposible leer fichero");
    else
        printf ("Leidos %lld bytes de %s en %p\n",(long long) n, ar[2], p);
}

ssize_t EscribirFichero (char *f, void *p, size_t cont, int overwrite) {
    ssize_t  n;
    int df,aux, flags = O_CREAT | O_EXCL | O_WRONLY;

    if (overwrite == 1)
        flags = O_CREAT | O_WRONLY | O_TRUNC;

    if ((df = open(f,flags, 0777)) == -1)
        return -1;

    if ((n = write(df,p,cont)) == -1){
        aux = errno;
        close(df);
        errno = aux;
        return -1;
    }
    close (df);
    return n;
}

void LlenarMemoria (void *p, size_t cont, unsigned char byte, int op) {
    unsigned char *arr = (unsigned char *) p;
    size_t i;

    if(op == 1)
        printf("Llenando %zu bytes de memoria con el byte (%d) a partir de la direccion %p\n", cont, byte, arr);

    for (i = 0; i < cont; i++)
        arr[i] = byte;
}

void Do_pmap (void){ /*sin argumentos*/
    pid_t pid;   /*hace el pmap (o equivalente) del proceso actual*/
    char elpid[32];
    char *argv[4] = {"pmap",elpid,NULL};

    sprintf (elpid,"%d", (int) getpid());
    if ((pid = fork()) == -1){
        perror ("Imposible crear proceso");
        return;
    }
    if (pid == 0){
        if (execvp(argv[0],argv) == -1)
            perror("cannot execute pmap (linux, solaris)");

        argv[0] = "procstat";
        argv[1] = "vm";
        argv[2] = elpid;
        argv[3] = NULL;

        if (execvp(argv[0],argv) == -1)/*No hay pmap, probamos procstat FreeBSD */
            perror("cannot execute procstat (FreeBSD)");

        argv[0] = "procmap", argv[1] = elpid;
        argv[2] = NULL;

        if (execvp(argv[0],argv) == -1)  /*probamos procmap OpenBSD*/
            perror("cannot execute procmap (OpenBSD)");

        argv[0] = "vmmap";
        argv[1] = "-interleave";
        argv[2] = elpid;argv[3] = NULL;

        if (execvp(argv[0],argv) == -1) /*probamos vmmap Mac-OS*/
            perror("cannot execute vmmap (Mac-OS)");
        exit(1);
    }
    waitpid (pid,NULL,0);
}

void Recursiva (int n) {
    char automatico[TAMANO];
    static char estatico[TAMANO];

    printf ("parametro:%3d(%p) array %p, arr estatico %p\n",n, &n, automatico, estatico);

    if (n > 0)
        Recursiva(n-1);
}
