//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleTest.h"

//----------------------------------------------------------------------------
// AStyle version 1.25 TEST functions
//----------------------------------------------------------------------------

TEST(v125_DeleteEmptyLines_BreakBlocks)
{
	// a missing closing bracket with delete-empty-lines and break-blocks
	// should not cause an assert error on the call to sourceIterator->peekNextLine()
	// in the function ASFormatter::commentAndHeaderFollows()
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar()\n"
		"    {\n"
		"\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar()\n"
		"    {\n"
		"    }";      // no end-of-line will be output
	char options[] = "delete-empty-lines, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_BreakBlocks_DeleteEmptyLines_Comment)
{
	// the following comment should not abort or duplicate code in the output
	// both break-blocks and delete-empty-lines must be used
	// problem is the beginning comments in the peekNextText() function
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"\n"
		"/*//BEGIN debug\n"
		"    kdDebug() << endl << endl;\n"
		"//END debug*/\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"    /*//BEGIN debug\n"
		"        kdDebug() << endl << endl;\n"
		"    //END debug*/\n"
		"}\n";
	char options[] = "break-blocks, delete-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_SharpLambdaOperatorIndent)
{
	// C# => is not an assignment operator
	// following lines should not be aligned on the =>
	char textIn[] =
		"\npublic static bool Foo()\n"
		"{\n"
		"    return @class.Attributes(\n"
		"               att =>\n"
		"                    att.AttributeType() &&\n"
		"                    att.PositionalArg == 2 &&\n"
		"                    String.Equals(\"System\")\n"
		"           );\n"
		"}\n";
	char text[] =
		"\npublic static bool Foo()\n"
		"{\n"
		"    return @class.Attributes(\n"
		"               att =>\n"
		"               att.AttributeType() &&\n"
		"               att.PositionalArg == 2 &&\n"
		"               String.Equals(\"System\")\n"
		"           );\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_KeywordsNotHeaders)
{
	// header is not a keyword if part of a definition
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    ADD_KEYWORD(return, TK_RETURN);\n"
		"    ADD_KEYWORD(switch, TK_SWITCH);\n"
		"    ADD_KEYWORD(case,   TK_CASE);\n"
		"    ADD_KEYWORD(default,TK_DEFAULT);\n"
		"}\n";
	char options[] = "pad-header";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_TwoGreaterSymblolsClosingTemplate)
{
	// two >> symbols closing a template
	char text[] =
		"\npublic Foo<KeyValuePair<string, string>> SpecialTypes {\n"
		"    get {\n"
		"        return typeConversionTable;\n"
		"    }\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_PossibleAssignmentInStatementIndentWithParenLineBegin)
{
	// a paren begins a line with an in-statement indent
	char text[] =
		"\nprivate void foo()\n"
		"{\n"
		"    search(\n"
		"        () => DoSearch(Select(i => i.Node).ToList()),\n"
		"        result => SearchCompleted(result),\n"
		"    );\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_Col1ElseWithPreceedingBracket)
{
	// else in col 1 with preceeding bracket tests a seldom used branch
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(isFoo)\n"
		"    {\n"
		"        bar1();\n"
		"    }\n"
		"else    // comment\n"
		"        bar2();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(isFoo)\n"
		"    {\n"
		"        bar1();\n"
		"    }\n"
		"    else    // comment\n"
		"        bar2();\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_TryCatchInHeader)
{
	// try-catch within a header
	// header must be restored from lastTempStack in ASBeautifier
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (foo1)\n"
		"        bar1;\n"
		"    else\n"
		"        try {\n"
		"            bar();\n"
		"        } catch (int e) {\n"
		"            cerr << \"error\" << endl;\n"
		"        }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_TryCatchFinallyInHeader)
{
	// try-catch within a header
	// header must be restored from lastTempStack in ASBeautifier
	char text[] =
		"\nprivate void foo()\n"
		"{\n"
		"    if (foo1)\n"
		"        bar1;\n"
		"    else\n"
		"        try {\n"
		"            bar();\n"
		"        } catch (int e) {\n"
		"            Console.WriteLine(\"error\");\n"
		"        } finally (int e) {\n"
		"            closefile();\n"
		"        }\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_DoWhileInHeader)
{
	// do-while within a header
	// header must be restored from lastTempStack in ASBeautifier
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (foo1)\n"
		"        bar1;\n"
		"    else\n"
		"        do {\n"
		"            bar();\n"
		"        } while (int x < 9);\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_TemplateASBeautifier)
{
	// template on multiple lines should be recognized by ASBeautifier
	// template within a template should be recognized by ASBeautifier
	char text[] =
		"\ntemplate<typename T, template<typename E,\n"
		"         typename Allocator = allocator<E> >\n"
		"         class Container = vector >\n"
		"class Foo\n"
		"{\n"
		"};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_ExtraClosingBrackets)
{
	// should not abort with extra closing brackets
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        int bar = 1;\n"
		"    }\n"
		"}\n"
		"}\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_ExtraClosingParens)
{
	// should not abort with extra closing parens
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo))))\n"
		"    {\n"
		"        bar()));\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_ExtraClosingBlockParens)
{
	// should not abort with extra closing block parens
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo))))\n"
		"    {\n"
		"        fooBar = bar[2]]];\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_DefinitionsNotHeaders)
{
	// definitions are not headers
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    ADD_KEYWORD ( if, TK_IF );\n"
		"    ADD_KEYWORD ( while, TK_WHILE );\n"
		"    ADD_KEYWORD ( else );\n"
		"    ADD_KEYWORD ( for );\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_SharpPeekNextTextMultiLineComment)
{
	// test C# peekNextText() with multi-ine comment before the text
	char text[] =
		"\npublic interface FooInterface {\n"
		"    int FooGet {\n"
		"        /* comment\n"
		"           comment */\n"
		"        get;\n"
		"        set;\n"
		"    }\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_SharpNotPotentialHeader)
{
	// test C# isNextWordSharpNonParenHeader() for !isCharPotentialHeader()
	char text[] =
		"\nprivate void foo()\n"
		"{\n"
		"    string[] lines = text.Split(new char[] {'.'});\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_EmptyLineComment)
{
	// test recognition of an empty line comment
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    //\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v125_ColZeroPointerOrReference)
{
	// test pointer or reference in column zero
	char textIn[] =
		"\nvoid foo(char *foo1, char\n"
		"*foo2, char *foo3)\n"
		"{\n"
		"    bar();\n"
		"}\n"
		"\n"
		"void foo(char &foo1, char\n"
		"&foo2, char &foo3)\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char text[] =
		"\nvoid foo(char *foo1, char\n"
		"         *foo2, char *foo3)\n"
		"{\n"
		"    bar();\n"
		"}\n"
		"\n"
		"void foo(char &foo1, char\n"
		"         &foo2, char &foo3)\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle version 1.24 TEST functions
//----------------------------------------------------------------------------

TEST(v124_AddBracketsHorstmannNestedIfStatements)
{
	// add on line brackets to nested "if" statements
	// with keep one line brackets
	// should not break the statement (a variable was not reset)
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isBar1)\n"
		"        if (isBar2) return true;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{   if (isBar1)\n"
		"        if (isBar2) { return true; }\n"
		"}\n";
	char options[] = "add-brackets, brackets=horstmann, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_ClassHorstmannComment)
{
	// handle special case of horstmann comment in a class statement
	char text[] =
		"\nclass Foo\n"
		"{   /*enum ResolutionFlags {\n"
		"           NoFlag = 0,\n"
		"           HadTypedef = 1,\n"
		"           HadAlias = 2\n"
		"         };*/\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_ClassIndentHorstmannComment)
{
	// handle special case of horstmann comment in an indented class statement
	char text[] =
		"\nclass Foo\n"
		"{   /*enum ResolutionFlags {\n"
		"           NoFlag = 0,\n"
		"           HadTypedef = 1,\n"
		"           HadAlias = 2\n"
		"         };*/\n"
		"}\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_AppendAttachedBracketInsideCommentsLineBreak)
{
	// should not insert an empty line after appending a bracket inside comments
	char textIn[] =
		"\nvoid foo()\n"
		"{   switch(req) {\n"
		"    case REQ_if:   // groff(7) \"IF\"\n"
		"    {   /* .if c anything\n"
		"         * .if N anything\n"
		"         */\n"
		"        c = c + j;\n"
		"        break;\n"
		"    }\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo() {\n"
		"    switch(req) {\n"
		"    case REQ_if: { // groff(7) \"IF\"\n"
		"        /* .if c anything\n"
		"         * .if N anything\n"
		"         */\n"
		"        c = c + j;\n"
		"        break;\n"
		"    }\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_ElseAttachedToLineComment)
{
	// else should not be attached to a line coment
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if ( x == 'G')\n"
		"        y = 1;\n"
		"    else\n"
		"//  if ( x == 'W')\n"
		"//      y= 3;\n"
		"//  else\n"
		"        if ( x == 'H')\n"
		"            y = 4;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BreakOneLineBlocks_Comment1)
{
	// comment should be moved to the previous line
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"    { bar(); } // comment\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        bar();    // comment\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BreakOneLineBlocks_Comment2)
{
	// comment should be moved to the previous line
	// option keep-one-line-statements is used
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"    { bar(); } // comment\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        bar();    // comment\n"
		"    }\n"
		"}\n";
	char options[] = "keep-one-line-statements";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_SharpDelegate)
{
	// sharp 'delegate' should be recognized as a keyword
	// the Linux brackets should be attached
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    delegate {\n"
		"        if (isFoo)\n"
		"        {\n"
		"            bar();\n"
		"        }\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    delegate {\n"
		"        if (isFoo) {\n"
		"            bar();\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=linux, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_JavaInStatement_LineCommentClear)
{
	// isNonInStatementArray should be cleared when a // follows a }
	// if not cleared the "? ERROR" line will not be correctly indented
	char text[] =
		"\npublic enum KeyboardCommand\n"
		"{\n"
		"    TAB_OUT_FORWARD,\n"
		"    TAB_OUT_BACK\n"
		"} // this comment\n"
		"\n"
		"static class Entry\n"
		"{\n"
		"    Entry(PluginJAR jar)\n"
		"    {\n"
		"        if (plugin != null)\n"
		"        {\n"
		"            status = plugin instanceof EditPlugin.Broken\n"
		"                     ? ERROR : LOADED;\n"
		"            clazz = plugin.getClassName();\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_JavaInStatement_CommentClear)
{
	// isNonInStatementArray should be cleared when a /* follows a }
	// if not cleared the "? ERROR" line will not be correctly indented
	char text[] =
		"\npublic enum KeyboardCommand\n"
		"{\n"
		"    TAB_OUT_FORWARD,\n"
		"    TAB_OUT_BACK\n"
		"} /* this comment */\n"
		"\n"
		"static class Entry\n"
		"{\n"
		"    Entry(PluginJAR jar)\n"
		"    {\n"
		"        if (plugin != null)\n"
		"        {\n"
		"            status = plugin instanceof EditPlugin.Broken\n"
		"                     ? ERROR : LOADED;\n"
		"            clazz = plugin.getClassName();\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_SharpAccessors)
{
	// get is preceded by []
	char text[] =
		"\npublic static MyApplication Application\n"
		"{\n"
		"    [DebuggerStepThrough]\n"
		"    get\n"
		"    {\n"
		"        if (isBar)\n"
		"            bar();\n"
		"        return application;\n"
		"    }\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_SharpNonParenHeader_Unchecked)
{
	// 'unchecked' should be recognized as a header, not an array
	char text[] =
		"\npublic override void foo()\n"
		"{\n"
		"    unchecked {\n"
		"        if (isBar)\n"
		"            bar += 1;\n"
		"    }\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_SharpNonParenHeader_Delegate)
{
	// 'delegate' should be recognized as a header, not an array
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    int fooBar = delegate {\n"
		"        if (isBar1) {\n"
		"            bar = 1;\n"
		"        } else if (isBar2) {\n"
		"            bar = 2;\n"
		"        } else if (isBar3) {\n"
		"            bar = 3;\n"
		"        }\n"
		"    };\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_PadCommentBeforeTab)
{
	// space padding the bracket should NOT pad a comment
	//     when the commet is preceeded by a tab
	//     but should delete a space when preceded spaces
	char textIn[] =
		"\nvoid foo() {\n"
		"    if (isBar1){	// comment\n"
		"        bar1();\n"
		"    }\n"
		"    if (isBar2){   // comment\n"
		"        bar2();\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo() {\n"
		"    if (isBar1) {	// comment\n"
		"        bar1();\n"
		"    }\n"
		"    if (isBar2) {  // comment\n"
		"        bar2();\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsBreak_PadParen)
{
	// break attached brackets with pad-paren
	// comments should be moved with one padded space
	char textIn[] =
		"\nvoid foo() { // comment0\n"
		"    if ((isFoo())) { // comment1\n"
		"        bar1();\n"
		"        bar2(fooBar); // comment2\n"
		"    }\n"
		"}\n"
		"\n"
		"void foo2(){// comment0\n"
		"    if ((isFoo())){// comment1\n"
		"        bar1();\n"
		"        bar2(fooBar);// comment2\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()   // comment0\n"
		"{\n"
		"    if ( ( isFoo() ) ) // comment1\n"
		"    {\n"
		"        bar1();\n"
		"        bar2 ( fooBar ); // comment2\n"
		"    }\n"
		"}\n"
		"\n"
		"void foo2() // comment0\n"
		"{\n"
		"    if ( ( isFoo() ) ) // comment1\n"
		"    {\n"
		"        bar1();\n"
		"        bar2 ( fooBar ); // comment2\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=break, pad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsAttach_CommentsMisc1)
{
	// attach bracket inside a line end comment
	// when multi-line comments follow a horstmann bracket
	char textIn[] =
		"\nvoid foo2(bool isFoo) /* comment0 */\n"
		"{   /* comment1\n"
		"     *\n"
		"     */\n"
		"    if(isFoo) /* comment2 */\n"
		"    {   /* comment3\n"
		"         *\n"
		"         */\n"
		"        bar();\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo2(bool isFoo) { /* comment0 */\n"
		"    /* comment1\n"
		"     *\n"
		"     */\n"
		"    if(isFoo) { /* comment2 */\n"
		"        /* comment3\n"
		"         *\n"
		"         */\n"
		"        bar();\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsAttach_CommentMisc2)
{
	// do NOT attach bracket inside a line end comment
	// when two comments are on the line
	char text[] =
		"\nvoid foo() {\n"
		"    if (isBar())   /* comment0 */ // comment0line\n"
		"    {\n"
		"        bar();\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=attach";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsAttach_CommentMisc3)
{
	// when a bracket is NOT attached
	// following horstmann comments should be broken and correctly formatted
	char textIn[] =
		"\nvoid foo() {\n"
		"    if (isBar())   /* comment0 */ // comment0line\n"
		"    {   /*\n"
		"         * comment1\n"
		"         */\n"
		"        bar();\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo() {\n"
		"    if (isBar())   /* comment0 */ // comment0line\n"
		"    {\n"
		"        /*\n"
		"         * comment1\n"
		"         */\n"
		"        bar();\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsAttach_CommentMisc4)
{
	// attached brackets with following comments
	// the second comment should be correctly formatted
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        // comment1\n"
		"        {\n"
		"            bar1();\n"
		"        }\n"
		"        /*else\n"
		"        {\n"
		"            bar2();\n"
		"        }*/\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo() {\n"
		"    if (isFoo) {\n"
		"        // comment1\n"
		"        {\n"
		"            bar1();\n"
		"        }\n"
		"        /*else\n"
		"        {\n"
		"            bar2();\n"
		"        }*/\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_Tabs)
{
	// test horstmann brackets with tab indents
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"    {\n"
		"        bar();\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{	if (isFoo())\n"
		"	{	bar();\n"
		"	}\n"
		"}\n";
	char options[] = "brackets=horstmann, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_Array1)
{
	// test horstmann brackets with single line array
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    wxChar name[MAX_PATH] = {0};\n"
		"    bar();\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{   wxChar name[MAX_PATH] = {0};\n"
		"    bar();\n"
		"}\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_Array2)
{
	// test horstmann brackets with structs and arrays
	char textIn[] =
		"\nstruct runinClass2\n"
		"{\n"
		"    bool bar;\n"
		"};\n"
		"\n"
		"const char *contributors[] =\n"
		"{\n"
		"    \"Bugs\",\n"
		"    \"Daffy\",\n"
		"};\n";
	char text[] =
		"\nstruct runinClass2\n"
		"{   bool bar;\n"
		"};\n"
		"\n"
		"const char *contributors[] =\n"
		"{   \"Bugs\",\n"
		"    \"Daffy\",\n"
		"};\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_Spaces1)
{
	// test horstmann brackets with extra spaces
	// extra spaces should be deleted
	char textIn[] =
		"\nvoid Foo()\n"
		"{     if (isFoo())\n"
		"      {     bar();\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{   if (isFoo())\n"
		"    {   bar();\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_Spaces2)
{
	// test multiple horstmann brackets runs
	// extra spaces should not be added on subsequent runs
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"    {\n"
		"        bar();\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{   if (isFoo())\n"
		"    {   bar();\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=horstmann";
	char* textOne = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	char* textOut = AStyleMain(textOne, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOne;
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_Preprocessor)
{
	// test horstmann brackets with preprocessor
	// preprocessor should NOT be attached
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"#ifdef xxx\n"
		"    bar1();\n"
		"#else\n"
		"    bar2();\n"
		"#endif\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"#ifdef xxx\n"
		"    bar1();\n"
		"#else\n"
		"    bar2();\n"
		"#endif\n"
		"}\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_EmptyLine)
{
	// test horstmann brackets with following empty line
	// empty line should NOT be deleted
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"\n"
		"    if (isFoo())\n"
		"        bar();\n"
		"}\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_Comment1)
{
	// test horstmann brackets with following comment
	// second comment should NOT be attached to the first
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    // comment1\n"
		"    // comment2\n"
		"    if (isFoo())\n"
		"        bar();\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{   // comment1\n"
		"    // comment2\n"
		"    if (isFoo())\n"
		"        bar();\n"
		"}\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_Comment2)
{
	// test horstmann brackets with following comment in column 1
	// the comment should NOT be attached
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"// comment1 does not attach\n"
		"// comment2\n"
		"    if (isFoo())\n"
		"        bar();\n"
		"}\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_Comment3)
{
	// test horstmann brackets with following comment
	// the comment should NOT be attached to the previous line
	char text[] =
		"\nvoid foo()\n"
		"{   foo1();\n"
		"    /* comment */\n"
		"}\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_Comment4)
{
	// test horstmann brackets with following comment
	// the comment should NOT be attached to the previous line
	char text[] =
		"\nvoid foo()\n"
		"{   // comment1\n"
		"    /*comment2*/\n"
		"}\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_Comment5)
{
	// test horstmann brackets with following comment
	// the comment on unattached lines should be correctly indented
	char textIn[] =
		"\nnamespace fooName\n"
		"{\n"
		"    /**\n"
		"     * comment1\n"
		"     */\n"
		"    class fooClass\n"
		"    {\n"
		"        /**\n"
		"         * comment1\n"
		"         */\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nnamespace fooName\n"
		"{\n"
		"/**\n"
		" * comment1\n"
		" */\n"
		"class fooClass\n"
		"{   /**\n"
		"     * comment1\n"
		"     */\n"
		"}\n"
		"}\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_Comment6)
{
	// test horstmann brackets with following comment
	// the comment on unattached lines should be correctly indented
	char textIn[] =
		"\nnamespace fooName\n"
		"{\n"
		"    /**\n"
		"     * comment1\n"
		"     */\n"
		"    class fooClass\n"
		"    {\n"
		"        /**\n"
		"         * comment1\n"
		"         */\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nnamespace fooName\n"
		"{\n"
		"    /**\n"
		"     * comment1\n"
		"     */\n"
		"    class fooClass\n"
		"    {   /**\n"
		"         * comment1\n"
		"         */\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=horstmann, indent-namespaces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_Comment7)
{
	// test horstmann brackets with comment following line comment
	// the comment should NOT be attached to the previous line
	char textIn[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        // comment\n"
		"/* FIXME comment in column 1 */\n"
		"        bar();\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo(bool isFoo)\n"
		"{   if (isFoo)\n"
		"    {   // comment\n"
		"        /* FIXME comment in column 1 */\n"
		"        bar();\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_BreakAllBlocks1)
{
	// test horstmann brackets with break all blocks
	// the blocks should be correctly broken
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar1();\n"
		"    if (isBar)  // comment\n"
		"    {\n"
		"        bar2();\n"
		"        return;\n"
		"    }\n"
		"    else\n"
		"    {\n"
		"        bar3();\n"
		"    }\n"
		"    bar4();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{   bar1();\n"
		"\n"
		"    if (isBar)  // comment\n"
		"    {   bar2();\n"
		"        return;\n"
		"    }\n"
		"\n"
		"    else\n"
		"    {   bar3();\n"
		"    }\n"
		"\n"
		"    bar4();\n"
		"}\n";
	char options[] = "brackets=horstmann, break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_BreakAllBlocks2)
{
	// test horstmann brackets with break all blocks and delete empty lines
	// and comments separated by an empty line
	// the empty line should NOT be deleted
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    // comment1\n"
		"\n"
		"    // comment2\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{   // comment1\n"
		"\n"
		"    // comment2\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"}\n";
	char options[] = "brackets=horstmann, break-blocks=all, delete-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_UnpadParen1)
{
	// test horstmann brackets with unpad parens
	// the indent should NOT be removed
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if ( isBar )\n"
		"    {\n"
		"        ( *_err ) << endl; // comment1\n"
		"        ( *_err ) << arg;  // comment2\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{   if(isBar)\n"
		"    {   (*_err) << endl;   // comment1\n"
		"        (*_err) << arg;    // comment2\n"
		"    }\n"
		"}\n";
	char options[] = ", brackets=horstmann, unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_UnpadParen2)
{
	// test horstmann brackets with unpad parens and pad-parens
	// the indent should NOT be removed
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isBar)\n"
		"    {\n"
		"        (*_err) << endl; // comment1\n"
		"        (*_err) << arg;  // comment2\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{   if ( isBar )\n"
		"    {   ( *_err ) << endl; // comment1\n"
		"        ( *_err ) << arg; // comment2\n"
		"    }\n"
		"}\n";
	char options[] = ", brackets=horstmann, unpad-paren, pad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_UnpadParen3)
{
	// test horstmann brackets with unpad parens and pad-parens
	//	and tab indents
	// the indent should NOT be removed
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isBar)\n"
		"    {\n"
		"        (*_err) << endl; // comment1\n"
		"        (*_err) << arg;  // comment2\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{	if ( isBar )\n"
		"	{	( *_err ) << endl; // comment1\n"
		"		( *_err ) << arg; // comment2\n"
		"	}\n"
		"}\n";
	char options[] = ", brackets=horstmann, unpad-paren, pad-paren, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_SingleLineBlock1)
{
	// test horstmann brackets with single line block
	char textIn[] =
		"\nvoid foo()\n"
		"{ bar1(); bar2() }\n";
	char text[] =
		"\nvoid foo()\n"
		"{   bar1();\n"
		"    bar2()\n"
		"}\n";
	char options[] = ", brackets=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v124_BracketsHorstmann_SingleLineBlock2)
{
	// test horstmann brackets with single line block
	char text[] =
		"\nvoid foo()\n"
		"{ bar1(); bar2() }\n";
	char options[] = ", brackets=horstmann, keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle version 1.23 TEST functions
//----------------------------------------------------------------------------

TEST(v123_ExternIndent)
{
	// no extra indent when extern is used
	char text[] =
		"\nextern void foo (bool bar2,\n"
		"                 bool bar2);\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_StructBitIndent)
{
	// do not break line when struct bit declaration is used
	// lines following struct should have correct indent
	char text[] =
		"\nstruct A {\n"
		"    int a:1;\n"
		"};\n"
		"\n"
		"struct X {\n"
		"    field x : 1;\n"
		"    field y : 2;\n"
		"};\n"
		"\n"
		"typedef union _USB_DEVICE_STATUS\n"
		"{\n"
		"    byte _byte;\n"
		"    struct\n"
		"    {\n"
		"        unsigned RemoteWakeup:1;\n"
		"        unsigned ctrl_trf_mem:1;\n"
		"    };\n"
		"} USB_DEVICE_STATUS;\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_ClassBitIndent)
{
	// do not break line when struct bit declaration is used
	// lines following class should have correct indent
	char text[] =
		"\nclass MainWindow\n"
		"{\n"
		"public:\n"
		"    bool inDebugMode;\n"
		"    uint guiStuffVisible : 1;\n"
		"    uint editorsReadOnly : 1;\n"
		"    uint savePluginPaths : 1;\n"
		"    bool shStartDialog;\n"
		"};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_RegionIndent)
{
	// no extra indent after a C# #region statement containing a keyword
	char text[] =
		"\npublic interface IDocument\n"
		"{\n"
		"    #region ILineManager interface\n"
		"    /// <value>\n"
		"    /// A collection of all line segments\n"
		"    #endregion\n"
		"\n"
		"    #region Nested enumerator class\n"
		"    private sealed class Enumerator : IEnumerator, IPluginCollectionEnumerator\n"
		"    {\n"
		"        private readonly PluginCollection m_collection;\n"
		"    }\n"
		"    #endregion\n"
		"}\n"
		"\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_StructIndent)
{
	// no extra indent when struct declaration is used
	char text[] =
		"\nstruct foo* bar (void) {\n"
		"}\n"
		"\n"
		"struct foo* bar\n"
		"(void)\n"
		"{\n"
		"}\n"
		"\n"
		"struct axt *chainToAxt(struct chain *chain,\n"
		"                       struct chain chain,\n"
		"                       struct dnaSeq *qSeq)\n"
		"/* Convert a chain to a list of axt's. This will break\n"
		" * where there is a double-sided gap in chain.\n"
		" */\n"
		"{\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_PreprocessorErrorStatement)
{
	// the ' in mustn't causes end comment to separate
	// and continuation comments to misalign
	// when pad-oper is used.
	// it thinks the ' is an opening quote
	char text[] =
		"\n#ifdef SLIM_CONFIG_USE_PLATE\n"
		"#error You mustn't compile this file.\n"
		"#endif\n"
		"\n"
		"/* @param\n"
		" * callee has in_region's ownership.\n"
		" */\n";

	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_SharpAccessorsWithElse)
{
	// test indent of getters and setters
	// #else causes a problem
	char text[] =
		"\npublic class FooClass\n"
		"{\n"
		"#if FRAMEWORK_VER_2x\n"
		"#else\n"
		"#endif\n"
		"\n"
		"    private bool foo;\n"
		"\n"
		"    public int foo\n"
		"    {\n"
		"        get\n"
		"        {\n"
		"            return foo;\n"
		"        }\n"
		"        set\n"
		"        {\n"
		"            foo = 1;\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_BreakElseIfWithCatch)
{
	// break-elseifs should not break C# catch statement with parens
	char text[] =
		"\nclass Test\n"
		"{\n"
		"    int foo()\n"
		"    {\n"
		"        try\n"
		"        {\n"
		"            bar();\n"
		"        }\n"
		"        catch (Exception e)\n"
		"        {\n"
		"            Console.WriteLine(e.message);\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "break-elseifs, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_IndentBracketsInComment)
{
	// test indent brackets with brackets in comment
	// should not indent brackets in comments
	char text[] =
		"\nvoid foo()\n"
		"    {\n"
		"    /*if (client == NULL)\n"
		"    {\n"
		"        int found = -1;\n"
		"    }*/\n"
		"    }\n";
	char options[] = "indent-brackets";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_BreakBlocksWithEmptyLine)
{
	// test break all blocks with an empty line following comments
	// an error in peekNextLine caused a line break before ++lineOpeningBlocksNum;
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    for (i = 0; i < 10; i++)\n"
		"    {\n"
		"        ++lineOpeningBlocksNum;\n"
		"//        if (isInClassHeader)\n"
		"//        isInClassHeader = false;\n"
		"\n"
		"        if (isInClassHeaderTab)\n"
		"            isInClassHeaderTab = false;\n"
		"    }\n"
		"}\n";
	char options[] = "break-blocks=all";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_UnmatchedBracketsInPreprocessor1)
{
	// unmatched brackets in preprocessor directives
	// should not cause formatting problems on following lines
	char text[] =
		"\n//-----------\n"
		"namespace fooName\n"
		"{\n"
		"\n"
		"#ifdef fooBar\n"
		"void foo1()\n"
		"{\n"
		"#else\n"
		"void foo1()\n"
		"{\n"
		"#endif\n"
		"}\n"
		"\n"
		"void foo2()\n"
		"{\n"
		"}\n"
		"\n"
		"}\n";
	char options[] = "brackets=linux";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_UnmatchedBracketsInPreprocessor2)
{
	// unmatched brackets in preprocessor directives
	// should not cause formatting problems on following lines
	char text[] =
		"\nnamespace fooName\n"
		"{\n"
		"\n"
		"#ifdef fooBar\n"
		"void foo1()\n"
		"{\n"
		"#else\n"
		"void foo1()\n"
		"{\n"
		"#endif\n"
		"}\n"
		"\n"
		"void foo2()\n"
		"{\n"
		"}\n"
		"\n"
		"}\n";
	char options[] = "delete-empty-lines";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_DeleteLinesAfterPreprocessor)
{
	// empty lines after a preprocessor
	// should should NOT be attached to the preprocessor
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"#if 0\n"
		"\n"
		"    {\n"
		"        bar0 = 0;\n"
		"    }\n"
		"#endif\n"
		"\n"
		"\n"
		"    {\n"
		"        bar1 = 1;\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"#if 0\n"
		"    {\n"
		"        bar0 = 0;\n"
		"    }\n"
		"#endif\n"
		"    {\n"
		"        bar1 = 1;\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=linux, delete-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_CSharp_NullableTypes)
{
	// C# nullable types should not separate the ? from the variable
	// when pad-oper is used
	char text[] =
		"\nclass MainClass\n"
		"{\n"
		"    static void Main()\n"
		"    {\n"
		"        // nullable types\n"
		"        // any type may be used as a nullable type\n"
		"        int? i = 10;\n"
		"        double? d1 = 3.14;\n"
		"        bool? flag = null;\n"
		"        char? letter = 'a';\n"
		"        int?[] arr = new int?[10];\n"
		"    }\n"
		"}\n";

	char options[] = "pad-oper, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_CSharp_QuestionQuestionOperator)
{
	// C# ?? operator should not separate when pad-oper is used
	char text[] =
		"\nclass MainClass\n"
		"{\n"
		"    static void Main()\n"
		"    {\n"
		"        // ?? operator example.\n"
		"        int? x = null;\n"
		"        // y = x, unless x is null, in which case y = -1.\n"
		"        int y = x ?? -1;\n"
		"        int i = GetNullableInt() ?? defaultInt(int);\n"
		"        string s = GetStringValue();\n"
		"        Console.WriteLine(s ?? \"Unspecified\");\n"
		"    }\n"
		"}\n";
	char options[] = "pad-oper, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_CSharp_NonGenericDefault)
{
	// C# non-generic default statement should not un-indent the line
	char text[] =
		"\nclass MainClass\n"
		"{\n"
		"    static void Main()\n"
		"    {\n"
		"        int i = GetNullableInt() ?? default(int);\n"
		"    }\n"
		"}\n";
	char options[] = "pad-oper, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_BreakBlocksWithPreprocessor)
{
	// empty lines should not be inserted after the #if
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if ( isFoo )\n"
		"    {\n"
		"        bar1();\n"
		"    }\n"
		"\n"
		"#if 0\n"
		"    bar2();\n"
		"    bar3();\n"
		"    bar4();\n"
		"    bar5();\n"
		"    bar6();\n"
		"#endif\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_CSharp_BreakBlocks_KeepOneLineBlocks)
{
	// C# do NOT break before a block with keep one line blocks
	char text[] =
		"\npublic class FooClass\n"
		"{\n"
		"    public bool Foo { get { return Count > 0; } }\n"
		"}\n";

	char options[] = "break-blocks, keep-one-line-blocks, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_EnumDefinitionPadding)
{
	// enum should space pad before the definition
	// NOTE: the enum is an array type bracket
	char textIn[] =
		"\n// should space pad after the closing bracket\n"
		"typedef enum tagSQObjectType{\n"
		"    OT_INTEGER = (_RT_INTEGER),\n"
		"    OT_BOOL =    (_RT_BOOL),\n"
		"}SQObjectType;\n"
		"\n"
		"// should NOT space pad before the closing semi-colon\n"
		"typedef enum tagSQObjectType{\n"
		"    OT_INTEGER = (_RT_INTEGER),\n"
		"    OT_BOOL =    (_RT_BOOL),\n"
		"};";
	char text[] =
		"\n// should space pad after the closing bracket\n"
		"typedef enum tagSQObjectType {\n"
		"    OT_INTEGER = (_RT_INTEGER),\n"
		"    OT_BOOL =    (_RT_BOOL),\n"
		"} SQObjectType;\n"
		"\n"
		"// should NOT space pad before the closing semi-colon\n"
		"typedef enum tagSQObjectType {\n"
		"    OT_INTEGER = (_RT_INTEGER),\n"
		"    OT_BOOL =    (_RT_BOOL),\n"
		"};";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_UnionDefinitionPadding)
{
	// union should space pad before the definition
	char textIn[] =
		"\n// should space pad after the brackets\n"
		"typedef union tagSQObjectValue{\n"
		"    struct SQTable *pTable;\n"
		"    struct SQArray *pArray;\n"
		"}SQObjectValue;\n"
		"\n"
		"// should NOT space pad before a semi-colon\n"
		"typedef union tagSQObjectValue{\n"
		"    struct SQTable *pTable;\n"
		"    struct SQArray *pArray;\n"
		"};";
	char text[] =
		"\n// should space pad after the brackets\n"
		"typedef union tagSQObjectValue {\n"
		"    struct SQTable *pTable;\n"
		"    struct SQArray *pArray;\n"
		"} SQObjectValue;\n"
		"\n"
		"// should NOT space pad before a semi-colon\n"
		"typedef union tagSQObjectValue {\n"
		"    struct SQTable *pTable;\n"
		"    struct SQArray *pArray;\n"
		"};";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(v123_StructDefinitionPadding)
{
	// struct should space pad before the definition
	char textIn[] =
		"\n// should space pad after the brackets\n"
		"typedef struct tagSQStackInfos{\n"
		"    const SQChar* funcname;\n"
		"    const SQChar* source;\n"
		"}SQStackInfos;\n"
		"\n"
		"// should NOT space pad before a semi-colon\n"
		"typedef struct tagSQStackInfos{\n"
		"    const SQChar* funcname;\n"
		"    const SQChar* source;\n"
		"};";
	char text[] =
		"\n// should space pad after the brackets\n"
		"typedef struct tagSQStackInfos {\n"
		"    const SQChar* funcname;\n"
		"    const SQChar* source;\n"
		"} SQStackInfos;\n"
		"\n"
		"// should NOT space pad before a semi-colon\n"
		"typedef struct tagSQStackInfos {\n"
		"    const SQChar* funcname;\n"
		"    const SQChar* source;\n"
		"};";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle Character Set Tests
//----------------------------------------------------------------------------

TEST(ExtendedCharacterSet)
{
	// multi-byte characters (c) and � should not cause assert error with
	//     Visual Studio isalpha(), isalnum(), is punct(), etc.
	// will happen only in the debug build
	char text[] =
		"\n// � is character 169\n"
		"\n// � is character 252\n"
		"void foo()\n"
		"{\n"
		"    �bar1();\n"
		"    bar�2();\n"
		"    bar3�();\n"
		"    ba�r4(�);\n"
		"    cout << \"��\" << endl;\n"
		"    �\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(UnicodeCharacterSet)
{
	// unicode characters should not cause assert error with
	//     Visual Studio isalpha(), isalnum(), is punct(), etc.
	// will happen only in the debug build
	char text[] =
		"\n// \xF0\x80\xA0\xB0 is a unicode UTF-8 character\n"
		"void foo()\n"
		"{\n"
		"    \xF0\x80\xA0\xB0\x62\x61r1();\n"
		"    bar\xF0\x80\xA0\xB0\x32();\n"
		"    bar3(\xF0\x80\xA0\xB0);\n"
		"    ba\xF0\x80\xA0\xB0r4();\n"
		"    cout << \"\xF0\x80\xA0\xB0\" << endl;\n"
		"    \xF0\x80\xA0\xB0\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(UTF8WithBOM)
{
	// UTF-8 BOM should not cause assert error with
	//     Visual Studio isalpha(), isalnum(), is punct(), etc.
	//     and should recognize "namespace" as a keyword
	// will happen only in the debug build
	char textIn[] =
		"\xEF\xBB\xBFnamespace {\n"
		"}\n";
	char text[] =
		"\xEF\xBB\xBFnamespace\n"
		"{\n"
		"}\n";
	char options[] = "brackets=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle Virgin Line Tests
//----------------------------------------------------------------------------

TEST(VirginLine)
{
	// test bracket on second line
	// linux bracket should not attach
	char text[] =
		"void Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"}\n";
	char options[] = "brackets=linux";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle Input Error Tests
// Test error reporting conditions in astyle_main
//----------------------------------------------------------------------------

TEST(AStyleMainInputError_NullErrorHandlerPointer)
{
	// test error handling for NULL error handler pointer
	// this cannot call the error handler, check only for NULL return
	// memory has NOT been allocated for this error
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, NULL, memoryAlloc);
	CHECK(textOut == NULL);
}

TEST(AStyleMainInputError_NullPointerToSource)
{
	// test error handling for NULL pointer to source
	// memory has NOT been allocated for this error
	char options[] = "";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(NULL, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	CHECK_EQUAL(errorsIn + 1, errorsOut);
	CHECK(textOut == NULL);
}

TEST(AStyleMainInputError_NullPointerToOptions)
{
	// test error handling for NULL pointer to options
	// memory has NOT been allocated for this error
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, NULL, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	CHECK_EQUAL(errorsIn + 1, errorsOut);
	CHECK(textOut == NULL);
}

TEST(AStyleMainInputError_NullPointerToMemoryAlloc)
{
	// test error handling for NULL memory allocation pointer
	// memory has NOT been allocated for this error
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char options[] = "";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, NULL);
	int errorsOut = getErrorHandler2Calls();
	CHECK_EQUAL(errorsIn + 1, errorsOut);
	CHECK(textOut == NULL);
}

TEST(AStyleMainInputError_InvalidOption)
{
	// test error handling for an invalid option
	// memory HAS been allocated for this error
	// the source will be formatted without the option
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"	bar();\n"
		"}\n";
	char options[] = "invalid-option, indent=tab";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(textIn, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	CHECK_EQUAL(errorsIn + 1, errorsOut);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle Macro formatting
// Test macros recognized by AStyle
//----------------------------------------------------------------------------

TEST(Macro_wxWidgetsEventHandler)
{
	// wxWidgets event handler should be indented
	char text[] =
		"\nBEGIN_EVENT_TABLE(JP5Frm,wxFrame)\n"
		"    EVT_CLOSE(JP5Frm::WindowClose)\n"
		"    EVT_PAINT(JP5Frm::WindowPaint)\n"
		"    EVT_MENU(ID_MENU_FILE_OPEN, JP5Frm::MenuFileOpen)\n"
		"    EVT_MENU(ID_MENU_FILE_EXIT, JP5Frm::MenuFileExit)\n"
		"END_EVENT_TABLE()\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Macro_wxWidgetsEventHandlerNonIndentComment)
{
	// wxWidgets event handler should be indented
	// but not the comments
	char text[] =
		"\nBEGIN_EVENT_TABLE(JP5Frm,wxFrame)\n"
		"//    EVT_CLOSE(JP5Frm::WindowClose)\n"
		"    EVT_PAINT(JP5Frm::WindowPaint)\n"
		"    EVT_MENU(ID_MENU_FILE_OPEN, JP5Frm::MenuFileOpen)\n"
		"//    EVT_MENU(ID_MENU_FILE_EXIT, JP5Frm::MenuFileExit)\n"
		"END_EVENT_TABLE()\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Macro_MfcMessageMap)
{
	// MFC message map should be indented
	char text[] =
		"\nBEGIN_MESSAGE_MAP(CMainJPWnd, CFrameWnd)\n"
		"    ON_WM_CLOSE()\n"
		"    ON_WM_PAINT()\n"
		"    ON_COMMAND(IDM_ABOUT, OnAbout)\n"
		"    ON_COMMAND(IDM_EXIT,  OnExit)\n"
		"END_MESSAGE_MAP()\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle short options used only by console
// should get an error unless they have been duplicated by another option
//----------------------------------------------------------------------------

TEST(ConsoleOption_SuffixNoneShort)
{
	// test suffix=none short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char options[] = "-n";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	CHECK_EQUAL(errorsIn + 1, errorsOut);
	CHECK(textOut != NULL);
	delete [] textOut;
}

TEST(ConsoleOption_Recursive1Short)
{
	// test recursive short option1
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char options[] = "-r";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	CHECK_EQUAL(errorsIn + 1, errorsOut);
	CHECK(textOut != NULL);
	delete [] textOut;
}

TEST(ConsoleOption_Recursive2Short)
{
	// test recursive short option2
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char options[] = "-R";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	CHECK_EQUAL(errorsIn + 1, errorsOut);
	CHECK(textOut != NULL);
	delete [] textOut;
}

TEST(ConsoleOption_ErrorsToStdoutShort)
{
	// test errors-to-stdout short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char options[] = "-X";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	CHECK_EQUAL(errorsIn + 1, errorsOut);
	CHECK(textOut != NULL);
	delete [] textOut;
}

TEST(ConsoleOption_PreserveDateShort)
{
	// test preserve-date short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char options[] = "-Z";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	CHECK_EQUAL(errorsIn + 1, errorsOut);
	CHECK(textOut != NULL);
	delete [] textOut;
}

TEST(ConsoleOption_VerboseShort)
{
	// test verbose short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char options[] = "-v";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	CHECK_EQUAL(errorsIn + 1, errorsOut);
	CHECK(textOut != NULL);
	delete [] textOut;
}

TEST(ConsoleOption_FormattedShort)
{
	// test formatted short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char options[] = "-Q";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	CHECK_EQUAL(errorsIn + 1, errorsOut);
	CHECK(textOut != NULL);
	delete [] textOut;
}

TEST(ConsoleOption_QuietShort)
{
	// test preserve-date short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char options[] = "-q";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	CHECK_EQUAL(errorsIn + 1, errorsOut);
	CHECK(textOut != NULL);
	delete [] textOut;
}

TEST(ConsoleOption_VersionShort)
{
	// test version short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char options[] = "-V";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	CHECK_EQUAL(errorsIn + 1, errorsOut);
	CHECK(textOut != NULL);
	delete [] textOut;
}

TEST(ConsoleOption_Help1Short)
{
	// test help short option1
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char options[] = "-h";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	CHECK_EQUAL(errorsIn + 1, errorsOut);
	CHECK(textOut != NULL);
	delete [] textOut;
}

TEST(ConsoleOption_Help2Short)
{
	// test help short option2
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	char options[] = "-?";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	CHECK_EQUAL(errorsIn + 1, errorsOut);
	CHECK(textOut != NULL);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle Quotes
//----------------------------------------------------------------------------

TEST(Quote)
{
	// test quotes
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    char* quote = \"this	is a quote \\\n"
		"  	quote	continuation  \\\n"
		"	quote continuation\";\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Quote_Single)
{
	// test single quotes
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (ch == \'\\r\')\n"
		"        eolWindows++;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Quote_CSharp_Verbatim1)
{
	// test C# verbatim quotes
	// whitespace should not change
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    string program = @\"using System;\n"
		"class Test {\n"
		"  void M(DerivedClass d) {\n"
		"    \n"
		"  }\n"
		"}\n"
		"class BaseClass<T> {\n"
		"	public T value;\n"
		"}\n"
		"class DerivedClass : BaseClass<string> {\n"
		"			\n"
		"}\n"
		";\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Quote_CSharp_Verbatim2)
{
	// test C# verbatim quotes with """" and ""
	// whitespace should not change
	char text[] =
		"\nconst string CodeEmptyResourceSetName = @\"using System.Resources;\n"
		"class A {\n"
		"    void B()\n"
		"    {\n"
		"        ResourceManager mgr = new ResourceManager(\"\"\"\", GetAssembly());\n"
		"        mgr.GetString(\"\"TestKey\"\");\n"
		"    }\n"
		"}\n"
		";\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Quote_CSharp_Empty)
{
	// test C# empty quotes with """"
	// whitespace should not change
	char text[] =
		"\npublic static string GetString(string key)\n"
		"{\n"
		"    return \"\"\"\";\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Quote_CSharp_Misc)
{
	// test C# strange looking quotes with """
	// whitespace should not change
	char text[] =
		"\npublic void TestString()\n"
		"{\n"
		"    CheckToken(@\"@\"\"-->\"\"\"\"<--\"\"\", @\"-->\"\"<--\");\n"
		"    CheckToken(@\"\"\"-->\\\"\"<--\"\"\", \"-->\\\"<--\");\n"
		"\n"
		"    CheckToken(@\"\"\"\\U00000041\"\"\", \"\\U00000041\");\n"
		"    CheckToken(@\"\"\"\\U00010041\"\"\", \"\\U00010041\");\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle Enum
//----------------------------------------------------------------------------

TEST(Enum_Namespace1)
{
	// test indent of enum in a namespace
	char text[] =
		"\nnamespace fooName\n"
		"{\n"
		"enum dStyle\n"
		"{\n"
		"    OK = 0,\n"
		"    YES_NO,\n"
		"};\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Enum_Namespace2)
{
	// test indent of enum in a namespace
	// with in-statement indent
	char text[] =
		"\nnamespace fooName\n"
		"{\n"
		"enum dStyle { OK = 0,\n"
		"              YES_NO,\n"
		"            };\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Enum_NamespaceIndent1)
{
	// test indent of enum in an indented namespace
	char text[] =
		"\nnamespace fooName\n"
		"{\n"
		"    enum dStyle\n"
		"    {\n"
		"        OK = 0,\n"
		"        YES_NO,\n"
		"    };\n"
		"}\n";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Enum_NamespaceIndent2)
{
	// test indent of enum in an indented namespace
	// with in-statement indent
	char text[] =
		"\nnamespace fooName\n"
		"{\n"
		"    enum dStyle { OK = 0,\n"
		"                  YES_NO,\n"
		"                };\n"
		"}\n";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Enum_ClassTypeSafe)
{
	// type safe enum class should be formatted as an enum
	char text[] =
		"\nenum class Day\n"
		"{\n"
		"    NoDays=0,\n"
		"    Sunday=1,\n"
		"    Monday,\n"
		"    FirstDay = Day::Sunday\n"
		"};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Enum_Class1)
{
	// test indent of enum in a class
	char text[] =
		"\nclass fooClass\n"
		"{\n"
		"public:\n"
		"    enum dStyle\n"
		"    {\n"
		"        OK = 0,\n"
		"        YES_NO,\n"
		"    };\n"
		"};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Enum_Class2)
{
	// test indent of enum in a class
	// with in-statement indent
	char text[] =
		"\nclass fooClass\n"
		"{\n"
		"public:\n"
		"    enum dStyle { OK = 0,\n"
		"                  YES_NO,\n"
		"                };\n"
		"};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Enum_ClassIndent1)
{
	// test indent of enum in an indented class
	char text[] =
		"\nclass fooClass\n"
		"{\n"
		"    public:\n"
		"        enum dStyle\n"
		"        {\n"
		"            OK = 0,\n"
		"            YES_NO,\n"
		"        };\n"
		"};\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Enum_ClassIndent2)
{
	// test indent of enum in an indented class
	// with in-statement indent
	char text[] =
		"\nclass fooClass\n"
		"{\n"
		"    public:\n"
		"        enum dStyle { OK = 0,\n"
		"                      YES_NO,\n"
		"                    };\n"
		"};\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Enum_ClassIndent3)
{
	// test indent of enum in an indented class
	// within a #else preprocessor
	char text[] =
		"\n#if VERSION(2)\n"
		"#else\n"
		"class fooClass\n"
		"{\n"
		"    public:\n"
		"        enum wxPaneState\n"
		"        {\n"
		"            optionFloating = 1 << 0,\n"
		"            optionHidden   = 1 << 1,\n"
		"        };\n"
		"};\n"
		"#endif\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Enum_Java)
{
	// test indent of java enum
	char text[] =
		"\npublic enum KeyboardCommand\n"
		"{   NONE,\n"
		"    TAB_OUT_FORWARD,\n"
		"    TAB_OUT_BACK\n"
		"}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle Struct
//----------------------------------------------------------------------------

TEST(Struct_Break)
{
	// struct with broken brackets
	char text[] =
		"\nstruct\n"
		"{\n"
		"    const char *name;\n"
		"    int id;\n"
		"} idmTable[] =\n"
		"{\n"
		"    {\"IDM_MRUFILE\", IDM_MRUFILE},\n"
		"    {\"IDM_TOOLS\",   IDM_TOOLS},\n"
		"};\n";
	char options[] = "brackets=break";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Struct_Attach)
{
	// struct with attached brackets
	char text[] =
		"\nstruct {\n"
		"    const char *name;\n"
		"    int id;\n"
		"} idmTable[] = {\n"
		"    {\"IDM_MRUFILE\", IDM_MRUFILE},\n"
		"    {\"IDM_TOOLS\",   IDM_TOOLS},\n"
		"};\n";
	char options[] = "brackets=attach";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Struct_Horstmann)
{
	// struct with attached brackets
	char text[] =
		"\nstruct\n"
		"{   const char *name;\n"
		"    int id;\n"
		"} idmTable[] =\n"
		"{   {\"IDM_MRUFILE\", IDM_MRUFILE},\n"
		"    {\"IDM_TOOLS\",   IDM_TOOLS},\n"
		"};\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle Preprocessor
//----------------------------------------------------------------------------

TEST(Preprocessor_CommandType)
{
	// check indentation
	// correctly identifying as a COMMND_TYPE bracket
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"#if wxUSE_UNICODE\n"
		"        if (c < 128)\n"
		"#else\n"
		"        if (c < 256)\n"
		"#endif\n"
		"        {\n"
		"            w += 1000;\n"
		"        }\n"
		"        else\n"
		"        {\n"
		"            w += 2000;\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Preprocessor_Elif)
{
	// #elif updates the waitingBeautifierStack
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"#if USE64\n"
		"        if (c < 64)\n"
		"#elif USE128\n"
		"        if (c < 128)\n"
		"#elif USE256\n"
		"        if (c < 256)\n"
		"#endif\n"
		"        {\n"
		"            w += 1000;\n"
		"        }\n"
		"        else\n"
		"        {\n"
		"            w += 2000;\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Preprocessor_EndOnEmptyLine)
{
	// TODO: AStyle adds a space to the empty line
	// preprocessor define ends with an empty line
	char textIn[] =
		"\n#define ITEM_ITERATION_UVC_LOOP_END(BOTTOMY) \\\n"
		"    } while ( p->m_y < BOTTOMY ); \\\n"
		"\n"
		"\n";
	char text[] =
		"\n#define ITEM_ITERATION_UVC_LOOP_END(BOTTOMY) \\\n"
		"    } while ( p->m_y < BOTTOMY ); \\\n"
		" \n"
		"\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Preprocessor_Assembler)
{
	// can have preprocessor in a assembler block
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    __asm {\n"
		"        mov eax, fs:[0x8]\n"
		"#ifdef _WIN32\n"
		"        mov dx, 0xD007\n"
		"#else\n"
		"        mov dx, 0xD008\n"
		"#endif\n"
		"        out dx, al\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Preprocessor_MissingOpener)
{
	// #else with missing #if
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    int foo = 1;\n"
		"#else\n"
		"    int foo = 2;\n"
		"#endif\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Preprocessor_WxWidgetsMacro)
{
	// preprocessor should NOT be indented
	char text[] =
		"\nBEGIN_EVENT_TABLE(ClassWizardDlg, wxDialog)\n"
		"    EVT_BUTTON(XRCID(\"btnCommonDir\"), ClassWizardDlg::OnCommonDirClick)\n"
		"#ifdef LOGGING\n"
		"    EVT_CHECKBOX(XRCID(\"chkLowerCase\"), ClassWizardDlg::OnLowerCaseClick)\n"
		"    EVT_BUTTON(XRCID(\"btnIncludeDir\"), ClassWizardDlg::OnIncludeDirClick)\n"
		"#endif\n"
		"    EVT_BUTTON(XRCID(\"btnImplDir\"), ClassWizardDlg::OnImplDirClick)\n"
		"END_EVENT_TABLE()\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Preprocessor_ArrayType)
{
	// check indentation
	// correctly identifying as an ARRAY_TYPE bracket
	char text[] =
		"\nstatic SQRegFunction base_funcs[] = {\n"
		"    {_SC(\"seterrorhandler\"),base_seterrorhandler,2, NULL},\n"
		"    {_SC(\"setdebughook\"),base_setdebughook,2, NULL},\n"
		"#ifndef NO_GARBAGE_COLLECTOR\n"
		"    {_SC(\"collectgarbage\"),base_collectgarbage,1, NULL},\n"
		"#endif\n"
		"    {0,0}\n"
		"};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Preprocessor_ArrayMissingOpener)
{
	// array #else with missing #if
	char text[] =
		"\nchar *section_list[] =\n"
		"{\n"
		"// #ifdef Q_OS_SOLARIS\n"
		"    \"1B\", \"SunOS/BSD\",\n"
		"#else\n"
		"    \"2\", \"System Calls\",\n"
		"#endif\n"
		"    NULL, \"Misc. Reference\",\n"
		"};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Preprocessor_ArrayHorstmann_Break)
{
	// check broken brackets to horstmann
	// should NOT run-in a preprocessor directive
	char text[] =
		"\nchar *section_list[] =\n"
		"{\n"
		"#ifdef Q_OS_SOLARIS\n"
		"    // for Solaris\n"
		"    \"1B\", \"SunOS/BSD\",\n"
		"#else\n"
		"    // Other OS\n"
		"    \"2\", \"System Calls\",\n"
		"#endif\n"
		"};\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Preprocessor_ArrayHorstmann_Attach)
{
	// check attached brackets to horstmann
	// should NOT run-in a preprocessor directive
	char textIn[] =
		"\nchar *section_list[] = {\n"
		"#ifdef Q_OS_SOLARIS\n"
		"    // for Solaris\n"
		"    \"1B\", \"SunOS/BSD\",\n"
		"#else\n"
		"    // Other OS\n"
		"    \"2\", \"System Calls\",\n"
		"#endif\n"
		"};\n";
	char text[] =
		"\nchar *section_list[] =\n"
		"{\n"
		"#ifdef Q_OS_SOLARIS\n"
		"    // for Solaris\n"
		"    \"1B\", \"SunOS/BSD\",\n"
		"#else\n"
		"    // Other OS\n"
		"    \"2\", \"System Calls\",\n"
		"#endif\n"
		"};\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Preprocessor_ArrayHorstmann_Horstmann)
{
	// check horstmann brackets to horstmann
	// should NOT run-in a preprocessor directive
	char text[] =
		"\nchar *section_list[] =\n"
		"{\n"
		"#ifdef Q_OS_SOLARIS\n"
		"    // for Solaris\n"
		"    \"1B\", \"SunOS/BSD\",\n"
		"#else\n"
		"    // Other OS\n"
		"    \"2\", \"System Calls\",\n"
		"#endif\n"
		"};\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle Comments
//----------------------------------------------------------------------------

TEST(Comment_BracketsNone_NamespaceClassIndent_None)
{
	// comments should indent with namespaces and classes
	// brackets=none with default brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"/*\n"
		" * comment0\n"
		" */\n"
		"class FooClass\n"
		"{\n"
		"public:\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"void foo()\n"
		"{\n"
		"/*\n"
		" * comment2\n"
		" */\n"
		"}\n"
		"};\n"
		"}\n";
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"    /*\n"
		"     * comment0\n"
		"     */\n"
		"    class FooClass\n"
		"    {\n"
		"        public:\n"
		"            /*\n"
		"             * comment1\n"
		"             */\n"
		"            void foo()\n"
		"            {\n"
		"                /*\n"
		"                 * comment2\n"
		"                 */\n"
		"            }\n"
		"    };\n"
		"}\n";
	char options[] = "indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_BracketsNone_NamespaceClassIndent_Break)
{
	// comments should indent with namespaces and classes
	// brackets=none with broken brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"/*\n"
		" * comment0\n"
		" */\n"
		"class FooClass\n"
		"{\n"
		"public:\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"void foo()\n"
		"{\n"
		"/*\n"
		" * comment2\n"
		" */\n"
		"}\n"
		"};\n"
		"}\n";
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"    /*\n"
		"     * comment0\n"
		"     */\n"
		"    class FooClass\n"
		"    {\n"
		"        public:\n"
		"            /*\n"
		"             * comment1\n"
		"             */\n"
		"            void foo()\n"
		"            {\n"
		"                /*\n"
		"                 * comment2\n"
		"                 */\n"
		"            }\n"
		"    };\n"
		"}\n";
	char options[] = "indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_BracketsNone_NamespaceClassIndent_Attach)
{
	// comments should indent with namespaces and classes
	// brackets=none with attached brackets
	char textIn[] =
		"\nnamespace FooName {\n"
		"/*\n"
		" * comment0\n"
		" */\n"
		"class FooClass {\n"
		"public:\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"void foo() {\n"
		"/*\n"
		" * comment2\n"
		" */\n"
		"}\n"
		"};\n"
		"}\n";
	char text[] =
		"\nnamespace FooName {\n"
		"    /*\n"
		"     * comment0\n"
		"     */\n"
		"    class FooClass {\n"
		"        public:\n"
		"            /*\n"
		"             * comment1\n"
		"             */\n"
		"            void foo() {\n"
		"                /*\n"
		"                 * comment2\n"
		"                 */\n"
		"            }\n"
		"    };\n"
		"}\n";
	char options[] = "indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_BracketsNone_NamespaceClassIndent_Horstmann)
{
	// comments should indent with namespaces and classes
	// brackets=none with with horstmann brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"class FooClass\n"
		"{\n"
		"public:\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"void foo()\n"
		"{/*\n"
		"  * comment2\n"
		"  */\n"
		"}\n"
		"};\n"
		"}\n";
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"    class FooClass\n"
		"    {\n"
		"        public:\n"
		"            /*\n"
		"             * comment1\n"
		"             */\n"
		"            void foo()\n"
		"            {   /*\n"
		"                 * comment2\n"
		"                 */\n"
		"            }\n"
		"    };\n"
		"}\n";
	char options[] = "indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_BracketsBreak_NamespaceClassIndent_Break)
{
	// comments should indent with namespaces and classes
	// brackets=break with broken brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"/*\n"
		" * comment0\n"
		" */\n"
		"class FooClass\n"
		"{\n"
		"public:\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"void foo()\n"
		"{\n"
		"/*\n"
		" * comment2\n"
		" */\n"
		"}\n"
		"};\n"
		"}\n";
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"    /*\n"
		"     * comment0\n"
		"     */\n"
		"    class FooClass\n"
		"    {\n"
		"        public:\n"
		"            /*\n"
		"             * comment1\n"
		"             */\n"
		"            void foo()\n"
		"            {\n"
		"                /*\n"
		"                 * comment2\n"
		"                 */\n"
		"            }\n"
		"    };\n"
		"}\n";
	char options[] = "brackets=break, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_BracketsBreak_NamespaceClassIndent_Attach)
{
	// comments should indent with namespaces and classes
	// brackets=break with attached brackets
	char textIn[] =
		"\nnamespace FooName {\n"
		"/*\n"
		" * comment0\n"
		" */\n"
		"class FooClass {\n"
		"public:\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"void foo() {\n"
		"/*\n"
		" * comment2\n"
		" */\n"
		"}\n"
		"};\n"
		"}\n";
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"    /*\n"
		"     * comment0\n"
		"     */\n"
		"    class FooClass\n"
		"    {\n"
		"        public:\n"
		"            /*\n"
		"             * comment1\n"
		"             */\n"
		"            void foo()\n"
		"            {\n"
		"                /*\n"
		"                 * comment2\n"
		"                 */\n"
		"            }\n"
		"    };\n"
		"}\n";
	char options[] = "brackets=break, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_BracketsBreak_NamespaceClassIndent_Horstmann)
{
	// comments should indent with namespaces and classes
	// brackets=break with horstmann brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"class FooClass\n"
		"{\n"
		"public:\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"void foo()\n"
		"{/*\n"
		"  * comment2\n"
		"  */\n"
		"}\n"
		"};\n"
		"}\n";
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"    class FooClass\n"
		"    {\n"
		"        public:\n"
		"            /*\n"
		"             * comment1\n"
		"             */\n"
		"            void foo()\n"
		"            {\n"
		"                /*\n"
		"                 * comment2\n"
		"                 */\n"
		"            }\n"
		"    };\n"
		"}\n";
	char options[] = "brackets=break, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_BracketsAttach_NamespaceClassIndent_Break)
{
	// comments should indent with namespaces and classes
	// brackets=attach with broken brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"/*\n"
		" * comment0\n"
		" */\n"
		"class FooClass\n"
		"{\n"
		"public:\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"void foo()\n"
		"{\n"
		"/*\n"
		" * comment2\n"
		" */\n"
		"}\n"
		"};\n"
		"}\n";
	char text[] =
		"\nnamespace FooName {\n"
		"    /*\n"
		"     * comment0\n"
		"     */\n"
		"    class FooClass {\n"
		"        public:\n"
		"            /*\n"
		"             * comment1\n"
		"             */\n"
		"            void foo() {\n"
		"                /*\n"
		"                 * comment2\n"
		"                 */\n"
		"            }\n"
		"    };\n"
		"}\n";
	char options[] = "brackets=attach, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_BracketsAttach_NamespaceClassIndent_Attach)
{
	// comments should indent with namespaces and classes
	// brackets=attach with attached brackets
	char textIn[] =
		"\nnamespace FooName {\n"
		"/*\n"
		" * comment0\n"
		" */\n"
		"class FooClass {\n"
		"public:\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"void foo() {\n"
		"/*\n"
		" * comment2\n"
		" */\n"
		"}\n"
		"};\n"
		"}\n";
	char text[] =
		"\nnamespace FooName {\n"
		"    /*\n"
		"     * comment0\n"
		"     */\n"
		"    class FooClass {\n"
		"        public:\n"
		"            /*\n"
		"             * comment1\n"
		"             */\n"
		"            void foo() {\n"
		"                /*\n"
		"                 * comment2\n"
		"                 */\n"
		"            }\n"
		"    };\n"
		"}\n";
	char options[] = "brackets=attach, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_BracketsAttach_NamespaceClassIndent_Horstmann)
{
	// comments should indent with namespaces and classes
	// brackets=attach with horstmann brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"class FooClass\n"
		"{\n"
		"public:\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"void foo()\n"
		"{/*\n"
		"  * comment2\n"
		"  */\n"
		"}\n"
		"};\n"
		"}\n";
	char text[] =
		"\nnamespace FooName {\n"
		"    class FooClass {\n"
		"        public:\n"
		"            /*\n"
		"             * comment1\n"
		"             */\n"
		"            void foo() {\n"
		"                /*\n"
		"                 * comment2\n"
		"                 */\n"
		"            }\n"
		"    };\n"
		"}\n";
	char options[] = "brackets=attach, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_BracketsHorstmann_NamespaceClassIndent_Break)
{
	// comments should indent with namespaces and classes
	// brackets=horstmann with broken brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"class FooClass\n"
		"{\n"
		"public:\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"void foo()\n"
		"{\n"
		"/*\n"
		" * comment2\n"
		" */\n"
		"}\n"
		"};\n"
		"}\n";
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"    class FooClass\n"
		"    {   public:\n"
		"            /*\n"
		"             * comment1\n"
		"             */\n"
		"            void foo()\n"
		"            {   /*\n"
		"                 * comment2\n"
		"                 */\n"
		"            }\n"
		"    };\n"
		"}\n";
	char options[] = "brackets=horstmann, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_BracketsHorstmann_NamespaceClassIndent_Attach)
{
	// comments should indent with namespaces and classes
	// brackets=horstmann with attached brackets
	char textIn[] =
		"\nnamespace FooName {\n"
		"class FooClass {\n"
		"public:\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"void foo() {\n"
		"/*\n"
		" * comment2\n"
		" */\n"
		"}\n"
		"};\n"
		"}\n";
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"    class FooClass\n"
		"    {   public:\n"
		"            /*\n"
		"             * comment1\n"
		"             */\n"
		"            void foo()\n"
		"            {   /*\n"
		"                 * comment2\n"
		"                 */\n"
		"            }\n"
		"    };\n"
		"}\n";
	char options[] = "brackets=horstmann, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_BracketsHorstmann_NamespaceClassIndent_Horstmann)
{
	// comments should indent with namespaces and classes
	// brackets=horstmann with horstmann brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"class FooClass\n"
		"{\n"
		"public:\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"void foo()\n"
		"{/*\n"
		"  * comment2\n"
		"  */\n"
		"}\n"
		"};\n"
		"}\n";
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"    class FooClass\n"
		"    {   public:\n"
		"            /*\n"
		"             * comment1\n"
		"             */\n"
		"            void foo()\n"
		"            {   /*\n"
		"                 * comment2\n"
		"                 */\n"
		"            }\n"
		"    };\n"
		"}\n";
	char options[] = "brackets=horstmann, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}


TEST(Comment_Namespace_Misc1)
{
	// comments should indent with namespaces
	// comments precede the brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"class FooClass\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"{\n"
		"public:\n"
		"void foo()\n"
		"/*\n"
		" * comment2\n"
		" */\n"
		"{\n"
		"}\n"
		"};\n"
		"}\n";
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"    class FooClass\n"
		"    /*\n"
		"     * comment1\n"
		"     */\n"
		"    {\n"
		"    public:\n"
		"        void foo()\n"
		"        /*\n"
		"         * comment2\n"
		"         */\n"
		"        {\n"
		"        }\n"
		"    };\n"
		"}\n";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_Namespace_ClassMisc2)
{
	// comments should indent with namespaces and classes
	// comments precede the brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"class FooClass\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"{\n"
		"public:\n"
		"void foo()\n"
		"/*\n"
		" * comment2\n"
		" */\n"
		"{\n"
		"}\n"
		"};\n"
		"}\n";
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"    class FooClass\n"
		"    /*\n"
		"     * comment1\n"
		"     */\n"
		"    {\n"
		"        public:\n"
		"            void foo()\n"
		"            /*\n"
		"             * comment2\n"
		"             */\n"
		"            {\n"
		"            }\n"
		"    };\n"
		"}\n";
	char options[] = "indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_NestedClass_Misc3)
{
	// comments should indent with classes
	// comments precede the brackets
	char text[] =
		"\nclass A\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"{\n"
		"public:\n"
		"    int foo1;\n"
		"    class B\n"
		"    /*\n"
		"     * comment1\n"
		"     */\n"
		"    {\n"
		"    public:\n"
		"        int foo2;\n"
		"        class C\n"
		"        /*\n"
		"         * comment1\n"
		"         */\n"
		"        {\n"
		"        public:\n"
		"        };\n"
		"    };\n"
		"};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_NestedClass_Misc4)
{
	// comments should indent with classes
	// comments precede the brackets in indented classes
	char text[] =
		"\nclass A\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"{\n"
		"    public:\n"
		"        int foo1;\n"
		"        class B\n"
		"        /*\n"
		"         * comment1\n"
		"         */\n"
		"        {\n"
		"            public:\n"
		"                int foo2;\n"
		"                class C\n"
		"                /*\n"
		"                 * comment1\n"
		"                 */\n"
		"                {\n"
		"                    public:\n"
		"                };\n"
		"        };\n"
		"};\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_NamespaceClass_Misc5)
{
	// comments should indent with classes with inheritance
	// comments precede the brackets
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"class FooClass\n"
		"    : public FooBase\n"
		"/*\n"
		" * comment1\n"
		" */\n"
		"{\n"
		"public:\n"
		"    void foo()\n"
		"    /*\n"
		"     * comment2\n"
		"     */\n"
		"    {\n"
		"    }\n"
		"};\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_NamespaceClass_Misc6)
{
	// comments should indent with classes with inheritance
	// comments precede the brackets
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"    class FooClass\n"
		"        : public FooBase\n"
		"    /*\n"
		"     * comment1\n"
		"     */\n"
		"    {\n"
		"    public:\n"
		"        void foo()\n"
		"        /*\n"
		"         * comment2\n"
		"         */\n"
		"        {\n"
		"        }\n"
		"    };\n"
		"}\n";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_BeforeStatement_Misc7)
{
	// comments before a statement should not be broken
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isBar) {\n"
		"        /*bool result =*/ Bar();\n"
		"        return;\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_LeadingSpaceCorrection1)
{
	// comment where the leading spaces need correction
	// will adjust the first line
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"       /*   EXEC SQL INSERT\n"
		"    INTO   branch (branch_id, branch_name, branch_addr,\n"
		"             branch_city, branch_phone)\n"
		"    VALUES (:bid, :bname, :baddr:baddr_ind);\n"
		"    */\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    /*   EXEC SQL INSERT\n"
		"    INTO   branch (branch_id, branch_name, branch_addr,\n"
		"             branch_city, branch_phone)\n"
		"    VALUES (:bid, :bname, :baddr:baddr_ind);\n"
		"    */\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_LeadingSpaceCorrection2)
{
	// comment where the leading spaces need correction
	// text has tabs
	// will adjust the first line
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"	   /*   EXEC SQL INSERT\n"
		"	INTO   branch (branch_id, branch_name, branch_addr,\n"
		"	         branch_city, branch_phone)\n"
		"    VALUES (:bid, :bname, :baddr:baddr_ind);\n"
		"	*/\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    /*   EXEC SQL INSERT\n"
		"    INTO   branch (branch_id, branch_name, branch_addr,\n"
		"             branch_city, branch_phone)\n"
		"    VALUES (:bid, :bname, :baddr:baddr_ind);\n"
		"    */\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Comment_LeadingSpaceCorrection3)
{
	// comment where the leading spaces need correction
	// and indent needs adjusting
	// will adjust the first line
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"         /*   EXEC SQL INSERT\n"
		"      INTO   branch (branch_id, branch_name, branch_addr,\n"
		"               branch_city, branch_phone)\n"
		"      VALUES (:bid, :bname, :baddr:baddr_ind);\n"
		"      */\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    /*   EXEC SQL INSERT\n"
		"    INTO   branch (branch_id, branch_name, branch_addr,\n"
		"             branch_city, branch_phone)\n"
		"    VALUES (:bid, :bname, :baddr:baddr_ind);\n"
		"    */\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle Continuation Lines
//----------------------------------------------------------------------------

TEST(Continuation_BracketsNone_Break)
{
	// continuation lines
	// brackets=none and input of broken brackets
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1())\n"
		"    {\n"
		"        wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2())\n"
		"    {\n"
		"        wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Continuation_BracketsNone_Attach)
{
	// continuation lines
	// brackets=none and input of attached brackets
	char text[] =
		"\nvoid foo() {\n"
		"    if (isFoo1()) {\n"
		"        wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2()) {\n"
		"        wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Continuation_BracketsNone_Horstmann)
{
	// continuation lines
	// brackets=none and input of horstmann brackets
	char text[] =
		"\nvoid foo()\n"
		"{   if (isFoo1())\n"
		"    {   wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2())\n"
		"    {   wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Continuation_BracketsBreak_Break)
{
	// continuation lines
	// brackets=break and input of broken brackets
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1())\n"
		"    {\n"
		"        wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2())\n"
		"    {\n"
		"        wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=break";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Continuation_BracketsBreak_Attach)
{
	// continuation lines
	// brackets=break and input of attached brackets
	char textIn[] =
		"\nvoid foo() {\n"
		"    if (isFoo1()) {\n"
		"        wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2()) {\n"
		"        wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1())\n"
		"    {\n"
		"        wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2())\n"
		"    {\n"
		"        wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Continuation_BracketsBreak_Horstmann)
{
	// continuation lines
	// brackets=break and input of horstmann brackets
	char textIn[] =
		"\nvoid foo()\n"
		"{   if (isFoo1())\n"
		"    {   wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2())\n"
		"    {   wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1())\n"
		"    {\n"
		"        wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2())\n"
		"    {\n"
		"        wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Continuation_BracketsAttach_Break)
{
	// continuation lines
	// brackets=attach and input of broken brackets
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1())\n"
		"    {\n"
		"        wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2())\n"
		"    {\n"
		"        wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo() {\n"
		"    if (isFoo1()) {\n"
		"        wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2()) {\n"
		"        wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Continuation_BracketsAttach_Attach)
{
	// continuation lines
	// brackets=attach and input of attached brackets
	char text[] =
		"\nvoid foo() {\n"
		"    if (isFoo1()) {\n"
		"        wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2()) {\n"
		"        wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=attach";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Continuation_BracketsAttach_Horstmann)
{
	// continuation lines
	// brackets=attach and input of horstmann brackets
	char textIn[] =
		"\nvoid foo()\n"
		"{   if (isFoo1())\n"
		"    {   wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2())\n"
		"    {   wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo() {\n"
		"    if (isFoo1()) {\n"
		"        wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2()) {\n"
		"        wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Continuation_BracketsHorstmann_Break)
{
	// continuation lines
	// brackets=horstmann and input of broken brackets
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1())\n"
		"    {\n"
		"        wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2())\n"
		"    {\n"
		"        wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{   if (isFoo1())\n"
		"    {   wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2())\n"
		"    {   wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Continuation_BracketsHorstmann_Attach)
{
	// continuation lines
	// brackets=horstmann and input of attached brackets
	char textIn[] =
		"\nvoid foo() {\n"
		"    if (isFoo1()) {\n"
		"        wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2()) {\n"
		"        wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{   if (isFoo1())\n"
		"    {   wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2())\n"
		"    {   wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Continuation_BracketsHorstmann_Horstmann)
{
	// continuation lines
	// brackets=horstmann and input of horstmann brackets
	char text[] =
		"\nvoid foo()\n"
		"{   if (isFoo1())\n"
		"    {   wxPoint bar(Xpos,\n"
		"                    Ypos);\n"
		"    }\n"
		"    if (isFoo2())\n"
		"    {   wxPoint bar ( Xpos,\n"
		"                      Ypos);\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}


TEST(Continuation_InlineTab1)
{
	// continuation lines
	// with inline tabs

	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1())\n"
		"    {\n"
		"        wxPointx	barx	( Xpos,\n"
		"                              Ypos );\n"
		"\n"
		"        wxPointxx	barxx	( Xpos,\n"
		"                              Ypos );\n"
		"\n"
		"        wxPointxxx	barxxx	( Xpos,\n"
		"                              Ypos );\n"
		"\n"
		"        wxPointxxxx	barxxxx	( Xpos,\n"
		"                              Ypos );\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Continuation_InlineTab2)
{
	// continuation lines with tabs after the paren
	// with inline tabs
	// NOTE: this all aligns when the quotes are removed
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1())\n"
		"    {\n"
		"        wxPoint bar (	Xpos,\n"
		"                        Ypos );\n"
		"\n"
		"        wxPoint barx (	Xpos,\n"
		"                        Ypos );\n"
		"\n"
		"        wxPoint barxx (	Xpos,\n"
		"                        Ypos );\n"
		"\n"
		"        wxPoint barxxx (	Xpos,\n"
		"                            Ypos );\n"
		"\n"
		"        wxPoint barxx (		Xpos,\n"
		"                            Ypos );\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle Continuation Lines with Tabs
//----------------------------------------------------------------------------

TEST(ContinuationTab_BracketsNone_Break)
{
	// continuation lines with tabs
	// brackets=none and input of broken brackets
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"	if (isFoo1())\n"
		"	{\n"
		"		wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2())\n"
		"	{\n"
		"		wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(ContinuationTab_BracketsNone_Attach)
{
	// continuation lines with tabs
	// brackets=none and input of attached brackets
	char text[] =
		"\nvoid foo() {\n"
		"	if (isFoo1()) {\n"
		"		wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2()) {\n"
		"		wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(ContinuationTab_BracketsNone_Horstmann)
{
	// continuation lines with tabs
	// brackets=none and input of horstmann brackets
	char text[] =
		"\nvoid foo()\n"
		"{	if (isFoo1())\n"
		"	{	wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2())\n"
		"	{	wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(ContinuationTab_BracketsBreak_Break)
{
	// continuation lines with tabs
	// brackets=break and input of broken brackets
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"	if (isFoo1())\n"
		"	{\n"
		"		wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2())\n"
		"	{\n"
		"		wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char options[] = "brackets=break, indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(ContinuationTab_BracketsBreak_Attach)
{
	// continuation lines with tabs
	// brackets=break and input of attached brackets
	char textIn[] =
		"\nvoid foo() {\n"
		"	if (isFoo1()) {\n"
		"		wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2()) {\n"
		"		wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"	if (isFoo1())\n"
		"	{\n"
		"		wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2())\n"
		"	{\n"
		"		wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char options[] = "brackets=break, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(ContinuationTab_BracketsBreak_Horstmann)
{
	// continuation lines with tabs
	// brackets=break and input of horstmann brackets
	char textIn[] =
		"\nvoid foo()\n"
		"{	if (isFoo1())\n"
		"	{	wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2())\n"
		"	{	wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"	if (isFoo1())\n"
		"	{\n"
		"		wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2())\n"
		"	{\n"
		"		wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char options[] = "brackets=break, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(ContinuationTab_BracketsAttach_Break)
{
	// continuation lines with tabs
	// brackets=attach and input of broken brackets
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"	if (isFoo1())\n"
		"	{\n"
		"		wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2())\n"
		"	{\n"
		"		wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char text[] =
		"\nvoid foo() {\n"
		"	if (isFoo1()) {\n"
		"		wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2()) {\n"
		"		wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char options[] = "brackets=attach, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(ContinuationTab_BracketsAttach_Attach)
{
	// continuation lines with tabs
	// brackets=attach and input of attached brackets
	char text[] =
		"\nvoid foo() {\n"
		"	if (isFoo1()) {\n"
		"		wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2()) {\n"
		"		wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char options[] = "brackets=attach, indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(ContinuationTab_BracketsAttach_Horstmann)
{
	// continuation lines with tabs
	// brackets=attach and input of horstmann brackets
	char textIn[] =
		"\nvoid foo()\n"
		"{	if (isFoo1())\n"
		"	{	wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2())\n"
		"	{	wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char text[] =
		"\nvoid foo() {\n"
		"	if (isFoo1()) {\n"
		"		wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2()) {\n"
		"		wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char options[] = "brackets=attach, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(ContinuationTab_BracketsHorstmann_Break)
{
	// continuation lines with tabs
	// brackets=horstmann and input of broken brackets
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"	if (isFoo1())\n"
		"	{\n"
		"		wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2())\n"
		"	{\n"
		"		wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{	if (isFoo1())\n"
		"	{	wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2())\n"
		"	{	wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char options[] = "brackets=horstmann, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(ContinuationTab_BracketsHorstmann_Attach)
{
	// continuation lines with tabs
	// brackets=horstmann and input of attached brackets
	char textIn[] =
		"\nvoid foo() {\n"
		"	if (isFoo1()) {\n"
		"		wxPoint bar(Xpos,\n"
		"	            Ypos);\n"
		"	}\n"
		"	if (isFoo2()) {\n"
		"		wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{	if (isFoo1())\n"
		"	{	wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2())\n"
		"	{	wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char options[] = "brackets=horstmann, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(ContinuationTab_BracketsHorstmann_Horstmann)
{
	// continuation lines with tabs
	// brackets=horstmann and input of horstmann brackets
	char text[] =
		"\nvoid foo()\n"
		"{	if (isFoo1())\n"
		"	{	wxPoint bar(Xpos,\n"
		"		            Ypos);\n"
		"	}\n"
		"	if (isFoo2())\n"
		"	{	wxPoint bar ( Xpos,\n"
		"		              Ypos);\n"
		"	}\n"
		"}\n";
	char options[] = "brackets=horstmann, indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(ContinuationTab_InlineTab1)
{
	// continuation lines with tabs
	// with inline tabs
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"	if (isFoo1())\n"
		"	{\n"
		"		wxPointx	barx	( Xpos,\n"
		"		                      Ypos );\n"
		"\n"
		"		wxPointxx	barxx	( Xpos,\n"
		"		                      Ypos );\n"
		"\n"
		"		wxPointxxx	barxxx	( Xpos,\n"
		"		                      Ypos );\n"
		"\n"
		"		wxPointxxxx	barxxxx	( Xpos,\n"
		"		                      Ypos );\n"
		"	}\n"
		"}\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(ContinuationTab_InlineTab2)
{
	// continuation lines with tabs
	// with inline tabs after the paren
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"	if (isFoo1())\n"
		"	{\n"
		"		wxPoint bar (	Xpos,\n"
		"		                Ypos );\n"
		"\n"
		"		wxPoint barx (	Xpos,\n"
		"		                Ypos );\n"
		"\n"
		"		wxPoint barxx (	Xpos,\n"
		"		                Ypos );\n"
		"\n"
		"		wxPoint barxxx (	Xpos,\n"
		"		                    Ypos );\n"
		"\n"
		"		wxPoint barxx (		Xpos,\n"
		"		                    Ypos );\n"
		"	}\n"
		"}\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(ContinuationForceTab_InlineTab1)
{
	// continuation lines with force tabs
	// with inline tabs

	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"	if (isFoo1())\n"
		"	{\n"
		"		wxPointx	barx	( Xpos,\n"
		"							  Ypos );\n"
		"\n"
		"		wxPointxx	barxx	( Xpos,\n"
		"							  Ypos );\n"
		"\n"
		"		wxPointxxx	barxxx	( Xpos,\n"
		"							  Ypos );\n"
		"\n"
		"		wxPointxxxx	barxxxx	( Xpos,\n"
		"							  Ypos );\n"
		"	}\n"
		"}\n";
	char options[] = "indent=force-tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(ContinuationForceTab_InlineTab2)
{
	// continuation lines with force tabs
	// with inline tabs after the paren
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"	if (isFoo1())\n"
		"	{\n"
		"		wxPoint bar (	Xpos,\n"
		"						Ypos );\n"
		"\n"
		"		wxPoint barx (	Xpos,\n"
		"						Ypos );\n"
		"\n"
		"		wxPoint barxx (	Xpos,\n"
		"						Ypos );\n"
		"\n"
		"		wxPoint barxxx (	Xpos,\n"
		"							Ypos );\n"
		"\n"
		"		wxPoint barxx (		Xpos,\n"
		"							Ypos );\n"
		"	}\n"
		"}\n";
	char options[] = "indent=force-tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// C++ operators << and >>
//----------------------------------------------------------------------------

TEST(AlignmentOperator_Cout)
{
	// Alignment of the operator<<
	char text[] =
		"\nvoid foo(std::ostream& os)\n"
		"{\n"
		"    os << \"Foo\"\n"
		"       << \"Bar\"\n"
		"       << std::endl;\n"
		"\n"
		"    cout << \"Foo\"\n"
		"         << \"Bar\"\n"
		"         << std::endl;\n"
		"\n"
		"    helpText << wxT(\"text1\")\n"
		"             << wxT(\"text2\")\n"
		"             << wxT(\"text3\");\n"
		"\n"
		"    int i = 0;\n"
		"    if (i)\n"
		"        i = 0;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(AlignmentOperator_Cin)
{
	// Alignment of the operator<<
	char text[] =
		"\nvoid foo(std::istream& someinputstream)\n"
		"{\n"
		"    someinputstream >> \"Foo\"\n"
		"                    >> \"Bar\"\n"
		"                    >> std::endl;\n"
		"\n"
		"    cin >> \"Foo\"\n"
		"        >> \"Bar\"\n"
		"        >> std::endl;\n"
		"\n"
		"    int i = 0;\n"
		"    if (i)\n"
		"        i = 0;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(AlignmentOperator_CoutBeginLine)
{
	// Alignment of the operator<< when it begins the line
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    Context->m_EventsConnectingCode\n"
		"            << _T(\"Connect(\")\n"
		"            << m_EventArray[i].Type\n"
		"            << _T(\");\") << endl;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}


TEST(AlignmentOperator_Cout2)
{
	// Alignment of the operator<<
	char text[] =
		"\nstd::ostream& operator<<(std::ostream& os)\n"
		"{\n"
		"    os << foo\n"
		"       << std::endl;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle SQL
//----------------------------------------------------------------------------

TEST(SQL)
{
	// standard SQL statements
	char text[] =
		"\nEXEC SQL INCLUDE sqlca;\n"
		"\n"
		"void Connect()\n"
		"{\n"
		"    EXEC SQL BEGIN DECLARE SECTION;\n"
		"        char userid[64];\n"
		"        char password[64];\n"
		"        char *DBname = \"@ug\";\n"
		"    EXEC SQL END DECLARE SECTION;\n"
		"\n"
		"    EXEC SQL CONECT :userid IDENTIFIED BY :password;\n"
		"}\n"
		"\n"
		"void Insert_Branch()\n"
		"{\n"
		"    EXEC SQL INSERT\n"
		"             INTO   branch (branch_id, branch_name, branch_addr,\n"
		"                            branch_city, branch_phone)\n"
		"             VALUES (:bid, :bname, :baddr:baddr_ind);\n"
		"\n"
		"    EXEC SQL COMMIT WORK;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(SQL_Comment)
{
	// SQL statements with comment
	char text[] =
		"\nvoid Insert_Branch()\n"
		"{\n"
		"    EXEC SQL INSERT\n"
		"             /*\n"
		"              *\n"
		"              */\n"
		"             INTO   branch (branch_id, branch_name, branch_addr,\n"
		"                            branch_city, branch_phone)\n"
		"             VALUES (:bid, :bname, :baddr:baddr_ind);\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(SQL_LineComment)
{
	// SQL statements with line comment
	char text[] =
		"\nvoid Insert_Branch()\n"
		"{\n"
		"    EXEC SQL INSERT\n"
		"             //\n"
		"             INTO   branch (branch_id, branch_name, branch_addr,\n"
		"                            branch_city, branch_phone)\n"
		"             VALUES (:bid, :bname, :baddr:baddr_ind);\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(SQL_NonIndentingTabs)
{
	// SQL statements with non-indenting tabs
	char textIn[] =
		"\nvoid Insert_Branch()\n"
		"{\n"
		"  	 	  EXEC SQL INSERT\n"
		"	           INTO   branch (branch_id, branch_name, branch_addr,\n"
		"	 	  	   		  branch_city, branch_phone)\n"
		"    	       VALUES (:bid, :bname, :baddr:baddr_ind);\n"
		"}\n";
	char text[] =
		"\nvoid Insert_Branch()\n"
		"{\n"
		"    EXEC SQL INSERT\n"
		"         INTO   branch (branch_id, branch_name, branch_addr,\n"
		"                branch_city, branch_phone)\n"
		"         VALUES (:bid, :bname, :baddr:baddr_ind);\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(SQL_NonHangingIndent)
{
	// SQL statements with a non-hanging indent
	// should format as a block
	char textIn[] =
		"\nvoid Insert_Branch()\n"
		"{\n"
		"          EXEC SQL INSERT\n"
		"      INTO   branch (branch_id, branch_name, branch_addr,\n"
		"             branch_city, branch_phone)\n"
		"      VALUES (:bid, :bname, :baddr:baddr_ind);\n"
		"}\n";
	char text[] =
		"\nvoid Insert_Branch()\n"
		"{\n"
		"    EXEC SQL INSERT\n"
		"    INTO   branch (branch_id, branch_name, branch_addr,\n"
		"           branch_city, branch_phone)\n"
		"    VALUES (:bid, :bname, :baddr:baddr_ind);\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(SQL_LowerCaseExtraSpaces)
{
	// SQL statements in lower case with extra spaces
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"      exec  sql   begin   declare   section;\n"
		"      char userid[64];\n"
		"      char password[64];\n"
		"      exeC  SqL   End   Declare  Section;\n"
		"\n"
		"      Exec   Sql SELECT BLP_PIN_TYPE\n"
		"                 INTO :m_Pin_Type;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    exec  sql   begin   declare   section;\n"
		"        char userid[64];\n"
		"        char password[64];\n"
		"    exeC  SqL   End   Declare  Section;\n"
		"\n"
		"    Exec   Sql SELECT BLP_PIN_TYPE\n"
		"               INTO :m_Pin_Type;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(SQL_EndOfLine)
{
	// SQL statements with EXEC SQL at end of line
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    EXEC SQL\n"
		"         SELECT BLP_PIN_TYPE\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(SQL_BreakAfterSemi)
{
	// SQL statements should break line after the semi-colon
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    {\n"
		"        EXEC SQL SELECT BLP_PIN_TYPE,\n"
		"             INTO :m_Pin_Type;}\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    {\n"
		"        EXEC SQL SELECT BLP_PIN_TYPE,\n"
		"             INTO :m_Pin_Type;\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(SQL_Switch)
{
	// SQL statements in switch
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    switch (foo)\n"
		"    {\n"
		"    case 1:\n"
		"        EXEC SQL SELECT BLP_PIN_TYPE\n"
		"             INTO :m_Pin_Type;\n"
		"\n"
		"    case 2:\n"
		"    {\n"
		"        EXEC SQL SELECT BLP_PIN_TYPE\n"
		"             INTO :m_Pin_Type;\n"
		"    }\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(SQL_SwitchIndentCase)
{
	// SQL statements in switch with indent case
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    switch (foo)\n"
		"    {\n"
		"    case 1:\n"
		"        EXEC SQL SELECT BLP_PIN_TYPE\n"
		"             INTO :m_Pin_Type;\n"
		"\n"
		"    case 2:\n"
		"        {\n"
		"            EXEC SQL SELECT BLP_PIN_TYPE\n"
		"                 INTO :m_Pin_Type;\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "indent-cases";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(SQL_BracketsHorstmann)
{
	// SQL statements in horstmann brackets
	char text[] =
		"\nvoid foo()\n"
		"{   EXEC SQL SELECT BLP_PIN_TYPE\n"
		"             INTO :m_Pin_Type;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(SQL_Sans)
{
	// not SQL statements (macros?)
	// SQL statements will not be changed
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    EXEC\n"
		"        bar1();\n"
		"    EXEC SQX\n"
		"        bar2();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    EXEC\n"
		"    bar1();\n"
		"    EXEC SQX\n"
		"    bar2();\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle Assembler
//----------------------------------------------------------------------------

TEST(Assembler1)
{
	// embedded assembler
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    asm (\"\n"
		"         movl -4(%ebp), %eax	; comment1\n"
		"         sarl %ebx				; comment2\n"
		"         \");\n"
		"\n"
		"    if (foo()) {\n"
		"        asm(\"int3\"); /*trap*/\n"
		"    }\n"
		"\n"
		"    int data;\n"
		"    asm volatile (\"mcr\t\" \"14, 0, %0, c1, c0\"::\"r\" (data));\n"
		"\n"
		"    if (bar())\n"
		"        { asm(\"int3\"); }\n"
		"}\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(Assembler2)
{
	// embedded assembler
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    asm (\"sar1 %1\n"
		"         movl %1, %0\": \"=r\"(res[i]) :\"r\" (res[i]), \"memory\");\n"
		"\n"
		"    __asm__ (\"sarl %0\"\n"
		"             : \"=r\" (res[i]) :\"r\" (num[i]), \"r\" (num[i]): \"memory\");\n"
		"\n"
		"    asm (\"addl %%ebx, %%eax;\"\n"
		"         : \"=a\" (add)\n"
		"         : \"a\" (arg1), \"b\" (arg2) );\n"
		"\n"
		"    __asm__ (\"addl %%ebx, %%eax;\" : \"=a\" (add) : \"a\" (arg1), \"b\" (arg2));\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(AssemblerMS1)
{
	// microsoft specific embedded assembler
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    _asm mov eax, fs:[0x8]\n"
		"    __asm push edp\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(AssemblerMS2)
{
	// microsoft specific embedded assembler
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    _asm {\n"
		"        mov eax, fs:[0x8]\n"
		"        mov dx, 0xD007\n"
		"        out dx, al\n"
		"    }\n"
		"\n"
		"    __asm {\n"
		"        mov eax, fs:[0x8]\n"
		"        mov dx, 0xD007\n"
		"        out dx, al\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle Multiple Varables separated by commas
//----------------------------------------------------------------------------

TEST(MultipleVariableAssignments)
{
	// multiple assignments are aligned on the first variable
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bool bName  = false,\n"
		"         bFile  = true,\n"
		"         bSize  = true,\n"
		"         bWidth = false;\n"
		"\n"
		"    m_x = (D*E - B*F) / G,\n"
		"    m_y = (A*F - C*E) / G,\n"
		"    m_z = (A*G - F*B) / G;\n"
		"\n"
		"    double rstep = Red() / size, rf = 0,\n"
		"           gstep = Green() / size, gf = 0,\n"
		"           bstep = Blue() / size, bf = 0;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(MultipleVariableAssignments_Comments)
{
	// multiple assignments are aligned on the first variable
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bool bName   =  false,   // comment1\n"
		"         bFile   =  true,    // comment2\n"
		"         bSize   =  true,    // comment3\n"
		"         bWidth  =  false;   // comment4\n"
		"\n"
		"    bool bName   =  false,   /* comment1 */\n"
		"         bFile   =  true,    /* comment2 */\n"
		"         bSize   =  true,    /* comment3 */\n"
		"         bWidth  =  false;   /* comment4 */\n"
		"\n"
		"    bool bName   =  /* comment1 */ false,\n"
		"         bFile   =  /* comment2 */  true,\n"
		"         bSize   = true  /* comment3 */,\n"
		"         bWidth  = false /* comment3 */;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(MultipleVariableAssignments_Sans)
{
	// these are not multiple assignments
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    // functions are not multiple assignments\n"
		"    int code = GetCode(m_Header,\n"
		"                       m_Code,\n"
		"                       m_Language,\n"
		"                       false);\n"
		"\n"
		"    // arrays are not multiple assignments\n"
		"    bar[] = \"one\",\n"
		"            \"two\";\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}


TEST(MultipleVariable)
{
	// multiple variables are aligned on first variable
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    int var1,\n"
		"        var2,   // comment1\n"
		"        var3;   /* comment2 */\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(MultipleVariable_MultipleStatementsPerLine)
{
	// multiple variables with multiple statements per line
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxString m_bar1, m_bar2,\n"
		"             m_bar3, m_bar4,\n"
		"             m_bar5, m_bar6;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(MultipleVariable_ClassInitializer1)
{
	// class initializers are aligned on first variable
	char text[] =
		"\nFoo::Foo()\n"
		"    : m_bar1(0),\n"
		"      m_bar2(this, id),\n"
		"      m_bar3(0)\n"
		"{\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(MultipleVariable_ClassInitializer2)
{
	// class initializers are aligned on first variable
	// colon on previous line
	char text[] =
		"\nFoo::Foo() :\n"
		"    m_bar1(0),\n"
		"    m_bar2(this, id),\n"
		"    m_bar3(0)\n"
		"{\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(MultipleVariable_ClassInitializer3)
{
	// class initializers are aligned on first variable
	// multiple variables per line
	char text[] =
		"\nFoo::Foo()\n"
		"    : m_bar1(0), m_bar2(0),\n"
		"      m_bar3(0), m_bar4(0), m_bar5(0),\n"
		"      m_bar6(-100), m_bar7(50)\n"
		"{\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(MultipleVariable_ClassInitializer4)
{
	// class initializers are aligned on first variable
	// comments after comma
	char text[] =
		"\nFoo::Foo()\n"
		"    : m_FileGroups(*fgam), // comment\n"
		"      m_pOrigFileGroups(fgam),\n"
		"      m_LastListSelection(0)\n"
		"{\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(MultipleVariable_ClassInitializer5)
{
	// class initializers are aligned on first variable
	// last line with brackets should be indented
	char text[] =
		"\nFooBar(int width = 1, int style = wxSOLID,\n"
		"       int cap = wxCAP_ROUND)\n"
		"    : m_bar1(0), m_bar2(0),\n"
		"      m_bar3(0), m_bar4(0),\n"
		"      m_bar5(0), m_bar6(NULL) {}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(MultipleVariable_ClassInitializer6)
{
	// class initializers are aligned on first variable
	// this checks if the variables have been reset
	char text[] =
		"\nFoo1::Foo1()\n"
		"    : bar1(cmd),\n"
		"      bar2(driver),\n"
		"{}\n"
		"\n"
		"Foo2::Foo2()\n"
		"    : bar3(branch),\n"
		"      bar4(tree)\n"
		"{}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(MultipleVariable_Misc1)
{
	// this checks if the inStatementIndentStack is correctly popped
	char text[] =
		"\nListBoxImpl::ListBoxImpl()\n"
		"    : unicodeMode(false),\n"
		"      desiredVisibleRows(5)\n"
		"{\n"
		"}\n"
		"\n"
		"void ListBoxImpl::Create (Window &parent,\n"
		"                          int lineHeight_) {\n"
		"    lineHeight =  lineHeight_;\n"
		"}\n"
		"\n"
		"long Platform::SendScintilla(WindowID w,\n"
		"                             unsigned long wParam,\n"
		"                             long lParam) {\n"
		"    wxScintilla* sci = (wxScintilla*)w;\n"
		"    return sci->SendMsg(msg, wParam, lParam);\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

TEST(MultipleVariable_Misc2)
{
	// this checks for various conditions in getInStatementIndentComma()
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    int\n"
		"    var1\n"
		"    ,\n"
		"    var2;\n"
		"}\n"
		"\n"
		"void foo()\n"
		"{\n"
		"    int\n"
		"    var1,\n"
		"    var2\n"
		"    , var3;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	CHECK_EQUAL(text, textOut);
	delete [] textOut;
}

