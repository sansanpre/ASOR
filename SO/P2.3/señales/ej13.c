// GLORIA PORTO Y SANDRA SÁNCHEZ

// P2.3 - ej13
/*
Escribir un programa que realice el borrado programado del propio ejecutable. 
El programa tendrá como argumento el número de segundos que esperará antes de borrar el fichero. 
El borrado del fichero se podrá detener si se recibe la señal SIGUSR1.
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

volatile int stop = 0;

void manejador(int senial){
    // si recibe la señal usr1 se podra detener
    if (senial == SIGUSR1) stop = 1;
}

int main(int argc, char **argv) {
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    struct sigaction act;
    
    // señal int
    sigaction(SIGUSR1, NULL, &act); //get manejador
    act.sa_handler = manejador;
    sigaction(SIGUSR1, &act, NULL); //set sa_manejador

    // pasamos a int el num de segundos que nos pasan por args
    int secs = atoi(argv[1]);
    int i = 0;
        // esperamos dichos segundos antes se seguir
        while (i < secs && stop == 0) {
        i++;
        sleep(1);
    }

    if (stop == 0) {
        printf("Borramos fichero");
        unlink(argv[0]);
    } else {
        printf("No borramos fichero. Se recibio la señal usr1");
    }

    return 0;
}