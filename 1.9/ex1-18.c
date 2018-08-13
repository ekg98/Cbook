/* Exercise 1-18.  Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines. */

#include <stdio.h>

#define	MAXLINE	1000	/* maximum input line size */
#define	YES	1
#define	NO	0

int getlinee(char line[], int maxline);

main()
{
	int i, intEnd;
	int len;	/* current line length */
	char line[MAXLINE];	/* current input line */
	
	intEnd = NO;

	while((len = getlinee(line, MAXLINE)) > 0)
	{

		/* find a character down to element 0 */
		for(i = (len - 1); (i >= 0) && (intEnd == NO); --i)
		{
			if(line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			{
				line[i + 1] = '\0';
				intEnd = YES;
			}	
		}
	
		/* check for blank line at element 0 */	
		if(line[0] == ' ' || line[0] == '\t' || line[0] == '\n' && intEnd == NO)
			line[0] = '\0';

		if(line[0] != '\0')
			printf("%s\n", line);
	
		intEnd = NO;
	}
	
	return 0;
}

/* getline:	read a line into s, return length */
int getlinee(char line[], int maxline)
{
	int c, i;

	for(i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if(c == '\n')
	{
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}

