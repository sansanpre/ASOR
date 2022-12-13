// GLORIA PORTO Y SANDRA SÁNCHEZ
/*
Ejercicio 4. 
Escribir un programa que abra la tubería con el nombre anterior en modo sólo escritura, 
y escriba en ella el primer argumento del programa. En otro terminal, leer de la tubería usando un comando adecuado.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv){

  	mkfifo(tuberia, 0777); // si ya la creamos en el ejer 3, ignora el error

	int fd = open("./tuberia", O_WRONLY);

    write(fd, argv[1], sizeof(argv[1]));
    close(fd); 

  return 0;
}