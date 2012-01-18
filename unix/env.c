#include "str.h"
#include "env.h"

/* Just returning the FIRST occurence of the matching env var */

int env_get(const char *s, char **v)
{
	int i;
	unsigned int len;

	if (!s) return -1;
	len = str_len(s);
	for (i = 0; environ[i]; ++i)
	{
		if (str_start(environ[i],s) && (environ[i][len] == '='))
		{
			*v = environ[i] + len + 1;
			return i;
		}
	}
	return -1;
}
