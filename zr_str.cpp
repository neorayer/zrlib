#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "zr_str.h"

void zr_str2lower(const char * src, char * buf) {
	strcpy(buf, src);
	int len = strlen(buf);
	for (int i=0; i< len; i++)
		if (buf[i]>='A' && buf[i] <= 'Z')
			buf[i] += 32;
}

void zr_strtrim(char * s) {
	char *p, *q;
	p = q = s;
	while (*q != '\0') {
		if (*q != ' ')
		*p++ = *q;
		q++;
	}
	*p = 0;
}