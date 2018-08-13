/* Exercise 2-8.  Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n bit positions. */

#include <stdio.h>

int rightrot(unsigned int x, int number);

int main()
{
	int inttofunction = 5;
	int bitstomove = 32;

	printf("The value %d moved to the right %d bits.\n", inttofunction, bitstomove);
	printf("Hex value is: %x\n", rightrot(inttofunction, bitstomove));
	printf("Integer value is: %d\n", rightrot(inttofunction, bitstomove));
	
	return 0;
}

/* rightrot:  Rotates integer x to the right by n bit positions. */

int rightrot(unsigned int x, int number)
{
	int i;
	unsigned int xrotatedright;
	unsigned int xmaskbeforerotate;
	unsigned int xmaskafterrotate;
	unsigned int xmask;
	unsigned int rotatecounter, rotatemask;

	xmask = ~(~0 << number);	/* creates a mask to get the bits of x before the rotation to the right */
	xmaskbeforerotate = xmask & x;	/* saves the number of bits that will be rotated so they don't fall into space */
	xrotatedright = x >> number;	/* rotates x to the right number of bits.  Number has padded zeros in leftmost slots */

	/* rotate mask uses a dummy mask to count the amount of bits in its respective type */
	rotatemask = ~0;
	while( rotatemask )
	{
		rotatemask = rotatemask << 1;
		++i;
	}

	xmaskafterrotate = xmaskbeforerotate << i - number;	/* shifts the saved bits to the correct position to be transplanted back into x */

	return xmaskafterrotate | xrotatedright;	/* transplants the bits back into x (effectively linking x in a loop with itself) */
}

