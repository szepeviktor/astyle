// Main_Test.h
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

#ifndef _MAIN_TEST_H_
#define _MAIN_TEST_H_

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

// disable warnings in wxWidgets headers
#ifdef _MSC_VER
	#pragma warning(disable: 4996)  // secure version deprecation warnings
#endif

#include <iostream>         // for cout
#include <wx/string.h>
#include <sstream>

//-----------------------------------------------------------------------------
// Global definitions
//-----------------------------------------------------------------------------

int  ShowMessageDialog(const wxString& message, long style);

//-----------------------------------------------------------------------------
// ConsoleRedirect class
//-----------------------------------------------------------------------------

class ConsoleRedirect
// Makes the console output available as a wxString.
{
public:
	ConsoleRedirect()
	{ m_oldBuffer = std::wcout.rdbuf(m_buffer.rdbuf()); }

	virtual ~ConsoleRedirect()
	{ std::wcout.rdbuf(m_oldBuffer); }

	wxString GetMessages()
	{ return m_buffer.str(); }

private:
	std::wstringstream m_buffer;
	std::wstreambuf* m_oldBuffer;
};

//----------------------------------------------------------------------------

#endif  // _MAIN_TEST_H_
