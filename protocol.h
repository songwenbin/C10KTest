#ifndef _PROTOCOL_HEADER_
#define _PROTOCOL_HEADER_

#include "server.h"
#define DEVICE_CONN 0x01

int parseProtocolHeader(client *c);
char *parseDeviceId(client *c, int *len);

#endif
