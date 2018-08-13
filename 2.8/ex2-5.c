/* Exercise 2-5.  Write the function any(s1, s2), which returns the first location in the string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2.  (The standard library function strpbrk does the same job but returns a pointer to the location. */

#include <stdio.h>

#define	MAXIMUM	1024

int any(char s1[], char s2[]);

int main()
{
	char string[MAXIMUM] = "This is a string!", quereString[MAXIMUM] = "a";

	printf("The location of the quered letter in the searched string is: %d", any(string, quereString));

	return 0;
}

int any(char s1[], char s2[])
{
	int i, quereCounter = 0;

	for(i = 0; s1[i] != '\0'; ++i)
	{
		for(quereCounter = 0; s2[quereCounter] != '\0'; ++quereCounter)
		{
			if(s1[i] == s2[quereCounter])
				return i;
		}

	}
	return -1;
}
