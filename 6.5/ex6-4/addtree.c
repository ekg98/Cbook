#include "talloc.h"
#include "tnode.h"
#include <stddef.h>
#include <string.h>

/* addtree:  Add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if(p == NULL)
	{
		p = talloc();
		p->word = nstrdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if(cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);

	return p;
}

/* converttnode:  Converts a tnode type structure to be sorted by frequency of occurrence */
struct tnode *converttnode(struct tnode *old)
{
	ind cond;
	struct tnode *newTnode = NULL;
	struct tnode *tempTnode = NULL;

	if(old != NULL)
	{
		// copy the information
		newTnode = talloc();
		newTnode->word = nstrdup(old->word);
		newTnode->count = old->count;
		newTnode->left = NULL;
		newTnode->right = NULL;

		if(old->left != NULL)
		{
			if(old->left->count > old->count)
				newTnode->right = old->left;
				
			//converttnode(old->left);
		}
		else if
		//converttnode(old->right);
	}
	return newTnode;
}
