/* Exercise 3-2.  Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string to s.  Use a switch.  Write a function for the other direction as well converting escape sequences into the real characters. */

#include <stdio.h>

#define	MAXIMUM	1024

int escape(char s[], char t[]);
int rescape(char s[], char t[]);
int getaline(char s[], int lim);

int main()
{
	char toescape[MAXIMUM];
	char fromescape[MAXIMUM];	
	char fromrescape[MAXIMUM];

	getaline(toescape, MAXIMUM);
	escape(fromescape, toescape);

	printf("Escape: %s\n", fromescape);

	rescape(fromrescape, fromescape);

	printf("Rescape: %s\n", fromrescape);	

	return 0;
}

/* Escape.  Copies string t to s and converts all escape sequences to visible format. */
int escape(char s[], char t[])
{
	int tpos = 0;
	int spos = 0;

	while(t[tpos] != '\0' && tpos < MAXIMUM && spos < MAXIMUM)
	{
		switch(t[tpos])
		{
			case '\n':
				tpos++;
				s[spos++] = '\\';
				s[spos++] = 'n';
				break;
			case '\t':
				tpos++;
				s[spos++] = '\\';
				s[spos++] = 't';
				break;
			default:
				s[spos++] = t[tpos++];
				break;
		}
	}

	s[spos] = '\0';
	
	return 0;
}

/* Rescape.  Copies string t to s and converts all visible escape sequences to real characters. */
int rescape(char s[], char t[])
{
	int tpos = 0;
	int spos = 0;

	while(t[tpos] != '\0' && tpos < MAXIMUM && spos < MAXIMUM)
	{
		switch(t[tpos])
		{
			case '\\':
				switch(t[++tpos])
				{
					case 'n':
						s[spos++] = '\n';
						++tpos;
						break;
					case 't':
						s[spos++] = '\t';
						++tpos;
						break;
					default:
						s[spos++] = '\\';
						break;
				}
				break;
			default:
				s[spos++] = t[tpos++];
				break;
		}
	}
	
	s[spos] = '\0';

	return 0;
}

/* getaline.  Gets a line */
int getaline(char s[], int lim)
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
