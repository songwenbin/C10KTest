#include "networking.h"
#include "zmalloc.h"
#include "ae.h"
#include "anet.h"

#include <errno.h>
#include "wstable.h"
#include "protocol.h"

void readDataFromClient(aeEventLoop *el, int fd, void *privdata, int mask); 

client *createClient(int fd)
{
        client *cli = zmalloc(sizeof(cli));
	if (fd != -1) {
                anetNonBlock(NULL, fd);
		anetEnableTcpNoDelay(NULL, fd);
	}

	if (aeCreateFileEvent(server.el, fd, AE_READABLE, readDataFromClient, cli) == AE_ERR) {
		close(fd);
                zfree(cli);
	}

	cli->fd = fd;
	if (fd != -1) {
                listAddNodeTail(server.clients, cli);
	}

	cli->querybuf = (char *)malloc(sizeof(char)*1024);


	return cli;
}

void freeClient(client *c) 
{
        sdsfree(c->querybuf);
	zfree(c);
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

void processInputBuffer(client *c);
void readDataFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
        client *c = (client *)privdata;
	int nread, readlen;
	size_t qblen = 0;
	readlen = 1024;
	printf("read data:");
	//qblen = sdslen(c->querybuf);
	/*
	if (c->querybuf_peak < qblen) {
                c->querybuf_peak = qblen;
	}
	*/
	//c->querybuf = sdsMakeRoomFor(c->querybuf, readlen);
	nread = read(fd, c->querybuf+qblen, readlen);
	if (nread == -1) {
                if (errno == EAGAIN) {
			return;
		} else {
			freeClient(c);
			return;
		}
	} else if (nread == 0) {
	        freeClient(c);
	        return;
	}
	//sdsIncrLen(c->querybuf, nread);

	processInputBuffer(c);
}

void processInputBuffer(client *c) {
        printf("%s", c->querybuf);
	char *id;
	if (parseProtocolHeader(c) == DEVICE_CONN) {
		id = getDeviceId(c);	
	}
}
