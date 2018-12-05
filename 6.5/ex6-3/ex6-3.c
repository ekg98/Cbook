/* Exercise 6-3.  Write a cross-referencer that prints a list of all words in a document, and for each word, a list of the line numbers on which it occurs. */
/* Remove noise words like "the", "and", and so on. */

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
	int lineNumber = 0;

	root = NULL;

	while(getaword(word, MAXWORD, lineNumber) != EOF)
		if(isalpha(word[0]))
			root = addtree(root, word, lineNumber);

	treeprint(root);

	return 0;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	if(p != NULL)
	{
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}
