/**
 * INFORMACIÓN HORARIA DEL SISTEMA - EJERCICIO 13
 *      Escribir un programa que mida, en microsegundos, 
 *      lo que tarda un bucle que incrementa una variable un millón de veces usando gettimeofday(2).
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
 *  int gettimeofday(struct timeval *tv, struct timezone *tz);
 *                              -->  can get the time as well as a timezone.
 * 
**/
int main() {
    
    struct timeval tv; //El programa empieza
    int p1 = gettimeofday(&tv, NULL); 
    int ini = tv.tv_usec; //Obtenemos el tiempo del día en microsegundos

    //Incrementamos variable 1M de veces
    for (int i = 0; i < 1000000; i++);

    //Obtenemos el tiempo que tarda el bucle
    int p2 = gettimeofday(&tv, NULL);
    int fin = tv.tv_usec;

    printf("El bucle ha tardado (ms): %i\n", fin - ini);

    return 1;
}
