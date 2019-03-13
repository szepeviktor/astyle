// EditorDlg.cpp
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include <wx/colordlg.h>
#include <wx/dcscreen.h>
#include <wx/fontenum.h>

#include "EditorDlg.h"

//-----------------------------------------------------------------------------
// EditorDlg class
//-----------------------------------------------------------------------------

// define static member variable
int EditorDlg::m_ix = 0;

EditorDlg::EditorDlg(ASFrame* frame, int page)
	: EditorDlgBase(frame), m_frame{frame}, m_page{page}
{
	m_editor = frame->GetEditor();
	// set editor options
	m_showDialogTips = frame->GetShowDialogTips();
	m_useBottomTabs->SetValue(frame->GetUseBottomTabs());
	m_useSmallToolbar->SetValue(frame->GetUseSmallToolbar());
	m_showToolbarTooltips->SetValue(frame->GetShowToolTips());
	m_showDialogTooltips->SetValue(frame->GetShowDialogTips());
	m_loadSession->SetValue(frame->GetLoadSession());
	m_hideFind->SetValue(frame->GetHideFindDialog());
	m_wrapSearch->SetValue(frame->GetWrapSearch());
	// set default font options
	wxFont defaultHeader = m_defaultHeader->GetFont();
	defaultHeader.SetWeight(wxFONTWEIGHT_BOLD);
	m_defaultHeader->SetFont(defaultHeader);
	SetDefaultFontOptions();
	// set comment font options
	wxFont commentHeader = m_commentHeader->GetFont();
	commentHeader.SetWeight(wxFONTWEIGHT_BOLD);
	m_commentHeader->SetFont(commentHeader);
	SetCommentFontOptions();
	// set stc style options
	const vector<TextStyle>& styleVector = m_frame->GetStyleVector();
	SetStcStyleOptions(styleVector);
	BuildDialogTips();
	// set selection to the previously selected page
	int pages = static_cast<int>(m_notebook->GetPageCount());
	if (m_page >= pages)
		m_page = 0;
	m_notebook->ChangeSelection(m_page);
	m_notebook->SetFocus();
	SetResetButton();
	// set the default sdb sizer button
	m_sdbSizer->GetAffirmativeButton()->SetDefault();
	// the reason for wxHAS_EVENT_BIND is described in AStyleDlg.cpp
#ifdef wxHAS_EVENT_BIND
	// set color button to display color dialog on mouse left up
	// must use bind because the event doesn't propagate
	m_foreground->Bind(wxEVT_LEFT_UP, &EditorDlg::OnForegroundClick, this);
#endif
}

void EditorDlg::BuildDialogTips() const
// Build dialog tool tips if requested.
{
	if (m_showDialogTips)
	{
		// options
		m_useBottomTabs->SetToolTip("Use bottom tabs for main window");
		m_useSmallToolbar->SetToolTip("Use small bitmaps for toolbar");
		m_showToolbarTooltips->SetToolTip("Show tooltips for toolbar");
		m_showDialogTooltips->SetToolTip("Show tooltips for dialog controls");
		m_loadSession->SetToolTip("Load files from the previous session");
		m_hideFind->SetToolTip("Hide find dialog after the first match\nUse F3 for next search");
		m_wrapSearch->SetToolTip("At end of page continue search at top of page");
		// fonts
		m_defaultFonts->SetToolTip("A monospace font used for everything except comments");
		m_defaultSizes->SetToolTip("Point size of the default font");
		m_commentFonts->SetToolTip("A proportional or monospace font used for comments");
		m_commentSizes->SetToolTip("Point size of the comment font");
		// styles
		m_foreground->SetToolTip("Select the text color.");
		m_bold->SetToolTip("Use bold text for this style.");
		m_italic->SetToolTip("Use italic text for this style.");
	}
}

wxFont EditorDlg::GetCommentFont() const
// Return the currently selected comment font.
{
	wxFont commentFont;
	wxString name = m_commentFonts->GetValue();
	commentFont.SetFaceName(name);
	wxString size = m_commentSizes->GetValue();
	long sizeInt = 0;
	size.ToLong(&sizeInt);
	commentFont.SetPointSize(static_cast<int>(sizeInt));
	return commentFont;
}

wxFont EditorDlg::GetDefaultFont() const
// Return the currently selected default font.
{
	wxFont defaultFont;
	wxString name = m_defaultFonts->GetValue();
	defaultFont.SetFaceName(name);
	wxString size = m_defaultSizes->GetValue();
	long sizeInt = 0;
	size.ToLong(&sizeInt);
	defaultFont.SetPointSize(static_cast<int>(sizeInt));
	return defaultFont;
}

void EditorDlg::GetExcludedFonts(wxArrayString& excludedFonts) const
// Symbol fonts excluded from the font list.
{
	//  all fonts beginning in lowercase are excluded
	excludedFonts.Add("Apple Symbols");
	excludedFonts.Add("Bookshelf Symbol 7");
	excludedFonts.Add("Dingbats");
	excludedFonts.Add("Gentium Basic");
	excludedFonts.Add("Gentium Book Basic");
	excludedFonts.Add("Marlett");
	excludedFonts.Add("MS Outlook");
	excludedFonts.Add("MS Reference 1");
	excludedFonts.Add("MS Reference 2");
	excludedFonts.Add("MS Reference Specialty");
	excludedFonts.Add("MT Extra");
	excludedFonts.Add("OpenSymbol");
	excludedFonts.Add("Standard Symbols L");
	excludedFonts.Add("Symbol");
	excludedFonts.Add("Webdings");
	excludedFonts.Add("Wingdings");
	excludedFonts.Add("Wingdings 2");
	excludedFonts.Add("Wingdings 3");
}

bool EditorDlg::GetHideFind() const
{
	return m_hideFind->IsChecked();
}

bool EditorDlg::GetLoadSession() const
{
	return m_loadSession->IsChecked();
}

vector<TextStyle>& EditorDlg::GetNewStyleVector()
{
	return m_newStyleVector;
}

int  EditorDlg::GetPage()
{
	return m_page;
}

bool EditorDlg::GetShowDialogTooltips() const
{
	return m_showDialogTooltips->IsChecked();
}

bool EditorDlg::GetShowToolbarTooltips() const
{
	return m_showToolbarTooltips->IsChecked();
}

bool EditorDlg::GetUseBottomTabs() const
{
	return m_useBottomTabs->IsChecked();
}

bool EditorDlg::GetUseSmallToolbar() const
{
	return m_useSmallToolbar->IsChecked();
}

bool EditorDlg::GetWrapSearch() const
{
	return m_wrapSearch->IsChecked();
}

void EditorDlg::OnBoldClick(wxCommandEvent& event)
{
	m_newStyleVector[m_ix].bold = event.IsChecked();
}

void EditorDlg::OnForegroundClick(wxMouseEvent& /*event*/)
{
	wxColourData data;
	data.SetColour(m_newStyleVector[m_ix].fore);
	wxColourDialog dialog(this, &data);
	if (dialog.ShowModal() == wxID_OK)
	{
		data = dialog.GetColourData();
		m_newStyleVector[m_ix].fore = data.GetColour();
		m_foreground->SetBackgroundColour(m_newStyleVector[m_ix].fore);
		m_foreground->Refresh();
	}
}

void EditorDlg::OnItalicClick(wxCommandEvent& event)
{
	m_newStyleVector[m_ix].italic = event.IsChecked();
}

void EditorDlg::OnListboxSelected(wxCommandEvent& event)
{
	m_ix = event.GetSelection();
	// set values for the new item
	m_foreground->SetBackgroundColour(m_newStyleVector[m_ix].fore);
	m_foreground->Refresh();
	m_bold->SetValue(m_newStyleVector[m_ix].bold);
	m_italic->SetValue(m_newStyleVector[m_ix].italic);
}

void EditorDlg::OnResetClick(wxCommandEvent& /*event*/)
{
	wxString page = m_notebook->GetPageText(m_page);
	assert(page == "Editor Options" || page == "Options"
	       || page == "Fonts" || page == "Styles");
	if (page == "Fonts")
	{
		// verify the reset
		wxString msg = "Do you want replace the current fonts with the default fonts?";
		if (ShowMessageDialog(msg, wxICON_QUESTION | wxYES_NO) == wxID_NO)
			return;
		// reset default font
		wxFont defaultFont = m_frame->FindDefaultFont();
		m_defaultFonts->SetStringSelection(defaultFont.GetFaceName());
		int defaultSize = defaultFont.GetPointSize();
		wxString defaultSizeStr = wxString::Format("%d", defaultSize);
		m_defaultSizes->SetStringSelection(defaultSizeStr);
		// reset comment font
		wxFont commentFont = m_frame->FindCommentFont();
		m_commentFonts->SetStringSelection(commentFont.GetFaceName());
		int commentSize = commentFont.GetPointSize();
		wxString commentSizeStr = wxString::Format("%d", commentSize);
		m_commentSizes->SetStringSelection(commentSizeStr);
	}
	else if (page == "Styles")
	{
		// verify the reset
		wxString msg = "Do you want replace the current styles with the default styles?";
		if (ShowMessageDialog(msg, wxICON_QUESTION | wxYES_NO) == wxID_NO)
			return;
		// reset styles
		m_newStyleVector = m_frame->GetConfig()->GetDefaultStyleOptions();
		m_foreground->SetBackgroundColour(m_newStyleVector[m_ix].fore);
		m_foreground->Refresh();
		m_bold->SetValue(m_newStyleVector[m_ix].bold);
		m_italic->SetValue(m_newStyleVector[m_ix].italic);
	}
}

void EditorDlg::OnNotebookPageChanged(wxBOOKCTRL_EVENT& event)
// A predefined book control event handler function.
// May be a Choicebook, Listbook, Notebook, or Treebook.
// Called when the page selection is changed.
{
	if (m_reset == nullptr)
		return;
	m_page = event.GetSelection();
	SetResetButton();
}

void EditorDlg::SetCommentFontOptions() const
// Set values in the comment font combo boxes.
{
	// Set comment fonts names.
	wxArrayString commentFontsAll;		// all comment fonts
	wxArrayString commentFonts;			// valid comment fonts
	wxFontEnumerator commentEnum;
	commentFontsAll = commentEnum.GetFacenames();
	SetFontNames(commentFontsAll, commentFonts);
	m_commentFonts->Set(commentFonts);
	m_commentFonts->SetValue(m_frame->GetCommentFont().GetFaceName());
	m_commentFonts->SetStringSelection(m_frame->GetCommentFont().GetFaceName());
	// Set comment fonts sizes.
	SetFontSizes(m_commentSizes);
	wxString commentPointSize;
	commentPointSize << m_frame->GetCommentFont().GetPointSize();
	m_commentSizes->SetValue(commentPointSize);
	m_commentSizes->SetStringSelection(commentPointSize);
}

void EditorDlg::SetDefaultFontOptions() const
// Set values in the default font combo boxes.
{
	// Set default font names.
	wxArrayString defaultFontsAll;		// all default fonts
	wxArrayString defaultFonts;			// valid default fonts
	defaultFontsAll = wxFontEnumerator::GetFacenames(wxFONTENCODING_SYSTEM, true);
	SetFontNames(defaultFontsAll, defaultFonts);
	m_defaultFonts->Set(defaultFonts);
	m_defaultFonts->SetValue(m_frame->GetDefaultFont().GetFaceName());
	m_defaultFonts->SetStringSelection(m_frame->GetDefaultFont().GetFaceName());
	// Set default font sizes.
	SetFontSizes(m_defaultSizes);
	wxString defaultPointSize;
	defaultPointSize << m_frame->GetDefaultFont().GetPointSize();
	m_defaultSizes->SetValue(defaultPointSize);
	m_defaultSizes->SetStringSelection(defaultPointSize);
}

void EditorDlg::SetFontNames(wxArrayString& fontNamesAll, wxArrayString& fontNames) const
// Sort and validate an array of font names and move them to a combo box.
{
	fontNamesAll.Sort();
	wxArrayString excludedFonts;
	GetExcludedFonts(excludedFonts);
	excludedFonts.Sort();
	size_t count = fontNamesAll.GetCount();
	size_t countx = excludedFonts.GetCount();
	for (size_t i = 0, ix = 0; i < count; i++)
	{
		if (fontNamesAll[i].StartsWith("@"))		// non-scalable bitmap font
			continue;
		if (fontNamesAll[i].StartsWith("AR "))		// new with Windows 7
			continue;
		if (islower(fontNamesAll[i][0]))				// special fonts (math,latex,etc)
			continue;
		while (ix < countx && excludedFonts[ix] < fontNamesAll[i])
			ix++;
		if (ix < countx && fontNamesAll[i] == excludedFonts[ix])
		{
			ix++;
			continue;
		}
		fontNames.Add(fontNamesAll[i]);
	}
}

void EditorDlg::SetFontSizes(wxComboBox* fontSizeList) const
// Move a list of font sizes to a combo box.
{
	wxString fontSize;
	for (size_t i = 0; i < 19; i++)
	{
		fontSize.Clear();
		fontSize << (i + 6);
		fontSizeList->Append(fontSize);
	}
}

void EditorDlg::SetResetButton() const
// Show or hide the reset button depending on the notebook page.
{
	wxString page = m_notebook->GetPageText(m_page);
	assert(page == "Editor Options" || page == "Options"
	       || page == "Fonts" || page == "Styles");
	if (page == "Fonts")
	{
		m_reset->SetLabel("Reset Fonts");
		if (m_showDialogTips)
			m_reset->SetToolTip("Reset fonts to their default value");
		else
			m_reset->SetToolTip(wxEmptyString);
		m_reset->Show();
		m_reset->Enable();
	}
	else if (page == "Styles")
	{
		m_reset->SetLabel("Reset Styles");
		if (m_showDialogTips)
			m_reset->SetToolTip("Reset styles to their default value");
		else
			m_reset->SetToolTip(wxEmptyString);
		m_reset->Show();
		m_reset->Enable();
	}
	else
	{
		m_reset->SetToolTip(wxEmptyString);
		m_reset->Hide();
		m_reset->Disable();
	}
}

void EditorDlg::SetStcStyleOptions(const vector<TextStyle>& styleVector)
// Move style vector options to the styles tab dialog.
{
	// set list box size
	const int numStyles = static_cast<int>(styleVector.size());
	wxFont stylesFont(*wxNORMAL_FONT);
	m_styles->SetFont(stylesFont);
	wxScreenDC dc;
	dc.SetFont(stylesFont);
	wxCoord charWidth = dc.GetCharWidth();
	wxCoord charHeight = dc.GetCharHeight();
#if defined(__WXMSW__)
	int width = charWidth * 16;
	int height = (charHeight + 1) * numStyles;
#elif defined(__WXOSX__)
	int width = charWidth * 14;
	int height = (charHeight + 6) * numStyles;
#else
	int width = charWidth * 14;
	int height = (charHeight + 2) * numStyles;
#endif
	if (width > 220)
		width = 220;
	if (height > 410)
		height = 410;
	m_styles->SetMinSize(wxSize(width, height));
	// resize
	m_editorDlgSizer->SetSizeHints(this);
	// copy the style vector for updating
	m_newStyleVector.reserve(numStyles);
	m_newStyleVector = styleVector;
	// build the array string for list box choices
	wxArrayString choices;
	for (int i = 0; i < numStyles; i++)
		choices.Add(" " + m_newStyleVector[i].name);
	m_styles->Set(choices);
	// set to last item selected
	m_styles->SetSelection(m_ix);
	// set checkbox and button displays
	wxCommandEvent event;
	event.SetInt(m_ix);
	OnListboxSelected(event);
}
