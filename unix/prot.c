#include "prot.h"

int prot_gid (int gid)
{
  if (setgroups(1, (const gid_t *)&gid) == -1) return -1 ;
  return setgid(gid); 
}
