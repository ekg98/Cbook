/* Exercise 1-19.  Write a function reverse(s) that reverses the character string s.  Use it to write a program that reverses its input a line at a time. */

#include <stdio.h>

#define	MAXLINE	1000	/* maximum input line size */

int getlinee(char s[], int lim);
void reverse(char rev[]);

main()
{
	int len;	/* current line length */
	char line[MAXLINE];	/* current input line */

	
	while((len = getlinee(line, MAXLINE)) > 0)
	{
		reverse(line);
		printf("%s\n", line);
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

/* Reverse:	Reverse the string */
void reverse(char rev[])
{
	char charTemp;
	int i, intEndLimit;

	charTemp = 0;

	for(i = 0; rev[i] != '\0'; ++i)
		;

	intEndLimit = i - 1;	

	if(intEndLimit > 1)
	{
		for(i = 0; i < intEndLimit; ++i)
		{
			charTemp = rev[i];
			rev[i] = rev[intEndLimit];
			rev[intEndLimit] = charTemp;
			--intEndLimit;
		}
	}			
}
