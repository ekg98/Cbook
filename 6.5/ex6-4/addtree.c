#include "talloc.h"
#include "tnode.h"
#include "addtree.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

enum {NO, YES};

// addtree:  Add a node with w, at or below p
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

// converttnode:  Converts a tnode type structure to be sorted by frequency of occurrence
struct tnode *converttnode(struct tnode *new, struct tnode *old)
{
	if(old != NULL)
	{
		converttnode(new, old->left);
		new = addtreenumsort(new, old->word, old->count);
		converttnode(new, old->right);
	}
	return new;
}

// addtreenumsort:  Add words to a binary tree but in numerical order
struct tnode *addtreenumsort(struct tnode *numsortedstruct, char *word, int num)
{
	if(numsortedstruct == NULL)
	{
		numsortedstruct = talloc();
		numsortedstruct->word = nstrdup(word);
		numsortedstruct->count = num;
		numsortedstruct->left = NULL;
		numsortedstruct->right = NULL;
	}
	else if(num == numsortedstruct->count)
		numsortedstruct->right = addtreenumsort(numsortedstruct->right, word, num);
	else if(num < numsortedstruct->count)
		numsortedstruct->right = addtreenumsort(numsortedstruct->right, word, num);
	else
		numsortedstruct->left = addtreenumsort(numsortedstruct->left, word, num);

	return numsortedstruct;
}
