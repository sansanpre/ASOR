/**
 * INFORMACIÓN HORARIA DEL SISTEMA - EJERCICIO 14
 *      Escribir un programa que muestre el año usando localtime(3).
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
 #include <sys/time.h>

/**En este ejercicio, utilizaremos:
 * time_t time(time_t *tloc);  -->  returns the time as the number of seconds 
 *                                   since the Epoch, 1970-01-01 00:00:00 +0000 (UTC).
 *  struct tm *localtime(const time_t *timep); 
 *                             --> take an argument of data type time_t, which represents calendar time.
 * 
**/

int main() {

    time_t t = time(NULL);

    int year = localtime(&t)->tm_year;   /* Year - 1900 */

	printf("Estamos en el año: %li\n", 1900 + year);

	return 1;
}