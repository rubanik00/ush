#include "ush.h"

void mx_ush_loop(void) {
    char *line;
    int status = 1;
    t_lst *head = malloc(sizeof(t_lst));

    while (status) {
        printf("u$h> ");
        line = mx_ush_read_line();
        head->args = mx_ush_split_line(line);
        status = mx_ush_execute(head);
        free(line);
        free(head->args);
    }

}
