/*  Exercise 5-13.  Write the program tail,  which prints the last n lines of its input.  By default, n is 10, let us say, but it can be changed by an optional argument, so that tail -n prints the last n lines. */
/*  The program should behave rationally no matter how unreasonable the input or the value of n.  Write the program so it makes the best use of available storage; lines should be stored as in the sorting program */
/*  of section 5.6, not in a two-dimensional array of fixed size. */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "alloc.h"	/* header file for alloc function char *alloc(int) */

int getaline(char *s, int limit);

int main(int argc, char *argv[])
{
	int argumentCounter = 1;
	int lineQuantity = 10;	/* default line quantity */

	if(argc > 1)	/* sets lineQuantity if a argument is present */
	{
		while(argumentCounter < argc)
		{
			if(*argv[argumentCounter] == '-')
			{
				if(isdigit(*(argv[argumentCounter] + 1)))
					lineQuantity = atoi(argv[argumentCounter] + 1);
				else
				{
					printf("Argument error.\n");
					return -1;
				}
			}
			argumentCounter++;
		}

	}

	char *lines[lineQuantity];	/* Allocate pointer array for lines based off default value or arguments */



	printf("argument value = %d\n", lineQuantity);
	
	
	return 0;
}

int getaline(char *s, int limit)
{
	int c, i;

	for(i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;

	if(c == '\n')
	{
		s[i] = c;
		i++;
	}

	s[i] = '\0';

	return i;
}
