#include "ush.h"

void mx_ush_loop(void) {
    // char *line;
    // char **args;
    char **env = mx_env_copy();
    int status = 1;
    t_lst *head = malloc(sizeof(t_lst));
    head->env = env;
    head->cmd = strdup("envp");
    head->av = malloc(sizeof(char *) * 300);
    // head->av[0] = strdup("-i");
    // head->av[0] = strdup("Y=B");
    // head->av[1] = strdup("A=B");
    // head->av[2] = strdup("B=C");
    // head->av[3] = strdup("!A!=====!B");

    while (status) {
        // printf("u$h> ");
        // line = mx_ush_read_line();
        // head = mx_ush_split_line(line);
        status = mx_ush_execute(head);
        // free(line);
        // free(args);
    }
    // free(head);
    // free(head->av);
}
