/* Exercise 1-22.  Write a program to "fold" long input lines into two or more shorter lines after the last non-blank character that occurs before the n-th column of input.  Make sure your program does something intelligent with very long lines, and if there are no blanks or tabs before the specified column. */

#include <stdio.h>

#define	MAXIMUM	1024
#define	YES	1
#define	NO	0

int getaline(char s[], int lim);

main()
{
	int intFoldLimit, blockcounter;
	int i;
	int intClosestSpace, arraypos;
	int resetblock, foundspace;
	intFoldLimit = 20;
	intClosestSpace = 0;
	arraypos = 0;
	blockcounter = 0;
	resetblock = NO;
	foundspace = NO;

	char charLine[MAXIMUM];
	char charFormattedLine[(MAXIMUM + 1) + (MAXIMUM / intFoldLimit)];

	while(getaline(charLine, MAXIMUM) > 0)
	{
		for(i = 0; i <= MAXIMUM; ++i)
		{
			charFormattedLine[arraypos] = charLine[i];
			++arraypos;

			if(charLine[i] == ' ')
				intClosestSpace = i;

			if((blockcounter + 1) == intFoldLimit)
			{
				for(; blockcounter >= (intFoldLimit - 4) && foundspace == NO; --blockcounter)
				{
					if(charLine[i - ((intFoldLimit - 1) - blockcounter)] == ' ')
						foundspace = YES;
				}

				if(foundspace == YES)
					charFormattedLine[arraypos - ((intFoldLimit - 1) - blockcounter)] = '\n';
				else
				{
					charFormattedLine[arraypos] = '\n';
					++arraypos;
				}

				resetblock = YES;
			}
				
			if(resetblock == YES)
			{
				blockcounter = 0;
				resetblock = NO;
			}
			else
				++blockcounter;

			foundspace = NO;
		}
		intClosestSpace = 0;
	}

	printf("%s\n", charFormattedLine);

	return 0;
}

/* getaline:	Gets a line from the keyboard and populates a string. */

int getaline(char string[], int limit)
{
	int c, i;

	for(i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		string[i] = c;
	if(c == '\n')
	{
		string[i] = c;
		++i;
	}
	string[i] = '\0';
	return i;
}
