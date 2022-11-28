// GLORIA PORTO Y SANDRA SÁNCHEZ

// P2.3 - ej6
/*
Escribir una plantilla de demonio (creación del nuevo proceso y de la sesión) en el que únicamente se muestren 
los atributos del proceso (como en el ejercicio anterior). Además, fijar el directorio de trabajo del demonio a /tmp.
*/


#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <sys/time.h>


void print_atributos(char *type){
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
    }
    else{
        printf("MAX LIMIT: %li\n", limit.rlim_max);

        // calculamos y mostramos el dir de trabajo actual (reservando)
        char *reserv_path = malloc(sizeof(char)*(4096 + 1));
        char *absolute_path = getcwd(reserv_path, 4096 + 1);
        printf("CWD: %s\n", reserv_path);
        free (reserv_path);
    }
}

int main() {

    // creamos 1 proceso hijo
    pid_t pid = fork();

    switch (pid) {
        // caso fallo
        case -1:
            perror("fork");
            exit(-1);
        break;

        // caso ejecutando el hijo
        case 0:
            // creamos sesion
            setsid(); 

            //cambiamos el dir de trabajo del demonio a tmp
            chdir("/tmp"); 

            //mostramos
            printf("[Hijo] Proceso %i (Padre: %i)\n",getpid(),getppid());
            print_atributos("Hijo");

            // dormimos para que termine antes el padre:
            //sleep (3);
        break;

        // >0 caso ejecutando el padre (el valor es el pid del hijo)
        default:
            // dormimos para que termine antes el hijo:
            //sleep (3);
            printf("[Padre] Proceso %i (Padre: %i)\n",getpid(),getppid());
            print_atributos("Padre");
        break;
    }
    return 0;
}