/* Exercise 5-11.  Entab.  Modify the programs entab and detab to accept a list of tab stops as arguments.  Use the default tab settings if there are no arguements. */

/* Takes text as a input argument.  Ritchie needed to be more clear on his exercises.  Does he mean take a argument flag that determines the first N number of possible tab stop locations get replaced by actual tabs */

/* entab takes a string as a command line argument.  Converts tabsize spaces into tabs. */

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
		printf("Entab:  Converts spaces into tabs in input text.  ");
		printf("Input required.  Please provide a list of text with tab sequences.\n");
		printf("Some terminals like bash require double quotes like \"text\".\n");
		return 1;
	}

	for(i = 1; i < argc; i++)
	{
		strcpy(charLine, argv[i]);
		
		printf("before: %s\n", charLine);		/* like levi asked for to help troubleshoot */
		entab(charLine, MAXIMUM, intTabSize);

		printf("after:  %s", charLine);
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


	strcpy(tempstring, string);		/* copy the string passed by main function to a temporary string.  This is so it doesnt overwrite the data. */


	for(i = 0; tempstring[i] != '\0' && i < limit - 1 && arraypos < limit - 1; i++)		/* count to the end of the input string or the maximum size of the array.  Whatever comes first. */
	{
		string[arraypos++] = tempstring[i]; 
		blockcounter++;

		if(blockcounter == tabsize)
		{
			for(; blockcounter > 0 && string[(arraypos - 1) - (tabsize - blockcounter)] == ' '; --blockcounter)		/* count the number of spaces backwards after the location the tab stop should be */
				intSpaces++;	

			if(intSpaces > 1)	/* replace with a tab if counting backwards from the tab stop there are more than 1 space */
			{
				arraypos -= intSpaces;
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
