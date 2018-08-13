#include <stdio.h>
#include <ctype.h>
#include "calc.h"

#define	SAVED	1
#define	NOTSAVED	0

int getop(char s[])
{
	int i, c;
	static int save;
	static int savestate;

	do
	{
		if(savestate == NOTSAVED)
			c = getch();
		else
		{
			c = save;
			savestate = NOTSAVED;
		}

	}while((s[0] = c)  == ' ' || c == '\t');
		

	s[1] = '\0';

	if(!isdigit(c) && c != '.')
		return c;

	i = 0;

	if(isdigit(c))
		while(isdigit(s[++i] = c = getch()))
			;

	if(c == '.')
		while(isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if(c != EOF)
	{
		save = c;
		savestate = SAVED;
	}
	return NUMBER;
}
