// GLORIA PORTO Y SANDRA SÁNCHEZ

// P2.3 - ej11
/*
Escribir un programa que bloquee las señales SIGINT y SIGTSTP. 
Después de bloquearlas el programa debe suspender su ejecución con sleep(3) 
un número de segundos que se obtendrán de la variable de entorno SLEEP_SECS. 
Al despertar, el proceso debe informar de si recibió la señal SIGINT y/o SIGTSTP. 
En este último caso, debe desbloquearla con lo que el proceso se detendrá 
y podrá ser reanudado en la shell (imprimir una cadena antes de finalizar el programa para comprobar este comportamiento).
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


int main(int argc, char **argv) {

    sigset_t set;

    // inicializamos las señales 
    sigemptyset(&set);

    // añadimos las señales de int y tstp
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTSTP);

    // protegemos la región de código contra la recepción de las señales
    sigprocmask(SIG_BLOCK, &set, NULL);
  
    // obtenemos la variable de entorno
    char *sleep_secs = getenv("SLEEP_SECS");
    int secs = atoi(sleep_secs);
    printf("El proceso se va a dormir durante %d s\n", secs);
  
    //Dormimos el proceso
    sleep(secs);

    // comprobamos las señales pendientes
    // señal int
    sigset_t pending;
    sigpending(&pending);
    if (sigismember(&pending, SIGINT) == 1) {
        printf("Se ha recibido la señal SIGINT\n");
        //Eliminamos la señal del conjunto anterior
        sigdelset(&set, SIGINT);
    }

    else {
        printf("No se ha recibido la señal SIGINT\n");
    }

    // señal tstp
    if (sigismember(&pending, SIGTSTP) == 1) {
        printf("Se ha recibido la señal SIGTSTP\n");
        //Eliminamos la señal del conjunto anterior
        sigdelset(&set, SIGTSTP);
    } 
    else {
        printf("No se ha recibido la señal SIGTSTP\n");
    }

    sigprocmask(SIG_UNBLOCK, &set, NULL); //to fetch and/or change the signal mask of the calling thread.  

return 0;
}