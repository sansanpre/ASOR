/**     PRACTICA 2.2
 * CREACIÓN Y ATRIBUTOS DE FICHEROS - EJERCICIO 11
 *  link(2) y symlink(2) crean enlaces rígidos y simbólicos, respectivamente. 
 *  Escribir un programa que reciba una ruta a un fichero como argumento. 
 *  Si la ruta es un fichero regular, creará un enlace simbólico y rígido 
 *  con el mismo nombre terminado en .sym y .hard, respectivamente. 
 *  Comprobar el resultado con ls(1).
 *  
**/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysmacros.h>
#include <stdlib.h>

//Includes de la pagina de manual de strerror(3)
#include <string.h>
//Includes de la pagina de manual de perror(3)
#include <errno.h>
//Includes de la pagina de manual de stat(2)
#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>

/**En este ejercicio, utilizaremos:
 *  int link(const char *oldpath, const char *newpath); -->  creates a new link (also known as a hard link)
 *                                                           to an existing file.
 *  int symlink(const char *target, const char *linkpath); -->  creates a symbolic link named 
 *                                                              linkpath which contains the string target.
 *  void *malloc(size_t size); --> function allocates size bytes and returns a pointer
 *                                 to the allocated memory  
 *  size_t strlen(const char *s); --> calculate the length of a string             
 *  char *strcpy(char *restrict dest, const char *src); --> function copies the string pointed to by 
 *                                                          src to the buffer pointed to by dest.
**/

int main(int argc, char **argv) {

    //Gestionamos los errores
    struct stat datos;
    if (argc < 2 || stat(argv[1], &datos) == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		return -1;
	}
    //Creamos el nombre de los enlaces
    char* hard = malloc(sizeof(char)*(5 + strlen(argv[1])));
	char* sym = malloc(sizeof(char)*(5 + strlen(argv[1])));
	strcpy(hard, argv[1]);
	strcpy(sym, argv[1]);
  
	printf("Enlace duro: %s\n", hard);
	printf("Enlace simbolico: %s\n", sym);
    
    //Comprobamos el tipo de archivo    
    switch (datos.st_mode & S_IFMT) {          
        case S_IFREG:  
            printf("Es un fichero regular\n");          

            if (link(argv[1], strcat(hard, ".hard")) == -1) {
                printf("ERROR: No se ha podido crear el enlace duro.\n");
            } 
            else printf("Se ha creado enlace duro.\n");

            if (symlink(argv[1], strcat(sym, ".sym")) == -1) {
                printf("ERROR: No se ha podido crear el enlace simbólico.\n");
            } 
            else printf("Se ha creado enlace simbólico.\n");  
        
            break;
    
        default:       
            printf("Solo se permite un fichero regular\n");                
            break;
    }

	return 0;
}