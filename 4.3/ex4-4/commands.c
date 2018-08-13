#include <string.h>
#include <stdio.h>

void clear(void);
double viewtop(void);
void duptop(void);
void swaptop(void);

/* check which command was entered */
int command(char string[])
{
	if(strcmp(string,"help") == 0)
	{
		printf("Polish calculator help menu:\n");
		printf("----------------------------\n");
		printf("This calculator takes polish notation.  Here is a exmaple.  Operators are always after a pair of numbers.\n");
		printf("\n10 10 +\n");
		printf("\t20\n\n");
		printf("Pressing enter will force numbers out of the stack.\n");
		printf("Available operators are: + - * / and %%.\n");
		printf("\nctrl + d to exit...\n");
		printf("\nAvailable commands:\n");
		printf("\thelp\t- This menu.\n");
		printf("\tviewtop\t- Views the top element of the stack without removing it from the stack.\n");
		printf("\tduptop\t- Duplicates the top element of the stack.\n");
		printf("\tswaptop\t- Swaps the top two elements of the stack.\n");
		printf("\tclear\t- Clears the stack.\n");
		printf("\n");
	}
	else if(strcmp(string,"clear") == 0)
		clear();
	else if(strcmp(string,"viewtop") == 0)
		printf("\t%.8g\n", viewtop());
	else if(strcmp(string,"duptop") == 0)
		duptop();
	else if(strcmp(string,"swaptop") == 0)
		swaptop();
	else
		printf("Error command not found: %s\n", string);	/* no command found */
}

