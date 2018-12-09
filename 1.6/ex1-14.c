#include <stdio.h>

/* Exercise 1-14.  Write a program to print a histogram of the frequencies of different characters in its input. */

main()
{
	int c, i, intRow;
	int intCharacterNumber[256];

	intRow = 0;

	for(i = 0; i < 256; ++i)
	{
		intCharacterNumber[i] = 0;
	}

	while((c = getchar()) != EOF)
	{
		++intCharacterNumber[c];
	}

	for(i = 0; i < 256; ++i)
	{
		
		if(i <= 9)
			printf("%d  |", i);
		if(i >= 10 && i <= 99)
			printf("%d |", i);
		if(i >= 100 && i <=999)
			printf("%d|", i);
		
		for(; intCharacterNumber[i] > 0; --intCharacterNumber[i])
			printf("#");

		printf("\n");
	}
}
