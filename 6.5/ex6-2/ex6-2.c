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

char *treeprint(struct tnode *, int, char *);

int main(int argc, char *argv[])
{
	struct tnode *root;
	char word[MAXWORD];
	int argWordLength = 6;
	int i, argCounter = 0;

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
		if(isalpha(word[0]))
			root = addtree(root, word);

	treeprint(root, argWordLength, NULL);

	return 0;
}

/* treeprint: in-order print of tree p */
char *treeprint(struct tnode *p, int length, char *parentWord)
{
	char *returnedWord = NULL;
	if(p != NULL)
	{
		/* checking left child.  Returning its word */
		returnedWord = treeprint(p->left, length, NULL);

		/* check left child to parent.  */
		if(strlen(p->word) >= length && returnedWord != NULL && strncmp(p->word, returnedWord, length) == 0)
		{
			printf("%4d %s\n", p->left->count, p->left->word);
			printf("%4d %s\n", p->count, p->word);
		}

		/* check right child to parent */
		else if(strlen(p->word) >= length && parentWord != NULL && strncmp(p->word, parentWord, length) == 0)
		{
			printf("%4d %s\n", NULL, parentWord);	/* this results in duplicates if parent was already printed */
			printf("%4d %s\n", p->count, p->word);
		}

		/* checking right child.  Sending its parent */
		treeprint(p->right, length, p->word);

		return p->word;
	}
	return NULL;
}
