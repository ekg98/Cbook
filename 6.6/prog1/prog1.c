/* Main program from chapter 6.6 */

#include <stdio.h>
#include "nlist.h"
#include "tablelookup.h"

int main()
{
	struct nlist *hellolookup = NULL;

	// install:  substitute Hello when looking up Hi
	install("Hi","Hello");

	// lookup:  Looking up Hi
	hellolookup = lookup("Hi");
	if(hellolookup != NULL)
		printf("%s\n", hellolookup->defn);

	return 0;
}
