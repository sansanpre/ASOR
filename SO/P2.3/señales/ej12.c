// GLORIA PORTO Y SANDRA SÁNCHEZ

// P2.3 - ej12
/*
Escribir un programa que instale un manejador para las señales SIGINT y SIGTSTP. 
El manejador debe contar las veces que ha recibido cada señal. 
El programa principal permanecerá en un bucle que se detendrá cuando se hayan recibido 10 señales. 
El número de señales de cada tipo se mostrará al finalizar el programa. 
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

volatile int int_count = 0;
volatile int tstp_count = 0;

// configuramos la funcion del manejador
void manejador(int senial){
    if (senial == SIGINT) int_count++;
    if (senial == SIGTSTP) tstp_count++;
}

int main(){

    struct sigaction act;

    // señal int
    sigaction(SIGINT, NULL, &act); //get manejador
    act.sa_handler = manejador;
    sigaction(SIGINT, &act, NULL); //set sa_manejador
    
    // señal tstp
    sigaction(SIGTSTP, NULL, &act); //set manejador
    act.sa_handler = manejador;
    sigaction(SIGTSTP, &act, NULL); //set sa_manejador

    sigset_t set;
    sigemptyset(&set);

    // permanecemos en bucle hasta que se hayan recibido 10 señales
    while (int_count + tstp_count < 10)
        sigsuspend(&set);

    // mostramos el total de señales recibidas de cada tipo
    printf("SIGINT recibidas: %i\n", int_count);
    printf("SIGTSTP recibidas: %i\n", tstp_count);

  return 0;
}