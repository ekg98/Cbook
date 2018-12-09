#include <stdio.h>

/* Exercise 1-15.  Rewrite the temperature conversion program of Section 1.2 to use a function for conversion. */

#define	LOWER	0
#define	UPPER	300
#define	STEP	20

int ftoc(int f);

main()
{
	int fahr;

	
	for(fahr = LOWER; fahr <= UPPER; fahr += STEP)
	{
		printf("%d\t%d\n",fahr, ftoc(fahr));
	}
	return 0;
}

/* Fahrenheit to Celsius function. */
int ftoc(int fahr)
{
	return (5 * (fahr - 32) / 9);
}
