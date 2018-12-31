// Exercise 7-3.  Revise minprintf to handle more of the other facilities of printf

// does not handle formatting.  Can be done by walking the input string and making a second string within minprintf.
// Once first string hits a character add it to second then terminate the second string retain p at the character for the case and pass the second string ot printf

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

void minprintf(char *, ...);

int main()
{
	int intNumber = 100;
	float floatNumber = 100.0;
	char character = 100;

	minprintf("Hello ,%s\n", "World");
	minprintf("number = %d %d\n", intNumber, intNumber);
	minprintf("float = %f\n", floatNumber);
	minprintf("char = %c\n", character);
	minprintf("octal = %o\n", 100);
	minprintf("hex lowercase = %#x\n", 100);
	minprintf("hex uppercase = %X\n", 100);
	minprintf("unsigned int = %d\n", 100);
	minprintf("ee = %e\n", 100.0);
	minprintf("EE = %E\n", 100.0);
	minprintf("a = %a\n", 100.0);
	minprintf("A = %A\n", 100.0);
	minprintf("g = %g\n", 100.0);
	minprintf("G = %G\n", 100.0);

	return 0;
}

void minprintf(char *fmt, ...)
{
	va_list ap;	// points to each unnamed arg in turn
	char *p, *sval;
	int ival;
	double dval;
	int cval;
	unsigned int oval, xval, uval;
	char formatList[20];
	char *fmtList = formatList;

	va_start(ap, fmt);	// make ap point to 1st unnamed arg

	for(p = fmt; *p; p++)
	{
		if(*p != '%')
		{
			putchar(*p);
			continue;
		}
		else
			*fmtList++ = *p;

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
				cval = va_arg(ap, int);
				printf(formatList, cval);
				break;
			case 's':
				for(sval = va_arg(ap ,char *); *sval; sval++)
					putchar(*sval);
				break;
			case 'd':
			case 'i':
				ival = va_arg(ap, int);
				printf(formatList, ival);
				break;
			case 'o':
				oval = va_arg(ap, unsigned int);
				printf(formatList, oval);
				break;
			case 'x':
				xval = va_arg(ap, unsigned int);
				printf(formatList, xval);
				break;
			case 'X':
				xval = va_arg(ap, unsigned int);
				printf(formatList, xval);
				break;
			case 'u':
				uval = va_arg(ap, unsigned int);
				printf(formatList, uval);
				break;
			case 'f':
				dval = va_arg(ap ,double);
				printf(formatList, dval);
				break;
			case 'e':
				dval = va_arg(ap, double);
				printf(formatList, dval);
				break;
			case 'E':
				dval = va_arg(ap, double);
				printf(formatList, dval);
				break;
			case 'a':
				dval = va_arg(ap, double);
				printf(formatList, dval);
				break;
			case 'A':
				dval = va_arg(ap, double);
				printf(formatList, dval);
				break;
			case 'g':
				dval = va_arg(ap, double);
				printf(formatList, dval);
				break;
			case 'G':
				dval = va_arg(ap, double);
				printf(formatList, dval);
				break;
			default:
				putchar(*p);
				break;
		}

		fmtList = formatList;	// reset pointer to beginning of string for next argument
	}

	va_end(ap);	// clean up when done
}
