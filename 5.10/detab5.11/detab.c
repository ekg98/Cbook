/* Exercise 5-11.  Detab.  Modify the programs entab and detab to accept a list of tab stops as arguments.  Use default tab settings if there are no arguments. */

/* This program theoretically works but cant be tested on bash unless I can figure out a way to pass a tab on the command line */

#include <stdio.h>
#include <string.h>
#define	MAXIMUM	1024

int detab(char *string, int limit, int tabsize);

int main(int argc, char *argv[])
{
	int i;
	int intTabSize = 8;
	char charCurrentLine[MAXIMUM];

	char charLine[intTabSize * MAXIMUM];
	
	if(argc == 1)
	{
		printf("Detab:  Converts tab sequences into spaces.\n");
		printf("Input required.  Please provide a list of text with tab sequences.\n");
		printf("Some terminals like bash require double quotes like \"text\\ttext\".\n");
	}

	for(i = 1; i < argc; i++)
	{
		if(strlen(argv[i]) > MAXIMUM)	/* if argv is too big exit program */
			return -1;
		
		strcpy(charLine, argv[i]);
		detab(charLine, MAXIMUM, intTabSize);

		printf("%s", charLine);
	}
	printf("\n");

}

int detab(char *string, int limit, int tabsize)
{
	int i;
	int intSpaceCounter = 0;
	int intOutputPos = 0;
	int intStringLength = 0;

	char stringCopy[limit * tabsize];

	strcpy(stringCopy, string);

	intStringLength = strlen(stringCopy);

		for(i = 0; i <= intStringLength; ++i)
		{
			if(stringCopy[i] == '\t')
			{
				for(; intSpaceCounter < tabsize; ++intSpaceCounter)
				{
					string[intOutputPos] = ' ';
					++intOutputPos;
				}
			}
			else
			{
				string[intOutputPos] = stringCopy[i];
				++intSpaceCounter;
				++intOutputPos;
			}
			
			if(intSpaceCounter == tabsize)
				intSpaceCounter = 0;
		}
		intSpaceCounter = 0;
		intOutputPos = 0;

	return strlen(string);
}
