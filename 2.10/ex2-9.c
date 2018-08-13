/* Exercise 2-9.  In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x.  Explain why.  Use this obervation to write a faster version of bitcount. */
/* x &= (x-1) deletes 1 bit from x and forces the bits to change progressively along the line.  When anded with x it removes all the subsequent bits that were generated when removing 1 bit.  This causes all the bits generated from the subtraction operation to be deleted */

#include <stdio.h>

int bitcount(unsigned int x);

int main()
{
	printf("%d bits in the hex number %x \n", bitcount(0x17), 0x17);

	return 0;
}

/* bitcount:  Counts the amount of bits in a binary input */
int bitcount(unsigned int x)
{
	int b;

	while(x)
	{
		x &= (x - 1);
		++b;
	}

	return b;
}
