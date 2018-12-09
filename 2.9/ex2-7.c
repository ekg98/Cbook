/* Exercise 2-7.  Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted (i.e. 1 changed into 0 and vice versa), leaving the others unchanged. */

#include <stdio.h>

unsigned int invert(unsigned int x, int position, int number);

int main()
{
	unsigned int xbitsendtofunction = 0xAF;
	int startposition = 4;
	int numberofbits = 3;

	printf("%x\n", invert(xbitsendtofunction, startposition, numberofbits));

	return 0;
}

unsigned int invert(unsigned int x, int position, int number)
{
	unsigned int xmod;
	unsigned int bitsafter;
	unsigned int bitsbefore;
	

	xmod = x >> (position + 1 - number);
	bitsbefore = xmod & ~(~0 << number);
	bitsafter = xmod & (~0 << number);
	bitsbefore = ~bitsbefore & ~(~0 << number);
	return bitsafter | bitsbefore;
}
