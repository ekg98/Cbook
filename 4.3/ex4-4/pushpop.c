/* Push and Pop for polish calculator */

#include <stdio.h>

#define	MAXVAL	100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
	if(sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
	if(sp > 0)
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* clear the stack */
void clear(void)
{
	int i;

	for(i = 0; i < MAXVAL; i++)
		val[i] = 0.0;
	
	sp = 0;	
}

/* views the top element of the stack without removing it */
double viewtop(void)
{
	return val[sp];
}

/* Duplicates the top elements of the stack. */
void duptop(void)
{
	double temp;

	if(sp >= 0 && sp < MAXVAL)
	{
		temp = val[sp];		/* gets the current top element */
		val[++sp] = temp;	/* takes last top element and copies it to a new top element */
	}
	else if(sp == MAXVAL)
		printf("error: stack full, cant duplicate.\n");
	else
		printf("error: stack empty\n");

}

/* swaps the top two elements of the stack */
void swaptop(void)
{
	double secondval;
	double topval;
	if(sp > 0)
	{
		secondval = val[sp];
		topval = val[--sp];

		val[sp++] = secondval;
		val[sp] = topval;
	}
	else
		printf("error: no value to swap.  Does not contain two values.\n");
}
