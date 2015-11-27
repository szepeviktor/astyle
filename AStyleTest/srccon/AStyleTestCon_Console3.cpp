// AStyleTestCon_Console3.cpp
// Copyright (c) 2015 by Jim Pattee <jimp03@email.com>.
// Licensed under the MIT license.
// License.txt describes the conditions under which this software may be distributed.


// AStyleTestCon tests the ASConsole class only. This class is used only in
// the console build. It also tests the parseOption function for options used
// by only by the console build (e.g. recursive, preserve-date, verbose). It
// does not explicitely test the ASStreamIterator class or any other part
// of the program.

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

//#include <algorithm>
#include "AStyleTestCon.h"
#ifdef _WIN32
	#include <windows.h>
#else
	#include <fcntl.h>
#endif

//----------------------------------------------------------------------------
// global variables
//----------------------------------------------------------------------------

// defined in astyle_main.cpp
// used by MingwFileGlobbing test
extern int _CRT_glob;

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {

//----------------------------------------------------------------------------
// AStyle ProcessOptions3F Class
//----------------------------------------------------------------------------

class ProcessOptions3F : public Test
// The ProcessOptions3F class captures the stdout output stream and redirects it to
// a file. The file is used to verify the Artistic Style console build print format.
// The functions were "borrowed" from the CapturedStream class in gtest-port.cc of
// Google Test (gtest).
{
public:
	// variables for redirecting stdout
	int fd_;					// stream to capture
	int uncaptured_fd_;			// stdout stream
	string filename_;			// temporary file holding the stdout output

public:
	ProcessOptions3F();

	~ProcessOptions3F();

	// redirect the stdout stream to a temporary file
	void redirectStream();

	// restore the stdout stream and return the captured text
	string restoreStream();

private:

	// called by restoreStream() to read the entire content of a file as a string
	string readEntireFile(FILE* file);
};

ProcessOptions3F::ProcessOptions3F()
// c'tor
{
#if defined(_MSC_VER) || defined(__BORLANDC__)
	// MSVC and C++Builder do not provide a definition of STDERR_FILENO.
	const int stdOutFileno = 1;
#else
	const int stdOutFileno = STDOUT_FILENO;
#endif  // _MSC_VER
	// initialize variables
	fd_ = stdOutFileno;
	uncaptured_fd_ = dup(stdOutFileno);
	// use C locale for consistent formatting
	setlocale(LC_ALL, "C");
}

ProcessOptions3F::~ProcessOptions3F()
// d'tor
{
	if (uncaptured_fd_ != -1)
	{
		// the stream must be restored first
		restoreStream();
		systemPause("\nCaptured fd_ was not restored.");
	}
	remove(filename_.c_str());
}

string ProcessOptions3F::readEntireFile(FILE* file)
// called by restoreStream() to read the entire content of a file as a string
{
	fseek(file, 0, SEEK_END);
	const size_t file_size = ftell(file);
	char* const buffer = new char[file_size];
	size_t bytes_last_read = 0;  // # of bytes read in the last fread()
	size_t bytes_read = 0;       // # of bytes read so far
	fseek(file, 0, SEEK_SET);
	// Keeps reading the file until we cannot read further or the
	// pre-determined file size is reached.
	do
	{
		bytes_last_read = fread(buffer + bytes_read, 1, file_size - bytes_read, file);
		bytes_read += bytes_last_read;
	}
	while (bytes_last_read > 0 && bytes_read < file_size);
	const string textOut(buffer, bytes_read);
	delete[] buffer;
	return textOut;
}

void ProcessOptions3F::redirectStream()
// redirect the stdout stream to a temporary file
{
#ifdef _WIN32
	char temp_file_path[MAX_PATH + 1] = { '\0' };
	const DWORD success = GetTempPath(sizeof(temp_file_path), temp_file_path);
	GTEST_CHECK_(success > 0) << "Unable to get temporary directory path";
	strcat(temp_file_path, "AStyleTestCon.tmp");
	const int captured_fd = creat(temp_file_path, _S_IREAD | _S_IWRITE);
	GTEST_CHECK_(captured_fd != -1) << "Unable to open temporary file " << temp_file_path;
	filename_ = temp_file_path;
#else
	// There's no guarantee that a test has write access to the
	// current directory, so we create the temporary file in the /tmp
	// directory instead.
	char temp_file_path[] = "/tmp/AStyleTestCon.tmp";
	const int captured_fd = creat(temp_file_path, S_IREAD | S_IWRITE);
	GTEST_CHECK_(captured_fd != -1) << "Unable to open temporary file " << temp_file_path;
	filename_ = temp_file_path;
#endif
	fflush(NULL);
	dup2(captured_fd, fd_);
	close(captured_fd);
}

string ProcessOptions3F::restoreStream()
// restore the stdout stream and return the captured text
{
	if (uncaptured_fd_ != -1)
	{
		// restore the original stream
		fflush(NULL);
		dup2(uncaptured_fd_, fd_);
		close(uncaptured_fd_);
		uncaptured_fd_ = -1;
	}
	FILE* const file = fopen(filename_.c_str(), "r");
	const string content = readEntireFile(file);
	fclose(file);
	return content;
}

//----------------------------------------------------------------------------
// AStyle help and version options
// The print on these needs to be redirected to a file.
//----------------------------------------------------------------------------

TEST_F(ProcessOptions3F, HelpOption)
// test processOptions for the long help option display
{
	ASFormatter formatter;
	createConsoleGlobalObject(formatter);
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--help");
	redirectStream();
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions for help option display
	// should have a good return
	EXPECT_EXIT(g_console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_SUCCESS),
	            "");
	string textOut = restoreStream();
	// check a sample of the text
	size_t heading1 = textOut.find("Bracket Style Options:");
	size_t heading2 = textOut.find("Other Options:");
	size_t heading3 = textOut.find("Command Line Only:");
	EXPECT_TRUE(heading1 != string::npos);
	EXPECT_TRUE(heading2 != string::npos);
	EXPECT_TRUE(heading3 != string::npos);
#else
	restoreStream();
#endif
	deleteConsoleGlobalObject();
}

TEST_F(ProcessOptions3F, HelpOption_Short1)
// test processOptions for the short help option display
{
	ASFormatter formatter;
	createConsoleGlobalObject(formatter);
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("-h");
	redirectStream();
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions for help option display
	// should have a good return
	EXPECT_EXIT(g_console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_SUCCESS),
	            "");
	string textOut = restoreStream();
	// check a sample of the text
	size_t heading1 = textOut.find("Bracket Style Options:");
	size_t heading2 = textOut.find("Other Options:");
	size_t heading3 = textOut.find("Command Line Only:");
	EXPECT_TRUE(heading1 != string::npos);
	EXPECT_TRUE(heading2 != string::npos);
	EXPECT_TRUE(heading3 != string::npos);
#else
	restoreStream();
#endif
	deleteConsoleGlobalObject();
}

TEST_F(ProcessOptions3F, HelpOption_Short2)
// test processOptions for short help option display
{
	ASFormatter formatter;
	createConsoleGlobalObject(formatter);
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("-?");
	redirectStream();
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions for help option display
	// should have a good return
	EXPECT_EXIT(g_console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_SUCCESS),
	            "");
	string textOut = restoreStream();
	// check a sample of the text
	size_t heading1 = textOut.find("Bracket Style Options:");
	size_t heading2 = textOut.find("Other Options:");
	size_t heading3 = textOut.find("Command Line Only:");
	EXPECT_TRUE(heading1 != string::npos);
	EXPECT_TRUE(heading2 != string::npos);
	EXPECT_TRUE(heading3 != string::npos);
#else
	restoreStream();
#endif
	deleteConsoleGlobalObject();
}

TEST_F(ProcessOptions3F, VersionOption)
// test processOptions for version option display
{
	ASFormatter formatter;
	createConsoleGlobalObject(formatter);
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--version");
	redirectStream();
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions for version option display
	// should have a good return
	EXPECT_EXIT(g_console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_SUCCESS),
	            "");
	string textOut = restoreStream();
	// check a sample of the text
	size_t output = textOut.find("Artistic Style Version ");
	EXPECT_TRUE(output != string::npos);
#else
	restoreStream();
#endif
	deleteConsoleGlobalObject();
}

TEST_F(ProcessOptions3F, VersionOption_Short)
// test processOptions for version short option display
{
	ASFormatter formatter;
	createConsoleGlobalObject(formatter);
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("-V");
	redirectStream();
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions for version option display
	// should have a good return
	EXPECT_EXIT(g_console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_SUCCESS),
	            "");
	string textOut = restoreStream();
	// check a sample of the text
	size_t output = textOut.find("Artistic Style Version ");
	EXPECT_TRUE(output != string::npos);
#else
	restoreStream();
#endif
	deleteConsoleGlobalObject();
}

//----------------------------------------------------------------------------
// AStyle html options
//----------------------------------------------------------------------------

TEST_F(ProcessOptions3F, HtmlOption)
// Test processOptions for html option.
{
	ASFormatter formatter;
	createConsoleGlobalObject(formatter);
	g_console->setBypassBrowserOpen(true);	// don't open the file
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--html");
	redirectStream();
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions for html option display
	// should have a good return
	EXPECT_EXIT(g_console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_SUCCESS),
	            "");
	string textOut = restoreStream();
	// check a sample of the text for valid exit
	size_t output = textOut.find("Opening HTML documentation");
	if (output == string::npos)
		output = textOut.find("Cannot open HTML file");
	EXPECT_FALSE(output == string::npos) << "Unexpected termination message:\n" << textOut;
#else
	restoreStream();
#endif
	deleteConsoleGlobalObject();
}

TEST_F(ProcessOptions3F, HtmlOption_Short)
// Test processOptions for html option.
{
	ASFormatter formatter;
	createConsoleGlobalObject(formatter);
	g_console->setBypassBrowserOpen(true);	// don't open the file
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("-!");
	redirectStream();
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions for html option display
	// should have a good return
	EXPECT_EXIT(g_console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_SUCCESS),
	            "");
	string textOut = restoreStream();
	// check a sample of the text for valid exit
	size_t output = textOut.find("Opening HTML documentation");
	if (output == string::npos)
		output = textOut.find("Cannot open HTML file");
	EXPECT_FALSE(output == string::npos) << "Unexpected termination message:\n" << textOut;
#else
	restoreStream();
#endif
	deleteConsoleGlobalObject();
}

TEST_F(ProcessOptions3F, HtmlOption_ValidFileName)
// Test processOptions for html option.
// Should be able to open a valid file.
{
	ASFormatter formatter;
	createConsoleGlobalObject(formatter);
	g_console->setBypassBrowserOpen(true);	// don't open the file
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--html=astyle.html");
	redirectStream();
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions for html option display
	// should have a good return
	EXPECT_EXIT(g_console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_SUCCESS),
	            "");
	string textOut = restoreStream();
	// check a sample of the text
	size_t output = textOut.find("Opening HTML documentation ");
	// allow "Cannot open" message if the path is correct
	if (output == string::npos
	        && textOut.find("Cannot open HTML file") != string::npos)
	{
#ifdef _WIN32
		output = textOut.find("\\AStyle\\doc\\astyle.html");
#else
		output = textOut.find("/usr/share/doc/astyle/html/");
#endif	// _WIN32
	}
	EXPECT_FALSE(output == string::npos) << "Unexpected termination message:\n" << textOut;
#else
	restoreStream();
#endif	// GTEST_HAS_DEATH_TEST
	deleteConsoleGlobalObject();
}

TEST_F(ProcessOptions3F, HtmlOption_InvalidFileName)
// Test processOptions for html= option with invalid file name.
// Should get an error message for an invalid file.
{
	ASFormatter formatter;
	createConsoleGlobalObject(formatter);
	g_console->setBypassBrowserOpen(true);	// don't open the file
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--html=invalid-name.html");
	redirectStream();
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions for invalid file name
	EXPECT_EXIT(g_console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_SUCCESS),
	            "");
	string textOut = restoreStream();
	// check a sample of the text
	size_t output = textOut.find("Cannot open HTML file");
	EXPECT_FALSE(output == string::npos) << "Unexpected termination message:\n" << textOut;
#else
	restoreStream();
#endif
	deleteConsoleGlobalObject();
}

//----------------------------------------------------------------------------
// AStyle other tests
//----------------------------------------------------------------------------

TEST(Other, MingwFileGlobbing)
// test that MinGW file globbing is turned OFF
{
	// _CRT_glob is a global variable defined in astyle_main.cpp
	// will get a link error if it is not defined in the GLOBAL namespace
	EXPECT_TRUE(_CRT_glob == 0);
}

TEST(Other, GlobalPreprocessorExternBracket)
// Test that g_preprocessorCppExternCBracket is reset for each file.
{
	// The ASBeautifier global variable g_preprocessorCppExternCBracket
	// must be cleared in the "init" method instead of the constructor.
	// If not cleared, the "int a;" will not be indented
	ASFormatter formatter;
	createConsoleGlobalObject(formatter);
	vector<string> astyleOptionsVector;
	g_console->setIsQuiet(true);		// change this to see results
	// test files
	char textIn1[] =
	    "\n#ifdef __cplusplus\n"
	    "#endif\n";
	char textIn2[] =
	    "\nextern \"C\" {\n"
	    "    int a;\n"
	    "}\n";
	// create test files
	cleanTestDirectory(getTestDirectory());
	string filename1 = getTestDirectory() + "/externBracket1.cpp";
	g_console->standardizePath(filename1);
	createTestFile(filename1, textIn1);
	string filename2 = getTestDirectory() + "/externBracket2.cpp";
	g_console->standardizePath(filename2);
	createTestFile(filename2, textIn2);
	// call astyle processFiles()
	astyleOptionsVector.push_back(filename1);
	astyleOptionsVector.push_back(filename2);
	g_console->processOptions(astyleOptionsVector);
	g_console->processFiles();
	// Check for 2nd file not formatted.
	// If the ASBeautifier global variable is not reset,
	// "int a;" line will not be indented.
	EXPECT_TRUE(g_console->getFilesAreIdentical())
	        << "Global variable has not been reset";
	deleteConsoleGlobalObject();
}

TEST(Other, ErrorExit)
// test the error exit without message
{
	ASFormatter formatter;
	createConsoleGlobalObject(formatter);
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// death test without error message
	EXPECT_EXIT(g_console->error(),
	            ExitedWithCode(EXIT_FAILURE),
	            "\nArtistic Style ");	// "Artistic Style has terminated!"
#endif
	deleteConsoleGlobalObject();
}

TEST(Other, ErrorExitWihMessage)
// test the error exit with message
{
	ASFormatter formatter;
	createConsoleGlobalObject(formatter);
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// death test with error message
	EXPECT_EXIT(g_console->error("why", "what"),
	            ExitedWithCode(EXIT_FAILURE),
	            "why what\n\nArtistic Style ");	// "Artistic Style has terminated!"
#endif
	deleteConsoleGlobalObject();
}

//----------------------------------------------------------------------------

}  // namespace

