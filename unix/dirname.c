#include "byte.h"
#include "str.h"

int dirname (char *s, const char *path)
{
  unsigned int n, i ;
  if (!path) return 0 ;
  n = str_len(path) ;
  i = byte_rchr((char *)path, n, '/') ;
  if (i == n)
  {
    s[0] = '.' ;
    s[1] = 0 ;
  }
  else
  {
    byte_copy(s, i, path) ;
    s[i] = 0 ;
  }
  return 1 ;
}
