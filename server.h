#ifndef _WAKEUP_SERVER_HEADER_
#define _WAKEUP_SERVER_HEADER_

#include <string.h>
#include <sys/types.h>

#define ANET_ERR_LEN 256

struct wakeupServer {
        char neterr[ANET_ERR_LEN];
	int tcp_backlog;
};

struct wakeupServer server;

void initServer(void);
void listenServer(int port);

#endif
