// AStyleTestCon_Console1.cpp
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
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

#include <time.h>
#include "AStyleTestCon.h"

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {
//
//----------------------------------------------------------------------------
// AStyle processOptions() for console options
// test vectors excludeVector, excludeHitsVector, fileNameVector, optionsVector
//----------------------------------------------------------------------------

TEST(ProcessOptions, ExcludeVector)
// test processOptions for excludeVector
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build excludeVector
	vector<string> excludesIn;
	excludesIn.push_back("--exclude=../dir1/prog1.cpp");
	excludesIn.push_back("--exclude=../dir1\\prog2.cpp");
	excludesIn.push_back("--exclude=../dir1/prog3.cpp");
	excludesIn.push_back("--exclude=prog4.cpp");
	excludesIn.push_back("--exclude=/prog5.cpp");
	excludesIn.push_back("--exclude=\\prog6.cpp");
	excludesIn.push_back("--exclude=../dir1/");
	excludesIn.push_back("--exclude=..\\dir2");
	excludesIn.push_back("--exclude=../dir3\\");
	excludesIn.push_back("--exclude=dir4");
	excludesIn.push_back("--exclude=/dir5");
	excludesIn.push_back("--exclude=\\dir6");
	console->processOptions(excludesIn);
	// build vector for checking results
	vector<string> excludes;
	for (size_t i = 0; i < excludesIn.size(); i++)
	{
		excludes.push_back(excludesIn[i].substr(10));
		console->standardizePath(excludes[i], true);
	}
	// check excludeVector
	vector<string> excludeVector = console->getExcludeVector();
	EXPECT_EQ(excludesIn.size(), excludeVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < excludeVector.size(); i++)
		EXPECT_EQ(excludes[i], excludeVector[i]);
}

TEST(ProcessOptions, ExcludeHitsVector)
// test processOptions for excludeHitsVector
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build excludeHitsVector
	vector<string> excludesIn;
	excludesIn.push_back("--exclude=../dir/prog1.cpp");
	excludesIn.push_back("--exclude=../dir\\prog2.cpp");
	excludesIn.push_back("--exclude=../dir/prog3.cpp");
	excludesIn.push_back("--exclude=../dir3/");
	excludesIn.push_back("--exclude=..\\dir4");
	excludesIn.push_back("--exclude=../dir\\");
	console->processOptions(excludesIn);
	// check excludeHitsVector
	vector<bool> excludeHitsVector = console->getExcludeHitsVector();
	EXPECT_EQ(excludesIn.size(), excludeHitsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < excludeHitsVector.size(); i++)
		EXPECT_FALSE(excludeHitsVector[i]);
}

TEST(ProcessOptions, FileNameVector)
// test processOptions for fileNameVector
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build fileNameVector
	vector<string> fileNameIn;
	fileNameIn.push_back("../..\\..\\srccon/*.cpp");
	console->processOptions(fileNameIn);
	vector<string> fileName;
	fileName.push_back("../../../srccon/*.cpp");
	console->standardizePath(fileName.back());
	// check fileNameVector
	vector<string> fileNameVector = console->getFileNameVector();
	EXPECT_EQ(fileName.size(), fileNameVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < fileNameVector.size(); i++)
		EXPECT_EQ(fileName[i], fileNameVector[i]);
}

TEST(ProcessOptions, OptionsVector)
// test processOptions for optionsVector
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build optionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--style=allman");
	optionsIn.push_back("--indent-classes");
	optionsIn.push_back("-OoP");
	optionsIn.push_back("-Ewc");
	optionsIn.push_back("--align-pointer=type");
	console->processOptions(optionsIn);
	// check optionsVector
	vector<string> optionsVector = console->getOptionsVector();
	EXPECT_EQ(optionsIn.size(), optionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < optionsVector.size(); i++)
		EXPECT_EQ(optionsIn[i], optionsVector[i]);
}

TEST(ProcessOptions, GetCurrentDirectory)
// test getCurrentDirectory function
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	console->setNoBackup(true);
	console->setIsQuiet(true);		// change this to see results
	char textIn[] = "void foo(){}\n";
	// a file without a path will call the console->getCurrentDirectory
	string testFile = "/GetCurrentDirectory.cpp";
	string testFilePath = getCurrentDirectory() + testFile;
	console->standardizePath(testFilePath);
	// write the output file to the current directory
	ofstream fout(testFilePath.c_str(), ios::binary | ios::trunc);
	if (!fout)
	{
		systemPause("Cannot open output file: " + testFilePath);
		return;
	}
	fout << textIn;
	fout.close();
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back(testFilePath);
	console->processOptions(astyleOptionsVector);
	// call astyle processFiles()
	console->processFiles();
	vector<string> fileName = console->getFileName();
	EXPECT_EQ(testFilePath, fileName[0]);
	removeTestFile(testFilePath);
}

TEST(ProcessOptions, OtherOptions)
// test processOptions for other options
// the "lineend" option is tested separately
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// set console options
	vector<string> optionsIn;
	optionsIn.push_back("--suffix=none");
	optionsIn.push_back("--suffix=.old");
	optionsIn.push_back("--recursive");
	optionsIn.push_back("--dry-run");
	optionsIn.push_back("--verbose");
	optionsIn.push_back("--formatted");
	optionsIn.push_back("--quiet");
	optionsIn.push_back("--errors-to-stdout");
	optionsIn.push_back("--preserve-date");
	console->processOptions(optionsIn);
	// check console options
	EXPECT_TRUE(console->getNoBackup());
	EXPECT_EQ(string(".old"), console->getOrigSuffix());
	EXPECT_TRUE(console->getIsRecursive());
	EXPECT_TRUE(console->getIsDryRun());
	EXPECT_TRUE(console->getIsVerbose());
	EXPECT_TRUE(console->getIsFormattedOnly());
	EXPECT_TRUE(console->getIsQuiet());
	EXPECT_TRUE(console->getErrorStream() == &cout);
	EXPECT_TRUE(console->getPreserveDate());
}

TEST(ProcessOptions, OtherOptions_Short)
// test processOptions for short other options
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// set console options
	vector<string> optionsIn;
	optionsIn.push_back("-n");	// suffix=none
	optionsIn.push_back("-r");	// recursive
	optionsIn.push_back("-R");	// recursive
	optionsIn.push_back("-v");	// verbose
	optionsIn.push_back("-Q");	// formatted
	optionsIn.push_back("-q");	// quiet
	optionsIn.push_back("-X");	// errors-to-stdout
	optionsIn.push_back("-Z");	// preserve-date
	console->processOptions(optionsIn);
	// check console options
	EXPECT_TRUE(console->getNoBackup());
	EXPECT_TRUE(console->getIsRecursive());
	EXPECT_TRUE(console->getIsVerbose());
	EXPECT_TRUE(console->getIsFormattedOnly());
	EXPECT_TRUE(console->getIsQuiet());
	EXPECT_TRUE(console->getErrorStream() == &cout);
	EXPECT_TRUE(console->getPreserveDate());
}

TEST(ProcessOptions, ConsoleOptions_Error)
// test processOptions for command line options errors
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--style=allman");
	optionsIn.push_back("-OoP");
	optionsIn.push_back("--invalid1");
	optionsIn.push_back("--invalid2");
	optionsIn.push_back("--invalid3");
	optionsIn.push_back("--indent-classes");
	optionsIn.push_back("--ascii");
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions with invalid command line options
	EXPECT_EXIT(console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_FAILURE),
	            "Invalid command line options:\n"
	            "\tinvalid1\n"
	            "\tinvalid2\n"
	            "\tinvalid3\n"
	            "For help on options type 'astyle -h'");
#endif
}

//----------------------------------------------------------------------------
// AStyle ascii, stdin, stdout, and ignore-exclude-errors options
//----------------------------------------------------------------------------

TEST(ProcessOptions, AsciiOption)
// test processOptions for ascii option
// For a complete test the user locale should be something besides English.
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--ascii");
	console->processOptions(optionsIn);
	string langID = console->getLanguageID();
	EXPECT_EQ(langID, "en");
}

TEST(ProcessOptions, AsciiOption_Short)
// test processOptions for ascii short option -I
// For a complete test the user locale should be something besides English.
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("-I");
	console->processOptions(optionsIn);
	// test the language
	string langID = console->getLanguageID();
	EXPECT_EQ(langID, "en");
}

TEST(ProcessOptions, StdInOption)
// test processOptions for stdin= option
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build optionsIn
	vector<string> optionsIn;
	string path = "../../folderin/filein.cpp";
	optionsIn.push_back("--stdin=" + path);
	console->processOptions(optionsIn);
	// test the filepath
	console->standardizePath(path);
	string filepath = console->getStdPathIn();
	EXPECT_EQ(filepath, path);
}

TEST(ProcessOptions, StdOutOption)
// test processOptions for stdout= option
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build optionsIn
	vector<string> optionsIn;
	string path = "../../folderout/fileout.cpp";
	optionsIn.push_back("--stdout=" + path);
	console->processOptions(optionsIn);
	// test the filepath
	console->standardizePath(path);
	string filepath = console->getStdPathOut();
	EXPECT_EQ(filepath, path);
}

TEST(ProcessOptions, IgnoreExcludeErrorsOption)
// test processOptions for ignore-exclude-errors option
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// set console options
	vector<string> optionsIn;
	optionsIn.push_back("--ignore-exclude-errors");
	console->processOptions(optionsIn);
	// check console options
	EXPECT_TRUE(console->getIgnoreExcludeErrors());
	EXPECT_FALSE(console->getIgnoreExcludeErrorsDisplay());
}

TEST(ProcessOptions, IgnoreExcludeErrorsOption_Short)
// test processOptions for ignore-exclude-errors short option
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// set console options
	vector<string> optionsIn;
	optionsIn.push_back("-i");
	console->processOptions(optionsIn);
	// check console options
	EXPECT_TRUE(console->getIgnoreExcludeErrors());
	EXPECT_FALSE(console->getIgnoreExcludeErrorsDisplay());
}

TEST(ProcessOptions, IgnoreExcludeErrorsAndDisplayOption)
// test processOptions for ignore-exclude-errors-x option
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// set console options
	vector<string> optionsIn;
	optionsIn.push_back("--ignore-exclude-errors-x");
	console->processOptions(optionsIn);
	// check console options
	EXPECT_TRUE(console->getIgnoreExcludeErrors());
	EXPECT_TRUE(console->getIgnoreExcludeErrorsDisplay());
}

TEST(ProcessOptions, IgnoreExcludeErrorsAndDisplayOption_Short)
// test processOptions for ignore-exclude-errors-x short option
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// set console options
	vector<string> optionsIn;
	optionsIn.push_back("-xi");
	console->processOptions(optionsIn);
	// check console options
	EXPECT_TRUE(console->getIgnoreExcludeErrors());
	EXPECT_TRUE(console->getIgnoreExcludeErrorsDisplay());
}

//----------------------------------------------------------------------------
// AStyle processOptions() for file options
// test vector fileOptionsVector
//----------------------------------------------------------------------------

TEST(ProcessDefaultOptions, OptionsPath)
// test processOptions for fileOptionsVector with --options=###
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "# this line is a comment\n"
	    "--style=attach   # this is a line-end comment\n"
	    "\n"
	    "# long options can be written without the preceding '--'\n"
	    "indent-switches     # cannot do this on the command line\n"
	    "\n"
	    "# short options must have the preceding '-'\r\n"
	    "-t -p\r\n"
	    "\n"
	    "# short options can be concatenated together\n"
	    "-M65Ucv\n"
	    "\n"
	    "# options can have CR line ends\r"
	    "pad-oper,-H\r"
	    "\r"
	    "# options can be separated with commas\n"
	    "indent-classes,-K\n";
#ifdef __BORLANDC__
	// Embarcadero istream does not recognize '\r' line ends
	for (size_t ec = 0; ec < strlen(fileIn); ec++)
		if (fileIn[ec] == '\r' && fileIn[ec + 1] != '\n')
			fileIn[ec] = '\n';
#endif
	vector<string> fileOptions;
	fileOptions.push_back("--style=attach");
	fileOptions.push_back("indent-switches");
	fileOptions.push_back("-t");
	fileOptions.push_back("-p");
	fileOptions.push_back("-M65Ucv");
	fileOptions.push_back("pad-oper");
	fileOptions.push_back("-H");
	fileOptions.push_back("indent-classes");
	fileOptions.push_back("-K");
	// write the options file
	string optionFileName = getTestDirectory() + "/astylerc.txt";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// build fileOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--options=" + optionFileName);
	console->processOptions(optionsIn);
	// check fileOptionsVector
	vector<string> fileOptionsVector = console->getFileOptionsVector();
	EXPECT_EQ(fileOptions.size(), fileOptionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < fileOptionsVector.size(); i++)
		EXPECT_EQ(fileOptions[i], fileOptionsVector[i]);
	removeTestFile(optionFileName);
}

TEST(ProcessDefaultOptions, EnvironmentVariable)
// test processOptions for fileOptionsVector
//     with ARTISTIC_STYLE_OPTIONS enviromnent variable
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");
	// set the new environment variable
	string envFilePath = getTestDirectory() + "/astylexx";
	string envValue = "ARTISTIC_STYLE_OPTIONS=" + envFilePath;
	console->standardizePath(envFilePath);
	console->standardizePath(envValue);
	int isError = putenv(const_cast<char*>(envValue.c_str()));
	if (isError)
	{
		systemPause("Cannot set ARTISTIC_STYLE_OPTIONS environment variable");
		return;
	}
	// write the options file
	if (!writeOptionsFile(envFilePath.c_str(), fileIn))
		return;
	// build fileOptionsVector
	vector<string> optionsIn;
	console->processOptions(optionsIn);
	// check fileOptionsVector
	vector<string> fileOptionsVector = console->getFileOptionsVector();
	EXPECT_EQ(fileOptions.size(), fileOptionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < fileOptionsVector.size(); i++)
		EXPECT_EQ(fileOptions[i], fileOptionsVector[i]);
	// clear the environment variable
	string envClear = "ARTISTIC_STYLE_OPTIONS=";
	putenv(const_cast<char*>(envClear.c_str()));
	// cleanup
	removeTestFile(envFilePath);
}

TEST(ProcessDefaultOptions, HomeEnvironmentVariable)
// test processOptions for fileOptionsVector with $HOME options
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");
	// write the options file
	string optionFileName = getDefaultOptionsFilePath();
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// build fileOptionsVector
	vector<string> optionsIn;
	console->processOptions(optionsIn);
	// check fileOptionsVector
	vector<string> fileOptionsVector = console->getFileOptionsVector();
	EXPECT_EQ(fileOptions.size(), fileOptionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < fileOptionsVector.size(); i++)
		EXPECT_EQ(fileOptions[i], fileOptionsVector[i]);
	removeTestFile(optionFileName);
}

TEST(ProcessDefaultOptions, DisabledOptionsFile)
// test processOptions for fileOptionsVector with --options=none
// should not process the astylerc file
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	// write the options file
	string optionFileName = getDefaultOptionsFilePath();
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// build fileOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--options=none");
	console->processOptions(optionsIn);
	// check fileOptionsVector
	vector<string> fileOptionsVector = console->getFileOptionsVector();
	EXPECT_TRUE(fileOptionsVector.size() == 0);
	removeTestFile(optionFileName);
}

TEST(ProcessDefaultOptions, DisableEnvironmentVariable)
// test processOptions for fileOptionsVector with --options=none
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");
	// set the new environment variable
	string envValue = "ARTISTIC_STYLE_OPTIONS=astyle.ini";;
	int isError = putenv(const_cast<char*>(envValue.c_str()));
	if (isError)
	{
		systemPause("Cannot set ARTISTIC_STYLE_OPTIONS environment variable");
		return;
	}
	// write the options file
	string optionFileName = getTestDirectory() + "/astyle.ini";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// build argvOptionsVector
	// test that 'none' will override command line and environment
	vector<string> optionsIn;
	optionsIn.push_back("--options=" + optionFileName);
	optionsIn.push_back("--options=none");
	optionsIn.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(optionsIn);
	// fileOptionsVector should be empty
	vector<string> fileOptionsVector = console->getFileOptionsVector();
	EXPECT_EQ(0U, fileOptionsVector.size()) << "Vector should be empty.";
	// clear the environment variable
	string envClear = "ARTISTIC_STYLE_OPTIONS=";
	putenv(const_cast<char*>(envClear.c_str()));
	// cleanup
	removeTestFile(optionFileName);
}

TEST(ProcessDefaultOptions, NoFinalLineEnd)
// test processOptions for fileOptionsVector with --options=###
//    and NO final line end
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes";		// *** no final line end ***
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");
	// write the options file
	string optionFileName = getTestDirectory() + "/astylerc";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// build fileOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--options=" + optionFileName);
	console->processOptions(optionsIn);
	// check fileOptionsVector
	vector<string> fileOptionsVector = console->getFileOptionsVector();
	EXPECT_EQ(fileOptions.size(), fileOptionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < fileOptionsVector.size(); i++)
		EXPECT_EQ(fileOptions[i], fileOptionsVector[i]);
	removeTestFile(optionFileName);
}

TEST(ProcessDefaultOptions, DefaultOptionErrors)
// test processOptions for file option errors
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "--style=allman\n"
	    "-OoP\n"
	    "--invalid1\n"
	    "--invalid2\n"
	    "--invalid3\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--invalid1");
	fileOptions.push_back("--invalid2");
	fileOptions.push_back("--invalid3");
	fileOptions.push_back("--indent-classes");
	// write options the file
	string optionFileName = getTestDirectory() + "/astylerc.txt";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--options=" + optionFileName);
	optionsIn.push_back("--ascii");
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions with invalid file options
	EXPECT_EXIT(console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_FAILURE),
	            "Invalid default options:\n"
	            "\tinvalid1\n"
	            "\tinvalid2\n"
	            "\tinvalid3\n"
	            "For help on options type 'astyle -h'");
#endif
	removeTestFile(optionFileName);
}

TEST(ProcessDefaultOptions, FileError1)
// test processOptions with an option file error
// input with --options=###
// invalidrc.txt is not a valid file
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build optionsIn
	string optionFileName = "../../srccon/invalidrc.txt";
	console->standardizePath(optionFileName);
	vector<string> optionsIn;
	optionsIn.push_back("--options=" + optionFileName);
	optionsIn.push_back("--ascii");
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions with options file error
	EXPECT_EXIT(console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_FAILURE),
	            "Cannot open default option file");
#endif
}

TEST(ProcessDefaultOptions, FileError2)
// test processOptions with an option file error
// input with --options= (no filename)
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--options=");
	optionsIn.push_back("--ascii");
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions with options file error
	EXPECT_EXIT(console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_FAILURE),
	            "Cannot open default option file");
#endif
}

TEST(ProcessDefaultOptions, FileError3)
// test processOptions with an option file error
// input with environment variable and no file present
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--ascii");
	// set the new environment variable
	string envFilePath = getTestDirectory() + "/astylerc";
	console->standardizePath(envFilePath);
	string envValue = "ARTISTIC_STYLE_OPTIONS=" + envFilePath;
	int isError = putenv(const_cast<char*>(envValue.c_str()));
	if (isError)
	{
		systemPause("Cannot set ARTISTIC_STYLE_OPTIONS environment variable");
		return;
	}
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions with options file error
	EXPECT_EXIT(console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_FAILURE),
	            "Cannot open default option file");
#endif
	// clear the environment variable
	string envClear = "ARTISTIC_STYLE_OPTIONS=";
	putenv(const_cast<char*>(envClear.c_str()));
	// cleanup
}

TEST(ProcessDefaultOptions, Excludes)
// test processOptions with resource fileexcludes
// input with --options=###
// the quotes must be removed from the excludeVector
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "--exclude=\"prog 1.cpp\"\n"
	    "exclude=\"\\prog 2.cpp\"\n"
	    "\"--exclude=/prog 3.cpp\"\n"
	    "\"exclude=prog 4.cpp\"\n"
	    "--exclude=prog-5.cpp exclude=prog-5a.cpp\n"
	    // missing closing quote are OK if followed by delimiter
	    "--exclude=\"prog 6.cpp\n"
	    "--exclude=\"prog 7.cpp, exclude=prog-7a.cpp\n"
	    "--exclude=\"prog 8.cpp\t --exclude=\"prog 8a.cpp\n";
	// build excludesOut containing the astylerc.txt excluded files
	vector<string> excludesOut;
	excludesOut.push_back("prog 1.cpp");
	excludesOut.push_back("prog 2.cpp");
	excludesOut.push_back("prog 3.cpp");
	excludesOut.push_back("prog 4.cpp");
	excludesOut.push_back("prog-5.cpp");
	excludesOut.push_back("prog-5a.cpp");
	excludesOut.push_back("prog 6.cpp");
	excludesOut.push_back("prog 7.cpp");
	excludesOut.push_back("prog-7a.cpp");
	excludesOut.push_back("prog 8.cpp");
	excludesOut.push_back("prog 8a.cpp");
	for (size_t i = 0; i < excludesOut.size(); i++)
		console->standardizePath(excludesOut[i], true);
	// write the options file
	string optionFileName = getTestDirectory() + "/astylerc.txt";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// build fileOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--options=" + optionFileName);
	console->processOptions(optionsIn);
	// check excludeVector
	vector<string> excludeVector = console->getExcludeVector();
	EXPECT_EQ(excludesOut.size(), excludeVector.size()) << "Vector sizes not equal.";
	// NOTE: errors may not display correctly on Windows because of '\' in file paths
	for (size_t i = 0; i < excludeVector.size(); i++)
		EXPECT_EQ(excludesOut[i], excludeVector[i]);
	removeTestFile(optionFileName);
}

TEST(ProcessDefaultOptions, Utf8BOM)
// test processOptions for fileOptionsVector with --options=###
// and with a UTF-8 BOM
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "\xEF\xBB\xBF"			// utf-8 bom
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");
	// write the options file
	string optionFileName = getTestDirectory() + "/astylerc.txt";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// build fileOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--options=" + optionFileName);
	console->processOptions(optionsIn);
	// check fileOptionsVector
	vector<string> fileOptionsVector = console->getFileOptionsVector();
	EXPECT_EQ(fileOptions.size(), fileOptionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < fileOptionsVector.size(); i++)
		EXPECT_EQ(fileOptions[i], fileOptionsVector[i]);
	removeTestFile(optionFileName);
}

TEST(ProcessDefaultOptions, Utf16LE)
// test processOptions for fileOptionsVector with --options=###
// and with UTF-16LE BOM and encoding
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "\xEF\xBB\xBF"			// utf-8 bom to be converted
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");

	// convert options file to utf-16le
	ASEncoding encode;         // file encoding conversion from astyle
	ostringstream out;
	size_t utf16Size = encode.utf16LengthFromUtf8(fileIn, strlen(fileIn));
	// NOTE: do not use smart pointer here
	char* utf16Out = new (nothrow) char[utf16Size];
	if (utf16Out == nullptr)
		FAIL() << "Cannot allocate utf16Out";
	size_t utf16Len = encode.utf8ToUtf16(fileIn, strlen(fileIn), false, utf16Out);
	EXPECT_TRUE(utf16Len <= utf16Size) << "Bad conversion length.";

	// write the utf-16le options file
	string optionFileName = getTestDirectory() + "/astylerc.txt";
	console->standardizePath(optionFileName);
	ofstream fout(optionFileName.c_str(), ios::binary | ios::trunc);
	fout << string(utf16Out, utf16Len);
	if (!fout)
	{
		systemPause("Cannot write options test file: " + optionFileName);
		return;
	}
	fout.close();

	// build fileOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--options=" + optionFileName);
	console->processOptions(optionsIn);
	// check fileOptionsVector
	vector<string> fileOptionsVector = console->getFileOptionsVector();
	EXPECT_EQ(fileOptions.size(), fileOptionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < fileOptionsVector.size(); i++)
		EXPECT_EQ(fileOptions[i], fileOptionsVector[i]);
	removeTestFile(optionFileName);
	delete[] utf16Out;
}

TEST(ProcessDefaultOptions, Utf16BE)
// test processOptions for fileOptionsVector with --options=###
// and with UTF-16BE BOM and encoding
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "\xEF\xBB\xBF"			// utf-8 bom to be converted
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");

	// convert options file to utf-16be
	ASEncoding encode;         // file encoding conversion from astyle
	ostringstream out;
	size_t utf16Size = encode.utf16LengthFromUtf8(fileIn, strlen(fileIn));
	// NOTE: do not use smart pointer here
	char* utf16Out = new (nothrow) char[utf16Size];
	if (utf16Out == nullptr)
		FAIL() << "Cannot allocate utf16Out";
	size_t utf16Len = encode.utf8ToUtf16(fileIn, strlen(fileIn), true, utf16Out);
	EXPECT_TRUE(utf16Len <= utf16Size) << "Bad conversion length.";

	// write the utf-16be options file
	string optionFileName = getTestDirectory() + "/astylerc.txt";
	console->standardizePath(optionFileName);
	ofstream fout(optionFileName.c_str(), ios::binary | ios::trunc);
	fout << string(utf16Out, utf16Len);
	if (!fout)
	{
		systemPause("Cannot write options test file: " + optionFileName);
		return;
	}
	fout.close();

	// build fileOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--options=" + optionFileName);
	console->processOptions(optionsIn);
	// check fileOptionsVector
	vector<string> fileOptionsVector = console->getFileOptionsVector();
	EXPECT_EQ(fileOptions.size(), fileOptionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < fileOptionsVector.size(); i++)
		EXPECT_EQ(fileOptions[i], fileOptionsVector[i]);
	removeTestFile(optionFileName);
	delete[] utf16Out;
}

//----------------------------------------------------------------------------
// AStyle processOptions() for project options
//----------------------------------------------------------------------------

TEST(ProcessProjectOptions, OptionsPath1)
// test processOptions for projectOptionsVector
// use the default filename .astylerc in the test directory
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "# this line is a comment\n"
	    "--style=attach   # this is a line-end comment\n"
	    "\n"
	    "# long options can be written without the preceding '--'\n"
	    "indent-switches     # cannot do this on the command line\n"
	    "\n"
	    "# short options must have the preceding '-'\r\n"
	    "-t -p\r\n"
	    "\n"
	    "# short options can be concatenated together\n"
	    "-M65Ucv\n"
	    "\n"
	    "# options can have CR line ends\r"
	    "pad-oper,-H\r"
	    "\r"
	    "# options can be separated with commas\n"
	    "indent-classes,-K\n";
#ifdef __BORLANDC__
	// Embarcadero istream does not recognize '\r' line ends
	for (size_t ec = 0; ec < strlen(fileIn); ec++)
		if (fileIn[ec] == '\r' && fileIn[ec + 1] != '\n')
			fileIn[ec] = '\n';
#endif
	vector<string> fileOptions;
	fileOptions.push_back("--style=attach");
	fileOptions.push_back("indent-switches");
	fileOptions.push_back("-t");
	fileOptions.push_back("-p");
	fileOptions.push_back("-M65Ucv");
	fileOptions.push_back("pad-oper");
	fileOptions.push_back("-H");
	fileOptions.push_back("indent-classes");
	fileOptions.push_back("-K");
	// write the options file
	string optionFileName = getTestDirectory() + "/.astylerc";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// build argvOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--project");
	optionsIn.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(optionsIn);
	// check projectOptionsVector for project options
	vector<string> projectOptionsVector = console->getProjectOptionsVector();
	EXPECT_EQ(fileOptions.size(), projectOptionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < projectOptionsVector.size(); i++)
		EXPECT_EQ(fileOptions[i], projectOptionsVector[i]);
	removeTestFile(optionFileName);
}

TEST(ProcessProjectOptions, OptionsPath2)
// test processOptions for projectOptionsVector
// use the default filename _astylerc in a parent of the test directory
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");
	// write the options file
	string optionFileName = getTestDirectory() + "/_astylerc";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// create directories
	string sub1  = getTestDirectory() + "/subdir1";
	console->standardizePath(sub1);
	createTestDirectory(sub1);
	// build argvOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--project");
	optionsIn.push_back(sub1 + "/*.cpp");
	console->processOptions(optionsIn);
	// check projectOptionsVector for project options
	vector<string> projectOptionsVector = console->getProjectOptionsVector();
	EXPECT_EQ(fileOptions.size(), projectOptionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < projectOptionsVector.size(); i++)
		EXPECT_EQ(fileOptions[i], projectOptionsVector[i]);
	removeTestFile(optionFileName);
	cleanTestDirectory(getTestDirectory());
}

TEST(ProcessProjectOptions, OptionsPath3)
// test processOptions for projectOptionsVector
// use the project=astyle.ini command line option in a parent of the test directory
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");
	// write the options file
	string optionFileName = getTestDirectory() + "/astyle.ini";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// create directories
	string sub1  = getTestDirectory() + "/subdir1";
	string sub1a = getTestDirectory() + "/subdir1/subdir1a";
	console->standardizePath(sub1);
	console->standardizePath(sub1a);
	createTestDirectory(sub1);
	createTestDirectory(sub1a);
	// build argvOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--project=astyle.ini");
	optionsIn.push_back(sub1a + "/*.cpp");
	console->processOptions(optionsIn);
	// check fileOptionsVector for project options
	vector<string> fileOptionsVector = console->getProjectOptionsVector();
	EXPECT_EQ(fileOptions.size(), fileOptionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < fileOptionsVector.size(); i++)
		EXPECT_EQ(fileOptions[i], fileOptionsVector[i]);
	removeTestFile(optionFileName);
	cleanTestDirectory(getTestDirectory());
}

TEST(ProcessProjectOptions, OptionsStdIn)
// test processOptions for the "--stdin=" option
// use the project=astyle.ini command line option in a parent of "--stdin="
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");
	// write the options file
	string optionFileName = getTestDirectory() + "/astyle.ini";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// create directories
	string sub1  = getTestDirectory() + "/subdir1";
	string sub1a = getTestDirectory() + "/subdir1/subdir1a";
	console->standardizePath(sub1);
	console->standardizePath(sub1a);
	createTestDirectory(sub1);
	createTestDirectory(sub1a);
	// build argvOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--project=astyle.ini");
	optionsIn.push_back("--stdin=" + sub1a + "/*.cpp");
	console->processOptions(optionsIn);
	// check fileOptionsVector for project options
	vector<string> fileOptionsVector = console->getProjectOptionsVector();
	EXPECT_EQ(fileOptions.size(), fileOptionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < fileOptionsVector.size(); i++)
		EXPECT_EQ(fileOptions[i], fileOptionsVector[i]);
	removeTestFile(optionFileName);
	cleanTestDirectory(getTestDirectory());
}

TEST(ProcessProjectOptions, EnvironmentVariable)
// test processOptions for projectOptionsVector
// use the ARTISTIC_STYLE_PROJECT_OPTIONS enviromnent variable
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");
	// write the options file
	string optionFileName = getTestDirectory() + "/astyle.ini";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// set the new environment variable
	if (putenv(const_cast<char*>("ARTISTIC_STYLE_PROJECT_OPTIONS=astyle.ini")))
		FAIL() << "Cannot set ARTISTIC_STYLE_PROJECT_OPTIONS environment variable";
	// build fileOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(optionsIn);
	// check projectOptionsVector
	vector<string> projectOptionsVector = console->getProjectOptionsVector();
	EXPECT_EQ(fileOptions.size(), projectOptionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < projectOptionsVector.size(); i++)
		EXPECT_EQ(fileOptions[i], projectOptionsVector[i]);
	// cleanup
#ifdef _WIN32
	putenv("ARTISTIC_STYLE_PROJECT_OPTIONS=");
#else
	unsetenv("ARTISTIC_STYLE_PROJECT_OPTIONS");
#endif
	if (getenv("ARTISTIC_STYLE_PROJECT_OPTIONS"))
		FAIL() << "ARTISTIC_STYLE_PROJECT_OPTIONS was not deleted.";
	removeTestFile(optionFileName);
}

TEST(ProcessProjectOptions, DisableEnvironmentVariable)
// test processOptions for projectOptionsVector with --project=none
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");
	// write the options file
	string optionFileName = getTestDirectory() + "/astyle.ini";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// set the new environment variable
	if (putenv(const_cast<char*>("ARTISTIC_STYLE_PROJECT_OPTIONS=astyle.ini")))
		FAIL() << "Cannot set ARTISTIC_STYLE_PROJECT_OPTIONS environment variable";
	// build argvOptionsVector
	// test that 'none' will override command line and environment
	vector<string> optionsIn;
	optionsIn.push_back("--project=astyle.ini");
	optionsIn.push_back("--project=none");
	optionsIn.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(optionsIn);
	// projectOptionsVector should be empty
	vector<string> projectOptionsVector = console->getProjectOptionsVector();
	EXPECT_EQ(0U, projectOptionsVector.size()) << "Vector should be empty.";
	// cleanup
#ifdef _WIN32
	putenv("ARTISTIC_STYLE_PROJECT_OPTIONS=");
#else
	unsetenv("ARTISTIC_STYLE_PROJECT_OPTIONS");
#endif
	if (getenv("ARTISTIC_STYLE_PROJECT_OPTIONS"))
		FAIL() << "ARTISTIC_STYLE_PROJECT_OPTIONS was not deleted.";
	removeTestFile(optionFileName);
}

TEST(ProcessProjectOptions, OverrideEnvironmentVariable)
// test processOptions for projectOptionsVector with --project=filename
// filename should override the environment variable
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");
	// write the options file
	string optionFileName = getTestDirectory() + "/astyle.ini";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// set the new environment variable
	if (putenv(const_cast<char*>("ARTISTIC_STYLE_PROJECT_OPTIONS=astyle.ini")))
		FAIL() << "Cannot set ARTISTIC_STYLE_PROJECT_OPTIONS environment variable";
	// build argvOptionsVector
	// test that 'project=' will override the environment variable
	vector<string> optionsIn;
	optionsIn.push_back("--project=astyle.ini");
	optionsIn.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(optionsIn);
	// check projectOptionFileName
	string projectOptionFileName = console->getProjectOptionFileName();
	EXPECT_EQ("astyle.ini", projectOptionFileName);
	// cleanup
#ifdef _WIN32
	putenv("ARTISTIC_STYLE_PROJECT_OPTIONS=");
#else
	unsetenv("ARTISTIC_STYLE_PROJECT_OPTIONS");
#endif
	if (getenv("ARTISTIC_STYLE_PROJECT_OPTIONS"))
		FAIL() << "ARTISTIC_STYLE_PROJECT_OPTIONS was not deleted.";
	removeTestFile(optionFileName);
}

TEST(ProcessProjectOptions, ProjectOptionErrors)
// test processOptions for file project option errors
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "--style=allman\n"
	    "-OoP\n"
	    "--invalid1\n"
	    "--invalid2\n"
	    "--invalid3\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--invalid1");
	fileOptions.push_back("--invalid2");
	fileOptions.push_back("--invalid3");
	fileOptions.push_back("--indent-classes");
	// write options the file
	string optionFileName = getTestDirectory() + "/_astylerc";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--project");
	optionsIn.push_back("--ascii");
	optionsIn.push_back(getTestDirectory() + "/*.cpp");
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions with invalid file options
	EXPECT_EXIT(console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_FAILURE),
	            "Invalid project options:\n"
	            "\tinvalid1\n"
	            "\tinvalid2\n"
	            "\tinvalid3\n"
	            "For help on options type 'astyle -h'");
#endif
	removeTestFile(optionFileName);
}

TEST(ProcessProjectOptions, FileError1)
// test processOptions with a project option file error
// input with --project=### and no file present
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--project=astylerc.txt");
	optionsIn.push_back("--ascii");
	optionsIn.push_back(getTestDirectory() + "/*.cpp");
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions with options file error
	EXPECT_EXIT(console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_FAILURE),
	            "Cannot open project option file astylerc.txt");
#endif
}

TEST(ProcessProjectOptions, FileError2)
// test processOptions with a project option file error
// input with --project= (no filename)
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--project=");
	optionsIn.push_back("--ascii");
	optionsIn.push_back(getTestDirectory() + "/*.cpp");
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions with options file error
	EXPECT_EXIT(console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_FAILURE),
	            "Cannot open project option file");
#endif
}

TEST(ProcessProjectOptions, FileError3)
// test processOptions with a project option file error
// input with --project and no file present
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--project");
	optionsIn.push_back("--ascii");
	optionsIn.push_back(getTestDirectory() + "/*.cpp");
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions with options file error
	EXPECT_EXIT(console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_FAILURE),
	            "Cannot open project option file .astylerc")
	        << "There must NOT be a project file in the parent directories back to HOME.";
#endif
}

TEST(ProcessProjectOptions, Excludes)
// test processOptions with resource fileexcludes
// input with --options=###
// the quotes must be removed from the excludeVector
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "--exclude=\"prog 1.cpp\"\n"
	    "exclude=\"\\prog 2.cpp\"\n"
	    "\"--exclude=/prog 3.cpp\"\n"
	    "\"exclude=prog 4.cpp\"\n"
	    "--exclude=prog-5.cpp exclude=prog-5a.cpp\n"
	    // missing closing quote are OK if followed by delimiter
	    "--exclude=\"prog 6.cpp\n"
	    "--exclude=\"prog 7.cpp, exclude=prog-7a.cpp\n"
	    "--exclude=\"prog 8.cpp\t --exclude=\"prog 8a.cpp\n";
	// build excludesOut containing the astylerc.txt excluded files
	vector<string> excludesOut;
	excludesOut.push_back("prog 1.cpp");
	excludesOut.push_back("prog 2.cpp");
	excludesOut.push_back("prog 3.cpp");
	excludesOut.push_back("prog 4.cpp");
	excludesOut.push_back("prog-5.cpp");
	excludesOut.push_back("prog-5a.cpp");
	excludesOut.push_back("prog 6.cpp");
	excludesOut.push_back("prog 7.cpp");
	excludesOut.push_back("prog-7a.cpp");
	excludesOut.push_back("prog 8.cpp");
	excludesOut.push_back("prog 8a.cpp");
	for (size_t i = 0; i < excludesOut.size(); i++)
		console->standardizePath(excludesOut[i], true);
	// write the options file
	string optionFileName = getTestDirectory() + "/astylerc.txt";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// build fileOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--project=astylerc.txt");
	optionsIn.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(optionsIn);
	// check excludeVector
	vector<string> excludeVector = console->getExcludeVector();
	EXPECT_EQ(excludesOut.size(), excludeVector.size()) << "Vector sizes not equal.";
	// NOTE: errors may not display correctly on Windows because of '\' in file paths
	for (size_t i = 0; i < excludeVector.size(); i++)
		EXPECT_EQ(excludesOut[i], excludeVector[i]);
	removeTestFile(optionFileName);
}

TEST(ProcessProjectOptions, Utf8BOM)
// test processOptions for fileOptionsVector with --project=###
// and with a UTF-8 BOM
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "\xEF\xBB\xBF"			// utf-8 bom
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");
	// write the options file
	string optionFileName = getTestDirectory() + "/astylerc.txt";
	console->standardizePath(optionFileName);
	if (!writeOptionsFile(optionFileName, fileIn))
		return;
	// build fileOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--project=astylerc.txt");
	optionsIn.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(optionsIn);
	// check projectOptionsVector
	vector<string> projectOptionsVector = console->getProjectOptionsVector();
	EXPECT_EQ(fileOptions.size(), projectOptionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < projectOptionsVector.size(); i++)
		EXPECT_EQ(fileOptions[i], projectOptionsVector[i]);
	removeTestFile(optionFileName);
}

TEST(ProcessProjectOptions, Utf16LE)
// test processOptions for fileOptionsVector with --project=###
// and with UTF-16LE BOM and encoding
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "\xEF\xBB\xBF"			// utf-8 bom to be converted
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");

	// convert options file to utf-16le
	ASEncoding encode;         // file encoding conversion from astyle
	ostringstream out;
	size_t utf16Size = encode.utf16LengthFromUtf8(fileIn, strlen(fileIn));
	// NOTE: do not use smart pointer here
	char* utf16Out = new (nothrow) char[utf16Size];
	if (utf16Out == nullptr)
		FAIL() << "Cannot allocate utf16Out";
	size_t utf16Len = encode.utf8ToUtf16(fileIn, strlen(fileIn), false, utf16Out);
	EXPECT_TRUE(utf16Len <= utf16Size) << "Bad conversion length.";

	// write the utf-16le options file
	string optionFileName = getTestDirectory() + "/astylerc.txt";
	console->standardizePath(optionFileName);
	ofstream fout(optionFileName.c_str(), ios::binary | ios::trunc);
	fout << string(utf16Out, utf16Len);
	if (!fout)
	{
		systemPause("Cannot write options test file: " + optionFileName);
		return;
	}
	fout.close();

	// build fileOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--project=astylerc.txt");
	optionsIn.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(optionsIn);
	// check projectOptionsVector
	vector<string> projectOptionsVector = console->getProjectOptionsVector();
	EXPECT_EQ(fileOptions.size(), projectOptionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < projectOptionsVector.size(); i++)
		EXPECT_EQ(fileOptions[i], projectOptionsVector[i]);
	removeTestFile(optionFileName);
	delete[] utf16Out;
}

TEST(ProcessProjectOptions, Utf16BE)
// test processOptions for fileOptionsVector with --project=###
// and with UTF-16BE BOM and encoding
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	char fileIn[] =
	    "\xEF\xBB\xBF"			// utf-8 bom to be converted
	    "--style=allman\n"
	    "-OoP\n"
	    "--indent-classes\n";
	vector<string> fileOptions;
	fileOptions.push_back("--style=allman");
	fileOptions.push_back("-OoP");
	fileOptions.push_back("--indent-classes");

	// convert options file to utf-16be
	ASEncoding encode;         // file encoding conversion from astyle
	ostringstream out;
	size_t utf16Size = encode.utf16LengthFromUtf8(fileIn, strlen(fileIn));
	// NOTE: do not use smart pointer here
	char* utf16Out = new (nothrow) char[utf16Size];
	if (utf16Out == nullptr)
		FAIL() << "Cannot allocate utf16Out";
	size_t utf16Len = encode.utf8ToUtf16(fileIn, strlen(fileIn), true, utf16Out);
	EXPECT_TRUE(utf16Len <= utf16Size) << "Bad conversion length.";

	// write the utf-16be options file
	string optionFileName = getTestDirectory() + "/astylerc.txt";
	console->standardizePath(optionFileName);
	ofstream fout(optionFileName.c_str(), ios::binary | ios::trunc);
	fout << string(utf16Out, utf16Len);
	if (!fout)
	{
		systemPause("Cannot write options test file: " + optionFileName);
		return;
	}
	fout.close();

	// build fileOptionsVector
	vector<string> optionsIn;
	optionsIn.push_back("--project=astylerc.txt");
	optionsIn.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(optionsIn);
	// check projectOptionsVector
	vector<string> projectOptionsVector = console->getProjectOptionsVector();
	EXPECT_EQ(fileOptions.size(), projectOptionsVector.size()) << "Vector sizes not equal.";
	for (size_t i = 0; i < projectOptionsVector.size(); i++)
		EXPECT_EQ(fileOptions[i], projectOptionsVector[i]);
	removeTestFile(optionFileName);
	delete[] utf16Out;
}

//----------------------------------------------------------------------------
// AStyle getTargetFilenames for recursive and wildcard processing
//----------------------------------------------------------------------------

TEST(GetTargetFilenames, One)
{
	// test getTargetFilenames with one file
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	vector<string> targetFilenameVector;
	string targetFilename = "*.cpp";
	console->getTargetFilenames(targetFilename, targetFilenameVector);
	ASSERT_EQ(1U, targetFilenameVector.size());
	EXPECT_EQ("*.cpp", targetFilenameVector[0]);
}

TEST(GetTargetFilenames, OneWithSpaces)
{
	// test getTargetFilenames with one file and spaces
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	vector<string> targetFilenameVector;
	string targetFilename = "  *.cpp  ";
	console->getTargetFilenames(targetFilename, targetFilenameVector);
	ASSERT_EQ(1U, targetFilenameVector.size());
	EXPECT_EQ("*.cpp", targetFilenameVector[0]);
}

TEST(GetTargetFilenames, ThreeWithSpaces)
{
	// test getTargetFilenames with three files and spaces
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	vector<string> targetFilenameVector;
	string targetFilename = " *.cpp,*.h  ,  *.cs ";
	console->getTargetFilenames(targetFilename, targetFilenameVector);
	ASSERT_EQ(3U, targetFilenameVector.size());
	EXPECT_EQ("*.cpp", targetFilenameVector[0]);
	EXPECT_EQ("*.h",   targetFilenameVector[1]);
	EXPECT_EQ("*.cs",  targetFilenameVector[2]);
}

TEST(GetTargetFilenames, None)
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	vector<string> targetFilenameVector;
	string targetFilename = " , ,, ";
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	string regex = "Missing filename in  , ,, ";
	EXPECT_EXIT(console->getTargetFilenames(targetFilename, targetFilenameVector),
	            ExitedWithCode(EXIT_FAILURE),
	            regex);
#endif
}

//----------------------------------------------------------------------------
// AStyle file suffix option
//----------------------------------------------------------------------------

struct FileSuffixF : public Test
{
	ASFormatter formatter;
	ASConsole* console;
	vector<string> fileNames;

	// build fileNames vector and write the output files
	FileSuffixF()
	{
		char textIn[] =
		    "\nvoid foo()\n"
		    "{\n"
		    "bar();\n"
		    "}\n";
		cleanTestDirectory(getTestDirectory());
		console = new ASConsole(formatter);
		fileNames.push_back(getTestDirectory() + "/suffix1.cpp");
		for (size_t i = 0; i < fileNames.size(); i++)
		{
			console->standardizePath(fileNames[i]);
			createTestFile(fileNames[i], textIn);
		}
	}

	~FileSuffixF()
	{
		delete console;
	}
};

TEST_F(FileSuffixF, None)
// test suffix=none option on files
{
	ASSERT_TRUE(console != nullptr) << "Console object not initialized.";
	// initialize variables
	console->setIsQuiet(true);		// change this to see results
	console->setNoBackup(true);		// test variable
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// call astyle processFiles()
	console->processFiles();
	// all files should be formatted
	ASSERT_EQ((int) fileNames.size(), console->getFilesFormatted());
	// check for .orig file on disk
	for (size_t i = 0; i < fileNames.size(); i++)
	{
		string origFileName = fileNames[0] + ".orig";
		struct stat stBuf;
		// display error if file is present
		if (stat(origFileName.c_str(), &stBuf) != -1)
			EXPECT_STREQ("no .orig file", origFileName.c_str());
	}
}

TEST_F(FileSuffixF, DotOld)
// test suffix=.old option on files (with dot)
{
	ASSERT_TRUE(console != nullptr) << "Console object not initialized.";
	// initialize variables
	console->setIsQuiet(true);		// change this to see results
	console->setOrigSuffix(".old"); 	// test variable (with dot)
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// call astyle processFiles()
	console->processFiles();
	// all files should be formatted
	EXPECT_TRUE(fileNames.size() > 0);
	ASSERT_EQ((int) fileNames.size(), console->getFilesFormatted());
	// check for .old file on disk
	for (size_t i = 0; i < fileNames.size(); i++)
	{
		string origFileName = fileNames[0] + ".old";
		struct stat stBuf;
		// display error if file is not present
		if (stat(origFileName.c_str(), &stBuf) == -1)
			EXPECT_STREQ("no .orig file", origFileName.c_str());
	}
}

TEST_F(FileSuffixF, SansDot)
// test suffix=xxx option on files (no dot)
{
	ASSERT_TRUE(console != nullptr) << "Console object not initialized.";
	// initialize variables
	console->setIsQuiet(true);		// change this to see results
	console->setOrigSuffix("xxx"); 	// test variable (no dot)
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// call astyle processFiles()
	console->processFiles();
	// all files should be formatted
	EXPECT_TRUE(fileNames.size() > 0);
	ASSERT_EQ((int) fileNames.size(), console->getFilesFormatted());
	// check for xxx file on disk
	for (size_t i = 0; i < fileNames.size(); i++)
	{
		string origFileName = fileNames[0] + "xxx";
		struct stat stBuf;
		// display error if file is not present
		if (stat(origFileName.c_str(), &stBuf) == -1)
			EXPECT_STREQ("no .orig file", origFileName.c_str());
	}
}

//----------------------------------------------------------------------------
// AStyle stringEndsWith function
//----------------------------------------------------------------------------

TEST(StringEndsWith, FileExtension_True)
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	bool result1 = console->stringEndsWith("fileName.cpp", string(".cpp"));
	EXPECT_TRUE(result1);
}

TEST(StringEndsWith, FileExtension_False)
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	bool result2 = console->stringEndsWith("fileName.cpp", string(".xxx"));
	EXPECT_FALSE(result2);
}

TEST(StringEndsWith, SansFileExtension)
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	bool result3 = console->stringEndsWith("fileNamenoextension", string("noextension"));
	EXPECT_TRUE(result3);
}

TEST(StringEndsWith, WholeName)
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	bool result4 = console->stringEndsWith("wholename", string("wholename"));
	EXPECT_TRUE(result4);
}

TEST(StringEndsWith, TestLongerThanName)
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	bool result5 = console->stringEndsWith("long", string("xlong"));
	EXPECT_FALSE(result5);
}

//----------------------------------------------------------------------------
// AStyle preserve-date option
//----------------------------------------------------------------------------

struct PreserveDateF : public Test
{
	ASFormatter formatter;
	ASConsole* console;
	vector<string> fileNames;
	struct utimbuf ut;

	// build fileNames vector and write the output files with an old date
	PreserveDateF()
	{
		char textIn[] =
		    "\nvoid foo()\n"
		    "{\n"
		    "bar();\n"
		    "}\n";
		struct tm t;
#ifdef _WIN32
		// Sat Jan 01 2000
		t.tm_sec   = 0;
		t.tm_min   = 0;
		t.tm_hour  = 8;		// 8 AM, or 7 AM if daylight savings
		t.tm_mday  = 1;		// day of the month	1-31
		t.tm_mon   = 0;		// month 0-11
		t.tm_year  = 100;	// years since 1900
		t.tm_wday  = 6;		// day of the week 0-6
		t.tm_yday  = 0;		// day of the year 0-365
		t.tm_isdst = 0;		// daylight savings time (not used?)
#else
		strptime("2000-01-01 08:00:00", "%Y-%m-%d %H:%M:%S", &t);
#endif
		ut.actime = ut.modtime = mktime(&t);
		cleanTestDirectory(getTestDirectory());
		console = new ASConsole(formatter);
		fileNames.push_back(getTestDirectory() + "/PreserveDate1.cpp");
		fileNames.push_back(getTestDirectory() + "/PreserveDate2.cpp");
		// write files and change the date
		for (size_t i = 0; i < fileNames.size(); i++)
		{
			console->standardizePath(fileNames[i]);
			createTestFile(fileNames[i], textIn);
			utime(fileNames[i].c_str(), &ut);
		}
	}

	~PreserveDateF()
	{
		delete console;
	}

	// get the date from time_t
	string getMDY(time_t dateIn)
	{
		string date = ctime(&dateIn);
		string dateMDY = date.erase(11, 9);	// remove the time
		if (dateMDY[8] == ' ')
			dateMDY[8] = '0';
		// cout << dateMDY << endl;
		return dateMDY;
	}
};

TEST_F(PreserveDateF, True)
// test formatting with preserve-date option
{
	ASSERT_TRUE(console != nullptr) << "Console object not initialized.";
	console->setIsQuiet(true);		// change this to see results
	console->setNoBackup(true);
	console->setPreserveDate(true);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// call astyle processFiles()
	console->processFiles();
	// loop thru fileNames vector checking the dates
	struct stat s;
	for (size_t i = 0; i < fileNames.size(); i++)
	{
		stat(fileNames[i].c_str(), &s);
		string fileMDY = getMDY(s.st_mtime);
		EXPECT_EQ("Sat Jan 01 2000\n", fileMDY);
#ifndef _MSC_VER
		// visual studio has a problem with daylight savings time!
		EXPECT_EQ(10, difftime(s.st_mtime, ut.modtime));
#endif
	}
}

TEST_F(PreserveDateF, False)
// test formatting without preserve-date option
{
	ASSERT_TRUE(console != nullptr) << "Console object not initialized.";
	console->setIsQuiet(true);		// change this to see results
	console->setNoBackup(true);
	console->setPreserveDate(false);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// call astyle processFiles()
	console->processFiles();
	// loop thru fileNames vector checking the dates
	string currMDY = getMDY(time(nullptr));
	struct stat s;
	for (size_t i = 0; i < fileNames.size(); i++)
	{
		stat(fileNames[i].c_str(), &s);
		string fileMDY = getMDY(s.st_mtime);
		EXPECT_EQ(currMDY, fileMDY);
	}
}

//----------------------------------------------------------------------------
// AStyle checksum procedure
//----------------------------------------------------------------------------

struct ChecksumF : public Test
{
	ASFormatter formatter;
	ASConsole* console;
	string fileName;
	size_t textChecksum;

	// build fileNames vector and write the output file
	ChecksumF()
	{
		textChecksum = 9699;
		char textIn[] =
		    "\n#include <stdio.h>\n"
		    "\n"
		    "void foo(int a)\n"
		    "{\n"
		    "    int i = 10;\n"
		    "    int i2 = 12;\n"
		    "    int i3 = i + i2;\n"
		    "    printf(\"i3 = %d\", i3);\n"
		    "    // for add-brackets test\n"
		    "    if (a == 0)\n"
		    "        x = 0;\n"
		    "}";
		cleanTestDirectory(getTestDirectory());
		console = new ASConsole(formatter);
		fileName = getTestDirectory() + "/Checksum.cpp";
		createTestFile(fileName, textIn);
	}

	~ChecksumF()
	{
		delete console;
	}
};

TEST_F(ChecksumF, NoAdds)
// test checksum procedure
{
	ASSERT_TRUE(console != nullptr) << "Console object not initialized.";
	console->setIsQuiet(true);		// change this to see results
	console->setNoBackup(true);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// call astyle processFiles()
	console->processFiles();
	// verify the checksums
	size_t checksumIn = formatter.getChecksumIn();
	size_t checksumOut = formatter.getChecksumOut();
#ifdef NDEBUG
	EXPECT_EQ(checksumIn, 0U);
	EXPECT_EQ(checksumOut, 0U);
#else
	EXPECT_EQ(checksumIn, textChecksum);
	EXPECT_EQ(checksumOut, textChecksum);
#endif
	EXPECT_TRUE(formatter.getChecksumDiff() == 0);
}

TEST_F(ChecksumF, AddBraces)
// test checksum procedure with add-braces
{
	ASSERT_TRUE(console != nullptr) << "Console object not initialized.";
	console->setIsQuiet(true);		// change this to see results
	console->setNoBackup(true);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back("--add-braces");
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// call astyle processFiles()
	console->processFiles();
	// verify the checksums
	textChecksum += '{' + '}';
	size_t checksumIn = formatter.getChecksumIn();
	size_t checksumOut = formatter.getChecksumOut();
#ifdef NDEBUG
	EXPECT_EQ(checksumIn, 0U);
	EXPECT_EQ(checksumOut, 0U);
#else
	EXPECT_EQ(checksumIn, textChecksum);
	EXPECT_EQ(checksumOut, textChecksum);
#endif
	EXPECT_TRUE(formatter.getChecksumDiff() == 0);
}

TEST_F(ChecksumF, AddOneLineBraces)
// test checksum procedure with add-one-line-braces
{
	ASSERT_TRUE(console != nullptr) << "Console object not initialized.";
	console->setIsQuiet(true);		// change this to see results
	console->setNoBackup(true);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back("--add-one-line-braces");
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// call astyle processFiles()
	console->processFiles();
	// verify the checksums
	textChecksum += '{' + '}';
	size_t checksumIn = formatter.getChecksumIn();
	size_t checksumOut = formatter.getChecksumOut();
#ifdef NDEBUG
	EXPECT_EQ(checksumIn, 0U);
	EXPECT_EQ(checksumOut, 0U);
#else
	EXPECT_EQ(checksumIn, textChecksum);
	EXPECT_EQ(checksumOut, textChecksum);
#endif
	EXPECT_TRUE(formatter.getChecksumDiff() == 0);
}

TEST(Checksum, CheckSumError)
// Test with --break-blocks and --delete-empty-lines and missing closing bracket
// Caused a checksum assert failure. This must be run in debug configuration.
{
	char textIn[] =
	    // this file is missing a closing bracket
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isBar)\n"
	    "        fooBar1();\n"
	    "\n"
	    "    fooBar2();\n";
	// initialization
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	console->setIsQuiet(true);		// change this to see results
	console->setNoBackup(true);
	// write test file
	cleanTestDirectory(getTestDirectory());
	string fileNames = getTestDirectory() + "/file1.cpp";
	console->standardizePath(fileNames);
	createTestFile(fileNames, textIn);
	// set the formatter options
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	astyleOptionsVector.push_back("--break-blocks");
	astyleOptionsVector.push_back("--delete-empty-lines");
	// call astyle processFiles()
	console->processOptions(astyleOptionsVector);
	console->processFiles();
	// Will actually get an assert error in astyle_main.cpp if this is not true.
	EXPECT_TRUE(formatter.getChecksumDiff() == 0);
}

//----------------------------------------------------------------------------
// AStyle ASResource operator vectors sequence
//----------------------------------------------------------------------------

TEST(OperatorVectorSequence, BuildOperators)
// check the sequence of ASResource::buildOperators
{
	// build the operators vector
	ASResource resource;
	vector<const string*> operators;
	resource.buildOperators(&operators, C_TYPE);
	// test the operators vector sequence
	// vector sequence is descending length of the operators
	size_t prevOperatorLength = 9;
	for (size_t i = 0; i < operators.size(); i++)
	{
		EXPECT_TRUE(prevOperatorLength >= (*operators[i]).length());
		prevOperatorLength = (*operators[i]).length();
	}
}

TEST(OperatorVectorSequence, BuildAssignmentOperators)
// check the sequence of ASResource::buildAssignmentOperators
{
	// build the assignmentOperators vector
	ASResource resource;
	vector<const string*> assignmentOperators;
	resource.buildAssignmentOperators(&assignmentOperators);
	// test the assignmentOperators vector sequence
	// vector sequence is descending length of the operators
	size_t prevOperatorLength = 9;
	for (size_t i = 0; i < assignmentOperators.size(); i++)
	{
		EXPECT_TRUE(prevOperatorLength >= (*assignmentOperators[i]).length());
		prevOperatorLength = (*assignmentOperators[i]).length();
	}
}

TEST(OperatorVectorSequence, BuildNonAssignmentOperators)
// check the sequence of ASResource::buildNonAssignmentOperators
{
	// build the nonAssignmentOperators vector
	ASResource resource;
	vector<const string*> nonAssignmentOperators;
	resource.buildNonAssignmentOperators(&nonAssignmentOperators);
	// test the nonAssignmentOperators vector sequence
	// vector sequence is descending length of the operators
	size_t prevOperatorLength = 9;
	for (size_t i = 0; i < nonAssignmentOperators.size(); i++)
	{
		EXPECT_TRUE(prevOperatorLength >= (*nonAssignmentOperators[i]).length());
		prevOperatorLength = (*nonAssignmentOperators[i]).length();
	}
}

//----------------------------------------------------------------------------
// AStyle ASResource header vectors sequence
//----------------------------------------------------------------------------

TEST(HeaderVectorSequence, BuildCastOperators)
// check the sequence of ASResource::buildCastOperators
{
	// build the castOperators vector
	ASResource resource;
	vector<const string*> castOperators;
	resource.buildCastOperators(&castOperators);
	// test the castOperators vector sequence
	// vector sequence is ascending header value
	string prevHeader;
	for (size_t i = 0; i < castOperators.size(); i++)
	{
		EXPECT_TRUE(prevHeader < (*castOperators[i]));
		prevHeader = (*castOperators[i]);
	}
}

TEST(HeaderVectorSequence, BuildHeaders)
// check the sequence of ASResource::buildHeaders
{
	// build the headers vector
	ASResource resource;
	vector<const string*> headers;
	resource.buildHeaders(&headers, SHARP_TYPE, true);
	// test the headers vector sequence
	// vector sequence is ascending header value
	string prevHeader;
	for (size_t i = 0; i < headers.size(); i++)
	{
		EXPECT_TRUE(prevHeader < (*headers[i]));
		prevHeader = (*headers[i]);
	}
}

TEST(HeaderVectorSequence, BuildIndentableHeaders)
// check the sequence of ASResource::buildIndentableHeaders
{
	// build the indentableHeaders vector
	ASResource resource;
	vector<const string*> indentableHeaders;
	resource.buildIndentableHeaders(&indentableHeaders);
	// test the indentableHeaders vector sequence
	// vector sequence is ascending header value
	string prevHeader;
	for (size_t i = 0; i < indentableHeaders.size(); i++)
	{
		EXPECT_TRUE(prevHeader < (*indentableHeaders[i]));
		prevHeader = (*indentableHeaders[i]);
	}
}

TEST(HeaderVectorSequence, BuildNonParenHeaders)
// check the sequence of ASResource::buildNonParenHeaders
{
	// build the nonParenHeaders vector
	ASResource resource;
	vector<const string*> nonParenHeaders;
	resource.buildNonParenHeaders(&nonParenHeaders, SHARP_TYPE, true);
	// test the nonParenHeaders vector sequence
	// vector sequence is ascending header value
	string prevHeader;
	for (size_t i = 0; i < nonParenHeaders.size(); i++)
	{
		EXPECT_TRUE(prevHeader < (*nonParenHeaders[i]));
		prevHeader = (*nonParenHeaders[i]);
	}
}

TEST(HeaderVectorSequence, BuildPreBlockStatements)
// check the sequence of ASResource::buildPreBlockStatements
{
	// build the preBlockStatements vector
	ASResource resource;
	vector<const string*> preBlockStatements;
	resource.buildPreBlockStatements(&preBlockStatements, SHARP_TYPE);
	// test the preBlockStatements vector sequence
	// vector sequence is ascending header value
	string prevHeader;
	for (size_t i = 0; i < preBlockStatements.size(); i++)
	{
		EXPECT_TRUE(prevHeader < (*preBlockStatements[i]));
		prevHeader = (*preBlockStatements[i]);
	}
}

TEST(HeaderVectorSequence, BuildPreCommandHeaders)
// check the sequence of ASResource::buildPreCommandHeaders
{
	// build the preCommandHeaders vector
	ASResource resource;
	vector<const string*> preCommandHeaders;
	resource.buildPreCommandHeaders(&preCommandHeaders, SHARP_TYPE);
	// test the preCommandHeaders vector sequence
	// vector sequence is ascending header value
	string prevHeader;
	for (size_t i = 0; i < preCommandHeaders.size(); i++)
	{
		EXPECT_TRUE(prevHeader < (*preCommandHeaders[i]));
		prevHeader = (*preCommandHeaders[i]);
	}
}

TEST(HeaderVectorSequence, BuildPreDefinitionHeaders)
// check the sequence of ASResource::buildPreDefinitionHeaders
{
	// build the preDefinitionHeaders vector
	ASResource resource;
	vector<const string*> preDefinitionHeaders;
	resource.buildPreDefinitionHeaders(&preDefinitionHeaders, SHARP_TYPE);
	// test the preDefinitionHeaders vector sequence
	// vector sequence is ascending header value
	string prevHeader;
	for (size_t i = 0; i < preDefinitionHeaders.size(); i++)
	{
		EXPECT_TRUE(prevHeader < (*preDefinitionHeaders[i]));
		prevHeader = (*preDefinitionHeaders[i]);
	}
}

//----------------------------------------------------------------------------
// AStyle Disable Formatting
//----------------------------------------------------------------------------

struct DisableFormattingF : public Test
{
	ASFormatter formatter;
	ASConsole* console;

	DisableFormattingF()
	{
		cleanTestDirectory(getTestDirectory());
		console = new ASConsole(formatter);
	}

	~DisableFormattingF()
	{
		delete console;
	}
};

TEST_F(DisableFormattingF, Unchanged)
// test disable formatting with an unchanged file
{
	ASSERT_TRUE(console != nullptr) << "Console object not initialized.";
	console->setIsQuiet(true);		// change this to see results
	console->setNoBackup(true);
	// create test file
	char text[] =
	    "\n// disable formatting unchanged\n"
	    "/*INDENT-OFF*/\n"
	    "#ifdef _WIN32\n"
	    "       #define STDCALL __stdcall\n"
	    "#endif\n"
	    "/*INDENT-ON*/\n";
	string fileName = getTestDirectory() + "/DisableFormatting.cpp";
	console->standardizePath(fileName);
	createTestFile(fileName, text);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// call astyle processFiles()
	console->processFiles();
	// check for file not formatted
	EXPECT_TRUE(console->getFilesAreIdentical());
}

TEST_F(DisableFormattingF, Formatted)
// test disable formatting with a formatted file
{
	ASSERT_TRUE(console != nullptr) << "Console object not initialized.";
	console->setIsQuiet(true);		// change this to see results
	console->setNoBackup(true);
	// create test file - the first line will be unindented
	char text[] =
	    "\n    // disable formatting formatted\n"
	    "/*INDENT-OFF*/\n"
	    "#ifdef _WIN32\n"
	    "       #define STDCALL __stdcall\n"
	    "#endif\n"
	    "/*INDENT-ON*/\n";
	string fileName = getTestDirectory() + "/DisableFormatting.cpp";
	console->standardizePath(fileName);
	createTestFile(fileName, text);
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	console->processOptions(astyleOptionsVector);
	// call astyle processFiles()
	console->processFiles();
	// check for file formatted
	EXPECT_FALSE(console->getFilesAreIdentical());
}

//----------------------------------------------------------------------------
// AStyle Removed Options release 2.02
//----------------------------------------------------------------------------

TEST(RemovedOptions, V202)
// test that removed options are rejected with a message
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--brackets=horstmann");
	optionsIn.push_back("--indent-brackets");
	optionsIn.push_back("--indent-blocks");
	optionsIn.push_back("-B");
	optionsIn.push_back("-G");
	// this is NOT a removed option
	optionsIn.push_back("--ascii");
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions with invalid command line options
	EXPECT_EXIT(console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_FAILURE),
	            "Invalid command line options:\n"
	            "\tbrackets=horstmann\n"
	            "\tindent-brackets\n"
	            "\tindent-blocks\n"
	            "\tB\n"
	            "\tG\n");
#endif
}

TEST(RemovedOptions, V204)
// test that removed options are rejected with a message
{
	ASFormatter formatter;
	unique_ptr<ASConsole> console(new ASConsole(formatter));
	// build optionsIn
	vector<string> optionsIn;
	optionsIn.push_back("--brackets=attach");
	optionsIn.push_back("--brackets=break");
	optionsIn.push_back("--brackets=run-in");
	optionsIn.push_back("--brackets=linux");
	optionsIn.push_back("--brackets=stroustrup");
	optionsIn.push_back("-a");
	optionsIn.push_back("-b");
	optionsIn.push_back("-g");
	optionsIn.push_back("-l");
	optionsIn.push_back("-u");
	// this is NOT a removed option
	optionsIn.push_back("--ascii");
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	// test processOptions with invalid command line options
	EXPECT_EXIT(console->processOptions(optionsIn),
	            ExitedWithCode(EXIT_FAILURE),
	            "\tbrackets=attach\n"
	            "\tbrackets=break\n"
	            "\tbrackets=run-in\n"
	            "\tbrackets=linux\n"
	            "\tbrackets=stroustrup\n"
	            "\ta\n"
	            "\tb\n"
	            "\tg\n"
	            "\tl\n"
	            "\tu\n");
#endif
}

//----------------------------------------------------------------------------

}  // namespace
