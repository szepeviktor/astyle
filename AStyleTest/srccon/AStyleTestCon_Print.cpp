// AStyleTestCon_Print.cpp
// Copyright (c) 2017 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

// AStyleTestCon tests the ASConsole class only. This class is used only in
// the console build. It also tests the parseOption function for options used
// by only by the console build (e.g. recursive, preserve-date, verbose). It
// does not explicitely test the ASStreamIterator class or any other part
// of the program.

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include <algorithm>
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
namespace astyle {
extern const char* g_version;
}

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {
//
//----------------------------------------------------------------------------
// AStyle PrintF Class
//----------------------------------------------------------------------------

class PrintF : public Test
// The PrintF class captures the stdout output stream and redirects it to a file.
// The file is used to verify the Artistic Style console build print format.
// The functions were "borrowed" from the CapturedStream class in gtest-port.cc
// of Google Test (gtest).
{
public:
	ASFormatter formatter;		// required formatter object
	ASConsole* console;         // console object
	vector<string> fileNames;	// files created for test
	size_t filesExcluded;		// number of files excluded from formatting

	// variables for redirecting stdout
	int fd_;					// stream to capture
	int uncaptured_fd_;			// stdout stream
	string filename_;			// temporary file holding the stdout output

public:
	PrintF();

	~PrintF();

	// make adjustments to expected text
	void adjustText(string& text);

	// make adjustments to textOut
	void adjustTextOut(string& textOut);

	// build a vector of files to exclude
	void buildExcludeVector();

	// get today's date in MDY format
	string getCurrentDate();

	// redirect the stdout stream to a temporary file
	void redirectStream();

	// restore the stdout stream and return the captured text
	string restoreStream();

private:
	// called by the constructor to build the test files
	void createTestFiles();

	// called by restoreStream() to read the entire content of a file as a string
	string readEntireFile(FILE* file);
};

PrintF::PrintF()
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
	filesExcluded = 0;
	// create test objects
	console = new ASConsole(formatter);
	createTestFiles();
	// use C locale for consistent formatting
	setlocale(LC_ALL, "C");
}

PrintF::~PrintF()
// d'tor
{
	if (uncaptured_fd_ != -1)
	{
		// the stream must be restored first
		restoreStream();
		systemPause("\nCaptured fd_ was not restored.");
	}
	removeTestFile(filename_);
	delete console;
}

void PrintF::adjustText(string& text)
// make adjustments to expected text
{
	// replace first line with version number and date
	if (text.compare(0, 14, "Artistic Style") == 0)
	{
		string tagVersion = "<version>";
		string tagDate = "<date>";
		string replaceVersion = string(g_version);
		size_t verStart = text.find(tagVersion);
		size_t verEnd = verStart + replaceVersion.length();
		if (verStart != string::npos)
			text.replace(verStart, tagVersion.length(), replaceVersion);
		if (replaceVersion.length() < tagVersion.length())
			text.insert(verEnd, tagVersion.length() - replaceVersion.length(), ' ');
		else if (replaceVersion.length() > tagVersion.length())
			text.erase(verEnd, replaceVersion.length() - tagVersion.length());
		size_t dateStart = text.find(tagDate);
		if (dateStart != string::npos)
			text.replace(dateStart, tagDate.length(), getCurrentDate());
	}
	// insert linefeed as first character for readability
	text.insert(0, "\n");
	// replace <test_directory> with the actual directory
	for (size_t i = 0; i < text.length(); i++)
	{
		i = text.find("<test_directory>", i);
		if (i == string::npos)
			break;
		text.replace(i, 16, getTestDirectory());
	}
	// replace backslashes in file paths
	for (size_t i = 0; i < text.length(); i++)
	{
		i = text.find('\\', i);
		if (i == string::npos)
			break;
		text[i] = '/';
	}
}

void PrintF::adjustTextOut(string& textOut)
// make adjustments to textOut
{
	// insert linefeed as first character for readability
	textOut.insert(0, "\n");
	// replace backslashes in file paths
	for (size_t i = 0; i < textOut.length(); i++)
	{
		i = textOut.find('\\', i);
		if (i == string::npos)
			break;
		textOut[i] = '/';
	}
	// delete any decimals in the time
	size_t decimal = textOut.rfind('.');
	if (decimal != string::npos
	        && textOut.length() > 30
	        && decimal > textOut.length() - 30)
	{
		// delete to the next space
		size_t space = textOut.find(' ', decimal);
		if (space != string::npos)
			textOut.erase(decimal, space - decimal);
	}
#ifdef __BORLANDC__
	// delete any bad data at the start of the text (problem with Embarcadero)
	// this should be fixed in a future compiler release
	// when the white "getinfo1.c" lines are not displayed remove the following
	if (textOut.compare(1, 10, "getinfo1.c") == 0)
	{
		size_t textStart = textOut.find("Artistic Style");
		textOut.erase(1, textStart - 1);
	}
#endif
}

void PrintF::buildExcludeVector()
// build a vector of files to exclude
{
	char textExcluded[] = "\nvoid foo() { bar(); }\n";
	// add files to fileNames vector
	fileNames.push_back(getTestDirectory() + "/fileExcluded.cpp");
	console->standardizePath(fileNames.back());
	createTestFile(fileNames.back(), textExcluded);
	// build exclude vector
	console->updateExcludeVector("fileExcluded.cpp");
	filesExcluded += 1;
}

void PrintF::createTestFiles()
// called by the constructor to build the test files
{
	char textFormatted[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "bar();\n"
	    "}\n";
	char textUnchanged[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	cleanTestDirectory(getTestDirectory());
	fileNames.push_back(getTestDirectory() + "/fileFormatted.cpp");
	console->standardizePath(fileNames.back());
	createTestFile(fileNames.back(), textFormatted);
	fileNames.push_back(getTestDirectory() + "/fileUnchanged.cpp");
	console->standardizePath(fileNames.back());
	createTestFile(fileNames.back(), textUnchanged);
}

string PrintF::getCurrentDate()
{
	struct tm* ptr;
	time_t lt;
	char str[20];
	lt = time(nullptr);
	ptr = localtime(&lt);
	strftime(str, 20, "%x", ptr);
	return string(str);
}

string PrintF::readEntireFile(FILE* file)
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

void PrintF::redirectStream()
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
	fflush(nullptr);
	dup2(captured_fd, fd_);
	close(captured_fd);
}

string PrintF::restoreStream()
// restore the stdout stream and return the captured text
{
	if (uncaptured_fd_ != -1)
	{
		// restore the original stream
		fflush(nullptr);
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
// AStyle print tests
//----------------------------------------------------------------------------

TEST_F(PrintF, DefaultWildcard)
// test print wildcard with no options
{
	// expected text
	string text =
	    "------------------------------------------------------------\n"
	    "Directory  <test_directory>/*.cpp\n"
	    "------------------------------------------------------------\n"
	    "Formatted  fileFormatted.cpp\n"
	    "Unchanged  fileUnchanged.cpp\n";
	adjustText(text);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back("--ascii");
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// redirect stdout and get the report
	redirectStream();
	console->processFiles();
	string textOut = restoreStream();
	adjustTextOut(textOut);
	// check entries in the fileNameVector
	vector<string> fileName = console->getFileName();
	ASSERT_EQ(fileNames.size(), fileName.size()) << "Print format was not checked.";
	// check the report content
	EXPECT_EQ(text, textOut);
}

TEST_F(PrintF, DefaultWildcard_Exclude)
// test print wildcard with an exclude
{
	// expected text
	string text =
	    "------------------------------------------------------------\n"
	    "Directory  <test_directory>/*.cpp\n"
	    "Exclude  fileExcluded.cpp\n"
	    "------------------------------------------------------------\n"
	    "Formatted  fileFormatted.cpp\n"
	    "Unchanged  fileUnchanged.cpp\n";
	adjustText(text);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back("--ascii");
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// add exclude files
	buildExcludeVector();
	// redirect stdout and get the report
	redirectStream();
	console->processFiles();
	string textOut = restoreStream();
	adjustTextOut(textOut);
	// check entries in the fileNameVector
	vector<string> fileName = console->getFileName();
	ASSERT_EQ(fileNames.size() - filesExcluded, fileName.size()) << "Print format was not checked.";
	// check the report content
	EXPECT_EQ(text, textOut);
}

TEST_F(PrintF, DefaultWildcard_ExcludeError)
// test print wildcard with exclude errors and ignore-exclude-errors
{
	// expected text
	string text =
	    "------------------------------------------------------------\n"
	    "Directory  <test_directory>/*.cpp\n"
	    "Exclude  fileExcluded.cpp\n"
	    "Exclude (unmatched)  noExcludedFile.cpp\n"
	    "Exclude (unmatched)  noExcludedDirectory\n"
	    "------------------------------------------------------------\n"
	    "Formatted  fileFormatted.cpp\n"
	    "Unchanged  fileUnchanged.cpp\n";
	adjustText(text);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back("--ascii");
	astyleOptionsVector.push_back("--ignore-exclude-errors");
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// add exclude files
	buildExcludeVector();
	console->updateExcludeVector("noExcludedFile.cpp");
	console->updateExcludeVector("noExcludedDirectory");
	// redirect stdout and get the report
	redirectStream();
	console->processFiles();
	string textOut = restoreStream();
	adjustTextOut(textOut);
	// check entries in the fileNameVector
	vector<string> fileName = console->getFileName();
	ASSERT_EQ(fileNames.size() - filesExcluded, fileName.size()) << "Print format was not checked.";
	// check the report content
	EXPECT_EQ(text, textOut);
}

TEST_F(PrintF, DefaultWildcard_ExcludeErrorNoPrint)
// test print wildcard with exclude errors and ignore-exclude-errors-x
{
	// expected text
	string text =
	    "------------------------------------------------------------\n"
	    "Directory  <test_directory>/*.cpp\n"
	    "Exclude  fileExcluded.cpp\n"
	    "------------------------------------------------------------\n"
	    "Formatted  fileFormatted.cpp\n"
	    "Unchanged  fileUnchanged.cpp\n";
	adjustText(text);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back("--ascii");
	astyleOptionsVector.push_back("--ignore-exclude-errors-x");
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// add exclude files
	buildExcludeVector();
	console->updateExcludeVector("noExcludedFile.cpp");
	console->updateExcludeVector("noExcludedDirectory");
	// redirect stdout and get the report
	redirectStream();
	console->processFiles();
	string textOut = restoreStream();
	adjustTextOut(textOut);
	// check entries in the fileNameVector
	vector<string> fileName = console->getFileName();
	ASSERT_EQ(fileNames.size() - filesExcluded, fileName.size()) << "Print format was not checked.";
	// check the report content
	EXPECT_EQ(text, textOut);
}

TEST_F(PrintF, FormattedWildcard)
// test print with "formatted" wildcard
{
	console->setIsFormattedOnly(true);		// test variable
	// expected text
	string text =
	    "------------------------------------------------------------\n"
	    "Directory  <test_directory>/*.cpp\n"
	    "------------------------------------------------------------\n"
	    "Formatted  fileFormatted.cpp\n";
	adjustText(text);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back("--ascii");
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// redirect stdout and get the report
	redirectStream();
	console->processFiles();
	string textOut = restoreStream();
	adjustTextOut(textOut);
	// check entries in the fileNameVector
	vector<string> fileName = console->getFileName();
	ASSERT_EQ(fileNames.size(), fileName.size()) << "Print format was not checked.";
	// check the report content
	EXPECT_EQ(text, textOut);
}

TEST_F(PrintF, VerboseWildcard_DefaultOptionFile)
// test print with "verbose" wildcard and default option file
{
	console->setIsVerbose(true);		// test variable
	// expected text
	string text =
	    "Artistic Style <version>                            <date>\n"
	    "Default option file  <test_directory>/astylerc.txt\n"
	    "------------------------------------------------------------\n"
	    "Directory  <test_directory>/*.cpp\n"
	    "------------------------------------------------------------\n"
	    "Formatted  fileFormatted.cpp\n"
	    "Unchanged  fileUnchanged.cpp\n"
	    "------------------------------------------------------------\n"
	    " 1 formatted   1 unchanged   0 seconds   12 lines\n\n";
	adjustText(text);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back("--ascii");
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// add option file
	console->setOptionFileName(getTestDirectory() + "/astylerc.txt");
	// redirect stdout and get the report
	redirectStream();
	console->processFiles();
	string textOut = restoreStream();
	adjustTextOut(textOut);
	// check entries in the fileNameVector
	vector<string> fileName = console->getFileName();
	ASSERT_EQ(fileNames.size() - filesExcluded, fileName.size()) << "Print format was not checked.";
	// check the report content
	EXPECT_EQ(text, textOut);
}

TEST_F(PrintF, VerboseWildcard_ProjectOptionFile)
// test print with "verbose" wildcard and project option file
{
	console->setIsVerbose(true);		// test variable
	// expected text
	string text =
	    "Artistic Style <version>                            <date>\n"
	    "Project option file  <test_directory>/astylerc.txt\n"
	    "------------------------------------------------------------\n"
	    "Directory  <test_directory>/*.cpp\n"
	    "------------------------------------------------------------\n"
	    "Formatted  fileFormatted.cpp\n"
	    "Unchanged  fileUnchanged.cpp\n"
	    "------------------------------------------------------------\n"
	    " 1 formatted   1 unchanged   0 seconds   12 lines\n\n";
	adjustText(text);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back("--ascii");
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// add project option file
	console->setProjectOptionFileName(getTestDirectory() + "/astylerc.txt");
	// redirect stdout and get the report
	redirectStream();
	console->processFiles();
	string textOut = restoreStream();
	adjustTextOut(textOut);
	// check entries in the fileNameVector
	vector<string> fileName = console->getFileName();
	ASSERT_EQ(fileNames.size() - filesExcluded, fileName.size()) << "Print format was not checked.";
	// check the report content
	EXPECT_EQ(text, textOut);
}

TEST_F(PrintF, VerboseWildcard_DefaultAndProjectOptionFiles)
// test print with "verbose" wildcard and default and project option files
{
	console->setIsVerbose(true);		// test variable
	// expected text
	string text =
	    "Artistic Style <version>                            <date>\n"
	    "Default option file  <test_directory>/astylerc.txt\n"
	    "Project option file  <test_directory>/astylerc.txt\n"
	    "------------------------------------------------------------\n"
	    "Directory  <test_directory>/*.cpp\n"
	    "------------------------------------------------------------\n"
	    "Formatted  fileFormatted.cpp\n"
	    "Unchanged  fileUnchanged.cpp\n"
	    "------------------------------------------------------------\n"
	    " 1 formatted   1 unchanged   0 seconds   12 lines\n\n";
	adjustText(text);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back("--ascii");
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// add option files
	console->setOptionFileName(getTestDirectory() + "/astylerc.txt");
	console->setProjectOptionFileName(getTestDirectory() + "/astylerc.txt");
	// redirect stdout and get the report
	redirectStream();
	console->processFiles();
	string textOut = restoreStream();
	adjustTextOut(textOut);
	// check entries in the fileNameVector
	vector<string> fileName = console->getFileName();
	ASSERT_EQ(fileNames.size() - filesExcluded, fileName.size()) << "Print format was not checked.";
	// check the report content
	EXPECT_EQ(text, textOut);
}

TEST_F(PrintF, VerboseFormattedWildcard)
// test print with "verbose" and "formatted" wildcard
{
	console->setIsVerbose(true);			// test variable
	console->setIsFormattedOnly(true);		// test variable
	// expected text
	string text =
	    "Artistic Style <version>                            <date>\n"
	    "------------------------------------------------------------\n"
	    "Directory  <test_directory>/*.cpp\n"
	    "------------------------------------------------------------\n"
	    "Formatted  fileFormatted.cpp\n"
	    "------------------------------------------------------------\n"
	    " 1 formatted   1 unchanged   0 seconds   12 lines\n\n";
	adjustText(text);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back("--ascii");
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// redirect stdout and get the report
	redirectStream();
	console->processFiles();
	string textOut = restoreStream();
	adjustTextOut(textOut);
	// check entries in the fileNameVector
	vector<string> fileName = console->getFileName();
	ASSERT_EQ(fileNames.size() - filesExcluded, fileName.size()) << "Print format was not checked.";
	// check the report content
	EXPECT_EQ(text, textOut);
}

TEST_F(PrintF, DefaultSingleFile)
// test print single file with no options
{
	// expected text
	string text = "Formatted  <test_directory>/fileFormatted.cpp\n";
	adjustText(text);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back("--ascii");
	astyleOptionsVector.push_back(getTestDirectory() + "/fileFormatted.cpp");
	console->processOptions(astyleOptionsVector);
	// redirect stdout and get the report
	redirectStream();
	console->processFiles();
	string textOut = restoreStream();
	adjustTextOut(textOut);
	// check entries in the fileNameVector
	vector<string> fileName = console->getFileName();
	ASSERT_EQ(1U, fileName.size()) << "Print format was not checked.";
	// check the report content
	EXPECT_EQ(text, textOut);
}

TEST_F(PrintF, FormattedSingleFile)
// test print with "formatted" single file
{
	console->setIsFormattedOnly(true);		// test variable
	// expected text
	string text = "Formatted  <test_directory>/fileFormatted.cpp\n";
	adjustText(text);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back("--ascii");
	astyleOptionsVector.push_back(getTestDirectory() + "/fileFormatted.cpp");
	console->processOptions(astyleOptionsVector);
	// redirect stdout and get the report
	redirectStream();
	console->processFiles();
	string textOut = restoreStream();
	adjustTextOut(textOut);
	// check entries in the fileNameVector
	vector<string> fileName = console->getFileName();
	ASSERT_EQ(1U, fileName.size()) << "Print format was not checked.";
	// check the report content
	EXPECT_EQ(text, textOut);
}

TEST_F(PrintF, VerboseSingleFile_OptionsFile)
// test print with "verbose" single file
{
	console->setIsVerbose(true);		// test variable
	// expected text
	string text =
	    "Artistic Style <version>                            <date>\n"
	    "Default option file  <test_directory>/astylerc.txt\n"
	    "Formatted  <test_directory>/fileFormatted.cpp\n"
	    " 1 formatted   0 unchanged   0 seconds   6 lines\n\n";
	adjustText(text);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back("--ascii");
	astyleOptionsVector.push_back(getTestDirectory() + "/fileFormatted.cpp");
	console->processOptions(astyleOptionsVector);
	// add options file
	console->setOptionFileName(getTestDirectory() + "/astylerc.txt");
	// redirect stdout and get the report
	redirectStream();
	console->processFiles();
	string textOut = restoreStream();
	adjustTextOut(textOut);
	// check entries in the fileNameVector
	vector<string> fileName = console->getFileName();
	ASSERT_EQ(1U, fileName.size()) << "Print format was not checked.";
	// check the report content
	EXPECT_EQ(text, textOut);
}

TEST_F(PrintF, Quiet_AllOptions)
// test print with "quiet" and all other options
{
	console->setIsFormattedOnly(true);
	console->setIsVerbose(true);
	console->setIsQuiet(true);		// test variable
	// expected text
	string text = "\n";
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back("--ascii");
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// add options and exclude files
	console->setOptionFileName(getTestDirectory() + "/astylerc.txt");
	buildExcludeVector();
	// redirect stdout and get the report
	redirectStream();
	console->processFiles();
	string textOut = restoreStream();
	adjustTextOut(textOut);
	// check entries in the fileNameVector
	vector<string> fileName = console->getFileName();
	ASSERT_EQ(fileNames.size() - filesExcluded, fileName.size()) << "Print format was not checked.";
	// check the report content
	EXPECT_EQ(text, textOut);
}

//----------------------------------------------------------------------------

}  // namespace
