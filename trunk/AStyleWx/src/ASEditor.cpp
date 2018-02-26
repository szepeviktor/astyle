// ASEditor.cpp
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include <wx/file.h>
#include <wx/fontmap.h>
#include <wx/numdlg.h>

#include "AStyleFormat.h"
#include "AStyleWx.h"
#include "FileManager.h"

//-----------------------------------------------------------------------------
// declarations
//-----------------------------------------------------------------------------

// Implement ASApp& wxGetApp()
wxDECLARE_APP(ASApp);

//-----------------------------------------------------------------------------
// Editor event table
//-----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(ASEditor, wxStyledTextCtrl)
	// mouse events
	EVT_MOUSE_CAPTURE_LOST(				ASEditor::OnMouseCaptureLost)
	// context menu events
	EVT_CONTEXT_MENU(					ASEditor::OnSTCContextMenu)
	// scintilla events (in include\wx\stc\stc.h)
	EVT_STC_CHANGE(ID_EDITOR,			ASEditor::OnSTCChange)
	EVT_STC_CHARADDED(ID_EDITOR,		ASEditor::OnSTCCharAdded)
	EVT_STC_DOUBLECLICK(ID_EDITOR,		ASEditor::OnSTCDoubleClick)
	EVT_STC_SAVEPOINTLEFT(ID_EDITOR,	ASEditor::OnSTCSavePointLeft)
	EVT_STC_SAVEPOINTREACHED(ID_EDITOR,	ASEditor::OnSTCSavePointReached)
	EVT_STC_UPDATEUI(ID_EDITOR,			ASEditor::OnSTCUpdateUI)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
// ASEditor class
//-----------------------------------------------------------------------------

ASEditor::ASEditor(wxWindow* notebook)
{
	// create styled text control
	wxStyledTextCtrl::Create(notebook,
	                         ID_EDITOR,
	                         wxDefaultPosition,
	                         wxSize(0, 0),
	                         0,                  // style
	                         wxSTCNameStr);

	// initialize find dialog
	m_wrapped = false;
	m_firstMatch = 0;

	// initialize other variables
	m_frame = wxGetApp().GetFrame();
	m_fileMode = FILEMODE_CPP;
	m_useBOM = false;
	m_encoding = wxLocale::GetSystemEncoding();
	m_sysEncoding = wxLocale::GetSystemEncoding();
	m_fileModTime = 0;
	m_fileModLastAsk = 0;
	m_isDirty = false;
	m_indentType = INDENT_SPACES;

	// set scintilla options
	// styles are set in UpdateStcStyleOptions()
	wxStyledTextCtrl::SetMarginWidth(STC_BOOKMARK_MARGIN, 0);
	wxStyledTextCtrl::SetWrapVisualFlags(wxSTC_WRAPVISUALFLAG_START);
	wxStyledTextCtrl::UsePopUp(false);       // will do a custom context menu
	// create bookmark markers
	wxStyledTextCtrl::MarkerSetBackground(BOOKMARK_1, wxColour(0x80, 0xFF, 0xA0));
	wxStyledTextCtrl::MarkerSetForeground(BOOKMARK_1, wxColour(0x80, 0x80, 0));
}

int ASEditor::BraceAtCaret()
/* Find if there is a brace next to the caret, checking before caret first,
 * then after caret.
 * If a brace is found the matching brace will be highlighted.
 * Return position if a brace is found, or -1 if no brace found.
 */
{
	int caretPos = wxStyledTextCtrl::GetCurrentPos();
	int braceAtCaret = -1;
	char charBefore = '\0';
	char matchChar[] = "{}()[]<>";

	// remove existing highlighting, if any
	wxStyledTextCtrl::BraceHighlight(wxSTC_INVALID_POSITION, wxSTC_INVALID_POSITION);
	wxStyledTextCtrl::BraceBadLight(wxSTC_INVALID_POSITION);
	wxStyledTextCtrl::SetHighlightGuide(0);

	// Priority goes to character before caret
	if (caretPos > 0)
		charBefore = static_cast<wxChar>(wxStyledTextCtrl::GetCharAt(caretPos - 1));
	if (charBefore && strchr(matchChar, charBefore))
		braceAtCaret = caretPos - 1;
	// No brace found so check other side
	if (braceAtCaret < 0)
	{
		int charAfter = wxStyledTextCtrl::GetCharAt(caretPos);
		if (charAfter && strchr(matchChar, charAfter))
			braceAtCaret = caretPos;
	}
	// check for matching brace and highlight
	if (braceAtCaret > 0)
	{
		// this forces lexing of the entire document so SCI_BRACEMATCH will work correctly
		int styleEnd = wxStyledTextCtrl::GetEndStyled();
		wxStyledTextCtrl::Colourise(styleEnd, -1);
		// match the brace
		int braceOpposite = wxStyledTextCtrl::BraceMatch(braceAtCaret);
		if (braceOpposite > -1)
		{
			wxStyledTextCtrl::BraceHighlight(braceAtCaret, braceOpposite);
			wxStyledTextCtrl::SetHighlightGuide(wxStyledTextCtrl::GetColumn(braceAtCaret));
		}
		else
			wxStyledTextCtrl::BraceBadLight(braceAtCaret);
	}
	return braceAtCaret;
}

void ASEditor::BookmarkClearAll(int markerBookmark)
{
	wxStyledTextCtrl::MarkerDeleteAll(markerBookmark);
}

void ASEditor::BookmarkNext(int markerBookmark)
{
	int pos = wxStyledTextCtrl::GetCurrentPos();
	int lineno = wxStyledTextCtrl::LineFromPosition(pos);
	int lineStart = lineno + 1;		//Scan starting from next line

	int nextLine = wxStyledTextCtrl::MarkerNext(lineStart, 1 << markerBookmark);
	//If not found, try from the beginning
	if (nextLine < 0)
		nextLine = wxStyledTextCtrl::MarkerNext(0, 1 << markerBookmark);
	if (nextLine >= 0 && nextLine != lineno)	// No bookmark (of the given type) or only one, and already on it
		wxStyledTextCtrl::GotoLine(nextLine);
}

void ASEditor::BookmarkPrevious(int markerBookmark)
{
	int pos = wxStyledTextCtrl::GetCurrentPos();
	int lineno = wxStyledTextCtrl::LineFromPosition(pos);
	int lineStart = lineno - 1;		//Scan starting from previous line
	int lineRetry = wxStyledTextCtrl::GetLineCount();	//If not found, try from the end

	int nextLine = wxStyledTextCtrl::MarkerPrevious(lineStart, 1 << markerBookmark);
	if (nextLine < 0)
		nextLine = wxStyledTextCtrl::MarkerPrevious(lineRetry, 1 << markerBookmark);
	if (nextLine >= 0 && nextLine != lineno)	// No bookmark (of the given type) or only one, and already on it
		wxStyledTextCtrl::GotoLine(nextLine);
}

void ASEditor::BookmarkToggle(int markerBookmark)
{
	int pos = wxStyledTextCtrl::GetCurrentPos();
	int lineno = wxStyledTextCtrl::LineFromPosition(pos);
	int state = wxStyledTextCtrl::MarkerGet(lineno);
	// add only if no other markers
	if (!state)
		wxStyledTextCtrl::MarkerAdd(lineno, markerBookmark);
	// delete only if the same bookmark
	if (state & (1 << markerBookmark))
		wxStyledTextCtrl::MarkerDelete(lineno, markerBookmark);
}

void ASEditor::CountLineEnds(wxString& text, int& linesCR, int& linesLF, int& linesCRLF)
{
	linesCR = 0;
	linesLF = 0;
	linesCRLF = 0;
	wxChar chPrev = ' ';
	wxChar chNext = ' ';
	int lengthText = static_cast<int>(text.Len());

	for (int i = 0; i < lengthText; i++)
	{
		int ch = chNext;
		if (lengthText > 0 && i < lengthText - 1)
			chNext = text[i + 1];
		else
			chNext = ' ';
		if (ch == '\r')
		{
			if (chNext == '\n')
				linesCRLF++;
			else
				linesCR++;
		}
		else if (ch == '\n')
		{
			if (chPrev != '\r')
				linesLF++;
		}
		chPrev = ch;
	}
}

void ASEditor::DiscoverEOLSetting(wxString& text)
{
	int linesCR;
	int linesLF;
	int linesCRLF;
	CountLineEnds(text, linesCR, linesLF, linesCRLF);
	if (((linesLF >= linesCR) && (linesLF > linesCRLF))
	        || ((linesLF > linesCR) && (linesLF >= linesCRLF)))
		wxStyledTextCtrl::SetEOLMode(wxSTC_EOL_LF);
	else if (((linesCR >= linesLF) && (linesCR > linesCRLF))
	         || ((linesCR > linesLF) && (linesCR >= linesCRLF)))
		wxStyledTextCtrl::SetEOLMode(wxSTC_EOL_CR);
	else if (((linesCRLF >= linesLF) && (linesCRLF > linesCR))
	         || ((linesCRLF > linesLF) && (linesCRLF >= linesCR)))
		wxStyledTextCtrl::SetEOLMode(wxSTC_EOL_CRLF);
}

bool ASEditor::FileNeedsReload()
{
	if (m_filepath.IsOk())
	{
		wxDateTime newModTime = m_filepath.GetModificationTime();
		if (newModTime > m_fileModTime && newModTime != m_fileModLastAsk)
		{
			m_fileModLastAsk = newModTime;
			return true;
		}
	}
	return false;
}

void ASEditor::FindMatchingBrace(bool select)
/* Find the matching brace for the brace at the caret.
 * Can optionally select the text between the braces.
 */
{
	int braceAtCaret = BraceAtCaret();

	if (braceAtCaret >= 0)
	{
		int braceOpposite = wxStyledTextCtrl::BraceMatch(braceAtCaret);

		if (braceOpposite > braceAtCaret)
			braceOpposite++;
		else
			braceAtCaret++;

		if (braceOpposite >= 0)
		{
			if (select)
			{
				// must select in low to high order.
				if (braceAtCaret < braceOpposite)
					wxStyledTextCtrl::SetSelection(braceAtCaret, braceOpposite);
				else
					wxStyledTextCtrl::SetSelection(braceOpposite, braceAtCaret);
			}
			else
				wxStyledTextCtrl::SetSelection(braceOpposite, braceOpposite);
		}
	}
}

int ASEditor::FindNext(const wxFindReplaceData& findData, bool reverseFind)
{
	wxString findString = findData.GetFindString();
	if (findString.Length() == 0)
	{
		wxMessageBox("No text to find.", "Find", wxOK | wxICON_ERROR, m_frame->GetFindDialog());
		return -1;
	}
	if (findString != m_lastFind)
	{
		m_wrapped = false;
		m_firstMatch = -1;
		m_lastFind = findString;
	}
	// convert wxFindReplaceFlags to wxStyledTextCtrl flags
	int sci_flags = 0;
	if ((findData.GetFlags() & wxFR_WHOLEWORD) != 0)
		sci_flags |= wxSTC_FIND_WHOLEWORD;
	if ((findData.GetFlags() & wxFR_MATCHCASE) != 0)
		sci_flags |= wxSTC_FIND_MATCHCASE;

	// find the text
	int lengthDocument = wxStyledTextCtrl::GetLength();
	int startPosition = wxStyledTextCtrl::GetSelectionEnd();
	int endPosition = lengthDocument;
	if (reverseFind)
	{
		startPosition = wxStyledTextCtrl::GetSelectionStart() - 1;
		endPosition = 0;
	}

	wxStyledTextCtrl::SetTargetStart(startPosition);
	wxStyledTextCtrl::SetTargetEnd(endPosition);
	wxStyledTextCtrl::SetSearchFlags(sci_flags);
	int posFind = wxStyledTextCtrl::SearchInTarget(findString);

	// check for wrap
	if (posFind == -1 && m_frame->GetWrapSearch())
	{
		// Failed to find in indicated direction
		// so search from the beginning (forward) or from the end (reverse)
		// unless wrapFind is false
		m_wrapped = true;
		if (reverseFind)
		{
			startPosition = lengthDocument;
			endPosition = 0;
		}
		else
		{
			startPosition = 0;
			endPosition = lengthDocument;
		}
		wxStyledTextCtrl::SetTargetStart(startPosition);
		wxStyledTextCtrl::SetTargetEnd(endPosition);
		posFind = wxStyledTextCtrl::SearchInTarget(findString);
	}

	// check for hit
	if (posFind == -1)
	{
		wxString msg = wxString::Format("Search string '%s' not found.", findString.c_str());
		wxMessageBox(msg, "Find", wxOK | wxICON_INFORMATION, m_frame->GetFindDialog()) ;
	}
	else
	{
		int start = wxStyledTextCtrl::GetTargetStart();
		if (m_firstMatch < 0)
		{
			// haven't found a match
			m_firstMatch = start;
		}
		else if (m_wrapped
		         && ((!reverseFind && m_firstMatch <= posFind)
		             || (reverseFind && m_firstMatch >= posFind)))
		{
			// search has wrapped and passed the first match
			wxMessageBox("Find has reached the starting point of the search.",
			             "Find",
			             wxOK | wxICON_INFORMATION,
			             m_frame->GetFindDialog());
			// restart the search on F3 or Shift+F3
			m_wrapped = false;
			m_firstMatch = -1;
			return -1;
		}
		// put line in middle of the window
		int goLine = wxStyledTextCtrl::LineFromPosition(start);
		wxStyledTextCtrl::GotoLine(goLine);
		int firstLine = wxStyledTextCtrl::GetFirstVisibleLine();
		int midLine   = wxStyledTextCtrl::LinesOnScreen() / 2;
		int adjust    = firstLine + midLine - 1;
		if (goLine != adjust)
			wxStyledTextCtrl::LineScroll(0, goLine - adjust);
		// highlight the word found
		int end = wxStyledTextCtrl::GetTargetEnd();
		wxStyledTextCtrl::SetSelection(start, end);
	}
	return posFind;
}

void ASEditor::FormatFile(bool formatSelection)
{
	wxStyledTextCtrl::Freeze();
	wxStatusBar* statusBar = m_frame->GetStatusBar();
	if (statusBar)
		statusBar->Freeze();
	// format the file
	AStyleIFace* astyle = m_frame->GetAStyle();
	wxString options = astyle->GetOptions();
	astyle->AppendFileModeOption(m_fileMode, options);
	wxString testOptions = m_frame->GetTestOptions();
	if (testOptions != wxEmptyString)
		options.Append("\n" + testOptions);
	AStyleFormat format;
	if (formatSelection)
		format.FormatSelection(this, options);
	else
		format.FormatSource(this, options);
	// restore window
	if (statusBar)
		statusBar->Thaw();
	wxStyledTextCtrl::Thaw();
	Refresh(false);
}

void ASEditor::FormatSelection()
{
	// do not allow multiple calls
	static bool formatting;
	if (formatting)
		return;

	// format the file
	formatting = true;
	FormatFile(true);
	formatting = false;
}

void ASEditor::FormatSource()
{
	// do not allow multiple calls
	static bool formatting;
	if (formatting)
		return;

	// format the file
	formatting = true;
	FormatFile(false);
	formatting = false;
}

wxString ASEditor::GetAStyleVersion()
{
	AStyleFormat format;
	return format.GetAStyleVersion();
}

wxString ASEditor::GetEncodingName() const
{
	return wxFontMapper::GetEncodingName(m_encoding);
}

wxString ASEditor::GetSysEncodingName() const
{
	return wxFontMapper::GetEncodingName(m_sysEncoding);
}

wxString ASEditor::GetWordAtCaret()
{
	int selStart = wxStyledTextCtrl::GetSelectionStart();
	int selEnd = wxStyledTextCtrl::GetSelectionEnd();
	int lengthDoc = wxStyledTextCtrl::GetLength();
	wxString wordAtCaret;
	if (selStart != selEnd)
	{
		// get selected text
		wxString selectedText = wxStyledTextCtrl::GetSelectedText();
		if (!selectedText.IsEmpty() && (selectedText.Length() < 100u))
			wordAtCaret = selectedText;
	}
	else
	{
		// Try and find a word at the caret
		wxString nonWordChars = "\t\n\r !\"#$%&'()*+,-./:;<=>?@[\\]^`{|}~";
		// On the left...
		while ((selStart > 0)
		        && (nonWordChars.Find(static_cast<wxChar>(
		                                  wxStyledTextCtrl::GetCharAt(selStart - 1))) == wxNOT_FOUND))
			selStart--;
		// and on the right
		while ((selEnd < lengthDoc)
		        && (nonWordChars.Find(static_cast<wxChar>(
		                                  wxStyledTextCtrl::GetCharAt(selEnd))) == wxNOT_FOUND))
			selEnd++;
		wxString word = wxStyledTextCtrl::GetTextRange(selStart, selEnd);
		if (!word.IsEmpty() && (word.Length() < 100u))
			wordAtCaret = word;
	}
	return wordAtCaret;
}

bool ASEditor::HeaderIsObjectiveC()
{
	// search the first 100 lines for a keyword
	wxArrayString keywords;
	keywords.Add("Foundation/Foundation.h");
	keywords.Add("@interface");
	keywords.Add("@protocol");
	int posMax = wxStyledTextCtrl::PositionFromLine(100);
	if (posMax == wxNOT_FOUND)
		posMax = wxStyledTextCtrl::GetTextLength();
	for (size_t i = 0; i < keywords.GetCount(); i++)
	{
		int pos = wxStyledTextCtrl::FindText(0, posMax, keywords[i],
		                                     wxSTC_FIND_MATCHCASE |
		                                     wxSTC_FIND_WHOLEWORD);
		if (pos != wxNOT_FOUND)
			return true;
	}
	return false;
}

void ASEditor::OnLineEndMenu(wxCommandEvent& event)
{
	int lineEndID = event.GetId();
	int eol = wxSTC_EOL_CRLF;
	if (lineEndID == ID_LINEEND_CRLF)
		eol = wxSTC_EOL_CRLF;
	else if (lineEndID == ID_LINEEND_LF)
		eol = wxSTC_EOL_LF;
	else if (lineEndID == ID_LINEEND_CR)
		eol = wxSTC_EOL_CR;
	// don't update if unchanged
	int currentEOL = wxStyledTextCtrl::GetEOLMode();
	if (eol == currentEOL)
		return;
	// update the end-of-line
	wxStatusBar* statusBar = m_frame->GetStatusBar();
	if (statusBar)
		statusBar->Freeze();
	wxStyledTextCtrl::ConvertEOLs(eol);
	wxStyledTextCtrl::SetEOLMode(eol);
	// cannot undo since SetEolMode will not be reset
//	wxStyledTextCtrl::EmptyUndoBuffer();
	m_frame->UpdateToolBarDisplay();
	m_frame->UpdateStatusBarDisplay();
	if (statusBar)
		statusBar->Thaw();
}

void ASEditor::OnModeMenu(wxCommandEvent& event)
{
	int menuID = event.GetId();
	// don't update if unchanged
	FileMode currentFileMode = m_fileMode;
	UpdateModeFromMenuSelection(menuID);
	if (m_fileMode == currentFileMode)
		return;
	// update the filemode
	m_frame->UpdateMenuBarDisplay();
	UpdateFormatSelectDisplay();
	UpdateStcStyleOptions();
	// cannot undo since all STC variables will not be reset
	wxStyledTextCtrl::EmptyUndoBuffer();
	m_frame->UpdateToolBarDisplay();
	m_frame->UpdateStatusBarDisplay();
}

void ASEditor::OnMouseCaptureLost(wxMouseCaptureLostEvent&)
{
	// This event doesn't currently do anything.
	// But will get an error if the event isn't captured.
	// It happens when the file need to be reloaded.
	// Use EVT_MOUSE_CAPTURE_CHANGED to set variables when the
	// mouse capture is lost, and this event when it is obtained.
}

void ASEditor::OnSTCChange(wxStyledTextEvent&)
// A change is made to the text of the document, except for style changes.
// This event will fire with LoadFile() and SetText().
{
	m_frame->UpdateStatusBarDisplay();
}

void ASEditor::OnSTCCharAdded(wxStyledTextEvent& event)
{
	int ch = event.GetKey();
	AutomaticIndentation(ch) ;
}

void ASEditor::OnSTCContextMenu(wxContextMenuEvent&)
{
	wxMenu contextMenu(0L);
	// settings and options menu
	contextMenu.Append(ID_EDIT_EDITOR_OPTIONS, "Editor Options...");
#ifdef TESTMODE1
	contextMenu.Append(ID_TOOL_TEST_OPTIONS, "Test Options...");
#endif
	contextMenu.Append(ID_TOOL_ASTYLE_OPTIONS, "AStyle Options...");
	contextMenu.AppendSeparator();
	contextMenu.Append(ID_TOOL_ASTYLE_SETTINGS, "AStyle Settings...");
	PopupMenu(&contextMenu);
}

void ASEditor::OnSTCDoubleClick(wxStyledTextEvent&)
{
	int  charPos = BraceAtCaret();
	if (charPos >= 0)
	{
		wxStyledTextCtrl::GotoPos(charPos);
		SelectBlock();
	}
}

void ASEditor::OnSTCSavePointLeft(wxStyledTextEvent&)
{
	m_isDirty = true;
	m_frame->GetMenuBar()->Enable(ID_FILE_SAVE, true);
	m_frame->UpdateToolBarDisplay();
}

void ASEditor::OnSTCSavePointReached(wxStyledTextEvent&)
// Disable menu and toolbar items.
{
	m_isDirty = false;
	m_frame->GetMenuBar()->Enable(ID_FILE_SAVE, false);
	m_frame->UpdateToolBarDisplay();
}

void ASEditor::OnSTCUpdateUI(wxStyledTextEvent&)
/* A change is made to the text, the styling, or the selection.
 * Includes changes in caret position, insert or overwrite,
 * selected text, and number of lines.
 * Used to update any GUI elements that should change as a result.
 */
{
	wxMenuBar* menuBar = m_frame->GetMenuBar();
	wxToolBar* toolBar = m_frame->GetToolBar();;

	// enable select block if brace at caret
	int caretPos = BraceAtCaret();
	bool isBrace = caretPos >= 0 ? true : false;
	menuBar->Enable(ID_EDIT_SELECTBLOCK, isBrace);
	if (toolBar != nullptr)
		toolBar->EnableTool(ID_TB_EDIT_SELECTBLOCK, isBrace);
	UpdateFormatSelectDisplay();
	m_frame->UpdateNotebookTabDisplay(wxStyledTextCtrl::GetModify());
	// NOTE: On Windows UpdateStatusBarDisplay() cannot be called
	// in the same event as the above BraceAtCaret().
	// BraceAtCaret() calls wxStyledTextCtrl::BraceHighlight()
	// which doesn't work with wxStatusBar::SetStatusText().
	// The statusbar will be updated by the ASFrame::OnIdleevent.
	m_frame->SetStatusBarNeedsUpdate(true);
}

void ASEditor::SelectBlock()
{
	int xOffset;             // horizontal scroll position
	int firstLine;           // first visible line of the edit control

	// save the viewing position
	Freeze();
	xOffset = wxStyledTextCtrl::GetXOffset();
	firstLine = wxStyledTextCtrl::GetFirstVisibleLine();
	// must do this test because inside char is checked first
	int charPos = wxStyledTextCtrl::GetCurrentPos();
	int testBrace = wxStyledTextCtrl::GetCharAt(charPos);
	if (testBrace == '{')
		wxStyledTextCtrl::GotoPos(charPos + 1); // set caret to brace

	// select to matching brace
	FindMatchingBrace(true);

	// restore the viewing position
	wxStyledTextCtrl::SetFirstVisibleLine(firstLine);
	wxStyledTextCtrl::SetXOffset(xOffset);
	Thaw();
}

void ASEditor::SelectToEnd()
{
	int xOffset;             // horizontal scroll position

	// save the viewing position
	Freeze();
	xOffset = wxStyledTextCtrl::GetXOffset();

	// select to end of document
	int currentPos = wxStyledTextCtrl::GetCurrentPos();
	int anchorPos = wxStyledTextCtrl::GetLength();
	wxStyledTextCtrl::SetSelection(currentPos, anchorPos);

	// restore the viewing position
	wxStyledTextCtrl::SetXOffset(xOffset);
	Thaw();
}

void ASEditor::SelectToStart()
{
	int xOffset;             // horizontal scroll position

	// save the viewing position
	Freeze();
	xOffset = wxStyledTextCtrl::GetXOffset();

	// select to beginning of document
	int currentPos = wxStyledTextCtrl::GetCurrentPos();
	int anchorPos = 0;
	wxStyledTextCtrl::SetSelection(anchorPos, currentPos);

	// restore the viewing position
	wxStyledTextCtrl::SetXOffset(xOffset);
	Thaw();
}

void ASEditor::SetFileVariables(const wxFileName& filepath, wxFontEncoding encoding, bool useBOM)
{
	m_filepath = filepath;
	if (m_filepath.IsRelative())
		m_filepath.MakeAbsolute();
	m_fileModTime = filepath.GetModificationTime();
	m_encoding = encoding;
	m_useBOM = useBOM;
}

bool ASEditor::ShowGotoLineDialog()
{
	wxString msg = wxString::Format("Line number : 1...%d", GetLineCount());
	int line = static_cast<int>(
	               wxGetNumberFromUser(msg, wxEmptyString, "Go to line",
	                                   GetCurrentLine() + 1, 1, GetLineCount(), this));

	if (line > 0)
	{
		wxStyledTextCtrl::GotoLine(line - 1);
		return true;
	}
	return false;
}

void ASEditor::StripTrailingSpaces()
// Strip all trailing spaces from the current document.
// Uses raw text to avoid the unicode conversions.
{
	wxStyledTextCtrl::Freeze();
	wxStyledTextCtrl::BeginUndoAction();
	int firstLine = wxStyledTextCtrl::GetFirstVisibleLine();
	// for each line in the document
	int totalLines = wxStyledTextCtrl::GetLineCount();
	std::string newText;
	for (int i = 0; i < totalLines; i++)
	{
		// do not call GetLineRaw if the last line is empty (July 2013)
		// it sets 'line' to nullptr and causes an exception, so end it here
		if (i + 1 == totalLines
		        && wxStyledTextCtrl::PositionFromLine(i) == wxStyledTextCtrl::GetTextLength())
			break;
		std::string lineStr = wxStyledTextCtrl::GetLineRaw(i).data();
		// strip line
		size_t wsend = lineStr.find_last_not_of(" \t\r\n");
		size_t eol = lineStr.find_last_not_of("\r\n");
		if (eol != std::string::npos)
		{
			if (wsend == std::string::npos)
				lineStr = lineStr.erase(0, eol + 1);
			else if (eol != 0
			         && eol != wsend + 1)
				lineStr = lineStr.erase(wsend + 1, eol - wsend);
		}
		newText.append(lineStr);
	}
	wxStyledTextCtrl::SetTextRaw(newText.c_str());
	wxStyledTextCtrl::GotoPos(PositionFromLine(firstLine));
	wxStyledTextCtrl::SetFirstVisibleLine(firstLine);
	wxStyledTextCtrl::EndUndoAction();
	wxStyledTextCtrl::Thaw();
}

void ASEditor::TabsToSpaces()
// Convert all tabs in the current document to spaces.
// Uses raw text to avoid the unicode conversions.
{
	wxStyledTextCtrl::Freeze();
	wxStyledTextCtrl::BeginUndoAction();
	int firstLine = wxStyledTextCtrl::GetFirstVisibleLine();
	int tabWidth = wxStyledTextCtrl::GetTabWidth();
	// for each line in the document
	int totalLines = wxStyledTextCtrl::GetLineCount();
	std::string newText;
	for (int i = 0; i < totalLines; i++)
	{
		// do not call GetLineRaw if the last line is empty (July 2013)
		// it sets 'line' to nullptr and causes an exception, so end it here
		if (i + 1 == totalLines
		        && wxStyledTextCtrl::PositionFromLine(i) == wxStyledTextCtrl::GetTextLength())
			break;
		std::string lineStr = wxStyledTextCtrl::GetLineRaw(i).data();
		const char* line = lineStr.c_str();
		// convert indentation
		size_t lineLength = strlen(line);
		size_t j;
		for (j = 0; j < lineLength; j++)
			if (line[j] != '\t')
				break;
		newText.append(tabWidth * j, ' ');
		// convert the rest
		size_t start = j;
		for (; j < lineLength; j++)
		{
			if (line[j] == '\t')
			{
				newText.append(line + start, j - start);
				size_t numSpaces = tabWidth - ((j - start) % tabWidth);
				newText.append(numSpaces, ' ');
				start = j + 1;
			}
		}
		newText.append(line + start);
	}
	wxStyledTextCtrl::SetTextRaw(newText.c_str());
	wxStyledTextCtrl::GotoPos(PositionFromLine(firstLine));
	wxStyledTextCtrl::SetFirstVisibleLine(firstLine);
	wxStyledTextCtrl::EndUndoAction();
	wxStyledTextCtrl::Thaw();
}

void ASEditor::TextToStrings()
// Convert all lines in the current document to strings.
// Strings are in the format to be copied into a test program.
// Uses raw text to avoid the unicode conversions.
{
	wxStyledTextCtrl::Freeze();
	wxStyledTextCtrl::BeginUndoAction();
	int firstLine = wxStyledTextCtrl::GetFirstVisibleLine();
	// for each line in the document
	int totalLines = wxStyledTextCtrl::GetLineCount();
	std::string newText;
	for (int i = 0; i < totalLines; i++)
	{
		// do not call GetLineRaw if the last line is empty (July 2013)
		// it sets 'line' to nullptr and causes an exception, so end it here
		if (i + 1 == totalLines
		        && wxStyledTextCtrl::PositionFromLine(i) == wxStyledTextCtrl::GetTextLength())
			break;
		std::string lineStr = wxStyledTextCtrl::GetLineRaw(i).data();
		// convert the line
		newText.append("\"");
		size_t lineLength = lineStr.length();
		size_t j;
		for (j = 0; j < lineLength; j++)
		{
			if (lineStr[j] == '\r' || lineStr[j] == '\n')
				break;
			// escape quotes
			if (lineStr[j] == '\"')
				newText.append("\\");
			// escape escapes
			if (lineStr[j] == '\\')
				newText.append("\\");
			newText.append(1, lineStr[j]);
		}
		newText.append("\\n\"");
		// attach line ends
		for (; j < lineLength; j++)
			newText.append(1, lineStr[j]);
	}
	// insert beginning text line feed
	if (newText.compare(1, 2, "\\n") != 0)
		newText.insert(1, "\\n\"\r\n\"");
	// remove ending text line feed
	size_t textEnd = newText.rfind("\\n");
	newText.erase(textEnd, 2);
	// replace the text
	wxStyledTextCtrl::SetTextRaw(newText.c_str());
	wxStyledTextCtrl::GotoPos(PositionFromLine(firstLine));
	wxStyledTextCtrl::SetFirstVisibleLine(firstLine);
	wxStyledTextCtrl::EndUndoAction();
	wxStyledTextCtrl::Thaw();
}

void ASEditor::UpdateCommentFonts(wxFont newFont)
{
	int commentStyles[] = { wxSTC_C_COMMENT,
	                        wxSTC_C_COMMENTLINE,
	                        wxSTC_C_COMMENTDOC,
	                        wxSTC_C_COMMENTLINEDOC
	                      };

	const size_t numStyles = sizeof(commentStyles) / sizeof(commentStyles[0]);
	for (unsigned i = 0; i < numStyles; i++)
	{
		wxStyledTextCtrl::StyleSetFaceName(commentStyles[i], newFont.GetFaceName());
		wxStyledTextCtrl::StyleSetSize(commentStyles[i], newFont.GetPointSize());
	}
}

void ASEditor::UpdateEditorFromAStyleOptions(const AStyleIFace* astyle)
// Update the wxStyledTextControl from the astyle options.
{
	m_indentType = static_cast<IndentType>(astyle->getIndentType());
	if (m_indentType == INDENT_SPACES)
		wxStyledTextCtrl::SetUseTabs(false);
	else if (m_indentType == INDENT_TABS)
		wxStyledTextCtrl::SetUseTabs(true);
	else if (m_indentType == INDENT_FTABS)
		wxStyledTextCtrl::SetUseTabs(true);
	int indentLen = astyle->getIndentLength();
	wxStyledTextCtrl::SetTabWidth(indentLen);
	wxStyledTextCtrl::SetIndent(0);		// set indent the same as tab size
	if (m_indentType == INDENT_FTABS && astyle->getUseTabLength())
	{
		int tabLen = astyle->getTabLength();
		if (tabLen != indentLen)
		{
			wxStyledTextCtrl::SetTabWidth(tabLen);
			wxStyledTextCtrl::SetIndent(indentLen);
		}
	}
}

void ASEditor::UpdateEditorFromViewMenuOptions()
// Update the wxStyledTextControl from the view menu options.
{
	wxMenuBar* menuBar = m_frame->GetMenuBar();
	bool isChecked;
	isChecked = menuBar->IsChecked(ID_VIEW_LINENUMBERS);
	UpdateLineNumberMargin(isChecked);
	isChecked = menuBar->IsChecked(ID_VIEW_MARGIN);
	UpdateSelectionMargin(isChecked);
	isChecked = menuBar->IsChecked(ID_VIEW_WHITESPACE);
	wxStyledTextCtrl::SetViewWhiteSpace(isChecked);
	isChecked = menuBar->IsChecked(ID_VIEW_ACTIVELINE);
	wxStyledTextCtrl::SetCaretLineVisible(isChecked);
	isChecked = menuBar->IsChecked(ID_VIEW_INDENTGUIDES);
	int indentView = isChecked ? wxSTC_IV_LOOKBOTH : wxSTC_IV_NONE;
	wxStyledTextCtrl::SetIndentationGuides(indentView);
	isChecked = menuBar->IsChecked(ID_VIEW_ENDLINE);
	wxStyledTextCtrl::SetViewEOL(isChecked);
	// should use wxSTC_WRAP_CHAR for Asian languages
	if (menuBar->IsChecked(ID_VIEW_WORDWRAP))
		wxStyledTextCtrl::SetWrapMode(wxSTC_WRAP_WORD);
	else
		wxStyledTextCtrl::SetWrapMode(wxSTC_WRAP_NONE);
	isChecked = menuBar->IsChecked(ID_VIEW_MONOSPACE);
	UpdateMonospaceFontDisplay(isChecked);
}

void ASEditor::UpdateFormatSelectDisplay()
{
	// enable format select if text is selected
	wxMenuBar* menuBar = m_frame->GetMenuBar();
	wxToolBar* toolBar = m_frame->GetToolBar();;
	if (m_fileMode == FILEMODE_CPP
	        || m_fileMode == FILEMODE_OBJC
	        || m_fileMode == FILEMODE_JAVA
	        || m_fileMode == FILEMODE_SHARP)
	{
		int selStart = wxStyledTextCtrl::GetSelectionStart();
		int selEnd = wxStyledTextCtrl::GetSelectionEnd();
		bool isSelected = selStart == selEnd ? false : true;
		menuBar->Enable(ID_TOOL_FORMATSELECT, isSelected);
		if (toolBar != nullptr)
			toolBar->EnableTool(ID_TB_TOOL_FORMATSELECT, isSelected);
	}
	else
	{
		menuBar->Enable(ID_TOOL_FORMATSELECT, false);
		if (toolBar != nullptr)
			toolBar->EnableTool(ID_TB_TOOL_FORMATSELECT, false);
	}
}

void ASEditor::UpdateLineNumberMargin(bool showMargin)
{
	if (showMargin)
	{
		int width = wxStyledTextCtrl::TextWidth(wxSTC_STYLE_LINENUMBER, "_1999");
		wxStyledTextCtrl::SetMarginWidth(STC_LINENUMBER_MARGIN, width);
	}
	else
	{
		wxStyledTextCtrl::SetMarginWidth(STC_LINENUMBER_MARGIN, 0);
	}
}

void ASEditor::UpdateModeFromFileExtension()
{
	wxString extension = m_filepath.GetExt();
	extension = extension.Lower();

	if (extension == "c"
	        || extension == "cc"
	        || extension == "cpp"
	        || extension == "cxx"
	        || extension == "hpp"
	        || extension == "hxx")
		m_fileMode = FILEMODE_CPP;
	else if (extension == "h")
	{
		// extension 'h' can be C or Objective-C
		m_fileMode = FILEMODE_CPP;
		if (HeaderIsObjectiveC())
			m_fileMode = FILEMODE_OBJC;
	}
	else if (extension == "m" || extension == "mm")
		m_fileMode = FILEMODE_OBJC;
	else if (extension == "java" || extension == "jav")
		m_fileMode = FILEMODE_JAVA;
	else if (extension == "cs")
		m_fileMode = FILEMODE_SHARP;
	else
		m_fileMode = FILEMODE_NONE;
}

void ASEditor::UpdateModeFromMenuSelection(int menuID)
{
	if (menuID == ID_FILEMODE_CPP)
		m_fileMode = FILEMODE_CPP;
	else if (menuID == ID_FILEMODE_OBJC)
		m_fileMode = FILEMODE_OBJC;
	else if (menuID == ID_FILEMODE_JAVA)
		m_fileMode = FILEMODE_JAVA;
	else if (menuID == ID_FILEMODE_SHARP)
		m_fileMode = FILEMODE_SHARP;
	else
		m_fileMode = FILEMODE_NONE;
}

void ASEditor::UpdateMonospaceFontDisplay(bool useMonoFont)
{
	// monospace font display changes stc comment font to default font
	wxFont defaultFont = m_frame->GetDefaultFont();
	wxFont commentFont = m_frame->GetCommentFont();
	if (useMonoFont)
		UpdateCommentFonts(defaultFont);
	else
		UpdateCommentFonts(commentFont);
}

void ASEditor::UpdateSelectionMargin(bool showMargin)
{
	if (showMargin)
	{
		int width = wxStyledTextCtrl::TextWidth(wxSTC_STYLE_LINENUMBER, "999");
		wxStyledTextCtrl::SetMarginWidth(STC_BOOKMARK_MARGIN, width);
	}
	else
	{
		wxStyledTextCtrl::SetMarginWidth(STC_BOOKMARK_MARGIN, 0);
	}
}

void ASEditor::UpdateStcStyleOptions()
// update wxStyledTextCtrl styles
{
	// set all styles to their initial state
	wxStyledTextCtrl::StyleResetDefault();
	// set the default font
	wxFont defaultFont = m_frame->GetDefaultFont();
	wxStyledTextCtrl::StyleSetFont(wxSTC_STYLE_DEFAULT, defaultFont);
	wxStyledTextCtrl::StyleClearAll();

	// set line number font
	wxFont commentFont = m_frame->GetCommentFont();
	wxStyledTextCtrl::StyleSetFont(wxSTC_STYLE_LINENUMBER, commentFont);
	UpdateLineNumberMargin(m_frame->GetMenuBar()->IsChecked(ID_VIEW_LINENUMBERS));

	int fileMode = GetFileMode();
	if (fileMode == FILEMODE_CPP || fileMode == FILEMODE_OBJC
	        || fileMode == FILEMODE_JAVA || fileMode == FILEMODE_SHARP)
	{
		wxStyledTextCtrl::SetLexer(wxSTC_LEX_CPP);
		wxStyledTextCtrl::SetKeyWords(0, m_frame->GetKeyWords(fileMode));
		// do not underline or update preprocessor blocks
		wxStyledTextCtrl::SetProperty("lexer.cpp.track.preprocessor", "false");
		wxStyledTextCtrl::SetProperty("lexer.cpp.update.preprocessor", "false");
		// set comment styles to the selected font
		bool isChecked = m_frame->GetMenuBar()->IsChecked(ID_VIEW_MONOSPACE);
		UpdateMonospaceFontDisplay(isChecked);
		// set style properties
		const vector<TextStyle>& styleVector = m_frame->GetStyleVector();
		const size_t numStyles = styleVector.size();
		for (unsigned i = 0; i < numStyles; i++)
		{
			int style = styleVector[i].style;
			wxStyledTextCtrl::StyleSetForeground(style, styleVector[i].fore);
			wxStyledTextCtrl::StyleSetBackground(style, styleVector[i].back);
			wxStyledTextCtrl::StyleSetBold(style, styleVector[i].bold);
			wxStyledTextCtrl::StyleSetItalic(style, styleVector[i].italic);
		}

		// set brace highlight styles
		wxColour cyan(0, 255, 255);
		wxColour red(255, 0, 0);
		wxStyledTextCtrl::StyleSetBackground(wxSTC_STYLE_BRACELIGHT, cyan);
		wxStyledTextCtrl::StyleSetForeground(wxSTC_STYLE_BRACEBAD, red);
		wxStyledTextCtrl::StyleSetBold(wxSTC_STYLE_BRACEBAD, true);
	}
	else
	{
		wxStyledTextCtrl::SetLexer(wxSTC_LEX_NULL);
		wxStyledTextCtrl::SetKeyWords(0, wxEmptyString);
	}
	// TODO: make these options
	wxStyledTextCtrl::SetCaretLineBackground(wxColour(0xD0, 0xF0, 0xB0));	// light green
	wxStyledTextCtrl::StyleSetForeground(wxSTC_STYLE_LINENUMBER, wxColour(0, 0, 0));
	wxStyledTextCtrl::StyleSetBackground(wxSTC_STYLE_LINENUMBER, wxColour(0xD9, 0xD9, 0xD9));
	wxStyledTextCtrl::StyleSetForeground(wxSTC_STYLE_INDENTGUIDE, wxColour(0xA0, 0xA0, 0xA0));
	wxStyledTextCtrl::StyleSetBackground(wxSTC_STYLE_INDENTGUIDE, wxColour(0xFF, 0xFF, 0xFF));
}
