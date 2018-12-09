/* Exercise 1-24.  Write a program to check a C program for rudimentary syntax errors like unbalanced parentheses, brackets, and braces.  Don't forget about quotes, both single and double, escape sequences, and comments. (This program is hard if you do it in full generality.) */

#include <stdio.h>

#define	MAXIMUM	1024
#define	YES	1
#define	NO	0

int getprogram(char s[], int lim);

main()
{
	char charProgram[MAXIMUM];

	int i;
	int programlength;
	
	/* declarations for error checking */
	int escapeArmed;
	int comment, inComment;
	int bracket, inBracket;
	int parenthesis, inParenthesis;
	int brace, inBrace;
	int inDoubleQuote;
	int inSingleQuote;
	int error;

	escapeArmed = NO;
	inComment = NO;
	comment = 0;
	inBracket = NO;
	bracket = 0;
	inParenthesis = NO;
	parenthesis = 0;
	inBrace = NO;
	brace = 0;
	inDoubleQuote = NO;
	inSingleQuote = NO;
	error = NO;

	programlength = 0;

	programlength = getprogram(charProgram,MAXIMUM);

		for(i = 0; i <= programlength; ++i)
		{
			if(i < (programlength - 1))
			{
				/* Arms escape sequence */
				if(charProgram[i] > 0)
					if(charProgram[i - 1] == '\\')
						escapeArmed = YES;
					else
						escapeArmed = NO;

				/* checks for entry into comment blocks */
				if(charProgram[i] == '/' && charProgram[i + 1] == '*')
				{
					++comment;
					if(comment != 0)
						inComment = YES;
					else
						inComment = NO;
				}
				/* checks for exit of comment blocks */
				if(charProgram[i] == '*' && charProgram[i + 1] == '/')
				{
					--comment;
					if(comment == 0)
						inComment = NO;
					else
						inComment = YES;
				}

				/* checks for brackets */
				if(charProgram[i] == '[' && inComment == NO)
				{
					++bracket;
					if(bracket != 0)
						inBracket = YES;
					else
						inBracket = NO;
				}
				if(charProgram[i] == ']' && inComment == NO)
				{
					--bracket;
					if(bracket == 0)
						inBracket = NO;
					else
						inBracket = YES;
				}


				/* check for parenthesis */
				if(charProgram[i] == '(' && inComment == NO)
				{
					++parenthesis;
					if(parenthesis != 0)
						inParenthesis = YES;
					else
						inParenthesis = NO;
				}
				if(charProgram[i] == ')' && inComment == NO)
				{
					--parenthesis;
					if(parenthesis == 0)
						inParenthesis = NO;
					else
						inParenthesis = YES;
				}
				
				/* check for braces */
				if(charProgram[i] == '{' && inComment == NO)
				{
					++brace;
					if(brace != 0)
						inBrace = YES;
					else
						inBrace = NO;
				}
				if(charProgram[i] == '}' && inComment == NO)
				{
					--brace;
					if(brace == 0)
						inBrace = NO;
					else
						inBrace = YES;
				}

				/* check for double quotes */
				if(charProgram[i] == '\"' && inComment == NO && escapeArmed == NO)
				{
					if(inDoubleQuote == NO)
						inDoubleQuote = YES;
					else
						inDoubleQuote = NO;
				}
				/* check for single quotes */
				if(charProgram[i] == '\'' && inComment == NO && escapeArmed == NO)
				{
					if(inSingleQuote == NO)
						inSingleQuote = YES;
					else
						inSingleQuote = NO;
				}
			}

		}
	
		if(inComment == YES)
		{
			printf("Error in syntax missing comment.\n");
			error = YES;
		}
		
		if(inParenthesis == YES)
		{
			printf("Error in syntax missing parenthesis.\n");
			error = YES;
		}

		if(inBracket == YES)
		{
			printf("Error in syntax missing brackets.\n");
			error = YES;
		}

		if(inBrace == YES)
		{
			printf("Error in syntax missing braces.\n");
			error = YES;
		}

		if(inSingleQuote == YES)
		{
			printf("Error in syntax missing single quote.\n");
			error = YES;
		}

		if(inDoubleQuote == YES)
		{
			printf("Error in syntax missing double quote.\n");
			error = YES;
		}

		if(error == NO)
			printf("No syntax errors found.\n");

	return 0;
}

/* getprogram:	This function will get a continous string from the keyboard */

int getprogram(char string[], int limit)
{
	int c, i;

	for(i = 0; i < limit - 1 && (c = getchar()) != EOF; ++i)
		string[i] = c;
		
	string[i] = '\0';

	return i;
}
