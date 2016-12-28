// AStyleFormat_Test.cpp
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.txt describes the conditions under which this software may be distributed.

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include <wx/app.h>
#include <wx/frame.h>

#include "Main_Test.h"
#include "AStyleFormat.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

//-------------------------------------------------------------------------
// AStyleFormat_Test Class
//-------------------------------------------------------------------------

class AStyleFormat_Test : public AStyleFormat
// A friend class of AStyleFormat so private data can be accessed.
{
public:
	AStyleFormat_Test() : m_frame(NULL)
		// Need this setup because of wxWidgets IMPLEMENT_APP_NO_MAIN.
		// It must be done to create a wxFrame object.
		// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
		// See the wxWidgets sample program mfctest.cpp.
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = NULL;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != NULL);		// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
		// now the objects can be created
		m_frame = new wxFrame(NULL, wxID_ANY, "AStyleWxTest");
		wxASSERT(m_frame != NULL);
	}

	virtual ~AStyleFormat_Test()
	// Need this because of IMPLEMENT_APP_NO_MAIN.
	// See the wxWidgets sample program mfctest.cpp.
	{
		wxTheApp->OnExit();			// call wxApp::OnExit()
		wxEntryCleanup();			// free resources from wxEntryStart
	}

	wxStyledTextCtrl* CreateStyledTextCtrl()
	// Use this to create the StyledTextCtrl.
	// It uses the initialized wxWidgets and sets the STC pointer in AStyleFormat.
	// Without it the AStyleFormat function calls will not work and
	// a SEH exception with code 0xc0000005 could be thrown in the test body.
	{
		wxStyledTextCtrl* stc = new wxStyledTextCtrl(m_frame, wxID_ANY);
		wxASSERT(stc != NULL);
		AStyleFormat::m_stc = stc;	// set the pointer in AStyleFormat
		return stc;
	}

	std::string GetBookmark1Marker() const
	{ return AStyleFormat::m_bookmark1Marker; }

	std::string GetFirstLineMarker() const
	{ return AStyleFormat::m_firstLineMarker; }

	bool GetLine0Inserted() const
	{ return AStyleFormat::m_line0Inserted; }

	std::string GetMinSelectionMarker() const
	{ return AStyleFormat::m_minSelectionMarker; }

	std::string GetMaxSelectionMarker() const
	{ return AStyleFormat::m_maxSelectionMarker; }

	void SetSelectionReversed(bool selectionReversed)
	{ AStyleFormat::m_selectionReversed = selectionReversed; }

	char* FormatSTCText(const wxString& optionsWx) const
	{ return AStyleFormat::FormatSTCText(optionsWx); }

	void InsertBookmarkMarkers(int bookmarkNumber, std::string& marker) const
	{ AStyleFormat::InsertBookmarkMarkers(bookmarkNumber, marker); }

	void InsertFirstVisibleLineMarker() const
	{ AStyleFormat::InsertFirstVisibleLineMarker(); }

	bool InsertFormattedText(const char* textOut)
	{ return AStyleFormat::InsertFormattedText(textOut); }

	bool InsertSelectionMarkers()
	{ return AStyleFormat::InsertSelectionMarkers(); }

	void RestoreBookmarks(int bookmarkNumber, std::string& marker) const
	{ AStyleFormat::RestoreBookmarks(bookmarkNumber, marker); }

	void RestoreFirstVisibleLine() const
	{ AStyleFormat::RestoreFirstVisibleLine(); }

	bool RestoreSelection() const
	{ return AStyleFormat::RestoreSelection(); }

	void SetLine0Inserted(bool state)
	{ AStyleFormat::m_line0Inserted = state; }

	void SetSectionReversed(bool reversed)
	{ AStyleFormat::m_selectionReversed = reversed; }

	// mocked method
	MOCK_CONST_METHOD2(CallAStyleMain, char* (const char*, const char*));

private:
	wxFrame* m_frame;
};

//-------------------------------------------------------------------------
// fake functions so AStyleFormat will compile
//-------------------------------------------------------------------------

#ifdef __WIN32__
	#define STDCALL __stdcall
#else
	#define STDCALL
#endif

const char* STDCALL AStyleGetVersion()
{
	static const char* version = "x.x.x";
	return version;
}

char* STDCALL AStyleMain(const char* textIn,
                         const char* /*options*/,
                         void(STDCALL* /*ErrorHandler*/)(int, const char*),
                         char* (STDCALL* /*MemoryAlloc*/)(unsigned long))
{ return const_cast<char*>(textIn); }

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {
//
//-------------------------------------------------------------------------
// AStyleFormat Tests
//-------------------------------------------------------------------------

TEST(AStyleFormat_Format, FormatSTCText_AStyleValid)
// Call AStyle to format a text string with a good return.
// CallAStyleMain is a mocked function that simply returns the text in.
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();

	// create test data
	// the original text in Unicode
	wxString textInWx =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// textIn in UTF8
	char textUTF8[] =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// create options as UTF8 and Unicode
	char optionsUTF8[] = "--style=allman, --pad-oper";
	wxString optionsWx = wxString::FromUTF8(optionsUTF8);
	stc->SetText(textInWx);

	// Expect CallAStyleMain to be called once for each call to FormatSTCText.
	// The return value from CallAStyleMain is the Unicode text input as raw text.
	// This raw text will be formatted by FormatSTCText and checked below.
	EXPECT_CALL(asf, CallAStyleMain(StrEq(textUTF8), StrEq(optionsUTF8))).Times(1);
	ON_CALL(asf, CallAStyleMain(_, _)).WillByDefault(Return(textUTF8));

	// test function
	char* textOut = asf.FormatSTCText(optionsWx);
	EXPECT_STREQ(textUTF8, textOut);
}

TEST(AStyleFormat_Format, FormatSTCText_AStyleError)
// Call AStyle to format a text string with an error return.
// CallAStyleMain is a mocked function that simply returns a NULL.
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();

	// create test data
	// the original text in Unicode
	wxString textInWx =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// textIn in UTF8
	char textUTF8[] =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// create options as UTF8 and Unicode
	char optionsUTF8[] = "--style=allman, --pad-oper";
	wxString optionsWx = wxString::FromUTF8(optionsUTF8);
	stc->SetText(textInWx);

	// Expect CallAStyleMain to be called once for each call to FormatSTCText.
	// The return value from CallAStyleMain is the Unicode text input as raw text.
	// This text will be formatted by FormatSTCText and checked below.
	EXPECT_CALL(asf, CallAStyleMain(StrEq(textUTF8), StrEq(optionsUTF8))).Times(1);
	ON_CALL(asf, CallAStyleMain(_, _)).WillByDefault(Return(reinterpret_cast<char*>(NULL)));

	// test function
	// NULL return indicates an error occurred in the AStyle program.
	char* textOut = asf.FormatSTCText(optionsWx);
	EXPECT_EQ(NULL, textOut);
}

TEST(AStyleFormat_Insert, InsertBookmarkMarkers_Marker1)
// Test InsertBookmarkMarkers for bookmark 1
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	std::string bookmark1Marker = asf.GetBookmark1Marker();
	int bookmarkNumber = 1;

	// create test data
	// the original text in
	wxString textIn =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// the text in with markers
	wxString textInMarked =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;" + bookmark1Marker + "\n"		// line 3
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;" + bookmark1Marker + "\n"	// line 6
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textIn);
	stc->MarkerAdd(3, bookmarkNumber);
	stc->MarkerAdd(6, bookmarkNumber);

	// test function
	asf.InsertBookmarkMarkers(bookmarkNumber, bookmark1Marker);
	wxString textInSTC = stc->GetText();
	EXPECT_STREQ(textInMarked.wc_str(), textInSTC.wc_str());
}

TEST(AStyleFormat_Insert, InsertBookmarkMarkers_NoMarkers)
// Test InsertBookmarkMarkers with no bookmarks
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	std::string bookmark1Marker = asf.GetBookmark1Marker();
	int bookmarkNumber = 1;

	// create test data
	// the original text in
	// should be the same as the text in marked
	wxString textIn =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textIn);

	// test function
	asf.InsertBookmarkMarkers(bookmarkNumber, bookmark1Marker);
	wxString textInSTC = stc->GetText();
	EXPECT_STREQ(textIn.wc_str(), textInSTC.wc_str());
}

TEST(AStyleFormat_Insert, InsertFirstVisibleLineMarker_Line0)
// Test InsertFirstVisibleLineMarker on Line 0.
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString firstLineMarker = asf.GetFirstLineMarker();

	// create test data
	// the original text in
	wxString textIn =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// the text in with marker
	wxString textInMarked =
	    "void breakLine(bool isSplitLine)" + firstLineMarker + "\n"	// first visible line
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textIn);

	// test function
	asf.InsertFirstVisibleLineMarker();
	wxString textInSTC = stc->GetText();
	EXPECT_STREQ(textInMarked.wc_str(), textInSTC.wc_str());
}

TEST(AStyleFormat_Insert, InsertFirstVisibleLineMarker_Line3)
// Test InsertFirstVisibleLineMarker on Line 3.
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString firstLineMarker = asf.GetFirstLineMarker();
	// scrolling more than 4 lines doesn't change the first visible line
	// because it is at the end of the text
	int scrolledLines = 3;

	// create test data
	// the original text in
	wxString textIn =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// the text in with marker
	wxString textInMarked =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;" + firstLineMarker + "\n"	// first visible line
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textIn);
	stc->LineScroll(0, scrolledLines);

	// test function
	asf.InsertFirstVisibleLineMarker();
	wxString textInSTC = stc->GetText();
	EXPECT_STREQ(textInMarked.wc_str(), textInSTC.wc_str());
}

TEST(AStyleFormat_Insert, InsertFormattedText)
// Test InsertFormattedText.
// Text should be replaced in the StyledTextCtrl.
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString minSelectionMarker = asf.GetMinSelectionMarker();
	wxString maxSelectionMarker = asf.GetMaxSelectionMarker();

	// create test data
	// the text is different so the replacement can be verified
	// the marked text in, lines 3 thru 5
	wxString textInMarked =
	    "void TextIn(bool isSplitLine)\n"
	    "{\n"
	    "    textInReady = true;" + minSelectionMarker + "\n"		// marked start
	    "    textInBreak = false;\n"
	    "    textInNum = nextLineSpacePadNum;\n"
	    "    textInPadNum = 0;" + maxSelectionMarker + "\n"		// marked end
	    "    textInLine =  formattedLine;\n"
	    "}";
	// the marked and formatted text out
	wxString textOutMarked =
	    "void FormattedOut(bool isSplitLine)\n"
	    "{\n"
	    "    formattedOutReady = true;" + minSelectionMarker + "\n"	// marked start
	    "    formattedOutBreak = false;\n"
	    "    formattedOutNum = nextLineSpacePadNum;\n"
	    "    formattedOutPadNum = 0;" + maxSelectionMarker + "\n"		// marked end
	    "    formattedOutLine =  formattedLine;\n"
	    "}";
	// the marked and formatted text out after replacement
	wxString textOutReplaced =
	    "void TextIn(bool isSplitLine)\n"
	    "{\n"
	    "    textInReady = true;" + minSelectionMarker + "\n"			// marked start
	    "    formattedOutBreak = false;\n"
	    "    formattedOutNum = nextLineSpacePadNum;\n"
	    "    formattedOutPadNum = 0;" + maxSelectionMarker + "\n"		// marked end
	    "    textInLine =  formattedLine;\n"
	    "}";
	// convert textOutMarked to raw text
	stc->SetText(textOutMarked);
	wxCharBuffer textOutMarkedRawBuf = stc->GetTextRaw();
	char* textOutMarkedRaw = textOutMarkedRawBuf.data();
	// set the text
	stc->ClearAll();
	stc->SetText(textInMarked);
	// test function
	EXPECT_TRUE(asf.InsertFormattedText(textOutMarkedRaw));
	wxString textOutSTC = stc->GetText();
	EXPECT_STREQ(textOutSTC.wc_str(), textOutReplaced.wc_str());
}

TEST(AStyleFormat_Insert, InsertFormattedText_Brackets)
// Test InsertFormattedText with the markers on brackets.
// With some options , such as A1, AStyle will break the line with the marker.
// On replacement, the extra line should be removed.
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString minSelectionMarker = asf.GetMinSelectionMarker();
	wxString maxSelectionMarker = asf.GetMaxSelectionMarker();

	// create test data
	// the text is different so the replacement can be verified
	// the marked text in, lines 3 thru 8
	wxString textInMarked =
	    "void TextIn(bool isSplitLine)\n"
	    "{" + minSelectionMarker + "\n"			// marked start
	    "    textInReady = true;\n"
	    "    textInBreak = false;\n"
	    "    textInNum = nextLineSpacePadNum;\n"
	    "    textInPadNum = 0;\n"
	    "    textInLine =  formattedLine;\n"
	    "}" + maxSelectionMarker;						// marked end
	// the marked and formatted text out
	wxString textOutMarked =
	    "void FormattedOut(bool isSplitLine)\n"
	    "{\n"											// marked start, originally here
	    "    " + minSelectionMarker + "\n"		// marked start, broken by astyle
	    "    formattedOutReady = true;\n"
	    "    formattedOutBreak = false;\n"
	    "    formattedOutNum = nextLineSpacePadNum;\n"
	    "    formattedOutPadNum = 0;\n"
	    "    formattedOutLine =  formattedLine;\n"
	    "}" + maxSelectionMarker;						// marked end
	// the marked and formatted text out after replacement
	wxString textOutReplaced =
	    "void TextIn(bool isSplitLine)\n"
	    "{" + minSelectionMarker + "\n"			// marked start, no empty line
	    "    formattedOutReady = true;\n"
	    "    formattedOutBreak = false;\n"
	    "    formattedOutNum = nextLineSpacePadNum;\n"
	    "    formattedOutPadNum = 0;\n"
	    "    formattedOutLine =  formattedLine;\n"
	    "}" + maxSelectionMarker;						// marked end
	// convert textOutMarked to raw text
	stc->SetText(textOutMarked);
	wxCharBuffer textOutMarkedRawBuf = stc->GetTextRaw();
	char* textOutMarkedRaw = textOutMarkedRawBuf.data();
	// set the text
	stc->ClearAll();
	stc->SetText(textInMarked);
	// test function
	EXPECT_TRUE(asf.InsertFormattedText(textOutMarkedRaw));
	wxString textOutSTC = stc->GetText();
	EXPECT_STREQ(textOutSTC.wc_str(), textOutReplaced.wc_str());
}

TEST(AStyleFormat_Insert, InsertFormattedText_NoMarkersOut)
// Test InsertFormattedText with no markers in the formatted text out.
// Should display an error message and replace the text in the StyledTextCtrl.
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString minSelectionMarker = asf.GetMinSelectionMarker();
	wxString maxSelectionMarker = asf.GetMaxSelectionMarker();

	// create test data
	// the text is different so the replacement can be verified
	// the marked text in
	wxString textInMarked =
	    "void TextIn(bool isSplitLine)\n"
	    "{\n"
	    "    textInReady = true;\n"
	    "    textInBreak = false;" + minSelectionMarker + "\n"	// marked start
	    "    textInNum = nextLineSpacePadNum;\n"
	    "    textInPadNum = 0;" + maxSelectionMarker + "\n"		// marked end
	    "    textInLine =  formattedLine;\n"
	    "}";
	// the unmarked formatted text out
	char textOut[] =
	    "void FormattedOut(bool isSplitLine)\n"
	    "{\n"
	    "    formattedOutReady = true;\n"
	    "    formattedOutBreak = false;\n"
	    "    formattedOutNum = nextLineSpacePadNum;\n"
	    "    formattedOutPadNum = 0;\n"
	    "    formattedOutLine =  formattedLine;\n"
	    "}";
	// convert textInMarked to raw text
	stc->SetText(textInMarked);
	// test function
	ConsoleRedirect console;	// capture the error message
	EXPECT_FALSE(asf.InsertFormattedText(textOut));
	// text should have been replaced
	wxCharBuffer textOutSTCBuf = stc->GetTextRaw();
	char* textOutSTC = textOutSTCBuf.data();
	EXPECT_STREQ(textOut, textOutSTC);
	// check the error message
	wxString expected =
	    "Unable to find an output selection marker during replacement!";
	wxString errors = console.GetMessages();
	EXPECT_STREQ(expected.wc_str(), errors.Left(expected.Len()).wc_str());
}

TEST(AStyleFormat_Insert, InsertFormattedText_NoMarkersSTC)
// Test InsertFormattedText with no markers in the StyledTextCtrl text in.
// Should display an error message and no text replaced in the StyledTextCtrl.
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString minSelectionMarker = asf.GetMinSelectionMarker();
	wxString maxSelectionMarker = asf.GetMaxSelectionMarker();

	// create test data
	// the text is different so the replacement can be verified
	// the unmarked text in
	wxString textIn =
	    "void TextIn(bool isSplitLine)\n"
	    "{\n"
	    "    textInReady = true;\n"
	    "    textInBreak = false;\n"
	    "    textInNum = nextLineSpacePadNum;\n"
	    "    textInPadNum = 0;\n"
	    "    textInLine =  formattedLine;\n"
	    "}";
	// the marked and formatted text out
	wxString textOutMarked =
	    "void FormattedOut(bool isSplitLine)\n"
	    "{\n"
	    "    formattedOutReady = true;\n"
	    "    formattedOutBreak = false;" + minSelectionMarker + "\n"	// marked start
	    "    formattedOutNum = nextLineSpacePadNum;\n"
	    "    formattedOutPadNum = 0;" + maxSelectionMarker + "\n"		// marked end
	    "    formattedOutLine =  formattedLine;\n"
	    "}";
	// convert textOutMarked to raw text
	stc->SetText(textOutMarked);
	wxCharBuffer textOutMarkedRawBuf = stc->GetTextRaw();
	char* textOutMarkedRaw = textOutMarkedRawBuf.data();
	// set the text
	stc->ClearAll();
	stc->SetText(textIn);
	// test function
	ConsoleRedirect console;	// capture the error message
	EXPECT_FALSE(asf.InsertFormattedText(textOutMarkedRaw));
	// text should not have changed
	wxString textOutSTC = stc->GetText();
	EXPECT_STREQ(textIn.wc_str(), textOutSTC.wc_str());
	// check the error message
	wxString expected =
	    "Unable to find a STC selection marker during replacement!";
	wxString errors = console.GetMessages();
	EXPECT_STREQ(expected.wc_str(), errors.Left(expected.Len()).wc_str());
}

TEST(AStyleFormat_Insert, InsertSelectionMarkers_CaretAtEnd)
// Insert selection markers with the caret at end of the selection.
// Should insert the markers and return "true".
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString minSelectionMarker = asf.GetMinSelectionMarker();
	wxString maxSelectionMarker = asf.GetMaxSelectionMarker();

	// create test data
	// the original text in
	wxString textIn =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// the text in with markers, lines 4 thru 7
	wxString textInMarked =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;" + minSelectionMarker + "\n"		// line 3
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;" + maxSelectionMarker + "\n"		// line 7
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textIn);
	// set selection  with caret at the end of the selection
	// will actually set the selection to the start of line 8
	int minPos = stc->PositionFromLine(4);
	int maxPos = stc->PositionFromLine(7 + 1);
	stc->SetSelection(minPos, maxPos);

	// test function
	EXPECT_TRUE(asf.InsertSelectionMarkers());
	wxString textInSTC = stc->GetText();
	EXPECT_STREQ(textInMarked.wc_str(), textInSTC.wc_str());
}

TEST(AStyleFormat_Insert, InsertSelectionMarkers_CaretAtBegin)
// Insert selection markers with the caret at beginning of the selection.
// Should insert the markers and return "true".
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString minSelectionMarker = asf.GetMinSelectionMarker();
	wxString maxSelectionMarker = asf.GetMaxSelectionMarker();

	// create test data
	// the original text in
	wxString textIn =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// the text in with markers, lines 4 thru 7
	wxString textInMarked =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;" + minSelectionMarker + "\n"		// line 3
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;" + maxSelectionMarker + "\n"	// line 7
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textIn);
	// set selection with caret at the beginning of the selection
	// will actually set the selection to the start of line 8
	int minPos = stc->PositionFromLine(4);
	int maxPos = stc->PositionFromLine(7 + 1);
	stc->SetSelection(minPos, maxPos);

	// test function
	EXPECT_TRUE(asf.InsertSelectionMarkers());
	wxString textInSTC = stc->GetText();
	EXPECT_STREQ(textInMarked.wc_str(), textInSTC.wc_str());
}

TEST(AStyleFormat_Insert, InsertSelectionMarkers_MaxSelection)
// Test InsertSelectionMarkers with the entire document selected.
// A line 0 is added for the marker.
// Should insert the markers and return "true".
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString minSelectionMarker = asf.GetMinSelectionMarker();
	wxString maxSelectionMarker = asf.GetMaxSelectionMarker();

	// create test data
	// the original text in
	wxString textIn =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// the text in with markers
	wxString textInMarked =
	    minSelectionMarker + "\n"						// line 0 added for the marker
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}"  + maxSelectionMarker;								// line 9
	stc->SetText(textIn);
	// need to set end of line mode for the inserted line
	stc->SetEOLMode(wxSTC_EOL_LF);
	// set selection for the entire document
	int minPos = stc->PositionFromLine(0);
	int maxPos = stc->GetLineEndPosition(9);
	stc->SetSelection(minPos, maxPos);

	// test function
	EXPECT_TRUE(asf.InsertSelectionMarkers());
	wxString textInSTC = stc->GetText();
	EXPECT_STREQ(textInMarked.wc_str(), textInSTC.wc_str());
	// should flag line 0 inserted
	EXPECT_TRUE(asf.GetLine0Inserted());
}

TEST(AStyleFormat_Insert, InsertSelectionMarkers_NoSelection)
// Test InsertSelectionMarkers with no selection.
// Should display an error message with no markers inserted and return "false".
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();

	// create test data
	// the original text in
	// should be the same as the text in marked
	wxString textIn =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textIn);

	// test function
	ConsoleRedirect console;	// capture the error message
	EXPECT_FALSE(asf.InsertSelectionMarkers());
	// text should not change
	wxString textInSTC = stc->GetText();
	EXPECT_STREQ(textIn.wc_str(), textInSTC.wc_str());
	// check the error message
	wxString expected =
	    "No text is selected, no text will be formatted!";
	wxString errors = console.GetMessages();
	EXPECT_STREQ(expected.wc_str(), errors.Left(expected.Len()).wc_str());

}

TEST(AStyleFormat_Insert, InsertSelectionMarkers_MinimumSelect)
// Test InsertSelectionMarkers with one character selected.
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString minSelectionMarker = asf.GetMinSelectionMarker();
	wxString maxSelectionMarker = asf.GetMaxSelectionMarker();

	// create test data
	// should align the selected line
	wxString textIn =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "}";
	wxString text =
	    "void breakLine(bool isSplitLine)\n"
	    "{" + minSelectionMarker + "\n"	// line 1
	    "    isLineReady = true;" + maxSelectionMarker + "\n"	// line 2
	    "    isInLineBreak = false;\n"
	    "}";
	stc->SetText(textIn);
	// select one character in the second line (the '=' sign)
	int minPos = stc->PositionFromLine(2);
	minPos += 16;
	int maxPos = minPos + 1;
	stc->SetSelection(minPos, maxPos);
	// check it just to be sure
	EXPECT_STREQ("=", stc->GetSelectedTextRaw());

	// test function
	EXPECT_TRUE(asf.InsertSelectionMarkers());
	// text should not change
	wxString textInSTC = stc->GetText();
	EXPECT_STREQ(text.wc_str(), textInSTC.wc_str());
}

TEST(AStyleFormat_Insert, InsertSelectionMarkers_MaximumSelect)
// Test InsertSelectionMarkers with the entire document selected.
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString minSelectionMarker = asf.GetMinSelectionMarker();
	wxString maxSelectionMarker = asf.GetMaxSelectionMarker();

	// create test data
	// should align the selected line
	wxString textIn =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "}";
	wxString text =
	    minSelectionMarker + "\n"	// line 0
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "}" + maxSelectionMarker;	// line 5
	// must have LF line ends for testing for the line added at position 0
	stc->SetEOLMode(wxSTC_EOL_LF);
	stc->SetText(textIn);
	// select the entire document
	stc->SelectAll();

	// test function
	EXPECT_TRUE(asf.InsertSelectionMarkers());
	// all text should be selected
	wxString textInSTC = stc->GetText();
	EXPECT_STREQ(text.wc_str(), textInSTC.wc_str());
}

TEST(AStyleFormat_Restore, RestoreBookmarks_Marker1)
// Test RestoreBookmarks for bookmark 1
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	std::string bookmark1Marker = asf.GetBookmark1Marker();
	int bookmarkNumber = 1;

	// create test data
	// the marked reformatted text out
	wxString textOutMarked =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;" + bookmark1Marker + "\n"		// line 3
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;" + bookmark1Marker + "\n"	// line 5
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// the unmarked reformatted STC text
	// the STC will have bookmarks at the marker locations
	wxString textOut =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textOutMarked);

	// test function
	asf.RestoreBookmarks(bookmarkNumber, bookmark1Marker);
	int lineStart = 0;
	int markerLine = stc->MarkerNext(lineStart, 1 << bookmarkNumber);
	EXPECT_EQ(3, markerLine);
	lineStart = ++markerLine;
	markerLine = stc->MarkerNext(lineStart, 1 << bookmarkNumber);
	EXPECT_EQ(5, markerLine);
	lineStart = ++markerLine;
	markerLine = stc->MarkerNext(lineStart, 1 << bookmarkNumber);
	EXPECT_EQ(-1, markerLine);
	// check the STC text
	wxString textOutSTC = stc->GetText();
	EXPECT_STREQ(textOut.wc_str(), textOutSTC.wc_str());
}

TEST(AStyleFormat_Restore, RestoreBookmarks_NoMarkers)
// Test RestoreBookmarkMarkers with no bookmarks
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	std::string bookmark1Marker = asf.GetBookmark1Marker();
	int bookmarkNumber = 1;

	// create test data
	// the marked reformatted text out
	// should be the same as the STC text
	wxString textOut =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textOut);

	// test function
	asf.RestoreBookmarks(bookmarkNumber, bookmark1Marker);
	int lineStart = 0;
	int markerLine = stc->MarkerNext(lineStart, 1 << bookmarkNumber);
	EXPECT_EQ(-1, markerLine);
	// check the STC text
	wxString textOutSTC = stc->GetText();
	EXPECT_STREQ(textOut.wc_str(), textOutSTC.wc_str());
}

TEST(AStyleFormat_Restore, RestoreFirstVisibleLine_Line0)
// Test RestoreFirstVisibleLine for line 0.
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString firstLineMarker = asf.GetFirstLineMarker();

	// create test data
	// the marked reformatted text out
	wxString textOutMarked =
	    "void breakLine(bool isSplitLine)" + firstLineMarker + "\n"	// first visible line
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// the unmarked reformatted STC text
	// the STC will have bookmarks at the marker locations
	wxString textOut =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textOutMarked);

	// test function
	asf.RestoreFirstVisibleLine();
	int markerLine = stc->GetFirstVisibleLine();
	EXPECT_EQ(0, markerLine);
	// check the STC text
	wxString textOutSTC = stc->GetText();
	EXPECT_STREQ(textOut.wc_str(), textOutSTC.wc_str());
}

TEST(AStyleFormat_Restore, RestoreFirstVisibleLine_Line3)
// Test RestoreFirstVisibleLine for line 3.
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString firstLineMarker = asf.GetFirstLineMarker();

	// create test data
	// the marked reformatted text out
	wxString textOutMarked =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;" + firstLineMarker + "\n"	// first visible line
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// the unmarked reformatted STC text
	// the STC will have bookmarks at the marker locations
	wxString textOut =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textOutMarked);

	// test function
	asf.RestoreFirstVisibleLine();
	int markerLine = stc->GetFirstVisibleLine();
	// using more than 4 lines doesn't change the first visible line
	// because it is at the end of the text
	EXPECT_EQ(3, markerLine);
	// check the STC text
	wxString textOutSTC = stc->GetText();
	EXPECT_STREQ(textOut.wc_str(), textOutSTC.wc_str());
}

TEST(AStyleFormat_Restore, RestoreSelection_CaretAtEnd)
// Test RestoreSelection with the caret at end of the selection.
// Should restore the selection and return "true".
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString minSelectionMarker = asf.GetMinSelectionMarker();
	wxString maxSelectionMarker = asf.GetMaxSelectionMarker();

	// create test data
	// the marked reformatted text out, selected lines 4 thru 7
	wxString textOutMarked =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;" + minSelectionMarker + "\n"		//line 3
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;" + maxSelectionMarker + "\n"		//line 7
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// the unmarked reformatted STC text
	// the STC will have selected text at the marker locations
	wxString textOut =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textOutMarked);

	// test function
	EXPECT_TRUE(asf.RestoreSelection());
	// lines 4 thru 7 should be selected
	// the end selection will actually be the start of line 8
	int minLine = stc->LineFromPosition(stc->GetSelectionStart());
	int maxLine = stc->LineFromPosition(stc->GetSelectionEnd());
	EXPECT_EQ(4, minLine);
	EXPECT_EQ(8, maxLine);
	// check end selection for the start of line 8
	int maxPos = stc->GetSelectionEnd();
	int lineStartPos = stc->PositionFromLine(8);
	EXPECT_EQ(lineStartPos, maxPos);
	// current position should be at end of selection
	int currentPos = stc->GetCurrentPos();
	int anchorPos = stc->GetAnchor();
	EXPECT_TRUE(currentPos > anchorPos);
	// check the STC text
	wxString textOutSTC = stc->GetText();
	EXPECT_STREQ(textOut.wc_str(), textOutSTC.wc_str());
}

TEST(AStyleFormat_Restore, RestoreSelection_CaretAtBegin)
// Test RestoreSelection with the caret at beginning of the selection.
// Should restore the selection and return "true".
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString minSelectionMarker = asf.GetMinSelectionMarker();
	wxString maxSelectionMarker = asf.GetMaxSelectionMarker();

	// create test data
	// the marked reformatted text out, lines 3 thru 8
	wxString textOutMarked =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;" + minSelectionMarker + "\n"		// line 2
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();" + maxSelectionMarker + "\n"	// line 8
	    "}";
	// the unmarked reformatted STC text
	// the STC will have selected text at the marker locations
	wxString textOut =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textOutMarked);
	asf.SetSectionReversed(true);	// reverse the selection

	// test function
	EXPECT_TRUE(asf.RestoreSelection());
	// lines 3 thru 8 should be selected
	// the end selection will actually be the start of line 9
	int minLine = stc->LineFromPosition(stc->GetSelectionStart());
	int maxLine = stc->LineFromPosition(stc->GetSelectionEnd());
	EXPECT_EQ(3, minLine);
	EXPECT_EQ(9, maxLine);
	// check end selection for the start of line 9
	int maxPos = stc->GetSelectionEnd();
	int lineStartPos = stc->PositionFromLine(9);
	EXPECT_EQ(lineStartPos, maxPos);
	// current position should be at beginning of selection
	// but since this currently doesn't work it is at the end
	int currentPos = stc->GetCurrentPos();
	int anchorPos = stc->GetAnchor();
	EXPECT_TRUE(currentPos > anchorPos);
	// check the STC text
	wxString textOutSTC = stc->GetText();
	EXPECT_STREQ(textOut.wc_str(), textOutSTC.wc_str());
}

TEST(AStyleFormat_Restore, RestoreSelection_MaxSelection)
// Test RestoreSelection with the entire document selected.
// A line 0 was added for the marker. It is removed on the output.
// Should restore the selection and return "true".
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString minSelectionMarker = asf.GetMinSelectionMarker();
	wxString maxSelectionMarker = asf.GetMaxSelectionMarker();

	// create test data
	// the marked reformatted text out, lines 0 thru 9
	wxString textOutMarked =
	    minSelectionMarker + "\n"					// line 0 added for the marker
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}" + maxSelectionMarker;							// line 9
	// the unmarked reformatted STC text
	// the STC will have selected text at the marker locations
	wxString textOut =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textOutMarked);

	// test function
	asf.SetLine0Inserted(true);		// flag line 0 as added
	EXPECT_TRUE(asf.RestoreSelection());
	// lines 0 thru 9 should be selected
	int minLine = stc->LineFromPosition(stc->GetSelectionStart());
	int maxLine = stc->LineFromPosition(stc->GetSelectionEnd());
	EXPECT_EQ(0, minLine);
	EXPECT_EQ(9, maxLine);
	// check end selection for the end of line 9
	int maxPos = stc->GetSelectionEnd();
	int lineEndPos = stc->GetLineEndPosition(9);
	EXPECT_EQ(lineEndPos, maxPos);
	// check the STC text
	wxString textOutSTC = stc->GetText();
	EXPECT_STREQ(textOut.wc_str(), textOutSTC.wc_str());
}

TEST(AStyleFormat_Restore, RestoreSelection_NoMinMarker)
// Test RestoreSelection with the with no minimum marker.
// Should display an error message with no text selected and return "false".
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString maxSelectionMarker = asf.GetMaxSelectionMarker();

	// create test data
	// the text out with no minimum marker
	wxString textOutMarked =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;" + maxSelectionMarker + "\n"	// line 7
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// the unmarked reformatted STC text
	// the STC will not have selected text
	wxString textOut =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textOutMarked);

	// test function
	ConsoleRedirect console;	// capture the error message
	EXPECT_FALSE(asf.RestoreSelection());
	// there should be no selected text
	int minPos = stc->GetSelectionStart();
	int maxPos = stc->GetSelectionEnd();
	EXPECT_TRUE(minPos == maxPos);
	// check the STC text
	wxString textOutSTC = stc->GetText();
	EXPECT_STREQ(textOut.wc_str(), textOutSTC.wc_str());
	// check the error message
	wxString expected =
	    "Unable to find a selection marker during restore!";
	wxString errors = console.GetMessages();
	EXPECT_STREQ(expected.wc_str(), errors.Left(expected.Len()).wc_str());
}

TEST(AStyleFormat_Restore, RestoreSelection_NoMaxMarker)
// Test RestoreSelection with the with no maximum marker.
// Should display an error message with no text selected and return "false".
{
	// create objects
	AStyleFormat_Test asf;
	wxStyledTextCtrl* stc = asf.CreateStyledTextCtrl();
	wxString minSelectionMarker = asf.GetMinSelectionMarker();

	// create test data
	// the text out with no maximum marker
	wxString textOutMarked =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;" + minSelectionMarker + "\n"	// line 3
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	// the unmarked reformatted STC text
	// the STC will not have selected text
	wxString textOut =
	    "void breakLine(bool isSplitLine)\n"
	    "{\n"
	    "    isLineReady = true;\n"
	    "    isInLineBreak = false;\n"
	    "    spacePadNum = nextLineSpacePadNum;\n"
	    "    nextLineSpacePadNum = 0;\n"
	    "    readyFormattedLine =  formattedLine;\n"
	    "    formattedLineCommentNum = string::npos;\n"
	    "    clearFormattedLineSplitPoints();\n"
	    "}";
	stc->SetText(textOutMarked);

	// test function
	ConsoleRedirect console;	// capture the error message
	EXPECT_FALSE(asf.RestoreSelection());
	// there should be no selected text
	int minPos = stc->GetSelectionStart();
	int maxPos = stc->GetSelectionEnd();
	EXPECT_TRUE(minPos == maxPos);
	// check the STC text
	wxString textOutSTC = stc->GetText();
	EXPECT_STREQ(textOut.wc_str(), textOutSTC.wc_str());
	// check the error message
	wxString expected =
	    "Unable to find a selection marker during restore!";
	wxString errors = console.GetMessages();
	EXPECT_STREQ(expected.wc_str(), errors.Left(expected.Len()).wc_str());

}

//----------------------------------------------------------------------------

}  // anonymous namespace
