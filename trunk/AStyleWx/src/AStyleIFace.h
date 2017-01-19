// AStyleIFace.h
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.txt describes the conditions under which this software may be distributed.

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
	AStyleIFace();
	virtual ~AStyleIFace();
	void AppendFileModeOption(FileMode fileMode, wxString& options) const;
	wxString GetOptions(bool showShort = false, bool useSeparator = true) const;
	virtual bool SetAStyleOptionFromConfig(const wxString& key, const wxString& value);	// mocked in tests
	int TranslatePadMethodColonString(wxString padMethodColonArg) const;
	wxString TranslatePadMethodColonValue(int padMethodColonArg) const;
	wxString TranslatePadMethodColonValueShort(int padMethodColonArg) const;

public:
	// default getters
	int  getDefaultIndentLength() const          { return defaultIndentLength; }
	int  getDefaultTabLength() const             { return defaultTabLength; }
	int  getDefaultContinuationIndent() const    { return defaultContinuationIndent; }
	MinConditional getDefaultMinConditionalOption() const  { return defaultMinConditionalOption; }
	int  getDefaultMaxInStatementIndent() const  { return defaultMaxInStatementIndent; }
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
	int  getContinuationIndent() const   { return continuationIndent; }
	bool getLabelIndent() const          { return labelIndent; }
	bool getPreprocBlockIndent() const   { return preprocBlockIndent; }
	bool getPreprocDefineIndent() const  { return preprocDefineIndent; }
	bool getPreprocCondIndent() const    { return preprocCondIndent; }
	bool getCol1CommentIndent() const    { return col1CommentIndent; }
	int  getMinConditionalOption() const { return minConditionalOption; }
	int  getMaxInStatementIndent() const { return maxInStatementIndent; }
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
	void setContinuationIndent(int value)    { continuationIndent = value; }
	void setLabelIndent(bool state)          { labelIndent = state; }
	void setPreprocBlockIndent(bool state)   { preprocBlockIndent = state; }
	void setPreprocDefineIndent(bool state)  { preprocDefineIndent = state; }
	void setPreprocCondIndent(bool state)    { preprocCondIndent = state; }
	void setCol1CommentIndent(bool state)    { col1CommentIndent = state; }
	void setMinConditionalOption(MinConditional value)  { minConditionalOption = value; }
	void setMaxInStatementIndent(int value)  { maxInStatementIndent = value; }
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
	bool SetAStyleOptionFromConfig_Bool(const wxString& key, bool value);

private:
	// the initial value is the default value in Artistic Style
	// comments are the command line option used to set the variable

	// brace style option
	BraceStyle braceStyle;              // --style=?

	// tabs/spaces options
	IndentType indentType;              // --indent=*
	int  indentLength;                  // --indent=*
	bool useTabLength;                  // --indent=force-tab-x=#
	int  tabLength;                     // --indent=force-tab-x=#

	// brace modifier options
	bool attachNamespace;               // --attach-namespaces
	bool attachClass;                   // --attach-classes
	bool attachInline;                  // --attach-inlines
	bool attachExternC;                 // --attach-extern-c
	bool attachClosingWhile;            // --attach-closing-while

	// indentation options
	bool classIndent;                   // --indent-classes
	bool modifierIndent;                // --indent-modifiers
	bool switchIndent;                  // --indent-switches
	bool caseIndent;                    // --indent-cases
	bool namespaceIndent;               // --indent-namespaces
	int  continuationIndent;            // --indent-continuation=#
	bool labelIndent;                   // --indent-labels
	bool preprocBlockIndent;            // --indent-preproc-block
	bool preprocDefineIndent;           // --indent-preproc-define
	bool preprocCondIndent;             // --indent-preproc-cond
	bool col1CommentIndent;             // --indent-col1-comments
	MinConditional minConditionalOption;// --min-conditional-indent=#
	int  maxInStatementIndent;          // --max-instatement-indent=#

	// padding options
	bool breakHeaderBlocks;             // --break-blocks, --break-blocks=all
	bool breakClosingBlocks;            // --break-blocks=all
	bool padOperator;                   // --pad-oper
	bool padComma;                      // --pad-comma
	bool padParenOutside;               // --pad-paren, --pad-paren-out
	bool padFirstParenOut;              // --pad-first-paren-out
	bool padParenInside;                // --pad-paren, --pad-paren-in
	bool padHeader;                     // --pad-header
	bool unpadParen;                    // --unpad-paren
	bool deleteEmptyLines;              // --delete-empty-lines
	bool fillEmptyLines;                // --fill-empty-lines
	PointerAlign alignPointer;          // --align-pointer= none, type, middle, name
	ReferenceAlign alignReference;      // --align-reference= none, type, middle, name same as pointer

	// formatting options
	bool breakClosingBraces;            // --break-closing-braces
	bool breakElseIfs;                  // --break-elseifs
	bool breakOneLineHeaders;           // --break-one-line-headers
	bool addBraces;                     // --add-braces
	bool addOneLineBraces;              // --add-one-line-braces
	bool removeBraces;                  // --remove-braces
	bool breakOneLineBlocks;            // --keep-one-line-blocks
	bool breakOneLineStmts;             // --keep-one-line-statements
	bool convertTabs;                   // --convert-tabs
	bool closeTemplates;                // --close-templates
	bool removeCommentPrefix;           // --remove-comment-prefix
	int  maxCodeLength;                 // --max-code-length=#
	bool breakAfterLogical;             // --break-after-logical

	// other options
	bool padMethodPrefix;               // --pad-method-prefix
	bool unpadMethodPrefix;             // --unpad-method-prefix
	bool padReturnType;                 // --pad-return-type
	bool unpadReturnType;               // --unpad-return-type
	bool padParamType;                  // --pad-param-type
	bool unpadParamType;                // --unpad-param-type
	bool alignMethodColon;              // --align-method-colon
	int  padMethodColon;                // --pad-method-colon=#

	// default values for integer variables, saved by constructor
	int defaultIndentLength;            // default indentLength
	int defaultTabLength;               // default tabLength
	int defaultContinuationIndent;      // default continuationIndent
	MinConditional defaultMinConditionalOption;    // default minConditionalIndent
	int defaultMaxInStatementIndent;    // default maxInStatementIndent
	int defaultMaxCodeLength;           // default maxCodeLength
};  // class AStyleIFace

#endif      // closes ASTYLE_IFACE_H
