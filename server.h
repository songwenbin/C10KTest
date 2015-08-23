#ifndef _WAKEUP_SERVER_HEADER_
#define _WAKEUP_SERVER_HEADER_

#include <string.h>
#include <sys/types.h>
#include "ae.h"

#define ANET_ERR_LEN 256

void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask);

struct wakeupServer {
        char neterr[ANET_ERR_LEN];
	int tcp_backlog;
	aeEventLoop *el;
	int ipfd[16];
	int ipfd_count;
};

struct wakeupServer server;

void initServer(void);
void listenServer(int port, int *fds, int *count);

#endif
