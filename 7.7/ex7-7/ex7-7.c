// Exercise 7-7.  Modify the pattern finding program of Chapter 5 to take its input from a set of named files or, if no files are named as arguments ,from the standard input.
// Should the file name be printed when a matching line is found?

#include <stdio.h>
#include <string.h>
#include "getaline.h"
#include "filestruct.h"

#define MAXLINE	1000

int main(int argc, char *argv[])
{
	char line[MAXLINE];
	long lineno = 0;
	int c, except = 0, number = 0, found = 0;

	// check for files here.  Go throught argc until you hit a - or until file can't be found.  Record number of files found, if 0 files are found set structure to use stdin

	while(--argc > 0 && (*++argv)[0] == '-')		// this checks removes a argument from argc and checks for - in that agrument
	{
		while(c = *++argv[0])
		{
			switch(c)
			{
				case 'x':
					except = 1;
					break;
				case 'n':
					number = 1;
					break;
				default:
					printf("find: illegal option %c\n", c);
					argc = 0;
					found = -1;
					break;
			}
		}
	}

	// adjust to use structure of file pointers
	if(argc != 1)
		printf("Useage: find -x -n pattern\n");
	else
		while(getaline(line, MAXLINE) > 0)
		{
			lineno++;
			if((strstr(line, *argv) != NULL) != except)
			{
				if(number)
					printf("%ld:", lineno);
				printf("%s", line);
				found++;
			}
		}

	return found;
}
