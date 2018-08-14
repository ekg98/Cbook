/* Exercise 5-11.  Entab.  Modify the programs entab and detab to accept a list of tab stops as arguments.  Use the default tab settings if there are no arguements. */

/* no arguements no workie.  Pretty simple.  Default settings?  Does it mean this should be written to take a argument to change the tab spacing size?  I have modified it to actually take a list of tab stops.  Input string.  */

#include <stdio.h>
#include <string.h>

#define	MAXIMUM	1024

int entab(char *s, int lim, int ts);

int main(int argc, char *argv[])
{
	char charLine[MAXIMUM];
	int intTabSize;
	int i;

	intTabSize = 8;
	if(argc == 1)
	{
		printf("Input required.  Please provide a list of text with tab sequences.\n");
		printf("Some terminals like bash require double tabs as follows \\\\t\n");
		return 1;
	}

	for(i = 1; i < argc; i++)
	{
		strcpy(charLine, argv[i]);

		entab(charLine, MAXIMUM, intTabSize);

		printf("%s", charLine);
	}

	printf("\n");

	return 0;
}

/* entab:  Replaces strings of spaces with tabs */
int entab(char *string, int limit, int tabsize)
{
	int i;
	int blockcounter = 0, arraypos = 0;
	int intSpaces = 0;
	char tempstring[MAXIMUM];


	strcpy(tempstring, string);		/* copy the string passed by main function to a temporary string */


	for(i = 0; tempstring[i] != '\0' && i < limit - 1 && arraypos < limit - 1; i++)
	{
		string[arraypos++] = tempstring[i]; 
		blockcounter++;

		if(blockcounter == tabsize)
		{
			printf("arraypos = %d\n", arraypos );
			for(; blockcounter > 0 ; --blockcounter)
			{
				if(string[arraypos - blockcounter] == ' ')
					intSpaces++;	
			}

			if(intSpaces > 1)
			{
				arraypos -= intSpaces;
				printf("arraypos %d\n", arraypos);
				string[arraypos] = '\t';
				++arraypos;
			}
			intSpaces = 0;
			blockcounter = 0;
		}
	}

	string[arraypos] = '\0';
		
	return strlen(string);
}
