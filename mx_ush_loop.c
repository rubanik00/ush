#include "ush.h"

void mx_ush_loop(void) {
    char *line;
    char **args;
    int status = 1;

    while (status) {
        printf("u$h> ");
        line = mx_ush_read_line(); // Прочитало лайн вернет аргв[0]
        args = mx_ush_split_line(line); // Соеденяет лайны и возвращает массив всехаргументов переданных в шел return *tokens
        status = mx_ush_execute(args);

        free(line);
        free(args);
    }
}
