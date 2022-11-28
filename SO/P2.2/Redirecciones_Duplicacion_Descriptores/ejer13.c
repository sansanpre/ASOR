/**     PRACTICA 2.2
 * REDIRECCIONES Y DUPLICACIONES DE DESCRIPTORES - EJERCICIO 13
 *  Modificar el programa anterior para que también redirija la salida estándar de error al fichero. 
 *  Comprobar el funcionamiento incluyendo varias sentencias que impriman en ambos flujos. 
 *  ¿Hay diferencia si las redirecciones se hacen en diferente orden? 
 *  ¿Por qué ls > dirlist 2>&1 es diferente a ls 2>&1 > dirlist?
 *  
**/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysmacros.h>
#include <stdlib.h>

//Includes de la pagina de manual de strerror(3)
#include <string.h>
//Includes de la pagina de manual de perror(3)
#include <errno.h>
//Includes de la pagina de manual de stat(2)
#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>

/**En este ejercicio, utilizaremos:
 *  int dup(int oldfd); --> allocates a new file descriptor that refers
 *                          to the same open file description as the descriptor oldfd.
 *  int dup2(int oldfd, int newfd); --> performs the same task as dup(), but
 *                                      instead of using the lowest-numbered unused file descriptor, it
 *                                      uses the file descriptor number specified in newfd.
 *                                      
**/

int main(int argc, char **argv) {

   //Gestionamos los errores
    struct stat datos;
    if (argc < 2 || stat(argv[1], &datos) == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		return -1;
	}
    //Obtenemos el descriptor de fichero del archivo
    int oldfd = open(argv[1], O_CREAT | O_RDWR, 00777);
    if (oldfd == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
        return -1;
    }

    //Nuevo descriptor de fichero
    int newfd1 = dup2(oldfd, 1);
    int newfd2 = dup2(oldfd, 2);
    if (newfd1== -1 || newfd2 == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
        return -1;
    }
    else{
        printf("La salida estándar se ha reedirigido a %s\n", argv[1]);
        printf("Olee nos ha salido el ejercicio\n");
        printf("Rubén rulate un 10\n");
        dup2(newfd1, oldfd);
        dup2(newfd2, oldfd);
    }
    close(oldfd);

	return 0;
}

/**
 * ¿Hay diferencia si las redirecciones se hacen en diferente orden? 
 * ¿Por qué ls > dirlist 2>&1 es diferente a ls 2>&1 > dirlist?
 * 
 * Usando el símbolo & podemos distinguir los archivos normales de los descriptores especiales: 
 *      1 es un archivo llamado 1 
 *      y &1 es el descriptor de la salida estándar (stdout).
 * Por todo esto, redirigir los errores a la salida normal se indica como 2>&1
 * 
 * Si usamos ls > dirlist 2> &1: redirige la salida normal al un fichero dilist
 * 
 * El contenido no cambia
 * 
 * **/