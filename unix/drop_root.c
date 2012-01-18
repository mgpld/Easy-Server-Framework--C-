#include "prot.h"
#include "env.h"
#include "strerr.h"

void drop_root (const char *prog, const char *fatal, const char isfatal)
{
  unsigned char *x;

  if (-1 < env_get("ROOT", &x)) {
    if (chdir(x) == -1)
      strerr_die5sys(111, prog, fatal, "unable to chdir to ", x, ": ") ;
    if (chroot(".") == -1)
      strerr_die5sys(111, prog, fatal, "unable to chroot to ", x, ": ") ;
  }
  else if (isfatal) strerr_die3x(111, prog, fatal, "$ROOT not set") ;
}
