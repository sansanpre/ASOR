/**     PRACTICA 2.5
 * PROTOCOLO UDP - EJERCICIO 3
 * Escribir el cliente para el servidor de hora. 
 * El cliente recibirá como argumentos la dirección del servidor, el puerto del servidor y el comando. 
 * Por ejemplo, para solicitar la hora, ./time_client 192.128.0.1 3000 t.
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

#define BUFFER_SIZE 128

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

	int s = getaddrinfo(argv[1], argv[2], & hints, & result);
	if (s != 0){
		printf("Error: getaddrinfo(): %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}
	
	//Creamos el socket
	int UDPsocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (UDPsocket == -1){
		perror("Error: socket()\n");
		exit(EXIT_FAILURE);
	}
	
	//Enviamos el comando
	ssize_t send_result = sendto(UDPsocket, argv[3], sizeof(argv[3]), 0, result->ai_addr, result->ai_addrlen);
	if (send_result == -1){
		perror("Error: sendto()\n");
		exit(EXIT_FAILURE);
	}
	
	//Respuesta
	if (argv[3][0] == 't' || argv[3][0] == 'd'){
		//Almacenamos direccion de cliente
		struct sockaddr_storage client_addr;
		socklen_t client_addrlen = sizeof(client_addr);
		
		char datos[BUFFER_SIZE + 1];
		
		//Se recibe la respuesta
		ssize_t recv_result = recvfrom(UDPsocket, datos, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &client_addrlen);
		if (recv_result == -1){
			perror("Error: recvfrom()\n");
			exit(EXIT_FAILURE);
		}
		
		datos[recv_result] = '\0';
		
		printf("Respuesta: %s\n", datos);
	}

  	return 0;
}