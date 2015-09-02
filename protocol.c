#include "protocol.h"
#include <string.h>
#include "wstable.h"

int parseProtocolHeader(client *c)
{
	if (c->querybuf[c->querybuf_idx++] == DEVICE_CONN) {
		return DEVICE_CONN;
	}

	return -1;
}

char * parseDeviceId(client *c, int *len)
{
	*len = c->querybuf[c->querybuf_idx++];
	char *id = malloc((*len) * sizeof(char));
	memcpy(id, &(c->querybuf[c->querybuf_idx]), *len);
	c->querybuf_idx = 0;

	return id;
}
