#include <unistd.h>
#include <stdio.h>
#include <iconv.h>
#include <errno.h>

#include "stralloc.h"

int stralloc_iconv(stralloc *sinput, stralloc *soutput, const char *from, const char *to)
{
	iconv_t cd;
	size_t 	outleft, outsize;
	size_t 	input_length;
	char 	*out, *outptr, *input;

	input = sinput->s;
	input_length = sinput->len;

	if ((cd = iconv_open(to, from)) == (iconv_t)-1) {
		goto nomem;
	}

	/* clean the soutput content */
	soutput->len = 0;
	outsize = ((input_length + 3) & ~3) + 1;
	if ( ! stralloc_ready(soutput, outsize) )
		goto nomem;

	out = soutput->s;
	outleft = soutput->a - 1; /* already allocated bytes */
	outptr = out;

retry:

	if (-1 == iconv(cd, &input, &input_length, &outptr, &outleft)) {
		size_t	 used;

		switch (errno) {
			case E2BIG:

				used = outptr - soutput->s;
				soutput->len = used;
				outsize = (outsize * 2);

				if ( ! stralloc_readyplus(soutput, outsize) ) 
					goto nomem;

				outptr = soutput->s + used;
				outleft = soutput->a - 1 - used;
				goto retry;

			case EINVAL:
				break;
			case EILSEQ:
				/* Invalid sequence, try to get the
				   rest of the string */

				input++;
				input_length--;
				goto retry;
			default:
				break;
		}
	} else {
		soutput->len = outptr - soutput->s; 
	}
	soutput->s[soutput->len] = 0;

	iconv_close(cd);

	return 1;

nomem:
	return 0;
}
