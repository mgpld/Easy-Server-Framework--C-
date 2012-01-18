/*	
 Created stralloc_execute.c the 16:37:03 (30/10/2003) on ro10box
 Last Modification at 17:43:35 (30/10/2003) on ro10box
 Contact : rolphin@games-expert.com
*/

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "uint32.h"
#include "stralloc.h"
#include "prot.h"
#include "wait.h"
#include "strerr.h"

#include "buffer.h"
#include "defines.h"

int stralloc_execute(stralloc *s, char **args, int uid, int gid)
{
	int		pid;
	int		pi[2];
	int		stat;

	if ( pipe(pi) == -1 ) 
		return -1;

	switch ( pid = fork() ) {
		case -1:
			return -1;

	 	case 0:
	   		close(pi[0]);
			
			if ( -1 < gid )
		   		if ( -1 == prot_gid(gid) ) 
					_exit(255);
			
			if ( -1  < uid )
				if ( -1 == prot_uid(uid) ) 
					_exit(255);

	   		if ( -1 == dup2(pi[1], 1 ) ) 
				_exit(255);

			if ( -1 == dup2(pi[1], 2 ) ) 
				_exit(255);

	   		execv(args[0],args);
	   		_exit(111);
	}
	
	close(pi[1]);

	if (stralloc_fd_cat(pi[0], s, 128) == -1) {
		return -1;
	}

	if ( wait_pid(&stat, pid) != -1 ) 
		if ( wait_crashed(stat) ) 
			return -1;

	if ( 255 == wait_exitcode(stat) ) 
		return -1;

	return wait_exitcode(stat);
}
