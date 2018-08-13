#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define	NUMBER	0
#define	BUFSIZE	100
#define	MAXOP	100
#define	MAXVAL	100

/* function declarations */

int getch(void);
void ungetch(int);
int getop(char *s);
void push(double);
double pop(void);
void ungets(char *s);
