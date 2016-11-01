#include <stdlib.h>
#include <string.h>
#include  <fcntl.h>

char *lsh_read_line(){

    char buffer[65];
    int file = open("instructions.txt",O_RDONLY);

    if(file < 0)
        return 1;
    read(file, buffer, 64);

}

void lsh_loop(void){
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    } while (status);
}


int main() {

// Load config files, if any.

    // Run command loop.
    lsh_loop();

    // Perform any shutdown/cleanup.

    return EXIT_SUCCESS;

}