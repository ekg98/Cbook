/* Modified for expr.  Chapter 5.10 */

#include "expr.h"

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : 0;
}

void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
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
