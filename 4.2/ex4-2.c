/* Exercise 4-2.  Extend atof to handle scientific notation of the form 123.45e-6 where a floating-point number may be followed by e or E and a optionally signed exponent. */
/* Ensure to compile with atofextend.c for function inclusiion */

#include <stdio.h>

double atof(char string[]);

int main()
{
	char number[] = "123.45e-6";

	printf("Before: %s\n", number);
	printf("After:  %10.10f\n", atof(number));

	return 0;
}
