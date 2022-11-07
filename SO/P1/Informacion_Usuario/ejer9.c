/**
 * INFORMACIÓN DEL USUARIO - EJERCICIO 9
 *      Escribir un programa que muestre, igual que id, el UID real y efectivo del usuario. 
 *      ¿Cuándo podríamos asegurar que el fichero del programa tiene activado el bit setuid?
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

/**En este ejercicio, utilizaremos:
 *  uid_t getuid(void);   -->  returns the real user ID of the calling process.                                           
 *  uid_t geteuid(void);  -->  returns the effective user ID of the calling process.
 * 
**/

int main() {

    uid_t uid = getuid();   // ID real del usuario
    uid_t uide = geteuid(); // ID efectivo del usuario 

    printf("UID Real del Usuario: %d\n", uid);
    printf("UID Efectivo del Usuario: %d\n", uide);
    
    return 1;
}

/** EL bit setuid es asignable a ficheros ejecutables, y permite que cuando un usuario 
 *  ejecute dicho fichero, el proceso adquiera los permisos del propietario del fichero ejecutado
 * 
 *      Podríamos comprobar que el fichero del programa tiene activado el bit setuid:
 *          # ls -l ejer9.c  (y comprobamos permisos)
 * 
*/