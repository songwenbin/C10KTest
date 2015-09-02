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
}

void TestWSTableAdd(CuTest *tc)
{
	server.table = CreateWSTable();
	createFdofWSEntry(server.table, 4);
	createFdofWSEntry(server.table, 3);

	int usedcount = 0;
	listNode *ln;
	listIter li;
	list *l = getEntryList(server.table);
	listRewind(l, &li);
	while ((ln = listNext(&li)) != NULL) {
		usedcount ++;
	}
	CuAssertIntEquals(tc, 2, usedcount);
}

void TestWSTableSearch(CuTest *tc)
{
	int expectedFd = 3;
	int actualFd = 0;

	server.table = CreateWSTable();
	createFdofWSEntry(server.table, 3);
	addId2WSEntry(server.table, 3, "abcdefghi", 9);
	actualFd = getFDofWSEntryById(server.table, "abcdefghi", 9);

	CuAssertIntEquals(tc, expectedFd, actualFd);
}

CuSuite* WSTableSuite()
{
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestWSTableInit);
	SUITE_ADD_TEST(suite, TestWSTableSearch);
	SUITE_ADD_TEST(suite, TestWSTableAdd);
	return suite;
}
