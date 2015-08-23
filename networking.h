#ifndef _NETWORKING_HEADER_
#define _NETWORKING_HEADER_

#include "server.h"

client *createClient(int fd);

void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask);


#endif
