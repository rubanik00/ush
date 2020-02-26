#include "ush.h"

static int choose_exec(char **args, char **env) {
    if (!env)
        return execvp(args[0], args);
    else 
        return execve(args[0], args, env);
}

int mx_ush_launch(char **args, char **env) {
    int status = 0;
    pid_t pid = fork();

    if (!pid) {
        if ((status = choose_exec(args, env)) < 0) {
            mx_printstr("ERROR\n");
            return 0;
        }
        exit(status);
    }
    if (pid < 0) {
        mx_printerr("ush: error starting a new proccess: ");
        mx_printerr(args[0]);
    }
    else {
        waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status))
            waitpid(pid, &status, WUNTRACED);
    }
    return status;
}
