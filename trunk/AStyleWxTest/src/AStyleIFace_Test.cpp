// AStyleIFace_Test.cpp
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

/* ----------------------------------------------------------------------------
TO ADD A NEW OPTION
Add new test function to "AStyleIFace_*Options, GetOptions_".
Add new test function to "AStyleIFace_*Short, GetOptions_".
Add new test function to "AStyleIFace_Config, SetAStyleOption".
All boolean functions for the above are added to "SetAStyleOptionBoolean".
---------------------------------------------------------------------------- */

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleIFace.h"
#include "gtest/gtest.h"

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {
//
//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Brace Style Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_StyleOptions, GetOptions_StylesAll)
// Test AStyleIFace::GetOptions for brace style options
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the options
	const wxString STYLE_EQ = "style=";
	astyle.SetBraceStyle(STYLE_NONE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBraceStyle(STYLE_ALLMAN);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + ALLMAN);
	astyle.SetBraceStyle(STYLE_JAVA);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + JAVA);
	astyle.SetBraceStyle(STYLE_KR);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + KandR);
	astyle.SetBraceStyle(STYLE_STROUSTRUP);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + STROUSTRUP);
	astyle.SetBraceStyle(STYLE_WHITESMITH);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + WHITESMITH);
	astyle.SetBraceStyle(STYLE_RATLIFF);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + RATLIFF);
	astyle.SetBraceStyle(STYLE_GNU);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + GNU);
	astyle.SetBraceStyle(STYLE_LINUX);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + LINUXX);
	astyle.SetBraceStyle(STYLE_HORSTMANN);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + HORSTMANN);
	astyle.SetBraceStyle(STYLE_1TBS);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + oneTBS);
	astyle.SetBraceStyle(STYLE_GOOGLE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + GOOGLE);
	astyle.SetBraceStyle(STYLE_MOZILLA);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + MOZILLA);
	astyle.SetBraceStyle(STYLE_WEBKIT);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + WEBKIT);
	astyle.SetBraceStyle(STYLE_PICO);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + PICO);
	astyle.SetBraceStyle(STYLE_LISP);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == STYLE_EQ + LISP);
	astyle.SetBraceStyle(static_cast<BraceStyle>(99));
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
	astyle.SetIndentType(INDENT_SPACES);
	astyle.SetIndentLength(4);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetIndentLength(2);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_SPACES "=2");
	astyle.SetIndentLength(20);
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
	astyle.SetIndentType(INDENT_TABS);
	astyle.SetIndentLength(4);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_TAB);
	astyle.SetIndentLength(2);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_TAB "=2");
	astyle.SetIndentLength(20);
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
	astyle.SetIndentType(INDENT_FTABS);
	astyle.SetIndentLength(4);
	astyle.SetUseTabLength(false);
	astyle.SetTabLength(8);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_FTAB);
	astyle.SetIndentLength(2);
	astyle.SetUseTabLength(false);
	astyle.SetTabLength(4);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_FTAB "=2");
	astyle.SetIndentLength(20);
	astyle.SetUseTabLength(false);
	astyle.SetTabLength(10);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_FTAB "=20");
	// test indent with force tabs and tab-length
	astyle.SetIndentType(INDENT_FTABS);
	astyle.SetIndentLength(4);
	astyle.SetUseTabLength(true);
	astyle.SetTabLength(8);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_FTAB_X);
	astyle.SetIndentLength(4);
	astyle.SetUseTabLength(true);
	astyle.SetTabLength(6);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_OPT_FTAB_X "=6");
	astyle.SetIndentLength(3);
	astyle.SetUseTabLength(true);
	astyle.SetTabLength(6);
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
	astyle.SetIndentType(static_cast<IndentType>(9));
	astyle.SetIndentLength(4);
	options = astyle.GetOptions();
	EXPECT_STREQ("invalid-indentType=9", options);

	// test invalid indent length
	// the options will also have indent=spaces=?
	astyle.SetIndentType(INDENT_SPACES);
	astyle.SetIndentLength(1);
	options = astyle.GetOptions();
	EXPECT_TRUE(options.Find("invalid-indentLength=1") != wxNOT_FOUND);
	astyle.SetIndentLength(21);
	options = astyle.GetOptions();
	EXPECT_TRUE(options.Find("invalid-indentLength=21") != wxNOT_FOUND);
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Brace Modifier Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_ModifierOptions, GetOptions_AttachNamespace)
// Test AStyleIFace::GetOptions attachNamespace option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetAttachNamespace(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAttachNamespace(true);
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
	astyle.SetAttachClass(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAttachClass(true);
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
	astyle.SetAttachInline(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAttachInline(true);
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
	astyle.SetAttachExternC(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAttachExternC(true);
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
	astyle.SetAttachClosingWhile(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAttachClosingWhile(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ATTACH_CLOSING_WHILE);
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Indentation Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_IndentOptions, GetOptions_AfterParenIndent)
// Test AStyleIFace::GetOptions afterParenIndent option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetAfterParenIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAfterParenIndent(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == INDENT_AFTER_PARENS);
}

TEST(AStyleIFace_IndentOptions, GetOptions_CaseIndent)
// Test AStyleIFace::GetOptions caseIndent option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetCaseIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetCaseIndent(true);
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
	astyle.SetClassIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetClassIndent(true);
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
	astyle.SetCol1CommentIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetCol1CommentIndent(true);
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
	astyle.SetContinuationIndent(1);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetContinuationIndent(2);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, INDENT_CONTINUATION "=2");

	// test invalid min conditional option
	astyle.SetContinuationIndent(-1);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, "invalid-continuationIndent=-1");
	astyle.SetContinuationIndent(5);
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
	astyle.SetLabelIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetLabelIndent(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == INDENT_LABELS);
}

TEST(AStyleIFace_IndentOptions, GetOptions_MaxContinuation)
// Test AStyleIFace::GetOptions maxContinuationIndent option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetMaxContinuationIndent(40);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetMaxContinuationIndent(50);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, MAX_CONTINUATION_INDENT "=50");
	// test invalid max instatement indent
	astyle.SetMaxContinuationIndent(39);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, "invalid-maxContinuationIndent=39");
	astyle.SetMaxContinuationIndent(121);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, "invalid-maxContinuationIndent=121");
}

TEST(AStyleIFace_IndentOptions, GetOptions_MinConditional)
// Test AStyleIFace::GetOptions minConditionalOption option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetMinConditionalOption(MINCOND_ZERO);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, MIN_CONDITIONAL_INDENT "=0");
	astyle.SetMinConditionalOption(MINCOND_ONE);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, MIN_CONDITIONAL_INDENT "=1");
	astyle.SetMinConditionalOption(MINCOND_TWO);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetMinConditionalOption(MINCOND_ONEHALF);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, MIN_CONDITIONAL_INDENT "=3");

	// test invalid min conditional option
	astyle.SetMinConditionalOption(static_cast<MinConditional>(-1));
	options = astyle.GetOptions();
	EXPECT_STREQ(options, "invalid-minConditionalOption=-1");
	astyle.SetMinConditionalOption(static_cast<MinConditional>(9));
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
	astyle.SetModifierIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetModifierIndent(true);
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
	astyle.SetNamespaceIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetNamespaceIndent(true);
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
	astyle.SetPreprocBlockIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPreprocBlockIndent(true);
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
	astyle.SetPreprocCondIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPreprocCondIndent(true);
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
	astyle.SetPreprocDefineIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPreprocDefineIndent(true);
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
	astyle.SetSwitchIndent(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetSwitchIndent(true);
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
	astyle.SetAlignPointer(PTR_ALIGN_NONE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAlignPointer(PTR_ALIGN_TYPE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ALIGN_POINTER_TYPE);
	astyle.SetAlignPointer(PTR_ALIGN_MIDDLE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ALIGN_POINTER_MIDDLE);
	astyle.SetAlignPointer(PTR_ALIGN_NAME);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ALIGN_POINTER_NAME);
	astyle.SetAlignPointer(static_cast<PointerAlign>(99));
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
	astyle.SetAlignReference(REF_ALIGN_NONE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ALIGN_REFERENCE_NONE);
	astyle.SetAlignReference(REF_ALIGN_TYPE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ALIGN_REFERENCE_TYPE);
	astyle.SetAlignReference(REF_ALIGN_MIDDLE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ALIGN_REFERENCE_MIDDLE);
	astyle.SetAlignReference(REF_ALIGN_NAME);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ALIGN_REFERENCE_NAME);
	astyle.SetAlignReference(static_cast<ReferenceAlign>(99));
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
	astyle.SetBreakHeaderBlocks(false);
	astyle.SetBreakClosingBlocks(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	// break-blocks
	astyle.SetBreakHeaderBlocks(true);
	astyle.SetBreakClosingBlocks(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == BREAK_BLOCKS);
	// break-blocks=all
	astyle.SetBreakHeaderBlocks(true);
	astyle.SetBreakClosingBlocks(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == BREAK_BLOCKS_ALL);
	// invalid
	astyle.SetBreakHeaderBlocks(false);
	astyle.SetBreakClosingBlocks(true);
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
	astyle.SetDeleteEmptyLines(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetDeleteEmptyLines(true);
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
	astyle.SetFillEmptyLines(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetFillEmptyLines(true);
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
	astyle.SetPadComma(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPadComma(true);
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
	astyle.SetPadFirstParenOut(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPadFirstParenOut(true);
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
	astyle.SetPadHeader(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPadHeader(true);
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
	astyle.SetPadOperator(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPadOperator(true);
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
	astyle.SetPadParenOutside(true);
	astyle.SetPadParenInside(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == PAD_PAREN);
	astyle.SetPadParenOutside(true);
	astyle.SetPadParenInside(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == PAD_PAREN_OUT);
	astyle.SetPadParenOutside(false);
	astyle.SetPadParenInside(true);
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
	astyle.SetUnpadParen(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetUnpadParen(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == UNPAD_PAREN);
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Formatting Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_FormatOptions, GetOptions_AddBraces)
// Test AStyleIFace::GetOptions addBraces option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetAddBraces(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAddBraces(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ADD_BRACES);
}

TEST(AStyleIFace_FormatOptions, GetOptions_AddOneLineBraces)
// Test AStyleIFace::GetOptions addOneLineBraces option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetAddOneLineBraces(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAddOneLineBraces(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ADD_ONE_LINE_BRACES);
}

TEST(AStyleIFace_FormatOptions, GetOptions_AttachReturnType)
// Test AStyleIFace::GetOptions attachReturnType option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetAttachReturnType(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAttachReturnType(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ATTACH_RETURN_TYPE);
}

TEST(AStyleIFace_FormatOptions, GetOptions_AttachReturnTypeDecl)
// Test AStyleIFace::GetOptions breakReturnTypeDecl option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetAttachReturnTypeDecl(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAttachReturnTypeDecl(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == ATTACH_RETURN_TYPE_DECL);
}

TEST(AStyleIFace_FormatOptions, GetOptions_BreakAfterLogical)
// Test AStyleIFace::GetOptions breakAfterLogical option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetBreakAfterLogical(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBreakAfterLogical(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == BREAK_AFTER_LOGICAL);
}

TEST(AStyleIFace_FormatOptions, GetOptions_BreakCloseBraces)
// Test AStyleIFace::GetOptions breakCloseBraces option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetBreakClosingBraces(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBreakClosingBraces(true);
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
	astyle.SetBreakElseIfs(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBreakElseIfs(true);
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
	astyle.SetBreakOneLineHeaders(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBreakOneLineHeaders(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == BREAK_ONE_LINE_HEADERS);
}

TEST(AStyleIFace_FormatOptions, GetOptions_BreakReturnType)
// Test AStyleIFace::GetOptions breakReturnType option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetBreakReturnType(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBreakReturnType(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == BREAK_RETURN_TYPE);
}

TEST(AStyleIFace_FormatOptions, GetOptions_BreakReturnTypeDecl)
// Test AStyleIFace::GetOptions breakReturnTypeDecl option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetBreakReturnTypeDecl(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBreakReturnTypeDecl(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == BREAK_RETURN_TYPE_DECL);
}

TEST(AStyleIFace_FormatOptions, GetOptions_CloseTemplates)
// Test AStyleIFace::GetOptions closeTemplates option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetCloseTemplates(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetCloseTemplates(true);
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
	astyle.SetConvertTabs(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetConvertTabs(true);
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
	astyle.SetBreakOneLineBlocks(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBreakOneLineBlocks(false);
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
	astyle.SetBreakOneLineStmts(true);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBreakOneLineStmts(false);
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
	astyle.SetMaxCodeLength(-1);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetMaxCodeLength(MAX_CODE_LENGTH_MIN);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, MAX_CODE_LENGTH "=50");
	astyle.SetMaxCodeLength(MAX_CODE_LENGTH_MAX);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, MAX_CODE_LENGTH "=200");
	// test invalid max code length
	astyle.SetMaxCodeLength(49);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == "invalid-maxCodeLength=49");
	astyle.SetMaxCodeLength(201);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == "invalid-maxCodeLength=201");
}

TEST(AStyleIFace_FormatOptions, GetOptions_RemoveBraces)
// Test AStyleIFace::GetOptions removeBraces option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetRemoveBraces(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetRemoveBraces(true);
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
	astyle.SetRemoveCommentPrefix(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetRemoveCommentPrefix(true);
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
	astyle.SetPadMethodPrefix(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPadMethodPrefix(true);
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
	astyle.SetUnpadMethodPrefix(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetUnpadMethodPrefix(true);
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
	astyle.SetPadReturnType(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPadReturnType(true);
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
	astyle.SetUnpadReturnType(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetUnpadReturnType(true);
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
	astyle.SetAlignMethodColon(false);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAlignMethodColon(true);
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
	astyle.SetPadMethodColon(COLON_PAD_NONE);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, PAD_METHOD_COLON "=none");
	astyle.SetPadMethodColon(COLON_PAD_ALL);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, PAD_METHOD_COLON "=all");
	astyle.SetPadMethodColon(COLON_PAD_AFTER);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, PAD_METHOD_COLON "=after");
	astyle.SetPadMethodColon(COLON_PAD_BEFORE);
	options = astyle.GetOptions();
	EXPECT_STREQ(options, PAD_METHOD_COLON "=before");

	// test invalid pad method colon
	astyle.SetPadMethodColon(COLON_PAD_NO_CHANGE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPadMethodColon(-1);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == "invalid-padMethodColon=-1");
	astyle.SetPadMethodColon(COLON_PAD_END);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxString::Format("invalid-padMethodColon=%d", COLON_PAD_END));
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Brace Style Short Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_StyleShort, GetOptions_All)
// Test AStyleIFace::GetOptions for style short options
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the options
	const wxString STYLE_EQ = "style=";
	astyle.SetBraceStyle(STYLE_NONE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBraceStyle(STYLE_ALLMAN);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A1") << (STYLE_EQ + ALLMAN);
	astyle.SetBraceStyle(STYLE_JAVA);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A2") << (STYLE_EQ + JAVA);
	astyle.SetBraceStyle(STYLE_KR);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A3") << (STYLE_EQ + KandR);
	astyle.SetBraceStyle(STYLE_STROUSTRUP);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A4") << (STYLE_EQ + STROUSTRUP);
	astyle.SetBraceStyle(STYLE_WHITESMITH);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A5") << (STYLE_EQ + WHITESMITH);
	astyle.SetBraceStyle(STYLE_RATLIFF);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A6") << (STYLE_EQ + RATLIFF);
	astyle.SetBraceStyle(STYLE_GNU);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A7") << (STYLE_EQ + GNU);
	astyle.SetBraceStyle(STYLE_LINUX);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A8") << (STYLE_EQ + LINUXX);
	astyle.SetBraceStyle(STYLE_HORSTMANN);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A9") << (STYLE_EQ + HORSTMANN);
	astyle.SetBraceStyle(STYLE_1TBS);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A10") << (STYLE_EQ + oneTBS);
	astyle.SetBraceStyle(STYLE_GOOGLE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A14") << (STYLE_EQ + GOOGLE);
	astyle.SetBraceStyle(STYLE_MOZILLA);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A16") << (STYLE_EQ + MOZILLA);
	astyle.SetBraceStyle(STYLE_WEBKIT);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A17") << (STYLE_EQ + WEBKIT);
	astyle.SetBraceStyle(STYLE_PICO);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A11") << (STYLE_EQ + PICO);
	astyle.SetBraceStyle(STYLE_LISP);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "A12") << (STYLE_EQ + LISP);
	astyle.SetBraceStyle(static_cast<BraceStyle>(99));
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
	astyle.SetIndentType(INDENT_SPACES);
	astyle.SetIndentLength(4);
	options = astyle.GetOptions(true);
	EXPECT_STREQ(wxEmptyString, options);
	astyle.SetIndentLength(2);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("s2", options);
	astyle.SetIndentLength(20);
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
	astyle.SetIndentType(INDENT_TABS);
	astyle.SetIndentLength(4);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("t", options);
	astyle.SetIndentLength(2);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("t2", options);
	astyle.SetIndentLength(20);
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
	astyle.SetIndentType(INDENT_FTABS);
	astyle.SetIndentLength(4);
	astyle.SetUseTabLength(false);
	astyle.SetTabLength(8);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("T", options) << INDENT_OPT_FTAB;
	astyle.SetIndentLength(2);
	astyle.SetUseTabLength(false);
	astyle.SetTabLength(4);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("T2", options) << INDENT_OPT_FTAB;
	astyle.SetIndentLength(20);
	astyle.SetUseTabLength(false);
	astyle.SetTabLength(10);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("T20", options) << INDENT_OPT_FTAB;
	// test indent with force tabs and tab-length
	astyle.SetIndentType(INDENT_FTABS);
	astyle.SetIndentLength(4);
	astyle.SetUseTabLength(true);
	astyle.SetTabLength(8);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("xT", options) << INDENT_OPT_FTAB;
	astyle.SetIndentLength(4);
	astyle.SetUseTabLength(true);
	astyle.SetTabLength(6);
	options = astyle.GetOptions(true);
	EXPECT_STREQ("xT6", options) << INDENT_OPT_FTAB;
	astyle.SetIndentLength(3);
	astyle.SetUseTabLength(true);
	astyle.SetTabLength(6);
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
	astyle.SetIndentType(static_cast<IndentType>(9));
	astyle.SetIndentLength(4);
	options = astyle.GetOptions();
	EXPECT_STREQ("invalid-indentType=9", options);

	// test invalid indent length
	// the options will also have indent=spaces=?
	astyle.SetIndentType(INDENT_SPACES);
	astyle.SetIndentLength(1);
	options = astyle.GetOptions();
	EXPECT_TRUE(options.Find("invalid-indentLength=1") != wxNOT_FOUND);
	astyle.SetIndentLength(21);
	options = astyle.GetOptions();
	EXPECT_TRUE(options.Find("invalid-indentLength=21") != wxNOT_FOUND);
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Brace Modifier Short Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_ModifierShort, GetOptions_AttachNamespace)
// Test AStyleIFace::GetOptions attachNamespace short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetAttachNamespace(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAttachNamespace(true);
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
	astyle.SetAttachClass(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAttachClass(true);
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
	astyle.SetAttachInline(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAttachInline(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xl");
}

TEST(AStyleIFace_ModifierShort, GetOptions_AttachExternC)
// Test AStyleIFace::GetOptions attachExternC short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetAttachExternC(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAttachExternC(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xk");
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Indentation Short Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_IndentShort, GetOptions_AfterParenIndent)
// Test AStyleIFace::GetOptions afterParenIndent short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetAfterParenIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAfterParenIndent(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xU");
}

TEST(AStyleIFace_IndentShort, GetOptions_CaseIndent)
// Test AStyleIFace::GetOptions caseIndent short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetCaseIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetCaseIndent(true);
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
	astyle.SetClassIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetClassIndent(true);
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
	astyle.SetCol1CommentIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetCol1CommentIndent(true);
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
	astyle.SetContinuationIndent(1);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetContinuationIndent(2);
	options = astyle.GetOptions(true);
	EXPECT_STREQ(options, "xt2");

	// test invalid min conditional option
	astyle.SetContinuationIndent(-1);
	options = astyle.GetOptions(true);
	EXPECT_STREQ(options, "invalid-continuationIndent=-1");
	astyle.SetContinuationIndent(5);
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
	astyle.SetLabelIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetLabelIndent(true);
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
	astyle.SetMaxContinuationIndent(40);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetMaxContinuationIndent(50);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "M50");
	// test invalid max instatement indent
	astyle.SetMaxContinuationIndent(39);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "invalid-maxContinuationIndent=39");
	astyle.SetMaxContinuationIndent(121);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "invalid-maxContinuationIndent=121");
}

TEST(AStyleIFace_IndentShort, GetOptions_MinConditional)
// Test AStyleIFace::GetOptions minConditionalOption short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetMinConditionalOption(MINCOND_ZERO);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "m0");
	astyle.SetMinConditionalOption(MINCOND_ONE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "m1");
	astyle.SetMinConditionalOption(MINCOND_TWO);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetMinConditionalOption(MINCOND_ONEHALF);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "m3");

	// test invalid min conditional option
	astyle.SetMinConditionalOption(static_cast<MinConditional>(-1));
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "invalid-minConditionalOption=-1");
	astyle.SetMinConditionalOption(static_cast<MinConditional>(9));
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
	astyle.SetModifierIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetModifierIndent(true);
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
	astyle.SetNamespaceIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetNamespaceIndent(true);
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
	astyle.SetPreprocBlockIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPreprocBlockIndent(true);
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
	astyle.SetPreprocCondIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPreprocCondIndent(true);
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
	astyle.SetPreprocDefineIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPreprocDefineIndent(true);
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
	astyle.SetSwitchIndent(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetSwitchIndent(true);
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
	astyle.SetAlignPointer(PTR_ALIGN_NONE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAlignPointer(PTR_ALIGN_TYPE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "k1");
	astyle.SetAlignPointer(PTR_ALIGN_MIDDLE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "k2");
	astyle.SetAlignPointer(PTR_ALIGN_NAME);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "k3");
	astyle.SetAlignPointer(static_cast<PointerAlign>(99));
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
	astyle.SetAlignReference(REF_ALIGN_NONE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "W0");
	astyle.SetAlignReference(REF_ALIGN_TYPE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "W1");
	astyle.SetAlignReference(REF_ALIGN_MIDDLE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "W2");
	astyle.SetAlignReference(REF_ALIGN_NAME);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "W3");
	astyle.SetAlignReference(static_cast<ReferenceAlign>(99));
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
	astyle.SetBreakHeaderBlocks(false);
	astyle.SetBreakClosingBlocks(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	// break-blocks
	astyle.SetBreakHeaderBlocks(true);
	astyle.SetBreakClosingBlocks(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "f");
	// break-blocks=all
	astyle.SetBreakHeaderBlocks(true);
	astyle.SetBreakClosingBlocks(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "F");
	// invalid
	astyle.SetBreakHeaderBlocks(false);
	astyle.SetBreakClosingBlocks(true);
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
	astyle.SetDeleteEmptyLines(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetDeleteEmptyLines(true);
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
	astyle.SetFillEmptyLines(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetFillEmptyLines(true);
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
	astyle.SetPadComma(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPadComma(true);
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
	astyle.SetPadFirstParenOut(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPadFirstParenOut(true);
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
	astyle.SetPadHeader(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPadHeader(true);
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
	astyle.SetPadOperator(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPadOperator(true);
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
	astyle.SetPadParenOutside(true);
	astyle.SetPadParenInside(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "P");
	astyle.SetPadParenOutside(true);
	astyle.SetPadParenInside(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "d");
	astyle.SetPadParenOutside(false);
	astyle.SetPadParenInside(true);
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
	astyle.SetUnpadParen(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetUnpadParen(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "U");
}

//-------------------------------------------------------------------------
// AStyleIFace GetOptions Tests for Formatting Short Options
//-------------------------------------------------------------------------

TEST(AStyleIFace_FormatShort, GetOptions_AddBraces)
// Test AStyleIFace::GetOptions addBraces short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetAddBraces(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAddBraces(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "j");
}

TEST(AStyleIFace_FormatShort, GetOptions_AddOneLineBraces)
// Test AStyleIFace::GetOptions addOneLineBraces short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetAddOneLineBraces(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAddOneLineBraces(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "J");
}

TEST(AStyleIFace_FormatShort, GetOptions_AttachReturnType)
// Test AStyleIFace::GetOptions attachReturnType short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetAttachReturnType(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAttachReturnType(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xf");
}

TEST(AStyleIFace_FormatShort, GetOptions_AttachReturnTypeDecl)
// Test AStyleIFace::GetOptions attachReturnTypeDecl short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetAttachReturnTypeDecl(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAttachReturnTypeDecl(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xh");
}

TEST(AStyleIFace_FormatShort, GetOptions_BreakCloseBraces)
// Test AStyleIFace::GetOptions breakCloseBraces short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetBreakClosingBraces(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBreakClosingBraces(true);
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
	astyle.SetBreakElseIfs(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBreakElseIfs(true);
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
	astyle.SetBreakOneLineHeaders(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBreakOneLineHeaders(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xb");
}

TEST(AStyleIFace_FormatShort, GetOptions_BreakReturnType)
// Test AStyleIFace::GetOptions breakReturnType short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetBreakReturnType(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBreakReturnType(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xB");
}

TEST(AStyleIFace_FormatShort, GetOptions_BreakReturnTypeDecl)
// Test AStyleIFace::GetOptions breakReturnTypeDecl short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetBreakReturnTypeDecl(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBreakReturnTypeDecl(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xD");
}

TEST(AStyleIFace_FormatShort, GetOptions_CloseTemplates)
// Test AStyleIFace::GetOptions closeTemplates short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetCloseTemplates(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetCloseTemplates(true);
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
	astyle.SetConvertTabs(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetConvertTabs(true);
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
	astyle.SetBreakOneLineBlocks(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBreakOneLineBlocks(false);
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
	astyle.SetBreakOneLineStmts(true);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetBreakOneLineStmts(false);
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
	astyle.SetMaxCodeLength(-1);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetMaxCodeLength(MAX_CODE_LENGTH_MIN);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xC50");
	astyle.SetMaxCodeLength(MAX_CODE_LENGTH_MAX);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xC200");
	// test invalid max code length
	astyle.SetMaxCodeLength(49);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "invalid-maxCodeLength=49");
	astyle.SetMaxCodeLength(201);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "invalid-maxCodeLength=201");
}

TEST(AStyleIFace_FormatShort, GetOptions_RemoveBraces)
// Test AStyleIFace::GetOptions removeBraces short option
{
	// create objects
	AStyleIFace astyle;
	wxString options;

	// test the option
	astyle.SetRemoveBraces(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetRemoveBraces(true);
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
	astyle.SetRemoveCommentPrefix(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetRemoveCommentPrefix(true);
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
	astyle.SetAlignMethodColon(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetAlignMethodColon(true);
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
	astyle.SetPadMethodPrefix(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPadMethodPrefix(true);
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
	astyle.SetUnpadMethodPrefix(false);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetUnpadMethodPrefix(true);
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
	astyle.SetPadMethodColon(COLON_PAD_NONE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xP0");
	astyle.SetPadMethodColon(COLON_PAD_ALL);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xP1");
	astyle.SetPadMethodColon(COLON_PAD_AFTER);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xP2");
	astyle.SetPadMethodColon(COLON_PAD_BEFORE);
	options = astyle.GetOptions(true);
	EXPECT_TRUE(options == "xP3");

	// test invalid min conditional option
	astyle.SetPadMethodColon(COLON_PAD_NO_CHANGE);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == wxEmptyString);
	astyle.SetPadMethodColon(-1);
	options = astyle.GetOptions();
	EXPECT_TRUE(options == "invalid-padMethodColon=-1");
	astyle.SetPadMethodColon(COLON_PAD_END);
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
	astyle.SetClassIndent(true);
	astyle.SetSwitchIndent(true);
	astyle.SetCaseIndent(true);
	astyle.SetNamespaceIndent(true);
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
	astyle.SetClassIndent(true);
	astyle.SetSwitchIndent(true);
	astyle.SetCaseIndent(true);
	astyle.SetNamespaceIndent(true);
	// get the short options without separators
	wxString options = astyle.GetOptions(true, false);
	// options should NOT have separators
	const wxWX2MBbuf optionsUTF8 = options.mb_str(wxConvUTF8);
	EXPECT_STREQ("CSKN", optionsUTF8);
}

//-------------------------------------------------------------------------
// AStyleIFace SetAStyleOption Tests
//-------------------------------------------------------------------------

TEST(AStyleIFace_Config, SetAStyleOptionInvalidKey)
// Test AStyleIFace::SetAStyleOption with an invalid key
{
	// create objects
	AStyleIFace astyle;

	// test for error
	EXPECT_FALSE(astyle.SetAStyleOption("Invalid-key-1", asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOption("Invalid-key-2", asFALSE));
	EXPECT_FALSE(astyle.SetAStyleOption("Invalid-key-3", "-1"));
	EXPECT_FALSE(astyle.SetAStyleOption("Invalid-key-4", "4"));
	EXPECT_FALSE(astyle.SetAStyleOption("Invalid-key-5", "X"));
}

TEST(AStyleIFace_Config, SetAStyleOptionAlignPointer)
// Test AStyleIFace::SetAStyleOption alignPointer options
{
	// create objects
	AStyleIFace astyle;

	// test for error
	EXPECT_FALSE(astyle.SetAStyleOption(ALIGN_POINTER, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOption(ALIGN_POINTER, asFALSE));
	EXPECT_FALSE(astyle.SetAStyleOption(ALIGN_POINTER, "-1"));
	EXPECT_FALSE(astyle.SetAStyleOption(ALIGN_POINTER, "4"));
	EXPECT_FALSE(astyle.SetAStyleOption(ALIGN_POINTER, "X"));
	// test the value
	EXPECT_TRUE(astyle.SetAStyleOption(ALIGN_POINTER, "1"));
	EXPECT_EQ(PTR_ALIGN_TYPE, astyle.AStyleIFace::GetAlignPointer());
	EXPECT_TRUE(astyle.SetAStyleOption(ALIGN_POINTER, "2"));
	EXPECT_EQ(PTR_ALIGN_MIDDLE, astyle.AStyleIFace::GetAlignPointer());
	EXPECT_TRUE(astyle.SetAStyleOption(ALIGN_POINTER, "3"));
	EXPECT_EQ(PTR_ALIGN_NAME, astyle.AStyleIFace::GetAlignPointer());
}

TEST(AStyleIFace_Config, SetAStyleOptionAlignReference)
// Test AStyleIFace::SetAStyleOption alignReference options
{
	// create objects
	AStyleIFace astyle;

	// test for error
	EXPECT_FALSE(astyle.SetAStyleOption(ALIGN_REFERENCE, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOption(ALIGN_REFERENCE, asFALSE));
	EXPECT_FALSE(astyle.SetAStyleOption(ALIGN_REFERENCE, "-1"));
	EXPECT_FALSE(astyle.SetAStyleOption(ALIGN_REFERENCE, "5"));
	EXPECT_FALSE(astyle.SetAStyleOption(ALIGN_REFERENCE, "X"));
	// test the value
	EXPECT_TRUE(astyle.SetAStyleOption(ALIGN_REFERENCE, "0"));
	EXPECT_EQ(REF_ALIGN_NONE, astyle.AStyleIFace::GetAlignReference());
	EXPECT_TRUE(astyle.SetAStyleOption(ALIGN_REFERENCE, "1"));
	EXPECT_EQ(REF_ALIGN_TYPE, astyle.AStyleIFace::GetAlignReference());
	EXPECT_TRUE(astyle.SetAStyleOption(ALIGN_REFERENCE, "2"));
	EXPECT_EQ(REF_ALIGN_MIDDLE, astyle.AStyleIFace::GetAlignReference());
	EXPECT_TRUE(astyle.SetAStyleOption(ALIGN_REFERENCE, "3"));
	EXPECT_EQ(REF_ALIGN_NAME, astyle.AStyleIFace::GetAlignReference());
	EXPECT_TRUE(astyle.SetAStyleOption(ALIGN_REFERENCE, "4"));
	EXPECT_EQ(REF_SAME_AS_PTR, astyle.AStyleIFace::GetAlignReference());
}

TEST(AStyleIFace_Config, SetAStyleOptionBoolean)
// Test AStyleIFace::SetAStyleOption for boolean options
{
	// create objects
	AStyleIFace astyle;

	// test invalid options
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_CLASSES, "error-test"));
	// test a few false options, should be invalid
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_CLASSES, asFALSE));
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_SWITCHES, asFALSE));
	// modifiers
	EXPECT_TRUE(astyle.SetAStyleOption(ATTACH_NAMESPACES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetAttachNamespace());
	EXPECT_TRUE(astyle.SetAStyleOption(ATTACH_CLASSES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetAttachClass());
	EXPECT_TRUE(astyle.SetAStyleOption(ATTACH_INLINES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetAttachInline());
	EXPECT_TRUE(astyle.SetAStyleOption(ATTACH_EXTERN_C, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetAttachExternC());
	EXPECT_TRUE(astyle.SetAStyleOption(ATTACH_CLOSING_WHILE, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetAttachClosingWhile());
	// indentation
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_AFTER_PARENS, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetAfterParenIndent());
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_CLASSES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetClassIndent());
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_MODIFIERS, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetModifierIndent());
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_SWITCHES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetSwitchIndent());
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_CASES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetCaseIndent());
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_NAMESPACES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetNamespaceIndent());
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_LABELS, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetLabelIndent());
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_PREPROC_BLOCK, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetPreprocBlockIndent());
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_PREPROC_DEFINE, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetPreprocDefineIndent());
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_PREPROC_COND, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetPreprocCondIndent());
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_COL1_COMMENTS, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetCol1CommentIndent());
	// padding
	EXPECT_TRUE(astyle.SetAStyleOption(PAD_OPER, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetPadOperator());
	EXPECT_TRUE(astyle.SetAStyleOption(PAD_COMMA, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetPadComma());
	EXPECT_TRUE(astyle.SetAStyleOption(PAD_HEADER, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetPadHeader());
	EXPECT_TRUE(astyle.SetAStyleOption(UNPAD_PAREN, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetUnpadParen());
	EXPECT_TRUE(astyle.SetAStyleOption(DELETE_EMPTY_LINES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetDeleteEmptyLines());
	EXPECT_TRUE(astyle.SetAStyleOption(FILL_EMPTY_LINES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetFillEmptyLines());
	// formatting
	EXPECT_TRUE(astyle.SetAStyleOption(ADD_BRACES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetAddBraces());
	EXPECT_TRUE(astyle.SetAStyleOption(ADD_ONE_LINE_BRACES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetAddOneLineBraces());
	EXPECT_TRUE(astyle.SetAStyleOption(ATTACH_RETURN_TYPE, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetAttachReturnType());
	EXPECT_TRUE(astyle.SetAStyleOption(ATTACH_RETURN_TYPE_DECL, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetAttachReturnTypeDecl());
	EXPECT_TRUE(astyle.SetAStyleOption(BREAK_CLOSING_BRACES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetBreakClosingBraces());
	EXPECT_TRUE(astyle.SetAStyleOption(BREAK_ELSEIFS, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetBreakElseIfs());
	EXPECT_TRUE(astyle.SetAStyleOption(BREAK_ONE_LINE_HEADERS, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetBreakOneLineHeaders());
	EXPECT_TRUE(astyle.SetAStyleOption(BREAK_RETURN_TYPE, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetBreakReturnType());
	EXPECT_TRUE(astyle.SetAStyleOption(BREAK_RETURN_TYPE_DECL, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetBreakReturnTypeDecl());
	EXPECT_TRUE(astyle.SetAStyleOption(REMOVE_BRACES, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetRemoveBraces());
	EXPECT_TRUE(astyle.SetAStyleOption(REMOVE_COMMENT_PREFIX, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetRemoveCommentPrefix());
	// default is true
	EXPECT_TRUE(astyle.AStyleIFace::GetBreakOneLineBlocks());
	EXPECT_TRUE(astyle.SetAStyleOption(KEEP_ONE_LINE_BLOCKS, asTRUE));
	EXPECT_FALSE(astyle.AStyleIFace::GetBreakOneLineBlocks());
	// default is true
	EXPECT_TRUE(astyle.AStyleIFace::GetBreakOneLineStmts());
	EXPECT_TRUE(astyle.SetAStyleOption(KEEP_ONE_LINE_STATEMENTS, asTRUE));
	EXPECT_FALSE(astyle.AStyleIFace::GetBreakOneLineStmts());
	// end default is true
	EXPECT_TRUE(astyle.SetAStyleOption(CONVERT_TABS, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetConvertTabs());
	EXPECT_TRUE(astyle.SetAStyleOption(BREAK_AFTER_LOGICAL, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetBreakAfterLogical());
	// other
	EXPECT_TRUE(astyle.SetAStyleOption(PAD_METHOD_PREFIX, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetPadMethodPrefix());
	EXPECT_TRUE(astyle.SetAStyleOption(UNPAD_METHOD_PREFIX, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetUnpadMethodPrefix());
	EXPECT_TRUE(astyle.SetAStyleOption(PAD_RETURN_TYPE, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetPadReturnType());
	EXPECT_TRUE(astyle.SetAStyleOption(UNPAD_RETURN_TYPE, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetUnpadReturnType());
	EXPECT_TRUE(astyle.SetAStyleOption(ALIGN_METHOD_COLON, asTRUE));
	EXPECT_TRUE(astyle.AStyleIFace::GetAlignMethodColon());
}

TEST(AStyleIFace_Config, SetAStyleOptionBreakBlocks)
// Test AStyleIFace::SetAStyleOption breakBlocks options
{
	// create objects
	AStyleIFace astyle;

	// test for error
	EXPECT_FALSE(astyle.SetAStyleOption(BREAK_BLOCKS, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOption(BREAK_BLOCKS, asFALSE));
	// test the value
	EXPECT_TRUE(astyle.SetAStyleOption(BREAK_BLOCKS, "open"));
	EXPECT_TRUE(astyle.AStyleIFace::GetBreakHeaderBlocks()) << "Failure for break-blocks";
	EXPECT_FALSE(astyle.AStyleIFace::GetBreakClosingBlocks()) << "Failure for break-blocks";
	EXPECT_TRUE(astyle.SetAStyleOption(BREAK_BLOCKS, "all"));
	EXPECT_TRUE(astyle.AStyleIFace::GetBreakHeaderBlocks()) << "Failure for break-blocks=all";
	EXPECT_TRUE(astyle.AStyleIFace::GetBreakClosingBlocks()) << "Failure for break-blocks=all";
}

TEST(AStyleIFace_Config, SetAStyleOptionContinuationIndent)
// Test AStyleIFace::SetAStyleOption continuationIndent option
{
	// create objects
	AStyleIFace astyle;

	// test the continuation indent for error
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_CONTINUATION, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_CONTINUATION, "-1"));
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_CONTINUATION, "5"));
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_CONTINUATION, "X"));
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_CONTINUATION, wxEmptyString));
	// test the continuation indent
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_CONTINUATION, "2"));
	EXPECT_EQ(2, astyle.AStyleIFace::GetContinuationIndent());
}

TEST(AStyleIFace_Config, SetAStyleOptionIndent)
// Test AStyleIFace::SetAStyleOption indent options
{
	// create objects
	AStyleIFace astyle;

	// test the indent-type for error
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_TYPE, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_TYPE, asFALSE));

	// test the indent-length for error
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_LENGTH, "-1"));
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_LENGTH, "0"));
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_LENGTH, "21"));
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_LENGTH, " "));
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_LENGTH, "="));
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_LENGTH, "tab"));
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_LENGTH, "X"));
	EXPECT_FALSE(astyle.SetAStyleOption(INDENT_LENGTH, wxEmptyString));

	// test the indent-type valid values
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_TYPE, INDENT_TYPE_SPACES));
	EXPECT_EQ(INDENT_SPACES, astyle.AStyleIFace::GetIndentType());
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_TYPE, INDENT_TYPE_TAB));
	EXPECT_EQ(INDENT_TABS, astyle.AStyleIFace::GetIndentType());
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_TYPE, INDENT_TYPE_FTAB));
	EXPECT_EQ(INDENT_FTABS, astyle.AStyleIFace::GetIndentType());

	// test the indent-length valid values
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_LENGTH, "2"));
	EXPECT_EQ(2, astyle.AStyleIFace::GetIndentLength());
	EXPECT_TRUE(astyle.SetAStyleOption(INDENT_LENGTH, "20"));
	EXPECT_EQ(20, astyle.AStyleIFace::GetIndentLength());
}

TEST(AStyleIFace_Config, SetAStyleOptionMaxCodeLength)
// Test AStyleIFace::SetAStyleOption maxCodeLength option
{
	// create objects
	AStyleIFace astyle;

	// test the max code length for error
	EXPECT_FALSE(astyle.SetAStyleOption(MAX_CODE_LENGTH, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOption(MAX_CODE_LENGTH, "-1"));
	EXPECT_FALSE(astyle.SetAStyleOption(MAX_CODE_LENGTH, "49"));
	EXPECT_FALSE(astyle.SetAStyleOption(MAX_CODE_LENGTH, "201"));
	EXPECT_FALSE(astyle.SetAStyleOption(MAX_CODE_LENGTH, "X"));
	EXPECT_FALSE(astyle.SetAStyleOption(MAX_CODE_LENGTH, wxEmptyString));
	// test the indent length
	EXPECT_TRUE(astyle.SetAStyleOption(MAX_CODE_LENGTH, "100"));
	EXPECT_EQ(100, astyle.AStyleIFace::GetMaxCodeLength());
}

TEST(AStyleIFace_Config, SetAStyleOptionMaxInStatement)
// Test AStyleIFace::SetAStyleOption maxInStatementIndent option
{
	// create objects
	AStyleIFace astyle;

	// test the indent length for error
	EXPECT_FALSE(astyle.SetAStyleOption(MAX_CONTINUATION_INDENT, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOption(MAX_CONTINUATION_INDENT, "-1"));
	EXPECT_FALSE(astyle.SetAStyleOption(MAX_CONTINUATION_INDENT, "39"));
	EXPECT_FALSE(astyle.SetAStyleOption(MAX_CONTINUATION_INDENT, "121"));
	EXPECT_FALSE(astyle.SetAStyleOption(MAX_CONTINUATION_INDENT, "X"));
	EXPECT_FALSE(astyle.SetAStyleOption(MAX_CONTINUATION_INDENT, wxEmptyString));
	// test the indent length
	EXPECT_TRUE(astyle.SetAStyleOption(MAX_CONTINUATION_INDENT, "50"));
	EXPECT_EQ(50, astyle.AStyleIFace::GetMaxContinuationIndent());
}

TEST(AStyleIFace_Config, SetAStyleOptionMinConditional)
// Test AStyleIFace::SetAStyleOption minConditionalOption option
{
	// create objects
	AStyleIFace astyle;

	// test the option for error
	EXPECT_FALSE(astyle.SetAStyleOption(MIN_CONDITIONAL_INDENT, asTRUE));
	EXPECT_FALSE(astyle.SetAStyleOption(MIN_CONDITIONAL_INDENT, "-1"));
	EXPECT_FALSE(astyle.SetAStyleOption(MIN_CONDITIONAL_INDENT, "4"));
	EXPECT_FALSE(astyle.SetAStyleOption(MIN_CONDITIONAL_INDENT, "X"));
	EXPECT_FALSE(astyle.SetAStyleOption(MIN_CONDITIONAL_INDENT, wxEmptyString));
	// test the option
	EXPECT_TRUE(astyle.SetAStyleOption(MIN_CONDITIONAL_INDENT, "0"));
	EXPECT_EQ(MINCOND_ZERO, astyle.AStyleIFace::GetMinConditionalOption());
	EXPECT_TRUE(astyle.SetAStyleOption(MIN_CONDITIONAL_INDENT, "1"));
	EXPECT_EQ(MINCOND_ONE, astyle.AStyleIFace::GetMinConditionalOption());
	EXPECT_TRUE(astyle.SetAStyleOption(MIN_CONDITIONAL_INDENT, "2"));	// this is the default
	EXPECT_EQ(MINCOND_TWO, astyle.AStyleIFace::GetMinConditionalOption());
	EXPECT_TRUE(astyle.SetAStyleOption(MIN_CONDITIONAL_INDENT, "3"));
	EXPECT_EQ(MINCOND_ONEHALF, astyle.AStyleIFace::GetMinConditionalOption());
}

TEST(AStyleIFace_Config, SetAStyleOptionPadMethodColon)
// Test AStyleIFace::SetAStyleOption padMethodColon option
{
	// create objects
	AStyleIFace astyle;

	// test the option for error
	EXPECT_FALSE(astyle.SetAStyleOption(PAD_METHOD_COLON, asTRUE));
	EXPECT_EQ(COLON_PAD_NO_CHANGE, astyle.AStyleIFace::GetPadMethodColon());
	EXPECT_FALSE(astyle.SetAStyleOption(PAD_METHOD_COLON, "non"));
	EXPECT_EQ(COLON_PAD_NO_CHANGE, astyle.AStyleIFace::GetPadMethodColon());
	EXPECT_FALSE(astyle.SetAStyleOption(PAD_METHOD_COLON, "allx"));
	EXPECT_EQ(COLON_PAD_NO_CHANGE, astyle.AStyleIFace::GetPadMethodColon());
	EXPECT_FALSE(astyle.SetAStyleOption(PAD_METHOD_COLON, wxEmptyString));
	EXPECT_EQ(COLON_PAD_NO_CHANGE, astyle.AStyleIFace::GetPadMethodColon());
	// test the option
	EXPECT_TRUE(astyle.SetAStyleOption(PAD_METHOD_COLON, "none"));
	EXPECT_EQ(COLON_PAD_NONE, astyle.AStyleIFace::GetPadMethodColon());
	EXPECT_TRUE(astyle.SetAStyleOption(PAD_METHOD_COLON, "all"));
	EXPECT_EQ(COLON_PAD_ALL, astyle.AStyleIFace::GetPadMethodColon());
	EXPECT_TRUE(astyle.SetAStyleOption(PAD_METHOD_COLON, "after"));	// this is the default
	EXPECT_EQ(COLON_PAD_AFTER, astyle.AStyleIFace::GetPadMethodColon());
	EXPECT_TRUE(astyle.SetAStyleOption(PAD_METHOD_COLON, "before"));
	EXPECT_EQ(COLON_PAD_BEFORE, astyle.AStyleIFace::GetPadMethodColon());
}

TEST(AStyleIFace_Config, SetAStyleOptionPadParens)
// Test AStyleIFace::SetAStyleOption padParens options
{
	// create objects
	AStyleIFace astyle;

	// test for error
	EXPECT_FALSE(astyle.SetAStyleOption(PAD_PAREN, "error-test"));
	EXPECT_FALSE(astyle.SetAStyleOption(PAD_PAREN, asTRUE));
	// test the value
	// test the pad-paren-out
	EXPECT_TRUE(astyle.SetAStyleOption(PAD_PAREN, "out"));
	EXPECT_TRUE(astyle.AStyleIFace::GetPadParenOutside()) << "Failure for pad-paren-out";
	EXPECT_FALSE(astyle.AStyleIFace::GetPadParenInside()) << "Failure for pad-paren-out";
	// test the pad-paren-in
	EXPECT_TRUE(astyle.SetAStyleOption(PAD_PAREN, "in"));
	EXPECT_FALSE(astyle.AStyleIFace::GetPadParenOutside()) << "Failure for pad-paren-in";
	EXPECT_TRUE(astyle.AStyleIFace::GetPadParenInside()) << "Failure for pad-paren-in";
	// test the pad-paren
	EXPECT_TRUE(astyle.SetAStyleOption(PAD_PAREN, "all"));
	EXPECT_TRUE(astyle.AStyleIFace::GetPadParenOutside()) << "Failure for pad-paren";
	EXPECT_TRUE(astyle.AStyleIFace::GetPadParenInside()) << "Failure for pad-paren";
}

TEST(AStyleIFace_Config, SetAStyleOptionStyles)
// Test AStyleIFace::SetAStyleOption for style options
{
	// create objects
	AStyleIFace astyle;

	// test for error
	EXPECT_FALSE(astyle.SetAStyleOption(STYLE, "error-test"));
	EXPECT_FALSE(astyle.SetAStyleOption(STYLE, asTRUE));
	// test the styles
	EXPECT_TRUE(astyle.SetAStyleOption(STYLE, ALLMAN));
	EXPECT_EQ(STYLE_ALLMAN, astyle.AStyleIFace::GetBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOption(STYLE, JAVA));
	EXPECT_EQ(STYLE_JAVA, astyle.AStyleIFace::GetBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOption(STYLE, KandR));
	EXPECT_EQ(STYLE_KR, astyle.AStyleIFace::GetBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOption(STYLE, STROUSTRUP));
	EXPECT_EQ(STYLE_STROUSTRUP, astyle.AStyleIFace::GetBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOption(STYLE, WHITESMITH));
	EXPECT_EQ(STYLE_WHITESMITH, astyle.AStyleIFace::GetBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOption(STYLE, RATLIFF));
	EXPECT_EQ(STYLE_RATLIFF, astyle.AStyleIFace::GetBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOption(STYLE, GNU));
	EXPECT_EQ(STYLE_GNU, astyle.AStyleIFace::GetBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOption(STYLE, LINUXX));
	EXPECT_EQ(STYLE_LINUX, astyle.AStyleIFace::GetBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOption(STYLE, HORSTMANN));
	EXPECT_EQ(STYLE_HORSTMANN, astyle.AStyleIFace::GetBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOption(STYLE, oneTBS));
	EXPECT_EQ(STYLE_1TBS, astyle.AStyleIFace::GetBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOption(STYLE, GOOGLE));
	EXPECT_EQ(STYLE_GOOGLE, astyle.AStyleIFace::GetBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOption(STYLE, MOZILLA));
	EXPECT_EQ(STYLE_MOZILLA, astyle.AStyleIFace::GetBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOption(STYLE, WEBKIT));
	EXPECT_EQ(STYLE_WEBKIT, astyle.AStyleIFace::GetBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOption(STYLE, PICO));
	EXPECT_EQ(STYLE_PICO, astyle.AStyleIFace::GetBraceStyle());
	EXPECT_TRUE(astyle.SetAStyleOption(STYLE, LISP));
	EXPECT_EQ(STYLE_LISP, astyle.AStyleIFace::GetBraceStyle());
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
