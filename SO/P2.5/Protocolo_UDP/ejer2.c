/**     PRACTICA 2.5
 * PROTOCOLO UDP - EJERCICIO 2
 * Escribir un servidor UDP de hora de forma que:
 *      ● La dirección y el puerto son el primer y segundo argumento del programa. 
 *          Las direcciones pueden expresarse en cualquier formato (nombre de host, notación de punto…). 
 *          Además, el servidor debe funcionar con direcciones IPv4 e IPv6 .
 *      ● El servidor recibirá un comando (codificado en un carácter), de forma que ‘t’ devuelva la hora, 
 *          ‘d’ devuelve la fecha y ‘q’ termina el proceso servidor.
 *      ● En cada mensaje el servidor debe imprimir el nombre y puerto del cliente, usar getnameinfo(3).
 * 
 * Probar el funcionamiento del servidor con la herramienta Netcat (comando nc o ncat) como cliente.
 *  
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
//Includes de la pagina de manual de time(2)
#include <sys/time.h>
#include <time.h>


/**En este ejercicio, utilizaremos:
 * int getaddrinfo(const char *restrict node,
                       const char *restrict service,
                       const struct addrinfo *restrict hints,
                       struct addrinfo **restrict res);
 *                                       
 * int socket(int domain, int type, int protocol);
**/

int main(int argc, char **argv) {

   //Gestionamos los errores
    if (argc < 2 == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		return -1;
	}

    struct addrinfo hints, *result, *rp;
    int sfd, s;

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

    //Creamos el socket
    int UDPsocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (UDPsocket == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
        exit(EXIT_FAILURE);
    }

    //Asociamos el socket a la direccion
    if (bind(UDPsocket, result->ai_addr, result->ai_addrlen) == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);

    /* Estructuras auxiliares */
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    char datos[3];

    struct sockaddr_storage client_addr;
    socklen_t client_addrlen = sizeof(client_addr);

   
	size_t time_bytes;
	struct tm *tm;
	char msg[129];

    //Recepción de datos
    while (1){
        ssize_t l = recvfrom(UDPsocket, datos, 2, 0, (struct sockaddr *) &client_addr, &client_addrlen);
        datos[l - 1] = '\0';

        /* Convertir la dirección de socket a un host y un servicio. */
		getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
		
        printf("Se han recibido %ld bytes desde host %s y servicio %s: %s\n", l, host, service, datos);

		
		/* Tiempo y Respuesta */
		time_t t = time(NULL);
		tm = localtime(&t);

        switch (datos[0]){
            case 't':
                time_bytes = strftime(msg, 128, "%T", tm);
                msg[time_bytes] = '\n';
                msg[time_bytes + 1] = '\0';
                
                if (sendto(UDPsocket, msg, time_bytes + 2, 0, (struct sockaddr *) &client_addr, client_addrlen) == -1) {
                    printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
                    exit(EXIT_FAILURE);
                }

                break;
            
            case 'd':
                time_bytes = strftime(msg, 128, "%F", tm);
                msg[time_bytes] = '\n';
                msg[time_bytes + 1] = '\0';
                
                if (sendto(UDPsocket, msg, time_bytes + 2, 0, (struct sockaddr *) &client_addr, client_addrlen) == -1) {
                    printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
                    exit(EXIT_FAILURE);
                }

                break;

            case 'q':
                printf("Saliendo del programa...\n");
                exit(EXIT_SUCCESS);
                break;


            default:
                printf("Prueba otro comando (comando no soportado): %s\n", datos);
                break;
        }

    }

  	return 0;
}