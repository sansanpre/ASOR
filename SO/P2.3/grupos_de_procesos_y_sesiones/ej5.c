// GLORIA PORTO Y SANDRA SÁNCHEZ

// P2.3 - ej5
/*
Escribir un programa que muestre los identificadores del proceso (PID, PPID, PGID y SID), 
el número máximo de ficheros que puede abrir y su directorio de trabajo actual.
*/

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <sys/time.h>

int main() {
    // mostramos identificador pid
    printf("PID: %i\n", getpid());

    // mostramos identificador ppid
    printf("PPID: %i\n", getppid());

    // mostramos identificador pgid
    printf("PGID: %i\n", getpgid(getpid()));

    // mostramos identificador sid
    printf("SID: %i\n", getsid(getpid()));

    // calculamos y mostramos el max de ficheros que puede abrir
    struct rlimit limit;
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("resource limits error");
        return -1;
    }
    printf("MAX LIMIT: %li\n", limit.rlim_max);

    // calculamos y mostramos el dir de trabajo actual (reservando)
    char *reserv_path = malloc(sizeof(char)*(4096 + 1));
    char *absolute_path = getcwd(reserv_path, 4096 + 1);
    printf("CWD: %s\n", reserv_path);
    free (reserv_path);

    return 0;
}