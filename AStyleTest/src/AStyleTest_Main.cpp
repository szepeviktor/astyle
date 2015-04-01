//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleTest.h"
#include "TersePrinter.h"

//----------------------------------------------------------------------------
// global variables and function declarations
//----------------------------------------------------------------------------

#ifdef ASTYLE_DYLIB
	fpASMain  AStyleMain;	// procedure address for AStyleMain
	void*     AStyleLib;	// pointer to the shared library
#endif
void systemPause();
int errorHandler2Calls;

// function declarations
void loadLibrary();
void freeLibrary();

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
	loadLibrary();
	int retval = RUN_ALL_TESTS();
	freeLibrary();
	// Verify that all tests were run. This can occur if a source file
	// is missing from the project. The UnitTest reflection API in
	// example 9 will not work here because of user modifications.
	// Change the following value to the number of tests (within 20).
	TersePrinter::PrintTestTotals(2300, __FILE__, __LINE__);

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

//----------------------------------------------------------------------------
// AStyleMain callback functions
//----------------------------------------------------------------------------

// Error handler for the Artistic Style formatter.
// Pause so the error will be noticed.
// Linux calls "sh -c", not bash.
void  STDCALL errorHandler(int errorNumber, const char* errorMessage)
{
	cout << "AStyle error " << errorNumber << ".\n" << errorMessage << endl;
	systemPause();
}

// Error handler 2 just adds to an error count.
// It is used to test error conditions.
void  STDCALL errorHandler2(int, const char*)
{
	errorHandler2Calls++;
}

// Return errorHandler2Calls global variable.
int getErrorHandler2Calls()
{
	return errorHandler2Calls;
}

// Allocate memory for the Artistic Style formatter.
char* STDCALL memoryAlloc(unsigned long memoryNeeded)
{
	// error condition is checked after return from AStyleMain
	// UnitTest++ will catch an allocation error
	char* buffer = new(nothrow) char [memoryNeeded];
	return buffer;
}

//----------------------------------------------------------------------------
// Windows dynamic load functions.
// Define the preprocessor macro ASTYLE_DYLIB to activate.
// Purpose is for faster linking.
// Can only be used with Visual Studio for now.
//----------------------------------------------------------------------------

// WINDOWS load library function.
// Does nothing if using a linked shared library.
void loadLibrary()
{
#ifdef ASTYLE_DYLIB
#ifdef NDEBUG
	AStyleLib = LoadLibrary(".\\AStyle-2.06.dll");
#else
	AStyleLib = LoadLibrary(".\\AStyle-2.06d.dll");
#endif
	if (!AStyleLib)
	{
		cout << "Cannot load dll library for AStyle!" << endl;
		systemPause();
		exit(EXIT_FAILURE);
	}
	// get AStyleMain function
	AStyleMain = reinterpret_cast<fpASMain>(
	                 GetProcAddress(reinterpret_cast<HMODULE>(AStyleLib), "AStyleMain"));
	if (!AStyleMain)
	{
		cout << "Cannot get dll address for AStyleMain!" << endl;
		systemPause();
		exit(EXIT_FAILURE);
	}
#endif
}

// WINDOWS free library function.
// Does nothing if using a linked shared library.
void freeLibrary()
{
#ifdef ASTYLE_DYLIB
	FreeLibrary(reinterpret_cast<HMODULE>(AStyleLib));
#endif
}
