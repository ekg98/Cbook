// Exercise 6-6.  Implement a simple version of the #define processor (i.e. no arguments) suitable for use with c programs, based on the routines of this section.
// You may also find getch and ungetch helpful.
// Modified from ex6-5.

#include <stdio.h>
#include "nlist.h"
#include "tablelookup.h"

int main()
{
	struct nlist *hellolookup = NULL;

	// install:  substitute Hello when looking up Hi
	install("Hi", "Hello");

	// lookup:  Looking up Hi
	if((hellolookup = lookup("Hi")) != NULL)
		printf("before undef: %s = %s\n", hellolookup->name, hellolookup->defn);
	else
		printf("before undef: NULL\n");


	// undef me
	if(undef("Hi"))
		printf("Undef sucessful.\n");
	else
		printf("Undef unsucessful.\n");


	// check it after undef
	if((hellolookup = lookup("Hi")) != NULL)
		printf("after undef: %s = %s\n", hellolookup->name, hellolookup->defn);
	else
		printf("after undef: NULL\n");

	return 0;
}
