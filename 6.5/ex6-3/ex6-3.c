/* Exercise 6-3.  Write a cross-referencer that prints a list of all words in a document, and for each word, a list of the line numbers on which it occurs. */
/* Remove noise words like "the", "and", and so on. */

// Need to modify getaword to give a line number
// Need to modify treeprint to display line numbers

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "addtree.h"
#include "tnode.h"
#include "getaword.h"

#define	MAXWORD	100

void treeprint(struct tnode *);

int main()
{
	struct tnode *root;
	char word[MAXWORD];
	int lineNumber = 1;

	root = NULL;

	while(getaword(word, MAXWORD, &lineNumber) != EOF)
		if(isalpha(word[0]))
			root = addtree(root, word, &lineNumber);

	treeprint(root);

	return 0;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	if(p != NULL)
	{
		treeprint(p->left);
		printf("line %d - %s\n", p->line, p->word);
		treeprint(p->center);
		treeprint(p->right);
	}
}
