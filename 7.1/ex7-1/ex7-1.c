// Exercise 7-1.  Write a program that converts upper case to lower or lower case to upper.  Depending on the name it is invoked with, as found in argv[0]

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int c;
	printf("%s\n", argv[0]);

	if(strcmp(argv[0], "upper") == 0)
		while((c = getchar()) != EOF)
			putchar(toupper(c));
	else if(strcmp(argv[0], "lower") == 0)
		while((c = getchar()) != EOF)
			putchar(tolower(c));
	else
		printf("Rename to upper or lower depending on desired operation.\n");

	return 0;
}
