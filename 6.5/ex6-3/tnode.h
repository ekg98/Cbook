/* tnode.h:  Structure of tnode */

struct tnode
{
	char *word;
	int line;
	struct tnode *left;
	struct tnode *center;
	struct tnode *right;
};
