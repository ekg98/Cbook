/* Modified for exercise 4-3.  Modulus and negative numbers. */
/* Modified for exercise 4-4.  Adds commands */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define	NUMBER	0
#define	COMMAND	1
#define	VARIABLESTORE 2
#define	VARIABLE 3
#define	LASTVALUE 4
#define	MAXIMUM	1024

int getch(void);
void ungetch(int);
void resetbuf(void);
int getaline(char s[], int lim);

int ccounter = 0;
char inputarray[MAXIMUM];

int getop(char s[])
{
	int i, c;
	if(ccounter == 0)
		getaline(inputarray, MAXIMUM);

		while((s[0] = c = inputarray[ccounter++]) == ' ' || c == '\t')
			;

		s[1] = '\0';

		i = 0;
		if(!isdigit(c) && c != '.' && c != '-')		/* return all operators except - */
		{
			if(c == '+' || c == '*' || c == '/' || c == '%' || c == '\n' || c == EOF)	/* return all normal operators and functioning sequences for operations */
			{
				
				if(c == '\n')
					ccounter = 0;
				return c;
			}
			else
			{
				while(isalpha(s[++i] = c = inputarray[ccounter++]))	/* gets letters for commands and future variables etc */
					;
			
				s[i] = '\0';
				/*if(c != '\n')*/
					--ccounter;

				if((strlen(s) == 1) && s[0] == '~')
					return LASTVALUE;

				if((strlen(s) == 1) && isalpha(s[0]))	/* is a single letter */
				{
					if(isdigit(c))
						while(isdigit(s[i++] = c = inputarray[ccounter++]))
						;
					else	/* is just one letter */
						return VARIABLE;

					if(c == '.')
						while(isdigit(s[i++] = c = inputarray[ccounter++]))
							;
					s[i] = '\0';

					if(c != '\n')
						--ccounter;
					return VARIABLESTORE;	/* return signal to store information in variable array instead of applying it to a operation */

				}

				/*ccounter = 0;*/
				if(c != '\n')
					ccounter = 0;
				if(strcmp(s, "quit") == 0) /* return EOF and quit program if you type quit */
					return EOF;
				else
					return COMMAND;	/* returns that there is a command waiting in s[] */
			}		
			
		}
	
		if(c == '-' && !isdigit(s[++i] = c = inputarray[ccounter++]))
		{
			if(c == '\n')
			{	
				--ccounter;
				/*ungetch(c);*/
				return '-'; 
			}
		}

		if(isdigit(c))
			while(isdigit(s[++i] = c = inputarray[ccounter++]))
				;


		if(c == '.')
			while(isdigit(s[++i] = c = inputarray[ccounter++]))
				;
		s[i] = '\0';
	
		/*ungetch(c);*/
		--ccounter;
		return NUMBER;
}

void resetcounter(void)
{
	ccounter = 0;
}
