/**
 * INFORMACIÓN HORARIA DEL SISTEMA - EJERCICIO 12
 *      Escribir un programa que muestre la hora, en segundos desde el Epoch, usando time(2). 
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
//Includes de la pagina de manual time(2)
 #include <time.h>

/**En este ejercicio, utilizaremos:
 *  time_t time(time_t *tloc);  -->  returns the time as the number of seconds 
 *                                   since the Epoch, 1970-01-01 00:00:00 +0000 (UTC).                                           
 *  
 * 
**/
int main() {

	time_t hora = time(NULL);

	printf("Seconds since 1970-01-01 00:00:00 +0000 (UTC): %li\n", hora);

	return 1;
}