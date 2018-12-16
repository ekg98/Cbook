/* Exercise 6-4.  Write a program that prints the distint words in its input sorted into decreasing order of frequency of occurrence. */
/* Precede each word by its count. */

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
	struct tnode *numsort;

	char word[MAXWORD];

	root = NULL;

	while(getaword(word, MAXWORD) != EOF)
		if(isalpha(word[0]))
			root = addtree(root, word);

	numsort = converttnode(root);

	printf("\n\nSorted alphabetically.\n\n");
	treeprint(root);
	printf("\n\nSorted by occurrence.\n\n");
	treeprint(numsort);

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
