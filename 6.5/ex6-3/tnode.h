/* tnode.h:  Structure of tnode */

struct tnode
{
	char *word;
	int line;
	struct tnode *left;
	struct tnode *center;	// Holds a new instance of tnode.  Reserved for the same word but to hold a different line number.
	struct tnode *right;
};
