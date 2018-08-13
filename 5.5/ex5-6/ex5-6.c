/* Exercise 5-6.  Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing.  Good possibilities include getline (ch 1 and 4), atoi, itoa, and their variants (ch 2,3,and 4), reverse (ch 3), and strindex and getop (ch 4) */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define	MAXIMUM	1024
#define	NUMBER	1

int getalinech1(char *s, int lim);		/* getline from chapter 1 */
int getalinech4(char *s, int lim);		/* getline from chapter 4 */
int atoich2(char *s);				/* atoi from chapter 2 */
int atoich3(char *s);				/* atoi from chapter 3 */
void itoach3(int n, char *s);			/* itoa from chapter 3 */
void reversech3(char *s);			/* reverse from chapter 3 */
int strindexch4(char *s, char *t);		/* strindex from chapter 4 */
int getopch4(char *s);				/* getop from chapter 4 */
int getch(void);				/* include getch from chapter 4 polish calculator */
void ungetch(int);				/* include ungetch from chapter 4 polish calculator */

int main()
{
	char string[MAXIMUM];
	int stringlength;

	/*while((stringlength = getalinech4(string, MAXIMUM)) > 0)
		printf("%d:) %s", stringlength, string);
	*/

	char atoistring[] = "-132";
	/*printf("atoistring = %s\n", atoistring);
	printf("atoi = %d\n", atoich3(atoistring));
	*/

	int itoanumber = 123;
	char itoastring[MAXIMUM];

	/*printf("itoanumber = %d\n", itoanumber);
	itoach3(itoanumber, itoastring);
	printf("itoa = %s\n",itoastring);
	*/

	char strindexsstring[] = "Won't you be my neighbor?";
	char strindextstring[] = "be my";
	
	/*printf("strindexsstring = %s\n", strindexsstring);
	printf("strindextstring = %s\n", strindextstring);
	printf("Where t starts in s (-1 if none): %d\n", strindexch4(strindexsstring, strindextstring));
	*/

	int getopreturn;
	char getopstring[MAXIMUM];

	getopreturn = getopch4(getopstring);

	printf("getopreturn = %d\n", getopreturn);
	printf("getopstring = %s\n", getopstring);

	return 0;
}

/* getalinech1:  Using pointers, Read a line into s, return length */
int getalinech1(char *s, int lim)
{
	char *firstcell = s;
	int c;

	while(firstcell - s < lim - 1 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;

	if(c == '\n')
		*s++ = c;
	
	*s = '\0';
	
	return s - firstcell;
}

/* getalinech4: Using pointers, Read a line into s, return length */
int getalinech4(char *s, int lim)
{
	char *firstcell = s;
	int c;

	while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	
	if(c == '\n')
		*s++ = c;
	
	*s = '\0';
	
	return s - firstcell;
}

/* atoich2: Using pointers, convert s to integer */
int atoich2(char *s)
{
	int n;

	n = 0;

	for( ; *s >= '0' && *s <= '9'; s++)
	{
		n = 10 * n + (*s - '0');
	}

	return n;
}

/* atoich3: Using pointers, convert s to integer; version 2 */
int atoich3(char *s)
{
	int n, sign;

	for( ; isspace(*s); s++)
		;
	
	sign = (*s == '-') ? -1 : 1;
	
	
	if(*s == '+' || *s == '-')
		s++;

	for(n = 0; isdigit(*s); s++)
		n = 10 * n + (*s - '0');

	return sign * n;
}

/* itoach3: Using pointers, convert n to characters in s */
void itoach3(int n, char *s)
{
	int sign;
	char *firstcell = s;

	if((sign = n) < 0)
		n = -n;

	do
	{
		*s++ = n % 10 + '0';
	}while((n /= 10) > 0);

	if(sign < 0)
		*s++ = '-';
	
	*s = '\0';

	reversech3(firstcell);
}

/* reversech3: Using pointers, reverse string s in place */
void reversech3(char *s)
{
	int c;
	char *sj = s;

	while(*sj)
		sj++;

	for(--sj ; s < sj; s++, sj--)
	{
		c = *s;
		*s = *sj;
		*sj = c;
	}
}

/* strindexch4: Using pointers, return index of t in s, -1 if none */
int strindexch4(char *s, char *t)
{
	char *firstcells = s;
	char *firstcellt = t;
	char *sj, *tk;

	for( ; *s ; s++)
	{
		for(sj = s, tk = t; *tk != '\0' && *sj == *tk; sj++, tk++)
			;

		if(tk > firstcellt && *tk == '\0')
			return s - firstcells;
	}

	return -1;
}

/* getopch4: Using pointers, get next operator of numeric operand */
int getopch4(char *s)
{
	int c;

	while((*s = c = getch()) == ' ' || c == '\t')
		;

	*(s + 1) = '\0';

	if(!isdigit(c) && c != '.')
		return c;

	if(isdigit(c))
		while(isdigit(*++s = c = getch()))
			;

	if(c == '.')
		while(isdigit(*++s = c = getch()))
			;

	*s = '\0';

	if(c != EOF)
		ungetch(c);

	return NUMBER;
}
