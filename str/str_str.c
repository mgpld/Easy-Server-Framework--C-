/*	
	Created str_str.c the 15:45:05 (13/11/2002) on rolphin
	Last Modification of str_str.c at 15:49:41 (13/11/2002) on rolphin
	Contact : rolphin@games-expert.com
*/

#include "str.h"

int str_str(const char *src, const char *needle, unsigned int max)
{
	unsigned int	len;
	unsigned int 	match = 0;
	unsigned int	i = 0;
	unsigned int	j = 0;
	unsigned int	ret = 0;

	len = str_len(needle);
	if (max < len) return -1;
	for (i = 0; i < max; i++)
	{
		if (src[i] == needle[0])
		{
			ret = i;
			match = 1;
			for (;;)
			{
				if (src[i + 1] != needle[j + 1]) break;
				if (++match == len) goto FOUND;
			}
		}
	}
	return -1;

FOUND:
		return ret;
}
