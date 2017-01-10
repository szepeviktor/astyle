// AStyleTest_BracesCpp1.cpp
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
	// test default brackets option (do not change)
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
	// test default brackets option (do not change)
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
	// test default brackets option (do not change)
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
	// test default brackets option (do not change)
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
	// test default brackets option (do not change)
	// do not change empty brackets
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
	// test default brackets option (do not change) with ending comments
	// do not change empty brackets
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
	// test default brackets option (do not change)
	// extern statement should not change its bracket type
	// and should NOT use in-statement indents
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
	// test default brackets option with broken brackets
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
	// test default brackets option with attached brackets
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
	// test default brackets option with linux brackets
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

TEST(BracesNoneCpp, Horstmann1)
{
	// test default brackets option with horstmann brackets
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

TEST(BracesNoneCpp, Horstmann2)
{
	// test default brackets option with horstmann brackets
	// and 2 brackets on the same line
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
	// test default brackets option with the following unusual format
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
	// test default brackets option with the following unusual format
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
	// test default brackets option with a macro
	// bracket type will be incorrectly classified as an array
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
	// test with class continuation and attached brackets
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
	// test with class continuation and broken brackets
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

TEST(BracesNoneCpp, HorstmannIndent1)
{
	// test default brackets option with horstmann brackets
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

TEST(BracesNoneCpp, HorstmannIndent2)
{
	// test default brackets option with horstmann brackets
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

TEST(BracesNoneCpp, HorstmannIndentComment1)
{
	// test default brackets option with horstmann brackets
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

TEST(BracesNoneCpp, HorstmannIndentComment2)
{
	// test default brackets option with horstmann brackets
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
	// line comments following broken brackets should be unchanged
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
	// line comments following attached brackets should be unchanged
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

TEST(BracesNoneCpp, LineCommentsHorstmann)
{
	// line comments following horstmann brackets should be unchanged
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
	// broken brackets should not change
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
	// attached brackets should not change
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

TEST(BracesNoneCpp, CommentsHorstmann1)
{
	// horstmann brackets should not change
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
	// broken brackets with following comments
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
	// attached brackets with following comments
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

TEST(BracesNoneCpp, CommentsHorstmann2)
{
	// horstmann brackets with following comments
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
	// comments following broken brackets should be unchanged
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
	// comments following attached brackets should be unchanged
	// multi-line comments following attached brackets break
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

TEST(BracesNoneCpp, CommentsHorstmann3)
{
	// comments following horstmann brackets should be unchanged
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
	// multiple comments with broken brackets should remain unchanged
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
	// multiple comments with attached brackets remain unchanged
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

TEST(BracesNoneCpp, MultipleCommentsHorstmann)
{
	// multiple comments with horstmann brackets remain unchanged
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
	// test break brackets option
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
	// test break brackets short option
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
	// test break brackets option
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
	// test break brackets option
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
	// test break brackets option
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
	// test break brackets option
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
	// test break brackets option with ending comments
	// do not change empty brackets
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
	// extern statement should not change its bracket type
	// and should NOT use in-statement indents
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
	// test break brackets option with broken brackets
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
	// test break brackets option with attached brackets
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
	// test break brackets option with linux brackets
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

TEST(BracesBreakCpp, Horstmann1)
{
	// test break brackets option with horstmann brackets
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

TEST(BracesBreakCpp, Horstmann2)
{
	// test default brackets option with horstmann brackets
	// and 2 brackets on the same line
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
	// test break brackets option with the following unusual format
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
	// test break brackets option with the following unusual format
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
	// test break brackets option with a macro
	// bracket type will be incorrectly classified as an array
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
	// test with class continuation and broken brackets
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
	// comments following broken brackets should be unchanged
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
	// comments following attached brackets should stay attached to the line
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

TEST(BracesBreakCpp, LineCommentsHorstmann)
{
	// comments following horstmann brackets should be broken
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
	// test comment alignment when a closing header is broken from a closing bracket
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
	// broken brackets should not change
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
	// break attached brackets with following comments
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

TEST(BracesBreakCpp, CommentsHorstmann1)
{
	// break horstmann brackets with following comments
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
	// broken brackets with following comments
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
	// break attached brackets with following comments
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

TEST(BracesBreakCpp, CommentsHorstmann2)
{
	// break horstmann brackets with following comments
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
	// comments following broken brackets should be unchanged
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
	// test comments following brackets
	// multi-line comments following attached brackets break
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

TEST(BracesBreakCpp, CommentsHorstmann3)
{
	// comments following horstmann brackets should be broken
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
	// multiple comments with broken brackets should remain unchanged
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
	// multiple comments with attached brackets should remain unchanged
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

TEST(BracesBreakCpp, MultipleCommentsHorstmann)
{
	// multiple comments with horstmann brackets should be broken
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
	// test attach brackets option
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
	// test attach brackets option
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
	// test attach brackets option
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
	// test attach brackets option
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
	// test attach brackets option
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
	// test attach brackets option
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
	// test attach brackets option
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
	// test attach brackets option with ending comments
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
	// extern statement should not change its bracket type
	// and should NOT use in-statement indents
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
	// test attach brackets option with broken brackets
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
	// test attach brackets option with attached brackets
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
	// test attach brackets option with linux brackets
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

TEST(BracesAttachCpp, Horstmann1)
{
	// test attach brackets option with horstmann brackets
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

TEST(BracesAttachCpp, Horstmann2)
{
	// test default brackets option with horstmann brackets
	// and 2 brackets on the same line
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
	// test attach brackets option with the following unusual format
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
	// test attach brackets option with the following unusual format
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
	// test attach brackets option with a macro
	// bracket type will be incorrectly classified as an array
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
	// test with class continuation and attached brackets
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
	// comments following broken brackets should NOT be attached
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

TEST(BracesAttachCpp, LineCommentsHorstmann)
{
	// comments following horstmann brackets should be attached
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
	// test comment alignment when a closing header is attached to a closing bracket
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
	// attach broken brackets with following comments
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
	// attached brackets should not change
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

TEST(BracesAttachCpp, CommentsHorstmann1)
{
	// attach horstmann brackets with following comments
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
	// attach broken brackets with following comments
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
	// attached brackets with following comments
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

TEST(BracesAttachCpp, CommentsHorstmann2)
{
	// attach horstmann brackets with following comments
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
	// comments following broken brackets should NOT be attached
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
	// test comments following brackets
	// multi-line comments following attached brackets break
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

TEST(BracesAttachCpp, CommentsHorstmann3)
{
	// comments following horstmann brackets should NOT be attached
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

TEST(BracesAttachCpp, CommentsHorstmann5)
{
	// attached brackets with following comments
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
	// multiple comments with broken brackets should NOT be attached
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
	// multiple comments with attached brackets should remain unchanged
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

TEST(BracesAttachCpp, MultipleCommentsHorstmann)
{
	// multiple comments with horstmann brackets should NOT be attached
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
	// don't attach brackets if previous line is empty
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
	// can attach brackets if previous empty line is deleted
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
	// cannot attach brackets following a semi-colon
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
	// cannot attach brackets following a "{" or "}"
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
	// test linux brackets option
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
	// test linux brackets option
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
	// test linux brackets option
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
	// test linux brackets option
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
	// test linux brackets option
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
	// test break closing brackets option with linux brackets
	// effective only with attach or linux brackets
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
	// test linux brackets option
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
	// test linux brackets option with ending comments
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
	// extern statement should not change its bracket type
	// and should NOT use in-statement indents
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
	// test linux brackets option with broken brackets
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
	// test linux brackets option with attached brackets
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
	// test linux brackets option with linux brackets
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

TEST(BracesLinuxCpp, Horstmann1)
{
	// test linux brackets option with horstmann brackets
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

TEST(BracesLinuxCpp, Horstmann2)
{
	// test default brackets option with horstmann brackets
	// and 2 brackets on the same line
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
	// test linux brackets option with the following unusual format
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
	// test linux brackets option with the following unusual format
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
	// test linux brackets option with a macro
	// bracket type will be incorrectly classified as an array
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
	// test with class continuation and linux brackets
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
	// test linux brackets option, for non-function top level objects
	// brackets are attached for function definitions within a class
	// brackets are attached for arrays, structs, enums and other top level
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
	// test linux brackets option, for non-function objects within a function
	// brackets are attached for arrays, structs, enums and other objects  within a function.
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
	// test indent nested namespaces with linux brackets
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
	// comments following broken brackets should NOT be attached
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
	// comments following attached brackets should stay attached to the line
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

TEST(BracesLinuxCpp, LineCommentsHorstmann)
{
	// comments following horstmann brackets should NOT be attached
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
	// test comment alignment when a closing header is attached to a closing bracket
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
	// broken brackets with following comments to linux
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
	// attached brackets with following comments to linux
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

TEST(BracesLinuxCpp, CommentsHorstmann1)
{
	// horstmann brackets with following comments to linux
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
	// broken brackets with following comments to linux
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
	// attached brackets with following comments to linux
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

TEST(BracesLinuxCpp, CommentsHorstmann2)
{
	// horstmann brackets with following comments to linux
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
	// comments following broken brackets should NOT be attached
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
	// test comments following brackets
	// multi-line comments following attached brackets break
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

TEST(BracesLinuxCpp, CommentsHorstmann3)
{
	// comments following horstmann brackets should NOT be attached
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
	// multiple comments with broken brackets should remain unchanged
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
	// multiple comments with attached brackets remain unchanged
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

TEST(BracesLinuxCpp, MultipleCommentsHorstmann)
{
	// multiple comments with horstmann brackets should NOT be attached
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
	// don't attach brackets if previous line is empty
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
	// can attach brackets if previous empty line is deleted
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
	// cannot attach brackets following a semi-colon
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
	// cannot attach brackets following a "{" or "}"
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
