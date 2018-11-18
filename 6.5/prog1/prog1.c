/* Program from the chapter 6.5 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "addtree.h"
#include "talloc.h"

#define	MAXWORD	100

void treeprint(struct tnode *);

int main()
{
	struct tnode *root;
	char word[MAXWORD];

	root = NULL;

	while(getword(word, MAXWORD) != EOF)
		if(isalpha(word[0]))
			root = addtree(root, word);

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
