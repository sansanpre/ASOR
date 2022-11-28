/**     PRACTICA 2.2
 * DIRECTORIOS - EJERCICIO 17
 *  Escribir un programa que muestre el contenido de un directorio:
 *      ● El programa tiene un único argumento que es la ruta a un directorio. El programa debe comprobar la corrección del argumento.
 *      ● El programa recorrerá las entradas del directorio y escribirá su nombre de fichero. Además:
    *      ○ Si es un fichero regular y tiene permiso de ejecución para usuario, grupo u otros, escribirá el carácter ‘*’ después del nombre.
    *      ○ Si es un directorio, escribirá el carácter ‘/’ después del nombre
    *      ○ Si es un enlace simbólico, escribirá “->” y el nombre del fichero enlazado después del nombre. Usar readlink(2).
 *      ● Al final de la lista, el programa escribirá el tamaño total que ocupan los ficheros (no directorios) en kilobytes.
 * 
**/


#include <stdio.h>
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
//Includes de la pagina de manual time(2)
 #include <time.h>
 #include <sys/time.h>
//Includes de la pagina de manual opendir(3)
 #include <dirent.h>

/**En este ejercicio, utilizaremos:
 *  DIR *opendir(const char *name); --> opens a directory stream corresponding to
 *                                             the directory name, and returns a pointer 
 *                                             to the directory stream
 * char *strcpy(char *restrict dest, const char *src); --> function copies the string pointed to by 
 *                                                          src to the buffer pointed to by dest.
 * ssize_t readlink(const char *path, char *buf, size_t bufsiz); --> places the contents of the symbolic 
 *                                                                   link path in the buffer buf, which has size bufsiz.
**/

int main(int argc, char **argv) {
    //Gestionamos los errores
    if (argc < 2 == -1) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
		return -1;
	}
    //Obtenemos el descriptor de fichero del archivo
    DIR *dir = opendir(argv[1]);
    if (dir == NULL) {
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
        return -1;
    }
    struct stat datos;
    struct dirent *dirent;
    int suma = 0;
    while((dirent =readdir(dir))!=NULL){
        char *path = malloc(sizeof(char)*(strlen(argv[1]) + strlen(dirent->d_name) + 3));
        strcpy(path, argv[1]);
        strcat(path, "/");
        strcat(path, dirent->d_name);

        if (stat(path, &datos) == -1) {
            printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
            free(path);
            closedir(dir);
            return -1;
        }

        //Comprobamos el tipo de archivo    
        switch (datos.st_mode & S_IFMT) {              
            case S_IFDIR:  
                printf("Directory\n"); 
                printf("%s/\n",dirent->d_name);              
                break;

            case S_IFLNK:  
                printf("Symlink\n");  
                char *link_name = malloc(datos.st_size + 1);
                int dir2 = readlink(path, link_name, datos.st_size + 1);
                printf("[S]: %s->%s \n", dirent->d_name, link_name);
                free(link_name);               
                break;

            case S_IFREG:  
                printf("Regular file\n");  
                //Comprobamos permisos
                if((datos.st_mode & S_IXUSR) && (datos.st_mode & S_IXGRP) 
                        && (datos.st_mode & S_IXOTH )){
                        
                        printf("%s*\n",dirent->d_name); 
                }
                else{
                    printf("%s\n",dirent->d_name); 
                }
                suma = suma + datos.st_size; 

                break;

            default:  
                printf("Otro tipo de archivo\n");                
                break;
        }

    }
    double total =(double)suma/1000;
    printf("El total de KB de los ficheros es: %f \n",total); //mostrar 6 decimales

    closedir(dir);

	return 0;
}
