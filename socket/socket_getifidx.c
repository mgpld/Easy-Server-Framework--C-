#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include "socket.h"

uint32 socket_getifidx(const char* ifname) {
#ifdef HAVE_N2I
  return if_nametoindex(ifname);
#else
  return 0;
#endif
}
