#include "networking.h"
#include "zmalloc.h"
#include "ae.h"
#include "anet.h"

#include <errno.h>

client *createClient(int fd)
{
        client *cli = zmalloc(sizeof(cli));
	if (fd != -1) {
                anetNonBlock(NULL, fd);
		anetEnableTcpNoDelay(NULL, fd);
	}

	cli->fd = fd;
	if (fd != -1) {
                listAddNodeTail(server.clients, cli);
	}


	return cli;
}

void IterClient()
{
        client *c;
	listNode *ln;
	listIter li;
	listRewind(server.clients, &li);
	while ((ln = listNext(&li)) != NULL) {
                c = listNodeValue(ln);
		printf("fd %d\n", c->fd);
	}
}

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
	       client *c = createClient(cfd);
	       server.connect_num ++;
	       printf(".. %d\n", server.connect_num);
	       //IterClient();
	}
}

