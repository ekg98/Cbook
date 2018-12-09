#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define	BUFSIZE	100
#define	YES	1
#define NO	0

char buf[BUFSIZE];
int bufp = 0;
char pushedback;
int pushbackoccupied = NO;

int getch(void)
{
	if(pushbackoccupied == YES)
	{
		pushbackoccupied = NO;
		return pushedback;
	}
	else
		return getchar();
}

void ungetch(int c)
{
	if(pushbackoccupied == YES)
		printf("ungetch: Pushback is occupied with a value.\n");
	else
	{
		pushedback = c;
		pushbackoccupied = YES;
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
