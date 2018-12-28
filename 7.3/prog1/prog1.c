// minprintf:  Minimal printf with variable argument list

#include <stdarg.h>
#include <stdio.h>

void minprintf(char *, ...);

int main()
{
	int intNumber = 5;
	float floatNumber = 5.0;

	minprintf("Hello ,%s\n", "World");
	minprintf("number = %d\n", intNumber);
	minprintf("float = %f\n", floatNumber);

	return 0;
}

void minprintf(char *fmt, ...)
{
	va_list ap;	// points to each unnamed arg in turn
	char *p, *sval;
	int ival;
	double dval;

	va_start(ap, fmt);	// make ap point to 1st unnamed arg

	for(p = fmt; *p; p++)
	{
		if(*p != '%')
		{
			putchar(*p);
			continue;
		}
		switch(*++p)
		{
			case 'd':
				ival = va_arg(ap, int);
				printf("%d", ival);
				break;
			case 'f':
				dval = va_arg(ap ,double);
				printf("%f", dval);
				break;
			case 's':
				for(sval = va_arg(ap ,char *); *sval; sval++)
					putchar(*sval);
				break;
			default:
				putchar(*p);
				break;
		}
	}

	va_end(ap);	// clean up when done
}
