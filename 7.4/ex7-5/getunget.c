#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "getunget.h"

#define	BUFSIZE	100

char buf[BUFSIZE], sfbuffer[BUFSIZE];
int bufp = 0;

int getch(void)
{
	//return (bufp > 0) ? buf[--bufp] : getchar();

	// if bufp is not populated use scanf to pass a string to ungets()
	// getch needs to return value
	int stringLength;

	if(bufp > 0)
		return buf[--bufp];
	else
	{
		scanf("%s", sfbuffer);

		// following statement forces a space in the buffer becuase scanf removes all whitespace
		if((stringLength = strlen(sfbuffer)) < BUFSIZE - 1)
		{
			sfbuffer[stringLength] = ' ';
			sfbuffer[stringLength + 1] = '\0';
		}
		else
		{
			fprintf(stderr, "getch: error buffer overflow!");
			exit(2);
		}

		ungets(sfbuffer);

		if(bufp > 0)
			return buf[--bufp];
		else
		{
			fprintf(stderr, "getch: empty buffer error.\n");
			exit(1);
		}
	}
}

void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

void resetbuf(void)
{
	bufp = 0;
}

void ungets(char string[])
{
	int i;

	if(bufp >= BUFSIZE)
		printf("ungets: too many characters\n");
	else
		for(i = (strlen(string) - 1); i >= 0; --i)
			buf[bufp++] = string[i];

}
