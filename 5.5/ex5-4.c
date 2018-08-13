/* Exercise 5-4.  Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s, and zero otherwise. */

#include <stdio.h>
#include <string.h>

int strend(char *s, char *t);

int main()
{
	char source[] = "Won't you be my neighbor?";
	char target[] = "my neighbor?";
	int returnvalue;

	printf("Source = %s\n", source);
	printf("Target = %s\n", target);
	printf("Return value = %d\n", (returnvalue = strend(source, target)));

	if(returnvalue)
		printf("String '%s' occurs at the end of string '%s'\n", target, source);
	else
		printf("String '%s' didn't occur at the end of string '%s'\n", target, source);

	return 0;
}

int strend(char *s, char *t)
{
	int tlength = strlen(t);
	int tcount = 0;

	while(*s)		/* go to the end of string s */
		s++;

	while(*t)		/* go to the end of string t */
		t++;

	while(*s == *t)		/* Going backwards check if the letters are the same, if they are go to the next letter from right to left. */
	{
		if(*t != '\0')		/* don't include the string terminator in the count of letters.  This allows it to be compaired to tlength beacuse strlen does not count the string terminator. */
			tcount += 1;
		
		s--;
		t--;
	}

	if(tlength == tcount)
		return 1;
	else
		return 0;
}
