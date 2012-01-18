#include <unistd.h>
#include "str.h"
#include "byte.h"
#include "stralloc.h"
#include "strerr.h"

int absolutepath (stralloc *sa, const char *path)
{
  int r = 1 ;
  if (!path) r = stralloc_copys(sa, "/") ;
  else if (path[0] == '/') r = stralloc_copys(sa, path) ;
  else
  {
    unsigned int n = 0 ;
    for (;;)
    {
      n += 1024 ;
      if (!stralloc_ready(sa, n))
      {
        r = 0 ;
        break ;
      }
      if (getcwd(sa->s, n)) break ;
      if (errno != ENOMEM)
      {
        r = 0 ;
        break ;
      }
    }
    sa->len = str_len(sa->s) ;
    if (r) r = stralloc_append(sa, "/") && stralloc_cats(sa, path) ;
    if (!r) stralloc_free(sa) ;
  }
  return r ? stralloc_0(sa) : 0 ;
}
