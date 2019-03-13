// AStyleFormat.h
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

#ifndef _ASTYLEFORMAT_H_
#define _ASTYLEFORMAT_H_

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#include <wx/msgdlg.h>
#include <wx/stc/stc.h>		// wxStyledTextCtrl
#ifdef ASTYLE_DYLIB
	#include <wx/dynlib.h>
#endif

#ifdef __clang__
	#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#endif

//-----------------------------------------------------------------------------
// definitions
//-----------------------------------------------------------------------------

// allow for different calling conventions in Linux and Windows
#ifdef __WXMSW__
	#define STDCALL __stdcall
#else
	#define STDCALL
#endif

#ifdef ASTYLE_DYLIB
// define function pointer types for convenience
// pointer to AStyleMain()
#define DECLARE_fpASMAIN typedef char* (STDCALL *fpASMain)(const char*, \
                                                           const char*, \
                                                           void(STDCALL *ErrorHandler)(int, const char*), \
                                                           char*(STDCALL *MemoryAlloc)(unsigned long));
// pointer to AStyleGetVersion()
#define	DECLARE_fpASVER typedef const char* (STDCALL *fpASVer)();
#endif	// ASTYLE_DYLIB

// external functions calls in Artistic Style shared or static library
extern "C"
{
	const char* STDCALL  AStyleGetVersion();
	char* STDCALL  AStyleMain(const char* textIn,
	                          const char* options,
	                          void(STDCALL* ErrorHandler)(int, const char*),
	                          char* (STDCALL* MemoryAlloc)(unsigned long));
}

//-----------------------------------------------------------------------------
// AStyleFormat Class
//-----------------------------------------------------------------------------

class AStyleFormat
{
public:
	friend class AStyleFormat_Test;

public:
	AStyleFormat();
	virtual ~AStyleFormat() = default;
	void FormatSource(wxStyledTextCtrl* stc, const wxString& optionsWx);
	void FormatSelection(wxStyledTextCtrl* stc, const wxString& optionsWx);
	wxString GetAStyleVersion() const;

private:
	virtual char* CallAStyleMain(const char* textIn, const char* options) const;	// mocked in tests
	char* FormatSTCText(const wxString& options) const;
	void InsertBookmarkMarkers(int bookmarkNumber, std::string& marker) const;
	void InsertFirstVisibleLineMarker() const;
	bool InsertFormattedText(const char* textOut);
	bool InsertSelectionMarkers();
	void RestoreBookmarks(int bookmarkNumber, std::string& marker) const;
	void RestoreFirstVisibleLine() const;
	bool RestoreSelection() const;
	// callback functions for Artistic Style
	static void  STDCALL ErrorHandler(int errorNumber, const char* errorMessage);
	static char* STDCALL MemoryAlloc(unsigned long memoryNeeded);

private:
	std::string m_firstLineMarker;
	std::string m_minSelectionMarker;
	std::string m_maxSelectionMarker;
	std::string m_bookmark1Marker;
	wxStyledTextCtrl* m_stc;
	bool m_selectionReversed;		// selected from max to min
	bool m_line0Inserted;

#ifdef ASTYLE_DYLIB
private:
	// wx dynamic library class
	// Data is static so the dynamic library can remain loaded
	// after the object is destroyed.

	// typedefs for AStyle function pointers
	DECLARE_fpASMAIN
	DECLARE_fpASVER

	static fpASMain fpAStyleMain;		// pointer to AStyleMain()
	static fpASVer fpAStyleGetVersion;	// pointer to AStyleGetVersion()

	static wxDynamicLibrary aslib;		// dynamic library object
	static wxDllType aslibHandle;		// dynamic library handle for unload

public:
	static wxString GetDynamicLibraryName();
	static void LoadDynamicLibrary();
	static void UnloadDynamicLibrary();

#endif
};

#endif  // _ASTYLEFORMAT_H_
