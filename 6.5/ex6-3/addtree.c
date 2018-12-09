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
		if(p->center == NULL)
		{
			p->center = talloc();
			p->center->word = nstrdup(w);
			p->center->line = lineNumber;
			p->left = NULL;
			p->right = NULL;
			p->center = NULL;
		}
	}
	else if(cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);

	return p;
}
