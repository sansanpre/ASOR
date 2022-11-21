/**     PRACTICA 2.2
 * CREACIÓN Y ATRIBUTOS DE FICHEROS - EJERCICIO 9
 *  Escribir un programa que emule el comportamiento de stat(1) y muestre:
 *      ● El número major y minor asociado al dispositivo.
 *      ● El número de inodo del fichero.
 *      ● El tipo de fichero (directorio, enlace simbólico o fichero ordinario).
 *      ● La hora en la que se accedió el fichero por última vez. ¿Qué diferencia hay entre st_mtime y st_ctime?
 *   
**/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysmacros.h>

//Includes de la pagina de manual de strerror(3)
#include <string.h>
//Includes de la pagina de manual de perror(3)
#include <errno.h>
//Includes de la pagina de manual de stat(2)
#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>


/**En este ejercicio, utilizaremos:
 *  int fstat(int fd, struct stat *statbuf); -->                                      
 * 
**/

int main() {

    const char *pathname = "./ejer9.txt";

    //Traducimos los permisos rw-r--r-x a octal --> 0645
    int descriptor_fichero = open(pathname, O_CREAT, 0645);

    if(descriptor_fichero == -1){
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
        return -1;
    }
    //Imprimimos por pantalla el descriptor
    printf("El descriptor del nuevo fichero es: %d\n", descriptor_fichero);

    struct stat datos;

    int p = fstat(descriptor_fichero, &datos);

    if(p == -1){
        printf("ERROR(%d): %s\n", errno, strerror(errno)); //Imprimimos por pantalla el error
    }
    else{
        //Nº major y minor asociado
        printf("El Major asociado al dispositivo es: %d\n", major(datos.st_dev));
        printf("El Minor asociado al dispositivo es: %d\n", minor(datos.st_dev));

        //Nº inodo de fichero
        printf("El Inodo del fichero es: %li\n", datos.st_ino);

        //Tipo fichero
        char *tipo;
        if(S_ISREG(datos.st_mode)){
            tipo = "Fichero Regular";

        }else if (S_ISDIR(datos.st_mode)){
            tipo = "Directorio";

        }else if (S_ISLNK(datos.st_mode)){
            tipo = "Enlace Simbolico";
        }
        printf("El tipo de archivo es: %s\n", tipo);

        //This is the time of the last access of file data.
        printf("Último acceso al archivo: %s", ctime(&datos.st_atim));    
        //This is the time of last modification of file data.
        printf("Última modificación en el archivo: %s", ctime(&datos.st_ctim));
        //This is the file's last status change timestamp (time of last change to the inode).
        printf("Última modificación del status del archivo: %s", ctime(&datos.st_mtim));
    }

	return 0;
}