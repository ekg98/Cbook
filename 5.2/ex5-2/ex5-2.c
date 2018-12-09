/* Exercise 5-2.  Write getfloat, the floating-point analog of getint.  What type does getfloat return as its function value. */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define YES	1
#define NO	0

int getch(void);
void ungetch(int);
int getfloat(float *pn);

int main()
{
	float *floatpointer;
	int returnvalue;
	float number;

	floatpointer = &number;

	while((returnvalue = getfloat(floatpointer)) != EOF)
	{
		printf("return value is: %d\n", returnvalue);
		printf("Pointer value is %f\n", *floatpointer);
		printf("float = %f\n", number);
	}
	return 0;
}

int getfloat(float *pn)
{
	int c, sign;
	int signholder;
	int signtoggle = 0;
	int afterdecimal = 0;
	int numbersafter = NO;

	while(isspace(c = getch()))
		;

	if(!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
	{
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1 : 1;

	if(c == '+' || c == '-')
	{
		signholder = c;
		c = getch();
		if(!isdigit(c) && c != '.')
			ungetch(signholder);
		else
			*pn = 0;

		signtoggle = YES;
	}


	if(isdigit(c))
	{
		for(*pn = 0; isdigit(c); c = getch())
			*pn = 10 * *pn + (c - '0');
		numbersafter = YES;

	}
	
	if(c == '.')
	{
		c = getch();
		if(isdigit(c) && numbersafter == NO)
		{
			*pn = 0;
			ungetch(c);
		}
		else
			ungetch(c);
		
		while(isdigit(c = getch()))
		{
			++afterdecimal;
			*pn = 10 * *pn + (c - '0');
		}
		*pn *= pow(10,(-1 * afterdecimal));
	}

	if(sign == -1)
		*pn *= sign;	

	if(c != EOF && signtoggle != YES)
		ungetch(c);
	
	return c;
}
