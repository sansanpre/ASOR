// GLORIA PORTO Y SANDRA SÁNCHEZ
/*
Ejercicio 2. 
Para la comunicación bi-direccional, es necesario crear dos tuberías, una para cada sentido: p_h y h_p. 
Escribir un programa que implemente el mecanismo de sincronización de parada y espera:
    · El padre leerá de la entrada estándar (terminal) y enviará el mensaje al proceso hijo, escribiéndolo en la tubería p_h. 
      Entonces permanecerá bloqueado esperando la confirmación por parte del hijo en la otra tubería, h_p.
    · El hijo leerá de la tubería p_h, escribirá el mensaje por la salida estándar y esperará 1 segundo. 
      Entonces, enviará el carácter ‘l’ al proceso padre, escribiéndolo en la tubería h_p, para indicar que está listo. 
      Después de 10 mensajes enviará el carácter ‘q’ para indicar al padre que finalice.
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {

    // creamos dos tuberias
    int p_h[2];
    pipe(p_h); 

    int h_p[2];
    pipe(h_p);

    // creamos el hijo
    pid_t pid=fork();

    switch(pid){
        // caso error:
        case -1: 
            perror("fork");
            return 1;
        break;

        // caso hijo
        case 0:
            close(p_h[1]); 
            close(h_p[0]);
            char mensaje[500];          // para la lectura y escritura
            for (int i = 0; i < 10; i++) {
                // lee de la tuberia p_h
                int bytes_leidos = read(p_h[0],&mensaje,sizeof(mensaje));
                
                // escribe por la salida estandar el mensaje leido
                printf("[HIJO] > He leido: %s\n", mensaje);

                //espera 1 segundo
                sleep(1);       
                char l = 'l';
                char q = 'q';
                if (i < 9) write(h_p[1],&l,sizeof(l));         // enviará el carácter ‘l’ al padre, escribiéndolo en la tubería h_p, para indicar que está listo
                else write(h_p[1],&q,sizeof(q));               // después de 10 mensajes enviará el carácter ‘q’ para indicar al padre que finalice
               
            }
            close(p_h[0]);
            close(h_p[1]);
        break;

        // caso padre
        default:
            close(p_h[0]); 
            close(h_p[1]);
            char flag = ' ';

            while ( flag != 'q') {
                char message[500];
                printf("[PADRE] > Mando: %s\n");
                scanf("%s", message);
                write(p_h[1],&message,sizeof(message));
                read(h_p[0],&flag,sizeof(flag));
            }

            close(p_h[1]);
            close(h_p[0]);
            wait(NULL);
        break;
    }

    return 0;
}

