/* Exercise 3-3.  Write a function expand(s1,s2) that expands shorthand notations like a-z in the string a1 into the equivalent complete list abc...xyz in s2.  Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z.  Arrange that a leading or trailing - is taken literally. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define	MAXIMUM	1024

int expand(char s1[], char s2[]);
int getaline(char string[], int lim);

int main()
{
	char compressedString[MAXIMUM];
	char decompressedString[MAXIMUM];

	getaline(compressedString, MAXIMUM);
	expand(compressedString, decompressedString);

	printf("Compressed string: %s\n", compressedString);
	printf("Decompressed string: %s\n", decompressedString);

	return 0;
}

/* Expand:  Expands s1's shorthand notation and deposits it in s2 */
int expand(char s1[], char s2[])
{
	int s2Size = 0;
	int s1pos = 0, s2pos = 0;
	char prevChar = EOF, currentChar = EOF, nextChar = EOF;

	s2Size = MAXIMUM;
	
	for(s1pos = 0; s1pos <= strlen(s1) && s2pos < s2Size && s2Size > 0; ++s1pos)
	{
		/* gets the current character */
		currentChar = s1[s1pos];
		
		/* get the previous character if not the first character */
		if(s1pos > 0)
			prevChar = s1[s1pos - 1];

		/* gets the next character */
		if(s1pos <= strlen(s1) && s1pos > 0)
			nextChar = s1[s1pos + 1];

		if(currentChar == '-' && s1pos != strlen(s1) && isalnum(prevChar) && isalnum(nextChar) && prevChar != EOF && nextChar != EOF)
		{
			
			/* performs the expand for digits 1 to 9 */
			if(isdigit(prevChar) && isdigit(nextChar))
			{
				prevChar++;
				while(prevChar < nextChar && s2pos < s2Size)
					s2[s2pos++] = prevChar++;
			}

			/* performs the expand for lowercase letters */
			else if(isalpha(prevChar) && isalpha(nextChar) && islower(prevChar) && islower(nextChar))
			{
				prevChar++;
				while(prevChar < nextChar && s2pos < s2Size)
					s2[s2pos++] = prevChar++;
			}

			/* performs the expand for uppercase letters */
			else if(isalpha(prevChar) && isalpha(nextChar) && isupper(prevChar) && isupper(nextChar))
			{
				prevChar++;
				while(prevChar < nextChar && s2pos < s2Size)
					s2[s2pos++] = prevChar++;
			}
			/* keep the - if it cant expand */
			else
				s2[s2pos++] = s1[s1pos];
		
		
		}
		else
			s2[s2pos++] = s1[s1pos];
	}

	s2[s2pos] = '\0';

	return 0;
}

int getaline(char string[], int lim)
{
	int c, i;

	for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		string[i] = c;
	if(c == '\n')
	{
		string[i] = c;
		++i;
	}
	string[i] = '\0';

	return i;
}
