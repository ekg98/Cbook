#include <stdio.h>

#define	IN	1
#define	OUT	0
#define MAXWORD	17	/* Maximum number of words that the program will keep track of */

/* Exercise 1-13.  Vertical Version.  Write a program to print a histogram of the lengths of words in its input.  It is easy to draw the histogram with the bars horizontal; a vertical orientation is mroe challenging. */

main()
{
	int c, i, state, intWordSize, intColumn;
	int intWordSizeArray[MAXWORD];	
	int intFirstWord, intMost;
	
	state = IN;
	intWordSize = 0;
	intFirstWord = 1;
	intColumn = 0;
	intMost = 0;

	for(i = 0; i < MAXWORD; ++i)
		intWordSizeArray[i] = 0;

	while((c = getchar()) != EOF)
	{
		if(c == ' ' || c == '\t' || c == '\n')
		{
			state = OUT;
			if((intWordSize > 0) && (intWordSize <= MAXWORD))
				++intWordSizeArray[intWordSize - 1];
			intWordSize = 0;
		}
		else if(state == OUT)
		{
			state = IN;
		}

		if((c != ' ' && c != '\t' && c != '\n') && (state == IN))
			++intWordSize;


	}

	printf("\n");

	/* Which has the most quantity of the word lengths */

	for(i = 0; i < MAXWORD; ++i)
	{
		if(intWordSizeArray[i] > intMost)
			intMost = intWordSizeArray[i];
	}

	/* This portion prints the histogram */
		
	while(intMost > 0)
	{
		for(i = 0; i < MAXWORD; ++i)
		{
			if(intWordSizeArray[i] >= intMost)
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
		--intMost;
	}

	for(i = 0; i < MAXWORD; ++i)
	{	
		if((i + 1) <= 9)
			printf("%d", (i + 1));
		if(((i + 1) >= 10) && ((i + 1) <= 99))
			printf("%d",  ((i + 1) - ((i + 1) % 10)) / 10);
	}

	printf("\n");
	
	for(i = 0; i < MAXWORD; ++i)
	{
		if((i + 1) <= 9)
			printf(" ");
		if(((i + 1) >= 10) && ((i + 1) <= 99))
			printf("%d", ((i + 1) % 10));
	}

	printf("\n");
}
