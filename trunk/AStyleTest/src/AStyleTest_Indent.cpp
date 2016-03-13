// AStyleTest_Indent.cpp
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// Licensed under the MIT license.
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
// AStyle Indent Classes
// Additional tests are in the Brackets tests
//-------------------------------------------------------------------------

TEST(IndentClasses, LongOption)
{
	// test indent class blocks
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
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, ShortOption)
{
	// test indent class blocks short option
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
	char options[] = "-C";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, EmptyClass)
{
	// empty brackets should not receive an extra indent
	char text[] =
	    "\nclass FooClass\n"
	    "{};\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, EmptyClassSans)
{
	// empty brackets should not receive an extra indent
	char text[] =
	    "\nclass FooClass\n"
	    "{};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, MultipleInheritance1)
{
	// indent classes with multiple inheritance on separate lines
	char text[] =
	    "\nclass SearchComboPopUp :\n"
	    "    public wxListBox,\n"
	    "    public wxComboPopup\n"
	    "{\n"
	    "public:\n"
	    "    int foo;\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentClasses, MultipleInheritance2)
{
	// indent classes with multiple inheritance on separate lines
	char text[] =
	    "\nclass SearchComboPopUp\n"
	    "    : public wxListBox,\n"
	    "      public wxComboPopup\n"
	    "{\n"
	    "public:\n"
	    "    int foo;\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentClasses, RunIn)
{
	// test indent class blocks with run-in brackets
	// 'public' 'private' and 'protected' are run-in if class block is indented
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
	char options[] = "indent-classes, style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, RunInTab)
{
	// test indent class blocks with run-in brackets and tab indents
	// 'public' 'private' and 'protected' are run-in if class block is indented
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
	    "{	private:\n"
	    "		bool foo1;\n"
	    "};\n"
	    "\n"
	    "class fooClass2\n"
	    "{		bool foo2;\n"
	    "};\n";
	char options[] = "indent-classes, style=horstmann, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, RunInSans)
{
	// test without indent class blocks with run-in brackets
	// 'public' 'private' and 'protected' are NOT run-in if class block is not indented
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
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, RunInSansTab)
{
	// test without indent class blocks with run-in brackets and tab indents
	// 'public' 'private' and 'protected' are NOT run-in if class block is not indented
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
	    "	bool foo1;\n"
	    "};\n"
	    "\n"
	    "class fooClass2\n"
	    "{	bool foo2;\n"
	    "};\n";
	char options[] = "style=horstmann, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, RunInLineComment)
{
	// test indent class blocks line comment with run-in brackets
	// is run-in if class block is indented and does not start in column 1
	char textIn[] =
	    "\nclass fooClass1\n"
	    "{\n"
	    "    // coment1\n"
	    "    public:\n"
	    "};\n"
	    "\n"
	    "class fooClass2\n"
	    "{\n"
	    "// comment2\n"
	    "    public:\n"
	    "};\n";
	char text[] =
	    "\nclass fooClass1\n"
	    "{   // coment1\n"
	    "    public:\n"
	    "};\n"
	    "\n"
	    "class fooClass2\n"
	    "{\n"
	    "// comment2\n"
	    "    public:\n"
	    "};\n";
	char options[] = "indent-classes, style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, RunInLineCommentSans)
{
	// test without indent class blocks line comment with run-in brackets
	// currently are run-in and indented one indent if class block is not indented
	char textIn[] =
	    "\nclass fooClass1\n"
	    "{\n"
	    "    // coment1\n"
	    "    public:\n"
	    "};\n"
	    "\n"
	    "class fooClass2\n"
	    "{\n"
	    "// comment2\n"
	    "    public:\n"
	    "};\n";
	char text[] =
	    "\nclass fooClass1\n"
	    "{   // coment1\n"
	    "public:\n"
	    "};\n"
	    "\n"
	    "class fooClass2\n"
	    "{\n"
	    "// comment2\n"
	    "public:\n"
	    "};\n";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, RunInComment)
{
	// test indent class blocks comment with run-in brackets
	// is run-in if class block is indented and does not start in column 1
	char textIn[] =
	    "\nclass fooClass1\n"
	    "{\n"
	    "/* coment1 */\n"
	    "public:\n"
	    "};\n";
	char text[] =
	    "\nclass fooClass1\n"
	    "{   /* coment1 */\n"
	    "    public:\n"
	    "};\n";
	char options[] = "indent-classes, style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, RunInCommentSans)
{
	// test without indent class blocks comment with run-in brackets
	// currently are run-in and indented one indent if class block is not indented
	char textIn[] =
	    "\nclass fooClass1\n"
	    "{\n"
	    "/* coment1 */\n"
	    "public:\n"
	    "};\n";
	char text[] =
	    "\nclass fooClass1\n"
	    "{   /* coment1 */\n"
	    "public:\n"
	    "};\n";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, LineComment)
{
	// test line comment with indent class blocks
	// line comment is before the opening bracket
	//     and should NOT receive an extra indent
	char text[] =
	    "\nclass FooClass\n"
	    "// -----------------\n"
	    "{\n"
	    "}\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentClasses, LineCommentSans)
{
	// test line comment without indent class blocks
	// line comment is before the opening bracket
	//     and should NOT receive an extra indent
	char text[] =
	    "\nclass FooClass\n"
	    "// -----------------\n"
	    "{\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentClasses, Comment)
{
	// test comment with indent class blocks
	// comment is before the opening bracket
	//     and should NOT receive an extra indent
	char text[] =
	    "\nclass FooClass\n"
	    "/* PURPOSE:   comment1\n"
	    "              comment2\n"
	    "*/\n"
	    "{\n"
	    "};\n"
	    "\n"
	    "void foo()\n"
	    "/* PURPOSE:   comment3\n"
	    "   RECEIVES:  comment4\n"
	    "   RETURNS:   comment5\n"
	    "*/\n"
	    "{\n"
	    "}\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, CommentSans)
{
	// test comment without indent class blocks
	// comment is before the opening bracket
	//     and should NOT receive an extra indent
	char text[] =
	    "\nclass FooClass\n"
	    "/* PURPOSE:   comment1\n"
	    "              comment2\n"
	    "*/\n"
	    "{\n"
	    "};\n"
	    "\n"
	    "void foo()\n"
	    "/* PURPOSE:   comment3\n"
	    "   RECEIVES:  comment4\n"
	    "   RETURNS:   comment5\n"
	    "*/\n"
	    "{\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, Struct)
{
	// struct with access modifiers should have extra indent
	// struct WITHOUT should NOT have extra indent
	char text[] =
	    "\nstruct FooClass1\n"
	    "{\n"
	    "    private:\n"
	    "        bool var1;\n"
	    "    protected:\n"
	    "        bool var2;\n"
	    "};\n"
	    "\n"
	    "struct FooClass2\n"
	    "{\n"
	    "    bool var1;\n"
	    "    bool var2;\n"
	    "};\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, StructComment)
{
	// struct with comments containing access modifiers
	// should NOT have extra indent
	char text[] =
	    "\nstruct FooClass2\n"
	    "{\n"
	    "    // private:\n"
	    "    bool var1;\n"
	    "    /* public:\n"
	    "    */\n"
	    "    bool var2;\n"
	    "};\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, StructQuote)
{
	// struct with quotes containing access modifiers and brackets
	// should NOT have extra indent
	char text[] =
	    "\nstruct cppText\n"
	    "{\n"
	    "    cppText()\n"
	    "    {\n"
	    "        textStr1 =\n"
	    "            \"class FooClass\\n\"\n"
	    "            \"{\\n\"\n"
	    "            \"private:\\n\"\n"
	    "            \"    bool var1;\\n\"\n"
	    "            \"};\\n\";\n"
	    "\n"
	    "        textStr2 =\n"
	    "            \"class FooClass {\\n\"\n"
	    "            \"private:\\n\"\n"
	    "            \"    bool var1;\\n\"\n"
	    "            \"};\\n\";\n"
	    "\n"
	    "        textStr3 =\n"
	    "            \"class FooClass\\n\"\n"
	    "            \"{   private:\\n\"\n"
	    "            \"        bool var1;\\n\"\n"
	    "            \"};\\n\";\n"
	    "\n"
	    "        textIn = textStr1.c_str();\n"
	    "    }\n"
	    "};\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, StructSansLeadingModifier)
{
	// struct without a leading access modifier
	char text[] =
	    "\nstruct FooClass2\n"
	    "{\n"
	    "        bool var1;\n"
	    "\n"
	    "    protected:\n"
	    "        bool var2;\n"
	    "};\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, StructBrackets)
{
	// struct containing non-struct brackets
	char text[] =
	    "\nstruct FooClass2\n"
	    "{\n"
	    "        bool publicFoo()\n"
	    "        {\n"
	    "            bool var1;\n"
	    "        }\n"
	    "    private:\n"
	    "        bool var2;\n"
	    "};\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, StructRunIn)
{
	// struct containing run-in brackets
	char textIn[] =
	    "\nstruct FooClass1\n"
	    "{\n"
	    "    protected:\n"
	    "        bool var1;\n"
	    "};\n"
	    "\n"
	    "struct FooClass2\n"
	    "{\n"
	    "        bool var1;\n"
	    "\n"
	    "    private:\n"
	    "        bool var2;\n"
	    "};\n";
	char text[] =
	    "\nstruct FooClass1\n"
	    "{   protected:\n"
	    "        bool var1;\n"
	    "};\n"
	    "\n"
	    "struct FooClass2\n"
	    "{       bool var1;\n"
	    "\n"
	    "    private:\n"
	    "        bool var2;\n"
	    "};\n";
	char options[] = "indent-classes, style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, StructRunInSans)
{
	// struct containing run-in brackets without indent-classes
	char textIn[] =
	    "\nstruct FooClass1\n"
	    "{\n"
	    "    protected:\n"
	    "        bool var1;\n"
	    "};\n"
	    "\n"
	    "struct FooClass2\n"
	    "{\n"
	    "        bool var1;\n"
	    "\n"
	    "    private:\n"
	    "        bool var2;\n"
	    "};\n";
	char text[] =
	    "\nstruct FooClass1\n"
	    "{\n"
	    "protected:\n"
	    "    bool var1;\n"
	    "};\n"
	    "\n"
	    "struct FooClass2\n"
	    "{   bool var1;\n"
	    "\n"
	    "private:\n"
	    "    bool var2;\n"
	    "};\n";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, StructUnmatchedBrackets)
{
	// struct with unmatched brackets should not cause an abort
	char textIn[] =
	    "\nstruct FooClass2\n"
	    "{\n"
	    "    bool var1;\n"
	    "    bool var2;\n"
	    "    bool unmached() {\n"
	    "};\n";
	char text[] =
	    "\nstruct FooClass2\n"
	    "{\n"
	    "    bool var1;\n"
	    "    bool var2;\n"
	    "    bool unmached() {\n"
	    "    };\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, StructSans)
{
	// struct without indent-classes should have not extra indent
	char text[] =
	    "\nstruct FooClass1\n"
	    "{\n"
	    "private:\n"
	    "    bool var1;\n"
	    "protected:\n"
	    "    bool var2;\n"
	    "};\n"
	    "\n"
	    "struct FooClass2\n"
	    "{\n"
	    "    bool var1;\n"
	    "    bool var2;\n"
	    "};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, NestedStruct)
{
	// test indent with nested structs
	char text[] =
	    "\nstruct RefTable\n"
	    "{\n"
	    "        struct RefNode0 {\n"
	    "            SQObjectPtr obj;\n"
	    "        };\n"
	    "        RefTable1();\n"
	    "        struct RefNode1 {\n"
	    "            protected:\n"
	    "                SQObjectPtr obj;\n"
	    "        };\n"
	    "        RefTable2();\n"
	    "    private:\n"
	    "        RefNode* _nodes;\n"
	    "};\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentClasses, FriendClass)
{
	// a 'friend class' statement should be ignored
	char text[] =
	    "\nclass DebuggerManager\n"
	    "{\n"
	    "    private:\n"
	    "        friend class Manager;\n"
	    "    public:\n"
	    "        inf foo;\n"
	    "};";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentClasses, FriendClassSans)
{
	// a 'friend class' statement without indent-classes should be ignored
	char text[] =
	    "\nclass DebuggerManager\n"
	    "{\n"
	    "private:\n"
	    "    friend class Manager;\n"
	    "public:\n"
	    "    inf foo;\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentClasses, SharpInheritance1)
{
	// a 'friend class' statement without indent-classes should be ignored
	char text[] =
	    "\npublic class ReportDesignerView : AbstractViewContent,\n"
	    "    IClipboardHandler, IUndoHandler\n"
	    "{\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentClasses, SharpInheritance2)
{
	// a 'friend class' statement without indent-classes should be ignored
	char text[] =
	    "\npublic class ReportDesignerView\n"
	    "    : AbstractViewContent,\n"
	    "      IClipboardHandler, IUndoHandler\n"
	    "{\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentClasses, JavaMultipleLine)
{
	// a Java class with multiple lines
	char text[] =
	    "\n"
	    "public class VFSBrowser extends JPanel implements DefaultFocusComponent,\n"
	    "    DockableWindow\n"
	    "{}";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Indent Modifiers
//-------------------------------------------------------------------------

TEST(IndentModifiers, LongOption)
{
	// test indent access modifiers
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "  private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "  protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "  public:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};";
	char options[] = "indent-modifiers";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentModifiers, ShortOption)
{
	// test indent access modifiers short option
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "  private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "  protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "  public:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};";
	char options[] = "-xG";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentModifiers, IndentClasses)
{
	// should not indent modifiers with indent classes
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "public:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};";
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "    private:\n"
	    "        bool var1;\n"
	    "        void func1();\n"
	    "    protected:\n"
	    "        bool var2;\n"
	    "        void func2();\n"
	    "    public:\n"
	    "        bool var2;\n"
	    "        void func2();\n"
	    "};";
	char options[] = "indent-modifiers, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentModifiers, IndentTab)
{
	// test indent access modifiers with indent=tab
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "public:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};";
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "  private:\n"
	    "	bool var1;\n"
	    "	void func1();\n"
	    "  protected:\n"
	    "	bool var2;\n"
	    "	void func2();\n"
	    "  public:\n"
	    "	bool var2;\n"
	    "	void func2();\n"
	    "};";
	char options[] = "indent-modifiers, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentModifiers, WithStruct)
{
	// test indent access modifiers for a struct
	char textIn[] =
	    "\nstruct FooStruct\n"
	    "{\n"
	    "private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "public:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};";
	char text[] =
	    "\nstruct FooStruct\n"
	    "{\n"
	    "  private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "  protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "  public:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};";
	char options[] = "indent-modifiers";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentModifiers, WithStructSansModifiers)
{
	// test indent access modifiers for a struct without modifiers
	char text[] =
	    "\nstruct FooStruct\n"
	    "{\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};";
	char options[] = "indent-modifiers";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentModifiers, HorstmannClass)
{
	// Test indent access modifiers with a Horstmann class.
	// The brackets should be run-in.
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "private:\n"
	    "    bool var1;\n"
	    "};";
	char text[] =
	    "\nclass FooClass\n"
	    "{ private:\n"
	    "    bool var1;\n"
	    "};";
	char options[] = "indent-modifiers, style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentModifiers, HorstmannStruct)
{
	// Test indent access modifiers with a Horstmann struct.
	// The brackets should be run-in.
	char textIn[] =
	    "\nstruct FooStruct\n"
	    "{\n"
	    "private:\n"
	    "    bool var1;\n"
	    "};";
	char text[] =
	    "\nstruct FooStruct\n"
	    "{ private:\n"
	    "    bool var1;\n"
	    "};";
	char options[] = "indent-modifiers, style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Indent Switches
//-------------------------------------------------------------------------

TEST(IndentSwitches, None)
{
	// test without indent switch blocks
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "    case 1:\n"
	    "        a += 1;\n"
	    "        break;\n"
	    "\n"
	    "    case 2:\n"
	    "    {\n"
	    "        a += 2;\n"
	    "        break;\n"
	    "    }\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, LongOption)
{
	// test indent switch blocks
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "        case 1:\n"
	    "            a += 1;\n"
	    "            break;\n"
	    "\n"
	    "        case 2:\n"
	    "        {\n"
	    "            a += 2;\n"
	    "            break;\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent-switches";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, ShortOption)
{
	// test indent switch blocks short option
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "        case 1:\n"
	    "            a += 1;\n"
	    "            break;\n"
	    "\n"
	    "        case 2:\n"
	    "        {\n"
	    "            a += 2;\n"
	    "            break;\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "-S";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, IndentForceTabX)
{
	// test indent switch blocks indent=force-tab-x
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch(x)\n"
	    "    {\n"
	    "	case 1:\n"
	    "	{\n"
	    "	    bar = 1;\n"
	    "	}\n"
	    "	break;\n"
	    "\n"
	    "	default:\n"
	    "	{\n"
	    "	    bar = 9;\n"
	    "	}\n"
	    "	break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent-switches, indent=force-tab-x";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, Comment1)
{
	// test switch block comments
	// comments NOT immediately preceding a 'case'
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (hit)\n"
	    "    {\n"
	    "        case NSScrollerDecrementLine:\n"
	    "            // Scroll to the left\n"
	    "            scrollColumnsLeftBy(1);\n"
	    "            break;\n"
	    "        case NSScrollerIncrementLine:\n"
	    "            /* Scroll to the right */\n"
	    "            scrollColumnsRightBy(1);\n"
	    "            break;\n"
	    "        default:\n"
	    "            /***************************/\n"
	    "            break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent-switches";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, Comment1Sans)
{
	// test switch block NOT indented comments
	// comments immediately preceding a 'case'
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (hit)\n"
	    "    {\n"
	    "    case NSScrollerDecrementLine:\n"
	    "        // Scroll to the left\n"
	    "        scrollColumnsLeftBy(1);\n"
	    "        break;\n"
	    "    case NSScrollerIncrementLine:\n"
	    "        /* Scroll to the right */\n"
	    "        scrollColumnsRightBy(1);\n"
	    "        break;\n"
	    "    default:\n"
	    "        /***************************/\n"
	    "        break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, Comment2)
{
	// test switch block comments
	// comments immediately preceeding a 'case' must be unindented
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (hit)\n"
	    "    {\n"
	    "        // Scroll to the left\n"
	    "        case NSScrollerDecrementLine:\n"
	    "            scrollColumnsLeftBy(1);\n"
	    "            break;\n"
	    "        /* Scroll to the right */\n"
	    "        case NSScrollerIncrementLine:\n"
	    "            scrollColumnsRightBy(1);\n"
	    "            break;\n"
	    "        /***************************/\n"
	    "        default:\n"
	    "            break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent-switches";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, Comment2Sans)
{
	// test switch block NOT indented comments
	// comments immediately preceeding a 'case' must be unindented
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (hit)\n"
	    "    {\n"
	    "    // Scroll to the left\n"
	    "    case NSScrollerDecrementLine:\n"
	    "        scrollColumnsLeftBy(1);\n"
	    "        break;\n"
	    "    /* Scroll to the right */\n"
	    "    case NSScrollerIncrementLine:\n"
	    "        scrollColumnsRightBy(1);\n"
	    "        break;\n"
	    "    /***************************/\n"
	    "    default:\n"
	    "        break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, Comment2MultiLine)
{
	// test switch block comments
	// multi-line comments immediately preceeding a 'case' must be unindented
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (hit)\n"
	    "    {\n"
	    "        // Scroll to the left\n"
	    "        // Scroll 2\n"
	    "        case NSScrollerDecrementLine:\n"
	    "            scrollColumnsLeftBy(1);\n"
	    "            break;\n"
	    "        /* Scroll to the right\n"
	    "         * Scroll 2\n"
	    "         */\n"
	    "        case NSScrollerIncrementLine:\n"
	    "            scrollColumnsRightBy(1);\n"
	    "            break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent-switches";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, Comment2MultiLineSans)
{
	// test switch block NOT indented comments
	// multi-line comments immediately preceeding a 'case' must be unindented
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (hit)\n"
	    "    {\n"
	    "    // Scroll to the left\n"
	    "    // Scroll 2\n"
	    "    case NSScrollerDecrementLine:\n"
	    "        scrollColumnsLeftBy(1);\n"
	    "        break;\n"
	    "    /* Scroll to the right\n"
	    "     * Scroll 2\n"
	    "     */\n"
	    "    case NSScrollerIncrementLine:\n"
	    "        scrollColumnsRightBy(1);\n"
	    "        break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, Comment3MultiLine)
{
	// test switch block with brackets comments
	// multi-line comments immediately preceeding a 'case' must be unindented
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (hit)\n"
	    "    {\n"
	    "        // Scroll to the left\n"
	    "        // Scroll 2\n"
	    "        case NSScrollerDecrementLine:\n"
	    "        {\n"
	    "            scrollColumnsLeftBy(1);\n"
	    "        }\n"
	    "        break;\n"
	    "        /* Scroll to the right\n"
	    "         * Scroll 2\n"
	    "         */\n"
	    "        case NSScrollerIncrementLine:\n"
	    "        {\n"
	    "            scrollColumnsRightBy(1);\n"
	    "            break;\n"
	    "        }\n"
	    "        /***************************/\n"
	    "        default:\n"
	    "            break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent-switches";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, Comment3MultiLineSans)
{
	// test switch block with brackets NOT indented comments
	// multi-line comments immediately preceeding a 'case' must be unindented
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (hit)\n"
	    "    {\n"
	    "    // Scroll to the left\n"
	    "    // Scroll 2\n"
	    "    case NSScrollerDecrementLine:\n"
	    "    {\n"
	    "        scrollColumnsLeftBy(1);\n"
	    "    }\n"
	    "    break;\n"
	    "    /* Scroll to the right\n"
	    "     * Scroll 2\n"
	    "     */\n"
	    "    case NSScrollerIncrementLine:\n"
	    "    {\n"
	    "        scrollColumnsRightBy(1);\n"
	    "        break;\n"
	    "    }\n"
	    "    /***************************/\n"
	    "    default:\n"
	    "        break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, Comment4PreceedsEmptyLine)
{
	// Test switch block with brackets preeceding an empty line.
	// The comments should not have an extra indent.
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (hit)\n"
	    "    {\n"
	    "        // NUMPAD KEY 0\n"
	    "\n"
	    "        case WXK_NUMPAD0:\n"
	    "            break;\n"
	    "\n"
	    "        // NUMPAD KEY 1\n"
	    "\n"
	    "        case WXK_NUMPAD1:\n"
	    "            break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent-switches";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, Comment4PreceedsEmptyLineSans)
{
	// Test switch block with brackets preeceding an empty line.
	// The comments should not have an extra indent.
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (hit)\n"
	    "    {\n"
	    "    // NUMPAD KEY 0\n"
	    "\n"
	    "    case WXK_NUMPAD0:\n"
	    "        break;\n"
	    "\n"
	    "    // NUMPAD KEY 1\n"
	    "\n"
	    "    case WXK_NUMPAD1:\n"
	    "        break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, NestedSwitchComments)
{
	// test nested switch block with brackets comments
	// multi-line comments immediately preceeding a 'case' must be unindented
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (hit)\n"
	    "    {\n"
	    "        // Scroll to the left\n"
	    "        // Scroll 2\n"
	    "        case NSScrollerDecrementLine:\n"
	    "        {\n"
	    "            scrollColumnsLeftBy(1);\n"
	    "        }\n"
	    "        break;\n"
	    "        /* Scroll to the right\n"
	    "         * Scroll 2\n"
	    "         */\n"
	    "        case NSScrollerIncrementLine:\n"
	    "        {\n"
	    "            switch (hit)\n"
	    "            {\n"
	    "                // Scroll to the left\n"
	    "                case NSScrollerDecrementLine:\n"
	    "                {\n"
	    "                    scrollColumnsLeftBy(1);\n"
	    "                }\n"
	    "                break;\n"
	    "                /* Scroll to the right */\n"
	    "                case NSScrollerIncrementLine:\n"
	    "                {\n"
	    "                    scrollColumnsRightBy(1);\n"
	    "                    break;\n"
	    "                }\n"
	    "            }\n"
	    "        }\n"
	    "        /***************************/\n"
	    "        default:\n"
	    "            break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent-switches";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, NestedSwitchCommentsSans)
{
	// test nested switch block with brackets NOT indented comments
	// multi-line comments immediately preceeding a 'case' must be unindented
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (hit)\n"
	    "    {\n"
	    "    // Scroll to the left\n"
	    "    // Scroll 2\n"
	    "    case NSScrollerDecrementLine:\n"
	    "    {\n"
	    "        scrollColumnsLeftBy(1);\n"
	    "    }\n"
	    "    break;\n"
	    "    /* Scroll to the right\n"
	    "     * Scroll 2\n"
	    "     */\n"
	    "    case NSScrollerIncrementLine:\n"
	    "    {\n"
	    "        switch (hit)\n"
	    "        {\n"
	    "        // Scroll to the left\n"
	    "        case NSScrollerDecrementLine:\n"
	    "        {\n"
	    "            scrollColumnsLeftBy(1);\n"
	    "        }\n"
	    "        break;\n"
	    "        /* Scroll to the right */\n"
	    "        case NSScrollerIncrementLine:\n"
	    "        {\n"
	    "            scrollColumnsRightBy(1);\n"
	    "            break;\n"
	    "        }\n"
	    "        }\n"
	    "    }\n"
	    "    /***************************/\n"
	    "    default:\n"
	    "        break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, RunInTab)
{
	// test indent switch blocks with run-in brackets and tab indents
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "        case 1:\n"
	    "            a += 1;\n"
	    "            break;\n"
	    "\n"
	    "        default:\n"
	    "        {\n"
	    "            a += 2;\n"
	    "            break;\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo()\n"
	    "{	switch (foo)\n"
	    "	{	case 1:\n"
	    "			a += 1;\n"
	    "			break;\n"
	    "\n"
	    "		default:\n"
	    "		{	a += 2;\n"
	    "			break;\n"
	    "		}\n"
	    "	}\n"
	    "}\n";
	char options[] = "indent-switches, style=horstmann, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, HorstmannTab)
{
	// Test switch block with horstmann style.
	// Horstmann style implies indented switch blocks.
	// textIn is broken brackets and indented switch blocks.
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "        case 1:\n"
	    "            a += 1;\n"
	    "            break;\n"
	    "\n"
	    "        default:\n"
	    "        {\n"
	    "            a += 2;\n"
	    "            break;\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo()\n"
	    "{	switch (foo)\n"
	    "	{	case 1:\n"
	    "			a += 1;\n"
	    "			break;\n"
	    "\n"
	    "		default:\n"
	    "		{	a += 2;\n"
	    "			break;\n"
	    "		}\n"
	    "	}\n"
	    "}\n";
	char options[] = "style=horstmann, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, HorstmannLineComment)
{
	// Test switch block comments with horstmann style.
	// Horstmann style implies indented switch blocks.
	// textIn is broken and indented switch blocks.
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "        // comment1\n"
	    "        case 1:\n"
	    "            a += 1;\n"
	    "            break;\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo()\n"
	    "{   switch (foo)\n"
	    "    {   // comment1\n"
	    "        case 1:\n"
	    "            a += 1;\n"
	    "            break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentSwitches, HorstmannComment)
{
	// Test switch block comments with horstmann style.
	// Horstmann style implies indented switch blocks.
	// textIn is broken brackets and indented switch blocks.
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "        /* comment1 */\n"
	    "        case 1:\n"
	    "            a += 1;\n"
	    "            break;\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo()\n"
	    "{   switch (foo)\n"
	    "    {   /* comment1 */\n"
	    "        case 1:\n"
	    "            a += 1;\n"
	    "            break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

struct NestedSwitchesF : public Test
{
	string textStr;
	const char* textIn;

	NestedSwitchesF()
	{
		textStr =
		    "\nvoid foo(int fooArg)\n"
		    "{\n"
		    "    int a, b;\n"
		    "    switch (fooArg)\n"
		    "    {\n"
		    "    case 1:\n"
		    "        a = 0;\n"
		    "    case 2:\n"
		    "    {\n"
		    "        b = 1;\n"
		    "    }\n"
		    "    case 3:\n"
		    "    {\n"
		    "        switch (fooArg)\n"
		    "        {\n"
		    "        case 1:\n"
		    "            a = 0;\n"
		    "        case 2:\n"
		    "        {\n"
		    "            b = 1;\n"
		    "        }\n"
		    "        case 3:\n"
		    "        {\n"
		    "            switch (fooArg)\n"
		    "            {\n"
		    "            case 1:\n"
		    "                a = 0;\n"
		    "            case 2:\n"
		    "            {\n"
		    "                b = 1;\n"
		    "            }\n"
		    "            }\n"
		    "        }\n"
		    "        }\n"
		    "    }\n"
		    "    }\n"
		    "}";
		textIn = textStr.c_str();
	}
};

TEST_F(NestedSwitchesF, SansIndents)
{
	// test nested switch indent with no options
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(textIn, textOut);
	delete [] textOut;
}

TEST_F(NestedSwitchesF, IndentSwitches)
{
	// test nested switch indent with indented switches
	char text[] =
	    "\nvoid foo(int fooArg)\n"
	    "{\n"
	    "    int a, b;\n"
	    "    switch (fooArg)\n"
	    "    {\n"
	    "        case 1:\n"
	    "            a = 0;\n"
	    "        case 2:\n"
	    "        {\n"
	    "            b = 1;\n"
	    "        }\n"
	    "        case 3:\n"
	    "        {\n"
	    "            switch (fooArg)\n"
	    "            {\n"
	    "                case 1:\n"
	    "                    a = 0;\n"
	    "                case 2:\n"
	    "                {\n"
	    "                    b = 1;\n"
	    "                }\n"
	    "                case 3:\n"
	    "                {\n"
	    "                    switch (fooArg)\n"
	    "                    {\n"
	    "                        case 1:\n"
	    "                            a = 0;\n"
	    "                        case 2:\n"
	    "                        {\n"
	    "                            b = 1;\n"
	    "                        }\n"
	    "                    }\n"
	    "                }\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}";
	char options[] = "indent-switches";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(NestedSwitchesF, IndentCases)
{
	// test nested switch indent with indented cases
	char text[] =
	    "\nvoid foo(int fooArg)\n"
	    "{\n"
	    "    int a, b;\n"
	    "    switch (fooArg)\n"
	    "    {\n"
	    "    case 1:\n"
	    "        a = 0;\n"
	    "    case 2:\n"
	    "        {\n"
	    "            b = 1;\n"
	    "        }\n"
	    "    case 3:\n"
	    "        {\n"
	    "            switch (fooArg)\n"
	    "            {\n"
	    "            case 1:\n"
	    "                a = 0;\n"
	    "            case 2:\n"
	    "                {\n"
	    "                    b = 1;\n"
	    "                }\n"
	    "            case 3:\n"
	    "                {\n"
	    "                    switch (fooArg)\n"
	    "                    {\n"
	    "                    case 1:\n"
	    "                        a = 0;\n"
	    "                    case 2:\n"
	    "                        {\n"
	    "                            b = 1;\n"
	    "                        }\n"
	    "                    }\n"
	    "                }\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}";
	char options[] = "indent-cases";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(NestedSwitchesF, IndentSwitches_IndentCases)
{
	// test nested switch indent with indented switches and cases
	char text[] =
	    "\nvoid foo(int fooArg)\n"
	    "{\n"
	    "    int a, b;\n"
	    "    switch (fooArg)\n"
	    "    {\n"
	    "        case 1:\n"
	    "            a = 0;\n"
	    "        case 2:\n"
	    "            {\n"
	    "                b = 1;\n"
	    "            }\n"
	    "        case 3:\n"
	    "            {\n"
	    "                switch (fooArg)\n"
	    "                {\n"
	    "                    case 1:\n"
	    "                        a = 0;\n"
	    "                    case 2:\n"
	    "                        {\n"
	    "                            b = 1;\n"
	    "                        }\n"
	    "                    case 3:\n"
	    "                        {\n"
	    "                            switch (fooArg)\n"
	    "                            {\n"
	    "                                case 1:\n"
	    "                                    a = 0;\n"
	    "                                case 2:\n"
	    "                                    {\n"
	    "                                        b = 1;\n"
	    "                                    }\n"
	    "                            }\n"
	    "                        }\n"
	    "                }\n"
	    "            }\n"
	    "    }\n"
	    "}";
	char options[] = "indent-switches, indent-cases";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Indent Cases
//-------------------------------------------------------------------------

TEST(IndentCases, LongOption)
{
	// test indent case blocks
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "    case 1:\n"
	    "        a += 1;\n"
	    "        break;\n"
	    "\n"
	    "    case 2:\n"
	    "        {\n"
	    "            a += 2;\n"
	    "            break;\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent-cases";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentCases, ShortOption)
{
	// test indent case blocks
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "    case 1:\n"
	    "        a += 1;\n"
	    "        break;\n"
	    "\n"
	    "    case 2:\n"
	    "        {\n"
	    "            a += 2;\n"
	    "            break;\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "-K";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentCases, Sans1)
{
	// test without indent case blocks
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "    case 1:\n"
	    "        a += 1;\n"
	    "        break;\n"
	    "\n"
	    "    case 2:\n"
	    "    {\n"
	    "        a += 2;\n"
	    "        break;\n"
	    "    }\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentCases, Sans2)
{
	// test indent=force-tab-x without indent case blocks
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch(x)\n"
	    "    {\n"
	    "    case 1:\n"
	    "    {\n"
	    "	bar = 1;\n"
	    "    }\n"
	    "    break;\n"
	    "\n"
	    "    default:\n"
	    "    {\n"
	    "	bar = 9;\n"
	    "    }\n"
	    "    break;\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent=force-tab-x";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentCases, Multiple1)
{
	// test multiple case statements per line, with keep one line statements
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "    case 1:case 2:\n"
	    "        a += 1;\n"
	    "        break;\n"
	    "\n"
	    "    case 3:case 4:\n"
	    "    {\n"
	    "        a += 2;\n"
	    "        break;\n"
	    "    }\n"
	    "    }\n"
	    "}\n";
	char options[] = "keep-one-line-statements";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentCases, Multiple2)
{
	// test multiple case statements per line, with break one line statements
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "    case 1:case 2:\n"
	    "        a += 1;\n"
	    "        break;\n"
	    "\n"
	    "    case 3:case 4:\n"
	    "    {\n"
	    "        a += 2;\n"
	    "        break;\n"
	    "    }\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "    case 1:\n"
	    "    case 2:\n"
	    "        a += 1;\n"
	    "        break;\n"
	    "\n"
	    "    case 3:\n"
	    "    case 4:\n"
	    "    {\n"
	    "        a += 2;\n"
	    "        break;\n"
	    "    }\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentCases, Switches)
{
	// test indent case blocks, with indent switch blocks
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "        case 1:\n"
	    "            a += 1;\n"
	    "            break;\n"
	    "\n"
	    "        case 2:\n"
	    "            {\n"
	    "                a += 2;\n"
	    "                break;\n"
	    "            }\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent-switches, indent-cases";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Indent Namespaces
// Additional tests are in the Brackets tests
//-------------------------------------------------------------------------

TEST(IndentNamespaces, LongOption)
{
	// test indent namespaces
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
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentNamespaces, ShortOption)
{
	// test indent namespaces short option
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
	char options[] = "-N";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentNamespaces, RunIn)
{
	// run-in brackets should NOT run-in to namespaces
	char text[] =
	    "\nnamespace FooName1\n"
	    "{\n"
	    "    bool foo;\n"
	    "}\n"
	    "\n"
	    "\nnamespace FooName2\n"
	    "{\n"
	    "    // comment1\n"
	    "}\n"
	    "\n"
	    "\nnamespace FooName3\n"
	    "{\n"
	    "    /* comment2 */\n"
	    "}\n";
	char options[] = "indent-namespaces, style=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Indent Labels
//-------------------------------------------------------------------------

TEST(IndentLabels, LongOption)
{
	// test indent labels
	char textIn[] =
	    "\nvoid Foo() {\n"
	    "    while (isFoo) {\n"
	    "        if (isFoo)\n"
	    "            goto error;\n"
	    "        bar1();\n"
	    "error:\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo() {\n"
	    "    while (isFoo) {\n"
	    "        if (isFoo)\n"
	    "            goto error;\n"
	    "        bar1();\n"
	    "    error:\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent-labels";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentLabels, ShortOption)
{
	// test indent labels short option
	char textIn[] =
	    "\nvoid Foo() {\n"
	    "    while (isFoo) {\n"
	    "        if (isFoo)\n"
	    "            goto error;\n"
	    "        bar1();\n"
	    "error:\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo() {\n"
	    "    while (isFoo) {\n"
	    "        if (isFoo)\n"
	    "            goto error;\n"
	    "        bar1();\n"
	    "    error:\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char options[] = "-L";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentLabels, Sans)
{
	// test labels without indent labels option
	char textIn[] =
	    "\nvoid Foo() {\n"
	    "    while (isFoo) {\n"
	    "        if (isFoo)\n"
	    "            goto error;\n"
	    "        bar1();\n"
	    "    error:\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo() {\n"
	    "    while (isFoo) {\n"
	    "        if (isFoo)\n"
	    "            goto error;\n"
	    "        bar1();\n"
	    "error:\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

// TODO: THE FOLLOWING TEST FAILS
//TEST(IndentLabelsSharp)
//{
//	// test indent labels for C#
//	char textIn[] =
//		"\nvoid Foo() {\n"
//		"    while (isFoo) {\n"
//		"        if (isFoo)\n"
//		"            goto error;\n"
//		"        bar1();\n"
//		"error:\n"
//		"        bar2();\n"
//		"    }\n"
//		"}\n";
//	char text[] =
//		"\nvoid Foo() {\n"
//		"    while (isFoo) {\n"
//		"        if (isFoo)\n"
//		"            goto error;\n"
//		"        bar1();\n"
//		"    error:\n"
//		"        bar2();\n"
//		"    }\n"
//		"}\n";
//	char options[] = "indent-labels, mode=cs";
//	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
//	EXPECT_STREQ(text, textOut);
//	delete [] textOut;
//}

//-------------------------------------------------------------------------
// AStyle Indent Preprocessor Block
//-------------------------------------------------------------------------

TEST(IndentPreprocBlock, LongOption)
{
	// test indent preprocessor block
	char textIn[] =
	    "\n#ifdef _WIN32\n"
	    "#define STDCALL __stdcall\n"
	    "#else\n"
	    "#define STDCALL\n"
	    "#endif";
	char text[] =
	    "\n#ifdef _WIN32\n"
	    "    #define STDCALL __stdcall\n"
	    "#else\n"
	    "    #define STDCALL\n"
	    "#endif";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, ShortOption)
{
	// test indent preprocessor block
	char textIn[] =
	    "\n#ifdef _WIN32\n"
	    "#define STDCALL __stdcall\n"
	    "#else\n"
	    "#define STDCALL\n"
	    "#endif";
	char text[] =
	    "\n#ifdef _WIN32\n"
	    "    #define STDCALL __stdcall\n"
	    "#else\n"
	    "    #define STDCALL\n"
	    "#endif";
	char options[] = "-xW";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, NoBeginningEmptyLine)
{
	// test indent preprocessor block without a beginning empty line
	char text[] =
	    "#ifdef _WIN32\n"
	    "    #define STDCALL __stdcall\n"
	    "#endif\n";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, ConsecutiveStatements)
{
	// test indent preprocessor block with consecutive statements
	char text[] =
	    "\n#ifdef _WIN32\n"
	    "    #define STDCALL __stdcall\n"
	    "#endif\n"
	    "#ifndef _WIN32\n"
	    "    #define STDCALL\n"
	    "#endif";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, NestedIndent)
{
	// test indent preprocessor block with nested indent
	char text[] =
	    "\n#ifdef _WIN32\n"
	    "    #ifdef __DMC__\n"
	    "        #ifdef FOO\n"
	    "            // digital mars doesn't have this\n"
	    "            const size_t SUBLANG_CHINESE_MACAU = 5;\n"
	    "        #endif\n"
	    "    #endif\n"
	    "#endif";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, ContainsElif)
{
	// test indent preprocessor block with #elif
	char text[] =
	    "\n#ifdef _WIN32\n"
	    "    #define MOZ_IMPORT_API __declspec(dllimport)\n"
	    "#elif defined(XP_OS2)\n"
	    "    #define MOZ_IMPORT_API  __declspec(dllimport)\n"
	    "#else\n"
	    "    #define MOZ_IMPORT_API MOZ_EXPORT\n"
	    "#endif";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, ContainsBrackets)
{
	// test indent preprocessor block contains brackets, should not be indented
	char text[] =
	    "\n#ifndef ASTYLE_LIB\n"
	    "// rewrite a stringstream converting the line ends\n"
	    "void Foo()\n"
	    "{\n"
	    "    string outStr;\n"
	    "}\n"
	    "#endif";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, ContainsSingleLineBlock)
{
	// test indent preprocessor block contains single line block, should not be indented
	char text[] =
	    "\n#ifdef __WIN32__\n"
	    "#include <windows.h>\n"
	    "inline void set_env(char* k, char* v) { SetEnvironmentVariable(k, v); }\n"
	    "#else\n"
	    "#include <stdlib.h>\n"
	    "inline void set_env(char* k, char* v) { setenv(k, v, 1); }\n"
	    "#endif";
	char options[] = "keep-one-line-blocks, indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, ContainsMultiLineDefine)
{
	// test indent preprocessor block contains multi-line define
	// should not be indented
	char text[] =
	    "\n#if DEBUG_OUTPUT == 1\n"
	    "#define TRACE(format, args...) \\\n"
	    "    DebugLog(F(format, ##args))\n"
	    "#else\n"
	    "#define TRACE(format, args...)\n"
	    "#endif";
	char options[] = "indent-preproc-define, indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, ConstructorInitializer1)
{
	// test indent preprocessor block in a constructor initializer
	// should be indented as code, not as a preprocessor block
	char text[] =
	    "\ncbAuiNotebook::cbAuiNotebook()\n"
	    "    : wxAuiNotebook(pParent),\n"
	    "      m_LastSelected(wxNOT_FOUND),\n"
	    "#ifdef __WXMSW__\n"
	    "      m_HasToolTip(true),\n"
	    "#endif\n"
	    "      m_SetZoomOnIdle(false)\n"
	    "{}";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, ConstructorInitializer2)
{
	// test indent preprocessor block in a constructor initializer
	// should be indented as code, not as a preprocessor block
	char text[] =
	    "\nwxPGCombo::wxPGCombo( wxPGCombo *parent, int style )\n"
	    "#if wxUSE_POPUPWIN\n"
	    "    : wxPGCombo(parent, style)\n"
	    "#else\n"
	    "    : wxPGCombo(parent,\n"
	    "                wxID_ANY,\n"
	    "                wxEmptyString,\n"
	    "                style)\n"
	    "#endif";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, FollowsNonIndentablePreprocessor)
{
	// test indent preprocessor block that follows a non-indentable statement
	char text[] =
	    "#include <foo>\n"
	    "#if !defined EXITED\n"
	    "    #define EXITED(x) 1\n"
	    "#endif\n"
	    "#include <foo1>\n"
	    "#if !defined EXITED1\n"
	    "    #define EXITED1(x) 1\n"
	    "#endif";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, HeaderIncludeGuard1)
{
	// test indent preprocessor with a header include guard
	// the include guard should be bypassed and included directives indented
	char text[] =
	    "\n/* * * * * * * * * * * * * * * * * * *\n"
	    " *   astyle.h\n"
	    " * * * * * * * * * * * * * * * * * * */\n"
	    "\n"
	    "#ifndef ASTYLE_H\n"
	    "#define ASTYLE_H\n"
	    "\n"
	    "#ifdef _MSC_VER\n"
	    "    #pragma warning(disable: 4996)\n"
	    "    #pragma warning(disable: 4267)\n"
	    "#endif\n"
	    "\n"
	    "#ifdef __INTEL_COMPILER\n"
	    "    #pragma warning(disable:  383)\n"
	    "    #pragma warning(disable:  981)\n"
	    "#endif\n"
	    "\n"
	    "#endif // closes ASTYLE_H\n"
	    "\n"
	    "/* * * * * * * * * * * * * * * * * * *\n"
	    " *  comments at end\n"
	    " * * * * * * * * * * * * * * * * * * */\n";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, HeaderIncludeGuard2)
{
	// test indent preprocessor with a header include guard
	// the include guard should be bypassed
	char text[] =
	    "\n#if !defined( __CHARTDEF_H__ )\n"
	    "#define __CHARTDEF_H__\n"
	    "#endif\n";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, Namespace)
{
	// test indent preprocessor block within a namespace
	char text[] =
	    "\nnamespace Foo {\n"
	    "\n"
	    "#ifdef _WIN32\n"
	    "    #define STDCALL __stdcall\n"
	    "#else\n"
	    "    #define STDCALL\n"
	    "#endif\n"
	    "\n"
	    "}   // end namespace";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, NamespaceIncludeGuard)
{
	// test indent preprocessor block within a namespace and include guard
	char text[] =
	    "\n#ifndef ASTYLE_H\n"
	    "#define ASTYLE_H\n"
	    "\n"
	    "namespace Foo {\n"
	    "\n"
	    "#ifdef _WIN32\n"
	    "    #define STDCALL __stdcall\n"
	    "#else\n"
	    "    #define STDCALL\n"
	    "#endif\n"
	    "\n"
	    "#ifdef _WIN32\n"
	    "    #ifdef __DMC__\n"
	    "        #ifdef FOO\n"
	    "            // digital mars doesn't have this\n"
	    "            const size_t SUBLANG_CHINESE_MACAU = 5;\n"
	    "        #endif\n"
	    "    #endif\n"
	    "#endif\n"
	    "\n"
	    "}   // end namespace\n"
	    "\n"
	    "#endif // closes ASTYLE_H";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, EmbeddedPreprocessor)
{
	// test indent preprocessor block within a unindented preprocessor
	// the embedded preprocessor beginning with _WIN32 should be indented
	char textIn[] =
	    "\n#ifndef ASTYLE_H\n"
	    "#define ASTYLE_H\n"
	    "\n"
	    "#ifdef _MACRO\n"
	    "\n"
	    "#ifdef _WIN32\n"
	    "#ifdef __DMC__\n"
	    "#ifdef FOO\n"
	    "// digital mars doesn't have this\n"
	    "const size_t SUBLANG_CHINESE_MACAU = 5;\n"
	    "#endif\n"
	    "#endif\n"
	    "#endif\n"
	    "\n"
	    "// so _MACRO will not indent\n"
	    "void Foo()\n"
	    "{}\n"
	    "\n"
	    "#endif  // _MACRO\n"
	    "\n"
	    "#endif // closes ASTYLE_H";
	char text[] =
	    "\n#ifndef ASTYLE_H\n"
	    "#define ASTYLE_H\n"
	    "\n"
	    "#ifdef _MACRO\n"
	    "\n"
	    "#ifdef _WIN32\n"
	    "    #ifdef __DMC__\n"
	    "        #ifdef FOO\n"
	    "            // digital mars doesn't have this\n"
	    "            const size_t SUBLANG_CHINESE_MACAU = 5;\n"
	    "        #endif\n"
	    "    #endif\n"
	    "#endif\n"
	    "\n"
	    "// so _MACRO will not indent\n"
	    "void Foo()\n"
	    "{}\n"
	    "\n"
	    "#endif  // _MACRO\n"
	    "\n"
	    "#endif // closes ASTYLE_H";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, PaddedPoundSign1)
{
	// test indent preprocessor block with the '#' separated from the statement
	char textIn[] =
	    "\n#if defined( DEBUG_PARSER )\n"
	    "#   if defined( DEBUG ) && defined( _MSC_VER )\n"
	    "#       include <windows.h>\n"
	    "#   endif\n"
	    "#endif\n";
	char text[] =
	    "\n#if defined( DEBUG_PARSER )\n"
	    "    #if defined( DEBUG ) && defined( _MSC_VER )\n"
	    "        #include <windows.h>\n"
	    "    #endif\n"
	    "#endif\n";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, PaddedPoundSign2)
{
	// test indent preprocessor block with the '#' separated from the statement
	// with no ending carriage return
	char textIn[] =
	    "\n#if defined( DEBUG_PARSER )\n"
	    "#   if defined( DEBUG ) && defined( _MSC_VER )\n"
	    "#       include <windows.h>\n"
	    "#   endif\n"
	    "#endif";
	char text[] =
	    "\n#if defined( DEBUG_PARSER )\n"
	    "    #if defined( DEBUG ) && defined( _MSC_VER )\n"
	    "        #include <windows.h>\n"
	    "    #endif\n"
	    "#endif";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, PaddedPoundSignEnd1)
{
	// test end of indent preprocessor block with the '#' separated from the statement
	// the final 'define' shpuld not be unpadded
	char textIn[] =
	    "\n#if defined( DEBUG_PARSER )\n"
	    "#   include <windows.h>\n"
	    "#endif\n"
	    "#    define FOO\n";
	char text[] =
	    "\n#if defined( DEBUG_PARSER )\n"
	    "    #include <windows.h>\n"
	    "#endif\n"
	    "#    define FOO\n";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, PaddedPoundSignEnd2)
{
	// test end of indent preprocessor block with the '#' separated from the statement
	// with no ending carriage return
	// the final 'define' should not be unpadded
	char textIn[] =
	    "\n#if defined( DEBUG_PARSER )\n"
	    "#   include <windows.h>\n"
	    "#endif\n"
	    "#    define FOO";
	char text[] =
	    "\n#if defined( DEBUG_PARSER )\n"
	    "    #include <windows.h>\n"
	    "#endif\n"
	    "#    define FOO";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, FillEmptyLines)
{
	// test indent preprocessor block with fill-empty-lines
	char textIn[] =
	    "\n#ifdef _WIN32\n"
	    "#define FOO\n"
	    "\n"
	    "#define BAR\n"
	    "#endif\n";
	char text[] =
	    "\n#ifdef _WIN32\n"
	    "    #define FOO\n"
	    "    \n"
	    "    #define BAR\n"
	    "#endif\n";
	char options[] = "fill-empty-lines, indent-preproc-block";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, SansFillEmptyLines)
{
	// test indent preprocessor block without fill-empty-lines
	char textIn[] =
	    "\n#ifdef _WIN32\n"
	    "    #define FOO\n"
	    "    \n"
	    "    #define BAR\n"
	    "#endif\n";
	char text[] =
	    "\n#ifdef _WIN32\n"
	    "    #define FOO\n"
	    "\n"
	    "    #define BAR\n"
	    "#endif\n";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, ClassHeader)
{
	// test indent preprocessor inside a class header
	// should not use the preprocessor block indent
	// use the class indent instead
	char text[] =
	    "\nclass ValueTooltip :\n"
	    "#ifndef __WXMAC__\n"
	    "    public wxPopupWindow\n"
	    "#else\n"
	    "    public wxWindow\n"
	    "#endif\n"
	    "{}";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, ClassInitializer)
{
	// test indent preprocessor inside a class initializer
	// should not use the preprocessor block indent
	// use the initializer indent instead
	char text[] =
	    "\nValueTooltip::ValueTooltip(cbWatch& watch, wxWindow* parent) :\n"
	    "#ifndef __WXMAC__\n"
	    "    wxPopupWindow(parent, wxBORDER_NONE | wxWANTS_CHARS),\n"
	    "#else\n"
	    "    wxWindow(parent, -1),\n"
	    "#endif\n"
	    "    m_watch(watch)\n"
	    "{}";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, UnmatchedParen)
{
	// test indent preprocessor with an unmatched paren
	// should NOT use the preprocessor block indent
	// should align the paren indent
	char text[] =
	    "\n#ifndef ASTYLE_MAIN_H\n"
	    "#define ASTYLE_MAIN_H\n"
	    "\n"
	    "#ifdef ASTYLE_LIB\n"
	    "utf16_t* AStyleMain(const utf16_t* pSourceIn,\n"
	    "                    const utf16_t* pOptions);\n"
	    "#endif\n"
	    "\n"
	    "#endif";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, UnmatchedParenNegative)
{
	// test indent preprocessor with an negative unmatched paren
	// the preprocessor block contains only a closing paren
	// should NOT use the preprocessor block indent
	// should align the paren indent
	char text[] =
	    "\nwxRegEx reStepI(wxT(\"(((\"),\n"
	    "#ifndef __WXMAC__\n"
	    "                wxRE_ADVANCED);\n"
	    "#else\n"
	    "                wxRE_EXTENDED);\n"
	    "#endif\n"
	    "wxRegEx reStepI2(_T(\"\\A\"),\n"
	    "#ifndef __WXMAC__\n"
	    "                 wxRE_ADVANCED);\n"
	    "#else\n"
	    "                 wxRE_EXTENDED);\n"
	    "#endif";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, Misc1)
{
	// this sequence caused a problem while testing
	char text[] =
	    "\n#ifdef __WIN32__\n"
	    "void set_env() { SetEnvironmentVariable(k, v); }\n"
	    "#endif\n"
	    "\n"
	    "#if !defined WEXITSTATUS\n"
	    "    #define WEXITSTATUS(x) x\n"
	    "#endif\n"
	    "\n"
	    "int main(int argc, char** argv)\n"
	    "{\n"
	    "    string outputFile;\n"
	    "}";
	char options[] = "keep-one-line-blocks, indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentPreprocBlock, Misc2)
{
	// this sequence caused a problem while testing
	char text[] =
	    "\nFILE* TiXmlFOpen()\n"
	    "{\n"
	    "#if defined(_MSC_VER)\n"
	    "    if (!err && fp)\n"
	    "        return fp;\n"
	    "    return 0;\n"
	    "#endif\n"
	    "}";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Indent Preprocessor Define
//-------------------------------------------------------------------------

TEST(IndentPreprocDefine, LongOption)
{
	// test indent preprocessor
	char textIn[] =
	    "\n#define Is_Bar(arg,a,b) \\\n"
	    "(Is_Foo((arg), (a)) \\\n"
	    "|| Is_Foo((arg), (b)))\n";
	char text[] =
	    "\n#define Is_Bar(arg,a,b) \\\n"
	    "    (Is_Foo((arg), (a)) \\\n"
	    "     || Is_Foo((arg), (b)))\n";
	char options[] = "indent-preproc-define";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocDefine, LongOptionDepreciated)
{
	// test depreciated indent preprocessor option
	// option was depreciated in release 2.04
	char textIn[] =
	    "\n#define Is_Bar(arg,a,b) \\\n"
	    "(Is_Foo((arg), (a)) \\\n"
	    "|| Is_Foo((arg), (b)))\n";
	char text[] =
	    "\n#define Is_Bar(arg,a,b) \\\n"
	    "    (Is_Foo((arg), (a)) \\\n"
	    "     || Is_Foo((arg), (b)))\n";
	char options[] = "indent-preprocessor";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocDefine, ShortOption)
{
	// test indent preprocessor short option
	char textIn[] =
	    "\n#define Is_Bar(arg,a,b) \\\n"
	    "(Is_Foo((arg), (a)) \\\n"
	    "|| Is_Foo((arg), (b)))\n";
	char text[] =
	    "\n#define Is_Bar(arg,a,b) \\\n"
	    "    (Is_Foo((arg), (a)) \\\n"
	    "     || Is_Foo((arg), (b)))\n";
	char options[] = "-w";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocDefine, InStatement)
{
	// test preprocessor statements with an in-statement indent
	char textIn[] =
	    "\n#define wxFORCED_FLAGS (wxSIMPLE_BORDER| \\\n"
	    "          wxNO_FULL_REPAINT_ON_RESIZE| \\\n"
	    "          wxCLIP_CHILDREN)\n";
	char text[] =
	    "\n#define wxFORCED_FLAGS (wxSIMPLE_BORDER| \\\n"
	    "                        wxNO_FULL_REPAINT_ON_RESIZE| \\\n"
	    "                        wxCLIP_CHILDREN)\n";
	char options[] = "indent-preproc-define";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocDefine, Sans)
{
	// test preprocessor statements without indent preprocessor option
	// they should not change
	char text[] =
	    "\n#define Is_Bar(arg,a,b) \\\n"
	    "  (Is_Foo((arg), (a)) \\\n"
	    "   || Is_Foo((arg), (b)))\n"
	    "\n"
	    "#define Is_Bar(arg,a,b) \\\n"
	    "      (Is_Foo((arg), (a)) \\\n"
	    "             || Is_Foo((arg), (b)))\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocDefine, SwitchSans1)
{
	// test preprocessor switch statements without indent preprocessor option
	// they should not change
	char text[] =
	    "\n#define GTEST_DEATH_TEST_(fail) \\\n"
	    "    {\\\n"
	    "       switch (fail) { \\\n"
	    "       case ::DeathTest: { \\\n"
	    "          SUPPRESS_CODE(); \\\n"
	    "          break; \\\n"
	    "          } \\\n"
	    "       } \\\n"
	    "    }"
	    "\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocDefine, SwitchSans2)
{
	// test preprocessor switch statements without indent preprocessor option
	// but with indent-switches and indent-cases
	// they should not change
	char text[] =
	    "\n#define GTEST_DEATH_TEST_(fail) \\\n"
	    "    {\\\n"
	    "       switch (fail) { \\\n"
	    "       case ::DeathTest: { \\\n"
	    "          SUPPRESS_CODE(); \\\n"
	    "          break; \\\n"
	    "          } \\\n"
	    "       } \\\n"
	    "    }"
	    "\n";
	char options[] = "indent-switches, indent-cases";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocDefine, SwitchIndent)
{
	// test preprocessor switch statements with switch indent
	// they should be indented
	char textIn[] =
	    "\n#define GTEST_DEATH_TEST_(fail) \\\n"
	    "    {\\\n"
	    "       switch (fail) { \\\n"
	    "       case ::DeathTest: { \\\n"
	    "          SUPPRESS_CODE(); \\\n"
	    "          break; \\\n"
	    "          } \\\n"
	    "       } \\\n"
	    "    }"
	    "\n";
	char text[] =
	    "\n#define GTEST_DEATH_TEST_(fail) \\\n"
	    "    {\\\n"
	    "        switch (fail) { \\\n"
	    "            case ::DeathTest: { \\\n"
	    "                SUPPRESS_CODE(); \\\n"
	    "                break; \\\n"
	    "            } \\\n"
	    "        } \\\n"
	    "    }"
	    "\n";
	char options[] = "indent-preproc-define, indent-switches";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocDefine, CaseIndent)
{
	// test preprocessor switch statements with case indent
	// they should be indented
	char textIn[] =
	    "\n#define GTEST_DEATH_TEST_(fail) \\\n"
	    "    {\\\n"
	    "       switch (fail) { \\\n"
	    "       case ::DeathTest: { \\\n"
	    "          SUPPRESS_CODE(); \\\n"
	    "          break; \\\n"
	    "          } \\\n"
	    "       } \\\n"
	    "    }"
	    "\n";
	char text[] =
	    "\n#define GTEST_DEATH_TEST_(fail) \\\n"
	    "    {\\\n"
	    "        switch (fail) { \\\n"
	    "        case ::DeathTest: { \\\n"
	    "                SUPPRESS_CODE(); \\\n"
	    "                break; \\\n"
	    "            } \\\n"
	    "        } \\\n"
	    "    }"
	    "\n";
	char options[] = "indent-preproc-define, indent-cases";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocDefine, SwitchCaseIndent)
{
	// test preprocessor switch statements with switch and case indent
	// they should be indented
	char textIn[] =
	    "\n#define GTEST_DEATH_TEST_(fail) \\\n"
	    "    {\\\n"
	    "       switch (fail) { \\\n"
	    "       case ::DeathTest: { \\\n"
	    "          SUPPRESS_CODE(); \\\n"
	    "          break; \\\n"
	    "          } \\\n"
	    "       } \\\n"
	    "    }"
	    "\n";
	char text[] =
	    "\n#define GTEST_DEATH_TEST_(fail) \\\n"
	    "    {\\\n"
	    "        switch (fail) { \\\n"
	    "            case ::DeathTest: { \\\n"
	    "                    SUPPRESS_CODE(); \\\n"
	    "                    break; \\\n"
	    "                } \\\n"
	    "        } \\\n"
	    "    }"
	    "\n";
	char options[] = "indent-preproc-define, indent-switches, indent-cases";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocDefine, CommentContinuation1)
{
	//  Comments within a preprocessor definition line can be
	//  continued without the backslash/newline.
	char textIn[] =
	    "\n#define MACRO(X,Y) \\\n"
	    "{                  \\\n"
	    "    /*  This comment breaks the indent engine.\n"
	    "     *  Compilers are ok with it */  \\\n"
	    "    {                      \\\n"
	    "        printf(X, Y);      \\\n"
	    "    }";
	char text[] =
	    "\n#define MACRO(X,Y) \\\n"
	    "    {                  \\\n"
	    "        /*  This comment breaks the indent engine.\n"
	    "         *  Compilers are ok with it */  \\\n"
	    "        {                      \\\n"
	    "            printf(X, Y);      \\\n"
	    "        }";
	char options[] = "indent-preproc-define";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocDefine, CommentContinuation2)
{
	//  Comments within a preprocessor definition line can be
	//  continued without the backslash/newline.
	char textIn[] =
	    "\n#define MACRO(X,Y) \\\n"
	    "{                  \\\n"
	    "    /*  This comment breaks the indent engine.\n"
	    "     *  Another line.\n"
	    "     *  Compilers are ok with it */  \\\n"
	    "    {                      \\\n"
	    "        printf(X, Y);      \\\n"
	    "    }";
	char text[] =
	    "\n#define MACRO(X,Y) \\\n"
	    "    {                  \\\n"
	    "        /*  This comment breaks the indent engine.\n"
	    "         *  Another line.\n"
	    "         *  Compilers are ok with it */  \\\n"
	    "        {                      \\\n"
	    "            printf(X, Y);      \\\n"
	    "        }";
	char options[] = "indent-preproc-define";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocDefine, PreprocessorWithinDefine)
{
	// Test a preprocessor conditional within a define.
	// This also tests the formatting after the preprocessor statement.
	// Caused a segmentation fault in Oct 2013.
	char textIn[] =
	    "\n#define SOMEDEF \\\n"
	    "#ifdef SOMEVAR \\\n"
	    "stuff();\n"
	    "#endif\n"
	    "\n"
	    "void foo()\n"
	    "{\n"
	    "return WriteBuf(NULL,\n"
	    "bytesPerLine);\n"
	    "}";
	char text[] =
	    "\n#define SOMEDEF \\\n"
	    "    #ifdef SOMEVAR \\\n"
	    "    stuff();\n"
	    "#endif\n"
	    "\n"
	    "void foo()\n"
	    "{\n"
	    "    return WriteBuf(NULL,\n"
	    "                    bytesPerLine);\n"
	    "}";
	char options[] = "--indent-preproc-define";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Indent Preprocessor Conditional
//-------------------------------------------------------------------------

TEST(IndentPreprocConditional, LongOption)
{
	// Test indent preprocessor conditional.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    #if wxUSE_UNICODE\n"
	    "    m_convertedText = wxString(wideBuff);\n"
	    "    #else\n"
	    "    m_convertedText = wxString(buffer);\n"
	    "    #endif\n"
	    "}";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, ShortOption)
{
	// Test indent preprocessor conditional short option.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    #if wxUSE_UNICODE\n"
	    "    m_convertedText = wxString(wideBuff);\n"
	    "    #else\n"
	    "    m_convertedText = wxString(buffer);\n"
	    "    #endif\n"
	    "}";
	char options[] = "-xw";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, UnattachedPoundSign)
{
	// Test indent preprocessor conditional with unattached pound sign.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    #    if wxUSE_UNICODE\n"
	    "    m_convertedText = wxString(wideBuff);\n"
	    "    #  else\n"
	    "    m_convertedText = wxString(buffer);\n"
	    "    # endif\n"
	    "}";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, SansTrailingSpace)
{
	// Test indent preprocessor conditional with no space before a trailing comment.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    #ifndef __WXMSW__//windows\n"
	    "    m_bIsConsole = target;\n"
	    "    #endif//ndef __WXMSW__\n"
	    "}";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, Include)
{
	// Test indent preprocessor conditional in #include statements.
	char text[] =
	    "\n#ifdef _WIN32\n"
	    "#include <windows.h>\n"
	    "#else\n"
	    "#include <dirent.h>\n"
	    "#ifdef __VMS\n"
	    "#include <starlet.h>\n"
	    "#endif\n"
	    "#endif";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, Declaration)
{
	// Test indent preprocessor conditional in a function declaration.
	char text[] =
	    "\nvoid RepeatedChars(wxT(\"[0-9]q\"),\n"
	    "                   #ifndef __WXMAC__\n"
	    "                   wxRE_ADVANCED);\n"
	    "                   #else\n"
	    "                   wxRE_EXTENDED);\n"
	    "                   #endif\n"
	    "{}";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, ExternC1)
{
	// Test indent preprocessor conditional around an extern "C" statement.
	char text[] =
	    "\n#ifdef __cplusplus\n"
	    "extern \"C\" {\n"
	    "#endif\n"
	    "\n"
	    "#ifdef __cplusplus\n"
	    "}\n"
	    "#endif";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, ExternC2)
{
	// Test indent preprocessor conditional around an extern "C" statement.
	// The closing extern "C" bracket is in a #else preprocessor statement.
	// It will NOT format correctly unless the variable
	// g_preprocessorCppExternCBracket is global.
	char text[] =
	    "\n#if HAVE_TSEARCH\n"
	    "#include <search.h>\n"
	    "#else\n"
	    "\n"
	    "#ifdef __cplusplus\n"
	    "extern \"C\" {\n"
	    "#endif\n"
	    "\n"
	    "/* comment line 1\n"
	    "   comment line 2\n"
	    " */\n"
	    "void tdelete(const void *key\n"
	    "             const void *value);\n"
	    "\n"
	    "#ifdef __cplusplus\n"
	    "}\n"
	    "#endif\n"
	    "\n"
	    "#endif";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, ExternC2Sans)
{
	// Test extern "C" statement WITHOUT indent preprocessor conditional.
	// The closing extern "C" bracket is in a #else preprocessor statement.
	// It will NOT format correctly unless the variable
	// g_preprocessorCppExternCBracket is global.
	char text[] =
	    "\n#if HAVE_TSEARCH\n"
	    "#include <search.h>\n"
	    "#else\n"
	    "\n"
	    "#ifdef __cplusplus\n"
	    "extern \"C\" {\n"
	    "#endif\n"
	    "\n"
	    "/* comment line 1\n"
	    "   comment line 2\n"
	    " */\n"
	    "void tdelete(const void *key\n"
	    "             const void *value);\n"
	    "\n"
	    "#ifdef __cplusplus\n"
	    "}\n"
	    "#endif\n"
	    "\n"
	    "#endif";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, DoubleConditional)
{
	// Test indent preprocessor conditional around a double conditional.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    #if defined(CC_TOKEN_DEBUG_OUTPUT)\n"
	    "    #if CC_TOKEN_DEBUG_OUTPUT\n"
	    "    wxStopWatch sw;\n"
	    "    sw.Start();\n"
	    "    #endif\n"
	    "    #endif\n"
	    "}";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, ElseMissingOpener)
{
	// Test indent preprocessor conditional with a missing #else opener.
	// Preprocessors will not be indented if no opening entry.
	char text[] =
	    "\nchar *section_list[] =\n"
	    "{\n"
	    "// #ifdef Q_OS_SOLARIS\n"
	    "    \"1B\", \"SunOS/BSD\",\n"
	    "#else\n"
	    "    \"2\", \"System Calls\",\n"
	    "#endif\n"
	    "    NULL, \"Misc. Reference\",\n"
	    "};\n";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, EndIfMissingOpener)
{
	// Test indent preprocessor conditional with a missing #endif opener.
	// Preprocessors will not be indented if no opening entry.
	char text[] =
	    "\nchar *section_list[] =\n"
	    "{\n"
	    "// #ifdef Q_OS_SOLARIS\n"
	    "    \"1B\", \"SunOS/BSD\",\n"
	    "// #else\n"
	    "    \"2\", \"System Calls\",\n"
	    "#endif\n"
	    "    NULL, \"Misc. Reference\",\n"
	    "};\n";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, ElIfMissingOpener)
{
	// Test indent preprocessor conditional with a missing #elif opener.
	// Preprocessors will not be indented if no opening entry.
	char text[] =
	    "\nchar *section_list[] =\n"
	    "{\n"
	    "// #ifdef Q_OS_SOLARIS\n"
	    "    \"1B\", \"SunOS/BSD\",\n"
	    "#elif Q_OS_\n"
	    "    \"2\", \"System Calls\",\n"
	    "#endif\n"
	    "    NULL, \"Misc. Reference\",\n"
	    "};\n";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, ClassDefinition)
{
	// Test indent preprocessor conditional in a class definition.
	char text[] =
	    "\nclass ValueTooltip :\n"
	    "    #ifndef __WXMAC__\n"
	    "    public wxPopupWindow\n"
	    "    #else\n"
	    "    public wxWindow\n"
	    "    #endif\n"
	    "{}";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, ClassInitializer)
{
	// Test indent preprocessor conditional in a class initializer.
	char text[] =
	    "\nSpellCheckerPlugin::SpellCheckerPlugin():\n"
	    "    m_pSpellChecker(NULL)\n"
	    "    #ifdef wxUSE_STATUSBAR\n"
	    "    ,m_fld(NULL)\n"
	    "    #endif\n"
	    "{}";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, FollowsConditional1)
{
	// Test indent preprocessor following a conditional statement.
	// Preprocessor is NOT followed by an open bracket.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (cleanOK)\n"
	    "    #if wxCHECK_VERSION(2, 9, 0)\n"
	    "        Log(GetTitle1(), bt);\n"
	    "    #else\n"
	    "        Log(GetTitle2(), bt);\n"
	    "    #endif\n"
	    "    else\n"
	    "    #if wxCHECK_VERSION(2, 9, 0)\n"
	    "        Log(GetTitle1(), bt);\n"
	    "    #else\n"
	    "        Log(GetTitle2(), bt);\n"
	    "    #endif\n"
	    "}";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, FollowsConditional2)
{
	// Test indent preprocessor following a conditional statement.
	// Preprocessor IS followed by an open bracket.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    while (text[i])\n"
	    "    #if wxCHECK_VERSION(2, 9, 0)\n"
	    "    {\n"
	    "        crc = (text[i++].GetValue());\n"
	    "    }\n"
	    "    #else\n"
	    "    {\n"
	    "        crc = (text[i++]);\n"
	    "    }\n"
	    "    #endif\n"
	    "}";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, FollowsConditional3)
{
	// Test indent preprocessor following a conditional statement.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    for (i = 0; i < menu->GetMenuItemCount(); ++i)\n"
	    "    {\n"
	    "        #if wxCHECK_VERSION(2, 9, 0)\n"
	    "        if (mm->GetItemLabel()==_(\"End-of-line mode\"))\n"
	    "        #else\n"
	    "        if (mm->GetLabel()==_(\"End-of-line mode\"))\n"
	    "        #endif\n"
	    "            menu->Remove(mm);\n"
	    "    }\n"
	    "}";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentPreprocConditional, FollowsConditional4)
{
	// Test indent preprocessor following a conditional statement.
	// This has a difficult combination of preprocessor statements.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (m_fontFileName.IsEmpty())\n"
	    "    {\n"
	    "        #if defined(__WXMSW__)\n"
	    "        if (m_file.IsEmpty() && m_font.IsOk())\n"
	    "            fontStream = LoadTrueTypeFontStream(m_font);\n"
	    "        else\n"
	    "        #elif defined(__WXMAC__)\n"
	    "        #if wxPDFMACOSX_HAS_CORE_TEXT\n"
	    "        if (m_file.IsEmpty() && m_font.IsOk())\n"
	    "        {\n"
	    "            #if wxCHECK_VERSION(2,9,0)\n"
	    "            CTFontRef fontRef = m_font.OSXGetCTFont();\n"
	    "            #else\n"
	    "            CTFontRef fontRef = m_font.MacGetCTFont();\n"
	    "            #endif\n"
	    "        }\n"
	    "        else\n"
	    "        #endif\n"
	    "        #endif\n"
	    "        {\n"
	    "            compressed = m_file.Lower().Right(2);\n"
	    "        }\n"
	    "    }\n"
	    "}";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Column one comment
//-------------------------------------------------------------------------

TEST(IndentCol1Comment, LongOption)
{
	// test indent column one comment
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    // comment 1\n"
	    "// comment 2\n"
	    " // comment 3\n"
	    "   // comment 4\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    // comment 1\n"
	    "    // comment 2\n"
	    "    // comment 3\n"
	    "    // comment 4\n"
	    "}\n";
	char options[] = "indent-col1-comments";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentCol1Comment, ShortOption)
{
	// test indent column one comment short option
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    // comment 1\n"
	    "// comment 2\n"
	    " // comment 3\n"
	    "   // comment 4\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    // comment 1\n"
	    "    // comment 2\n"
	    "    // comment 3\n"
	    "    // comment 4\n"
	    "}\n";
	char options[] = "-Y";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentCol1Comment, Sans)
{
	// test without indent column one comment
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    // comment 1\n"
	    "// comment 2\n"
	    " // comment 3\n"
	    "   // comment 4\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    // comment 1\n"
	    "// comment 2\n"
	    "// comment 3\n"
	    "    // comment 4\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(IndentCol1Comment, Namespace1)
{
	// test in namespace before the opening bracket
	// namespace is NOT indented
	char text[] =
	    "\n// ---------------------------\n"
	    "namespace\n"
	    "// ---------------------------\n"
	    "{\n"
	    "// comment\n"
	    "}";
	char options[] = "indent-col1-comments";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentCol1Comment, Namespace2)
{
	// test in namespace before the opening bracket
	// namespace IS indented
	char textIn[] =
	    "\n// ---------------------------\n"
	    "namespace\n"
	    "// ---------------------------\n"
	    "{\n"
	    "// comment\n"
	    "}";
	char text[] =
	    "\n// ---------------------------\n"
	    "namespace\n"
	    "// ---------------------------\n"
	    "{\n"
	    "    // comment\n"
	    "}";
	char options[] = "indent-namespaces, indent-col1-comments";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentCol1Comment, NamespaceSans1)
{
	// test in namespace before the opening bracket
	// namespace is NOT indented, no indent-col1-comments
	char textIn[] =
	    "\n// ---------------------------\n"
	    "namespace\n"
	    "// ---------------------------\n"
	    "{\n"
	    "    // comment\n"
	    "}";
	char text[] =
	    "\n// ---------------------------\n"
	    "namespace\n"
	    "// ---------------------------\n"
	    "{\n"
	    "// comment\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(IndentCol1Comment, NamespaceSans2)
{
	// test in namespace before the opening bracket
	// namespace IS indented, no indent-col1-comments
	char text[] =
	    "\n// ---------------------------\n"
	    "namespace\n"
	    "// ---------------------------\n"
	    "{\n"
	    "// comment\n"
	    "}";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Max Instatement Indent
//-------------------------------------------------------------------------

TEST(MaxInstatementIndent, LongOption)
{
	// test max instatement indent
	char textIn[] =
	    "\nvoid Long_40_Byte_Indent_Function_xxxxxxxxxxxxxxxx(bar1,\n"
	    "          bar2,\n"
	    "          bar3)\n"
	    "{\n"
	    "    char Long_40_Byte_Indent_Array_xxxxxxxxxxxxxxxxxxxxx[] = { red,\n"
	    "            green,\n"
	    "            blue\n"
	    "    };\n"
	    "}\n";
	char text[] =
	    "\nvoid Long_40_Byte_Indent_Function_xxxxxxxxxxxxxxxx(bar1,\n"
	    "                                                   bar2,\n"
	    "                                                   bar3)\n"
	    "{\n"
	    "    char Long_40_Byte_Indent_Array_xxxxxxxxxxxxxxxxxxxxx[] = { red,\n"
	    "                                                               green,\n"
	    "                                                               blue\n"
	    "                                                             };\n"
	    "}\n";
	char options[] = "max-instatement-indent=60";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MaxInstatementIndent, ShortOption)
{
	// test max instatement indent short option
	char textIn[] =
	    "\nvoid Long_40_Byte_Indent_Function_xxxxxxxxxxxxxxxx(bar1,\n"
	    "          bar2,\n"
	    "          bar3)\n"
	    "{\n"
	    "    char Long_40_Byte_Indent_Array_xxxxxxxxxxxxxxxxxxxxx[] = { red,\n"
	    "            green,\n"
	    "            blue\n"
	    "    };\n"
	    "}\n";
	char text[] =
	    "\nvoid Long_40_Byte_Indent_Function_xxxxxxxxxxxxxxxx(bar1,\n"
	    "                                                   bar2,\n"
	    "                                                   bar3)\n"
	    "{\n"
	    "    char Long_40_Byte_Indent_Array_xxxxxxxxxxxxxxxxxxxxx[] = { red,\n"
	    "                                                               green,\n"
	    "                                                               blue\n"
	    "                                                             };\n"
	    "}\n";
	char options[] = "-M60";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MaxInstatementIndent, Max)
{
	// test max instatement indent with the max value
	char textIn[] =
	    "\nvoid Long_80_Byte_Indent_Function_xxxxx12345678901234567890123456789012345678901234567890123456789012345678901234567890(bar1,\n"
	    "                                        bar2,\n"
	    "                                        bar3)\n"
	    "{\n"
	    "    char Long_80_Byte_Indent_Array_xx12345678901234567890123456789012345678901234567890123456789012345678901234567890[] = { red,\n"
	    "                                            green,\n"
	    "                                            blue\n"
	    "                                          };\n"
	    "}\n";
	char text[] =
	    "\nvoid Long_80_Byte_Indent_Function_xxxxx12345678901234567890123456789012345678901234567890123456789012345678901234567890(bar1,\n"
	    "                                                                                                                        bar2,\n"
	    "                                                                                                                        bar3)\n"
	    "{\n"
	    "    char Long_80_Byte_Indent_Array_xx12345678901234567890123456789012345678901234567890123456789012345678901234567890[] = { red,\n"
	    "                                                                                                                            green,\n"
	    "                                                                                                                            blue\n"
	    "                                                                                                                          };\n"
	    "}\n";
	char options[] = "max-instatement-indent=120";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MaxInstatementIndent, Sans)
{
	// test max instatement indent with no value
	// should use the default of 40
	char text[] =
	    "\nvoid Long_40_Byte_Indent_Function_xxx(bar1,\n"
	    "                                      bar2,\n"
	    "                                      bar3)\n"
	    "{\n"
	    "    char Long_40_Byte_Indent_Array_xx[] = { red,\n"
	    "                                            green,\n"
	    "                                            blue\n"
	    "                                          };\n"
	    "}\n";
	char options[] = "max-instatement-indent=";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MaxInstatementIndent, Misc1)
{
	// test instatement indent greater than max
	// should use 2 * indent (8)
	char text[] =
	    "\nvoid InsertClassMethodDlg::DoFillMethodsFor(wxCheckListBox* clb,\n"
	    "        Token* parentToken,\n"
	    "        const wxString& ns,\n"
	    "        bool includePrivate)\n"
	    "{\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MaxInstatementIndent, Misc2)
{
	// Text should align on the paren,
	// if max-instatement-indent is large enough.
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    m_pTextFileSearcher = TextFileSearcher::BuildTextFileSearcher ( findData.GetFindText(),\n"
	    "                          findData.GetMatchWord(),\n"
	    "                          findData.GetRegEx() );\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    m_pTextFileSearcher = TextFileSearcher::BuildTextFileSearcher ( findData.GetFindText(),\n"
	    "                                                                    findData.GetMatchWord(),\n"
	    "                                                                    findData.GetRegEx() );\n"
	    "}\n";
	char options[] = "max-instatement-indent=80";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MaxInstatementIndent, Misc3)
{
	// Text should align on the second paren,
	// if max-instatement-indent is large enough.
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    lineItemId = m_pTreeLog->AppendItem ( fileItemId, wxString::Format ( wxT ( \"%s: %s\" ),\n"
	    "                                          words[i].c_str(),\n"
	    "                                          words[i + 1].c_str() ) );\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    lineItemId = m_pTreeLog->AppendItem ( fileItemId, wxString::Format ( wxT ( \"%s: %s\" ),\n"
	    "                                                                         words[i].c_str(),\n"
	    "                                                                         words[i + 1].c_str() ) );\n"
	    "}\n";
	char options[] = "max-instatement-indent=80";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MaxInstatementIndent, ErrorMax)
{
	// test max instatement indent with an invalid value
	// should call the error handler
	char text[] =
	    "\nvoid Long_40_Byte_Indent_Function_xxx(bar1,\n"
	    "                                      bar2,\n"
	    "                                      bar3)\n"
	    "{\n"
	    "    char Long_40_Byte_Indent_Array_xx[] = { red,\n"
	    "                                            green,\n"
	    "                                            blue\n"
	    "                                          };\n"
	    "}\n";
	// use errorHandler2 to verify the error
	char options[] = "max-instatement-indent=121";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Min Conditional Indent
//-------------------------------------------------------------------------

TEST(MinConditionalIndent, LongOption)
{
	// test min conditional indent default
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (a < b\n"
	    "            || c < d)\n"
	    "        bar++;\n"
	    "\n"
	    "    if (a < b\n"
	    "            || c < d)\n"
	    "    {\n"
	    "        bar++;\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MinConditionalIndent, ShortOption)
{
	// test min conditional indent short option with a value of zero
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (a < b\n"
	    "            || c < d)\n"
	    "        bar++;\n"
	    "\n"
	    "    if (a < b\n"
	    "            || c < d)\n"
	    "    {\n"
	    "        bar++;\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (a < b\n"
	    "        || c < d)\n"
	    "        bar++;\n"
	    "\n"
	    "    if (a < b\n"
	    "        || c < d)\n"
	    "    {\n"
	    "        bar++;\n"
	    "    }\n"
	    "}\n";
	char options[] = "-m0";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MinConditionalIndent, Zero)
{
	// test min conditional indent with a value of 0
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (a < b\n"
	    "            || c < d)\n"
	    "        bar++;\n"
	    "\n"
	    "    if (a < b\n"
	    "            || c < d)\n"
	    "    {\n"
	    "        bar++;\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (a < b\n"
	    "        || c < d)\n"
	    "        bar++;\n"
	    "\n"
	    "    if (a < b\n"
	    "        || c < d)\n"
	    "    {\n"
	    "        bar++;\n"
	    "    }\n"
	    "}\n";
	char options[] = "min-conditional-indent=0";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MinConditionalIndent, One)
{
	// test min conditional indent with a value of 1
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (a < b\n"
	    "        || c < d)\n"
	    "        bar++;\n"
	    "\n"
	    "    if (a < b\n"
	    "        || c < d)\n"
	    "    {\n"
	    "        bar++;\n"
	    "    }\n"
	    "}\n";
	char options[] = "min-conditional-indent=1";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MinConditionalIndent, Two)
{
	// test min conditional indent with a value of 2
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (a < b\n"
	    "            || c < d)\n"
	    "        bar++;\n"
	    "\n"
	    "    if (a < b\n"
	    "            || c < d)\n"
	    "    {\n"
	    "        bar++;\n"
	    "    }\n"
	    "}\n";
	char options[] = "min-conditional-indent=2";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MinConditionalIndent, Three)
{
	// test min conditional indent with a value of 3
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "        if (a < b\n"
	    "            || c < d)\n"
	    "                bar++;\n"
	    "\n"
	    "        if (a < b\n"
	    "            || c < d)\n"
	    "        {\n"
	    "                bar++;\n"
	    "        }\n"
	    "}\n";
	char options[] = "min-conditional-indent=3, indent=spaces=8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MinConditionalIndent, NoValue)
{
	// test min conditional indent with no value
	// should use the default
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (a < b\n"
	    "            || c < d)\n"
	    "        bar++;\n"
	    "\n"
	    "    if (a < b\n"
	    "            || c < d)\n"
	    "    {\n"
	    "        bar++;\n"
	    "    }\n"
	    "}\n";
	char options[] = "min-conditional-indent=";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MinConditionalIndent, OverMax)
{
	// test min conditional indent over max
	// should use 2 * indent
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (!wxUnsetEnv(the_key))\n"
	    "    {\n"
	    "        Manager::Get()->GetLogManager()->LongLine(noParen,\n"
	    "                                                 _(\"Unsetting environment variable failed.\")));\n"
	    "        EV_DBGLOG(_T(\"EnvVars: Unsetting environment variable failed.\"));\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (!wxUnsetEnv(the_key))\n"
	    "    {\n"
	    "        Manager::Get()->GetLogManager()->LongLine(noParen,\n"
	    "                _(\"Unsetting environment variable failed.\")));\n"
	    "        EV_DBGLOG(_T(\"EnvVars: Unsetting environment variable failed.\"));\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MinConditionalIndent, ParenOverMax)
{
	// test min conditional indent over max with line ending in a paren
	// should use 2 * indent
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (!wxUnsetEnv(the_key))\n"
	    "    {\n"
	    "        Manager::Get()->GetLogManager()->Log(F(\n"
	    "                                                 _(\"Unsetting environment variable failed.\")));\n"
	    "        EV_DBGLOG(_T(\"EnvVars: Unsetting environment variable failed.\"));\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (!wxUnsetEnv(the_key))\n"
	    "    {\n"
	    "        Manager::Get()->GetLogManager()->Log(F(\n"
	    "                _(\"Unsetting environment variable failed.\")));\n"
	    "        EV_DBGLOG(_T(\"EnvVars: Unsetting environment variable failed.\"));\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(MinConditionalIndent, Error)
{
	// test min conditional indent with an invalid value
	// should call the error handler
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (a < b\n"
	    "            || c < d)\n"
	    "        bar++;\n"
	    "\n"
	    "    if (a < b\n"
	    "            || c < d)\n"
	    "    {\n"
	    "        bar++;\n"
	    "    }\n"
	    "}\n";
	// use errorHandler2 to verify the error
	char options[] = "min-conditional-indent=41";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------

}  // namespace
