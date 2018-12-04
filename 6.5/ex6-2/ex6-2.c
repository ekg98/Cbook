/* Exercise 6-2.  Write a program that reads a C program and prints in alphabetical order each group of variable */
/* names that are identical in the first 6 characters, but different somewhere thereafter.  Don't count words within */
/* strings and comments.  Make 6 a parameter that can be set from the command line. */

/* This program uses my version of getaword.  This is a modified variant of the main program in chapter 6.5 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "addtree.h"
#include "tnode.h"
#include "getaword.h"

#define	MAXWORD	100

/* function declarations */
void treeprint(struct tnode *, int);

/* enums */
enum {YES, NO};

int main(int argc, char *argv[])
{
	struct tnode *root;
	char word[MAXWORD];
	int argWordLength = 6;
	int i, argCounter = 0;
	int isVariable = NO;

	for(i = 1; i < argc; i++)
	{
		if(*argv[i] == '-')
		{
			if(strcmp(argv[i] + 1, "h") == 0)
			{
					printf("Exercise 6-2.  This program takes a C program as input and returns variables that are identical by a certain length \n");
					printf("default length is 6 characters\n");
					printf("\n\t-\tThis menu.\n");
					printf("\t-n4\tAdjust returned variable length where the number is the length.\n");
					return 0;
			}
			if(*(argv[i] + 1) == 'n')
			{
				argCounter = 2;
				while(*(argv[i] + argCounter))
				{
					if(!isdigit(*(argv[i] + argCounter)))
					{
						printf("Invalid argument:  n must be followed by a valid number.\n");
						return 1;
					}
					argCounter++;
				}
				if(*(argv[i] + 2) == '\0')
				{
					printf("Invalid argument:  n must be followed by a valid number.\n");
					return 1;
				}
				else
					argWordLength = atoi(argv[i] + 2);
			}
			else
			{
				printf("Not a valid argument!\n");
				return 1;
			}
		}
	}

	root = NULL;

	while(getaword(word, MAXWORD) != EOF)
	{
		// if a variable is found and its correct
		if(isVariable == YES && isalpha(word[0]))
		{
			root = addtree(root, word);
			isVariable = NO;
		}

		// skip strings
		if(word[0] == '"')
			continue;

		// skip comments
		if((word[0] == '/' && word[1] == '*') || (word[0] == '/' && word[1] == '/'))
			continue;

		// skip preprocessor directives
		if(word[0] == '#')
			continue;

		// handles basic data types.  Could be expanded for modifiers
		if(strcmp(word, "int") == 0)
		{
			isVariable = YES;
			continue;
		}
		else if(strcmp(word, "char") == 0)
		{
			isVariable = YES;
			continue;
		}
		else if(strcmp(word,"float") == 0)
		{
			isVariable = YES;
			continue;
		}
		else if(strcmp(word, "double") == 0)
		{
			isVariable = YES;
			continue;
		}

	}

	// Display the argWordLength formatted tree
	treeprint(root, argWordLength);

	return 0;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p, int length)
{
	static struct tnode *previous = NULL;	//previous tnode structure to check current tnode structure against.
	static int firstPrint = YES;	//toggle to determine if we should print first word.

	if(p != NULL)
	{

		treeprint(p->left, length);
		if(previous != NULL && strncmp(p->word, previous->word, length) == 0)
		{
			//firstPrint - encountering first matching word make sure to print it.
			if(firstPrint == YES)
				printf("%4d %s\n", previous->count, previous->word);

			printf("%4d %s\n", p->count, p->word);

			firstPrint = NO;	//Toggle that we are not on first print anymore.
		}
		previous = p;
		treeprint(p->right, length);
	}
}
