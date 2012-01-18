/*	
 Created stralloc_count_char.c the 21:15:16 (26/09/2004) on ro10box
 Last Modification at 22:27:00 (26/09/2004) on ro10box
 Contact : rolphin@games-expert.com
*/

#include "stralloc.h"
#include "uint32.h"

#define EX_DOUBLE	1

int stralloc_count_char(stralloc  *s, const char c, uint32 *level, uint32 flags)
{
	uint32		i;
	uint32		cnt = 0;

	if ( s->len == 0 )
		return 0;

	if ( flags & EX_DOUBLE ) {
		for ( i = 0; i < s->len; i++ ) {
			if ( s->s[i] == c ) {
				while ( s->s[i + 1] == c && i < s->len ) 
					i++;
				cnt++;
			}
		}
		*level = cnt;
		return 1;
	}

	return 0;
}
