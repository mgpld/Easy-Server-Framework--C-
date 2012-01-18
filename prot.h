#ifndef _PROT_H_
#define _PROT_H_

#include <sys/types.h>
#include <unistd.h>
#include <grp.h>

extern int prot_gid(int gid);
#define prot_uid(x) setuid(x)

extern void drop_uidgid (const char *prog, const char *fatal, const char isfatal);
extern void drop_root (const char *prog, const char *fatal, const char isfatal);

#endif 
