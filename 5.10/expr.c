/* Exercise 5-10.  Write the program expr, which evaluates a reverse Polish expression from the command line, where each operator or operand is a seperate arguement.  For example, expr 2 3 4 + * evaluates 2 x (3 + 4). */

#include "expr.h"

int main(int argc, char *argv[])
{
	int i;
	int type, iop1, iop2;
	double op2;
	char s[MAXOP];

	if(argc == 1)	/* if you don't enter any data */
	{
		printf("Expecting operators and operands.\n");
		return 0;
	}
	
	printf("argc = %d\n", argc);

	for(i = 1; i < argc; i++)
	{
		ungets(argv[i]);
		type = getop(s);
		printf("i = %d, s = %s\n", i, s);
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
			default:
				printf("error: entering the unknown.\n");
				break;
		}
	}

	printf("\t%.8g\n", pop());

	return 0;
}
