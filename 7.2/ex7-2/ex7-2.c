// Exercise 7-2.  Write a program that will print arbitrary input in a sensible way.  As a minimum, it should print non-graphic characters in octal or hexadecimal.
// according to local custom, and break long text lines.

#include <stdio.h>
#include <ctype.h>

int main()
{
	int c;

	while((c = getchar()) != EOF)
	{
		if(isgraph(c))
			putchar(c);
		else
			printf("%x", c);
	}
	return 0;
}
