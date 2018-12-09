#include <stdio.h>

#define ON	1
#define OFF	0

/* Exercise 1-10.  Write a program to copy its input to its output, replacing each tab by \t, each backspace by \b, and each backslash by \\.  This makes tabs and backspaces visible in a unambiguous way. */

main()
{
	int c, intTrigger;

	intTrigger = OFF;

	while((c = getchar()) != EOF )
	{
		if(c == '\t')
		{
			putchar('\\');
			putchar('t');
			intTrigger = ON;
		}
		
		if(c == '\b')
		{
			putchar('\\');
			putchar('b');
			intTrigger = ON;
		}
		
		if(c == '\\')
		{
			putchar('\\');
			putchar('\\');
			intTrigger = ON;
		}
		
		if(intTrigger == OFF)
			putchar(c);
		
		intTrigger = OFF;
	}
}
