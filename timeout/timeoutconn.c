#include <errno.h>
#include "ndelay.h"
#include "socket.h"
#include "iopause.h"
#include "timeoutconn.h"

int timeoutconn(int s,const char ip[4],uint16 port,unsigned int timeout)
{
  struct taia now;
  struct taia deadline;
  iopause_fd x;

  if (socket_connect4(s,ip,port) == -1) {
    if ((errno != EWOULDBLOCK) && (errno != EINPROGRESS)) return -1;
    x.fd = s;
    x.events = IOPAUSE_WRITE;
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
  }

  if (ndelay_off(s) == -1) return -1;
  return 0;
}
