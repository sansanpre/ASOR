/**     PRACTICA 2.5
 * PROTOCOLO TCP - EJERCICIO 9
Añadir la lógica necesaria en el servidor para que no quede ningún proceso en estado zombie. 
Para ello, se deberá capturar la señal SIGCHLD y obtener la información de estado de los procesos hijos finalizados.
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

void check(int signal){
  pid_t notzombie;
  notzomobie = wait(NULL);
  printf("ok\n");
}

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


  // cap
  signal(SIGCHLD, check);
  
  
  int status;
  while (1) {

    cli_sd = accept(socketTCP,(struct sockaddr *) &cli, &clen);

    pid_t pid;
    pid = fork();
    if (pid == 0) {
      while (1) {
        getnameinfo((struct sockaddr *)&cli, clen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);
        printf("[PID: %i] Conexión desde %s:%s\n", getpid(), host, serv);

        c = recv(cli_sd, buf, 80, 0);
        buf[c] = '\0';

        if ((buf[0] == 'q') && (c == 2)) {
          printf("Conexión terminada\n");
          exit(0);
        } else {
          send(cli_sd, buf, c, 0);
        }
      }
    } else {
      pid = wait(&status);
      close(cli_sd);
      exit(0);
    }
  }

  close(cli_sd);



  return 0;
}