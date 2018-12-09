#include "talloc.h"
#include "tnode.h"
#include <stddef.h>
#include <string.h>

/* addtree:  Add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int lineNumber)
{
	int cond;

	if(p == NULL)
	{
		p = talloc();
		p->word = nstrdup(w);
		p->line = lineNumber;
		p->left = p->right = NULL;
		p->center = NULL;
	}
	else if((cond = strcmp(w, p->word)) == 0)  //put new word here if found duplicate  record new structure with line number
	{
		if(p->center != NULL)
			p->center = addtree(p->center, w, lineNumber);
	}
	else if(cond < 0)
		p->left = addtree(p->left, w, lineNumber);
	else
		p->right = addtree(p->right, w, lineNumber);

	return p;
}
