#ifndef _WS_TABLE_HEADER_
#define _WS_TABLE_HEADER_

#include "server.h"

#define DEVICE_ID_LEN 20

#define MAX_ENTRY 200

struct WSEntry {
	char id[DEVICE_ID_LEN];
	int idLen;
	int fd;
	int timeout;
};

struct WSTable {
	list *wsEntry;
        int max_entry;
};

struct WSEntry *createWSEntry();
struct WSTable *CreateWSTable();
list *getEntryList(struct WSTable *table);
void createFdofWSEntry(struct WSTable *table, int fd);
void addId2WSEntry(struct WSTable *table, int fd, char *id, int idLen);
int getFDofWSEntryById(struct WSTable *table, char* id, int size);

#endif
