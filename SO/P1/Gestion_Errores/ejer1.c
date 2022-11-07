/**
 * GESTIÓN DE ERRORES - EJERCICIO 1
 *      Añadir el código necesario para gestionar correctamente los errores generados por setuid(2). 
 *      Consultar en el manual el propósito de la llamada y su prototipo.
 * 
 *      Return Value setuid():  0 = success
 *                              -1 = error
 * 
**/

//Includes de la pagina de manual de setuid(2)
#include <sys/types.h> 
#include <unistd.h> 
//Includes de la pagina de manual de perror(3)
#include <stdio.h> 
#include <errno.h>

/**En este ejercicio, utilizaremos perror(3) para gestionar el error
 *   void perror(const char *s); --> produces a message on standard error describing the last error 
 *                                   encountered during a call to a system or library function.
 * 
**/
int main() {
    char *s; 
    //En caso de error, gestionamos el error generado por setuid con perror
    if(setuid(0) == -1){ 
        perror(s);
    }
    
    return 1;
}
