/* Exercise 5-12.  Extend entab and detab to accept the shorthand.  "entab -m +n" to mean tab stops every n columns , starting at column m.  Choose convenient default behavior. */

/* This is modified from exercise 5-11. */
/* entab takes a string as a command line argument.  Converts tabsize spaces into tabs.  This variant has provisions for command line arguments */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define	MAXIMUM	1024

int entab(char *s, int lim, int tabsize, int intStartPosition);

int main(int argc, char *argv[])
{
	char charLine[MAXIMUM];
	int intTabSize = 8;		/* initial tab size */
	int intStartPosition = 0;
	int i;

	if(argc == 1)
	{
		printf("Entab:  Converts spaces into tabs in input text.  ");
		printf("Input required.  Please provide a list of text with spaces.\n");
		printf("Some terminals like bash require double quotes like \"text\".\n");
		return 1;
	}

	for(i = 1; i < argc; i++)
	{
		switch(*argv[i])
		{
			case '-':
				if(*(argv[i] + 1) == 'h')	/* helpful argument */
				{
					printf("Entab:  Converts spaces into tabs in input text.\n");
					printf("\nSome terminals like bash require double quotes around your text like \"text\".\n");
					printf("\nAvailable entab arguments:\n");
					printf("+n \'n\' is a number that controls the size of a tab.\n");
					printf("-m \'m\' is a number that controls the starting position of entab.\n");
					return 0;
				}

				if(isdigit(*(argv[i] + 1)))			/* changes the starting position of where entab starts functioning */
					intStartPosition = atoi(argv[i] + 1);
			       break;
			case '+':
				if(isdigit(*(argv[i] + 1)))			/* changes the size of inttabsize from a argument */
					intTabSize = atoi(argv[i] + 1);
			       break;
			default:
				strcpy(charLine, argv[i]);
				printf("before: %s", charLine);
				entab(charLine, MAXIMUM, intTabSize, intStartPosition);
				printf("\n");
				printf("after:  %s", charLine);
				break;
		}
	}

	printf("\n");

	return 0;
}

/* entab:  Replaces strings of spaces with tabs */
int entab(char *string, int limit, int tabsize, int intStartPosition)
{
	int i;
	int blockcounter = 0, arraypos = 0;
	int intSpaces = 0;
	char tempstring[MAXIMUM];


	strcpy(tempstring, string);		/* copy the string passed by main function to a temporary string.  This is so it doesnt overwrite the data. */


	for(i = 0; tempstring[i] != '\0' && i < limit - 1 && arraypos < limit - 1; i++)		/* count to the end of the input string or the maximum size of the array.  Whatever comes first. */
	{
		string[arraypos++] = tempstring[i]; 
		blockcounter++;

		if(blockcounter == tabsize)
		{
			for(; i >= intStartPosition && blockcounter > 0 && string[(arraypos - 1) - (tabsize - blockcounter)] == ' '; --blockcounter)	/* count the number of spaces going backwards from tab stop */
				intSpaces++;	

			if(intSpaces > 1)	/* replace with a tab if counting backwards from the tab stop there are more than 1 space */
			{
				arraypos -= intSpaces;
				string[arraypos] = '\t';
				++arraypos;
			}
			intSpaces = 0;
			blockcounter = 0;
		}
	}

	string[arraypos] = '\0';
		
	return strlen(string);
}
