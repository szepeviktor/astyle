#ifndef ASTYLE_TEST_H
#define ASTYLE_TEST_H

//-------------------------------------------------------------------------
// headers
//-------------------------------------------------------------------------
// NOTE: astyle.h is NOT included to prevent recompiling all of the
// test source files when changes are made to the astyle.h header.

#include <gtest/gtest.h>
#include <stdlib.h>
#include <iostream>		// for cout
#include <string.h>		// need both string and string.h for GCC
#include <string>

using namespace std;
using namespace testing;

//-------------------------------------------------------------------------
// definitions
//-------------------------------------------------------------------------

// define STDCALL for Windows
// MINGW defines STDCALL in Windows.h (actually windef.h)
#ifdef _WIN32
#ifndef STDCALL
#define STDCALL __stdcall
#endif
// define STDCALL for non-Windows
#else
#define STDCALL
#endif	// #ifdef _WIN32

//-----------------------------------------------------------------------------
// declarations for AStyleMain library build
//-----------------------------------------------------------------------------

typedef void (STDCALL* fpError)(int, const char*);      // pointer to callback error handler
typedef char* (STDCALL* fpAlloc)(unsigned long);		// pointer to callback memory allocation
extern "C" char* STDCALL AStyleMain(const char*, const char*, fpError, fpAlloc);
extern "C" const char* STDCALL AStyleGetVersion (void);

//-----------------------------------------------------------------------------
// declarations for AStyleMainUtf16 library build
//-----------------------------------------------------------------------------

extern "C" wchar_t* STDCALL AStyleMainUtf16(const wchar_t*, const wchar_t*, fpError, fpAlloc);

//-----------------------------------------------------------------------------
// declarations for AStyleTest callback functions
//-----------------------------------------------------------------------------

// AStyleMain callback function declarations
void  STDCALL errorHandler(int errorNumber, const char* errorMessage);
char* STDCALL memoryAlloc(unsigned long memoryNeeded);

// errorHandler2 functions
void  STDCALL errorHandler2(int, const char*);
int   getErrorHandler2Calls();

//-------------------------------------------------------------------------

#endif // closes ASTYLE_TEST_H
