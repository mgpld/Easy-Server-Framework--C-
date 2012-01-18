#include <errno.h>
#include "ndelay.h"
#include "socket.h"
#include "iopause.h"
#include "timeoutaccept.h"

int timeoutaccept6(int s,char ip[16],uint16 *port,unsigned int timeout,uint32 *scope_id)
{
  struct taia now;
  struct taia deadline;
  iopause_fd x;

  x.fd = s;
  x.events = IOPAUSE_READ;
  taia_now(&now);
  taia_uint(&deadline,timeout);
  taia_add(&deadline,&now,&deadline);
  for (;;) {
    taia_now(&now);
    iopause(&x,1,&deadline,&now);
    if (x.revents) break;
    if (taia_less(&deadline,&now)) {
      errno = ETIMEDOUT; /* note that connect attempt is continuing */
      return -1;
    }
  }
  if (!socket_connected(s)) return -1;
  if (ndelay_off(s) == -1) return -1;
  return socket_accept6(s,ip,port,scope_id);
}
