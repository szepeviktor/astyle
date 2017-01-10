// AStyleTest_BracesSharp.cpp
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.txt describes the conditions under which this software may be distributed.

//-----------------------------------------------------------------------------
// AStyle C# Brace Options
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
// AStyle C# Brace Options
//-----------------------------------------------------------------------------

//-------------------------------------------------------------------------
// AStyle C# Default Brace Options
//-------------------------------------------------------------------------

struct BracesNoneSharpF : public Test
{
	string textStr;
	const char* textIn;

	BracesNoneSharpF()
	{
		textStr =
		    "\nnamespace FooName\n"
		    "{\n"
		    "\n"
		    "public interface FooInterface\n"
		    "{\n"
		    "    int FooGet {get; set;}\n"
		    "    void Write(string text);\n"
		    "}\n"
		    "\n"
		    "public class FooClass\n"
		    "{\n"
		    "    private bool var1;\n"
		    "    private bool var2;\n"
		    "\n"
		    "    public void foo(bool isFoo)\n"
		    "    {\n"
		    "        if (isFoo)\n"
		    "        {\n"
		    "            bar();\n"
		    "        } else {\n"
		    "            anotherBar();\n"
		    "        }\n"
		    "    }\n"
		    "}\n"
		    "}\n";
		textIn = textStr.c_str();
	}
};

TEST_F(BracesNoneSharpF, Default)
{
	// test default brackets option (do not change)
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "public interface FooInterface\n"
	    "{\n"
	    "    int FooGet {\n"
	    "        get;\n"
	    "        set;\n"
	    "    }\n"
	    "    void Write(string text);\n"
	    "}\n"
	    "\n"
	    "public class FooClass\n"
	    "{\n"
	    "    private bool var1;\n"
	    "    private bool var2;\n"
	    "\n"
	    "    public void foo(bool isFoo)\n"
	    "    {\n"
	    "        if (isFoo)\n"
	    "        {\n"
	    "            bar();\n"
	    "        } else {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesNoneSharpF, Namespace)
{
	// test default brackets option, with indented namespace
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "    public interface FooInterface\n"
	    "    {\n"
	    "        int FooGet {\n"
	    "            get;\n"
	    "            set;\n"
	    "        }\n"
	    "        void Write(string text);\n"
	    "    }\n"
	    "\n"
	    "    public class FooClass\n"
	    "    {\n"
	    "        private bool var1;\n"
	    "        private bool var2;\n"
	    "\n"
	    "        public void foo(bool isFoo)\n"
	    "        {\n"
	    "            if (isFoo)\n"
	    "            {\n"
	    "                bar();\n"
	    "            } else {\n"
	    "                anotherBar();\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent-namespaces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneSharp, EmptyBraces)
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
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneSharp, EmptyBracesWithComments)
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
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneSharp, Break)
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
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneSharp, Attach)
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
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneSharp, Linux)
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
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneSharp, RunIn)
{
	// test default brackets option with run-in brackets
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   // comment\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C# Break Brace Options
//-------------------------------------------------------------------------

struct BracesBreakSharpF : public Test
{
	string textStr;
	const char* textIn;

	BracesBreakSharpF()
	{
		textStr =
		    "\nnamespace FooName\n"
		    "{\n"
		    "\n"
		    "public interface FooInterface\n"
		    "{\n"
		    "    int FooGet {get; set;}\n"
		    "    void Write(string text);\n"
		    "}\n"
		    "\n"
		    "public class FooClass\n"
		    "{\n"
		    "    private bool var1;\n"
		    "    private bool var2;\n"
		    "\n"
		    "    public void foo(bool isFoo)\n"
		    "    {\n"
		    "        if (isFoo)\n"
		    "        {\n"
		    "            bar();\n"
		    "        } else {\n"
		    "            anotherBar();\n"
		    "        }\n"
		    "    }\n"
		    "}\n"
		    "}\n";
		textIn = textStr.c_str();
	}
};

TEST_F(BracesBreakSharpF, LongOption)
{
	// test break brackets option
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "public interface FooInterface\n"
	    "{\n"
	    "    int FooGet\n"
	    "    {\n"
	    "        get;\n"
	    "        set;\n"
	    "    }\n"
	    "    void Write(string text);\n"
	    "}\n"
	    "\n"
	    "public class FooClass\n"
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
	    "}\n"
	    "}\n";
	char options[] = "style=allman, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesBreakSharpF, ShortOption)
{
	// test break brackets short option
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "public interface FooInterface\n"
	    "{\n"
	    "    int FooGet\n"
	    "    {\n"
	    "        get;\n"
	    "        set;\n"
	    "    }\n"
	    "    void Write(string text);\n"
	    "}\n"
	    "\n"
	    "public class FooClass\n"
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
	    "}\n"
	    "}\n";
	char options[] = "-A1, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesBreakSharpF, Namespace)
{
	// test break brackets option, with indented namespace
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "    public interface FooInterface\n"
	    "    {\n"
	    "        int FooGet\n"
	    "        {\n"
	    "            get;\n"
	    "            set;\n"
	    "        }\n"
	    "        void Write(string text);\n"
	    "    }\n"
	    "\n"
	    "    public class FooClass\n"
	    "    {\n"
	    "        private bool var1;\n"
	    "        private bool var2;\n"
	    "\n"
	    "        public void foo(bool isFoo)\n"
	    "        {\n"
	    "            if (isFoo)\n"
	    "            {\n"
	    "                bar();\n"
	    "            }\n"
	    "            else\n"
	    "            {\n"
	    "                anotherBar();\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=allman, indent-namespaces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakSharp, EmptyBraces)
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
	char options[] = "style=allman, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakSharp, EmptyBracesWithComments)
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
	char options[] = "style=allman, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakSharp, Break)
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
	char options[] = "style=allman, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakSharp, Attach)
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
	char options[] = "style=allman, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakSharp, Linux)
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
	char options[] = "style=allman, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakSharp, RunIn)
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
	char options[] = "style=allman, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C# Attach Brace Options
//-------------------------------------------------------------------------

struct BracesAttachSharpF : public Test
{
	string textStr;
	const char* textIn;

	BracesAttachSharpF()
	{
		textStr =
		    "\nnamespace FooName\n"
		    "{\n"
		    "\n"
		    "public interface FooInterface\n"
		    "{\n"
		    "    int FooGet {get; set;}\n"
		    "    void Write(string text);\n"
		    "}\n"
		    "\n"
		    "public class FooClass\n"
		    "{\n"
		    "    private bool var1;\n"
		    "    private bool var2;\n"
		    "\n"
		    "    public void foo(bool isFoo)\n"
		    "    {\n"
		    "        if (isFoo)\n"
		    "        {\n"
		    "            bar();\n"
		    "        } else {\n"
		    "            anotherBar();\n"
		    "        }\n"
		    "    }\n"
		    "}\n"
		    "}\n";
		textIn = textStr.c_str();
	}
};

TEST_F(BracesAttachSharpF, LongOption)
{
	// test attach brackets option
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "public interface FooInterface {\n"
	    "    int FooGet {\n"
	    "        get;\n"
	    "        set;\n"
	    "    }\n"
	    "    void Write(string text);\n"
	    "}\n"
	    "\n"
	    "public class FooClass {\n"
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
	    "}\n"
	    "}\n";
	char options[] = "style=java, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesAttachSharpF, ShortOption)
{
	// test attach brackets short option
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "public interface FooInterface {\n"
	    "    int FooGet {\n"
	    "        get;\n"
	    "        set;\n"
	    "    }\n"
	    "    void Write(string text);\n"
	    "}\n"
	    "\n"
	    "public class FooClass {\n"
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
	    "}\n"
	    "}\n";
	char options[] = "-A2, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesAttachSharpF, Namespace)
{
	// test attach brackets option, with indented namespace
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "    public interface FooInterface {\n"
	    "        int FooGet {\n"
	    "            get;\n"
	    "            set;\n"
	    "        }\n"
	    "        void Write(string text);\n"
	    "    }\n"
	    "\n"
	    "    public class FooClass {\n"
	    "        private bool var1;\n"
	    "        private bool var2;\n"
	    "\n"
	    "        public void foo(bool isFoo) {\n"
	    "            if (isFoo) {\n"
	    "                bar();\n"
	    "            } else {\n"
	    "                anotherBar();\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java, indent-namespaces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesAttachSharpF, BreakClosing)
{
	// test attach brackets option, with break closing brackets
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "public interface FooInterface {\n"
	    "    int FooGet {\n"
	    "        get;\n"
	    "        set;\n"
	    "    }\n"
	    "    void Write(string text);\n"
	    "}\n"
	    "\n"
	    "public class FooClass {\n"
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
	    "}\n"
	    "}\n";
	char options[] = "style=java, break-closing-braces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachSharp, EmptyBraces)
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
	char options[] = "style=java, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachSharp, EmptyBracesWithComments)
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
	char options[] = "style=java, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachSharp, Break)
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
	char options[] = "style=java, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachSharp, Attach)
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
	char options[] = "style=java, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachSharp, Linux)
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
	char options[] = "style=java, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachSharp, RunIn)
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
	char options[] = "style=java, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C# Linux Brace Options
//-------------------------------------------------------------------------

struct BracesLinuxSharpF : public Test
{
	string textStr;
	const char* textIn;

	BracesLinuxSharpF()
	{
		textStr =
		    "\nnamespace FooName\n"
		    "{\n"
		    "\n"
		    "public interface FooInterface\n"
		    "{\n"
		    "    int FooGet {get; set;}\n"
		    "    void Write(string text);\n"
		    "}\n"
		    "\n"
		    "public class FooClass\n"
		    "{\n"
		    "    private bool var1;\n"
		    "    private bool var2;\n"
		    "\n"
		    "    public void foo(bool isFoo)\n"
		    "    {\n"
		    "        if (isFoo)\n"
		    "        {\n"
		    "            bar();\n"
		    "        } else {\n"
		    "            anotherBar();\n"
		    "        }\n"
		    "    }\n"
		    "}\n"
		    "}\n";
		textIn = textStr.c_str();
	}
};

TEST_F(BracesLinuxSharpF, LongOption)
{
	// test linux brackets option
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "public interface FooInterface\n"
	    "{\n"
	    "    int FooGet {\n"
	    "        get;\n"
	    "        set;\n"
	    "    }\n"
	    "    void Write(string text);\n"
	    "}\n"
	    "\n"
	    "public class FooClass\n"
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
	    "}\n"
	    "}\n";
	char options[] = "style=kr, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesLinuxSharpF, ShortOption)
{
	// test linux brackets short option
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "public interface FooInterface\n"
	    "{\n"
	    "    int FooGet {\n"
	    "        get;\n"
	    "        set;\n"
	    "    }\n"
	    "    void Write(string text);\n"
	    "}\n"
	    "\n"
	    "public class FooClass\n"
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
	    "}\n"
	    "}\n";
	char options[] = "-A3, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesLinuxSharpF, Namespace)
{
	// test linux brackets option, with indented namespace
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "    public interface FooInterface\n"
	    "    {\n"
	    "        int FooGet {\n"
	    "            get;\n"
	    "            set;\n"
	    "        }\n"
	    "        void Write(string text);\n"
	    "    }\n"
	    "\n"
	    "    public class FooClass\n"
	    "    {\n"
	    "        private bool var1;\n"
	    "        private bool var2;\n"
	    "\n"
	    "        public void foo(bool isFoo)\n"
	    "        {\n"
	    "            if (isFoo) {\n"
	    "                bar();\n"
	    "            } else {\n"
	    "                anotherBar();\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr, indent-namespaces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesLinuxSharpF, BreakClosing)
{
	// test linux brackets option, with break closing brackets
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "public interface FooInterface\n"
	    "{\n"
	    "    int FooGet {\n"
	    "        get;\n"
	    "        set;\n"
	    "    }\n"
	    "    void Write(string text);\n"
	    "}\n"
	    "\n"
	    "public class FooClass\n"
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
	    "}\n"
	    "}\n";
	char options[] = "style=kr, break-closing-braces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxSharp, EmptyBraces)
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
	char options[] = "style=kr, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxSharp, EmptyBracesWithComments)
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
	char options[] = "style=kr, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxSharp, Break)
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
	char options[] = "style=kr, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxSharp, Attach)
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
	char options[] = "style=kr, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxSharp, Linux)
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
	char options[] = "style=kr, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxSharp, RunIn)
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
	char options[] = "style=kr, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxSharp, Formatting)
{
	// test linux brackets option, for non-function top level objects
	// brackets are attached for arrays, structs, and other top level objects
	//     that are not classes or functions.
	char textIn[] =
	    "\nnamespace fooName\n"
	    "{\n"
	    "public class fooClass\n"
	    "{\n"
	    "    public struct Examination\n"
	    "    {\n"
	    "        public void setDetails(string str1, string str2)\n"
	    "        {\n"
	    "            ExamCode=str1;\n"
	    "        }\n"
	    "\n"
	    "        public string[] getdetails()\n"
	    "        {\n"
	    "            temp=new string[2];\n"
	    "            return temp;\n"
	    "        }\n"
	    "    }\n"
	    "}\n"
	    "}\n";
	char text[] =
	    "\nnamespace fooName\n"
	    "{\n"
	    "public class fooClass\n"
	    "{\n"
	    "    public struct Examination {\n"
	    "        public void setDetails(string str1, string str2)\n"
	    "        {\n"
	    "            ExamCode=str1;\n"
	    "        }\n"
	    "\n"
	    "        public string[] getdetails()\n"
	    "        {\n"
	    "            temp=new string[2];\n"
	    "            return temp;\n"
	    "        }\n"
	    "    }\n"
	    "}\n"
	    "}\n";
	char options[] = "style=kr, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxSharp, NestedNamespace)
{
	// test nested namespaces with linux brackets
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "class A\n"
	    "{\n"
	    "    namespace B\n"
	    "    {\n"
	    "    class B\n"
	    "    {\n"
	    "        namespace C\n"
	    "        {\n"
	    "        class C\n"
	    "        {\n"
	    "        }\n"
	    "        }\n"
	    "    }\n"
	    "    }\n"
	    "}\n"
	    "}\n";
	char options[] = "style=kr, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C# Stroustrup Brace Options
//-------------------------------------------------------------------------

struct BracesStroustrupSharpF : public Test
{
	string textStr;
	const char* textIn;

	BracesStroustrupSharpF()
	{
		textStr =
		    "\nnamespace FooName\n"
		    "{\n"
		    "\n"
		    "public interface FooInterface\n"
		    "{\n"
		    "    int FooGet {get; set;}\n"
		    "    void Write(string text);\n"
		    "}\n"
		    "\n"
		    "public class FooClass\n"
		    "{\n"
		    "    private bool var1;\n"
		    "    private bool var2;\n"
		    "\n"
		    "    public void foo(bool isFoo)\n"
		    "    {\n"
		    "        if (isFoo)\n"
		    "        {\n"
		    "            bar();\n"
		    "        } else {\n"
		    "            anotherBar();\n"
		    "        }\n"
		    "    }\n"
		    "}\n"
		    "}\n";
		textIn = textStr.c_str();
	}
};

TEST_F(BracesStroustrupSharpF, LongOption)
{
	// test stroustrup brackets option
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "public interface FooInterface {\n"
	    "    int FooGet {\n"
	    "        get;\n"
	    "        set;\n"
	    "    }\n"
	    "    void Write(string text);\n"
	    "}\n"
	    "\n"
	    "public class FooClass {\n"
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
	    "}\n"
	    "}\n";
	char options[] = "style=stroustrup, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesStroustrupSharpF, ShortOption)
{
	// test stroustrup brackets short option
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "public interface FooInterface {\n"
	    "    int FooGet {\n"
	    "        get;\n"
	    "        set;\n"
	    "    }\n"
	    "    void Write(string text);\n"
	    "}\n"
	    "\n"
	    "public class FooClass {\n"
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
	    "}\n"
	    "}\n";
	char options[] = "-A4, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesStroustrupSharpF, Namespace)
{
	// test stroustrup brackets option, with indented namespace
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "    public interface FooInterface {\n"
	    "        int FooGet {\n"
	    "            get;\n"
	    "            set;\n"
	    "        }\n"
	    "        void Write(string text);\n"
	    "    }\n"
	    "\n"
	    "    public class FooClass {\n"
	    "        private bool var1;\n"
	    "        private bool var2;\n"
	    "\n"
	    "        public void foo(bool isFoo)\n"
	    "        {\n"
	    "            if (isFoo) {\n"
	    "                bar();\n"
	    "            } else {\n"
	    "                anotherBar();\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=stroustrup, indent-namespaces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesStroustrupSharpF, BreakClosing)
{
	// test stroustrup brackets option with break closing brackets
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "public interface FooInterface {\n"
	    "    int FooGet {\n"
	    "        get;\n"
	    "        set;\n"
	    "    }\n"
	    "    void Write(string text);\n"
	    "}\n"
	    "\n"
	    "public class FooClass {\n"
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
	    "}\n"
	    "}\n";
	char options[] = "style=stroustrup, break-closing-braces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesStroustrupSharp, EmptyBraces)
{
	// test stroustrup brackets option
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
	char options[] = "style=stroustrup, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesStroustrupSharp, EmptyBracesWithComments)
{
	// test stroustrup brackets option with ending comments
	char textIn[] =
	    "\npublic class FooClass { //comment\n"
	    "    public FooClass() {} //comment\n"
	    "    public FooClass() { // comment\n"
	    "    }\n"
	    "    public FooClass() //comment\n"
	    "    {}\n"
	    "}\n";
	char text[] =
	    "\npublic class FooClass { //comment\n"
	    "    public FooClass() {} //comment\n"
	    "    public FooClass()   // comment\n"
	    "    {\n"
	    "    }\n"
	    "    public FooClass() //comment\n"
	    "    {}\n"
	    "}\n";
	char options[] = "style=stroustrup, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesStroustrupSharp, Formatting)
{
	// test stroustrup brackets option, for non-function top level objects
	// brackets are attached for arrays, structs, and other top level objects
	//     that are not classes or functions.
	char textIn[] =
	    "\nnamespace fooName\n"
	    "{\n"
	    "public class fooClass\n"
	    "{\n"
	    "    public struct Examination\n"
	    "    {\n"
	    "        public void setDetails(string str1, string str2)\n"
	    "        {\n"
	    "            ExamCode=str1;\n"
	    "        }\n"
	    "\n"
	    "        public string[] getdetails()\n"
	    "        {\n"
	    "            temp=new string[2];\n"
	    "            return temp;\n"
	    "        }\n"
	    "    }\n"
	    "}\n"
	    "}\n";
	char text[] =
	    "\nnamespace fooName {\n"
	    "public class fooClass {\n"
	    "    public struct Examination {\n"
	    "        public void setDetails(string str1, string str2)\n"
	    "        {\n"
	    "            ExamCode=str1;\n"
	    "        }\n"
	    "\n"
	    "        public string[] getdetails()\n"
	    "        {\n"
	    "            temp=new string[2];\n"
	    "            return temp;\n"
	    "        }\n"
	    "    }\n"
	    "}\n"
	    "}\n";
	char options[] = "style=stroustrup, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesStroustrupSharp, NestedNamespace)
{
	// test nested namespaces with stroustrup brackets
	char text[] =
	    "\nnamespace A {\n"
	    "class A {\n"
	    "    namespace B {\n"
	    "    class B {\n"
	    "        namespace C {\n"
	    "        class C {\n"
	    "        }\n"
	    "        }\n"
	    "    }\n"
	    "    }\n"
	    "}\n"
	    "}\n";
	char options[] = "style=stroustrup, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C# RunIn Brace Options
//-------------------------------------------------------------------------

struct BracesRunInSharpF : public Test
{
	string textStr;
	const char* textIn;

	BracesRunInSharpF()
	{
		textStr =
		    "\nnamespace FooName\n"
		    "{\n"
		    "\n"
		    "public interface FooInterface\n"
		    "{\n"
		    "    int FooGet {get; set;}\n"
		    "    void Write(string text);\n"
		    "}\n"
		    "\n"
		    "public class FooClass\n"
		    "{\n"
		    "    private bool var1;\n"
		    "    private bool var2;\n"
		    "\n"
		    "    public void foo(bool isFoo)\n"
		    "    {\n"
		    "        if (isFoo)\n"
		    "        {\n"
		    "            bar();\n"
		    "        } else {\n"
		    "            anotherBar();\n"
		    "        }\n"
		    "    }\n"
		    "}\n"
		    "}\n";
		textIn = textStr.c_str();
	}
};

TEST_F(BracesRunInSharpF, LongOption)
{
	// test run-in brackets option
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "public interface FooInterface\n"
	    "{   int FooGet\n"
	    "    {   get;\n"
	    "        set;\n"
	    "    }\n"
	    "    void Write(string text);\n"
	    "}\n"
	    "\n"
	    "public class FooClass\n"
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
	    "}\n"
	    "}\n";
	char options[] = "style=horstmann, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesRunInSharpF, ShortOption)
{
	// test run-in brackets short option
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "public interface FooInterface\n"
	    "{   int FooGet\n"
	    "    {   get;\n"
	    "        set;\n"
	    "    }\n"
	    "    void Write(string text);\n"
	    "}\n"
	    "\n"
	    "public class FooClass\n"
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
	    "}\n"
	    "}\n";
	char options[] = "-A9, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesRunInSharpF, Namespace)
{
	// test run-in brackets option, with indented namespace
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "    public interface FooInterface\n"
	    "    {   int FooGet\n"
	    "        {   get;\n"
	    "            set;\n"
	    "        }\n"
	    "        void Write(string text);\n"
	    "    }\n"
	    "\n"
	    "    public class FooClass\n"
	    "    {   private bool var1;\n"
	    "        private bool var2;\n"
	    "\n"
	    "        public void foo(bool isFoo)\n"
	    "        {   if (isFoo)\n"
	    "            {   bar();\n"
	    "            }\n"
	    "            else\n"
	    "            {   anotherBar();\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=horstmann, indent-namespaces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInSharp, EmptyBraces)
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
	char options[] = "style=horstmann, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInSharp, EmptyBracesWithComments)
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
	char options[] = "style=horstmann, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInSharp, Break)
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
	char options[] = "style=horstmann, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInSharp, Attach)
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
	char options[] = "style=horstmann, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInSharp, Linux)
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
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=horstmann, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInSharp, RunIn)
{
	// test break brackets option with run-in brackets
	char text[] =
	    "\npublic void Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=horstmann, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C# Other Brace Options
//-------------------------------------------------------------------------

struct BracesOtherSharpF : public Test
{
	string textStr;
	const char* textIn;

	BracesOtherSharpF()
	{
		textStr =
		    "\nnamespace FooName\n"
		    "{\n"
		    "\n"
		    "public interface FooInterface\n"
		    "{\n"
		    "    int FooGet {get; set;}\n"
		    "    void Write(string text);\n"
		    "}\n"
		    "\n"
		    "public class FooClass\n"
		    "{\n"
		    "    private bool var1;\n"
		    "    private bool var2;\n"
		    "\n"
		    "    public void foo(bool isFoo)\n"
		    "    {\n"
		    "        if (isFoo)\n"
		    "        {\n"
		    "            bar();\n"
		    "        } else {\n"
		    "            anotherBar();\n"
		    "        }\n"
		    "    }\n"
		    "}\n"
		    "}\n";
		textIn = textStr.c_str();
	}
};

TEST_F(BracesOtherSharpF, IndentClasses)
{
	// indent classes should NOT affect C# formatting
	char options[] = "indent-classes, keep-one-line-blocks, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(textIn, textOut);
	delete[] textOut;
}

TEST(BracesOtherSharp, ClassContinuation_Attached)
{
	// test with class continuation and attached brackets
	char text[] =
	    "\npublic interface Foo\n"
	    "    : Bar {\n"
	    "}\n"
	    "\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherSharp, ClassContinuation_Broken)
{
	// test with class continuation and broken brackets
	char text[] =
	    "\npublic interface Foo\n"
	    "    : Bar\n"
	    "{\n"
	    "}\n"
	    "\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherSharp, Where)
{
	// test a method that contains a where statement
	// should be recognized as a block opener
	char text[] =
	    "\nvoid SetParent<T> (List<T> list) where T : INode\n"
	    "{\n"
	    "    if (list != null)\n"
	    "    {\n"
	    "        foreach (T x in list)\n"
	    "        {\n"
	    "            x.Parent = parent;\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherSharp, WhereClass)
{
	// test a class that contains a where statement
	char text[] =
	    "\npublic sealed class Foo<A, B> : FooBar\n"
	    "    where A : Bar1\n"
	    "    where B : Bar2\n"
	    "{\n"
	    "    int a;\n"
	    "    int b;\n"
	    "\n"
	    "    protected override void Foo1()\n"
	    "    {\n"
	    "        if foo()\n"
	    "        {\n"
	    "            FooBar1();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherSharp, WhereClassClass)
{
	// test a class that contains a where statement, with two 'class' statements
	char text[] =
	    "\npublic class Foo<T> : FooBar1<T>, FooBar2\n"
	    "    where T : class\n"
	    "{\n"
	    "    Bar();\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherSharp, Accessors1)
{
	// test indent of getters and setters
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    private bool foo;\n"
	    "\n"
	    "    public bool Foo\n"
	    "    {\n"
	    "        get\n"
	    "        {\n"
	    "            return foo;\n"
	    "        }\n"
	    "        set\n"
	    "        {\n"
	    "            foo = value;\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherSharp, Accessors2)
{
	// test indent of getters and setters, with comments and empty lines
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    private bool foo;\n"
	    "\n"
	    "    public bool Foo\n"
	    "    {\n"
	    "        // comment\n"
	    "\n"
	    "        get\n"
	    "        {\n"
	    "            return foo;\n"
	    "        }\n"
	    "        set\n"
	    "        {\n"
	    "            foo = value;\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherSharp, NestedClass)
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
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherSharp, NestedNamespace)
{
	// test nested namespaces
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "namespace B\n"
	    "{\n"
	    "namespace C\n"
	    "{\n"
	    "public class fooClass\n"
	    "{\n"
	    "    void foo(bool isFoo)\n"
	    "    {\n"
	    "        if (isFoo)\n"
	    "        {\n"
	    "            bar();\n"
	    "        }\n"
	    "        else\n"
	    "            anotherBar();\n"
	    "    }\n"
	    "}\n"
	    "}\n"
	    "}\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherSharp, NestedNamespace_IndentNamespaces)
{
	// test nested indented namespaces
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "    namespace B\n"
	    "    {\n"
	    "        namespace C\n"
	    "        {\n"
	    "            public class fooClass\n"
	    "            {\n"
	    "                void foo(bool isFoo)\n"
	    "                {\n"
	    "                    if (isFoo)\n"
	    "                    {\n"
	    "                        bar();\n"
	    "                    }\n"
	    "                    else\n"
	    "                        anotherBar();\n"
	    "                }\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent-namespaces, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C# Other Brace Options
//-------------------------------------------------------------------------

//----------------------------------------------------------------------------
// C# Lambda Tests
//----------------------------------------------------------------------------

TEST(CsLambda, Standard)
{
	// C# lambda =>
	char text[] =
	    "\n[Test]\n"
	    "public void GroupTest()\n"
	    "{\n"
	    "    Action<QueryExpressionVB> constraint = expr => {\n"
	    "        Assert.IsTrue ( gv.Expression && Identifier == \"p\" );\n"
	    "        Assert.IsTrue ( bv.Expression && MemberName == \"Category\" );\n"
	    "    };\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(CsLambda, StatementAlignment)
{
	// C# lambda => with statement alignment
	char text[] =
	    "\n[Test]\n"
	    "public void GroupTest()\n"
	    "{\n"
	    "    Action<QueryExpressionVB> constraint = expr => {\n"
	    "        Assert.IsTrue ( iv.Expression &&\n"
	    "                        ( iv.Expression as IdentifierExpression ).Identifier == \"Group\" );\n"
	    "        if (vc != null)\n"
	    "        {\n"
	    "            var vertex = vertexControl.Vertex as DependencyVertex;\n"
	    "            if (vertex != null && Dependency != null)\n"
	    "                ChangeGraph(BuildDependencyGraph());\n"
	    "        }\n"
	    "    };\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(CsLambda, KeepOneLineBlocks)
{
	// C# lambda => with keep one line blocks
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    Closed += (closedSender, closedArgs) => { popup.IsOpen = false; };\n"
	    "    BeginInvoke(Background, new Action(() => { IsLoading = value; }));\n"
	    "}";
	char options[] = "keep-one-line-blocks, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(CsLambda, KeepOneLineBlocksSans)
{
	// C# lambda => without keep one line blocks
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    Closed += (closedSender, closedArgs) => { popup.IsOpen = false; };\n"
	    "    BeginInvoke(Background, new Action(() => { IsLoading = value; }));\n"
	    "}";
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    Closed += (closedSender, closedArgs) => {\n"
	    "        popup.IsOpen = false;\n"
	    "    };\n"
	    "    BeginInvoke(Background, new Action(() => {\n"
	    "        IsLoading = value;\n"
	    "    }));\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(CsLambda, LambdaInParen)
{
	// C# lambda => with lambda in paren
	char textIn[] =
	    "\nprivate ObjectGraphNode getExistingNodeForValue(Value value)\n"
	    "{\n"
	    "    ObjectGraphNode nodeWithSameAddress = nodesWithSameHashCode.Find(\n"
	    "            node => { return node.GetObjectAddress() == objectAddress; } );\n"
	    "    return nodeWithSameAddress;\n"
	    "}";
	char text[] =
	    "\nprivate ObjectGraphNode getExistingNodeForValue(Value value)\n"
	    "{\n"
	    "    ObjectGraphNode nodeWithSameAddress = nodesWithSameHashCode.Find(\n"
	    "    node => {\n"
	    "        return node.GetObjectAddress() == objectAddress;\n"
	    "    } );\n"
	    "    return nodeWithSameAddress;\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(CsLambda, LambdaInParenKeepOneLineBlocks)
{
	// C# lambda => with lambda in paren with keep one line blocks
	char text[] =
	    "\nprivate ObjectGraphNode getExistingNodeForValue(Value value)\n"
	    "{\n"
	    "    ObjectGraphNode nodeWithSameAddress = nodesWithSameHashCode.Find(\n"
	    "    node => { return node.GetObjectAddress() == objectAddress; } );\n"
	    "    return nodeWithSameAddress;\n"
	    "}";
	char options[] = "keep-one-line-blocks, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(CsLambda, Delegate)
{
	// C# lambda => with delegate, indent=tab to test continuation line formatting
	// TODO: doesn't work, delegate is not indented
	char textIn[] =
	    "\nvoid LoadData()\n"
	    "{\n"
	    "	task.Execute(() => LoadWorker(rangeStart, rangeEnd),\n"
	    "	             list => LoadCompleted(list, layer),\n"
	    "	             delegate { layer.Remove(ad); });\n"
	    "}";
	char text[] =
	    "\nvoid LoadData()\n"
	    "{\n"
	    "	task.Execute(() => LoadWorker(rangeStart, rangeEnd),\n"
	    "	             list => LoadCompleted(list, layer),\n"
	    "	delegate {\n"
	    "		layer.Remove(ad);\n"
	    "	});\n"
	    "}";
	char options[] = "indent=tab, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(CsLambda, DelegateKeepOneLineBlocks)
{
	// C# lambda => with delegate with keep one line blocks,
	// indent=tab to test continuation line formatting
	char text[] =
	    "\nvoid LoadData()\n"
	    "{\n"
	    "	task.Execute(() => LoadWorker(rangeStart, rangeEnd),\n"
	    "	             list => LoadCompleted(list, layer),\n"
	    "	             delegate { layer.Remove(ad); });\n"
	    "}";
	char options[] = "indent=tab, keep-one-line-blocks, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(CsLambda, Indent1)
{
	// C# lambda test
	char text[] =
	    "\nprivate void Foo()\n"
	    "{\n"
	    "    worker.DoWork += (source, args) => MetricsReader = new MetricsReader(fileDialog.FileName);\n"
	    "    worker.RunWorkerCompleted += (source, args) => {\n"
	    "        progressBar.Visibility = Visibility.Hidden;\n"
	    "        assemblyStats.Visibility = Visibility.Visible;\n"
	    "        FillMatrix();\n"
	    "    };\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(CsLambda, Indent2)
{
	// C# lambda test
	// TODO: doesn't work, should be indented like testIn
	char textIn[] =
	    "\nvoid UpdateErrorList(IEnumerable<CompilerError> errors)\n"
	    "{\n"
	    "    Dispatcher.Invoke(\n"
	    "        (Action)(\n"
	    "            () =>\n"
	    "            {\n"
	    "                var tasks = errors.Select(error => new Task()).ToList();\n"
	    "                if (tasks.Count > 0)\n"
	    "                {\n"
	    "                    TaskService.ClearExceptCommentTasks();\n"
	    "                    TaskService.AddRange(tasks);\n"
	    "                }\n"
	    "            }\n"
	    "        )\n"
	    "    );\n"
	    "}";
	char text[] =
	    "\nvoid UpdateErrorList(IEnumerable<CompilerError> errors)\n"
	    "{\n"
	    "    Dispatcher.Invoke(\n"
	    "        (Action)(\n"
	    "            () =>\n"
	    "    {\n"
	    "        var tasks = errors.Select(error => new Task()).ToList();\n"
	    "        if (tasks.Count > 0)\n"
	    "        {\n"
	    "            TaskService.ClearExceptCommentTasks();\n"
	    "            TaskService.AddRange(tasks);\n"
	    "        }\n"
	    "    }\n"
	    "        )\n"
	    "    );\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(CsLambda, Indent3)
{
	// C# lambda test
	char text[] =
	    "\npublic void TestEmptyFile()\n"
	    "{\n"
	    "    TestKeyPress('o', CodeCompletion.CompletedInclude,\n"
	    "                 list =>\n"
	    "    {\n"
	    "        Assert.IsTrue(Items.All(item => item.Image == Keyword));\n"
	    "        ContainsAll(Items.Select(item => item.Text).ToArray(),\n"
	    "                    \"Shadows\", \"Structure\", \"Interface\");\n"
	    "    }\n"
	    "                );\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(CsLambda, Set)
{
	// test Lambda in Set
	char text[] =
	    "\npublic IEnumerable<DesignItem> SelectedItems {\n"
	    "    set {\n"
	    "        Current.Begin(new Action(delegate {\n"
	    "            selectedItems = value;\n"
	    "        }), DispatcherPriority.Background);\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "static CodeType CreateNode(List<Type> nodeTypes) {\n"
	    "    m.Add(new xx(new yy(new zz(), \"Begin\"), new aaa[] { var }));\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherSharp, NewOperator)
{
	// test new operator ending with })
	char text[] =
	    "\npublic ResolveResult ResolveIdentifier(string identifier)\n"
	    "{\n"
	    "    return Identifier(new IdentifierExpression(identifier) {\n"
	    "        StartLocation = position\n"
	    "    }, context);\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherSharp, NewOperatorDelegate)
{
	// Test new operator ending with }) that contains a delegate block.
	// C# does a full indent of brackets within a paren.
	// TODO: doesn't work, should be indented like textIn
	char textIn[] =
	    "\nstatic void Parse(string fileName, string fileContent)\n"
	    "{\n"
	    "    Module module = BooParser(4, new CompileUnit(), fileName,\n"
	    "                              new StringReader(fileContent),\n"
	    "                              delegate(RecognitionException e) {\n"
	    "                                  AppendLine(e.ToString());\n"
	    "                              });\n"
	    "}\n";
	char text[] =
	    "\nstatic void Parse(string fileName, string fileContent)\n"
	    "{\n"
	    "    Module module = BooParser(4, new CompileUnit(), fileName,\n"
	    "                              new StringReader(fileContent),\n"
	    "    delegate(RecognitionException e) {\n"
	    "        AppendLine(e.ToString());\n"
	    "    });\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesOtherSharp, ReturnStatement)
{
	// test return statement ending with };
	// }; should not have an in-statement indent.
	char text[] =
	    "\npublic IViewContent CreateContentForFile(OpenedFile file)\n"
	    "{\n"
	    "    return new SimpleViewContent(errorMessage) {\n"
	    "        TitleName = Path.GetFileName(file.FileName)\n"
	    "    };\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C# Array Brace Options
//-------------------------------------------------------------------------

TEST(BracesArraySharp, None_Comments)
{
	// comments preceding array entries should NOT break the line
	char text[] =
	    "\nstatic readonly\n"
	    "int[][] _stateTable =             { // 0    1    2    3    4\n"
	    "    /* 0: in Code       */ new int[] { 1,   7,   0,   0,   0 },\n"
	    "    /* 1: after quote   */ new int[] { 2,   6,   10,  0,   8 },\n"
	    "    /* 2: after d-quote */ new int[] { 3,   7,   0,   0,   0 }\n"
	    "};\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArraySharp, None_Misc1)
{
	// The following unusual C# array was badly formatted.
	// It could be better but this is an improvement over what it was.
	char textIn[] =
	    "\nprivate static readonly SplashIdMapping[] SplashIdMappings = {\n"
	    "    new SplashIdMapping(\"Bank Accts\", PwIcon.Homebanking,\n"
	    "        new string[]{ PwDefs.TitleField, \"Account #\", PwDefs.PasswordField,\n"
	    "            PwDefs.UserNameField, \"Branch\", \"Phone #\" }),\n"
	    "    new SplashIdMapping(\"Birthdays\", PwIcon.UserCommunication,\n"
	    "        new string[]{ PwDefs.TitleField, \"Date\" }),\n"
	    "    new SplashIdMapping(\"Calling Cards\", PwIcon.EMail,\n"
	    "        new string[]{ PwDefs.TitleField, PwDefs.UserNameField,\n"
	    "            PwDefs.PasswordField }),\n"
	    "};";
	char text[] =
	    "\nprivate static readonly SplashIdMapping[] SplashIdMappings = {\n"
	    "    new SplashIdMapping(\"Bank Accts\", PwIcon.Homebanking,\n"
	    "    new string[]{\n"
	    "        PwDefs.TitleField, \"Account #\", PwDefs.PasswordField,\n"
	    "        PwDefs.UserNameField, \"Branch\", \"Phone #\"\n"
	    "    }),\n"
	    "    new SplashIdMapping(\"Birthdays\", PwIcon.UserCommunication,\n"
	    "    new string[]{ PwDefs.TitleField, \"Date\" }),\n"
	    "    new SplashIdMapping(\"Calling Cards\", PwIcon.EMail,\n"
	    "    new string[]{\n"
	    "        PwDefs.TitleField, PwDefs.UserNameField,\n"
	    "        PwDefs.PasswordField\n"
	    "    }),\n"
	    "};";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArraySharp, Break_Comments)
{
	// comments preceding array entries should NOT break the line
	char text[] =
	    "\nstatic readonly\n"
	    "int[][] _stateTable =               // 0    1    2    3    4\n"
	    "{\n"
	    "    /* 0: in Code       */ new int[] { 1,   7,   0,   0,   0 },\n"
	    "    /* 1: after quote   */ new int[] { 2,   6,   10,  0,   8 },\n"
	    "    /* 2: after d-quote */ new int[] { 3,   7,   0,   0,   0 }\n"
	    "};\n";
	char options[] = "style=allman, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArraySharp, Break_Misc1)
{
	// The following unusual C# array was badly formatted.
	// It could be better but this is an improvement over what it was.
	char textIn[] =
	    "\nprivate static readonly SplashIdMapping[] SplashIdMappings = {\n"
	    "    new SplashIdMapping(\"Bank Accts\", PwIcon.Homebanking,\n"
	    "        new string[]{ PwDefs.TitleField, \"Account #\", PwDefs.PasswordField,\n"
	    "            PwDefs.UserNameField, \"Branch\", \"Phone #\" }),\n"
	    "    new SplashIdMapping(\"Birthdays\", PwIcon.UserCommunication,\n"
	    "        new string[]{ PwDefs.TitleField, \"Date\" }),\n"
	    "    new SplashIdMapping(\"Calling Cards\", PwIcon.EMail,\n"
	    "        new string[]{ PwDefs.TitleField, PwDefs.UserNameField,\n"
	    "            PwDefs.PasswordField }),\n"
	    "};";
	char text[] =
	    "\nprivate static readonly SplashIdMapping[] SplashIdMappings =\n"
	    "{\n"
	    "    new SplashIdMapping(\"Bank Accts\", PwIcon.Homebanking,\n"
	    "    new string[]{\n"
	    "        PwDefs.TitleField, \"Account #\", PwDefs.PasswordField,\n"
	    "        PwDefs.UserNameField, \"Branch\", \"Phone #\"\n"
	    "    }),\n"
	    "    new SplashIdMapping(\"Birthdays\", PwIcon.UserCommunication,\n"
	    "    new string[]{ PwDefs.TitleField, \"Date\" }),\n"
	    "    new SplashIdMapping(\"Calling Cards\", PwIcon.EMail,\n"
	    "    new string[]{\n"
	    "        PwDefs.TitleField, PwDefs.UserNameField,\n"
	    "        PwDefs.PasswordField\n"
	    "    }),\n"
	    "};";
	char options[] = "style=allman, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArraySharp, Attach_Comments)
{
	// comments preceding array entries should NOT break the line
	char text[] =
	    "\nstatic readonly\n"
	    "int[][] _stateTable =             { // 0    1    2    3    4\n"
	    "    /* 0: in Code       */ new int[] { 1,   7,   0,   0,   0 },\n"
	    "    /* 1: after quote   */ new int[] { 2,   6,   10,  0,   8 },\n"
	    "    /* 2: after d-quote */ new int[] { 3,   7,   0,   0,   0 }\n"
	    "};\n";
	char options[] = "style=java, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArraySharp, Attach_Misc1)
{
	// The following unusual C# array was badly formatted.
	// It could be better but this is an improvement over what it was.
	char textIn[] =
	    "\nprivate static readonly SplashIdMapping[] SplashIdMappings =\n"
	    "{\n"
	    "    new SplashIdMapping(\"Bank Accts\", PwIcon.Homebanking,\n"
	    "        new string[]{ PwDefs.TitleField, \"Account #\", PwDefs.PasswordField,\n"
	    "            PwDefs.UserNameField, \"Branch\", \"Phone #\" }),\n"
	    "    new SplashIdMapping(\"Birthdays\", PwIcon.UserCommunication,\n"
	    "        new string[]{ PwDefs.TitleField, \"Date\" }),\n"
	    "    new SplashIdMapping(\"Calling Cards\", PwIcon.EMail,\n"
	    "        new string[]{ PwDefs.TitleField, PwDefs.UserNameField,\n"
	    "            PwDefs.PasswordField }),\n"
	    "};";
	char text[] =
	    "\nprivate static readonly SplashIdMapping[] SplashIdMappings = {\n"
	    "    new SplashIdMapping(\"Bank Accts\", PwIcon.Homebanking,\n"
	    "    new string[]{\n"
	    "        PwDefs.TitleField, \"Account #\", PwDefs.PasswordField,\n"
	    "        PwDefs.UserNameField, \"Branch\", \"Phone #\"\n"
	    "    }),\n"
	    "    new SplashIdMapping(\"Birthdays\", PwIcon.UserCommunication,\n"
	    "    new string[]{ PwDefs.TitleField, \"Date\" }),\n"
	    "    new SplashIdMapping(\"Calling Cards\", PwIcon.EMail,\n"
	    "    new string[]{\n"
	    "        PwDefs.TitleField, PwDefs.UserNameField,\n"
	    "        PwDefs.PasswordField\n"
	    "    }),\n"
	    "};";
	char options[] = "style=java, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArraySharp, RunIn_Comments)
{
	// comments preceding array entries should NOT break the line
	char text[] =
	    "\nstatic readonly\n"
	    "int[][] _stateTable =               // 0    1    2    3    4\n"
	    "{   /* 0: in Code       */ new int[] { 1,   7,   0,   0,   0 },\n"
	    "    /* 1: after quote   */ new int[] { 2,   6,   10,  0,   8 },\n"
	    "    /* 2: after d-quote */ new int[] { 3,   7,   0,   0,   0 }\n"
	    "};\n";
	char options[] = "style=horstmann, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArraySharp, RunIn_Misc1)
{
	// The following unusual C# array was badly formatted.
	// It could be better but this is an improvement over what it was.
	char textIn[] =
	    "\nprivate static readonly SplashIdMapping[] SplashIdMappings = {\n"
	    "    new SplashIdMapping(\"Bank Accts\", PwIcon.Homebanking,\n"
	    "        new string[]{ PwDefs.TitleField, \"Account #\", PwDefs.PasswordField,\n"
	    "            PwDefs.UserNameField, \"Branch\", \"Phone #\" }),\n"
	    "    new SplashIdMapping(\"Birthdays\", PwIcon.UserCommunication,\n"
	    "        new string[]{ PwDefs.TitleField, \"Date\" }),\n"
	    "    new SplashIdMapping(\"Calling Cards\", PwIcon.EMail,\n"
	    "        new string[]{ PwDefs.TitleField, PwDefs.UserNameField,\n"
	    "            PwDefs.PasswordField }),\n"
	    "};";
	char text[] =
	    "\nprivate static readonly SplashIdMapping[] SplashIdMappings =\n"
	    "{   new SplashIdMapping(\"Bank Accts\", PwIcon.Homebanking,\n"
	    "    new string[]{ PwDefs.TitleField, \"Account #\", PwDefs.PasswordField,\n"
	    "        PwDefs.UserNameField, \"Branch\", \"Phone #\"\n"
	    "    }),\n"
	    "    new SplashIdMapping(\"Birthdays\", PwIcon.UserCommunication,\n"
	    "    new string[]{ PwDefs.TitleField, \"Date\" }),\n"
	    "    new SplashIdMapping(\"Calling Cards\", PwIcon.EMail,\n"
	    "    new string[]{ PwDefs.TitleField, PwDefs.UserNameField,\n"
	    "        PwDefs.PasswordField\n"
	    "    }),\n"
	    "};";
	char options[] = "style=horstmann, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArraySharp, Enum)
{
	// test enum formatting
	// the enum bracket should be space padded and should not be broken
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    enum SQGeneratorState{ eRunning, eSuspended, eDead };\n"
	    "};\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    enum SQGeneratorState { eRunning, eSuspended, eDead };\n"
	    "};\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C# Array Brace Non-In-Statement Options
// Currently with C# some commands are handled as non-in-statement arrays
//-------------------------------------------------------------------------

TEST(BracesArraySharp, InStatementIndentWithParenLineBegin)
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
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArraySharp, Clear_NonInStatementArray2)
{
	// The isNonInStatementArray should be cleared before brackets are added.
	// If not cleared the CreateDirectory line is wrong.
	char textIn[] =
	    "\npublic void CreateEntry()\n"
	    "{\n"
	    "    workspaceItem.Name = StringParser(new string[,] {{SolutionName}});\n"
	    "    if (!Directory.Exists(SolutionPath))\n"
	    "        CreateDirectory(SolutionPath);\n"
	    "}";
	char text[] =
	    "\npublic void CreateEntry()\n"
	    "{\n"
	    "    workspaceItem.Name = StringParser(new string[,] {{SolutionName}});\n"
	    "    if (!Directory.Exists(SolutionPath)) {\n"
	    "        CreateDirectory(SolutionPath);\n"
	    "    }\n"
	    "}";
	char options[] = "add-braces, keep-one-line-blocks, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArraySharp, Clear_NonInStatementArray3)
{
	// The isNonInStatementArray should be cleared before brackets are added.
	// If not cleared the final in-statement indent will be wrong.
	char text[] =
	    "\nstatic void LoadProjectInternal()\n"
	    "{\n"
	    "    string[,] parseArgs = {{solutionFile}, {fileName}};\n"
	    "    int res = ShowCustomDialog(MessageService.ProductName,\n"
	    "                               StringParser.Parse(parseArgs1),\n"
	    "                               0, 2);\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArraySharp, Clear_NonInStatementArray4)
{
	// The isNonInStatementArray should be cleared before brackets are added.
	// If not cleared the last two lines will be wrong.
	char text[] =
	    "\nstatic void NeedsToClear()\n"
	    "{\n"
	    "    Message.Show(Parse(new string[,] {{ count.ToString() }}));\n"
	    "    MessageBox.Show(WorkbenchSingleton.MainWin32Window,\n"
	    "                    MessageBoxButtons.OK,\n"
	    "                    MessageBoxIcon.Information);\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------

}  // namespace
