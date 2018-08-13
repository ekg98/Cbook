/* Exercise 3-1.  Our binary search makes two tests inside the loop, when one would suffice (at the price of more tests outside).  Write a version with only one test inside the loop and measure the difference in run-time. */

#include <stdio.h>

#define	MAXIMUM	1024

int binsearch(int x, int v[], int n);

int main()
{
	int array[MAXIMUM];
	int searchnumber = 500;
	int i;

	for(i = 0; i < MAXIMUM; ++i)
		array[i] = i;

	printf("%d was found at location %d", searchnumber, binsearch(searchnumber, array, MAXIMUM));
	
	return 0;
}

/* binsearch:  find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while(low <= high)
	{
		mid = (low + high) / 2;
		if(x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}
