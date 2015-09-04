#include "networking.h"
#include "zmalloc.h"
#include "ae.h"
#include "anet.h"

#include <errno.h>
#include "wstable.h"
#include "protocol.h"

void readDataFromClient(aeEventLoop *el, int fd, void *privdata, int mask); 
void processInputBuffer(client *c);
void processRegisterCommand(client *c, char *id, int len);
void processWakeupCommand(client *c, char *id, int len);
void processProtocolCommand(client *c, char head, char *id, int len);

client *createClient(int fd)
{
        client *cli = malloc(sizeof(cli));
	if (fd != -1) {
                anetNonBlock(NULL, fd);
		anetEnableTcpNoDelay(NULL, fd);
	}

	if (aeCreateFileEvent(server.el, fd, AE_READABLE, readDataFromClient, cli) == AE_ERR) {
		close(fd);
                free(cli);
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

void processInputBuffer(client *c) 
{
	int len = 0;
	char head = parseProtocolHeader(c);
	char *id   = parseDeviceId(c, &len);
	c->querybuf_idx = 0;
	processProtocolCommand(c, head, id, len);
}

void processProtocolCommand(client *c, char head, char *id, int len)
{
        if (head == REGISTER_DEVICE_HEAD) {
		processRegisterCommand(c, id, len);
	} else if (head == WAKEUP_DEVICE_HEAD) {
		processWakeupCommand(c, id, len);
	}
}

void processRegisterCommand(client *c, char *id, int len)
{
	addId2WSEntry(server.table, c->fd, id, len);
}

void processWakeupCommand(client *c, char *id, int len)
{
        struct WSEntry *result;
	result = searchWSEntryById(server.table, id, len);
	if (result != NULL) {
		c->dfd = getFDofWSEntryById(server.table, id, len);
		c->dstring = strdup(result->wakestr);
		delWSEntryById(server.table, id, len);
	} else {
		c->dfd = c->fd;
		c->dstring = strdup("error");
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
