#include "networking.h"
#include "zmalloc.h"
#include "ae.h"
#include "anet.h"

#include <errno.h>
#include "wstable.h"
#include "protocol.h"

void readDataFromClient(aeEventLoop *el, int fd, void *privdata, int mask); 

//
client *createClient(int fd)
{
        client *cli = malloc(sizeof(cli));
	if (fd != -1) {
                anetNonBlock(NULL, fd);
		anetEnableTcpNoDelay(NULL, fd);
	}

	if (aeCreateFileEvent(server.el, fd, AE_READABLE, readDataFromClient, cli) == AE_ERR) {
		close(fd);
                zfree(cli);
	}

	cli->querybuf = (char *)malloc(sizeof(char)*1024);
	cli->querybuf_idx = 0;
	cli->fd = fd;
	if (fd != -1) {
                listAddNodeTail(server.clients, cli);
		createFdofWSEntry(server.table, cli->fd);
	}

	return cli;
}

void freeClient(client *c) 
{
	if (c->fd != -1) {
		aeDeleteFileEvent(server.el, c->fd, AE_READABLE);
		close(c->fd);
	}

	if (c->fd != -1) {
		listNode *ln;
		ln = listSearchKey(server.clients, c);
		listDelNode(server.clients, ln);
		// Todo delete WSEntry
	}
        free(c->querybuf);
	c->querybuf = NULL;
	free(c);
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
	}
}

void processInputBuffer(client *c);
void readDataFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
        client *c = (client *)privdata;
	int nread, readlen;
	readlen = 1024;
	printf("read data:");
	nread = read(fd, c->querybuf, readlen);
	if (nread == -1) {
                if (errno == EAGAIN) {
			printf("1\n");
			return;
		} else {
			printf("2\n");
			freeClient(c);
			return;
		}
	} else if (nread == 0) {
		printf("3\n");
	        freeClient(c);
	        return;
	}

	processInputBuffer(c);
}

void processInputBuffer(client *c) {
        //printf("%s", c->querybuf);
	char *id;
	int len = 0;

	if (parseProtocolHeader(c) == DEVICE_CONN) {
		id = parseDeviceId(c, &len);	
		if (len > 1024 - c->querybuf_idx) {
			c->querybuf_idx = 0;
			return;
		}
		addId2WSEntry(server.table, c->fd, id, len);

		int i = 0;
		printf("len :%d\n", len);
		printf("data:");
		for (i = 0; i < len; i++ ) {
			printf("%c", id[i]);
		}
		printf("\n");
		free(id);
	}
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
