/*	
 Created scan_taia64.c the 21:34:16 (17/07/2004) on ro10box
 Last Modification at 21:42:23 (17/07/2004) on ro10box
 Contact : rolphin@games-expert.com
*/

#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "fmt.h"
#include "str.h"

#include "taia.h"

int taia64_date(const char *taiastamp, uint32 len, char date[HUMAN_TIMESTAMP])
{
	time_t 		secs = 0;
	unsigned long 	nanosecs = 0;
	unsigned long 	u;
	struct tm 	*t;
	uint32		i;

	if ( '@' != taiastamp[0] )
		goto wrong_format;
		
	for ( i = 1; i < len; i++ ) {
		if ( 0 == taiastamp[i] )
			goto wrong_format;

        	u = taiastamp[i] - '0';
        	if (u >= 10) {
        		u = taiastamp[i] - 'a';
        		u += 10;
        	}
		secs <<= 4;
		secs += nanosecs >> 28;
		nanosecs &= 0xfffffff;
		nanosecs <<= 4;
		nanosecs += u;
	}

	secs -= 4611686018427387914ULL;
	t = localtime(&secs);
	
	i = fmt_ulong(date, 1900 + t->tm_year);
	date[i++] = '-';
	i += fmt_uint0(date + i, 1 + t->tm_mon, 2);
	date[i++] = '-';
	i += fmt_uint0(date + i, t->tm_mday, 2);
	date[i++] = ' ';
	i += fmt_uint0(date + i,t->tm_hour, 2); 
	date[i++] = ':'; 
	i += fmt_uint0(date + i, t->tm_min, 2);
	date[i++] = ':'; 
	i += fmt_uint0(date + i,t->tm_sec, 2);
	date[i++] = '.'; 
	i += fmt_uint0(date + i, nanosecs, 9);

	return i;

wrong_format:
	return 0;
}
