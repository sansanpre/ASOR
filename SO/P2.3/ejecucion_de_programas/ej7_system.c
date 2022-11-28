// GLORIA PORTO Y SANDRA SÁNCHEZ

// P2.3 - ej7_system
/*
Con system, escribir un programa que ejecute otro programa que se pasará como argumento por línea de comandos. 
En cada caso, se debe imprimir la cadena “El comando terminó de ejecutarse” después de la ejecución
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){

    //Concatenamos todo lo que nos pase por pantalla:

    // calculamos el tamaño del argumento que nos pasan
    int longitud = 1;
    int i;
    for (i = 1; i < argc; i++)
        longitud += strlen(argv[i]) + 1;

    // reservamos espacio en memoria para dicho tamaño
    char *cmd = malloc(sizeof(char)*longitud);
    strcpy(cmd, "");

    // concatenamos los argumentos
    for (i = 1; i < argc; i++) {
        strcat(cmd, argv[i]);
        strcat(cmd, " ");
    }

    // ejecutamos con system el programa que nos pasan como argumento
    if (system(cmd) == -1) {
        printf("ERROR\n");
    }

    printf("El comando terminó de ejecutarse.\n");


    return 0;
}