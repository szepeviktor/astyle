// AStyleTest_BracesJava.cpp
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.txt describes the conditions under which this software may be distributed.

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
	// test default brackets option (do not change)
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
	// test default brackets option (do not change)
	// do not change empty brackets
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
	// test default brackets option (do not change) with ending comments
	// do not change empty brackets
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
	// test default brackets option with broken brackets
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
	// test default brackets option with attached brackets
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
	// test default brackets option with linux brackets
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
	// test default brackets option with run-in brackets
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
	// test default brackets option with an enum constructor
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
	// test default brackets option with an enum constructor
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
	// test default brackets option with an enum constructor
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
	// test break brackets option
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
	char options[] = "style=allman, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesBreakJavaF, ShortOption)
{
	// test break brackets short option
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
	// test break brackets option
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
	char options[] = "style=allman, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakJava, EmptyBracesWithComments)
{
	// test break brackets option with ending comments
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
	char options[] = "style=allman, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakJava, Break)
{
	// test break brackets option with broken brackets
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
	char options[] = "style=allman, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakJava, Attach)
{
	// test break brackets option with attached brackets
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
	char options[] = "style=allman, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakJava, Linux)
{
	// test break brackets option with linux brackets
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
	char options[] = "style=allman, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakJava, RunIn)
{
	// test break brackets option with run-in brackets
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
	char options[] = "style=allman, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakJava, EnumConstructor)
{
	// test break brackets option with an enum constructor
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
	char options[] = "style=allman, mode=java";
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
	// test attach brackets option
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
	char options[] = "style=java, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesAttachJavaF, ShortOption)
{
	// test attach brackets short option
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
	// test attach brackets option, with break closing brackets
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
	char options[] = "style=java, break-closing-braces, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachJava, EmptyBraces)
{
	// test attach brackets option
	char text[] =
	    "\npublic class FooClass {\n"
	    "    public FooClass() {}\n"
	    "    public FooClass() {\n"
	    "    }\n"
	    "    public FooClass()\n"
	    "    {}\n"
	    "}\n";
	char options[] = "style=java, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachJava, EmptyBracesWithComments)
{
	// test attach brackets option with ending comments
	char text[] =
	    "\npublic class FooClass { // comment\n"
	    "    public FooClass() {} // comment\n"
	    "    public FooClass() { // comment\n"
	    "    }\n"
	    "    public FooClass() // comment\n"
	    "    {}\n"
	    "}\n";
	char options[] = "style=java, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachJava, Break)
{
	// test attach brackets option with broken brackets
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
	char options[] = "style=java, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachJava, Attach)
{
	// test attach brackets option with attached brackets
	char text[] =
	    "\npublic void Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachJava, Linux)
{
	// test attach brackets option with linux brackets
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
	char options[] = "style=java, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachJava, RunIn)
{
	// test attach brackets option with run-in brackets
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
	char options[] = "style=java, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachJava, EnumConstructor)
{
	// test attach brackets option with an enum constructor
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
	char options[] = "style=java, mode=java";
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
	// test linux brackets option
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
	// test linux brackets short option
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
	// test linux brackets option, with break closing brackets
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
	// test linux brackets option
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
	// test linux brackets option with ending comments
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
	// test linux brackets option with broken brackets
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
	// test linux brackets option with attached brackets
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
	// test linux brackets option with linux brackets
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
	// test linux brackets option with run-in brackets
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
	// test linux brackets option with an enum constructor
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
// AStyle Java Stroustrup Brace Options
//-------------------------------------------------------------------------

struct BracesStroustrupJavaF : public Test
{
	string textStr;
	const char* textIn;

	BracesStroustrupJavaF()
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

TEST_F(BracesStroustrupJavaF, LongOption)
{
	// test stroustrup brackets option
	char text[] =
	    "\npublic class FooClass {\n"
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
	char options[] = "style=stroustrup, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesStroustrupJavaF, ShortOption)
{
	// test stroustrup brackets short option
	char text[] =
	    "\npublic class FooClass {\n"
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
	char options[] = "-A4, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesStroustrupJavaF, BreakClosing)
{
	// test stroustrup brackets option, with break closing brackets
	char text[] =
	    "\npublic class FooClass {\n"
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
	char options[] = "style=stroustrup, break-closing-braces, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesStroustrupJava, EmptyBraces)
{
	// test stroustrup brackets option
	// do not change empty brackets
	char textIn[] =
	    "\npublic class FooClass {\n"
	    "    public FooClass() {}\n"
	    "    public FooClass() {\n"
	    "    }\n"
	    "    public FooClass()\n"
	    "    {}\n"
	    "}\n";
	char text[] =
	    "\npublic class FooClass {\n"
	    "    public FooClass() {}\n"
	    "    public FooClass()\n"
	    "    {\n"
	    "    }\n"
	    "    public FooClass()\n"
	    "    {}\n"
	    "}\n";
	char options[] = "style=stroustrup, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesStroustrupJava, EmptyBracesWithComments)
{
	// test stroustrup brackets option with ending comments
	// do not change empty brackets
	char textIn[] =
	    "\npublic class FooClass { // comment\n"
	    "    public FooClass() {} // comment\n"
	    "    public FooClass() { // comment\n"
	    "    }\n"
	    "    public FooClass() // comment\n"
	    "    {}\n"
	    "}\n";
	char text[] =
	    "\npublic class FooClass { // comment\n"
	    "    public FooClass() {} // comment\n"
	    "    public FooClass()   // comment\n"
	    "    {\n"
	    "    }\n"
	    "    public FooClass() // comment\n"
	    "    {}\n"
	    "}\n";
	char options[] = "style=stroustrup, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesStroustrupJava, EnumConstructor)
{
	// test stroustrup brackets option with an enum constructor
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
	char options[] = "style=stroustrup, mode=java";
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
	// test run-in brackets option
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
	char options[] = "style=horstmann, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesRunInJavaF, ShortOption)
{
	// test run-in brackets short option
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
	// test run-in brackets option
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
	char options[] = "style=horstmann, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInJava, EmptyBracesWithComments)
{
	// test run-in brackets option with ending comments
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
	char options[] = "style=horstmann, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInJava, Break)
{
	// test run-in brackets option with broken brackets
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
	char options[] = "style=horstmann, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInJava, Attach)
{
	// test run-in brackets option with attached brackets
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
	char options[] = "style=horstmann, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInJava, Linux)
{
	// test run-in brackets option with linux brackets
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
	char options[] = "style=horstmann, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInJava, RunIn)
{
	// test run-in brackets option with run-in brackets
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=horstmann, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInJava, EnumConstructor)
{
	// test run-in brackets option with an enum constructor
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
	char options[] = "style=horstmann, mode=java";
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
	// test with class continuation and attached brackets
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
	// test with class continuation and broken brackets
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
	// test default brackets option (do not change)
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
	// Array brackets should not pad the '( {"unchecked"})'.
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
	// Array brackets should not pad the '( {"unchecked"})'.
	char text[] =
	    "\npublic void Foo()\n"
	    "{\n"
	    "    try\n"
	    "    {\n"
	    "        @SuppressWarnings({\"unchecked\"})\n"
	    "        t(transferable);\n"
	    "    }\n"
	    "}";
	char options[] = "style=allman, mode=java";
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
	char options[] = "style=allman, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayJava, Attach_BraceInParens)
{
	// Array brackets should not pad the '( {"unchecked"})'.
	char text[] =
	    "\npublic void Foo() {\n"
	    "    try {\n"
	    "        @SuppressWarnings({\"unchecked\"})\n"
	    "        t(transferable);\n"
	    "    }\n"
	    "}";
	char options[] = "style=java, mode=java";
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
	char options[] = "style=java, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayJava, RunIn_BraceInParens)
{
	// Array brackets should not pad the beginning bracket '( {"unchecked"})'.
	char text[] =
	    "\npublic void Foo()\n"
	    "{   try\n"
	    "    {   @SuppressWarnings({\"unchecked\"})\n"
	    "        t(transferable);\n"
	    "    }\n"
	    "}";
	char options[] = "style=horstmann, mode=java";
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
	char options[] = "style=horstmann, mode=java";
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
