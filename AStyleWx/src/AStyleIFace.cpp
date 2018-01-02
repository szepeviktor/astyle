// AStyleIFace.cpp
// Copyright (c) 2017 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

/* ----------------------------------------------------------------------------
TO ADD A NEW OPTION

All options:
Add variable to AStyleIFace.h.
Add variable initialization to AStyleIFace constructor.
Add "getter" method to AStyleIFace.h.
Add "setter" method to AStyleIFace.h.
Add the string constant to Constants.h.
Add the option to "AStyleIFace::GetOptions".

If the option is boolean:
Add new option to "AStyleIFace::SetAStyleOptionBool".

If the option is non-boolean:
Add new option to "AStyleIFace::SetAStyleOption".

Update AStyleDlg.cpp and AStyleDlg.h.
---------------------------------------------------------------------------- */

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include "AStyleIFace.h"

//-----------------------------------------------------------------------------
// AStyleIFace class
//-----------------------------------------------------------------------------

AStyleIFace::AStyleIFace()
// The AStyleIFace constructor sets the variable default values.
{
	// brace style options
	braceStyle = STYLE_NONE;                 // --style=?

	// tabs/spaces options
	indentType           = INDENT_SPACES;      // --indent=?, --indent=force-tab=#
	indentLength         = 4;                  // --indent=?, --force-indent=tab=#
	useTabLength         = false;              // --indent=force-tab-x=#
	tabLength            = 8;                  // --indent=force-tab-x=#

	// brace modifier options
	attachNamespace      = false;              // --attach-namespaces
	attachClass          = false;              // --attach-classes
	attachInline         = false;              // --attach-inlines
	attachExternC        = false;              // --attach-extern-c
	attachClosingWhile   = false;              // --attach-closing-while

	// indentation options
	classIndent          = false;              // --indent-classes
	modifierIndent       = false;              // --indent-modifiers
	switchIndent         = false;              // --indent-switches
	caseIndent           = false;              // --indent-cases
	namespaceIndent      = false;              // --indent-namespaces
	afterParenIndent     = false;              // --indent-after-parens
	continuationIndent   = 1;                  // --continuation-indent=#
	labelIndent          = false;              // --indent-labels
	preprocBlockIndent   = false;              // --indent-preproc-block
	preprocDefineIndent  = false;              // --indent-preproc-define
	preprocCondIndent    = false;              // --indent-preproc-cond
	col1CommentIndent    = false;              // --indent-col1-comments
	maxContinuationIndent = 40;                // --max-continuation-indent=#
	minConditionalOption = MINCOND_TWO;        // --min-conditional-indent=#

	// padding options
	breakHeaderBlocks    = false;              // --break-blocks, --break-blocks=all
	breakClosingBlocks   = false;              // --break-blocks=all
	padOperator          = false;              // --pad=oper
	padComma             = false;              // --pad=comma
	padParenOutside      = false;              // --pad-paren, --pad=paren-out
	padFirstParenOut     = false;              // --pad-first-paren-out
	padParenInside       = false;              // --pad-paren, --pad-paren-in
	padHeader            = false;              // --pad-header
	unpadParen           = false;              // --unpad=paren
	deleteEmptyLines     = false;              // --delete-empty-lines
	fillEmptyLines       = false;              // --fill-empty-lines
	alignPointer         = PTR_ALIGN_NONE;     // --align-pointer= none, type, middle, name
	alignReference       = REF_SAME_AS_PTR;    // --align-reference= none, type, middle, name same as pointer

	// formatting options
	breakClosingBraces   = false;              // -- break-closing-braces
	breakElseIfs         = false;              // --break-elseifs
	breakOneLineHeaders  = false;              // --break-one-line-headers
	addBraces            = false;              // --add-braces
	addOneLineBraces     = false;              // --add-one-line-braces
	removeBraces         = false;              // --remove-braces
	breakReturnType      = false;              // --break-return-type
	breakReturnTypeDecl  = false;              // --break-return-type-decl
	attachReturnType     = false;              // --attach-return-type
	attachReturnTypeDecl = false;              // --attach-return-type-decl
	breakOneLineBlocks   = true;               // --one-line=keep-blocks
	breakOneLineStmts    = true;               // --one-line=keep-statements
	convertTabs          = false;              // --convert-tabs
	closeTemplates       = false;              // --close-templates
	removeCommentPrefix  = false;              // --remove-comment-prefix
	maxCodeLength        = 0;                  // --max-code-length=#
	breakAfterLogical    = false;              // --break-after-logical

	// other options
	padMethodPrefix      = false;              // --pad-method-prefix
	unpadMethodPrefix    = false;              // --unpad-method-prefix
	padReturnType        = false;              // --pad-return-type
	unpadReturnType      = false;              // --unpad-return-type
	padParamType         = false;              // --pad-param-type
	unpadParamType       = false;              // --unpad-param-type
	alignMethodColon     = false;              // --align-method-colon
	padMethodColon  =  COLON_PAD_NO_CHANGE;    // --pad-method-colon

	// save integer default values
	defaultIndentLength         = indentLength;
	defaultTabLength            = tabLength;
	defaultContinuationIndent   = continuationIndent;
	defaultMinConditionalOption = minConditionalOption;
	defaultMaxContinuationIndent = maxContinuationIndent;
	defaultMaxCodeLength        = maxCodeLength;
}

AStyleIFace::~AStyleIFace()
{}

void AStyleIFace::AppendFileModeOption(FileMode fileMode, wxString& options) const
{
	// get the file mode
	wxString mode;
	// NOTE: fileMode == FILEMODE_OBJC is not currently sent
	if (fileMode != FILEMODE_CPP && fileMode != FILEMODE_OBJC)
	{
		if (fileMode == FILEMODE_JAVA)
			mode = MODE_JAVA;
		else if (fileMode == FILEMODE_SHARP)
			mode = MODE_CS;
		else	// force an error message
			mode = wxString::Format("\ninvalid-fileMode=%d", fileMode);
	}
	// append the file mode
	if (mode != wxEmptyString)
	{
		if (options != wxEmptyString)
			options.Append("\n" + mode);
		else
			options.Append(mode);
	}
}

wxString AStyleIFace::GetOptions(bool showShort /*false*/, bool useSeparator /*true*/) const
/* Build a string of options from the current option variables.
 * An option is generated only if the current value is different
 * than the default value.
 * If an option variable is invalid, invalid text is sent to
 * Artistic Style so the private ErrorHandler method will be called.
 * Return a string containing the options for Artistic Style.
*/
{
	wxString options;                     // options to Artistic Style
	options.Alloc(50);
	wxString separator = "\n";       // can be new-line, tab, space, or comma

	// brace style
	if (getBraceStyle() != STYLE_NONE)
	{
		const wxString EQ = "=";
		if (getBraceStyle() == STYLE_ALLMAN)
		{
			if (showShort)
				options.append("A1");
			else
				options.append(STYLE + EQ + ALLMAN);
		}
		else if (getBraceStyle() == STYLE_JAVA)
		{
			if (showShort)
				options.append("A2");
			else
				options.append(STYLE + EQ + JAVA);
		}
		else if (getBraceStyle() == STYLE_KR)
		{
			if (showShort)
				options.append("A3");
			else
				options.append(STYLE + EQ + KandR);
		}
		else if (getBraceStyle() == STYLE_STROUSTRUP)
		{
			if (showShort)
				options.append("A4");
			else
				options.append(STYLE + EQ + STROUSTRUP);
		}
		else if (getBraceStyle() == STYLE_WHITESMITH)
		{
			if (showShort)
				options.append("A5");
			else
				options.append(STYLE + EQ + WHITESMITH);
		}
		else if (getBraceStyle() == STYLE_VTK)
		{
			if (showShort)
				options.append("A15");
			else
				options.append(STYLE + EQ + VTK);
		}
		else if (getBraceStyle() == STYLE_RATLIFF)
		{
			if (showShort)
				options.append("A6");
			else
				options.append(STYLE + EQ + RATLIFF);
		}
		else if (getBraceStyle() == STYLE_GNU)
		{
			if (showShort)
				options.append("A7");
			else
				options.append(STYLE + EQ + GNU);
		}
		else if (getBraceStyle() == STYLE_LINUX)
		{
			if (showShort)
				options.append("A8");
			else
				options.append(STYLE + EQ + LINUXX);
		}
		else if (getBraceStyle() == STYLE_HORSTMANN)
		{
			if (showShort)
				options.append("A9");
			else
				options.append(STYLE + EQ + HORSTMANN);
		}
		else if (getBraceStyle() == STYLE_1TBS)
		{
			if (showShort)
				options.append("A10");
			else
				options.append(STYLE + EQ + oneTBS);
		}
		else if (getBraceStyle() == STYLE_GOOGLE)
		{
			if (showShort)
				options.append("A14");
			else
				options.append(STYLE + EQ + GOOGLE);
		}
		else if (getBraceStyle() == STYLE_MOZILLA)
		{
			if (showShort)
				options.append("A16");
			else
				options.append(STYLE + EQ + MOZILLA);
		}
		else if (getBraceStyle() == STYLE_PICO)
		{
			if (showShort)
				options.append("A11");
			else
				options.append(STYLE + EQ + PICO);
		}
		else if (getBraceStyle() == STYLE_LISP)
		{
			if (showShort)
				options.append("A12");
			else
				options.append(STYLE + EQ + LISP);
		}
		else		// force an error message
			options.append(wxString::Format("invalid-braceStyle=%d", getBraceStyle()));
		if (useSeparator)
			options.append(separator);
	}
	// begin indent check
	if (getIndentType() == INDENT_SPACES)               // space is the default
	{
		// check conditions to use default space setting
		if (getIndentLength() != getDefaultIndentLength())
		{
			if (showShort)
				options.append(wxString::Format("s%d", getIndentLength()));
			else
				options.append(INDENT_OPT_SPACES + wxString::Format("=%d", getIndentLength()));
			if (useSeparator)
				options.append(separator);
		}
	}
	else if (getIndentType() == INDENT_TABS)             // tab is not the default
	{
		// check conditions to use default tab setting
		if (getIndentLength() == getDefaultIndentLength())
		{
			if (showShort)
				options.append("t");
			else
				options.append(INDENT_OPT_TAB);
		}
		else
		{
			if (showShort)
				options.append(wxString::Format("t%d", getIndentLength()));
			else
				options.append(INDENT_OPT_TAB + wxString::Format("=%d", getIndentLength()));
		}
		if (useSeparator)
			options.append(separator);
	}
	else if (getIndentType() == INDENT_FTABS)
	{
		// check conditions to use default force-tab setting
		if (getIndentLength() == getDefaultIndentLength())
		{
			if (!getUseTabLength())
			{
				if (showShort)
					options.append("T");
				else
					options.append(INDENT_OPT_FTAB);
				if (useSeparator)
					options.append(separator);
			}
		}
		else
		{
			if (showShort)
				options.append(wxString::Format("T%d", getIndentLength()));
			else
				options.append(INDENT_OPT_FTAB + wxString::Format("=%d", getIndentLength()));
			if (useSeparator)
				options.append(separator);
		}
		// check conditions to use different tab setting
		if (getUseTabLength())
		{
			if (getTabLength() == getDefaultTabLength())
			{
				if (showShort)
					options.append("xT");
				else
					options.append(INDENT_OPT_FTAB_X);
			}
			else
			{
				if (showShort)
					options.append(wxString::Format("xT%d", getTabLength()));
				else
					options.append(INDENT_OPT_FTAB_X + wxString::Format("=%d", getTabLength()));
			}
			if (useSeparator)
				options.append(separator);
		}
	}
	else	// force an error message
	{
		options.append(wxString::Format("invalid-indentType=%d", getIndentType()));
		if (useSeparator)
			options.append(separator);
	}
	if (getIndentLength() < 2 || getIndentLength() > 20)		// validate indent length
	{
		options.append(wxString::Format("invalid-indentLength=%d",  getIndentLength()));
		if (useSeparator)
			options.append(separator);
	}
	// end indent check
	if (getAttachNamespace())
	{
		if (showShort)
			options.append("xn");
		else
			options.append(ATTACH_NAMESPACES);
		if (useSeparator)
			options.append(separator);
	}
	if (getAttachClass())
	{
		if (showShort)
			options.append("xc");
		else
			options.append(ATTACH_CLASSES);
		if (useSeparator)
			options.append(separator);
	}
	if (getAttachInline())
	{
		if (showShort)
			options.append("xl");
		else
			options.append(ATTACH_INLINES);
		if (useSeparator)
			options.append(separator);
	}
	if (getAttachExternC())
	{
		if (showShort)
			options.append("xk");
		else
			options.append(ATTACH_EXTERN_C);
		if (useSeparator)
			options.append(separator);
	}
	if (getAttachClosingWhile())
	{
		if (showShort)
			options.append("xV");
		else
			options.append(ATTACH_CLOSING_WHILE);
		if (useSeparator)
			options.append(separator);
	}
	if (getClassIndent())
	{
		if (showShort)
			options.append("C");
		else
			options.append(INDENT_CLASSES);
		if (useSeparator)
			options.append(separator);
	}
	if (getModifierIndent())
	{
		if (showShort)
			options.append("xG");
		else
			options.append(INDENT_MODIFIERS);
		if (useSeparator)
			options.append(separator);
	}
	if (getSwitchIndent())
	{
		if (showShort)
			options.append("S");
		else
			options.append(INDENT_SWITCHES);
		if (useSeparator)
			options.append(separator);
	}
	if (getCaseIndent())
	{
		if (showShort)
			options.append("K");
		else
			options.append(INDENT_CASES);
		if (useSeparator)
			options.append(separator);
	}
	if (getNamespaceIndent())
	{
		if (showShort)
			options.append("N");
		else
			options.append(INDENT_NAMESPACES);
		if (useSeparator)
			options.append(separator);
	}
	if (getAfterParenIndent())
	{
		if (showShort)
			options.append("xU");
		else
			options.append(INDENT_AFTER_PARENS);
		if (useSeparator)
			options.append(separator);
	}
	if (getContinuationIndent() != getDefaultContinuationIndent())
	{
		if (getContinuationIndent() >= 0 && getContinuationIndent() <= 4)
		{
			if (showShort)
				options.append(wxString::Format("xt%d", getContinuationIndent()));
			else
				options.append(INDENT_CONTINUATION + wxString::Format("=%d", getContinuationIndent()));
		}
		else
			options.append(wxString::Format("invalid-continuationIndent=%d", getContinuationIndent()));
		if (useSeparator)
			options.append(separator);
	}
	if (getLabelIndent())
	{
		if (showShort)
			options.append("L");
		else
			options.append(INDENT_LABELS);
		if (useSeparator)
			options.append(separator);
	}
	if (getPreprocBlockIndent())
	{
		if (showShort)
			options.append("xW");
		else
			options.append(INDENT_PREPROC_BLOCK);
		if (useSeparator)
			options.append(separator);
	}
	if (getPreprocDefineIndent())
	{
		if (showShort)
			options.append("w");
		else
			options.append(INDENT_PREPROC_DEFINE);
		if (useSeparator)
			options.append(separator);
	}
	if (getPreprocCondIndent())
	{
		if (showShort)
			options.append("xw");
		else
			options.append(INDENT_PREPROC_COND);
		if (useSeparator)
			options.append(separator);
	}
	if (getCol1CommentIndent())
	{
		if (showShort)
			options.append("Y");
		else
			options.append(INDENT_COL1_COMMENTS);
		if (useSeparator)
			options.append(separator);
	}
	if (getMinConditionalOption() != getDefaultMinConditionalOption())
	{
		if (getMinConditionalOption() == MINCOND_ZERO
		        || getMinConditionalOption() == MINCOND_ONE
		        || getMinConditionalOption() == MINCOND_TWO
		        || getMinConditionalOption() == MINCOND_ONEHALF)
		{
			if (showShort)
				options.append(wxString::Format("m%d", getMinConditionalOption()));
			else
				options.append(MIN_CONDITIONAL_INDENT + wxString::Format("=%d", getMinConditionalOption()));
		}
		else
			options.append(wxString::Format("invalid-minConditionalOption=%d", getMinConditionalOption()));
		if (useSeparator)
			options.append(separator);
	}
	if (getMaxContinuationIndent() != getDefaultMaxContinuationIndent())
	{
		if (getMaxContinuationIndent() >= 40 && getMaxContinuationIndent() <= 120)
		{
			if (showShort)
				options.append(wxString::Format("M%d", getMaxContinuationIndent()));
			else
				options.append(MAX_CONTINUATION_INDENT + wxString::Format("=%d", getMaxContinuationIndent()));
		}
		else
			options.append(wxString::Format("invalid-maxContinuationIndent=%d", getMaxContinuationIndent()));
		if (useSeparator)
			options.append(separator);
	}
	// begin break blocks
	if (getBreakHeaderBlocks())
	{
		if (getBreakClosingBlocks())
		{
			if (showShort)
				options.append("F");
			else
				options.append(BREAK_BLOCKS_ALL);
			if (useSeparator)
				options.append(separator);
		}
		else
		{
			if (showShort)
				options.append("f");
			else
				options.append(BREAK_BLOCKS);
			if (useSeparator)
				options.append(separator);
		}
	}
	else if (getBreakClosingBlocks())
	{
		options.append("invalid-breakClosingBlocks=true");
		if (useSeparator)
			options.append(separator);
	}
	// end break blocks
	if (getPadOperator())
	{
		if (showShort)
			options.append("p");
		else
			options.append(PAD_OPER);
		if (useSeparator)
			options.append(separator);
	}
	if (getPadComma())
	{
		if (showShort)
			options.append("xg");
		else
			options.append(PAD_COMMA);
		if (useSeparator)
			options.append(separator);
	}
	// begin pad parens check
	if (getPadParenOutside() && getPadParenInside())
	{
		if (showShort)
			options.append("P");
		else
			options.append(PAD_PAREN);
		if (useSeparator)
			options.append(separator);
	}
	else if (getPadParenOutside())
	{
		if (showShort)
			options.append("d");
		else
			options.append(PAD_PAREN_OUT);
		if (useSeparator)
			options.append(separator);
	}
	else if (getPadParenInside())
	{
		if (showShort)
			options.append("D");
		else
			options.append(PAD_PAREN_IN);
		if (useSeparator)
			options.append(separator);
	}
	// end pad parens check
	if (getPadFirstParenOut())
	{
		if (showShort)
			options.append("xd");
		else
			options.append(PAD_FIRST_PAREN_OUT);
		if (useSeparator)
			options.append(separator);
	}
	if (getPadHeader())
	{
		if (showShort)
			options.append("H");
		else
			options.append(PAD_HEADER);
		if (useSeparator)
			options.append(separator);
	}
	if (getUnpadParen())
	{
		if (showShort)
			options.append("U");
		else
			options.append(UNPAD_PAREN);
		if (useSeparator)
			options.append(separator);
	}
	if (getDeleteEmptyLines())
	{
		if (showShort)
			options.append("xe");
		else
			options.append(DELETE_EMPTY_LINES);
		if (useSeparator)
			options.append(separator);
	}
	if (getFillEmptyLines())
	{
		if (showShort)
			options.append("E");
		else
			options.append(FILL_EMPTY_LINES);
		if (useSeparator)
			options.append(separator);
	}
	if (getAlignPointer() != PTR_ALIGN_NONE)
	{
		if (getAlignPointer() == PTR_ALIGN_TYPE)
		{
			if (showShort)
				options.append("k1");
			else
				options.append(ALIGN_POINTER_TYPE);
		}
		else if (getAlignPointer() == PTR_ALIGN_MIDDLE)
		{
			if (showShort)
				options.append("k2");
			else
				options.append(ALIGN_POINTER_MIDDLE);
		}
		else if (getAlignPointer() == PTR_ALIGN_NAME)
		{
			if (showShort)
				options.append("k3");
			else
				options.append(ALIGN_POINTER_NAME);
		}
		else		// force an error message
			options.append(wxString::Format("invalid-alignPointer=%d", getAlignPointer()));
		if (useSeparator)
			options.append(separator);
	}
	if (getAlignReference() != REF_SAME_AS_PTR)
	{
		if (getAlignReference() == REF_ALIGN_NONE)
		{
			if (showShort)
				options.append("W0");
			else
				options.append(ALIGN_REFERENCE_NONE);
		}
		else if (getAlignReference() == REF_ALIGN_TYPE)
		{
			if (showShort)
				options.append("W1");
			else
				options.append(ALIGN_REFERENCE_TYPE);
		}
		else if (getAlignReference() == REF_ALIGN_MIDDLE)
		{
			if (showShort)
				options.append("W2");
			else
				options.append(ALIGN_REFERENCE_MIDDLE);
		}
		else if (getAlignReference() == REF_ALIGN_NAME)
		{
			if (showShort)
				options.append("W3");
			else
				options.append(ALIGN_REFERENCE_NAME);
		}
		else		// force an error message
			options.append(wxString::Format("invalid-alignReference=%d", getAlignReference()));
		if (useSeparator)
			options.append(separator);
	}
	if (getBreakClosingBraces())
	{
		if (showShort)
			options.append("y");
		else
			options.append(BREAK_CLOSING_BRACES);
		if (useSeparator)
			options.append(separator);
	}
	if (getBreakElseIfs())
	{
		if (showShort)
			options.append("e");
		else
			options.append(BREAK_ELSEIFS);
		if (useSeparator)
			options.append(separator);
	}
	if (getBreakOneLineHeaders())
	{
		if (showShort)
			options.append("xb");
		else
			options.append(BREAK_ONE_LINE_HEADERS);
		if (useSeparator)
			options.append(separator);
	}
	if (getAddBraces())
	{
		if (showShort)
			options.append("j");
		else
			options.append(ADD_BRACES);
		if (useSeparator)
			options.append(separator);
	}
	if (getAddOneLineBraces())
	{
		if (showShort)
			options.append("J");
		else
			options.append(ADD_ONE_LINE_BRACES);
		if (useSeparator)
			options.append(separator);
	}
	if (getRemoveBraces())
	{
		if (showShort)
			options.append("xj");
		else
			options.append(REMOVE_BRACES);
		if (useSeparator)
			options.append(separator);
	}
	if (getBreakReturnType())
	{
		if (showShort)
			options.append("xB");
		else
			options.append(BREAK_RETURN_TYPE);
		if (useSeparator)
			options.append(separator);
	}
	if (getBreakReturnTypeDecl())
	{
		if (showShort)
			options.append("xD");
		else
			options.append(BREAK_RETURN_TYPE_DECL);
		if (useSeparator)
			options.append(separator);
	}
	if (getAttachReturnType())
	{
		if (showShort)
			options.append("xf");
		else
			options.append(ATTACH_RETURN_TYPE);
		if (useSeparator)
			options.append(separator);
	}
	if (getAttachReturnTypeDecl())
	{
		if (showShort)
			options.append("xh");
		else
			options.append(ATTACH_RETURN_TYPE_DECL);
		if (useSeparator)
			options.append(separator);
	}
	if (! getBreakOneLineBlocks())               // default = true
	{
		if (showShort)
			options.append("O");
		else
			options.append(KEEP_ONE_LINE_BLOCKS);
		if (useSeparator)
			options.append(separator);
	}
	if (! getBreakOneLineStmts())                // default = true
	{
		if (showShort)
			options.append("o");
		else
			options.append(KEEP_ONE_LINE_STATEMENTS);
		if (useSeparator)
			options.append(separator);
	}
	if (getConvertTabs())
	{
		if (showShort)
			options.append("c");
		else
			options.append(CONVERT_TABS);
		if (useSeparator)
			options.append(separator);
	}
	if (getCloseTemplates())
	{
		if (showShort)
			options.append("xy");
		else
			options.append(CLOSE_TEMPLATES);
		if (useSeparator)
			options.append(separator);
	}
	if (getRemoveCommentPrefix())
	{
		if (showShort)
			options.append("xp");
		else
			options.append(REMOVE_COMMENT_PREFIX);
		if (useSeparator)
			options.append(separator);
	}
	if (getMaxCodeLength() > 0)
	{
		if (getMaxCodeLength() >= MAX_CODE_LENGTH_MIN && getMaxCodeLength() <= MAX_CODE_LENGTH_MAX)
		{
			if (showShort)
				options.append(wxString::Format("xC%d", getMaxCodeLength()));
			else
				options.append(MAX_CODE_LENGTH + wxString::Format("=%d", getMaxCodeLength()));
		}
		else
			options.append(wxString::Format("invalid-maxCodeLength=%d", getMaxCodeLength()));
		if (useSeparator)
			options.append(separator);
	}
	if (getBreakAfterLogical())
	{
		if (showShort)
			options.append("xL");
		else
			options.append(BREAK_AFTER_LOGICAL);
		if (useSeparator)
			options.append(separator);
	}
	if (getPadMethodPrefix())
	{
		if (showShort)
			options.append("xQ");
		else
			options.append(PAD_METHOD_PREFIX);
		if (useSeparator)
			options.append(separator);
	}
	if (getUnpadMethodPrefix())
	{
		if (showShort)
			options.append("xR");
		else
			options.append(UNPAD_METHOD_PREFIX);
		if (useSeparator)
			options.append(separator);
	}
	if (getPadReturnType())
	{
		if (showShort)
			options.append("xq");
		else
			options.append(PAD_RETURN_TYPE);
		if (useSeparator)
			options.append(separator);
	}
	if (getUnpadReturnType())
	{
		if (showShort)
			options.append("xr");
		else
			options.append(UNPAD_RETURN_TYPE);
		if (useSeparator)
			options.append(separator);
	}
	if (getPadParamType())
	{
		if (showShort)
			options.append("xS");
		else
			options.append(PAD_PARAM_TYPE);
		if (useSeparator)
			options.append(separator);
	}
	if (getUnpadParamType())
	{
		if (showShort)
			options.append("xs");
		else
			options.append(UNPAD_PARAM_TYPE);
		if (useSeparator)
			options.append(separator);
	}
	if (getAlignMethodColon())
	{
		if (showShort)
			options.append("xM");
		else
			options.append(ALIGN_METHOD_COLON);
		if (useSeparator)
			options.append(separator);
	}
	if (getPadMethodColon() != COLON_PAD_NO_CHANGE)
	{
		if (getPadMethodColon() > COLON_PAD_NO_CHANGE && getPadMethodColon() < COLON_PAD_END)
		{
			if (showShort)
				options.append(TranslatePadMethodColonValueShort(getPadMethodColon()));
			else
				options.append(PAD_METHOD_COLON + wxString("=") + TranslatePadMethodColonValue(getPadMethodColon()));
		}
		else
			options.append(wxString::Format("invalid-padMethodColon=%d", getPadMethodColon()));
		if (useSeparator)
			options.append(separator);
	}
	// delete the last separator
	if (options.length() > 0 && options[options.length() - 1] == separator)
		options.erase(options.length() - 1);

	return options;
}

bool AStyleIFace::SetAStyleOption(const wxString& key, const wxString& value)
// Set an astyle option from a config file key (wxString value).
{
	// all values from the config file should be true
	if (value == asTRUE)
		return SetAStyleOptionBool(key, true);
	// check non-boolean options
	if (key == STYLE)
	{
		if (value == ALLMAN)
			braceStyle = STYLE_ALLMAN;
		else if (value == JAVA)
			braceStyle = STYLE_JAVA;
		else if (value == KandR)
			braceStyle = STYLE_KR;
		else if (value == STROUSTRUP)
			braceStyle = STYLE_STROUSTRUP;
		else if (value == WHITESMITH)
			braceStyle = STYLE_WHITESMITH;
		else if (value == VTK)
			braceStyle = STYLE_VTK;
		else if (value == RATLIFF)
			braceStyle = STYLE_RATLIFF;
		else if (value == GNU)
			braceStyle = STYLE_GNU;
		else if (value == LINUXX)
			braceStyle = STYLE_LINUX;
		else if (value == HORSTMANN)
			braceStyle = STYLE_HORSTMANN;
		else if (value == oneTBS)
			braceStyle = STYLE_1TBS;
		else if (value == GOOGLE)
			braceStyle = STYLE_GOOGLE;
		else if (value == MOZILLA)
			braceStyle = STYLE_MOZILLA;
		else if (value == PICO)
			braceStyle = STYLE_PICO;
		else if (value == LISP)
			braceStyle = STYLE_LISP;
		else
			return false;
	}
	else if (key == INDENT_TYPE)
	{
		if (value == INDENT_TYPE_SPACES)
			indentType = INDENT_SPACES;
		else if (value == INDENT_TYPE_TAB)
			indentType = INDENT_TABS;
		else if (value == INDENT_TYPE_FTAB)
			indentType = INDENT_FTABS;
		else
			return false;
	}
	else if (key == INDENT_LENGTH)
	{
		long intValue;
		if (!value.ToLong(&intValue))
			return false;
		if (intValue < 1 || intValue > 20)
			return false;
		indentLength = static_cast<int>(intValue);
	}
	// TAB_LENGTH also sets useTabLength
	else if (key == TAB_LENGTH)
	{
		long intValue;
		if (!value.ToLong(&intValue))
			return false;
		if (intValue < 1 || intValue > 20)
			return false;
		tabLength = static_cast<int>(intValue);
		useTabLength = true;
	}
	else if (key == INDENT_CONTINUATION)
	{
		long intValue;
		if (!value.ToLong(&intValue))
			return false;
		if (intValue < 0 || intValue > 4)
			return false;
		continuationIndent = static_cast<int>(intValue);
	}
	else if (key == MIN_CONDITIONAL_INDENT)
	{
		long intValue;
		if (!value.ToLong(&intValue))
			return false;
		if (intValue < 0 || intValue > 3)
			return false;
		minConditionalOption = static_cast<MinConditional>(intValue);
	}
	else if (key == MAX_CONTINUATION_INDENT)
	{
		long intValue;
		if (!value.ToLong(&intValue))
			return false;
		if (intValue < 40 || intValue > 120)
			return false;
		maxContinuationIndent = static_cast<int>(intValue);
	}
	else if (key == BREAK_BLOCKS)
	{
		breakHeaderBlocks = true;
		if (value == "all")
			breakClosingBlocks = true;
		else if (value != "open")
			return false;
	}
	else if (key == PAD_PAREN)
	{
		if (value == "all")
		{
			padParenOutside = true;
			padParenInside = true;
		}
		else if (value == "out")
		{
			padParenOutside = true;
			padParenInside = false;
		}
		else if (value == "in")
		{
			padParenOutside = false;
			padParenInside = true;
		}
		else
			return false;
	}
	else if (key == ALIGN_POINTER)
	{
		long intValue;
		if (!value.ToLong(&intValue))
			return false;
		if (intValue >=  0 && intValue < PTR_ALIGN_END)
			alignPointer = static_cast<PointerAlign>(intValue);
		else
			return false;
	}
	else if (key == ALIGN_REFERENCE)
	{
		long intValue;
		if (!value.ToLong(&intValue))
			return false;
		if (intValue >=  0 && intValue < REF_ALIGN_END)
			alignReference = static_cast<ReferenceAlign>(intValue);
		else
			return false;
	}
	else if (key == MAX_CODE_LENGTH)
	{
		long intValue;
		if (!value.ToLong(&intValue))
			return false;
		if (intValue < MAX_CODE_LENGTH_MIN || intValue > MAX_CODE_LENGTH_MAX)
			return false;
		maxCodeLength = static_cast<int>(intValue);
	}
	else if (key == PAD_METHOD_COLON)
	{
		if (value != "none"
		        && value != "all"
		        && value != "after"
		        && value != "before")
			return false;
		padMethodColon = TranslatePadMethodColonString(value);
	}
	else
	{
		return false;
	}
	return true;
}

bool AStyleIFace::SetAStyleOptionBool(const wxString& key, bool value)
// Set an astyle boolean option (bool value).
// This private function is accessed from SetAStyleOption();
{
	if (key == USE_TAB_LENGTH)
		useTabLength = value;
	else if (key == ATTACH_NAMESPACES)
		attachNamespace = value;
	else if (key == ATTACH_CLASSES)
		attachClass = value;
	else if (key == ATTACH_INLINES)
		attachInline = value;
	else if (key == ATTACH_EXTERN_C)
		attachExternC = value;
	else if (key == ATTACH_CLOSING_WHILE)
		attachClosingWhile = value;
	else if (key == BREAK_CLOSING_BRACES)
		breakClosingBraces = value;
	else if (key == INDENT_CLASSES)
		classIndent = value;
	else if (key == INDENT_MODIFIERS)
		modifierIndent = value;
	else if (key == INDENT_SWITCHES)
		switchIndent = value;
	else if (key == INDENT_CASES)
		caseIndent = value;
	else if (key == INDENT_NAMESPACES)
		namespaceIndent = value;
	else if (key == INDENT_AFTER_PARENS)
		afterParenIndent = value;
	else if (key == INDENT_LABELS)
		labelIndent = value;
	else if (key == INDENT_PREPROC_BLOCK)
		preprocBlockIndent = value;
	else if (key == INDENT_PREPROC_DEFINE)
		preprocDefineIndent = value;
	else if (key == INDENT_PREPROC_COND)
		preprocCondIndent = value;
	else if (key == INDENT_COL1_COMMENTS)
		col1CommentIndent = value;
	else if (key == BREAK_ELSEIFS)
		breakElseIfs = value;
	else if (key == BREAK_ONE_LINE_HEADERS)
		breakOneLineHeaders = value;
	else if (key == PAD_OPER)
		padOperator = value;
	else if (key == PAD_COMMA)
		padComma = value;
	else if (key == PAD_FIRST_PAREN_OUT)
		padFirstParenOut = value;
	else if (key == PAD_HEADER)
		padHeader = value;
	else if (key == UNPAD_PAREN)
		unpadParen = value;
	else if (key == DELETE_EMPTY_LINES)
		deleteEmptyLines = value;
	else if (key == KEEP_ONE_LINE_STATEMENTS)
		breakOneLineStmts = false;
	else if (key == KEEP_ONE_LINE_BLOCKS)
		breakOneLineBlocks = false;
	else if (key == ADD_BRACES)
		addBraces = value;
	else if (key == ADD_ONE_LINE_BRACES)
		addOneLineBraces = value;
	else if (key == REMOVE_BRACES)
		removeBraces = value;
	else if (key == BREAK_RETURN_TYPE)
		breakReturnType = value;
	else if (key == BREAK_RETURN_TYPE_DECL)
		breakReturnTypeDecl = value;
	else if (key == ATTACH_RETURN_TYPE)
		attachReturnType = value;
	else if (key == ATTACH_RETURN_TYPE_DECL)
		attachReturnTypeDecl = value;
	else if (key == CLOSE_TEMPLATES)
		closeTemplates = value;
	else if (key == REMOVE_COMMENT_PREFIX)
		removeCommentPrefix = value;
	else if (key == CONVERT_TABS)
		convertTabs = value;
	else if (key == FILL_EMPTY_LINES)
		fillEmptyLines = value;
	else if (key == BREAK_AFTER_LOGICAL)
		breakAfterLogical = value;
	else if (key == PAD_METHOD_PREFIX)
		padMethodPrefix = value;
	else if (key == UNPAD_METHOD_PREFIX)
		unpadMethodPrefix = value;
	else if (key == PAD_RETURN_TYPE)
		padReturnType = value;
	else if (key == UNPAD_RETURN_TYPE)
		unpadReturnType = value;
	else if (key == PAD_PARAM_TYPE)
		padParamType = value;
	else if (key == UNPAD_PARAM_TYPE)
		unpadParamType = value;
	else if (key == ALIGN_METHOD_COLON)
		alignMethodColon = value;
	else
	{
		return false;
	}
	return true;
}

int AStyleIFace::TranslatePadMethodColonString(wxString padMethodColonArg) const
// Translate the alpha padMethodColon value to numeric.
{
	int value = COLON_PAD_NO_CHANGE;
	if (padMethodColonArg == "none")
		value = COLON_PAD_NONE;
	else if (padMethodColonArg == "all")
		value = COLON_PAD_ALL;
	else if (padMethodColonArg == "after")
		value = COLON_PAD_AFTER;
	else if (padMethodColonArg == "before")
		value = COLON_PAD_BEFORE;
	return value;
}

wxString AStyleIFace::TranslatePadMethodColonValue(int padMethodColonArg) const
// Translate the numeric padMethodColon value to alpha.
{
	wxString value;
	if (padMethodColonArg == COLON_PAD_NONE)
		value = "none";
	else if (padMethodColonArg == COLON_PAD_ALL)
		value = "all";
	else if (padMethodColonArg == COLON_PAD_AFTER)
		value = "after";
	else if (padMethodColonArg == COLON_PAD_BEFORE)
		value = "before";
	return value;
}

wxString AStyleIFace::TranslatePadMethodColonValueShort(int padMethodColonArg) const
// Translate the numeric padMethodColon value to the short option.
{
	wxString value;
	if (padMethodColonArg == COLON_PAD_NONE)
		value = "xP0";
	else if (padMethodColonArg == COLON_PAD_ALL)
		value = "xP1";
	else if (padMethodColonArg == COLON_PAD_AFTER)
		value = "xP2";
	else if (padMethodColonArg == COLON_PAD_BEFORE)
		value = "xP3";
	return value;
}
