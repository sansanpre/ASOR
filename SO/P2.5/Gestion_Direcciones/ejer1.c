/**     PRACTICA 2.5
 * GESTIÓN DE DIRECCIONES - EJERCICIO 1
 *  Escribir un programa que obtenga todas las posibles direcciones con las que se podría 
 *  crear un socket asociado a un host dado como primer argumento del programa. 
 *  Para cada dirección, mostrar la IP numérica, la familia de protocolos y tipo de socket. 
 *  Comprobar el resultado para:
 *      ● Una dirección IPv4 válida (ej. “147.96.1.9”).
 *      ● Una dirección IPv6 válida (ej. “fd00::a:0:0:0:1”).
 *      ● Un nombre de dominio válido (ej. “www.google.com”).
 *      ● Un nombre en /etc/hosts válido (ej. “localhost”).
 *      ● Una dirección o nombre incorrectos en cualquiera de los casos anteriores.
 *  El programa se implementará usando getaddrinfo(3) para obtener la lista de posibles direcciones 
 *  de socket (struct sockaddr). Cada dirección se imprimirá en su valor numérico, 
 *  usando getnameinfo(3) con el flag NI_NUMERICHOST, así como la familia de direcciones y el tipo de socket.
**/

//Includes de la pagina de manual de getaddrinfo(3)
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
//Includes de la pagina de manual de perror(3)
#include <errno.h>
#include <string.h>

/**En este ejercicio, utilizaremos:
 *   int getaddrinfo(const char *restrict node,
                       const char *restrict service,
                       const struct addrinfo *restrict hints,
                       struct addrinfo **restrict res);  ->  Given node and service, which identify an Internet host and a
                                                            service, getaddrinfo() returns one or more addrinfo structures,
                                                            each of which contains an Internet address that can be specified
                                                            in a call to bind(2) or connect(2).                                      
 * 
**/

int main(int argc, char **argv) {

   //Gestionamos los errores
    if (argc < 2 == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		return -1;
	}

    struct addrinfo hints, *result, *rp;
    int sfd, s;

    char host[NI_MAXHOST];

    //Inicializar Filtro: 
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = 0;          /* Socket addresses of any type can be returned */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    s = getaddrinfo(argv[1], NULL, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    /* getaddrinfo() returns a list of address structures.
              Try each address until we successfully bind(2).
              If socket(2) (or bind(2)) fails, we (close the socket
              and) try the next address. */

    for (rp = result; rp != NULL; rp = rp->ai_next) {

        /* Obtener la información a partir del host numérico. */
		getnameinfo(rp->ai_addr, rp->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
		printf("Dirección: %s (familia %d; tipo %d)\n", host, rp->ai_family, rp->ai_socktype);

    }

    freeaddrinfo(result);     /* No longer needed */

  	return 0;
}