#ifndef ASTYLE_TESTLIB_H
#define ASTYLE_TESTLIB_H

//-------------------------------------------------------------------------
// headers
//-------------------------------------------------------------------------
// NOTE: astyle.h is NOT included to prevent recompiling all of the
// test source files when changes are made to the astyle.h header.

#include <gtest/gtest.h>
#ifndef __BORLANDC__        // can't use gmock
#include "gmock/gmock.h"
#endif

// must be AFTER gmock.h
// use this to test the Linux compile with MinGW
#ifdef MINGW_LINUX
#undef _WIN32
#endif

#include <stdlib.h>
#include <iostream>		// for cout
#include <string.h>		// need both string and string.h for GCC
#include <string>

using namespace std;

//-------------------------------------------------------------------------
// definitions
//-------------------------------------------------------------------------

// define STDCALL and EXPORT for Windows
// MINGW defines STDCALL in Windows.h (actually windef.h)
// EXPORT has no value for Visual C if ASTYLE_NO_VCX (no VC Exports) is defined
//        this works with VS2012 and higher
#ifdef _WIN32
#ifndef STDCALL
#define STDCALL __stdcall
#endif
#if defined(_MSC_VER) && defined(ASTYLE_NO_VCX)
#define EXPORT
#else
#define EXPORT __declspec(dllexport)
#endif
// define STDCALL and EXPORT for non-Windows
#else
#define STDCALL
#define EXPORT
#endif	// #ifdef _WIN32

//-----------------------------------------------------------------------------
// declarations for AStyleMain library build
//-----------------------------------------------------------------------------

typedef void (STDCALL* fpError)(int, const char*);      // pointer to callback error handler
typedef char* (STDCALL* fpAlloc)(unsigned long);		// pointer to callback memory allocation
extern "C" EXPORT char* STDCALL AStyleMain(const char*, const char*, fpError, fpAlloc);
extern "C" EXPORT const char* STDCALL AStyleGetVersion (void);

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

#endif // closes ASTYLE_TESTLIB_H
