/* Exercise 5-20.  Expand dcl to handle declarations with function argument types, qualifiers like const, and so on. */
/* Modified for Exercise 5-18. */

/* Because ritche didn't specify what recover means.  I take it to mean restart from beginning.  Thats what this program does if it encounters a error. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "getungetch.h"

#define	MAXTOKEN	100

enum { NAME, PARENS, BRACKETS, ERROR, CLEAN, ARG, ARGPTR, ARGARRAY };

void dcl(void);
void dirdcl(void);
int gettoken(void);
void recovery(void);

int tokentype;			/* type of last token */
char token[MAXTOKEN];		/* last token string */
char name[MAXTOKEN];		/* identifier name */
char datatype[MAXTOKEN];	/* data type = char, int, etc. */
char out[1000];			/* output string */

int main()
{
	while(gettoken() != EOF)		/* first token on the line */
	{
		strcpy(datatype, token);	/* is the datatype */
		out[0] = '\0';
		
		dcl();				/* parse rest of line */
		
		if(tokentype != '\n')		/* if we found garbage at the end of analyzing the string assume its a syntax error */
		{
			printf("syntax error\n");
			recovery();
			continue;
		}
			
		printf("%s: %s %s\n", name, out, datatype);		/* print the output of the results */
		recovery();
	}
	return 0;
}

/* dcl:  parse a declarator */
void dcl(void)
{
	int ns;

	for(ns = 0; gettoken() == '*'; )	/* call gettoken to count *'s if some are found keep track of them */
		ns++;

	if(tokentype != '\n')	/* call dirdcl to find everything else thats not a * */
		dirdcl();

	if(tokentype != ERROR)
		while(ns-- > 0)				/* if dcl found that it was a pointer amend the results of dirdcl to specify its pointing to something */
			strcat(out, " pointer to");
	else
		recovery();
}

/* dirdcl:  Analyze everything inside brackets thats not a * */
void dirdcl(void)
{
	int type;
	

	if(tokentype == '(')						/* sitting on a open paren.  Next could be a name or a dcl */
	{
		dcl();							/* check to see if you have a dcl or a dirdcl.  Go through the opened paren area and look for *, name, and opposing paren */
		if(tokentype != ')')
		{
			printf("error: missing )\n");			/* if a opposing paren was not found then generate error message */
			tokentype = ERROR;
			return;
		}
	}
	else if(tokentype == NAME)		/* If dirdcl returned a name set the name string to the name dirdcl returned */
	{
		strcpy(name, token);
	}
	else if(tokentype == ARG)
	{
		strcat(out, " function passing ");
		strcat(out, token);
	}
	else if(tokentype == ARGPTR)
	{
		strcat(out, " function passing a pointer to ");
		strcat(out, token);
	}
	else
	{
		printf("error: expected name or (dcl)\n");		/* if you have a open paren and dirdcl didn't find a name.  Generate a error message */
		tokentype = ERROR;
		return;
	}

	while((type = gettoken()) == PARENS || type == BRACKETS)
	{
		if(type == PARENS)					/* if dirdcl found a complete set of parens.  You are a function */
			strcat(out, " function returning");
		else							/* else if your not parens dirdcl must have found you must be brackets */
		{
			strcat(out, " array");
			strcat(out, token);				/* the name of the array */
			strcat(out, " of");
		}
	}

	if(tokentype == '(')						/* if a open paren after it looked for a group of closed parens is found, run dirdcl back through to look for new works or some type of error */
		dirdcl();
}

/* gettoken:  Gets a character at a time from the input and analyzes it.  Depending on what it is the return tokentype is changed. */
int gettoken(void)
{
	int c;
	char *p = token;


	while((c = getch()) == ' ' || c == '\t' || c == ',')		/* filter out all whitespace */
		;

	if(c == '(')
	{
		if((c = getch()) == ')')			/* Look for the opposing paren.  update token with the information  */
		{
			strcpy(token, "()");
			return tokentype = PARENS;		/* return that it found a complete set of parens */
		}
		else						/* if a full set of parens were not found.  Push the last char back into the buffer for the next run */
		{
			ungetch(c);
			return tokentype = '(';			/* return that it is sitting on a paren.  Could be a name thats coming or something else */
		}
	}
	else if(c == '[')					/* look for brackets */
	{
		for(*p++ = c; (*p++ = getch()) != ']'; )	/* get information out of the buffer or input until it finds the opposing bracket in the string */
			;

		*p = '\0';
		return tokentype = BRACKETS;			/* return that it found a set of brackets */
	}
	else if(isalpha(c))					/* look for alphabetical characters.  NAME  Could be a function or an array name */
	{
		for(*p++ = c; isalnum(c = getch()); )		/* keep going unless it finds something thats not a letter */
			*p++ = c;

		*p = '\0';
		ungetch(c);

		if(strcmp(token, "int") == 0)
		{
			while((c = getch()) == ' ' || c == '\t')
				;

			if(c == '(')
			{
				ungetch(c);
				return tokentype = NAME;
			}
			else if(c == '*')
				return tokentype = ARGPTR;
			else if(c == ',' || c == ')')
			{
				if(c == ')')
					ungetch(c);

				return tokentype = ARG;
			}
			else
				ungetch(c);
			

		}



		return tokentype = NAME;			/* return that it found a name of something */
	}
	else
		return tokentype = c;				/* return anything else thats not a paren, bracket, or a name.  Like a newline or other control sequences. */
}

/* recovery function resets everything to a default state for another pass at data input */
void recovery(void)
{
	
	/* reset all the strings */
	out[0] = '\0';
	datatype[0] = '\0';
	name[0] = '\0';
	token[0] = '\0';

	resetbuf();

	if(tokentype == ERROR)
	{
		printf("Error: Please try again.\n");
		tokentype = CLEAN;
	}
	else
		tokentype = CLEAN;
}
