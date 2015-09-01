#ifndef _WS_TABLE_HEADER_
#define _WS_TABLE_HEADER_

#include "server.h"

#define DEVICE_ID_LEN 20

#define MAX_ENTRY 200

struct WSEntry {
	char id[DEVICE_ID_LEN];
	int fd;
};

struct WSTable {
	list *wsEntry;
        int max_entry;
	int id_length;
};

struct WSEntry *createWSEntry();
struct WSTable *CreateWSTable();
list *getEntryList(struct WSTable *table);
void addWSEntry(struct WSTable *table, int fd, char *id);

#endif
