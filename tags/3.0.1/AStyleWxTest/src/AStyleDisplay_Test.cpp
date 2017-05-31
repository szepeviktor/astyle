// AStyleDisplay_Test.cpp
// Copyright (c) 2017 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include <wx/app.h>
#include <wx/frame.h>

#include "AStyleDisplay.h"
#include "AStyleDlgBase.h"
#include "gtest/gtest.h"

using namespace testing;

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {
//
//-------------------------------------------------------------------------
// AStyleDisplay Display*Options Tests
// The method variables should be updated.
//-------------------------------------------------------------------------

struct AStyleDisplayF_Init : public Test
{
	// Need this setup because of wxWidgets IMPLEMENT_APP_NO_MAIN.
	// It must be done to create a wxFrame object.
	// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
	// See the wxWidgets sample program mfctest.cpp.
	AStyleDisplayF_Init() : m_frame(nullptr)
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = nullptr;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != nullptr);	// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
		// now the objects can be created
		m_frame = new wxFrame(nullptr, wxID_ANY, "AStyleWxTest");
		wxASSERT(m_frame != nullptr);
	}
	virtual ~AStyleDisplayF_Init()
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
		wxASSERT(stc != nullptr);
		return stc;
	}
	wxFrame* m_frame;
};

TEST_F(AStyleDisplayF_Init, DisplayFormatOptions)
// Check that the member variables are updated with the method call.
{
	// create objects
	AStyleDisplay asd(0, 0, 0, 0, 0, 0);
	wxStyledTextCtrl* stc = this->CreateStyledTextCtrl();
	wxCommandEvent event(wxEVT_COMMAND_CHECKBOX_CLICKED, ID_BREAK_CLOSING);

	// test the method
	EXPECT_EQ(nullptr, asd.GetEvent());
	EXPECT_EQ(nullptr, asd.GetSTC());
	asd.DisplayFormatOptions(event, stc);
	EXPECT_EQ(&event, asd.GetEvent());
	EXPECT_EQ(stc, asd.GetSTC());
}

TEST_F(AStyleDisplayF_Init, DisplayIndentOptions)
// Check that the member variables are updated with the method call.
{
	// create objects
	AStyleDisplay asd(0, 0, 0, 0, 0, 0);
	wxStyledTextCtrl* stc = this->CreateStyledTextCtrl();
	wxCommandEvent event(wxEVT_COMMAND_CHECKBOX_CLICKED, ID_INDENT_CLASS);

	// test the method
	EXPECT_EQ(nullptr, asd.GetEvent());
	EXPECT_EQ(nullptr, asd.GetSTC());
	asd.DisplayIndentOptions(event, stc);
	EXPECT_EQ(&event, asd.GetEvent());
	EXPECT_EQ(stc, asd.GetSTC());
}

TEST_F(AStyleDisplayF_Init, DisplayModifierOptions)
// Check that the member variables are updated with the method call.
{
	// create objects
	AStyleDisplay asd(0, 0, 0, 0, 0, 0);
	wxStyledTextCtrl* stc = this->CreateStyledTextCtrl();
	wxCommandEvent event(wxEVT_COMMAND_CHECKBOX_CLICKED, ID_ATTACH_NAMESPACE);

	// test the method
	EXPECT_EQ(nullptr, asd.GetEvent());
	EXPECT_EQ(nullptr, asd.GetSTC());
	asd.DisplayModifierOptions(event, stc);
	EXPECT_EQ(&event, asd.GetEvent());
	EXPECT_EQ(stc, asd.GetSTC());
}

TEST_F(AStyleDisplayF_Init, DisplayOtherOptions)
// Check that the member variables are updated with the method call.
{
	// create objects
	AStyleDisplay asd(0, 0, 0, 0, 0, 0);
	wxStyledTextCtrl* stc = this->CreateStyledTextCtrl();
	wxCommandEvent event(wxEVT_COMMAND_CHECKBOX_CLICKED, ID_ALIGN_METHOD_COLON);

	// test the method
	EXPECT_EQ(nullptr, asd.GetEvent());
	EXPECT_EQ(nullptr, asd.GetSTC());
	asd.DisplayOtherOptions(event, stc);
	EXPECT_EQ(&event, asd.GetEvent());
	EXPECT_EQ(stc, asd.GetSTC());
}

TEST_F(AStyleDisplayF_Init, DisplayPadOptions)
// Check that the member variables are updated with the method call.
{
	// create objects
	AStyleDisplay asd(0, 0, 0, 0, 0, 0);
	wxStyledTextCtrl* stc = this->CreateStyledTextCtrl();
	wxCommandEvent event(wxEVT_COMMAND_CHECKBOX_CLICKED, ID_BREAK_HEADER);

	// test the method
	EXPECT_EQ(nullptr, asd.GetEvent());
	EXPECT_EQ(nullptr, asd.GetSTC());
	asd.DisplayPadOptions(event, stc);
	EXPECT_EQ(&event, asd.GetEvent());
	EXPECT_EQ(stc, asd.GetSTC());
}

TEST_F(AStyleDisplayF_Init, DisplayStyleOptions)
// Check that the member variables are updated with the method call.
{
	// create objects
	AStyleDisplay asd(0, 0, 0, 0, 0, 0);
	wxStyledTextCtrl* stc = this->CreateStyledTextCtrl();
	wxCommandEvent event(wxEVT_COMMAND_CHECKBOX_CLICKED, ID_STYLE_ALLMAN);

	// test the method
	EXPECT_EQ(nullptr, asd.GetEvent());
	EXPECT_EQ(nullptr, asd.GetSTC());
	asd.DisplayStyleOptions(event, stc);
	EXPECT_EQ(&event, asd.GetEvent());
	EXPECT_EQ(stc, asd.GetSTC());
}

TEST_F(AStyleDisplayF_Init, DisplayTabOptions)
// Check that the member variables are updated with the method call.
{
	// create objects
	AStyleDisplay asd(0, 0, 0, 0, 0, 0);
	wxStyledTextCtrl* stc = this->CreateStyledTextCtrl();
	wxCommandEvent event(wxEVT_COMMAND_CHECKBOX_CLICKED, ID_INDENTWITH_SPACE);

	// test the method
	EXPECT_EQ(nullptr, asd.GetEvent());
	EXPECT_EQ(nullptr, asd.GetSTC());
	asd.DisplayTabOptions(event, stc);
	EXPECT_EQ(&event, asd.GetEvent());
	EXPECT_EQ(stc, asd.GetSTC());
}

//-------------------------------------------------------------------------
// AStyleDisplay Display*Options Tests
// An error message should be displayed for an unrecognized control.
//-------------------------------------------------------------------------

struct AStyleDisplayF_Error : public Test
{
	// Need this setup because of wxWidgets IMPLEMENT_APP_NO_MAIN.
	// It must be done to create a wxFrame object.
	// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
	// See the wxWidgets sample program mfctest.cpp.
	AStyleDisplayF_Error() : m_frame(nullptr)
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = nullptr;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != nullptr);	// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
		// now the objects can be created
		m_frame = new wxFrame(nullptr, wxID_ANY, "AStyleWxTest");
		wxASSERT(m_frame != nullptr);
	}
	virtual ~AStyleDisplayF_Error()
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
		wxASSERT(stc != nullptr);
		return stc;
	}
	wxFrame* m_frame;
};

TEST_F(AStyleDisplayF_Error, DisplayFormatOptions)
// Check that the switch statement has a default error handler.
{
	// create objects
	AStyleDisplay asd(0, 0, 0, 0, 0, 0);
	wxStyledTextCtrl* stc = this->CreateStyledTextCtrl();
	wxCommandEvent event(wxEVT_COMMAND_CHECKBOX_CLICKED, 99999);

	// test the method
	asd.DisplayFormatOptions(event, stc);
	EXPECT_STREQ("\nUnidentified format ID 99999.\n", stc->GetText());
}

TEST_F(AStyleDisplayF_Error, DisplayIndentOptions)
// Check that the switch statement has a default error handler.
{
	// create objects
	AStyleDisplay asd(0, 0, 0, 0, 0, 0);
	wxStyledTextCtrl* stc = this->CreateStyledTextCtrl();
	wxCommandEvent event(wxEVT_COMMAND_CHECKBOX_CLICKED, 99999);

	// test the method
	asd.DisplayIndentOptions(event, stc);
	EXPECT_STREQ("\nUnidentified indent ID 99999.\n", stc->GetText());
}

TEST_F(AStyleDisplayF_Error, DisplayModifierOptions)
// Check that the switch statement has a default error handler.
{
	// create objects
	AStyleDisplay asd(0, 0, 0, 0, 0, 0);
	wxStyledTextCtrl* stc = this->CreateStyledTextCtrl();
	wxCommandEvent event(wxEVT_COMMAND_CHECKBOX_CLICKED, 99999);

	// test the method
	asd.DisplayModifierOptions(event, stc);
	EXPECT_STREQ("\nUnidentified modifier ID 99999.\n", stc->GetText());
}

TEST_F(AStyleDisplayF_Error, DisplayOtherOptions)
// Check that the switch statement has a default error handler.
{
	// create objects
	AStyleDisplay asd(0, 0, 0, 0, 0, 0);
	wxStyledTextCtrl* stc = this->CreateStyledTextCtrl();
	wxCommandEvent event(wxEVT_COMMAND_CHECKBOX_CLICKED, 99999);

	// test the method
	asd.DisplayOtherOptions(event, stc);
	EXPECT_STREQ("\nUnidentified other ID 99999.\n", stc->GetText());
}

TEST_F(AStyleDisplayF_Error, DisplayPadOptions)
// Check that the switch statement has a default error handler.
{
	// create objects
	AStyleDisplay asd(0, 0, 0, 0, 0, 0);
	wxStyledTextCtrl* stc = this->CreateStyledTextCtrl();
	wxCommandEvent event(wxEVT_COMMAND_CHECKBOX_CLICKED, 99999);

	// test the method
	asd.DisplayPadOptions(event, stc);
	EXPECT_STREQ("\nUnidentified pad ID 99999.\n", stc->GetText());
}

TEST_F(AStyleDisplayF_Error, DisplayStyleOptions)
// Check that the switch statement has a default error handler.
{
	// create objects
	AStyleDisplay asd(0, 0, 0, 0, 0, 0);
	wxStyledTextCtrl* stc = this->CreateStyledTextCtrl();
	wxCommandEvent event(wxEVT_COMMAND_CHECKBOX_CLICKED, 99999);

	// test the method
	asd.DisplayStyleOptions(event, stc);
	EXPECT_STREQ("\nUnidentified style ID 99999.\n", stc->GetText());
}

TEST_F(AStyleDisplayF_Error, DisplayTabOptions)
// Check that the switch statement has a default error handler.
{
	// create objects
	AStyleDisplay asd(0, 0, 0, 0, 0, 0);
	wxStyledTextCtrl* stc = this->CreateStyledTextCtrl();
	wxCommandEvent event(wxEVT_COMMAND_CHECKBOX_CLICKED, 99999);

	// test the method
	asd.DisplayTabOptions(event, stc);
	EXPECT_STREQ("\nUnidentified tab ID 99999.\n", stc->GetText());
}

//----------------------------------------------------------------------------

}  // anonymous namespace
