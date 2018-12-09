#include <stdio.h>

/* count blanks, tabs, and newlines in input */

main()
{
	int c, blanks, tabs, nl;

	nl = 0;
	blanks = 0;
	tabs = 0;

	while((c = getchar()) != EOF)
	{
		if(c == '\n')
			++nl;
		if(c == ' ')
			++blanks;
		if(c == '\t')
			++tabs;
	}
	printf("\n%d blanks, %d tabs, %d newlines\n", blanks, tabs, nl);
}
