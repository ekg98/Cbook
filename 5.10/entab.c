/* Exercise 5-11.  Entab.  Modify the programs entab and detab to accept a list of tab stops as arguments.  Use the default tab settings if there are no arguements. */

/* no arguements no workie.  Pretty simple.  Default settings?  Does it mean this should be written to take a argument to change the tab spacing size?  I have modified it to actually take a list of tab stops.  Input string.  */

#include <stdio.h>
#include <string.h>

#define	MAXIMUM	1024

int entab(char s[], int lim, int ts);

int main(int argc, char *argv[])
{
	char charLine[MAXIMUM];
	int intTabSize;
	int i;

	intTabSize = 8;
	if(argc == 1)
	{
		printf("Input required.  Please provide a list of text with tab sequences.\n");
		printf("Some terminals like bash require double tabs as follows \\\\t\n");
		return 1;
	}

	for(i = 1; i < argc; i++)
	{
		strcpy(charLine, argv[i]);

		entab(charLine, MAXIMUM, intTabSize);

		printf("%s", charLine);
	}

	printf("\n");

	return 0;
}

/* entab:  Replaces strings of spaces with tabs */
int entab(char string[], int limit, int tabsize)
{
	int i,c;
	int blockcounter, arraypos;
	int intSpaces;
	int stringSize;

	blockcounter = 0;
	arraypos = 0;
	intSpaces = 0;

	stringSize = strlen(string);

	for(i = 0; i <= stringSize && i < limit - 1 && arraypos < limit - 1; i++)
	{
		++arraypos;

		if((blockcounter + 1) == tabsize)
		{
			for(; blockcounter >= 0 && string[arraypos - (tabsize - blockcounter)] == ' '; --blockcounter)
					++intSpaces;
			
			if(intSpaces > 1)
			{
				arraypos -= intSpaces;
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
