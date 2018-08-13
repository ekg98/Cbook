/* Exercise 5-1.  As written, getint treats a + or - not followed by a digit as a valid representation of zero.  Fix it to push such a character back on the input. */

#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);
int getaint(int *pn);

int main()
{
	int *intpointer;
	int returnvalue;
	int integer;

	intpointer = &integer;

	while((returnvalue = getaint(intpointer)) != EOF)
	{
		printf("return value is: %d\n", returnvalue);
		printf("Pointer value is %d\n", *intpointer);
		printf("integer = %d\n", integer);
	}
	return 0;
}

int getaint(int *pn)
{
	int c, sign;
	int signholder;
	int signtoggle = 0;

	while(isspace(c = getch()))
		;

	if(!isdigit(c) && c != EOF && c != '+' && c != '-')
	{
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1 : 1;

	if(c == '+' || c == '-')
	{
		signholder = c;
		c = getch();
		if(!isdigit(c))
			ungetch(signholder);

		signtoggle = 1;
	}


	if(isdigit(c))
	{
		for(*pn = 0; isdigit(c); c = getch())
			*pn = 10 * *pn + (c - '0');

		*pn *= sign;
	}


	if(c != EOF && signtoggle != 1)
		ungetch(c);
	
	return c;
}
