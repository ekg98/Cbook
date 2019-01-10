//  Exercise 7-6.  Write a program to compare to files, printing the first line where they differ.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE	250

int main(int argc, char *argv[])
{
	FILE *fileOne;
	FILE *fileTwo;

	char stringFileOne[MAXLINE];
	char stringFileTwo[MAXLINE];

	if(argc != 3)
	{
		fprintf(stderr, "%s : Input error.  Two filenames required.\n", *argv);
		exit(1);
	}
	else
	{
		fileOne = fopen(argv[1], "r");
		if(fileOne == NULL)
		{
			fprintf(stderr, "%s : Error cannot open file %s.\n", *argv, argv[1]);
			exit(2);
		}

		fileTwo = fopen(argv[2], "r");
		if(fileTwo == NULL)
		{
			fprintf(stderr, "%s : Error cannot open file %s.\n", *argv, argv[2]);
			exit(2);
		}

		while(!feof(fileOne))
		{
			fgets(stringFileOne, MAXLINE, fileOne);
			fgets(stringFileTwo, MAXLINE, fileTwo);

			if(strcmp(stringFileOne,stringFileTwo) == 0)	// if the strings are the same then continue and grab the next.
				continue;
			else	// must have found a difference.  Print the differences.
			{
				printf("\n");
				printf("< %s\n", stringFileOne);
				printf("> %s\n", stringFileTwo);
				exit(0);
			}
		}
	}

	fclose(fileOne);
	fclose(fileTwo);

	return 0;
}
