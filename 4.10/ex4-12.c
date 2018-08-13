/* Exercise 4-12.  Write a recursive version of itoa() */
#include <stdio.h>

void itoa(int n, char s[]);

int main()
{
	char inputstring[1024];
	int number = -454;

	itoa(number, inputstring);
	
	printf("Number = %d\n", number);
	printf("String = %s\n", inputstring);

	return 0;
}

void itoa(int n, char s[])
{
	static int i = 0;

	if(n < 0)	/* if the number on the first call is negative then put a negative sign as the first place in the string.  Then make the number positive.  This will only happen on first call to the function. */
	{
		s[i++] = '-';
		n = -n;
	}
	if(n / 10)
		itoa(n / 10, s);	
	
	s[i++] = n % 10 + '0';
	/*}while((n /= 10) > 0);*/
	
	if((n / 10) < 1)
		s[i] = '\0';
}
