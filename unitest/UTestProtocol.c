#include "CuTest.h"
#include "protocol.h"
#include "networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

client *createClientTest(int fd)
{
        client *cli = malloc(sizeof(cli));
	if (fd != -1) {
                anetNonBlock(NULL, fd);
		anetEnableTcpNoDelay(NULL, fd);
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

void TestProtocol(CuTest *tc) 
{

	server.el = aeCreateEventLoop(10);
	server.clients = listCreate();
	server.table = CreateWSTable();
	client *c = createClientTest(5);

	c->querybuf[0] = REGISTER_DEVICE_HEAD;
	c->querybuf[1] = 2;
	c->querybuf[2] = 'a';
	c->querybuf[3] = 'b';

	int i = parseProtocolHeader(c);
	CuAssertIntEquals(tc, REGISTER_DEVICE_HEAD, i);
	char *actual = parseDeviceId(c, &i);
	CuAssertIntEquals(tc, 2, i);
	char *expected = strdup("ab");
	CuAssertStrEquals(tc, expected, actual);

}

CuSuite* ProtocolSuite()
{
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestProtocol);
	return suite;
}
