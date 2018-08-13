/* Exercise 2-1.  Write a program to determine the ranges of char, short, int, and long variables, both signed and unsigned, by printing the appropriate values from standard headers and by direct computation.  Harder if you compute them:  determine the ranges of various floating-point types */

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
	char charCounter, charMax, charMin;
	short shortCounter, shortMax, shortMin;
	int intCounter, intMax, intMin;
	long longCounter, longMax, longMin;

	charMax = 0;
	printf("<limits.h>\n");
	printf("CHAR_MAX: %d\n", CHAR_MAX);
	printf("CHAR_MIN: %d\n", CHAR_MIN);
	printf("INT_MAX: %d\n", INT_MAX);
	printf("INT_MIN: %d\n", INT_MIN);
	printf("SCHAR_MAX: %d\n", SCHAR_MAX);
	printf("SCHAR_MIN: %d\n", SCHAR_MIN);
	printf("UCHAR_MAX: %d\n", UCHAR_MAX);
	printf("SHRT_MAX: %d\n", SHRT_MAX);
	printf("SHRT_MIN: %d\n", SHRT_MIN);
	printf("UCHAR_MAX %u\n", UCHAR_MAX);
	printf("UINT_MAX %u\n", UINT_MAX);
	printf("ULONG_MAX %u\n", ULONG_MAX);
	printf("USHRT_MAX %u\n", USHRT_MAX);
	printf("\n<float.h>\n");
	printf("FLT_MAX %f\n", FLT_MAX);
	printf("FLT_MIN %f\n", FLT_MIN);
	printf("DBL_MAX %f\n", DBL_MAX);
	printf("DBL_MIN %f\n", DBL_MIN);


	/* Char Max */
	for(charCounter = 1; charCounter > 0; ++charCounter)
		++charMax;

	/* Char Min */
	for(charCounter = -1; charCounter < 0; --charCounter)
		--charMin;

	/* Short Max */
	for(shortCounter = 1; shortCounter > 0; ++shortCounter)
		++shortMax;

	/* Short Min */
	for(shortCounter = -1; shortCounter < 0; --shortCounter)
		--shortMin;

	/* Int Max */
	for(intCounter = 1; intCounter > 0; ++intCounter)
		++intMax;

	/* Int Min */
	for(intCounter = -1; intCounter < 0; --intCounter)
		--intMin;

	/* Long Max */
	for(longCounter = 1; longCounter > 0; ++longCounter)
		++longMax;

	/* Long Min */
	for(longCounter = -1; longCounter < 0; --longCounter)
		--longMin;

	printf("\ncharMax: %d\n", charMax);
	printf("charMin: %d\n", charMin);
	printf("shortMax: %d\n", shortMax);
	printf("shortMin: %d\n", shortMin);
	printf("intMax: %d\n", intMax);
	printf("intMin: %d\n", intMin);
	printf("longMax: %d\n", longMax);
	printf("longMin: %d\n", longMin);

	return 0;
}
