// AStyleFormat.cpp
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.txt describes the conditions under which this software may be distributed.

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include "AStyleFormat.h"

#ifdef __BORLANDC__
	#pragma warn -8004	// variable is assigned a value that is never used
#endif

//-----------------------------------------------------------------------------
// Global definitions
//-----------------------------------------------------------------------------

int  ShowMessageDialog(const wxString& message, long style);

//-----------------------------------------------------------------------------
// AStyleFormat class
//-----------------------------------------------------------------------------

AStyleFormat::AStyleFormat()
{
	// don't use '{' or '}' in the markers
	m_firstLineMarker    = "//]])>0";
	m_minSelectionMarker = "//]])>1";
	m_maxSelectionMarker = "//]])>2";
	m_bookmark1Marker	 = "//]])>3";
	m_stc = nullptr;
	m_selectionReversed = false;
	m_line0Inserted = false;
}

AStyleFormat::~AStyleFormat()
{
}

char* AStyleFormat::CallAStyleMain(const char* textIn, const char* options) const
{
#ifdef ASTYLE_DYLIB
	// format using dynamic library
	if (fpAStyleMain == nullptr)	// cannot use aslib.IsLoaded() after Detach()
	{
		ShowMessageDialog(wxString::Format(
		                      "Error calling the function AStyleMain.\n"
		                      "The AStyle library %s is not loaded.\n"
		                      "The text cannot be formatted.\n"
		                      "This must be corrected to format the text!",
		                      GetDynamicLibraryName().c_str()),
		                  wxOK | wxICON_ERROR);
		return nullptr;
	}

	char* textOut = fpAStyleMain(textIn,
	                             options,
	                             ErrorHandler,
	                             MemoryAlloc);
#else
	// format using static library
	char* textOut = AStyleMain(textIn,
	                           options,
	                           ErrorHandler,
	                           MemoryAlloc);
#endif	// ASTYLE_DYLIB
	return textOut;
}

void AStyleFormat::FormatSelection(wxStyledTextCtrl* stc, const wxString& optionsWx)
// Format the selected text in the styled text control.
{
	m_stc = stc;
	m_selectionReversed = false;
	m_line0Inserted = false;
	int xOffset = stc->GetXOffset();
	// flag reversed selection for restore
	if (m_stc->GetAnchor() > m_stc->GetCurrentPos())
		m_selectionReversed = true;
	// insert markers
	// selection markers MUST be FIRST or the selection will be removed
	stc->BeginUndoAction();
	if (!InsertSelectionMarkers())
		return;
	InsertFirstVisibleLineMarker();
	InsertBookmarkMarkers(1, m_bookmark1Marker);
	// format text
	char* textOut = FormatSTCText(optionsWx);
	if (textOut != nullptr)
		InsertFormattedText(textOut);
	delete [] textOut;
	textOut = nullptr;
	// restore viewing position
	// selection markers MUST be LAST or the selection will be removed
	RestoreBookmarks(1, m_bookmark1Marker);
	RestoreFirstVisibleLine();
	RestoreSelection();
	// restore the window
	stc->EndUndoAction();
	stc->SetXOffset(xOffset);
	m_stc = nullptr;
}

void AStyleFormat::FormatSource(wxStyledTextCtrl* stc, const wxString& optionsWx)
// Format the entire text in the styled text control.
{
	m_stc = stc;
	m_selectionReversed = false;
	m_line0Inserted = false;
	int xOffset = stc->GetXOffset();
	// check if text is selected
#ifdef NDEBUG
	int selMin = stc->GetSelectionStart();
	int selMax = stc->GetSelectionEnd();
	if (selMax - selMin > 4)	// allow slop
	{
		if (ShowMessageDialog("Do you want to format the entire source?",
		                      wxYES_NO  | wxICON_QUESTION) == wxID_NO)
			return;
	}
#endif
	// insert markers
	stc->BeginUndoAction();
	InsertFirstVisibleLineMarker();
	InsertBookmarkMarkers(1, m_bookmark1Marker);
	// format text
	char* textOut = FormatSTCText(optionsWx);
	if (textOut != nullptr)
		m_stc->SetTextRaw(textOut);
	delete [] textOut;
	textOut = nullptr;
	// restore viewing position
	RestoreBookmarks(1, m_bookmark1Marker);
	RestoreFirstVisibleLine();
	// restore the window
	stc->EndUndoAction();
	stc->SetXOffset(xOffset);
	m_stc = nullptr;
}

char* AStyleFormat::FormatSTCText(const wxString& options) const
// Call Artistic Style to format the text in the styled text control.
// The formatted text will be placed in the textOutWx string.
// textOutWx will be wxEmptyString if a error occurs.
{
	assert(m_stc != nullptr);
	// GetTextRaw avoids the unicode encoding conversions
	wxCharBuffer textInBuf = m_stc->GetTextRaw();
	char* textIn = textInBuf.data();
	char* textOut = CallAStyleMain(textIn, options.ToUTF8());
	return textOut;
}

wxString AStyleFormat::GetAStyleVersion() const
{
#ifdef ASTYLE_DYLIB
	if (fpAStyleGetVersion == nullptr)	// cannot use aslib.IsLoaded() after Detach()
	{
		ShowMessageDialog(wxString::Format(
		                      "Error calling the function AStyleGetVersion.\n"
		                      "The AStyle library %s is not loaded.\n"
		                      "The version cannot be obtained!",
		                      GetDynamicLibraryName().c_str()),
		                  wxOK | wxICON_ERROR);
		return "????";
	}

	const char* versionCStr = fpAStyleGetVersion();
	// convert the version to a unicode string
	wxString version = wxString(versionCStr, wxConvUTF8);
#else
	// get the version as a unicode string
	wxString version = wxString(AStyleGetVersion(), wxConvUTF8);
#endif	// ASTYLE_DYLIB
	return version;
}

void AStyleFormat::InsertBookmarkMarkers(int bookmarkNumber, std::string& marker) const
// Insert bookmark markers at the end of the line.
{
	assert(m_stc != nullptr);
	int lineStart = 0;
	int markerLine = m_stc->MarkerNext(lineStart, 1 << bookmarkNumber);
	while (markerLine >= 0)
	{
		int markerLineEOLPos = m_stc->GetLineEndPosition(markerLine);
		if (m_stc->GetCharAt(markerLineEOLPos - 1) == '*')		// don't create '*/'
			m_stc->InsertTextRaw(markerLineEOLPos, (' ' + marker).c_str());
		else
			m_stc->InsertTextRaw(markerLineEOLPos, marker.c_str());
		++markerLine;
		markerLine = m_stc->MarkerNext(markerLine, 1 << bookmarkNumber);
	}
}

void AStyleFormat::InsertFirstVisibleLineMarker() const
// Insert a first visible line marker at the end of the line.
{
	assert(m_stc != nullptr);
	int firstVisibleLine = m_stc->GetFirstVisibleLine();
	int firstVisibleLineEOLPos = m_stc->GetLineEndPosition(firstVisibleLine);
	if (m_stc->GetCharAt(firstVisibleLineEOLPos - 1) == '*')		// don't create '*/'
		m_stc->InsertTextRaw(firstVisibleLineEOLPos, (' ' + m_firstLineMarker).c_str());
	else
		m_stc->InsertTextRaw(firstVisibleLineEOLPos, m_firstLineMarker.c_str());
}

bool AStyleFormat::InsertFormattedText(const char* textOut)
// Insert the output selected formatted text into the original unformatted string.
{
	assert(m_stc != nullptr);
	// find formatted text in the formatted output string
	char* minOut = nullptr;
	char* maxOut = nullptr;
	minOut = strstr(const_cast<char*>(textOut), m_minSelectionMarker.c_str());
	if (minOut != nullptr)
		maxOut = strstr(minOut, m_maxSelectionMarker.c_str());
	if (minOut == nullptr || maxOut == nullptr)
	{
		ShowMessageDialog("Unable to find an output selection marker during replacement!\n"
		                  "The entire document will be replaced for debugging.",
		                  wxOK | wxICON_ERROR);
		m_stc->ClearAll();
		m_stc->SetTextRaw(textOut);
		return false;
	}
	// find original text in the styled text control
	int minSTC = -1;
	int maxSTC = -1;
	minSTC = m_stc->FindText(0, m_stc->GetTextLength(), m_minSelectionMarker, wxSTC_FIND_MATCHCASE);
	if (minSTC >= 0)
		maxSTC = m_stc->FindText(minSTC, m_stc->GetTextLength(), m_maxSelectionMarker, wxSTC_FIND_MATCHCASE);
	if (minSTC < 0 || maxSTC < 0)
	{
		ShowMessageDialog("Unable to find a STC selection marker during replacement!\n"
		                  "The document with markers will be retained for debugging.",
		                  wxOK | wxICON_ERROR);
		return false;
	}
	// replace the original selected text with the formatted text
	wxString selectedTextOut(minOut, wxConvUTF8, maxOut - minOut);
	m_stc->SetTargetStart(minSTC);
	m_stc->SetTargetEnd(maxSTC);
	m_stc->ReplaceTarget(selectedTextOut);
	return true;
}

bool AStyleFormat::InsertSelectionMarkers()
// Insert selection markers.
// Beginning marker at end of the PREVIOUS line.
// Ending marker at the end of the last selected line.
{
	assert(m_stc != nullptr);
	int selMin = m_stc->GetSelectionStart();
	int selMax = m_stc->GetSelectionEnd();
	if (selMax == selMin)
	{
		ShowMessageDialog("No text is selected, no text will be formatted!\n"
		                  "The selection may have been removed during processing.",
		                  wxOK | wxICON_ERROR);
		return false;
	}
	int minLine = m_stc->LineFromPosition(selMin);
	int maxLine = m_stc->LineFromPosition(selMax);
	// see if anything is actually selected on the last line
	int selMaxTest = m_stc->PositionFromLine(maxLine);
	if (selMax == selMaxTest)
		--maxLine;
	// insert max marker first so it's position doesn't change
	int selMaxLineEOLPos = m_stc->GetLineEndPosition(maxLine);
	if (m_stc->GetCharAt(selMaxLineEOLPos - 1) == '*')		// don't create '*/'
		m_stc->InsertTextRaw(selMaxLineEOLPos, (' ' + m_maxSelectionMarker).c_str());
	else
		m_stc->InsertTextRaw(selMaxLineEOLPos, m_maxSelectionMarker.c_str());
	// insert min marker at end of the PREVIOUS line
	if (minLine > 0)
	{
		int selMinLineEOLPos = m_stc->GetLineEndPosition(minLine - 1);
		if (m_stc->GetCharAt(selMinLineEOLPos - 1) == '*')		// don't create '*/'
			m_stc->InsertTextRaw(selMinLineEOLPos, (' ' + m_minSelectionMarker).c_str());
		else
			m_stc->InsertTextRaw(selMinLineEOLPos, m_minSelectionMarker.c_str());
	}
	else
	{
		// special handling for line 0
		int eolMode = m_stc->GetEOLMode();
		std::string eol;
		if (eolMode == wxSTC_EOL_CRLF)
			eol = "\r\n";
		else if (eolMode == wxSTC_EOL_LF)
			eol = "\n";
		else
			eol = "\r";
		// insert a new line 0 and flag
		m_stc->InsertTextRaw(0, (m_minSelectionMarker + eol).c_str());
		m_line0Inserted = true;
	}
	return true;
}

void AStyleFormat::RestoreBookmarks(int bookmarkNumber, std::string& marker) const
// Remove the bookmark markers and restore the bookmark positions.
{
	assert(m_stc != nullptr);
	int markerLine = 0;
	int markerPosition = m_stc->FindText(markerLine, m_stc->GetTextLength(), marker, wxSTC_FIND_MATCHCASE);
	while (markerPosition >= 0)
	{
		markerLine = m_stc->LineFromPosition(markerPosition);
		// there may be a marker after this
		int markerEnd = markerPosition + marker.length();
		// trim extra whitespace
		wxString whitespaceChars = " \t";
		while ((markerPosition > 0)
		        && (whitespaceChars.Find(static_cast<char>(m_stc->GetCharAt(markerPosition - 1))) != wxNOT_FOUND))
			--markerPosition;
		// remove the marker
		m_stc->SetTargetStart(markerPosition);
		m_stc->SetTargetEnd(markerEnd);
		m_stc->ReplaceTarget(wxEmptyString);
		// add the bookmark
		m_stc->MarkerAdd(markerLine, bookmarkNumber);
		// get next marker
		++markerLine;
		markerPosition = m_stc->FindText(markerLine, m_stc->GetTextLength(), marker, wxSTC_FIND_MATCHCASE);
	}
}

void AStyleFormat::RestoreFirstVisibleLine() const
// Remove the first visible line marker and restore the viewing position.
{
	assert(m_stc != nullptr);
	int firstVisibleLine = 0;
	int firstVisiblePosition = m_stc->FindText(0, m_stc->GetTextLength(), m_firstLineMarker, wxSTC_FIND_MATCHCASE);
	// TODO: fix this
	// formatting removes the beginning space in the marker
	if (firstVisiblePosition < 0)
	{
		wxString zeroPosText = ' ' + m_stc->GetTextRange(0, m_firstLineMarker.length() - 1);
		if (zeroPosText == m_firstLineMarker)
		{
			firstVisiblePosition = 0;
			m_stc->InsertTextRaw(0, " ");
		}
	}
	// end of fix
	if (firstVisiblePosition >= 0)
	{
		firstVisibleLine = m_stc->LineFromPosition(firstVisiblePosition);
		// there may be a marker after this
		int markerEnd = firstVisiblePosition + m_firstLineMarker.length();
		// trim extra whitespace
		wxString whitespaceChars = " \t";
		while ((firstVisiblePosition > 0)
		        && (whitespaceChars.Find(static_cast<char>(m_stc->GetCharAt(firstVisiblePosition - 1))) != wxNOT_FOUND))
			--firstVisiblePosition;
		// remove the marker
		m_stc->SetTargetStart(firstVisiblePosition);
		m_stc->SetTargetEnd(markerEnd);
		m_stc->ReplaceTarget(wxEmptyString);
	}
	else
	{
		ShowMessageDialog("Unable to find the visible-line marker!\n"
		                  "The viewing position will not be restored.",
		                  wxOK | wxICON_ERROR);
	}
	// restore the first visible line
	m_stc->SetFirstVisibleLine(firstVisibleLine);
	// set cursor position
	int currentPosOut = m_stc->PositionFromLine(firstVisibleLine);
	m_stc->GotoPos(currentPosOut);
}

bool AStyleFormat::RestoreSelection() const
// Remove the selection markers and select the text.
// The entire lines are selected.
{
	assert(m_stc != nullptr);
	bool returnValue = true;
	// the first visible line must later be restored
	int firstVisibleLine = m_stc->GetFirstVisibleLine();
	// find the selection markers
	int minPosition = -1;
	int maxPosition = -1;
	minPosition = m_stc->FindText(0, m_stc->GetTextLength(), m_minSelectionMarker, wxSTC_FIND_MATCHCASE);
	if (minPosition >= 0)
		maxPosition = m_stc->FindText(minPosition, m_stc->GetTextLength(), m_maxSelectionMarker, wxSTC_FIND_MATCHCASE);
	else
		maxPosition = m_stc->FindText(0, m_stc->GetTextLength(), m_maxSelectionMarker, wxSTC_FIND_MATCHCASE);
	int minLine = -1;
	int maxLine = -1;
	// get the max line number and remove the marker
	// remove max first so it's position doesn't change
	if (maxPosition > 0)
	{
		maxLine = m_stc->LineFromPosition(maxPosition);
		int maxEndPosition = maxPosition + m_maxSelectionMarker.length();
		// trim extra whitespace
		wxString whitespaceChars = " \t";
		while ((maxPosition > 0)
		        && (whitespaceChars.Find(static_cast<char>(m_stc->GetCharAt(maxPosition - 1))) != wxNOT_FOUND))
			--maxPosition;
		// remove the marker
		m_stc->SetTargetStart(maxPosition);
		m_stc->SetTargetEnd(maxEndPosition);
		m_stc->ReplaceTarget(wxEmptyString);
	}
	// get the min line number and remove the marker
	if (minPosition >= 0)
	{
		minLine = m_stc->LineFromPosition(minPosition);
		int minEndPosition = minPosition + m_minSelectionMarker.length();
		// if a marker line was inserted, remove the entire line
		if (m_line0Inserted	&& minLine == 0)
			minEndPosition = m_stc->LineLength(0);
		// trim extra whitespace
		wxString whitespaceChars = " \t";
		while ((minPosition > 0)
		        && (whitespaceChars.Find(static_cast<char>(m_stc->GetCharAt(minPosition - 1))) != wxNOT_FOUND))
			--minPosition;
		// remove the marker
		m_stc->SetTargetStart(minPosition);
		m_stc->SetTargetEnd(minEndPosition);
		m_stc->ReplaceTarget(wxEmptyString);
	}
	if ((minLine >= 0) && (maxLine >= 0))
	{
		// select the text
		// minimum marker was placed at the end of the previous line
		int selMin = m_stc->PositionFromLine(minLine + 1);
		// if a marker line was inserted select line 0
		if (m_line0Inserted && minLine == 0)
			selMin = 0;
		// select to the start of the following line
		else
			++maxLine;
		int selMax = m_stc->PositionFromLine(maxLine);
		// NOTE: reverse selection does not currently work (July 2013)
//		if (!m_selectionReversed)
		m_stc->SetSelection(selMin, selMax);
//		else
//			m_stc->SetSelection(selMax, selMin);
	}
	else
	{
		ShowMessageDialog("Unable to find a selection marker during restore!\n"
		                  "The formatted text will not be selected.",
		                  wxOK | wxICON_ERROR);
		returnValue = false;
	}
	// restore the first visible line
	if (m_line0Inserted)
		--firstVisibleLine;
	m_stc->SetFirstVisibleLine(firstVisibleLine);
	return returnValue;
}

//-----------------------------------------------------------------------------
// callback methods from AStyle
//-----------------------------------------------------------------------------

char* STDCALL AStyleFormat::MemoryAlloc(const unsigned long memoryNeeded)
// This method is called when Artistic Style needs to allocate memory.
// This program is responsible for freeing the memory.
{
	// error condition should be checked by the calling procedure
	char* buffer = new (std::nothrow) char [memoryNeeded];
	return buffer;
}

void STDCALL AStyleFormat::ErrorHandler(int errorNumber, const char* errorMessage)
// Method to handle error messages from messages from Artistic Style.
// This method is called only if there are errors when AStyleMain is called.
// This is for debugging and there should be no errors when the calling
// parameters are correct.
{
	wxString msgOut = wxString::FromUTF8(errorMessage);
	ShowMessageDialog(wxString::Format("astyle formatting error %d\n%s", errorNumber, msgOut.c_str()),
	                  wxOK | wxICON_ERROR);
}

#ifdef ASTYLE_DYLIB
//-----------------------------------------------------------------------------
// variables for dll build of AStyle
//-----------------------------------------------------------------------------

// typedefs for AStyle function pointers
DECLARE_fpASMAIN
DECLARE_fpASVER

// static definitions for the AStyle dynamic library
wxDynamicLibrary AStyleFormat::aslib;
wxDllType AStyleFormat::aslibHandle = 0;
fpASMain  AStyleFormat::fpAStyleMain = nullptr;
fpASVer   AStyleFormat::fpAStyleGetVersion = nullptr;

//-----------------------------------------------------------------------------
// methods for dll build of AStyle
//-----------------------------------------------------------------------------

wxString AStyleFormat::GetDynamicLibraryName()
{
	wxString libName;
#ifdef __WXMSW__
	libName = "AStyle-2.7";
#else
	libName = "astyle-2.7";
#endif
#ifndef NDEBUG
	libName += "d";
#endif	// NDEBUG
	libName = aslib.CanonicalizeName(libName);
	return libName;
}

void AStyleFormat::LoadDynamicLibrary()
// STATIC function to dynamically load the AStyle library.
{
	// check if already loaded
	if (aslib.IsLoaded())
	{
		ShowMessageDialog(wxString::Format(
		                      "AStyle library %s is already loaded!",
		                      GetDynamicLibraryName().c_str()),
		                  wxOK | wxICON_INFORMATION);
		return;
	}
	// load the library
	wxString libName = GetDynamicLibraryName();
	aslib.Load(libName, wxDL_DEFAULT | wxDL_QUIET);
	if (!aslib.IsLoaded())
	{
		ShowMessageDialog(wxString::Format(
		                      "Cannot load the AStyle library:\n%s.\n"
		                      "This must be corrected to format the text!",
		                      libName.c_str()),
		                  wxOK | wxICON_ERROR);
		return;
	}

	// get the AStyleMain address
	fpAStyleMain = (fpASMain) aslib.GetSymbol("AStyleMain");
	if (fpAStyleMain == nullptr)
	{
		ShowMessageDialog(wxString::Format(
		                      "Cannot find the symbol AStyleMain in %s.\n"
		                      "The function must be undecorated in the library.\n"
		                      "This must be corrected to format the text!",
		                      libName.c_str()),
		                  wxOK | wxICON_ERROR);
		return;
	}

	// verify AStyleGetVersion function - the function address is obtained when it is called
	fpAStyleGetVersion = (fpASVer) aslib.GetSymbol("AStyleGetVersion");
	if (fpAStyleGetVersion == nullptr)
	{
		ShowMessageDialog(wxString::Format(
		                      "Cannot find the symbol AStyleGetVersion in %s.\n"
		                      "The function must be undecorated in the library.\n"
		                      "This must be corrected to obtain the version!",
		                      libName.c_str()),
		                  wxOK | wxICON_ERROR);
		return;
	}

	// keep the dynamic library in memory
	aslibHandle = aslib.Detach();
}

void AStyleFormat::UnloadDynamicLibrary()
{
	if (aslib.IsLoaded())
		wxDynamicLibrary::Unload(aslibHandle);
	aslibHandle = 0;
}
#endif	// ASTYLE_DYLIB
