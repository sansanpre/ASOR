/**
 * INFORMACIÓN DEL SISTEMA - EJERCICIO 7
 *      Escribir un programa que obtenga, con pathconf(3), información de configuración 
 *      del sistema de ficheros e imprima, por ejemplo, el número máximo de enlaces, 
 *      el tamaño máximo de una ruta y el de un nombre de fichero.
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
 *  long pathconf(const char *path, int name); -->  gets a value for configuration option name for the filename path.
 *      
 * Return Value sysconf():  -1 = error
 * 
**/

int main() {

    const char *path = "."; //Utilizamos como path el directorio raiz

    //En caso de error, gestionamos el error generado por pathconf con strerror
    if(pathconf(path, _PC_LINK_MAX) == -1){ 
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
    }
    else{
        //Imprimimos por pantalla la info del sistema
        printf("Número máximo de enlaces: %li\n", pathconf(path, _PC_LINK_MAX));
    }
    if(pathconf(path, _PC_PATH_MAX)== -1){ 
        printf("ERROR(%d): %s\n", errno, strerror(errno)); 
    }
    else{
	    printf("Tamaño máximo de una ruta: %li\n", pathconf(path, _PC_PATH_MAX));
    }
    if(pathconf(path, _PC_NAME_MAX) == -1){ 
        printf("ERROR(%d): %s\n", errno, strerror(errno)); 
    }
    else{
	    printf("Nombre de un fichero: %li\n", pathconf(path, _PC_NAME_MAX) );
    }
    
    return 1;
}