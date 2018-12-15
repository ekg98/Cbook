/* tnode.h:  Structure of tnode */

struct tnode
{
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};
