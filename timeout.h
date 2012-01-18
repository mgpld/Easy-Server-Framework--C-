#ifndef TIMEOUT_H
#define TIMEOUT_H

#include "uint16.h"
#include "uint32.h"
#include "iopause.h"

/* ip v4 */
extern int timeoutconn(int s, const char ip[4], uint16 port, unsigned int timeout);
extern int timeoutaccept(int s, char ip[4], uint16 port, unsigned int timeout);

/* ip v6 */
extern int timeoutconn6(int s, const char ip[4], uint16 *port, unsigned timeout, uint32 *scope_id);
extern int timeoutaccept6(int s, char ip[16], uint16 *port, unsigned int timeout, uint32 *scope_id);

/* misc */
extern int timeoutread(int t,int fd,char *buf,int len);
extern int timeoutwrite(int t,int fd,const char *buf,int len);
extern int deepsleep(unsigned int s);

#endif
