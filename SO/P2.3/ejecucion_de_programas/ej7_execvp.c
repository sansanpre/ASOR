// GLORIA PORTO Y SANDRA SÁNCHEZ

// P2.3 - ej7_execvp
/*
Con execvp, escribir un programa que ejecute otro programa que se pasará como argumento por línea de comandos. 
En cada caso, se debe imprimir la cadena “El comando terminó de ejecutarse” después de la ejecución
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){

    //ejecutamos con execvp el programa que nos pasan como argumento
    if (execvp(argv[1], argv + 1) == -1) {
        printf("ERROR\n");
    }

    printf("El comando terminó de ejecutarse.\n");

    return 0;
}