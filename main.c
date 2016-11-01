#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/*char *lsh_read_line(){

    char buffer[1024    ];
    char auxBuffer[65];
    int file;
    file = open("instructions",O_RDONLY);
    int auxFile = open("testfile.txt",O_WRONLY|O_CREAT|O_TRUNC,0700);
    int gotten;
    gotten = read(file, &buffer, sizeof(buffer));
    printf("%d", gotten);

    while (){

        buffer[gotten] = '\0';
        write(auxFile, buffer, 64);
        break;
    }
    close(file);
    close(auxFile);
}

void lsh_loop(void){
    char *line;
    char **args;
    int status;

    do {
       // printf("> ");
        line = lsh_read_line();
        //args = lsh_split_line(line);
        //status = lsh_execute(args);

        free(line);
        free(args);
        break;
    } while (status);
}


int main() {

// Load config files, if any.

    // Run command loop.
    lsh_loop();

    // Perform any shutdown/cleanup.

    return EXIT_SUCCESS;

}
*/
/*
int main(void)
{
    int filedesc = open("testfile.txt", O_WRONLY | O_APPEND | O_CREAT);

    printf("%d", filedesc);
    if (filedesc < 0) {
        return -1;
    }

    if (write(filedesc, "This will be output to testfile.txt\n", 36) != 36) {
        write(2, "There was an error writing to testfile.txt\n", 43);
        return -1;
    }
    close(filedesc);
    return 0;
}*/

int main(int argc, char *argv[]){

    /* Variables */
    int fd1,fd2;
    char buffer[1024];
    int numbytes;


    /* Abrimos los dos archivos */
    fd1 = open("instructions", O_RDONLY);
    fd2 = open("testfile.txt", O_WRONLY|O_CREAT|O_TRUNC, 0700);

    /* Bucle de lectura/escritura */
    while ((numbytes = read(fd1, &buffer, sizeof(char))) > 0){
        write(fd2, &buffer, numbytes);
    }

    /* Cierre de archivos */
    close(fd1);
    close(fd2);
}