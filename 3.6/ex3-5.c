/* Exercise 3-5.  Write the function itob(n,s,b) that converts the integer n into a base b character representation in the string s.  In particular, itob(n,s,16) formats n as a hexadecimal integer in s. */

#include <stdio.h>
#include <string.h>

#define	MAXIMUM	1024

void itob(int n, char s[], int b);
void reverse(char s[]);

int main()
{
	int number = 4783;
	char string[MAXIMUM];	
	int base = 16;

	itob(number, string, base);

	printf("Number is: %d\n", number);
	printf("Base is: %d\n", base);
	printf("Number string is: %s\n", string);

	return 0;
}

void itob(int number, char string[], int base)
{
	int i, sign;

	if((sign = number) < 0)
		number = -number;

	i = 0;
	
	 
	do
	{
		if((number % base) >= 10)
			string[i++] = ((number % base) - 10) + 'A';
		else
			string[i++] = number % base + '0';
	}while((number /= base) > 0);

	if(sign < 0)
		string[i++] = '-';	
	string[i++] = '\0';
	reverse(string);
}

void reverse(char s[])
{
	int c, i ,j;

	for(i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
