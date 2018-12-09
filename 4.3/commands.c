#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void clear(void);
double viewtop(void);
void duptop(void);
void swaptop(void);
void push(double);
double pop(void);
void ungetch(int);
void clearvar(void);
void ungets(int []);
void resetcounter(void);

/* global variable declarations */
double variables[26];
double lastvalue;

/* check which command was entered */
int command(char string[])
{
	double op2;

	if(strcmp(string,"help") == 0)
	{
		printf("Polish calculator help menu:\n");
		printf("----------------------------\n");
		printf("This calculator takes polish notation.  Here is a exmaple.  Operators are always after a pair of numbers.\n");
		printf("\n10 10 +\n");
		printf("\t20\n\n");
		printf("Pressing enter will force numbers out of the stack.\n");
		printf("Available operators are: + - * / and %%.\n");
		printf("Available special functions: sin, exp, and pow.\n");
		printf("This program supports use of variables a-z to do calculations.  Example...\n");
		printf("\na10 b15\n");
		printf("a b +\n");
		printf("\t25\n");
		printf("\n~ is the last calculated value and can be used in a calculation.  Example...\n");
		printf("\n~ 10 +\n");
		printf("\t35\n");
		printf("\nAvailable commands:\n");
		printf("\thelp\t\t- This menu.\n");
		printf("\tviewtop\t\t- Views the top element of the stack without removing it from the stack.\n");
		printf("\tduptop\t\t- Duplicates the top element of the stack.\n");
		printf("\tswaptop\t\t- Swaps the top two elements of the stack.\n");
		printf("\tclear\t\t- Clears the stack.\n");
		printf("\tclearvar\t- Clears the variable set.\n");
		printf("\tquit\t\t- Quits the program.\n");
		printf("\n");
		resetcounter();
	}
	else if(strcmp(string,"clear") == 0)
	{
		clear();
		resetcounter();
	}	
	else if(strcmp(string,"viewtop") == 0)
	{
		printf("\t%.8g\n", viewtop());
		resetcounter();
	}
	else if(strcmp(string,"duptop") == 0)
	{
		duptop();
		resetcounter();
	}
	else if(strcmp(string,"swaptop") == 0)
	{
		swaptop();
		resetcounter();
	}
	else if(strcmp(string,"sin") == 0)
	{
		push(sin(pop()));
	}
	else if(strcmp(string,"exp") == 0)
	{
		push(exp(pop()));
	}
	else if(strcmp(string,"pow") == 0)
	{
		op2 = pop();
		push(pow(pop(), op2));
	}
	else if(strcmp(string,"clearvar") == 0)
	{
		clearvar();
		resetcounter();
	}
	else
		printf("Error command not found: %s\n", string);	/* no command found */
}

int variable(char string[])
{
	int var = 0;
	int i;

	var = string[0];

	for(i = 0; string[i] != '\0'; ++i)
		string[i] = string[i + 1];

	string[i] = '\0';


	variables[(var - 'z' ) + 25] = atof(string);

	return var;
}

double varget(char string[])
{

	return variables[(string[0] - 'z') + 25];
}

void clearvar(void)
{
	int i;

	for(i = 0; i < 26; i++)
		variables[i] = 0.0;
}

double getlast(void)
{
	return lastvalue;
}

void putlast(double value)
{
	lastvalue = value;
}
