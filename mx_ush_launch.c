#include "ush.h"

static int choose_exec(t_lst *head) {
    char **new_env;
    int status = 0;

    if (strcmp(head->args[0], "env") == 0) {
        new_env = mx_env(head);
        if (new_env == NULL)
            return 1;
        else
            status = execve(head->args[0], head->av, head->cmd);
        mx_del_strarr(&new_env);
    }
    else {
        if ((status = execvp(head->args[0], head->args)) == -1)
            mx_printerr("ERROR");
        exit(0);
    }

    return status;
}

int mx_ush_launch(t_lst *head) {
    pid_t pid = fork();
    int status = 0;

    if (pid == 0) {
        if ((status = choose_exec(head)) < 0) {
            mx_printstr("ERROR\n");
            return 0;
        }
        exit(status);
    }
    if (pid < 0) {
        mx_printerr("ush: error starting a new proccess: ");
        mx_printerr(head->args[0]);
    }
    else
        status = waitpid(pid, &status, WUNTRACED);
    return status;
}
