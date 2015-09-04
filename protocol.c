#include "protocol.h"
#include <string.h>
#include "wstable.h"

int parseProtocolHeader(client *c)
{
	char head = c->querybuf[c->querybuf_idx++];
	if (head == REGISTER_DEVICE_HEAD) {
		goto register_device;
	} else if(head == WAKEUP_DEVICE_HEAD) {
		goto wakeup_device;
	} else {
		goto error_device;
	}

register_device:
	return REGISTER_DEVICE_HEAD;
wakeup_device:
	return WAKEUP_DEVICE_HEAD;
error_device:
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
