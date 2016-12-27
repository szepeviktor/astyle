// AStyleTestLib.h
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.txt describes the conditions under which this software may be distributed.

#ifndef ASTYLE_TESTLIB_H
#define ASTYLE_TESTLIB_H

//-------------------------------------------------------------------------
// headers
//-------------------------------------------------------------------------

#include "gmock/gmock.h"
#include "gtest/gtest.h"
// for gmock macros
using namespace testing;

// must be AFTER gmock.h
// use this to test the Linux compile with MinGW
#ifdef MINGW_LINUX
	#undef _WIN32
#endif

#include <stdlib.h>
#include <iostream>		// for cout
#include <string.h>		// need both string and string.h for GCC
#include <string>

//-----------------------------------------------------------------------------
// definitions
//-----------------------------------------------------------------------------

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
