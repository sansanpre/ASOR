/**
 * INFORMACIÓN HORARIA DEL SISTEMA - EJERCICIO 15
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
 * size_t strftime(char *s, size_t max, const char *format, const struct tm *tm);
 *                             --> formats the broken-down time tm according to the format specification 
 *                                 format and places the result in the character array s of size max.
 * 
**/

int main() {

    time_t t = time(NULL);
    struct tm *timedata = localtime(&t);

    //Incluimos
    char hora[100];

    // %A: The full name of the day of the week according to the current locale.
    // %H: The hour as a decimal number using a 24-hour clock (range 00 to 23).
    // %M: The minute as a decimal number (range 00 to 59). 
    // %B: The full month name according to the current locale.
    // %Y: The year as a decimal number including the century.
    strftime(hora, 100, "%A, %d de %B de %Y, %H:%M", timedata);
    // %d: The day of the month as a decimal number (range 01 to 31). 

    printf("Hoy estamos a %s\n", hora);

	return 1;
}