// AStyleIFace.h
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

#ifndef ASTYLE_IFACE_H
#define ASTYLE_IFACE_H

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include "Constants.h"

#ifdef ASTYLE_DYLIB
	#include <wx/dynlib.h>
#endif

#ifdef __clang__
	#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#endif

//-----------------------------------------------------------------------------
// AStyleIFace Class
//-----------------------------------------------------------------------------

class AStyleIFace
{
public:
	AStyleIFace() = default;
	virtual ~AStyleIFace()                     = default;
	AStyleIFace(const AStyleIFace&)            = default;
	AStyleIFace& operator=(AStyleIFace const&) = default;

	void AppendFileModeOption(FileMode fileMode, wxString& options) const;
	wxString GetOptions(bool showShort = false, bool useSeparator = true) const;
	virtual bool SetAStyleOption(const wxString& key, const wxString& value);	// mocked in tests
	int TranslatePadMethodColonString(const wxString& padMethodColonArg) const;
	wxString TranslatePadMethodColonValue(int padMethodColonArg) const;
	wxString TranslatePadMethodColonValueShort(int padMethodColonArg) const;

public:
	// default getters
	int  GetDefaultIndentLength() const          { return defaultIndentLength; }
	int  GetDefaultTabLength() const             { return defaultTabLength; }
	int  GetDefaultContinuationIndent() const    { return defaultContinuationIndent; }
	MinConditional GetDefaultMinConditionalOption() const  { return defaultMinConditionalOption; }
	int  GetDefaultMaxContinuationIndent() const { return defaultMaxContinuationIndent; }
	int  GetDefaultMaxCodeLength() const         { return defaultMaxCodeLength; }
	// getters - brace style
	int  GetBraceStyle() const           { return braceStyle; }
	// getters - tab
	int  GetIndentType() const           { return indentType; }
	int  GetIndentLength() const         { return indentLength; }
	bool GetUseTabLength() const         { return useTabLength; }
	int  GetTabLength() const            { return tabLength; }
	// getters - brace modifiers
	bool GetAttachNamespace() const      { return attachNamespace; }
	bool GetAttachClass() const          { return attachClass; }
	bool GetAttachInline() const         { return attachInline; }
	bool GetAttachExternC() const        { return attachExternC; }
	bool GetAttachClosingWhile() const   { return attachClosingWhile; }
	// getters - indentation
	bool GetClassIndent() const          { return classIndent; }
	bool GetModifierIndent() const       { return modifierIndent; }
	bool GetSwitchIndent() const         { return switchIndent; }
	bool GetCaseIndent() const           { return caseIndent; }
	bool GetNamespaceIndent() const      { return namespaceIndent; }
	bool GetAfterParenIndent() const     { return afterParenIndent; }
	int  GetContinuationIndent() const   { return continuationIndent; }
	bool GetLabelIndent() const          { return labelIndent; }
	bool GetPreprocBlockIndent() const   { return preprocBlockIndent; }
	bool GetPreprocDefineIndent() const  { return preprocDefineIndent; }
	bool GetPreprocCondIndent() const    { return preprocCondIndent; }
	bool GetCol1CommentIndent() const    { return col1CommentIndent; }
	int  GetMinConditionalOption() const { return minConditionalOption; }
	int  GetMaxContinuationIndent() const { return maxContinuationIndent; }
	// getters - padding
	bool GetBreakHeaderBlocks() const    { return breakHeaderBlocks; }
	bool GetBreakClosingBlocks() const   { return breakClosingBlocks; }
	bool GetPadOperator() const          { return padOperator; }
	bool GetPadComma() const             { return padComma; }
	bool GetPadParenOutside() const      { return padParenOutside; }
	bool GetPadParenInside() const       { return padParenInside; }
	bool GetPadFirstParenOut() const     { return padFirstParenOut; }
	bool GetPadHeader() const            { return padHeader; }
	bool GetUnpadParen() const           { return unpadParen; }
	bool GetDeleteEmptyLines() const     { return deleteEmptyLines; }
	bool GetFillEmptyLines() const       { return fillEmptyLines; }
	int  GetAlignPointer() const         { return alignPointer; }
	int  GetAlignReference() const       { return alignReference; }
	// getters - formatting
	bool GetBreakClosingBraces() const   { return breakClosingBraces; }
	bool GetBreakElseIfs() const         { return breakElseIfs; }
	bool GetBreakOneLineHeaders() const  { return breakOneLineHeaders; }
	bool GetAddBraces() const            { return addBraces; }
	bool GetAddOneLineBraces() const     { return addOneLineBraces; }
	bool GetRemoveBraces() const         { return removeBraces; }
	bool GetBreakReturnType() const      { return breakReturnType; }
	bool GetBreakReturnTypeDecl() const  { return breakReturnTypeDecl; }
	bool GetAttachReturnType() const     { return attachReturnType; }
	bool GetAttachReturnTypeDecl() const { return attachReturnTypeDecl; }
	bool GetBreakOneLineBlocks() const   { return breakOneLineBlocks; }
	bool GetBreakOneLineStmts() const    { return breakOneLineStmts; }
	bool GetConvertTabs() const          { return convertTabs; }
	bool GetCloseTemplates() const       { return closeTemplates; }
	bool GetRemoveCommentPrefix() const  { return removeCommentPrefix; }
	int  GetMaxCodeLength() const        { return maxCodeLength; }
	bool GetBreakAfterLogical() const    { return breakAfterLogical; }
	// getters - other
	bool GetPadMethodPrefix() const      { return padMethodPrefix; }
	bool GetUnpadMethodPrefix() const    { return unpadMethodPrefix; }
	bool GetPadReturnType() const        { return padReturnType; }
	bool GetUnpadReturnType() const      { return unpadReturnType; }
	bool GetPadParamType() const         { return padParamType; }
	bool GetUnpadParamType() const       { return unpadParamType; }
	bool GetAlignMethodColon() const     { return alignMethodColon; }
	int  GetPadMethodColon() const       { return padMethodColon; }
	// setters - brace style
	void SetBraceStyle(BraceStyle value)   { braceStyle = value; }
	// setters - tab
	void SetIndentType(IndentType value)     { indentType = value; }
	void SetIndentLength(int value)          { indentLength = value; }
	void SetUseTabLength(bool state)         { useTabLength = state; }
	void SetTabLength(int value)             { tabLength = value; }
	// setters - brace modifiers
	void SetAttachNamespace(bool state)      { attachNamespace = state; }
	void SetAttachClass(bool state)          { attachClass = state; }
	void SetAttachInline(bool state)         { attachInline = state; }
	void SetAttachExternC(bool state)        { attachExternC = state; }
	void SetAttachClosingWhile(bool state)   { attachClosingWhile = state; }
	// setters - indentation
	void SetClassIndent(bool state)          { classIndent = state; }
	void SetModifierIndent(bool state)       { modifierIndent = state; }
	void SetSwitchIndent(bool state)         { switchIndent = state; }
	void SetCaseIndent(bool state)           { caseIndent = state; }
	void SetNamespaceIndent(bool state)      { namespaceIndent = state; }
	void SetAfterParenIndent(bool state)     { afterParenIndent = state; }
	void SetContinuationIndent(int value)    { continuationIndent = value; }
	void SetLabelIndent(bool state)          { labelIndent = state; }
	void SetPreprocBlockIndent(bool state)   { preprocBlockIndent = state; }
	void SetPreprocDefineIndent(bool state)  { preprocDefineIndent = state; }
	void SetPreprocCondIndent(bool state)    { preprocCondIndent = state; }
	void SetCol1CommentIndent(bool state)    { col1CommentIndent = state; }
	void SetMinConditionalOption(MinConditional value)  { minConditionalOption = value; }
	void SetMaxContinuationIndent(int value) { maxContinuationIndent = value; }
	// setters - padding
	void SetBreakHeaderBlocks(bool state)    { breakHeaderBlocks = state; }
	void SetBreakClosingBlocks(bool state)   { breakClosingBlocks = state; }
	void SetPadOperator(bool state)          { padOperator = state; }
	void SetPadComma(bool state)             { padComma = state; }
	void SetPadParenOutside(bool state)      { padParenOutside = state; }
	void SetPadParenInside(bool state)       { padParenInside = state; }
	void SetPadFirstParenOut(bool state)     { padFirstParenOut = state; }
	void SetPadHeader(bool state)            { padHeader = state; }
	void SetUnpadParen(bool state)           { unpadParen = state; }
	void SetDeleteEmptyLines(bool state)     { deleteEmptyLines = state; }
	void SetFillEmptyLines(bool state)       { fillEmptyLines = state; }
	void SetAlignPointer(PointerAlign value)     { alignPointer = value; }
	void SetAlignReference(ReferenceAlign value) { alignReference = value; }
	// setters - formatting
	void SetBreakClosingBraces(bool state)   { breakClosingBraces = state; }
	void SetBreakElseIfs(bool state)         { breakElseIfs = state; }
	void SetBreakOneLineHeaders(bool state)  { breakOneLineHeaders = state; }
	void SetAddBraces(bool state)            { addBraces = state; }
	void SetAddOneLineBraces(bool state)     { addOneLineBraces = state; }
	void SetRemoveBraces(bool state)         { removeBraces = state; }
	void SetBreakReturnType(bool state)      { breakReturnType = state; }
	void SetBreakReturnTypeDecl(bool state)  { breakReturnTypeDecl = state; }
	void SetAttachReturnType(bool state)     { attachReturnType = state; }
	void SetAttachReturnTypeDecl(bool state) { attachReturnTypeDecl = state; }
	void SetBreakOneLineBlocks(bool state)   { breakOneLineBlocks = state; }
	void SetBreakOneLineStmts(bool state)    { breakOneLineStmts = state; }
	void SetConvertTabs(bool state)          { convertTabs = state; }
	void SetCloseTemplates(bool state)       { closeTemplates = state; }
	void SetRemoveCommentPrefix(bool state)  { removeCommentPrefix = state; }
	void SetMaxCodeLength(int value)         { maxCodeLength = value; }
	void SetBreakAfterLogical(bool state)    { breakAfterLogical = state; }
	// setters - other
	void SetPadMethodPrefix(bool state)      { padMethodPrefix = state; }
	void SetUnpadMethodPrefix(bool state)    { unpadMethodPrefix = state; }
	void SetPadReturnType(bool state)        { padReturnType = state; }
	void SetUnpadReturnType(bool state)      { unpadReturnType = state; }
	void SetPadParamType(bool state)         { padParamType = state; }
	void SetUnpadParamType(bool state)       { unpadParamType = state; }
	void SetAlignMethodColon(bool state)     { alignMethodColon = state; }
	void SetPadMethodColon(int value)        { padMethodColon = value; }

private:
	bool SetAStyleOptionBool(const wxString& key, bool value);

private:
	// the initial value is the default value in Artistic Style
	// comments are the AStyle command line option used to set the variable

	// brace style options
	BraceStyle braceStyle      = STYLE_NONE;     // --style=?

	// tabs/spaces options
	IndentType indentType      = INDENT_SPACES;  // --indent=?, --indent=force-tab=#
	int indentLength           = 4;              // --indent=?, --force-indent=tab=#
	bool useTabLength          = false;          // --indent=force-tab-x=#
	int tabLength              = 8;              // --indent=force-tab-x=#

	// brace modifier options
	bool attachNamespace       = false;          // --attach-namespaces
	bool attachClass           = false;          // --attach-classes
	bool attachInline          = false;          // --attach-inlines
	bool attachExternC         = false;          // --attach-extern-c
	bool attachClosingWhile    = false;          // --attach-closing-while

	// indentation options
	bool classIndent           = false;          // --indent-classes
	bool modifierIndent        = false;          // --indent-modifiers
	bool switchIndent          = false;          // --indent-switches
	bool caseIndent            = false;          // --indent-cases
	bool namespaceIndent       = false;          // --indent-namespaces
	bool afterParenIndent      = false;          // --indent-after-parens
	int  continuationIndent    = 1;              // --indent-continuation=#
	bool labelIndent           = false;          // --indent-labels
	bool preprocBlockIndent    = false;          // --indent-preproc-block
	bool preprocDefineIndent   = false;          // --indent-preproc-define
	bool preprocCondIndent     = false;          // --indent-preproc-cond
	bool col1CommentIndent     = false;          // --indent-col1-comments
	MinConditional minConditionalOption = MINCOND_TWO;  // --min-conditional-indent=#
	int  maxContinuationIndent = 40;             // --max-continuation-indent=#

	// padding options
	bool breakHeaderBlocks     = false;          // --break-blocks, --break-blocks=all
	bool breakClosingBlocks    = false;          // --break-blocks=all
	bool padOperator           = false;          // --pad-oper
	bool padComma              = false;          // --pad-comma
	bool padParenOutside       = false;          // --pad-paren, --pad-paren-out
	bool padFirstParenOut      = false;          // --pad-first-paren-out
	bool padParenInside        = false;          // --pad-paren, --pad-paren-in
	bool padHeader             = false;          // --pad-header
	bool unpadParen            = false;          // --unpad-paren
	bool deleteEmptyLines      = false;          // --delete-empty-lines
	bool fillEmptyLines        = false;          // --fill-empty-lines
	PointerAlign alignPointer  = PTR_ALIGN_NONE; // --align-pointer=#
	ReferenceAlign alignReference = REF_SAME_AS_PTR;    // --align-reference=#

	// formatting options
	bool breakClosingBraces    = false;          // --break-closing-braces
	bool breakElseIfs          = false;          // --break-elseifs
	bool breakOneLineHeaders   = false;          // --break-one-line-headers
	bool addBraces             = false;          // --add-braces
	bool addOneLineBraces      = false;          // --add-one-line-braces
	bool removeBraces          = false;          // --remove-braces
	bool breakReturnType       = false;          // --break-return-type
	bool breakReturnTypeDecl   = false;          // --break-return-type-decl
	bool attachReturnType      = false;          // --attach-return-type
	bool attachReturnTypeDecl  = false;          // --attach-return-type-decl
	bool breakOneLineBlocks    = true;           // --keep-one-line-blocks
	bool breakOneLineStmts     = true;           // --keep-one-line-statements
	bool convertTabs           = false;          // --convert-tabs
	bool closeTemplates        = false;          // --close-templates
	bool removeCommentPrefix   = false;          // --remove-comment-prefix
	int  maxCodeLength         = 0;              // --max-code-length=#
	bool breakAfterLogical     = false;          // --break-after-logical

	// other options
	bool padMethodPrefix       = false;          // --pad-method-prefix
	bool unpadMethodPrefix     = false;          // --unpad-method-prefix
	bool padReturnType         = false;          // --pad-return-type
	bool unpadReturnType       = false;          // --unpad-return-type
	bool padParamType          = false;          // --pad-param-type
	bool unpadParamType        = false;          // --unpad-param-type
	bool alignMethodColon      = false;          // --align-method-colon
	int  padMethodColon = COLON_PAD_NO_CHANGE;   // --pad-method-colon=#

	// save integer default values
	int defaultIndentLength          = indentLength;
	int defaultTabLength             = tabLength;
	int defaultContinuationIndent    = continuationIndent;
	MinConditional defaultMinConditionalOption  = minConditionalOption;
	int defaultMaxContinuationIndent = maxContinuationIndent;
	int defaultMaxCodeLength         = maxCodeLength;
};  // class AStyleIFace

#endif      // closes ASTYLE_IFACE_H
