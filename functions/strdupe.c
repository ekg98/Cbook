// strdupe:  make a duplicate of s

#include <stdlib.h>
#include <string.h>

char *strdupe(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s) + 1);

	if(p != NULL)
		strcpy(p, s);

	return p;
}
