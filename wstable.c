#include "wstable.h"

struct WSEntry *createWSEntry()
{
	return (struct WSEntry *)malloc(sizeof(struct WSEntry));
}

struct WSTable *CreateWSTable()
{
	struct WSTable *table = (struct WSTable *)malloc(sizeof(struct WSTable));
	table->wsEntry = listCreate();
	table->max_entry = MAX_ENTRY;

	return table;
}

list *getEntryList(struct WSTable *table)
{
        return table->wsEntry;
}

void createFdofWSEntry(struct WSTable *table, int fd)
{
        struct WSEntry *entry = createWSEntry();
     	entry->fd = fd;
        listAddNodeTail(table->wsEntry, entry);
}

void addId2WSEntry(struct WSTable *table, int fd, char *id, int idLen)
{
	struct WSEntry *entry;
        listNode *ln;
	listIter li;
	listRewind(getEntryList(table), &li);
	while ((ln = listNext(&li)) != NULL) {
		entry = listNodeValue(ln);	
		if (entry->fd == fd) {
			entry->idLen = idLen;
			memcpy(entry->id, id, idLen);
		}
	}
}

int getFDofWSEntryById(struct WSTable *table, char* id, int size)
{
	struct WSEntry *entry;

        listNode *ln;
	listIter li;
	listRewind(getEntryList(table), &li);
	while ((ln = listNext(&li)) != NULL) {
		entry = listNodeValue(ln);
		if (memcmp(entry->id, id, size) == 0) {
			return entry->fd;
		}
	}

	return -1;
}
