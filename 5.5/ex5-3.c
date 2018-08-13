/* Exercise 5-3.  Write a pointer version of the function strcat that we showed in Chapter 2: strcat(s,t) copies the string t to the end of s. */

#include <stdio.h>

#define MAXIMUM	1024

void sstrcat(char *s, char *t);

int main()
{
	char source2[] = "my neighbor?";	
	char source1[] = "Won't you be ";
	char target[1024];

	*target = '\0';
	
	sstrcat(target, source1);
	sstrcat(target, source2);
	printf("Source1 = %s\n", source1);
	printf("Source2 = %s\n", source2);
	printf("Target = %s\n", target);

	return 0;
}

void sstrcat(char *s, char *t)
{
	while(*s)
		s++;

	while(*s++ = *t++)
		;
}
