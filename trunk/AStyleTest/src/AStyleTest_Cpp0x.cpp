// AStyleTest_C++0x.cpp
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
//----------------------------------------------------------------------------
// AStyle C++11 Standard
//----------------------------------------------------------------------------

TEST(Cpp11Standard, NoExceptInClass)
{
	// Class indentation of C++11 'noexcept'.
	// The colon should not unindent the line.
	char text[] =
	    "\nclass Foo\n"
	    "{\n"
	    "    int _x, _y;\n"
	    "    Foo(int x, int y) noexcept :\n"
	    "        _x(x), _y(y) {};\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Standard, NoExceptInIndentedClass)
{
	// Class indentation of C++11 'noexcept' with an indented class.
	// The colon should not unindent the line.
	char text[] =
	    "\nclass Foo\n"
	    "{\n"
	    "    private:\n"
	    "        int _x, _y;\n"
	    "        Foo(int x, int y) noexcept :\n"
	    "            _x(x), _y(y) {};\n"
	    "};";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Standard, RangeBasedForLoop1)
{
	// range-based for loop
	// the colon should not unindent the line
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    for (auto it : s) {\n"
	    "        int i = it;\n"
	    "        printf (\"%d\", i);\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Standard, RangeBasedForLoop2)
{
	// range-based for loop
	// the colon should not unindent the line
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    for (auto it : s)\n"
	    "        int i = it;\n"
	    "    printf (\"%d\", i);\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Standard, RangeBasedForLoop3)
{
	// range-based for loop with pad-oper
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    for (auto it:s)\n"
	    "        int i = it;\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    for (auto it : s)\n"
	    "        int i = it;\n"
	    "}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Standard, RangeBasedForLoop4)
{
	// range-based for loop with a reference and pad-oper
	// reference should not be padded
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    for (auto& it : s)\n"
	    "        auto i = it;\n"
	    "}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Standard, RangeBasedForLoop5)
{
	// range-based for loop with a pointer and pad-oper
	// pointer should not be padded
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    for (auto* it : s)\n"
	    "        auto i = it;\n"
	    "}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Standard, EnumWithBaseType1)
{
	// enum with a base-type
	// the colon should not unindent the line
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    enum foo:int { ... };\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Standard, EnumWithBaseType2)
{
	// enum with a base-type formatted with pad-oper
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    enum foo:int { ... };\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    enum foo : int { ... };\n"
	    "}\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Standard, EnumClass)
{
	// enum class should be recognized as an 'enum', not a 'class'
	// enum class should be recognized as a brace opener in ASBeautifier
	char textIn[] =
	    "\nenum class test {\n"
	    "test1 = 1,\n"
	    "test2 = 2\n"
	    "};\n";
	char text[] =
	    "\nenum class test\n"
	    "{\n"
	    "	test1 = 1,\n"
	    "	test2 = 2\n"
	    "};\n";
	char options[] = "style=break, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Standard, EnumClassWithBaseType1)
{
	// enum class should be recognized as an 'enum', not a 'class'
	// enum class should be recognized as a brace opener in ASBeautifier
	char textIn[] =
	    "\nenum class test : unsigned long\n"
	    "{\n"
	    "test1 = 1,\n"
	    "test2 = 2\n"
	    "};\n";
	char text[] =
	    "\nenum class test : unsigned long {\n"
	    "	test1 = 1,\n"
	    "	test2 = 2\n"
	    "};\n";
	char options[] = "style=attach, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Standard, EnumClassWithBaseType2)
{
	// enum class should be recognized as an 'enum', not a 'class'
	// enum class should be recognized as a brace opener in ASBeautifier
	char textIn[] =
	    "\nenum class test\n"
	    ": unsigned long\n"
	    "{\n"
	    "test1 = 1,\n"
	    "test2 = 2\n"
	    "};\n";
	char text[] =
	    "\nenum class test\n"
	    "	: unsigned long {\n"
	    "	test1 = 1,\n"
	    "	test2 = 2\n"
	    "};\n";
	char options[] = "style=kr, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Standard, EnumClassWithBaseType3)
{
	// enum class should be recognized as an 'enum', not a 'class'
	// enum class should be recognized as a brace opener in ASBeautifier
	char textIn[] =
	    "\nenum class test :\n"
	    "unsigned long {\n"
	    "test1 = 1,\n"
	    "test2 = 2\n"
	    "};\n";
	char text[] =
	    "\nenum class test :\n"
	    "	unsigned long\n"
	    "{\n"
	    "	test1 = 1,\n"
	    "	test2 = 2\n"
	    "};\n";
	char options[] = "style=vtk, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle C++11 Uniform Initializer
//----------------------------------------------------------------------------

TEST(Cpp11Initializer, UniformInitializerNone)
{
	// test uniform initializers with none braces
	// the uniform initializer brace should NOT be space padded
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    int j_one{ wrap(j + 1, x.size()) };\n"
	    "    for (int j{ 0 }; j < x.size(); j++) {}\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerAttach)
{
	// test uniform initializers with attached braces
	// the uniform initializer brace should NOT be space padded
	char text[] =
	    "\nvoid foo() {\n"
	    "    int j_one{ wrap(j + 1, x.size()) };\n"
	    "    for (int j{ 0 }; j < x.size(); j++) {}\n"
	    "}";
	char options[] = "style=attach";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerBreak)
{
	// test uniform initializers with broken braces
	// the uniform initializer brace should NOT be space padded
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    int j_one{ wrap(j + 1, x.size()) };\n"
	    "    for (int j{ 0 }; j < x.size(); j++) {}\n"
	    "}";
	char options[] = "style=break";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerRunIn)
{
	// test uniform initializers with run-in braces
	// the uniform initializer brace should NOT be space padded
	char text[] =
	    "\nvoid foo()\n"
	    "{   int j_one{ wrap(j + 1, x.size()) };\n"
	    "    for (int j{ 0 }; j < x.size(); j++) {}\n"
	    "}";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerConst1)
{
	// The uniform initializer should be identified as an array-type.
	// The 'const' keyword should not cause it to be a command-type
	// which will break the braces.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    const string separator{ \" - \" };\n"
	    "    static const string separator{ \" - \" };\n"
	    "    const static string separator{ \" - \" };\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerConst2)
{
	// The uniform initializer should be identified as an array-type.
	// The 'const' keyword should not cause it to be a command-type
	// which will break the braces.
	char text[] =
	    "\nusing Container = std::vector<std::pair<int, int>>;\n"
	    "\n"
	    "const Container c1 { {0, 0} };\n"
	    "Container const c2 { {0, 0} };\n"
	    "\n"
	    "volatile Container c1 { {0, 0} };\n"
	    "Container volatile c2 { {0, 0} };\n"
	    "\n"
	    "const Container c3 ( { {0, 0} } );\n"
	    "Container const c4 ( { {0, 0} } );\n";
	char options[] = "style=break";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerMisc1)
{
	// The uniform initializer should be identified as an array-type.
	// The opening brace should not be automatically space padded.
	// The closing brace should not be automatically broken from the line.
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    vector<int> x{ 0,\n"
	    "                   1,\n"
	    "                   2 }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerClassInitializerNone)
{
	// The uniform initializer in a class initializer is an array-type.
	// The opening command type brace should be correctly identified.
	// This type is for default braces.
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : bar{0}\n"
	    "{\n"
	    "    foo(a,\n"
	    "        b);\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerClassInitializerBreak)
{
	// The uniform initializer in a class initializer is an array-type.
	// The opening command type brace should be correctly identified.
	// This type is for broken braces.
	char textIn[] =
	    "\nFoo::Foo()\n"
	    "    : bar{0} {\n"
	    "    foo(a,\n"
	    "        b);\n"
	    "}";
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : bar{0}\n"
	    "{\n"
	    "    foo(a,\n"
	    "        b);\n"
	    "}";

	char options[] = "style=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerClassInitializerAttach)
{
	// The uniform initializer in a class initializer is an array-type.
	// The opening command type brace should be correctly identified.
	// This type is for attached braces.
	char textIn[] =
	    "\nFoo::Foo()\n"
	    "    : bar{0}\n"
	    "{\n"
	    "    foo(a,\n"
	    "        b);\n"
	    "}";
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : bar{0} {\n"
	    "    foo(a,\n"
	    "        b);\n"
	    "}";
	char options[] = "style=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerClassInitializerLinux)
{
	// The uniform initializer in a class initializer is an array-type.
	// The opening command type brace should be correctly identified.
	// This type is for linux braces.
	char textIn[] =
	    "\nFoo::Foo()\n"
	    "    : bar{0} {\n"
	    "    foo(a,\n"
	    "        b);\n"
	    "}";
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : bar{0}\n"
	    "{\n"
	    "    foo(a,\n"
	    "        b);\n"
	    "}";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerClassInitializerRunIn)
{
	// The uniform initializer in a class initializer is an array-type.
	// The opening command type brace should be correctly identified.
	// This type is for run-in braces.
	char textIn[] =
	    "\nFoo::Foo()\n"
	    "    : bar{0} {\n"
	    "    foo(a,\n"
	    "        b);\n"
	    "}";
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : bar{0}\n"
	    "{   foo(a,\n"
	    "        b);\n"
	    "}";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerClassInitializerOneLine)
{
	// The uniform initializer in a class initializer is an array-type.
	/// The opening command type brace should be correctly identified.
	char textIn[] =
	    "\nclass HasPtr\n"
	    "{\n"
	    "public:\n"
	    "    HasPtr(HasPtr && p) noexcept : ps{ p.ps }, i{ p.i }{ p.ps = 0; }\n"
	    "};";
	char text[] =
	    "\nclass HasPtr\n"
	    "{\n"
	    "public:\n"
	    "    HasPtr(HasPtr && p) noexcept : ps{ p.ps }, i{ p.i } {\n"
	    "        p.ps = 0;\n"
	    "    }\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerClassInitializerMultiLine1)
{
	// The uniform initializer in a class initializer is an array-type.
	// The opening brace should be left as-is and not automatically space padded.
	// The closing brace should be left as-is and not automatically broken.
	char text[] =
	    "\nMyClass::MyClass()\n"
	    "    : x{0,\n"
	    "        1,\n"
	    "        2},\n"
	    "      y{0}\n"
	    "{}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerClassInitializerMultiLine2)
{
	// The uniform initializer in a class initializer is an array-type.
	// The opening brace should be left as-is.
	// The closing brace should be left as-is.
	char text[] =
	    "\nMyClass::MyClass()\n"
	    "    : x { 0,\n"
	    "          1,\n"
	    "          2\n"
	    "        },\n"
	    "      y { 0 }\n"
	    "{}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializer1)
{
	// uniform initializers are aligned on first variable
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : m_bar1{0},\n"
	    "      m_bar2{this, id},\n"
	    "      m_bar3{0}\n"
	    "{\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializer2)
{
	// uniform initializers are aligned on first variable
	// colon on previous line
	char text[] =
	    "\nFoo::Foo() :\n"
	    "    m_bar1{0},\n"
	    "    m_bar2{this, id},\n"
	    "    m_bar3{0}\n"
	    "{\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializer3)
{
	// uniform initializers are aligned on first variable
	// multiple variables per line
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : m_bar1{0}, m_bar2{0},\n"
	    "      m_bar3{0}, m_bar4{0}, m_bar5{0},\n"
	    "      m_bar6{-100}, m_bar7{50}\n"
	    "{\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializer4)
{
	// uniform initializers are aligned on first variable
	// comments after comma
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : m_FileGroups{*fgam}, // comment\n"
	    "      m_pOrigFileGroups{fgam},\n"
	    "      m_LastListSelection{0}\n"
	    "{\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializer5)
{
	// uniform initializers are aligned on first variable
	// last line with braces should be indented
	char text[] =
	    "\nFooBar::FooBar(int width = 1, int style = wxSOLID,\n"
	    "               int cap = wxCAP_ROUND)\n"
	    "    : m_bar1{0}, m_bar2{0},\n"
	    "      m_bar3{0}, m_bar4{0},\n"
	    "      m_bar5{0}, m_bar6{NULL} {}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializer6)
{
	// uniform initializers are aligned on first variable
	// initializer with multiple lines
	// variables are aligned
	// ending brace is NOT broken
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : m_bar1{0,\n"
	    "             1,\n"
	    "             2},\n"
	    "      m_bar2{0},\n"
	    "      m_bar3{0} {}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializer7)
{
	// uniform initializers are aligned on first variable
	// initializer braces are NOT block openers
	// the command brace IS a block opener
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : bar { new Bar }\n"
	    "{\n"
	    "    foo( a,\n"
	    "         b );\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializer8)
{
	// uniform initializers are aligned on first variable
	// variables are aligned
	// ending brace is NOT broken
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : bar { new Bar }\n"
	    "{\n"
	    "    foo( a,\n"
	    "         b );\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializer9)
{
	// uniform initializers are aligned on first variable
	// class initializer with a "noexcept"
	char textIn[] =
	    "\nclass HasPtr\n"
	    "{\n"
	    "public:\n"
	    "    HasPtr(HasPtr && p) noexcept : ps{p.ps}, i{p.i} { p.ps = 0; }\n"
	    "};";
	char text[] =
	    "\nclass HasPtr\n"
	    "{\n"
	    "public:\n"
	    "    HasPtr(HasPtr && p) noexcept : ps{p.ps}, i{p.i} {\n"
	    "        p.ps = 0;\n"
	    "    }\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializer10)
{
	// uniform initializers are aligned on first variable
	// colon on a line by itself
	char text[] =
	    "\nstruct A\n"
	    "{\n"
	    "    A(int a, int b)\n"
	    "        :\n"
	    "        m_a {a},\n"
	    "        m_b {a}\n"
	    "    {}\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerCommaFirst1)
{
	// "comma first" uniform initializers are aligned on the colon
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : m_bar1{0}\n"
	    "    ,  m_bar2{this, id}\n"
	    "    ,  m_bar3{0}\n"
	    "{}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Initializer, UniformInitializerCommaFirst2)
{
	// "comma first" uniform initializers are aligned on the colon
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : m_bar1{0},\n"
	    "    ,  m_bar2{this, id},\n"
	    "    ,  m_bar3{0} {}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle C++11 Trailing Return Type Functions
//----------------------------------------------------------------------------

TEST(Cpp11Function, BracesNone_Break)
{
	// test default braces option with broken braces
	char text[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesNone_Attach)
{
	char text[] =
	    // test default braces option with attached braces
	    "\n"
	    "auto Foo() -> void {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesNone_Linux)
{
	// test default braces option with linux braces
	char text[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesNone_RunIn)
{
	// test default braces option with run-in braces
	char text[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesBreak_Break)
{
	// test break braces option with broken braces
	char text[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=break";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesBreak_Attach)
{
	// test break braces option with attached braces
	char textIn[] =
	    "\n"
	    "auto Foo() -> void {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesBreak_Linux)
{
	// test break braces option with linux braces
	char textIn[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesBreak_RunIn)
{
	// test break braces option with run-in braces
	char textIn[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesAttach_Break)
{
	// test attach braces option with broken braces
	char text[] =
	    "\n"
	    "auto Foo() -> void {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char textIn[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesAttach_Attach)
{
	// test attach braces option with attached braces
	char text[] =
	    "\n"
	    "auto Foo() -> void {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=attach";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesAttach_Linux)
{
	// test attach braces option with linux braces
	char text[] =
	    "\n"
	    "auto Foo() -> void {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char textIn[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesAttach_RunIn)
{
	// test attach braces option with run-in braces
	char text[] =
	    "\n"
	    "auto Foo() -> void {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char textIn[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesLinux_Break)
{
	// test linux braces option with broken braces
	char text[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char textIn[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesLinux_Attach)
{
	// test linux braces option with attached braces
	char text[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char textIn[] =
	    "\n"
	    "auto Foo() -> void {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesLinux_Linux)
{
	// test linux braces option with linux braces
	char text[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesLinux_RunIn)
{
	// test linux braces option with run-in braces
	char text[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char textIn[] =
	    "\n"
	    "auto Foo() -> void {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesRunIn_Break)
{
	// test run-in braces option with broken braces
	char text[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}";
	char textIn[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesRunIn_Attach)
{
	// test run-in braces option with attached braces
	char text[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}";
	char textIn[] =
	    "\n"
	    "auto Foo() -> void {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesRunIn_Linux)
{
	// test run-in braces option with linux braces
	char text[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}";
	char textIn[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesRunIn_RunIn)
{
	// test run-in braces option with run-in braces
	char text[] =
	    "\n"
	    "auto Foo() -> void\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BracesClass)
{
	// test braces in a class
	char text[] =
	    "\n"
	    "class serial_pool\n"
	    "{\n"
	    "    auto submit() -> void\n"
	    "    {\n"
	    "        if (!ThreadpoolCallback(callback))\n"
	    "        {\n"
	    "            throw windows_exception();\n"
	    "        }\n"
	    "    }\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BraceNamespaceClass)
{
	// test braces in a namespace and class
	char text[] =
	    "\n"
	    "namespace pool\n"
	    "{\n"
	    "class serial_pool\n"
	    "{\n"
	    "    auto submit() -> void\n"
	    "    {\n"
	    "        if (!ThreadpoolCallback(callback))\n"
	    "        {\n"
	    "            throw windows_exception();\n"
	    "        }\n"
	    "    }\n"
	    "};\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, BraceNamespaceClassIndent)
{
	// test braces in an indented namespace and class
	char text[] =
	    "\n"
	    "namespace pool\n"
	    "{\n"
	    "    class serial_pool\n"
	    "    {\n"
	    "        auto submit() -> void\n"
	    "        {\n"
	    "            if (!ThreadpoolCallback(callback))\n"
	    "            {\n"
	    "                throw windows_exception();\n"
	    "            }\n"
	    "        }\n"
	    "    };\n"
	    "}";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, NestedClass)
{
	// test nested classes
	char text[] =
	    "\nclass A\n"
	    "{\n"
	    "public:\n"
	    "    int foo1;\n"
	    "    class B\n"
	    "    {\n"
	    "    public:\n"
	    "        int foo2;\n"
	    "        class C\n"
	    "        {\n"
	    "        public:\n"
	    "            auto submit() -> void\n"
	    "            {\n"
	    "                if (!ThreadpoolCallback(callback))\n"
	    "                {\n"
	    "                    throw windows_exception();\n"
	    "                }\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, NestedNamespace)
{
	// test nested namespaces
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "namespace B\n"
	    "{\n"
	    "namespace C\n"
	    "{\n"
	    "auto submit() -> void\n"
	    "{\n"
	    "    if (!ThreadpoolCallback(callback))\n"
	    "    {\n"
	    "        throw windows_exception();\n"
	    "    }\n"
	    "}\n"
	    "}\n"
	    "}\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Function, NestedNamespaceClass)
{
	// test namespaces within a class
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "class A\n"
	    "{\n"
	    "public:\n"
	    "    namespace B\n"
	    "    {\n"
	    "    class B\n"
	    "    {\n"
	    "    public:\n"
	    "        namespace C\n"
	    "        {\n"
	    "        class C\n"
	    "        {\n"
	    "        public:\n"
	    "            auto submit() -> void\n"
	    "            {\n"
	    "                if (!ThreadpoolCallback(callback))\n"
	    "                {\n"
	    "                    throw windows_exception();\n"
	    "                }\n"
	    "            }\n"
	    "        }\n"
	    "        }\n"
	    "    }\n"
	    "    }\n"
	    "}\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle C++11 Raw String Literals
//----------------------------------------------------------------------------

TEST(Cpp11Quote, RawStringLiteral1)
{
	// test C++11 raw string literal (verbatim quote)
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "string str  =   R\"~(raw\n"
	    "string)~\";\n"
	    "string str  =   R\"(raw\n"
	    "string)\";\n"
	    "wstring str =  LR\"xxx(raw\n"
	    "string)xxx\";\n"
	    "string str  = u8R\"(raw\n"
	    "string)\";\n"
	    "wstring str =  uR\"(raw\n"
	    "string)\";\n"
	    "wstring str =  UR\"(raw\n"
	    "string)\";\n"
	    "bar();\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    string str  =   R\"~(raw\n"
	    "string)~\";\n"
	    "    string str  =   R\"(raw\n"
	    "string)\";\n"
	    "    wstring str =  LR\"xxx(raw\n"
	    "string)xxx\";\n"
	    "    string str  = u8R\"(raw\n"
	    "string)\";\n"
	    "    wstring str =  uR\"(raw\n"
	    "string)\";\n"
	    "    wstring str =  UR\"(raw\n"
	    "string)\";\n"
	    "    bar();\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Quote, RawStringLiteral2)
{
	// test C++11 raw string literal (verbatim quote)
	// missing opening paren should not cause an exception
	// it will be formatted as a standard string
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    string str = R\"raw\n"
	    "string)~\";\n"
	    "    bar();\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    string str = R\"raw\n"
	    "                 string)~\";\n"
	    "    bar();\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Quote, RawStringLiteral3)
{
	// test C++11 raw string literal (verbatim quote)
	// short closing delimiter should not cause an exception
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    string str = R\"xxx(raw string\n"
	    ")xx\";\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Quote, RawStringLiteral4)
{
	// test C++11 raw string literal (verbatim quote)
	// quotes in the literal should not end the literal
	// the % signs will be padded if it fails
	char text[] =
	    "\nvoid foo() {\n"
	    "    m_childProc->Execute(_T(R\"(\"%SOURCE%\" %AUDIOMAP%)\"));\n"
	    "}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp11Quote, RawStringLiteral5)
{
	// test C++11 raw string literal (verbatim quote)
	// the ~ should end the quote
	// the 2*2 signs will NOT be padded if it fails
	char textIn[] =
	    "\nvoid foo() {\n"
	    "    m_childProc->Execute(_T(R\"~(\"%SOURCE%\" %AUDIOMAP%)~\"));\n"
	    "    x = 2*2;\n"
	    "}";
	char text[] =
	    "\nvoid foo() {\n"
	    "    m_childProc->Execute(_T(R\"~(\"%SOURCE%\" %AUDIOMAP%)~\"));\n"
	    "    x = 2 * 2;\n"
	    "}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle C++14 Digit Separator
//----------------------------------------------------------------------------

TEST(Cpp14Standard, Cpp14DigitSeparator)
{
	// C++14 single quotation mark as digit separator.
	// Some lines will be indented if not recognized.
	char text[] =
	    "\n"
	    "long decval=1'048'576;   //groups of three digits\n"
	    "long hexval=0x10'0000;   // four digits\n"
	    "long hexval=0xbc'd1'4e;  // hex before and after\n"
	    "long octval=00'04'00'00; //two digits\n"
	    "long binval=0b100'000000;//six digits\n"
	    "wchar_t wide= L'0';\n"
	    "cout << 10'000 << endl;\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Cpp14Standard, Cpp14DigitSeparatorNegative)
{
	// C++14 single quotation mark ise not a digit separator.
	// Will get a "Debug Assertion Failed" if chars are not cast as
	// (unsigned char) in astyle isDigitSeparator() function.
	char text[] =
	    "\n"
	    "int negBeg = \x81'0';  // negative value before single quote\n"
	    "int negEnd = 0'\x81';  // negative value after single quote\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}


//----------------------------------------------------------------------------

}  // namespace
