#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define	BUFSIZE	100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
	{
		printf("%d\n", c);
		buf[bufp++] = c;
	}
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
