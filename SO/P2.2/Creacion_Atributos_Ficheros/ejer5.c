/**     PRACTICA 2.2
 * CREACIÓN Y ATRIBUTOS DE FICHEROS - EJERCICIO 5
 *      Escribir un programa que, usando open(2), cree un fichero con los permisos rw-r--r-x. 
 *      Comprobar el resultado y las características del fichero con ls(1).
 * 
 *      Para ello usamos:
 *          int open(const char *pathname, int flags, mode_t mode); --> open and possibly create a file
**/

#include <stdio.h> 
//Includes de la pagina de manual de open(2)
#include <fcntl.h>
//Includes de la pagina de manual de perror(3)
#include <errno.h>
//Includes de la pagina de manual de strerror(3)
#include <string.h>

int main() {

    const char *pathname = "./ejer5.txt";

    //Traducimos los permisos rw-r--r-x a octal --> 0645
    int descriptor_fichero = open(pathname, O_CREAT, 0645);

    if(descriptor_fichero == -1){
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
    }
    else{
        //Imprimimos por pantalla el descriptor
        printf("El descriptor del nuevo fichero es: %d\n", descriptor_fichero);
    }

	return 0;
}

