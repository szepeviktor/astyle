// Main_Test.cpp
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include <wx/wx.h>
#include "TersePrinter.h"

#ifdef LEAK_DETECTOR
	#include "vld.h"
#endif

//----------------------------------------------------------------------------
// global variables
//----------------------------------------------------------------------------

void SystemPause();

//-------------------------------------------------------------------------
// wxWidgets wxIMPLEMENT_APP_NO_MAIN instead of wxIMPLEMENT_APP
//-------------------------------------------------------------------------

// Create a wxApp object to initialize wxWidgets.
// Do not want a main() or WinMain() function.
// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
// It is needed to create a wxFrame parent for Editor and wxStyledTextCtrl classes.
// The wxWidgets function wxEntryStart() must be called for tests that require a wxFrame object.
// See the AStyleFormat constructor or the wxWidgets sample program mfctest.cpp.
wxIMPLEMENT_APP_NO_MAIN(wxApp);

//----------------------------------------------------------------------------
// main function
//----------------------------------------------------------------------------

int main(int argc, char** argv)
{
	// parse command line BEFORE InitGoogleTest
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
		else if (strcmp(argv[i], "--gtest_color=no") == 0 )
			useColor = false;
	}

	// do this after parsing the command line but before changing printer
	testing::InitGoogleTest(&argc, argv);

	// change to TersePrinter
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
	if (useTersePrinter)
		TersePrinter::PrintTestTotals(260, __FILE__, __LINE__);
	else
		ColoredPrintf(COLOR_YELLOW, "\n* USING DEFAULT GTEST PRINTER *\n\n");
#ifdef __WIN32
	printf("%c", '\n');
#endif
	if (noClose)			// command line option
		SystemPause();

	return retval;
}

void SystemPause()
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
// Global functions
//----------------------------------------------------------------------------

int ShowMessageDialog(const wxString& message, long)
//  function from AStyleWx
{
	// gtest doesn't like wxMessageDialog with a nullptr parent.
	// Remove the message by using gmock for Config::ShowInvalidConfig.
#ifdef wxUSE_UNICODE
	std::wcout << message.c_str() << std::endl;
#else
	std::cout << message.c_str() << std::endl;
#endif
	return wxOK;
}
