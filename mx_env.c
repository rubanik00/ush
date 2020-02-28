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

// static char **mx_reassign(t_lst *head) {
//     head->proces = malloc(sizeof(char) * 3);
//     head->stream = malloc(sizeof(char) * 3);

//     head->p_name = mx_strjoin("/bin/", head->args[index]); // "/bin/sh"
    
//     head->proces[0] = head->args[index];

//     head->proces[1] = NULL;

//     head->stream[0] = NULL;
//     head->stream[1] = NULL;

//     return head->stream; 
// }

static void print_env(t_env *env) {
    for (int i = 0; env->stream_name[i]; i++) { 
        check_valid_av(env->stream_name[i]);
        mx_printstr(env->stream_name[i]);
        mx_printchar('\n');
    }
}

char **mx_env(t_lst *head, t_env *env) {
    int i = 0;

    // if (!head->args[0])
    //     return NULL;
    
    // while (head->args[i]) {
    //     if (strcmp(head->args[i], "sh") == 0 
    //         || strcmp(head->args[i], "bash") == 0) {
    //             return mx_reassign(head, i);
    //     }
    //     i++;
    // }
    // if (env->util) { // sh || bash
    //     return mx_reassign(head);
    // }
    if (!head->args[1]) { // prosto env
        mx_print_strarr(head->env, "\n");
        return NULL;
    }
    else if (env->i == 1) {
        if (!env->stream_name) {
            return NULL;
        }
        // else if (env->util)
        //     mx_parse_util();
        else {
            print_env(env);
            return NULL;
        }
        // for (i = 2; head->args[i]; i++) {
        //     check_valid_av(head->args[i]);
        //     if (head->args[i]) {
        //         mx_printstr(head->args[i]);
        //         mx_printchar('\n');
        //     }
        //     else {
        //         return NULL;
        //     }
        // }
    }
    else {
        // if (env->util)
        //     mx_parse_util();
        mx_print_strarr(head->env, "\n");
        if (env->stream_name) {
           print_env(env); 
        }
        return NULL;
        
        // i = 1;
        // while (head->args[i]){
        //     i++;
        // }
        // if (i > 0) {
        //     mx_print_strarr(head->env, "\n");
        //     for (i = 1; head->args[i]; i++) {
        //         if (head->args[i]) {
        //             mx_printstr(head->args[i]);
        //             mx_printchar('\n');
        //         }
        //         else {
        //             return NULL;
        //         }
        //     }
        // }
        // else {
        //     mx_print_strarr(head->env, "\n");
        //     return NULL;
        // }
    }
    return NULL;
}
