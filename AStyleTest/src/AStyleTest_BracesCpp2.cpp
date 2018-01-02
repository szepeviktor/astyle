// AStyleTest_BracesCpp2.cpp
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

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
// AStyle C++ Brace Options
//-----------------------------------------------------------------------------

//-------------------------------------------------------------------------
// AStyle C++ RunIn Brace Options
//-------------------------------------------------------------------------

struct BracesRunInCppF : public Test
{
	string textStr;
	const char* textIn;

	BracesRunInCppF()
	{
		textStr =
		    "\nnamespace FooName\n"
		    "{\n"
		    "\n"
		    "class FooClass\n"
		    "{\n"
		    "private:\n"
		    "    bool var1;\n"
		    "    void func1();\n"
		    "protected:\n"
		    "    bool var2;\n"
		    "    void func2();\n"
		    "};\n"
		    "\n"
		    "void FooClass::Foo(bool isFoo)\n"
		    "{\n"
		    "    if (isFoo) {\n"
		    "        bar();\n"
		    "    } else {\n"
		    "        anotherBar();\n"
		    "    }\n"
		    "}\n"
		    "\n"
		    "}   // end FooName\n";
		textIn = textStr.c_str();
	}
};

TEST_F(BracesRunInCppF, RunInOption)
{
	// test run-in braces option
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "class FooClass\n"
	    "{\n"
	    "private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesRunInCppF, HorstmannOption)
{
	// test horstmann braces option
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "class FooClass\n"
	    "{\n"
	    "private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesRunInCppF, ShortOption)
{
	// test run-in braces short option
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "class FooClass\n"
	    "{\n"
	    "private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "-A9";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesRunInCppF, Namespace)
{
	// test run-in braces option
	// indented namespace
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "    class FooClass\n"
	    "    {\n"
	    "    private:\n"
	    "        bool var1;\n"
	    "        void func1();\n"
	    "    protected:\n"
	    "        bool var2;\n"
	    "        void func2();\n"
	    "    };\n"
	    "\n"
	    "    void FooClass::Foo(bool isFoo)\n"
	    "    {   if (isFoo)\n"
	    "        {   bar();\n"
	    "        }\n"
	    "        else\n"
	    "        {   anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=run-in, indent-namespaces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesRunInCppF, Class)
{
	// test run-in braces option
	// indent class blocks
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "class FooClass\n"
	    "{   private:\n"
	    "        bool var1;\n"
	    "        void func1();\n"
	    "    protected:\n"
	    "        bool var2;\n"
	    "        void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=run-in, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesRunInCppF, NamespaceClass)
{
	// test run-in braces option
	// indented namespace and class
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "    class FooClass\n"
	    "    {   private:\n"
	    "            bool var1;\n"
	    "            void func1();\n"
	    "        protected:\n"
	    "            bool var2;\n"
	    "            void func2();\n"
	    "    };\n"
	    "\n"
	    "    void FooClass::Foo(bool isFoo)\n"
	    "    {   if (isFoo)\n"
	    "        {   bar();\n"
	    "        }\n"
	    "        else\n"
	    "        {   anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=run-in, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, EmptyBraces)
{
	// test run-in braces option
	// do not change empty braces
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "public:\n"
	    "    FooClass() : ed(ed) {}\n"
	    "    FooClass() : ed(ed) {\n"
	    "    }\n"
	    "    FooClass() : ed(ed)\n"
	    "    {}\n"
	    "};\n"
	    "\n"
	    "FooClass() : ed(ed) {}\n"
	    "FooClass() : ed(ed) {\n"
	    "}\n"
	    "FooClass() : ed(ed)\n"
	    "{}\n";
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "public:\n"
	    "    FooClass() : ed(ed) {}\n"
	    "    FooClass() : ed(ed)\n"
	    "    {\n"
	    "    }\n"
	    "    FooClass() : ed(ed)\n"
	    "    {}\n"
	    "};\n"
	    "\n"
	    "FooClass() : ed(ed) {}\n"
	    "FooClass() : ed(ed)\n"
	    "{\n"
	    "}\n"
	    "FooClass() : ed(ed)\n"
	    "{}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, EmptyBracesWithComments)
{
	// test run-in braces option with ending comments
	// do not change empty braces
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "public:\n"
	    "    FooClass() : ed(ed) {} // comment\n"
	    "    FooClass() : ed(ed) { // comment\n"
	    "    }\n"
	    "    FooClass() : ed(ed) // comment\n"
	    "    {}\n"
	    "};\n"
	    "\n"
	    "FooClass() : ed(ed) {} // comment\n"
	    "FooClass() : ed(ed) { // comment\n"
	    "}\n"
	    "FooClass() : ed(ed) // comment\n"
	    "{}\n";
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "public:\n"
	    "    FooClass() : ed(ed) {} // comment\n"
	    "    FooClass() : ed(ed)   // comment\n"
	    "    {\n"
	    "    }\n"
	    "    FooClass() : ed(ed) // comment\n"
	    "    {}\n"
	    "};\n"
	    "\n"
	    "FooClass() : ed(ed) {} // comment\n"
	    "FooClass() : ed(ed)   // comment\n"
	    "{\n"
	    "}\n"
	    "FooClass() : ed(ed) // comment\n"
	    "{}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, Extern)
{
	// extern statement should not change its brace type
	// and should NOT use continuation indents
	char textIn[] =
	    "\nextern \"C\" {\n"
	    "	extern void foo1() {\n"
	    "		bar1();\n"
	    "	}\n"
	    "}\n"
	    "\n"
	    "extern \"C\"\n"
	    "{\n"
	    "	void foo2()\n"
	    "	{\n"
	    "		bar2();\n"
	    "	}\n"
	    "}\n";
	char text[] =
	    "\nextern \"C\"\n"
	    "{	extern void foo1()\n"
	    "	{	bar1();\n"
	    "	}\n"
	    "}\n"
	    "\n"
	    "extern \"C\"\n"
	    "{	void foo2()\n"
	    "	{	bar2();\n"
	    "	}\n"
	    "}\n";
	char options[] = "indent=tab, style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, Assembler)
{
	// assembler statement should be formatted
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    _asm {\n"
	    "        mov eax, fs:[0x8]\n"
	    "        mov dx, 0xD007\n"
	    "        out dx, al\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   _asm\n"
	    "    {   mov eax, fs:[0x8]\n"
	    "        mov dx, 0xD007\n"
	    "        out dx, al\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, Break)
{
	// test run-in braces option with broken braces
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
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
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, Attach)
{
	// test run-in braces option with attached braces
	char textIn[] =
	    "\nvoid Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, Linux)
{
	// test run-in braces option with linux braces
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, RunIn1)
{
	// test run-in braces option with run-in braces
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, RunIn2)
{
	// test default braces option with run-in braces
	// and 2 braces on the same line
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   if(isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   if(isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, ClassSansPrivate1)
{
	// test run-in braces without class indent
	// with and without 'private' class modifier
	char textIn[] =
	    "\nclass fooClass1\n"
	    "{\n"
	    "private:\n"
	    "    bool foo1;\n"
	    "};\n"
	    "\n"
	    "class fooClass2\n"
	    "{\n"
	    "    bool foo2;\n"
	    "};\n";
	char text[] =
	    "\nclass fooClass1\n"
	    "{\n"
	    "private:\n"
	    "    bool foo1;\n"
	    "};\n"
	    "\n"
	    "class fooClass2\n"
	    "{   bool foo2;\n"
	    "};\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, ClassSansPrivate2)
{
	// test run-in braces with class indent
	// with and without 'private' class modifier
	char textIn[] =
	    "\nclass fooClass1\n"
	    "{\n"
	    "private:\n"
	    "    bool foo1;\n"
	    "};\n"
	    "\n"
	    "class fooClass2\n"
	    "{\n"
	    "    bool foo2;\n"
	    "};\n";
	char text[] =
	    "\nclass fooClass1\n"
	    "{   private:\n"
	    "        bool foo1;\n"
	    "};\n"
	    "\n"
	    "class fooClass2\n"
	    "{       bool foo2;\n"
	    "};\n";
	char options[] = "style=run-in, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, Misc1)
{
	// test run-in braces option with the following unusual format
	char textIn[] =
	    "\nvoid foo1() { error = false;\n"
	    "              errorId = 0;\n"
	    "            }\n"
	    "\n"
	    "void foo2() {  // comment2\n"
	    "               error = false;\n"
	    "               errorId = 0;\n"
	    "            }\n"
	    "\n"
	    "void foo3() {  /* comment3 */\n"
	    "               error = false;\n"
	    "               errorId = 0;\n"
	    "            }\n";
	char text[] =
	    "\nvoid foo1()\n"
	    "{   error = false;\n"
	    "    errorId = 0;\n"
	    "}\n"
	    "\n"
	    "void foo2()    // comment2\n"
	    "{   error = false;\n"
	    "    errorId = 0;\n"
	    "}\n"
	    "\n"
	    "void foo3()    /* comment3 */\n"
	    "{   error = false;\n"
	    "    errorId = 0;\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, Misc2)
{
	// test run-in braces option with the following unusual format
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (bar1()) {/* dummy */}\n"
	    "\n"
	    "    if (bar1()) {;/* dummy */}\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (bar1()) {/* dummy */}\n"
	    "\n"
	    "    if (bar1()) {;/* dummy */}\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, Misc3)
{
	// test run-in braces option with a macro
	// brace type will be incorrectly classified as an array
	// but should not break at the semi colon
	char text[] =
	    "\nvoid foo()\n"
	    "{   YY_RULE_SETUP\n"
	    "    { BEGIN(list); return CONT; }\n"
	    "    YY_BREAK\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, ClassContinuation)
{
	// test with class continuation and run-in braces
	char text[] =
	    "\nclass Foo :\n"
	    "    public Bar\n"
	    "{\n"
	    "public:\n"
	    "    Foo(T *in);\n"
	    "};\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, ClassContinuation_IndentClass)
{
	// test with class continuation, run-in braces, and indented class blocks
	char text[] =
	    "\nclass Foo :\n"
	    "    public Bar\n"
	    "{   public:\n"
	    "        Foo(T *in);\n"
	    "};\n";
	char options[] = "style=run-in, indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, RunInIndent1)
{
	// test run-in braces option with run-in braces
	// with the indent changed from 2 to 4
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{ if (isFoo)\n"
	    "  { foo();\n"
	    "  }\n"
	    "  else\n"
	    "  { // comment\n"
	    "    bar();\n"
	    "  }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo()\n"
	    "{   if (isFoo)\n"
	    "    {   foo();\n"
	    "    }\n"
	    "    else\n"
	    "    {   // comment\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, RunInIndent2)
{
	// test run-in braces option with run-in braces
	// with the indent changed from 6 to 4
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{     if (isFoo)\n"
	    "      {     foo();\n"
	    "      }\n"
	    "      else\n"
	    "      {     // comment\n"
	    "            bar();\n"
	    "      }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo()\n"
	    "{   if (isFoo)\n"
	    "    {   foo();\n"
	    "    }\n"
	    "    else\n"
	    "    {   // comment\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, LineCommentsBreak)
{
	// comments following broken braces should be attached
	char textIn[] =
	    "\nvoid foo(bool isFoo)\n"
	    "{\n"
	    "    // comment1\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        // comment2\n"
	    "        while (isBar)\n"
	    "        {\n"
	    "            // comment3\n"
	    "            fooBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo(bool isFoo)\n"
	    "{   // comment1\n"
	    "    if (isFoo)\n"
	    "    {   // comment2\n"
	    "        while (isBar)\n"
	    "        {   // comment3\n"
	    "            fooBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, LineCommentsAttach)
{
	// comments following attached braces should stay attached to the line
	char textIn[] =
	    "\nvoid foo(bool isFoo) {    // comment1\n"
	    "    if (isFoo) {          // comment2\n"
	    "        while (isBar) {   // comment3\n"
	    "            fooBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo(bool isFoo)      // comment1\n"
	    "{   if (isFoo)            // comment2\n"
	    "    {   while (isBar)     // comment3\n"
	    "        {   fooBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, LineCommentsRunIn)
{
	// comments following run-in braces should be unchanged
	char text[] =
	    "\nvoid foo(bool isFoo)\n"
	    "{   // comment1\n"
	    "    if (isFoo)\n"
	    "    {   // comment2\n"
	    "        while (isBar)\n"
	    "        {   // comment3\n"
	    "            fooBar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, LineCommentsClosingHeader)
{
	// test comment alignment when a closing header is attached to a closing brace
	char textIn[] =
	    "\nvoid foo()       // comment0\n"
	    "{\n"
	    "    if (isFoo) { // comment1\n"
	    "        bar1();  // comment2\n"
	    "    } else {     // comment3\n"
	    "        bar2();  // comment4\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()       // comment0\n"
	    "{   if (isFoo)   // comment1\n"
	    "    {   bar1();  // comment2\n"
	    "    }\n"
	    "    else         // comment3\n"
	    "    {   bar2();  // comment4\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, CommentsBreak1)
{
	// broken braces with following comments to run-in
	char textIn[] =
	    "\nvoid (foo)\n"
	    "{\n"
	    "    /*\n"
	    "     * comment1\n"
	    "     */\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        /*\n"
	    "         * comment2\n"
	    "         */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid (foo)\n"
	    "{   /*\n"
	    "     * comment1\n"
	    "     */\n"
	    "    if (isFoo)\n"
	    "    {   /*\n"
	    "         * comment2\n"
	    "         */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, CommentsAttach1)
{
	// attached braces with following comments to run-in
	char textIn[] =
	    "\nvoid (foo) {\n"
	    "    /*\n"
	    "     * comment1\n"
	    "     */\n"
	    "    if (isFoo) {\n"
	    "        /*\n"
	    "         * comment2\n"
	    "         */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid (foo)\n"
	    "{   /*\n"
	    "     * comment1\n"
	    "     */\n"
	    "    if (isFoo)\n"
	    "    {   /*\n"
	    "         * comment2\n"
	    "         */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, CommentsRunIn1)
{
	// run-in braces should not change
	char text[] =
	    "\nvoid (foo)\n"
	    "{   /*\n"
	    "     * comment1\n"
	    "     */\n"
	    "    if (isFoo)\n"
	    "    {   /*\n"
	    "         * comment2\n"
	    "         */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, CommentsBreak2)
{
	// broken braces with following comments to run-in
	// mixed tabs and spaces
	char textIn[] =
	    "\nvoid (foo)\n"
	    "{\n"
	    "	/*\n"
	    "	 * comment1\n"
	    "     */\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "		/*\n"
	    " 	     * comment2\n"
	    "  	     */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid (foo)\n"
	    "{   /*\n"
	    "     * comment1\n"
	    "     */\n"
	    "    if (isFoo)\n"
	    "    {   /*\n"
	    "         * comment2\n"
	    "         */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, CommentsAttach2)
{
	// attached braces with following comments to run-in
	// mixed tabs and spaces
	char textIn[] = "\nvoid (foo) {\n"
	                "	/*\n"
	                "	 * comment1\n"
	                "     */\n"
	                "    if (isFoo) {\n"
	                "		/*\n"
	                " 	     * comment2\n"
	                "  	     */\n"
	                "        bar();\n"
	                "    }\n"
	                "}\n";
	char text[] =
	    "\nvoid (foo)\n"
	    "{   /*\n"
	    "     * comment1\n"
	    "     */\n"
	    "    if (isFoo)\n"
	    "    {   /*\n"
	    "         * comment2\n"
	    "         */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, CommentsRunIn2)
{
	// run-in braces with following comments to run-in
	// mixed tabs and spaces
	char textIn[] =
	    "\nvoid (foo)\n"
	    "{	/*\n"
	    "	 * comment1\n"
	    "     */\n"
	    "    if (isFoo)\n"
	    "    {	/*\n"
	    " 	     * comment2\n"
	    "  	     */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid (foo)\n"
	    "{   /*\n"
	    "     * comment1\n"
	    "     */\n"
	    "    if (isFoo)\n"
	    "    {   /*\n"
	    "         * comment2\n"
	    "         */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, CommentsBreak3)
{
	// comments following broken braces should attach to the brace
	char textIn[] =
	    "\nvoid foo1(bool isFoo) /* comment0 */\n"
	    "{\n"
	    "    /* comment1 */\n"
	    "    if(isFoo)\n"
	    "    {\n"
	    "        /* comment2 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo)\n"
	    "{\n"
	    "    /* comment3\n"
	    "     *\n"
	    "     */\n"
	    "    if(isFoo)\n"
	    "    {\n"
	    "        /* comment4\n"
	    "         *\n"
	    "         */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo1(bool isFoo) /* comment0 */\n"
	    "{   /* comment1 */\n"
	    "    if(isFoo)\n"
	    "    {   /* comment2 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo)\n"
	    "{   /* comment3\n"
	    "     *\n"
	    "     */\n"
	    "    if(isFoo)\n"
	    "    {   /* comment4\n"
	    "         *\n"
	    "         */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, CommentsAttach3)
{
	// test comments following braces
	// multi-line comments following attached braces break
	//    but are NOT aligned
	char textIn[] =
	    "\nvoid foo1(bool isFoo) {  /* comment0 */\n"
	    "    if(isFoo) {  /* comment1 */\n"
	    "    /* comment2 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo) { /* comment3\n"
	    "    *\n"
	    "    */\n"
	    "    if(isFoo) {\n"
	    "        /* comment4\n"
	    "         *\n"
	    "         */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo1(bool isFoo)    /* comment0 */\n"
	    "{   if(isFoo)    /* comment1 */\n"
	    "    {   /* comment2 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo)\n"
	    "{   /* comment3\n"
	    "        *\n"
	    "        */\n"
	    "    if(isFoo)\n"
	    "    {   /* comment4\n"
	    "         *\n"
	    "         */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, CommentsRunIn3)
{
	// comments following run-in braces should be unchanged
	char text[] =
	    "\nvoid foo1(bool isFoo) /* comment0 */\n"
	    "{   /* comment1 */\n"
	    "    if(isFoo)\n"
	    "    {   /* comment2 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo)\n"
	    "{   /* comment3\n"
	    "     *\n"
	    "     */\n"
	    "    if(isFoo)\n"
	    "    {   /* comment4\n"
	    "         *\n"
	    "         */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, CommentsRunInNamespace1)
{
	// Comments following run-in namespace should be BROKEN.
	// Will not format correctly if left as run-in.
	char textIn[] =
	    "\n"
	    "namespace CodeActions\n"
	    "{/* TODO: Enable.\n"
	    "	[TestFixture]\n"
	    "	public class TestBase\n"
	    "	{\n"
	    "		[Test]\n"
	    "		public void TestSimple()\n"
	    "		{\n"
	    "			Test<ConvertDoWhileToWhileLoopAction>(@\"\n"
	    "		}\n"
	    "	}*/\n"
	    "}";
	char text[] =
	    "\n"
	    "namespace CodeActions\n"
	    "{\n"
	    "    /* TODO: Enable.\n"
	    "    [TestFixture]\n"
	    "    public class TestBase\n"
	    "    {\n"
	    "    	[Test]\n"
	    "    	public void TestSimple()\n"
	    "    	{\n"
	    "    		Test<ConvertDoWhileToWhileLoopAction>(@\"\n"
	    "    	}\n"
	    "    }*/\n"
	    "}";
	char options[] = "indent-namespaces";
	char* textOut1 = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut1);
	// do it again to check for changes
	char* textOut2 = AStyleMain(textOut1, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut2);
	delete[] textOut1;
	delete[] textOut2;
}

TEST(BracesRunInCpp, CommentsRunInNamespace2)
{
	// Comments following run-in namespace should be BROKEN.
	// Will not format correctly if left as run-in.
	// This namespace is indented.
	char textIn[] =
	    "\n"
	    "namespace CodeActions\n"
	    "{/* TODO: Enable.\n"
	    "	[TestFixture]\n"
	    "	public class TestBase\n"
	    "	{\n"
	    "		[Test]\n"
	    "		public void TestSimple()\n"
	    "		{\n"
	    "			Test<ConvertDoWhileToWhileLoopAction>(@\"\n"
	    "		}\n"
	    "	}*/\n"
	    "}";
	char text[] =
	    "\n"
	    "namespace CodeActions\n"
	    "{\n"
	    "/* TODO: Enable.\n"
	    "[TestFixture]\n"
	    "public class TestBase\n"
	    "{\n"
	    "	[Test]\n"
	    "	public void TestSimple()\n"
	    "	{\n"
	    "		Test<ConvertDoWhileToWhileLoopAction>(@\"\n"
	    "	}\n"
	    "}*/\n"
	    "}";
	char options[] = "";
	char* textOut1 = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut1);
	// do it again to check for changes
	char* textOut2 = AStyleMain(textOut1, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut2);
	delete[] textOut1;
	delete[] textOut2;
}

TEST(BracesRunInCpp, MultipleCommentsBreak)
{
	// multiple comments with broken braces should be run-in
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo) /* comment1 */  // comment2\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo) /* comment1 */  // comment2\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, MultipleCommentsAttach)
{
	// multiple comments with attached braces should not be broken
	char textIn[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo) { /* comment1 */  // comment2\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo) { /* comment1 */  // comment2\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesRunInCpp, MultipleCommentsRunIn)
{
	// multiple comments with run-in braces should remain unchanged
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo) /* comment1 */  // comment2\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C++ Array Default Brace Options
// NOTE: Array braces are NOT converted TO or FROM RunIn style
//-------------------------------------------------------------------------

TEST(BracesArrayNoneCpp, Break)
{
	// test array formatting with broken brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =\n"
	    "{\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayNoneCpp, Attach)
{
	// test array formatting with attached braces
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] = {\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] = {\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayNoneCpp, RunIn1)
{
	// test array formatting with run-in braces
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst int foo[] =\n"
	    "{   FOO1,\n"
	    "    FOO2,\n"
	    "    FOO3,\n"
	    "};\n";
	char text[] =
	    "\nconst int foo[] =\n"
	    "{	FOO1,\n"
	    "	FOO2,\n"
	    "	FOO3,\n"
	    "};\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayNoneCpp, RunIn2)
{
	// test array formatting with run-in braces
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{   \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =\n"
	    "{	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayNoneCpp, RunIn3)
{
	// test array formatting with multiple braces
	// use indent=tab to check indent character
	char textIn[] =
	    "\nstatic wxString codes[2][4] =\n"
	    "{   {   _T(\"0001101\"),_T(\"0100011\"),\n"
	    "        _T(\"0110001\"),_T(\"0001011\")\n"
	    "    },\n"
	    "    {   _T(\"1110010\"),_T(\"1011100\"),\n"
	    "        _T(\"1001110\"),_T(\"1110100\")\n"
	    "    }\n"
	    "};\n";
	char text[] =
	    "\nstatic wxString codes[2][4] =\n"
	    "{	{	_T(\"0001101\"),_T(\"0100011\"),\n"
	    "		_T(\"0110001\"),_T(\"0001011\")\n"
	    "	},\n"
	    "	{	_T(\"1110010\"),_T(\"1011100\"),\n"
	    "		_T(\"1001110\"),_T(\"1110100\")\n"
	    "	}\n"
	    "};\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayNoneCpp, RunIn4)
{
	// test array formatting with multiple one-line-statement braces
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst ct_data static_ltree[L_CODES+2] =\n"
	    "{   {{ 12},{  8}}, {{140},{  8}}, {{ 76},{  8}}, {{204},{  8}}, {{ 44},{  8}},\n"
	    "    {{172},{  8}}, {{108},{  8}}, {{236},{  8}}, {{ 28},{  8}}, {{156},{  8}}\n"
	    "};\n";
	char text[] =
	    "\nconst ct_data static_ltree[L_CODES+2] =\n"
	    "{	{{ 12},{  8}}, {{140},{  8}}, {{ 76},{  8}}, {{204},{  8}}, {{ 44},{  8}},\n"
	    "	{{172},{  8}}, {{108},{  8}}, {{236},{  8}}, {{ 28},{  8}}, {{156},{  8}}\n"
	    "};\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayNoneCpp, RunIn5)
{
	// test array formatting
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst int Chunks[][8] =\n"
	    "{   { 1,1,1,1,\n"
	    "      0,0,0,0 }\n"
	    "};\n";
	char text[] =
	    "\nconst int Chunks[][8] =\n"
	    "{	{	1,1,1,1,\n"
	    "		0,0,0,0\n"
	    "	}\n"
	    "};\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayNoneCpp, RunIn6)
{
	// test array formatting
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst LanguageInfo g_LanguagePrefs [] =\n"
	    "{   // C++\n"
	    "    {   _T(\"C++\"),\n"
	    "        _T(\"*.c;*.cc;*.cpp;*.cxx;*.cs;*.h;*.hh;*.hpp;*.hxx;*.sma\"),\n"
	    "        wxSCI_LEX_CPP,\n"
	    "        {   {TOKEN_DEFAULT, NULL},\n"
	    "            {TOKEN_COMMENT, NULL},\n"
	    "        }\n"
	    "    }\n"
	    "};\n";
	char text[] =
	    "\nconst LanguageInfo g_LanguagePrefs [] =\n"
	    "{	// C++\n"
	    "	{	_T(\"C++\"),\n"
	    "		_T(\"*.c;*.cc;*.cpp;*.cxx;*.cs;*.h;*.hh;*.hpp;*.hxx;*.sma\"),\n"
	    "		wxSCI_LEX_CPP,\n"
	    "		{	{TOKEN_DEFAULT, NULL},\n"
	    "			{TOKEN_COMMENT, NULL},\n"
	    "		}\n"
	    "	}\n"
	    "};\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayNoneCpp, RunInLineComments)
{
	// test array formatting with following comments
	// should not change run-in line comment run-ins
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{   // comment\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =\n"
	    "{	// comment\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayNoneCpp, RunInComments)
{
	// test array formatting with following comment
	// should not change run-in comment run-ins
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{   /* comment */\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =\n"
	    "{	/* comment */\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayNoneCpp, InStatement1)
{
	// in-statement arrays should remain unchanged
	// use indent=tab to check indent character
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    char* a[] = { \"one\", \"two\",\n"
	    "                  \"uno\", \"dos\"\n"
	    "                };\n"
	    "};\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "	char* a[] = { \"one\", \"two\",\n"
	    "	              \"uno\", \"dos\"\n"
	    "	            };\n"
	    "};\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayNoneCpp, InStatement2)
{
	// test array formatting with run-in braces
	// and a non in-statement brace on the same line
	// use indent=tab to check indent character
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   wxChar* names[] = {\n"
	    "        _T(\"cvt \"),\n"
	    "        NULL\n"
	    "    };\n"
	    "\n"
	    "    bar1();\n"
	    "    bar2();\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{	wxChar* names[] = {\n"
	    "		_T(\"cvt \"),\n"
	    "		NULL\n"
	    "	};\n"
	    "\n"
	    "	bar1();\n"
	    "	bar2();\n"
	    "}\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayNoneCpp, Comments1)
{
	// test array formatting with preceding comments
	// use indent=tab to check indent character
	char textIn[] =
	    "\nstatic tAction StateTable[enStates][enEvents] = {\n"
	    "    // IN APPLICATION MODE:         eEventInit       eEventFTPDone\n"
	    "    /* eStateIdle              */ { NULL,            FKT(actReturnToIdle) },\n"
	    "    /* eStateIdleGetVersion    */ { FKT(actCrashed), FKT(actReturnToIdle) },\n"
	    "    // IN UPDATE MODE:\n"
	    "    /* eStateUpdate            */ { FKT(actUpdate),  FKT(actReturnToIdle) },\n"
	    "    /* eStateUpdateGetVersion  */ { FKT(actCrashed), FKT(actReturnToIdle) },\n"
	    "};\n";
	char text[] =
	    "\nstatic tAction StateTable[enStates][enEvents] = {\n"
	    "	// IN APPLICATION MODE:         eEventInit       eEventFTPDone\n"
	    "	/* eStateIdle              */ { NULL,            FKT(actReturnToIdle) },\n"
	    "	/* eStateIdleGetVersion    */ { FKT(actCrashed), FKT(actReturnToIdle) },\n"
	    "	// IN UPDATE MODE:\n"
	    "	/* eStateUpdate            */ { FKT(actUpdate),  FKT(actReturnToIdle) },\n"
	    "	/* eStateUpdateGetVersion  */ { FKT(actCrashed), FKT(actReturnToIdle) },\n"
	    "};\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayNoneCpp, Comments2)
{
	// test array formatting, opening brace after a comment
	// TODO: Fix the following array
	char textIn[] =
	    "\nstatic tAction StateTable[enStates][enEvents] =\n"
	    "    // IN APPLICATION MODE:         eEventInit       eEventFTPDone\n"
	    "    /* eStateIdle              */{{ NULL,            FKT(actReturnToIdle) },\n"
	    "    /* eStateIdleGetVersion    */ { FKT(actCrashed), FKT(actReturnToIdle) },\n"
	    "    // IN UPDATE MODE:\n"
	    "    /* eStateUpdate            */ { FKT(actUpdate),  FKT(actReturnToIdle) },\n"
	    "    /* eStateUpdateGetVersion  */ { FKT(actCrashed), FKT(actReturnToIdle) },\n"
	    "};\n";
	char text[] =
	    "\nstatic tAction StateTable[enStates][enEvents] =\n"
	    "    // IN APPLICATION MODE:         eEventInit       eEventFTPDone\n"
	    "/* eStateIdle              */ {{ NULL,            FKT(actReturnToIdle) },\n"
	    "    /* eStateIdleGetVersion    */ { FKT(actCrashed), FKT(actReturnToIdle) },\n"
	    "    // IN UPDATE MODE:\n"
	    "    /* eStateUpdate            */ { FKT(actUpdate),  FKT(actReturnToIdle) },\n"
	    "    /* eStateUpdateGetVersion  */ { FKT(actCrashed), FKT(actReturnToIdle) },\n"
	    "};\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayNoneCpp, Enum)
{
	// test enum formatting
	// the enum brace should be space padded and should not be broken
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
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C++ Array Break Brace Options
// NOTE: Array braces are NOT converted TO or FROM RunIn style
//-------------------------------------------------------------------------

TEST(BracesArrayBreakCpp, Break)
{
	// test array formatting with broken braces
	// should not change a broken brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =\n"
	    "{\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=allman, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayBreakCpp, Attach)
{
	// test array formatting with attached braces
	// should break an attached brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] = {\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =\n"
	    "{\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=allman, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayBreakCpp, RunIn1)
{
	// test array formatting with run-in braces
	// should break run-in run-ins
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst int foo[] =\n"
	    "{   FOO1,\n"
	    "    FOO2,\n"
	    "    FOO3,\n"
	    "};\n";
	char text[] =
	    "\nconst int foo[] =\n"
	    "{\n"
	    "	FOO1,\n"
	    "	FOO2,\n"
	    "	FOO3,\n"
	    "};\n";
	char options[] = "style=allman, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayBreakCpp, RunIn2)
{
	// test array formatting with run-in braces
	// should break run-in run-ins
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{   \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =\n"
	    "{\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=allman, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayBreakCpp, RunIn3)
{
	// test array formatting with multiple braces
	// should break run-in run-ins
	// use indent=tab to check indent character
	char textIn[] =
	    "\nstatic wxString codes[2][4] =\n"
	    "{   {   _T(\"0001101\"),_T(\"0100011\"),\n"
	    "        _T(\"0110001\"),_T(\"0001011\")\n"
	    "    },\n"
	    "    {   _T(\"1110010\"),_T(\"1011100\"),\n"
	    "        _T(\"1001110\"),_T(\"1110100\")\n"
	    "    }\n"
	    "};\n";
	char text[] =
	    "\nstatic wxString codes[2][4] =\n"
	    "{\n"
	    "	{\n"
	    "		_T(\"0001101\"),_T(\"0100011\"),\n"
	    "		_T(\"0110001\"),_T(\"0001011\")\n"
	    "	},\n"
	    "	{\n"
	    "		_T(\"1110010\"),_T(\"1011100\"),\n"
	    "		_T(\"1001110\"),_T(\"1110100\")\n"
	    "	}\n"
	    "};\n";
	char options[] = "style=allman, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayBreakCpp, RunIn4)
{
	// test array formatting with multiple one-line-statement braces
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst ct_data static_ltree[L_CODES+2] =\n"
	    "{   {{ 12},{  8}}, {{140},{  8}}, {{ 76},{  8}}, {{204},{  8}}, {{ 44},{  8}},\n"
	    "    {{172},{  8}}, {{108},{  8}}, {{236},{  8}}, {{ 28},{  8}}, {{156},{  8}}\n"
	    "};\n";
	char text[] =
	    "\nconst ct_data static_ltree[L_CODES+2] =\n"
	    "{\n"
	    "	{{ 12},{  8}}, {{140},{  8}}, {{ 76},{  8}}, {{204},{  8}}, {{ 44},{  8}},\n"
	    "	{{172},{  8}}, {{108},{  8}}, {{236},{  8}}, {{ 28},{  8}}, {{156},{  8}}\n"
	    "};\n";
	char options[] = "style=allman, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayBreakCpp, RunIn5)
{
	// test array formatting
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst int Chunks[][8] =\n"
	    "{   { 1,1,1,1,\n"
	    "      0,0,0,0 }\n"
	    "};\n";
	char text[] =
	    "\nconst int Chunks[][8] =\n"
	    "{\n"
	    "	{\n"
	    "		1,1,1,1,\n"
	    "		0,0,0,0\n"
	    "	}\n"
	    "};\n";
	char options[] = "style=allman, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayBreakCpp, RunIn6)
{
	// test array formatting
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst LanguageInfo g_LanguagePrefs [] =\n"
	    "{   // C++\n"
	    "    {   _T(\"C++\"),\n"
	    "        _T(\"*.c;*.cc;*.cpp;*.cxx;*.cs;*.h;*.hh;*.hpp;*.hxx;*.sma\"),\n"
	    "        wxSCI_LEX_CPP,\n"
	    "        {   {TOKEN_DEFAULT, NULL},\n"
	    "            {TOKEN_COMMENT, NULL},\n"
	    "        }\n"
	    "    }\n"
	    "};\n";
	char text[] =
	    "\nconst LanguageInfo g_LanguagePrefs [] =\n"
	    "{\n"
	    "	// C++\n"
	    "	{\n"
	    "		_T(\"C++\"),\n"
	    "		_T(\"*.c;*.cc;*.cpp;*.cxx;*.cs;*.h;*.hh;*.hpp;*.hxx;*.sma\"),\n"
	    "		wxSCI_LEX_CPP,\n"
	    "		{	{TOKEN_DEFAULT, NULL},\n"
	    "			{TOKEN_COMMENT, NULL},\n"
	    "		}\n"
	    "	}\n"
	    "};\n";
	char options[] = "style=allman, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayBreakCpp, RunInLineComments)
{
	// test array formatting with following line comment
	// should break run-in line comment run-ins
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{   // comment\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =\n"
	    "{\n"
	    "	// comment\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=allman, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayBreakCpp, RunInComments)
{
	// test array formatting with following comment
	// should break run-in comment run-ins
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{   /* comment */\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =\n"
	    "{\n"
	    "	/* comment */\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=allman, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayBreakCpp, InStatement1)
{
	// in-statement arrays should remain unchanged
	// use indent=tab to check indent character
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    char* a[] = { \"one\", \"two\",\n"
	    "                  \"uno\", \"dos\"\n"
	    "                };\n"
	    "};\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "	char* a[] = { \"one\", \"two\",\n"
	    "	              \"uno\", \"dos\"\n"
	    "	            };\n"
	    "};\n";
	char options[] = "style=allman, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayBreakCpp, InStatement2)
{
	// test array formatting with run-in braces
	// and a non in-statement brace on the same line
	// use indent=tab to check indent character
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   wxChar* names[] = {\n"
	    "        _T(\"cvt \"),\n"
	    "        NULL\n"
	    "    };\n"
	    "\n"
	    "    bar1();\n"
	    "    bar2();\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "	wxChar* names[] =\n"
	    "	{\n"
	    "		_T(\"cvt \"),\n"
	    "		NULL\n"
	    "	};\n"
	    "\n"
	    "	bar1();\n"
	    "	bar2();\n"
	    "}\n";
	char options[] = "style=allman, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayBreakCpp, LineComments)
{
	// test array formatting with line-end comments
	// should break an attached brace
	char textIn[] =
	    "\nconst char *foo[] = { // comment\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =   // comment\n"
	    "{\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayBreakCpp, Comments)
{
	// test array formatting with comments
	// should break an attached brace
	// UNLESS it is multi-line
	// TODO: Fix indentation of multi-line comment
	char textIn[] =
	    "\nconst char *foo[] = { /* comment */\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n"
	    "\n"
	    "\nconst char *foo[] = { /* comment\n"
	    "    */\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =   /* comment */\n"
	    "{\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n"
	    "\n"
	    "\nconst char *foo[] = { /* comment\n"
	    "    */\n"
	    "                        \"foo1\",\n"	// fix indentation
	    "                        \"foo2\",\n"
	    "                        \"foo3\",\n"
	    "                    };\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayBreakCpp, Enum)
{
	// test enum formatting
	// the enum brace should be space padded and should not be broken
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
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C++ Array Attach Brace Options
// NOTE: Array braces are NOT converted TO or FROM RunIn style
//-------------------------------------------------------------------------

TEST(BracesArrayAttachCpp, Break)
{
	// test array formatting with broken braces
	// should attach a broken brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] = {\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=java, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayAttachCpp, Attach)
{
	// test array formatting with attached braces
	// should not change an attached brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] = {\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] = {\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=java, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayAttachCpp, RunIn1)
{
	// test array formatting with horstmann braces
	// should attach a run-in brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst int foo[] =\n"
	    "{   FOO1,\n"
	    "    FOO2,\n"
	    "    FOO3,\n"
	    "};\n";
	char text[] =
	    "\nconst int foo[] = {\n"
	    "	FOO1,\n"
	    "	FOO2,\n"
	    "	FOO3,\n"
	    "};\n";
	char options[] = "style=java, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayAttachCpp, RunIn2)
{
	// test array formatting with horstmann braces
	// should attach a run-in brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{   \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] = {\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=java, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayAttachCpp, RunIn3)
{
	// test array formatting with multiple braces
	// should break run-in run-ins
	// use indent=tab to check indent character
	char textIn[] =
	    "\nstatic wxString codes[2][4] =\n"
	    "{   {   _T(\"0001101\"),_T(\"0100011\"),\n"
	    "        _T(\"0110001\"),_T(\"0001011\")\n"
	    "    },\n"
	    "    {   _T(\"1110010\"),_T(\"1011100\"),\n"
	    "        _T(\"1001110\"),_T(\"1110100\")\n"
	    "    }\n"
	    "};\n";
	char text[] =
	    "\nstatic wxString codes[2][4] = {\n"
	    "	{\n"
	    "		_T(\"0001101\"),_T(\"0100011\"),\n"
	    "		_T(\"0110001\"),_T(\"0001011\")\n"
	    "	},\n"
	    "	{\n"
	    "		_T(\"1110010\"),_T(\"1011100\"),\n"
	    "		_T(\"1001110\"),_T(\"1110100\")\n"
	    "	}\n"
	    "};\n";
	char options[] = "style=java, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayAttachCpp, RunIn4)
{
	// test array formatting with multiple one-line-statement braces
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst ct_data static_ltree[L_CODES+2] =\n"
	    "{   {{ 12},{  8}}, {{140},{  8}}, {{ 76},{  8}}, {{204},{  8}}, {{ 44},{  8}},\n"
	    "    {{172},{  8}}, {{108},{  8}}, {{236},{  8}}, {{ 28},{  8}}, {{156},{  8}}\n"
	    "};\n";
	char text[] =
	    "\nconst ct_data static_ltree[L_CODES+2] = {\n"
	    "	{{ 12},{  8}}, {{140},{  8}}, {{ 76},{  8}}, {{204},{  8}}, {{ 44},{  8}},\n"
	    "	{{172},{  8}}, {{108},{  8}}, {{236},{  8}}, {{ 28},{  8}}, {{156},{  8}}\n"
	    "};\n";
	char options[] = "style=java, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayAttachCpp, RunIn5)
{
	// test array formatting
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst int Chunks[][8] =\n"
	    "{   { 1,1,1,1,\n"
	    "      0,0,0,0 }\n"
	    "};\n";
	char text[] =
	    "\nconst int Chunks[][8] = {\n"
	    "	{\n"
	    "		1,1,1,1,\n"
	    "		0,0,0,0\n"
	    "	}\n"
	    "};\n";
	char options[] = "style=java, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayAttachCpp, RunIn6)
{
	// test array formatting
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst LanguageInfo g_LanguagePrefs [] =\n"
	    "{   // C++\n"
	    "    {   _T(\"C++\"),\n"
	    "        _T(\"*.c;*.cc;*.cpp;*.cxx;*.cs;*.h;*.hh;*.hpp;*.hxx;*.sma\"),\n"
	    "        wxSCI_LEX_CPP,\n"
	    "        {   {TOKEN_DEFAULT, NULL},\n"
	    "            {TOKEN_COMMENT, NULL},\n"
	    "        }\n"
	    "    }\n"
	    "};\n";
	char text[] =
	    "\nconst LanguageInfo g_LanguagePrefs [] = {\n"
	    "	// C++\n"
	    "	{\n"
	    "		_T(\"C++\"),\n"
	    "		_T(\"*.c;*.cc;*.cpp;*.cxx;*.cs;*.h;*.hh;*.hpp;*.hxx;*.sma\"),\n"
	    "		wxSCI_LEX_CPP,\n"
	    "		{	{TOKEN_DEFAULT, NULL},\n"
	    "			{TOKEN_COMMENT, NULL},\n"
	    "		}\n"
	    "	}\n"
	    "};\n";
	char options[] = "style=java, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayAttachCpp, RunInLineComments)
{
	// test array formatting with following line comments
	// should attach run-in line comment run-ins
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{   // comment\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] = {\n"
	    "	// comment\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=java, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayAttachCpp, RunInComments)
{
	// test array formatting with following comments
	// should attach run-in comment run-ins
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{   /* comment */\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] = {\n"
	    "	/* comment */\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=java, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayAttachCpp, InStatement1)
{
	// in-statement arrays should remain unchanged
	// use indent=tab to check indent character
	char textIn[] =
	    "\nvoid foo() {\n"
	    "    char* a[] = { \"one\", \"two\",\n"
	    "                  \"uno\", \"dos\"\n"
	    "                };\n"
	    "};\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "	char* a[] = { \"one\", \"two\",\n"
	    "	              \"uno\", \"dos\"\n"
	    "	            };\n"
	    "};\n";
	char options[] = "style=java, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayAttachCpp, InStatement2)
{
	// test array formatting with run-in braces
	// and a non in-statement brace on the same line
	// use indent=tab to check indent character
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   wxChar* names[] = {\n"
	    "        _T(\"cvt \"),\n"
	    "        NULL\n"
	    "    };\n"
	    "\n"
	    "    bar1();\n"
	    "    bar2();\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "	wxChar* names[] = {\n"
	    "		_T(\"cvt \"),\n"
	    "		NULL\n"
	    "	};\n"
	    "\n"
	    "	bar1();\n"
	    "	bar2();\n"
	    "}\n";
	char options[] = "style=java, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayAttachCpp, LineComments)
{
	// test array formatting with line-end comments
	// should attach a broken brace
	char textIn[] =
	    "\nconst char *foo[] = // comment\n"
	    "{\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] = { // comment\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayAttachCpp, Comments)
{
	// test array formatting with comments
	// should attach a broken brace
	// UNLESS it is multi-line
	// TODO: Attach brace to line-end comment
	char textIn[] =
	    "\nconst char *foo[] = /* comment */\n"
	    "{\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n"
	    "\n"
	    "\nconst char *foo[] = /* comment\n"
	    "    */\n"
	    "{\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] = /* comment */\n"
	    "{\n"				//brace should attach
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n"
	    "\n"
	    "\nconst char *foo[] = /* comment\n"
	    "    */\n"
	    "{\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayAttachCpp, Sans)
{
	// test array formatting
	// should not attach if preceded by an empty line
	char text[] =
	    "\nconst char *foo[] =\n"
	    "\n"
	    "{\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayAttachCpp, Enum)
{
	// test enum formatting
	// the enum brace should be space padded and should not be broken
	char textIn[] =
	    "\nvoid foo() {\n"
	    "    enum SQGeneratorState{ eRunning, eSuspended, eDead };\n"
	    "};\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    enum SQGeneratorState { eRunning, eSuspended, eDead };\n"
	    "};\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C++ Array Linux Brace Options
// NOTE: Array braces are NOT converted TO or FROM RunIn style
// Linux array braces do NOT have complete tests.
//-------------------------------------------------------------------------

TEST(BracesArrayLinuxCpp, Break)
{
	// linux attaches the opening brace for arrays
	// test array formatting with broken braces
	// should attach a broken brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] = {\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=kr, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayLinuxCpp, Attach)
{
	// linux attaches the opening brace for arrays
	// test array formatting with attached braces
	// should not change attached brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] = {\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] = {\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=kr, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayLinuxCpp, RunIn1)
{
	// linux attaches the opening brace for arrays
	// test array formatting with run-in braces
	// should attach run-ins
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst int foo[] =\n"
	    "{   FOO1,\n"
	    "    FOO2,\n"
	    "    FOO3,\n"
	    "};\n";
	char text[] =
	    "\nconst int foo[] = {\n"
	    "	FOO1,\n"
	    "	FOO2,\n"
	    "	FOO3,\n"
	    "};\n";
	char options[] = "style=kr, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayLinuxCpp, Enum)
{
	// test enum formatting
	// the enum brace should be space padded and should not be broken
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
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C++ Array RunIn Brace Options
// NOTE: Array braces are NOT converted TO or FROM RunIn style
//-------------------------------------------------------------------------

TEST(BracesArrayRunInCpp, Break1)
{
	// test array formatting with broken braces
	// should run-in a broken brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst int foo[] =\n"
	    "{\n"
	    "    FOO1,\n"
	    "    FOO2,\n"
	    "    FOO3,\n"
	    "};\n";
	char text[] =
	    "\nconst int foo[] =\n"
	    "{	FOO1,\n"
	    "	FOO2,\n"
	    "	FOO3,\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, Break2)
{
	// test array formatting with quotes
	// should run-in a broken brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =\n"
	    "{	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, Break3)
{
	// test array formatting with multiple braces
	// should run-in all braces
	// use indent=tab to check indent character
	char textIn[] =
	    "\nstatic wxString codes[2][4] =\n"
	    "{\n"
	    "    {\n"
	    "        _T(\"0001101\"),_T(\"0100011\"),\n"
	    "        _T(\"0110001\"),_T(\"0001011\")\n"
	    "    },\n"
	    "    {\n"
	    "        _T(\"1110010\"),_T(\"1011100\"),\n"
	    "        _T(\"1001110\"),_T(\"1110100\")\n"
	    "    }\n"
	    "};\n";
	char text[] =
	    "\nstatic wxString codes[2][4] =\n"
	    "{	{	_T(\"0001101\"),_T(\"0100011\"),\n"
	    "		_T(\"0110001\"),_T(\"0001011\")\n"
	    "	},\n"
	    "	{	_T(\"1110010\"),_T(\"1011100\"),\n"
	    "		_T(\"1001110\"),_T(\"1110100\")\n"
	    "	}\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, Break4)
{
	// test array formatting with multiple one-line-statement braces
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst ct_data static_ltree[L_CODES+2] =\n"
	    "{\n"
	    "    {{ 12},{  8}}, {{140},{  8}}, {{ 76},{  8}}, {{204},{  8}}, {{ 44},{  8}},\n"
	    "    {{172},{  8}}, {{108},{  8}}, {{236},{  8}}, {{ 28},{  8}}, {{156},{  8}}\n"
	    "};\n";
	char text[] =
	    "\nconst ct_data static_ltree[L_CODES+2] =\n"
	    "{	{{ 12},{  8}}, {{140},{  8}}, {{ 76},{  8}}, {{204},{  8}}, {{ 44},{  8}},\n"
	    "	{{172},{  8}}, {{108},{  8}}, {{236},{  8}}, {{ 28},{  8}}, {{156},{  8}}\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, Break5)
{
	// test array formatting
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst int Chunks[][8] =\n"
	    "{\n"
	    "    {\n"
	    "      1,1,1,1,\n"
	    "      0,0,0,0 }\n"
	    "};\n";
	char text[] =
	    "\nconst int Chunks[][8] =\n"
	    "{	{	1,1,1,1,\n"
	    "		0,0,0,0\n"
	    "	}\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, Break6)
{
	// test array formatting
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst LanguageInfo g_LanguagePrefs [] =\n"
	    "{\n"
	    "    // C++\n"
	    "    {\n"
	    "        _T(\"C++\"),\n"
	    "        _T(\"*.c;*.cc;*.cpp;*.cxx;*.cs;*.h;*.hh;*.hpp;*.hxx;*.sma\"),\n"
	    "        wxSCI_LEX_CPP,\n"
	    "        {\n"
	    "            {TOKEN_DEFAULT, NULL},\n"
	    "            {TOKEN_COMMENT, NULL},\n"
	    "        }\n"
	    "    }\n"
	    "};\n";
	char text[] =
	    "\nconst LanguageInfo g_LanguagePrefs [] =\n"
	    "{	// C++\n"
	    "	{	_T(\"C++\"),\n"
	    "		_T(\"*.c;*.cc;*.cpp;*.cxx;*.cs;*.h;*.hh;*.hpp;*.hxx;*.sma\"),\n"
	    "		wxSCI_LEX_CPP,\n"
	    "		{	{TOKEN_DEFAULT, NULL},\n"
	    "			{TOKEN_COMMENT, NULL},\n"
	    "		}\n"
	    "	}\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, Attach1)
{
	// test array formatting with attached braces
	// should run-in an attached brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst int foo[] = {\n"
	    "    FOO1,\n"
	    "    FOO2,\n"
	    "    FOO3,\n"
	    "};\n";
	char text[] =
	    "\nconst int foo[] =\n"
	    "{	FOO1,\n"
	    "	FOO2,\n"
	    "	FOO3,\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, Attach2)
{
	// test array formatting with quotes
	// should run-in an attached brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] = {\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =\n"
	    "{	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, Attach3)
{
	// test array formatting with multiple braces
	// should run-in all braces
	// use indent=tab to check indent character
	char textIn[] =
	    "\nstatic wxString codes[2][4] = {\n"
	    "    {\n"
	    "        _T(\"0001101\"),_T(\"0100011\"),\n"
	    "        _T(\"0110001\"),_T(\"0001011\")\n"
	    "    },\n"
	    "    {\n"
	    "        _T(\"1110010\"),_T(\"1011100\"),\n"
	    "        _T(\"1001110\"),_T(\"1110100\")\n"
	    "    }\n"
	    "};\n";
	char text[] =
	    "\nstatic wxString codes[2][4] =\n"
	    "{	{	_T(\"0001101\"),_T(\"0100011\"),\n"
	    "		_T(\"0110001\"),_T(\"0001011\")\n"
	    "	},\n"
	    "	{	_T(\"1110010\"),_T(\"1011100\"),\n"
	    "		_T(\"1001110\"),_T(\"1110100\")\n"
	    "	}\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, Attach4)
{
	// test array formatting with multiple one-line-statement braces
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst ct_data static_ltree[L_CODES+2] = {\n"
	    "    {{ 12},{  8}}, {{140},{  8}}, {{ 76},{  8}}, {{204},{  8}}, {{ 44},{  8}},\n"
	    "    {{172},{  8}}, {{108},{  8}}, {{236},{  8}}, {{ 28},{  8}}, {{156},{  8}}\n"
	    "};\n";
	char text[] =
	    "\nconst ct_data static_ltree[L_CODES+2] =\n"
	    "{	{{ 12},{  8}}, {{140},{  8}}, {{ 76},{  8}}, {{204},{  8}}, {{ 44},{  8}},\n"
	    "	{{172},{  8}}, {{108},{  8}}, {{236},{  8}}, {{ 28},{  8}}, {{156},{  8}}\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, Attach5)
{
	// test array formatting
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst int Chunks[][8] = {\n"
	    "    {\n"
	    "      1,1,1,1,\n"
	    "      0,0,0,0 }\n"
	    "};\n";
	char text[] =
	    "\nconst int Chunks[][8] =\n"
	    "{	{	1,1,1,1,\n"
	    "		0,0,0,0\n"
	    "	}\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, Attach6)
{
	// test array formatting
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst LanguageInfo g_LanguagePrefs [] = {\n"
	    "    // C++\n"
	    "    {\n"
	    "        _T(\"C++\"),\n"
	    "        _T(\"*.c;*.cc;*.cpp;*.cxx;*.cs;*.h;*.hh;*.hpp;*.hxx;*.sma\"),\n"
	    "        wxSCI_LEX_CPP,\n"
	    "        {\n"
	    "            {TOKEN_DEFAULT, NULL},\n"
	    "            {TOKEN_COMMENT, NULL},\n"
	    "        }\n"
	    "    }\n"
	    "};\n";
	char text[] =
	    "\nconst LanguageInfo g_LanguagePrefs [] =\n"
	    "{	// C++\n"
	    "	{	_T(\"C++\"),\n"
	    "		_T(\"*.c;*.cc;*.cpp;*.cxx;*.cs;*.h;*.hh;*.hpp;*.hxx;*.sma\"),\n"
	    "		wxSCI_LEX_CPP,\n"
	    "		{	{TOKEN_DEFAULT, NULL},\n"
	    "			{TOKEN_COMMENT, NULL},\n"
	    "		}\n"
	    "	}\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, AttachLineComments)
{
	// test array formatting with attach to run-in with following comments
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] = { // comment\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =   // comment\n"
	    "{	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, AttachComments)
{
	// test array formatting with attach to run-in with following comments
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] = { /* comment */\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =   /* comment */\n"
	    "{	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, RunIn1)
{
	// test array formatting
	// should NOT change a run-in brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst int foo[] =\n"
	    "{   FOO1,\n"
	    "    FOO2,\n"
	    "    FOO3,\n"
	    "};\n";
	char text[] =
	    "\nconst int foo[] =\n"
	    "{	FOO1,\n"
	    "	FOO2,\n"
	    "	FOO3,\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, RunIn2)
{
	// test array formatting with quotes
	// should NOT change a run-in brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{   \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =\n"
	    "{	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, RunIn3)
{
	// test array formatting with multiple braces
	// should NOT change a run-in brace
	// use indent=tab to check indent character
	char textIn[] =
	    "\nstatic wxString codes[2][4] =\n"
	    "{   {   _T(\"0001101\"),_T(\"0100011\"),\n"
	    "        _T(\"0110001\"),_T(\"0001011\")\n"
	    "    },\n"
	    "    {   _T(\"1110010\"),_T(\"1011100\"),\n"
	    "        _T(\"1001110\"),_T(\"1110100\")\n"
	    "    }\n"
	    "};\n";
	char text[] =
	    "\nstatic wxString codes[2][4] =\n"
	    "{	{	_T(\"0001101\"),_T(\"0100011\"),\n"
	    "		_T(\"0110001\"),_T(\"0001011\")\n"
	    "	},\n"
	    "	{	_T(\"1110010\"),_T(\"1011100\"),\n"
	    "		_T(\"1001110\"),_T(\"1110100\")\n"
	    "	}\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, RunIn4)
{
	// test array formatting with multiple one-line-statement braces
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst ct_data static_ltree[L_CODES+2] =\n"
	    "{   {{ 12},{  8}}, {{140},{  8}}, {{ 76},{  8}}, {{204},{  8}}, {{ 44},{  8}},\n"
	    "    {{172},{  8}}, {{108},{  8}}, {{236},{  8}}, {{ 28},{  8}}, {{156},{  8}}\n"
	    "};\n";
	char text[] =
	    "\nconst ct_data static_ltree[L_CODES+2] =\n"
	    "{	{{ 12},{  8}}, {{140},{  8}}, {{ 76},{  8}}, {{204},{  8}}, {{ 44},{  8}},\n"
	    "	{{172},{  8}}, {{108},{  8}}, {{236},{  8}}, {{ 28},{  8}}, {{156},{  8}}\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, RunIn5)
{
	// test array formatting
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst int Chunks[][8] =\n"
	    "{   { 1,1,1,1,\n"
	    "      0,0,0,0 }\n"
	    "};\n";
	char text[] =
	    "\nconst int Chunks[][8] =\n"
	    "{	{	1,1,1,1,\n"
	    "		0,0,0,0\n"
	    "	}\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, RunIn6)
{
	// test array formatting
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst LanguageInfo g_LanguagePrefs [] =\n"
	    "{   // C++\n"
	    "    {   _T(\"C++\"),\n"
	    "        _T(\"*.c;*.cc;*.cpp;*.cxx;*.cs;*.h;*.hh;*.hpp;*.hxx;*.sma\"),\n"
	    "        wxSCI_LEX_CPP,\n"
	    "        {   {TOKEN_DEFAULT, NULL},\n"
	    "            {TOKEN_COMMENT, NULL},\n"
	    "        }\n"
	    "    }\n"
	    "};\n";
	char text[] =
	    "\nconst LanguageInfo g_LanguagePrefs [] =\n"
	    "{	// C++\n"
	    "	{	_T(\"C++\"),\n"
	    "		_T(\"*.c;*.cc;*.cpp;*.cxx;*.cs;*.h;*.hh;*.hpp;*.hxx;*.sma\"),\n"
	    "		wxSCI_LEX_CPP,\n"
	    "		{	{TOKEN_DEFAULT, NULL},\n"
	    "			{TOKEN_COMMENT, NULL},\n"
	    "		}\n"
	    "	}\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, RunInLineComments1)
{
	// test array formatting
	// should not change run-in line comment run-ins
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{   // comment\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =\n"
	    "{	// comment\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, RunInLineComments2)
{
	// test array formatting
	// should NOT run-in a non-indent line comment
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{\n"
	    "// comment\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =\n"
	    "{\n"
	    "// comment\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, RunInComments)
{
	// test array formatting
	// should not change run-in comment run-ins
	// use indent=tab to check indent character
	char textIn[] =
	    "\nconst char *foo[] =\n"
	    "{   /* comment */\n"
	    "    \"foo1\",\n"
	    "    \"foo2\",\n"
	    "    \"foo3\",\n"
	    "};\n";
	char text[] =
	    "\nconst char *foo[] =\n"
	    "{	/* comment */\n"
	    "	\"foo1\",\n"
	    "	\"foo2\",\n"
	    "	\"foo3\",\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, InStatement1)
{
	// in-statement arrays should remain unchanged
	// use indent=tab to check indent character
	char text[] =
	    "\nvoid foo()\n"
	    "{	char* a[] = { \"one\", \"two\",\n"
	    "	              \"uno\", \"dos\"\n"
	    "	            };\n"
	    "};\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, InStatement2)
{
	// test array formatting with run-in braces
	// and a non in-statement brace on the same line
	// use indent=tab to check indent character
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    wxChar* names[] = {\n"
	    "        _T(\"cvt \"),\n"
	    "        NULL\n"
	    "    };\n"
	    "\n"
	    "    bar1();\n"
	    "    bar2();\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{	wxChar* names[] =\n"
	    "	{	_T(\"cvt \"),\n"
	    "		NULL\n"
	    "	};\n"
	    "\n"
	    "	bar1();\n"
	    "	bar2();\n"
	    "}\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, InStatement3)
{
	// test array formatting with run-in braces
	// and a non in-statement brace on the same line
	// use indent=tab to check indent character
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   wxChar* names[] = {\n"
	    "        _T(\"cvt \"),\n"
	    "        NULL\n"
	    "    };\n"
	    "\n"
	    "    bar1();\n"
	    "    bar2();\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{	wxChar* names[] =\n"
	    "	{	_T(\"cvt \"),\n"
	    "		NULL\n"
	    "	};\n"
	    "\n"
	    "	bar1();\n"
	    "	bar2();\n"
	    "}\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayRunInCpp, Enum)
{
	// test enum formatting
	// the enum brace should be space padded and should not be broken
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   enum SQGeneratorState{ eRunning, eSuspended, eDead };\n"
	    "};\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   enum SQGeneratorState { eRunning, eSuspended, eDead };\n"
	    "};\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C++ Array Non-In-Statement Brace Options
//-------------------------------------------------------------------------

TEST(BracesArrayCpp, ClearNonInStatementArray1)
{
	// Setting of isImmediatelyPostNonInStmt flag.
	// The isNonInStatementArray flag should be cleared at the end of the array.
	// If it is not, the continuation lines in the "for" statement will not be indented.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    int folderID[nbGrpFolder][nbControl] = {\\\n"
	    "        {IDC_FOLDEROPEN_FG, IDC_FOLDEROPEN_BG},\\\n"
	    "        {IDC_FOLDERCLOSE_FG, IDC_FOLDERCLOSE_BG}\\\n"
	    "    };\n"
	    "\n"
	    "    for (TiXmlNodeA *childNode = node->ChildElement(Item);\n"
	    "            childNode ;\n"
	    "            childNode = childNode->NextSibling(Item))\n"
	    "    {\n"
	    "        TiXmlElementA *element = childNode->ToElement();\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesArrayCpp, ClearNonInStatementArray2)
{
	// Setting of isImmediatelyPostNonInStmt flag.
	// The isNonInStatementArray flag should be NOT cleared at the "},{" sequence.
	// If it is, the following lines containing a dot "." will have an indent.
	char text[] =
	    "\ntype_t var = {\n"
	    "items:\n"
	    "    (type2_t[]) {\n"
	    "        {\n"
	    "            NULL,\n"
	    "        }, {\n"
	    "            .log = 1,\n"
	    "            .use_log = 1,\n"
	    "            .send_log = 1,\n"
	    "        },\n"
	    "        NULL\n"
	    "    }\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------

}  // namespace
