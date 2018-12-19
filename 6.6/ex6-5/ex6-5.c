// Exercise 6-5.  Write a function undef that will remove a name and definition from the table maintained by lookup and install.

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
