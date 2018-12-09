#include <stdio.h>

#define YES	1
#define NO	0

/* Exercise 1-12. Write a program that prints its input one word per line. */

main()
{
	int c, intWhiteSpace;

	intWhiteSpace = NO;

	while((c = getchar()) != EOF)
	{
		if(c == ' ' || c == '\t')
			intWhiteSpace = YES;
		else
			if(intWhiteSpace == YES)
			{
				intWhiteSpace = NO;
				printf("\n");
			}
		
		if(c != ' ' && c != '\t' && c != '\n')	
			putchar(c);
	}
}
