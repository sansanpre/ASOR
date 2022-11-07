/**
 * INFORMACIÓN DEL SISTEMA - EJERCICIO 6
 *      Escribir un programa que obtenga, con sysconf(3), información de configuración del sistema 
 *      e imprima, por ejemplo, la longitud máxima de los argumentos, el número máximo de hijos 
 *      y el número máximo de ficheros abiertos
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
//Includes de la pagina de manual de uname(2)
#include <sys/utsname.h> 
#include <stdlib.h>

/**En este ejercicio, utilizaremos sysconf(3) para obtener la información del sistema                                                    
 *  long sysconf(int name); -->  The values obtained from these functions are system configuration constants.  
 *                               They do not change during the lifetime of a process.
 *      
 * Return Value sysconf():  -1 = error
 *                         
**/

int main() {

    
    //En caso de error, gestionamos el error generado por sysconf con strerror
    if(sysconf(_SC_ARG_MAX) == -1){ 
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
    }
    else{
        //Imprimimos por pantalla la info del sistema
        printf("Longitud máxima de los argumentos: %li\n", sysconf(_SC_ARG_MAX));
    }
    if(sysconf(_SC_CHILD_MAX) == -1){ 
        printf("ERROR(%d): %s\n", errno, strerror(errno)); 
    }
    else{
	    printf("Número máximo de hijos: %li\n", sysconf(_SC_CHILD_MAX));
    }
    if(sysconf(_SC_OPEN_MAX) == -1){ 
        printf("ERROR(%d): %s\n", errno, strerror(errno)); 
    }
    else{
	    printf("Número máximo de ficheros abiertos: %li\n", sysconf(_SC_OPEN_MAX));
    }
    
    return 1;
}