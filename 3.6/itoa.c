/* itoa:  Takes a interger and converts it to a string. */

#include <stdio.h>
#include <string.h>

#define	MAXIMUM	1024

void itoa(int n, char s[]);
void reverse(char s[]);

int main()
{
	int number = 5;
	char string[MAXIMUM];	
	
	itoa(number, string);

	printf("Number is %d\n", number);
	printf("Number string is %s\n", string);

	return 0;
}

void itoa(int n, char s[])
{
	int i, sign;

	if((sign = n) < 0)
		n = -n;

	i = 0;

	do
	{
		s[i++] = n % 10 + '0';
	}while((n /= 10) > 0);

	if(sign < 0)
		s[i++] = '-';	
	s[i++] = '\0';
	reverse(s);
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
