#ifndef _WAKEUP_SERVER_HEADER_
#define _WAKEUP_SERVER_HEADER_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "ae.h"
#include "adlist.h"
#include "wstable.h"

#define ANET_ERR_LEN 256

struct wakeupServer {
        char neterr[ANET_ERR_LEN];
	int tcp_backlog;
	aeEventLoop *el;
	int ipfd[16];
	int ipfd_count;
	list *clients;
	int connect_num;
	struct WSTable *table;
};

typedef struct client {
        int fd;
	char* querybuf;
	int querybuf_idx;
} client;

struct wakeupServer server;

void initServer(void);
void listenServer(int port, int *fds, int *count);

#endif
