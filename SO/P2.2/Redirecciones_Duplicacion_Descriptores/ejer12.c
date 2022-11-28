/**     PRACTICA 2.2
 * REDIRECCIONES Y DUPLICACIONES DE DESCRIPTORES - EJERCICIO 12
 *  Escribir un programa que redirija la salida estándar a un fichero cuya ruta se pasa como primer argumento. 
 *  Probar haciendo que el programa escriba varias cadenas en la salida estándar.
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
    int newfd = dup2(oldfd, 1);
    if (newfd == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
        return -1;
    }
    else{
        printf("La salida estándar se ha reedirigido a %s\n", argv[1]);
        printf("Olee nos ha salido el ejercicio\n");
        printf("Rubén rulate un 10\n");

        dup2(newfd, oldfd);
    }
    close(oldfd);

	return 0;
}