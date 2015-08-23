#include "server.h"
#include "networking.h"
#include "anet.h"
#include <stdio.h>
#include <errno.h>


void initServer(void)
{
	server.clients = listCreate();
	server.connect_num = 0;
	server.tcp_backlog = 1000;
	server.el = aeCreateEventLoop(20000);
        listenServer(8888, server.ipfd, &server.ipfd_count);

	int j;

	for (j = 0; j < server.ipfd_count; j ++) {
	        if (aeCreateFileEvent(server.el, server.ipfd[j], AE_READABLE, acceptTcpHandler, NULL) == AE_ERR) {

	        }
	}

	aeMain(server.el);
	aeDeleteEventLoop(server.el);
}

void listenServer(int port, int *fds, int *count)
{
        fds[*count] = anetTcpServer(server.neterr, port, NULL, server.tcp_backlog);
	anetNonBlock(NULL, fds[*count]);
	(*count)++;
}
