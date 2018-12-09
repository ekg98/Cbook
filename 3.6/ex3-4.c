/* Exercise 3-4.  In a two's complement number representation, our version of itoa does not handle the largest negative number, that is, the value of n equal to -(2^wordsize-1).  Explain why not.  Modify it to print that value correctly, regardless of the machine on which it runs. */

/* The -n is used to flip the number from negative to positive.  INT_MAX will always be -1 in excursion from INT_MIN.  This is due to how two's complement works.  Binary inversion and adding 1 for a negative number.  This means you lose that 1 on the upper side of the sign. */

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define	MAXIMUM	1024
#define	YES	1
#define	NO	0

void itoa(int n, char s[]);
void reverse(char s[]);

int main()
{
	int number = INT_MIN;
	char string[MAXIMUM];	
	
	itoa(number, string);

	printf("The maximum/minimum size of a int: %d/%d\n", INT_MAX, INT_MIN);
	printf("Number is %d\n", number);
	printf("Number string is %s\n", string);

	return 0;
}

void itoa(int n, char s[])
{
	int i, sign;
	int min = NO;

	if(n == INT_MIN)
	{
		n += 1;
		min = YES;
	}
	else
		min = NO;

	if((sign = n) < 0)
		n = -n;

	i = 0;

	do
	{
		if(min == YES)
		{
			s[i++] = ((n % 10 + '0') + 1);
			min = NO;
		}
		else
			s[i++] = n % 10 + '0';
	}while((n /= 10) > 0);

	if(sign < 0)
		s[i++] = '-';
	s[i] = '\0';
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
