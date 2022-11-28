/**     PRACTICA 2.2
 * CERROJOS DE FICHEROS - EJERCICIO 15
 *  Escribir un programa que intente bloquear un fichero usando lockf(3):
 *      ● Si lo consigue, mostrará la hora actual y suspenderá su ejecución durante 10 segundos con sleep(3). 
 *        A continuación, desbloqueará el fichero, suspenderá su ejecución durante otros 10 segundos y terminará.
 *      ● Si no lo consigue, el programa mostrará el error con perror(3) y terminará.
 *
 *  
**/


#include <stdio.h>
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
//Includes de la pagina de manual time(2)
 #include <time.h>
 #include <sys/time.h>

/**En este ejercicio, utilizaremos:
 *  int lockf(int fd, int cmd, off_t len); --> Apply, test, or remove a POSIX lock on a section of an open file.
 *      F_LOCK: Set an exclusive lock on the specified section of the file.
 *      F_ULOCK: Unlock the indicated section of the file.
**/

int main(int argc, char **argv) {

   //Gestionamos los errores
    if (argc < 2 == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		return -1;
	}
    //Obtenemos el descriptor de fichero del archivo
    int fd = open(argv[1], O_CREAT | O_RDWR, 00777);
    if (fd == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
        return -1;
    }

    if(lockf(fd, F_LOCK, 0) == -1){
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		return -1;
    }
    //Obtenemos hora actual
     time_t t = time(NULL);
    struct tm *timedata = localtime(&t);
    char hora[100];
    strftime(hora, 100, "%A, %d de %B de %Y, %H:%M", timedata);
    printf("Hoy estamos a %s\n", hora);

    //Espera 10 segundos
    sleep(3);
    
    if(lockf(fd,F_ULOCK,0) ==-1 ){
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		return -1;
    }
    //Espera 10 segundos
    sleep(3);

    close(fd);   

	return 0;
}
