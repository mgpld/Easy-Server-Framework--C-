#include "prot.h"
#include "env.h"
#include "scan.h"
#include "strerr.h"

void drop_uidgid (const char *prog, const char *fatal, const char isfatal)
{
	unsigned char *x;
	int id = 0;
	
	if (-1 < env_get("GID", &x)) {
		if ( 0 < scan_uint(x, &id) ) {
	  		if (prot_gid(id) == -1) {
	    			strerr_die3sys(111, prog, fatal, "unable to setgid: ");
			}
		} else {
			errno = ERANGE;
			strerr_die3sys(111, prog, fatal, "GID is not numerical: ");
		}
	}
	else if (isfatal) strerr_die3x(111, prog, fatal,"$GID not set") ;
	
	if (-1 < env_get("UID", &x)) {
		if ( 0 < scan_uint(x, &id) ) {
			if (prot_uid(id) == -1) {
				strerr_die3sys(111, prog, fatal, "unable to setuid: ");
			}
		} else {
			errno = ERANGE;
			strerr_die3sys(111, prog, fatal, "UID is not numerical: ");
		}
	}
	else if (isfatal) strerr_die3x(111, prog, fatal, "$UID not set") ;
}
