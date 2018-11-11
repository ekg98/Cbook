/* Exercise 6-1.  Our version of getword does not properly handle underscores, string constants, comments, or preprocessor */
/* control lines.  Write a better version.  */

/* string constants complete */
/* preprocessor control lines complete */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "getungetch.h"

#define MAXWORD	100
#define NKEYS (sizeof keytab / sizeof(struct key))

struct key
{
	char *word;
	int count;
};

int getword(char *, int);
int binsearch(char *, struct key *, int);

struct key keytab[] = {
	"#define",	0,
	"#elif",	0,
	"#else",	0,
	"#endif",	0,
	"#error",	0,
	"#if",		0,
	"#ifdef",	0,
	"#ifndef",	0,
	"#include",	0,
	"#pragma",	0,
	"#undef",	0,
	"auto",		0,
	"break",	0,
	"case",		0,
	"char",		0,
	"const",	0,
	"continue",	0,
	"default",	0,
	"string constant('s)",	0,
	"unsigned",	0,
	"void",		0,
	"volatile",	0,
	"while",	0
};

int main()
{
	int n;
	char word[MAXWORD];
	char *wpointer = word;

	while(getword(word, MAXWORD) != EOF)
	{
		if(isalpha(word[0]) || word[0] == '#')
		{
			n = binsearch(word, keytab, NKEYS);
			if(n >= 0)
				keytab[n].count++;
		}

		if(word[0] == '\"')
		{
			while(*wpointer != '\0')
				wpointer++;
			
			if(*wpointer == '\0')
			{
				--wpointer;
				if(*wpointer == '\"')
				{
					n = binsearch("string constant('s)", keytab, NKEYS);
					if(n >= 0)
						keytab[n].count++;
				}
			}
		}
	}

	for(n = 0; n < NKEYS; n++)
	{
		if(keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
	}

	return 0;
}

/* binsearch:  find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;

	while(low <= high)
	{
		mid = (low + high) / 2;

		if((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if(cond > 0)
			low = mid + 1;
		else
			return mid;
	}

	return -1;
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
	int c;
	char *w = word;

	while(isspace(c = getch()))
		;

	if(c != EOF)
		*w++ = c;
	
	if(c == '#')
	{
		for(; --lim > 0; w++)
			if(!isalnum(*w = getch()))
			{
				ungetch(*w);
				break;
			}
	}
	else if(c == '\"')
	{
		for(; --lim > 0; w++)
		{
			*w = getch();

			if(*w == '\"' || *w == '\n')
			{
				w++;
				break;
			}
		}
	}
	else
	{
		if(!isalpha(c))
		{
			*w = '\0';
			return c;
		}

		for(; --lim > 0; w++)
			if(!isalnum(*w = getch()))
			{
				ungetch(*w);
				break;
			}
	}

	*w = '\0';
	return word[0];
}
