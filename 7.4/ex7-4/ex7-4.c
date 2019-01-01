// Exercise 7-4.  Write a private version of scanf analogous to minprintf from the previous section.

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int minscanf(char *, ...);

int main()
{
	int intNumber, intNumberTwo;
	float floatNumber;
	char character;

	minscanf("%d %d", &intNumber, &intNumberTwo);
	printf("intNumber = %d %d\n", intNumber, intNumberTwo);

	return 0;
}

int minscanf(char *fmt, ...)
{
	va_list ap;	// points to each unnamed arg in turn
	char *p, *sval;
	int *ival;
	double *dval;
	int *cval;
	unsigned int *oval, *xval, *uval;
	char formatList[20];
	char *fmtList = formatList;
	int matches, totalMatches;

	va_start(ap, fmt);	// make ap point to 1st unnamed arg

	for(p = fmt; *p; p++)
	{
		if(*p != '%')
		{
			*fmtList++ = *p;
			continue;
		}
		else
			*fmtList++ = *p;	// p is % add to string

		while(*(p + 1) != '\0' && !isalpha(*(p + 1)))
		{
			*fmtList++ = *(p + 1);
			p++;
		}
		if(isalpha(*(p + 1)))
			*fmtList++ = *(p + 1);

		*fmtList = '\0';

		switch(*++p)
		{
			case 'c':
				cval = va_arg(ap, int *);
				matches = scanf(formatList, cval);
				if(matches > 0)
					totalMatches += matches;
				else
				{
					va_end(ap);
					return 0;
				}
				break;
			case 's':
				sval = va_arg(ap ,char *);
				matches = scanf(formatList, sval);
				if(matches > 0)
					totalMatches += matches;
				else
				{
					va_end(ap);
					return 0;
				}
				break;
			case 'd':
			case 'i':
				ival = va_arg(ap, int *);
				matches = scanf(formatList, ival);
				if(matches > 0)
					totalMatches += matches;
				else
				{
					va_end(ap);
					return 0;
				}
				break;
			case 'o':
				oval = va_arg(ap, unsigned int *);
				matches = scanf(formatList, oval);
				if(matches > 0)
					totalMatches += matches;
				else
				{
					va_end(ap);
					return 0;
				}
				break;
			case 'x':
				xval = va_arg(ap, unsigned int *);
				matches = scanf(formatList, xval);
				if(matches > 0)
					totalMatches += matches;
				else
				{
					va_end(ap);
					return 0;
				}
				break;
			case 'X':
				xval = va_arg(ap, unsigned int *);
				matches = scanf(formatList, xval);
				if(matches > 0)
					totalMatches += matches;
				else
				{
					va_end(ap);
					return 0;
				}
				break;
			case 'u':
				uval = va_arg(ap, unsigned int *);
				matches = scanf(formatList, uval);
				if(matches > 0)
					totalMatches += matches;
				else
				{
					va_end(ap);
					return 0;
				}
				break;
			case 'f':
				dval = va_arg(ap ,double *);
				matches = scanf(formatList, dval);
				if(matches > 0)
					totalMatches += matches;
				else
				{
					va_end(ap);
					return 0;
				}
				break;
			case 'e':
				dval = va_arg(ap, double *);
				matches = scanf(formatList, dval);
				if(matches > 0)
					totalMatches += matches;
				else
				{
					va_end(ap);
					return 0;
				}
				break;
			case 'E':
				dval = va_arg(ap, double *);
				matches = scanf(formatList, dval);
				if(matches > 0)
					totalMatches += matches;
				else
				{
					va_end(ap);
					return 0;
				}
				break;
			case 'a':
				dval = va_arg(ap, double *);
				matches = scanf(formatList, dval);
				if(matches > 0)
					totalMatches += matches;
				else
				{
					va_end(ap);
					return 0;
				}
				break;
			case 'A':
				dval = va_arg(ap, double *);
				matches = scanf(formatList, dval);
				if(matches > 0)
					totalMatches += matches;
				else
				{
					va_end(ap);
					return 0;
				}
				break;
			case 'g':
				dval = va_arg(ap, double *);
				matches = scanf(formatList, dval);
				if(matches > 0)
					totalMatches += matches;
				else
				{
					va_end(ap);
					return 0;
				}
				break;
			case 'G':
				dval = va_arg(ap, double *);
				matches = scanf(formatList, dval);
				if(matches > 0)
					totalMatches += matches;
				else
				{
					va_end(ap);
					return 0;
				}
				break;
			default:
				
				break;
		}

		fmtList = formatList;	// reset pointer to beginning of string for next argument
	}

	va_end(ap);	// clean up when done
	return totalMatches;
}
