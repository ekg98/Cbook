// Exercise 7-8.  Write a program to print a set of files, starting each new one on a new page, with a title and a running page count for each file.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "getaline.h"
#include "filestruct.h"

#define MAXLINE	1000
#define PAGELENGTH	15

int openFileStructure(struct fileStructure **, char **[], int *);	// returns amount of files opened.
int closeFileStructure(struct fileStructure **);

int main(int argc, char *argv[])
{
	char line[MAXLINE];
	long lineno = 0;
	int c, except = 0, number = 0, found = 0, filesOpened, filesClosed, fileNameSize = 0;
	int pageCount = 0;
	struct fileStructure *root = NULL;
	struct fileStructure *tempfsp = NULL;

	if(argc == 1)
		fprintf(stderr, "Useage: %s [files]\n", argv[0]);
	else
	{
		filesOpened = openFileStructure(&root, &argv, &argc);

		tempfsp = root;

		while(tempfsp != NULL)	// each file
		{
			printf("%s\n", tempfsp->fileName);	// print fileName header
			++lineno;

			fileNameSize = strlen(tempfsp->fileName);	// prints nice lined bar
			while(fileNameSize--)
				printf("-");
			printf("\n");
			++lineno;



			tempfsp = tempfsp->next;	// advances to next file
			lineno = 0;
		}
	}

	// close files here and free structure
	filesClosed = closeFileStructure(&root);

	if(filesClosed != filesOpened)
		fprintf(stderr, "Error closing files.\n");

	return 0;
}

// openFileStructure:  Takes a initial structure and argv and argc.  Populates the structure with the correct locations of the file pointers.
int openFileStructure(struct fileStructure **rootFileStructure, char **strings[], int *argQuantity)
{
	int filesOpened = 0;
	FILE *fp = NULL;
	struct fileStructure *newFileStructure = NULL;

	if(*argQuantity > 1)
	{
		while(*argQuantity > 1 && (fp = fopen(*++(*strings), "r")) != NULL)
		{
			--*argQuantity;
			++filesOpened;

			if(*rootFileStructure == NULL)	// if root does not contain a sucessive entry
			{
				*rootFileStructure = (struct fileStructure *) malloc(sizeof (struct fileStructure));
				(*rootFileStructure)->next = NULL;
				(*rootFileStructure)->filePointer = fp;
				(*rootFileStructure)->fileName = **strings;
			}
			else	// one is on the line.  We need to create space and add it to the beginning.
			{
				newFileStructure = (struct fileStructure *) malloc(sizeof (struct fileStructure));
				newFileStructure->filePointer = fp;
				newFileStructure->fileName = **strings;
				newFileStructure->next = *rootFileStructure;
				*rootFileStructure = newFileStructure;
			}
		}
		*--(*strings);
	}
	else
		*rootFileStructure = NULL;

	return filesOpened;
}

// closeFileStructure:  Closes and frees the file structure and associatied memory
int closeFileStructure(struct fileStructure **rootFileStructure)
{
	int amountClosed = 0;
	struct fileStructure *tempFileStructure = NULL;

	while(*rootFileStructure != NULL)
	{
		tempFileStructure = (*rootFileStructure)->next;

		if(fclose((*rootFileStructure)->filePointer) == 0)
			++amountClosed;

		free(*rootFileStructure);

		*rootFileStructure = tempFileStructure;
	}

	return amountClosed;
}
