/* Polish calculator chapter 4.3 */

/* modified for exercise 4-3 */

#include <stdio.h>
#include <stdlib.h>

#define	MAXOP	100
#define	NUMBER	0

int getop(char s[]);
void push(double);
double pop(void);

int main()
{
	int type, iop1, iop2;
	double op2;
	char s[MAXOP];

	while((type = getop(s)) != EOF)
	{
		switch(type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				op2 = pop();
				push(pop() + op2);
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if(op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '%':
				iop2 = pop();
				iop1 = pop();
				if(iop2 != 0)
					push(iop1 % iop2);
				else
					printf("error: zero modulus\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;

		}
	}
	return 0;
}
