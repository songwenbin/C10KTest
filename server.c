#include "server.h"
#include "anet.h"
#include <stdio.h>
#include <errno.h>

void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
        int max = 1000;
	int cport, cfd;
	char cip[46];

	while(max--) {
                cfd = anetTcpAccept(server.neterr, fd, cip, sizeof(cip), &cport);
	        if (cfd == ANET_ERR) {
		       if (errno != EWOULDBLOCK) {
                               printf("Accepting clinet connect: %s", server.neterr);
		       }
		       return;
	       }	       
	}
}

void initServer(void)
{
	server.el = aeCreateEventLoop(1024);
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
