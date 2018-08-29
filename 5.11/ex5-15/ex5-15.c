/* Exercise 5-15.  Add the option -f to fold upper and lower case together, so that case distinctions are not made during sorting; for example, a and A compare equal. */
/* Exercise is already modified to comply with 5-14. */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "alloc.h"
#include "getaline.h"

#define	MAXLINES	5000	/* max #lines to be sorted */
#define	TRUE	1
#define	FALSE	0

char *lineptr[MAXLINES];	/* pointers to text lines */

/* function declarations */
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsortnew(void *lineptr[], int left, int right, int (*comp)(void *, void *));
void qsortignorecase(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int strcmpfold(char *, char *);
int rnumcmp(char *, char *);
int rstrcmp(char *, char *);
int rstrcmpfold(char *, char*);

int main(int argc, char *argv[])
{
	int numeric = FALSE;
	int reverse = FALSE;
	int fold = FALSE;
	int nlines;
	int i;
	int argcounter = 1;
	void (*compare) = NULL;

	if(argc > 1)
	{
		for(i = 1; i < argc; i++)					/* look at each input argv */
		{
			if(strcmp(argv[i], "-h") == 0)
			{
				printf("Text sort.  K&R book.  Chapter 5.\n");
				printf("This program sorts lines of input text via argumented criteria.  Default is lexigraphical sorting.\n");
				printf("Available arguments:\n\n");
				printf("-h\tThis menu.\n");
				printf("-n\tNumeric sorting.\n");
				printf("-r\tReverse sorting.\n");
				printf("-f\tFold upper case and lower case together.  (ignore case)\n");
				return 0;
			}

			if(*argv[i] == '-')					/* detect the '-' marker */
			{

				if(strlen(argv[i]) == 1)			/* check argument length and if it has nothing follow the '-' generate error message and quit. */
				{
					printf("Error: Unknown argument!\n");
					return 1;
				}

				while(*(argv[i] + argcounter))			/* walk through the string and search for valid arguments */
				{
					if(*(argv[i] + argcounter) == 'n')	/* n for numeric ordering */
						numeric = TRUE;					
					else if(*(argv[i] + argcounter) == 'r')	/* r for reverse search */
						reverse = TRUE;
					else if(*(argv[i] + argcounter) == 'f')	/* f for folding case.  (ignore case) */
						fold = TRUE;
					else
					{
						printf("Error: Unknown argument!\n");
						return 1;
					}
					argcounter++;
				}
			}
		
		}

	}

	if(numeric == FALSE && reverse == FALSE && fold == FALSE)		/* default activated if no flags are present */
		compare = strcmp;

	if(numeric == FALSE && reverse == FALSE && fold == TRUE)		/* Activate strcmpfold if f flag is solo. (ignore case) */
		compare = strcmpfold;

	if(numeric == FALSE && reverse == TRUE && fold == FALSE)		/* Activate reverse strcmp if flag solo r was detected */
		compare = rstrcmp;

	if(numeric == FALSE && reverse == TRUE && fold == TRUE)			/* Activate reverse strcmpfold if flag rf was detected */
		compare = rstrcmpfold;

	if(numeric == TRUE && reverse == FALSE && fold == FALSE)		/* Activate numaric compare if flag solo n was detected*/
		compare = numcmp;

	if(numeric == TRUE && reverse == TRUE && fold == FALSE)			/* Activate reverse numeric compare if the flags were a combination of r & n */
		compare = rnumcmp;

	if(numeric == TRUE && fold == TRUE)					/* Generate error if fold is used with number compare */
	{
		printf("Error: Fold option only works on strings.");
		return 1;
	}

	if((nlines = readlines(lineptr, MAXLINES)) >= 0)
	{
		qsortnew((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *))(compare));	/* Function pointer.  Can change depending on f flag */
		writelines(lineptr, nlines);
		return 0;
	}
	else
	{
		printf("Input too big to sort\n");
		return 1;
	}
}

/* Qsort */
void qsortnew(void *v[], int left, int right, int (*comp)(void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);

	if(left >= right)
		return;

	swap(v, left, (left + right) / 2);
	last = left;

	for(i = left + 1; i <= right; i++)
		if((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsortnew(v, left, last - 1, comp);
	qsortnew(v, last + 1, right, comp);
}

/* standard numcmp */
int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);

	if(v1 < v2)
		return -1;
	else if(v1 > v2)
		return 1;
	else
		return 0;
}

/* Reverse numcmp */
int rnumcmp(char *s2, char *s1)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);

	if(v1 < v2)
		return -1;
	else if(v1 > v2)
		return 1;
	else
		return 0;
}

/* strcmpfold */
int strcmpfold(char *s, char *t)
{
	for( ; tolower(*s) == tolower(*t); s++, t++)
		if(*s == '\0')
			return 0;
	return tolower(*s) - tolower(*t);
}

/* Reverse strcmp */
int rstrcmp(char *t, char *s)
{
	for( ; *s == *t; s++, t++)
		if(*s == '\0')
			return 0;
	return *s - *t;
}

/* Reverse strcmpfold */
int rstrcmpfold(char *t, char *s)
{
	for( ; tolower(*s) == tolower(*t); s++, t++)
		if(*s == '\0')
			return 0;
	return tolower(*s) - tolower(*t);
}

/* swap function for qsort */
void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* readlines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLINES];

	nlines = 0;

	while((len = getaline(line, MAXLINES)) >0)
	{
		if(nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else
		{
			line[len -1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	
	return nlines;
	
}

/* writelines */
void writelines(char *lineptr[], int nlines)
{
	int i;

	for(i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

