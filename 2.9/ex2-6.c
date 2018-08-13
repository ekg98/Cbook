/* Exercise 2-6.  Write a functuion setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged. */

#include <stdio.h>

unsigned int setbits(unsigned int xbin, int position, int number, unsigned int ybin);

int main()
{
	unsigned int xbinsendtofunction = 0x8;
	unsigned int ybinsendtofunction = 0x13;
	int startposition = 3;	/* Starting position to start obtaining bits to the right including itself */
	int numberofbits = 3;	/* Number of bits to get to the right of position including position */

	printf("%x\n", setbits(xbinsendtofunction, startposition, numberofbits, ybinsendtofunction)); 

	return 0;
}

/* setbits:  Function that returns x that has been modified.  Modifies x to shift to contain the n number of bits to the right of the p position.  Then sets the n number of bits to the right of p position to match the same n number of bits to the right most bits of y.  Leave the bits to the left of p position unchanged. */

unsigned int setbits(unsigned int xbin, int position, int number, unsigned int ybin)
{
	unsigned int xmod;
	unsigned int ymasked;
	unsigned int xmasked;

	xmod = xbin >> (position + 1 - number);	/* Captures a certain number of bits to the right of the position including position */
	ymasked = ybin & ~(~0 << number);	/* Applies a mask to y to only get its n number of bits on the right side */
	xmasked = xmod & (~0 << number);	/* Applies a mask to x to remove its n number of bits on the right and keep its bits on the left */
	return xmasked | ymasked;		/* returns n bits left of p position on x with the n right most bits of y merged together */
}
