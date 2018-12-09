/* htoi:  Write the function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value.  The allowable digits are 0 through 9, a through f, and A through F. */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define	YES	1
#define NO	0
#define	HEXSIZE	16	/* How many 0x digits can the array hold */

int htoi(char string[]);
int gethex(char string[], int limit);

int main()
{
	char hexstring[HEXSIZE + 1];
	int decimal = 0;

	if(gethex(hexstring, HEXSIZE + 1))
	{
		printf("Hex input not formatted correctly.\n");
		return 1;
	}
	decimal = htoi(hexstring);

	printf("Hex value: %s\nDecimal value: %d\n", hexstring, decimal);

	return 0;
}

/* htoi:  Converts hexadecimal string to integer */

int htoi(char s[])
{
	int intDecimal = 0;
	int i, intNibble = 0;
	int isNumber = NO, isLetter = NO;

	for(i = 0; s[i] != '\0'; ++i)
		;

	while(i >= 0)
	{
		if(i == 1)
		{
			if(tolower(s[1]) == 'x' && s[0] == '0')
			{
				i = 0;
				return intDecimal;
			}
		}
		else
		{
			if(s[i] == '\0')
				--i;

			if(s[i] >= '0' && s[i] <= '9')
			{ 
				intDecimal += (s[i] - '0') * pow(16, intNibble);
				--i;
				++intNibble;
				isNumber = YES;
			}
			else
				isNumber = NO;
			
			if(tolower(s[i]) >= 'a' && tolower(s[i]) <= 'f')
			{
				intDecimal += ((tolower(s[i]) - 'a') + 10) * pow(16, intNibble);
				--i;
				++intNibble;
				isLetter = YES;
			}
			else
				isLetter = NO;
			
			if(isNumber == NO && isLetter == NO && s[i] != '\0')
				return 0;


		}
		
	}

	return intDecimal;
}

/* gethex:	Gets hex number from the keyboard and checks to see if its formatted correcly.  Returns 0 if formatted correctly.  Returns 1 if not formatted correctly. */

int gethex(char s[], int lim)
{
	int c, i;
	int isNumber = NO;
	int isLetter = NO;

	for(i = 0; i <= lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
		
	s[i] = '\0';

	for(i = 0; i <= lim && s[i] != '\0'; ++i)
	{
		if(i == 0)
		{
			if(s[0] == '0' && tolower(s[1]) == 'x')
				i = 2;
		}
		/* check to see if a valid 0 - 9 number exists */
		if(s[i] >= '0' && s[i] <= '9')
			isNumber = YES;
		else
			isNumber = NO;

		/* check to see if a valid letter exists */
		if(tolower(s[i]) >= 'a' && tolower(s[i]) <= 'f')
			isLetter = YES;
		else
			isLetter = NO;
		
		if(isNumber == NO && isLetter == NO)
			return 1;

	}
	return 0;
}
