/* Modified for exercise 4-3.  Modulus and negative numbers. */
/* Modified for exercise 4-4.  Adds commands */

#include <ctype.h>
#include <stdio.h>
#define	NUMBER	0
#define	COMMAND	1

int getch(void);
void ungetch(int);

int getop(char s[])
{
	int i, c;

	while((s[0] = c = getch()) == ' ' || c == '\t')
		;

	s[1] = '\0';

	i = 0;
	if(!isdigit(c) && c != '.' && c != '-')		/* return all operators except - */
	{
		if(c == '+' || c == '*' || c == '/' || c == '%' || c == '\n' || c == EOF)	/* return all normal operators and functioning sequences for operations */
			return c;
		else
		{
			while(isalpha(s[++i] = c = getch()))	/* gets letters for commands and future variables etc */
				;
			
			s[i] = '\0';
			if(c != '\n')	/* puts every character that was not newline back into the buffer */
				ungetch(c);
			return COMMAND;	/* returns that there is a command waiting in s[] */
		}		
			
	}
	
	if(c == '-' && !isdigit(s[++i] = c = getch()))
	{
		if(c == '\n')
		{
			ungetch(c);
			return '-'; 
		}
	}

	if(isdigit(c))
		while(isdigit(s[++i] = c = getch()))
			;


	if(c == '.')
		while(isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	return NUMBER;
}
