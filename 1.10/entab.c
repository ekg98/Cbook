/* Exercise 1-21.  Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing.  Use the same tab stops as for detab.  When either a tab or a signle blank would suffice to reach a tab stop, which should be given preference? */

#include <stdio.h>

#define	MAXIMUM	1024

int entab(char s[], int lim, int ts);

main()
{
	char charLine[MAXIMUM];
	int intTabSize;

	intTabSize = 8;

	while(entab(charLine, MAXIMUM, intTabSize) > 0)
	{
		printf("%s\n", charLine);
	}

	return 0;
}

/* entab:	Replaces strings of spaces with tabs */
int entab(char string[], int limit, int tabsize)
{
	int i,c;
	int blockcounter, arraypos;
	int intSpaces;

	blockcounter = 0;
	arraypos = 0;
	intSpaces = 0;

	for(i = 0; (c = getchar()) != EOF && c != '\n' && i < limit - 1; ++i)
	{
		string[arraypos] = c;
		++arraypos;

		if((blockcounter + 1) == tabsize)
		{
			for(; blockcounter >= 0 && string[arraypos - (tabsize - blockcounter)] == ' '; --blockcounter)
					++intSpaces;
			
			if(intSpaces > 1)
			{
				arraypos = arraypos - intSpaces;
				string[arraypos] = '\t';
				++arraypos;
			}

			blockcounter = -1;
			intSpaces = 0;
		}
		
		++blockcounter;
	}

	string[arraypos] = '\0';
		
	return i;
}
