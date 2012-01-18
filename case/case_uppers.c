#include "case.h"

void case_uppers (register char *s)
{
	register unsigned char const d = 'a' - 'A' ;
	while (*s)
	{
		if (('a' <= *s) && (*s <= 'z')) 
			*s -= d ;
		++s;
	}
}
