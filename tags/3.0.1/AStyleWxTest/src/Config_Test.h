// Config_Test.h
// Copyright (c) 2017 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

#ifndef ASTYLEWX_TEST_H
#define ASTYLEWX_TEST_H

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

// disable warnings in wxWidgets headers
#ifdef _MSC_VER
	#pragma warning(disable: 4996)  // secure version deprecation warnings
#endif

#include <iostream>         // for cout
#include <wx/config.h>
#include <wx/font.h>
#include <wx/msgdlg.h>
#include <wx/stc/stc.h>     // wxStyledTextCtrl
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "AStyleIFace.h"
#include "Config.h"

//----------------------------------------------------------------------------
// Test Specific Definitions
//----------------------------------------------------------------------------

#define COMMENT_VALUE     "Comment Font"
#define DEFAULT_VALUE     "Default Font"
#define POINT_SIZE        "10"
#define DIRECTORY_VALUE   "Current Directory"
#define FILE_FILTER_VALUE "1"
#define ASTYLE_DLG_VALUE  "1"
#define EDITOR_DLG_VALUE  "1"

#ifdef __WXMSW__
	#define CONFIG_TEST_NAME  "AStyleWxTest"
#else
	#define CONFIG_TEST_NAME  "astylewxtest"
#endif

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
	// class ASFrame ..........................
	ID_START = 1001,
	ID_VIEW_LINENUMBERS,
	ID_VIEW_MARGIN,
	ID_VIEW_WHITESPACE,
	ID_VIEW_ACTIVELINE,
	ID_VIEW_INDENTGUIDES,
	ID_VIEW_ENDLINE,
	ID_VIEW_WORDWRAP,
	ID_VIEW_MONOSPACE,
	ID_VIEW_TOOLBAR,
	ID_VIEW_TOOLBAR_NONE,
	ID_VIEW_STATUSBAR,
};

//-------------------------------------------------------------------------
// Fake ASEditor Class
// This is used instead of the GUI ASEditor class.
//-------------------------------------------------------------------------

class ASEditor
{
public:
	ASEditor() {}
	int  GetAStyleDlgPage() const        { return ToLong(ASTYLE_DLG_VALUE); }
	wxString GetCurrentDirectory() const { return DIRECTORY_VALUE; }
	// active functions
	int  ToLong(wxString value) const
	{
		long intValue = 0;
		value.ToLong(&intValue);
		return static_cast<int>(intValue);
	}
};

//-------------------------------------------------------------------------
// Fake ASFrame Class
// This is used instead of the GUI ASFrame class.
//-------------------------------------------------------------------------

class ASFrame
{
public:
	ASFrame(ASEditor* editor)
		: m_editor(editor),
		  m_boolReturn(false),
		  m_commentFont(FindCommentFont()),
		  m_defaultFont(FindDefaultFont())
	{
	}
	wxFont FindCommentFont() const
	{
		return wxFont(10,
		              wxFONTFAMILY_SWISS,
		              wxFONTSTYLE_NORMAL,
		              wxFONTWEIGHT_NORMAL);
	}
	wxFont FindDefaultFont() const
	{
		return wxFont(11,
		              wxFONTFAMILY_MODERN,
		              wxFONTSTYLE_NORMAL,
		              wxFONTWEIGHT_NORMAL);
	}
	int  GetAStyleDlgPage() const        { return ToLong(ASTYLE_DLG_VALUE); }
	const wxFont& GetCommentFont() const { return m_commentFont; }
	const wxFont& GetDefaultFont() const { return m_defaultFont; }
	ASEditor* GetEditor()                { return m_editor; }
	int  GetEditorDlgPage() const        { return ToLong(EDITOR_DLG_VALUE); }
	bool GetHideFindAfterMatch() const   { return m_boolReturn; }
	bool GetShowDialogTips()             { return m_boolReturn; }
	bool GetUseBottomTabs()              { return m_boolReturn; }
	bool GetUseSmallToolbar()            { return m_boolReturn; }
	bool GetShowToolTips()               { return m_boolReturn; }
	int  GetFileFilterIndex()            { return ToLong(FILE_FILTER_VALUE); }
	bool GetWrapSearch() const           { return m_boolReturn; }
	bool IsMaximized()                   { return m_boolReturn; }    // a wxTopLevelWindow function
	// active functions
	bool IsMenuItemChecked(int viewMenuId) const
	{
		if (viewMenuId == ID_VIEW_TOOLBAR_NONE)
			return !m_boolReturn;
		else
			return m_boolReturn;
	}
	void SetFrameBoolReturn(bool state)
	{
		m_boolReturn = state;
	}
	int  ToLong(wxString value) const
	{
		long intValue = 0;
		value.ToLong(&intValue);
		return static_cast<int>(intValue);
	}
	// mocked method
	MOCK_METHOD2(SetEditorOrViewOption, bool(const wxString&, const wxString&));

private:
	ASEditor* m_editor;		// variable
	bool m_boolReturn;		// return value for boolean getters
	wxFont m_commentFont;
	wxFont m_defaultFont;
};

//-------------------------------------------------------------------------
// AStyleIFace_Test Class
// There is one mocked method for Config::SetAStyleOptionFromConfig calls.
// Getters and setters are used from AStyleIFace to avoid duplication in the test class.
//-------------------------------------------------------------------------

class AStyleIFace_Test : public AStyleIFace
{
public:
	// mocked method
	MOCK_METHOD2(SetAStyleOptionFromConfig, bool(const wxString&, const wxString&));
};

//-------------------------------------------------------------------------
// Config_Test Class
// This is used for testing the Config class.
// The file entries are deleted before each test.
//-------------------------------------------------------------------------

class Config_Test : public Config
{
public:
	// delete file entries before and after each test
	Config_Test(wxString appNameTest) : Config(appNameTest) { DeleteAll(); }
	virtual ~Config_Test() { DeleteAll(); }

	// mocked method
	MOCK_METHOD1(ShowInvalidConfig, void(const wxString&));
};

//----------------------------------------------------------------------------

#endif // closes ASTYLEWX_TEST_H
