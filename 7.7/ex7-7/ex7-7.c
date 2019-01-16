// Exercise 7-7.  Modify the pattern finding program of Chapter 5 to take its input from a set of named files or, if no files are named as arguments ,from the standard input.
// Should the file name be printed when a matching line is found?

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "getaline.h"
#include "filestruct.h"

#define MAXLINE	1000

int openFileStructure(struct fileStructure *, char *[], int *);	// returns amount of files opened.

int main(int argc, char *argv[])
{
	char line[MAXLINE];
	long lineno = 0;
	int c, except = 0, number = 0, found = 0, filesOpened;
	struct fileStructure *root = NULL;
	struct fileStructure *tempfsp = NULL;

	filesOpened = openFileStructure(root, argv, &argc);

	printf("Files Opened - %d\n", filesOpened);

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


	if(argc != 1)
		printf("Useage: find [files] -x -n pattern\n");
	else
	{
		if(filesOpened == 0)
		{
			while(getaline(stdin, line, MAXLINE) > 0)
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
		}
		else	// if detected files as input use them as the stream
		{
			tempfsp = root;
			while(tempfsp != NULL)
			{
				while(getaline(tempfsp->filePointer, line, MAXLINE) > 0)
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

				tempfsp = tempfsp->next;
			}
		}
	}

	// close files here
	return found;
}

int openFileStructure(struct fileStructure *rootFileStructure, char *strings[], int *argQuantity)
{
	int filesOpened = 0;
	FILE *fp = NULL;
	struct fileStructure *newFileStructure = NULL;

	if(*argQuantity > 1)
	{
		while(*argQuantity > 1 && (fp = fopen(*++strings,"r")) != NULL)
		{
			--argQuantity;
			++filesOpened;

			if(rootFileStructure == NULL)	// if root does not contain a sucessive entry
			{
				rootFileStructure = (struct fileStructure *) malloc(sizeof (struct fileStructure));
				rootFileStructure->next = NULL;
				rootFileStructure->filePointer = fp;
				rootFileStructure->fileName = *strings;
			}
			else	// one is on the line.  We need to create space and add it to the beginning.
			{
				newFileStructure = (struct fileStructure *) malloc(sizeof (struct fileStructure));
				newFileStructure->filePointer = fp;
				newFileStructure->fileName = *strings;
				newFileStructure->next = rootFileStructure;
				rootFileStructure = newFileStructure;
			}
		}
	}
	else
		rootFileStructure = NULL;

	return filesOpened;
}
