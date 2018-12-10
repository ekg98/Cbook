#include <ctype.h>
#include <stdio.h>
#include "getungetch.h"

enum {NO, YES};

/* getword:  get next word or character from input.  lineNumber is a populated returned value that contains the line number of the word returned. */
int getaword(char *word, int lim, int *lineNumber)
{
	int c;
	char *w = word;
	int newLine = NO;
	static int internalLineNumber = 1;

	while(isspace(c = getch()))
		if(c == '\n')
			internalLineNumber += 1;

	if(c != EOF)
		*w++ = c;

	/* comments */
	if(c == '/')
	{
		*w = getch();
		if(*w  == '*')
		{
			w++;
			for(; --lim > 0; w++)
			{
				*w = getch();

				if(*w == '\n')
					internalLineNumber += 1;

				if(c == '*' && *w == '/')	/* tests to see if c previously held asterisk */
				{
					w++;
					break;
				}

				c = *w;				/* if the loop got this far store previous character in c for next run's check */
			}
		}
		else if(*w == '/')	// checks for cpp style comments
		{
			w++;
			for(; --lim > 0; w++)
			{
				*w = getch();
				if(*w == '\n')
				{
					newLine = YES;
					break;
				}
			}
		}
	}
	/* preprocessor control directives */
	else if(c == '#')
	{
		for(; --lim > 0; w++)
		{
			if(!isalnum(*w = getch()))
			{
				if(*w == '\n')
					newLine = YES;
				else
					ungetch(*w);

				break;
			}
		}
	}
	/* string constants */
	else if(c == '"')
	{
		for(; --lim > 0; w++)
		{
			*w = getch();

			if(*w == '"' || *w == '\n')
			{
				if(*w == '\n')
					newLine = YES;

				w++;
				break;
			}
		}
	}
	/* keywords now accepts underscores */
	else
	{
		if(!(isalpha(c) || c == '_'))
		{
			if(c == '\n')
				newLine = YES;

			*w = '\0';
			return c;
		}

		for(; --lim > 0; w++)
		{
			if(!(isalnum(*w = getch()) || *w == '_'))
			{
				if(*w == '\n')
					newLine = YES;
				else
					ungetch(*w);

				break;
			}
		}
	}

	if(newLine == YES)
	{
		newLine = NO;
		*lineNumber = internalLineNumber;
		internalLineNumber += 1;
	}
	else
		*lineNumber = internalLineNumber;

	*w = '\0';
	return word[0];
}
