// GLORIA PORTO Y SANDRA SÁNCHEZ
/*
Ejercicio 5. 
Crear otra tubería con nombre. Escribir un programa que espere hasta que haya datos listos para leer en alguna de ellas. 
El programa debe mostrar la tubería desde la que leyó y los datos leídos. Consideraciones: 
  ·	Para optimizar las operaciones de lectura usar un buffer (ej. de 256 bytes).
  ·	Usar read(2) para leer de la tubería y gestionar adecuadamente la longitud de los datos leídos.
  ·	Normalmente, la apertura de la tubería para lectura se bloqueará hasta que se abra para escritura (ej. con echo 1 > tuberia). Para evitarlo, usar la opción O_NONBLOCK en open(2).
  ·	Cuando el escritor termina y cierra la tubería, read(2) devolverá 0, indicando el fin de fichero, por lo que hay que cerrar la tubería y volver a abrirla. Si no, select(2) considerará el descriptor siempre listo para lectura y no se bloqueará.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>





int main(){

    // creamos las 2 tuberias
    mkfifo("tuberia1",0777);  
    mkfifo("tuberia2",0777); 

    // abrimos ambas tuberias 
    int fd1 = open("./tuberia1",O_RDONLY | O_NONBLOCK);
    int fd2 = open("./tuberia2",O_RDONLY | O_NONBLOCK);

    // variables
    int cambios = 0;
    int tub_act = 0;
    char buffer[257];


    while (cambios != -1 ) {
      fd_set conjunto;
      FD_ZERO(&conjunto);
      FD_SET(fd1, &conjunto);
      FD_SET(fd2, &conjunto);
      int id_tub_act;

      if(fd1 > fd2){ 
        id_tub_act = fd1; 
      } 
      else {
        id_tub_act = fd2;
      }
                
      cambios = select(id_tub_act+1,&conjunto,0,0,0);

      if (cambios > 0){
          // determinamos la tuberia en la que nos encontramos y realizamos las operaciones del descriptor:
          // tuberia 1
          if (FD_ISSET(fd1, &conjunto)) {
            id_tub_act = 1;
            tub_act = fd1;
          } 

          // o tuberia 2
          else if (FD_ISSET(fd2, &conjunto)) {
            id_tub_act = 2;
            tub_act = fd2;
          }

        // gestionamos el tamaño del buffer
        ssize_t readsize = 256;
			  
        while (readsize == 256) {
          readsize = read(tub_act, buffer, 256);
          buffer[readsize] = '\0';
          printf("Tuberia %i: %s", id_tub_act, buffer);
			  }

        if (readsize != 256 && id_tub_act == 1) {
            close(fd1);
            fd1 = open("./tuberia1", O_RDONLY | O_NONBLOCK);
            if (fd1 == -1) {
                perror("Error al abrir de nuevo la tuberia");
                close(fd1);
                close(fd2);
                return -1;
            }
        }
        else if (readsize != 256 && id_tub_act == 2) {
            close(fd2);
            fd2 = open("./tuberia2", O_RDONLY | O_NONBLOCK);
            if (fd2 == -1) {
                perror("Error al abrir de nuevo la tuberia");
                close(fd1);
                close(fd2);
                return -1;
            }
        }


		  }
    }
    
  close(fd1);
  close(fd2);
  return 0;  
}

