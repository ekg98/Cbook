/* Extended atof for exercise 4-2. */

#include <ctype.h>
#include <math.h>

double atof(char s[])
{
	double val, power;
	double valbeforeEE, valafterEE;

	int i, sign, EEsign, EEval;

	for(i = 0; isspace(s[i]); i++)
		;
	
	sign = (s[i] == '-') ? -1 : 1;

	if(s[i] == '+' || s[i] == '-')
		i++;

	for(val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');

	if(s[i] == '.')
		i++;

	for(power = 1.0; isdigit(s[i]); i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	valbeforeEE = sign * val / power;
	
	if(tolower(s[i]) == 'e')
	{
		i++;

		EEsign = (s[i] == '-') ? -1 : 1;

		if(s[i] == '+' || s[i] == '-')
			i++;

		for(EEval = 0; isdigit(s[i]); i++)
			EEval = 10 * EEval + (s[i] - '0');
		
		EEval *= EEsign;

		valafterEE = valbeforeEE * pow(10.0, EEval);

		return valafterEE;
	}
	else
		return valbeforeEE;
}
