/* Exercise 1-17.  Write a program to print all input lines that are longer than 80 characters */

#include <stdio.h>

#define	MAXLINE	1000	/* maximum input line size */

int getlinee(char line[], int maxline);

main()
{
	int len;	/* current line length */
	char line[MAXLINE];	/* current input line */

	
	while((len = getlinee(line, MAXLINE)) > 0)
		if(len > 80)
			printf("%d char: %s",len - 1, line);
		else
			printf("No lines were longer than 80 characters\n");
	
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

