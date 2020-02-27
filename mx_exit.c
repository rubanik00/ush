#include "ush.h"

static unsigned long long mx_atoi_long(const char *str) {
   int i = 0;
   unsigned long long n = 0;
   int s = 1;
   
   while (!mx_isdigit(str[i])){
       if (!mx_isspace(str[i]) && str[i] != '-' && str[i] != '+')
           return 0;
       i++;
   }
   if (str[i - 1] == '-')
       s = -s;
   for (; mx_isdigit(str[i]); i++)
       n = ((n * 10) + (str[i] - '0'));
   if (s < 0)
       n = -n;
   return n;
}

int mx_exit(char **args) {
    unsigned long long a = 9223372036854775807;
    unsigned long long res = 0;

    if (args[1])
        res = mx_atoi_long(args[1]);
    if (res > a) {
        printf("%s", " exit: ");
        printf("%llu", res);
        printf("%s", ": numeric argument required\n");
        exit(255);
    }
    else if (!args[1])
        exit(0);
    else if (args[1])
        exit(mx_atoi(args[1]));
    
    return 0;
}

