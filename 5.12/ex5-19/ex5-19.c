/* Exercise 5-19.  Modify undcl so that it does not add redundant parentheses to declarations */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "getungetch.h"

#define	MAXTOKEN	100
#define	YES	1
#define	NO	0

enum {NAME, PARENS, BRACKETS, ERROR, CLEAN};

int gettoken(void);
void reset(void);

int tokentype;
char token[MAXTOKEN];
char out[100];
int nextToken;

int main()
{
	int type;
	char temp[MAXTOKEN];

	while(gettoken() != EOF)
	{
		strcpy(out, token);
		while((type = gettoken()) != '\n' && nextToken != '\n')
		{
			if(type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if(type == '*')					/* Detecting a pointer dcl to something */	
			{
				nextToken = gettoken();
				if(nextToken == '\n')				/* if you find a pointer dcl at the end of a line, amend out to point to something */
				{
					sprintf(temp, "*%s", out);
					strcpy(out, temp);
					break;
				}
				else if(nextToken == NAME)			/* if you find a name after a pointer dcl */
				{
					sprintf(temp, "*%s", out);
					sprintf(out, "%s %s", token, temp);
				}
				else						/* pointer to a function */
				{	
					sprintf(temp, "(*%s)", out);
					strcpy(out, temp);
				}
			}
			else if(type == NAME)
			{
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			}
			else
			{
				printf("invalid input at %s\n", token);
				tokentype = ERROR;
				reset();
				break;
			}
		}
		printf("%s\n", out);
		reset();
			
	}
	return 0;
}

int gettoken(void)
{
	int c;

	char *p = token;

	while((c = getch()) == ' ' || c == '\t')
		;

	if(c == '(')
	{
		if((c = getch()) == ')')
		{
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else
		{
			ungetch(c);
			return tokentype = '(';
		}
	}
	else if(c == '[')
	{
		for(*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	}
	else if(isalpha(c))
	{
		for(*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	else
		return tokentype = c;

}

void reset(void)
{
	out[0] = '\0';
	token[0] = '\0';
	nextToken = CLEAN;

	resetbuf();

	if(tokentype == ERROR)
	{
		printf("Error: Please try again.\n");
		tokentype = CLEAN;
	}
	else
		tokentype = CLEAN;
}
