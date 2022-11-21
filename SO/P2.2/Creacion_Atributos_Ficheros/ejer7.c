/**     PRACTICA 2.2
 * CREACIÓN Y ATRIBUTOS DE FICHEROS - EJERCICIO 7
 *      
**/

#include <stdio.h> 
//Includes de la pagina de manual de open(2)
#include <fcntl.h>
//Includes de la pagina de manual de perror(3)
#include <errno.h>
//Includes de la pagina de manual de strerror(3)
#include <string.h>
//Includes de la pagina de manual de umask()
#include <sys/stat.h>


/**En este ejercicio, utilizaremos:
 *  mode_t umask(mode_t mask);  -->  sets the calling process's file mode creation mask(umask) to mask                                          
 * 
**/


int main() {

    const char *pathname = "./ejer6.txt";

    mode_t mask = umask(640);

    //Traducimos los permisos rw-r--r-x a octal --> 0645
    int descriptor_fichero = open(pathname, O_CREAT, mask);

    if(descriptor_fichero == -1){
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
    }
    else{
        //Imprimimos por pantalla el descriptor
        printf("El descriptor del nuevo fichero es: %d\n", descriptor_fichero);
    }

	return 0;
}
