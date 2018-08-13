/* Modified and truncated for exercise expr 5.10. */

#include "expr.h"

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
	}
	
	if(c == '-' && !isdigit(s[++i] = c = getch()))
	{
			return '-'; 
	}

	if(isdigit(c))
		while(isdigit(s[++i] = c = getch()))
			;


	if(c == '.')
		while(isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	
	return NUMBER;
}
