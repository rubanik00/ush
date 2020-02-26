#include "ush.h"

static void print_err(char *av) {
    mx_printerr(av);
    mx_printerr(": event not found\n");
    exit(0);
}

static void check_valid_av(char *av) {
    int i = 0;
    int index = mx_get_char_index(av, '=');    
    char *frst_part = strndup(av, index);
    char *sec_part = strndup(av + index + 1, strlen(av) - index);

    if (frst_part[0] == '!') {
        print_err(av);
    }
    while (sec_part[i]) {
        if (sec_part[i] == '!'
            && (sec_part[i + 1] != '=' && sec_part[i + 1] != '\0')) {
            print_err(av);
        }
        i++;
    }
}

int mx_env(t_lst *head, char **env) {
    int i = 0;

    if (!head->av[0]) {
        mx_print_strarr(env, "\n");
        return 0;
    }
    else if (strcmp(head->av[0], "-i") == 0) {
        for (i = 1; head->av[i]; i++) {
            check_valid_av(head->av[i]);
            if (head->av[i]) {
                mx_printstr(head->av[i]);
                mx_printchar('\n');
                return 0;
            }
            else {
                return 0;
            }
        }
    }
    else {
        i = 0;
        while (head->av[i]){
            i++;
        }
        if (i > 0) {
            mx_print_strarr(env, "\n");
            for (i = 0; head->av[i]; i++) {
                if (head->av[i]) {
                    mx_printstr(head->av[i]);
                    mx_printchar('\n');
                    return 0;
                }
                else {
                    return 0;
                }
            }
        }
        else {
            mx_print_strarr(env, "\n");
            return 0;
        }
    }
    return 0;
}
