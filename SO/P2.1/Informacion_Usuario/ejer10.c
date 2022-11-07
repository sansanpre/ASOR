/**
 * INFORMACIÓN DEL USUARIO - EJERCICIO 10
 *      Modificar el programa anterior para que muestre además el nombre de usuario, 
 *      el directorio home y la descripción del usuario.
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
//Includes de la pagina de manual de getpwuid(3)
#include <pwd.h>

/**En este ejercicio, utilizaremos:
 *  uid_t getuid(void);   -->  returns the real user ID of the calling process.                                           
 *  uid_t geteuid(void);  -->  returns the effective user ID of the calling process.
 *  struct passwd *getpwuid(uid_t uid); 
 *                        -->  function returns a pointer to a structure containing the broken-out fields 
 *                              of the record in the password database that matches the user ID uid.
 * 
**/

int main() {

    uid_t uid = getuid();   // ID real del usuario
    uid_t uide = geteuid(); // ID efectivo del usuario 

    printf("UID Real del Usuario: %d\n", uid);
    printf("UID Efectivo del Usuario: %d\n", uide);

    //Para mostrar:
    struct passwd *s = getpwuid(uid);

    char *username = s->pw_name;
    char *home_dir = s->pw_dir;
    char *user_info = s->pw_gecos;

    printf("Nombre de Usuario: %s\n", username);
    printf("Directorio Home: %s\n", home_dir);
    printf("Info: %s\n",user_info);
    
    return 1;
}