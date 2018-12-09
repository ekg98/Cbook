/* Exercise 1-23.  Write a program to remove all comments from a C program.  Don't forget to handle quoted strings and character constants properly.  C comments do not nest. */

#include <stdio.h>

#define	MAXIMUM	1024
#define	YES	1
#define	NO	0

int getprogram(char s[], int lim);

main()
{
	char charProgram[MAXIMUM];
	char charFormattedProgram[MAXIMUM];

	int i, intWrite, arraypos;
	int programlength;

	intWrite = YES;
	arraypos = 0;
	programlength = 0;

	programlength = getprogram(charProgram,MAXIMUM);

		for(i = 0; i <= programlength; ++i)
		{
			if(i < (programlength - 1))
			{
				if(charProgram[i] == '/' && charProgram[i + 1] == '*')
					intWrite = NO;

				if(charProgram[i] == '*' && charProgram[i + 1] == '/')
				{
					i += 2;
					intWrite = YES;
				}
			}

			if(intWrite == YES)
			{
				charFormattedProgram[arraypos] = charProgram[i];
				++arraypos;
			}
			

		}
	
	printf("%s\n", charFormattedProgram);

	return 0;
}

/* getprogram:	This function will get a continous string from the keyboard */

int getprogram(char string[], int limit)
{
	int c, i;

	for(i = 0; i < limit - 1 && (c = getchar()) != EOF; ++i)
		string[i] = c;
		
	string[i] = '\0';

	return i;
}
