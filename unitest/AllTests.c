#include <stdio.h>

#include "CuTest.h"

CuSuite* WSTableSuite();
CuSuite* ProtocolSuite();

void RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, WSTableSuite());
	CuSuiteAddSuite(suite, ProtocolSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

int main(void)
{
	RunAllTests();
}
