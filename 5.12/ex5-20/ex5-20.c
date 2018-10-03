/* Exercise 5-20.  Expand dcl to handle declarations with function argument types, qualifiers like const, and so on. */
/* Modified for Exercise 5-18. */
/* Modified for Exercise 5-20.  Not perfect, does not handle unknown types in function arguments. */

/* Because ritche didn't specify what recover means.  I take it to mean restart from beginning.  Thats what this program does if it encounters a error. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "getungetch.h"

#define	MAXTOKEN	100

enum { NAME, PARENS, BRACKETS, ERROR, CLEAN, ARG, ARGPTR, ARGARRAY, MODIFIER, YES, NO };

void dcl(void);
void dirdcl(void);
int gettoken(void);
void recovery(void);
int argcheck(char *);
int modcheck(char *);

int tokentype;			/* type of last token */
char token[MAXTOKEN];		/* last token string */
char name[MAXTOKEN];		/* identifier name */
char datatype[MAXTOKEN];	/* data type = char, int, etc. */
char modifier[MAXTOKEN];	/* last modifier */
char out[1000];			/* output string */
int foundarg = NO;		/* toggle if detected a function argument */
int foundmod = NO;		/* toggle if detected a modifier for a datatype */

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
		if(tokentype != ')' && foundarg == NO)
		{
			printf("error: missing )\n");			/* if a opposing paren was not found then generate error message */
			tokentype = ERROR;
			return;
		}
		else if(tokentype == ')')	/* dcl returns ) when it has processed arguments */
		{
			foundarg = NO;
			type = gettoken();
			return;
		}
		else				/* error handling if dcl returns garbage it cant handle */
		{
			printf("error: unknown\n");
			tokentype = ERROR;
			return;
		}
	}
	else if(tokentype == NAME)		/* If dirdcl returned a name set the name string to the name dirdcl returned */
	{
		strcpy(name, token);
	}
	else if(tokentype == ARG || tokentype == ARGPTR || tokentype == ARGARRAY || tokentype == MODIFIER)	/* if found a argument of some kind */
	{
		foundarg = YES;
		
		/* First ARG, ARGPTR, ARGARRAY, and MODIFIER  check.  This deposits the first argument into the out string */
		if(tokentype == ARG)
		{
			strcat(out, " function passing ");
			strcat(out, token);
			strcat(out, ",");
		}
		else if(tokentype == ARGPTR)
		{
			strcat(out, " function passing a pointer to ");
			strcat(out, token);
			strcat(out, ",");
		}
		else if(tokentype == ARGARRAY)
		{
			strcat(out, " function passing an array of ");
			strcat(out, token);
			strcat(out, ",");
		}
		else if(tokentype == MODIFIER)
		{
			foundmod = YES;
			strcpy(modifier, token);
		}

		/* Checks to see if there is a second or more arguments,  deposits them in the out string */
		while((type = gettoken()) == ARG || type == ARGPTR || type == ARGARRAY || type == MODIFIER)
		{
			if(type == ARG)			/* found a argument, adjust output string and add modifier */
			{
				strcat(out, " function passing ");
				if(foundmod == YES)
				{
					foundmod = NO;
					strcat(out, modifier);
					strcat(out, " ");
				}
				strcat(out, token);
				strcat(out, ",");

			}
			else if(type == ARGPTR)		/* found a pointer argument, adjust output string and add modifier */
			{
				strcat(out, " function passing a pointer to ");
				if(foundmod == YES)
				{
					foundmod = NO;
					strcat(out, modifier);
					strcat(out, " ");
				}
				strcat(out, token);
				strcat(out, ",");
			}
			else if(type == ARGARRAY)	/* found a array argument, adjust output string and add modifier */ 
			{
				strcat(out, " function passing an array of ");
				if(foundmod == YES)
				{
					foundmod = NO;
					strcat(out, modifier);
					strcat(out, " ");
				}
				strcat(out, token);
				strcat(out, ",");
			}
			else if(type == MODIFIER)	/* found a modifier in a function declaration, record so and store */
			{
				foundmod = YES;
				strcpy(modifier, token);
			}

		}

		if(tokentype == ')')		/* checks if its the end of a function declaration */
		{
			strcat(out, " function returning");
		}
		else				/* error handling */
		{
			printf("error: missing ) after function arguments.\n");
			tokentype = ERROR;
			return;
		}


	}
	else
	{
		printf("error: expected name or (dcl)\n");		/* if you have a open paren and dirdcl didn't find a name.  Generate a error message */
		tokentype = ERROR;
		return;
	}
	
	if(tokentype != ')')
	{
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
		
		if(modcheck(token) == 0)	/* check to see if the token is a modifier */
			return tokentype = MODIFIER;

		if(argcheck(token) == 0)	/* check to see if the token is a argument */
		{
			while((c = getch()) == ' ' || c == '\t')	/* remove any white space to next character */
				;

			if(c == '(')				/* if encountering a ( after a token assume its a name */
			{
				ungetch(c);
				return tokentype = NAME;
			}
			else if(c == '*')				/* if the next character makes it a pointer */
				return tokentype = ARGPTR;
			else if(c == '[')				/* if found a set of brackets it makes it a array */
			{
				c = getch();
				if(c == ']')
					return tokentype = ARGARRAY;
				else
				{
					printf("error: missing ]\n");
					return tokentype = ERROR;
				}
			}

			else if(c == ',' || c == ')')	/* run to the end of the argument or the end of the definition */
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

	if(tokentype == ERROR)	/* generate message if error, not so if just recovering */ 
	{
		printf("Error: Please try again.\n");
		tokentype = CLEAN;
	}
	else
		tokentype = CLEAN;
}

/* argcheck:  checks for valid arguments that are of standard datatypes */
int argcheck(char *arg)
{
	char *arglist[] = { "int", "char", "float", "double", "void" };
	int i, argmax, argreturnvalue;

	argmax = sizeof arglist / sizeof(char *);	/* calculates amount of arguments in the list */

	for(i = 0; i < argmax; i++)			/* looks for those arguments, if found return 0 */
	{
		if((argreturnvalue = strcmp(arg, arglist[i])) == 0)
			return 0;
	}

	return argreturnvalue;				/* if not found return discrepancy */
}

/* modcheck:  checks for valid modifiers that are of standard types */
int modcheck(char *modifier)
{
	char *modlist[] = { "short", "long", "signed", "unsigned" };
	int i, modmax, modreturnvalue;

	modmax = sizeof modlist / sizeof(char *);	/* calculates amount of modifiers in the list */

	for(i = 0; i < modmax; i++)			/* looks for those modifiers, if found return 0 */
	{
		if((modreturnvalue = strcmp(modifier, modlist[i])) == 0)
			return 0;
	}

	return modreturnvalue;				/* if not found return discrepancy */
}
