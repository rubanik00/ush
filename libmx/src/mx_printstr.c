#include "libmx.h"

void mx_printstr(const char *s) {
    char tmp = '?';
    int i = 0;

    if (s) {
		if (isatty(1))
			while (s[i]) {
				(s[i] > 31 && s[i] < 127) ? write(1, &s[i], 1) : write(1, &tmp, 1);
				i++;
			}
		else if (!isatty(1))
			write(1, s, mx_strlen(s));
    }
}
