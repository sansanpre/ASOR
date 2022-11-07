/**
 * GESTIÓN DE ERRORES - EJERCICIO 3
 *      Escribir un programa que imprima todos los mensajes de error disponibles en el sistema. 
 *      Considerar inicialmente que el límite de errores posibles es 255.
 * 
**/

const int MAX_ERROR = 255; //Limite de errores posibles

//Includes de la pagina de manual de setuid(2)
#include <sys/types.h> 
#include <unistd.h> 
//Includes de la pagina de manual de perror(3)
#include <stdio.h> 
#include <errno.h>
//Includes de la pagina de manual de strerror(3)
#include <string.h>

/**En este ejercicio, utilizaremos strerror(3) para gestionar el error
 *   char *strerror(int errnum); -->  returns a pointer to a string that describes 
 *                                    the error code passed in the argument errnum
 * 
**/
int main() {
    //Recorremos todos los errores posibles
    for (int i = 0; i < MAX_ERROR; i++){
        printf("ERROR(%d): %s\n", i, strerror(i)); //Imprimimos por pantalla el error i
    }
    
    return 1;
}