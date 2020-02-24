#include "ush.h"

int mx_ush_launch(char **args) {
    pid_t pid;
    pid_t wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1)
            perror("ush");
        exit(EXIT_FAILURE);
    } 
    else if (pid < 0) {
        // Error forking
        perror("ush");
    }
    else {
        // Parent process
        wpid = waitpid(pid, &status, WUNTRACED);
    }
    return 1;
}
