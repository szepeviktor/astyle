// Config.cpp
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

/* ----------------------------------------------------------------------------
TO ADD A NEW OPTION

AStyle options:
Add new option to method "SaveAStyleOptions".

ASEditor options:
Add new option to method "SaveEditorOptions" or "SaveViewMenuOptions".

Style options:
Add new option to method "SaveStyleOptions"
---------------------------------------------------------------------------- */

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#ifndef ASTYLEWX_TEST
	#include "AStyleWx.h"		// production classes
#else
	#include "Config_Test.h"	// fake classes for test
#endif

//-----------------------------------------------------------------------------
// Global definitions
//-----------------------------------------------------------------------------

// duplicate needed for Config_Test.h
int  ShowMessageDialog(const wxString& message, long style);

//-----------------------------------------------------------------------------
// Config class
//-----------------------------------------------------------------------------

int Config::FindStyleVectorIndex(const wxString& groupPath, const vector<TextStyle>& styleVector)
// Get the style vector index from a config path name.
{
	// get style ID from the path name
	int lastDash = groupPath.Find('-', true);
	if (lastDash == wxNOT_FOUND)
		return wxNOT_FOUND;
	wxString styleStr = groupPath.Mid(lastDash + 1);
	long styleID;
	bool ok = styleStr.ToLong(&styleID);
	if (!ok)
		return wxNOT_FOUND;
	// find style ID in the vector
	for (size_t i = 0; i < styleVector.size(); i++)
	{
		if (styleID == styleVector[i].style)
			return static_cast<int>(i);
	}
	return wxNOT_FOUND;
}

void Config::GetAStyleOptions(AStyleIFace* astyle)
// Update the AStyle display from the config file.
{
	// enumeration variables
	wxString key;		// editor key
	wxString value;		// value of the key
	long index;			// don't use this
	bool ok;			// the entry is ok

	// enum AStyle entries - invalid entries cannot be removed during enum
	wxArrayString invalidEntries;
	wxConfig::SetPath("/AStyle");
	bool hasMoreEntries = wxConfig::GetFirstEntry(key, index);
	// set the item status from the config key
	while (hasMoreEntries)
	{
		if (wxConfig::GetEntryType(key) == wxConfig::Type_String)
		{
			wxConfig::Read(key, &value);
			ok = astyle->SetAStyleOption(key, value);
		}
		else
			ok = false;
		if (!ok)
			invalidEntries.Add(key);
		hasMoreEntries = wxConfig::GetNextEntry(key, index);
	}
	// remove invalid entries
	if (invalidEntries.GetCount())
	{
		for (size_t i = 0; i < invalidEntries.GetCount(); i++)
		{
			ShowInvalidConfig(invalidEntries[i]);
			wxConfig::DeleteEntry(invalidEntries[i], false);
		}
		wxConfig::Flush();
	}
	wxConfig::SetPath("/");
}

vector<TextStyle> Config::GetDefaultStyleOptions()
// Initialize a style vector with the default values.
{
	vector<TextStyle> styleVector;
	TextStyle style;

	// style 01
	style.name   = "comment  /*";
	style.style  = wxSTC_C_COMMENT;
	style.fore   = wxColour(0, 128, 0);
	style.back   = wxColour(255, 255, 255);
	style.bold   = false;
	style.italic = true;
	styleVector.push_back(style);

	// style 02
	style.name   = "comment  //";
	style.style  = wxSTC_C_COMMENTLINE;
	style.fore   = wxColour(0, 128, 0);
	style.back   = wxColour(255, 255, 255);
	style.bold   = false;
	style.italic = true;
	styleVector.push_back(style);

	// style 03
	style.name   = "comment  /**";
	style.style  = wxSTC_C_COMMENTDOC;
	style.fore   = wxColour(0, 128, 0);
	style.back   = wxColour(255, 255, 255);
	style.bold   = false;
	style.italic = true;
	styleVector.push_back(style);

	// style 15
	style.name   = "comment  ///";
	style.style  = wxSTC_C_COMMENTLINEDOC;
	style.fore   = wxColour(0, 128, 0);
	style.back   = wxColour(255, 255, 255);
	style.bold   = false;
	style.italic = true;
	styleVector.push_back(style);

	// style 07
	style.name   = "character";
	style.style  = wxSTC_C_CHARACTER;
	style.fore   = wxColour(128, 0, 0);
	style.back   = wxColour(255, 255, 255);
	style.bold   = false;
	style.italic = false;
	styleVector.push_back(style);

	// style 11
	style.name   = "identifier";
	style.style  = wxSTC_C_IDENTIFIER;
	style.fore   = wxColour(4, 4, 4);
	style.back   = wxColour(255, 255, 255);
	style.bold   = false;
	style.italic = false;
	styleVector.push_back(style);

	// style 05
	style.name   = "keyword";
	style.style  = wxSTC_C_WORD;
	style.fore   = wxColour(0, 0, 255);
	style.back   = wxColour(255, 255, 255);
	style.bold   = false;
	style.italic = false;
	styleVector.push_back(style);

	// style 04
	style.name   = "number";
	style.style  = wxSTC_C_NUMBER;
	style.fore   = wxColour(0, 128, 128);
	style.back   = wxColour(255, 255, 255);
	style.bold   = false;
	style.italic = false;
	styleVector.push_back(style);

	// style 10
	style.name   = "operator";
	style.style  = wxSTC_C_OPERATOR;
	style.fore   = wxColour(0, 0, 0);
	style.back   = wxColour(255, 255, 255);
	style.bold   = true;
	style.italic = false;
	styleVector.push_back(style);

	// style 09
	style.name   = "preprocessor";
	style.style  = wxSTC_C_PREPROCESSOR;
	style.fore   = wxColour(0, 0, 255);
	style.back   = wxColour(255, 255, 255);
	style.bold   = false;
	style.italic = false;
	styleVector.push_back(style);

	// style 06
	style.name   = "string";
	style.style  = wxSTC_C_STRING;
	style.fore   = wxColour(128, 0, 0);
	style.back   = wxColour(255, 255, 255);
	style.bold   = false;
	style.italic = false;
	styleVector.push_back(style);

	// style 13
	style.name   = "raw string";
	style.style  = wxSTC_C_VERBATIM;
	style.fore   = wxColour(128, 0, 0);
	style.back   = wxColour(255, 255, 255);
	style.bold   = false;
	style.italic = false;
	styleVector.push_back(style);

	return styleVector;
}

void Config::GetEditorAndViewOptions()
// Update the Editor display from the config file.
{
	// enumeration variables
	wxString key;       // Editor key
	wxString value;		// value of the key
	long index;			// don't use this
	bool ok;			// the entry is ok

	// enum Editor entries - invalid entries cannot be removed during enum
	wxArrayString invalidEntries;
	wxConfig::SetPath("/");
	bool hasMoreEntries = wxConfig::GetFirstEntry(key, index);
	// no entries means the file has not been initialized
	if (!hasMoreEntries)
	{
		InitializeConfigFile();
		hasMoreEntries = wxConfig::GetFirstEntry(key, index);
	}
	// set the item status from the config key
	while (hasMoreEntries)
	{
		if (wxConfig::GetEntryType(key) == wxConfig::Type_String)
		{
			wxConfig::Read(key, &value);
			ok = m_frame->SetEditorOrViewOption(key, value);
		}
		else
			ok = false;
		if (!ok)
			invalidEntries.Add(key);
		hasMoreEntries = wxConfig::GetNextEntry(key, index);
	}
	// remove invalid entries
	if (invalidEntries.GetCount())
	{
		for (size_t i = 0; i < invalidEntries.GetCount(); i++)
		{
			ShowInvalidConfig(invalidEntries[i]);
			wxConfig::DeleteEntry(invalidEntries[i], false);
		}
		wxConfig::Flush();
	}
	wxConfig::SetPath("/");
}

wxArrayString Config::GetSessionFiles()
// Get session filepaths from the config file.
{
	wxConfig::SetPath("/Session");
	wxArrayString filePaths;
	if (m_frame->GetLoadSession())
	{
		int configCount = wxConfig::GetNumberOfEntries();
		wxString key;
		wxString value;
		// read the keys in ascending sequence
		for (size_t i = 0; configCount > 0; i++)
		{
			key = SESSION_FILE + wxString::Format("%d", static_cast<int>(i + 1));
			if (wxConfig::Read(key, &value))
			{
				filePaths.Add(value);
				--configCount;
			}
		}
	}
	wxConfig::SetPath("/");
	return filePaths;
}

vector<TextStyle> Config::GetStcStyleOptions()
// Get the style options from the config file and build a style vector.
{
	// enumeration variables
	wxString group;			// Style group
	long index;				// don't use this

	vector<TextStyle> styleVector = GetDefaultStyleOptions();
	// enum Style groups - empty groups cannot be removed during enum
	wxArrayString invalidGroups;
	wxString stylePath = "/Styles";
	wxConfig::SetPath(stylePath);
	bool hasMoreGroups = wxConfig::GetFirstGroup(group, index);
	// if there are no entries initialize the defaults
	if (!hasMoreGroups)
		SaveStcStyleOptions(styleVector);
	else
	{
		// process the style entries
		while (hasMoreGroups)
		{
			wxString groupPath = stylePath + "/" + group;
			bool ok = UpdateStyleEntry(groupPath, styleVector);
			if (!ok)
				invalidGroups.Add(groupPath);
			wxConfig::SetPath(stylePath);
			hasMoreGroups = wxConfig::GetNextGroup(group, index);
		}
		// remove invalid groups
		if (invalidGroups.GetCount())
		{
			for (size_t i = 0; i < invalidGroups.GetCount(); i++)
			{
				ShowInvalidConfig(invalidGroups[i]);
				wxConfig::DeleteGroup(invalidGroups[i]);
			}
			wxConfig::Flush();
		}
	}
	wxConfig::SetPath("/");
	return styleVector;
}

void Config::InitializeConfigFile()
// Initialize the config file for the first use.
{
	wxConfig::SetPath("/");
	// set these to true
	wxConfig::Write(LINE_NUMBERS, asTRUE);
	wxConfig::Write(TOOLBAR_TOOLTIPS, asTRUE);
	wxConfig::Write(DIALOG_TOOLTIPS, asTRUE);
	wxConfig::Write(LOAD_SESSION, asTRUE);
	wxConfig::Write(SHOW_TOOLBAR, asTRUE);
	wxConfig::Write(SHOW_STATUSBAR, asTRUE);
	// find some fonts
	wxFont defaultFont = m_frame->FindDefaultFont();
	wxConfig::Write(DEFAULT_FONT_FACE, defaultFont.GetFaceName());
	wxConfig::Write(DEFAULT_FONT_SIZE, wxString::Format("%d", defaultFont.GetPointSize()));
	wxFont commentFont = m_frame->FindCommentFont();
	wxConfig::Write(COMMENT_FONT_FACE, commentFont.GetFaceName());
	wxConfig::Write(COMMENT_FONT_SIZE, wxString::Format("%d", commentFont.GetPointSize()));
	wxConfig::Flush();
}

void Config::SaveAStyleOptions(AStyleIFace* astyle)
// Save the AStyle options to a config file
{
	wxConfig::SetPath("/AStyle");

	int braceStyle = astyle->getBraceStyle();
	if (braceStyle == STYLE_NONE)
		wxConfig::DeleteEntry(STYLE, false);
	else if (braceStyle == STYLE_ALLMAN)
		wxConfig::Write(STYLE, ALLMAN);
	else if (braceStyle == STYLE_JAVA)
		wxConfig::Write(STYLE, JAVA);
	else if (braceStyle == STYLE_KR)
		wxConfig::Write(STYLE, KandR);
	else if (braceStyle == STYLE_STROUSTRUP)
		wxConfig::Write(STYLE, STROUSTRUP);
	else if (braceStyle == STYLE_WHITESMITH)
		wxConfig::Write(STYLE, WHITESMITH);
	else if (braceStyle == STYLE_VTK)
		wxConfig::Write(STYLE, VTK);
	else if (braceStyle == STYLE_RATLIFF)
		wxConfig::Write(STYLE,  RATLIFF);
	else if (braceStyle == STYLE_GNU)
		wxConfig::Write(STYLE, GNU);
	else if (braceStyle == STYLE_LINUX)
		wxConfig::Write(STYLE, LINUXX);
	else if (braceStyle == STYLE_HORSTMANN)
		wxConfig::Write(STYLE, HORSTMANN);
	else if (braceStyle == STYLE_1TBS)
		wxConfig::Write(STYLE, oneTBS);
	else if (braceStyle == STYLE_GOOGLE)
		wxConfig::Write(STYLE, GOOGLE);
	else if (braceStyle == STYLE_MOZILLA)
		wxConfig::Write(STYLE, MOZILLA);
	else if (braceStyle == STYLE_WEBKIT)
		wxConfig::Write(STYLE, WEBKIT);
	else if (braceStyle == STYLE_PICO)
		wxConfig::Write(STYLE, PICO);
	else if (braceStyle == STYLE_LISP)
		wxConfig::Write(STYLE, LISP);

	astyle->getAttachNamespace() ? wxConfig::Write(ATTACH_NAMESPACES, asTRUE) : wxConfig::DeleteEntry(ATTACH_NAMESPACES, false);
	astyle->getAttachClass() ? wxConfig::Write(ATTACH_CLASSES, asTRUE) : wxConfig::DeleteEntry(ATTACH_CLASSES, false);
	astyle->getAttachInline() ? wxConfig::Write(ATTACH_INLINES, asTRUE) : wxConfig::DeleteEntry(ATTACH_INLINES, false);
	astyle->getAttachExternC() ? wxConfig::Write(ATTACH_EXTERN_C, asTRUE) : wxConfig::DeleteEntry(ATTACH_EXTERN_C, false);
	astyle->getAttachClosingWhile() ? wxConfig::Write(ATTACH_CLOSING_WHILE, asTRUE) : wxConfig::DeleteEntry(ATTACH_CLOSING_WHILE, false);

	IndentType indentType = static_cast<IndentType>(astyle->getIndentType());
	int indentLength = astyle->getIndentLength();
	bool useTabLength = astyle->getUseTabLength();
	int tabLength = astyle->getTabLength();
	int defaultIndentLength = astyle->getDefaultIndentLength();
	int defaultTabLength = astyle->getDefaultTabLength();
	if (indentLength == defaultIndentLength && indentType == INDENT_SPACES)
	{
		wxConfig::DeleteEntry(INDENT_TYPE, false);
		wxConfig::DeleteEntry(INDENT_LENGTH, false);
	}
	else if (indentLength == defaultIndentLength)
	{
		if (indentType == INDENT_TABS)
			wxConfig::Write(INDENT_TYPE, INDENT_TYPE_TAB);
		else if (indentType == INDENT_FTABS)
			wxConfig::Write(INDENT_TYPE, INDENT_TYPE_FTAB);
		wxConfig::DeleteEntry(INDENT_LENGTH, false);
	}
	else
	{
		if (indentType == INDENT_SPACES)
			wxConfig::Write(INDENT_TYPE, INDENT_TYPE_SPACES);
		else if (indentType == INDENT_TABS)
			wxConfig::Write(INDENT_TYPE, INDENT_TYPE_TAB);
		else if (indentType == INDENT_FTABS)
			wxConfig::Write(INDENT_TYPE, INDENT_TYPE_FTAB);
		if (indentLength < 2)
			indentLength = 2;
		else if (indentLength > 20)
			indentLength = 20;
		wxConfig::Write(INDENT_LENGTH, wxString::Format("%d", indentLength));
	}
	if (indentType == INDENT_FTABS && useTabLength)
	{
		wxConfig::Write(USE_TAB_LENGTH, asTRUE);
		if (tabLength != defaultTabLength)
			wxConfig::Write(TAB_LENGTH, wxString::Format("%d", tabLength));
		else
			wxConfig::DeleteEntry(TAB_LENGTH, false);
	}
	else
	{
		wxConfig::DeleteEntry(USE_TAB_LENGTH, false);
		wxConfig::DeleteEntry(TAB_LENGTH, false);
	}

	astyle->getClassIndent() ? wxConfig::Write(INDENT_CLASSES, asTRUE) : wxConfig::DeleteEntry(INDENT_CLASSES, false);
	astyle->getModifierIndent() ? wxConfig::Write(INDENT_MODIFIERS, asTRUE) : wxConfig::DeleteEntry(INDENT_MODIFIERS, false);
	astyle->getSwitchIndent() ? wxConfig::Write(INDENT_SWITCHES, asTRUE) : wxConfig::DeleteEntry(INDENT_SWITCHES, false);
	astyle->getCaseIndent() ? wxConfig::Write(INDENT_CASES, asTRUE) : wxConfig::DeleteEntry(INDENT_CASES, false);
	astyle->getNamespaceIndent() ? wxConfig::Write(INDENT_NAMESPACES, asTRUE) : wxConfig::DeleteEntry(INDENT_NAMESPACES, false);
	astyle->getAfterParenIndent() ? wxConfig::Write(INDENT_AFTER_PARENS, asTRUE) : wxConfig::DeleteEntry(INDENT_AFTER_PARENS, false);

	int continuationIndent = astyle->getContinuationIndent();
	if (continuationIndent < 0 || continuationIndent >= 5)
		continuationIndent = astyle->getDefaultContinuationIndent();
	if (continuationIndent == astyle->getDefaultContinuationIndent())
		wxConfig::DeleteEntry(INDENT_CONTINUATION, false);
	else
		wxConfig::Write(INDENT_CONTINUATION, wxString::Format("%d", continuationIndent));

	astyle->getLabelIndent() ? wxConfig::Write(INDENT_LABELS, asTRUE) : wxConfig::DeleteEntry(INDENT_LABELS, false);
	astyle->getPreprocBlockIndent() ? wxConfig::Write(INDENT_PREPROC_BLOCK, asTRUE) : wxConfig::DeleteEntry(INDENT_PREPROC_BLOCK, false);
	astyle->getPreprocDefineIndent() ? wxConfig::Write(INDENT_PREPROC_DEFINE, asTRUE) : wxConfig::DeleteEntry(INDENT_PREPROC_DEFINE, false);
	astyle->getPreprocCondIndent() ? wxConfig::Write(INDENT_PREPROC_COND, asTRUE) : wxConfig::DeleteEntry(INDENT_PREPROC_COND, false);
	astyle->getCol1CommentIndent() ? wxConfig::Write(INDENT_COL1_COMMENTS, asTRUE) : wxConfig::DeleteEntry(INDENT_COL1_COMMENTS, false);

	int minConditionalOption = astyle->getMinConditionalOption();
	if (minConditionalOption < 0 || minConditionalOption >= MINCOND_END)
		minConditionalOption = astyle->getDefaultMinConditionalOption();
	if (minConditionalOption == astyle->getDefaultMinConditionalOption())
		wxConfig::DeleteEntry(MIN_CONDITIONAL_INDENT, false);
	else
		wxConfig::Write(MIN_CONDITIONAL_INDENT, wxString::Format("%d", minConditionalOption));

	int maxContinuationIndent = astyle->getMaxContinuationIndent();
	if (maxContinuationIndent < 40)
		maxContinuationIndent = 40;
	else if (maxContinuationIndent > 120)
		maxContinuationIndent = 120;
	if (maxContinuationIndent == astyle->getDefaultMaxContinuationIndent())
		wxConfig::DeleteEntry(MAX_CONTINUATION_INDENT, false);
	else
		wxConfig::Write(MAX_CONTINUATION_INDENT, wxString::Format("%d", maxContinuationIndent));

	if (astyle->getBreakHeaderBlocks() && astyle->getBreakClosingBlocks())
		wxConfig::Write(BREAK_BLOCKS, "all");
	else if (astyle->getBreakHeaderBlocks())
		wxConfig::Write(BREAK_BLOCKS, "open");
	else
		wxConfig::DeleteEntry(BREAK_BLOCKS, false);

	astyle->getPadOperator() ? wxConfig::Write(PAD_OPER, asTRUE) : wxConfig::DeleteEntry(PAD_OPER, false);
	astyle->getPadComma() ? wxConfig::Write(PAD_COMMA, asTRUE) : wxConfig::DeleteEntry(PAD_COMMA, false);

	if (astyle->getPadParenOutside() && astyle->getPadParenInside())
		wxConfig::Write(PAD_PAREN, "all");
	else if (astyle->getPadParenOutside())
		wxConfig::Write(PAD_PAREN, "out");
	else if (astyle->getPadParenInside())
		wxConfig::Write(PAD_PAREN, "in");
	else
		wxConfig::DeleteEntry(PAD_PAREN, false);

	astyle->getPadFirstParenOut() ? wxConfig::Write(PAD_FIRST_PAREN_OUT, asTRUE) : wxConfig::DeleteEntry(PAD_FIRST_PAREN_OUT, false);
	astyle->getPadHeader() ? wxConfig::Write(PAD_HEADER, asTRUE) : wxConfig::DeleteEntry(PAD_HEADER, false);
	astyle->getUnpadParen() ? wxConfig::Write(UNPAD_PAREN, asTRUE) : wxConfig::DeleteEntry(UNPAD_PAREN, false);
	astyle->getDeleteEmptyLines() ? wxConfig::Write(DELETE_EMPTY_LINES, asTRUE) : wxConfig::DeleteEntry(DELETE_EMPTY_LINES, false);
	astyle->getFillEmptyLines() ? wxConfig::Write(FILL_EMPTY_LINES, asTRUE) : wxConfig::DeleteEntry(FILL_EMPTY_LINES, false);

	// align pointer
	if (astyle->getAlignPointer() < 0 || astyle->getAlignPointer() >= PTR_ALIGN_END)
		astyle->setAlignPointer(PTR_ALIGN_NONE);
	if (astyle->getAlignPointer() == PTR_ALIGN_NONE)
		wxConfig::DeleteEntry(ALIGN_POINTER, false);
	else
		wxConfig::Write(ALIGN_POINTER, wxString::Format("%d", astyle->getAlignPointer()));
	// align reference
	if (astyle->getAlignReference() < 0
	        || astyle->getAlignReference() >= REF_ALIGN_END
	        || (astyle->getAlignReference() == astyle->getAlignPointer()
	            && astyle->getAlignReference() != REF_ALIGN_NONE))
		astyle->setAlignReference(REF_SAME_AS_PTR);
	if (astyle->getAlignReference() == REF_SAME_AS_PTR)
		wxConfig::DeleteEntry(ALIGN_REFERENCE, false);
	else
		wxConfig::Write(ALIGN_REFERENCE, wxString::Format("%d", astyle->getAlignReference()));

	astyle->getBreakClosingBraces() ? wxConfig::Write(BREAK_CLOSING_BRACES, asTRUE) : wxConfig::DeleteEntry(BREAK_CLOSING_BRACES, false);
	astyle->getBreakElseIfs() ? wxConfig::Write(BREAK_ELSEIFS, asTRUE) : wxConfig::DeleteEntry(BREAK_ELSEIFS, false);
	astyle->getBreakOneLineHeaders() ? wxConfig::Write(BREAK_ONE_LINE_HEADERS, asTRUE) : wxConfig::DeleteEntry(BREAK_ONE_LINE_HEADERS, false);
	astyle->getAddBraces() ? wxConfig::Write(ADD_BRACES, asTRUE) : wxConfig::DeleteEntry(ADD_BRACES, false);
	astyle->getAddOneLineBraces() ? wxConfig::Write(ADD_ONE_LINE_BRACES, asTRUE) : wxConfig::DeleteEntry(ADD_ONE_LINE_BRACES, false);
	astyle->getRemoveBraces() ? wxConfig::Write(REMOVE_BRACES, asTRUE) : wxConfig::DeleteEntry(REMOVE_BRACES, false);
	astyle->getBreakReturnType() ? wxConfig::Write(BREAK_RETURN_TYPE, asTRUE) : wxConfig::DeleteEntry(BREAK_RETURN_TYPE, false);
	astyle->getBreakReturnTypeDecl() ? wxConfig::Write(BREAK_RETURN_TYPE_DECL, asTRUE) : wxConfig::DeleteEntry(BREAK_RETURN_TYPE_DECL, false);
	astyle->getAttachReturnType() ? wxConfig::Write(ATTACH_RETURN_TYPE, asTRUE) : wxConfig::DeleteEntry(ATTACH_RETURN_TYPE, false);
	astyle->getAttachReturnTypeDecl() ? wxConfig::Write(ATTACH_RETURN_TYPE_DECL, asTRUE) : wxConfig::DeleteEntry(ATTACH_RETURN_TYPE_DECL, false);
	astyle->getBreakOneLineBlocks()  ? wxConfig::DeleteEntry(KEEP_ONE_LINE_BLOCKS, false) : wxConfig::Write(KEEP_ONE_LINE_BLOCKS, asTRUE);
	astyle->getBreakOneLineStmts() ? wxConfig::DeleteEntry(KEEP_ONE_LINE_STATEMENTS, false) : wxConfig::Write(KEEP_ONE_LINE_STATEMENTS, asTRUE);
	astyle->getConvertTabs() ? wxConfig::Write(CONVERT_TABS, asTRUE) : wxConfig::DeleteEntry(CONVERT_TABS, false);
	astyle->getCloseTemplates() ? wxConfig::Write(CLOSE_TEMPLATES, asTRUE) : wxConfig::DeleteEntry(CLOSE_TEMPLATES, false);
	astyle->getRemoveCommentPrefix() ? wxConfig::Write(REMOVE_COMMENT_PREFIX, asTRUE) : wxConfig::DeleteEntry(REMOVE_COMMENT_PREFIX, false);

	int maxCodeLength = astyle->getMaxCodeLength();
	if (maxCodeLength > 0)		// default value is 0, no maximum
	{
		if (maxCodeLength < MAX_CODE_LENGTH_MIN)
			maxCodeLength = MAX_CODE_LENGTH_MIN;
		else if (maxCodeLength > MAX_CODE_LENGTH_MAX)
			maxCodeLength = MAX_CODE_LENGTH_MAX;
	}
	if (maxCodeLength == astyle->getDefaultMaxCodeLength())
		wxConfig::DeleteEntry(MAX_CODE_LENGTH, false);
	else
		wxConfig::Write(MAX_CODE_LENGTH, wxString::Format("%d", maxCodeLength));

	(astyle->getBreakAfterLogical() && maxCodeLength > 0) ?
	wxConfig::Write(BREAK_AFTER_LOGICAL, asTRUE) : wxConfig::DeleteEntry(BREAK_AFTER_LOGICAL, false);

	astyle->getPadMethodPrefix() ? wxConfig::Write(PAD_METHOD_PREFIX, asTRUE) : wxConfig::DeleteEntry(PAD_METHOD_PREFIX, false);
	astyle->getUnpadMethodPrefix() ? wxConfig::Write(UNPAD_METHOD_PREFIX, asTRUE) : wxConfig::DeleteEntry(UNPAD_METHOD_PREFIX, false);
	astyle->getPadReturnType() ? wxConfig::Write(PAD_RETURN_TYPE, asTRUE) : wxConfig::DeleteEntry(PAD_RETURN_TYPE, false);
	astyle->getUnpadReturnType() ? wxConfig::Write(UNPAD_RETURN_TYPE, asTRUE) : wxConfig::DeleteEntry(UNPAD_RETURN_TYPE, false);
	astyle->getPadParamType() ? wxConfig::Write(PAD_PARAM_TYPE, asTRUE) : wxConfig::DeleteEntry(PAD_PARAM_TYPE, false);
	astyle->getUnpadParamType() ? wxConfig::Write(UNPAD_PARAM_TYPE, asTRUE) : wxConfig::DeleteEntry(UNPAD_PARAM_TYPE, false);
	astyle->getAlignMethodColon() ? wxConfig::Write(ALIGN_METHOD_COLON, asTRUE) : wxConfig::DeleteEntry(ALIGN_METHOD_COLON, false);

	int padMethodColon = astyle->getPadMethodColon();
	if (padMethodColon != COLON_PAD_NO_CHANGE)
	{
		if (padMethodColon <= COLON_PAD_NO_CHANGE)
			padMethodColon = COLON_PAD_NO_CHANGE + 1;
		else if (padMethodColon >= COLON_PAD_END)
			padMethodColon = COLON_PAD_END - 1;
	}
	if (padMethodColon == COLON_PAD_NO_CHANGE)
		wxConfig::DeleteEntry(PAD_METHOD_COLON, false);
	else
		wxConfig::Write(PAD_METHOD_COLON, astyle->TranslatePadMethodColonValue(padMethodColon));

	// file mode option is not saved
	wxConfig::Flush();
	wxConfig::SetPath("/");
}

void Config::SaveEditorOptions()
// Save the Editor options to a config file.
// For true/false values, true values are saved, false values are deleted.
{
	wxConfig::SetPath("/");
	// toolbar and dialogs
	m_frame->GetUseBottomTabs()   ? wxConfig::Write(USE_BOTTOM_TABS, asTRUE) : wxConfig::DeleteEntry(USE_BOTTOM_TABS, false);
	m_frame->GetUseSmallToolbar() ? wxConfig::Write(USE_SMALL_TOOLBAR, asTRUE) : wxConfig::DeleteEntry(USE_SMALL_TOOLBAR, false);
	m_frame->GetShowToolTips()    ? wxConfig::Write(TOOLBAR_TOOLTIPS, asTRUE) : wxConfig::DeleteEntry(TOOLBAR_TOOLTIPS, false);
	m_frame->GetShowDialogTips()  ? wxConfig::Write(DIALOG_TOOLTIPS, asTRUE) : wxConfig::DeleteEntry(DIALOG_TOOLTIPS, false);
	m_frame->GetLoadSession()     ? wxConfig::Write(LOAD_SESSION, asTRUE) : wxConfig::DeleteEntry(LOAD_SESSION, false);
	// find dialog
	m_frame->GetHideFindDialog()  ? wxConfig::Write(HIDE_FIND, asTRUE) : wxConfig::DeleteEntry(HIDE_FIND, false);
	m_frame->GetWrapSearch()      ? wxConfig::Write(WRAP_SEARCH, asTRUE) : wxConfig::DeleteEntry(WRAP_SEARCH, false);
	// fonts
	wxConfig::Write(DEFAULT_FONT_FACE, m_frame->GetDefaultFont().GetFaceName());
	wxConfig::Write(DEFAULT_FONT_SIZE, wxString::Format("%d", m_frame->GetDefaultFont().GetPointSize()));
	wxConfig::Write(COMMENT_FONT_FACE, m_frame->GetCommentFont().GetFaceName());
	wxConfig::Write(COMMENT_FONT_SIZE, wxString::Format("%d", m_frame->GetCommentFont().GetPointSize()));
	// other
	wxConfig::Write(FILE_FILTER_INDEX, wxString::Format("%d", m_frame->GetFileFilterIndex()));
	wxConfig::Write(ASTYLE_DLG_PAGE, wxString::Format("%d", m_frame->GetAStyleDlgPage()));
	wxConfig::Write(EDITOR_DLG_PAGE, wxString::Format("%d", m_frame->GetEditorDlgPage()));
	m_frame->IsMaximized() ? wxConfig::Write(FRAME_MAXIMIZED, asTRUE) : wxConfig::DeleteEntry(FRAME_MAXIMIZED, false);
	wxConfig::Flush();
	wxConfig::SetPath("/");
}

void Config::SaveSessionFiles()
{
	wxConfig::SetPath("/Session");
	wxArrayString filePaths = m_frame->GetOpenFilePaths();
	// save current session if option is set
	size_t fileCount = filePaths.GetCount();
	size_t i = 0;
	if (m_frame->GetLoadSession())
	{
		for (i = 0; i < fileCount; i++)
		{
			wxFileName filePath = filePaths[i];
			if (!filePath.IsAbsolute())
				continue;
			wxString key = SESSION_FILE + wxString::Format("%d", static_cast<int>(i + 1));
			wxConfig::Write(key, filePath.GetFullPath());
		}
	}
	// remove extra entries
	size_t sessionCount = wxConfig::GetNumberOfEntries();
	for (; i < sessionCount; i++)
	{
		wxString key = SESSION_FILE + wxString::Format("%d", static_cast<int>(i + 1));
		wxConfig::DeleteEntry(key);
	}
}

void Config::SaveStcStyleOptions(const vector<TextStyle>& styleVector)
// Save ALL variable style options to a config file.
{
	for (TextStyle textStyle : styleVector)
	{
		wxString stylePath = wxString::Format("/Styles/Style-%02u", textStyle.style);
		wxConfig::SetPath(stylePath);
		wxConfig::Write("fore", textStyle.fore.GetAsString(wxC2S_CSS_SYNTAX));
		wxConfig::Write("back", textStyle.back.GetAsString(wxC2S_CSS_SYNTAX));
		wxConfig::Write("bold", textStyle.bold ? asTRUE : asFALSE);
		wxConfig::Write("italic", textStyle.italic ? asTRUE : asFALSE);
	}
	wxConfig::Flush();
	wxConfig::SetPath("/");
}

void Config::SaveTestOptions(const wxString& testOptions)
// Save the test options to a config file.
{
	wxConfig::SetPath("/");
	testOptions != wxEmptyString ? wxConfig::Write(TEST_OPTIONS, testOptions) : wxConfig::DeleteEntry(TEST_OPTIONS, false);
	wxConfig::Flush();
	wxConfig::SetPath("/");
}

void Config::SaveViewMenuOptions()
// Save the View menu status to a config file.
// Checked values are saved, unchecked values are deleted.
{
	wxConfig::SetPath("/");
	// view menu
	m_frame->IsMenuItemChecked(ID_VIEW_LINENUMBERS) ? wxConfig::Write(LINE_NUMBERS, asTRUE) : wxConfig::DeleteEntry(LINE_NUMBERS, false);
	m_frame->IsMenuItemChecked(ID_VIEW_MARGIN) ? wxConfig::Write(SELECTION_MARGIN, asTRUE) : wxConfig::DeleteEntry(SELECTION_MARGIN, false);
	m_frame->IsMenuItemChecked(ID_VIEW_WHITESPACE) ? wxConfig::Write(WHITESPACE, asTRUE) : wxConfig::DeleteEntry(WHITESPACE, false);
	m_frame->IsMenuItemChecked(ID_VIEW_ACTIVELINE) ? wxConfig::Write(ACTIVE_LINE, asTRUE) : wxConfig::DeleteEntry(ACTIVE_LINE, false);
	m_frame->IsMenuItemChecked(ID_VIEW_INDENTGUIDES) ? wxConfig::Write(INDENT_GUIDES, asTRUE) : wxConfig::DeleteEntry(INDENT_GUIDES, false);
	m_frame->IsMenuItemChecked(ID_VIEW_ENDLINE) ? wxConfig::Write(END_OF_LINE, asTRUE) : wxConfig::DeleteEntry(END_OF_LINE, false);
	m_frame->IsMenuItemChecked(ID_VIEW_WORDWRAP) ? wxConfig::Write(WORD_WRAP, asTRUE) : wxConfig::DeleteEntry(WORD_WRAP, false);
	m_frame->IsMenuItemChecked(ID_VIEW_MONOSPACE) ? wxConfig::Write(MONOSPACE, asTRUE) : wxConfig::DeleteEntry(MONOSPACE, false);

	m_frame->IsMenuItemChecked(ID_VIEW_TOOLBAR) ? wxConfig::Write(SHOW_TOOLBAR, asTRUE) : wxConfig::DeleteEntry(SHOW_TOOLBAR, false);
	m_frame->IsMenuItemChecked(ID_VIEW_STATUSBAR) ? wxConfig::Write(SHOW_STATUSBAR, asTRUE) : wxConfig::DeleteEntry(SHOW_STATUSBAR, false);
	wxConfig::Flush();
}

void Config::ShowInvalidConfig(const wxString& entry)
// Show the invalid config file entries before they are deleted.
{
	if (wxConfig::GetEntryType(entry) == wxConfig::Type_String)
	{
		wxString value;
		wxConfig::Read(entry, &value);
		ShowMessageDialog(wxString::Format(
		                      "Invalid config file entry\n"
		                      "\"%s\"  \"%s\"."
		                      "\n\nThe entry will be removed!",
		                      entry, value),
		                  wxOK | wxICON_ERROR);
	}
	else
	{
		ShowMessageDialog(wxString::Format(
		                      "Invalid config file value\n"
		                      "\"%s\"  \"%s\"."
		                      "\n\nThe entry will be removed!",
		                      entry, "non-string value"),
		                  wxOK | wxICON_ERROR);
	}
}

bool Config::UpdateStyleEntry(const wxString& groupPath, vector<TextStyle>& styleVector)
// Update a style from the given group path.
// This is a private function called by GetStcStyleOptions().
{
	// enumeration variables
	wxString key;       // Style key
	wxString value;		// value of the key
	long index;			// don't use this

	// invalid entries cannot be removed during enum
	wxArrayString invalidEntries;
	wxConfig::SetPath(groupPath);
	bool hasMoreEntries = wxConfig::GetFirstEntry(key, index);
	if (!hasMoreEntries)
		return false;
	// update the styles vector from the config keys
	const int iStyle = FindStyleVectorIndex(groupPath, styleVector);
	if (iStyle == wxNOT_FOUND)
		return false;
	while (hasMoreEntries)
	{
		wxConfig::Read(key, &value);
		if (key == "fore")
		{
			wxColour color;
			if (color.Set(value))
				styleVector[iStyle].fore = color;
			else
				invalidEntries.Add(key);
		}
		else if (key == "back")
		{
			wxColour color;
			if (color.Set(value))
				styleVector[iStyle].back = color;
			else
				invalidEntries.Add(key);
		}
		else if (key == "bold")
			styleVector[iStyle].bold = (value == asTRUE ? true : false);
		else if (key == "italic")
			styleVector[iStyle].italic = (value == asTRUE ? true : false);
		else
			invalidEntries.Add(key);
		hasMoreEntries = wxConfig::GetNextEntry(key, index);
	}
	// remove invalid entries
	if (invalidEntries.GetCount())
	{
		for (size_t i = 0; i < invalidEntries.GetCount(); i++)
		{
			ShowInvalidConfig(invalidEntries[i]);
			wxConfig::DeleteEntry(invalidEntries[i], false);
		}
		wxConfig::Flush();
	}
	if (wxConfig::GetNumberOfEntries() == 0)
		return false;
	return true;
}
