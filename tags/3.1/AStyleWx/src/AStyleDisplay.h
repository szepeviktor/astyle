// AStyleDisplay.h
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

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
	wxString AlignIndentAfterParens(const wxString& text) const;
	wxString AlignMaxContinuation(const wxString& text) const;
	wxString AlignMethodColon(const wxString& text) const;
	void AlignReplaceIndent(wxString& line, wxString& indent) const;
	void LexStcText(wxString boldChars = wxEmptyString);
	// Format Tab
	wxString StcFormat_AddBraces() const;
	wxString StcFormat_AddOneLineBraces() const;
	wxString StcFormat_AttachReturnType() const;
	wxString StcFormat_AttachReturnTypeDecl() const;
	wxString StcFormat_BreakClosingBraces() const;
	wxString StcFormat_BreakElseIf() const;
	wxString StcFormat_BreakOneLineHeaders() const;
	wxString StcFormat_CloseTemplates() const;
	wxString StcFormat_ConvertTabs() const;
	wxString StcFormat_KeepOneLineBlocks() const;
	wxString StcFormat_KeepOneLineStatements() const;
	wxString StcFormat_MaxCodeLength_BreakAfterLogical() const;
	wxString StcFormat_RemoveBraces() const;
	wxString StcFormat_RemoveCommentPrefix() const;
	wxString StcFormat_BreakReturnType() const;
	wxString StcFormat_BreakReturnTypeDecl() const;
	// Indent Tab
	wxString StcIndent_IndentAfterParen() const;
	wxString StcIndent_IndentCase_IndentSwitch() const;
	wxString StcIndent_IndentClass() const;
	wxString StcIndent_IndentCol1Comment() const;
	wxString StcIndent_IndentContinuation() const;
	wxString StcIndent_IndentGoTo() const;
	wxString StcIndent_IndentModifier() const;
	wxString StcIndent_IndentNamespace() const;
	wxString StcIndent_IndentPreprocBlock() const;
	wxString StcIndent_IndentPreprocCond() const;
	wxString StcIndent_IndentPreprocDefine() const;
	wxString StcIndent_MinConditionalDisplay() const;
	wxString StcIndent_MaxContinuationDisplay() const;
	// Other Tab
	wxString StcOther_AlignMethodColon() const;
	wxString StcOther_PadMethodColon() const;
	wxString StcOther_PadMethodPrefix() const;
	wxString StcOther_UnpadMethodPrefix() const;
	wxString StcOther_PadReturnType() const;
	wxString StcOther_UnpadReturnType() const;
	wxString StcOther_PadParamType() const;
	wxString StcOther_UnpadParamType() const;
	// Pad Tab
	wxString StcPad_AlignPointer() const;
	wxString StcPad_AlignReference() const;
	wxString StcPad_BreakAll() const;
	wxString StcPad_BreakHeader() const;
	wxString StcPad_DeleteEmptyLine() const;
	wxString StcPad_FillEmptyLine() const;
	wxString StcPad_PadComma() const;
	wxString StcPad_PadFirstParenOut() const;
	wxString StcPad_PadHeader() const;
	wxString StcPad_PadOperator() const;
	wxString StcPad_PadParenOut() const;
	wxString StcPad_PadParenIn() const;
	wxString StcPad_UnpadParen() const;
	// Style Tab
	wxString StcStyle_Allman() const;
	wxString StcStyle_Gnu() const;
	wxString StcStyle_Google() const;
	wxString StcStyle_Horstmann() const;
	wxString StcStyle_Java() const;
	wxString StcStyle_KR() const;
	wxString StcStyle_Linux() const;
	wxString StcStyle_Lisp() const;
	wxString StcStyle_Mozilla() const;
	wxString StcStyle_None() const;
	wxString StcStyle_Pico() const;
	wxString StcStyle_Ratliff() const;
	wxString StcStyle_Stroustrup() const;
	wxString StcStyle_Vtk() const;
	wxString StcStyle_Whitesmith() const;
	wxString StcStyle_1TBS() const;
	// Tab Tab
	wxString StcModifier_AttachNamespace() const;
	wxString StcModifier_AttachClass_AttachInline() const;
	wxString StcModifier_AttachClosingWhile() const;
	wxString StcModifier_AttachExternC() const;
	wxString StcTab_IndentLengthDisplay() const;
	wxString StcTab_IndentWithForceTab_UseTabLength() const;
	wxString StcTab_IndentWithSpace() const;
	wxString StcTab_IndentWithTab() const;

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
