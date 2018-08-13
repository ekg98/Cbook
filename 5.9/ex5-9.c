/* Exercise 5-9.  Rewrite the routines day_of_year and month_day with pointers instead of indexing. */

#include <stdio.h>

#define	YEAR	2018
#define	YEARDAY	100

int day_of_year(int year, int month, int day);			/* returns 0 if error */
int month_day(int year, int day, int *pmonth, int *pday);	/* returns 0 if error */

static char daytab[2][13] =
{
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main()
{
	int month, year, day, yearday;

	if(month_day(YEAR, YEARDAY, &month, &day))
		printf("month_day(), month = %d, day = %d, year = %d, yearday = %d\n", month, day, YEAR, YEARDAY);
	else
		printf("Error: input out of range.\n");
	
	if(yearday = day_of_year(YEAR, month, day))
		printf("%d = day_of_year(), year = %d, month = %d, day = %d\n", yearday , YEAR, month, day);
	else
		printf("Error: input out of range.\n");

	return 0;
}

int day_of_year(int year, int month, int day)
{
	int i, leap;

	if(month < 1 || month > 12 || day < 1 || day > 365)
		return 0;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;


	for(i = 1; i < month; i++)
	{
		day += *(*(daytab + leap) + i);

	}

	return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	
	if(yearday < 1 || yearday > 365)
		return 0;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	for(i = 1; yearday > *(*(daytab + leap) + i); i++)
		yearday -= *(*(daytab + leap) + i);
	*pmonth = i;
	*pday = yearday;
}
