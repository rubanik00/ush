#include "ush.h"

static void print_err(char *av) {
    mx_printerr(av);
    mx_printerr(": event not found\n");
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

static char **mx_reassign(t_lst *head, int index) {
    head->args[0] = mx_strjoin("/bin/", head->args[index]); // "/bin/sh"
    head->av[0] = head->args[index];                        // "{sh, NULL}"
    head->av[1] = NULL;
    head->cmd[0] = "A=B";                                   // "{A=B, NULL}"
    head->cmd[1] = NULL;

    return head->cmd; 
}

char **mx_env(t_lst *head) {
    int i = 0;

    if (!head->args[0])
        return NULL;
    
    while (head->args[i]) {
        if (strcmp(head->args[i], "sh") == 0 
            || strcmp(head->args[i], "bash") == 0) {
                return mx_reassign(head, i);
        }
        i++;
    }
    i = 0;

    if (!head->args[1]) {
        mx_print_strarr(head->env, "\n");
        return NULL;
    }
    else if (strcmp(head->args[1], "-i") == 0) {
        for (i = 2; head->args[i]; i++) {
            check_valid_av(head->args[i]);
            if (head->args[i]) {
                mx_printstr(head->args[i]);
                mx_printchar('\n');
            }
            else {
                return NULL;
            }
        }
    }
    else {
        i = 1;
        while (head->args[i]){
            i++;
        }
        if (i > 0) {
            mx_print_strarr(head->env, "\n");
            for (i = 1; head->args[i]; i++) {
                if (head->args[i]) {
                    mx_printstr(head->args[i]);
                    mx_printchar('\n');
                }
                else {
                    return NULL;
                }
            }
        }
        else {
            mx_print_strarr(head->env, "\n");
            return NULL;
        }
    }
    return NULL;
}
