//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleTest.h"

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace
{

//-------------------------------------------------------------------------
// AStyle Break Blocks
//-------------------------------------------------------------------------

TEST(BreakBlocks, LongOption)
{
	// simple break blocks test
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"    fooBar1 = 1;\n"
		"    fooBar2 = 2;\n"
		"    fooBar3 = 3;\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        Bar2();\n"
		"    }\n"
		"    fooBar1 = 1;\n"
		"    fooBar2 = 2;\n"
		"    fooBar3 = 3;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"\n"
		"    fooBar1 = 1;\n"
		"    fooBar2 = 2;\n"
		"    fooBar3 = 3;\n"
		"\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        Bar2();\n"
		"    }\n"
		"\n"
		"    fooBar1 = 1;\n"
		"    fooBar2 = 2;\n"
		"    fooBar3 = 3;\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, ShortOption)
{
	// simple break blocks short option test
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"    fooBar1 = 1;\n"
		"    fooBar2 = 2;\n"
		"    fooBar3 = 3;\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        Bar2();\n"
		"    }\n"
		"    fooBar1 = 1;\n"
		"    fooBar2 = 2;\n"
		"    fooBar3 = 3;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"\n"
		"    fooBar1 = 1;\n"
		"    fooBar2 = 2;\n"
		"    fooBar3 = 3;\n"
		"\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        Bar2();\n"
		"    }\n"
		"\n"
		"    fooBar1 = 1;\n"
		"    fooBar2 = 2;\n"
		"    fooBar3 = 3;\n"
		"}\n";
	char options[] = "-f";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, WithBrackets)
{
	// break blocks with preceding and following brackets
	// should NOT braek before brackets
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        Bar2();\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        Bar2();\n"
		"    }\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, WithElse)
{
	// break blocks with 'else' statement
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"    else\n"
		"        Bar2();\n"
		"    fooBar1 = 1;\n"
		"    fooBar2 = 2;\n"
		"    fooBar3 = 3;\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        Bar2();\n"
		"    }\n"
		"    else\n"
		"    {\n"
		"        Bar2();\n"
		"    }\n"
		"    fooBar1 = 1;\n"
		"    fooBar2 = 2;\n"
		"    fooBar3 = 3;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"    else\n"
		"        Bar2();\n"
		"\n"
		"    fooBar1 = 1;\n"
		"    fooBar2 = 2;\n"
		"    fooBar3 = 3;\n"
		"\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        Bar2();\n"
		"    }\n"
		"    else\n"
		"    {\n"
		"        Bar2();\n"
		"    }\n"
		"\n"
		"    fooBar1 = 1;\n"
		"    fooBar2 = 2;\n"
		"    fooBar3 = 3;\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, WithForLoop)
{
	// break blocks with 'for' loops
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar1 = 1;\n"
		"    for (int i=0; i<fooMax; ++i)\n"
		"        bar1++;\n"
		"    fooBar2 = 2;\n"
		"    for (int i=0; i<fooMax; ++i)\n"
		"    {\n"
		"        bar2++;\n"
		"    }\n"
		"    fooBar3 = 3;\n"
		"    for (int i=0; i<fooMax; ++i)\n"
		"        if (isBar)\n"
		"            bar3++;\n"
		"    fooBar4 = 4;\n"
		"    for (int i=0; i<getMax(); ++i)\n"
		"        if (isBar)\n"
		"            bar4++;\n"
		"    fooBar5 = 5;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar1 = 1;\n"
		"\n"
		"    for (int i=0; i<fooMax; ++i)\n"
		"        bar1++;\n"
		"\n"
		"    fooBar2 = 2;\n"
		"\n"
		"    for (int i=0; i<fooMax; ++i)\n"
		"    {\n"
		"        bar2++;\n"
		"    }\n"
		"\n"
		"    fooBar3 = 3;\n"
		"\n"
		"    for (int i=0; i<fooMax; ++i)\n"
		"        if (isBar)\n"
		"            bar3++;\n"
		"\n"
		"    fooBar4 = 4;\n"
		"\n"
		"    for (int i=0; i<getMax(); ++i)\n"
		"        if (isBar)\n"
		"            bar4++;\n"
		"\n"
		"    fooBar5 = 5;\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, WithSwitch1)
{
	// Break blocks with 'switch' statement.
	// Case starements with NO brackets are broken.
	char textIn[] =
		"\nvoid fooFunction()\n"
		"{\n"
		"    switch (x) {\n"
		"    case (a + b) * c:\n"
		"        foo = 4;\n"
		"        foo = 5;\n"
		"        break;\n"
		"    default:\n"
		"        foo = 6;\n"
		"        break;\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid fooFunction()\n"
		"{\n"
		"    switch (x) {\n"
		"    case (a + b) * c:\n"
		"        foo = 4;\n"
		"        foo = 5;\n"
		"        break;\n"
		"\n"
		"    default:\n"
		"        foo = 6;\n"
		"        break;\n"
		"    }\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, WithSwitch2)
{
	// Break blocks with 'switch' statement.
	// Case starements WITH brackets are broken.
	// Break statements are INSIDE the brackets.
	char textIn[] =
		"\nvoid fooFunction()\n"
		"{\n"
		"    switch (x) {\n"
		"    case (a + b) * c:\n"
		"    {\n"
		"        foo = 4;\n"
		"        foo = 5;\n"
		"        break;\n"
		"    }\n"
		"    default:\n"
		"    {\n"
		"        foo = 6;\n"
		"        break;\n"
		"    }\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid fooFunction()\n"
		"{\n"
		"    switch (x) {\n"
		"    case (a + b) * c:\n"
		"    {\n"
		"        foo = 4;\n"
		"        foo = 5;\n"
		"        break;\n"
		"    }\n"
		"\n"
		"    default:\n"
		"    {\n"
		"        foo = 6;\n"
		"        break;\n"
		"    }\n"
		"    }\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, WithSwitch3)
{
	// Break blocks with 'switch' statement.
	// Case starements WITH brackets are broken.
	// Break statements are OUTSIDE the brackets.
	char textIn[] =
		"\nvoid fooFunction()\n"
		"{\n"
		"    switch (x) {\n"
		"    case (a + b) * c:\n"
		"    {\n"
		"        foo = 4;\n"
		"        foo = 5;\n"
		"    }\n"
		"        break;\n"
		"    default:\n"
		"    {\n"
		"        foo = 6;\n"
		"    }\n"
		"        break;\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid fooFunction()\n"
		"{\n"
		"    switch (x) {\n"
		"    case (a + b) * c:\n"
		"    {\n"
		"        foo = 4;\n"
		"        foo = 5;\n"
		"    }\n"
		"    break;\n"
		"\n"
		"    default:\n"
		"    {\n"
		"        foo = 6;\n"
		"    }\n"
		"    break;\n"
		"    }\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, WithSwitch4)
{
	// Break blocks with 'switch' statement.
	// Multiple fsll-thru case statements with no bracket.
	char textIn[] =
		"\nvoid fooFunction()\n"
		"{\n"
		"    switch (nr)\n"
		"    {\n"
		"    case '0':\n"
		"    case '1':\n"
		"    case '2':\n"
		"    case '3':\n"
		"    case '4':\n"
		"        nr = xr;\n"
		"        break;\n"
		"    case 5:\n"
		"    default:\n"
		"        nr = current_size;\n"
		"    }\n"
		"}";
	char text[] =
		"\nvoid fooFunction()\n"
		"{\n"
		"    switch (nr)\n"
		"    {\n"
		"    case '0':\n"
		"    case '1':\n"
		"    case '2':\n"
		"    case '3':\n"
		"    case '4':\n"
		"        nr = xr;\n"
		"        break;\n"
		"\n"
		"    case 5:\n"
		"    default:\n"
		"        nr = current_size;\n"
		"    }\n"
		"}";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, WithPreprocessor)
{
	// do NOT break blocks at a preprocessor directive
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"#ifdef fooDef\n"
		"    if (isBar1)\n"
		"        fooBar1();\n"
		"#else\n"
		"    if (isBar2)\n"
		"        fooBar2();\n"
		"#endif\n"
		"    if (isBar3)\n"
		"        fooBar3();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"#ifdef fooDef\n"
		"\n"
		"    if (isBar1)\n"
		"        fooBar1();\n"
		"\n"
		"#else\n"
		"\n"
		"    if (isBar2)\n"
		"        fooBar2();\n"
		"\n"
		"#endif\n"
		"\n"
		"    if (isBar3)\n"
		"        fooBar3();\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, WithEolComment1)
{
	// the block after an end of eol comment should be broken
	// even if it starts  with a comment
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar1(); // eol comment 1\n"
		"    // comment 1\n"
		"    if (isFoo)\n"
		"        bar1(); // eol comment 2\n"
		"    // comment 2\n"
		"    else\n"
		"        bar2(); // eol comment 3\n"
		"    // comment 3\n"
		"    bar3();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar1(); // eol comment 1\n"
		"\n"
		"    // comment 1\n"
		"    if (isFoo)\n"
		"        bar1(); // eol comment 2\n"
		"    // comment 2\n"
		"    else\n"
		"        bar2(); // eol comment 3\n"
		"\n"
		"    // comment 3\n"
		"    bar3();\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, WithEolComment2)
{
	// the block after an end of eol comment should be broken
	// even if it starts  with a comment
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar1(); /* eol comment 1 */\n"
		"    /* comment 1 */\n"
		"    if (isFoo)\n"
		"        bar1(); /* eol comment 2 */\n"
		"    /* comment 2 */\n"
		"    else\n"
		"        bar2(); /* eol comment 3 */\n"
		"    /* comment 3 */\n"
		"    bar3();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar1(); /* eol comment 1 */\n"
		"\n"
		"    /* comment 1 */\n"
		"    if (isFoo)\n"
		"        bar1(); /* eol comment 2 */\n"
		"    /* comment 2 */\n"
		"    else\n"
		"        bar2(); /* eol comment 3 */\n"
		"\n"
		"    /* comment 3 */\n"
		"    bar3();\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, WithComment1)
{
	// blocks with comments are correctly broken
	// and should not be changed
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar1 = 1;\n"
		"\n"
		"    // comment one\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"    else\n"
		"        Bar2();\n"
		"\n"
		"    fooBar2 = 2;\n"
		"\n"
		"    /* comment two */\n"
		"    if (isFoo2) {\n"
		"        Bar3();\n"
		"    } else {\n"
		"        Bar4();\n"
		"    }\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, WithComment2)
{
	// blocks with comments beginning the line
	// should be broken
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar1 = 1;\n"
		"    // comment one\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"    else\n"
		"        Bar2();\n"
		"    fooBar2 = 2;\n"
		"    /* comment two */\n"
		"    if (isFoo2) {\n"
		"        Bar3();\n"
		"    } else {\n"
		"        Bar4();\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar1 = 1;\n"
		"\n"
		"    // comment one\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"    else\n"
		"        Bar2();\n"
		"\n"
		"    fooBar2 = 2;\n"
		"\n"
		"    /* comment two */\n"
		"    if (isFoo2) {\n"
		"        Bar3();\n"
		"    } else {\n"
		"        Bar4();\n"
		"    }\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, WithComment3)
{
	// blocks with comments not beginning the line
	// should be broken
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar1 = 1;  // comment one\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"    else\n"
		"        Bar2();\n"
		"    fooBar2 = 2;  /* comment two */\n"
		"    if (isFoo2) {\n"
		"        Bar3();\n"
		"    } else {\n"
		"        Bar4();\n"
		"    }\n"
		"    fooBar3 = 3;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar1 = 1;  // comment one\n"
		"\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"    else\n"
		"        Bar2();\n"
		"\n"
		"    fooBar2 = 2;  /* comment two */\n"
		"\n"
		"    if (isFoo2) {\n"
		"        Bar3();\n"
		"    } else {\n"
		"        Bar4();\n"
		"    }\n"
		"\n"
		"    fooBar3 = 3;\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, WithComment4)
{
	// blocks with comments should be broken
	// leaving comments with the blocks
	// but closing headers should NOT be broken
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar1 = 1;\n"
		"    // comment one\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"    // comment two\n"
		"    else\n"
		"        Bar2();\n"
		"    fooBar2 = 2;\n"
		"    /* comment three */\n"
		"    if (isFoo3)\n"
		"    {\n"
		"        Bar3();\n"
		"    }\n"
		"    /* comment four */\n"
		"    else\n"
		"        Bar4();\n"
		"    fooBar3 = 3;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar1 = 1;\n"
		"\n"
		"    // comment one\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"    // comment two\n"
		"    else\n"
		"        Bar2();\n"
		"\n"
		"    fooBar2 = 2;\n"
		"\n"
		"    /* comment three */\n"
		"    if (isFoo3)\n"
		"    {\n"
		"        Bar3();\n"
		"    }\n"
		"    /* comment four */\n"
		"    else\n"
		"        Bar4();\n"
		"\n"
		"    fooBar3 = 3;\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, WithComment5)
{
	// blocks with comments should be broken
	// leaving comments with the blocks
	// test mixing comments and line comments
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar();\n"
		"    /* comment1 */\n"
		"    // comment2\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"    fooBar();\n"
		"    /* comment1 */\n"
		"    // comment2\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar();\n"
		"\n"
		"    /* comment1 */\n"
		"    // comment2\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"\n"
		"    fooBar();\n"
		"\n"
		"    /* comment1 */\n"
		"    // comment2\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, Sans1)
{
	// don't break bocks for preDefinitionHeaders (namespace, class...)
	// don't break bocks for access modifiers (public, private, protected)
	//     when keep-one-line-statements is used.
	char text[] =
		"\nnamespace astyle\n"
		"{\n"
		"class ASSourceIterator\n"
		"{\n"
		"public:\n"
		"    ASSourceIterator() {}\n"
		"};\n"
		"\n"
		"class ASResource\n"
		"{\n"
		"public:\n"
		"    ASResource() {}\n"
		"};\n"
		"}\n";
	char options[] = "break-blocks, keep-one-line-statements, keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, Sans2)
{
	// don't break blocks for C# 'get' and 'set' or 'add' and 'remove'
	char text[] =
		"\npublic class TextEditor : ITextEditor\n"
		"{\n"
		"    public event KeyEventHandler KeyPress {\n"
		"        add { textArea.KeyEventHandler += value; }\n"
		"        remove { textArea.KeyEventHandler -= value; }\n"
		"    }\n"
		"\n"
		"    public IndentStyle IndentStyle {\n"
		"        get { return textEditorControl.IndentStyle; }\n"
		"        set { SetIndentStyle(value); }\n"
		"    }\n"
		"}\n";
	char options[] = "break-blocks, keep-one-line-blocks, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakBlocks, Sans3)
{
	// don't break blocks if comment is not followed by a header
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar1 = 1;\n"
		"    // comment one\n"
		"    fooBar2 = 2;\n"
		"}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Break All Blocks
//-------------------------------------------------------------------------

TEST(BreakAllBlocks, LongOption)
{
	// simple break all blocks test
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"    else\n"
		"        Bar2();\n"
		"    fooBar1 = 1;\n"
		"    if (isFoo2) {\n"
		"        Bar1();\n"
		"    }\n"
		"    else {\n"
		"        Bar2();\n"
		"    }\n"
		"    fooBar2 = 2;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"\n"
		"    else\n"
		"        Bar2();\n"
		"\n"
		"    fooBar1 = 1;\n"
		"\n"
		"    if (isFoo2) {\n"
		"        Bar1();\n"
		"    }\n"
		"\n"
		"    else {\n"
		"        Bar2();\n"
		"    }\n"
		"\n"
		"    fooBar2 = 2;\n"
		"}\n";
	char options[] = "break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakAllBlocks, ShortOption)
{
	// simple break all blocks short option test
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"    else\n"
		"        Bar2();\n"
		"    fooBar1 = 1;\n"
		"    if (isFoo2) {\n"
		"        Bar1();\n"
		"    }\n"
		"    else {\n"
		"        Bar2();\n"
		"    }\n"
		"    fooBar2 = 2;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"\n"
		"    else\n"
		"        Bar2();\n"
		"\n"
		"    fooBar1 = 1;\n"
		"\n"
		"    if (isFoo2) {\n"
		"        Bar1();\n"
		"    }\n"
		"\n"
		"    else {\n"
		"        Bar2();\n"
		"    }\n"
		"\n"
		"    fooBar2 = 2;\n"
		"}\n";
	char options[] = "-F";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakAllBlocks, BreakBrackets)
{
	// test break all blocks with break brackets
	char textIn[] =
		"\nvoid foo() {\n"
		"    bar1();\n"
		"    if (isBar) {  // comment\n"
		"        bar2();\n"
		"        return;\n"
		"    }\n"
		"    bar3();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar1();\n"
		"\n"
		"    if (isBar)    // comment\n"
		"    {\n"
		"        bar2();\n"
		"        return;\n"
		"    }\n"
		"\n"
		"    bar3();\n"
		"}\n";
	char options[] = "break-blocks=all, brackets=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakAllBlocks, AttachBrackets)
{
	// test break all blocks with attach brackets
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar1();\n"
		"    if (isBar)   // comment\n"
		"    {\n"
		"        bar2();\n"
		"        return;\n"
		"    }\n"
		"    bar3();\n"
		"}\n";
	char text[] =
		"\nvoid foo() {\n"
		"    bar1();\n"
		"\n"
		"    if (isBar) { // comment\n"
		"        bar2();\n"
		"        return;\n"
		"    }\n"
		"\n"
		"    bar3();\n"
		"}\n";
	char options[] = "break-blocks=all, brackets=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakAllBlocks, WithDoWhile)
{
	// break all blocks with do-while
	// closing while should NOT be broken from the block
	// but the following statement should be broken
	char textIn[] =
		"void Foo()\n"
		"{\n"
		"    do\n"
		"    {\n"
		"        bar1();\n"
		"    }\n"
		"    while (false);\n"
		"    bar2();\n"
		"}\n";
	char text[] =
		"void Foo()\n"
		"{\n"
		"    do\n"
		"    {\n"
		"        bar1();\n"
		"    }\n"
		"    while (false);\n"
		"\n"
		"    bar2();\n"
		"}\n";
	char options[] = "break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakAllBlocks, WithEolComment)
{
	// the block after an end of eol comment should be broken
	// even if it starts  with a comment
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar1(); // eol comment 1\n"
		"    // comment 1\n"
		"    if (isFoo)\n"
		"        bar1(); // eol comment 2\n"
		"    // comment 2\n"
		"    else\n"
		"        bar2(); // eol comment 3\n"
		"    // comment 3\n"
		"    bar3();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar1(); // eol comment 1\n"
		"\n"
		"    // comment 1\n"
		"    if (isFoo)\n"
		"        bar1(); // eol comment 2\n"
		"\n"
		"    // comment 2\n"
		"    else\n"
		"        bar2(); // eol comment 3\n"
		"\n"
		"    // comment 3\n"
		"    bar3();\n"
		"}\n";
	char options[] = "break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakAllBlocks, WithEolComment2)
{
	// the block after an end of eol comment should be broken
	// even if it starts  with a comment
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar1(); /* eol comment 1 */\n"
		"    /* comment 1 */\n"
		"    if (isFoo)\n"
		"        bar1(); /* eol comment 2 */\n"
		"    /* comment 2 */\n"
		"    else\n"
		"        bar2(); /* eol comment 3 */\n"
		"    /* comment 3 */\n"
		"    bar3();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar1(); /* eol comment 1 */\n"
		"\n"
		"    /* comment 1 */\n"
		"    if (isFoo)\n"
		"        bar1(); /* eol comment 2 */\n"
		"\n"
		"    /* comment 2 */\n"
		"    else\n"
		"        bar2(); /* eol comment 3 */\n"
		"\n"
		"    /* comment 3 */\n"
		"    bar3();\n"
		"}\n";
	char options[] = "break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakAllBlocks, WithComment1)
{
	// blocks with comments are correctly broken
	// and should not be changed
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    // comment\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"\n"
		"    // comment\n"
		"    else\n"
		"        Bar1();\n"
		"\n"
		"    /* comment */\n"
		"    if (isFoo2) {\n"
		"        Bar2();\n"
		"    }\n"
		"\n"
		"    /* comment */\n"
		"    else {\n"
		"        Bar2();\n"
		"    }\n"
		"}\n";
	char options[] = "break-blocks=all";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakAllBlocks, WithComment2)
{
	// blocks with comments not beginning the line
	// should be broken
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar0 = 0;\n"
		"    if (isFoo1) {\n"
		"        Bar1();\n"
		"    }            // comment one\n"
		"    else\n"
		"        Bar2();\n"
		"    fooBar1 = 1;\n"
		"    if (isFoo2) {\n"
		"        Bar1();\n"
		"    }            /* comment two */\n"
		"    else {\n"
		"        Bar2();\n"
		"    }\n"
		"    fooBar2 = 2;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar0 = 0;\n"
		"\n"
		"    if (isFoo1) {\n"
		"        Bar1();\n"
		"    }            // comment one\n"
		"\n"
		"    else\n"
		"        Bar2();\n"
		"\n"
		"    fooBar1 = 1;\n"
		"\n"
		"    if (isFoo2) {\n"
		"        Bar1();\n"
		"    }            /* comment two */\n"
		"\n"
		"    else {\n"
		"        Bar2();\n"
		"    }\n"
		"\n"
		"    fooBar2 = 2;\n"
		"}\n";
	char options[] = "break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakAllBlocks, WithComment3)
{
	// blocks with comments should be broken
	// leaving comments with the blocks
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    // comment\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"    // comment\n"
		"    else\n"
		"        Bar1();\n"
		"    /* comment */\n"
		"    if (isFoo2) {\n"
		"        Bar2();\n"
		"    }\n"
		"    /* comment */\n"
		"    else {\n"
		"        Bar2();\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    // comment\n"
		"    if (isFoo1)\n"
		"        Bar1();\n"
		"\n"
		"    // comment\n"
		"    else\n"
		"        Bar1();\n"
		"\n"
		"    /* comment */\n"
		"    if (isFoo2) {\n"
		"        Bar2();\n"
		"    }\n"
		"\n"
		"    /* comment */\n"
		"    else {\n"
		"        Bar2();\n"
		"    }\n"
		"}\n";
	char options[] = "break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakAllBlocks, AfterComment1)
{
	// closing block should break after a comment
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1) {\n"
		"        Bar1();\n"
		"        // comment\n"
		"    } else {\n"
		"        Bar2();\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1) {\n"
		"        Bar1();\n"
		"        // comment\n"
		"\n"
		"    } else {\n"
		"        Bar2();\n"
		"    }\n"
		"}\n";
	char options[] = "break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakAllBlocks, AfterComment2)
{
	// closing block should break after a comment
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1) {\n"
		"        Bar1();\n"
		"        // comment\n"
		"    } else {\n"
		"        Bar2();\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1) {\n"
		"        Bar1();\n"
		"        // comment\n"
		"\n"
		"    } else {\n"
		"        Bar2();\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=linux, break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakAllBlocks, AfterComment3)
{
	// closing block should break after a comment
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1)\n {\n"
		"        Bar1();\n"
		"        // comment\n"
		"    } else {\n"
		"        Bar2();\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"    {\n"
		"        Bar1();\n"
		"        // comment\n"
		"    }\n"
		"\n"
		"    else\n"
		"    {\n"
		"        Bar2();\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=break, break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Pad Operator
//-------------------------------------------------------------------------

TEST(PadOperator, LongOption)
{
	// all operators should be tested
	// test sequence is the same as ASResource::buildOperators
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    a+=b;\n"
		"    a-=b;\n"
		"    a*=b;\n"
		"    a/=b;\n"
		"    a%=b;\n"
		"    a|=b;\n"
		"    a&=b;\n"
		"    a^=b;\n"
		"    a==b;\n"
		"    a--;\n"       // should not pad
		"    a++;\n"       // should not pad
		"    --b;\n"       // should not pad
		"    ++b;\n"       // should not pad
		"    a!=b;\n"
		"    a>=b;\n"
		"    a>>>=b;\n"
		"    a>>=b;\n"
		"    a>>>b;\n"
		"    a>>b;\n"
		"    a<=b;\n"
		"    a<<<=b;\n"
		"    a<<=b;\n"
		"    a<<<b;\n"
		"    a<<b;\n"
		"    a??b;\n"
		"    a=>b;\n"
		"    a<?b;\n"
		"    a>?b;\n"
		"    a->b;\n"      // should not pad
		"    a&&b;\n"
		"    a||b;\n"
		"    a::b;\n"      // should not pad
		"    a+b;\n"
		"    a-b;\n"
		"    x=a*b;\n"     // without the equal sign it is a pointer
		"    a/b;\n"
		"    a%b;\n"
		"    x=a?b:c;\n"   // without the equal sign ':' is a label
		"    a=b;\n"
		"    a<b;\n"
		"    a>b;\n"
		"    x=a^b;\n"
		"    a|b;\n"
		"    x=a&b;\n"     // without the equal sign it is a reference
		"}\n";             // 'operator' and 'return' are not tested
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    a += b;\n"
		"    a -= b;\n"
		"    a *= b;\n"
		"    a /= b;\n"
		"    a %= b;\n"
		"    a |= b;\n"
		"    a &= b;\n"
		"    a ^= b;\n"
		"    a == b;\n"
		"    a--;\n"         // should not pad
		"    a++;\n"         // should not pad
		"    --b;\n"         // should not pad
		"    ++b;\n"         // should not pad
		"    a != b;\n"
		"    a >= b;\n"
		"    a >>>= b;\n"
		"    a >>= b;\n"
		"    a >>> b;\n"
		"    a >> b;\n"
		"    a <= b;\n"
		"    a <<<= b;\n"
		"    a <<= b;\n"
		"    a <<< b;\n"
		"    a << b;\n"
		"    a ?? b;\n"
		"    a => b;\n"
		"    a <? b;\n"
		"    a >? b;\n"
		"    a->b;\n"        // should not pad
		"    a && b;\n"
		"    a || b;\n"
		"    a::b;\n"        // should not pad
		"    a + b;\n"
		"    a - b;\n"
		"    x = a * b;\n"   // without the equal sign it is a pointer
		"    a / b;\n"
		"    a % b;\n"
		"    x = a ? b : c;\n" // without the equal sign ':' is a label
		"    a = b;\n"
		"    a < b;\n"
		"    a > b;\n"
		"    x = a ^ b;\n"
		"    a | b;\n"
		"    x = a & b;\n"   // without the equal sign it is a reference
		"}\n";               // 'operator' and 'return' are not tested
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, ShortOption)
{
	// test pad operators short option
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    x=a+b-((c*d)/e);\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    x = a + b - ((c * d) / e);\n"
		"}\n";
	char options[] = "-p";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Return)
{
	// operators following a "return" statement should be padded
	// a "return" is the same as an assignment operator
	// but do not pad a pointer dereference or "address of"
	char textIn[] =
		"\nint foo()\n"
		"{\n"
		"    // should pad\n"
		"    return a*b;\n"
		"    return a&b;\n"
		"    return (a*b);\n"
		"    return (a&b);\n"
		"    // should NOT pad\n"
		"    return *p;\n"
		"    return &p;\n"
		"    return (*p);\n"
		"    return (&p);\n"
		"}\n";
	char text[] =
		"\nint foo()\n"
		"{\n"
		"    // should pad\n"
		"    return a * b;\n"
		"    return a & b;\n"
		"    return (a * b);\n"
		"    return (a & b);\n"
		"    // should NOT pad\n"
		"    return *p;\n"
		"    return &p;\n"
		"    return (*p);\n"
		"    return (&p);\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Misc1)
{
	// more pad operators tests
	char textIn[] =
		"\nbool operator== (fooBar& a, fooBar &b);\n"
		"bool operator== (fooBar* a, fooBar *b);\n"
		"\n"
		"void foo(pdfColour& a, pdfColour &b)\n"
		"{\n"
		"    xxx=new yyy(zzz,_(\"XXX\"),_T(\"YYY\"));\n"
		"\n"
		"    while (*p=='x'||*p=='y')\n"
		"        ++p;\n"
		"\n"
		"    if (*sl==s) *sl=t;\n"
		"\n"
		"    setProperty(\"md5 \"+md5Count);\n"
		"\n"
		"    return (i-m+1);\n"
		"    *end=endAlt;\n"
		"    return &end;\n"
		"}\n";
	char text[] =
		"\nbool operator== (fooBar& a, fooBar &b);\n"
		"bool operator== (fooBar* a, fooBar *b);\n"
		"\n"
		"void foo(pdfColour& a, pdfColour &b)\n"
		"{\n"
		"    xxx = new yyy(zzz, _(\"XXX\"), _T(\"YYY\"));\n"
		"\n"
		"    while (*p == 'x' || *p == 'y')\n"
		"        ++p;\n"
		"\n"
		"    if (*sl == s) *sl = t;\n"
		"\n"
		"    setProperty(\"md5 \" + md5Count);\n"
		"\n"
		"    return (i - m + 1);\n"
		"    *end = endAlt;\n"
		"    return &end;\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Misc2)
{
	// more pad operators tests
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (len>cap||cap>3*(len+8))\n"
		"        len=1;\n"
		"    wxChar c[2] = { j>>0&0xFF, j>>8&0xFF };\n"
		"    curpos=(curpos+8)&0xfff8;\n"
		"    recalc(h+2*m, v+1);\n"
		"    xxx=((Index>=0)&(Index<GetResourcesCount()));\n"
		"\n"
		"    setForce(GetGravityFactor()*-9.8f);\n"
		"    setForce(GetGravityFactor()*+9.8f);\n"
		"    setForce(GetGravityFactor()*9.8f);\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (len > cap || cap > 3 * (len + 8))\n"
		"        len = 1;\n"
		"    wxChar c[2] = { j >> 0 & 0xFF, j >> 8 & 0xFF };\n"
		"    curpos = (curpos + 8) & 0xfff8;\n"
		"    recalc(h + 2 * m, v + 1);\n"
		"    xxx = ((Index >= 0) & (Index < GetResourcesCount()));\n"
		"\n"
		"    setForce(GetGravityFactor() * -9.8f);\n"
		"    setForce(GetGravityFactor() * +9.8f);\n"
		"    setForce(GetGravityFactor() * 9.8f);\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Misc3)
{
	// pad operators with <> separated by && or ||
	// it is not a template
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (age<3.0f&&age>0.0f)\n"
		"        setValue(age/3.0f);\n"
		"\n"
		"    if (age<3.0f||age>0.0f)\n"
		"        setValue(age/3.0f);\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (age < 3.0f && age > 0.0f)\n"
		"        setValue(age / 3.0f);\n"
		"\n"
		"    if (age < 3.0f || age > 0.0f)\n"
		"        setValue(age / 3.0f);\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Misc4)
{
	// pad operators with following (
	// the * should be padded
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    memmove(\n"
		"        body1,\n"
		"        body2,\n"
		"        sizeof(T)*(position-part1Length));\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    memmove(\n"
		"        body1,\n"
		"        body2,\n"
		"        sizeof(T) * (position - part1Length));\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Misc5)
{
	// test C# ? operator and nullable types
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    int? bar;\n"
		"    (bar==1)?\"topic\":\"topics\";\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    int? bar;\n"
		"    (bar == 1) ? \"topic\" : \"topics\";\n"
		"}\n";
	char options[] = "pad-oper, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Misc6)
{
	// test pad operator in a one-line "case" statement
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    swtch (bar)\n"
		"    {\n"
		"    case _OP_COMPARITH: DerefInc(((arg1&0xFFFF0000)>>16), (arg1&0x0000FFFF), false); continue;\n"
		"    default: continue;\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    swtch (bar)\n"
		"    {\n"
		"    case _OP_COMPARITH: DerefInc(((arg1 & 0xFFFF0000) >> 16), (arg1 & 0x0000FFFF), false); continue;\n"
		"    default: continue;\n"
		"    }\n"
		"}\n";
	char options[] = "pad-oper, keep-one-line-statements";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Misc7)
{
	// test pad operator in an IF statement
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (iPages*ROWS_PAGE != iDatas)\n"
		"        iPages+=1;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (iPages * ROWS_PAGE != iDatas)\n"
		"        iPages += 1;\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Sans1)
{
	// do not pad a pointer dereference or "address of"
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    // should pad\n"
		"    x = a*b;\n"
		"    x = (a*b);\n"
		"    x = a&b;\n"
		"    x = (a&b);\n"
		"    // should NOT pad\n"
		"    x = *p;\n"
		"    x = &p;\n"
		"    x = (*p);\n"
		"    x = (&p);\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    // should pad\n"
		"    x = a * b;\n"
		"    x = (a * b);\n"
		"    x = a & b;\n"
		"    x = (a & b);\n"
		"    // should NOT pad\n"
		"    x = *p;\n"
		"    x = &p;\n"
		"    x = (*p);\n"
		"    x = (&p);\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Sans2)
{
	// these operators should NOT be padded
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"public:\n"
		"    ~Foo();\n"
		"    ~Foo() {\n"
		"    }\n"
		"    ~Foo();\n"
		"};\n"
		"\n"
		"void FooClass::Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        bar[] = \"one\",\n"
		"                \"two\";\n"
		"    }\n"
		"\n"
		"    if (!(x == y))\n"
		"        bar();\n"
		"\n"
		"    double x(-2.0);\n"
		"\n"
		"    x->y = 2;\n"
		"    x = (-2 * -1);\n"
		"    x = -2 + -1;\n"
		"\n"
		"    x.*y = z;\n"
		"    x->*y = z;\n"
		"\n"
		"    x = ~y;\n"
		"\n"
		"    return +1;\n"
		"    return (+1);\n"
		"    return -1;\n"
		"    return (-1);\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Sans3)
{
	// overloaded operators should NOT be padded
	char text[] =
		"\nclass Foo {\n"
		"    Foo::operator= () {}\n"
		"    Foo::operator> () {}\n"
		"    Foo::operator>= () {}\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Sans4)
{
	// these * operators should NOT be padded
	char text[] =
		"\nvoid* foo(char* bar1, char& bar2,)\n"
		"{\n"
		"    return strcmp(*(char **)(a1), *(char **)(a2));\n"
		"\n"
		"    return Call(**(Callee**)ud, *(Func*)(sizeof(Callee*)));\n"
		"\n"
		"    if (!*(p + 1))\n"
		"        *mp++ = EOL;\n"
		"\n"
		"    if (*p == 'x' && *(p + 1))\n"
		"        i++;\n"
		"\n"
		"    if (*p == 'x' || *(p + 1))\n"
		"        i++;\n"
		"\n"
		"    bar(*ptr1, *ptr2);\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Sans5)
{
	// these operators should NOT be padded
	char text[] =
		"\nvoid* foo(char* bar1, char& bar2,)\n"
		"{\n"
		"    UInt32*  arr1;\n"
		"    if (input1 < 0x80)\n"
		"        *length1 = 1;\n"
		"    if (input2 < 0x80)\n"
		"        length2 = &length1;\n"
		"    Connect(&bar3);\n"
		"    while (*++Name)\n"
		"        Name = &Bar;\n"
		"    return (void*) &s[0];\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Sans6)
{
	// embedded assembler should not be padded (the colon)
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    _asm mov eax, fs:[0x8]\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Sans7)
{
	// this template should NOT be padded
	char text[] =
		"\ntypedef foo<void(whatever *const)> callback;\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Sans8)
{
	// this template within a template should NOT be padded
	char text[] =
		"\ntemplate<typename T, template<typename E> >\n"
		"class Foo\n"
		"{\n"
		"};\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Sans9)
{
	// template with a default parameter should not be padded
	char text[] =
		"\ntemplate<typename T, typename Allocator = allocator<E> >\n"
		"class Foo\n"
		"{\n"
		"};\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Sans10)
{
	// the Java generic <?> should NOT be padded
	char text[] =
		"\npublic Class<?> Foo(Class<?> _class)\n"
		"{\n"
		"    return bar;\n"
		"}\n";
	char options[] = "pad-oper, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Sans11)
{
	// should not pad a dereference following a cast
	char text[] =
		"\nvoid foo() {\n"
		"    int bar = (int*) *ptr;\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Sans12)
{
	// these operators and pointers should not change
	char text[] =
		"\nvoid SetXPM (const char* const* linesForm );\n"
		"void Foo()\n"
		"{\n"
		"    if (a & b) c = d;\n"
		"    if (a & b) { c = d; }\n"
		"    if (a * b != c)\n"
		"        x += 1;\n"
		"    for (const int* node = first(); node; node = next)\n"
		"        y += 1;\n"
		"}\n";
	char options[] = "pad-oper, align-pointer=type, keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}
TEST(PadOperator, CommaSemiColon)
{
	// semi-colons should ALWAYS be padded
	// commas should be padded with pad-oper, but not in arrays
	char textIn[] =
		"\nvoid foo(int bar1,int bar2,int bar3)\n"
		"{\n"
		"    for (i=0,j=0;i<10;i++)\n"
		"        xxx+=i;\n"
		"}\n"
		"\n"
		"static bool[,] set = {\n"
		"    {T,T,x,T, x,T,x,T, T,T,x,T, T,T,T,x},\n"
		"    {x,x,x,x, x,x,x,x, x,x,x,T, T,T,T,x},\n"
		"    {T,T,x,T, x,T,x,T, T,T,x,T, T,T,T,x},\n"
		"    {x,T,T,T, T,T,T,T, T,T,T,T, T,T,T,T}\n"
		"};\n";
	char text[] =
		"\nvoid foo(int bar1, int bar2, int bar3)\n"
		"{\n"
		"    for (i = 0, j = 0; i < 10; i++)\n"
		"        xxx += i;\n"
		"}\n"
		"\n"
		"static bool[,] set = {\n"
		"    {T, T, x, T, x, T, x, T, T, T, x, T, T, T, T, x},\n"
		"    {x, x, x, x, x, x, x, x, x, x, x, T, T, T, T, x},\n"
		"    {T, T, x, T, x, T, x, T, T, T, x, T, T, T, T, x},\n"
		"    {x, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}\n"
		"};\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Comments)
{
	// EOL comments remain in the same column if possible
	// moved comments retain the original spacing
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    c=a+b;      // comment ok\n"
		"    g=d+e+f;    // comment must move\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    c = a + b;  // comment ok\n"
		"    g = d + e + f; // comment must move\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, BlockParens)
{
	// operators in block paren should be padded
	// this was added in release 2.01
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    str[i+2] = 2;\n"
		"    str[i-2] = 2;\n"
		"    str[i*2] = 2;\n"
		"    str[i/2] = 2;\n"
		"    str[i%2] = 2;\n"
		"    str[boo*foo] = 2;\n"
		"    str[2*i] = 2;\n"
		"    crc = crc_table[(crc^(*text++))&0xFF];\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    str[i + 2] = 2;\n"
		"    str[i - 2] = 2;\n"
		"    str[i * 2] = 2;\n"
		"    str[i / 2] = 2;\n"
		"    str[i % 2] = 2;\n"
		"    str[boo * foo] = 2;\n"
		"    str[2 * i] = 2;\n"
		"    crc = crc_table[(crc ^ (*text++)) & 0xFF];\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, BlockParensSans)
{
	// dereference or address-of in block parens should NOT be padded
	// this was added in release 2.01
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    int step = utf8ByteTable[*((char*) p)];\n"
		"    *output = (char) (input[*length]);\n"
		"    char style = ptr[-1];\n"
		"    tabs += charLengths[size_t (*c)] - 1;\n"
		"    targets[(CompileTargetBase*) cbp] = globalUsedLibs;\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, ReferenceToPointer)
{
	// Test with a reference to pointer (*&).
	// It should not be an operator.
	char text[] =
		"\nvoid foo(QObject*& o)\n"
		"{}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}
TEST(PadOperator, AlternateConditionals)
{
	// test padding of alternate conditionals 'and' and 'or'
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if((test == 1)and(counter < 3))\n"
		"        ptr++;\n"
		"\n"
		"    if((test == 1)or(counter < 3))\n"
		"        ptr++;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if((test == 1) and (counter < 3))\n"
		"        ptr++;\n"
		"\n"
		"    if((test == 1) or (counter < 3))\n"
		"        ptr++;\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, SharpAlternateConditionals2)
{
	// test padding of alternate conditionals 'and' and 'or'
	// should not pad a semi-colon.
	char textIn[] =
		"\npublic class ReportingLanguage : Grammar\n"
		"{\n"
		"    BinOp.Rule1 = Symbol \"&&\"|\"||\"|and|or;\n"
		"    BinOp.Rule1 = Symbol \"||\"|\"&&\"|or|and;\n"
		"}\n";
	char text[] =
		"\npublic class ReportingLanguage : Grammar\n"
		"{\n"
		"    BinOp.Rule1 = Symbol \"&&\" | \"||\" | and | or;\n"
		"    BinOp.Rule1 = Symbol \"||\" | \"&&\" | or | and;\n"
		"}\n";
	char options[] = "pad-oper, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, SharpSans1)
{
	// pad-oper should not pad C# pointers, dereferences and address-of.
	char text[] =
		"\npublic unsafe void GetValue()\n"
		"{\n"
		"    int i = 5;\n"
		"    int* j = &i;\n"
		"    ret = *((int*) j);\n"
		"    if (int* eventItem =\n"
		"                GetItemData)\n"
		"        fooBar();\n"
		"}\n";
	char options[] = "pad-oper, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, SharpSansAlignPointer)
{
	// test pad-oper with align-pointer on C#
	char textIn[] =
		"\nbool foo()\n"
		"{\n"
		"    StringBuilder s = new StringBuilder(length*count);\n"
		"    return (modifier&query) == query;\n"
		"    foo((int)a*(int)b);\n"
		"}\n";
	char text[] =
		"\nbool foo()\n"
		"{\n"
		"    StringBuilder s = new StringBuilder(length * count);\n"
		"    return (modifier & query) == query;\n"
		"    foo((int)a * (int)b);\n"
		"}\n";
	char options[] = "pad-oper, align-pointer=type, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Array1)
{
	// test pad-oper in an array
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    int a,b,c,d,e,f,g,h;\n"
		"    int[4] = { a*b, c*d, e*f, g*h };\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    int a, b, c, d, e, f, g, h;\n"
		"    int[4] = { a * b, c * d, e * f, g * h };\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, Array2)
{
	// test pad-oper in an array
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxPoint next[] = {\n"
		"        wxPoint (ceil (x+w*z))\n"
		"    };\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxPoint next[] = {\n"
		"        wxPoint (ceil (x + w * z))\n"
		"    };\n"
		"}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, ArraySans1)
{
	// do not pad an array of dereferences
	char text[] =
		"\nwxColour foregrounds[stCount] =\n"
		"{\n"
		"    *wxBLACK,\n"
		"    *wxWHITE,\n"
		"    *wxWHITE,\n"
		"    *wxBLACK\n"
		"};";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, ArraySans2)
{
	// do not pad array holding pointers to chars
	char text[] =
		"\nchar* font[2] =\n"
		"{\n"
		"    (char*) \"B\",\n"
		"    (char*) \"R\"\n"
		"};";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, ArraySans3)
{
	// do not pad array array of addresses
	char text[] =
		"\nInfoSetter entryFunc[] = { &wxPdfInfo::SetTitle, &wxPdfInfo::SetAuthor };";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, ArraySans4)
{
	// do not pad the following pointer
	char text[] =
		"\nstatic const wxChar* foo[] = {\n"
		"    wxT (\"Normal\"),\n"
		"    (const wxChar*) NULL\n"
		"};";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, EnumSans)
{
	// do not pad the following enumerator with a pointer
	char text[] =
		"enum { TypeID = VAR_TYPE_CONST_STRING, Size = sizeof(const SQChar*) };";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadOperator, StructSans)
{
	// do not pad the following struct with pointers
	char text[] =
		"struct TemporaryPropertiesList\n"
		"{\n"
		"    wxsProperty* Property;\n"
		"    wxsPropertyContainer* Container;\n"
		"};";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Pad Paren
//-------------------------------------------------------------------------

TEST(PadParen, LongOption)
{
	// test pad parens
	char textIn[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo(a, b))\n"
		"        bar(a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo ( bool isFoo )\n"
		"{\n"
		"    if ( isFoo ( a, b ) )\n"
		"        bar ( a, b );\n"
		"}\n";
	char options[] = "pad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadParen, ShortOption)
{
	// test pad parens short option
	char textIn[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo(a, b))\n"
		"        bar(a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo ( bool isFoo )\n"
		"{\n"
		"    if ( isFoo ( a, b ) )\n"
		"        bar ( a, b );\n"
		"}\n";
	char options[] = "-P";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadParen, Comments)
{
	// EOL comments remain in the same column if possible
	// moved comments retain the original spacing
	char textIn[] =
		"\nvoid foo(bool isFoo)    // comment ok\n"
		"{\n"
		"    if (isFoo(a, b))    // comment must move\n"
		"        bar(a, b);        // comment ok\n"
		"}\n";
	char text[] =
		"\nvoid foo ( bool isFoo ) // comment ok\n"
		"{\n"
		"    if ( isFoo ( a, b ) ) // comment must move\n"
		"        bar ( a, b );     // comment ok\n"
		"}\n";
	char options[] = "pad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadParen, Template)
{
	// templates should NOT be padded
	char text[] =
		"\ntemplate<typename T, typename Allocator = allocator<E> >\n"
		"class Foo\n"
		"{\n"
		"};\n";
	char options[] = "pad-paren";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadParen, BlockParenSans)
{
	// do NOT pad a closing paren followed by a block paren ")]"
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (buffer[6+font->GetSize1()] == 128)\n"
		"        bar();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if ( buffer[6+font->GetSize1()] == 128 )\n"
		"        bar();\n"
		"}\n";
	char options[] = "pad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Pad Paren Out
//-------------------------------------------------------------------------

TEST(PadParenOut, LongOption)
{
	// test pad parens out
	char textIn[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo(a, b))\n"
		"        bar(a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo (bool isFoo)\n"
		"{\n"
		"    if (isFoo (a, b) )\n"
		"        bar (a, b);\n"
		"}\n";
	char options[] = "pad-paren-out";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadParenOut, ShortOption)
{
	// test pad parens out short option
	char textIn[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo(a, b))\n"
		"        bar(a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo (bool isFoo)\n"
		"{\n"
		"    if (isFoo (a, b) )\n"
		"        bar (a, b);\n"
		"}\n";
	char options[] = "-d";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadParenOut, Comments)
{
	// EOL comments remain in the same column if possible
	// moved comments retain the original spacing
	char textIn[] =
		"\nvoid foo(bool isFoo)  // comment ok\n"
		"{\n"
		"    if (isFoo(a, b))  // comment must move\n"
		"        bar(a, b);      // comment ok\n"
		"}\n";
	char text[] =
		"\nvoid foo (bool isFoo) // comment ok\n"
		"{\n"
		"    if (isFoo (a, b) ) // comment must move\n"
		"        bar (a, b);     // comment ok\n"
		"}\n";
	char options[] = "pad-paren-out";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Pad First Paren Out
//-------------------------------------------------------------------------

TEST(PadFirstParenOut, LongOption)
{
	// Test pad first paren out.
	char textIn[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo(a, b))\n"
		"        bar(a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo (bool isFoo)\n"
		"{\n"
		"    if (isFoo (a, b))\n"
		"        bar (a, b);\n"
		"}\n";
	char options[] = "pad-first-paren-out";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadFirstParenOut, ShortOption)
{
	// test pad first paren out short option
	char textIn[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo(a, b))\n"
		"        bar(a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo (bool isFoo)\n"
		"{\n"
		"    if (isFoo (a, b))\n"
		"        bar (a, b);\n"
		"}\n";
	char options[] = "-xd";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadFirstParenOut, MultipleParens)
{
	// Test with multiple opening parens.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    mode = ((inmode[j] == VOIDmode\n"
		"             || (GET_MODE_SIZE(outmode[j]) > GET_MODE_SIZE(inmode[j])))\n"
		"            ? outmode[j] : inmode[j]);\n"
		"}";
	char text[] =
		"\nvoid Foo ()\n"
		"{\n"
		"    mode = ((inmode[j] == VOIDmode\n"
		"             || (GET_MODE_SIZE (outmode[j]) > GET_MODE_SIZE (inmode[j])))\n"
		"            ? outmode[j] : inmode[j]);\n"
		"}";
	char options[] = "pad-first-paren-out";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadFirstParenOut, UnpadParen)
{
	// Test with unpad paren.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    mode = ( ( inmode[j] == VOIDmode\n"
		"               || ( GET_MODE_SIZE ( outmode[j] ) > GET_MODE_SIZE ( inmode[j] ) ) )\n"
		"             ? outmode[j] : inmode[j] );\n"
		"}";
	char text[] =
		"\nvoid Foo ()\n"
		"{\n"
		"    mode = ((inmode[j] == VOIDmode\n"
		"             || (GET_MODE_SIZE (outmode[j]) > GET_MODE_SIZE (inmode[j])))\n"
		"            ? outmode[j] : inmode[j]);\n"
		"}";
	char options[] = "pad-first-paren-out, unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadFirstParenOut, PadParen)
{
	// Test with pad paren. Pad paren should be used.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    mode = ((inmode[j] == VOIDmode\n"
		"             || (GET_MODE_SIZE (outmode[j]) > GET_MODE_SIZE (inmode[j])))\n"
		"            ? outmode[j] : inmode[j]);\n"
		"}";
	char text[] =
		"\nvoid Foo ()\n"
		"{\n"
		"    mode = ( ( inmode[j] == VOIDmode\n"
		"               || ( GET_MODE_SIZE ( outmode[j] ) > GET_MODE_SIZE ( inmode[j] ) ) )\n"
		"             ? outmode[j] : inmode[j] );\n"
		"}";
	char options[] = "pad-first-paren-out, pad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadFirstParenOut, PadParenOut)
{
	// Test with pad paren out. Pad paren out should be used.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    mode = ((inmode[j] == VOIDmode\n"
		"             || (GET_MODE_SIZE (outmode[j]) > GET_MODE_SIZE (inmode[j])))\n"
		"            ? outmode[j] : inmode[j]);\n"
		"}";
	char text[] =
		"\nvoid Foo ()\n"
		"{\n"
		"    mode = ( (inmode[j] == VOIDmode\n"
		"              || (GET_MODE_SIZE (outmode[j]) > GET_MODE_SIZE (inmode[j]) ) )\n"
		"             ? outmode[j] : inmode[j]);\n"
		"}";
	char options[] = "pad-first-paren-out, pad-paren-out";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadFirstParenOut, PadParenIn)
{
	// Test with pad paren in. Pad paren in should also be used.
	char textIn[] =
		"\nvoid Foo ()\n"
		"{\n"
		"    mode = ((inmode[j] == VOIDmode\n"
		"             || (GET_MODE_SIZE (outmode[j]) > GET_MODE_SIZE (inmode[j])))\n"
		"            ? outmode[j] : inmode[j]);\n"
		"}";
	char text[] =
		"\nvoid Foo ()\n"
		"{\n"
		"    mode = ( ( inmode[j] == VOIDmode\n"
		"               || ( GET_MODE_SIZE ( outmode[j] ) > GET_MODE_SIZE ( inmode[j] ) ) )\n"
		"             ? outmode[j] : inmode[j] );\n"
		"}";
	char options[] = "pad-first-paren-out, pad-paren-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadFirstParenOut, Comments)
{
	// EOL comments remain in the same column if possible
	// moved comments retain the original spacing
	char textIn[] =
		"\nvoid foo(bool isFoo)  // comment ok\n"
		"{\n"
		"    if(isFoo(a, b))     // comment must move\n"
		"        bar(a, b);      // comment ok\n"
		"}\n";
	char text[] =
		"\nvoid foo (bool isFoo) // comment ok\n"
		"{\n"
		"    if (isFoo (a, b))   // comment must move\n"
		"        bar (a, b);     // comment ok\n"
		"}\n";
	char options[] = "pad-first-paren-out";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Pad Paren In
//-------------------------------------------------------------------------

TEST(PadParenIn, LongOption)
{
	// test pad parens in
	char textIn[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo(a, b))\n"
		"        bar(a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo( bool isFoo )\n"
		"{\n"
		"    if ( isFoo( a, b ) )\n"
		"        bar( a, b );\n"
		"}\n";
	char options[] = "pad-paren-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadParenIn, ShortOption)
{
	// test pad parens in short option
	char textIn[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo(a, b))\n"
		"        bar(a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo( bool isFoo )\n"
		"{\n"
		"    if ( isFoo( a, b ) )\n"
		"        bar( a, b );\n"
		"}\n";
	char options[] = "-D";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadParenIn, Comments)
{
	// EOL comments remain in the same column if possible
	// moved comments retain the original spacing
	char textIn[] =
		"\nvoid foo(bool isFoo)   // comment ok\n"
		"{\n"
		"    if (isFoo(a, b))  // comment must move\n"
		"        bar(a, b);      // comment ok\n"
		"}\n";
	char text[] =
		"\nvoid foo( bool isFoo ) // comment ok\n"
		"{\n"
		"    if ( isFoo( a, b ) ) // comment must move\n"
		"        bar( a, b );    // comment ok\n"
		"}\n";
	char options[] = "pad-paren-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Pad Header
//-------------------------------------------------------------------------

TEST(PadHeader, LongOption)
{
	// test pad header
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(isFoo(a, b))\n"
		"        bar(a, b);\n"
		"\n"
		"    while(a>b)\n"
		"        fooBar(a, b);\n"
		"\n"
		"    nonHeader(a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo(a, b))\n"
		"        bar(a, b);\n"
		"\n"
		"    while (a>b)\n"
		"        fooBar(a, b);\n"
		"\n"
		"    nonHeader(a, b);\n"
		"}\n";
	char options[] = "pad-header";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadHeader, ShortOption)
{
	// test header short option
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(isFoo(a, b))\n"
		"        bar(a, b);\n"
		"\n"
		"    while(a>b)\n"
		"        fooBar(a, b);\n"
		"\n"
		"    nonHeader(a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo(a, b))\n"
		"        bar(a, b);\n"
		"\n"
		"    while (a>b)\n"
		"        fooBar(a, b);\n"
		"\n"
		"    nonHeader(a, b);\n"
		"}\n";
	char options[] = "-H";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadHeader, Sans)
{
	// test without pad header
	// headers should remain unchanged
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(isFoo(a, b))\n"
		"        bar(a, b);\n"
		"\n"
		"    while (a>b)\n"
		"        fooBar(a, b);\n"
		"\n"
		"    nonHeader1(a, b);\n"
		"\n"
		"    nonHeader2 (a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(isFoo(a, b))\n"
		"        bar(a, b);\n"
		"\n"
		"    while (a>b)\n"
		"        fooBar(a, b);\n"
		"\n"
		"    nonHeader1(a, b);\n"
		"\n"
		"    nonHeader2 (a, b);\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}
TEST(PadHeader, UnpadParen)
{
	// test pad header with unpad paren
	// headers should be padded, others should not
	// will remove extra padding from headers
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(isFoo(a, b))\n"
		"        bar(a, b);\n"
		"\n"
		"    while  (a>b)\n"
		"        fooBar(a, b);\n"
		"\n"
		"    nonHeader1(a, b);\n"
		"\n"
		"    nonHeader2 (a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo(a, b))\n"
		"        bar(a, b);\n"
		"\n"
		"    while (a>b)\n"
		"        fooBar(a, b);\n"
		"\n"
		"    nonHeader1(a, b);\n"
		"\n"
		"    nonHeader2(a, b);\n"
		"}\n";
	char options[] = "pad-header, unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadHeader, Comments)
{
	// EOL comments remain in the same column if possible
	// moved comments retain the original spacing
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(isFoo(a, b)) // comment must move\n"
		"        bar(a, b);\n"
		"\n"
		"    while(a>b)      // comment ok\n"
		"        fooBar(a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo(a, b)) // comment must move\n"
		"        bar(a, b);\n"
		"\n"
		"    while (a>b)     // comment ok\n"
		"        fooBar(a, b);\n"
		"}\n";
	char options[] = "pad-header";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadHeader, ShortLine)
{
	// Line with a header and no paren.
	// With VS2010 in debug this could get an exception.
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if\n"
		"    (c == 0)\n"
		"    {\n"
		"        char c2 = readCh();\n"
		"    }\n"
		"}\n";
	char options[] = "pad-header";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadHeader, Switch)
{
	// Switch and case with statements should be padded.
	char textIn[] =
		"\nvoid fooFunction()\n"
		"{\n"
		"    switch(x) {\n"
		"    case(a + b) * c:\n"
		"        //...\n"
		"    }\n"
		"}";
	char text[] =
		"\nvoid fooFunction()\n"
		"{\n"
		"    switch (x) {\n"
		"    case (a + b) * c:\n"
		"        //...\n"
		"    }\n"
		"}";
	char options[] = "pad-header";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadHeader, SwitchUnpad)
{
	// Switch and case with statements should be padded,
	// even with unpad parens.
	char textIn[] =
		"\nvoid fooFunction()\n"
		"{\n"
		"    switch(x) {\n"
		"    case(a + b) * c:\n"
		"        //...\n"
		"    }\n"
		"}";
	char text[] =
		"\nvoid fooFunction()\n"
		"{\n"
		"    switch (x) {\n"
		"    case (a + b) * c:\n"
		"        //...\n"
		"    }\n"
		"}";
	char options[] = "pad-header, unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadHeader, Return)
{
	// A 'return' statement may or may not be a paren header.
	char textIn[] =
		"\nint max(int a, int b)\n"
		"{\n"
		"    if (a > 0)\n"
		"        return 0;\n"
		"    return(a > b ? a : b);\n"
		"}";
	char text[] =
		"\nint max(int a, int b)\n"
		"{\n"
		"    if (a > 0)\n"
		"        return 0;\n"
		"    return (a > b ? a : b);\n"
		"}";
	char options[] = "pad-header";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadHeader, ReturnUnpad1)
{
	// A 'return' statement should be padded even with unpad parens.
	char textIn[] =
		"\nint max (int a, int b)\n"
		"{\n"
		"    if (a > 0)\n"
		"        return 0;\n"
		"    return (a > b ? a : b);\n"
		"}";
	char text[] =
		"\nint max(int a, int b)\n"
		"{\n"
		"    if (a > 0)\n"
		"        return 0;\n"
		"    return (a > b ? a : b);\n"
		"}";
	char options[] = "pad-header, unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadHeader, ReturnUnpad2)
{
	// A 'return' statement should be padded even with unpad parens.
	// The paren inside should be unpadded.
	char textIn[] =
		"\nint max (int a, int b)\n"
		"{\n"
		"    return( crc_table);\n"
		"}";
	char text[] =
		"\nint max(int a, int b)\n"
		"{\n"
		"    return (crc_table);\n"
		"}";
	char options[] = "pad-header, unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadHeader, Throw1)
{
	// A 'throw' statement may or may not be a paren header.
	// Should not pad a 'throw' in the definition.
	char textIn[] =
		"\nvoid with_type() throw(int) {\n"
		"    throw(1);\n"
		"}";
	char text[] =
		"\nvoid with_type() throw(int) {\n"
		"    throw (1);\n"
		"}";
	char options[] = "pad-header";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadHeader, Throw2)
{
	// A 'throw' statement may or may not be a paren header.
	// Should not pad a 'throw' in the definition (following a 'const').
	char textIn[] =
		"\nvoid with_type() throw(int) {\n"
		"    throw(1);\n"
		"}";
	char text[] =
		"\nvoid with_type() throw(int) {\n"
		"    throw (1);\n"
		"}";
	char options[] = "pad-header";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(PadHeader, ThrowUnpad)
{
	// A 'throw' statement should be padded even with unpad parens.
	char textIn[] =
		"\nvoid with_type() throw(int) {\n"
		"    throw(1);\n"
		"}";
	char text[] =
		"\nvoid with_type() throw(int) {\n"
		"    throw (1);\n"
		"}";
	char options[] = "pad-header, unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Unpad Paren
//-------------------------------------------------------------------------

TEST(UnpadParen, LongOption)
{
	// test unpad parens
	char textIn[] =
		"\nvoid foo ( bool isFoo )\n"
		"{\n"
		"    if ( isFoo ( a, b ) )\n"
		"        bar ( a, b );\n"
		"}\n";
	char text[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if(isFoo(a, b))\n"
		"        bar(a, b);\n"
		"}\n";
	char options[] = "unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(UnpadParen, ShortOption)
{
	// test unpad parens short option
	char textIn[] =
		"\nvoid foo ( bool isFoo )\n"
		"{\n"
		"    if ( isFoo ( a, b ) )\n"
		"        bar ( a, b );\n"
		"}\n";
	char text[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if(isFoo(a, b))\n"
		"        bar(a, b);\n"
		"}\n";
	char options[] = "-U";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(UnpadParen, Comments)
{
	// EOL comments ALWAYS remain in the same column
	char textIn[] =
		"\nvoid foo ( bool isFoo ) // comment ok\n"
		"{\n"
		"    if ( isFoo ( a, b ) ) // comment ok\n"
		"        bar ( a, b );     // comment ok\n"
		"}\n";
	char text[] =
		"\nvoid foo(bool isFoo)    // comment ok\n"
		"{\n"
		"    if(isFoo(a, b))       // comment ok\n"
		"        bar(a, b);        // comment ok\n"
		"}\n";
	char options[] = "unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(UnpadParen, ReturnSans)
{
	// don't unpad a 'return'
	char text[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    return (2 * x);\n"
		"}\n";
	char options[] = "unpad-paren";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(UnpadParen, ThrowSans)
{
	// don't unpad a 'throw'
	char text[] =
		"\nvoid with_type() throw(int) {\n"
		"    throw 1;\n"
		"}";
	char options[] = "unpad-paren";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(UnpadParen, CastSans)
{
	// don't unpad a cast
	char text[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    bool bar2 = bool (bar1);\n"
		"    int bar2 = int (bar1);\n"
		"    void bar2 = void (bar1);\n"
		"    void* bar2 = void* (bar1);\n"
		"    size_t bar2 = size_t (bar1);\n"
		"    BOOL bar2 = BOOL (bar1);\n"
		"    DWORD bar2 = DWORD (bar1);\n"
		"    HWND bar2 = HWND (bar1);\n"
		"    INT bar2 = INT (bar1);\n"
		"    LPSTR bar2 = LPSTR (bar1);\n"
		"    VOID bar2 = VOID (bar1);\n"
		"    LPVOID bar2 = LPVOID (bar1);\n"
		"}\n";
	char options[] = "unpad-paren";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(UnpadParen, OperatorSans1)
{
	// don't unpad a leading operator
	char text[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    x = y + (z + 2);\n"
		"    x = y - (z + 2);\n"
		"    x = y * (z + 2);\n"
		"    x = y / (z + 2);\n"
		"    x = y % (z + 2);\n"
		"    x = y ^ (z + 2);\n"
		"}\n";
	char options[] = "unpad-paren";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(UnpadParen, OperatorSans2)
{
	// don't unpad a trailing operator
	char text[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    x = (z + 2) + y;\n"
		"    x = (z + 2) - y;\n"
		"    x = (z + 2) * y;\n"
		"    x = (z + 2) / y;\n"
		"    x = (z + 2) % y;\n"
		"    x = (z + 2) ^ y;\n"
		"}\n";
	char options[] = "unpad-paren";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(UnpadParen, PadParen)
{
	// test unpad parens with pad parens
	// should be padded but will remove extra padding
	char textIn[] =
		"\nvoid foo ( bool isFoo )\n"
		"{\n"
		"    if  (  isFoo  ( a, b )  )\n"
		"        bar ( a, b );\n"
		"    if (isFoo(a, b))\n"
		"        bar(a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo ( bool isFoo )\n"
		"{\n"
		"    if ( isFoo ( a, b ) )\n"
		"        bar ( a, b );\n"
		"    if ( isFoo ( a, b ) )\n"
		"        bar ( a, b );\n"
		"}\n";
	char options[] = "unpad-paren, pad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(UnpadParen, PadParenOut)
{
	// test unpad parens with pad parens out
	// should be padded outside but will remove extra padding
	char textIn[] =
		"\nvoid foo( bool isFoo )\n"
		"{\n"
		"    if  (  isFoo  ( a, b )  )\n"
		"        bar ( a, b );\n"
		"    if (isFoo(a, b))\n"
		"        bar(a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo (bool isFoo)\n"
		"{\n"
		"    if (isFoo (a, b))\n"
		"        bar (a, b);\n"
		"    if (isFoo (a, b))\n"
		"        bar (a, b);\n"
		"}\n";
	char options[] = "unpad-paren, pad-paren-out";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(UnpadParen, PadIn)
{
	// test unpad parens with pad parens in
	// should be padded inside but will remove extra padding
	char textIn[] =
		"\nvoid foo (bool isFoo)\n"
		"{\n"
		"    if (  isFoo (  a, b  )  )\n"
		"        bar ( a, b );\n"
		"    if (isFoo(a, b))\n"
		"        bar(a, b);\n"
		"}\n";
	char text[] =
		"\nvoid foo( bool isFoo )\n"
		"{\n"
		"    if( isFoo( a, b ) )\n"
		"        bar( a, b );\n"
		"    if( isFoo( a, b ) )\n"
		"        bar( a, b );\n"
		"}\n";
	char options[] = "unpad-paren, pad-paren-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(UnpadParen, PadOper1)
{
	// test unpad parens with pad operator
	char textIn[] =
		"\nvoid foo ()\n"
		"{\n"
		"    memmove(sizeof(T)*(pos));\n"
		"    memmove(sizeof(T) * (pos));\n"
		"    memmove(sizeof(T)&(pos));\n"
		"    memmove(sizeof(T) & (pos));\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    memmove(sizeof(T) * (pos));\n"
		"    memmove(sizeof(T) * (pos));\n"
		"    memmove(sizeof(T) & (pos));\n"
		"    memmove(sizeof(T) & (pos));\n"
		"}\n";
	char options[] = "unpad-paren, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(UnpadParen, PadOper2)
{
	// test unpad parens with pad operator on alternate conditionals
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if((test == 1)and(counter < 3))\n"
		"        ptr++;\n"
		"\n"
		"    if((test == 1)or(counter < 3))\n"
		"        ptr++;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if((test == 1) and (counter < 3))\n"
		"        ptr++;\n"
		"\n"
		"    if((test == 1) or (counter < 3))\n"
		"        ptr++;\n"
		"}\n";
	char options[] = "unpad-paren, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(UnpadParen, Throw)
{
	// Unpad a 'throw' enclosed in parens.
	char textIn[] =
		"\nvoid with_type() throw(int) {\n"
		"    throw (1);\n"
		"}";
	char text[] =
		"\nvoid with_type() throw(int) {\n"
		"    throw(1);\n"
		"}";
	char options[] = "unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Delete Empty Lines
//-------------------------------------------------------------------------

TEST(DeleteEmptyLines, LongOption)
{
	// test delete empty lines
	char textIn[] =
		"\nclass fooClass\n"
		"{\n"
		"\n"
		"public:\n"
		"\n"
		"    int foo1;\n"
		"\n"
		"    int foo2;\n"
		"\n"
		"    fooClass() {\n"
		"\n"
		"        int foo1 = 0;\n"
		"\n"
		"\n"
		"        int foo2 = 0;\n"
		"\n"
		"    }\n"
		"\n"
		"};\n"
		"\n"
		"void fooClass::fooBar()\n"
		"{\n"
		"\n"
		"    foo1 = 1;\n"
		"\n"
		"    foo2 = 2;\n"
		"\n"
		"}\n";
	char text[] =
		"\nclass fooClass\n"
		"{\n"
		"\n"
		"public:\n"
		"\n"
		"    int foo1;\n"
		"\n"
		"    int foo2;\n"
		"\n"
		"    fooClass() {\n"
		"        int foo1 = 0;\n"
		"        int foo2 = 0;\n"
		"    }\n"
		"\n"
		"};\n"
		"\n"
		"void fooClass::fooBar()\n"
		"{\n"
		"    foo1 = 1;\n"
		"    foo2 = 2;\n"
		"}\n";
	char options[] = "delete-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, ShortOption)
{
	// test delete empty lines
	char textIn[] =
		"\nclass fooClass\n"
		"{\n"
		"\n"
		"public:\n"
		"\n"
		"    int foo1;\n"
		"\n"
		"    int foo2;\n"
		"\n"
		"    fooClass() {\n"
		"\n"
		"        int foo1 = 0;\n"
		"\n"
		"\n"
		"        int foo2 = 0;\n"
		"\n"
		"    }\n"
		"\n"
		"};\n"
		"\n"
		"void fooClass::fooBar()\n"
		"{\n"
		"\n"
		"    foo1 = 1;\n"
		"\n"
		"    foo2 = 2;\n"
		"\n"
		"}\n";
	char text[] =
		"\nclass fooClass\n"
		"{\n"
		"\n"
		"public:\n"
		"\n"
		"    int foo1;\n"
		"\n"
		"    int foo2;\n"
		"\n"
		"    fooClass() {\n"
		"        int foo1 = 0;\n"
		"        int foo2 = 0;\n"
		"    }\n"
		"\n"
		"};\n"
		"\n"
		"void fooClass::fooBar()\n"
		"{\n"
		"    foo1 = 1;\n"
		"    foo2 = 2;\n"
		"}\n";
	char options[] = "-xe";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, Comment)
{
	// the empty lines before and after comments should be deleted
	char textIn[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"\n"
		"    // the above and following empty lines should be deleted\n"
		"\n"
		"    if (fooBar)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"\n"
		"    // the above and following empty lines should be deleted\n"
		"\n"
		"    else\n"
		"    {\n"
		"        bar3();\n"
		"    }\n"
		"\n"
		"    bar4();\n"
		"}\n";
	char text[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"    // the above and following empty lines should be deleted\n"
		"    if (fooBar)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"    // the above and following empty lines should be deleted\n"
		"    else\n"
		"    {\n"
		"        bar3();\n"
		"    }\n"
		"    bar4();\n"
		"}\n";
	char options[] = "delete-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocks1)
{
	// test delete empty lines, with break blocks
	// the empty lines created by break blocks should NOT be deleted
	char textIn[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"\n"
		"    // the above empty line should not be deleted\n"
		"    if (fooBar)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"\n"
		"    // the above empty line should be deleted\n"
		"    else\n"
		"    {\n"
		"        bar3();\n"
		"    }\n"
		"\n"
		"    bar4();\n"
		"}\n";
	char text[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"\n"
		"    // the above empty line should not be deleted\n"
		"    if (fooBar)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"    // the above empty line should be deleted\n"
		"    else\n"
		"    {\n"
		"        bar3();\n"
		"    }\n"
		"\n"
		"    bar4();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocks2)
{
	// test delete empty lines, with break blocks
	// the empty lines should not be deleted on header blocks
	// the empty lines should be deleted on closing header blocks
	char textIn[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"\n"
		"    // the above and following empty lines should not be deleted\n"
		"\n"
		"    if (fooBar)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"\n"
		"    // the above and following empty lines should be deleted\n"
		"\n"
		"    else\n"
		"    {\n"
		"        bar3();\n"
		"    }\n"
		"\n"
		"    bar4();\n"
		"}\n";
	char text[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"\n"
		"    // the above and following empty lines should not be deleted\n"
		"\n"
		"    if (fooBar)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"    // the above and following empty lines should be deleted\n"
		"    else\n"
		"    {\n"
		"        bar3();\n"
		"    }\n"
		"\n"
		"    bar4();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocks3)
{
	// test delete empty lines, with break blocks
	// the comments are not followed by a potential header
	char textIn[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"    // comment 1\n"
		"\n"
		"    // comment 2\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"\n"
		"    bar3();\n"
		"}\n";
	char text[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"    // comment 1\n"
		"    // comment 2\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"    bar3();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocks4)
{
	// test delete empty lines, with break blocks
	// the empty lines are not followed by a header
	char textIn[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"\n"
		"    // comment 1\n"
		"\n"
		"    // comment 2\n"
		"    bar2();\n"
		"\n"
		"    bar3();\n"
		"}\n";
	char text[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"    // comment 1\n"
		"    // comment 2\n"
		"    bar2();\n"
		"    bar3();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocks5)
{
	// test delete empty lines, with break blocks
	// the line before "else" should be deleted
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar1()\n"
		"\n"
		"    // comment 1\n"
		"    if (isFoo)\n"
		"        bar2();\n"
		"\n"
		"    // comment 2\n"
		"    else\n"
		"        bar3();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar1()\n"
		"\n"
		"    // comment 1\n"
		"    if (isFoo)\n"
		"        bar2();\n"
		"    // comment 2\n"
		"    else\n"
		"        bar3();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocks6)
{
	// test delete empty lines, with break blocks
	// the line after opening bracket should be deleted
	// the line before closing bracket should be deleted
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"\n"
		"    // comment\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    // comment\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocksAll1)
{
	// test delete empty lines, with break all blocks
	// the empty lines created by break all blocks should NOT be deleted
	char text[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"\n"
		"    // the above empty line should not be deleted\n"
		"    if (fooBar)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"\n"
		"    // the above empty line should not be deleted\n"
		"    else\n"
		"    {\n"
		"        bar3();\n"
		"    }\n"
		"\n"
		"    bar4();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks=all";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocksAll2)
{
	// test delete empty lines, with break all blocks
	// the empty lines created by break all blocks should NOT be deleted
	char text[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"\n"
		"    // the above and following empty lines should not be deleted\n"
		"\n"
		"    if (fooBar)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"\n"
		"    // the above and following empty lines should not be deleted\n"
		"\n"
		"    else\n"
		"    {\n"
		"        bar3();\n"
		"    }\n"
		"\n"
		"    bar4();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks=all";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocksAll3)
{
	// test delete empty lines, with break all blocks
	// the comments are not followed by a potential header
	char textIn[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"    // comment 1\n"
		"\n"
		"    // comment 2\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"\n"
		"    bar3();\n"
		"}\n";
	char text[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"    // comment 1\n"
		"    // comment 2\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"    bar3();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocksAll4)
{
	// test delete empty lines, with break all blocks
	// the comments are not followed by a header
	char textIn[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"\n"
		"    // comment 1\n"
		"\n"
		"    // comment 2\n"
		"    bar2();\n"
		"\n"
		"    bar3();\n"
		"}\n";
	char text[] =
		"\nvoid Foo(bool fooBar)\n"
		"{\n"
		"    bar1();\n"
		"    // comment 1\n"
		"    // comment 2\n"
		"    bar2();\n"
		"    bar3();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocksAll5)
{
	// test delete empty lines, with break blocks
	// the line before "else" should be deleted
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar1()\n"
		"\n"
		"    // comment 1\n"
		"    if (isFoo)\n"
		"        bar2();\n"
		"\n"
		"    // comment 2\n"
		"    else\n"
		"        bar3();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks=all";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocksAll6)
{
	// test delete empty lines, with break blocks
	// the line after opening bracket should be deleted
	// the line before closing bracket should be deleted
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"\n"
		"    // comment\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    // comment\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocksComment1)
{
	// delete empty lines with break blocks
	// should not delete lines between comments
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"    bar1();\n"
		"    // comment1\n"
		"\n"
		"    // comment2\n"
		"    if (isFoo)\n"
		"        bar2();\n"
		"\n"
		"    bar3();\n"
		"    /* comment3 */\n"
		"\n"
		"    /* comment4 */\n"
		"    if (isFoo)\n"
		"        bar4();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocksComment2)
{
	// delete empty lines with break blocks
	// test mixing comments and line comments
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar();\n"
		"    /* comment1 */\n"
		"    // comment2\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"    fooBar();\n"
		"    /* comment1 */\n"
		"    // comment2\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    fooBar();\n"
		"\n"
		"    /* comment1 */\n"
		"    // comment2\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"\n"
		"    fooBar();\n"
		"\n"
		"    /* comment1 */\n"
		"    // comment2\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocksComment3)
{
	// delete-empty-lines (-x) with break-blocks (-f).
	// Test mixing comments and line comments.
	// The combination of empty lines and comments caused an
	// "assert(peekStart == 0)" failure in "ASStreamIterator<T>::nextLine()".
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    //    bar1();\n"
		"\n"
		"    /* */ bar2();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    //    bar1();\n"
		"    /* */ bar2();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(DeleteEmptyLines, BreakBlocksComment4)
{
	// delete-empty-lines (-x) with break-blocks (-f).
	// The empty line should NOT be deleted.
	// Test mixing comments and line comments.
	// The combination of empty lines and comments caused an
	// "assert(peekStart == 0)" failure in "ASStreamIterator<T>::nextLine()".
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    //    bar1();\n"
		"\n"
		"    /* */   if (isBar)\n"
		"        bar2();\n"
		"}\n";
	char options[] = "delete-empty-lines, break-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Fill Empty Lines
//-------------------------------------------------------------------------

TEST(FillEmptyLines, LongOption)
{
	// test fill empty lines
	char textIn[] =
		"\nvoid foo1(bool isFoo)\n"
		"{\n"
		"    a = 1;\n"
		"\n"
		"    if (isFoo)\n"
		"        b = 2;\n"
		"\n"
		"    c = 3;\n"
		"}\n";
	char text[] =
		"\nvoid foo1(bool isFoo)\n"
		"{\n"
		"    a = 1;\n"
		"    \n"
		"    if (isFoo)\n"
		"        b = 2;\n"
		"        \n"
		"    c = 3;\n"
		"}\n";
	char options[] = "fill-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FillEmptyLines, ShortOption)
{
	// test fill empty lines short option
	char textIn[] =
		"\nvoid foo1(bool isFoo)\n"
		"{\n"
		"    a = 1;\n"
		"\n"
		"    if (isFoo)\n"
		"        b = 2;\n"
		"\n"
		"    c = 3;\n"
		"}\n";
	char text[] =
		"\nvoid foo1(bool isFoo)\n"
		"{\n"
		"    a = 1;\n"
		"    \n"
		"    if (isFoo)\n"
		"        b = 2;\n"
		"        \n"
		"    c = 3;\n"
		"}\n";
	char options[] = "-E";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FillEmptyLines, Tab)
{
	// test fill empty lines with tabs
	char textIn[] =
		"\nvoid foo1(bool isFoo)\n"
		"{\n"
		"    a = 1;\n"
		"\n"
		"    if (isFoo)\n"
		"        b = 2;\n"
		"    bool shouldFill = (newOperator != &AS_COLON\n"
		"                       && newOperator != &AS_PAREN);\n"
		"                       \n"
		"    c = 3;\n"
		"}\n";
	char text[] =
		"\nvoid foo1(bool isFoo)\n"
		"{\n"
		"	a = 1;\n"
		"	\n"
		"	if (isFoo)\n"
		"		b = 2;\n"
		"	bool shouldFill = (newOperator != &AS_COLON\n"
		"	                   && newOperator != &AS_PAREN);\n"
		"	                   \n"
		"	c = 3;\n"
		"}\n";
	char options[] = "fill-empty-lines, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FillEmptyLines, Enum)
{
	// test fill empty lines in an enum statement
	char textIn[] =
		"\nenum\n"
		"{\n"
		"    NUM1,\n"
		"    NUM2,\n"
		"\n"
		"    NUM3,\n"
		"};\n";
	char text[] =
		"\nenum\n"
		"{\n"
		"    NUM1,\n"
		"    NUM2,\n"
		"    \n"
		"    NUM3,\n"
		"};\n";
	char options[] = "fill-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FillEmptyLines, ForceTab)
{
	// test fill empty lines with force tabs
	char textIn[] =
		"\nvoid foo1(bool isFoo)\n"
		"{\n"
		"    a = 1;\n"
		"\n"
		"    if (isFoo)\n"
		"        b = 2;\n"
		"\n"
		"    bool shouldFill = (newOperator != &AS_COLON\n"
		"                       && newOperator != &AS_PAREN);\n"
		"                       \n"
		"    c = 3;\n"
		"}\n";
	char text[] =
		"\nvoid foo1(bool isFoo)\n"
		"{\n"
		"	a = 1;\n"
		"	\n"
		"	if (isFoo)\n"
		"		b = 2;\n"
		"		\n"
		"	bool shouldFill = (newOperator != &AS_COLON\n"
		"					   && newOperator != &AS_PAREN);\n"
		"					   \n"
		"	c = 3;\n"
		"}\n";
	char options[] = "fill-empty-lines, indent=force-tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FillEmptyLines, ForceTabX)
{
	// test fill empty lines with force-tab-tab
	char textIn[] =
		"\nvoid foo1(bool isFoo)\n"
		"{\n"
		"    a = 1;\n"
		"\n"
		"    if (isFoo)\n"
		"        b = 2;\n"
		"\n"
		"    bool shouldFill = (newOperator != &AS_COLON\n"
		"                       && newOperator != &AS_PAREN);\n"
		"                       \n"
		"    c = 3;\n"
		"}\n";
	char text[] =
		"\nvoid foo1(bool isFoo)\n"
		"{\n"
		"    a = 1;\n"
		"    \n"
		"    if (isFoo)\n"
		"	b = 2;\n"
		"	\n"
		"    bool shouldFill = (newOperator != &AS_COLON\n"
		"		       && newOperator != &AS_PAREN);\n"
		"		       \n"
		"    c = 3;\n"
		"}\n";
	char options[] = "fill-empty-lines, indent=force-tab-x";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FillEmptyLines, EventTable)
{
	// test fill empty lines in an event table
	char textIn[] =
		"\nBEGIN_EVENT_TABLE(JP5Frm,wxFrame)\n"
		"    EVT_PAINT(JP5Frm::WindowPaint)\n"
		"\n"
		"\n"
		"    EVT_MENU(ID_MENU_FILE_OPEN, JP5Frm::MenuFileOpen)\n"
		"END_EVENT_TABLE()\n";
	char text[] =
		"\nBEGIN_EVENT_TABLE(JP5Frm,wxFrame)\n"
		"    EVT_PAINT(JP5Frm::WindowPaint)\n"
		"    \n"
		"    \n"
		"    EVT_MENU(ID_MENU_FILE_OPEN, JP5Frm::MenuFileOpen)\n"
		"END_EVENT_TABLE()\n";
	char options[] = "fill-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FillEmptyLines, SQL)
{
	// test fill empty lines in an SQL statement
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    EXEC SQL INSERT\n"
		"             INTO   branch (branch_id)\n"
		"\n"
		"             VALUES (:bid, :bname, :baddr:baddr_ind);\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    EXEC SQL INSERT\n"
		"             INTO   branch (branch_id)\n"
		"    \n"
		"             VALUES (:bid, :bname, :baddr:baddr_ind);\n"
		"}\n";
	char options[] = "fill-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Align Pointer
// default Align Pointer value REF_SAME_AS_PTR is tested here
//-------------------------------------------------------------------------
TEST(AlignPointerNone, LongOption)
{
	// pointers and references should not be changed
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string* bar;     // comment\n"
		"    const string *bar;     // comment\n"
		"    const string   *bar;   // comment\n"
		"    const string  * bar;   // comment\n"
		"    const string*bar;      // comment\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, Tabs)
{
	// test with tab separators
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const char	*bar;\n"
		"    const char		*bar;\n"
		"    const char*		bar;\n"
		"    const char		*		bar;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, AddressOf)
{
	// "address of" operator should NOT be changed
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (bar1 == &AS_BAR1\n"
		"            || bar2 == &AS_BAR2)   // comment\n"
		"        return;\n"
		"    return &x;\n"
		"    return (&x);\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, Dereference)
{
	// dereference should NOT be changed
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    TRxtra (*prevWordH);   // comment\n"
		"    if (fileName.empty())\n"
		"        *traceOutF << lineNum << endl;\n"
		"    else\n"
		"        *traceOutF << fileName << endl;\n"
		"    RegisterImage((char**)xpm_data_ptrs[i]);\n"
		"    if (i > *maxcol) *maxcol = i;\n"
		"    *newVec = **iter;\n"
		"    (info.*entryFunc[j])(value);\n"
		"    bool gtr = (*a)->IsLarger(**b);\n"
		"    return *this;\n"
		"    return (*this);\n"
		"    if (*doc) delete *doc;\n"
		"\n"
		"    if(prev) next = next;\n"
		"    else *chain = next;\n"
		"\n"
		"    for (tp::iterator it = p.begin(); it != p.end(); ++it) {\n"
		"        fill( m, **it );\n"
		"    }\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, Dereference2)
{
	// dereference following a comment should NOT be changed
	char text[] =
		"\nvoid f(int** pp)\n"
		"{\n"
		"    // comment\n"
		"    **pp = 0;\n"
		"}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, GlobalVariables)
{
	// test with global variables
	char textIn[] =
		"\n// global variables\n"
		"ostream* _err = &cerr;\n"
		"ASConsole * g_console;\n"
		"stringstream *_err = NULL;\n";
	char text[] =
		"\n// global variables\n"
		"ostream* _err = &cerr;\n"
		"ASConsole * g_console;\n"
		"stringstream *_err = NULL;\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, GlobalDeclarations)
{
	// test with global declarations
	char text[] =
		"\n// function declarations\n"
		"void *foo(char* fooBar);\n"
		"char&bar(char&);\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, Cast1)
{
	// cast should not be changed
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string *bar;          // comment0\n"
		"    foo = (RefNode **) bar();   // comment1\n"
		"    foo = (RefNode *) bar();    // comment2\n"
		"    foo = ( RefNode ** ) bar(); // comment1\n"
		"    foo = ( RefNode * ) bar();  // comment2\n"
		"    foo = const_cast<RefNode **>(bar()); // comment3\n"
		"    foo = const_cast<RefNode *>(bar());  // comment4\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, Cast2)
{
	// cast should not be changed
	char text[] =
		"\nvoid foo(void *, void *);\n"
		"void foo(void *fooBar, void * fooBar);\n"
		"void foo(void **, void**);\n"
		"void foo(wxCommandEvent &);\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, ConvertTabs)
{
	// test tab conversion
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox	*channel;\n"
		"    wxTextCtrl	*filename;\n"
		"    char		*	stamp;\n"
		"    void			*userData;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox   *channel;\n"
		"    wxTextCtrl  *filename;\n"
		"    char        *   stamp;\n"
		"    void            *userData;\n"
		"}\n";
	char options[] = "convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, Paren)
{
	// test pointer recognition in a paren
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(cbProject* p  = pm->GetProject())\n"
		"        getBar();\n"
		"    if(cbProject * p = pm->GetProject())\n"
		"        getBar();\n"
		"    if(cbProject  *p = pm->GetProject())\n"
		"        getBar();\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, PointerToPointer1)
{
	// test double pointer
	char text[] =
		"\nint main(int argc, char **argv)\n"
		"{\n"
		"    char    **bar1;\n"
		"    char  **  bar1;\n"
		"    char**    bar1;\n"
		"    char	**	bar1;\n"
		"    char		**		bar1;\n"
		"    char**bar1;\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, PointerToPointer2)
{
	// test double pointer beginning a line
	char text[] =
		"\nvoid SQNativeClosure::Mark ( SQCollectable\n"
		"                             ** chain )\n"
		"{\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, EndOfLine1)
{
	// test pointer at end of line
	char text[] =
		"\nvoid*\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, EndOfLine2)
{
	// test pointer at end of line with spaces or comment after
	char textIn[] =
		"\nvoid*   \n"
		"foo() {}\n"
		"\n"
		"char &   \n"
		"bar() {}\n"
		"\n"
		"void*      // comment  \n"
		"foo() {}\n"
		"\n"
		"void **    /* comment */  \n"
		"foo() {}\n"
		"\n"
		"char**   \n"
		"bar() {}\n";
	char text[] =
		"\nvoid*\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n"
		"\n"
		"void*      // comment\n"
		"foo() {}\n"
		"\n"
		"void **    /* comment */\n"
		"foo() {}\n"
		"\n"
		"char**\n"
		"bar() {}\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, Comment)
{
	// test pointer with comment after
	char text[] =
		"\nvoid Foo(WordList*/*keyword*/,\n"
		"         WordList**/*keyword*/) {\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, OperatorOverload)
{
	// test pointer with overloaded operator
	char text[] =
		"\nclass Foo\n"
		"{\n"
		"    T& operator* () const {};\n"
		"    T * operator-> () {};\n"
		"};\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, ConversionOperator)
{
	// test pointer with conversion operator
	char text[] =
		"\n// conversion operator declarations\n"
		"operator EventRef &() { return fEvent; }\n"
		"operator HIRect * () { return this; }\n"
		"operator bool() { return len ? true : false; }\n"
		"\n"
		"// conversion operator definitions\n"
		"operator EventRef&();\n"
		"operator HIRect *();\n"
		"operator bool() const;\n"
		"\n"
		"// conversion operator casts\n"
		"EventRef& rf = (EventRef&) tf;\n"
		"HIRect *pr   = (HIRect *) tr;\n"
		"bool bb      = (bool) tb;\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, ScopeResolution)
{
	// should not change scope resolution operator
	char text[] =
		"\nstruct CV {\n"
		"    VarType TClassType::*var;\n"
		"    VarType TClassType:: *var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType:: * var;\n"
		"} cv;\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, PadParenOutside)
{
	// should not change scope resolution operator
	char text[] =
		"\nBOOL RegisterServer() {\n"
		"    static DOREGSTRUCT ClsidEntries[] = {\n"
		"        { ShowIcon, (LPTSTR)& showIcon},\n"
		"        { Dynamic,  (LPTSTR) & isDynamic},\n"
		"        { Maxtext,  (LPTSTR) &maxText},\n"
		"        { IconID,   (LPTSTR)&iconID},\n"
		"    };\n"
		"}";
	char options[] = "pad-paren-out";
	char* textOut1 = AStyleMain(text, options, errorHandler, memoryAlloc);
	// format twice to be sure an extra space is not added
	char* textOut = AStyleMain(textOut1, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut1;
	delete [] textOut;
}

TEST(AlignPointerNone, UnpadParen)
{
	// unpad-paren should NOT delete space padding
	char text[] =
		"\nLUA_API lua_State     *(lua_tothread)(lua_State *L, int idx);\n"
		"LUA_API const void     *(lua_topointer)(lua_State *L, int idx);\n";
	char options[] = "unpad-paren";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, CppCLI)
{
	// should not change a C++/CLI file.
	char text[] =
		"\nclass referencetype\n"
		"{\n"
		"protected:\n"
		"    String^ stringVar;\n"
		"    array<int> ^ intArr;\n"
		"    List<double> ^doubleList;\n"
		"    String^ s1 = \"abc\";\n"
		"    Object  ^  o1 = s1;\n"
		"    Object  ^o2 = s2;\n"
		"public:\n"
		"    referencetype(String^ str, int *pointer, int number)\n"
		"    {\n"
		"        System::Console::WriteLine(str->Trim() + number);\n"
		"    }\n"
		"};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerNone, CSharp)
{
	// should not change a C# file.
	char text[] =
		"\npublic unsafe void GetValue()\n"
		"{\n"
		"    int i = 5;\n"
		"    int * j = &i;\n"
		"    ret = *((int *) j);\n"
		"    if (int* eventItem =\n"
		"                GetItemData)\n"
		"        fooBar();\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}
TEST(AlignPointerType, LongOption)
{
	// test align pointer=type
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string* bar;     // comment\n"
		"    const string *bar;     // comment\n"
		"    const string   *bar;   // comment\n"
		"    const string  * bar;   // comment\n"
		"    const string*bar;      // comment\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string* bar;     // comment\n"
		"    const string* bar;     // comment\n"
		"    const string*   bar;   // comment\n"
		"    const string*   bar;   // comment\n"
		"    const string* bar;     // comment\n"
		"    const string& bar;     // comment\n"
		"    const string& bar;     // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string& bar;     // comment\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, ShortOption)
{
	// test align pointer=type short option
	char textIn[] =
		"\nstring foo(const string *bar)\n"
		"{\n"
		"    const string* bar;\n"
		"    const string *bar;\n"
		"}\n";
	char text[] =
		"\nstring foo(const string* bar)\n"
		"{\n"
		"    const string* bar;\n"
		"    const string* bar;\n"
		"}\n";
	char options[] = "-k1";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, FromCentered)
{
	// test align pointer=type when input is centered
	// a space is deleted in certain circumstances
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string * bar;     // remove space\n"
		"    const string  * bar;    // don't remove\n"
		"    const string *  bar;    // don't remove\n"
		"    const string* bar;      // don't remove\n"
		"    const string *bar;      // don't remove\n"
		"\n"
		"    const string ** bar;    // remove space\n"
		"    const string  ** bar;   // don't remove\n"
		"    const string **  bar;   // don't remove\n"
		"    const string** bar;     // don't remove\n"
		"    const string **bar;     // don't remove\n"
		"\n"
		"    const string & bar;     // remove space\n"
		"    const string  & bar;    // don't remove\n"
		"    const string &  bar;    // don't remove\n"
		"    const string& bar;      // don't remove\n"
		"    const string &bar;      // don't remove\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string* bar;      // remove space\n"
		"    const string*   bar;    // don't remove\n"
		"    const string*   bar;    // don't remove\n"
		"    const string* bar;      // don't remove\n"
		"    const string* bar;      // don't remove\n"
		"\n"
		"    const string** bar;     // remove space\n"
		"    const string**   bar;   // don't remove\n"
		"    const string**   bar;   // don't remove\n"
		"    const string** bar;     // don't remove\n"
		"    const string** bar;     // don't remove\n"
		"\n"
		"    const string& bar;      // remove space\n"
		"    const string&   bar;    // don't remove\n"
		"    const string&   bar;    // don't remove\n"
		"    const string& bar;      // don't remove\n"
		"    const string& bar;      // don't remove\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, Tabs)
{
	// test with tab separators
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const char	*bar;\n"
		"    const char		*bar;\n"
		"    const char*		bar;\n"
		"    const char		*		bar;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const char*	bar;\n"
		"    const char*		bar;\n"
		"    const char*		bar;\n"
		"    const char*				bar;\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, AddressOf)
{
	// "address of" operator should NOT be separated from the name
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (bar1 == &AS_BAR1\n"
		"            || bar2 == &AS_BAR2)   // comment\n"
		"        return;\n"
		"    return &x;\n"
		"    return (&x);\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, Dereference)
{
	// dereference should NOT be separated from the name
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    TRxtra (*prevWordH);   // comment\n"
		"    if (fileName.empty())\n"
		"        *traceOutF << lineNum << endl;\n"
		"    else\n"
		"        *traceOutF << fileName << endl;\n"
		"    RegisterImage((char**)xpm_data_ptrs[i]);\n"
		"    if (i > *maxcol) *maxcol = i;\n"
		"    *newVec = **iter;\n"
		"    (info.*entryFunc[j])(value);\n"
		"    bool gtr = (*a)->IsLarger(**b);\n"
		"    return *this;\n"
		"    return (*this);\n"
		"    if (*doc) delete *doc;\n"
		"\n"
		"    if(prev) next = next;\n"
		"    else *chain = next;\n"
		"\n"
		"    for (tp::iterator it = p.begin(); it != p.end(); ++it) {\n"
		"        fill( m, **it );\n"
		"    }\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, Dereference2)
{
	// dereference following a comment should NOT be changed
	char text[] =
		"\nvoid f(int** pp)\n"
		"{\n"
		"    // comment\n"
		"    **pp = 0;\n"
		"}";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, GlobalVariables)
{
	// test with global variables
	char textIn[] =
		"\n// global variables\n"
		"ostream *_err = &cerr;\n"
		"ASConsole *g_console;\n"
		"stringstream *_err = NULL;\n";
	char text[] =
		"\n// global variables\n"
		"ostream* _err = &cerr;\n"
		"ASConsole* g_console;\n"
		"stringstream* _err = NULL;\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, GlobalDeclarations)
{
	// test with global declarations
	char textIn[] =
		"\n// function declarations\n"
		"void *foo(char*fooBar);\n"
		"char&bar(char&);\n";
	char text[] =
		"\n// function declarations\n"
		"void* foo(char* fooBar);\n"
		"char& bar(char&);\n";;
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, Cast1)
{
	// cast should not be space padded
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string *bar;          // comment0\n"
		"    foo = (RefNode **) bar();   // comment1\n"
		"    foo = (RefNode *) bar();    // comment2\n"
		"    foo = ( RefNode ** ) bar(); // comment1\n"
		"    foo = ( RefNode * ) bar();  // comment2\n"
		"    foo = const_cast<RefNode **>(bar()); // comment3\n"
		"    foo = const_cast<RefNode *>(bar());  // comment4\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string* bar;          // comment0\n"
		"    foo = (RefNode**) bar();    // comment1\n"
		"    foo = (RefNode*) bar();     // comment2\n"
		"    foo = ( RefNode** ) bar();  // comment1\n"
		"    foo = ( RefNode* ) bar();   // comment2\n"
		"    foo = const_cast<RefNode**>(bar());  // comment3\n"
		"    foo = const_cast<RefNode*>(bar());   // comment4\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, Cast2)
{
	// cast should not be space padded
	char textIn[] =
		"\nvoid foo(void *, void *);\n"
		"void foo(void *fooBar, void * fooBar);\n";
	char text[] =
		"\nvoid foo(void*, void*);\n"
		"void foo(void* fooBar, void* fooBar);\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, ConvertTabs)
{
	// test tab conversion on type
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox	*channel;\n"
		"    wxTextCtrl	*filename;\n"
		"    char		*	stamp;\n"
		"    void			*userData;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox*   channel;\n"
		"    wxTextCtrl*  filename;\n"
		"    char*           stamp;\n"
		"    void*            userData;\n"
		"}\n";
	char options[] = "align-pointer=type, convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, Paren)
{
	// test pointer recognition in a paren
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(cbProject *p = pm->GetProject())\n"
		"        getBar();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(cbProject* p = pm->GetProject())\n"
		"        getBar();\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, PointerToPointer1)
{
	// test double pointer
	char textIn[] =
		"\nint main(int argc, char **argv)\n"
		"{\n"
		"    char    **bar1;\n"
		"    char  **  bar1;\n"
		"    char**    bar1;\n"
		"    char	**	bar1;\n"
		"    char		**		bar1;\n"
		"    char**bar1;\n"
		"}\n";
	char text[] =
		"\nint main(int argc, char** argv)\n"
		"{\n"
		"    char**    bar1;\n"
		"    char**    bar1;\n"
		"    char**    bar1;\n"
		"    char**		bar1;\n"
		"    char**				bar1;\n"
		"    char** bar1;\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, PointerToPointer2)
{
	// test double pointer beginning a line
	char text[] =
		"\nvoid SQNativeClosure::Mark ( SQCollectable\n"
		"                             ** chain )\n"
		"{\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, EndOfLine1)
{
	// test pointer at end of line
	char textIn[] =
		"\nvoid*\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n";
	char text[] =
		"\nvoid*\n"
		"foo() {}\n"
		"\n"
		"char&\n"
		"bar() {}\n";
	char options[] = "align-pointer=type, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, EndOfLine2)
{
	// test pointer at end of line with spaces or comment after
	char textIn[] =
		"\nvoid*   \n"
		"foo() {}\n"
		"\n"
		"char &   \n"
		"bar() {}\n"
		"\n"
		"void*      // comment  \n"
		"foo() {}\n"
		"\n"
		"void **    /* comment */  \n"
		"foo() {}\n"
		"\n"
		"char**   \n"
		"bar() {}\n";
	char text[] =
		"\nvoid*\n"
		"foo() {}\n"
		"\n"
		"char&\n"
		"bar() {}\n"
		"\n"
		"void*      // comment\n"
		"foo() {}\n"
		"\n"
		"void**     /* comment */\n"
		"foo() {}\n"
		"\n"
		"char**\n"
		"bar() {}\n";
	char options[] = "align-pointer=type, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, Comment)
{
	// test pointer with comment after
	char textIn[] =
		"\nvoid Foo(WordList*/*keyword*/,\n"
		"         WordList**/*keyword*/) {\n"
		"}\n";
	char text[] =
		"\nvoid Foo(WordList* /*keyword*/,\n"
		"         WordList** /*keyword*/) {\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, OperatorOverload)
{
	// test pointer with overloaded operator
	char textIn[] =
		"\nclass Foo\n"
		"{\n"
		"    T& operator* () const {};\n"
		"    T * operator-> () {};\n"
		"};\n";
	char text[] =
		"\nclass Foo\n"
		"{\n"
		"    T& operator* () const {};\n"
		"    T* operator-> () {};\n"
		"};\n";
	char options[] = "align-pointer=type, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, ConversionOperator)
{
	// test pointer with conversion operator
	char textIn[] =
		"\n// conversion operator declarations\n"
		"operator EventRef &() { return fEvent; }\n"
		"operator HIRect * () { return this; }\n"
		"operator bool() { return len ? true : false; }\n"
		"\n"
		"// conversion operator definitions\n"
		"operator EventRef&();\n"
		"operator HIRect *();\n"
		"operator bool() const;\n"
		"\n"
		"// conversion operator casts\n"
		"EventRef& rf = (EventRef&) tf;\n"
		"HIRect *pr   = (HIRect *) tr;\n"
		"bool bb      = (bool) tb;\n";
	char text[] =
		"\n// conversion operator declarations\n"
		"operator EventRef& () { return fEvent; }\n"
		"operator HIRect* () { return this; }\n"
		"operator bool() { return len ? true : false; }\n"
		"\n"
		"// conversion operator definitions\n"
		"operator EventRef& ();\n"
		"operator HIRect* ();\n"
		"operator bool() const;\n"
		"\n"
		"// conversion operator casts\n"
		"EventRef& rf = (EventRef&) tf;\n"
		"HIRect* pr   = (HIRect*) tr;\n"
		"bool bb      = (bool) tb;\n";
	char options[] = "align-pointer=type, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, ScopeResolution)
{
	// should pad scope resolution operator
	char textIn[] =
		"\nstruct CV {\n"
		"    VarType TClassType::*var;\n"
		"    VarType TClassType:: *var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType:: * var;\n"
		"} cv;\n";
	char text[] =
		"\nstruct CV {\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType::* var;\n"
		"} cv;\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, PadParenOutside)
{
	// should not change scope resolution operator
	char textIn[] =
		"\nBOOL RegisterServer() {\n"
		"    static DOREGSTRUCT ClsidEntries[] = {\n"
		"        { ShowIcon, (LPTSTR)& showIcon},\n"
		"        { Dynamic,  (LPTSTR) & isDynamic},\n"
		"        { Maxtext,  (LPTSTR) &maxText},\n"
		"        { IconID,   (LPTSTR)&iconID},\n"
		"    };\n"
		"}";
	char text[] =
		"\nBOOL RegisterServer() {\n"
		"    static DOREGSTRUCT ClsidEntries[] = {\n"
		"        { ShowIcon, (LPTSTR)& showIcon},\n"
		"        { Dynamic,  (LPTSTR)& isDynamic},\n"
		"        { Maxtext,  (LPTSTR)& maxText},\n"
		"        { IconID,   (LPTSTR)& iconID},\n"
		"    };\n"
		"}";
	char options[] = "align-pointer=type, pad-paren-out";
	char* textOut1 = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	// format twice to be sure an extra space is not added
	char* textOut = AStyleMain(textOut1, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut1;
	delete [] textOut;
}

TEST(AlignPointerType, UnpadParen)
{
	// unpad-paren should NOT delete space padding
	char textIn[] =
		"\nLUA_API lua_State     *(lua_tothread)(lua_State *L, int idx);\n"
		"LUA_API const void     *(lua_topointer)(lua_State *L, int idx);\n";
	char text[] =
		"\nLUA_API lua_State*     (lua_tothread)(lua_State* L, int idx);\n"
		"LUA_API const void*     (lua_topointer)(lua_State* L, int idx);\n";
	char options[] = "align-pointer=type, unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, Catch)
{
	// 'catch' statement is a reference, not an operator
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    try {\n"
		"        wxBufferedInputStream fb(fs);\n"
		"    }\n"
		"    catch (cbException&ex) {\n"
		"        ex.ShowErrorMessage(true);\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    try {\n"
		"        wxBufferedInputStream fb(fs);\n"
		"    }\n"
		"    catch (cbException& ex) {\n"
		"        ex.ShowErrorMessage(true);\n"
		"    }\n"
		"}\n";
	char options[] = "align-pointer=type, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, PostTemplate1)
{
	// post template is a pointer or reference, not an operator
	char textIn[] =
		"\nvoid some_function(int * value,\n"
		"                   int & num,\n"
		"                   std::vector<int> * a\n"
		"                   std::vector<int> & b)\n"
		"{}\n";
	char text[] =
		"\nvoid some_function(int* value,\n"
		"                   int& num,\n"
		"                   std::vector<int>* a\n"
		"                   std::vector<int>& b)\n"
		"{}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, PostTemplate2)
{
	// post template is a pointer or reference, not an operator
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string*>* tempStack1;\n"
		"    vector<string*> * tempStack1;\n"
		"    vector<string*> *tempStack1;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string*>* tempStack1;\n"
		"    vector<string*>* tempStack1;\n"
		"    vector<string*>* tempStack1;\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, AndOperator)
{
	// should not unpad && operator
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo() && isBar())   // comment\n"
		"        return;\n"
		"    if (isFoo && isBar)   // comment\n"
		"        return;\n"
		"    if (isFoo\n"
		"            && isBar1)   // comment\n"
		"        return;\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, Sans1)
{
	// these are not pointers
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    a *= b;\n"
		"    a &= b;\n"
		"    a && b;\n"
		"    x = a * b;\n"
		"    x = a & b;\n"
		"    bar[boo*foo-1] = 2;\n"
		"}\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, Sans2)
{
	// these should be padded as operators
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    a*=b;\n"
		"    a&=b;\n"
		"    a&&b;\n"
		"    x=a*b;\n"
		"    x=a&b;\n"
		"    if (len*tab>longest) bar();\n"
		"    SetWidth(width()+(pixels*indentAmt));\n"
		"    if (m_Flags&flLocal) return;\n"
		"    Link(m_y+.5*h-.5*m_fontSize);\n"
		"    if ((Flags&flVariable)&&(Flags&flId))\n"
		"        bar();\n"
		"    out_html(change_to_size(i*j));\n"
		"    if (i>*maxcol) *maxcol=i;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    a *= b;\n"
		"    a &= b;\n"
		"    a && b;\n"
		"    x = a * b;\n"
		"    x = a & b;\n"
		"    if (len * tab > longest) bar();\n"
		"    SetWidth(width() + (pixels * indentAmt));\n"
		"    if (m_Flags & flLocal) return;\n"
		"    Link(m_y + .5 * h - .5 * m_fontSize);\n"
		"    if ((Flags & flVariable) && (Flags & flId))\n"
		"        bar();\n"
		"    out_html(change_to_size(i * j));\n"
		"    if (i > *maxcol) *maxcol = i;\n"
		"}\n";
	char options[] = "align-pointer=type, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, CppCLI)
{
	// test align-pointer=type on C++/CLI file.
	char textIn[] =
		"\nclass referencetype\n"
		"{\n"
		"protected:\n"
		"    String^ stringVar;\n"
		"    array<int> ^ intArr;\n"
		"    List<double> ^doubleList;\n"
		"    String^ s1 = \"abc\";\n"
		"    Object  ^  o1 = s1;\n"
		"    Object  ^o2 = s2;\n"
		"public:\n"
		"    referencetype(String^ str, int *pointer, int number)\n"
		"    {\n"
		"        System::Console::WriteLine(str->Trim() + number);\n"
		"    }\n"
		"};\n";
	char text[] =
		"\nclass referencetype\n"
		"{\n"
		"protected:\n"
		"    String^ stringVar;\n"
		"    array<int>^ intArr;\n"
		"    List<double>^ doubleList;\n"
		"    String^ s1 = \"abc\";\n"
		"    Object^    o1 = s1;\n"
		"    Object^  o2 = s2;\n"
		"public:\n"
		"    referencetype(String^ str, int* pointer, int number)\n"
		"    {\n"
		"        System::Console::WriteLine(str->Trim() + number);\n"
		"    }\n"
		"};\n";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerType, CSharp)
{
	// test align-pointer=type on C# file.
	char textIn[] =
		"\npublic unsafe void GetValue()\n"
		"{\n"
		"    int i = 5;\n"
		"    int * j = &i;\n"
		"    ret = *((int *) j);\n"
		"    if (int * eventItem =\n"
		"                GetItemData)\n"
		"        fooBar();\n"
		"}\n";
	char text[] =
		"\npublic unsafe void GetValue()\n"
		"{\n"
		"    int i = 5;\n"
		"    int* j = &i;\n"
		"    ret = *((int*) j);\n"
		"    if (int* eventItem =\n"
		"                GetItemData)\n"
		"        fooBar();\n"
		"}\n";
	char options[] = "align-pointer=type, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, LongOption)
{
	// test align pointer=middle
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string* bar;     // comment\n"
		"    const string *bar;     // comment\n"
		"    const string   *bar;   // comment\n"
		"    const string  * bar;   // comment\n"
		"    const string*bar;      // comment\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string * bar)  // comment\n"
		"{\n"
		"    const string * bar;    // comment\n"
		"    const string * bar;    // comment\n"
		"    const string  * bar;   // comment\n"
		"    const string  * bar;   // comment\n"
		"    const string * bar;    // comment\n"
		"    const string & bar;    // comment\n"
		"    const string & bar;    // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string & bar;    // comment\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, ShortOption)
{
	// test align pointer=middle short option
	char textIn[] =
		"\nstring foo(const string *bar)\n"
		"{\n"
		"    const string* bar;\n"
		"    const string *bar;\n"
		"}\n";
	char text[] =
		"\nstring foo(const string * bar)\n"
		"{\n"
		"    const string * bar;\n"
		"    const string * bar;\n"
		"}\n";
	char options[] = "-k2";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, Tabs)
{
	// test with tab separators
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const char	*bar;\n"
		"    const char		*bar;\n"
		"    const char*		bar;\n"
		"    const char		*		bar;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const char	* bar;\n"
		"    const char	*	bar;\n"
		"    const char	*	bar;\n"
		"    const char		*		bar;\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, AddressOf)
{
	// "address of" operator should NOT be separated from the name
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (bar1 == &AS_BAR1\n"
		"            || bar2 == &AS_BAR2)   // comment\n"
		"        return;\n"
		"    return &x;\n"
		"    return (&x);\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, Dereference)
{
	// dereference should NOT be separated from the name
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    TRxtra (*prevWordH);   // comment\n"
		"    if (fileName.empty())\n"
		"        *traceOutF << lineNum << endl;\n"
		"    else\n"
		"        *traceOutF << fileName << endl;\n"
		"    RegisterImage((char **)xpm_data_ptrs[i]);\n"
		"    if (i > *maxcol) *maxcol = i;\n"
		"    *newVec = **iter;\n"
		"    (info.*entryFunc[j])(value);\n"
		"    bool gtr = (*a)->IsLarger(**b);\n"
		"    return *this;\n"
		"    return (*this);\n"
		"    if (*doc) delete *doc;\n"
		"\n"
		"    if(prev) next = next;\n"
		"    else *chain = next;\n"
		"\n"
		"    for (tp::iterator it = p.begin(); it != p.end(); ++it) {\n"
		"        fill( m, **it );\n"
		"    }\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, Dereference2)
{
	// dereference following a comment should NOT be changed
	char text[] =
		"\nvoid f(int ** pp)\n"
		"{\n"
		"    // comment\n"
		"    **pp = 0;\n"
		"}";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, GlobalVariables)
{
	// test with global variables
	char textIn[] =
		"\n// global variables\n"
		"ostream* _err = &cerr;\n"
		"ASConsole* g_console;\n"
		"stringstream* _err = NULL;\n";
	char text[] =
		"\n// global variables\n"
		"ostream * _err = &cerr;\n"
		"ASConsole * g_console;\n"
		"stringstream * _err = NULL;\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, GlobalDeclarations)
{
	// test with global declarations
	char textIn[] =
		"\n// function declarations\n"
		"void *foo(char*fooBar);\n"
		"char&bar(char&);\n";
	char text[] =
		"\n// function declarations\n"
		"void * foo(char * fooBar);\n"
		"char & bar(char &);\n";;
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, Cast1)
{
	// cast should be space padded
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string* bar;          // comment0\n"
		"    foo = (RefNode**) bar();    // comment1\n"
		"    foo = (RefNode*) bar();     // comment2\n"
		"    foo = ( RefNode** ) bar();  // comment1\n"
		"    foo = ( RefNode* ) bar();   // comment2\n"
		"    foo = const_cast<RefNode**>(bar());  // comment3\n"
		"    foo = const_cast<RefNode*>(bar());   // comment4\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string * bar;         // comment0\n"
		"    foo = (RefNode **) bar();   // comment1\n"
		"    foo = (RefNode *) bar();    // comment2\n"
		"    foo = ( RefNode ** ) bar(); // comment1\n"
		"    foo = ( RefNode * ) bar();  // comment2\n"
		"    foo = const_cast<RefNode **>(bar()); // comment3\n"
		"    foo = const_cast<RefNode *>(bar());  // comment4\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, Cast2)
{
	// cast should be space padded
	char textIn[] =
		"\nvoid foo(void*, void*);\n"
		"void foo(void*fooBar, void* fooBar);\n";
	char text[] =
		"\nvoid foo(void *, void *);\n"
		"void foo(void * fooBar, void * fooBar);\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, ConvertTabs)
{
	// test tab conversion on type
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox*	channel;\n"
		"    wxTextCtrl	*filename;\n"
		"    char		*	stamp;\n"
		"    void*			userData;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox * channel;\n"
		"    wxTextCtrl * filename;\n"
		"    char      *     stamp;\n"
		"    void      *     userData;\n"
		"}\n";
	char options[] = "align-pointer=middle, convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, Paren)
{
	// test pointer recognition in a paren
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(cbProject *p = pm->GetProject())\n"
		"        getBar();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(cbProject * p = pm->GetProject())\n"
		"        getBar();\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, PointerToPointer1)
{
	// test double pointer
	char textIn[] =
		"\nint main(int argc, char **argv)\n"
		"{\n"
		"    char    **bar1;\n"
		"    char  **  bar1;\n"
		"    char**    bar1;\n"
		"    char	**	bar1;\n"
		"    char		**		bar1;\n"
		"    char**bar1;\n"
		"}\n";
	char text[] =
		"\nint main(int argc, char ** argv)\n"
		"{\n"
		"    char  **  bar1;\n"
		"    char  **  bar1;\n"
		"    char  **  bar1;\n"
		"    char	**	bar1;\n"
		"    char		**		bar1;\n"
		"    char ** bar1;\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, PointerToPointer2)
{
	// test double pointer beginning a line
	char text[] =
		"\nvoid SQNativeClosure::Mark ( SQCollectable\n"
		"                             ** chain )\n"
		"{\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, EndOfLine1)
{
	// test pointer at end of line
	char textIn[] =
		"\nvoid*\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n";
	char text[] =
		"\nvoid *\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n";
	char options[] = "align-pointer=middle, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, EndOfLine2)
{
	// test pointer at end of line with spaces or comment after
	char textIn[] =
		"\nvoid*   \n"
		"foo() {}\n"
		"\n"
		"char &   \n"
		"bar() {}\n"
		"\n"
		"void*      // comment  \n"
		"foo() {}\n"
		"\n"
		"void **    /* comment */  \n"
		"foo() {}\n"
		"\n"
		"char**   \n"
		"bar() {}\n";
	char text[] =
		"\nvoid *\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n"
		"\n"
		"void *     // comment\n"
		"foo() {}\n"
		"\n"
		"void **    /* comment */\n"
		"foo() {}\n"
		"\n"
		"char **\n"
		"bar() {}\n";
	char options[] = "align-pointer=middle, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, Comment)
{
	// test pointer with comment after
	char textIn[] =
		"\nvoid Foo(WordList*/*keyword*/,\n"
		"         WordList**/*keyword*/) {\n"
		"}\n";
	char text[] =
		"\nvoid Foo(WordList * /*keyword*/,\n"
		"         WordList ** /*keyword*/) {\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, OperatorOverload)
{
	// test pointer with overloaded operator
	char textIn[] =
		"\nclass Foo\n"
		"{\n"
		"    T& operator* () const {};\n"
		"    T * operator-> () {};\n"
		"};\n";
	char text[] =
		"\nclass Foo\n"
		"{\n"
		"    T & operator* () const {};\n"
		"    T * operator-> () {};\n"
		"};\n";
	char options[] = "align-pointer=middle, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, ConversionOperator)
{
	// test pointer with conversion operator
	char textIn[] =
		"\n// conversion operator declarations\n"
		"operator EventRef &() { return fEvent; }\n"
		"operator HIRect * () { return this; }\n"
		"operator bool() { return len ? true : false; }\n"
		"\n"
		"// conversion operator definitions\n"
		"operator EventRef&();\n"
		"operator HIRect *();\n"
		"operator bool() const;\n"
		"\n"
		"// conversion operator casts\n"
		"EventRef& rf = (EventRef&) tf;\n"
		"HIRect *pr   = (HIRect *) tr;\n"
		"bool bb      = (bool) tb;\n";
	char text[] =
		"\n// conversion operator declarations\n"
		"operator EventRef & () { return fEvent; }\n"
		"operator HIRect * () { return this; }\n"
		"operator bool() { return len ? true : false; }\n"
		"\n"
		"// conversion operator definitions\n"
		"operator EventRef & ();\n"
		"operator HIRect * ();\n"
		"operator bool() const;\n"
		"\n"
		"// conversion operator casts\n"
		"EventRef & rf = (EventRef &) tf;\n"
		"HIRect * pr   = (HIRect *) tr;\n"
		"bool bb      = (bool) tb;\n";
	char options[] = "align-pointer=middle, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, ScopeResolution)
{
	// should pad scope resolution operator
	char textIn[] =
		"\nstruct CV {\n"
		"    VarType TClassType::*var;\n"
		"    VarType TClassType:: *var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType:: * var;\n"
		"} cv;\n";
	char text[] =
		"\nstruct CV {\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType::*  var;\n"
		"} cv;\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, PadParenOutside)
{
	// should not change scope resolution operator
	char textIn[] =
		"\nBOOL RegisterServer() {\n"
		"    static DOREGSTRUCT ClsidEntries[] = {\n"
		"        { ShowIcon, (LPTSTR)& showIcon},\n"
		"        { Dynamic,  (LPTSTR) & isDynamic},\n"
		"        { Maxtext,  (LPTSTR) &maxText},\n"
		"        { IconID,   (LPTSTR)&iconID},\n"
		"    };\n"
		"}";
	char text[] =
		"\nBOOL RegisterServer() {\n"
		"    static DOREGSTRUCT ClsidEntries[] = {\n"
		"        { ShowIcon, (LPTSTR) & showIcon},\n"
		"        { Dynamic,  (LPTSTR) & isDynamic},\n"
		"        { Maxtext,  (LPTSTR) & maxText},\n"
		"        { IconID,   (LPTSTR) & iconID},\n"
		"    };\n"
		"}";
	char options[] = "align-pointer=middle, pad-paren-out";
	char* textOut1 = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	// format twice to be sure an extra space is not added
	char* textOut = AStyleMain(textOut1, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut1;
	delete [] textOut;
}

TEST(AlignPointerMiddle, UnpadParen)
{
	// unpad-paren should NOT delete space padding
	char textIn[] =
		"\nLUA_API lua_State*     (lua_tothread)(lua_State *L, int idx);\n"
		"LUA_API const void     *(lua_topointer)(lua_State *L, int idx);\n";
	char text[] =
		"\nLUA_API lua_State   *  (lua_tothread)(lua_State * L, int idx);\n"
		"LUA_API const void   *  (lua_topointer)(lua_State * L, int idx);\n";
	char options[] = "align-pointer=middle, unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, Catch)
{
	// 'catch' statement is a reference, not an operator
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    try {\n"
		"        wxBufferedInputStream fb(fs);\n"
		"    }\n"
		"    catch (cbException&ex) {\n"
		"        ex.ShowErrorMessage(true);\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    try {\n"
		"        wxBufferedInputStream fb(fs);\n"
		"    }\n"
		"    catch (cbException & ex) {\n"
		"        ex.ShowErrorMessage(true);\n"
		"    }\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}


TEST(AlignPointerMiddle, PostTemplate1)
{
	// post template is a pointer or reference, not an operator
	char textIn[] =
		"\nvoid some_function(int* value,\n"
		"                   int &num,\n"
		"                   std::vector<int> *a\n"
		"                   std::vector<int>& b)\n"
		"{}\n";
	char text[] =
		"\nvoid some_function(int * value,\n"
		"                   int & num,\n"
		"                   std::vector<int> * a\n"
		"                   std::vector<int> & b)\n"
		"{}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, PostTemplate2)
{
	// post template is a pointer or reference, not an operator
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string*>* tempStack1;\n"
		"    vector<string*> * tempStack1;\n"
		"    vector<string*> *tempStack1;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string *> * tempStack1;\n"
		"    vector<string *> * tempStack1;\n"
		"    vector<string *> * tempStack1;\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, AndOperator)
{
	// should not unpad && operator
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo() && isBar())   // comment\n"
		"        return;\n"
		"    if (isFoo && isBar)   // comment\n"
		"        return;\n"
		"    if (isFoo\n"
		"            && isBar1)   // comment\n"
		"        return;\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, Sans1)
{
	// these are not pointers
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    a *= b;\n"
		"    a &= b;\n"
		"    a && b;\n"
		"    x = a * b;\n"
		"    x = a & b;\n"
		"    bar[boo*foo-1] = 2;\n"
		"}\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, Sans2)
{
	// these should be padded as operators
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    a*=b;\n"
		"    a&=b;\n"
		"    a&&b;\n"
		"    x=a*b;\n"
		"    x=a&b;\n"
		"    if (len*tab>longest) bar();\n"
		"    SetWidth(width()+(pixels*indentAmt));\n"
		"    if (m_Flags&flLocal) return;\n"
		"    Link(m_y+.5*h-.5*m_fontSize);\n"
		"    if ((Flags&flVariable)&&(Flags&flId))\n"
		"        bar();\n"
		"    out_html(change_to_size(i*j));\n"
		"    if (i>*maxcol) *maxcol=i;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    a *= b;\n"
		"    a &= b;\n"
		"    a && b;\n"
		"    x = a * b;\n"
		"    x = a & b;\n"
		"    if (len * tab > longest) bar();\n"
		"    SetWidth(width() + (pixels * indentAmt));\n"
		"    if (m_Flags & flLocal) return;\n"
		"    Link(m_y + .5 * h - .5 * m_fontSize);\n"
		"    if ((Flags & flVariable) && (Flags & flId))\n"
		"        bar();\n"
		"    out_html(change_to_size(i * j));\n"
		"    if (i > *maxcol) *maxcol = i;\n"
		"}\n";
	char options[] = "align-pointer=middle, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, CppCLI)
{
	// test align-pointer=middle on C++/CLI file.
	char textIn[] =
		"\nclass referencetype\n"
		"{\n"
		"protected:\n"
		"    String^ stringVar;\n"
		"    array<int> ^ intArr;\n"
		"    List<double> ^doubleList;\n"
		"    String^ s1 = \"abc\";\n"
		"    Object  ^  o1 = s1;\n"
		"    Object  ^o2 = s2;\n"
		"public:\n"
		"    referencetype(String^ str, int *pointer, int number)\n"
		"    {\n"
		"        System::Console::WriteLine(str->Trim() + number);\n"
		"    }\n"
		"};\n";
	char text[] =
		"\nclass referencetype\n"
		"{\n"
		"protected:\n"
		"    String ^ stringVar;\n"
		"    array<int> ^ intArr;\n"
		"    List<double> ^ doubleList;\n"
		"    String ^ s1 = \"abc\";\n"
		"    Object  ^  o1 = s1;\n"
		"    Object ^ o2 = s2;\n"
		"public:\n"
		"    referencetype(String ^ str, int * pointer, int number)\n"
		"    {\n"
		"        System::Console::WriteLine(str->Trim() + number);\n"
		"    }\n"
		"};\n";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerMiddle, CSharp)
{
	// test align-pointer=middle on C# file.
	char textIn[] =
		"\npublic unsafe void GetValue()\n"
		"{\n"
		"    int i = 5;\n"
		"    int* j = &i;\n"
		"    ret = *((int*) j);\n"
		"    if (int *eventItem =\n"
		"                GetItemData)\n"
		"        fooBar();\n"
		"}\n";
	char text[] =
		"\npublic unsafe void GetValue()\n"
		"{\n"
		"    int i = 5;\n"
		"    int * j = &i;\n"
		"    ret = *((int *) j);\n"
		"    if (int * eventItem =\n"
		"                GetItemData)\n"
		"        fooBar();\n"
		"}\n";
	char options[] = "align-pointer=middle, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}
TEST(AlignPointerName, LongOption)
{
	// test align pointer=name
	char textIn[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string* bar;     // comment\n"
		"    const string *bar;     // comment\n"
		"    const string   *bar;   // comment\n"
		"    const string  * bar;   // comment\n"
		"    const string*bar;      // comment\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string *bar;     // comment\n"
		"    const string *bar;     // comment\n"
		"    const string   *bar;   // comment\n"
		"    const string   *bar;   // comment\n"
		"    const string *bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string &bar;     // comment\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, ShortOption)
{
	// test align pointer=name short option
	char textIn[] =
		"\nstring foo(const string* bar)\n"
		"{\n"
		"    const string *bar;\n"
		"    const string* bar;\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)\n"
		"{\n"
		"    const string *bar;\n"
		"    const string *bar;\n"
		"}\n";
	char options[] = "-k3";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, FromCentered)
{
	// test align pointer=name when input is centered
	// a space is deleted in certain circumstances
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string * bar;     // remove space\n"
		"    const string  * bar;    // don't remove\n"
		"    const string *  bar;    // don't remove\n"
		"    const string* bar;      // don't remove\n"
		"    const string *bar;      // don't remove\n"
		"\n"
		"    const string ** bar;    // remove space\n"
		"    const string  ** bar;   // don't remove\n"
		"    const string **  bar;   // don't remove\n"
		"    const string** bar;     // don't remove\n"
		"    const string **bar;     // don't remove\n"
		"\n"
		"    const string & bar;     // remove space\n"
		"    const string  & bar;    // don't remove\n"
		"    const string &  bar;    // don't remove\n"
		"    const string& bar;      // don't remove\n"
		"    const string &bar;      // don't remove\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string *bar;      // remove space\n"
		"    const string   *bar;    // don't remove\n"
		"    const string   *bar;    // don't remove\n"
		"    const string *bar;      // don't remove\n"
		"    const string *bar;      // don't remove\n"
		"\n"
		"    const string **bar;     // remove space\n"
		"    const string   **bar;   // don't remove\n"
		"    const string   **bar;   // don't remove\n"
		"    const string **bar;     // don't remove\n"
		"    const string **bar;     // don't remove\n"
		"\n"
		"    const string &bar;      // remove space\n"
		"    const string   &bar;    // don't remove\n"
		"    const string   &bar;    // don't remove\n"
		"    const string &bar;      // don't remove\n"
		"    const string &bar;      // don't remove\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, Tabs)
{
	// test with tab separators
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const char*	bar;\n"
		"    const char	*	bar;\n"
		"    const char		*bar;\n"
		"    const char		*		bar;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const char	*bar;\n"
		"    const char		*bar;\n"
		"    const char		*bar;\n"
		"    const char				*bar;\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, AddressOf)
{
	// "address of" operator should NOT be separated from the name
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (bar1 == &AS_BAR1\n"
		"            || bar2 == &AS_BAR2)   // comment\n"
		"        return;\n"
		"    return &x;\n"
		"    return (&x);\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, Dereference)
{
	// dereference should NOT be separated from the name
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    TRxtra (*prevWordH);   // comment\n"
		"    if (fileName.empty())\n"
		"        *traceOutF << lineNum << endl;\n"
		"    else\n"
		"        *traceOutF << fileName << endl;\n"
		"    RegisterImage((char **)xpm_data_ptrs[i]);\n"
		"    if (i > *maxcol) *maxcol = i;\n"
		"    *newVec = **iter;\n"
		"    (info.*entryFunc[j])(value);\n"
		"    bool gtr = (*a)->IsLarger(**b);\n"
		"    return *this;\n"
		"    return (*this);\n"
		"    if (*doc) delete *doc;\n"
		"\n"
		"    if(prev) next = next;\n"
		"    else *chain = next;\n"
		"\n"
		"    for (tp::iterator it = p.begin(); it != p.end(); ++it) {\n"
		"        fill( m, **it );\n"
		"    }\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, Dereference2)
{
	// dereference following a comment should NOT be changed
	char text[] =
		"\nvoid f(int **pp)\n"
		"{\n"
		"    // comment\n"
		"    **pp = 0;\n"
		"}";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, GlobalVariables)
{
	// test with global variables
	char textIn[] =
		"\n// global variables\n"
		"ostream* _err = &cerr;\n"
		"ASConsole* g_console;\n"
		"stringstream* _err = NULL;\n";
	char text[] =
		"\n// global variables\n"
		"ostream *_err = &cerr;\n"
		"ASConsole *g_console;\n"
		"stringstream *_err = NULL;\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, GlobalDeclarations)
{
	// test with global declarations
	char textIn[] =
		"\n// function declarations\n"
		"void* foo(char*fooBar);\n"
		"char&bar(char&);\n";
	char text[] =
		"\n// function declarations\n"
		"void *foo(char *fooBar);\n"
		"char &bar(char &);\n";;
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, Cast1)
{
	// cast should be space padded
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string* bar;          // comment0\n"
		"    foo = (RefNode**) bar();    // comment1\n"
		"    foo = (RefNode*) bar();     // comment2\n"
		"    foo = ( RefNode** ) bar();  // comment1\n"
		"    foo = ( RefNode* ) bar();   // comment2\n"
		"    foo = const_cast<RefNode**>(bar());  // comment3\n"
		"    foo = const_cast<RefNode*>(bar());   // comment4\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    const string *bar;          // comment0\n"
		"    foo = (RefNode **) bar();   // comment1\n"
		"    foo = (RefNode *) bar();    // comment2\n"
		"    foo = ( RefNode ** ) bar(); // comment1\n"
		"    foo = ( RefNode * ) bar();  // comment2\n"
		"    foo = const_cast<RefNode **>(bar()); // comment3\n"
		"    foo = const_cast<RefNode *>(bar());  // comment4\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, Cast2)
{
	// cast should be space padded
	char textIn[] =
		"\nvoid foo(void*, void*);\n"
		"void foo(void*fooBar, void* fooBar);\n";
	char text[] =
		"\nvoid foo(void *, void *);\n"
		"void foo(void *fooBar, void *fooBar);\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, ConvertTabs)
{
	// test tab conversion on type
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox*	channel;\n"
		"    wxTextCtrl*	filename;\n"
		"    char		*	stamp;\n"
		"    void*			userData;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    wxListBox  *channel;\n"
		"    wxTextCtrl *filename;\n"
		"    char           *stamp;\n"
		"    void           *userData;\n"
		"}\n";
	char options[] = "align-pointer=name, convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, Paren)
{
	// test pointer recognition in a paren
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(cbProject * p = pm->GetProject())\n"
		"        getBar();\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if(cbProject *p = pm->GetProject())\n"
		"        getBar();\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, PointerToPointer1)
{
	// test double pointer
	char textIn[] =
		"\nint main(int argc, char** argv)\n"
		"{\n"
		"    char**    bar1;\n"
		"    char  **  bar1;\n"
		"    char    **bar1;\n"
		"    char	**	bar1;\n"
		"    char		**		bar1;\n"
		"}\n";
	char text[] =
		"\nint main(int argc, char **argv)\n"
		"{\n"
		"    char    **bar1;\n"
		"    char    **bar1;\n"
		"    char    **bar1;\n"
		"    char		**bar1;\n"
		"    char				**bar1;\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, PointerToPointer2)
{
	// test double pointer beginning a line
	char text[] =
		"\nvoid SQNativeClosure::Mark ( SQCollectable\n"
		"                             **chain )\n"
		"{\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, EndOfLine1)
{
	// test pointer at end of line
	char textIn[] =
		"\nvoid*\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n";
	char text[] =
		"\nvoid *\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n";
	char options[] = "align-pointer=name, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, EndOfLine2)
{
	// test pointer at end of line with spaces or comment after
	char textIn[] =
		"\nvoid*   \n"
		"foo() {}\n"
		"\n"
		"char &   \n"
		"bar() {}\n"
		"\n"
		"void*      // comment  \n"
		"foo() {}\n"
		"\n"
		"void **    /* comment */  \n"
		"foo() {}\n"
		"\n"
		"char**   \n"
		"bar() {}\n";
	char text[] =
		"\nvoid *\n"
		"foo() {}\n"
		"\n"
		"char &\n"
		"bar() {}\n"
		"\n"
		"void *     // comment\n"
		"foo() {}\n"
		"\n"
		"void **    /* comment */\n"
		"foo() {}\n"
		"\n"
		"char **\n"
		"bar() {}\n";
	char options[] = "align-pointer=name, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, Comment)
{
	// test pointer with comment after
	char textIn[] =
		"\nvoid Foo(WordList*/*keyword*/,\n"
		"         WordList**/*keyword*/) {\n"
		"}\n";
	char text[] =
		"\nvoid Foo(WordList */*keyword*/,\n"
		"         WordList **/*keyword*/) {\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, OperatorOverload)
{
	// test pointer with overloaded operator
	char textIn[] =
		"\nclass Foo\n"
		"{\n"
		"    T& operator* () const {};\n"
		"    T * operator-> () {};\n"
		"};\n";
	char text[] =
		"\nclass Foo\n"
		"{\n"
		"    T &operator* () const {};\n"
		"    T *operator-> () {};\n"
		"};\n";
	char options[] = "align-pointer=name, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, ConversionOperator)
{
	// test pointer with conversion operator
	char textIn[] =
		"\n// conversion operator declarations\n"
		"operator EventRef &() { return fEvent; }\n"
		"operator HIRect * () { return this; }\n"
		"operator bool() { return len ? true : false; }\n"
		"\n"
		"// conversion operator definitions\n"
		"operator EventRef&();\n"
		"operator HIRect *();\n"
		"operator bool() const;\n"
		"\n"
		"// conversion operator casts\n"
		"EventRef& rf = (EventRef&) tf;\n"
		"HIRect *pr   = (HIRect *) tr;\n"
		"bool bb      = (bool) tb;\n";
	char text[] =
		"\n// conversion operator declarations\n"
		"operator EventRef &() { return fEvent; }\n"
		"operator HIRect *() { return this; }\n"
		"operator bool() { return len ? true : false; }\n"
		"\n"
		"// conversion operator definitions\n"
		"operator EventRef &();\n"
		"operator HIRect *();\n"
		"operator bool() const;\n"
		"\n"
		"// conversion operator casts\n"
		"EventRef &rf = (EventRef &) tf;\n"
		"HIRect *pr   = (HIRect *) tr;\n"
		"bool bb      = (bool) tb;\n";
	char options[] = "align-pointer=name, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, ScopeResolution)
{
	// should not pad scope resolution operator
	char textIn[] =
		"\nstruct CV {\n"
		"    VarType TClassType::*var;\n"
		"    VarType TClassType:: *var;\n"
		"    VarType TClassType::* var;\n"
		"    VarType TClassType:: * var;\n"
		"} cv;\n";
	char text[] =
		"\nstruct CV {\n"
		"    VarType TClassType::*var;\n"
		"    VarType TClassType::*var;\n"
		"    VarType TClassType::*var;\n"
		"    VarType TClassType::*var;\n"
		"} cv;\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, PadParenOutside)
{
	// test align-pointer with pad-paren-out
	char textIn[] =
		"\nBOOL RegisterServer() {\n"
		"    static DOREGSTRUCT ClsidEntries[] = {\n"
		"        { ShowIcon, (LPTSTR)& showIcon},\n"
		"        { Dynamic,  (LPTSTR) & isDynamic},\n"
		"        { Maxtext,  (LPTSTR) &maxText},\n"
		"        { IconID,   (LPTSTR)&iconID},\n"
		"    };\n"
		"}";
	char text[] =
		"\nBOOL RegisterServer() {\n"
		"    static DOREGSTRUCT ClsidEntries[] = {\n"
		"        { ShowIcon, (LPTSTR) &showIcon},\n"
		"        { Dynamic,  (LPTSTR) &isDynamic},\n"
		"        { Maxtext,  (LPTSTR) &maxText},\n"
		"        { IconID,   (LPTSTR) &iconID},\n"
		"    };\n"
		"}";
	char options[] = "align-pointer=name, pad-paren-out";
	char* textOut1 = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	// format twice to be sure an extra space is not added
	char* textOut = AStyleMain(textOut1, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut1;
	delete [] textOut;
}

TEST(AlignPointerName, UnpadParen)
{
	// unpad-paren should NOT delete space padding
	char textIn[] =
		"\nLUA_API lua_State*     (lua_tothread)(lua_State *L, int idx);\n"
		"LUA_API const void*     (lua_topointer)(lua_State *L, int idx);\n";
	char text[] =
		"\nLUA_API lua_State     *(lua_tothread)(lua_State *L, int idx);\n"
		"LUA_API const void     *(lua_topointer)(lua_State *L, int idx);\n";
	char options[] = "align-pointer=name, unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, Catch)
{
	// 'catch' statement is a reference, not an operator
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    try {\n"
		"        wxBufferedInputStream fb(fs);\n"
		"    }\n"
		"    catch (cbException&ex) {\n"
		"        ex.ShowErrorMessage(true);\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    try {\n"
		"        wxBufferedInputStream fb(fs);\n"
		"    }\n"
		"    catch (cbException &ex) {\n"
		"        ex.ShowErrorMessage(true);\n"
		"    }\n"
		"}\n";
	char options[] = "align-pointer=name, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}


TEST(AlignPointerName, PostTemplate1)
{
	// post template is a pointer or reference, not an operator
	char textIn[] =
		"\nvoid some_function(int * value,\n"
		"                   int& num,\n"
		"                   std::vector<int>* a\n"
		"                   std::vector<int> & b)\n"
		"{}\n";
	char text[] =
		"\nvoid some_function(int *value,\n"
		"                   int &num,\n"
		"                   std::vector<int> *a\n"
		"                   std::vector<int> &b)\n"
		"{}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, PostTemplate2)
{
	// post template is a pointer or reference, not an operator
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string*>* tempStack1;\n"
		"    vector<string*> * tempStack1;\n"
		"    vector<string*> *tempStack1;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string *> *tempStack1;\n"
		"    vector<string *> *tempStack1;\n"
		"    vector<string *> *tempStack1;\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, AndOperator)
{
	// should not unpad && operator
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo() && isBar())   // comment\n"
		"        return;\n"
		"    if (isFoo && isBar)   // comment\n"
		"        return;\n"
		"    if (isFoo\n"
		"            && isBar1)   // comment\n"
		"        return;\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, Sans1)
{
	// these are not pointers
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    a *= b;\n"
		"    a &= b;\n"
		"    a && b;\n"
		"    x = a * b;\n"
		"    x = a & b;\n"
		"    bar[boo*foo-1] = 2;\n"
		"}\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, Sans2)
{
	// these should be padded as operators
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    a*=b;\n"
		"    a&=b;\n"
		"    a&&b;\n"
		"    x=a*b;\n"
		"    x=a&b;\n"
		"    if (len*tab>longest) bar();\n"
		"    SetWidth(width()+(pixels*indentAmt));\n"
		"    if (m_Flags&flLocal) return;\n"
		"    Link(m_y+.5*h-.5*m_fontSize);\n"
		"    if ((Flags&flVariable)&&(Flags&flId))\n"
		"        bar();\n"
		"    out_html(change_to_size(i*j));\n"
		"    if (i>*maxcol) *maxcol=i;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    a *= b;\n"
		"    a &= b;\n"
		"    a && b;\n"
		"    x = a * b;\n"
		"    x = a & b;\n"
		"    if (len * tab > longest) bar();\n"
		"    SetWidth(width() + (pixels * indentAmt));\n"
		"    if (m_Flags & flLocal) return;\n"
		"    Link(m_y + .5 * h - .5 * m_fontSize);\n"
		"    if ((Flags & flVariable) && (Flags & flId))\n"
		"        bar();\n"
		"    out_html(change_to_size(i * j));\n"
		"    if (i > *maxcol) *maxcol = i;\n"
		"}\n";
	char options[] = "align-pointer=name, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, CppCLI)
{
	// test align-pointer=name on C++/CLI file.
	char textIn[] =
		"\nclass referencetype\n"
		"{\n"
		"protected:\n"
		"    String ^ stringVar;\n"
		"    array<int> ^ intArr;\n"
		"    List<double> ^ doubleList;\n"
		"    String ^ s1 = \"abc\";\n"
		"    Object  ^  o1 = s1;\n"
		"    Object ^ o2 = s2;\n"
		"public:\n"
		"    referencetype(String ^ str, int * pointer, int number)\n"
		"    {\n"
		"        System::Console::WriteLine(str->Trim() + number);\n"
		"    }\n"
		"};\n";
	char text[] =
		"\nclass referencetype\n"
		"{\n"
		"protected:\n"
		"    String ^stringVar;\n"
		"    array<int> ^intArr;\n"
		"    List<double> ^doubleList;\n"
		"    String ^s1 = \"abc\";\n"
		"    Object    ^o1 = s1;\n"
		"    Object ^o2 = s2;\n"
		"public:\n"
		"    referencetype(String ^str, int *pointer, int number)\n"
		"    {\n"
		"        System::Console::WriteLine(str->Trim() + number);\n"
		"    }\n"
		"};\n";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignPointerName, CSharp)
{
	// test align-pointer=type on C# file.
	char textIn[] =
		"\npublic unsafe void GetValue()\n"
		"{\n"
		"    int i = 5;\n"
		"    int* j = &i;\n"
		"    ret = *((int*) j);\n"
		"    if (int* eventItem =\n"
		"                GetItemData)\n"
		"        fooBar();\n"
		"}\n";
	char text[] =
		"\npublic unsafe void GetValue()\n"
		"{\n"
		"    int i = 5;\n"
		"    int *j = &i;\n"
		"    ret = *((int *) j);\n"
		"    if (int *eventItem =\n"
		"                GetItemData)\n"
		"        fooBar();\n"
		"}\n";
	char options[] = "align-pointer=name, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}
TEST(AlignPointer, ShortLowerLimit)
{
	// test error handling for the short option lower limit
	// should call the error handler
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	// use errorHandler2 to verify the error
	char options[] = "-k0";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	delete [] textOut;
}

TEST(AlignPointer, ShortUpperLimit)
{
	// test error handling for the short option upper limit
	// should call the error handler
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    bar();\n"
		"}\n";
	// use errorHandler2 to verify the error
	char options[] = "-k4";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	delete [] textOut;
}

TEST(AlignPointer, Java)
{
	// align-pointer should have no effect on Java
	// should pad-oper not align-pointer=type
	char textIn[] =
		"\nbool foo()\n"
		"{\n"
		"    StringBuilder s = new StringBuilder(length*count);\n"
		"    return (modifier&query) == query;\n"
		"}\n";
	char text[] =
		"\nbool foo()\n"
		"{\n"
		"    StringBuilder s = new StringBuilder(length * count);\n"
		"    return (modifier & query) == query;\n"
		"}\n";
	char options[] = "mode=java, pad-oper, align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}


//-------------------------------------------------------------------------
// AStyle Align Reference
// default value REF_SAME_AS_PTR is tested with Align Pointer
//-------------------------------------------------------------------------
TEST(AlignReferenceNone, PointerNone)
{
	// references should not be changed
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char options[] = "align-reference=none";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceNone, PointerType)
{
	// references should not be changed
	char text[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char options[] = "align-reference=none, align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceNone, PointerMiddle)
{
	// references should not be changed
	char text[] =
		"\nstring foo(const string * bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char options[] = "align-reference=none, align-pointer=middle";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceNone, PointerName)
{
	// references should not be changed
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char options[] = "align-reference=none, align-pointer=name";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceNone, ShortOption)
{
	// test align-reference=none short option
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char options[] = "-W0";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}
TEST(AlignReferenceType, PointerNone)
{
	// test align-reference=type
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string& bar;     // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string& bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceType, PointerType)
{
	// test align-reference=type
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string& bar;     // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string& bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=type, align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}
TEST(AlignReferenceType, PointerMiddle)
{
	// test align-reference=type
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string * bar)  // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string& bar;     // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string& bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=type, align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}
TEST(AlignReferenceType, PointerName)
{
	// test align-reference=type
	char textIn[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string& bar;     // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string& bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=type, align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceType, ShortOption)
{
	// test align-reference=type short option
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string& bar;     // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string&    bar;  // comment\n"
		"    const string& bar;     // comment\n"
		"}\n";
	char options[] = "-W1";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceMiddle, PointerNone)
{
	// test align-reference=middle
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string & bar;    // comment\n"
		"    const string & bar;    // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string & bar;    // comment\n"
		"}\n";
	char options[] = "align-reference=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceMiddle, PointerType)
{
	// test align-reference=middle
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string & bar;    // comment\n"
		"    const string & bar;    // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string & bar;    // comment\n"
		"}\n";
	char options[] = "align-reference=middle, align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}
TEST(AlignReferenceMiddle, PointerMiddle)
{
	// test align-reference=middle
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string * bar)  // comment\n"
		"{\n"
		"    const string & bar;    // comment\n"
		"    const string & bar;    // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string & bar;    // comment\n"
		"}\n";
	char options[] = "align-reference=middle, align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}
TEST(AlignReferenceMiddle, PointerName)
{
	// test align-reference=middle
	char textIn[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string & bar;    // comment\n"
		"    const string & bar;    // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string & bar;    // comment\n"
		"}\n";
	char options[] = "align-reference=middle, align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceMiddle, ShortOption)
{
	// test align-reference=middle short option
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string & bar;    // comment\n"
		"    const string & bar;    // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string & bar;    // comment\n"
		"}\n";
	char options[] = "-W2";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceName, PointerNone)
{
	// test align-reference=name
	char textIn[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string &bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string &bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceName, PointerType)
{
	// test align-reference=name
	char textIn[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string &bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string &bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=name, align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceName, PointerMiddle)
{
	// test align-reference=name
	char textIn[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string * bar)  // comment\n"
		"{\n"
		"    const string &bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string &bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=name, align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceName, Pointername)
{
	// test align-reference=name
	char textIn[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string *bar)   // comment\n"
		"{\n"
		"    const string &bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string &bar;     // comment\n"
		"}\n";
	char options[] = "align-reference=name, align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceName, ShortOption)
{
	// test align-reference=name short option
	char textIn[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string& bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string  &  bar;  // comment\n"
		"    const string&bar;      // comment\n"
		"}\n";
	char text[] =
		"\nstring foo(const string* bar)   // comment\n"
		"{\n"
		"    const string &bar;     // comment\n"
		"    const string &bar;     // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string    &bar;  // comment\n"
		"    const string &bar;     // comment\n"
		"}\n";
	char options[] = "-W3";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Align Pointer and Align Reference for special case of Reference to a Pointer (*&)
// Cannot have a Pointer to a Reference (&*)
//-------------------------------------------------------------------------
TEST(AlignReferenceToPointer, PointerType_ReferenceDefault)
{
	// Test *& with align-pointer=type and align-reference default.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> * & container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType>*& container)\n"
		"{}\n"
		"void buildOperators (vector<const string*>& operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*>*& container)\n"
		"{}";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceToPointer, PointerType_ReferenceType)
{
	// Test *& with align-pointer=type and align-reference=type.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> * & container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType>*& container)\n"
		"{}\n"
		"void buildOperators (vector<const string*>& operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*>*& container)\n"
		"{}";
	char options[] = "align-pointer=type, align-reference=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceToPointer, PointerType_ReferenceMiddle)
{
	// Test *& with align-pointer=type and align-reference=middle.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string *>& operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> * &container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType>* & container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*>* & container)\n"
		"{}";
	char options[] = "align-pointer=type, align-reference=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceToPointer, PointerType_ReferenceName)
{
	// Test *& with align-pointer=type and align-reference=name.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string*>& operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> * & container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType>* &container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> &operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*>* &container)\n"
		"{}";
	char options[] = "align-pointer=type, align-reference=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceToPointer, PointerMiddle_ReferenceType_)
{
	// Test *& with align-pointer=middle and align-reference=type.
	// Conflicting alignments aligns both to pointer value.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*>* &container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> *& container)\n"
		"{}\n"
		"void buildOperators (vector<const string *>& operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> *& container)\n"
		"{}";
	char options[] = "align-pointer=middle, align-reference=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceToPointer, PointerMiddle_ReferenceDefault)
{
	// Test *& with align-pointer=middle and align-reference default.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> &operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*> *& container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> *& container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> *& container)\n"
		"{}";
	char options[] = "align-pointer=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceToPointer, PointerMiddle_ReferenceMiddle)
{
	// Test *& with align-pointer=middle and align-reference=middle.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> &operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*> *& container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> *& container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> *& container)\n"
		"{}";
	char options[] = "align-pointer=middle, align-reference=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceToPointer, PointerMiddle_ReferenceName)
{
	// Test *& with align-pointer=middle and align-reference=name.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType> *& container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*>* &container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> * &container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> &operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> * &container)\n"
		"{}";
	char options[] = "align-pointer=middle, align-reference=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceToPointer, PointerName_ReferenceType)
{
	// Test *& with align-pointer=name and align-reference=type.
	// Conflicting alignments aligns both to pointer value.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType>*& container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*>* &container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string *>& operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> *&container)\n"
		"{}";
	char options[] = "align-pointer=name, align-reference=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceToPointer, PointerName_ReferenceMiddle)
{
	// Test *& with align-pointer=name and align-reference=middle.
	// Conflicting alignments aligns both to pointer value.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType>*& container)\n"
		"{}\n"
		"void buildOperators (vector<const string*>& operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*>* &container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> *&container)\n"
		"{}";
	char options[] = "align-pointer=name, align-reference=middle";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceToPointer, PointerName_ReferenceDefault)
{
	// Test *& with align-pointer=middle and align-reference default.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType>*& container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*> * & container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> &operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> *&container)\n"
		"{}";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AlignReferenceToPointer, PointerName_ReferenceName)
{
	// Test *& with align-pointer=name and align-reference=name.
	char textIn[] =
		"\nvoid deleteContainer2 (vector<BracketType>*& container)\n"
		"{}\n"
		"void buildOperators (vector<const string*> & operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string*>*> * & container)\n"
		"{}";
	char text[] =
		"\nvoid deleteContainer2 (vector<BracketType> *&container)\n"
		"{}\n"
		"void buildOperators (vector<const string *> &operators)\n"
		"{}\n"
		"void deleteContainer1 (vector<vector<const string *>*> *&container)\n"
		"{}";
	char options[] = "align-pointer=name, align-reference=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}


//----------------------------------------------------------------------------

}  // namespace
