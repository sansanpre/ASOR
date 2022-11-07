/**
 * INFORMACIÓN DEL SISTEMA - EJERCICIO 5
 *      Escribir un programa que muestre, con uname(2), cada aspecto del sistema 
 *      y su valor. Comprobar la correcta ejecución de la llamada.
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

/**En este ejercicio, utilizaremos uname(2) para obtener la información del sistema                                                    
 *  int uname(struct utsname *buf); ->  returns system information in the structure pointed to by buf.
 *      
 * Return Value uname():  0 = success
 *                        -1 = error
**/
int main() {

    struct utsname sis_info; //Struct con la información del sistema
    
    //En caso de error, gestionamos el error generado por uname con strerror
    if(uname(&sis_info) == -1){ 
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
    }
    else{
        //Imprimimos por pantalla la info del sistema
        printf("Nombre del Sistema: %s\n", sis_info.sysname);
        printf("Nodename: %s\n", sis_info.nodename);
        printf("Release: %s\n", sis_info.release);
        printf("Version: %s\n", sis_info.version);
        printf("Machine: %s\n", sis_info.machine);
    }

    return 1;
}