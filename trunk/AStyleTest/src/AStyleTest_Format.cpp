//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleTest.h"

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {

//-------------------------------------------------------------------------
// AStyle Break Closing Brackets
// Additional tests are in the Brackets tests
//-------------------------------------------------------------------------

TEST(BreakClosingBrackets, LongOption)
{
	// test NONE_MODE brackets with break closing headers
	char textIn[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char text[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"    else {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char options[] = "break-closing-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakClosingBrackets, ShortOption)
{
	// test NONE_MODE brackets with break closing headers
	char textIn[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char text[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"    else {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char options[] = "-y";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakClosingBrackets, Break)
{
	// test BREAK_MODE brackets with break closing headers
	char textIn[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char text[] =
		"\nvoid FooClass::Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        bar();\n"
		"    }\n"
		"    else\n"
		"    {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char options[] = "brackets=break, break-closing-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakClosingBrackets, Attach)
{
	// test ATTACH_MODE brackets with break closing headers
	char textIn[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char text[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"    else {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char options[] = "brackets=attach, break-closing-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakClosingBrackets, Linux)
{
	// test LINUX_MODE brackets with break closing headers
	char textIn[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char text[] =
		"\nvoid FooClass::Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"    else {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char options[] = "brackets=linux, break-closing-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakClosingBrackets, Stroustrup)
{
	// test STROUSTRUP_MODE brackets with break closing headers
	char textIn[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char text[] =
		"\nvoid FooClass::Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"    else {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char options[] = "brackets=stroustrup, break-closing-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakClosingBrackets, KeepBlocks)
{
	// test break closing headers with keep one line blocks
	// it shouldn't make any difference
	char textIn[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char text[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"    else {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char options[] = "brackets=attach, break-closing-brackets, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakClosingBrackets, ElseSans)
{
	// test if/else without break closing brackets
	// else statement should be attached to the closing bracket
	char textIn[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"    else {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char text[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else {\n"
		"        anotherBar();\n"
		"    }\n"
		"}\n"
		"\n";
	char options[] = "brackets=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakClosingBrackets, Catch)
{
	// test try/catch with break closing brackets
	char textIn[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    try {\n"
		"        bar();\n"
		"    } catch (int i) {\n"
		"        cout << i << endl;\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    try {\n"
		"        bar();\n"
		"    }\n"
		"    catch (int i) {\n"
		"        cout << i << endl;\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=attach, break-closing-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakClosingBrackets, CatchSans)
{
	// test try/catch without break closing brackets
	// catch statement should be attached to the closing bracket
	char textIn[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    try {\n"
		"        bar();\n"
		"    }\n"
		"    catch (int i) {\n"
		"        cout << i << endl;\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    try {\n"
		"        bar();\n"
		"    } catch (int i) {\n"
		"        cout << i << endl;\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakClosingBrackets, While)
{
	// test do/while with break closing brackets
	char textIn[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    do {\n"
		"        bar();\n"
		"    } while (int x < 9);\n"
		"}\n";
	char text[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    do {\n"
		"        bar();\n"
		"    }\n"
		"    while (int x < 9);\n"
		"}\n";
	char options[] = "brackets=attach, break-closing-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakClosingBrackets, WhileSans)
{
	// test do/while without break closing brackets
	// while statement should be attached to the closing bracket
	char textIn[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    do {\n"
		"        bar();\n"
		"    }\n"
		"    while (int x < 9);\n"
		"}\n";
	char text[] =
		"\nvoid FooClass::Foo(bool isFoo) {\n"
		"    do {\n"
		"        bar();\n"
		"    } while (int x < 9);\n"
		"}\n";
	char options[] = "brackets=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Break Else If
//-------------------------------------------------------------------------

TEST(BreakElseIfs, LongOption)
{
	// test break else/if
	// else/if statements should be broken
	char textIn[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else\n"
		"        if (isBar) {\n"
		"            anotherBar();\n"
		"            } else    if (isBar) {\n"
		"                anotherBar();\n"
		"            } else {\n"
		"                if (isBar) {\n"
		"                    anotherBar();\n"
		"                }\n"
		"            }\n"
		"\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else anotherBar();\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"\n"
		"#if 0\n"
		"    foo();\n"
		"#else\n"
		"    if (bar)\n"
		"        fooBar();\n"
		"#endif\n"
		"}\n";
	char text[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else\n"
		"        if (isBar) {\n"
		"            anotherBar();\n"
		"        } else\n"
		"            if (isBar) {\n"
		"                anotherBar();\n"
		"            } else {\n"
		"                if (isBar) {\n"
		"                    anotherBar();\n"
		"                }\n"
		"            }\n"
		"\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else anotherBar();\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"\n"
		"#if 0\n"
		"    foo();\n"
		"#else\n"
		"    if (bar)\n"
		"        fooBar();\n"
		"#endif\n"
		"}\n";
	char options[] = "break-elseifs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakElseIfs, ShortOption)
{
	// test break else/if short options
	// else/if statements should be broken
	char textIn[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else\n"
		"        if (isBar) {\n"
		"            anotherBar();\n"
		"            } else    if (isBar) {\n"
		"                anotherBar();\n"
		"            } else {\n"
		"                if (isBar) {\n"
		"                    anotherBar();\n"
		"                }\n"
		"            }\n"
		"\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else anotherBar();\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"\n"
		"#if 0\n"
		"    foo();\n"
		"#else\n"
		"    if (bar)\n"
		"        fooBar();\n"
		"#endif\n"
		"}\n";
	char text[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else\n"
		"        if (isBar) {\n"
		"            anotherBar();\n"
		"        } else\n"
		"            if (isBar) {\n"
		"                anotherBar();\n"
		"            } else {\n"
		"                if (isBar) {\n"
		"                    anotherBar();\n"
		"                }\n"
		"            }\n"
		"\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else anotherBar();\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"\n"
		"#if 0\n"
		"    foo();\n"
		"#else\n"
		"    if (bar)\n"
		"        fooBar();\n"
		"#endif\n"
		"}\n";
	char options[] = "-e";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakElseIfs, Sans)
{
	// test without break else/if
	// else/if statements should be joined
	// but do NOT join #else
	char textIn[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else\n"
		"        if (isBar) {\n"
		"            anotherBar();\n"
		"            } else    if (isBar) {\n"
		"                anotherBar();\n"
		"            } else {\n"
		"                if (isBar) {\n"
		"                    anotherBar();\n"
		"                }\n"
		"            }\n"
		"\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else anotherBar();\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"\n"
		"#if fooDef1\n"
		"    foo();\n"
		"#else\n"
		"    if (bar)\n"
		"        fooBar();\n"
		"#endif\n"
		"#   if fooDef2\n"
		"    foo();\n"
		"#   else\n"
		"    fooBar();\n"
		"#   endif\n"
		"}\n";
	char text[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else if (isBar) {\n"
		"        anotherBar();\n"
		"    } else    if (isBar) {\n"
		"        anotherBar();\n"
		"    } else {\n"
		"        if (isBar) {\n"
		"            anotherBar();\n"
		"        }\n"
		"    }\n"
		"\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    } else anotherBar();\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"\n"
		"#if fooDef1\n"
		"    foo();\n"
		"#else\n"
		"    if (bar)\n"
		"        fooBar();\n"
		"#endif\n"
		"#   if fooDef2\n"
		"    foo();\n"
		"#   else\n"
		"    fooBar();\n"
		"#   endif\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakElseIfs, KeepOneLineBlocks)
{
	// test break else/if with keep one line blocks
	// else/if statements remain the same with breaking/attaching
	char text[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    { bar(); if (isBar1) anotherBar1(); else if (isBar2) anotherBar2(); }\n"
		"    { if (isBar1) anotherBar1(); else if (isBar2) anotherBar2(); }\n"
		"}\n";
	char options[] = "break-elseifs, keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakElseIfs, KeepOneLineStatements)
{
	// test break else/if with keep one line statements
	// else/if statements remain the same with breaking/attaching
	char text[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    bar(); if (isBar1) anotherBar1(); else if (isBar2) anotherBar2();\n"
		"    if (isBar1) anotherBar1(); else if (isBar2) anotherBar2();\n"
		"}\n";
	char options[] = "break-elseifs, keep-one-line-statements";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakElseIfs, Comments1)
{
	// Test break else/if with comments preceding the 'else'.
	// The should be indented the same as the following 'else'.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        bar1();\n"
		"    // comment 2\n"
		"    else if (isFoo2)\n"
		"        bar2();\n"
		"    // comment 3\n"
		"    else if (isFoo3)\n"
		"        bar3();\n"
		"    // comment 4\n"
		"    else bar4();\n"
		"    // not else-if comment\n"
		"    endBar();\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        bar1();\n"
		"    // comment 2\n"
		"    else\n"
		"        if (isFoo2)\n"
		"            bar2();\n"
		"        // comment 3\n"
		"        else\n"
		"            if (isFoo3)\n"
		"                bar3();\n"
		"            // comment 4\n"
		"            else bar4();\n"
		"    // not else-if comment\n"
		"    endBar();\n"
		"}";
	char options[] = "break-elseifs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakElseIfs, Comments2)
{
	// Test break else/if with comments preceding the 'else'.
	// The should be indented the same as the following 'else'.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        bar1(); /* comment 1A */\n"
		"    /* comment 2 */\n"
		"    else if (isFoo2) /* comment 2A */\n"
		"    { bar2(); }\n"
		"    /*  comment 3 */\n"
		"    else if (isFoo3)\n"
		"    { bar3(); }\n"
		"    /* comment 4 */\n"
		"    else bar4();\n"
		"    /*  not else-if comment */\n"
		"    endBar();\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        bar1(); /* comment 1A */\n"
		"    /* comment 2 */\n"
		"    else\n"
		"        if (isFoo2) /* comment 2A */\n"
		"        { bar2(); }\n"
		"        /*  comment 3 */\n"
		"        else\n"
		"            if (isFoo3)\n"
		"            { bar3(); }\n"
		"            /* comment 4 */\n"
		"            else bar4();\n"
		"    /*  not else-if comment */\n"
		"    endBar();\n"
		"}";
	char options[] = "break-elseifs, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakElseIfs, Comments3)
{
	// Test break else/if with comments IFs with no ELSE.
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        // comment 2\n"
		"        if (isFoo2)\n"
		"            // comment 3\n"
		"            if (isFoo3)\n"
		"                bar3();\n"
		"    // not IF comment\n"
		"    endBar();\n"
		"}";
	char options[] = "break-elseifs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakElseIfs, Comments4)
{
	// Test break else/if with multiple-line comments preceding the 'else'.
	// The should be indented the same as the following 'else'.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        bar1();\n"
		"    else if (isFoo2)\n"
		"        bar2();\n"
		"    else if (isFoo3)\n"
		"        bar3();\n"
		"    // comment 4A\n"
		"    // comment 4B\n"
		"    // comment 4C\n"
		"    else bar4();\n"
		"    // not else-if commentA\n"
		"    // not else-if commentB\n"
		"    // not else-if commentC\n"
		"    endBar();\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        bar1();\n"
		"    else\n"
		"        if (isFoo2)\n"
		"            bar2();\n"
		"        else\n"
		"            if (isFoo3)\n"
		"                bar3();\n"
		"            // comment 4A\n"
		"            // comment 4B\n"
		"            // comment 4C\n"
		"            else bar4();\n"
		"    // not else-if commentA\n"
		"    // not else-if commentB\n"
		"    // not else-if commentC\n"
		"    endBar();\n"
		"}";
	char options[] = "break-elseifs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakElseIfs, Comments5)
{
	// Test break else/if with multiple-line comments preceding the 'else'.
	// The should be indented the same as the following 'else'.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        bar1();\n"
		"    else if (isFoo2)\n"
		"        bar2();\n"
		"    /** comment 3A\n"
		"      * comment 3B\n"
		"      * comment 3C */\n"
		"    else if (isFoo3)\n"
		"        bar3();\n"
		"    /** comment 4A\n"
		"      * comment 4B\n"
		"      * comment 4C\n"
		"      */\n"
		"    else bar4();\n"
		"    /* not else-if commentA\n"
		"     * not else-if commentB\n"
		"     * not else-if commentC\n"
		"     */\n"
		"    endBar();\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        bar1();\n"
		"    else\n"
		"        if (isFoo2)\n"
		"            bar2();\n"
		"        /** comment 3A\n"
		"          * comment 3B\n"
		"          * comment 3C */\n"
		"        else\n"
		"            if (isFoo3)\n"
		"                bar3();\n"
		"            /** comment 4A\n"
		"              * comment 4B\n"
		"              * comment 4C\n"
		"              */\n"
		"            else bar4();\n"
		"    /* not else-if commentA\n"
		"     * not else-if commentB\n"
		"     * not else-if commentC\n"
		"     */\n"
		"    endBar();\n"
		"}";
	char options[] = "break-elseifs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakElseIfs, CommentsInPreprocessor)
{
	// Test break else/if with comment in a preprocessor directive.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        bar1();\n"
		"    else if (isFoo4)\n"
		"        bar4();\n"
		"#ifdef IS_GUI\n"
		"    // Beg of options used by GUI\n"
		"    else if (isFoo4A)\n"
		"        bar4A();\n"
		"#else\n"
		"    // Options used by only console\n"
		"    else if (isFoo5)\n"
		"        bar5();\n"
		"#endif\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        bar1();\n"
		"    else\n"
		"        if (isFoo4)\n"
		"            bar4();\n"
		"#ifdef IS_GUI\n"
		"        // Beg of options used by GUI\n"
		"        else\n"
		"            if (isFoo4A)\n"
		"                bar4A();\n"
		"#else\n"
		"        // Options used by only console\n"
		"        else\n"
		"            if (isFoo5)\n"
		"                bar5();\n"
		"#endif\n"
		"}";
	char options[] = "break-elseifs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakElseIfs, AddBrackets)
{
	// Test break else/if with add-brackets.
	// The resulting closing brackets should align
	// with the 'if' instead of the 'else'.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"        bar1();\n"
		"    else if (isFoo2)\n"
		"        bar2();\n"
		"    else if (isFoo3)\n"
		"        bar3();\n"
		"    else bar4();\n"
		"    endBar();\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo1) {\n"
		"        bar1();\n"
		"    }\n"
		"    else\n"
		"        if (isFoo2) {\n"
		"            bar2();\n"
		"        }\n"
		"        else\n"
		"            if (isFoo3) {\n"
		"                bar3();\n"
		"            }\n"
		"            else {\n"
		"                bar4();\n"
		"            }\n"
		"    endBar();\n"
		"}";
	char options[] = "break-elseifs, add-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakElseIfs, EndOfFileComments1)
{
	// Test comments at the end of file.
	// Was causing an exception in call to PeekNextText().
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    endBar();\n"
		"}"
		"// end of line comment";
	char options[] = "break-elseifs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakElseIfs, EndOfFileComments2)
{
	// Test comments at the end of file.
	// Was causing an exception in call to PeekNextText().
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    endBar();\n"
		"}"
		"/* end of line comment */";
	char options[] = "break-elseifs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakElseIfs, WithSwitch)
{
	// test break else/if with a switch statement
	// should not separate the colon from the header
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    switch (Current_Led_Toggle)\n"
		"    {\n"
		"    case LED_TOGGLE_NORMAL:\n"
		"        break;\n"
		"    default:\n"
		"        break;\n"
		"    }\n"
		"}\n";
	char options[] = "break-elseifs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BreakElseIfs, WithMaxCodeLength)
{
	// test break else/if with a max code length
	// should not have an empty line between the IF and the statement
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (config.chkAnnSource)                                   param << _T(\" -A\") << config.txtAnnSource;\n"
		"    if (config.chkMinCount)                                    param << _T(\" -m\") << config.spnMinCount;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (config.chkAnnSource)\n"
		"        param << _T(\" -A\") << config.txtAnnSource;\n"
		"    if (config.chkMinCount)\n"
		"        param << _T(\" -m\") << config.spnMinCount;\n"
		"}\n";
	char options[] = "break-elseifs, max-code-length=50";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Keep One Line Statements
//-------------------------------------------------------------------------

TEST(KeepOneLineStatements, LongOption)
{
	// test keep one line statements
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        isFoo=false; isBar=true;\n"
		"    }\n"
		"}\n";
	char options[] = "keep-one-line-statements";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineStatements, ShortOption)
{
	// // test keep one line statements short option
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        isFoo=false; isBar=true;\n"
		"    }\n"
		"}\n";
	char options[] = "-o";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineStatements, WithHeader)
{
	// test keep one line statements with a header in one of the statements
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    SendEvent(0, m_editItem, &te); if (!te.IsAllowed()) return;\n"
		"    CalculatePositions();\n"
		"}";
	char options[] = "keep-one-line-statements";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineStatements, SansWithHeader1)
{
	// test without keep-one-line statements
	// one-line statements with a header in one of the statements
	// should break the statements
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    SendEvent(0, m_editItem, &te); if (!te.IsAllowed()) return;\n"
		"    CalculatePositions();\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    SendEvent(0, m_editItem, &te);\n"
		"    if (!te.IsAllowed()) return;\n"
		"    CalculatePositions();\n"
		"}";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineStatements, SansWithHeader2)
{
	// test without keep-one-line statements but with break blocks
	// one-line statements with a header in one of the statements
	// should break the statements and the header block
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    SendEvent(0, m_editItem, &te); if (!te.IsAllowed()) return;\n"
		"    CalculatePositions();\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    SendEvent(0, m_editItem, &te);\n"
		"\n"
		"    if (!te.IsAllowed()) return;\n"
		"\n"
		"    CalculatePositions();\n"
		"}";
	char options[] = "break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineStatements, BreakBlocks1)
{
	// test with break-blocks=all and a header as the SECOND statement
	// should not change the lines
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    SendEvent(0, m_editItem, &te); if (!te.IsAllowed()) return;\n"
		"    CalculatePositions();\n"
		"}";
	char options[] = "keep-one-line-statements, break-blocks=all";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineStatements, BreakBlocks2)
{
	// Test with break-blocks=all and a header as the FIRST statement.
	// Should keep the one-line statements and break the block.
	// Adding keep-one-line-blocks would not break the block.
	// See the following test.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (!te.IsAllowed()) return; SendEvent(0, m_editItem, &te);\n"
		"    CalculatePositions();\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (!te.IsAllowed()) return; SendEvent(0, m_editItem, &te);\n"
		"\n"
		"    CalculatePositions();\n"
		"}";
	char options[] = "keep-one-line-statements, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineStatements, BreakBlocks3)
{
	// Test with break-blocks and keep-one-line-statements.
	// Should not break the Block.
	// Without keep-one-line-statements it will break the block.
	// See the previous test.
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if ( getter ) mv.Get = _T ( \"Get\" ) + method;\n"
		"    else mv.Get = wxEmptyString;\n"
		"}";
	char options[] = "keep-one-line-statements, break-blocks, keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineStatements, BreakBlocksMaxCodeLength1)
{
	// test with break-blocks=all and max code length
	// should break the IF statement and break the block
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    SendEvent(0, m_editItem, &te); if (!te.IsAllowed()) return;\n"
		"    CalculatePositions();\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    SendEvent(0, m_editItem, &te);\n"
		"\n"
		"    if (!te.IsAllowed()) return;\n"
		"\n"
		"    CalculatePositions();\n"
		"}";
	char options[] = "keep-one-line-statements, break-blocks=all, max-code-length=60";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineStatements, BreakBlocksMaxCodeLength2)
{
	// test with break-blocks=all and without max code length
	// should NOT break the one line statement
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    SendEvent(0, m_editItem, &te); if (!te.IsAllowed()) return;\n"
		"    CalculatePositions();\n"
		"}";
	char options[] = "keep-one-line-statements, break-blocks=all";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Keep One Line Blocks
//-------------------------------------------------------------------------

TEST(KeepOneLineBlocks, LongOption)
{
	// test keep one line blocks
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (!j) { j=1; i=i-10; }\n"
		"}\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, ShortOption)
{
	// test keep one line blocks short option
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (!j) { j=1; i=i-10; }\n"
		"}\n";
	char options[] = "-O";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, StartOfLine)
{
	// line beginning with one-line blocks do NOT get a extra indent
	char text[] =
		"\nclass Foo\n"
		"{\n"
		"public:\n"
		"    int getFoo() const\n"
		"    { return isFoo; }\n"
		"};\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, NoneBrackets)
{
	// test keep one line blocks
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (comment&&code) { ++codecomments_lines; }\n"
		"    else if (comment) { ++comment_lines; }\n"
		"    else if (code) { ++code_lines; }\n"
		"}\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, BreakBrackets)
{
	// test keep one line blocks
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (comment&&code) { ++codecomments_lines; }\n"
		"    else if (comment) { ++comment_lines; }\n"
		"    else if (code) { ++code_lines; }\n"
		"}\n";
	char options[] = "keep-one-line-blocks, brackets=break";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, AttachBrackets)
{
	// test keep one line blocks
	char text[] =
		"\nvoid foo() {\n"
		"    if (comment&&code) { ++codecomments_lines; }\n"
		"    else if (comment) { ++comment_lines; }\n"
		"    else if (code) { ++code_lines; }\n"
		"}\n";
	char options[] = "keep-one-line-blocks, brackets=attach";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, LinuxBrackets)
{
	// test keep one line blocks
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (comment&&code) { ++codecomments_lines; }\n"
		"    else if (comment) { ++comment_lines; }\n"
		"    else if (code) { ++code_lines; }\n"
		"}\n";
	char options[] = "keep-one-line-blocks, brackets=linux";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, RunInBrackets)
{
	// test keep one line blocks
	char text[] =
		"\nvoid foo()\n"
		"{   if (comment&&code) { ++codecomments_lines; }\n"
		"    else if (comment) { ++comment_lines; }\n"
		"    else if (code) { ++code_lines; }\n"
		"}\n";
	char options[] = "keep-one-line-blocks, brackets=run-in";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, BreakElseIf)
{
	// test keep one line blocks and break elseifs
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (!j) { j=1; if (i) i=i-10; }\n"
		"    if (!j) { j=1; if (i) i=i-10; else i=i-20; }\n"
		"    if (!j) { j=1; if (i) i=i-10; else if (j) j=j-10; }\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (!j) { j=1; if (i) i=i-10; }\n"
		"    if (!j) { j=1; if (i) i=i-10; else i=i-20; }\n"
		"    if (!j) { j=1; if (i) i=i-10; else if (j) j=j-10; }\n"
		"}\n";
	char options[] = "keep-one-line-blocks, break-elseifs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, KeepOneLineStatementsAndBreakElseIf)
{
	// test keep one line blocks and keep one line statements
	//     with if statement and break elseifs
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (!j) { j=1; if (i) i=i-10; }\n"
		"    if (!j) { j=1; if (i) i=i-10; else i=i-20; }\n"
		"    if (!j) { j=1; if (i) i=i-10; else if (j) j=j-10; }\n"
		"}\n";
	char options[] = "keep-one-line-blocks, keep-one-line-statements, break-elseifs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, BreakBlocks1)
{
	// test keep one line blocks and break blocks
	// should NOT break the block
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    { SendEvent(0, m_editItem, &te); if (!te.IsAllowed()) return; }\n"
		"    CalculatePositions();\n"
		"}";
	char options[] = "keep-one-line-blocks, break-blocks=all";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, BreakBlocks2)
{
	// test keep one line blocks and break blocks
	// should NOT break the block
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    { if (!te.IsAllowed()) return; SendEvent(0, m_editItem, &te); }\n"
		"    CalculatePositions();\n"
		"}";
	char options[] = "keep-one-line-blocks, break-blocks=all";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, BreakBlocks3)
{
	// test keep one line blocks and break blocks
	// should NOT break the one-line block
	// should break the other IF block
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"    { if (!te.IsAllowed()) return; SendEvent(0, m_editItem, &te); }\n"
		"    CalculatePositions();\n"
		"}";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"    { if (!te.IsAllowed()) return; SendEvent(0, m_editItem, &te); }\n"
		"\n"
		"    CalculatePositions();\n"
		"}";
	char options[] = "keep-one-line-blocks, break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, MultipleBrackets)
{
	// test keep one line blocks with multiple brackets
	char text[] =
		"\npublic class FooClass\n"
		"{\n"
		"    public string FooName { get { return Foo; } set { Foo = value; } }\n"
		"\n"
		"    public event EventHandler Cancelled { add { } remove { } }\n"
		"}\n";
	char options[] = "keep-one-line-blocks, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, Sans1)
{
	// test without keep one line blocks
	// should not break {} when break brackets
	char text[] =
		"\nclass JipeConsole\n"
		"{\n"
		"    public JipeConsole(Jipe parent)\n"
		"    {\n"
		"        jipeConsole.addKeyListener(new KeyListener()\n"
		"        {\n"
		"            public void keyReleased(KeyEvent e) {}\n"
		"            public void keyTyped(KeyEvent e) {}\n"
		"        });\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=break, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, Sans2)
{
	// test without keep one line blocks
	// test attach bracket inside comment on single line block
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())     // comment\n"
		"        { return false; }\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo()) {   // comment\n"
		"        return false;\n"
		"    }\n"
		"}\n";
	char options[] = "brackets=linux";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, SansMultipleBrackets)
{
	// test without keep one line blocks with multiple brackets
	char textIn[] =
		"\npublic class FooClass\n"
		"{\n"
		"    public string FooName { get { return Foo; } set { Foo = value; } }\n"
		"\n"
		"    public event EventHandler Cancelled { add { } remove { } }\n"
		"}\n";
	char text[] =
		"\npublic class FooClass\n"
		"{\n"
		"    public string FooName {\n"
		"        get {\n"
		"            return Foo;\n"
		"        }\n"
		"        set {\n"
		"            Foo = value;\n"
		"        }\n"
		"    }\n"
		"\n"
		"    public event EventHandler Cancelled {\n"
		"        add { } remove { }\n"
		"    }\n"
		"}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, NoneRunIn)
{
	// test none brackets with keep one line blocks and run-in
	// should not indent the run-in
	char text[] =
		"\nvoid foo()\n"
		"{   if (isFoo)\n"
		"    {/*ok*/;}\n"
		"    else {bar();}\n"
		"}\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, RunInRunIn)
{
	// test run-in brackets with keep one line blocks and run-in
	// should not indent the run-in
	char text[] =
		"\nvoid foo()\n"
		"{   if (isFoo)\n"
		"    {/*ok*/;}\n"
		"    else {bar();}\n"
		"}\n";
	char options[] = "keep-one-line-blocks, brackets=run-in";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, NoneClosingHeader)
{
	// test keep one line blocks followed by a closing header
	// should not attach header to the one line statement
	char text[] =
		"\nvoid foo() {\n"
		"    if (isFoo)\n"
		"    {/*ok*/;}\n"
		"    else {bar();}\n"
		"}\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, BreakClosingHeader)
{
	// test keep one line blocks followed by a closing header
	// should not attach header to the one line statement
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"    {/*ok*/;}\n"
		"    else {bar();}\n"
		"}\n";
	char options[] = "keep-one-line-blocks, brackets=break";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, AttachClosingHeader)
{
	// test keep one line blocks followed by a closing header
	// should not attach header to the one line statement
	char text[] =
		"\nvoid foo() {\n"
		"    if (isFoo)\n"
		"    {/*ok*/;}\n"
		"    else {bar();}\n"
		"}\n";
	char options[] = "keep-one-line-blocks, brackets=attach";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, LinuxClosingHeader)
{
	// test keep one line blocks followed by a closing header
	// should not attach header to the one line statement
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"    {/*ok*/;}\n"
		"    else {bar();}\n"
		"}\n";
	char options[] = "keep-one-line-blocks, brackets=linux";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, IndentSwitchBlock)
{
	// test one-line blocks with switch blocks
	char text[] =
		"\nvoid Foo(int fooBar)\n"
		"{\n"
		"    switch (fooBar)\n"
		"    {\n"
		"    case 1:\n"
		"        fooBar = 1;\n"
		"        break;\n"
		"    case 2:\n"
		"    { fooBar = 2; }\n"
		"    break;\n"
		"    default:\n"
		"    { break; }\n"
		"    }\n"
		"    int bar = true;\n"
		"}\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, IndentSwitchBlock_IndentSwitches)
{
	// test one-line blocks with indented switch blocks
	char text[] =
		"\nvoid Foo(int fooBar)\n"
		"{\n"
		"    switch (fooBar)\n"
		"    {\n"
		"        case 1:\n"
		"            fooBar = 1;\n"
		"            break;\n"
		"        case 2:\n"
		"        { fooBar = 2; }\n"
		"        break;\n"
		"        default:\n"
		"        { break; }\n"
		"    }\n"
		"    int bar = true;\n"
		"}\n";
	char options[] = "keep-one-line-blocks, indent-switches";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, IndentAfterHeader)
{
	// test one line blocks indentation following a header
	char text[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo)\n"
		"    { bar(); }\n"
		"    else\n"
		"    { anotherBar(); }\n"
		"}\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, IndentAfterHeaderSansBrackets)
{
	// Test one line blocks indentation following a header
	// when the header does not contain brackets.
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"    if (isBar1)\n"
		"        if (isBar2)\n"
		"        { return true; }\n"
		"\n"
		"    if (isBar1)\n"
		"        if (isBar2) { return true; }\n"
		"}\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, IndentSansHeader)
{
	// test one line blocks indentation withouta header
	char text[] =
		"\nvoid foo(bool isFoo)\n"
		"{\n"
		"    bar()\n"
		"    { anotherBar(); }\n"
		"}\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, IndentWithConstMethod)
{
	// Test one line blocks indentation following a header
	// when the header does not contain brackets.
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"    virtual bool foo() const\n"
		"    { return false; }\n"
		"};\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, WithAccessModifier)
{
	// A one line block with an access modifier should not break after the modifier.
	char text[] =
		"\ntemplate<typename T>\n"
		"struct RunHelper<T> { public: int Run(TestCases<T>&) { return 0; } };";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(KeepOneLineBlocks, WithAccessModifierSans)
{
	// A one line block with an access modifier should break if keep is NOT used.
	char textIn[] =
		"\ntemplate<typename T>\n"
		"struct RunHelper<T> { public: int Run(TestCases<T>&) { return 0; } };";
	char text[] =
		"\ntemplate<typename T>\n"
		"struct RunHelper<T> {\n"
		"public:\n"
		"    int Run(TestCases<T>&) {\n"
		"        return 0;\n"
		"    }\n"
		"};";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Add Brackets
//-------------------------------------------------------------------------

TEST(AddBrackets, LongOption)
{
	// test add brackets
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo()) {\n"
		"        return false;\n"
		"    }\n"
		"}\n";
	char options[] = "add-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, ShortOption)
{
	// test add brackets short option
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo()) {\n"
		"        return false;\n"
		"    }\n"
		"}\n";
	char options[] = "-j";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, All)
{
	// test add brackets for all headers
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"    else\n"
		"        return true;\n"
		"\n"
		"    for (int i = 0; i <= 12; ++i)\n"
		"        bar &= ::FooBar();\n"
		"\n"
		"    while (isFoo)\n"
		"        bar();\n"
		"\n"
		"    do\n"
		"        bar();\n"
		"    while (isFoo);\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo()) {\n"
		"        return false;\n"
		"    }\n"
		"\n"
		"    if (isFoo()) {\n"
		"        return false;\n"
		"    }\n"
		"    else {\n"
		"        return true;\n"
		"    }\n"
		"\n"
		"    for (int i = 0; i <= 12; ++i) {\n"
		"        bar &= ::FooBar();\n"
		"    }\n"
		"\n"
		"    while (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"\n"
		"    do {\n"
		"        bar();\n"
		"    }\n"
		"    while (isFoo);\n"
		"}\n";
	char options[] = "add-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, ElseIf)
{
	// test add brackets for "else if" statements
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"    else if (isFoo())\n"
		"        return false;\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo()) {\n"
		"        return false;\n"
		"    }\n"
		"    else if (isFoo()) {\n"
		"        return false;\n"
		"    }\n"
		"}\n";
	char options[] = "add-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, SemiFollows)
{
	// test add brackets when a semi-colon follows the statement
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (a == 0) ; func1(); i++;\n"
		"    while (isFoo)  // comment\n"
		"            ;\n"
		"    while (isFoo); // comment\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (a == 0) ;\n"
		"    func1();\n"
		"    i++;\n"
		"    while (isFoo)  // comment\n"
		"        ;\n"
		"    while (isFoo); // comment\n"
		"}\n";
	char options[] = "add-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, Sharp)
{
	// test add brackets to C# headers
	// 'delegate' statement contans brackets
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    foreach (int i in fibarray)\n"
		"        System.Console.WriteLine(i);\n"
		"\n"
		"    if (isFoo)\n"
		"        bar(delegate { fooBar* = null; });\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    foreach (int i in fibarray) {\n"
		"        System.Console.WriteLine(i);\n"
		"    }\n"
		"\n"
		"    if (isFoo)\n"
		"        bar(delegate {\n"
		"        fooBar* = null;\n"
		"    });\n"
		"}\n";
	char options[] = "add-brackets, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, KeepOneLiners)
{
	// add brackets with keep one liners
	// should break the added brackets
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"    else\n"
		"        return true;\n"
		"\n"
		"    for (int i = 0; i <= 12; ++i)\n"
		"        bar &= ::FooBar();\n"
		"\n"
		"    while (isFoo)\n"
		"        bar();\n"
		"\n"
		"    do\n"
		"        bar();\n"
		"        while (isFoo);\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo()) {\n"
		"        return false;\n"
		"    }\n"
		"\n"
		"    if (isFoo()) {\n"
		"        return false;\n"
		"    }\n"
		"    else {\n"
		"        return true;\n"
		"    }\n"
		"\n"
		"    for (int i = 0; i <= 12; ++i) {\n"
		"        bar &= ::FooBar();\n"
		"    }\n"
		"\n"
		"    while (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"\n"
		"    do {\n"
		"        bar();\n"
		"    }\n"
		"    while (isFoo);\n"
		"}\n";
	char options[] = "add-brackets, keep-one-line-blocks, keep-one-line-statements";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, SingleLine)
{
	// add brackets to one line statements
	// should break the statements
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo()) return false;\n"
		"\n"
		"    if (isFoo()) return false; else return true;\n"
		"\n"
		"    for (int i = 0; i <= 12; ++i) bar &= ::FooBar();\n"
		"\n"
		"    while (isFoo) bar();\n"
		"\n"
		"    do bar(); while (isFoo);\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo()) {\n"
		"        return false;\n"
		"    }\n"
		"\n"
		"    if (isFoo()) {\n"
		"        return false;\n"
		"    }\n"
		"    else {\n"
		"        return true;\n"
		"    }\n"
		"\n"
		"    for (int i = 0; i <= 12; ++i) {\n"
		"        bar &= ::FooBar();\n"
		"    }\n"
		"\n"
		"    while (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"\n"
		"    do {\n"
		"        bar();\n"
		"    }\n"
		"    while (isFoo);\n"
		"}\n";
	char options[] = "add-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, SingleLineKeepOneLiners)
{
	// add brackets to one line statements with keep one liners
	// should keep one line blocks with added brackets
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo()) return false;\n"
		"\n"
		"    if (isFoo()) return false; else return true;\n"
		"\n"
		"    for (int i = 0; i <= 12; ++i) bar &= ::FooBar();\n"
		"\n"
		"    while (isFoo) bar();\n"
		"\n"
		"    do bar(); while (isFoo);\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo()) { return false; }\n"
		"\n"
		"    if (isFoo()) { return false; } else { return true; }\n"
		"\n"
		"    for (int i = 0; i <= 12; ++i) { bar &= ::FooBar(); }\n"
		"\n"
		"    while (isFoo) { bar(); }\n"
		"\n"
		"    do { bar(); } while (isFoo);\n"
		"}\n";
	char options[] = "add-brackets, keep-one-line-blocks, keep-one-line-statements";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, Break)
{
	// test add brackets for broken brackets
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"    else\n"
		"        return true;\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"    {\n"
		"        return false;\n"
		"    }\n"
		"    else\n"
		"    {\n"
		"        return true;\n"
		"    }\n"
		"}\n";
	char options[] = "add-brackets, brackets=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, Attach)
{
	// test add brackets for attached brackets
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"    else\n"
		"        return true;\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo()) {\n"
		"        return false;\n"
		"    } else {\n"
		"        return true;\n"
		"    }\n"
		"}\n";
	char options[] = "add-brackets, brackets=linux";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, RunIn)
{
	// test add brackets for run-in brakets
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"    else\n"
		"        return true;\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{   if (isFoo())\n"
		"    {   return false;\n"
		"    }\n"
		"    else\n"
		"    {   return true;\n"
		"    }\n"
		"}\n";
	char options[] = "add-brackets, brackets=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, ExtraSpaces)
{
	// extra spaces should be removed
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if ( str )   (*str) += \"<?xml \";\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if ( str ) {\n"
		"        (*str) += \"<?xml \";\n"
		"    }\n"
		"}\n";
	char options[] = "add-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, ElseParen)
{
	// else statement with following paren
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo) break;\n"
		"    else (numBar)--;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo) {\n"
		"        break;\n"
		"    }\n"
		"    else {\n"
		"        (numBar)--;\n"
		"    }\n"
		"}\n";
	char options[] = "add-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, Quote)
{
	// must bypass quote with semi-colons and escaped quote marks
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo) bar = '\\'';\n"
		"    if (isFoo) bar = '\\\\';\n"
		"    if (isBar) bar = \";;version=\";\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo) {\n"
		"        bar = '\\'';\n"
		"    }\n"
		"    if (isFoo) {\n"
		"        bar = '\\\\';\n"
		"    }\n"
		"    if (isBar) {\n"
		"        bar = \";;version=\";\n"
		"    }\n"
		"}\n";
	char options[] = "add-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, QuoteSans)
{
	// must bypass multi-line quote
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"        char* bar = \"one \\\n"
		"  two \\\n"
		"      three\";\n"
		"}\n";
	char options[] = "add-brackets";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, Comment)
{
	// must bypass comment before a semi-colon
	// the last statement should be bracketed
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo) bar = // comment\n"
		"            foo2;\n"
		"    if (isFoo) bar =  /* comment */\n"
		"            foo2;\n"
		"    if (isFoo) bar = /* comment\n"
		"                        comment */\n"
		"            foo2;\n"
		"    if (isFoo) bar = /* comment */ foo2;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo) bar = // comment\n"
		"            foo2;\n"
		"    if (isFoo) bar =  /* comment */\n"
		"            foo2;\n"
		"    if (isFoo) bar = /* comment\n"
		"                        comment */\n"
		"            foo2;\n"
		"    if (isFoo) {\n"
		"        bar = /* comment */ foo2;\n"
		"    }\n"
		"}\n";
	char options[] = "add-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddBrackets, Sans)
{
	// brackets should be added to specified headers only
	char text[] =
		"\npublic unsafe int foo()\n"
		"{\n"
		"    int readCount;\n"
		"    fixed(byte* pBuffer = buffer)\n"
		"        readCount = ReadMemory(size);\n"
		"}\n";
	char options[] = "add-brackets, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Add One Line Brackets
// Implies keep-one-line-blocks
//-------------------------------------------------------------------------

TEST(AddOneLineBrackets, LongOption)
{
	// test add one line brackets
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"    { return false; }\n"
		"}\n";
	char options[] = "add-one-line-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, ShortOption)
{
	// test add one line brackets short option
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"    { return false; }\n"
		"}\n";
	char options[] = "-J";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, All)
{
	// test add one line brackets for all headers
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"    else\n"
		"        return true;\n"
		"\n"
		"    for (int i = 0; i <= 12; ++i)\n"
		"        bar &= ::FooBar();\n"
		"\n"
		"    while (isFoo)\n"
		"        bar();\n"
		"\n"
		"    do\n"
		"        bar();\n"
		"    while (isFoo);\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"    { return false; }\n"
		"\n"
		"    if (isFoo())\n"
		"    { return false; }\n"
		"    else\n"
		"    { return true; }\n"
		"\n"
		"    for (int i = 0; i <= 12; ++i)\n"
		"    { bar &= ::FooBar(); }\n"
		"\n"
		"    while (isFoo)\n"
		"    { bar(); }\n"
		"\n"
		"    do\n"
		"    { bar(); }\n"
		"    while (isFoo);\n"
		"}\n";
	char options[] = "add-one-line-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, ElseIf)
{
	// test add one line brackets for "else if" statements
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"    else if (isFoo())\n"
		"        return false;\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"    { return false; }\n"
		"    else if (isFoo())\n"
		"    { return false; }\n"
		"}\n";
	char options[] = "add-one-line-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, SemiFollows)
{
	// test add brackets when a semi-colon follows the statement
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (a == 0) ; func1(); i++;\n"
		"    while (isFoo)  // comment\n"
		"            ;\n"
		"    while (isFoo); // comment\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (a == 0) ;\n"
		"    func1();\n"
		"    i++;\n"
		"    while (isFoo)  // comment\n"
		"        ;\n"
		"    while (isFoo); // comment\n"
		"}\n";
	char options[] = "add-one-line-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, Sharp)
{
	// test add one line brackets to C# headers
	// 'delegate' statement contans brackets
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    foreach (int i in fibarray)\n"
		"        System.Console.WriteLine(i);\n"
		"\n"
		"    if (isFoo)\n"
		"        bar(delegate { fooBar* = null; });\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    foreach (int i in fibarray)\n"
		"    { System.Console.WriteLine(i); }\n"
		"\n"
		"    if (isFoo)\n"
		"        bar(delegate { fooBar* = null; });\n"
		"}\n";
	char options[] = "add-one-line-brackets, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, SingleLine)
{
	// add one line brackets to one line statements
	// should keep the one line statements
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo()) return false;\n"
		"\n"
		"    if (isFoo()) return false; else return true;\n"
		"\n"
		"    for (int i = 0; i <= 12; ++i) bar &= ::FooBar();\n"
		"\n"
		"    while (isFoo) bar();\n"
		"\n"
		"    do bar(); while (isFoo);\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo()) { return false; }\n"
		"\n"
		"    if (isFoo()) { return false; }\n"
		"    else { return true; }\n"
		"\n"
		"    for (int i = 0; i <= 12; ++i) { bar &= ::FooBar(); }\n"
		"\n"
		"    while (isFoo) { bar(); }\n"
		"\n"
		"    do { bar(); }\n"
		"    while (isFoo);\n"
		"}\n";
	char options[] = "add-one-line-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, SingleLineKeepOneLiners)
{
	// add one line brackets to one line statements with keep one liners
	// should keep the one liners (keep blocks is implied)
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo()) return false;\n"
		"\n"
		"    if (isFoo()) return false; else return true;\n"
		"\n"
		"    for (int i = 0; i <= 12; ++i) bar &= ::FooBar();\n"
		"\n"
		"    while (isFoo) bar();\n"
		"\n"
		"    do bar(); while (isFoo);\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo()) { return false; }\n"
		"\n"
		"    if (isFoo()) { return false; } else { return true; }\n"
		"\n"
		"    for (int i = 0; i <= 12; ++i) { bar &= ::FooBar(); }\n"
		"\n"
		"    while (isFoo) { bar(); }\n"
		"\n"
		"    do { bar(); } while (isFoo);\n"
		"}\n";
	char options[] = "add-one-line-brackets, keep-one-line-statements";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, Break)
{
	// test add one line brackets for broken brackets
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"    else\n"
		"        return true;\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"    { return false; }\n"
		"    else\n"
		"    { return true; }\n"
		"}\n";
	char options[] = "add-one-line-brackets, brackets=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, Attach)
{
	// test add one line brackets for attached brackets
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"    else\n"
		"        return true;\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"    { return false; }\n"
		"    else\n"
		"    { return true; }\n"
		"}\n";
	char options[] = "add-one-line-brackets, brackets=linux";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, RunIn)
{
	// test add one line brackets for run-in brakets
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo())\n"
		"        return false;\n"
		"    else\n"
		"        return true;\n"
		"}\n";
	char text[] =
		"\nvoid Foo()\n"
		"{   if (isFoo())\n"
		"    { return false; }\n"
		"    else\n"
		"    { return true; }\n"
		"}\n";
	char options[] = "add-one-line-brackets, brackets=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, ExtraSpaces)
{
	// extra spaces should not be removed
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if ( str )   (*str) += \"<?xml \";\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if ( str )   { (*str) += \"<?xml \"; }\n"
		"}\n";
	char options[] = "add-one-line-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, ElseParen)
{
	// else statement with following paren
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo) break;\n"
		"    else (numBar)--;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo) { break; }\n"
		"    else { (numBar)--; }\n"
		"}\n";
	char options[] = "add-one-line-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, Quote)
{
	// must bypass quote with semi-colons and escaped quote marks
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo) bar = '\\'';\n"
		"    if (isFoo) bar = '\\\\';\n"
		"    if (isBar) bar = \";;version=\";\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo) { bar = '\\''; }\n"
		"    if (isFoo) { bar = '\\\\'; }\n"
		"    if (isBar) { bar = \";;version=\"; }\n"
		"}\n";
	char options[] = "add-one-line-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, QuoteSans)
{
	// must bypass multi-line quote
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo)\n"
		"        char* bar = \"one \\\n"
		"  two \\\n"
		"      three\";\n"
		"}\n";
	char options[] = "add-one-line-brackets";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, Comment)
{
	// must bypass comment before a semi-colon
	// the last statement should be bracketed
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo) bar = // comment\n"
		"            foo2;\n"
		"    if (isFoo) bar =  /* comment */\n"
		"            foo2;\n"
		"    if (isFoo) bar = /* comment\n"
		"                        comment */\n"
		"            foo2;\n"
		"    if (isFoo) bar = /* comment */ foo2;\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    if (isFoo) bar = // comment\n"
		"            foo2;\n"
		"    if (isFoo) bar =  /* comment */\n"
		"            foo2;\n"
		"    if (isFoo) bar = /* comment\n"
		"                        comment */\n"
		"            foo2;\n"
		"    if (isFoo) { bar = /* comment */ foo2; }\n"
		"}\n";
	char options[] = "add-one-line-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AddOneLineBrackets, Sans)
{
	// brackets should be added to specified headers only
	char text[] =
		"\npublic unsafe int foo()\n"
		"{\n"
		"    int readCount;\n"
		"    fixed(byte* pBuffer = buffer)\n"
		"        readCount = ReadMemory(size);\n"
		"}\n";
	char options[] = "add-one-line-brackets, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Remove Brackets
//-------------------------------------------------------------------------

TEST(RemoveBrackets, LongOption)
{
	// test remove brackets
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"    else if (isFoo3) {\n"
		"        bar3();\n"
		"    }\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"        bar2();\n"
		"    else if (isFoo3)\n"
		"        bar3();\n"
		"}";
	char options[] = "remove-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, ShortOption)
{
	// test remove brackets
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"    else if (isFoo3) {\n"
		"        bar3();\n"
		"    }\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"        bar2();\n"
		"    else if (isFoo3)\n"
		"        bar3();\n"
		"}";
	char options[] = "-xj";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, WithEmptyLine1)
{
	// test with a preceeding empty line
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"    {\n"
		"\n"
		"        bar2();\n"
		"    }\n"
		"    else if (isFoo3) {\n"
		"    \n"
		"        bar3();\n"
		"    }\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"\n"
		"        bar2();\n"
		"    else if (isFoo3)\n"
		"\n"
		"        bar3();\n"
		"}";
	char options[] = "remove-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, WithEmptyLine2)
{
	// test with a following empty line
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        bar2();\n"
		"\n"
		"    }\n"
		"    else if (isFoo3) {\n"
		"        bar3();\n"
		"    \n"
		"    }\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"        bar2();\n"
		"\n"
		"    else if (isFoo3)\n"
		"        bar3();\n"
		"\n"
		"}";
	char options[] = "remove-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, Sans)
{
	// don't remove if not a single statement
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        bar2();\n"
		"        bar2a();\n"
		"    }\n"
		"    else if (isFoo3) {\n"
		"        bar3();\n"
		"        bar3a();\n"
		"    }\n"
		"}";
	char options[] = "remove-brackets";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, OneLineBlock1)
{
	// test with a one line block and keep-one-line-blocks
	// should NOT break the one-line block
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"    { bar2(); }\n"
		"    else if (isFoo3) { bar3(); }\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"        bar2();\n"
		"    else if (isFoo3)  bar3();\n"
		"}";
	char options[] = "remove-brackets, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, OneLineBlockSans1)
{
	// test with a one line block and NOT keep-one-line-blocks
	// should break the one-line block
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"    { bar2(); }\n"
		"    else if (isFoo3) { bar3(); }\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"        bar2();\n"
		"    else if (isFoo3)\n"
		"        bar3();\n"
		"}";
	char options[] = "remove-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, OneLineBlockSans2)
{
	// test with a one line block to NOT remove brackets
	// with keep-one-line-blocks
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"    { bar2();  bar4(); }\n"
		"    else if (isFoo3) { bar3(); bar4(); }\n"
		"}";
	char options[] = "remove-brackets, keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, OneLineBlockSans3)
{
	// test with a one line block to NOT remove brackets
	// without keep-one-line-blocks
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"    { bar2();  bar4(); }\n"
		"    else if (isFoo3) { bar3(); bar4(); }\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        bar2();\n"
		"        bar4();\n"
		"    }\n"
		"    else if (isFoo3) {\n"
		"        bar3();\n"
		"        bar4();\n"
		"    }\n"
		"}";
	char options[] = "remove-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, BreakBlocks1)
{
	// test remove brackets with break blocks
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    bar5();\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"    else if (isFoo3) {\n"
		"        bar3();\n"
		"    }\n"
		"    bar6();\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    bar5();\n"
		"\n"
		"    if (isFoo2)\n"
		"        bar2();\n"
		"    else if (isFoo3)\n"
		"        bar3();\n"
		"\n"
		"    bar6();\n"
		"}";
	char options[] = "remove-brackets, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, BreakBlocks2)
{
	// test remove brackets with break all blocks
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    bar5();\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"    else if (isFoo3) {\n"
		"        bar3();\n"
		"    }\n"
		"    bar6();\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    bar5();\n"
		"\n"
		"    if (isFoo2)\n"
		"        bar2();\n"
		"\n"
		"    else if (isFoo3)\n"
		"        bar3();\n"
		"\n"
		"    bar6();\n"
		"}";
	char options[] = "remove-brackets, break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, CommentSans1)
{
	// don't remove if a preceeding comment
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    // comment"
		"    if (isFoo2)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"    else if (isFoo3) {\n"
		"        /* comment\n"
		"           comment */\n"
		"        bar3();\n"
		"    }\n"
		"}";
	char options[] = "remove-brackets";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, CommentSans2)
{
	// don't remove if a preceeding column 1 comment
	char text[] =
		"\nvoid Foo() {\n"
		"    if(result)\n"
		"    {\n"
		"//        Manager::Get()->GetLogManager();\n"
		"    }\n"
		"    else\n"
		"    {\n"
		"//        Manager::Get()->GetLogManager();\n"
		"    }\n"
		"}";
	char options[] = "remove-brackets";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, FollowingHeaderSans)
{
	// don't remove if a following header
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"    {\n"
		"        if (isFoo2)\n"
		"        {\n"
		"            bar2();\n"
		"        }\n"
		"        else if (isFoo3) {\n"
		"            bar3();\n"
		"        }\n"
		"    }\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo1)\n"
		"    {\n"
		"        if (isFoo2)\n"
		"            bar2();\n"
		"        else if (isFoo3)\n"
		"            bar3();\n"
		"    }\n"
		"}";
	char options[] = "remove-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, AddBracketsSans)
{
	// should NOT remove brackets if add brackets is also requested
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"    else if (isFoo3) {\n"
		"        bar3();\n"
		"    }\n"
		"}";
	char options[] = "remove-brackets, add-brackets";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, AddOneLineBracketsSans)
{
	// should NOT remove brackets if add one line brackets is also requested
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"    else if (isFoo3) {\n"
		"        bar3();\n"
		"    }\n"
		"}";
	char options[] = "remove-brackets, add-one-line-brackets";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, OtherHeaders)
{
	// test remove brackets with other headers
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    for (i = 0; i < 10; i++)\n"
		"    {\n"
		"        bar2();\n"
		"    }\n"
		"    while (i > 0 && i < 10)\n"
		"    {\n"
		"        bar3();\n"
		"    }\n"
		"    do {\n"				// NOT removed from do-while
		"        bar4();\n"
		"    } while (int x < 9);\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    for (i = 0; i < 10; i++)\n"
		"        bar2();\n"
		"    while (i > 0 && i < 10)\n"
		"        bar3();\n"
		"    do {\n"				// NOT removed from do-while
		"        bar4();\n"
		"    } while (int x < 9);\n"
		"}";
	char options[] = "remove-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, SharpOtherHeaders)
{
	// test remove brackets with other C# headers
	char textIn[] =
		"\nprivate void Foo()\n"
		"{\n"
		"    foreach (T x in list)\n"
		"    {\n"
		"        foo = bar;\n"
		"    }\n"
		"}";
	char text[] =
		"\nprivate void Foo()\n"
		"{\n"
		"    foreach (T x in list)\n"
		"        foo = bar;\n"
		"}";
	char options[] = "remove-brackets, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, OTBSSans)
{
	// should NOT remove brackets if "One True Brace Style" is requested
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2) {\n"
		"        bar2();\n"
		"    } else if (isFoo3) {\n"
		"        bar3();\n"
		"    }\n"
		"}";
	char options[] = "remove-brackets, style=otbs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, BreakClosingBrackets)
{
	// test remove brackets with break closing brackets
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        bar2();\n"
		"    } else if (isFoo3) {\n"
		"        bar3();\n"
		"    }\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"        bar2();\n"
		"    else if (isFoo3)\n"
		"        bar3();\n"
		"}";
	char options[] = "remove-brackets, break-closing-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, UnbrokenElse)
{
	// test remove brackets with a unbroken "else if" statement
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"    {\n"
		"        bar2();\n"
		"    } else if (isFoo3) {\n"
		"        bar3();\n"
		"    }\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    if (isFoo2)\n"
		"        bar2();\n"
		"    else if (isFoo3)\n"
		"        bar3();\n"
		"}";
	char options[] = "remove-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, Preprocessor)
{
	// test remove brackets with a preprocessor directive
	// the brackets should NOT be removed
	char text[] =
		"\nvoid Foo() {\n"
		"#define if(_RET_SUCCEED(exp)) { result = (exp); }\n"
		"}";
	char options[] = "remove-brackets";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, BracketInQuote)
{
	// test remove brackets within a quote
	// should not remove the bracket in the quotes
	char textIn[] =
		"\nprivate void Foo() {\n"
		"    if (closingBrackets > 0) {\n"
		"        wrapper.Append(new string('}', closingBrackets));\n"
		"    }\n"
		"}";
	char text[] =
		"\nprivate void Foo() {\n"
		"    if (closingBrackets > 0)\n"
		"        wrapper.Append(new string('}', closingBrackets));\n"
		"}";
	char options[] = "remove-brackets, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, BracketInComment1)
{
	// test remove with brackets within a line comment
	// should not remove the brackets
	char text[] =
		"\nprivate void Foo() {\n"
		"    if (closingBrackets > 0) {\n"
		"        wrapper.Append(closingBrackets); // }\n"
		"    }\n"
		"}";
	char options[] = "remove-brackets, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(RemoveBrackets, BracketInComment2)
{
	// test remove with brackets within a comment
	// should not remove the brackets
	char text[] =
		"\nprivate void Foo() {\n"
		"    if (closingBrackets > 0) {\n"
		"        wrapper.Append(closingBrackets); /* } */\n"
		"    }\n"
		"}";
	char options[] = "remove-brackets, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Convert Tabs
//-------------------------------------------------------------------------

TEST(ConvertTabs, LongOption)
{
	// test convert tabs
	char textIn[] =
		"\nstatic FooBar foo1[] =\n"
		"{\n"
		"    { 10000,	0,		9 },\n"
		"    { 20000, 	0, 		9 },\n"
		"    { 30000,  	0,  	9 },\n"
		"    { 40000,   	0,   	9 },\n"
		"};\n"
		"\n"
		"static FooBar foo2[] =\n"
		"{\n"
		"	{ 10000,	0,		9 },\n"
		"	{ 20000, 	0, 		9 },\n"
		"	{ 30000,  	0,  	9 },\n"
		"	{ 40000,   	0,   	9 },\n"
		"};\n"
		"\n"
		"static FooBar foo3[] =\n"
		"{\n"
		"	{ 10000,	0,		9 },\n"
		" 	{ 20000, 	0, 		9 },\n"
		"  	{ 30000,  	0,  	9 },\n"
		"   	{ 40000,   	0,   	9 },\n"
		"};\n"
		"\n"
		"static FooBar foo4[] =\n"
		"{\n"
		"	{ 100,  	0,		9 },\n"
		" 	{ 200,   	0, 		9 },\n"
		"  	{ 300,    	0,  	9 },\n"
		"   	{ 400,     	0,   	9 },\n"
		"};\n";
	char text[] =
		"\nstatic FooBar foo1[] =\n"
		"{\n"
		"    { 10000,    0,      9 },\n"
		"    { 20000,    0,      9 },\n"
		"    { 30000,    0,      9 },\n"
		"    { 40000,    0,      9 },\n"
		"};\n"
		"\n"
		"static FooBar foo2[] =\n"
		"{\n"
		"    { 10000,    0,      9 },\n"
		"    { 20000,    0,      9 },\n"
		"    { 30000,    0,      9 },\n"
		"    { 40000,    0,      9 },\n"
		"};\n"
		"\n"
		"static FooBar foo3[] =\n"
		"{\n"
		"    { 10000,    0,      9 },\n"
		"    { 20000,    0,      9 },\n"
		"    { 30000,    0,      9 },\n"
		"    { 40000,    0,      9 },\n"
		"};\n"
		"\n"
		"static FooBar foo4[] =\n"
		"{\n"
		"    { 100,      0,      9 },\n"
		"    { 200,      0,      9 },\n"
		"    { 300,      0,      9 },\n"
		"    { 400,      0,      9 },\n"
		"};\n";
	char options[] = "convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ConvertTabs, ShortOption)
{
	// test convert tabs short option
	char textIn[] =
		"\nstatic FooBar foo[] =\n"
		"{\n"
		"    { 10000,	0,		9 },\n"
		"    { 20000, 	0, 		9 },\n"
		"    { 30000,  	0,  	9 },\n"
		"    { 40000,   	0,   	9 },\n"
		"};\n"
		"\n"
		"static FooBar fooTab[] =\n"
		"{\n"
		"	{ 10000,	0,		9 },\n"
		"	{ 20000, 	0, 		9 },\n"
		"	{ 30000,  	0,  	9 },\n"
		"	{ 40000,   	0,   	9 },\n"
		"}\n";
	char text[] =
		"\nstatic FooBar foo[] =\n"
		"{\n"
		"    { 10000,    0,      9 },\n"
		"    { 20000,    0,      9 },\n"
		"    { 30000,    0,      9 },\n"
		"    { 40000,    0,      9 },\n"
		"};\n"
		"\n"
		"static FooBar fooTab[] =\n"
		"{\n"
		"    { 10000,    0,      9 },\n"
		"    { 20000,    0,      9 },\n"
		"    { 30000,    0,      9 },\n"
		"    { 40000,    0,      9 },\n"
		"}\n";
	char options[] = "-c";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ConvertTabs, Misc1)
{
	// convert comments, line comments, preprocessor
	// do NOT convert quotes
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"	/*\n"
		"	 * comment		comment\n"
		"  	 * comment	 	comment\n"
		"   	 * comment	  	comment\n"
		"     * comment	   	comment\n"
		"  	 */\n"
		"\n"
		"/*\n"
		"	commentedCode();\n"
		"*/\n"
		"\n"
		"    //	line    comment\n"
		" 	//  line	comment\n"
		"  	// 	line	comment\n"
		"   	//	line	comment\n"
		"\n"
		"#ifdef	foo\n"
		"	#error is foo\n"
		"  	#endif	// end	 of	if\n"
		"\n"
		"	char* quote =\n"
		" 	    \"this	is	a	quote \\\n"
		"  	quote 		continuation  \\\n"
		"	quote  		continuation\";\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"	/*\n"
		"	 * comment      comment\n"
		"	 * comment      comment\n"
		"	 * comment      comment\n"
		"	 * comment      comment\n"
		"	 */\n"
		"\n"
		"	/*\n"
		"	    commentedCode();\n"
		"	*/\n"
		"\n"
		"	//  line    comment\n"
		"	//  line    comment\n"
		"	//  line    comment\n"
		"	//  line    comment\n"
		"\n"
		"#ifdef  foo\n"
		"#error is foo\n"
		"#endif  // end   of if\n"
		"\n"
		"	char* quote =\n"
		"	    \"this	is	a	quote \\\n"
		"  	quote 		continuation  \\\n"
		"	quote  		continuation\";\n"
		"}\n";
	char options[] = "convert-tabs, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ConvertTabs, Misc2)
{
	// test convert-tabs with comments
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"	/*	comment1\n"
		"		comment2\n"
		"	*/\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    /*  comment1\n"
		"        comment2\n"
		"    */\n"
		"}\n";
	char options[] = "convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ConvertTabs, Misc3)
{
	// test convert-tabs with line comments and tabbed output
	// should NOT convert the leading tabs in a non-indent comment
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"//	comment1	comment1a\n"
		" //	comment2	comment2a\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"//	comment1 comment1a\n"
		"//	comment2    comment2a\n"
		"}\n";
	char options[] = "convert-tabs, --indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ConvertTabs, Misc4)
{
	// test convert-tabs with unpad-paren and pad-paren-in
	// should replace the tab after the opening paren
	char textIn[] =
		"\nvoid foo( bool isFoo )\n"
		"{\n"
		"    if(	isFoo )\n"
		"        bar;\n"
		"}\n";
	char text[] =
		"\nvoid foo( bool isFoo )\n"
		"{\n"
		"    if( isFoo )\n"
		"        bar;\n"
		"}\n";
	char options[] = "convert-tabs, unpad-paren, pad-paren-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ConvertTabs, Misc5)
{
	// test convert-tabs with comment continuation
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"	int bar1; /* comment1 */\n"
		"	int bar2; /* comment2\n"
		"				 comment3 */\n"
		"	int bar3; /* comment3 */\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    int bar1; /* comment1 */\n"
		"    int bar2; /* comment2\n"
		"                 comment3 */\n"
		"    int bar3; /* comment3 */\n"
		"}\n";
	char options[] = "convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ConvertTabs, Misc6)
{
	// verify that tabs are still present within quotes
	// should NOT have been replaced when AStyle was run
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    char* quote = \"this	is	a	quote \";\n"
		"}\n";
	// just check for the tab characters
	EXPECT_EQ('\t', text[37]);
	EXPECT_EQ('\t', text[40]);
	EXPECT_EQ('\t', text[42]);
}

TEST(ConvertTabs, ForceTabX1)
{
	// test convert-tabs in indent=force-tab-x
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    int bar1;		// comment1\n"
		"    int bar111;		/* comment2 */\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    int bar1;           // comment1\n"
		"    int bar111;         /* comment2 */\n"
		"}\n";
	char options[] = "indent=force-tab-x, convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ConvertTabs, ForceTabX2)
{
	// test convert-tabs in indent=force-tab-x with comment continuation
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    int bar1; /* comment1 */\n"
		"    int bar2; /* comment2\n"
		"		 comment3 */\n"
		"    int bar3; /* comment3 */\n"
		"}\n";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    int bar1; /* comment1 */\n"
		"    int bar2; /* comment2\n"
		"                 comment3 */\n"
		"    int bar3; /* comment3 */\n"
		"}\n";
	char options[] = "indent=force-tab-x, convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ConvertTabs, PreprocessorIndent)
{
	// Test convert-tabs in a preprocessor indent.
	// NOTE: The defines do NOT have a #endif closing the define.
	// This will cause a memory leak if the activeBeautifierStack and
	// waitingBeautifierStack are not deleted properly in ASBeautifier.
	char textIn[] =
		"\n#if (! defined (yyoverflow) \\\n"
		"     && (! defined (__cplusplus) \\\n"
		"\t || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))\n";
	char text[] =
		"\n#if (! defined (yyoverflow) \\\n"
		"     && (! defined (__cplusplus) \\\n"
		"     || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))\n";
	char options[] = "indent-preprocessor, convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Close Templates Tabs
//-------------------------------------------------------------------------

TEST(CloseTemplates, LongOption)
{
	// Test close-templates long option.
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string<int> > vec\n"
		"}";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string<int>> vec\n"
		"}";
	char options[] = "close-templates";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(CloseTemplates, ShortOption)
{
	// Test close-templates short option.
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string<int> > vec;\n"
		"}";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string<int>> vec;\n"
		"}";
	char options[] = "-xy";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(CloseTemplates, Sans)
{
	// Templates should NOT be closed without the option.
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string<int> > vec;\n"
		"}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(CloseTemplates, Padded)
{
	// Test close-templates with padding inside the templates.
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector< string< int > > vec;\n"
		"}";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    vector<string<int>> vec;\n"
		"}";
	char options[] = "close-templates";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Objective-C Align Method Colon
//-------------------------------------------------------------------------

TEST(ObjCAlignMethodColon, LongOption)
{
	// Test oc-align-method-colon long option.
	char text[] =
		"\n"
		"- (BOOL)tableView:(NSTableView *)tableView\n"
		"       acceptDrop:(id <NSDraggingInfo>)info\n"
		"              row:(int)row";
	char options[] = "oc-align-method-colon";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCAlignMethodColon, ShortOption)
{
	// Test oc-align-method-colon short option.
	char text[] =
		"\n"
		"- (BOOL)tableView:(NSTableView *)tableView\n"
		"       acceptDrop:(id <NSDraggingInfo>)info\n"
		"              row:(int)row";
	char options[] = "-xM";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCAlignMethodColon, Headers)
{
	// Test oc-align-method-colon headers.
	char text[] =
		"\n"
		"- (BOOL)tableView:(NSTableView *)tableView\n"
		"       acceptDrop:(id <NSDraggingInfo>)info\n"
		"              row:(int)row;\n"
		"\n"
		"- (id)tableView:(NSTableView *)aTableView\n"
		"    objectValueForTableColumn:(NSTableColumn *)aTableColumn\n"
		"            row:(int)rowIndex;\n"
		"\n"
		"- (BOOL)openFile:(NSString *)fullPath\n"
		" withApplication:(NSString *)appname\n"
		"   andDeactivate:(BOOL)flag;";
	char options[] = "oc-align-method-colon";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCAlignMethodColon, MethodsBreak)
{
	// Test oc-align-method-colon methods with broken brackets.
	char text[] =
		"\n"
		"- (BOOL)tableView:(NSTableView *)tableView\n"
		"       acceptDrop:(id <NSDraggingInfo>)info\n"
		"              row:(int)row\n"
		"{ }\n"
		"\n"
		"- (id)tableView:(NSTableView *)aTableView\n"
		"    objectValueForTableColumn:(NSTableColumn *)aTableColumn\n"
		"            row:(int)rowIndex\n"
		"{ }\n"
		"\n"
		"- (BOOL)openFile:(NSString *)fullPath\n"
		" withApplication:(NSString *)appname\n"
		"   andDeactivate:(BOOL)flag\n"
		"{ }\n";
	char options[] = "oc-align-method-colon";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCAlignMethodColon, MethodsAttach)
{
	// Test oc-align-method-colon methods with attached brackets.
	char text[] =
		"\n"
		"- (BOOL)tableView:(NSTableView *)tableView\n"
		"       acceptDrop:(id <NSDraggingInfo>)info\n"
		"              row:(int)row {\n"
		"}\n"
		"\n"
		"- (id)tableView:(NSTableView *)aTableView\n"
		"    objectValueForTableColumn:(NSTableColumn *)aTableColumn\n"
		"            row:(int)rowIndex {\n"
		"}\n"
		"\n"
		"- (BOOL)openFile:(NSString *)fullPath\n"
		" withApplication:(NSString *)appname\n"
		"   andDeactivate:(BOOL)flag {\n"
		"}\n";
	char options[] = "oc-align-method-colon";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------

}  // namespace
