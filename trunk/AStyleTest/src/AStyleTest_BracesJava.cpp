// AStyleTest_BracesJava.cpp
// Copyright (c) 2017 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

//-----------------------------------------------------------------------------
// AStyle Java Brace Options
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleTest.h"

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {
//
//-----------------------------------------------------------------------------
// AStyle Java Brace Options
//-----------------------------------------------------------------------------

//-------------------------------------------------------------------------
// AStyle Java Default Brace Options
//-------------------------------------------------------------------------

struct BracesNoneJavaF : public Test
{
	string textStr;
	const char* textIn;

	BracesNoneJavaF()
	{
		textStr =
		    "\npublic class FooClass\n"
		    "{\n"
		    "    private bool var1;\n"
		    "    private bool var2;\n"
		    "\n"
		    "    public void foo(bool isFoo)\n"
		    "    {\n"
		    "        if (isFoo) {\n"
		    "            bar();\n"
		    "        } else {\n"
		    "            anotherBar();\n"
		    "        }\n"
		    "    }\n"
		    "}\n";
		textIn = textStr.c_str();
	}
};

TEST_F(BracesNoneJavaF, Default)
{
	// test default braces option (do not change)
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    private bool var1;\n"
	    "    private bool var2;\n"
	    "\n"
	    "    public void foo(bool isFoo)\n"
	    "    {\n"
	    "        if (isFoo) {\n"
	    "            bar();\n"
	    "        } else {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneJava, EmptyBraces)
{
	// test default braces option (do not change)
	// do not change empty braces
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    public FooClass() {}\n"
	    "    public FooClass() {\n"
	    "    }\n"
	    "    public FooClass()\n"
	    "    {}\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneJava, EmptyBracesWithComments)
{
	// test default braces option (do not change) with ending comments
	// do not change empty braces
	char text[] =
	    "\npublic class FooClass // comment\n"
	    "{\n"
	    "    public FooClass() {} // comment\n"
	    "    public FooClass() { // comment\n"
	    "    }\n"
	    "    public FooClass() // comment\n"
	    "    {}\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneJava, Break)
{
	// test default braces option with broken braces
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneJava, Attach)
{
	// test default braces option with attached braces
	char text[] =
	    "\npublic void Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneJava, Linux)
{
	// test default braces option with linux braces
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneJava, RunIn)
{
	// test default braces option with run-in braces
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneJava, EnumConstructorBreak)
{
	// test default braces option with an enum constructor
	char text[] =
	    "\npublic enum Scope\n"
	    "{\n"
	    "    global, view, editpane;\n"
	    "\n"
	    "    public static Scope fromString(String s)\n"
	    "    {\n"
	    "        Scope[] scopes = values();\n"
	    "        for (Scope scope: scopes)\n"
	    "        {\n"
	    "            if (scope.toString().equals(s))\n"
	    "                return scope;\n"
	    "        }\n"
	    "\n"
	    "        return global;\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneJava, EnumConstructorAttach)
{
	// test default braces option with an enum constructor
	char text[] =
	    "\npublic enum Scope {\n"
	    "    global, view, editpane;\n"
	    "\n"
	    "    public static Scope fromString(String s) {\n"
	    "        Scope[] scopes = values();\n"
	    "        for (Scope scope: scopes) {\n"
	    "            if (scope.toString().equals(s))\n"
	    "                return scope;\n"
	    "        }\n"
	    "\n"
	    "        return global;\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneJava, EnumConstructorRunIn)
{
	// test default braces option with an enum constructor
	char text[] =
	    "\npublic enum Scope\n"
	    "{   global, view, editpane;\n"
	    "\n"
	    "    public static Scope fromString(String s)\n"
	    "    {   Scope[] scopes = values();\n"
	    "        for (Scope scope: scopes)\n"
	    "        {   if (scope.toString().equals(s))\n"
	    "                return scope;\n"
	    "        }\n"
	    "\n"
	    "        return global;\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Java Break Brace Options
//-------------------------------------------------------------------------

struct BracesBreakJavaF : public Test
{
	string textStr;
	const char* textIn;

	BracesBreakJavaF()
	{
		textStr =
		    "\npublic class FooClass\n"
		    "{\n"
		    "    private bool var1;\n"
		    "    private bool var2;\n"
		    "\n"
		    "    public void foo(bool isFoo)\n"
		    "    {\n"
		    "        if (isFoo) {\n"
		    "            bar();\n"
		    "        } else {\n"
		    "            anotherBar();\n"
		    "        }\n"
		    "    }\n"
		    "}\n";
		textIn = textStr.c_str();
	}
};

TEST_F(BracesBreakJavaF, LongOption)
{
	// test break braces option
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    private bool var1;\n"
	    "    private bool var2;\n"
	    "\n"
	    "    public void foo(bool isFoo)\n"
	    "    {\n"
	    "        if (isFoo)\n"
	    "        {\n"
	    "            bar();\n"
	    "        }\n"
	    "        else\n"
	    "        {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=break, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesBreakJavaF, ShortOption)
{
	// test break braces short option
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    private bool var1;\n"
	    "    private bool var2;\n"
	    "\n"
	    "    public void foo(bool isFoo)\n"
	    "    {\n"
	    "        if (isFoo)\n"
	    "        {\n"
	    "            bar();\n"
	    "        }\n"
	    "        else\n"
	    "        {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "-A1, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakJava, EmptyBraces)
{
	// test break braces option
	char textIn[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    public FooClass() {}\n"
	    "    public FooClass() {\n"
	    "    }\n"
	    "    public FooClass()\n"
	    "    {}\n"
	    "}\n";
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    public FooClass() {}\n"
	    "    public FooClass()\n"
	    "    {\n"
	    "    }\n"
	    "    public FooClass()\n"
	    "    {}\n"
	    "}\n";
	char options[] = "style=break, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakJava, EmptyBracesWithComments)
{
	// test break braces option with ending comments
	char textIn[] =
	    "\npublic class FooClass // comment\n"
	    "{\n"
	    "    public FooClass() {} // comment\n"
	    "    public FooClass() { // comment\n"
	    "    }\n"
	    "    public FooClass() // comment\n"
	    "    {}\n"
	    "}\n";
	char text[] =
	    "\npublic class FooClass // comment\n"
	    "{\n"
	    "    public FooClass() {} // comment\n"
	    "    public FooClass()   // comment\n"
	    "    {\n"
	    "    }\n"
	    "    public FooClass() // comment\n"
	    "    {}\n"
	    "}\n";
	char options[] = "style=break, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakJava, Break)
{
	// test break braces option with broken braces
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=break, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakJava, Attach)
{
	// test break braces option with attached braces
	char textIn[] =
	    "\npublic void Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=break, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakJava, Linux)
{
	// test break braces option with linux braces
	char textIn[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=break, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakJava, RunIn)
{
	// test break braces option with run-in braces
	char textIn[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=break, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakJava, EnumConstructor)
{
	// test break braces option with an enum constructor
	char textIn[] =
	    "\npublic enum Scope {\n"
	    "    global, view, editpane;\n"
	    "\n"
	    "    public static Scope fromString(String s) {\n"
	    "        Scope[] scopes = values();\n"
	    "        for (Scope scope: scopes) {\n"
	    "            if (scope.toString().equals(s))\n"
	    "                return scope;\n"
	    "        }\n"
	    "\n"
	    "        return global;\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic enum Scope\n"
	    "{\n"
	    "    global, view, editpane;\n"
	    "\n"
	    "    public static Scope fromString(String s)\n"
	    "    {\n"
	    "        Scope[] scopes = values();\n"
	    "        for (Scope scope: scopes)\n"
	    "        {\n"
	    "            if (scope.toString().equals(s))\n"
	    "                return scope;\n"
	    "        }\n"
	    "\n"
	    "        return global;\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=break, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Java Attach Brace Options
//-------------------------------------------------------------------------

struct BracesAttachJavaF : public Test
{
	string textStr;
	const char* textIn;

	BracesAttachJavaF()
	{
		textStr =
		    "\npublic class FooClass\n"
		    "{\n"
		    "    private bool var1;\n"
		    "    private bool var2;\n"
		    "\n"
		    "    public void foo(bool isFoo)\n"
		    "    {\n"
		    "        if (isFoo) {\n"
		    "            bar();\n"
		    "        } else {\n"
		    "            anotherBar();\n"
		    "        }\n"
		    "    }\n"
		    "}\n";
		textIn = textStr.c_str();
	}
};

TEST_F(BracesAttachJavaF, LongOption)
{
	// test attach braces option
	char text[] =
	    "\npublic class FooClass {\n"
	    "    private bool var1;\n"
	    "    private bool var2;\n"
	    "\n"
	    "    public void foo(bool isFoo) {\n"
	    "        if (isFoo) {\n"
	    "            bar();\n"
	    "        } else {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=attach, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesAttachJavaF, ShortOption)
{
	// test attach braces short option
	char text[] =
	    "\npublic class FooClass {\n"
	    "    private bool var1;\n"
	    "    private bool var2;\n"
	    "\n"
	    "    public void foo(bool isFoo) {\n"
	    "        if (isFoo) {\n"
	    "            bar();\n"
	    "        } else {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "-A2, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesAttachJavaF, BreakClosing)
{
	// test attach braces option, with break closing braces
	char text[] =
	    "\npublic class FooClass {\n"
	    "    private bool var1;\n"
	    "    private bool var2;\n"
	    "\n"
	    "    public void foo(bool isFoo) {\n"
	    "        if (isFoo) {\n"
	    "            bar();\n"
	    "        }\n"
	    "        else {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=attach, break-closing-braces, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachJava, EmptyBraces)
{
	// test attach braces option
	char text[] =
	    "\npublic class FooClass {\n"
	    "    public FooClass() {}\n"
	    "    public FooClass() {\n"
	    "    }\n"
	    "    public FooClass()\n"
	    "    {}\n"
	    "}\n";
	char options[] = "style=attach, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachJava, EmptyBracesWithComments)
{
	// test attach braces option with ending comments
	char text[] =
	    "\npublic class FooClass { // comment\n"
	    "    public FooClass() {} // comment\n"
	    "    public FooClass() { // comment\n"
	    "    }\n"
	    "    public FooClass() // comment\n"
	    "    {}\n"
	    "}\n";
	char options[] = "style=attach, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachJava, Break)
{
	// test attach braces option with broken braces
	char textIn[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic void Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=attach, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachJava, Attach)
{
	// test attach braces option with attached braces
	char text[] =
	    "\npublic void Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=attach, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachJava, Linux)
{
	// test attach braces option with linux braces
	char textIn[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic void Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=attach, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachJava, RunIn)
{
	// test attach braces option with run-in braces
	char textIn[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic void Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=attach, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachJava, EnumConstructor)
{
	// test attach braces option with an enum constructor
	char textIn[] =
	    "\npublic enum Scope\n"
	    "{\n"
	    "    global, view, editpane;\n"
	    "\n"
	    "    public static Scope fromString(String s)\n"
	    "    {\n"
	    "        Scope[] scopes = values();\n"
	    "        for (Scope scope: scopes)\n"
	    "        {\n"
	    "            if (scope.toString().equals(s))\n"
	    "                return scope;\n"
	    "        }\n"
	    "\n"
	    "        return global;\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic enum Scope {\n"
	    "    global, view, editpane;\n"
	    "\n"
	    "    public static Scope fromString(String s) {\n"
	    "        Scope[] scopes = values();\n"
	    "        for (Scope scope: scopes) {\n"
	    "            if (scope.toString().equals(s))\n"
	    "                return scope;\n"
	    "        }\n"
	    "\n"
	    "        return global;\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=attach, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Java Linux Brace Options
//-------------------------------------------------------------------------

struct BracesLinuxJavaF : public Test
{
	string textStr;
	const char* textIn;

	BracesLinuxJavaF()
	{
		textStr =
		    "\npublic class FooClass\n"
		    "{\n"
		    "    private bool var1;\n"
		    "    private bool var2;\n"
		    "\n"
		    "    public void foo(bool isFoo)\n"
		    "    {\n"
		    "        if (isFoo) {\n"
		    "            bar();\n"
		    "        } else {\n"
		    "            anotherBar();\n"
		    "        }\n"
		    "    }\n"
		    "}\n";
		textIn = textStr.c_str();
	}
};

TEST_F(BracesLinuxJavaF, LongOption)
{
	// test linux braces option
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    private bool var1;\n"
	    "    private bool var2;\n"
	    "\n"
	    "    public void foo(bool isFoo)\n"
	    "    {\n"
	    "        if (isFoo) {\n"
	    "            bar();\n"
	    "        } else {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesLinuxJavaF, ShortOption)
{
	// test linux braces short option
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    private bool var1;\n"
	    "    private bool var2;\n"
	    "\n"
	    "    public void foo(bool isFoo)\n"
	    "    {\n"
	    "        if (isFoo) {\n"
	    "            bar();\n"
	    "        } else {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "-A3, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesLinuxJavaF, BreakClosing)
{
	// test linux braces option, with break closing braces
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    private bool var1;\n"
	    "    private bool var2;\n"
	    "\n"
	    "    public void foo(bool isFoo)\n"
	    "    {\n"
	    "        if (isFoo) {\n"
	    "            bar();\n"
	    "        }\n"
	    "        else {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr, break-closing-braces, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxJava, EmptyBraces)
{
	// test linux braces option
	char textIn[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    public FooClass() {}\n"
	    "    public FooClass() {\n"
	    "    }\n"
	    "    public FooClass()\n"
	    "    {}\n"
	    "}\n";
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    public FooClass() {}\n"
	    "    public FooClass()\n"
	    "    {\n"
	    "    }\n"
	    "    public FooClass()\n"
	    "    {}\n"
	    "}\n";
	char options[] = "style=kr, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxJava, EmptyBracesWithComments)
{
	// test linux braces option with ending comments
	char textIn[] =
	    "\npublic class FooClass // comment\n"
	    "{\n"
	    "    public FooClass() {} // comment\n"
	    "    public FooClass() { // comment\n"
	    "    }\n"
	    "    public FooClass() // comment\n"
	    "    {}\n"
	    "}\n";
	char text[] =
	    "\npublic class FooClass // comment\n"
	    "{\n"
	    "    public FooClass() {} // comment\n"
	    "    public FooClass()   // comment\n"
	    "    {\n"
	    "    }\n"
	    "    public FooClass() // comment\n"
	    "    {}\n"
	    "}\n";
	char options[] = "style=kr, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxJava, Break)
{
	// test linux braces option with broken braces
	char textIn[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxJava, Attach)
{
	// test linux braces option with attached braces
	char textIn[] =
	    "\npublic void Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxJava, Linux)
{
	// test linux braces option with linux braces
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxJava, RunIn)
{
	// test linux braces option with run-in braces
	char textIn[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxJava, EnumConstructor)
{
	// test linux braces option with an enum constructor
	char textIn[] =
	    "\npublic enum Scope\n"
	    "{\n"
	    "    global, view, editpane;\n"
	    "\n"
	    "    public static Scope fromString(String s)\n"
	    "    {\n"
	    "        Scope[] scopes = values();\n"
	    "        for (Scope scope: scopes)\n"
	    "        {\n"
	    "            if (scope.toString().equals(s))\n"
	    "                return scope;\n"
	    "        }\n"
	    "\n"
	    "        return global;\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic enum Scope {\n"
	    "    global, view, editpane;\n"
	    "\n"
	    "    public static Scope fromString(String s)\n"
	    "    {\n"
	    "        Scope[] scopes = values();\n"
	    "        for (Scope scope: scopes) {\n"
	    "            if (scope.toString().equals(s))\n"
	    "                return scope;\n"
	    "        }\n"
	    "\n"
	    "        return global;\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Java RunIn Brace Options
//-------------------------------------------------------------------------

struct BracesRunInJavaF : public Test
{
	string textStr;
	const char* textIn;

	BracesRunInJavaF()
	{
		textStr =
		    "\npublic class FooClass\n"
		    "{\n"
		    "    private bool var1;\n"
		    "    private bool var2;\n"
		    "\n"
		    "    public void foo(bool isFoo)\n"
		    "    {\n"
		    "        if (isFoo) {\n"
		    "            bar();\n"
		    "        } else {\n"
		    "            anotherBar();\n"
		    "        }\n"
		    "    }\n"
		    "}\n";
		textIn = textStr.c_str();
	}
};

TEST_F(BracesRunInJavaF, LongOption)
{
	// test run-in braces option
	char text[] =
	    "\npublic class FooClass\n"
	    "{   private bool var1;\n"
	    "    private bool var2;\n"
	    "\n"
	    "    public void foo(bool isFoo)\n"
	    "    {   if (isFoo)\n"
	    "        {   bar();\n"
	    "        }\n"
	    "        else\n"
	    "        {   anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesRunInJavaF, ShortOption)
{
	// test run-in braces short option
	char text[] =
	    "\npublic class FooClass\n"
	    "{   private bool var1;\n"
	    "    private bool var2;\n"
	    "\n"
	    "    public void foo(bool isFoo)\n"
	    "    {   if (isFoo)\n"
	    "        {   bar();\n"
	    "        }\n"
	    "        else\n"
	    "        {   anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "-A9, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInJava, EmptyBraces)
{
	// test run-in braces option
	char textIn[] =
	    "\npublic class FooClass\n"
	    "{   public FooClass() {}\n"
	    "    public FooClass() {\n"
	    "    }\n"
	    "    public FooClass()\n"
	    "    {}\n"
	    "}\n";
	char text[] =
	    "\npublic class FooClass\n"
	    "{   public FooClass() {}\n"
	    "    public FooClass()\n"
	    "    {\n"
	    "    }\n"
	    "    public FooClass()\n"
	    "    {}\n"
	    "}\n";
	char options[] = "style=run-in, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInJava, EmptyBracesWithComments)
{
	// test run-in braces option with ending comments
	char textIn[] =
	    "\npublic class FooClass // comment\n"
	    "{   public FooClass() {} // comment\n"
	    "    public FooClass() { // comment\n"
	    "    }\n"
	    "    public FooClass() // comment\n"
	    "    {}\n"
	    "}\n";
	char text[] =
	    "\npublic class FooClass // comment\n"
	    "{   public FooClass() {} // comment\n"
	    "    public FooClass()   // comment\n"
	    "    {\n"
	    "    }\n"
	    "    public FooClass() // comment\n"
	    "    {}\n"
	    "}\n";
	char options[] = "style=run-in, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInJava, Break)
{
	// test run-in braces option with broken braces
	char textIn[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInJava, Attach)
{
	// test run-in braces option with attached braces
	char textIn[] =
	    "\npublic void Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInJava, Linux)
{
	// test run-in braces option with linux braces
	char textIn[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInJava, RunIn)
{
	// test run-in braces option with run-in braces
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInJava, EnumConstructor)
{
	// test run-in braces option with an enum constructor
	char textIn[] =
	    "\npublic enum Scope\n"
	    "{\n"
	    "    global, view, editpane;\n"
	    "\n"
	    "    public static Scope fromString(String s)\n"
	    "    {\n"
	    "        Scope[] scopes = values();\n"
	    "        for (Scope scope: scopes)\n"
	    "        {\n"
	    "            if (scope.toString().equals(s))\n"
	    "                return scope;\n"
	    "        }\n"
	    "\n"
	    "        return global;\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\npublic enum Scope\n"
	    "{   global, view, editpane;\n"
	    "\n"
	    "    public static Scope fromString(String s)\n"
	    "    {   Scope[] scopes = values();\n"
	    "        for (Scope scope: scopes)\n"
	    "        {   if (scope.toString().equals(s))\n"
	    "                return scope;\n"
	    "        }\n"
	    "\n"
	    "        return global;\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Java Other Brace Options
//-------------------------------------------------------------------------

struct BracesOtherJavaF : public Test
{
	string textStr;
	const char* textIn;

	BracesOtherJavaF()
	{
		textStr =
		    "\npublic class FooClass\n"
		    "{\n"
		    "    private bool var1;\n"
		    "    private bool var2;\n"
		    "\n"
		    "    public void foo(bool isFoo)\n"
		    "    {\n"
		    "        if (isFoo) {\n"
		    "            bar();\n"
		    "        } else {\n"
		    "            anotherBar();\n"
		    "        }\n"
		    "    }\n"
		    "}\n";
		textIn = textStr.c_str();
	}
};

TEST_F(BracesOtherJavaF, IndentNamespaces)
{
	// indent namespaces should NOT affect java formatting
	char options[] = "indent-namespaces, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(textIn, textOut);
	delete[] textOut;
}

TEST_F(BracesOtherJavaF, IndentClasses)
{
	// indent classes should NOT affect java formatting
	char options[] = "indent-classes, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(textIn, textOut);
	delete[] textOut;
}

TEST_F(BracesOtherJavaF, IndentNamespaces_IndentClass)
{
	// indent namespaces and classes should NOT affect java formatting
	char options[] = "indent-namespaces, indent-classes, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(textIn, textOut);
	delete[] textOut;
}

TEST(BracesOtherJava, ClassContinuation_Attached)
{
	// test with class continuation and attached braces
	char text[] =
	    "\npublic class Foo\n"
	    "    extends Bar1\n"
	    "    implements Bar2 {\n"
	    "    private int FOO = 1;\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherJava, ClassContinuation_Broken)
{
	// test with class continuation and broken braces
	char text[] =
	    "\npublic class Foo\n"
	    "    extends Bar1\n"
	    "    implements Bar2\n"
	    "{\n"
	    "    private int FOO = 1;\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherJava, Interface)
{
	// test default braces option (do not change)
	char text[] =
	    "\npublic interface FooIF\n"
	    "{\n"
	    "    public void foo1();\n"
	    "    public void foo2();\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherJava, NestedClass)
{
	// test interface with nested classes
	char text[] =
	    "\npublic class A\n"
	    "{\n"
	    "    public int foo1;\n"
	    "    public class B\n"
	    "    {\n"
	    "        public int foo2;\n"
	    "        public class C\n"
	    "        {\n"
	    "            public void foo(bool isFoo)\n"
	    "            {\n"
	    "                if (isFoo)\n"
	    "                {\n"
	    "                    bar();\n"
	    "                }\n"
	    "                else\n"
	    "                    anotherBar();\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherJava, StaticConstructor)
{
	// test gnu style option, with static constructor
	// should NOT indent the method opening bracket
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    private bool foo;\n"
	    "    private int  bar;\n"
	    "\n"
	    "    static\n"
	    "    {\n"
	    "        if (foo)\n"
	    "        {\n"
	    "            bar = 0;\n"
	    "        }\n"
	    "        else\n"
	    "            bar = 1;\n"
	    "    }\n"
	    "}\n"
	    "\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherJava, Throws)
{
	// test a method that contains a throws statement
	// should be recognized as a block opener
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    private bool foo;\n"
	    "    private int  bar;\n"
	    "\n"
	    "    public void fooBar() throws IOException\n"
	    "    {\n"
	    "        if (foo)\n"
	    "        {\n"
	    "            throw new IOException(bar);\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherJava, NewOperator1)
{
	// test new operator ending with })
	char text[] =
	    "\npublic class fooClass\n"
	    "{\n"
	    "    public Foo()\n"
	    "    {\n"
	    "        foo(new bar()\n"
	    "        {\n"
	    "            public void fooBar(ChangeEvent e)\n"
	    "            {\n"
	    "                int x = 2;\n"
	    "            }\n"
	    "        });\n"
	    "\n"
	    "        mlist.setListData(new Object [] { });\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherJava, NewOperator2)
{
	// test new operator ending with }.start();
	char text[] =
	    "\npublic class fooClass\n"
	    "{\n"
	    "    public Foo()\n"
	    "    {\n"
	    "        new Thread(\"Sizesavingdelay\")\n"
	    "        {\n"
	    "        } .start();\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Java Array Brace Options
//-------------------------------------------------------------------------

TEST(BracesArrayJava, None_BraceInParens)
{
	// Array braces should not pad the '( {"unchecked"})'.
	char text[] =
	    "\npublic void Foo()\n"
	    "{\n"
	    "    try\n"
	    "    {\n"
	    "        @SuppressWarnings({\"unchecked\"})\n"
	    "        t(transferable);\n"
	    "    }\n"
	    "}";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayJava, None_InStatement)
{
	// the following "new Type" array should have an in statement indent
	char text[] =
	    "\npublic class ClassUtil implements Constants\n"
	    "{\n"
	    "	static void generateMethod()\n"
	    "	{\n"
	    "		cv.visitMethodInsn(\n"
	    "		    Type.getMethodDescriptor(\n"
	    "		        Type.getType(Object.class),\n"
	    "		        new Type [] {\n"
	    "		            Type.getType(String.class),\n"
	    "		            Type.getType(Object [].class),\n"
	    "		            Type.getType(Boolean.TYPE)\n"
	    "		        }\n"
	    "		    )\n"
	    "		);\n"
	    "	}\n"
	    "}\n";
	char options[] = "indent=tab, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayJava, None_OneLineBlock1)
{
	// single line blocks should not be broken
	char text[] =
	    "\npublic OSTask[] getOSTasks()\n"
	    "{\n"
	    "    return new OSTask[] { /* comment */ };\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayJava, None_OneLineBlock2)
{
	// the single line block "{io.toString()}" should not be broken
	char text[] =
	    "\npublic void foo()\n"
	    "{\n"
	    "    catch (IOException io)\n"
	    "    {\n"
	    "        VFSManager.error(comp,directory,new String[]\n"
	    "                         {io.toString()});\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayJava, Break_BraceInParens)
{
	// Array braces should not pad the '( {"unchecked"})'.
	char text[] =
	    "\npublic void Foo()\n"
	    "{\n"
	    "    try\n"
	    "    {\n"
	    "        @SuppressWarnings({\"unchecked\"})\n"
	    "        t(transferable);\n"
	    "    }\n"
	    "}";
	char options[] = "style=break, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayJava, Break_OneLineBlock2)
{
	// the single line block "{io.toString()}" should not be broken
	char text[] =
	    "\npublic void foo()\n"
	    "{\n"
	    "    catch (IOException io)\n"
	    "    {\n"
	    "        VFSManager.error(comp,directory,new String[]\n"
	    "                         {io.toString()});\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=break, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayJava, Attach_BraceInParens)
{
	// Array braces should not pad the '( {"unchecked"})'.
	char text[] =
	    "\npublic void Foo() {\n"
	    "    try {\n"
	    "        @SuppressWarnings({\"unchecked\"})\n"
	    "        t(transferable);\n"
	    "    }\n"
	    "}";
	char options[] = "style=attach, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayJava, Attach_OneLineBlock2)
{
	// the single line block "{io.toString()}" should not be broken
	char text[] =
	    "\npublic void foo() {\n"
	    "    catch (IOException io) {\n"
	    "        VFSManager.error(comp,directory,new String[]\n"
	    "                         {io.toString()});\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=attach, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayJava, RunIn_BraceInParens)
{
	// Array braces should not pad the beginning brace '( {"unchecked"})'.
	char text[] =
	    "\npublic void Foo()\n"
	    "{   try\n"
	    "    {   @SuppressWarnings({\"unchecked\"})\n"
	    "        t(transferable);\n"
	    "    }\n"
	    "}";
	char options[] = "style=run-in, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayJava, RunIn_OneLineBlock2)
{
	// the single line block "{io.toString()}" should not be broken
	char text[] =
	    "\npublic void foo()\n"
	    "{   catch (IOException io)\n"
	    "    {   VFSManager.error(comp,directory,new String[]\n"
	    "                         {io.toString()});\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Java Array Brace Non-In-Statement Options
//-------------------------------------------------------------------------

TEST(BracesArrayJava, InStatementArray1)
{
	// TODO: This should be indented as an in-statement array.
	//       Why is it indented 9 spaces?
	char text[] =
	    "\nvoid LoadToc()\n"
	    "{\n"
	    "    File[] files = new File[] { new File(dir1, \"test.java\"),\n"
	    "             new File(dir2, \"test.class\"),\n"
	    "             new File(dir3, \"that.java\")\n"
	    "    };\n"
	    "}";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayJava, InStatementArray2)
{
	// TODO: This should be indented as an in-statement array.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    String footerText = jEdit.getProperty ( \"print.footerText\",\n"
	    "    new Object[] { new Date(), valueOf(pageIndex + 1)});\n"
	    "}";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayJava, InStatement_LineCommentClear)
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
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayJava, InStatement_CommentClear)
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
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------

}  // namespace
