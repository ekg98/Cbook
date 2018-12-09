#include <stdio.h>

int main()
{
	int i, c;
	char s[1024];

	for(i = 0; !(!(i < 1024 - 1) + !((c = getchar()) != '\n') + !(c !=EOF)); ++i)
		s[i] = c;

	s[i] = '\0';

	printf("%s\n", s);
	return 0;
}
