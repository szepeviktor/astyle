// AStyleDisplay.h
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.txt describes the conditions under which this software may be distributed.

#ifndef _ASTYLEDISPLAY_H_
#define _ASTYLEDISPLAY_H_

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include <wx/checkbox.h>
#include <wx/stc/stc.h>

#ifdef __clang__
	#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#endif

//-----------------------------------------------------------------------------
// AStyleDisplay Class
// Contains the Preview STC display methods for AStyleDlg.
//-----------------------------------------------------------------------------
class AStyleDisplay
{
public:
	AStyleDisplay(wxCheckBox*, wxCheckBox*, wxCheckBox*,
	              wxCheckBox*, wxCheckBox*, wxCheckBox*);
	~AStyleDisplay();
	void DisplayFormatOptions(wxCommandEvent& event, wxStyledTextCtrl* formatPreviewSTC);
	void DisplayIndentOptions(wxCommandEvent& event, wxStyledTextCtrl* indentPreviewSTC);
	void DisplayModifierOptions(wxCommandEvent& event, wxStyledTextCtrl* tabPreviewSTC);
	void DisplayOtherOptions(wxCommandEvent& event, wxStyledTextCtrl* otherPreviewSTC);
	void DisplayPadOptions(wxCommandEvent& event, wxStyledTextCtrl* padPreviewSTC);
	void DisplayStyleOptions(wxCommandEvent& event, wxStyledTextCtrl* stylePreviewSTC);
	void DisplayTabOptions(wxCommandEvent& event, wxStyledTextCtrl* tabPreviewSTC);
	// getters
	wxCommandEvent* GetEvent() const { return m_event; };
	wxStyledTextCtrl* GetSTC() const { return m_stc; };

private:
	wxString AlignConvertTabs(const wxString& text) const;
	wxString AlignGetLine(const wxString& text, int lineNumber) const;
	wxArrayString AlignGetLineArray(const wxString& text) const;
	int  AlignGetSpaceEquivalent(wxString& line) const;
	wxString AlignMaxInStatement(const wxString& text) const;
	wxString AlignMethodColon(const wxString& text) const;
	void AlignReplaceIndent(wxString& line, wxString& indent) const;
	void LexStcText(wxString boldChars = wxEmptyString);
	// Format Tab
	wxString StcFormat_AddBraces();
	wxString StcFormat_AddOneLineBraces();
	wxString StcFormat_BreakClosingBraces();
	wxString StcFormat_BreakElseIf();
	wxString StcFormat_BreakOneLineHeaders();
	wxString StcFormat_CloseTemplates();
	wxString StcFormat_ConvertTabs();
	wxString StcFormat_KeepOneLineBlocks();
	wxString StcFormat_KeepOneLineStatements();
	wxString StcFormat_MaxCodeLength_BreakAfterLogical();
	wxString StcFormat_RemoveBraces();
	wxString StcFormat_RemoveCommentPrefix();
	// Indent Tab
	wxString StcIndent_IndentCase_IndentSwitch();
	wxString StcIndent_IndentClass();
	wxString StcIndent_IndentCol1Comment();
	wxString StcIndent_IndentContinuation();
	wxString StcIndent_IndentGoTo();
	wxString StcIndent_IndentModifier();
	wxString StcIndent_IndentNamespace();
	wxString StcIndent_IndentPreprocBlock();
	wxString StcIndent_IndentPreprocCond();
	wxString StcIndent_IndentPreprocDefine();
	wxString StcIndent_MinConditionalDisplay();
	wxString StcIndent_MaxInStatementDisplay();
	// Other Tab
	wxString StcOther_AlignMethodColon();
	wxString StcOther_PadMethodColon();
	wxString StcOther_PadMethodPrefix();
	wxString StcOther_UnpadMethodPrefix();
	wxString StcOther_PadReturnType();
	wxString StcOther_UnpadReturnType();
	wxString StcOther_PadParamType();
	wxString StcOther_UnpadParamType();
	// Pad Tab
	wxString StcPad_AlignPointer();
	wxString StcPad_AlignReference();
	wxString StcPad_BreakAll();
	wxString StcPad_BreakHeader();
	wxString StcPad_DeleteEmptyLine();
	wxString StcPad_FillEmptyLine();
	wxString StcPad_PadComma();
	wxString StcPad_PadFirstParenOut();
	wxString StcPad_PadHeader();
	wxString StcPad_PadOperator();
	wxString StcPad_PadParenOut();
	wxString StcPad_PadParenIn();
	wxString StcPad_UnpadParen();
	// Style Tab
	wxString StcStyle_Allman();
	wxString StcStyle_Banner();
	wxString StcStyle_Gnu();
	wxString StcStyle_Google();
	wxString StcStyle_Horstmann();
	wxString StcStyle_Java();
	wxString StcStyle_KR();
	wxString StcStyle_Linux();
	wxString StcStyle_Lisp();
	wxString StcStyle_Mozilla();
	wxString StcStyle_None();
	wxString StcStyle_Pico();
	wxString StcStyle_Stroustrup();
	wxString StcStyle_Vtk();
	wxString StcStyle_Whitesmith();
	wxString StcStyle_1TBS();
	// Tab Tab
	wxString StcModifier_AttachNamespace();
	wxString StcModifier_AttachClass_AttachInline();
	wxString StcModifier_AttachClosingWhile();
	wxString StcModifier_AttachExternC();
	wxString StcTab_IndentLengthDisplay();
	wxString StcTab_IndentWithForceTab_UseTabLength();
	wxString StcTab_IndentWithSpace();
	wxString StcTab_IndentWithTab();

private:
	// objects set by each event
	wxCommandEvent* m_event;					// the event causing the display
	wxStyledTextCtrl* m_stc;					// the stc to update
	// objects set by the constructor
	const wxCheckBox* m_useTabLength;			// pointer to m_useTabLength
	const wxCheckBox* m_attachClass;			// pointer to m_attachCase
	const wxCheckBox* m_attachInline;			// pointer to m_attachInline
	const wxCheckBox* m_indentSwitchBlocks;		// pointer to m_indentSwitchBlocks
	const wxCheckBox* m_indentCaseBlocks;		// pointer to m_indentCaseBlocks
	const wxCheckBox* m_breakAfterLogical;		// pointer to m_breakAfterLogical
};

#endif	// _ASTYLEDISPLAY_H_
