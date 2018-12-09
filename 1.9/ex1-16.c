/* Exercise 1-16.  Revise the main routine of the longest-line program so it will correctly print the length of arbitrarily long input lines, and as much as possible of the text. */

#include <stdio.h>

#define	MAXLINE	1000	/* maximum input line size */

int getlinee(char line[], int maxline);
void copy(char to[], char from[]);


main()
{
	int len;	/* current line length */
	int max;	/* maximum length seen so far */
	char line[MAXLINE];	/* current input line */
	char longest[MAXLINE];	/* longest line saved here */

	max = 0;
	
	while((len = getlinee(line, MAXLINE)) > 0)
		if(len > max)
		{
			max = len;
			copy(longest,line);
		}

	if(max > 0)	/* there was a line */
	{
		printf("\nLongest line has %d characters (including \\0):\n", max);	
		printf("%s", longest);
	}	

	return 0;
}

/* getline:	read a line into s, return length */
int getlinee(char s[], int lim)
{
	int c, i;

	for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if(c == '\n')
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* copy:	copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
	int i;

	i = 0;
	while((to[i] = from[i]) != '\0')
		++i;
}
