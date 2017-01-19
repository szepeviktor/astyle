// AStyleTest_Format.cpp
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.txt describes the conditions under which this software may be distributed.

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleTest.h"

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {
//
//-------------------------------------------------------------------------
// AStyle Break Closing Brackets
// Additional tests are in the Brackets tests
//-------------------------------------------------------------------------

TEST(BreakClosingBraces, LongOption)
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
	char options[] = "break-closing-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakClosingBraces, ShortOption)
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
	delete[] textOut;
}

TEST(BreakClosingBraces, BreakClosingBraces)
{
	// test NONE_MODE brackets with break closing braces
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
	char options[] = "break-closing-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakClosingBraces, Break)
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
	char options[] = "style=allman, break-closing-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakClosingBraces, Attach)
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
	char options[] = "style=java, break-closing-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakClosingBraces, Linux)
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
	char options[] = "style=kr, break-closing-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakClosingBraces, RunIn)
{
	// test RUN_IN_MODE brackets with break closing headers
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
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n"
	    "\n";
	char options[] = "style=horstmann, break-closing-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakClosingBraces, KeepBlocks)
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
	char options[] = "style=java, break-closing-braces, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakClosingBraces, ElseSans)
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
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakClosingBraces, Catch)
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
	char options[] = "style=java, break-closing-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakClosingBraces, CatchSans)
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
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakClosingBraces, While)
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
	char options[] = "style=java, break-closing-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakClosingBraces, WhileSans)
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
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakClosingBraces, CSharp)
{
	// test break closing brackets with a preceeding one line block
	char textIn[] =
	    "\n"
	    "bool CtrlSpace()\n"
	    "{\n"
	    "    if (new[] { \"Setter\", \"EventSetter\" }) {\n"
	    "        Show(completion);\n"
	    "    } else if (Name.EndsWith(\"Trigger\")) {\n"
	    "        Show(completion);\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\n"
	    "bool CtrlSpace()\n"
	    "{\n"
	    "    if (new[] { \"Setter\", \"EventSetter\" }) {\n"
	    "        Show(completion);\n"
	    "    }\n"
	    "    else if (Name.EndsWith(\"Trigger\")) {\n"
	    "        Show(completion);\n"
	    "    }\n"
	    "}";
	char options[] = "break-closing-braces, keep-one-line-statements, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
}

TEST(BreakElseIfs, Sans1)
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
	delete[] textOut;
}

TEST(BreakElseIfs, Sans2)
{
	// test without break else/if
	// but do NOT join to #else following an else
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "#ifdef sun\n"
	    "    if (isUDP(mSettings)) {\n"
	    "        UDPSingleServer();\n"
	    "    }\n"
	    "    else\n"
	    "#else\n"
	    "    if (isSingleUDP(mSettings)) {\n"
	    "        UDPSingleServer();\n"
	    "    }\n"
	    "    else\n"
	    "#endif\n"
	    "    {\n"
	    "        thread_Settings *tempSettings = NULL;\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
}

TEST(BreakElseIfs, AddBraces)
{
	// Test break else/if with add-braces.
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
	char options[] = "break-elseifs, add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Break One Line Headers
//-------------------------------------------------------------------------

TEST(BreakOneLineHeaders, LongOption)
{
	// test break one line headers long option
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) bar = 1;\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "        bar = 1;\n"
	    "}";
	char options[] = "break-one-line-headers";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, ShortOption)
{
	// test break one line headers short option
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) bar = 1;\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "        bar = 1;\n"
	    "}";
	char options[] = "-xb";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, MultipleParens)
{
	// test break one line headers with multiple parens
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if ((isFoo1) && isFoo2) bar = 1;\n"
	    "}\n"
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1 && (isFoo2)) bar = 1;\n"
	    "}\n"
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if ((isFoo1) && (isFoo2)) bar = 1;\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if ((isFoo1) && isFoo2)\n"
	    "        bar = 1;\n"
	    "}\n"
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1 && (isFoo2))\n"
	    "        bar = 1;\n"
	    "}\n"
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if ((isFoo1) && (isFoo2))\n"
	    "        bar = 1;\n"
	    "}";
	char options[] = "break-one-line-headers";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, Else)
{
	// test break one line headers with else
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1) bar = 1;\n"
	    "    else bar = x;\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1)\n"
	    "        bar = 1;\n"
	    "    else\n"
	    "        bar = x;\n"
	    "}";
	char options[] = "break-one-line-headers";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, ElseIf)
{
	// test break one line headers with else-if
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1) bar = 1;\n"
	    "    else if (isFoo2)bar = x;\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1)\n"
	    "        bar = 1;\n"
	    "    else if (isFoo2)\n"
	    "        bar = x;\n"
	    "}";
	char options[] = "break-one-line-headers";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, ElseIfBreak)
{
	// test break one line headers with break-elseifs
	// should NOT prevent the break
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1) bar = 1;\n"
	    "    else if (isFoo2)bar = x;\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1)\n"
	    "        bar = 1;\n"
	    "    else\n"
	    "        if (isFoo2)\n"
	    "            bar = x;\n"
	    "}";
	char options[] = "break-one-line-headers, break-elseifs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, Catch)
{
	// test break one line headers with catch
	// should break AFTER the parens
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    try\n"
	    "    {\n"
	    "        app.go();\n"
	    "    }\n"
	    "    catch( Exception& e )\n"
	    "    {\n"
	    "        std::cerr << \"exception: \" << e.getDescription();\n"
	    "    }\n"
	    "}";
	char options[] = "break-one-line-headers";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, BreakBlocks)
{
	// test break one line headers with break blocks
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1) bar = 1;\n"
	    "    else bar = x;\n"
	    "    bar1();\n"
	    "    if (isFoo2) bar = 2;\n"
	    "    bar2();\n"
	    "    if (isFoo3) bar = 3;\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1)\n"
	    "        bar = 1;\n"
	    "    else\n"
	    "        bar = x;\n"
	    "\n"
	    "    bar1();\n"
	    "\n"
	    "    if (isFoo2)\n"
	    "        bar = 2;\n"
	    "\n"
	    "    bar2();\n"
	    "\n"
	    "    if (isFoo3)\n"
	    "        bar = 3;\n"
	    "}";
	char options[] = "break-one-line-headers, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, BreakBlocksAll)
{
	// test break one line headers with break blocks all
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1) bar = 1;\n"
	    "    else bar = x;\n"
	    "    bar1();\n"
	    "    if (isFoo2) bar = 2;\n"
	    "    bar2();\n"
	    "    if (isFoo3) bar = 3;\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1)\n"
	    "        bar = 1;\n"
	    "\n"
	    "    else\n"
	    "        bar = x;\n"
	    "\n"
	    "    bar1();\n"
	    "\n"
	    "    if (isFoo2)\n"
	    "        bar = 2;\n"
	    "\n"
	    "    bar2();\n"
	    "\n"
	    "    if (isFoo3)\n"
	    "        bar = 3;\n"
	    "}";
	char options[] = "break-one-line-headers, break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLStatements1)
{
	// a single one line header should break with keep OL statements
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1) bar = 1;\n"
	    "    else if (isFoo2)bar = x;\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1)\n"
	    "        bar = 1;\n"
	    "    else if (isFoo2)\n"
	    "        bar = x;\n"
	    "}";
	char options[] = "break-one-line-headers, keep-one-line-statements";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLStatements2)
{
	// a one line header with "else" should break with keep OL statements
	// break all blocks added to test
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) { bar1(); } else if (isFoo2) { bar2(); }\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar1();\n"
	    "\n"
	    "    } else if (isFoo2) {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char options[] = "break-one-line-headers, keep-one-line-statements, break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLStatements3)
{
	// a one line header should NOT break this with keep OL statements
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isBar1) anotherBar1(); else anotherBar2();\n"
	    "}";
	char options[] = "break-one-line-headers, keep-one-line-statements";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLStatements4)
{
	// a one line header should NOT break this with keep OL statements
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isBar1) anotherBar1(); bar2();\n"
	    "}";
	char options[] = "break-one-line-headers, keep-one-line-statements";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLStatements5)
{
	// a one line header should NOT break this with keep OL statements
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    bar2(); if (isBar1) anotherBar1();\n"
	    "}";
	char options[] = "break-one-line-headers, keep-one-line-statements";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLStatementsBreakBlocks)
{
	// test break one line headers with keep one line statements and break blocks
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    bar0();\n"
	    "    if (isFoo1) bar = 1; else bar = x;\n"
	    "    if (isFoo2) bar = 2; bar2();\n"
	    "    if (isFoo3) bar = 3; bar3();\n"
	    "    bar4();\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    bar0();\n"
	    "\n"
	    "    if (isFoo1) bar = 1; else bar = x;\n"
	    "\n"
	    "    if (isFoo2) bar = 2; bar2();\n"
	    "\n"
	    "    if (isFoo3) bar = 3; bar3();\n"
	    "\n"
	    "    bar4();\n"
	    "}";
	char options[] = "break-one-line-headers, keep-one-line-statements, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLBlocksSansBreak)
{
	// broken one line header followed by one line block
	// should NOT break the block
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1)\n"
	    "    { bar1(); }\n"
	    "    else if (isFoo2)\n"
	    "    { bar2(); }\n"
	    "}";
	char options[] = "break-one-line-headers, keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLBlocks1)
{
	// break one line headers ignores keep one line blocks
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) { bar1(); }\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar1();\n"
	    "    }\n"
	    "}";
	char options[] = "break-one-line-headers, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLBlocks2)
{
	// break one line headers ignores keep one line blocks
	// -A1 is style=allman
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) { bar1(); } else { bar2(); }\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar1();\n"
	    "    }\n"
	    "    else\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char options[] = "-A1, break-one-line-headers, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLBlocks3)
{
	// break one line headers ignores keep one line blocks
	// -A2 is style=java
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) { bar1(); } else if (isFoo2) { bar2(); }\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo() {\n"
	    "    if (isFoo) {\n"
	    "        bar1();\n"
	    "    } else if (isFoo2) {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char options[] = "-A2, break-one-line-headers, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLBlocksBreakBlocks)
{
	// break one line headers ignores keep one line blocks
	// -A5 is style=whitesmith
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) { bar1(); } else { bar2(); }\n"
	    "    baz1();\n"
	    "    if (isFoo) { bar1(); } else { bar2(); }\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "    {\n"
	    "    if (isFoo)\n"
	    "        {\n"
	    "        bar1();\n"
	    "        }\n"
	    "    else\n"
	    "        {\n"
	    "        bar2();\n"
	    "        }\n"
	    "\n"
	    "    baz1();\n"
	    "\n"
	    "    if (isFoo)\n"
	    "        {\n"
	    "        bar1();\n"
	    "        }\n"
	    "    else\n"
	    "        {\n"
	    "        bar2();\n"
	    "        }\n"
	    "    }";
	char options[] = "-A5, break-one-line-headers, keep-one-line-blocks, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLBlocksBreakBlocksAll)
{
	// break one line headers ignores keep one line blocks
	// -A9 is style=horstmann
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) { bar1(); } else { bar2(); }\n"
	    "    baz1();\n"
	    "    if (isFoo) { bar1(); } else { bar2(); }\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{   if (isFoo)\n"
	    "    {   bar1();\n"
	    "    }\n"
	    "\n"
	    "    else\n"
	    "    {   bar2();\n"
	    "    }\n"
	    "\n"
	    "    baz1();\n"
	    "\n"
	    "    if (isFoo)\n"
	    "    {   bar1();\n"
	    "    }\n"
	    "\n"
	    "    else\n"
	    "    {   bar2();\n"
	    "    }\n"
	    "}";
	char options[] = "-A9, break-one-line-headers, keep-one-line-blocks, break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLBlocksNonParenHeader)
{
	// with keep OL blocks and non-paren headers
	// should break headers and one line blocks
	// -A11 is style=pico
	char textIn[] =
	    "\n"
	    "public virtual int ZOrder\n"
	    "{\n"
	    "    get { return 0; }\n"
	    "    set { lastBuildResults = value; }\n"
	    "    add { TextChanged += value; }\n"
	    "    remove { TextChanged -= value; }\n"
	    "}";
	char text[] =
	    "\n"
	    "public virtual int ZOrder\n"
	    "{   get\n"
	    "    {   return 0; }\n"
	    "    set\n"
	    "    {   lastBuildResults = value; }\n"
	    "    add\n"
	    "    {   TextChanged += value; }\n"
	    "    remove\n"
	    "    {   TextChanged -= value; } }";
	char options[] = "-A11, break-one-line-headers, keep-one-line-blocks, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLBlocksElseIf)
{
	// keep OL blocks with an if else statement
	// should break one line blocks
	// -A12 is style=lisp
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) { bar1(); } else if (isFoo2) { bar2(); }\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo() {\n"
	    "    if (isFoo) {\n"
	    "        bar1(); }\n"
	    "\n"
	    "    else if (isFoo2) {\n"
	    "        bar2(); } }";
	char options[] = "-A12, break-one-line-headers, keep-one-line-blocks, break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, AddBracketsKeepOneLine1)
{
	// -Oo, keep-one-line-blocks, keep-one-line-statements
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) bar();\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "break-one-line-headers, add-braces, -Oo";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, AddBracketsKeepOneLine2)
{
	// -Oo, keep-one-line-blocks, keep-one-line-statements
	char textIn[] =
	    "\n"
	    "void Foo() \n"
	    "{\n"
	    "    if (isFoo) bar1(); else bar2();\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar1();\n"
	    "    } else {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char options[] = "break-one-line-headers, add-braces, -Oo";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, NoFollowingStatement)
{
	// should NOT break an ending semicolon
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (newPos currPos) /*use current mark*/;\n"
	    "    if (newPos currPos);\n"
	    "    for (int i = 0; i < end; i++);\n"
	    "}";
	char options[] = "break-one-line-headers";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, EmptyBracketsFollow)
{
	// empty brackets should NOT be changed
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    while (foo() < bar) {}\n"
	    "    for (int i = 0; i < end; i++)\n"
	    "    {}\n"
	    "}";
	char options[] = "break-one-line-headers";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, JavaSynchronizedMethod)
{
	// java synchronized method should NOT be broken
	char text[] =
	    "\n"
	    "public synchronized ZipFile getZipFile() throws IOException\n"
	    "{ }";
	char options[] = "break-one-line-headers";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLBlocksAndStmts1)
{
	// this should break with both keep one lines
	// -Oo, keep-one-line-blocks, keep-one-line-statements
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) { bar1(); }\n"
	    "    if (isFoo) bar1();\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar1();\n"
	    "    }\n"
	    "    if (isFoo)\n"
	    "        bar1();\n"
	    "}";
	char options[] = "break-one-line-headers, -Oo";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, KeepOLBlocksAndStmts2)
{
	// this should break with both keep one lines
	// -Oo, keep-one-line-blocks, keep-one-line-statements
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) { bar1(); } else { bar2(); }\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar1();\n"
	    "    } else {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char options[] = "break-one-line-headers, -Oo";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, EmptyBlockKeepOLBlocks)
{
	// empty block or ';' should not break with keep OL blocks
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    while (isFoo1) {}\n"
	    "\n"
	    "    while (isFoo2) {;}\n"
	    "\n"
	    "    if (fileExists(filenameStr)) {;/*OK Use exe path*/}\n"
	    "\n"
	    "    if (itemData) {;} //variable unused\n"
	    "\n"
	    "    if (fileExists(filenameStr)) {/*OK Use exe path*/;}\n"
	    "\n"
	    "    if (itemData) ; //variable unused\n"
	    "}";
	char options[] = "break-one-line-headers, keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, EmptyBlock)
{
	// empty block or ';' should not break withOUT keep OL blocks
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    while (isFoo1) {}\n"
	    "\n"
	    "    while (isFoo2) {;}\n"
	    "\n"
	    "    if (fileExists(filenameStr)) {;/*OK Use exe path*/}\n"
	    "\n"
	    "    if (itemData) {;} //variable unused\n"
	    "\n"
	    "    if (fileExists(filenameStr)) {/*OK Use exe path*/;}\n"
	    "\n"
	    "    if (itemData) ; //variable unused\n"
	    "}";
	char options[] = "break-one-line-headers";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, BlockStatementKeepOneLine)
{
	// statement enclosed in brackets with keep one line blocks
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if(!closed){if(true){bar();}}\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if(!closed) {\n"
	    "        if(true) {\n"
	    "            bar();\n"
	    "        }\n"
	    "    }\n"
	    "}";
	char options[] = "break-one-line-headers, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, BlockStatementAddBracketsKeepOneLine)
{
	// statement enclosed in brackets with add brackets and keep one line blocks
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if(!closed){if(true)bar();}\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if(!closed) {\n"
	    "        if(true) {\n"
	    "            bar();\n"
	    "        }\n"
	    "    }\n"
	    "}";
	char options[] = "break-one-line-headers, add-braces, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, PicoStyleAddBrackets)
{
	// test add brackets for pico brackets
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
	    "    {   return false; }\n"
	    "    else\n"
	    "    {   return true; } }\n";
	char options[] = "add-braces, style=pico, add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, Misc1)
{
	// the else-if statement should NOT break
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo1) {\n"
	    "        bar1();\n"
	    "#if DEBUG\n"
	    "        bar1d();\n"
	    "#endif\n"
	    "    } else if (isFoo2) {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char options[] = "break-one-line-headers";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakOneLineHeaders, Misc2)
{
	// should break the ending bracket after ('=') without a semicolon
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (CUR_CHAR != _SC('=')) { RETURN_TOKEN('=') }\n"
	    "    else { NEXT(); RETURN_TOKEN(TK_EQ); }\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (CUR_CHAR != _SC('=')) {\n"
	    "        RETURN_TOKEN('=')\n"
	    "    }\n"
	    "    else {\n"
	    "        NEXT();\n"
	    "        RETURN_TOKEN(TK_EQ);\n"
	    "    }\n"
	    "}";
	char options[] = "break-one-line-headers";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Add Braces
//-------------------------------------------------------------------------

TEST(AddBraces, LongOption)
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
	char options[] = "add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, ShortOption)
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
	delete[] textOut;
}

TEST(AddBraces, TempBracketsOption)
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
	delete[] textOut;
}

TEST(AddBraces, All)
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
	char options[] = "add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, ElseIf)
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
	char options[] = "add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, SemiFollows)
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
	char options[] = "add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, Sharp)
{
	// test add brackets to C# headers
	// 'delegate' statement contains brackets
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
	char options[] = "add-braces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, KeepOneLiners)
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
	char options[] = "add-braces, keep-one-line-blocks, keep-one-line-statements";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, SingleLine)
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
	char options[] = "add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, SingleLineKeepOneLiners)
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
	char options[] = "add-braces, keep-one-line-blocks, keep-one-line-statements";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, Break)
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
	char options[] = "add-braces, style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, Attach)
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
	char options[] = "add-braces, style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, RunIn)
{
	// test add brackets for run-in brackets
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
	char options[] = "add-braces, style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, ExtraSpaces)
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
	char options[] = "add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, ElseParen)
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
	char options[] = "add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, ElseBlock)
{
	// else statement should be recognized as a command-type bracket
	char textIn[] =
	    "\n"
	    "{\n"
	    "    if (x == 10)\n"
	    "        printf(\"x = %d\\n\", x);\n"
	    "    else\n"
	    "        printf(\"Nothing\");\n"
	    "}";
	char text[] =
	    "\n"
	    "{\n"
	    "    if (x == 10) {\n"
	    "        printf(\"x = %d\\n\", x);\n"
	    "    }\n"
	    "    else {\n"
	    "        printf(\"Nothing\");\n"
	    "    }\n"
	    "}";
	char options[] = "add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, Quote)
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
	char options[] = "add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, QuoteSans)
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
	char options[] = "add-braces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, Comment)
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
	char options[] = "add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, AfterCommentKeepOLBlocks)
{
	// add brackets after a comment with keep one line blocks
	// the brackets should be broken
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    for (it = 0; it != end(); ++it)\n"
	    "        // comment\n"
	    "        insert(*it);\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    for (it = 0; it != end(); ++it)\n"
	    "        // comment\n"
	    "    {\n"
	    "        insert(*it);\n"
	    "    }\n"
	    "}";
	char options[] = "add-braces, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, Sans)
{
	// brackets should be added to specified headers only
	char text[] =
	    "\npublic unsafe int foo()\n"
	    "{\n"
	    "    int readCount;\n"
	    "    fixed(byte* pBuffer = buffer)\n"
	    "        readCount = ReadMemory(size);\n"
	    "}\n";
	char options[] = "add-braces, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, ConvertTabs)
{
	// add brackets with convert tabs
	// the tabs should be converted
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (!isDoc)   //\t\"/*\" + ?\n"
	    "        isDoc = CurrentChar();    //\t\"/**\" but not \"/**/\"\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (!isDoc) { //    \"/*\" + ?\n"
	    "        isDoc = CurrentChar();    //    \"/**\" but not \"/**/\"\n"
	    "    }\n"
	    "}";
	char options[] = "add-braces, convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, KeepOneLineBlocks)
{
	// should NOT add brackets to one line blocks
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    { if(true) bar(); }\n"
	    "}";
	char options[] = "add-braces, keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, KeepOneLineBlocksSans1)
{
	// should add brackets if one line blocks are NOT retained
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    { if(true) bar(); }\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    {\n"
	    "        if(true) {\n"
	    "            bar();\n"
	    "        }\n"
	    "    }\n"
	    "}";
	char options[] = "add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, KeepOneLineBlocksSans2)
{
	// should add brackets if one line blocks are NOT retained
	// with more than one statement
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "	if (isFoo)\n"
	    "	{ *length = 0; return; }    // comment\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        *length = 0;    // comment\n"
	    "        return;\n"
	    "    }\n"
	    "}";
	char options[] = "add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, KeepOneLineStatements)
{
	// should NOT add brackets to one line statements
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    switch (nr)\n"
	    "    {\n"
	    "    case '\\0': break;\n"
	    "    default: nr=current_size+nr; if (nr>9) nr=9; if (nr< -9) nr=-9; break;\n"
	    "    }\n"
	    "}";
	char options[] = "add-braces, keep-one-line-statements";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddBraces, KeepOneLineStatementsSans)
{
	// should add brackets if one line statements are NOT retained
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    switch (nr)\n"
	    "    {\n"
	    "    case '\\0': break;\n"
	    "    default: nr=current_size+nr; if (nr>9) nr=9; if (nr< -9) nr=-9; break;\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    switch (nr)\n"
	    "    {\n"
	    "    case '\\0':\n"
	    "        break;\n"
	    "    default:\n"
	    "        nr=current_size+nr;\n"
	    "        if (nr>9) {\n"
	    "            nr=9;\n"
	    "        }\n"
	    "        if (nr< -9) {\n"
	    "            nr=-9;\n"
	    "        }\n"
	    "        break;\n"
	    "    }\n"
	    "}";
	char options[] = "add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Add One Line Braces
// Implies keep-one-line-blocks
//-------------------------------------------------------------------------

TEST(AddOneLineBraces, LongOption)
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
	char options[] = "add-one-line-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddOneLineBraces, ShortOption)
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
	delete[] textOut;
}

TEST(AddOneLineBraces, TempBracketsOption)
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
	delete[] textOut;
}

TEST(AddOneLineBraces, All)
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
	char options[] = "add-one-line-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddOneLineBraces, ElseIf)
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
	char options[] = "add-one-line-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddOneLineBraces, SemiFollows)
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
	char options[] = "add-one-line-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddOneLineBraces, Sharp)
{
	// test add one line brackets to C# headers
	// 'delegate' statement contains brackets
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
	char options[] = "add-one-line-braces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddOneLineBraces, SingleLine)
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
	char options[] = "add-one-line-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddOneLineBraces, SingleLineKeepOneLiners)
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
	char options[] = "add-one-line-braces, keep-one-line-statements";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddOneLineBraces, Break)
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
	char options[] = "add-one-line-braces, style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddOneLineBraces, Attach)
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
	char options[] = "add-one-line-braces, style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddOneLineBraces, RunIn)
{
	// test add one line brackets for run-in brackets
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
	char options[] = "add-one-line-braces, style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddOneLineBraces, ExtraSpaces)
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
	char options[] = "add-one-line-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddOneLineBraces, ElseParen)
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
	char options[] = "add-one-line-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddOneLineBraces, Quote)
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
	char options[] = "add-one-line-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddOneLineBraces, QuoteSans)
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
	char options[] = "add-one-line-braces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddOneLineBraces, Comment)
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
	char options[] = "add-one-line-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AddOneLineBraces, Sans)
{
	// brackets should be added to specified headers only
	char text[] =
	    "\npublic unsafe int foo()\n"
	    "{\n"
	    "    int readCount;\n"
	    "    fixed(byte* pBuffer = buffer)\n"
	    "        readCount = ReadMemory(size);\n"
	    "}\n";
	char options[] = "add-one-line-braces, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Remove Braces
//-------------------------------------------------------------------------

TEST(RemoveBraces, LongOption)
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
	char options[] = "remove-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, ShortOption)
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
	delete[] textOut;
}

TEST(RemoveBraces, TempBracketsOption)
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
	delete[] textOut;
}

TEST(RemoveBraces, WithEmptyLine1)
{
	// test with a preceding empty line
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
	char options[] = "remove-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, WithEmptyLine2)
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
	char options[] = "remove-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, WithEmptyLine3)
{
	// test attached brackets with a empty lines
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    if (IsUsingTree()) {\n"
	    "\n"
	    "        m_pTree->Delete();\n"
	    "\n"
	    "    }\n"
	    "    else {\n"
	    "\n"
	    "	     m_pCommands->Clear();\n"
	    "	     m_pCategories->Clear();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    if (IsUsingTree())\n"
	    "\n"
	    "        m_pTree->Delete();\n"
	    "\n"
	    "    else {\n"
	    "\n"
	    "        m_pCommands->Clear();\n"
	    "        m_pCategories->Clear();\n"
	    "    }\n"
	    "}";
	char options[] = "remove-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, Sans)
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
	char options[] = "remove-braces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, OneLineBlock1)
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
	char options[] = "remove-braces, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, OneLineBlockSans1)
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
	char options[] = "remove-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, OneLineBlockSans2)
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
	char options[] = "remove-braces, keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, OneLineBlockSans3)
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
	char options[] = "remove-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, BreakBlocks1)
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
	char options[] = "remove-braces, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, BreakBlocks2)
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
	char options[] = "remove-braces, break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, Comment1)
{
	// remove one-line brackets with a comment
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (keycode == WXK_RETURN)\n"
	    "        { myidx = 0; } // Edit\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (keycode == WXK_RETURN)\n"
	    "        myidx = 0;   // Edit\n"
	    "}";
	char options[] = "remove-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, Comment2)
{
	// remove one-line brackets with a comment
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "     if ( (target = Convert()) )\n"
	    "    {;}//ok\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if ( (target = Convert()) )\n"
	    "        ; //ok\n"
	    "}";
	char options[] = "remove-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, Comment3)
{
	// remove brackets with a comment following closing bracket
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    for(size_t i = 0; i < Count; ++i)\n"
	    "    {\n"
	    "        AppendToLog(Output[i]);\n"
	    "    } // end for : idx: i\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    for(size_t i = 0; i < Count; ++i)\n"
	    "        AppendToLog(Output[i]);\n"
	    "    // end for : idx: i\n"
	    "}";
	char options[] = "remove-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, Comment4)
{
	// remove attached bracket with a comment
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    if (isFoo) {  // comment\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    if (isFoo)    // comment\n"
	    "        bar();\n"
	    "}";
	char options[] = "remove-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, CommentSans1)
{
	// don't remove if a preceding comment
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
	char options[] = "remove-braces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, CommentSans2)
{
	// don't remove if a preceding column 1 comment
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
	char options[] = "remove-braces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, FollowingHeaderSans)
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
	char options[] = "remove-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, AddBracketsSans)
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
	char options[] = "remove-braces, add-braces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, AddOneLineBracketsSans)
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
	char options[] = "remove-braces, add-one-line-braces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, OtherHeaders)
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
	char options[] = "remove-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, SharpOtherHeaders)
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
	char options[] = "remove-braces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, OTBSSans)
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
	char options[] = "remove-braces, style=otbs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, BreakClosingBraces)
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
	char options[] = "remove-braces, break-closing-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, UnbrokenElse)
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
	char options[] = "remove-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, Preprocessor)
{
	// test remove brackets with a preprocessor directive
	// the brackets should NOT be removed
	char text[] =
	    "\nvoid Foo() {\n"
	    "#define if(_RET_SUCCEED(exp)) { result = (exp); }\n"
	    "}";
	char options[] = "remove-braces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, BracketInQuote)
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
	char options[] = "remove-braces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, BracketInComment1)
{
	// test remove with brackets within a line comment
	// should not remove the brackets
	char text[] =
	    "\nprivate void Foo() {\n"
	    "    if (closingBrackets > 0) {\n"
	    "        wrapper.Append(closingBrackets); // }\n"
	    "    }\n"
	    "}";
	char options[] = "remove-braces, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, BracketInComment2)
{
	// test remove with brackets within a comment
	// should not remove the brackets
	char text[] =
	    "\nprivate void Foo() {\n"
	    "    if (closingBrackets > 0) {\n"
	    "        wrapper.Append(closingBrackets); /* } */\n"
	    "    }\n"
	    "}";
	char options[] = "remove-braces, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveBraces, HorstmannBracketWithComment)
{
	// test remove horstmann bracket with a comment
	// should not remove the brackets
	char text[] =
	    "\nvoid Foo()\n"
	    "{   if (isFoo)\n"
	    "    {   // comment\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "remove-braces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	char options[] = "keep-one-line-blocks, style=allman";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	char options[] = "keep-one-line-blocks, style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	char options[] = "keep-one-line-blocks, style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	char options[] = "keep-one-line-blocks, style=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	delete[] textOut;
}

TEST(KeepOneLineBlocks, KeepOOLStatementsBreakElseIf)
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	char options[] = "style=allman, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	char options[] = "keep-one-line-blocks, style=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	delete[] textOut;
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
	char options[] = "keep-one-line-blocks, style=allman";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	char options[] = "keep-one-line-blocks, style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	char options[] = "keep-one-line-blocks, style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	delete[] textOut;
}

TEST(KeepOneLineBlocks, IndentSwitchBlockIndentSwitches)
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
}

TEST(KeepOneLineBlocks, IndentSansHeader)
{
	// test one line blocks indentation without a header
	char text[] =
	    "\nvoid foo(bool isFoo)\n"
	    "{\n"
	    "    bar()\n"
	    "    { anotherBar(); }\n"
	    "}\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
}

TEST(KeepOneLineStatements, ElseAtEndOfLine1)
{
	// test special case of an an "else" statement at the end of line
	// should NOT put everything on one line
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if ( Family == wxDECORATIVE ) FamilyStr = _T(\"wxDECORATIVE\"); else\n"
	    "    if ( Family == wxROMAN      ) FamilyStr = _T(\"wxROMAN\");      else\n"
	    "    if ( Family == wxSCRIPT     ) FamilyStr = _T(\"wxSCRIPT\");     else\n"
	    "    if ( Family == wxTELETYPE   ) FamilyStr = _T(\"wxTELETYPE\");\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if ( Family == wxDECORATIVE ) FamilyStr = _T(\"wxDECORATIVE\");\n"
	    "    else if ( Family == wxROMAN      ) FamilyStr = _T(\"wxROMAN\");\n"
	    "    else if ( Family == wxSCRIPT     ) FamilyStr = _T(\"wxSCRIPT\");\n"
	    "    else if ( Family == wxTELETYPE   ) FamilyStr = _T(\"wxTELETYPE\");\n"
	    "}";
	char options[] = "keep-one-line-statements";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(KeepOneLineStatements, ElseAtEndOfLine2)
{
	// test special case of an an "else" statement at the end of line with added brackets
	// should NOT put everything on one line
	char textIn[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if ( Family == wxDECORATIVE ) FamilyStr = _T(\"wxDECORATIVE\"); else\n"
	    "    if ( Family == wxROMAN      ) FamilyStr = _T(\"wxROMAN\");      else\n"
	    "    if ( Family == wxSCRIPT     ) FamilyStr = _T(\"wxSCRIPT\");     else\n"
	    "    if ( Family == wxTELETYPE   ) FamilyStr = _T(\"wxTELETYPE\");\n"
	    "}";
	char text[] =
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    if ( Family == wxDECORATIVE ) { FamilyStr = _T(\"wxDECORATIVE\"); }\n"
	    "    else if ( Family == wxROMAN      ) { FamilyStr = _T(\"wxROMAN\"); }\n"
	    "    else if ( Family == wxSCRIPT     ) { FamilyStr = _T(\"wxSCRIPT\"); }\n"
	    "    else if ( Family == wxTELETYPE   ) { FamilyStr = _T(\"wxTELETYPE\"); }\n"
	    "}";
	char options[] = "keep-one-line-statements, add-one-line-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
}

TEST(ConvertTabs, CommentsPreprocessorQuotes)
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
	delete[] textOut;
}

TEST(ConvertTabs, Comments1)
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
	delete[] textOut;
}

TEST(ConvertTabs, Comments2)
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
	delete[] textOut;
}

TEST(ConvertTabs, Comments3)
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
	delete[] textOut;
}

TEST(ConvertTabs, Misc1)
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
	delete[] textOut;
}

TEST(ConvertTabs, Misc2)
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
	delete[] textOut;
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
	delete[] textOut;
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
	char options[] = "indent-preproc-define, convert-tabs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
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
	delete[] textOut;
}

TEST(CloseTemplates, Padded)
{
	// Test close-templates with padding inside the templates.
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    vector1< string< int > > vec;\n"
	    "    vector2< string< int >    > vec;\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    vector1< string< int >> vec;\n"
	    "    vector2< string< int >> vec;\n"
	    "}";
	char options[] = "close-templates";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Remove Comment Prefix
//-------------------------------------------------------------------------

TEST(RemoveCommentPrefix, LongOption)
{
	// Test remove-comment-prefix long option.
	char textIn[] =
	    "\n/* comment\n"
	    " *\n"
	    " */";
	char text[] =
	    "\n/*  comment\n"
	    "\n"
	    "*/";
	char options[] = "remove-comment-prefix";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveCommentPrefix, ShortOption)
{
	// Test remove-comment-prefix short option.
	char textIn[] =
	    "\n/* comment\n"
	    " *\n"
	    " */";
	char text[] =
	    "\n/*  comment\n"
	    "\n"
	    "*/";
	char options[] = "-xp";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveCommentPrefix, SansMultiLine)
{
	// Test remove-comment-prefix with single-line comments.
	// They should not be changed.
	char text[] =
	    "\nvoid foo(bool isFoo)\n"
	    "{\n"
	    "    /* comment3 */\n"
	    "    /*xcomment4x*/\n"
	    "}";
	char options[] = "remove-comment-prefix";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveCommentPrefix, Format1)
{
	// Test remove-comment-prefix indentation.
	char textIn[] =
	    "\nvoid foo(bool isFoo)\n"
	    "{\n"
	    "        /* comment1\n"
	    "         *\n"
	    "         */\n"
	    "    if(isFoo) {\n"
	    "                    /* comment2\n"
	    "                     *\n"
	    "                     */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nvoid foo(bool isFoo)\n"
	    "{\n"
	    "    /*  comment1\n"
	    "\n"
	    "    */\n"
	    "    if(isFoo) {\n"
	    "        /*  comment2\n"
	    "\n"
	    "        */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}";
	char options[] = "remove-comment-prefix";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveCommentPrefix, Format2)
{
	// Test remove-comment-prefix option.
	// Beginning and ending '*' should be removed.
	// Text should be indented one indent.
	// The all '*' lines should not change
	char textIn[] =
	    "\n"
	    "/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
	    " * This software is distributed WITHOUT ANY WARRANTY, even the implied     *\n"
	    " * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.        *\n"
	    " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */";
	char text[] =
	    "\n"
	    "/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
	    "    This software is distributed WITHOUT ANY WARRANTY, even the implied\n"
	    "    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
	    " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */";
	char options[] = "remove-comment-prefix";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveCommentPrefix, Format3)
{
	// Test remove-comment-prefix option without '*'.
	// Text should be indented one indent.
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    /* This file is a part of Artistic Style - an indentation and\n"
	    "       reformatting tool for C, C++, C# and Java source files.\n"
	    "    */\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    /*  This file is a part of Artistic Style - an indentation and\n"
	    "        reformatting tool for C, C++, C# and Java source files.\n"
	    "    */\n"
	    "}";
	char options[] = "remove-comment-prefix";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveCommentPrefix, Format4)
{
	// Test remove-comment-prefix option.
	// Beginning '*' should be removed.
	// Text should NOT be indented - it is greater than one indent.
	char textIn[] =
	    "\n"
	    "/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
	    " *   Copyright (C) 2006-2011 by Jim Pattee <jimp03@email.com>\n"
	    " *   Copyright (C) 1998-2002 by Tal Davidson\n"
	    " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
	    " */";
	char text[] =
	    "\n"
	    "/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
	    "     Copyright (C) 2006-2011 by Jim Pattee <jimp03@email.com>\n"
	    "     Copyright (C) 1998-2002 by Tal Davidson\n"
	    " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
	    "*/";
	char options[] = "remove-comment-prefix";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveCommentPrefix, Format5)
{
	// Test remove-comment-prefix option.
	// Beginning '*' should be removed.
	// Text with tabs should NOT be indented - it is greater than one indent.
	// The '*' is ERASED and not replaced with a space.
	char textIn[] =
	    "\n"
	    "/*\n"
	    " *\ttabbed comment\n"
	    " */";
	char text[] =
	    "\n"
	    "/*\n"
	    " \ttabbed comment\n"
	    "*/";
	char options[] = "remove-comment-prefix";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveCommentPrefix, Format6)
{
	// Test remove-comment-prefix option.
	// Beginning '*' should be removed.
	// The tabbed text should be properly indented.
	// The '/*!' should not be separated.
	char textIn[] =
	    "\n"
	    "/*! \\brief	Update manifest.xml with the latest version string.\n"
	    " * \\author	Gary Harris\n"
	    " * \\date  	03/03/10\n"
	    " * \\return void\n"
	    " */";
	char text[] =
	    "\n"
	    "/*! \\brief	Update manifest.xml with the latest version string.\n"
	    "    \\author	Gary Harris\n"
	    "    \\date  	03/03/10\n"
	    "    \\return void\n"
	    "*/";
	char options[] = "remove-comment-prefix";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveCommentPrefix, Format7)
{
	// Test remove-comment-prefix option.
	// Beginning '*' should be removed.
	// The text should be properly indented.
	// The '/**' should not be separated.
	char textIn[] =
	    "\n"
	    "/** @brief A file editor\n"
	    " *\n"
	    " * @param use If true tooltips are allowed\n"
	    " */";
	char text[] =
	    "\n"
	    "/**   @brief A file editor\n"
	    "\n"
	    "      @param use If true tooltips are allowed\n"
	    "*/";
	char options[] = "remove-comment-prefix, indent=spaces=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(RemoveCommentPrefix, CommentedCode1)
{
	// Test remove-comment-prefix option with commented text.
	// The tabbed alignment should be maintained.
	char textIn[] =
	    "\nvoid foo(bool isFoo)\n"
	    "{\n"
	    "    /*if (client == NULL) {\n"
	    "    	//int found = -1;\n"
	    "    	for (int i=0; i < getCount(); i++)\n"
	    "    		if ((Item(i)) == event.GetEventObject())\n"
	    "    			client = m_arrAttachedWnd.Item(i);\n"
	    "    }*/\n"
	    "}";
	char text[] =
	    "\nvoid foo(bool isFoo)\n"
	    "{\n"
	    "    /*  if (client == NULL) {\n"
	    "    	//int found = -1;\n"
	    "    	for (int i=0; i < getCount(); i++)\n"
	    "    		if ((Item(i)) == event.GetEventObject())\n"
	    "    			client = m_arrAttachedWnd.Item(i);\n"
	    "        }*/\n"
	    "}";
	char options[] = "remove-comment-prefix";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------

}  // namespace
