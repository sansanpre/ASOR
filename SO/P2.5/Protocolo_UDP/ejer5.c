/**     PRACTICA 2.5
 * PROTOCOLO UDP - EJERCICIO 5
 * Convertir el servidor UDP en multi-proceso siguiendo el patrón pre-fork. 
 * Una vez asociado el socket a la dirección local con bind(2), crear varios procesos que llamen a recvfrom(2) 
 * de forma que cada uno atenderá un mensaje de forma concurrente. 
 * Imprimir el PID del proceso servidor para comprobarlo. Para terminar el servidor, 
 * enviar la señal SIGTERM al grupo de procesos.
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

void gestionarMensajes(int UDPsocket){
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
	
	while (1){
		l = recvfrom(UDPsocket, datos, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &client_addrlen);
		datos[l - 1] = '\0';
		
		//Convertir direccion socket
		getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
		printf("Recibidos %ld bytes desde host %s y servicio %s: %s\n", l, host, service, datos);
		
		t = time(NULL);
		tm = localtime(&t);
		
        switch (datos[0]){
            case 't':
                time_bytes = strftime(msg, MESSAGE_SIZE, "%T", tm);
                msg[time_bytes] = '\n';
                msg[time_bytes + 1] = '\0';
                
                if (sendto(UDPsocket, msg, time_bytes + 2, 0, (struct sockaddr *) &client_addr, client_addrlen) == -1){
                    printf("sendto()\n");
                    exit(EXIT_FAILURE);
                }

                break;
            
            case 'd':
                time_bytes = strftime(msg, MESSAGE_SIZE, "%F", tm);
                msg[time_bytes] = '\n';
                msg[time_bytes + 1] = '\0';
                
                if (sendto(UDPsocket, msg, time_bytes + 2, 0, (struct sockaddr *) &client_addr, client_addrlen) == -1){
                    printf("sendto()\n");
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
}

int main(int argc, char **argv){
	//Gestionamos los errores
    if (argc < 2 == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		return -1;
	}

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
	
	if (s != 0)	{
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		exit(EXIT_FAILURE);
	}
	
	int UDPsocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (UDPsocket == -1){
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		exit(EXIT_FAILURE);
	}
	
	if (bind(UDPsocket, result->ai_addr, result->ai_addrlen) == -1)	{
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		exit(EXIT_FAILURE);
	}
	
	freeaddrinfo(result);
	
	printf("Escuchando...\n");
	
	for (int i = 0; i < 5; i++)	{
		pid_t pid = fork();

		switch(pid)		{
			case -1:
				return 1;
			case 0:
				gestionarMensajes(UDPsocket);
				return 0;
			default:
				break;
		}
	}

	for (int i = 0; i < 5; i++)	{
		int hijo = wait(NULL);

		printf("HIJO Finaliza: %d\n", hijo);
	}
	
	return 0;
}

