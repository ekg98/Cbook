/* Exercise 5-5. Write versions of the library functions strncpy, strncat, and strncmp, which operate on at most the first n characters of their argument strings. For example, strncpy(s,t,n) copies at most n characters of t to s.  Full descriptions are in appendix B. */

#include <stdio.h>
#include <string.h>

#define	MAXIMUM	1024

char *sstrncpy(char *s, char *t, int n);
char *sstrncat(char *s, char *t, int n);
int sstrncmp(char *s, char *t, int n);

int main()
{
	char sourcecpy[MAXIMUM];
	char targetcpy[] = "my neighbor?";

	char sourcecat[MAXIMUM];
	char targetcat[] = "my neighbor?";

	char sourcecmp[] = "hello there";
	char targetcmp[] = "hello";

	sourcecpy[0] = '\0';
	sourcecat[0] = '\0';

	sstrncat(sourcecpy,"Won't you be ", 13);

	printf("Sourcecpy before = '%s'\n", sourcecpy);
	printf("Targetcpy before = '%s'\n", targetcpy);

	printf("sstrncpy returns = '%s'\n", sstrncpy(sourcecpy, targetcpy, 8));
	
	printf("\n");

	sstrncat(sourcecat, "Won't you be ", 13);
	printf("Sourcecat before = '%s'\n", sourcecat);
	printf("Targetcat before = '%s'\n", targetcat);

	printf("sstrncat returns = '%s'\n", sstrncat(sourcecat, targetcat, 5));
	
	printf("\nsstrncmp return = %d\n", sstrncmp(sourcecmp, targetcmp, 6));
	printf("\nstrncmp return = %d\n", strncmp(sourcecmp, targetcmp, 6));


	return 0;
}

/* sstrncpy:  Copy at most n characters of string t to s; return s.  Pad with '\0' if t has fewer than n characters. */
char *sstrncpy(char *s, char *t, int n)
{
	char *firstcell = s;

	while(n > 0 && *t)
	{
		n -= 1;	
		*s++ = *t++;
	}

	if(n > 0)
		while(n-- > 0)
			*s++ = '\0';

	return firstcell;
}

/* sstrncat:  Concatenate at most n characters of string t to string s, terminate s with '\0'; return s. */
char *sstrncat(char *s, char *t, int n)
{
	char *firstcell = s;
	char *tcounter = t;

	while(*s)
		s++;

	while(n > 0 && *tcounter)
	{
		tcounter++;
		n -= 1;
	}

	while(t < tcounter)
		*s++ = *t++;

	*s = '\0';

	/*if(n > 0)
		while(n-- > 0)
			*s++ = '\0';*/

	return firstcell;
}

/* sstrncmp:  Compare at most n characters of string s to string t; return <0 if s<t, 0 if s == t, or >0 if s >t. */
int sstrncmp(char *s, char *t, int n)
{
	for(n -= 1 ; *s == *t && n > 0; s++, t++)
	{
		n -= 1;	
		if(*s == '\0')
			return 0;
	}

	return *s - *t;
}
