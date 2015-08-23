#ifndef _WAKEUP_SERVER_HEADER_
#define _WAKEUP_SERVER_HEADER_

#include <string.h>
#include <sys/types.h>

#include "ae.h"
#include "adlist.h"

#define ANET_ERR_LEN 256

struct wakeupServer {
        char neterr[ANET_ERR_LEN];
	int tcp_backlog;
	aeEventLoop *el;
	int ipfd[16];
	int ipfd_count;
	list *clients;
	int connect_num;
};

typedef struct client {
        int fd;
} client;

struct wakeupServer server;

void initServer(void);
void listenServer(int port, int *fds, int *count);

#endif
