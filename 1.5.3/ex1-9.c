#include <stdio.h>

/* Exercise 1-9. Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank. */

main()
{
	int c, prevcharInt;

	prevcharInt = 0;

	while((c = getchar()) != EOF)
	{
		if(c == ' ')
		{
			if(prevcharInt != ' ')
				putchar(c);
		}
		if(c != ' ')
				putchar(c);
		prevcharInt = c;
	}
}
