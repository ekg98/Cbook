/* Program ch 5.7.  day_of_year and month_day */

#include <stdio.h>

#define	YEAR	2018
#define	YEARDAY	100

int day_of_year(int year, int month, int day);
void month_day(int year, int day, int *pmonth, int *pday);

static char daytab[2][13] =
{
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main()
{
	int month, year, day;

	month_day(YEAR, YEARDAY, &month, &day);
	printf("month_day(), month = %d, day = %d, year = %d, yearday = %d\n", month, day, YEAR, YEARDAY);
	printf("%d = day_of_year(), year = %d, month = %d, day = %d\n", day_of_year(YEAR, month, day), YEAR, month, day);
	return 0;
}

int day_of_year(int year, int month, int day)
{
	int i, leap;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	for(i = 1; i < month; i++)
		day += daytab[leap][i];

	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	for(i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}
