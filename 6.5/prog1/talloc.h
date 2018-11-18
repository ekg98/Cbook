/* talloc.h:  Contains function declarations for talloc and strdup */

struct tnode
{
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *talloc(void);
char *nstrdup(char *);
