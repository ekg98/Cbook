/* Exercise 4-14.  Define a macro swap(t,x,y) that interchanges two arguments of type t.  (a block structure will help) */

#include <stdio.h>

#define swap(t, x, y) {t temp; temp = x; x = y; y = temp;}

int main()
{
	double xx, yy;

	xx = 5.0;
	yy = 10.0;

	printf("xx = %f, yy = %f\n", xx, yy);

	swap(double , xx, yy);

	printf("xx = %f\nyy = %f\n", xx, yy);

	return 0;
}
