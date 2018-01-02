// AStyleTest_BracesCpp1.cpp
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
// AStyle C++ Default Brace Options
//-------------------------------------------------------------------------

struct BracesNoneCppF : public Test
{
	string textStr;
	const char* textIn;

	BracesNoneCppF()
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

TEST_F(BracesNoneCppF, Default)
{
	// test default braces option (do not change)
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
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesNoneCppF, Namespace)
{
	// test default braces option (do not change)
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
	    "    {\n"
	    "        if (isFoo) {\n"
	    "            bar();\n"
	    "        } else {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesNoneCppF, Class)
{
	// test default braces option (do not change)
	// indent class blocks
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "class FooClass\n"
	    "{\n"
	    "    private:\n"
	    "        bool var1;\n"
	    "        void func1();\n"
	    "    protected:\n"
	    "        bool var2;\n"
	    "        void func2();\n"
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
	char options[] = "indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesNoneCppF, NamespaceClass)
{
	// test default braces option (do not change)
	// indented namespace and class
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "    class FooClass\n"
	    "    {\n"
	    "        private:\n"
	    "            bool var1;\n"
	    "            void func1();\n"
	    "        protected:\n"
	    "            bool var2;\n"
	    "            void func2();\n"
	    "    };\n"
	    "\n"
	    "    void FooClass::Foo(bool isFoo)\n"
	    "    {\n"
	    "        if (isFoo) {\n"
	    "            bar();\n"
	    "        } else {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, EmptyBraces)
{
	// test default braces option (do not change)
	// do not change empty braces
	char text[] =
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
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, EmptyBracesWithComments)
{
	// test default braces option (do not change) with ending comments
	// do not change empty braces
	char text[] =
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
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, Extern)
{
	// test default braces option (do not change)
	// extern statement should not change its brace type
	// and should NOT use continuation indents
	char text[] =
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
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, Assembler)
{
	// assembler statement should be formatted
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    _asm\n"
	    "    {\n"
	    "        mov eax, fs:[0x8]\n"
	    "        mov dx, 0xD007\n"
	    "        out dx, al\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, Break)
{
	// test default braces option with broken braces
	char text[] =
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
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, Attach)
{
	// test default braces option with attached braces
	char text[] =
	    "\nvoid Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, Linux)
{
	// test default braces option with linux braces
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, RunIn1)
{
	// test default braces option with horstmann braces
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, RunIn2)
{
	// test default braces option with horstmann braces
	// and 2 braces on the same line
	char text[] =
	    "\nvoid foo()\n"
	    "{   if(isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, Misc1)
{
	// test default braces option with the following unusual format
	char textIn[] =
	    "\nvoid foo1() { error = false;\n"
	    "              errorId = 0;\n"
	    "            }\n"
	    "\n"
	    "void foo2() { // comment2\n"
	    "              error = false;\n"
	    "              errorId = 0;\n"
	    "            }\n"
	    "\n"
	    "void foo3() { /* comment3 */\n"
	    "              error = false;\n"
	    "              errorId = 0;\n"
	    "            }\n";
	char text[] =
	    "\nvoid foo1() {\n"
	    "    error = false;\n"
	    "    errorId = 0;\n"
	    "}\n"
	    "\n"
	    "void foo2() { // comment2\n"
	    "    error = false;\n"
	    "    errorId = 0;\n"
	    "}\n"
	    "\n"
	    "void foo3() { /* comment3 */\n"
	    "    error = false;\n"
	    "    errorId = 0;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, Misc2)
{
	// test default braces option with the following unusual format
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (bar1()) {/* dummy */}\n"
	    "\n"
	    "    if (bar1()) {;/* dummy */}\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, Misc3)
{
	// test default braces option with a macro
	// brace type will be incorrectly classified as an array
	// but should not break at the semi colon
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    YY_RULE_SETUP\n"
	    "    { BEGIN(list); return CONT; }\n"
	    "    YY_BREAK\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, ClassContinuation_Attach)
{
	// test with class continuation and attached braces
	char text[] =
	    "\nclass Foo :\n"
	    "    public Bar {\n"
	    "public:\n"
	    "    Foo(T *in);\n"
	    "};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, ClassContinuation_Break)
{
	// test with class continuation and broken braces
	char text[] =
	    "\nclass Foo :\n"
	    "    public Bar\n"
	    "{\n"
	    "public:\n"
	    "    Foo(T *in);\n"
	    "};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, RunInIndent1)
{
	// test default braces option with horstmann braces
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
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, RunInIndent2)
{
	// test default braces option with horstmann braces
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
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, RunInComment1)
{
	// test default braces option with horstmann braces
	// with the indent changed from 2 to 4
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{ if (isFoo)\n"
	    "  { /* comment1 */\n"
	    "    foo();\n"
	    "  }\n"
	    "  else\n"
	    "  { /* comment2\n"
	    "     *\n"
	    "     */\n"
	    "    bar();\n"
	    "  }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo()\n"
	    "{   if (isFoo)\n"
	    "    {   /* comment1 */\n"
	    "        foo();\n"
	    "    }\n"
	    "    else\n"
	    "    {   /* comment2\n"
	    "         *\n"
	    "         */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, RunInComment2)
{
	// test default braces option with horstmann braces
	// with the indent changed from 6 to 4
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{     if (isFoo)\n"
	    "      {     /* comment1 */\n"
	    "            foo();\n"
	    "      }\n"
	    "      else\n"
	    "      {     /* comment2\n"
	    "             *\n"
	    "             */\n"
	    "            bar();\n"
	    "      }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo()\n"
	    "{   if (isFoo)\n"
	    "    {   /* comment1 */\n"
	    "        foo();\n"
	    "    }\n"
	    "    else\n"
	    "    {   /* comment2\n"
	    "         *\n"
	    "         */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, LineCommentsBreak)
{
	// line comments following broken braces should be unchanged
	char text[] =
	    "\nvoid foo(bool isFoo) // comment0\n"
	    "{\n"
	    "    // comment1\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        // comment2\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, LineCommentsAttach)
{
	// line comments following attached braces should be unchanged
	char text[] =
	    "\nvoid foo(bool isFoo) {    // comment1\n"
	    "    if (isFoo) {          // comment2\n"
	    "        // comment3\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, LineCommentsRunIn)
{
	// line comments following horstmann braces should be unchanged
	char text[] =
	    "\nvoid foo(bool isFoo) // comment0\n"
	    "{   // comment1\n"
	    "    if (isFoo)\n"
	    "    {   // comment2\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, CommentsBreak1)
{
	// broken braces should not change
	char text[] =
	    "\nvoid (foo)\n"
	    "{\n"
	    "    /*\n"
	    "     * comment\n"
	    "     */\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, CommentsAttach1)
{
	// attached braces should not change
	char text[] =
	    "\nvoid (foo) {\n"
	    "    /*\n"
	    "     * comment\n"
	    "     */\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, CommentsRunIn1)
{
	// horstmann braces should not change
	char text[] =
	    "\nvoid (foo)\n"
	    "{   /*\n"
	    "     * comment\n"
	    "     */\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, CommentsBreak2)
{
	// broken braces with following comments
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
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, CommentsAttach2)
{
	// attached braces with following comments
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
	char text[] = "\nvoid (foo) {\n"
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
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, CommentsRunIn2)
{
	// horstmann braces with following comments
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
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, CommentsBreak3)
{
	// comments following broken braces should be unchanged
	char text[] =
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
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, CommentsAttach3)
{
	// comments following attached braces should be unchanged
	// multi-line comments following attached braces break
	//    but are NOT aligned
	char textIn[] =
	    "\nvoid foo1(bool isFoo) { /* comment1 */\n"
	    "    if(isFoo) { /* comment2 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo) { /* comment3\n"
	    "     *\n"
	    "     */\n"
	    "    if(isFoo) { /* comment4\n"
	    "                 *\n"
	    "                 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo1(bool isFoo) { /* comment1 */\n"
	    "    if(isFoo) { /* comment2 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo) {\n"
	    "    /* comment3\n"
	    "         *\n"
	    "         */\n"
	    "    if(isFoo) {\n"
	    "        /* comment4\n"
	    "                     *\n"
	    "                     */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, CommentsRunIn3)
{
	// comments following horstmann braces should be unchanged
	char text[] =
	    "\nvoid foo1(bool isFoo) /* comment0 */\n"
	    "{   /* comment1 */\n"
	    "    if(isFoo)\n"
	    "    {   /* comment2 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo) /* comment0 */\n"
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
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, MultipleCommentsBreak)
{
	// multiple comments with broken braces should remain unchanged
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo) /* comment1 */  // comment2\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, MultipleCommentsAttach)
{
	// multiple comments with attached braces remain unchanged
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo) { /* comment1 */  // comment2\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesNoneCpp, MultipleCommentsRunIn)
{
	// multiple comments with horstmann braces remain unchanged
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo) /* comment1 */  // comment2\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C++ Break Brace Options
//-------------------------------------------------------------------------

struct BracesBreakCppF : public Test
{
	string textStr;
	const char* textIn;

	BracesBreakCppF()
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

TEST_F(BracesBreakCppF, LongOption)
{
	// test break braces option
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
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesBreakCppF, ShortOption)
{
	// test break braces short option
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
	    "\n"
	    "}   // end FooName\n";
	char options[] = "-A1";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesBreakCppF, Namespace)
{
	// test break braces option
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
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=allman, indent-namespaces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesBreakCppF, Class)
{
	// test break braces option
	// indent class blocks
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "class FooClass\n"
	    "{\n"
	    "    private:\n"
	    "        bool var1;\n"
	    "        void func1();\n"
	    "    protected:\n"
	    "        bool var2;\n"
	    "        void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo)\n"
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
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=allman, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesBreakCppF, NamespaceClass)
{
	// test break braces option
	// indented namespace and class
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "    class FooClass\n"
	    "    {\n"
	    "        private:\n"
	    "            bool var1;\n"
	    "            void func1();\n"
	    "        protected:\n"
	    "            bool var2;\n"
	    "            void func2();\n"
	    "    };\n"
	    "\n"
	    "    void FooClass::Foo(bool isFoo)\n"
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
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=allman, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, EmptyBraces)
{
	// test break braces option
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
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, EmptyBracesWithComments)
{
	// test break braces option with ending comments
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
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, Extern)
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
	    "\nextern \"C\" {\n"
	    "	extern void foo1()\n"
	    "	{\n"
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
	char options[] = "indent=tab, style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, Assembler)
{
	// assembler statement should be formatted
	char textIn[] =
	    "\nvoid foo() {\n"
	    "    _asm {\n"
	    "        mov eax, fs:[0x8]\n"
	    "        mov dx, 0xD007\n"
	    "        out dx, al\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    _asm\n"
	    "    {\n"
	    "        mov eax, fs:[0x8]\n"
	    "        mov dx, 0xD007\n"
	    "        out dx, al\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, Break)
{
	// test break braces option with broken braces
	char text[] =
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
	char options[] = "style=allman";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, Attach)
{
	// test break braces option with attached braces
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
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, Linux)
{
	// test break braces option with linux braces
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
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, RunIn1)
{
	// test break braces option with horstmann braces
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
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
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, RunIn2)
{
	// test default braces option with horstmann braces
	// and 2 braces on the same line
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   if(isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if(isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, Misc1)
{
	// test break braces option with the following unusual format
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
	    "{\n"
	    "    error = false;\n"
	    "    errorId = 0;\n"
	    "}\n"
	    "\n"
	    "void foo2()    // comment2\n"
	    "{\n"
	    "    error = false;\n"
	    "    errorId = 0;\n"
	    "}\n"
	    "\n"
	    "void foo3()    /* comment3 */\n"
	    "{\n"
	    "    error = false;\n"
	    "    errorId = 0;\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, Misc2)
{
	// test break braces option with the following unusual format
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (bar1()) {/* dummy */}\n"
	    "\n"
	    "    if (bar1()) {;/* dummy */}\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, Misc3)
{
	// test break braces option with a macro
	// brace type will be incorrectly classified as an array
	// but should not break at the semi colon
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    YY_RULE_SETUP\n"
	    "    { BEGIN(list); return CONT; }\n"
	    "    YY_BREAK\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, ClassContinuation)
{
	// test with class continuation and broken braces
	char text[] =
	    "\nclass Foo :\n"
	    "    public Bar\n"
	    "{\n"
	    "public:\n"
	    "    Foo(T *in);\n"
	    "};\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, LineCommentsBreak)
{
	// comments following broken braces should be unchanged
	char text[] =
	    "\nvoid foo(bool isFoo) // comment0\n"
	    "{\n"
	    "    // comment1\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        // comment2\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, LineCommentsAttach)
{
	// comments following attached braces should stay attached to the line
	char textIn[] =
	    "\nvoid foo(bool isFoo) {  // comment1\n"
	    "    if(isFoo) {           // comment2\n"
	    "        // comment3\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo(bool isFoo)    // comment1\n"
	    "{\n"
	    "    if(isFoo)             // comment2\n"
	    "    {\n"
	    "        // comment3\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, LineCommentsRunIn)
{
	// comments following horstmann braces should be broken
	char textIn[] =
	    "\nvoid foo(bool isFoo) // comment0\n"
	    "{   // comment1\n"
	    "    if (isFoo)\n"
	    "    {   // comment2\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo(bool isFoo) // comment0\n"
	    "{\n"
	    "    // comment1\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        // comment2\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, LineCommentsClosingHeader)
{
	// test comment alignment when a closing header is broken from a closing brace
	char textIn[] =
	    "\nvoid foo() {     // comment0\n"
	    "    if (isFoo) { // comment1\n"
	    "        bar1();  // comment2\n"
	    "    } else {     // comment3\n"
	    "        bar2();  // comment4\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()       // comment0\n"
	    "{\n"
	    "    if (isFoo)   // comment1\n"
	    "    {\n"
	    "        bar1();  // comment2\n"
	    "    }\n"
	    "    else         // comment3\n"
	    "    {\n"
	    "        bar2();  // comment4\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, CommentsBreak1)
{
	// broken braces should not change
	char text[] =
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
	char options[] = "style=allman";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, CommentsAttach1)
{
	// break attached braces with following comments
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
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, CommentsRunIn1)
{
	// break horstmann braces with following comments
	char textIn[] =
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
	char text[] =
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
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, CommentsBreak2)
{
	// broken braces with following comments
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
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, CommentsAttach2)
{
	// break attached braces with following comments
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
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, CommentsRunIn2)
{
	// break horstmann braces with following comments
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
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, CommentsBreak3)
{
	// comments following broken braces should be unchanged
	char text[] =
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
	char options[] = "style=allman";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, CommentsAttach3)
{
	// test comments following braces
	// multi-line comments following attached braces break
	//    but are NOT aligned
	char textIn[] =
	    "\nvoid foo1(bool isFoo) {   /* comment1 */\n"
	    "    if(isFoo) {  /* comment2 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo) { /* comment3\n"
	    "     *\n"
	    "     */\n"
	    "    if(isFoo) { /* comment4\n"
	    "                 *\n"
	    "                 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo1(bool isFoo)     /* comment1 */\n"
	    "{\n"
	    "    if(isFoo)    /* comment2 */\n"
	    "    {\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo)\n"
	    "{\n"
	    "    /* comment3\n"
	    "         *\n"
	    "         */\n"
	    "    if(isFoo)\n"
	    "    {\n"
	    "        /* comment4\n"
	    "                     *\n"
	    "                     */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, CommentsRunIn3)
{
	// comments following horstmann braces should be broken
	char textIn[] =
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
	char text[] =
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
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, MultipleCommentsBreak)
{
	// multiple comments with broken braces should remain unchanged
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo) /* comment1 */  // comment2\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, MultipleCommentsAttach)
{
	// multiple comments with attached braces should remain unchanged
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo) { /* comment1 */  // comment2\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesBreakCpp, MultipleCommentsRunIn)
{
	// multiple comments with horstmann braces should be broken
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo) /* comment1 */  // comment2\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo) /* comment1 */  // comment2\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C++ Attach Brace Options
//-------------------------------------------------------------------------

struct BracesAttachCppF : public Test
{
	string textStr;
	const char* textIn;

	BracesAttachCppF()
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

TEST_F(BracesAttachCppF, LongOption)
{
	// test attach braces option
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "class FooClass {\n"
	    "private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesAttachCppF, ShortOption)
{
	// test attach braces option
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "class FooClass {\n"
	    "private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "-A2";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesAttachCppF, Namespace)
{
	// test attach braces option
	// indented namespace
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "    class FooClass {\n"
	    "    private:\n"
	    "        bool var1;\n"
	    "        void func1();\n"
	    "    protected:\n"
	    "        bool var2;\n"
	    "        void func2();\n"
	    "    };\n"
	    "\n"
	    "    void FooClass::Foo(bool isFoo) {\n"
	    "        if (isFoo) {\n"
	    "            bar();\n"
	    "        } else {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=java, indent-namespaces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesAttachCppF, Class)
{
	// test attach braces option
	// indent class blocks
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "class FooClass {\n"
	    "    private:\n"
	    "        bool var1;\n"
	    "        void func1();\n"
	    "    protected:\n"
	    "        bool var2;\n"
	    "        void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=java, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesAttachCppF, NamespaceClass)
{
	// test attach braces option
	// indented namespace and class
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "    class FooClass {\n"
	    "        private:\n"
	    "            bool var1;\n"
	    "            void func1();\n"
	    "        protected:\n"
	    "            bool var2;\n"
	    "            void func2();\n"
	    "    };\n"
	    "\n"
	    "    void FooClass::Foo(bool isFoo) {\n"
	    "        if (isFoo) {\n"
	    "            bar();\n"
	    "        } else {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=java, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesAttachCppF, BreakClosing)
{
	// test attach braces option
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "class FooClass {\n"
	    "private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=java, break-closing-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, EmptyBraces)
{
	// test attach braces option
	char text[] =
	    "\nclass FooClass {\n"
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
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, EmptyBracesWithComments)
{
	// test attach braces option with ending comments
	char text[] =
	    "\nclass FooClass {\n"
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
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, Extern)
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
	    "\nextern \"C\" {\n"
	    "	extern void foo1() {\n"
	    "		bar1();\n"
	    "	}\n"
	    "}\n"
	    "\n"
	    "extern \"C\"\n"
	    "{\n"
	    "	void foo2() {\n"
	    "		bar2();\n"
	    "	}\n"
	    "}\n";
	char options[] = "indent=tab, style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, Assembler)
{
	// assembler statement should be formatted
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    _asm\n"
	    "    {\n"
	    "        mov eax, fs:[0x8]\n"
	    "        mov dx, 0xD007\n"
	    "        out dx, al\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    _asm {\n"
	    "        mov eax, fs:[0x8]\n"
	    "        mov dx, 0xD007\n"
	    "        out dx, al\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, Break)
{
	// test attach braces option with broken braces
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
	    "\nvoid Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, Attach)
{
	// test attach braces option with attached braces
	char text[] =
	    "\nvoid Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, Linux)
{
	// test attach braces option with linux braces
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
	    "\nvoid Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, RunIn1)
{
	// test attach braces option with horstmann braces
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, RunIn2)
{
	// test default braces option with horstmann braces
	// and 2 braces on the same line
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   if(isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    if(isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, Misc1)
{
	// test attach braces option with the following unusual format
	char textIn[] =
	    "\nvoid foo1() { error = false;\n"
	    "              errorId = 0;\n"
	    "            }\n"
	    "\n"
	    "void foo2() { // comment2\n"
	    "              error = false;\n"
	    "              errorId = 0;\n"
	    "            }\n"
	    "\n"
	    "void foo3() { /* comment3 */\n"
	    "              error = false;\n"
	    "              errorId = 0;\n"
	    "            }\n";
	char text[] =
	    "\nvoid foo1() {\n"
	    "    error = false;\n"
	    "    errorId = 0;\n"
	    "}\n"
	    "\n"
	    "void foo2() { // comment2\n"
	    "    error = false;\n"
	    "    errorId = 0;\n"
	    "}\n"
	    "\n"
	    "void foo3() { /* comment3 */\n"
	    "    error = false;\n"
	    "    errorId = 0;\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, Misc2)
{
	// test attach braces option with the following unusual format
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (bar1()) {/* dummy */}\n"
	    "\n"
	    "    if (bar1()) {;/* dummy */}\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, Misc3)
{
	// test attach braces option with a macro
	// brace type will be incorrectly classified as an array
	// but should not break at the semi colon
	char text[] =
	    "\nvoid foo() {\n"
	    "    YY_RULE_SETUP\n"
	    "    { BEGIN(list); return CONT; }\n"
	    "    YY_BREAK\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, ClassContinuation)
{
	// test with class continuation and attached braces
	char text[] =
	    "\nclass Foo :\n"
	    "    public Bar {\n"
	    "public:\n"
	    "    Foo(T *in);\n"
	    "};\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, LineCommentsBreak)
{
	// comments following broken braces should NOT be attached
	char textIn[] =
	    "\nvoid foo(bool isFoo) // comment0\n"
	    "{\n"
	    "    // comment1\n"
	    "    if(isFoo)\n"
	    "    {\n"
	    "        // comment2\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo(bool isFoo) { // comment0\n"
	    "    // comment1\n"
	    "    if(isFoo) {\n"
	    "        // comment2\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, LineCommentsAttach)
{
	char text[] =
	    "\nvoid foo(bool isFoo) {    // comment1\n"
	    "    if (isFoo) {          // comment2\n"
	    "        // comment3\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, LineCommentsRunIn)
{
	// comments following horstmann braces should be attached
	char textIn[] =
	    "\nvoid foo(bool isFoo) // comment0\n"
	    "{   // comment1\n"
	    "    if (isFoo)\n"
	    "    {   // comment2\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo(bool isFoo) { // comment0\n"
	    "    // comment1\n"
	    "    if (isFoo) {\n"
	    "        // comment2\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, LineCommentsClosingHeader)
{
	// test comment alignment when a closing header is attached to a closing brace
	char textIn[] =
	    "\nvoid foo()       // comment0\n"
	    "{\n"
	    "    if (isFoo)   // comment1\n"
	    "    {\n"
	    "        bar1();  // comment2\n"
	    "    }\n"
	    "    else         // comment3\n"
	    "    {\n"
	    "        bar2();  // comment4\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {     // comment0\n"
	    "    if (isFoo) { // comment1\n"
	    "        bar1();  // comment2\n"
	    "    } else {     // comment3\n"
	    "        bar2();  // comment4\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, CommentsBreak1)
{
	// attach broken braces with following comments
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
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, CommentsAttach1)
{
	// attached braces should not change
	char text[] =
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
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, CommentsRunIn1)
{
	// attach horstmann braces with following comments
	char textIn[] =
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
	char text[] =
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
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, CommentsBreak2)
{
	// attach broken braces with following comments
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
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, CommentsAttach2)
{
	// attached braces with following comments
	char textIn[] =
	    "\nvoid (foo) {\n"
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
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, CommentsRunIn2)
{
	// attach horstmann braces with following comments
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
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, CommentsBreak3)
{
	// comments following broken braces should NOT be attached
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
	    "\nvoid foo1(bool isFoo) { /* comment0 */\n"
	    "    /* comment1 */\n"
	    "    if(isFoo) {\n"
	    "        /* comment2 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo) {\n"
	    "    /* comment3\n"
	    "     *\n"
	    "     */\n"
	    "    if(isFoo) {\n"
	    "        /* comment4\n"
	    "         *\n"
	    "         */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, CommentsAttach3)
{
	// test comments following braces
	// multi-line comments following attached braces break
	//    but are NOT aligned
	char textIn[] =
	    "\nvoid foo1(bool isFoo) { /* comment1 */\n"
	    "    if(isFoo) { /* comment2 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo) { /* comment3\n"
	    "     *\n"
	    "     */\n"
	    "    if(isFoo) { /* comment4\n"
	    "                 *\n"
	    "                 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo1(bool isFoo) { /* comment1 */\n"
	    "    if(isFoo) { /* comment2 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo) {\n"
	    "    /* comment3\n"
	    "         *\n"
	    "         */\n"
	    "    if(isFoo) {\n"
	    "        /* comment4\n"
	    "                     *\n"
	    "                     */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, CommentsRunIn3)
{
	// comments following horstmann braces should NOT be attached
	char textIn[] =
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
	char text[] =
	    "\nvoid foo1(bool isFoo) { /* comment0 */\n"
	    "    /* comment1 */\n"
	    "    if(isFoo) {\n"
	    "        /* comment2 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo) {\n"
	    "    /* comment3\n"
	    "     *\n"
	    "     */\n"
	    "    if(isFoo) {\n"
	    "        /* comment4\n"
	    "         *\n"
	    "         */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, CommentsRunIn5)
{
	// attached braces with following comments
	// if NOT attached the run-in statement should be broken
	char textIn[] =
	    "\n// -------------\n"
	    "void foo()\n"
	    "// ----------------\n"
	    "{ /* comment1 */\n"
	    "}\n";
	char text[] =
	    "\n// -------------\n"
	    "void foo()\n"
	    "// ----------------\n"
	    "{\n"
	    "    /* comment1 */\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, MultipleCommentsBreak)
{
	// multiple comments with broken braces should NOT be attached
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo) /* comment1 */  // comment2\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo) /* comment1 */  // comment2\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, MultipleCommentsAttach)
{
	// multiple comments with attached braces should remain unchanged
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo) { /* comment1 */  // comment2\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, MultipleCommentsRunIn)
{
	// multiple comments with horstmann braces should NOT be attached
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo) /* comment1 */  // comment2\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo) /* comment1 */  // comment2\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, Xtra1)
{
	// don't attach braces if previous line is empty
	char text[] =
	    "\nvoid foo()\n"
	    "\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "\n"
	    "    {\n"
	    "        bar = 1;\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, Xtra2)
{
	// can attach braces if previous empty line is deleted
	char textIn[] =
	    "\nvoid foo()\n"
	    "\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "\n"
	    "    {\n"
	    "        bar = 1;\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar = 1;\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java, delete-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, Xtra3)
{
	// cannot attach braces following a semi-colon
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar1();\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    bar1();\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, Xtra4)
{
	// cannot attach braces following a "{" or "}"
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    {\n"
	    "        bar1();\n"
	    "    }\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    {\n"
	    "        bar1();\n"
	    "    }\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesAttachCpp, Xtra5)
{
	// attach to a tabbed comment
	char textIn[] =
	    "\nvoid foo()			// comment\n"
	    "{\n"
	    "    if (isFoo)			// comment\n"
	    "    {\n"
	    "        bar = 0;\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {		// comment\n"
	    "    if (isFoo) {		// comment\n"
	    "        bar = 0;\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle C++ Linux Brace Options
//-------------------------------------------------------------------------

struct BracesLinuxCppF : public Test
{
	string textStr;
	const char* textIn;

	BracesLinuxCppF()
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

TEST_F(BracesLinuxCppF, LongOption)
{
	// test linux braces option
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
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesLinuxCppF, ShortOption)
{
	// test linux braces option
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
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "-A3";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesLinuxCppF, Namespace)
{
	// test linux braces option
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
	    "    {\n"
	    "        if (isFoo) {\n"
	    "            bar();\n"
	    "        } else {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=kr, indent-namespaces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesLinuxCppF, Class)
{
	// test linux braces option
	// indent class blocks
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "class FooClass\n"
	    "{\n"
	    "    private:\n"
	    "        bool var1;\n"
	    "        void func1();\n"
	    "    protected:\n"
	    "        bool var2;\n"
	    "        void func2();\n"
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
	char options[] = "style=kr, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesLinuxCppF, NamespaceClass)
{
	// test linux braces option
	// indented namespace and class
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "    class FooClass\n"
	    "    {\n"
	    "        private:\n"
	    "            bool var1;\n"
	    "            void func1();\n"
	    "        protected:\n"
	    "            bool var2;\n"
	    "            void func2();\n"
	    "    };\n"
	    "\n"
	    "    void FooClass::Foo(bool isFoo)\n"
	    "    {\n"
	    "        if (isFoo) {\n"
	    "            bar();\n"
	    "        } else {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=kr, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(BracesLinuxCppF, BreakClosing)
{
	// test break closing braces option with linux braces
	// effective only with attach or linux braces
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
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=kr, break-closing-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, EmptyBraces)
{
	// test linux braces option
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
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, EmptyBracesWithComments)
{
	// test linux braces option with ending comments
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
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, Extern)
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
	    "\nextern \"C\" {\n"
	    "	extern void foo1()\n"
	    "	{\n"
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
	char options[] = "indent=tab, style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, Assembler)
{
	// assembler statements should be attached
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    _asm\n"
	    "    {\n"
	    "        mov eax, fs:[0x8]\n"
	    "        mov dx, 0xD007\n"
	    "        out dx, al\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    _asm {\n"
	    "        mov eax, fs:[0x8]\n"
	    "        mov dx, 0xD007\n"
	    "        out dx, al\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, Break)
{
	// test linux braces option with broken braces
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
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, Attach)
{
	// test linux braces option with attached braces
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
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, Linux)
{
	// test linux braces option with linux braces
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, RunIn1)
{
	// test linux braces option with horstmann braces
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, RunIn2)
{
	// test default braces option with horstmann braces
	// and 2 braces on the same line
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   if(isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if(isFoo) {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, Misc1)
{
	// test linux braces option with the following unusual format
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
	    "{\n"
	    "    error = false;\n"
	    "    errorId = 0;\n"
	    "}\n"
	    "\n"
	    "void foo2()    // comment2\n"
	    "{\n"
	    "    error = false;\n"
	    "    errorId = 0;\n"
	    "}\n"
	    "\n"
	    "void foo3()    /* comment3 */\n"
	    "{\n"
	    "    error = false;\n"
	    "    errorId = 0;\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, Misc2)
{
	// test linux braces option with the following unusual format
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (bar1()) {/* dummy */}\n"
	    "\n"
	    "    if (bar1()) {;/* dummy */}\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, Misc3)
{
	// test linux braces option with a macro
	// brace type will be incorrectly classified as an array
	// but should not break at the semi colon
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    YY_RULE_SETUP\n"
	    "    { BEGIN(list); return CONT; }\n"
	    "    YY_BREAK\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, ClassContinuation)
{
	// test with class continuation and linux braces
	char text[] =
	    "\nclass Foo :\n"
	    "    public Bar\n"
	    "{\n"
	    "public:\n"
	    "    Foo(T *in);\n"
	    "};\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, Formatting1)
{
	// test linux braces option, for non-function top level objects
	// braces are attached for function definitions within a class
	// braces are attached for arrays, structs, enums and other top level
	//      objects that are not classes or functions.
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "class FooClass\n"
	    "{\n"
	    "public:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "private:\n"
	    "    // inline class functions are broken\n"
	    "    void FooClass()\n"
	    "    {\n"
	    "        if (isFoo) {\n"
	    "            bar();\n"
	    "        } else {\n"
	    "            anotherBar();\n"
	    "        }\n"
	    "    }\n"
	    "\n"
	    "};\n"
	    "\n"
	    "// arrays are NOT broken\n"
	    "fooArray[] = {\n"
	    "    red,\n"
	    "    green,\n"
	    "    darkblue\n"
	    "};\n"
	    "\n"
	    "// structs are NOT broken\n"
	    "struct fooStruct {\n"
	    "    int foo;\n"
	    "}\n"
	    "\n"
	    "// enums are NOT broken\n"
	    "enum fooEnum {\n"
	    "    foo,\n"
	    "    bar\n"
	    "}\n"
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
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, Formatting2)
{
	// test linux braces option, for non-function objects within a function
	// braces are attached for arrays, structs, enums and other objects  within a function.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "\n"
	    "    // arrays are NOT broken\n"
	    "    fooArray[] = {\n"
	    "        red,\n"
	    "        green,\n"
	    "        darkblue\n"
	    "    };\n"
	    "\n"
	    "    // structs are NOT broken\n"
	    "    struct fooStruct {\n"
	    "        int foo;\n"
	    "    }\n"
	    "\n"
	    "    // enums are NOT broken\n"
	    "    enum fooEnum {\n"
	    "        foo,\n"
	    "        bar\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, NestedNamespace)
{
	// test indent nested namespaces with linux braces
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
	    "        }\n"
	    "        }\n"
	    "    }\n"
	    "    }\n"
	    "}\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, LineCommentsBreak)
{
	// comments following broken braces should NOT be attached
	char textIn[] =
	    "\nvoid foo(bool isFoo) // comment0\n"
	    "{\n"
	    "    // comment1\n"
	    "    if (isFoo) // comment2\n"
	    "    {\n"
	    "        // comment3\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo(bool isFoo) // comment0\n"
	    "{\n"
	    "    // comment1\n"
	    "    if (isFoo) { // comment2\n"
	    "        // comment3\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, LineCommentsAttach)
{
	// comments following attached braces should stay attached to the line
	char textIn[] =
	    "\nvoid foo(bool isFoo) {    // comment0\n"
	    "    // comment1\n"
	    "    if (isFoo) {          // comment2\n"
	    "        // comment3\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo(bool isFoo)      // comment0\n"
	    "{\n"
	    "    // comment1\n"
	    "    if (isFoo) {          // comment2\n"
	    "        // comment3\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, LineCommentsRunIn)
{
	// comments following horstmann braces should NOT be attached
	char textIn[] =
	    "\nvoid foo(bool isFoo) /* comment0 */\n"
	    "{   // comment1\n"
	    "    if (isFoo)\n"
	    "    {   // comment2\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo(bool isFoo) /* comment0 */\n"
	    "{\n"
	    "    // comment1\n"
	    "    if (isFoo) {\n"
	    "        // comment2\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, LineCommentsClosingHeader)
{
	// test comment alignment when a closing header is attached to a closing brace
	char textIn[] =
	    "\nvoid foo()       // comment0\n"
	    "{\n"
	    "    if (isFoo)   // comment1\n"
	    "    {\n"
	    "        bar1();  // comment2\n"
	    "    }\n"
	    "    else         // comment3\n"
	    "    {\n"
	    "        bar2();  // comment4\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()       // comment0\n"
	    "{\n"
	    "    if (isFoo) { // comment1\n"
	    "        bar1();  // comment2\n"
	    "    } else {     // comment3\n"
	    "        bar2();  // comment4\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, CommentsBreak1)
{
	// broken braces with following comments to linux
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
	    "{\n"
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
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, CommentsAttach1)
{
	// attached braces with following comments to linux
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
	    "{\n"
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
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, CommentsRunIn1)
{
	// horstmann braces with following comments to linux
	char textIn[] =
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
	char text[] =
	    "\nvoid (foo)\n"
	    "{\n"
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
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, CommentsBreak2)
{
	// broken braces with following comments to linux
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
	    "{\n"
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
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, CommentsAttach2)
{
	// attached braces with following comments to linux
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
	    "{\n"
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
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, CommentsRunIn2)
{
	// horstmann braces with following comments to linux
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
	    "{\n"
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
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, CommentsBreak3)
{
	// comments following broken braces should NOT be attached
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
	    "{\n"
	    "    /* comment1 */\n"
	    "    if(isFoo) {\n"
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
	    "    if(isFoo) {\n"
	    "        /* comment4\n"
	    "         *\n"
	    "         */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, CommentsAttach3)
{
	// test comments following braces
	// multi-line comments following attached braces break
	//    but are NOT aligned
	char textIn[] =
	    "\nvoid foo1(bool isFoo) {  /* comment0 */\n"
	    "    /* comment1 */\n"
	    "    if(isFoo) { /* comment2 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo) {  /* comment3\n"
	    "     *\n"
	    "     */\n"
	    "    if(isFoo) { /* comment4\n"
	    "                 *\n"
	    "                 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo1(bool isFoo)    /* comment0 */\n"
	    "{\n"
	    "    /* comment1 */\n"
	    "    if(isFoo) { /* comment2 */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(bool isFoo)\n"
	    "{\n"
	    "    /* comment3\n"
	    "         *\n"
	    "         */\n"
	    "    if(isFoo) {\n"
	    "        /* comment4\n"
	    "                     *\n"
	    "                     */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, CommentsRunIn3)
{
	// comments following horstmann braces should NOT be attached
	char textIn[] =
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
	char text[] =
	    "\nvoid foo1(bool isFoo) /* comment0 */\n"
	    "{\n"
	    "    /* comment1 */\n"
	    "    if(isFoo) {\n"
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
	    "    if(isFoo) {\n"
	    "        /* comment4\n"
	    "         *\n"
	    "         */\n"
	    "        fooBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, MultipleCommentsBreak)
{
	// multiple comments with broken braces should remain unchanged
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo) /* comment1 */  // comment2\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, MultipleCommentsAttach)
{
	// multiple comments with attached braces remain unchanged
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo) { /* comment1 */  // comment2\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, MultipleCommentsRunIn)
{
	// multiple comments with horstmann braces should NOT be attached
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo) /* comment1 */  // comment2\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo) /* comment1 */  // comment2\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, Xtra1)
{
	// don't attach braces if previous line is empty
	char text[] =
	    "\nvoid foo()\n"
	    "\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "\n"
	    "    {\n"
	    "        bar = 1;\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, Xtra2)
{
	// can attach braces if previous empty line is deleted
	char textIn[] =
	    "\nvoid foo()\n"
	    "\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "\n"
	    "    {\n"
	    "        bar = 1;\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar = 1;\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr, delete-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, Xtra3)
{
	// cannot attach braces following a semi-colon
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar1();\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar1();\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, Xtra4)
{
	// cannot attach braces following a "{" or "}"
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    {\n"
	    "        bar1();\n"
	    "    }\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    {\n"
	    "        bar1();\n"
	    "    }\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BracesLinuxCpp, Xtra5)
{
	// attach to a tabbed comment
	char textIn[] =
	    "\nvoid foo()			// comment\n"
	    "{\n"
	    "    if (isFoo)			// comment\n"
	    "    {\n"
	    "        bar = 0;\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()			// comment\n"
	    "{\n"
	    "    if (isFoo) {		// comment\n"
	    "        bar = 0;\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------

}  // namespace
