#include <stdio.h>

#include "CuTest.h"

CuSuite* WSTableSuite();
CuSuite* ProtocolSuite();
CuSuite* WakeupSuite();

void RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, WSTableSuite());
	CuSuiteAddSuite(suite, ProtocolSuite());
	CuSuiteAddSuite(suite, WakeupSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

int main(void)
{
	RunAllTests();
}
