#include <ctype.h>
#include <stdio.h>
#include "getungetch.h"

/* getword:  get next word or character from input */
int getaword(char *word, int lim, int *lineNumber)
{
	int c;
	char *w = word;

	while(isspace(c = getch()))
		;

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
				if(*w == '/' && c == '*')	/* tests to see if c previously held asterisk */
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
					*lineNumber += 1;
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
					*lineNumber += 1;
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
					*lineNumber += 1;

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
				*lineNumber += 1;

			*w = '\0';
			return c;
		}

		for(; --lim > 0; w++)
		{
			if(!(isalnum(*w = getch()) || *w == '_'))
			{
				if(*w == '\n')
					*lineNumber += 1;
				else
					ungetch(*w);

				break;
			}
		}
	}

	*w = '\0';
	return word[0];
}
