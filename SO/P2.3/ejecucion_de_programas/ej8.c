// GLORIA PORTO Y SANDRA SÁNCHEZ

// P2.3 - ej8
/*
Usando la versión con execvp(3) del ejercicio 7 y la plantilla de demonio del ejercicio 6, 
escribir un programa que ejecute cualquier programa como si fuera un demonio. 
Además, redirigir los flujos estándar asociados al terminal usando dup2(2):
    ·	La salida estándar al fichero /tmp/daemon.out.
    ·	La salida de error estándar al fichero /tmp/daemon.err.
    ·	La entrada estándar a /dev/null.
Comprobar que el proceso sigue en ejecución tras cerrar la shell.
*/


#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv){


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
            printf("[Hijo] Proceso %i (Padre: %i)\n",getpid(),getppid());
            int fd = open("/tmp/daemon.out",O_CREAT | O_RDWR, 00777);
            int fderr = open("/tmp/daemon.err", O_CREAT | O_RDWR, 00777);
            int null = open("/dev/null", O_CREAT | O_RDWR, 00777);
            int fd2 = dup2(fd,2);
            int fd3 = dup2(fderr, 1);
            int fd4 = dup2(null, 0);

            //ejecutamos con execvp el programa que nos pasan como argumento (ej7_execpv)
            if (execvp(argv[1], argv + 1) == -1) {
                printf("ERROR\n");
            }

            printf("El comando terminó de ejecutarse.\n");
        break;

        // >0 caso ejecutando el padre (el valor es el pid del hijo)
        default:
            printf("[Padre] Proceso %i (Padre: %i)\n",getpid(),getppid());
        break;
    }
    return 0;
}