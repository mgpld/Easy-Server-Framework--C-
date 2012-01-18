#include "stralloc.h"
#include "str.h"

static int my_str_str(const char *src, const char *needle, unsigned int max)
{
	unsigned int	len;
	unsigned int 	match = 0;
	unsigned int	i = 0;
	unsigned int	ret = 0;

	len = str_len(needle);
	if (max < len) return -1;
	for (i = 0; i < max; i++) {
		if (src[i] == needle[0]) {
			ret = i++;
			match = 1;

			for (;;) {

				if (match == len)
					goto found;

				if (src[i++] != needle[match++])
					break;
			}
		}
	}
	return -1;

found:
	return ret;
}

int stralloc_replace(stralloc *str, const char *this, const char *that)
{
	stralloc	tmp = {0};
	unsigned int	i = 0;
	unsigned int	len = 0;
	unsigned int	remain = 0;
	char		*pos = 0;

	if (0 == this) goto error;
	if (0 == that) goto error;
	pos = str->s;
	len = str_len(this);
	remain = str->len;
	if (!stralloc_copys(&tmp, "")) goto error;
	for (;;)
	{
		if (remain <= 0) break;
		i = my_str_str(pos, this, remain);
		if (i == -1) break;
		if (!stralloc_catb(&tmp, pos, i)) goto error;
		if (!stralloc_cats(&tmp, that)) goto error;
		pos += i + len;
		remain -= i + len;
	}
	if (remain > 0)
	{
		if (!stralloc_catb(&tmp, pos, remain)) goto error;
	}
	if (!stralloc_copy(str, &tmp)) goto error;
	stralloc_free(&tmp);
	return 1;
	
error:
	stralloc_free(&tmp);
	return 0;
}
