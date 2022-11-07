/**
 * GESTIÓN DE ERRORES - EJERCICIO 2
 *      Imprimir el código numérico de error generado por 
 *      la llamada del código anterior y el mensaje asociado.
 * 
**/

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
    
    //En caso de error, gestionamos el error generado por setuid con strerror
    if(setuid(0) == -1){ 
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla
    }
    
    return 1;
}