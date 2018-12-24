// Exercise 6-6.  Implement a simple version of the #define processor (i.e. no arguments) suitable for use with c programs, based on the routines of this section.
// You may also find getch and ungetch helpful.
// Modified from ex6-5.

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "nlist.h"
#include "tablelookup.h"
#include "getungetch.h"
#include "getaword.h"

#define MAXWORD	1000

int main()
{
	struct nlist *definetable = NULL;
	char c, word[MAXWORD];
	char name[MAXWORD], defn[MAXWORD];
	char *wp = word;

	while((c = getch()) != EOF)
	{
		if(c == '#')
		{
			wp = c;	// put # in the string
			wp++;

			while(isalpha(c = getch()))	// get the next character and check if its a letter
			{
				wp = c;
				wp++;
			}

			wp = '\0';
			ungetch(c);

			if(strcmp(word, "#define") == 0)	// assumes after define there is a name and a definition and adds them to the table
			{
				getaword(name, MAXWORD);
				getaword(defn, MAXWORD);

				definetable = install(name, defn);
			}
			else
				ungets(word);
		}
		else
			printf("%c", c);
	}

	return 0;
}
