/* Exercise 5-17.  Add a field-handling capability, so sorting may be done on fields within lines, each field sorted according to an independant set of options. */
/* Exercise is already modified to comply with 5-14. */
/* Exercise is already modified to comply with 5-15. */
/* Exercise is already modified to comply with 5-16. */

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
char *fieldptr[MAXLINES];	/* pointer to field to be sorted */

/* function declarations */
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsortnew(void *lineptr[], int left, int right, int (*comp)(void *, void *), void *fieldptr[]);
int numcmp(char *, char *);
int strcmpfold(char *, char *);
int dordercmp(char *, char *);
int rdordercmp(char *, char *);
int dordercmpfold(char *, char *);
int rdordercmpfold(char *, char *);
int rnumcmp(char *, char *);
int rstrcmp(char *, char *);
int rstrcmpfold(char *, char*);
void sortfield(void *field[], int, int, void *line[]);

int main(int argc, char *argv[])
{
	int numeric = FALSE;
	int reverse = FALSE;
	int fold = FALSE;
	int dorder = FALSE;
	int field = 0;
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
				printf("-d\tDirectory order.  Sort only by letters, numbers, and whitespace.\n");
				printf("-3\t Field sorting.  Sorts by the field represented by a number.  Change 3 to suit which field you are sorting by.\n");
				return 0;
			}

			if(*argv[i] == '-')					/* detect the '-' marker */
			{

				if(strlen(argv[i]) == 1)			/* check argument length and if it has nothing follow the '-' generate error message and quit. */
				{
					printf("Error: Unknown argument!\n");
					return 1;
				}

				while(*(argv[i] + argcounter))								/* walk through the string and search for valid arguments */
				{
					if(*(argv[i] + argcounter) == 'n')						/* n for numeric ordering */
						numeric = TRUE;					
					else if(*(argv[i] + argcounter) == 'r')						/* r for reverse search */
						reverse = TRUE;
					else if(*(argv[i] + argcounter) == 'f')						/* f for folding case.  (ignore case) */
						fold = TRUE;
					else if(*(argv[i] + argcounter) == 'd')						/* d for directory order. */
						dorder = TRUE;
					else if(isdigit(*(argv[i] + argcounter)))					/* -(number) determines the field to sort by */
						field = atoi(argv[i] + 1);
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


	if(numeric == FALSE && reverse == FALSE && fold == FALSE && dorder == FALSE)		/* strcmp no flags */
		compare = strcmp;

	if(numeric == FALSE && reverse == TRUE && fold == FALSE && dorder == FALSE)		/* Reverse strcmp -r */
		compare = rstrcmp;

	if(numeric == FALSE && reverse == FALSE && fold == TRUE && dorder == FALSE)		/* strcmpfold -f (ignore case) */
		compare = strcmpfold;

	if(numeric == FALSE && reverse == TRUE && fold == TRUE && dorder == FALSE)		/* reverse strcmpfold -rf */
		compare = rstrcmpfold;

	if(numeric == FALSE && reverse == FALSE && fold == FALSE && dorder == TRUE)		/* Directory order -d */
		compare = dordercmp;

	if(numeric == FALSE && reverse == TRUE && fold == FALSE && dorder == TRUE)		/* reverse directory order -d */
		compare = rdordercmp;

	if(numeric == FALSE && reverse == FALSE && fold == TRUE && dorder == TRUE)		/* directory order fold -df */
		compare = dordercmpfold;

	if(numeric == FALSE && reverse == TRUE && fold == TRUE && dorder == TRUE)		/* reverse directory order fold -drf */
		compare = rdordercmpfold;

	if(numeric == TRUE && reverse == FALSE && fold == FALSE)				/* numaric -n */
		compare = numcmp;

	if(numeric == TRUE && reverse == TRUE && fold == FALSE)					/* reverse numeric -rn */
		compare = rnumcmp;

	if(numeric == TRUE && fold == TRUE)							/* Generate error if fold is used with number compare */
	{
		printf("Error: Fold option only works on strings.\n");
		return 1;
	}

	if(numeric == TRUE && dorder == TRUE)							/* Generate error if directory order is used with number compare */
	{
		printf("Error: Directory order only works on strings.\n");
		return 1;
	}

	if((nlines = readlines(lineptr, MAXLINES)) >= 0)
	{
		sortfield((void **) fieldptr, field, nlines, (void **)lineptr);
		qsortnew((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *))(compare), (void **) fieldptr);	/* Function pointer.  Can change depending on f flag */
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
void qsortnew(void *v[], int left, int right, int (*comp)(void *, void *), void *vfield[])
{
	int i, last;
	void swap(void *v[], int, int);

	if(left >= right)
		return;

	swap(v, left, (left + right) / 2);
	last = left;

	for(i = left + 1; i <= right; i++)
		if((*comp)(vfield[i], vfield[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsortnew(v, left, last - 1, comp, vfield);
	qsortnew(v, last + 1, right, comp, vfield);
}

/* sortfield */
void sortfield(void *vfield[], int fieldselect,int numlines, void *lines[])
{
	int i;
	int letterpos;
	int fieldcounter;

	for(i = 0; i < numlines; i++)
		vfield[i] = lines[i];

	for(i = 0; i < numlines; i++)
	{
		for(letterpos = 0, fieldcounter = 0; (*(((char *)lines[i]) + letterpos)) != '\0' && fieldcounter < fieldselect; letterpos++)
			if(isspace(*(((char *)lines[i]) + letterpos)))
				fieldcounter++;
	
		
		printf("fieldcounter = %d letterpos = %d line = %s\n", fieldcounter, letterpos, lines[i] + letterpos );

		vfield[i] = lines[i] + letterpos;
	}

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
int rnumcmp(char *s1, char *s2)
{
	return numcmp(s2, s1);
}

/* strcmpfold */
int strcmpfold(char *s, char *t)
{
	for( ; tolower(*s) == tolower(*t); s++, t++)
		if(*s == '\0')
			return 0;
	return tolower(*s) - tolower(*t);
}

/* dordercmp */
int dordercmp(char *s, char *t)
{
	for( ; *s != '\0'; s++, t++)
	{
		if(*s != *t && (isalnum(*s) || isspace(*s)) && (isalnum(*t) || isspace(*t)))
			return *s - *t;
	}

	return 0;
}

/* rdordercmp */
int rdordercmp(char *s, char *t)
{
	return dordercmp(t, s);
}

/* dordercmpfold */
int dordercmpfold(char *s, char *t)
{
	for( ; *s != '\0'; s++, t++)
	{
		if(tolower(*s) != tolower(*t) && (isalnum(tolower(*s)) || isspace(*s)) && (isalnum(tolower(*t)) || isspace(*t)))
			return tolower(*s) - tolower(*t);
	}

	return 0;
}

/* rdordercmpfold */
int rdordercmpfold(char *s, char *t)
{
	return dordercmpfold(t, s);
}

/* Reverse strcmp */
int rstrcmp(char *s, char *t)
{
	return strcmp(t, s);
}

/* Reverse strcmpfold */
int rstrcmpfold(char *s, char *t)
{
	return strcmpfold(t, s);
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

