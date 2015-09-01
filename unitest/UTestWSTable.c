#include "CuTest.h"
#include "protocol.h"
#include "networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "wstable.h" 

void TestWSTableInit(CuTest *tc) 
{

	server.table = CreateWSTable();
	CuAssertPtrNotNull(tc, server.table);

	/*  
	int freecount = 0;
	list *l = getFreeList(server.table);
	listNode *ln;
	listIter li;
	listRewind(l, &li);
	while ((ln = listNext(&li)) != NULL) {
		freecount ++;
	}
	CuAssertIntEquals(tc, 200, freecount);

	int usedcount = 0;
	l = getUsedList(server.table);
	listRewind(l, &li);
	while ((ln = listNext(&li)) != NULL) {
		usedcount ++;
	}
	CuAssertIntEquals(tc, 0, usedcount);
	*/
}

void TestWSTableAdd(CuTest *tc)
{
	server.table = CreateWSTable();
	addWSEntry(server.table, 3, "abcdefghi");
}

CuSuite* WSTableSuite()
{
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestWSTableInit);
	return suite;
}
