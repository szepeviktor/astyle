// AStyleTestCon tests the ASConsole class only. This class is used only in
// the console build. It also tests the parseOption function for options used
// by only by the console build (e.g. recursive, preserve-date, verbose). It
// does not explicitely test the ASStreamIterator class or any other part
// of the program.

#ifndef ASTYLE_TESTCON_H
#define ASTYLE_TESTCON_H

//-------------------------------------------------------------------------
// headers
//-------------------------------------------------------------------------

#include "astyle_main.h"
#include "gtest/gtest.h"

#include <stdlib.h>
#include <fstream>
#include <errno.h>

using namespace astyle;
using namespace testing;

//-------------------------------------------------------------------------
// extern global variables in astyle_main.cpp
//-------------------------------------------------------------------------

// global variables in astyle_main.cpp
// NOTE: the Embarcadero compiler needs the astyle:: qualifier for some reason
namespace astyle {
extern astyle::ASConsole* g_console;
extern ostream* _err;
}

//-------------------------------------------------------------------------
// declarations
//-------------------------------------------------------------------------

// functions in AStyleTestCon_Main.cpp
// char** buildArgv(const vector<string>& argIn);
void cleanTestDirectory(const string& directory);
wstring convertToWideChar(const string& mbStr);
void createConsoleGlobalObject(ASFormatter& formatter);
void createTestDirectory(const string& dirName);
void createTestFile(const string& testFilePath, const char* testFileText, int size = 0);
void deleteConsoleGlobalObject();
string getCurrentDirectory();
string getDefaultOptionsFilePath();
string& getTestDirectory();
void printI18nMessage();
void removeTestDirectory(const string& dirName);
void removeTestFile(const string& testFileName);
void renameDefaultOptionsFile();
void restoreDefaultOptionsFile();
void setTestDirectory();
void systemAbort(const string& message);
void systemPause();
void systemPause(const string& message);
bool writeOptionsFile(const string& optionsFileName, const char* fileIn);

// windows specific functions
#ifdef _WIN32
	void cleanTestDirectory(const wstring& directory);
	void displayLastError();
	void retryCreateDirectory(const string& directory);
	void retryRemoveDirectory(const wstring& directory);
	void sleep(int seconds);
	void systemAbort(const wstring& message);
#endif

//-------------------------------------------------------------------------

#endif // closes ASTYLE_TESTCON_H
