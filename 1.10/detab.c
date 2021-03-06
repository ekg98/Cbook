/* Exercise 1-20.  Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop.  Assume a fixed set of tab stops, say every N columns.  Should N be a variable or a symbolics parameter? */

#include <stdio.h>
#define	MAXIMUM	1024

int getlinee(char string[], int limit);

main()
{
	int intStringLength, intTabSize, i;
	char charCurrentLine[MAXIMUM];
	int intSpaceCounter, intOutputPos;

	intStringLength = 0;
	intTabSize = 8;
	intSpaceCounter = 0;
	intOutputPos = 0;	

	char charOutputLine[intTabSize * MAXIMUM];


	while((intStringLength = getlinee(charCurrentLine, MAXIMUM)) > 0)
	{
		for(i = 0; i <= intStringLength; ++i)
		{
			if(charCurrentLine[i] == '\t')
			{
				for(; intSpaceCounter < intTabSize; ++intSpaceCounter)
				{
					charOutputLine[intOutputPos] = ' ';
					++intOutputPos;
				}
			}
			else
			{
				charOutputLine[intOutputPos] = charCurrentLine[i];
				++intSpaceCounter;
				++intOutputPos;
			}
			
			if(intSpaceCounter == intTabSize)
				intSpaceCounter = 0;
		}
		intSpaceCounter = 0;
		intOutputPos = 0;

		printf("%s", charOutputLine);
	}
	return 0;
}

/* getlinee: a function to get a line */
int getlinee(char s[], int lim)
{
	int c, i;

	for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if(c == '\n')
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
