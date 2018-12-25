#include <ctype.h>
#include <stdio.h>
#include "getungetch.h"

/* getword:  get next word or character from input */
int getaword(char *word, int lim)
{
	int c;
	char *w = word;

	while(isspace(c = getch()))
		;

	if(c != EOF)
		*w++ = c;

	if(isdigit(c))
	{
		while(isdigit(c = getch()))
			*w++ = c;

		ungetch(c);
	}
	else
	{
		if(!(isalpha(c) || c == '_'))
		{
			*w = '\0';
			return c;
		}

		for(; --lim > 0; w++)
			if(!(isalnum(*w = getch()) || *w == '_'))
			{
				ungetch(*w);
				break;
			}
	}

	*w = '\0';
	return word[0];
}
