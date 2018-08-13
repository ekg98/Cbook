/* Exercise 3-6.  Write a version of itoa that accepts three arguments instead of two.  The third argument is a minimum field width; the converted number must be padded with blanks on the left if necessary to make it wide enough. */

#include <stdio.h>
#include <string.h>

#define	MAXIMUM	1024

void itoa(int n, char s[], int w);
void reverse(char s[]);

int main()
{
	int number = 5000;
	char string[MAXIMUM];	
	int fieldwidth = 5;

	itoa(number, string, fieldwidth);

	printf("Number is %d\n", number);
	printf("Number string is %s\n", string);

	return 0;
}

void itoa(int n, char s[], int width)
{
	int i, sign;

	if((sign = n) < 0)
		n = -n;

	i = 0;

	do
	{
		s[i++] = n % 10 + '0';
		--width;
	}while((n /= 10) > 0);

	if(sign < 0)
		s[i++] = '-';	

	while(width > 0)
	{
		--width;
		s[i++] = ' ';
	}

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
