// TersePrinter class provides alternative output mode
// which displays only the failed tests but in an enhanced form.
// It is a modified sample9_unittest.cc from gtest.

#ifndef TERSE_PRINTER_H
#define TERSE_PRINTER_H

// this MUST be included before windows.h because of a
// bug in the mingw limits header
#include "gtest/gtest.h"

#ifdef _WIN32
	#include <windows.h>
#else
	#include <stdarg.h>
#endif

enum ConsoleColor
{
	COLOR_DEFAULT,
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE,
	COLOR_YELLOW,
	COLOR_MAGENTA,
	COLOR_CYAN,
	COLOR_WHITE
};

using namespace std;
using namespace testing;

// Provides alternative output mode which displays only
// the failed tests but in an enhanced form.
class TersePrinter : public EmptyTestEventListener
{

	public:

		explicit TersePrinter(bool useTerseOutput_, bool /* use_color */)
			: useTerseOutput(useTerseOutput_)
		{};

		static void PrintTestTotals(int all_test_total_check, const char* file, int line);

	private:

		bool useTerseOutput;		// from initializer
//		bool use_color_;			// from initializer
		bool test_header_printed_;	// true if the test case header has been printed
		string test_case_name_;		// from OnTestStart
		string test_info_name_;		// from OnTestStart

	private:

		// Called before each iteration of tests starts.
		void OnTestIterationStart(const UnitTest& unit_test, int /*iteration*/);

		// Called before environment set-up for each iteration of tests starts.
		void OnEnvironmentsSetUpStart(const UnitTest& /*unit_test*/);

		// Called before the test case starts.
		void OnTestCaseStart(const TestCase& test_case);

		// Called before the test starts.
		void OnTestStart(const TestInfo& test_info);

		// Called after a failed assertion or a SUCCESS().
		virtual void OnTestPartResult(const TestPartResult& test_part_result);

		// Called after the test ends.
		void OnTestEnd(const TestInfo& test_info);

		// Called after the test case ends.
		void OnTestCaseEnd(const TestCase& test_case);

		// Called before environment tear-down for each iteration of tests starts.
		void OnEnvironmentsTearDownStart(const UnitTest& /*unit_test*/);

		// Called after each iteration of tests finishes.
		void OnTestIterationEnd(const UnitTest& unit_test, int /*iteration*/);

		// Internal helper functions.
		void PrintFailedTestSummary(const string& summary_) const;
		void PrintFailedTestsList(const UnitTest& unit_test) const;
		string ReplaceSummaryString(const string& summary) const;
		void PrintTestHeader(ConsoleColor color) const;
		string FormatTestCount(int count) const;
		char PeekNextChar(const string& line, int i) const;
};  // class TersePrinter

// Color print functions.
void ColoredPrintf(ConsoleColor color, const char* fmt, ...);
#ifdef _WIN32
	WORD GetColorAttribute(ConsoleColor color);
#else
	string GetAnsiColorCode(ConsoleColor color);
	bool ShouldUseColor(bool stdoutIsTty);
#endif

#endif	// closes TERSE_PRINTER_H
