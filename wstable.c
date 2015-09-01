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
	table->id_length = DEVICE_ID_LEN;

	return table;
}

list *getEntryList(struct WSTable *table)
{
        return table->wsEntry;
}

void addWSEntry(struct WSTable *table, int fd, char *id)
{
	int i;
        struct WSEntry *entry = createWSEntry();
     	entry->fd = fd;
        for (i = 0; i < DEVICE_ID_LEN; i ++) {
                entry->id[i] = id[i]; 
        }
        listAddNodeTail(table->wsEntry, entry);
}

void delWSEntry(struct WSTable *table, )
{

}

void searchWSEntryByFd(struct WSTable *table, int fd)
{
	
}

void searchWSEntryById(struct WSTable *table, char* id)
{

}
