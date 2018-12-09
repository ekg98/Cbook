/* Polish calculator chapter 4.3 */

/* modified for exercise 4-3 */

/* Exercise 4-3.  Given the basic framework, it's straightforward to extend the calculator.  Add the modulus(%) operator and provisions for negative numbers. */
/* Exercise 4-4.  Add commands to print the top element of the stack without popping, to duplicate it, and to swap the top two elements. Add a command to clear the stack. */

#include <stdio.h>
#include <stdlib.h>

#define	MAXOP	100
#define	NUMBER	0
#define	COMMAND	1
#define	VARIABLESTORE 2
#define	VARIABLE 3
#define	LASTVALUE 4

int getop(char s[]);
void push(double);
double pop(void);
int command(char string[]);
int variable(char string[]);
double varget(char string[]);
double getlast(void);
void putlast(double);

int main()
{
	int type, iop1, iop2;
	double op2, popped;
	char s[MAXOP];
	int cmd;

	while((type = getop(s)) != EOF)
	{
		switch(type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case COMMAND:
				command(s);
				break;
			case VARIABLESTORE:
				variable(s);
				break;
			case VARIABLE:
				push(varget(s));
				break;
			case LASTVALUE:
				push(getlast());
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
				popped = pop();
				putlast(popped);
				printf("\t%.8g\n", popped);
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;

		}
	}
	return 0;
}
