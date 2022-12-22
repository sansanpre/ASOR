/**     PRACTICA 2.5
 * PROTOCOLO TCP - EJERCICIO 6
 * Crear un servidor TCP de eco que escuche por conexiones entrantes en una dirección (IPv4 o IPv6) y puerto dados. 
 * Cuando reciba una conexión entrante, debe mostrar la dirección y número de puerto del cliente. 
 * A partir de ese momento, enviará al cliente todo lo que reciba desde el mismo (eco). 
 * Comprobar su funcionamiento empleando la herramienta Netcat como cliente. 
 * Comprobar qué sucede si varios clientes intentan conectar al mismo tiempo.
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

#define SOCKET_BACKLOG 5
#define BUFFER_LEN 128

int main(int argc, char **argv){
	//Gestionamos los errores
    if (argc < 2 == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		return -1;
	}
	
	struct addrinfo hints;
	struct addrinfo * result;
	
	memset(& hints, 0, sizeof(struct addrinfo));
	
	hints.ai_family 	= AF_UNSPEC;
	hints.ai_socktype 	= SOCK_STREAM;
	hints.ai_flags 		= AI_PASSIVE;
	hints.ai_protocol 	= 0;
	hints.ai_addrlen 	= 0;
	hints.ai_addr 		= NULL;
	hints.ai_canonname 	= NULL;
	hints.ai_next 		= NULL;
	
	int info_result = getaddrinfo(argv[1], argv[2], &hints, &result);
	if (info_result != 0){
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		exit(EXIT_FAILURE);
	}
	
	
	int TCPsocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (TCPsocket == -1){
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		exit(EXIT_FAILURE);
	}
	
	int bind_result = bind(TCPsocket, result->ai_addr, result->ai_addrlen);
	if (bind_result == -1){
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		exit(EXIT_FAILURE);
	}
	
	freeaddrinfo(result);
	
	int listen_result = listen(TCPsocket, SOCKET_BACKLOG);
	
	if (listen_result == -1){
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		exit(EXIT_FAILURE);
	}
	
	struct sockaddr_storage client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	int client_sd;
	int gni_result;
	char client_host[NI_MAXHOST];
	char client_service[NI_MAXSERV];
	ssize_t recv_len;
	ssize_t send_len;
	char client_buffer[BUFFER_LEN + 1];
	
	while (1){
		client_sd = accept(TCPsocket, (struct sockaddr *) &client_addr, &client_addr_len);
		if (client_sd == -1){
            printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
			exit(EXIT_FAILURE);
		}
		
		gni_result = getnameinfo((struct sockaddr *) &client_addr, client_addr_len, client_host, NI_MAXHOST, client_service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
		if (gni_result != 0){
            printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
			exit(EXIT_FAILURE);
		}
		
		printf("Se establece conexión desde %s:%s\n", client_host, client_service);
		
		while (1){
			recv_len = recv(client_sd, client_buffer, BUFFER_LEN, 0);
			if (recv_len == -1){
                printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
				exit(EXIT_FAILURE);
			}
			else if (recv_len == 0)	{
				break;
			}
			
			send_len = send(client_sd, client_buffer, strlen(client_buffer), 0);
			if (send_len == -1){
                printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
				exit(EXIT_FAILURE);
			}
			
			memset(client_buffer, 0, BUFFER_LEN);
		}
		
		printf("La conexión ha terminado\n");
	}

	return 0;
}