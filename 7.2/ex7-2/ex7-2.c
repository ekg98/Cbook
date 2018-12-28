// Exercise 7-2.  Write a program that will print arbitrary input in a sensible way.  As a minimum, it should print non-graphic characters in octal or hexadecimal.
// according to local custom, and break long text lines.

#include <stdio.h>
#include <ctype.h>

#define	LINESIZE	50

int main()
{
	int c, lineCounter = 0;

	while((c = getchar()) != EOF)
	{
		if(lineCounter < LINESIZE)
			;
		else
		{
			putchar('\n');
			lineCounter = 0;
		}

		if(isgraph(c))
			putchar(c);
		else
			printf("%#X", c);

		lineCounter++;
	}
	return 0;
}
