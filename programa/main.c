#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

char **split(char *phrase, const size_t length, const char delimiter, size_t *n_tokens){
    int words = 1;

    size_t n;
    for (n = 0; n < length; n++)
        words += phrase[n] == delimiter;

    char **input = malloc(sizeof(char*) * words);

    int j = 0;
    char *token = strtok(phrase, &delimiter);
    while (token != NULL) {
        input[j] = malloc(sizeof(char) * strlen(token) + sizeof(char));
        strcpy(input[j++], token);
        token = strtok(NULL, &delimiter);
    }

    *n_tokens = words;
    return input;
}

char **split_line(char *phrase, size_t *n_tokens){
	const size_t length = sizeof(phrase);
	const char delimiter = ' ';

	return split(phrase, length, delimiter, n_tokens);
}

char *read_char(){
    char *c;
    c = malloc(sizeof(char));
    read(STDIN_FILENO, c, sizeof(char));
    return c;
}

char *read_line(){
    size_t bufsize = 1024;
    int position = 0;
    char *c;
    char *buffer = malloc(sizeof(char) * bufsize);

    while (1){
        c = read_char();

        if (*c == EOF || *c == '\n'){
            buffer[position] = '\0';
            return buffer;
        }
        else{
            buffer[position] = *c;
        }
        position++;

        if (position >= bufsize){
            bufsize += 1024;
            buffer = realloc(buffer, bufsize);
        }
    }
}


void loop(void){
    char *line;
    char **args;
    int status;
    int i;
    size_t line_size,valor = 0;
    size_t *n_args = &valor;

    do {
        write(STDOUT_FILENO,"> ",2);
        line = read_line();
        line_size = strlen(line);
        args = split_line(line, n_args);
        status = execute(args);
	    free(line);
	    free(args);
    } while (status);
}

int execute(char **args){
    pid_t pid, wpid;
    int status;
    int i;

    pid = fork();
    if (pid == 0) {

        // Child process
        if (execvp(args[0], args) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("lsh");
    } else {
        for (i = 0; i < 1024; ++i) {
            if(args[i]== NULL){
                i--;
                break;
            }
        }
        // Parent process
        if (!strcmp(args[i],"&")) {
            usleep(100000);
        } else{
            do {
                wpid = waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }

    return 1;
}

int main() {

    // Load config files, if any.

    // Run command loop.
    loop();

    // Perform any shutdown/cleanup.

    return 0;

}

