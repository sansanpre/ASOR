/**     PRACTICA 2.5
 * PROTOCOLO UDP - EJERCICIO 4
 * Modificar el servidor para que, además de poder recibir comandos por red, 
 * los pueda recibir directamente por el terminal, leyendo dos caracteres (el comando y ‘\n’) 
 * de la entrada estándar. Multiplexar el uso de ambos canales usando select(2).
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

#define BUFFER_SIZE 2
#define MESSAGE_SIZE 128

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

   //Estructuras necesarias
	struct addrinfo hints;
	struct addrinfo *result;

	memset(&hints, 0, sizeof(struct addrinfo));
	
	hints.ai_family 	= AF_UNSPEC;
	hints.ai_socktype 	= SOCK_DGRAM;
	hints.ai_flags 		= AI_PASSIVE;
	hints.ai_protocol 	= 0;
	hints.ai_canonname 	= NULL;
	hints.ai_addr 		= NULL;
	hints.ai_next 		= NULL;
	
	int s = getaddrinfo(argv[1], argv[2], &hints, &result);
	
	//Gestionamos errores
	if (s != 0){
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		exit(EXIT_FAILURE);
	}
	
	int UDPsocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	
	if (UDPsocket == -1){
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error

		exit(EXIT_FAILURE);
	}
	
	if (bind(UDPsocket, result->ai_addr, result->ai_addrlen) == -1){
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		exit(EXIT_FAILURE);
	}
	
	freeaddrinfo(result);
	
	//Almacenamos direccion de cliente
	struct sockaddr_storage client_addr;
	socklen_t client_addrlen = sizeof(client_addr);
	
	//CLIENTE
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	
	char datos[BUFFER_SIZE + 1];
	
	ssize_t l;
	time_t t;
	size_t time_bytes;
	struct tm *tm;
	char msg[MESSAGE_SIZE + 1];

	fd_set set;
	
	while (1){
		FD_ZERO(&set);
		FD_SET(0, &set); 		
		FD_SET(UDPsocket, &set); 

		int cambio = select(UDPsocket + 1, &set, NULL, NULL, NULL);
		if (cambio == -1){
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
			exit(EXIT_FAILURE);
		}

		if (FD_ISSET(0, &set)){
			int bytes = read(0, datos, BUFFER_SIZE);
			printf("Se han recibido %d bytes desde la entrada estándar\n", bytes);
		}
		else{
			/* Recibir datos desde el cliente. */
			/* Como la dirección está vacía, recibe desde cualquiera. */
			l = recvfrom(UDPsocket, datos, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &client_addrlen);
			datos[l - 1] = '\0';
			
			/* Convertir la dirección de socket a un host y un servicio. */
			getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
			printf("Recibidos %ld bytes desde servicio %s y host %s: %s\n", l, service, host, datos);
		}
		
		/* Preparar la respuesta. */
		t = time(NULL);
		tm = localtime(&t);
		
		/* Comprobar comando. */
		if (datos[0] == 't'){
			time_bytes = strftime(msg, MESSAGE_SIZE, "%T", tm);
			msg[time_bytes] = '\n';
			msg[time_bytes + 1] = '\0';
			
			if (FD_ISSET(0, &set)){
				printf("%s\n", msg);
			}
			else{
				if (sendto(UDPsocket, msg, time_bytes + 2, 0, (struct sockaddr *) &client_addr, client_addrlen) == -1){
					printf("sendto()\n");
					exit(EXIT_FAILURE);
				}
			}
		}
		else if (datos[0] == 'd'){
			time_bytes = strftime(msg, MESSAGE_SIZE, "%F", tm);
			msg[time_bytes] = '\n';
			msg[time_bytes + 1] = '\0';
			
			if (FD_ISSET(0, &set)){
				printf("%s\n", msg);
			}
			else{
				if (sendto(UDPsocket, msg, time_bytes + 2, 0, (struct sockaddr *) &client_addr, client_addrlen) == -1){
					printf("sendto()\n");
					exit(EXIT_FAILURE);
				}
			}
		}
		else if (datos[0] == 'q'){
			printf("Salida del sistema\n");			
			exit(EXIT_SUCCESS);
		}
		else{
			printf("Comando no encontrado: %s\n", datos);
		}
	}

  	return 0;
}