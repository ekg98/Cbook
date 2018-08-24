/*  Exercise 5-13.  Write the program tail,  which prints the last n lines of its input.  By default, n is 10, let us say, but it can be changed by an optional argument, so that tail -n prints the last n lines. */
/*  The program should behave rationally no matter how unreasonable the input or the value of n.  Write the program so it makes the best use of available storage; lines should be stored as in the sorting program */
/*  of section 5.6, not in a two-dimensional array of fixed size. */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "alloc.h"	/* header file for alloc function char *alloc(int) */

#define	INPUTBUF	1024	/* Maximum buffer size */

int getaline(char *s, int limit);
int push(char *string, char *linesarray[], int linelimit);

int main(int argc, char *argv[])
{
	int argumentCounter = 1;
	int lineQuantity = 10;	/* default line quantity */
	int i;

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
					return 1;
				}
			}
			argumentCounter++;
		}

	}

	char *lines[lineQuantity];	/* Allocate pointer array for lines based off default value or arguments */
	char inputLineBuffer[INPUTBUF];

	for(i = 0; i < lineQuantity - 1; i++)	/* NULL the pointer array */
		lines[i] = NULL;	

	while(getaline(inputLineBuffer, INPUTBUF) > 0)
	{
		if(push(inputLineBuffer, lines, lineQuantity))
		{
			printf("Error: Could not allocate enough memory.\n");
			return 1;
		}
	}

	printf("\n");

	for(i = lineQuantity - 1; i >= 0; i--)
		if(lines[i] != NULL)
			printf("%s",lines[i]);
	
	return 0;
}

/* Standard getline function.  Grabs keyboard input and populates the string to the limit. */
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

int push(char *string, char *linesarray[], int linelimit)
{
	int stringsize;
	char *newstring = NULL;
	char *tempstring = NULL;
	int i;

	stringsize = (strlen(string) + 1);

	if((newstring = alloc(stringsize)) == NULL)	/* Allocate memory for the string transfer */
		return 1;

	strcpy(newstring, string);			/* copy the new string */
	

	while(--linelimit)
	       	linesarray[linelimit] = linesarray[linelimit - 1];

	linesarray[0] = newstring;

	return 0;
}

