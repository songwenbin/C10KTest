#ifndef _PROTOCOL_HEADER_
#define _PROTOCOL_HEADER_

#include "server.h"
#define REGISTER_DEVICE_HEAD 0x01
#define WAKEUP_DEVICE_HEAD   0x02

int parseProtocolHeader(client *c);
char *parseDeviceId(client *c, int *len);

// phone wake protocol
/*
 * +----------------------+-----------------------+-----------
 * |protocol header(1byte)|device id length(1byte)|device id
 * +----------------------+-----------------------+-----------
 *
 * protocol header == 0x01: register device
 * protocol header == 0x02: wakeup  device
 */

#endif
