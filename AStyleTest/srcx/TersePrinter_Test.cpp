// TersePrinter test program.
// The output must be inspected visually.

#include "gtest/gtest.h"
#include "TersePrinter.h"

void errorExit(const char* msg);
void errorNoExit(const char* msg);


TEST(TestCase1, SUCCEED)
{
	SUCCEED() << "SUCCEED() has been invoked from here";
}

TEST(TestCase1, Equal_Succeeds)
{
	EXPECT_EQ(1, 1);
}

TEST(TestCase2, Equal_Fails)
{
	EXPECT_EQ(1, 2) << "EXPECT_EQ failure.";
}

TEST(TestCase2, NotEqual_Fails)
{
	EXPECT_NE(1, 1) << "EXPECT_NE failure.";
}

TEST(TestCase2, StringPrintSpecifierEQ_Fails)
// string containing a print specifier
{
	string expected = "%s %n";
	string actual   = "%n %s";
	EXPECT_EQ(expected, actual) << "EXPECT_EQ string failure.";
}

TEST(TestCase2, StringPrintSpecifierNE_Fails)
// string containing a print specifier
{
	string expected = "%s %n";
	string actual   = "%s %n";
	EXPECT_NE(expected, actual) << "EXPECT_NE string failure.";
}

TEST(TestCase2, CStringEQ_Fails)
{
	char expected_str[] =
	    "\nvoid foo() {\n"
	    "    isBar = true;\n"
	    "    bar();\n"
	    "}";
	char actual_str[] =
	    "\nvoid foo() {\n"
	    "    isBar = true;\n"
	    "        bar();\n"
	    "}";
	EXPECT_STREQ(expected_str, actual_str) << "EXPECT_STREQ failure.";
}

TEST(TestCase2, CStringNE_Fails)
{
	char expected_str[] =
	    "\nvoid foo() {\n"
	    "    isBar = true;\n"
	    "    bar();\n"
	    "}";
	char actual_str[] =
	    "\nvoid foo() {\n"
	    "    isBar = true;\n"
	    "    bar();\n"
	    "}";
	EXPECT_STRNE(expected_str, actual_str) << "EXPECT_STRNE failure.";
}

TEST(TestCase2, DeathTest_WrongMessage)
{
	// test ok but wrong message
	EXPECT_EXIT(errorExit("Actual message."),
	            ExitedWithCode(EXIT_FAILURE),
	            "Expected message.") << "EXPECT_EXIT with wrong message.";
}

TEST(TestCase2, DeathTest_Fails)
{
	// test fails with wrong return code
	EXPECT_EXIT(errorExit("Expected message."),
	            ExitedWithCode(EXIT_SUCCESS),
	            "Expected message.") << "EXPECT_EXIT with wrong exit status.";;
}

TEST(TestCase2, DeathTest_FailsToDie)
{
	// test fails with wrong return code
	EXPECT_EXIT(errorNoExit("Expected message."),
	            ExitedWithCode(EXIT_SUCCESS),
	            "Expected message.") << "EXPECT_EXIT fails to die.";;
}

TEST(TestCase2, TrueFalse_Fails)
{
	int process_return = 1;
	int CONTINUE = 0;
	EXPECT_TRUE(process_return == CONTINUE) << "EXPECT_TRUE failure.";
}

TEST(DISABLED_TestCase2, Disabled)
{
}

TEST(TestCase3, MultipleFailures)
{
	int process_return = 1;
	int CONTINUE = 0;
	EXPECT_TRUE(process_return == CONTINUE) << "EXPECT_TRUE failure 1.";
	EXPECT_TRUE(process_return == CONTINUE) << "EXPECT_TRUE failure 2.";
	EXPECT_TRUE(process_return == CONTINUE) << "EXPECT_TRUE failure 3.";
}

int main(int argc, char** argv)
{
	// Parse command line BEFORE testing::InitGoogleTest
	bool use_terse_printer = true;	// true for TersePrinter, false for gtest default
	bool use_terse_output = false;	// print terse output if --terse_output option is set
	bool use_color = true;
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "--terse_output") == 0 )
			use_terse_output = true;
		else if (strcmp(argv[i], "--gtest_color=no") == 0 )
			use_color = false;
	}
	// Do this after parsing the command line but before changing printer.
	testing::InitGoogleTest(&argc, argv);
	// If we are given the --terse_printer command line flag, suppresses the
	// standard output and attaches own result printer.
	if (use_terse_printer)
	{
		UnitTest& unit_test = *UnitTest::GetInstance();
		testing::TestEventListeners& listeners = unit_test.listeners();
		// Removes the default console output listener from the list so it will
		// not receive events from Google Test and won't print any output. Since
		// this operation transfers ownership of the listener to the caller we
		// have to delete it as well.
		delete listeners.Release(listeners.default_result_printer());
		// Adds the custom output listener to the list. It will now receive
		// events from Google Test and print the alternative output. We don't
		// have to worry about deleting it since Google Test assumes ownership
		// over it after adding it to the list.
		listeners.Append(new TersePrinter(use_terse_output, use_color));
	}
	int retval = RUN_ALL_TESTS();
	if (!use_terse_printer)
		ColoredPrintf(COLOR_YELLOW, "\n* USING DEFAULT GTEST PRINTER *\n\n");
	else
	{
		if (use_terse_output)
			ColoredPrintf(COLOR_YELLOW, "\n* USING TersePrinter AND --terse_output *\n\n");
		else
			ColoredPrintf(COLOR_YELLOW, "\n* NOT USING --terse_output *\n\n");
	}
	return retval;
}

// function for death test
// error message must go to cerr not cout
void errorExit(const char* msg)
{
	cerr << msg << endl;
	exit(EXIT_FAILURE);
}

// function for death test failed
// error message must go to cerr not cout
void errorNoExit(const char* msg)
{
	cerr << msg << endl;
}
