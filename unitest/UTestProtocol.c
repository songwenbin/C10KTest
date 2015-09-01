#include "CuTest.h"
#include "protocol.h"
#include "networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void TestProtocol(CuTest *tc) 
{

	server.el = aeCreateEventLoop(20000);
	server.clients = listCreate();
	client *c = createClient(3);

	c->querybuf[0] = 1;
	c->querybuf[1] = 2;
	c->querybuf[2] = 'a';
	c->querybuf[3] = 'b';

	char *actual = getDeviceId(c);
	char *expected = strdup("ab");
	CuAssertStrEquals(tc, expected, actual);

}

CuSuite* ProtocolSuite()
{
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestProtocol);
	return suite;
}
