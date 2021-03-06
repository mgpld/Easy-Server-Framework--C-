#include "fmt.h"
#include "textcode.h"
#include "str.h"
#include "haveinline.h"

static inline int tohex(char c) {
  return c>9?c-10+'a':c+'0';
}

unsigned int fmt_codehexdump(char* dest,const char* src,unsigned int len) {
  register const unsigned char* s=(const unsigned char*) src;
  unsigned long written=0,i;
  for (i=0; i<len; ++i) 
  {
  	 dest[written]='\\';
  	 dest[written+1]='x';
    dest[written+2]=tohex(s[i]>>4);
    dest[written+3]=tohex(s[i]&15);
    written+=4;
  }
  return written;
}
