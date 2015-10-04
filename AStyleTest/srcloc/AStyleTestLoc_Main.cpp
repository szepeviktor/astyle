//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "TersePrinter.h"

//----------------------------------------------------------------------------
// global variables and function declarations
//----------------------------------------------------------------------------

void systemPause();

//----------------------------------------------------------------------------
// main functions
//----------------------------------------------------------------------------

int main(int argc, char** argv)
{
	// Parse command line BEFORE InitGoogleTest.
	bool useTersePrinter = true;	// ALWAYS true (for testing only)
	bool useTerseOutput = false;	// option for terse (true) or all (false)
	bool useColor = true;
	bool noClose = false;
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "--terse_output") == 0 )
			useTerseOutput = true;
		else if (strcmp(argv[i], "--no_close") == 0 )
			noClose = true;
		else if (strcmp(argv[i], "--gtest_color=no") == 0)
			useColor = false;
	}
	// Do this after parsing the command line but before changing printer.
	testing::InitGoogleTest(&argc, argv);
	// ALWAYS uses TersePrinter.
	if (useTersePrinter)
	{
		UnitTest& unit_test = *UnitTest::GetInstance();
		TestEventListeners& listeners = unit_test.listeners();
		delete listeners.Release(listeners.default_result_printer());
		listeners.Append(new TersePrinter(useTerseOutput, useColor));
	}
	// run the tests
	int retval = RUN_ALL_TESTS();
	// Verify that all tests were run. This can occur if a source file
	// is missing from the project. The UnitTest reflection API in
	// example 9 will not work here because of user modifications.
	// Change the following value to the number of tests (within 20).
	TersePrinter::PrintTestTotals(50, __FILE__, __LINE__);

#ifdef __WIN32
	printf("%c", '\n');
#endif
	if (noClose)			// command line option
		systemPause();

	return retval;
}

void systemPause()
{
#ifdef _WIN32
	system("pause");
#else
	cout << "Press ENTER to continue." << endl;
	if (system("read x") > 0)
		cout << "Bad return from 'system' call." << endl;
#endif
}
