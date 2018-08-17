/* Exercise 5-12.  Extend entab and detab to accept the shorthand.  "detab -m +n" to mean tab stops every n columns, starting at column m.  Choose a convient default behavior. */

/* Levi showed me how to pass a tab on the command line.  Ctrl + v and then tab in bash. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define	MAXIMUM	1024

int detab(char *string, int limit, int tabsize, int intStartPosition);

int main(int argc, char *argv[])
{
	int i;
	int intTabSize = 8;
	int intStartPosition = 0;

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
		switch(*argv[i])
		{
			case '-':
				if(*(argv[i] + 1) == 'h')
				{
					printf("Detab:  Converts tab sequences in the input text into spaces.\n");
					printf("\nSome terminals like bash require double quotes around your text like \"text\\ttext\".\n");
					printf("\nAvailable detab arguments:\n");
					printf("+n \'n\' is a number that controls the size of a tab.\n");
					printf("-m \'n\' is a number that controls the starting position of detab.\n");
					return 0;
				}

				if(isdigit(*(argv[i] + 1)))
					intStartPosition = atoi(argv[i] + 1);
				break;
			case '+':
				if(isdigit(*(argv[i] + 1)))
					intTabSize = atoi(argv[i] + 1);
				break;
			default:
				if(strlen(argv[i]) > MAXIMUM)	/* if argv is too big exit program */
					return -1;
		
				strcpy(charLine, argv[i]);
				detab(charLine, MAXIMUM, intTabSize, intStartPosition);
				printf("%s", charLine);
		}
	}
	printf("\n");

}

int detab(char *string, int limit, int tabsize, int intStartPosition)
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
			if(stringCopy[i] == '\t' && i >= intStartPosition)
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
