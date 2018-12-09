#include <stdio.h>

#define	IN	1
#define	OUT	0

/* Exercise 1-13.  Horizontal Version.  Write a program to print a histogram of the lengths of words in its input.  It is easy to draw the histogram with the bars horizontal; a vertical orientation is mroe challenging. */

main()
{
	int c, i, state, intWordSize, intRow;
	int intWordSizeArray[15];	
	int intFirstWord;
	
	state = IN;
	intWordSize = 0;
	intFirstWord = 1;
	intRow = 0;

	for(i = 0; i < 15; ++i)
		intWordSizeArray[i] = 0;

	while((c = getchar()) != EOF)
	{
		if(c == ' ' || c == '\t' || c == '\n')
		{
			state = OUT;
			if(intWordSize > 0)
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

	for(i = 0; i < 15; ++i)
	{
		if(i < 9)
			printf("%d |", i + 1);
		else
			printf("%d|", i + 1);

		for(intRow = 0; intRow < intWordSizeArray[i]; ++intRow)
			printf("#");
		printf("\n");
	}

}
