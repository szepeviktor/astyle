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
	int  getDefaultIndentLength() const          { return defaultIndentLength; }
	int  getDefaultTabLength() const             { return defaultTabLength; }
	int  getDefaultContinuationIndent() const    { return defaultContinuationIndent; }
	MinConditional getDefaultMinConditionalOption() const  { return defaultMinConditionalOption; }
	int  getDefaultMaxContinuationIndent() const { return defaultMaxContinuationIndent; }
	int  getDefaultMaxCodeLength() const         { return defaultMaxCodeLength; }
	// getters - brace style
	int  getBraceStyle() const           { return braceStyle; }
	// getters - tab
	int  getIndentType() const           { return indentType; }
	int  getIndentLength() const         { return indentLength; }
	bool getUseTabLength() const         { return useTabLength; }
	int  getTabLength() const            { return tabLength; }
	// getters - brace modifiers
	bool getAttachNamespace() const      { return attachNamespace; }
	bool getAttachClass() const          { return attachClass; }
	bool getAttachInline() const         { return attachInline; }
	bool getAttachExternC() const        { return attachExternC; }
	bool getAttachClosingWhile() const   { return attachClosingWhile; }
	// getters - indentation
	bool getClassIndent() const          { return classIndent; }
	bool getModifierIndent() const       { return modifierIndent; }
	bool getSwitchIndent() const         { return switchIndent; }
	bool getCaseIndent() const           { return caseIndent; }
	bool getNamespaceIndent() const      { return namespaceIndent; }
	bool getAfterParenIndent() const     { return afterParenIndent; }
	int  getContinuationIndent() const   { return continuationIndent; }
	bool getLabelIndent() const          { return labelIndent; }
	bool getPreprocBlockIndent() const   { return preprocBlockIndent; }
	bool getPreprocDefineIndent() const  { return preprocDefineIndent; }
	bool getPreprocCondIndent() const    { return preprocCondIndent; }
	bool getCol1CommentIndent() const    { return col1CommentIndent; }
	int  getMinConditionalOption() const { return minConditionalOption; }
	int  getMaxContinuationIndent() const { return maxContinuationIndent; }
	// getters - padding
	bool getBreakHeaderBlocks() const    { return breakHeaderBlocks; }
	bool getBreakClosingBlocks() const   { return breakClosingBlocks; }
	bool getPadOperator() const          { return padOperator; }
	bool getPadComma() const             { return padComma; }
	bool getPadParenOutside() const      { return padParenOutside; }
	bool getPadParenInside() const       { return padParenInside; }
	bool getPadFirstParenOut() const     { return padFirstParenOut; }
	bool getPadHeader() const            { return padHeader; }
	bool getUnpadParen() const           { return unpadParen; }
	bool getDeleteEmptyLines() const     { return deleteEmptyLines; }
	bool getFillEmptyLines() const       { return fillEmptyLines; }
	int  getAlignPointer() const         { return alignPointer; }
	int  getAlignReference() const       { return alignReference; }
	// getters - formatting
	bool getBreakClosingBraces() const   { return breakClosingBraces; }
	bool getBreakElseIfs() const         { return breakElseIfs; }
	bool getBreakOneLineHeaders() const  { return breakOneLineHeaders; }
	bool getAddBraces() const            { return addBraces; }
	bool getAddOneLineBraces() const     { return addOneLineBraces; }
	bool getRemoveBraces() const         { return removeBraces; }
	bool getBreakReturnType() const      { return breakReturnType; }
	bool getBreakReturnTypeDecl() const  { return breakReturnTypeDecl; }
	bool getAttachReturnType() const     { return attachReturnType; }
	bool getAttachReturnTypeDecl() const { return attachReturnTypeDecl; }
	bool getBreakOneLineBlocks() const   { return breakOneLineBlocks; }
	bool getBreakOneLineStmts() const    { return breakOneLineStmts; }
	bool getConvertTabs() const          { return convertTabs; }
	bool getCloseTemplates() const       { return closeTemplates; }
	bool getRemoveCommentPrefix() const  { return removeCommentPrefix; }
	int  getMaxCodeLength() const        { return maxCodeLength; }
	bool getBreakAfterLogical() const    { return breakAfterLogical; }
	// getters - other
	bool getPadMethodPrefix() const      { return padMethodPrefix; }
	bool getUnpadMethodPrefix() const    { return unpadMethodPrefix; }
	bool getPadReturnType() const        { return padReturnType; }
	bool getUnpadReturnType() const      { return unpadReturnType; }
	bool getPadParamType() const         { return padParamType; }
	bool getUnpadParamType() const       { return unpadParamType; }
	bool getAlignMethodColon() const     { return alignMethodColon; }
	int  getPadMethodColon() const       { return padMethodColon; }
	// setters - brace style
	void setBraceStyle(BraceStyle value)   { braceStyle = value; }
	// setters - tab
	void setIndentType(IndentType value)     { indentType = value; }
	void setIndentLength(int value)          { indentLength = value; }
	void setUseTabLength(bool state)         { useTabLength = state; }
	void setTabLength(int value)             { tabLength = value; }
	// setters - brace modifiers
	void setAttachNamespace(bool state)      { attachNamespace = state; }
	void setAttachClass(bool state)          { attachClass = state; }
	void setAttachInline(bool state)         { attachInline = state; }
	void setAttachExternC(bool state)        { attachExternC = state; }
	void setAttachClosingWhile(bool state)   { attachClosingWhile = state; }
	// setters - indentation
	void setClassIndent(bool state)          { classIndent = state; }
	void setModifierIndent(bool state)       { modifierIndent = state; }
	void setSwitchIndent(bool state)         { switchIndent = state; }
	void setCaseIndent(bool state)           { caseIndent = state; }
	void setNamespaceIndent(bool state)      { namespaceIndent = state; }
	void setAfterParenIndent(bool state)     { afterParenIndent = state; }
	void setContinuationIndent(int value)    { continuationIndent = value; }
	void setLabelIndent(bool state)          { labelIndent = state; }
	void setPreprocBlockIndent(bool state)   { preprocBlockIndent = state; }
	void setPreprocDefineIndent(bool state)  { preprocDefineIndent = state; }
	void setPreprocCondIndent(bool state)    { preprocCondIndent = state; }
	void setCol1CommentIndent(bool state)    { col1CommentIndent = state; }
	void setMinConditionalOption(MinConditional value)  { minConditionalOption = value; }
	void setMaxContinuationIndent(int value) { maxContinuationIndent = value; }
	// setters - padding
	void setBreakHeaderBlocks(bool state)    { breakHeaderBlocks = state; }
	void setBreakClosingBlocks(bool state)   { breakClosingBlocks = state; }
	void setPadOperator(bool state)          { padOperator = state; }
	void setPadComma(bool state)             { padComma = state; }
	void setPadParenOutside(bool state)      { padParenOutside = state; }
	void setPadParenInside(bool state)       { padParenInside = state; }
	void setPadFirstParenOut(bool state)     { padFirstParenOut = state; }
	void setPadHeader(bool state)            { padHeader = state; }
	void setUnpadParen(bool state)           { unpadParen = state; }
	void setDeleteEmptyLines(bool state)     { deleteEmptyLines = state; }
	void setFillEmptyLines(bool state)       { fillEmptyLines = state; }
	void setAlignPointer(PointerAlign value)     { alignPointer = value; }
	void setAlignReference(ReferenceAlign value) { alignReference = value; }
	// setters - formatting
	void setBreakClosingBraces(bool state)   { breakClosingBraces = state; }
	void setBreakElseIfs(bool state)         { breakElseIfs = state; }
	void setBreakOneLineHeaders(bool state)  { breakOneLineHeaders = state; }
	void setAddBraces(bool state)            { addBraces = state; }
	void setAddOneLineBraces(bool state)     { addOneLineBraces = state; }
	void setRemoveBraces(bool state)         { removeBraces = state; }
	void setBreakReturnType(bool state)      { breakReturnType = state; }
	void setBreakReturnTypeDecl(bool state)  { breakReturnTypeDecl = state; }
	void setAttachReturnType(bool state)     { attachReturnType = state; }
	void setAttachReturnTypeDecl(bool state) { attachReturnTypeDecl = state; }
	void setBreakOneLineBlocks(bool state)   { breakOneLineBlocks = state; }
	void setBreakOneLineStmts(bool state)    { breakOneLineStmts = state; }
	void setConvertTabs(bool state)          { convertTabs = state; }
	void setCloseTemplates(bool state)       { closeTemplates = state; }
	void setRemoveCommentPrefix(bool state)  { removeCommentPrefix = state; }
	void setMaxCodeLength(int value)         { maxCodeLength = value; }
	void setBreakAfterLogical(bool state)    { breakAfterLogical = state; }
	// setters - other
	void setPadMethodPrefix(bool state)      { padMethodPrefix = state; }
	void setUnpadMethodPrefix(bool state)    { unpadMethodPrefix = state; }
	void setPadReturnType(bool state)        { padReturnType = state; }
	void setUnpadReturnType(bool state)      { unpadReturnType = state; }
	void setPadParamType(bool state)         { padParamType = state; }
	void setUnpadParamType(bool state)       { unpadParamType = state; }
	void setAlignMethodColon(bool state)     { alignMethodColon = state; }
	void setPadMethodColon(int value)        { padMethodColon = value; }

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
