// tablelookup.c:  Contains functions associated with 6.6 program 1 table tablelookup

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "nlist.h"
#include "tablelookup.h"
#include "strdupe.h"

#define HASHSIZE	101

static struct nlist *hashtab[HASHSIZE];

enum {NO, YES};

// hash:  form hash value for string s
unsigned hash(char *s)
{
	unsigned hashval;

	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

// lookup:  look for s in hashtab
struct nlist *lookup(char *s)
{
	struct nlist *np;

	for(np = hashtab[hash(s)]; np != NULL; np = np->next)
		if(strcmp(s, np->name) == 0)
			return np;
	return NULL;
}

// install:  put (name, defn) in hashtab
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if((np = lookup(name)) == NULL)		// not found
	{
		np = (struct nlist *) malloc(sizeof(*np));

		if(np == NULL || (np->name = strdupe(name)) == NULL)
			return NULL;

		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else
		free((void *) np->defn);

	if((np->defn = strdupe(defn)) == NULL)
		return NULL;

	return np;
}

// undef:  Undefines a name within a instance of nlist.  Returns 1 if sucessful.  0 if failure.
int undef(char *name)
{
	struct nlist *np = NULL;
	struct nlist *npprev = NULL;

	int isFound = NO;

	for(np = hashtab[hash(name)], npprev = hashtab[hash(name)]; np != NULL; np = np->next)
	{
		if(strcmp(name, np->name) == 0)
		{
			isFound = YES;
			break;
		}
		npprev = np;	// this will stay with the previous pointer because the loop breaks
	}

	if(isFound == YES)
	{
		npprev->next = np->next;

		free(np->name);
		free(np->defn);
		free(lookup(name));
		return 1;
	}
	else
		return 0;
}
