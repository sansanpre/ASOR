// GLORIA PORTO Y SANDRA SÁNCHEZ
/*
Ejercicio 1. 
Escribir un programa que emule el comportamiento de la shell en la ejecución de una sentencia en la forma: comando1 argumento1 | comando2 argumento2. 
El programa creará una tubería sin nombre y creará un hijo:
    · El proceso padre redireccionará la salida estándar al extremo de escritura de la tubería y ejecutará comando1 argumento1.
    · El proceso hijo redireccionará la entrada estándar al extremo de lectura de la tubería y ejecutará comando2 argumento2.
Probar el funcionamiento con una sentencia similar a: ./ejercicio1 echo 12345 wc -c
Nota: Antes de ejecutar el comando correspondiente, deben cerrarse todos los descriptores no necesarios.
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	
    // creamos la tuberia sin nombre
    int fd[2];

    // comprobamos que se ha creado bien
    if(pipe(fd)==-1){
        perror("Error\n");
    }

    // creamos el hijo
    pid_t pid=fork();


    switch(pid){
        // caso error:
        case -1: 
            perror("fork");
            return 1;
        break;

        // caso proceso hijo:
        case 0:
            dup2(fd[0],0);                                  // cambiamos el descriptor de la entrada
            close(fd[0]);                       
            close(fd[1]);                         
            execlp(argv[3], argv[3], argv[4]), NULL;        // ejecutamos comando 2 argumento 2   
        break;
       
        // caso padre
        default:
            dup2(fd[1],1);                                  // cambiamos el descriptor de la salida
            close(fd[0]);                           
            close(fd[1]);                           
            execlp(argv[1], argv[1], argv[2], NULL);        // ejecutamos comando 1 argumento 1  
        break;
    }
   return 0;
}
