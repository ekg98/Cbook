/* Exercise 4-13.  Write a recursive version of the function reverse(s), which reverses the string s in place. */

#include <stdio.h>

void reverse(char s[]);

int main()
{
	char string[] = "Reverse this string!";

	printf("Before reverse = %s\n", string);
	reverse(string);
	printf("After reverse = %s\n", string);

	return 0;
}

/* Reverse:  Take a string as a input and reverse it in the same array but doing this recursively */
void reverse(char s[])
{
	static int fwdi = 0;
	static int afti = 0;
	char temp;

	if(s[fwdi] != '\0' && fwdi >= 0)
	{
		temp = s[fwdi++];
		reverse(s);
		s[afti++] = temp;
	}


}
