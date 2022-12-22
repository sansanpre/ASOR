/**     PRACTICA 2.5
 * PROTOCOLO TCP - EJERCICIO 7
 * Escribir el cliente para conectarse con el servidor del ejercicio anterior. 
 El cliente recibirá la dirección y el puerto del servidor como argumentos y, 
 una vez establecida la conexión con el servidor, le enviará lo que el usuario 
 escriba por teclado. Mostrará en la consola la respuesta recibida desde el servidor. 
 Cuando el usuario escriba el carácter ‘Q’ como único carácter de una línea, el cliente cerrará la conexión con el servidor y terminará.
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

int main(int argc, char**argv){

  //Gestionamos los errores
    if (argc < 2 == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
        return -1;
    }

    struct addrinfo hints;
    struct addrinfo *result;

    memset(& hints, 0, sizeof(struct addrinfo));

    hints.ai_family 	= AF_UNSPEC;
    hints.ai_socktype 	= SOCK_STREAM;
    hints.ai_flags 		= AI_PASSIVE;

 
    int info_result = getaddrinfo(argv[1], argv[2], &hints, &result)
    if (info_result != 0) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		exit(EXIT_FAILURE);
    }

    int TCPsocket = socket(result->ai_family, result->ai_socktype, 0);
    connect(TCPsocket,(struct sockaddr *)result->ai_addr, result->ai_addrlen);
    freeaddrinfo(result);

    char host[200];
    char serv[200];
    char buffin[256];
    char buffout[256];
    ssize_t c;


while (1) {
        c = read(0,buffout, 255);
        buffout[c] = '\0';
        send(socketTCP,buffout, c, 0);


        if ((buffout[1] == 'q') && (c == 2)) {
        printf("Conexión terminada\n");
        break;
        }

        c = recv(socketTCP, buffin, 255, 0);
        buffin[c] = '\0';
        printf("[OUT]:%s\n", buffin);
}

close(socketTCP);
return 0;
}