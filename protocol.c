#include "protocol.h"
#include <string.h>
#include "wstable.h"

int parseProtocolHeader(client *c)
{
	if (c->querybuf[0] == DEVICE_CONN) {
		return DEVICE_CONN;
	}

	return 0;
}

char * getDeviceId(client *c)
{
	char *id = malloc((int)c->querybuf[1]*sizeof(char) + 1);
	memcpy(id, &(c->querybuf[2]), (int)c->querybuf[1] + 1);
	id[2] = '\0';

	return id;
}
