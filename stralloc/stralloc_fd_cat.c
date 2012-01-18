#include <errno.h>
#include <unistd.h>
#include "uint32.h"
#include "stralloc.h"

/* stralloc_fd_cat(int fd, stralloc *s, uint32 size)
read from fd and fill s with data using chunk of size bytes
return -1 if error
return bytes read if not
*/
int stralloc_fd_cat(int fd, stralloc *s, uint32 size)
{
	int 	r;

	for (;;) {
		if ( ! stralloc_readyplus(s, size) ) { 
			close(fd); 
			return -1; 
		}
		
		r = read(fd, s->s + s->len, size);
		
		if (r == -1) 
			if (errno == EINTR) 
				continue;

		if (r <= 0) { 
			close(fd); 
			return r; 
		}
		s->len += r;
	}
}
