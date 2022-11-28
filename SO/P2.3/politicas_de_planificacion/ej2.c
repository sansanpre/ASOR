// GLORIA PORTO Y SANDRA SÁNCHEZ

// P2.3 - ej2
/*
Escribir un programa que muestre la politica de planificacion (como cadena) y la prioridad del proceso actual, 
ademas de mostrar los valores maximo y minimo de la prioridad para la politica de planificacion. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>


int main(int argc, char **argv) {
	
    // consultamos la PID y la política de planificación del proceso actual
    int pid = atoi(argv[0]);                         // convertimos a int
    int politica = sched_getscheduler(pid);          // consultamos la politica de planificacion (scheduler) del proceso actual (si pid=0, recupera la politica del proceso de llamada)


    // mostramos como cadena la politica de planificacion consultada
    switch (politica) {
        case SCHED_OTHER:
            printf("SCHEDULER: OTHER\n");
        break;

        case SCHED_FIFO:
            printf("SCHEDULER: FIFO\n");
        break;

        case SCHED_RR:
            printf("SCHEDULER: RR\n");
        break;

        default:
            printf("ERROR\n");
        break;
    }


    // consultamos la prioridad del proceso 
    struct sched_param parametros;
    sched_getparam(pid,&parametros);

    // mostramos la prioridad asignada al proceso
    printf("PRIORIDAD: %i\n", parametros.sched_priority);

    // tambien podriamos mostrar la prioridad actual del proceso: 
        //  printf("PRIORIDAD: %i\n", parametros.sched_curpriority);


    // consultamos los valores max y min de la prioridad para la politica de planificacion
    int max = sched_get_priority_max(politica);
    int min = sched_get_priority_min(politica);

    // mostramos los valores max y min de la prioridad para la política de planificacion
    printf("MAX: %i - MIN: %i\n", max, min);

}