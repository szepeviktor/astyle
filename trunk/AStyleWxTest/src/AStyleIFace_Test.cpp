// AStyleIFace_Test.cpp
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.txt describes the conditions under which this software may be distributed.

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleIFace.h"
#include "gtest/gtest.h"

/* ----------------------------------------------------------------------------
TO ADD A NEW OPTION
Add new test function to "AStyleIFace_*Options, GetOptions_".
Add new test function to "AStyleIFace_*Short, GetOptions_".
Add new test function to "AStyleIFace_Config, SetAStyleOptionFromConfig_".
All boolean functions for the above are added to "SetAStyleOptionFromConfig_Boolean".
---------------------------------------------------------------------------- */

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {
//
//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Bracket Style Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_StyleOptions, GetOptions_StylesAll)
// Test AStyleIFace::GetOptions for bracket style options
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the options
	const wxString STYLE_EQ = "style=";
	astyle.setBraceStyle(STYLE_NONE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setBraceStyle(STYLE_ALLMAN);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + ALLMAN);
	astyle.setBraceStyle(STYLE_JAVA);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + JAVA);
	astyle.setBraceStyle(STYLE_KR);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + KandR);
	astyle.setBraceStyle(STYLE_STROUSTRUP);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + STROUSTRUP);
	astyle.setBraceStyle(STYLE_WHITESMITH);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + WHITESMITH);
	astyle.setBraceStyle(STYLE_BANNER);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + BANNER);
	astyle.setBraceStyle(STYLE_GNU);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + GNU);
	astyle.setBraceStyle(STYLE_LINUX);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + LINUXX);
	astyle.setBraceStyle(STYLE_HORSTMANN);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + HORSTMANN);
	astyle.setBraceStyle(STYLE_1TBS);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + oneTBS);
	astyle.setBraceStyle(STYLE_GOOGLE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + GOOGLE);
	astyle.setBraceStyle(STYLE_MOZILLA);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + MOZILLA);
	astyle.setBraceStyle(STYLE_PICO);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + PICO);
	astyle.setBraceStyle(STYLE_LISP);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + LISP);
	astyle.setBraceStyle(static_cast<BraceStyle>(99));
	options = astyle.GetOptions();
	EXPECT_TRUE(options == "invalid-braceStyle=99");
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Tab Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_TabOptions, GetOptions_IndentSpaces)
// Test AStyleIFace::GetOptions indent with spaces
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// there is no indent=spaces returned
	astyle.setIndentType(INDENT_SPACES);
	astyle.setIndentLength(4);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setIndentLength(2);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_SPACES "=2");
	astyle.setIndentLength(20);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_SPACES "=20");
}

TEST(AStyleIFace_TabOptions, GetOptions_IndentTabs)
// Test AStyleIFace::GetOptions indent with tabs
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test indent with tabs
	astyle.setIndentType(INDENT_TABS);
	astyle.setIndentLength(4);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_TAB);
	astyle.setIndentLength(2);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_TAB "=2");
	astyle.setIndentLength(20);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_TAB "=20");
}

TEST(AStyleIFace_TabOptions, GetOptions_IndentForceTabs)
// Test AStyleIFace::GetOptions indent with force tabs
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test indent with force tabs
	astyle.setIndentType(INDENT_FTABS);
	astyle.setIndentLength(4);
	astyle.setUseTabLength(false);
	astyle.setTabLength(8);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_FTAB);
	astyle.setIndentLength(2);
	astyle.setUseTabLength(false);
	astyle.setTabLength(4);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_FTAB "=2");
	astyle.setIndentLength(20);
	astyle.setUseTabLength(false);
	astyle.setTabLength(10);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_FTAB "=20");
	// test indent with force tabs and tab-length
	astyle.setIndentType(INDENT_FTABS);
	astyle.setIndentLength(4);
	astyle.setUseTabLength(true);
	astyle.setTabLength(8);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_FTAB_X);
	astyle.setIndentLength(4);
	astyle.setUseTabLength(true);
	astyle.setTabLength(6);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_FTAB_X "=6");
	astyle.setIndentLength(3);
	astyle.setUseTabLength(true);
	astyle.setTabLength(6);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_FTAB "=3\n" INDENT_OPT_FTAB_X "=6");
}

TEST(AStyleIFace_TabOptions, GetOptions_IndentInvalid)
// Test AStyleIFace::GetOptions invalid options
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test invalid indent type
	astyle.setIndentType(static_cast<IndentType>(9));
	astyle.setIndentLength(4);
	options = astyle.GetOptions();
	EXPECT_STREQ("invalid-indentType=9", options);

	// test invalid indent length
	// the options will also have indent=spaces=?
	astyle.setIndentType(INDENT_SPACES);
	astyle.setIndentLength(1);
	options = astyle.GetOptions();
	EXPECT_TRUE(options.Find("invalid-indentLength=1") != wxNOT_FOUND);
	astyle.setIndentLength(21);
	options = astyle.GetOptions();
	EXPECT_TRUE(options.Find("invalid-indentLength=21") != wxNOT_FOUND);
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Bracket Modifier Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_ModifierOptions, GetOptions_AttachNamespace)
// Test AStyleIFace::GetOptions attachNamespace option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setAttachNamespace(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAttachNamespace(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ATTACH_NAMESPACES);
}

TEST(AStyleIFace_ModifierOptions, GetOptions_AttachClass)
// Test AStyleIFace::GetOptions attachClass option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setAttachClass(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAttachClass(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ATTACH_CLASSES);
}

TEST(AStyleIFace_ModifierOptions, GetOptions_AttachInline)
// Test AStyleIFace::GetOptions attachInline option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setAttachInline(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAttachInline(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ATTACH_INLINES);
}

TEST(AStyleIFace_ModifierOptions, GetOptions_AttachExternC)
// Test AStyleIFace::GetOptions attachExternC option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setAttachExternC(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAttachExternC(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ATTACH_EXTERN_C);
}

TEST(AStyleIFace_ModifierOptions, GetOptions_AttachClosingWhile)
// Test AStyleIFace::GetOptions attachExternC option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setAttachClosingWhile(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAttachClosingWhile(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ATTACH_CLOSING_WHILE);
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Indentation Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_IndentOptions, GetOptions_CaseIndent)
// Test AStyleIFace::GetOptions caseIndent option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setCaseIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setCaseIndent(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == INDENT_CASES);
}

TEST(AStyleIFace_IndentOptions, GetOptions_ClassIndent)
// Test AStyleIFace::GetOptions classIndent option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setClassIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setClassIndent(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == INDENT_CLASSES);
}

TEST(AStyleIFace_IndentOptions, GetOptions_Col1CommentIndent)
// Test AStyleIFace::GetOptions col1CommentIndent option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setCol1CommentIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setCol1CommentIndent(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == INDENT_COL1_COMMENTS);
}

TEST(AStyleIFace_IndentOptions, GetOptions_ContinuationIndent)
// Test AStyleIFace::GetOptions continuationIndent option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setContinuationIndent(1);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setContinuationIndent(2);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_CONTINUATION "=2");

	// test invalid min conditional option
	astyle.setContinuationIndent(-1);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, "invalid-continuationIndent=-1");
	astyle.setContinuationIndent(5);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, "invalid-continuationIndent=5");
}

TEST(AStyleIFace_IndentOptions, GetOptions_LabelIndent)
// Test AStyleIFace::GetOptions labelIndent option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setLabelIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setLabelIndent(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == INDENT_LABELS);
}

TEST(AStyleIFace_IndentOptions, GetOptions_MaxInStatement)
// Test AStyleIFace::GetOptions maxInStatementIndent option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setMaxInStatementIndent(40);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setMaxInStatementIndent(50);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, MAX_INSTATEMENT_INDENT "=50");
	// test invalid max instatement indent
	astyle.setMaxInStatementIndent(39);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, "invalid-maxInStatementIndent=39");
	astyle.setMaxInStatementIndent(121);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, "invalid-maxInStatementIndent=121");
}

TEST(AStyleIFace_IndentOptions, GetOptions_MinConditional)
// Test AStyleIFace::GetOptions minConditionalOption option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setMinConditionalOption(MINCOND_ZERO);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, MIN_CONDITIONAL_INDENT "=0");
	astyle.setMinConditionalOption(MINCOND_ONE);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, MIN_CONDITIONAL_INDENT "=1");
	astyle.setMinConditionalOption(MINCOND_TWO);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setMinConditionalOption(MINCOND_ONEHALF);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, MIN_CONDITIONAL_INDENT "=3");

	// test invalid min conditional option
	astyle.setMinConditionalOption(static_cast<MinConditional>(-1));
	options = astyle.GetOptions();
	EXPECT_STREQ(options, "invalid-minConditionalOption=-1");
	astyle.setMinConditionalOption(static_cast<MinConditional>(9));
	options = astyle.GetOptions();
	EXPECT_STREQ(options, "invalid-minConditionalOption=9");
}

TEST(AStyleIFace_IndentOptions, GetOptions_ModifierIndent)
// Test AStyleIFace::GetOptions modifierIndent option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setModifierIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setModifierIndent(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == INDENT_MODIFIERS);
}

TEST(AStyleIFace_IndentOptions, GetOptions_NamespaceIndent)
// Test AStyleIFace::GetOptions namespaceIndent option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setNamespaceIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setNamespaceIndent(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == INDENT_NAMESPACES);
}

TEST(AStyleIFace_IndentOptions, GetOptions_PreprocBlockIndent)
// Test AStyleIFace::GetOptions preprocBlockIndent option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPreprocBlockIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPreprocBlockIndent(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == INDENT_PREPROC_BLOCK);
}

TEST(AStyleIFace_IndentOptions, GetOptions_PreprocCondIndent)
// Test AStyleIFace::GetOptions preprocCondIndent option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPreprocCondIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPreprocCondIndent(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == INDENT_PREPROC_COND);
}

TEST(AStyleIFace_IndentOptions, GetOptions_PreprocDefineIndent)
// Test AStyleIFace::GetOptions preprocDefineIndent option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPreprocDefineIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPreprocDefineIndent(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == INDENT_PREPROC_DEFINE);
}

TEST(AStyleIFace_IndentOptions, GetOptions_SwitchIndent)
// Test AStyleIFace::GetOptions switchIndent option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setSwitchIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setSwitchIndent(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == INDENT_SWITCHES);
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Padding Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_PadOptions, GetOptions_AlignPointer)
// Test GetOptions alignPointer options
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the options
	astyle.setAlignPointer(PTR_ALIGN_NONE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAlignPointer(PTR_ALIGN_TYPE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ALIGN_POINTER_TYPE);
	astyle.setAlignPointer(PTR_ALIGN_MIDDLE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ALIGN_POINTER_MIDDLE);
	astyle.setAlignPointer(PTR_ALIGN_NAME);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ALIGN_POINTER_NAME);
	astyle.setAlignPointer(static_cast<PointerAlign>(99));
	options = astyle.GetOptions();
	EXPECT_TRUE(options == "invalid-alignPointer=99");
}

TEST(AStyleIFace_PadOptions, GetOptions_AlignReference)
// Test GetOptions alignReference options
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the options
	astyle.setAlignReference(REF_ALIGN_NONE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ALIGN_REFERENCE_NONE);
	astyle.setAlignReference(REF_ALIGN_TYPE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ALIGN_REFERENCE_TYPE);
	astyle.setAlignReference(REF_ALIGN_MIDDLE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ALIGN_REFERENCE_MIDDLE);
	astyle.setAlignReference(REF_ALIGN_NAME);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ALIGN_REFERENCE_NAME);
	astyle.setAlignReference(static_cast<ReferenceAlign>(99));
	options = astyle.GetOptions();
	EXPECT_TRUE(options == "invalid-alignReference=99");
}

TEST(AStyleIFace_PadOptions, GetOptions_BreakBlocks)
// Test AStyleIFace::GetOptions breakBlocks options
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the options
	astyle.setBreakHeaderBlocks(false);
	astyle.setBreakClosingBlocks(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	// break-blocks
	astyle.setBreakHeaderBlocks(true);
	astyle.setBreakClosingBlocks(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == BREAK_BLOCKS);
	// break-blocks=all
	astyle.setBreakHeaderBlocks(true);
	astyle.setBreakClosingBlocks(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == BREAK_BLOCKS_ALL);
	// invalid
	astyle.setBreakHeaderBlocks(false);
	astyle.setBreakClosingBlocks(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == "invalid-breakClosingBlocks=true");
}

TEST(AStyleIFace_PadOptions, GetOptions_DeleteEmptyLines)
// Test AStyleIFace::GetOptions deleteEmptyLines option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setDeleteEmptyLines(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setDeleteEmptyLines(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == DELETE_EMPTY_LINES);
}

TEST(AStyleIFace_PadOptions, GetOptions_FillEmptyLines)
// Test AStyleIFace::GetOptions fillEmptyLines option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setFillEmptyLines(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setFillEmptyLines(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == FILL_EMPTY_LINES);
}

TEST(AStyleIFace_PadOptions, GetOptions_PadComma)
// Test AStyleIFace::GetOptions padComma option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPadComma(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPadComma(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == PAD_COMMA);
}

TEST(AStyleIFace_PadOptions, GetOptions_PadFirstParenOut)
// Test AStyleIFace::GetOptions padFirstParenOut option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPadFirstParenOut(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPadFirstParenOut(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == PAD_FIRST_PAREN_OUT);
}

TEST(AStyleIFace_PadOptions, GetOptions_PadHeader)
// Test AStyleIFace::GetOptions padHeader option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPadHeader(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPadHeader(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == PAD_HEADER);
}

TEST(AStyleIFace_PadOptions, GetOptions_PadOperator)
// Test AStyleIFace::GetOptions padOperator option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPadOperator(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPadOperator(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == PAD_OPER);
}

TEST(AStyleIFace_PadOptions, GetOptions_PadParen)
// Test AStyleIFace::GetOptions padParen options
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the options
	astyle.setPadParenOutside(true);
	astyle.setPadParenInside(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == PAD_PAREN);
	astyle.setPadParenOutside(true);
	astyle.setPadParenInside(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == PAD_PAREN_OUT);
	astyle.setPadParenOutside(false);
	astyle.setPadParenInside(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == PAD_PAREN_IN);
}

TEST(AStyleIFace_PadOptions, GetOptions_UnpadParen)
// Test AStyleIFace::GetOptions unpadParen option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setUnpadParen(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setUnpadParen(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == UNPAD_PAREN);
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Formatting Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_FormatOptions, GetOptions_AddBrackets)
// Test AStyleIFace::GetOptions addBrackets option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setAddBraces(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAddBraces(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ADD_BRACES);
}

TEST(AStyleIFace_FormatOptions, GetOptions_AddOneLineBrackets)
// Test AStyleIFace::GetOptions addOneLineBrackets option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setAddOneLineBraces(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAddOneLineBraces(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ADD_ONE_LINE_BRACES);
}

TEST(AStyleIFace_FormatOptions, GetOptions_BreakAfterLogical)
// Test AStyleIFace::GetOptions breakAfterLogical option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setBreakAfterLogical(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setBreakAfterLogical(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == BREAK_AFTER_LOGICAL);
}

TEST(AStyleIFace_FormatOptions, GetOptions_BreakCloseBrackets)
// Test AStyleIFace::GetOptions breakCloseBrackets option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setBreakClosingBraces(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setBreakClosingBraces(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == BREAK_CLOSING_BRACES);
}

TEST(AStyleIFace_FormatOptions, GetOptions_BreakElseIfs)
// Test AStyleIFace::GetOptions breakElseIfs option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setBreakElseIfs(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setBreakElseIfs(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == BREAK_ELSEIFS);
}

TEST(AStyleIFace_FormatOptions, GetOptions_BreakOneLineHeaders)
// Test AStyleIFace::GetOptions breakOneLineHeaders option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setBreakOneLineHeaders(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setBreakOneLineHeaders(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == BREAK_ONE_LINE_HEADERS);
}

TEST(AStyleIFace_FormatOptions, GetOptions_CloseTemplates)
// Test AStyleIFace::GetOptions closeTemplates option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setCloseTemplates(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setCloseTemplates(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == CLOSE_TEMPLATES);
}

TEST(AStyleIFace_FormatOptions, GetOptions_ConvertTabs)
// Test AStyleIFace::GetOptions convertTabs option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setConvertTabs(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setConvertTabs(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == CONVERT_TABS);
}

TEST(AStyleIFace_FormatOptions, GetOptions_KeepOneLineBlocks)
// Test AStyleIFace::GetOptions breakOneLineBlocks option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	// NOTE: the option is TRUE by default
	astyle.setBreakOneLineBlocks(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setBreakOneLineBlocks(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == KEEP_ONE_LINE_BLOCKS);
}

TEST(AStyleIFace_FormatOptions, GetOptions_KeepOneLineStatements)
// Test AStyleIFace::GetOptions breakOneLineStmts option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	// NOTE: the option is TRUE by default
	astyle.setBreakOneLineStmts(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setBreakOneLineStmts(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == KEEP_ONE_LINE_STATEMENTS);
}

TEST(AStyleIFace_IndentOptions, GetOptions_MaxCodeLength)
// Test AStyleIFace::GetOptions maxCodeLength option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setMaxCodeLength(-1);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setMaxCodeLength(MAX_CODE_LENGTH_MIN);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, MAX_CODE_LENGTH "=50");
	astyle.setMaxCodeLength(MAX_CODE_LENGTH_MAX);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, MAX_CODE_LENGTH "=200");
	// test invalid max code length
	astyle.setMaxCodeLength(49);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == "invalid-maxCodeLength=49");
	astyle.setMaxCodeLength(201);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == "invalid-maxCodeLength=201");
}

TEST(AStyleIFace_FormatOptions, GetOptions_RemoveBrackets)
// Test AStyleIFace::GetOptions removeBrackets option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setRemoveBraces(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setRemoveBraces(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == REMOVE_BRACES);
}

TEST(AStyleIFace_FormatOptions, GetOptions_RemoveCommentPrefix)
// Test AStyleIFace::GetOptions removeCommentPrefix option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setRemoveCommentPrefix(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setRemoveCommentPrefix(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == REMOVE_COMMENT_PREFIX);
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Other Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_OtherOptions, GetOptions_PadMethodPrefix)
// Test AStyleIFace::GetOptions padMethodPrefix option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPadMethodPrefix(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPadMethodPrefix(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == PAD_METHOD_PREFIX);
}

TEST(AStyleIFace_OtherOptions, GetOptions_UnpadMethodPrefix)
// Test AStyleIFace::GetOptions unpadMethodPrefix option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setUnpadMethodPrefix(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setUnpadMethodPrefix(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == UNPAD_METHOD_PREFIX);
}

TEST(AStyleIFace_OtherOptions, GetOptions_PadReturnType)
// Test AStyleIFace::GetOptions padReturnType option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPadReturnType(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPadReturnType(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == PAD_RETURN_TYPE);
}

TEST(AStyleIFace_OtherOptions, GetOptions_UnpadReturnType)
// Test AStyleIFace::GetOptions unpadReturnType option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setUnpadReturnType(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setUnpadReturnType(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == UNPAD_RETURN_TYPE);
}

TEST(AStyleIFace_OtherOptions, GetOptions_AlignMethodColon)
// Test AStyleIFace::GetOptions alignMethodColon option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setAlignMethodColon(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAlignMethodColon(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ALIGN_METHOD_COLON);
}

TEST(AStyleIFace_OtherOptions, GetOptions_PadMethodColon)
// Test AStyleIFace::GetOptions adMethodColon option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPadMethodColon(COLON_PAD_NONE);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, PAD_METHOD_COLON "=none");
	astyle.setPadMethodColon(COLON_PAD_ALL);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, PAD_METHOD_COLON "=all");
	astyle.setPadMethodColon(COLON_PAD_AFTER);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, PAD_METHOD_COLON "=after");
	astyle.setPadMethodColon(COLON_PAD_BEFORE);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, PAD_METHOD_COLON "=before");

	// test invalid pad method colon
	astyle.setPadMethodColon(COLON_PAD_NO_CHANGE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPadMethodColon(-1);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == "invalid-padMethodColon=-1");
	astyle.setPadMethodColon(COLON_PAD_END);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxString::Format("invalid-padMethodColon=%d", COLON_PAD_END));
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Bracket Style Short Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_StyleShort, GetOptions_All)
// Test AStyleIFace::GetOptions for style short options
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the options
	const wxString STYLE_EQ = "style=";
	astyle.setBraceStyle(STYLE_NONE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setBraceStyle(STYLE_ALLMAN);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A1") << (STYLE_EQ + ALLMAN);
	astyle.setBraceStyle(STYLE_JAVA);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A2") << (STYLE_EQ + JAVA);
	astyle.setBraceStyle(STYLE_KR);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A3") << (STYLE_EQ + KandR);
	astyle.setBraceStyle(STYLE_STROUSTRUP);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A4") << (STYLE_EQ + STROUSTRUP);
	astyle.setBraceStyle(STYLE_WHITESMITH);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A5") << (STYLE_EQ + WHITESMITH);
	astyle.setBraceStyle(STYLE_BANNER);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A6") << (STYLE_EQ + BANNER);
	astyle.setBraceStyle(STYLE_GNU);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A7") << (STYLE_EQ + GNU);
	astyle.setBraceStyle(STYLE_LINUX);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A8") << (STYLE_EQ + LINUXX);
	astyle.setBraceStyle(STYLE_HORSTMANN);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A9") << (STYLE_EQ + HORSTMANN);
	astyle.setBraceStyle(STYLE_1TBS);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A10") << (STYLE_EQ + oneTBS);
	astyle.setBraceStyle(STYLE_GOOGLE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A14") << (STYLE_EQ + GOOGLE);
	astyle.setBraceStyle(STYLE_MOZILLA);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A16") << (STYLE_EQ + MOZILLA);
	astyle.setBraceStyle(STYLE_PICO);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A11") << (STYLE_EQ + PICO);
	astyle.setBraceStyle(STYLE_LISP);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A12") << (STYLE_EQ + LISP);
	astyle.setBraceStyle(static_cast<BraceStyle>(99));
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "invalid-braceStyle=99");
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Tab Options Short Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_TabShort, GetOptions_IndentSpaces)
// Test AStyleIFace::GetOptions indent with spaces short options
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test indent with spaces
	// there is no indent=spaces returned
	astyle.setIndentType(INDENT_SPACES);
	astyle.setIndentLength(4);
	options = astyle.GetOptions(true);
	EXPECT_STREQ(wxEmptyString, options);
	astyle.setIndentLength(2);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("s2", options);
	astyle.setIndentLength(20);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("s20", options);
}

TEST(AStyleIFace_TabShort, GetOptions_IndentTabs)
// Test AStyleIFace::GetOptions indent with tabs short options
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test indent with tabs
	astyle.setIndentType(INDENT_TABS);
	astyle.setIndentLength(4);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("t", options);
	astyle.setIndentLength(2);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("t2", options);
	astyle.setIndentLength(20);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("t20", options);
}

TEST(AStyleIFace_TabShort, GetOptions_IndentForceTabs)
// Test AStyleIFace::GetOptions indent with force tabs short options
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test indent with force tabs
	astyle.setIndentType(INDENT_FTABS);
	astyle.setIndentLength(4);
	astyle.setUseTabLength(false);
	astyle.setTabLength(8);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("T", options) << INDENT_OPT_FTAB;
	astyle.setIndentLength(2);
	astyle.setUseTabLength(false);
	astyle.setTabLength(4);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("T2", options) << INDENT_OPT_FTAB;
	astyle.setIndentLength(20);
	astyle.setUseTabLength(false);
	astyle.setTabLength(10);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("T20", options) << INDENT_OPT_FTAB;
	// test indent with force tabs and tab-length
	astyle.setIndentType(INDENT_FTABS);
	astyle.setIndentLength(4);
	astyle.setUseTabLength(true);
	astyle.setTabLength(8);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("xT", options) << INDENT_OPT_FTAB;
	astyle.setIndentLength(4);
	astyle.setUseTabLength(true);
	astyle.setTabLength(6);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("xT6", options) << INDENT_OPT_FTAB;
	astyle.setIndentLength(3);
	astyle.setUseTabLength(true);
	astyle.setTabLength(6);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("T3\nxT6", options) << INDENT_OPT_FTAB;
}

TEST(AStyleIFace_TabShort, GetOptions_IndentInvalid)
// Test AStyleIFace::GetOptions invalid short options
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test invalid indent type
	astyle.setIndentType(static_cast<IndentType>(9));
	astyle.setIndentLength(4);
	options = astyle.GetOptions();
	EXPECT_STREQ("invalid-indentType=9", options);

	// test invalid indent length
	// the options will also have indent=spaces=?
	astyle.setIndentType(INDENT_SPACES);
	astyle.setIndentLength(1);
	options = astyle.GetOptions();
	EXPECT_TRUE(options.Find("invalid-indentLength=1") != wxNOT_FOUND);
	astyle.setIndentLength(21);
	options = astyle.GetOptions();
	EXPECT_TRUE(options.Find("invalid-indentLength=21") != wxNOT_FOUND);
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Bracket Modifier Short Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_ModifierShort, GetOptions_AttachNamespace)
// Test AStyleIFace::GetOptions attachNamespace short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setAttachNamespace(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAttachNamespace(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xn");
}

TEST(AStyleIFace_ModifierShort, GetOptions_AttachClass)
// Test AStyleIFace::GetOptions attachClass short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setAttachClass(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAttachClass(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xc");
}

TEST(AStyleIFace_ModifierShort, GetOptions_AttachInline)
// Test AStyleIFace::GetOptions attachInline short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setAttachInline(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAttachInline(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xi");
}

TEST(AStyleIFace_ModifierShort, GetOptions_AttachExternC)
// Test AStyleIFace::GetOptions attachExternC short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setAttachExternC(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAttachExternC(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xk");
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Indentation Short Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_IndentShort, GetOptions_CaseIndent)
// Test AStyleIFace::GetOptions caseIndent short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setCaseIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setCaseIndent(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "K");
}

TEST(AStyleIFace_IndentShort, GetOptions_ClassIndent)
// Test AStyleIFace::GetOptions classIndent short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setClassIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setClassIndent(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "C");
}

TEST(AStyleIFace_IndentShort, GetOptions_Col1CommentIndent)
// Test AStyleIFace::GetOptions col1CommentIndent short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setCol1CommentIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setCol1CommentIndent(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "Y");
}

TEST(AStyleIFace_IndentShort, GetOptions_ContinuationIndent)
// Test AStyleIFace::GetOptions continuationIndent short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setContinuationIndent(1);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setContinuationIndent(2);
	options = astyle.GetOptions(true);
	EXPECT_STREQ(options, "xt2");

	// test invalid min conditional option
	astyle.setContinuationIndent(-1);
	options = astyle.GetOptions(true);
	EXPECT_STREQ(options, "invalid-continuationIndent=-1");
	astyle.setContinuationIndent(5);
	options = astyle.GetOptions(true);
	EXPECT_STREQ(options, "invalid-continuationIndent=5");
}

TEST(AStyleIFace_IndentShort, GetOptions_LabelIndent)
// Test AStyleIFace::GetOptions labelIndent short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setLabelIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setLabelIndent(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "L");
}

TEST(AStyleIFace_IndentShort, GetOptions_MaxInStatement)
// Test AStyleIFace::GetOptions maxInStatementIndent short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setMaxInStatementIndent(40);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setMaxInStatementIndent(50);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "M50");
	// test invalid max instatement indent
	astyle.setMaxInStatementIndent(39);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "invalid-maxInStatementIndent=39");
	astyle.setMaxInStatementIndent(121);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "invalid-maxInStatementIndent=121");
}

TEST(AStyleIFace_IndentShort, GetOptions_MinConditional)
// Test AStyleIFace::GetOptions minConditionalOption short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setMinConditionalOption(MINCOND_ZERO);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "m0");
	astyle.setMinConditionalOption(MINCOND_ONE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "m1");
	astyle.setMinConditionalOption(MINCOND_TWO);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setMinConditionalOption(MINCOND_ONEHALF);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "m3");

	// test invalid min conditional option
	astyle.setMinConditionalOption(static_cast<MinConditional>(-1));
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "invalid-minConditionalOption=-1");
	astyle.setMinConditionalOption(static_cast<MinConditional>(9));
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "invalid-minConditionalOption=9");
}

TEST(AStyleIFace_IndentShort, GetOptions_ModifierIndent)
// Test AStyleIFace::GetOptions modifierIndent short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setModifierIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setModifierIndent(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xG");
}

TEST(AStyleIFace_IndentShort, GetOptions_NamespaceIndent)
// Test AStyleIFace::GetOptions namespaceIndent short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setNamespaceIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setNamespaceIndent(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "N");
}

TEST(AStyleIFace_IndentShort, GetOptions_PreprocBlockIndent)
// Test AStyleIFace::GetOptions preprocBlockIndent short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPreprocBlockIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPreprocBlockIndent(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xW");
}

TEST(AStyleIFace_IndentShort, GetOptions_PreprocCondIndent)
// Test AStyleIFace::GetOptions preprocCondIndent short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPreprocCondIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPreprocCondIndent(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xw");
}

TEST(AStyleIFace_IndentShort, GetOptions_PreprocDefineIndent)
// Test AStyleIFace::GetOptions preprocDefineIndent short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPreprocDefineIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPreprocDefineIndent(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "w");
}

TEST(AStyleIFace_IndentShort, GetOptions_SwitchIndent)
// Test AStyleIFace::GetOptions switchIndent short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setSwitchIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setSwitchIndent(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "S");
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Padding Short Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_PadShort, GetOptions_AlignPointer)
// Test GetOptions alignPointer short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the options
	astyle.setAlignPointer(PTR_ALIGN_NONE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAlignPointer(PTR_ALIGN_TYPE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "k1");
	astyle.setAlignPointer(PTR_ALIGN_MIDDLE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "k2");
	astyle.setAlignPointer(PTR_ALIGN_NAME);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "k3");
	astyle.setAlignPointer(static_cast<PointerAlign>(99));
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "invalid-alignPointer=99");
}

TEST(AStyleIFace_PadShort, GetOptions_AlignReference)
// Test GetOptions alignReference short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the options
	astyle.setAlignReference(REF_ALIGN_NONE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "W0");
	astyle.setAlignReference(REF_ALIGN_TYPE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "W1");
	astyle.setAlignReference(REF_ALIGN_MIDDLE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "W2");
	astyle.setAlignReference(REF_ALIGN_NAME);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "W3");
	astyle.setAlignReference(static_cast<ReferenceAlign>(99));
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "invalid-alignReference=99");
}

TEST(AStyleIFace_PadShort, GetOptions_BreakBlocks)
// Test AStyleIFace::GetOptions breakBlocks short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the options
	astyle.setBreakHeaderBlocks(false);
	astyle.setBreakClosingBlocks(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	// break-blocks
	astyle.setBreakHeaderBlocks(true);
	astyle.setBreakClosingBlocks(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "f");
	// break-blocks=all
	astyle.setBreakHeaderBlocks(true);
	astyle.setBreakClosingBlocks(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "F");
	// invalid
	astyle.setBreakHeaderBlocks(false);
	astyle.setBreakClosingBlocks(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "invalid-breakClosingBlocks=true");
}

TEST(AStyleIFace_PadShort, GetOptions_DeleteEmptyLines)
// Test AStyleIFace::GetOptions deleteEmptyLines short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setDeleteEmptyLines(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setDeleteEmptyLines(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xe");
}

TEST(AStyleIFace_PadShort, GetOptions_FillEmptyLines)
// Test AStyleIFace::GetOptions fillEmptyLines short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setFillEmptyLines(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setFillEmptyLines(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "E");
}

TEST(AStyleIFace_PadShort, GetOptions_PadComma)
// Test AStyleIFace::GetOptions padComma short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPadComma(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPadComma(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xg");
}

TEST(AStyleIFace_PadShort, GetOptions_PadFirstParenOut)
// Test AStyleIFace::GetOptions padFirstParenOut short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPadFirstParenOut(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPadFirstParenOut(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xd");
}

TEST(AStyleIFace_PadShort, GetOptions_PadHeader)
// Test AStyleIFace::GetOptions padHeader short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPadHeader(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPadHeader(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "H");
}

TEST(AStyleIFace_PadShort, GetOptions_PadOperator)
// Test AStyleIFace::GetOptions padOperator short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPadOperator(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPadOperator(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "p");
}

TEST(AStyleIFace_PadShort, GetOptions_PadParen)
// Test AStyleIFace::GetOptions padParen short options
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the options
	astyle.setPadParenOutside(true);
	astyle.setPadParenInside(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "P");
	astyle.setPadParenOutside(true);
	astyle.setPadParenInside(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "d");
	astyle.setPadParenOutside(false);
	astyle.setPadParenInside(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "D");
}

TEST(AStyleIFace_PadShort, GetOptions_UnpadParen)
// Test AStyleIFace::GetOptions unpadParen short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setUnpadParen(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setUnpadParen(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "U");
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Formatting Short Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_FormatShort, GetOptions_AddBrackets)
// Test AStyleIFace::GetOptions addBrackets short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setAddBraces(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAddBraces(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "j");
}

TEST(AStyleIFace_FormatShort, GetOptions_AddOneLineBrackets)
// Test AStyleIFace::GetOptions addOneLineBrackets short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setAddOneLineBraces(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAddOneLineBraces(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "J");
}

TEST(AStyleIFace_FormatShort, GetOptions_BreakCloseBrackets)
// Test AStyleIFace::GetOptions breakCloseBrackets short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setBreakClosingBraces(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setBreakClosingBraces(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "y");
}

TEST(AStyleIFace_FormatShort, GetOptions_BreakElseIfs)
// Test AStyleIFace::GetOptions breakElseIfs short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setBreakElseIfs(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setBreakElseIfs(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "e");
}

TEST(AStyleIFace_FormatShort, GetOptions_BreakOneLineHeaders)
// Test AStyleIFace::GetOptions breakOneLineHeaders short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setBreakOneLineHeaders(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setBreakOneLineHeaders(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xb");
}

TEST(AStyleIFace_FormatShort, GetOptions_CloseTemplates)
// Test AStyleIFace::GetOptions closeTemplates short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setCloseTemplates(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setCloseTemplates(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xy");
}

TEST(AStyleIFace_FormatShort, GetOptions_ConvertTabs)
// Test AStyleIFace::GetOptions convertTabs short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setConvertTabs(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setConvertTabs(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "c");
}

TEST(AStyleIFace_FormatShort, GetOptions_KeepOneLineBlocks)
// Test AStyleIFace::GetOptions breakOneLineBlocks short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	// NOTE: the option is TRUE by default
	astyle.setBreakOneLineBlocks(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setBreakOneLineBlocks(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "O");
}

TEST(AStyleIFace_FormatShort, GetOptions_KeepOneLineStatements)
// Test AStyleIFace::GetOptions breakOneLineStmts short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	// NOTE: the option is TRUE by default
	astyle.setBreakOneLineStmts(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setBreakOneLineStmts(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "o");
}

TEST(AStyleIFace_FormatShort, GetOptions_MaxCodeLength)
// Test AStyleIFace::GetOptions maxCodeLength short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setMaxCodeLength(-1);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setMaxCodeLength(MAX_CODE_LENGTH_MIN);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xC50");
	astyle.setMaxCodeLength(MAX_CODE_LENGTH_MAX);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xC200");
	// test invalid max code length
	astyle.setMaxCodeLength(49);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "invalid-maxCodeLength=49");
	astyle.setMaxCodeLength(201);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "invalid-maxCodeLength=201");
}

TEST(AStyleIFace_FormatShort, GetOptions_RemoveBrackets)
// Test AStyleIFace::GetOptions removeBrackets short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setRemoveBraces(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setRemoveBraces(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xj");
}

TEST(AStyleIFace_FormatShort, GetOptions_RemoveCommentPrefix)
// Test AStyleIFace::GetOptions removeCommentPrefix short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setRemoveCommentPrefix(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setRemoveCommentPrefix(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xp");
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Other Short Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_OtherShort, GetOptions_AlignMethodColon)
// Test AStyleIFace::GetOptions alignMethodColon short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setAlignMethodColon(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setAlignMethodColon(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xM");
}

TEST(AStyleIFace_OtherShort, GetOptions_PadMethodPrefix)
// Test AStyleIFace::GetOptions padMethodPrefix short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPadMethodPrefix(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPadMethodPrefix(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xQ");
}

TEST(AStyleIFace_OtherShort, GetOptions_UnpadMethodPrefix)
// Test AStyleIFace::GetOptions unpadMethodPrefix short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setUnpadMethodPrefix(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setUnpadMethodPrefix(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xR");
}

TEST(AStyleIFace_OtherShort, GetOptions_PadMethodColon)
// Test AStyleIFace::GetOptions padMethodColon short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.setPadMethodColon(COLON_PAD_NONE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xP0");
	astyle.setPadMethodColon(COLON_PAD_ALL);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xP1");
	astyle.setPadMethodColon(COLON_PAD_AFTER);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xP2");
	astyle.setPadMethodColon(COLON_PAD_BEFORE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xP3");

	// test invalid min conditional option
	astyle.setPadMethodColon(COLON_PAD_NO_CHANGE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.setPadMethodColon(-1);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == "invalid-padMethodColon=-1");
	astyle.setPadMethodColon(COLON_PAD_END);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxString::Format("invalid-padMethodColon=%d", COLON_PAD_END));
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions useSeparator Tests
//-------------------------------------------------------------------------

TEST(AStyleIFace_OptionsSeparator, UseSeparator)
// Test the useSeparator default (true) option of GetOptions().
{
	// create objects
	AStyleIFace astyle;

	// set some options
	astyle.setClassIndent(true);
	astyle.setSwitchIndent(true);
	astyle.setCaseIndent(true);
	astyle.setNamespaceIndent(true);
	// get the short options with separators
	wxString options = astyle.GetOptions(true);
	// options should have separators
	const wxWX2MBbuf optionsUTF8 = options.mb_str(wxConvUTF8);
	EXPECT_STREQ("C\nS\nK\nN", optionsUTF8);
}

TEST(AStyleIFace_OptionsSeparator, UseSeparatorSans)
// Test the useSeparator=false option of GetOptions().
{
	// create objects
	AStyleIFace astyle;

	// set some options
	astyle.setClassIndent(true);
	astyle.setSwitchIndent(true);
	astyle.setCaseIndent(true);
	astyle.setNamespaceIndent(true);
	// get the short options without separators
	wxString options = astyle.GetOptions(true, false);
	// options should NOT have separators
	const wxWX2MBbuf optionsUTF8 = options.mb_str(wxConvUTF8);
	EXPECT_STREQ("CSKN", optionsUTF8);
}

//-------------------------------------------------------------------------
// AStyleIFace SetAStyleOptionFromConfig Tests
//-------------------------------------------------------------------------

TEST(AStyleIFace_Config, SetAStyleOptionFromConfig_InvalidKey)
// Test AStyleIFace::SetAStyleOptionFromConfig with an invalid key
{
	// create objects
	AStyleIFace astyle;

	// test for error
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig("Invalid-key-1", asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig("Invalid-key-2", asFALSE));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig("Invalid-key-3", "-1"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig("Invalid-key-4", "4"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig("Invalid-key-5", "X"));
}

TEST(AStyleIFace_Config, SetAStyleOptionFromConfig_AlignPointer)
// Test AStyleIFace::SetAStyleOptionFromConfig alignPointer options
{
	// create objects
	AStyleIFace astyle;

	// test for error
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(ALIGN_POINTER, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(ALIGN_POINTER, asFALSE));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(ALIGN_POINTER, "-1"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(ALIGN_POINTER, "4"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(ALIGN_POINTER, "X"));
	// test the value
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ALIGN_POINTER, "1"));
	EXPECT_EQ(PTR_ALIGN_TYPE, astyle.AStyleIFace::getAlignPointer());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ALIGN_POINTER, "2"));
	EXPECT_EQ(PTR_ALIGN_MIDDLE, astyle.AStyleIFace::getAlignPointer());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ALIGN_POINTER, "3"));
	EXPECT_EQ(PTR_ALIGN_NAME, astyle.AStyleIFace::getAlignPointer());
}

TEST(AStyleIFace_Config, SetAStyleOptionFromConfig_AlignReference)
// Test AStyleIFace::SetAStyleOptionFromConfig alignReference options
{
	// create objects
	AStyleIFace astyle;

	// test for error
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(ALIGN_REFERENCE, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(ALIGN_REFERENCE, asFALSE));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(ALIGN_REFERENCE, "-1"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(ALIGN_REFERENCE, "5"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(ALIGN_REFERENCE, "X"));
	// test the value
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ALIGN_REFERENCE, "0"));
	EXPECT_EQ(REF_ALIGN_NONE, astyle.AStyleIFace::getAlignReference());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ALIGN_REFERENCE, "1"));
	EXPECT_EQ(REF_ALIGN_TYPE, astyle.AStyleIFace::getAlignReference());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ALIGN_REFERENCE, "2"));
	EXPECT_EQ(REF_ALIGN_MIDDLE, astyle.AStyleIFace::getAlignReference());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ALIGN_REFERENCE, "3"));
	EXPECT_EQ(REF_ALIGN_NAME, astyle.AStyleIFace::getAlignReference());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ALIGN_REFERENCE, "4"));
	EXPECT_EQ(REF_SAME_AS_PTR, astyle.AStyleIFace::getAlignReference());
}

TEST(AStyleIFace_Config, SetAStyleOptionFromConfig_Boolean)
// Test AStyleIFace::SetAStyleOptionFromConfig for boolean options
{
	// create objects
	AStyleIFace astyle;

	// test invalid options
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_CLASSES, "error-test"));
	// test a few false options, should be invalid
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_CLASSES, asFALSE));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_SWITCHES, asFALSE));
	// modifiers
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ATTACH_NAMESPACES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getAttachNamespace());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ATTACH_CLASSES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getAttachClass());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ATTACH_INLINES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getAttachInline());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ATTACH_EXTERN_C, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getAttachExternC());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ATTACH_CLOSING_WHILE, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getAttachClosingWhile());
	// indentation
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_CLASSES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getClassIndent());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_MODIFIERS, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getModifierIndent());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_SWITCHES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getSwitchIndent());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_CASES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getCaseIndent());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_NAMESPACES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getNamespaceIndent());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_LABELS, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getLabelIndent());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_PREPROC_BLOCK, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getPreprocBlockIndent());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_PREPROC_DEFINE, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getPreprocDefineIndent());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_PREPROC_COND, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getPreprocCondIndent());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_COL1_COMMENTS, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getCol1CommentIndent());
	// padding
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(PAD_OPER, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getPadOperator());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(PAD_COMMA, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getPadComma());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(PAD_HEADER, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getPadHeader());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(UNPAD_PAREN, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getUnpadParen());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(DELETE_EMPTY_LINES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getDeleteEmptyLines());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(FILL_EMPTY_LINES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getFillEmptyLines());
	// formatting
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(BREAK_CLOSING_BRACES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getBreakClosingBraces());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(BREAK_ELSEIFS, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getBreakElseIfs());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(BREAK_ONE_LINE_HEADERS, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getBreakOneLineHeaders());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ADD_BRACES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getAddBraces());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ADD_ONE_LINE_BRACES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getAddOneLineBraces());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(REMOVE_BRACES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getRemoveBraces());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(REMOVE_COMMENT_PREFIX, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getRemoveCommentPrefix());
	// default is true
	EXPECT_TRUE(astyle.AStyleIFace::getBreakOneLineBlocks());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(KEEP_ONE_LINE_BLOCKS, asTRUE));
	EXPECT_FALSE(astyle.AStyleIFace::getBreakOneLineBlocks());
	// default is true
	EXPECT_TRUE(astyle.AStyleIFace::getBreakOneLineStmts());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(KEEP_ONE_LINE_STATEMENTS, asTRUE));
	EXPECT_FALSE(astyle.AStyleIFace::getBreakOneLineStmts());
	// end default is true
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(CONVERT_TABS, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getConvertTabs());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(BREAK_AFTER_LOGICAL, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getBreakAfterLogical());
	// other
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(PAD_METHOD_PREFIX, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getPadMethodPrefix());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(UNPAD_METHOD_PREFIX, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getUnpadMethodPrefix());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(PAD_RETURN_TYPE, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getPadReturnType());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(UNPAD_RETURN_TYPE, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getUnpadReturnType());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(ALIGN_METHOD_COLON, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::getAlignMethodColon());
}

TEST(AStyleIFace_Config, SetAStyleOptionFromConfig_BreakBlocks)
// Test AStyleIFace::SetAStyleOptionFromConfig breakBlocks options
{
	// create objects
	AStyleIFace astyle;

	// test for error
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(BREAK_BLOCKS, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(BREAK_BLOCKS, asFALSE));
	// test the value
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(BREAK_BLOCKS, "open"));
	EXPECT_TRUE(astyle.AStyleIFace::getBreakHeaderBlocks()) << "Failure for break-blocks";
	EXPECT_FALSE(astyle.AStyleIFace::getBreakClosingBlocks()) << "Failure for break-blocks";
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(BREAK_BLOCKS, "all"));
	EXPECT_TRUE(astyle.AStyleIFace::getBreakHeaderBlocks()) << "Failure for break-blocks=all";
	EXPECT_TRUE(astyle.AStyleIFace::getBreakClosingBlocks()) << "Failure for break-blocks=all";
}

TEST(AStyleIFace_Config, SetAStyleOptionFromConfig_ContinuationIndent)
// Test AStyleIFace::SetAStyleOptionFromConfig continuationIndent option
{
	// create objects
	AStyleIFace astyle;

	// test the continuation indent for error
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_CONTINUATION, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_CONTINUATION, "-1"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_CONTINUATION, "5"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_CONTINUATION, "X"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_CONTINUATION, wxEmptyString));
	// test the continuation indent
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_CONTINUATION, "2"));
	EXPECT_EQ(2, astyle.AStyleIFace::getContinuationIndent());
}

TEST(AStyleIFace_Config, SetAStyleOptionFromConfig_Indent)
// Test AStyleIFace::SetAStyleOptionFromConfig indent options
{
	// create objects
	AStyleIFace astyle;

	// test the indent-type for error
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_TYPE, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_TYPE, asFALSE));

	// test the indent-length for error
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_LENGTH, "-1"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_LENGTH, "0"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_LENGTH, "21"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_LENGTH, " "));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_LENGTH, "="));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_LENGTH, "tab"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_LENGTH, "X"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(INDENT_LENGTH, wxEmptyString));

	// test the indent-type valid values
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_TYPE, INDENT_TYPE_SPACES));
	EXPECT_EQ(INDENT_SPACES, astyle.AStyleIFace::getIndentType());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_TYPE, INDENT_TYPE_TAB));
	EXPECT_EQ(INDENT_TABS, astyle.AStyleIFace::getIndentType());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_TYPE, INDENT_TYPE_FTAB));
	EXPECT_EQ(INDENT_FTABS, astyle.AStyleIFace::getIndentType());

	// test the indent-length valid values
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_LENGTH, "2"));
	EXPECT_EQ(2, astyle.AStyleIFace::getIndentLength());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(INDENT_LENGTH, "20"));
	EXPECT_EQ(20, astyle.AStyleIFace::getIndentLength());
}

TEST(AStyleIFace_Config, SetAStyleOptionFromConfig_MaxCodeLength)
// Test AStyleIFace::SetAStyleOptionFromConfig maxCodeLength option
{
	// create objects
	AStyleIFace astyle;

	// test the max code length for error
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MAX_CODE_LENGTH, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MAX_CODE_LENGTH, "-1"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MAX_CODE_LENGTH, "49"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MAX_CODE_LENGTH, "201"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MAX_CODE_LENGTH, "X"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MAX_CODE_LENGTH, wxEmptyString));
	// test the indent length
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(MAX_CODE_LENGTH, "100"));
	EXPECT_EQ(100, astyle.AStyleIFace::getMaxCodeLength());
}

TEST(AStyleIFace_Config, SetAStyleOptionFromConfig_MaxInStatement)
// Test AStyleIFace::SetAStyleOptionFromConfig maxInStatementIndent option
{
	// create objects
	AStyleIFace astyle;

	// test the indent length for error
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MAX_INSTATEMENT_INDENT, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MAX_INSTATEMENT_INDENT, "-1"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MAX_INSTATEMENT_INDENT, "39"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MAX_INSTATEMENT_INDENT, "121"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MAX_INSTATEMENT_INDENT, "X"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MAX_INSTATEMENT_INDENT, wxEmptyString));
	// test the indent length
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(MAX_INSTATEMENT_INDENT, "50"));
	EXPECT_EQ(50, astyle.AStyleIFace::getMaxInStatementIndent());
}

TEST(AStyleIFace_Config, SetAStyleOptionFromConfig_MinConditional)
// Test AStyleIFace::SetAStyleOptionFromConfig minConditionalOption option
{
	// create objects
	AStyleIFace astyle;

	// test the option for error
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MIN_CONDITIONAL_INDENT, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MIN_CONDITIONAL_INDENT, "-1"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MIN_CONDITIONAL_INDENT, "4"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MIN_CONDITIONAL_INDENT, "X"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(MIN_CONDITIONAL_INDENT, wxEmptyString));
	// test the option
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(MIN_CONDITIONAL_INDENT, "0"));
	EXPECT_EQ(MINCOND_ZERO, astyle.AStyleIFace::getMinConditionalOption());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(MIN_CONDITIONAL_INDENT, "1"));
	EXPECT_EQ(MINCOND_ONE, astyle.AStyleIFace::getMinConditionalOption());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(MIN_CONDITIONAL_INDENT, "2"));	// this is the default
	EXPECT_EQ(MINCOND_TWO, astyle.AStyleIFace::getMinConditionalOption());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(MIN_CONDITIONAL_INDENT, "3"));
	EXPECT_EQ(MINCOND_ONEHALF, astyle.AStyleIFace::getMinConditionalOption());
}

TEST(AStyleIFace_Config, SetAStyleOptionFromConfig_PadMethodColon)
// Test AStyleIFace::SetAStyleOptionFromConfig padMethodColon option
{
	// create objects
	AStyleIFace astyle;

	// test the option for error
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(PAD_METHOD_COLON, asTRUE));
	EXPECT_EQ(COLON_PAD_NO_CHANGE, astyle.AStyleIFace::getPadMethodColon());
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(PAD_METHOD_COLON, "non"));
	EXPECT_EQ(COLON_PAD_NO_CHANGE, astyle.AStyleIFace::getPadMethodColon());
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(PAD_METHOD_COLON, "allx"));
	EXPECT_EQ(COLON_PAD_NO_CHANGE, astyle.AStyleIFace::getPadMethodColon());
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(PAD_METHOD_COLON, wxEmptyString));
	EXPECT_EQ(COLON_PAD_NO_CHANGE, astyle.AStyleIFace::getPadMethodColon());
	// test the option
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(PAD_METHOD_COLON, "none"));
	EXPECT_EQ(COLON_PAD_NONE, astyle.AStyleIFace::getPadMethodColon());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(PAD_METHOD_COLON, "all"));
	EXPECT_EQ(COLON_PAD_ALL, astyle.AStyleIFace::getPadMethodColon());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(PAD_METHOD_COLON, "after"));	// this is the default
	EXPECT_EQ(COLON_PAD_AFTER, astyle.AStyleIFace::getPadMethodColon());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(PAD_METHOD_COLON, "before"));
	EXPECT_EQ(COLON_PAD_BEFORE, astyle.AStyleIFace::getPadMethodColon());
}

TEST(AStyleIFace_Config, SetAStyleOptionFromConfig_PadParens)
// Test AStyleIFace::SetAStyleOptionFromConfig padParens options
{
	// create objects
	AStyleIFace astyle;

	// test for error
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(PAD_PAREN, "error-test"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(PAD_PAREN, asTRUE));
	// test the value
	// test the pad-paren-out
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(PAD_PAREN, "out"));
	EXPECT_TRUE(astyle.AStyleIFace::getPadParenOutside()) << "Failure for pad-paren-out";
	EXPECT_FALSE(astyle.AStyleIFace::getPadParenInside()) << "Failure for pad-paren-out";
	// test the pad-paren-in
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(PAD_PAREN, "in"));
	EXPECT_FALSE(astyle.AStyleIFace::getPadParenOutside()) << "Failure for pad-paren-in";
	EXPECT_TRUE(astyle.AStyleIFace::getPadParenInside()) << "Failure for pad-paren-in";
	// test the pad-paren
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(PAD_PAREN, "all"));
	EXPECT_TRUE(astyle.AStyleIFace::getPadParenOutside()) << "Failure for pad-paren";
	EXPECT_TRUE(astyle.AStyleIFace::getPadParenInside()) << "Failure for pad-paren";
}

TEST(AStyleIFace_Config, SetAStyleOptionFromConfig_Styles)
// Test AStyleIFace::SetAStyleOptionFromConfig for style options
{
	// create objects
	AStyleIFace astyle;

	// test for error
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(STYLE, "error-test"));
	EXPECT_FALSE(astyle.SetAStyleOptionFromConfig(STYLE, asTRUE));
	// test the styles
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(STYLE, ALLMAN));
	EXPECT_EQ(STYLE_ALLMAN, astyle.AStyleIFace::getBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(STYLE, JAVA));
	EXPECT_EQ(STYLE_JAVA, astyle.AStyleIFace::getBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(STYLE, KandR));
	EXPECT_EQ(STYLE_KR, astyle.AStyleIFace::getBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(STYLE, STROUSTRUP));
	EXPECT_EQ(STYLE_STROUSTRUP, astyle.AStyleIFace::getBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(STYLE, WHITESMITH));
	EXPECT_EQ(STYLE_WHITESMITH, astyle.AStyleIFace::getBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(STYLE, BANNER));
	EXPECT_EQ(STYLE_BANNER, astyle.AStyleIFace::getBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(STYLE, GNU));
	EXPECT_EQ(STYLE_GNU, astyle.AStyleIFace::getBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(STYLE, LINUXX));
	EXPECT_EQ(STYLE_LINUX, astyle.AStyleIFace::getBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(STYLE, HORSTMANN));
	EXPECT_EQ(STYLE_HORSTMANN, astyle.AStyleIFace::getBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(STYLE, oneTBS));
	EXPECT_EQ(STYLE_1TBS, astyle.AStyleIFace::getBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(STYLE, GOOGLE));
	EXPECT_EQ(STYLE_GOOGLE, astyle.AStyleIFace::getBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(STYLE, MOZILLA));
	EXPECT_EQ(STYLE_MOZILLA, astyle.AStyleIFace::getBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(STYLE, PICO));
	EXPECT_EQ(STYLE_PICO, astyle.AStyleIFace::getBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOptionFromConfig(STYLE, LISP));
	EXPECT_EQ(STYLE_LISP, astyle.AStyleIFace::getBraceStyle());
}

//-------------------------------------------------------------------------
// AStyleIFace Other AStyleIFace Tests
//-------------------------------------------------------------------------

TEST(AStyleIFace_Other, TranslatePadMethodColonString)
// Test AStyleIFace::TranslatePadMethodColonString for correct returns.
{
	// create objects
	AStyleIFace astyle;

	// test the option for error
	EXPECT_EQ(COLON_PAD_NO_CHANGE, astyle.TranslatePadMethodColonString(asTRUE));
	EXPECT_EQ(COLON_PAD_NO_CHANGE, astyle.TranslatePadMethodColonString("X"));
	EXPECT_EQ(COLON_PAD_NO_CHANGE, astyle.TranslatePadMethodColonString(wxEmptyString));

	// test the option
	EXPECT_EQ(COLON_PAD_NONE, astyle.TranslatePadMethodColonString("none"));
	EXPECT_EQ(COLON_PAD_ALL, astyle.TranslatePadMethodColonString("all"));
	EXPECT_EQ(COLON_PAD_AFTER, astyle.TranslatePadMethodColonString("after"));
	EXPECT_EQ(COLON_PAD_BEFORE, astyle.TranslatePadMethodColonString("before"));
}

TEST(AStyleIFace_Other, TranslatePadMethodColonValue)
// Test AStyleIFace::TranslatePadMethodColonValue for correct returns.
{
	// create objects
	AStyleIFace astyle;

	// test the option for error
	EXPECT_TRUE(astyle.TranslatePadMethodColonValue(COLON_PAD_NO_CHANGE) == wxEmptyString);
	EXPECT_TRUE(astyle.TranslatePadMethodColonValue(COLON_PAD_END) == wxEmptyString);

	// test the option
	EXPECT_TRUE(astyle.TranslatePadMethodColonValue(COLON_PAD_NONE) == "none");
	EXPECT_TRUE(astyle.TranslatePadMethodColonValue(COLON_PAD_ALL) == "all");
	EXPECT_TRUE(astyle.TranslatePadMethodColonValue(COLON_PAD_AFTER) == "after");
	EXPECT_TRUE(astyle.TranslatePadMethodColonValue(COLON_PAD_BEFORE) == "before");
}

//----------------------------------------------------------------------------

}  // anonymous namespace
