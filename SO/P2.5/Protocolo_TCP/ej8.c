/**     PRACTICA 2.5
 * PROTOCOLO TCP - EJERCICIO 8
 Modificar el código del servidor para que acepte varias conexiones simultáneas. 
 Cada petición debe gestionarse en un proceso diferente, siguiendo el patrón accept-and-fork. 
 El proceso padre debe cerrar el socket devuelto por accept(2).usuario escriba el carácter ‘Q’ 
 como único carácter de una línea, el cliente cerrará la conexión con el servidor y terminará.
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

    if (argc < 2 == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
        return -1;
    }

    struct addrinfo hints;
    struct addrinfo *result;

    memset(& hints, 0, sizeof(struct addrinfo));

    hints.ai_family 	= AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

 
  if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0) {
      printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
      exit(EXIT_FAILURE);
  }

  int socketTCP = socket(result->ai_family, result->ai_socktype, 0);
  bind(socketTCP, result->ai_addr, result->ai_addrlen);
  freeaddrinfo(result);

  listen(socketTCP, 5);

  struct sockaddr_storage cli;
  socklen_t clen = sizeof(cli);

  char buf[81];
  int cli_sd;
  char host[200];
  char serv[200];
  ssize_t c;


  while (1) {

    cli_sd = accept(socketTCP,(struct sockaddr *) &cli, &clen);

    pid_t pid;
    pid = fork();
    if (pid == 0) {
      while (1) {
        getnameinfo((struct sockaddr *)&cli, clen, host, 200, serv, 200, 200);
        printf("[PID: %i] Conexión desde %s:%s\n", getpid(), host, serv);

        c = recv(cli_sd, buf, 80, 0);
        buf[c] = '\0';

        if ((buf[0] == 'Q') && (c == 2)) {
          printf("Conexión terminada\n");
          break;
        }
        send(cli_sd, buf, c, 0);
      }
      close(cli_sd);
    } else {
      close(cli_sd);
    }
  }

  close(cli_sd);



  return 0;
}