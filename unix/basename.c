#include "byte.h"
#include "str.h"

char *basename (const char *path)
{
  unsigned int n, i ;
  if (!path) return 0 ;
  n = str_len(path) ;
  i = byte_rchr((char *)path, n, '/') ;
  return (i == n) ? (char *)path : (char *)path + i+1 ;  
}
