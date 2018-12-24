/* getch and ungetch functions */

#include <stdio.h>
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
		printf("ungetch:  too many characters\n");
	else
		buf[bufp++] = c;
}

// ungets:  Put a string back into the buffer
void ungets(char *word)
{
	int stringSize = strlen(word);

	if(bufp >= BUFSIZE)
		printf("ungets:  too many characters in buffer\n");
	else if(stringSize <= 0)
		printf("ungets:  string is too small\n");
	else if((BUFSIZE - bufp) < stringSize)
		printf("ungets:  string too large for buffer\n");
	else
		for(; stringSize >= 0; stringSize--)
			buf[bufp++] = word[stringSize];

}
