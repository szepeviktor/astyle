// AStyleDisplay.cpp
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include <wx/msgdlg.h>
//
#include "AStyleDisplay.h"
#include "AStyleDlgBase.h"	// for the AStyle option IDs
#include "Constants.h"

//-----------------------------------------------------------------------------
// AStyleDisplay class
// Contains the Preview STC display methods for AStyleDlg.
//-----------------------------------------------------------------------------

AStyleDisplay::AStyleDisplay(wxCheckBox* _useTabLength,
                             wxCheckBox* _attachClass,
                             wxCheckBox* _attachInline,
                             wxCheckBox* _indentSwitchBlocks,
                             wxCheckBox* _indentCaseBlocks,
                             wxCheckBox* _breakAfterLogical)
	:  m_useTabLength(_useTabLength),
	   m_attachClass(_attachClass),
	   m_attachInline(_attachInline),
	   m_indentSwitchBlocks(_indentSwitchBlocks),
	   m_indentCaseBlocks(_indentCaseBlocks),
	   m_breakAfterLogical(_breakAfterLogical)
{
	m_event = nullptr;
	m_stc = nullptr;
}

wxString AStyleDisplay::AlignConvertTabs(const wxString& text) const
// Align the convert tabs text for the styled text control display.
// Convert to spaces first because GetTextExtent doesn't work with tabs.
// The spacing to the comment will be 3 tabs, or the equivalent in spaces.
// Will work for proportional fonts.
{
	wxString line0 = AlignGetLine(text, 0);
	wxString line1 = AlignGetLine(text, 1);
	wxString line2 = AlignGetLine(text, 2);
	wxString line3 = AlignGetLine(text, 3);
	wxString line4 = AlignGetLine(text, 4);
	// replace all tabs in line 3
	int tabWidth = m_stc->GetTabWidth();
	wxString tabSpacing(' ', tabWidth);
	size_t numTabs = line3.Replace("\t", tabSpacing);
	// get the extent for line 3 code, excluding comment
	int start3 = line3.Find(';');
	assert(start3 != wxNOT_FOUND);
	start3++;
	wxString line3Code = line3.Mid(0, start3);
	// get line 3 comment
	int commentPos = line3.Find('/');
	assert(commentPos != wxNOT_FOUND);
	wxString line3Comment = line3.Mid(commentPos);
	// build the new line 3
	if (numTabs > 1)
		// use tabs for spacing
		line3 = line3Code + "\t\t\t" + line3Comment;
	else
	{
		// compute length of the partial tab after the code
		int codeSpaceEquivalents = AlignGetSpaceEquivalent(line3Code);
		int partialTab = tabWidth - (codeSpaceEquivalents % tabWidth);
		wxString line3PartialTabSpacing(' ', partialTab);
		line3 = line3Code + line3PartialTabSpacing + tabSpacing + tabSpacing + line3Comment;
	}
	return line0 + line1 + line2 + line3 + line4;
}

wxArrayString AStyleDisplay::AlignGetLineArray(const wxString& text) const
{
	wxArrayString lines;
	int start = -1;
	int end = -1;
	int len = static_cast<int>(text.length());
	while (end < len - 1)
	{
		start = end + 1;
		end = static_cast<int>(text.find('\n', start));
		if (end == wxNOT_FOUND)
			end = static_cast<int>(text.Length()) - 1;
		wxString line = text.Mid(start, end - start + 1);
		lines.Add(line);
	}
	return lines;
}

wxString AStyleDisplay::AlignGetLine(const wxString& text, int lineNumber) const
// return a line, including line end, of a multi-line string
{
	int start = -1;
	int end = -1;
	for (int i = 0; i <= lineNumber; i++)
	{
		start = end + 1;
		end = static_cast<int>(text.find('\n', start));
		if (end == wxNOT_FOUND)
			end = static_cast<int>(text.Length()) - 1;
	}
	return text.Mid(start, end - start + 1);
}

int AStyleDisplay::AlignGetSpaceEquivalent(wxString& line) const
// Get the number of space equivalents for a given text extent
// using the styled text control font.
{
	int extent;
	int h;
	m_stc->GetTextExtent(line, &extent, &h);
	// get space equivalents for the extent
	wxString indent;
	int spaceExtent = 0;
	while (spaceExtent < extent)
	{
		indent.Append(' ');
		m_stc->GetTextExtent(indent, &spaceExtent, &h);
	}
	return static_cast<int>(indent.Length());
}

wxString AStyleDisplay::AlignIndentAfterParens(const wxString& text) const
// Align the indent after parens text for the styled text control display.
// Will work for proportional fonts.
{
	wxString line0  = AlignGetLine(text, 0);
	wxString line1  = AlignGetLine(text, 1);
	wxString line2  = AlignGetLine(text, 2);
	wxString line3  = AlignGetLine(text, 3);
	wxString line4  = AlignGetLine(text, 4);
	wxString line5  = AlignGetLine(text, 5);
	wxString line6  = AlignGetLine(text, 6);
	wxString line7  = AlignGetLine(text, 7);
	wxString line8  = AlignGetLine(text, 8);
	wxString line9  = AlignGetLine(text, 9);
	wxString line10 = AlignGetLine(text, 10);

	// align line 2 to line 1
	int i1 = line1.Find("bool");
	assert(i1 != wxNOT_FOUND);
	wxString line1Extent = line1.Mid(0, i1);
	int line1NumIndents = AlignGetSpaceEquivalent(line1Extent);
	wxString space1Indent(' ', line1NumIndents);
	AlignReplaceIndent(line2, space1Indent);
	// align line 5 to line 4
	int i4 = line4.Find("bar");
	assert(i4 != wxNOT_FOUND);
	wxString line4Extent = line4.Mid(0, i4);
	int line4NumSpaces = AlignGetSpaceEquivalent(line4Extent);
	wxString space4Indent(' ', line4NumSpaces);
	AlignReplaceIndent(line5, space4Indent);
	// align line 8 to line 7
	int i7 = line7.Find("foo");
	assert(i7 != wxNOT_FOUND);
	wxString line7Extent = line7.Mid(0, i7);
	int line7NumSpaces = AlignGetSpaceEquivalent(line7Extent);
	wxString space7Indent(' ', line7NumSpaces);
	AlignReplaceIndent(line8, space7Indent);
	// return the text
	return line0 + line1 + line2 + line3 + line4 + line5 +
	       line6 + line7 + line8 + line9 + line10;
}

wxString AStyleDisplay::AlignMaxContinuation(const wxString& text) const
// Align the max continuation text for the styled text control display.
// Will work for proportional fonts.
{
	wxString line0 = AlignGetLine(text, 0);
	wxString line1 = AlignGetLine(text, 1);
	wxString line2 = AlignGetLine(text, 2);
	wxString line3 = AlignGetLine(text, 3);
	wxString line4 = AlignGetLine(text, 4);
	wxString line5 = AlignGetLine(text, 5);
	wxString line6 = AlignGetLine(text, 6);
	wxString line7 = AlignGetLine(text, 7);
	wxString line8 = AlignGetLine(text, 8);
	wxString line9 = AlignGetLine(text, 9);

	// align lines 4 and 5 to line 3
	int i3 = line3.Find("red");
	assert(i3 != wxNOT_FOUND);
	wxString line3Extent = line3.Mid(0, i3);
	int line3NumIndents = AlignGetSpaceEquivalent(line3Extent);
	wxString space3Indent(' ', line3NumIndents);
	AlignReplaceIndent(line4, space3Indent);
	AlignReplaceIndent(line5, space3Indent);
	// align lines 8 and 9 to line 7
	int i7 = line7.Find("bar");
	assert(i7 != wxNOT_FOUND);
	wxString line7Extent = line7.Mid(0, i7);
	int line7NumSpaces = AlignGetSpaceEquivalent(line7Extent);
	wxString space7Indent(' ', line7NumSpaces);
	AlignReplaceIndent(line8, space7Indent);
	AlignReplaceIndent(line9, space7Indent);
	// return the text
	return line0 + line1 + line2 + line3 + line4 +
	       line5 + line6 + line7 + line8 + line9;
}

wxString AStyleDisplay::AlignMethodColon(const wxString& text) const
// Align the align-method-colon text for the styled text control display.
// Will work for proportional fonts.
{
	wxArrayString line = AlignGetLineArray(text);
	size_t i = 0;
	int indentsToColon = 0;

	// find the first line containing a colon
	for (i = 0; i < line.Count(); i++)
	{
		int colon = static_cast<int>(line[i].find(':'));
		if (colon == wxNOT_FOUND)
			continue;
		wxString lineExtent = line[i].Mid(0, colon);
		indentsToColon = AlignGetSpaceEquivalent(lineExtent);
		break;
	}

	// align remaining lines
	for (++i; i < line.Count(); i++)
	{
		int lineText = static_cast<int>(line[i].find_first_not_of(" \t"));
		int colon = static_cast<int>(line[i].find(':'));
		assert(colon != wxNOT_FOUND);
		wxString lineTextExtent = line[i].Mid(lineText, colon - lineText);
		int lineTextIndents = AlignGetSpaceEquivalent(lineTextExtent);
		int lineNumIndents = indentsToColon - lineTextIndents;
		wxString spaceIndent(' ', lineNumIndents);
		AlignReplaceIndent(line[i], spaceIndent);
	}

	// return the aligned string
	wxString alignedText;
	for (i = 0; i < line.size(); i++)
	{
		alignedText += line[i];
	}
	return alignedText;
}

void AStyleDisplay::AlignReplaceIndent(wxString& line, wxString& indent) const
// Replace the indent characters on a given line.
{
	size_t firstText = line.find_first_not_of(" \t");
	line.replace(0, firstText, indent);
}

void AStyleDisplay::DisplayFormatOptions(wxCommandEvent& event, wxStyledTextCtrl* formatPreviewSTC)
{
	m_event = &event;
	m_stc = formatPreviewSTC;
	wxString textOut;

	m_stc->ClearAll();
	m_stc->SetTabWidth(5);
	// wxSTC_WS_INVISIBLE, wxSTC_WS_VISIBLEALWAYS, wxSTC_WS_VISIBLEAFTERINDENT
	m_stc->SetViewWhiteSpace(wxSTC_WS_INVISIBLE);
	m_stc->SetUseHorizontalScrollBar(false);

	switch (m_event->GetId())
	{
		case ID_ADD_BRACES:
			textOut = StcFormat_AddBraces();
			break;

		case ID_ADD_OL_BRACES:
			textOut = StcFormat_AddOneLineBraces();
			break;

		case ID_ATTACH_RETURN_TYPE:
			textOut = StcFormat_AttachReturnType();
			break;

		case ID_ATTACH_RETURN_TYPE_DECL:
			textOut = StcFormat_AttachReturnTypeDecl();
			break;

		case ID_BREAK_CLOSING:
			textOut = StcFormat_BreakClosingBraces();
			break;

		case ID_BREAK_ELSEIF:
			textOut = StcFormat_BreakElseIf();
			break;

		case ID_BREAK_OL_HEADERS:
			textOut = StcFormat_BreakOneLineHeaders();
			break;

		case ID_BREAK_RETURN_TYPE:
			textOut = StcFormat_BreakReturnType();
			break;

		case ID_BREAK_RETURN_TYPE_DECL:
			textOut = StcFormat_BreakReturnTypeDecl();
			break;

		case ID_CLOSE_TEMPLATES:
			textOut = StcFormat_CloseTemplates();
			break;

		case ID_CONVERT_TABS:
			// text is aligned for proportional fonts
			m_stc->SetViewWhiteSpace(wxSTC_WS_VISIBLEAFTERINDENT);
			textOut = StcFormat_ConvertTabs();
			break;

		case ID_KEEP_OL_BLOCKS:
			textOut = StcFormat_KeepOneLineBlocks();
			break;

		case ID_KEEP_OL_STATEMENTS:
			textOut = StcFormat_KeepOneLineStatements();
			break;

		case ID_MAX_CODE_LENGTH:
		case ID_MAX_CODE_LENGTH_DISPLAY:
		case ID_BREAK_AFTER_LOGICAL:
			m_stc->SetUseHorizontalScrollBar(true);
			m_stc->SetScrollWidth(400);
			textOut = StcFormat_MaxCodeLength_BreakAfterLogical();
			break;

		case ID_REMOVE_BRACES:
			textOut = StcFormat_RemoveBraces();
			break;

		case ID_REMOVE_COMMENT_PREFIX:
			textOut = StcFormat_RemoveCommentPrefix();
			break;

		default:
		{
#ifndef ASTYLEWX_TEST
			wxMessageBox(wxString::Format("Unidentified format ID %d.", m_event->GetId()));
#endif
			textOut = (wxString::Format("\nUnidentified format ID %d.\n", m_event->GetId()));
		}
		break;

	}	// switch

	m_stc->AppendText(textOut);
	LexStcText();
}

void AStyleDisplay::DisplayIndentOptions(wxCommandEvent& event, wxStyledTextCtrl* indentPreviewSTC)
{
	m_event = &event;
	m_stc = indentPreviewSTC;
	wxString textOut;

	m_stc->ClearAll();
	m_stc->SetTabWidth(5);
	// wxSTC_WS_INVISIBLE, wxSTC_WS_VISIBLEALWAYS, wxSTC_WS_VISIBLEAFTERINDENT
	m_stc->SetViewWhiteSpace(wxSTC_WS_INVISIBLE);

	switch (m_event->GetId())
	{
		case ID_INDENT_AFTER_PAREN:
			textOut = StcIndent_IndentAfterParen();
			break;

		case ID_INDENT_CASE:
		case ID_INDENT_SWITCH:
			textOut = StcIndent_IndentCase_IndentSwitch();
			break;

		case ID_INDENT_CLASS:
			textOut = StcIndent_IndentClass();
			break;

		case ID_INDENT_COL1_COMMENT:
			textOut = StcIndent_IndentCol1Comment();
			break;

		case ID_INDENT_CONTINUATION:
			textOut = StcIndent_IndentContinuation();
			break;

		case ID_INDENT_GOTO:
			textOut = StcIndent_IndentGoTo();
			break;

		case ID_INDENT_MODIFIER:
			textOut = StcIndent_IndentModifier();
			break;

		case ID_INDENT_NAMESPACE:
			textOut = StcIndent_IndentNamespace();
			break;

		case ID_INDENT_PREPROC_BLOCK:
			textOut = StcIndent_IndentPreprocBlock();
			break;

		case ID_INDENT_PREPROC_COND:
			textOut = StcIndent_IndentPreprocCond();
			break;

		case ID_INDENT_PREPROC_DEFINE:
			textOut = StcIndent_IndentPreprocDefine();
			break;

		case ID_MIN_CONDITIONAL_DISPLAY:
			textOut = StcIndent_MinConditionalDisplay();
			break;

		case ID_MAX_CONTINUATION_DISPLAY:
			textOut = StcIndent_MaxContinuationDisplay();
			break;

		default:
		{
#ifndef ASTYLEWX_TEST
			wxMessageBox(wxString::Format("Unidentified indent ID %d.", m_event->GetId()));
#endif
			textOut = (wxString::Format("\nUnidentified indent ID %d.\n", m_event->GetId()));
		}
		break;

	}	// switch

	m_stc->AppendText(textOut);
	LexStcText();
}

void AStyleDisplay::DisplayModifierOptions(wxCommandEvent& event, wxStyledTextCtrl* tabPreviewSTC)
{
	m_event = &event;
	m_stc = tabPreviewSTC;
	wxString textOut;

	// brace modifiers use the tab page
	m_stc->ClearAll();
	m_stc->SetTabWidth(5);
	// wxSTC_WS_INVISIBLE, wxSTC_WS_VISIBLEALWAYS, wxSTC_WS_VISIBLEAFTERINDENT
	m_stc->SetViewWhiteSpace(wxSTC_WS_INVISIBLE);

	switch (m_event->GetId())
	{
		case ID_ATTACH_CLASS:
			textOut = StcModifier_AttachClass_AttachInline();
			break;

		case ID_ATTACH_CLOSING_WHILE:
			textOut = StcModifier_AttachClosingWhile();
			break;

		case ID_ATTACH_EXTERN_C:
			textOut = StcModifier_AttachExternC();
			break;

		case ID_ATTACH_INLINE:
			textOut = StcModifier_AttachClass_AttachInline();
			break;

		case ID_ATTACH_NAMESPACE:
			textOut = StcModifier_AttachNamespace();
			break;

		default:
		{
#ifndef ASTYLEWX_TEST
			wxMessageBox(wxString::Format("Unidentified modifier ID %d.", m_event->GetId()));
#endif
			textOut = (wxString::Format("\nUnidentified modifier ID %d.\n", m_event->GetId()));
		}
		break;

	}	// switch

	m_stc->AppendText(textOut);
	LexStcText("{}");
	LexStcText(".");	// for ". . ." in attach namespace
}

void AStyleDisplay::DisplayOtherOptions(wxCommandEvent& event, wxStyledTextCtrl* otherPreviewSTC)
{
	m_event = &event;
	m_stc = otherPreviewSTC;
	wxString textOut;

	m_stc->ClearAll();
	m_stc->SetTabWidth(5);
	// wxSTC_WS_INVISIBLE, wxSTC_WS_VISIBLEALWAYS, wxSTC_WS_VISIBLEAFTERINDENT
	m_stc->SetViewWhiteSpace(wxSTC_WS_INVISIBLE);

	switch (m_event->GetId())
	{
		case ID_PAD_METHOD_COLON:
		case ID_PAD_METHOD_COLON_DISPLAY:
			textOut = StcOther_PadMethodColon();
			break;

		case ID_PAD_METHOD_PREFIX:
			textOut = StcOther_PadMethodPrefix();
			break;

		case ID_UNPAD_METHOD_PREFIX:
			textOut = StcOther_UnpadMethodPrefix();
			break;

		case ID_PAD_RETURN_TYPE:
			textOut = StcOther_PadReturnType();
			break;

		case ID_UNPAD_RETURN_TYPE:
			textOut = StcOther_UnpadReturnType();
			break;

		case ID_PAD_PARAM_TYPE:
			textOut = StcOther_PadParamType();
			break;

		case ID_UNPAD_PARAM_TYPE:
			textOut = StcOther_UnpadParamType();
			break;

		case ID_ALIGN_METHOD_COLON:
			textOut = StcOther_AlignMethodColon();
			break;

		default:
		{
#ifndef ASTYLEWX_TEST
			wxMessageBox(wxString::Format("Unidentified other ID %d.", m_event->GetId()));
#endif
			textOut = (wxString::Format("\nUnidentified other ID %d.\n", m_event->GetId()));
		}
		break;

	}	// switch

	m_stc->AppendText(textOut);
	LexStcText("-:");
}

void AStyleDisplay::DisplayPadOptions(wxCommandEvent& event, wxStyledTextCtrl* padPreviewSTC)
{
	m_event = &event;
	m_stc = padPreviewSTC;
	wxString textOut;

	m_stc->ClearAll();
	m_stc->SetTabWidth(5);
	// wxSTC_WS_INVISIBLE, wxSTC_WS_VISIBLEALWAYS, wxSTC_WS_VISIBLEAFTERINDENT
	m_stc->SetViewWhiteSpace(wxSTC_WS_INVISIBLE);

	switch (m_event->GetId())
	{
		case ID_ALIGN_POINTER:
		case ID_ALIGN_POINTER_DISPLAY:
			textOut = StcPad_AlignPointer();
			break;

		case ID_ALIGN_REFERENCE:
		case ID_ALIGN_REFERENCE_DISPLAY:
			textOut = StcPad_AlignReference();
			break;

		case ID_BREAK_ALL:
			textOut = StcPad_BreakAll();
			break;

		case ID_BREAK_HEADER:
			textOut = StcPad_BreakHeader();
			break;

		case ID_DELETE_EMPTY_LINE:
			textOut = StcPad_DeleteEmptyLine();
			break;

		case ID_FILL_EMPTY_LINE:
			m_stc->SetViewWhiteSpace(wxSTC_WS_VISIBLEALWAYS);
			textOut = StcPad_FillEmptyLine();
			break;

		case ID_PAD_FIRST_PAREN_OUT:
			textOut = StcPad_PadFirstParenOut();
			break;

		case ID_PAD_HEADER:
			textOut = StcPad_PadHeader();
			break;

		case ID_PAD_OPERATOR:
			textOut = StcPad_PadOperator();
			break;

		case ID_PAD_COMMA:
			textOut = StcPad_PadComma();
			break;

		case ID_PAD_PAREN_OUT:
			textOut = StcPad_PadParenOut();
			break;

		case ID_PAD_PAREN_IN:
			textOut = StcPad_PadParenIn();
			break;

		case ID_UNPAD_PAREN:
			textOut = StcPad_UnpadParen();
			break;

		default:
		{
#ifndef ASTYLEWX_TEST
			wxMessageBox(wxString::Format("Unidentified pad ID %d.", m_event->GetId()));
#endif
			textOut = (wxString::Format("\nUnidentified pad ID %d.\n", m_event->GetId()));
		}
		break;

	}	// switch

	m_stc->AppendText(textOut);
	LexStcText();
}

void AStyleDisplay::DisplayStyleOptions(wxCommandEvent& event, wxStyledTextCtrl* stylePreviewSTC)
{
	m_event = &event;
	m_stc = stylePreviewSTC;
	wxString textOut;

	m_stc->ClearAll();
	m_stc->SetTabWidth(5);
	// wxSTC_WS_INVISIBLE, wxSTC_WS_VISIBLEALWAYS, wxSTC_WS_VISIBLEAFTERINDENT
	m_stc->SetViewWhiteSpace(wxSTC_WS_INVISIBLE);

	switch (m_event->GetId())
	{
		case ID_STYLE_ALLMAN:
			textOut = StcStyle_Allman();
			break;

		case ID_STYLE_GNU:
			textOut = StcStyle_Gnu();
			break;

		case ID_STYLE_GOOGLE:
			textOut = StcStyle_Google();
			break;

		case ID_STYLE_HORSTMANN:
			textOut = StcStyle_Horstmann();
			break;

		case ID_STYLE_JAVA:
			textOut = StcStyle_Java();
			break;

		case ID_STYLE_KR:
			textOut = StcStyle_KR();
			break;

		case ID_STYLE_LINUX:
			textOut = StcStyle_Linux();
			break;

		case ID_STYLE_LISP:
			textOut = StcStyle_Lisp();
			break;

		case ID_STYLE_MOZILLA:
			textOut = StcStyle_Mozilla();
			break;

		case ID_STYLE_NONE:
			textOut = StcStyle_None();
			break;

		case ID_STYLE_PICO:
			textOut = StcStyle_Pico();
			break;

		case ID_STYLE_RATLIFF:
			textOut = StcStyle_Ratliff();
			break;

		case ID_STYLE_STROUSTRUP:
			textOut = StcStyle_Stroustrup();
			break;

		case ID_STYLE_VTK:
			textOut = StcStyle_Vtk();
			break;

		case ID_STYLE_WEBKIT:
			textOut = StcStyle_WebKit();
			break;

		case ID_STYLE_WHITESMITH:
			textOut = StcStyle_Whitesmith();
			break;

		case ID_STYLE_1TBS:
			textOut = StcStyle_1TBS();
			break;

		default:
		{
#ifndef ASTYLEWX_TEST
			wxMessageBox(wxString::Format("Unidentified style ID %d.", m_event->GetId()));
#endif
			textOut = (wxString::Format("\nUnidentified style ID %d.\n", m_event->GetId()));
		}
		break;

	}	// switch

	m_stc->AppendText(textOut);
	LexStcText("{}");
}

void AStyleDisplay::DisplayTabOptions(wxCommandEvent& event, wxStyledTextCtrl* tabPreviewSTC)
{
	m_event = &event;
	m_stc = tabPreviewSTC;
	wxString textOut;

	m_stc->ClearAll();
	m_stc->SetTabWidth(4);
	// wxSTC_WS_INVISIBLE, wxSTC_WS_VISIBLEALWAYS, wxSTC_WS_VISIBLEAFTERINDENT
	m_stc->SetViewWhiteSpace(wxSTC_WS_VISIBLEALWAYS);

	switch (m_event->GetId())
	{
		case ID_INDENT_LENGTH_DISPLAY:
		{
			// flag to alternate the display
			static bool displayLong = true;
			displayLong = !displayLong;
			int tabWidth = displayLong ? 6 : 4;
			m_stc->SetTabWidth(tabWidth);
			textOut = StcTab_IndentLengthDisplay();
		}
		break;

		case ID_INDENTWITH_FTAB:
		case ID_USE_TAB_LENGTH:
			if (m_useTabLength->IsChecked())
				m_stc->SetTabWidth(8);
			textOut = StcTab_IndentWithForceTab_UseTabLength();
			break;

		case ID_INDENTWITH_SPACE:
			textOut = StcTab_IndentWithSpace();
			break;

		case ID_INDENTWITH_TAB:
			textOut = StcTab_IndentWithTab();
			break;

		default:
		{
#ifndef ASTYLEWX_TEST
			wxMessageBox(wxString::Format("Unidentified tab ID %d.", m_event->GetId()));
#endif
			textOut = (wxString::Format("\nUnidentified tab ID %d.\n", m_event->GetId()));
		}
		break;

	}	// switch

	m_stc->AppendText(textOut);
	LexStcText();
}

void AStyleDisplay::LexStcText(wxString boldChars /*wxEmptyString*/)
// set style options for the preview styled text control
// use styles 0 to 31
{
	const int COMMENT = 10;
	const int BOLD_CHAR = 20;
	bool isInComment = false;
	bool isInLineComment = false;
	int textLength = static_cast<int>(m_stc->GetTextLength());
	for (int i = 0; i < textLength; i++)
	{
		int currentChar = m_stc->GetCharAt(i);
		int previousChar = m_stc->GetCharAt(i - 1);
		// find comments
		if (currentChar == '/')
		{
			int nextChar = m_stc->GetCharAt(i + 1);
			if (nextChar == '*')
				isInComment = true;
			else if (nextChar == '/')
				isInLineComment = true;
		}
		if (currentChar == '\n')
			isInLineComment = false;
		if (isInComment || isInLineComment)
		{
#if wxCHECK_VERSION(3, 1, 1)
			m_stc->StartStyling(i);
#else
			// depreciated in version 3.1.1 of STC
			m_stc->StartStyling(i, 0);
#endif
			m_stc->SetStyling(1, COMMENT);
		}
		if (isInComment && previousChar == '*' && currentChar == '/')
			isInComment = false;
		// find bold chars
		for (size_t j = 0; j < boldChars.Length(); j++)
		{
			int boldChar = boldChars[j];
			if (currentChar == boldChar)
			{
#if wxCHECK_VERSION(3, 1, 1)
				m_stc->StartStyling(i);
#else
				// depreciated in version 3.1.1 of STC
				m_stc->StartStyling(i, 0);
#endif
				m_stc->SetStyling(1, BOLD_CHAR);
			}
		}
	}
	// set the style options
	m_stc->StyleSetBold(BOLD_CHAR, true);
	m_stc->StyleSetItalic(COMMENT, true);
}

//-----------------------------------------------------------------------------
// STC Display for the Format Tab
//-----------------------------------------------------------------------------

wxString AStyleDisplay::StcFormat_AddBraces() const
{
	wxString checked =     "              \n"
	                       "if (isFoo) {  \n"
	                       "	bar();    \n"
	                       "}             \n";

	wxString unchecked =   "              \n"
	                       "if (isFoo)    \n"
	                       "	bar();    \n"
	                       "                ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcFormat_AddOneLineBraces() const
{
	wxString checked =     "             \n"
	                       "if (isFoo)   \n"
	                       "{ bar(); }   \n"
	                       "             \n"
	                       "               ";

	wxString unchecked =   "             \n"
	                       "if (isFoo)   \n"
	                       "	bar();   \n"
	                       "               ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcFormat_AttachReturnType() const
{
	wxString checked =     "                     \n"
	                       "void Foo(bool isFoo) \n"
	                       "{ ... }              \n";

	wxString unchecked =   "                     \n"
	                       "void                 \n"
	                       "Foo(bool isFoo)      \n"
	                       "{ ... }                ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcFormat_AttachReturnTypeDecl() const
{
	wxString checked =     "                     \n"
	                       "void Foo(bool isFoo);\n";

	wxString unchecked =   "                     \n"
	                       "void                 \n"
	                       "Foo(bool isFoo);       ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcFormat_BreakClosingBraces() const
{
	wxString checked =     "                       \n"
	                       "void Foo(bool isFoo)   \n"
	                       "{                      \n"
	                       "	if (isFoo) {       \n"
	                       "		bar();         \n"
	                       "	}                  \n"
	                       "	else {             \n"
	                       "		anotherBar();  \n"
	                       "	}                  \n"
	                       "}                        ";

	wxString unchecked =   "                       \n"
	                       "void Foo(bool isFoo)   \n"
	                       "{                      \n"
	                       "	if (isFoo) {       \n"
	                       "		bar();         \n"
	                       "	} else {           \n"
	                       "		anotherBar();  \n"
	                       "	}                  \n"
	                       "}                        ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcFormat_BreakElseIf() const
{
	wxString checked =     "                    \n"
	                       "if (isFoo) {        \n"
	                       "	bar();          \n"
	                       "}                   \n"
	                       "else                \n"
	                       "	if (isFoo1()) { \n"
	                       "		bar1();     \n"
	                       "	}               \n"
	                       "	else            \n"
	                       "		if (isFoo2()) {\n"
	                       "			bar2(); \n"
	                       "		}             ";

	wxString unchecked =   "                    \n"
	                       "if (isFoo) {        \n"
	                       "	bar();          \n"
	                       "}                   \n"
	                       "else if (isFoo1()) {\n"
	                       "	bar1();         \n"
	                       "}                   \n"
	                       "else if (isFoo2()) {\n"
	                       "	bar2();         \n"
	                       "}                     ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcFormat_BreakOneLineHeaders() const
{
	wxString checked =     "                           \n"
	                       "	if (isFoo1)            \n"
	                       "		bar1();            \n"
	                       "                           \n"
	                       "	if (isFoo2) {          \n"
	                       "		bar2();            \n"
	                       "	}                      \n"
	                       "                            ";

	wxString unchecked =   "                           \n"
	                       "	if (isFoo1) bar1();    \n"
	                       "                           \n"
	                       "	if (isFoo2) { bar2(); }\n"
	                       "                            ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcFormat_BreakReturnType() const
{
	wxString checked =     "                     \n"
	                       "void                 \n"
	                       "Foo(bool isFoo)      \n"
	                       "{ ... }                ";

	wxString unchecked =   "                     \n"
	                       "void Foo(bool isFoo) \n"
	                       "{ ... }              \n";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcFormat_BreakReturnTypeDecl() const
{
	wxString checked =     "                     \n"
	                       "void                 \n"
	                       "Foo(bool isFoo);       ";

	wxString unchecked =   "                     \n"
	                       "void Foo(bool isFoo);\n";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcFormat_CloseTemplates() const
{
	wxString checked =     "\n"
	                       "Stack<int,List<int>> stack1;";

	wxString unchecked =   "\n"
	                       "Stack<int,List<int> > stack1;";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcFormat_ConvertTabs() const
{
	// this case shows whitespace, cannot have formatting spaces in text
	wxString checked =     "\n"
	                       "if (Foo)\n"
	                       "{\n"
	                       "	bar();         // comment\n"
	                       "}";

	// this case shows whitespace, cannot have formatting spaces in text
	wxString unchecked =   "\n"
	                       "if (Foo)\n"
	                       "{\n"
	                       "	bar();\t\t\t// comment\n"
	                       "}";

	// text is aligned for proportional fonts
	return m_event->IsChecked() ? AlignConvertTabs(checked) : AlignConvertTabs(unchecked);
}

wxString AStyleDisplay::StcFormat_KeepOneLineBlocks() const
{
	wxString checked =     "                   \n"
	                       "if (isFoo)         \n"
	                       "{ foo=false;  bar=true; } ";

	wxString unchecked =   "                   \n"
	                       "if (isFoo)         \n"
	                       "{                  \n"
	                       "	foo=false;     \n"
	                       "	bar=true;      \n"
	                       "}                    ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcFormat_KeepOneLineStatements() const
{
	wxString checked =     "                   \n"
	                       "if (isFoo)         \n"
	                       "{                  \n"
	                       "	foo=false;  bar=true;\n"
	                       "}                    ";

	wxString unchecked =   "                   \n"
	                       "if (isFoo)         \n"
	                       "{                  \n"
	                       "	foo=false;     \n"
	                       "	bar=true;      \n"
	                       "}                  \n"
	                       "                     ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcFormat_MaxCodeLength_BreakAfterLogical() const
{
	// flag to alternate the display
	static bool displayBrokenLine = true;
	displayBrokenLine = displayBrokenLine ? false : true;
	if (m_event->GetId() == ID_BREAK_AFTER_LOGICAL)
		displayBrokenLine = true;
	else
	{
		if (m_event->GetId() == ID_MAX_CODE_LENGTH)
		{
			if (m_event->GetSelection() == 0)
				displayBrokenLine = false;
			else
				displayBrokenLine = true;
		}
	}

	wxString textOut;
	if (displayBrokenLine == false)
	{
		textOut =     "                   \n"
		              "if (this1 == that1 || this2 == that2 || this3 == that3)\n"
		              "	bar();            \n";
	}
	else if (m_breakAfterLogical->IsChecked())
	{
		textOut =     "                       \n"
		              "if (this1 == that1 ||  \n"
		              "		this2 == that2 || \n"
		              "		this3 == that3)   \n"
		              "	bar();                \n";
	}
	else
	{
		textOut =     "                       \n"
		              "if (this1 == that1     \n"
		              "		|| this2 == that2 \n"
		              "		|| this3 == that3)\n"
		              "	bar();                \n";
	}
	return textOut;
}

wxString AStyleDisplay::StcFormat_RemoveBraces() const
{
	wxString checked   =   "              \n"
	                       "if (isFoo)    \n"
	                       "	bar();    \n"
	                       "                ";

	wxString unchecked =   "              \n"
	                       "if (isFoo)    \n"
	                       "{             \n"
	                       "	bar();    \n"
	                       "}             \n";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcFormat_RemoveCommentPrefix() const
{
	wxString checked   =   "                  \n"
	                       "/*                \n"
	                       "    comment line 1\n"
	                       "    comment line 2\n"
	                       "*/                ";

	wxString unchecked =   "                  \n"
	                       "/*                \n"
	                       " * comment line 1 \n"
	                       " * comment line 2 \n"
	                       " */               ";

	return m_event->IsChecked() ? checked : unchecked;
}

//-----------------------------------------------------------------------------
// STC Display for the Indent Tab
//-----------------------------------------------------------------------------

wxString AStyleDisplay::StcIndent_IndentAfterParen() const
{
	wxString checked =     "                     \n"
	                       "void Foo(bool bar1,  \n"
	                       "	bool bar2)       \n"
	                       "{                    \n"
	                       "isLongFunction(bar1, \n"
	                       "	bar2);           \n"
	                       "                     \n"
	                       "isLongVariable = foo1\n"
	                       "	|| foo2;         \n"
	                       "};                   ";

	wxString unchecked =   "                     \n"
	                       "void Foo(bool bar1,  \n"
	                       "         bool bar2)  \n"
	                       "{                    \n"
	                       "isLongFunction(bar1, \n"
	                       "               bar2);\n"
	                       "                     \n"
	                       "isLongVariable = foo1\n"
	                       "                 || foo2;\n"
	                       "};                   ";

	// text is aligned for proportional fonts
	return m_event->IsChecked() ? checked : AlignIndentAfterParens(unchecked);
}

wxString AStyleDisplay::StcIndent_IndentCase_IndentSwitch() const
{
	// indent case and indent switch work together
	bool switchChecked = m_indentSwitchBlocks->IsChecked();
	bool caseChecked   = m_indentCaseBlocks->IsChecked();
	wxString display;

	if (switchChecked)
	{
		if (caseChecked)
		{
			display =      "                   \n"         // yes switch - yes case
			               "switch (foo)       \n"
			               "{                  \n"
			               "	case 1:        \n"
			               "		a += 1;    \n"
			               "		break;     \n"
			               "                   \n"
			               "	case 2:        \n"
			               "		{          \n"
			               "			a += 2;\n"
			               "			break; \n"
			               "		}          \n"
			               "}                  ";
		}
		else
		{
			display =      "                   \n"         // yes switch - no case
			               "switch (foo)       \n"
			               "{                  \n"
			               "	case 1:        \n"
			               "		a += 1;    \n"
			               "		break;     \n"
			               "                   \n"
			               "	case 2:        \n"
			               "	{              \n"
			               "		a += 2;    \n"
			               "		break;     \n"
			               "	}              \n"
			               "}                  ";
		}
	}
	else
	{
		if (caseChecked)
		{
			display =      "                   \n"         // no switch - yes case
			               "switch (foo)       \n"
			               "{                  \n"
			               "case 1:            \n"
			               "	a += 1;         \n"
			               "	break;         \n"
			               "                   \n"
			               "case 2:            \n"
			               "	{              \n"
			               "		a += 2;    \n"
			               "		break;     \n"
			               "	}              \n"
			               "}                  ";
		}
		else
		{
			display =      "                   \n"         // no switch - no case
			               "switch (foo)       \n"
			               "{                  \n"
			               "case 1:            \n"
			               "	a += 1;        \n"
			               "	break;         \n"
			               "                   \n"
			               "case 2:            \n"
			               "{                  \n"
			               "	a += 2;        \n"
			               "	break;         \n"
			               "}                  \n"
			               "}                  ";
		}
	}
	return display;
}

wxString AStyleDisplay::StcIndent_IndentClass() const
{
	wxString checked =     "                   \n"
	                       "class FooClass     \n"
	                       "{                  \n"
	                       "	public:        \n"
	                       "		Foo();     \n"
	                       "		virtual ~Foo();\n"
	                       "};                 ";

	wxString unchecked =   "                   \n"
	                       "class FooClass     \n"
	                       "{                  \n"
	                       "public:            \n"
	                       "	Foo();         \n"
	                       "	virtual ~Foo();\n"
	                       "};                 ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcIndent_IndentCol1Comment() const
{
	wxString checked =     "                    \n"
	                       "void Foo(bool isFoo)\n"
	                       "{                   \n"
	                       "	// comment      \n"
	                       "                    \n"
	                       "	if (isFoo)      \n"
	                       "		bar();      \n"
	                       "}                  ";

	wxString unchecked =   "                    \n"
	                       "void Foo(bool isFoo)\n"
	                       "{                   \n"
	                       "// comment          \n"
	                       "                    \n"
	                       "	if (isFoo)      \n"
	                       "		bar();      \n"
	                       "}                  ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcIndent_IndentContinuation() const
{
	wxString threeIndents = "                  \n"
	                        "//  three indents \n"
	                        "                  \n"
	                        "isLongVariable =  \n"
	                        "			foo1 ||\n"
	                        "			foo2;  \n"
	                        "                  \n"
	                        "isLongFunction(   \n"
	                        "			bar1,  \n"
	                        "			bar2); \n"
	                        "                  ";

	wxString oneIndent =    "                 \n"
	                        "//  one indent (default)\n"
	                        "                 \n"
	                        "isLongVariable = \n"
	                        "	foo1 ||       \n"
	                        "	foo2;         \n"
	                        "                 \n"
	                        "isLongFunction(  \n"
	                        "	bar1,         \n"
	                        "	bar2);        \n"
	                        "                  ";

	return m_event->IsChecked() ? threeIndents : oneIndent;
}

wxString AStyleDisplay::StcIndent_IndentGoTo() const
{
	wxString checked =     "                   \n"
	                       "int foospace() {   \n"
	                       "	if (isFoo)     \n"
	                       "		goto error;\n"
	                       "		...        \n"
	                       "	}              \n"
	                       "                   \n"
	                       "	error:         \n"
	                       "		...        \n"
	                       "}                  ";

	wxString unchecked =   "                   \n"
	                       "int foospace() {   \n"
	                       "	if (isFoo) \n"
	                       "		goto error;\n"
	                       "		...        \n"
	                       "	}              \n"
	                       "                   \n"
	                       "error:             \n"
	                       "		...        \n"
	                       "}                  ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcIndent_IndentModifier() const
{
	wxString checked =     "                   \n"
	                       "class FooClass     \n"
	                       "{                  \n"
	                       "  public:          \n"
	                       "	Foo();         \n"
	                       "	virtual ~Foo();\n"
	                       "};                 ";

	wxString unchecked =   "                   \n"
	                       "class FooClass     \n"
	                       "{                  \n"
	                       "public:            \n"
	                       "	Foo();         \n"
	                       "	virtual ~Foo();\n"
	                       "};                 ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcIndent_IndentNamespace() const
{
	wxString checked =     "                   \n"
	                       "namespace FooName  \n"
	                       "{                  \n"
	                       "	class FooClass \n"
	                       "	{              \n"
	                       "		public:    \n"
	                       "			Foo(); \n"
	                       "			virtual ~Foo();\n"
	                       "	};             \n"
	                       "}                  ";

	wxString unchecked =   "                   \n"
	                       "namespace FooName  \n"
	                       "{                  \n"
	                       "class FooClass     \n"
	                       "{                  \n"
	                       "	public:        \n"
	                       "		Foo();     \n"
	                       "		virtual ~Foo();\n"
	                       "};                 \n"
	                       "}                  ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcIndent_IndentPreprocBlock() const
{
	wxString checked =   "                       \n"
	                     "#ifdef _WIN32          \n"
	                     "	#include <windows.h> \n"
	                     "	#ifndef NO_EXPORT    \n"
	                     "		#define EXPORT   \n"
	                     "	#endif               \n"
	                     "#endif                 ";

	wxString unchecked = "                       \n"
	                     "#ifdef _WIN32          \n"
	                     "#include <windows.h>   \n"
	                     "#ifndef NO_EXPORT      \n"
	                     "#define EXPORT         \n"
	                     "#endif                 \n"
	                     "#endif                 ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcIndent_IndentPreprocCond() const
{
	wxString checked =     "                          \n"
	                       "          isFoo = true;   \n"
	                       "          #ifdef UNICODE  \n"
	                       "          text = wideBuff;\n"
	                       "          #else           \n"
	                       "          text = buff;    \n"
	                       "          #endif;         ";

	wxString unchecked =   "                          \n"
	                       "          isFoo = true;   \n"
	                       "#ifdef UNICODE            \n"
	                       "          text = wideBuff;\n"
	                       "#else                     \n"
	                       "          text = buff;    \n"
	                       "#endif;                   ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcIndent_IndentPreprocDefine() const
{
	wxString checked =     "                           \n"
	                       "#define Is_Foo(arg,op)  \\ \n"
	                       "	((arg).compare(op)==0) \n"
	                       "                           \n"
	                       "#define Is_Bar(arg,a,b)  \\\n"
	                       "	(Is_Foo((arg), (a))  \\\n"
	                       "		|| Is_Foo((arg), (b)))";

	wxString unchecked =   "                           \n"
	                       "#define Is_Foo(arg,op)  \\ \n"
	                       "((arg).compare(op)==0)     \n"
	                       "                           \n"
	                       "#define Is_Bar(arg,a,b)  \\\n"
	                       "(Is_Foo((arg), (a))   \\   \n"
	                       "|| Is_Foo((arg), (b)))     ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcIndent_MinConditionalDisplay() const
{
	wxString zeroIndents = "                   \n"
	                       "//  zero indents   \n"
	                       "                   \n"
	                       "if (a < b          \n"
	                       "    || c > d)      \n"
	                       "    foo++;         \n"
	                       "                   \n"
	                       "if (a < b          \n"
	                       "    || c > d)      \n"
	                       "{                  \n"
	                       "    foo++;         \n"
	                       "}                    ";

	wxString twoIndents =  "                   \n"
	                       "//  two indents (default)\n"
	                       "                   \n"
	                       "if (a < b          \n"
	                       "         || c > d) \n"
	                       "    foo++;         \n"
	                       "                   \n"
	                       "if (a < b          \n"
	                       "         || c > d) \n"
	                       "{                  \n"
	                       "    foo++;         \n"
	                       "}                    ";

	static bool display = false;
	display = !display;
	return display == true ? zeroIndents : twoIndents;
}

wxString AStyleDisplay::StcIndent_MaxContinuationDisplay() const
{
	wxString smaller =     "                             \n"
	                       "//  max continuation smaller \n"
	                       "                             \n"
	                       "fooArray[] = { red,          \n"
	                       "          green,             \n"
	                       "          darkblue };        \n"
	                       "                             \n"
	                       "fooFunction( barArg1,        \n"
	                       "          barArg2,           \n"
	                       "          barArg3 );           ";

	wxString larger =      "                             \n"
	                       "//  max continuation larger  \n"
	                       "                             \n"
	                       "fooArray[] = { red,          \n"
	                       "               green,        \n"
	                       "               darkblue };   \n"
	                       "                             \n"
	                       "fooFunction( barArg1,        \n"
	                       "             barArg2,        \n"
	                       "             barArg3 );        ";

	// text is aligned for proportional fonts
	static bool display = false;
	display = !display;
	return display ? smaller : AlignMaxContinuation(larger);
}

//-----------------------------------------------------------------------------
// STC Display for the Other Tab
//-----------------------------------------------------------------------------

wxString AStyleDisplay::StcOther_AlignMethodColon() const
{
	wxString checked =     "                            \n"
	                       "-(void)addKey : (id)key     \n"
	                       "      atIndex : (int)index  \n"
	                       "       ofNode : (Node*)node;";

	wxString unchecked =   "                            \n"
	                       "-(void)addKey : (id)key     \n"
	                       "	atIndex : (int)index    \n"
	                       "	ofNode : (Node*)node;   ";

	// text is aligned for proportional fonts
	return m_event->IsChecked() ? AlignMethodColon(checked) :  unchecked;
}

wxString AStyleDisplay::StcOther_PadMethodColon() const
{
	static size_t display = COLON_PAD_NO_CHANGE;
	if (m_event->GetId() == ID_PAD_METHOD_COLON)
		display = reinterpret_cast<size_t>(m_event->GetClientData());
	else
	{
		++display;
		if (display >= COLON_PAD_END)
			display = COLON_PAD_NO_CHANGE;
	}

	wxString textOut;
	if (display == COLON_PAD_NO_CHANGE)
	{
		textOut = "";
	}
	else if (display == COLON_PAD_NONE)
	{
		textOut = "                          \n"
		          "//  do not pad            \n"
		          "                          \n"
		          "-(void)addKey:(id)key     \n"
		          "      atIndex:(int)index  \n"
		          "       ofNode:(Node*)node;";
	}
	else if (display == COLON_PAD_ALL)
	{
		textOut = "                            \n"
		          "//  pad before and after    \n"
		          "                            \n"
		          "-(void)addKey : (id)key     \n"
		          "      atIndex : (int)index  \n"
		          "       ofNode : (Node*)node;";
	}
	else if (display == COLON_PAD_AFTER)
	{
		textOut = "                           \n"
		          "//  pad after only         \n"
		          "                           \n"
		          "-(void)addKey: (id)key     \n"
		          "      atIndex: (int)index  \n"
		          "       ofNode: (Node*)node;";
	}
	else if (display == COLON_PAD_BEFORE)
	{
		textOut = "                           \n"
		          "//  pad before only        \n"
		          "                           \n"
		          "-(void)addKey :(id)key     \n"
		          "      atIndex :(int)index  \n"
		          "       ofNode :(Node*)node;";
	}
	else
	{
		wxMessageBox(wxString::Format("Unidentified pad method colon display %d.\n", display));
	}
	return display == COLON_PAD_NO_CHANGE ? textOut : AlignMethodColon(textOut);
}

wxString AStyleDisplay::StcOther_PadMethodPrefix() const
{
	wxString checked =     "             \n"
	                       "- (void)foo1;\n"
	                       "- (void)foo2;\n";

	wxString unchecked =   "             \n"
	                       "-(void)foo1; \n"
	                       "-    (void)foo2; \n";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcOther_UnpadMethodPrefix() const
{
	wxString checked =     "             \n"
	                       "-(void)foo1; \n"
	                       "-(void)foo2; \n";

	wxString unchecked =   "             \n"
	                       "- (void)foo1;\n"
	                       "-     (void)foo2;\n";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcOther_PadReturnType() const
{
	wxString checked =   "             \n"
	                     "-(void) foo1;\n"
	                     "-(void) foo2;\n";

	wxString unchecked = "             \n"
	                     "-(void)foo1; \n"
	                     "-(void)   foo2; \n";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcOther_UnpadReturnType() const
{
	wxString checked =   "             \n"
	                     "-(void)foo1; \n"
	                     "-(void)foo2; \n";

	wxString unchecked = "             \n"
	                     "-(void) foo1;\n"
	                     "-(void)    foo2;\n";
	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcOther_PadParamType() const
{
	wxString checked =   "                            \n"
	                     "-(void)foo1: (bool) barArg1;\n"
	                     "-(void)foo2: (bool) barArg2;\n";

	wxString unchecked = "                          \n"
	                     "-(void)foo1:(bool)barArg1;\n"
	                     "-(void)foo2:    (bool)   barArg2;\n";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcOther_UnpadParamType() const
{
	wxString checked =   "                           \n"
	                     "-(void)foo1:(bool)barArg1;\n"
	                     "-(void)foo2:(bool)barArg2;\n";

	wxString unchecked = "                            \n"
	                     "-(void)foo1: (bool)    barArg1;\n"
	                     "-(void)foo2:     (bool)     barArg2;\n";
	return m_event->IsChecked() ? checked : unchecked;
}

//-----------------------------------------------------------------------------
// STC Display for the Pad Tab
//-----------------------------------------------------------------------------

wxString AStyleDisplay::StcPad_AlignPointer() const
{
	static size_t display = 0;
	if (m_event->GetId() == ID_ALIGN_POINTER)
	{
		display = reinterpret_cast<size_t>(m_event->GetClientData());
	}
	else if (++display > 3)
		display = 1;

	wxString textOut;
	if (display == PTR_ALIGN_NONE)
	{
		// display for option only, not for button
		textOut =  "                        \n";
	}
	else if (display == PTR_ALIGN_TYPE)
	{
		textOut =  "                        \n"
		           "	// attach to type   \n"
		           "                        \n"
		           "	char*  foo1;        \n"
		           "	char&  foo2;        \n";
	}
	else if (display == PTR_ALIGN_MIDDLE)
	{
		textOut =  "                        \n"
		           "	// align in middle  \n"
		           "                        \n"
		           "	char  *  foo1;      \n"
		           "	char  &  foo2;      \n";
	}
	else if (display == PTR_ALIGN_NAME)
	{
		textOut =  "                        \n"
		           "	// attach to name   \n"
		           "                        \n"
		           "	char  *foo1;        \n"
		           "	char  &foo2;        \n";
	}
	else
	{
		wxMessageBox(wxString::Format("Unidentified align pointer display %d.\n", display));
	}
	return textOut;
}

wxString AStyleDisplay::StcPad_AlignReference() const
{
	static size_t display = 0;
	if (m_event->GetId() == ID_ALIGN_REFERENCE)
	{
		display = reinterpret_cast<size_t>(m_event->GetClientData());
	}
	else if (++display >= REF_SAME_AS_PTR)
		display = REF_ALIGN_TYPE;

	wxString textOut;
	if (display == REF_ALIGN_NONE || display == REF_SAME_AS_PTR)
	{
		// display for option only, not for button
		textOut =  "                        \n";
	}
	else if (display == REF_ALIGN_TYPE)
	{
		textOut =  "	                    \n"
		           "	// attach to type   \n"
		           "	// reference only   \n"
		           "	                    \n"
		           "	char&  foo2;        \n";
	}
	else if (display == REF_ALIGN_MIDDLE)
	{
		textOut =  "	                    \n"
		           "	// align in middle  \n"
		           "	// reference only   \n"
		           "	                    \n"
		           "	char  &  foo2;      \n";
	}
	else if (display == REF_ALIGN_NAME)
	{
		textOut =  "	                    \n"
		           "	// attach to name   \n"
		           "	// reference only   \n"
		           "	                    \n"
		           "	char  &foo2;        \n";
	}
	else
	{
		wxMessageBox(wxString::Format("Unidentified align reference display %d.\n", display));
	}
	return textOut;
}

wxString AStyleDisplay::StcPad_BreakAll() const
{
	wxString checked =     "                   \n"
	                       "isFoo = true;      \n"
	                       "                   \n"
	                       "if (isFoo) {       \n"
	                       "	bar();         \n"
	                       "                   \n"
	                       "} else {           \n"
	                       "	anotherBar();  \n"
	                       "}                  \n"
	                       "                   \n"
	                       "isBar = false;     ";

	wxString unchecked =   "                   \n"
	                       "isFoo = true;      \n"
	                       "if (isFoo) {       \n"
	                       "	bar();         \n"
	                       "} else {           \n"
	                       "	anotherBar();  \n"
	                       "}                  \n"
	                       "isBar = false;     ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcPad_BreakHeader() const
{
	wxString checked =     "                   \n"
	                       "isFoo = true;      \n"
	                       "                   \n"
	                       "if (isFoo) {       \n"
	                       "	bar();         \n"
	                       "} else {           \n"
	                       "    anotherBar();  \n"
	                       "}                  \n"
	                       "                   \n"
	                       "isBar = false;     ";

	wxString unchecked =   "                   \n"
	                       "isFoo = true;      \n"
	                       "if (isFoo) {       \n"
	                       "	bar();         \n"
	                       "} else {           \n"
	                       "	anotherBar();  \n"
	                       "}                  \n"
	                       "isBar = false;     ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcPad_DeleteEmptyLine() const
{
	// this case shows whitespace, cannot have formatting spaces in text
	wxString checked =     "\n"
	                       "void  fooBar()\n"
	                       "{\n"
	                       "	foo1 = 1;\n"
	                       "	foo2 = 2;\n"
	                       "}";

	wxString unchecked =   "\n"
	                       "void  fooBar()\n"
	                       "{\n"
	                       "\n"
	                       "	foo1 = 1;\n"
	                       "\n"
	                       "	foo2 = 2;\n"
	                       "\n"
	                       "}";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcPad_FillEmptyLine() const
{
	// this case shows whitespace, cannot have formatting spaces in text
	wxString checked =     "\n"
	                       "	if (isFoo)\n"
	                       "	{\n"
	                       "		bar();\n"
	                       "	}\n"
	                       "	\n"
	                       "	\n"
	                       "	else\n"
	                       "		anotherBar();";

	// this case shows whitespace, cannot have formatting spaces in text
	wxString unchecked =   "\n"
	                       "	if (isFoo)\n"
	                       "	{\n"
	                       "		bar();\n"
	                       "	}\n"
	                       "\n"
	                       "\n"
	                       "	else\n"
	                       "		anotherBar();";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcPad_PadComma() const
{
	wxString checked =   "                 \n"
	                     "                 \n"
	                     "if (isFoo(a, b)  \n"
	                     "    bar(a, b);   \n"
	                     "                 ";

	wxString unchecked = "                 \n"
	                     "                 \n"
	                     "if (isFoo(a,b)   \n"
	                     "    bar(a,b);    \n"
	                     "                 ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcPad_PadFirstParenOut() const
{
	wxString checked =    "                     \n"
	                      "                     \n"
	                      "if (isFoo ((a+2), b))\n"
	                      "    bar (a, b);      \n"
	                      "                     ";

	wxString unchecked =  "                     \n"
	                      "                     \n"
	                      "if (isFoo((a+2), b)) \n"
	                      "    bar(a, b);       \n"
	                      "                     ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcPad_PadHeader() const
{
	wxString checked =    "                    \n"
	                      "                    \n"
	                      "if (isFoo((a+2), b))\n"
	                      "    bar(a, b);      \n"
	                      "                    ";

	wxString unchecked =  "                   \n"
	                      "                   \n"
	                      "if(isFoo((a+2), b))\n"
	                      "    bar(a, b);     \n"
	                      "                   ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcPad_PadOperator() const
{
	wxString checked =    "                        \n"
	                      "                        \n"
	                      "if (foo == 2)           \n"
	                      "    a = bar((b - c) * a, d--);\n"
	                      "                        ";

	wxString unchecked =  "                        \n"
	                      "                        \n"
	                      "if (foo==2)             \n"
	                      "    a=bar((b-c)*a,d--);\n"
	                      "                        ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcPad_PadParenOut() const
{
	wxString checked =    "                       \n"
	                      "                       \n"
	                      "if (isFoo ( (a+2), b) )\n"
	                      "    bar (a, b);        ";

	wxString unchecked =  "                       \n"
	                      "                       \n"
	                      "if (isFoo((a+2), b))   \n"
	                      "    bar(a, b);         ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcPad_PadParenIn() const
{
	wxString checked =    "                          \n"
	                      "                          \n"
	                      "if ( isFoo( ( a+2 ), b ) )\n"
	                      "    bar( a, b );          ";

	wxString unchecked =  "                          \n"
	                      "                          \n"
	                      "if (isFoo((a+2), b))      \n"
	                      "    bar(a, b);           ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcPad_UnpadParen() const
{
	wxString checked =    "                           \n"
	                      "                           \n"
	                      "if (isFoo((a+2), b))       \n"
	                      "    bar(a, b);             \n"
	                      "                           \n"
	                      "// unpad can be modified   \n"
	                      "// by pad paren options    ";

	wxString unchecked =  "                           \n"
	                      "                           \n"
	                      "if ( isFoo ( ( a+2 ), b ) )\n"
	                      "    bar ( a, b );          \n"
	                      "                           \n"
	                      "// unpad can be modified   \n"
	                      "// by pad paren options    ";

	return m_event->IsChecked() ? checked : unchecked;
}

//-----------------------------------------------------------------------------
// STC Display for the Style Tab
//-----------------------------------------------------------------------------

wxString AStyleDisplay::StcStyle_Allman() const
{
	wxString selected =    "                    \n"
	                       "//  Allman Style    \n"
	                       "                    \n"
	                       "namespace FooName   \n"
	                       "{                   \n"
	                       "class FooClass      \n"
	                       "{                   \n"
	                       "public:             \n"
	                       "	int Foo();      \n"
	                       "};                  \n"
	                       "                    \n"
	                       "int FooClass::Foo() \n"
	                       "{                   \n"
	                       "	if (isFoo)      \n"
	                       "	{               \n"
	                       "		bar();      \n"
	                       "		return 1;   \n"
	                       "	}               \n"
	                       "	else            \n"
	                       "		return 0;   \n"
	                       "}                   \n"
	                       "}                   ";

	return selected;
}

wxString AStyleDisplay::StcStyle_Gnu() const
{
	wxString selected =    "                     \n"
	                       "//  GNU Style        \n"
	                       "                     \n"
	                       "namespace FooName    \n"
	                       "{                    \n"
	                       "class FooClass       \n"
	                       "{                    \n"
	                       "public:              \n"
	                       "	int Foo();       \n"
	                       "};                   \n"
	                       "                     \n"
	                       "int FooClass::Foo()  \n"
	                       "{                    \n"
	                       "	if (isFoo)       \n"
	                       "		{            \n"
	                       "			bar();   \n"
	                       "			return 1;\n"
	                       "		}            \n"
	                       "	else             \n"
	                       "		return 0;    \n"
	                       "}                    \n"
	                       "}                    ";

	return selected;
}

wxString AStyleDisplay::StcStyle_Google() const
{
	wxString selected =    "                     \n"
	                       "//  Google Style     \n"
	                       "                     \n"
	                       "namespace FooName {  \n"
	                       "class FooClass {     \n"
	                       "  public:            \n"
	                       "	int Foo();       \n"
	                       "};                   \n"
	                       "                     \n"
	                       "int FooClass::Foo() {\n"
	                       "	if (isFoo) {     \n"
	                       "		bar();       \n"
	                       "		return 1;    \n"
	                       "	} else           \n"
	                       "		return 0;    \n"
	                       "}                    \n"
	                       "}                    ";

	return selected;
}

wxString AStyleDisplay::StcStyle_Horstmann() const
{
	wxString selected =    "                    \n"
	                       "//  Horstmann Style \n"
	                       "                    \n"
	                       "namespace FooName   \n"
	                       "{                   \n"
	                       "class FooClass      \n"
	                       "{                   \n"
	                       "public:             \n"
	                       "	int Foo();      \n"
	                       "};                  \n"
	                       "                    \n"
	                       "int FooClass::Foo() \n"
	                       "{	if (isFoo)      \n"
	                       "	{	bar();      \n"
	                       "		return 1;   \n"
	                       "	}               \n"
	                       "	else            \n"
	                       "		return 0;   \n"
	                       "}                   \n"
	                       "}                   ";

	return selected;
}

wxString AStyleDisplay::StcStyle_Java() const
{
	wxString selected =    "                     \n"
	                       "//  Java Style       \n"
	                       "                     \n"
	                       "namespace FooName {  \n"
	                       "class FooClass {     \n"
	                       "public:              \n"
	                       "	int Foo()        \n"
	                       "};                   \n"
	                       "                     \n"
	                       "int FooClass::Foo() {\n"
	                       "	if (isFoo) {     \n"
	                       "		bar();       \n"
	                       "		return 1;    \n"
	                       "	} else           \n"
	                       "		return 0;    \n"
	                       "}                    \n"
	                       "}                    ";

	return selected;
}

wxString AStyleDisplay::StcStyle_KR() const
{
	wxString selected =    "                    \n"
	                       "//  K & R Style     \n"
	                       "                    \n"
	                       "namespace FooName   \n"
	                       "{                   \n"
	                       "class FooClass      \n"
	                       "{                   \n"
	                       "public:             \n"
	                       "	int Foo();      \n"
	                       "};                  \n"
	                       "                    \n"
	                       "int FooClass::Foo() \n"
	                       "{                   \n"
	                       "	if (isFoo) {    \n"
	                       "		bar();      \n"
	                       "		return 1;   \n"
	                       "	} else          \n"
	                       "		return 0;   \n"
	                       "}                   \n"
	                       "}                   ";

	return selected;
}

wxString AStyleDisplay::StcStyle_Linux() const
{
	wxString selected =    "                    \n"
	                       "//  Linux Style     \n"
	                       "                    \n"
	                       "namespace FooName   \n"
	                       "{                   \n"
	                       "class FooClass      \n"
	                       "{                   \n"
	                       "public:             \n"
	                       "	int Foo();      \n"
	                       "};                  \n"
	                       "                    \n"
	                       "int FooClass::Foo() \n"
	                       "{                   \n"
	                       "	if (isFoo) {    \n"
	                       "		bar();      \n"
	                       "		return 1;   \n"
	                       "	} else          \n"
	                       "		return 0;   \n"
	                       "}                   \n"
	                       "}                   ";

	return selected;
}

wxString AStyleDisplay::StcStyle_Lisp() const
{
	wxString selected =    "                     \n"
	                       "//  Lisp Style       \n"
	                       "                     \n"
	                       "namespace FooName {  \n"
	                       "class FooClass {     \n"
	                       "public:              \n"
	                       "	int Foo();  };   \n"
	                       "                     \n"
	                       "int FooClass::Foo() {\n"
	                       "	if (isFoo) {     \n"
	                       "		bar();       \n"
	                       "		return 1; }  \n"
	                       "	else             \n"
	                       "		return 0; } }";

	return selected;
}

wxString AStyleDisplay::StcStyle_Mozilla() const
{
	wxString selected =    "                    \n"
	                       "//  Mozilla Style   \n"
	                       "                    \n"
	                       "namespace FooName { \n"
	                       "class FooClass      \n"
	                       "{                   \n"
	                       "public:             \n"
	                       "	int Foo();      \n"
	                       "};                  \n"
	                       "                    \n"
	                       "int FooClass::Foo() \n"
	                       "{                   \n"
	                       "	if (isFoo) {    \n"
	                       "		bar();      \n"
	                       "		return 1;   \n"
	                       "	} else          \n"
	                       "		return 0;   \n"
	                       "}                   \n"
	                       "}                   ";

	return selected;
}

wxString AStyleDisplay::StcStyle_None() const
{
	wxString selected =  "";

	return selected;
}

wxString AStyleDisplay::StcStyle_Pico() const
{
	wxString selected =    "                     \n"
	                       "//  Pico Style       \n"
	                       "                     \n"
	                       "namespace FooName    \n"
	                       "{                    \n"
	                       "class FooClass       \n"
	                       "{                    \n"
	                       "public:              \n"
	                       "	int Foo(); };    \n"
	                       "                     \n"
	                       "int FooClass::Foo()  \n"
	                       "{	if (isFoo)       \n"
	                       "	{	bar();       \n"
	                       "		return 1; }  \n"
	                       "	else             \n"
	                       "		return 0; } }";

	return selected;
}

wxString AStyleDisplay::StcStyle_Ratliff() const
{
	wxString selected =    "                     \n"
	                       "//  Ratliff Style    \n"
	                       "                     \n"
	                       "namespace FooName {  \n"
	                       "class FooClass {     \n"
	                       "	public:          \n"
	                       "		int Foo();   \n"
	                       "	};               \n"
	                       "                     \n"
	                       "int FooClass::Foo() {\n"
	                       "	if (isFoo) {     \n"
	                       "		bar();       \n"
	                       "		return 1;    \n"
	                       "		}            \n"
	                       "	else             \n"
	                       "		return 0;    \n"
	                       "	}                \n"
	                       "}                    ";

	return selected;
}

wxString AStyleDisplay::StcStyle_Stroustrup() const
{
	wxString selected =    "                    \n"
	                       "//  Stroustrup Style\n"
	                       "                    \n"
	                       "namespace FooName { \n"
	                       "class FooClass {    \n"
	                       "public:             \n"
	                       "	int Foo();      \n"
	                       "};                  \n"
	                       "                    \n"
	                       "int FooClass::Foo() \n"
	                       "{                   \n"
	                       "	if (isFoo) {    \n"
	                       "		bar();      \n"
	                       "		return 1;   \n"
	                       "	}               \n"
	                       "    else            \n"
	                       "		return 0;   \n"
	                       "}                   \n"
	                       "}                   ";

	return selected;
}

wxString AStyleDisplay::StcStyle_Vtk() const
{
	wxString selected =    "                    \n"
	                       "//  VTK Style       \n"
	                       "                    \n"
	                       "namespace FooName   \n"
	                       "{                   \n"
	                       "class FooClass      \n"
	                       "{                   \n"
	                       "public:             \n"
	                       "	int Foo();      \n"
	                       "};                  \n"
	                       "                    \n"
	                       "int FooClass::Foo() \n"
	                       "{                   \n"
	                       "	if (isFoo)      \n"
	                       "		{           \n"
	                       "		bar();      \n"
	                       "		return 1;   \n"
	                       "		}           \n"
	                       "	else            \n"
	                       "		return 0;   \n"
	                       "}                   \n"
	                       "}                   ";

	return selected;
}

wxString AStyleDisplay::StcStyle_WebKit() const
{
	wxString selected =    "                    \n"
	                       "//  WebKit Style    \n"
	                       "                    \n"
	                       "namespace FooName { \n"
	                       "class FooClass {    \n"
	                       "public:             \n"
	                       "	int Foo();      \n"
	                       "};                  \n"
	                       "                    \n"
	                       "int FooClass::Foo() \n"
	                       "{                   \n"
	                       "	if (isFoo) {    \n"
	                       "		bar();      \n"
	                       "		return 1;   \n"
	                       "	} else          \n"
	                       "		return 0;   \n"
	                       "}                   \n"
	                       "}                   ";

	return selected;
}

wxString AStyleDisplay::StcStyle_Whitesmith() const
{
	wxString selected =    "                    \n"
	                       "//  Whitesmith Style\n"
	                       "                    \n"
	                       "namespace FooName   \n"
	                       "{                   \n"
	                       "class FooClass      \n"
	                       "	{               \n"
	                       "	public:         \n"
	                       "		int Foo()   \n"
	                       "	};              \n"
	                       "                    \n"
	                       "int FooClass::Foo() \n"
	                       "	{               \n"
	                       "	if (isFoo)      \n"
	                       "		{           \n"
	                       "		bar();      \n"
	                       "		return 1;   \n"
	                       "		}           \n"
	                       "	else            \n"
	                       "		return 0;   \n"
	                       "	}               \n"
	                       "}                   ";

	return selected;
}

wxString AStyleDisplay::StcStyle_1TBS() const
{
	wxString selected =    "                   \n"
	                       "//  One True Brace Style\n"
	                       "                   \n"
	                       "namespace FooName  \n"
	                       "{                  \n"
	                       "class FooClass     \n"
	                       "{                  \n"
	                       "public:            \n"
	                       "	int Foo();     \n"
	                       "};                 \n"
	                       "                   \n"
	                       "int Foo(bool isFoo)\n"
	                       "{                  \n"
	                       "	if (isFoo) {   \n"
	                       "		bar();     \n"
	                       "		return 1;  \n"
	                       "	} else {       \n"
	                       "		return 0;  \n"
	                       "	}              \n"
	                       "}                  \n"
	                       "}                  ";

	return selected;
}

//-----------------------------------------------------------------------------
// STC Display for the Tab Tab
//-----------------------------------------------------------------------------

wxString AStyleDisplay::StcModifier_AttachNamespace() const
{
	wxString checked =     "                   \n"
	                       "namespace FooName {\n"
	                       "		. . .      \n"
	                       "}                  ";

	wxString unchecked =   "                   \n"
	                       "namespace FooName  \n"
	                       "{                  \n"
	                       "		. . .      \n"
	                       "}                  ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcModifier_AttachClass_AttachInline() const
{
	// attach class and attach inline work together
	bool classChecked  = m_attachClass->IsChecked();
	bool inlineChecked = m_attachInline->IsChecked();
	wxString display;

	if (classChecked)
	{
		if (inlineChecked)
		{
			display =      "                    \n"        // yes class - yes inline
			               "class FooClass {    \n"
			               "	public:         \n"
			               "		Foo() {     \n"
			               "			isFoo();\n"
			               "		}           \n"
			               "};                  ";
		}
		else
		{
			display =      "                    \n"        // yes class - no inline
			               "class FooClass {    \n"
			               "	public:         \n"
			               "		Foo()       \n"
			               "		{           \n"
			               "			isFoo();\n"
			               "		}           \n"
			               "};                  ";
		}
	}
	else
	{
		if (inlineChecked)
		{
			display =      "                    \n"        // no class - yes inline
			               "class FooClass      \n"
			               "{                   \n"
			               "	public:         \n"
			               "		Foo() {     \n"
			               "			isFoo();\n"
			               "		}           \n"
			               "};                  ";
		}
		else
		{
			display =      "                    \n"        // no class - no inline
			               "class FooClass      \n"
			               "{                   \n"
			               "	public:         \n"
			               "		Foo()       \n"
			               "		{           \n"
			               "			isFoo();\n"
			               "		}           \n"
			               "};                  ";
		}
	}
	return display;
}

wxString AStyleDisplay::StcModifier_AttachClosingWhile() const
{
	wxString checked =     "                      \n"
	                       "void Foo()            \n"
	                       "{                     \n"
	                       "    do                \n"
	                       "    {                 \n"
	                       "        bar();        \n"
	                       "        ++x;          \n"
	                       "    } while (x < max);\n"
	                       "}                     ";

	wxString unchecked =   "                      \n"
	                       "void Foo()            \n"
	                       "{                     \n"
	                       "    do                \n"
	                       "    {                 \n"
	                       "        bar();        \n"
	                       "        ++x;          \n"
	                       "    }                 \n"
	                       "    while (x < max);  \n"
	                       "}                   ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcModifier_AttachExternC() const
{
	wxString checked =     "                  \n"
	                       "#ifdef __cplusplus\n"
	                       "extern \"C\" {    \n"
	                       "#endif            ";

	wxString unchecked =   "                  \n"
	                       "#ifdef __cplusplus\n"
	                       "extern \"C\"      \n"
	                       "{                 \n"
	                       "#endif            ";

	return m_event->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcTab_IndentLengthDisplay() const
{
	wxString selected =    "\n"
	                       "void Foo(bool isFoo)\n"
	                       "{\n"
	                       "	if (isFoo) {\n"
	                       "		anotherBar(barArg1);\n"
	                       "	}\n"
	                       "	else {\n"
	                       "		bar(barArg1,\n"
	                       "		    barArg2,\n"
	                       "		    barArg3);\n"
	                       "	}\n"
	                       "}";

	return selected;
}

wxString AStyleDisplay::StcTab_IndentWithForceTab_UseTabLength() const
{
	// this case shows whitespace, cannot have formatting spaces in text
	wxString checked =     "\n"
	                       "void Foo(bool isFoo)\n"
	                       "{\n"
	                       "    if (isFoo) {\n"
	                       "	anotherBar(barArg1);\n"
	                       "    }\n"
	                       "    else {\n"
	                       "	bar(barArg1,\n"
	                       "	    barArg2,\n"
	                       "	    barArg3);\n"
	                       "    }\n"
	                       "}";

	wxString unchecked =   "\n"
	                       "void Foo(bool isFoo)\n"
	                       "{\n"
	                       "	if (isFoo) {\n"
	                       "		anotherBar(barArg1);\n"
	                       "	}\n"
	                       "	else {\n"
	                       "		bar(barArg1,\n"
	                       "			barArg2,\n"
	                       "			barArg3);\n"
	                       "	}\n"
	                       "}";

	return m_useTabLength->IsChecked() ? checked : unchecked;
}

wxString AStyleDisplay::StcTab_IndentWithSpace() const
{
	// this case shows whitespace, cannot have formatting spaces in text
	wxString selected =    "\n"
	                       "void Foo(bool isFoo) \n"
	                       "{\n"
	                       "    if (isFoo) {\n"
	                       "        anotherBar(barArg1);\n"
	                       "    }\n"
	                       "    else {\n"
	                       "        bar(barArg1,\n"
	                       "            barArg2,\n"
	                       "            barArg3);\n"
	                       "    }\n"
	                       "}";

	return selected;
}

wxString AStyleDisplay::StcTab_IndentWithTab() const
{
	// this case shows whitespace, cannot have formatting spaces in text
	wxString selected =    "\n"
	                       "void Foo(bool isFoo)\n"
	                       "{\n"
	                       "	if (isFoo) {\n"
	                       "		anotherBar(barArg1);\n"
	                       "	}\n"
	                       "	else {\n"
	                       "		bar(barArg1,\n"
	                       "		    barArg2,\n"
	                       "		    barArg3);\n"
	                       "	}\n"
	                       "}";

	return selected;
}
