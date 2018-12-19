// tablelookup.h:  Function prototypes for tablelookup.c  chapter 6.6 program 1

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
int undef(char *);
