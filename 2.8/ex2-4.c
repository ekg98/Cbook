/* Exercise 2-4.  Write an alternate version of squeeze(s1, s2) that deletes each character in s1 that matches any character in the string s2. */

#include <stdio.h>

#define	MAXIMUM	1024

void squeeze(char string1[], char string2[]);

int main()
{
	char ModifiedString[MAXIMUM] = "This is a modified String!", quereString[MAXIMUM] = "s";

	printf("Before Modification: %s\n", ModifiedString);
	squeeze(ModifiedString, quereString);

	printf("Modified String: %s\nQuere String: %s\n", ModifiedString, quereString);

	return 0;
}

void squeeze(char s1[], char s2[])
{
	int i, j;
	int quereCounter = 0;

	while(s2[quereCounter] != '\0')
	{
		for(i = j = 0; s1[i] != '\0'; i++)
			if(s1[i] != s2[quereCounter])
				s1[j++] = s1[i];
		
		s1[j] = '\0';

		++quereCounter;
	}
}
