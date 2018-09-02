/* alloc.c:  Contains the functions for alloc.  */

#include <stdlib.h>

#define ALLOCSIZE	10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
	if(allocbuf + ALLOCSIZE - allocp >= n)
	{
		allocp += n;
		return allocp - n;
	}
	else
		return NULL;
}
