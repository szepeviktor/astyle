// AStyleTest_BugFix.cpp
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
// AStyle version 2.06 TEST functions
//----------------------------------------------------------------------------

TEST(BugFix_V30, PreprocDefineMemoryLeak1)
{
	// This caused a memory leak in version 2.06.
	// If run in debug it will now cause an assert failure if it occurs.
	// It was caused by the #define ending on an empty line.
	char text[] =
	    "\n"
	    "#define TRACE_TO_FILE(msg)                      \\\n"
	    "    if (g_EnableDebugTraceFile)                 \\\n"
	    "        wxTextFile f(g_DebugTraceFile);         \\\n"
	    "\n"
	    "#define TRACE_THIS_TO_FILE(msg)                 \\\n"
	    "    if (!g_DebugTraceFile.IsEmpty())            \\\n"
	    "        wxTextFile f(g_DebugTraceFile);         \\\n"
	    "\n";
	char options[] = "indent-preproc-define";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V30, PreprocDefineMemoryLeak2)
{
	// This was mal-formatted when run WITHOUT indent-preproc-define.
	// It was caused by the #define ending on an empty line.
	char text[] =
	    "\n"
	    "#define TRACE_THIS_TO_FILE(msg)           \\\n"
	    "    if (!g_DebugTraceFile.IsEmpty())      \\\n"
	    "        cbAssert(f.Write() && f.Close()); \\\n"
	    "\n"
	    "CCLogger::CCLogger() :\n"
	    "    m_Parent(nullptr),\n"
	    "    m_AddTokenId(-1)\n"
	    "{}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V206, StripBrokenBraces)
{
	// The brace broken from should not have an ending space.
	char textIn[] =
	    "\n"
	    "[Test()]\n"
	    "public void Test2142 ()\n"
	    "{\n"
	    "    CodeCompletionBugTests.CombinedProviderTest (\n"
	    "        @\"enum Name {\n"
	    "	$p$\n"
	    "}\n"
	    "\", provider => {\n"
	    "        Assert.AreEqual ( 0, provider.Count );\n"
	    "    });\n"
	    "}";
	char text[] =
	    "\n"
	    "[Test()]\n"
	    "public void Test2142 ()\n"
	    "{\n"
	    "    CodeCompletionBugTests.CombinedProviderTest (\n"
	    "        @\"enum Name {\n"
	    "	$p$\n"
	    "}\n"
	    "\", provider =>\n"
	    "    {\n"
	    "        Assert.AreEqual ( 0, provider.Count );\n"
	    "    });\n"
	    "}";
	char options[] = "style=allman, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V206, CommaFirstInArguments)
{
	// Test commas first in argument list.
	char text[] =
	    "\n"
	    "static void setDBInfo(const std::string& dbname\n"
	    "                      , const std::string& username = \"\"\n"
	    "                      , const std::string host = \"localhost\"\n"
	    "                      , const unsigned int port = 3306);";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V206, TemplateClearVariable)
{
	// Variable isInTemplate should be cleared at end of a statement.
	// Second '=' continuation will NOT be indented if it is not reset.
	char text[] =
	    "\n"
	    "const double sound_speed\n"
	    "    = EulerEquations<dim>::template compute_sound_speed (W[q]);\n"
	    "const double velocity\n"
	    "    = EulerEquations<dim>::template compute_velocity_magnitude (W[q]);\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V206, AttachBraceInsideCommentAbort)
{
	// When formatting attached braces to the first line the program aborts.
	// This text CANNOT START WITH A BLANK LINE.
	char text[] =
	    "// comment\n"
	    "{\n"
	    "    int x = 10;\n"
	    "}";
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V206, BlockFormatAtStartOfFileAttached)
{
	// Format a block without a method name at the start of file.
	// Should not insert a beginning blank line.
	// This text CANNOT START WITH A BLANK LINE.
	char text[] =
	    "{\n"
	    "    int x = 10;\n"
	    "}";
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V206, BlockFormatAtStartOfFileBroken)
{
	// Format a block without a method name at the start of file.
	// Should not insert a beginning blank line.
	// This text CANNOT START WITH A BLANK LINE.
	char text[] =
	    "{\n"
	    "    int x = 10;\n"
	    "}";
	char options[] = "style=allman";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V206, BlockFormatAtStartOfFileRunIn)
{
	// Format a block without a method name at the start of file.
	// Should not insert a beginning blank line.
	// This text CANNOT START WITH A BLANK LINE.
	char textIn[] =
	    "{\n"
	    "    int x = 10;\n"
	    "}";
	char text[] =
	    "{   int x = 10;\n"
	    "}";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V206, QuoteEscapedSpace)
{
	// Recogninion of an escaped space within a quote.
	// The ending brace will be misplaced if the '\ ' isn't recognized.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    Str.Concat (Dummy__Str, \" \\ \");\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V206, CSharpUsingStatement)
{
	// Recogninion of a C# "using" statement as a header.
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    using (Process proc = Process.Start(astylewx))\n"
	    "    {\n"
	    "        proc.WaitForExit();\n"
	    "    }\n"
	    "    using (Process proc = Process.Start(astylewx))\n"
	    "        proc.WaitForExit();\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V206, CSharpUsingStatementSans)
{
	// Recogninion of a C# "using" declaration as a non-header.
	// The LoadContents method following a "using" directive should be indented.
	char text[] =
	    "\nusing System;\n"
	    "\n"
	    "public class AnalysisPanel : XmlPanel\n"
	    "{\n"
	    "    public void LoadContents()\n"
	    "    {\n"
	    "    }\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V206, PointerInACast)
{
	// Recogninion of a pointer in a C++ cast.
	// The static_cast in the last line has a pointer
	// that should NOT be padded with pad-oper.
	char text[] =
	    "\nCSyncClockFilter::CSyncClockFilter(HRESULT* phr)\n"
	    "    : CBaseFilter(nullptr, &m_Lock, CLSID_NULL)\n"
	    "    , m_Clock(static_cast<IBaseFilter*>(this), phr)\n"
	    "{}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle version 2.05 TEST functions
//----------------------------------------------------------------------------

TEST(BugFix_V205, PadOperator)
{
	// Beginning with version 2.05 this should be considered an operator.
	char textIn[] =
	    "\nstruct Bar\n"
	    "{\n"
	    "    int foo = 2;\n"
	    "    int bar = 4;\n"
	    "    int baz = foo*bar;\n"
	    "};";
	char text[] =
	    "\nstruct Bar\n"
	    "{\n"
	    "    int foo = 2;\n"
	    "    int bar = 4;\n"
	    "    int baz = foo * bar;\n"
	    "};";
	char options[] = "pad-oper, align-pointer=type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V205, AlignPointer)
{
	// This problem was caused by not clearing templateDepth when exiting checkIfTemplateOpener().
	char textIn[] =
	    "\nclass Test\n"
	    "{\n"
	    "    void g(Test && a);\n"
	    "    void f(int i) { i < 1; }\n"
	    "    void g(Test && a);\n"
	    "};";
	char text[] =
	    "\nclass Test\n"
	    "{\n"
	    "    void g(Test&& a);\n"
	    "    void f(int i) { i < 1; }\n"
	    "    void g(Test&& a);\n"
	    "};";
	char options[] = "align-pointer=type, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V205, StructObjectIdentification)
{
	// This struct caused an indentation problem.
	char text[] =
	    "\nvoid foo() {\n"
	    "    while (bytes < limit) {\n"
	    "        struct inotify *eventp = (struct inotify *)bytes;\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V205, CaseIndentAfterAsmBlock)
{
	// Fix the extra indent in a 'case' statement after an _asm block.
	// The '_asm' opening brace was not identified as a block opener
	// and the variable 'isInAsmBlock" was never being cleared
	// in ASBeautifier.
	char textIn[] =
	    "\nvoid foo() {\n"
	    "_asm {cld};\n"
	    "\n"
	    "    switch (var)\n"
	    "    {\n"
	    "    case 1:\n"
	    "            foo = this1;\n"
	    "        bar = this2;\n"
	    "        break;\n"
	    "\n"
	    "    default:\n"
	    "            foo = that1;\n"
	    "        bar = that2;\n"
	    "        break;\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nvoid foo() {\n"
	    "    _asm {cld};\n"
	    "\n"
	    "    switch (var)\n"
	    "    {\n"
	    "    case 1:\n"
	    "        foo = this1;\n"
	    "        bar = this2;\n"
	    "        break;\n"
	    "\n"
	    "    default:\n"
	    "        foo = that1;\n"
	    "        bar = that2;\n"
	    "        break;\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle version 2.04 TEST functions
//----------------------------------------------------------------------------

TEST(BugFix_V204, PreprocessorRecognition)
{
	// Should not identify ##errormsg as a preprocessor.
	char text[] =
	    "\n#define compile_time_assert(test, errormsg)                 \\\n"
	    "    do {                                                    \\\n"
	    "        struct ERROR_##errormsg {};                         \\\n"
	    "        typedef compile_time_check< (test) != 0 > tmplimpl; \\\n"
	    "        tmplimpl aTemp = tmplimpl(ERROR_##errormsg());      \\\n"
	    "        sizeof(aTemp);                                      \\\n"
	    "    } while (0)\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V204, OperatorRecognition)
{
	// These are operators, not a template.
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    fBold=def.fontWeight<FW_BOLD&&param.Find(L\"bd\")>=0;\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    fBold = def.fontWeight < FW_BOLD && param.Find(L\"bd\") >= 0;\n"
	    "}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V204, BlockOpener)
{
	// This "struct" should be recognized as a block opener.
	char text[] =
	    "\ntemplate <typename ArgType, typename ResType>\n"
	    "struct CallableTraits<ResType(*)(ArgType)> {\n"
	    "    typedef ResType ResultType;\n"
	    "    typedef ResType(*StorageType)(ArgType);\n"
	    "\n"
	    "    static void CheckIsValid(ResType(*f)(ArgType)) {\n"
	    "        GTEST_CHECK_(f != NULL)\n"
	    "                << \"NULL function pointer\";\n"
	    "    }\n"
	    "    template <typename T>\n"
	    "    static ResType Invoke(ResType(*f)(ArgType), T arg) {\n"
	    "        return (*f)(arg);\n"
	    "    }\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V204, TemplateAlignment)
{
	// Templates should align with the '<'.
	char text[] =
	    "\ntemplate < class X,\n"
	    "           class Y >\n"
	    "template <\n"
	    "    class X,\n"
	    "    class Y >\n"
	    "void foo()\n"
	    "{}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V204, PadOperatorWithComma)
{
	// An operator followed by a comma should NOT be padded after.
	// Can happens in a macro.
	char text[] =
	    "\nMATCHER(Eq, ==, \"is equal\");\n"
	    "MATCHER(Gt,  >, \"is >\");\n"
	    "MATCHER(Le, <=, \"is <=\");\n"
	    "MATCHER(Lt,  <, \"is <\");\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V204, OperatorWithBitwiseNot)
{
	// These should be recognized as an operator.
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    a = b*~c;\n"
	    "    a = b&~c;\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    a = b * ~c;\n"
	    "    a = b & ~c;\n"
	    "}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V204, AttachBraceToBackslash)
{
	// Fix braces to NOT attach to a line ending in a backslash (\).
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo) \\\n"	// line ends in backslash
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo) \\\n"	// line ends in backslash
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V204, PadParenInside)
{
	// Fix pad-paren-inside with align-pointer-name.
	// Pad paren inside should fully pad the (*) to ( * ).
	char textIn[] =
	    "\nstruct bfd_hash_entry* (*)( unsigned int );";
	char text[] =
	    "\nstruct bfd_hash_entry *( * )( unsigned int );";
	char options[] = "pad-paren-in, align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle version 2.03 TEST functions
//----------------------------------------------------------------------------

TEST(BugFix_V203, NegativeParenStack)
{
	// In a preprocessor directive it is possible for the parenStack to go negative.
	// This can cause formatting problems later on.
	// In this case the :Manager::" on the last line will not be indented correctly.
	char textIn[] =
	    "\nstatic wxRegEx reNextI(_T(\"[0-9]\"),\n"
	    "#ifndef __WXMAC__\n"
	    "    wxRE_ADVANCED);\n"
	    "#else\n"
	    "    wxRE_EXTENDED);\n"
	    "#endif\n"
	    "\n"
	    "class GdbCmd_AddBreakpointCondition\n"
	    "{\n"
	    "    void ParseOutput()\n"
	    "    {\n"
	    "        if (cbMessageBox() == wxID_YES)\n"
	    "        {\n"
	    "            m_pDriver->QueueCommand();\n"
	    "        }\n"
	    "        else if (alreadySet)\n"
	    "        {\n"
	    "            m_pDriver->RemoveBreakpoint(m_BP);\n"
	    "            ((cbEditor *)Manager::GetEditorManager()->SetDebugLine(-1);\n"
	    "        }\n"
	    "    }\n"
	    "};";
	char text[] =
	    "\nstatic wxRegEx reNextI(_T(\"[0-9]\"),\n"
	    "#ifndef __WXMAC__\n"
	    "                       wxRE_ADVANCED);\n"
	    "#else\n"
	    "                       wxRE_EXTENDED);\n"
	    "#endif\n"
	    "\n"
	    "class GdbCmd_AddBreakpointCondition {\n"
	    "    void ParseOutput() {\n"
	    "        if (cbMessageBox() == wxID_YES) {\n"
	    "            m_pDriver->QueueCommand();\n"
	    "        } else if (alreadySet) {\n"
	    "            m_pDriver->RemoveBreakpoint(m_BP);\n"
	    "            ((cbEditor *)\n"
	    "             Manager::GetEditorManager()->SetDebugLine(-1);\n"
	    "        }\n"
	    "    }\n"
	    "};";
	char options[] = "style=java, max-code-length=50";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V203, InStatementIndentExceedsLimit)
{
	// Indenting an instatement array that exceeds the max-instatement-indent.
	// It should NOT revert to a lesser indent.
	// Tabs are used to check the in-statement indent
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    static const PRUint32 UTF8CharLenTable[] = {0, 1, 0, 0, 0, 0, 2, 3,\n"
	    "            3, 3, 4, 4, 5, 5, 6, 6\n"
	    "                                               };\n"
	    "}";
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    static const PRUint32 UTF8CharLenTable[] = {0, 1, 0, 0, 0, 0, 2, 3,\n"
	    "                                                3, 3, 4, 4, 5, 5, 6, 6\n"
	    "                                               };\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V203, JavaAnonmyousMethod1)
{
	// Indenting a java anonymous function,
	// "_dialog.dispose();" should be correct.
	char text[] =
	    "\nprotected void _addButtons() {\n"
	    "    _buttonPanel.add(new JButton(new Action(\"Generate\") {\n"
	    "        public void actionPerformed(ActionEvent e) {\n"
	    "            result[0] = true;\n"
	    "            _dialog.dispose();\n"
	    "        }\n"
	    "    }));\n"
	    "}";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V203, JavaAnonmyousMethod2)
{
	// Indenting a java anonymous function,
	// "public boolean accept(File dir, String name)" should be correct.
	char text[] =
	    "\npublic String [] getSavedLayouts()\n"
	    "{\n"
	    "    File[] files = dir.listFiles(new FilenameFilter()\n"
	    "    {\n"
	    "        public boolean accept(File dir, String name)\n"
	    "        {\n"
	    "            return name.endsWith(\".xml\");\n"
	    "        }\n"
	    "    });\n"
	    "}";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V203, TrimContinuationLine)
{
	// A line end should not be trimmed if it ends with a '\'.
	// The line ending with "\\." should NOT be trimmed
	char textIn[] =
	    "\nboost::bimap<int,int> = boost::list_of<boost::bimap<int,int>::relation>\n"
	    "                        ( 1, 2 ) // \\ \n"
	    "                        ( 3, 4 )       \n"
	    "                        ( 5, 6 );      \n";
	char text[] =
	    "\nboost::bimap<int,int> = boost::list_of<boost::bimap<int,int>::relation>\n"
	    "                        ( 1, 2 ) // \\ \n"
	    "                        ( 3, 4 )\n"
	    "                        ( 5, 6 );\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V203, SansBreakAfterLeadingComments1)
{
	// Should NOT break after leading comments.
	char text[] =
	    "\n/* a */ int p1 = 0;\n"
	    "/* a */ int p2 = 0;\n"
	    "\n"
	    "/* a */ void f()\n"
	    "{\n"
	    "}\n"
	    "\n"
	    "/* a */ int p3 = 0;\n"
	    "/* a */ int p4 = 0;";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V203, SansBreakAfterLeadingComments2)
{
	// SHOULD break if the comments are not leading.
	char text[] =
	    "\n/* a */\n"
	    "int p1 = 0;\n"
	    "/* a */ int p2 = 0;\n"
	    "\n"
	    "/* a */\n"
	    "void f()\n"
	    "{\n"
	    "}\n"
	    "\n"
	    "/* a */\n"
	    "int p3 = 0;\n"
	    "/* a */ int p4 = 0;";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V203, DoubleTemplateDefinition)
{
	// Test formatting of template within a template.
	// Problem was the >> ending.
	char text[] =
	    "\nnamespace whatever\n"
	    "{\n"
	    "template <class Source, class Target, class TransformPolicy = GenericTransform<Source, Target>>\n"
	    "class ObjectModelConnection : public IObjectModelConnection, public TransformPolicy\n"
	    "{\n"
	    "public:\n"
	    "    ObjectModelConnection()\n"
	    "    {\n"
	    "    }\n"
	    "};\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V203, JavaWildcardGenericDefinitions)
{
	// In Java, wildcards can be used in generic definitions.
	// <? should NOT be considered an operator if --pad-oper is used.
	char text[] =
	    "\nabstract.void.bar1(<Child.extends.Parent>.x);\n"
	    "abstract.void.bar2(<?.extends.Parent>.x);\n"
	    "abstract.void.bar3( < ?.extends.Parent >.x );\n"
	    "InnerNode<?, ?> folder3 = (InnerNode<?, ?>)source.getChildAt(2);\n"
	    "public CheckBoxJList(Vector<?> listData);\n"
	    "public void compileEnded(File workDir, List<? extends File> excludedFiles) {};";
	char options[] = "pad-oper, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V203, QuoteContinuationPreprocessor)
{
	// A quote continuation with a preprocessor directive should
	// not be processed as a preprocessor directive.
	char text[] =
	    "\nconst char *dbus_includes = \"\\n\\\n"
	    "#include <dbus-c++/dbus.h>\\n\\\n"
	    "#include <cassert>\\n\\\n"
	    "\";\n"
	    "\n"
	    "void foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V203, StructReturnType)
{
	// Functions with a 'struct' return type and Linux style braces
	// should break the opening brace on a function.
	// The brace on the struct definition should be attached.
	char text[] =
	    "\nstruct foo {\n"
	    "    int foo;\n"
	    "    char bar;\n"
	    "};\n"
	    "\n"
	    "struct rt_wdb *\n"
	    "wdb_fopen_v(const char *filename, int version)\n"
	    "{\n"
	    "    struct db_i *dbip;\n"
	    "}";
	char options[] = "style=k/r";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V203, CaseWithBreakElseIfs)
{
	// Test case statement with break-elseifs.
	// It should not break the line after the 'case' statement.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    switch(x)\n"
	    "    {\n"
	    "    case 1:\n"
	    "        break;\n"
	    "    case 'r':\n"
	    "        break;\n"
	    "    case aspsJava:\n"
	    "        break;\n"
	    "    case FileTreeData::ftdkProject:\n"
	    "        break;\n"
	    "    case aspsHorstmann:     // Horstmann\n"
	    "        break;\n"
	    "    case (pttFunction):\n"
	    "        break;\n"
	    "    case _T(' '):\n"
	    "        break;\n"
	    "    }\n"
	    "}";
	char options[] = "break-elseifs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V203, CaseWithBreakBlocksDeleteEmptyLines)
{
	// Test comment in a case statement with break-blocks and delete-empty-lines.
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    switch(FileType)\n"
	    "    {\n"
	    "    case ftHeader:\n"
	    "    // fallthrough\n"
	    "\n"
	    "    case ftSource:\n"
	    "        bar = true;\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    switch(FileType)\n"
	    "    {\n"
	    "    case ftHeader:\n"
	    "\n"
	    "    // fallthrough\n"
	    "    case ftSource:\n"
	    "        bar = true;\n"
	    "    }\n"
	    "}";
	char options[] = "break-blocks, delete-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle version 2.02 TEST functions
//----------------------------------------------------------------------------

TEST(BugFix_V202, BreakBeforeAssignmenOperator1)
{
	// Line beginning with an assignment operator should be indented.
	char text[] =
	    "\nvoid main(void)\n"
	    "{\n"
	    "    a_long_variable_name\n"
	    "        = another_very_long_variable_name + a_long_function_name();\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V202, BreakBeforeAssignmenOperator2)
{
	// Line beginning with an assignment operator should be indented,
	// and continuation lines should also be indented.
	char text[] =
	    "\nvoid main(void)\n"
	    "{\n"
	    "    a_long_variable_name\n"
	    "        = another_very_long_variable_name\n"
	    "          + a_long_function_name()\n"
	    "          + another_long_function_name();\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V202, BreakBeforeAssignmenOperator3)
{
	// Line beginning with an assignment operator should be indented,
	// not a line containing an assignment operator.
	char text[] =
	    "\nvoid main(void)\n"
	    "{\n"
	    "    if (isalnum(*h)) {\n"
	    "        e=h+1;\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V202, PointerPreceedsAPaddedParen)
{
	// Pointer preceding a padded paren was spaced incorrectly
	char textIn[] =
	    "\nclass CrashHandler\n"
	    "{\n"
	    "    typedef void    * ( *AddHandler_t ) ( unsigned long );\n"
	    "    typedef void* ( *AddHandler_t ) ( unsigned long );\n"
	    "    typedef void *( *AddHandler_t ) ( unsigned long );\n"
	    "};";
	char text[] =
	    "\nclass CrashHandler\n"
	    "{\n"
	    "    typedef void    * ( *AddHandler_t ) ( unsigned long );\n"
	    "    typedef void * ( *AddHandler_t ) ( unsigned long );\n"
	    "    typedef void * ( *AddHandler_t ) ( unsigned long );\n"
	    "};";
	char options[] = "align-pointer=name, pad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V202, ConditionalWithinConditional)
{
	// When a ? conditional is in a conditional the foundQuestionMark flag is not reset.
	// This caused the following "case" ending : to be padded when pad-oper is used.
	// The ? conditional in the IF statement should be padded.
	char textIn[] =
	    "\nvoid main(void)\n"
	    "{\n"
	    "    if (version == IPMC_IP_VERSION_MLD?mld_filter_id:igmp_filter_id) {\n"
	    "        switch ( version ) {\n"
	    "        case IPMC_IP_VERSION_IGMP:\n"
	    "            break;\n"
	    "        default:\n"
	    "            break;\n"
	    "        }\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nvoid main(void)\n"
	    "{\n"
	    "    if (version == IPMC_IP_VERSION_MLD ? mld_filter_id : igmp_filter_id) {\n"
	    "        switch ( version ) {\n"
	    "        case IPMC_IP_VERSION_IGMP:\n"
	    "            break;\n"
	    "        default:\n"
	    "            break;\n"
	    "        }\n"
	    "    }\n"
	    "}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V202, TryFinallyExceptExtension1)
{
	// C++ __try __finally __except Microsoft extension
	// Added to headers and non-paren headers to be recognized as a command brace.
	// Broken braces, no style. __finally and __except are attached.
	char text[] =
	    "\nvoid fooBar()\n"
	    "{\n"
	    "    __try\n"
	    "    {\n"
	    "        foo1();\n"
	    "        __try\n"
	    "        {\n"
	    "            foo2();\n"
	    "        }\n"
	    "        __finally\n"
	    "        {\n"
	    "            foo3();\n"
	    "        }\n"
	    "    }\n"
	    "    __except(filter(111))\n"
	    "    {\n"
	    "        foo4();\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V202, TryFinallyExceptExtension2)
{
	// C++ __try __finally __except Microsoft extension
	// Added to headers and non-paren headers to be recognized as a command brace.
	// Attached braces, no style. __finally and __except are attached.
	char text[] =
	    "\nvoid fooBar() {\n"
	    "    __try {\n"
	    "        foo1();\n"
	    "        __try {\n"
	    "            foo2();\n"
	    "        } __finally {\n"
	    "            foo3();\n"
	    "        }\n"
	    "    } __except(filter(111)) {\n"
	    "        foo4();\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V202, TryFinallyExceptExtension3)
{
	// C++ __try __finally __except Microsoft extension
	// Added to headers and non-paren headers to be recognized as a command brace.
	// Attached braces changed to Allman style. __finally and __except are broken.
	char textIn[] =
	    "\nvoid fooBar() {\n"
	    "    __try {\n"
	    "        foo1();\n"
	    "        __try {\n"
	    "            foo2();\n"
	    "        } __finally {\n"
	    "            foo3();\n"
	    "        }\n"
	    "    } __except(filter(111)) {\n"
	    "        foo4();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nvoid fooBar()\n"
	    "{\n"
	    "    __try\n"
	    "    {\n"
	    "        foo1();\n"
	    "        __try\n"
	    "        {\n"
	    "            foo2();\n"
	    "        }\n"
	    "        __finally\n"
	    "        {\n"
	    "            foo3();\n"
	    "        }\n"
	    "    }\n"
	    "    __except(filter(111))\n"
	    "    {\n"
	    "        foo4();\n"
	    "    }\n"
	    "}";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V202, TryFinallyExceptExtension4)
{
	// C++ __try __finally __except Microsoft extension
	// Added to headers and non-paren headers to be recognized as a command brace.
	// Broken braces changed to Java style. __finally and __except are attached.
	char textIn[] =
	    "\nvoid fooBar()\n"
	    "{\n"
	    "    __try\n"
	    "    {\n"
	    "        foo1();\n"
	    "        __try\n"
	    "        {\n"
	    "            foo2();\n"
	    "        }\n"
	    "        __finally\n"
	    "        {\n"
	    "            foo3();\n"
	    "        }\n"
	    "    }\n"
	    "    __except(filter(111))\n"
	    "    {\n"
	    "        foo4();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nvoid fooBar() {\n"
	    "    __try {\n"
	    "        foo1();\n"
	    "        __try {\n"
	    "            foo2();\n"
	    "        } __finally {\n"
	    "            foo3();\n"
	    "        }\n"
	    "    } __except(filter(111)) {\n"
	    "        foo4();\n"
	    "    }\n"
	    "}";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V202, PreprocessorDefine_SansBreakAfterComment)
{
	// Preprocessor define should not break after a comment.
	char text[] =
	    "\n#define ABC { def; /*ghi*/ }";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V202, BreakBlocks_ConstVariableFollowsHeader)
{
	// With break-blocks where a "const" variable follows a header, the lines
	// continued to be inserted. There should not be an empty line between the
	// "const int" and "int b" statements.
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (true) { x = 1;}\n"
	    "    const int a = bar();\n"
	    "    int b = baz();\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (true) {\n"
	    "        x = 1;\n"
	    "    }\n"
	    "\n"
	    "    const int a = bar();\n"
	    "    int b = baz();\n"
	    "}";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V202, RunInBraces_ColonIdentification)
{
	// With run-in braces when using indent-namespaces and indent-classes with a class modifier
	// on the same line as the class opening brace resulted in failure to recognize the class indent.
	// This was a problem only when indent-labels was also used.
	char text[] =
	    "\nnamespace\n"
	    "{\n"
	    "    class wxsNotebookExtra\n"
	    "    {   public:\n"				// this line is the problem
	    "            void OnEnumProperties(long Flags)\n"
	    "            {   WXS_SHORT_STRING(wxsNotebookExtra);\n"
	    "                WXS_BOOL(wxsNotebookExtra);\n"
	    "            }\n"
	    "    };\n"
	    "}\n";
	char options[] = "indent-namespaces, indent-classes, indent-labels";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle version 2.01 TEST functions
//----------------------------------------------------------------------------

TEST(BugFix_V201, UnpadParen_PadParenIn)
{
	// Using both --unpad-paren and --pad-paren-in, becomes "if(( isFoo ) )"'
	// The leading paren was unpadded by the unpad-paren option.
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if ((isFoo))\n"
	    "        bar();\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if( ( isFoo ) )\n"
	    "        bar();\n"
	    "}";
	char options[] = "unpad-paren, pad-paren-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, AlignOnBrace)
{
	// Test alignment on a brace.
	char text[] =
	    "\n[Browsable(true),\n"
	    " DisplayName(\"Display ordinal\"),\n"
	    " CustomAttribute(2)]\n"
	    "public int DisplayOrdinal\n"
	    "{\n"
	    "//...\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, TwoBracesOnLine)
{
	// Test brace alignment with two braces on a line.
	char text[] =
	    "\nvoid LoadToc()\n"
	    "{\n"
	    "    if (!IsLocalHelp) DataContext = null;\n"
	    "    else DataContext = new[] { new TocEntry(-1)\n"
	    "        {\n"
	    "            Title = StringParser.Parse(\"${HelpLibraryRootTitle}\")\n"
	    "        }\n"
	    "    };\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, WhitesmithSingleLineArray)
{
	// Test whitesmith style with a single line array.
	// The last single line entry should be correctly indented.
	char text[] =
	    "\npublic void foo()\n"
	    "    {\n"
	    "    optionSet = new OptionSet ()\n"
	    "        {\n"
	    "            { 0, \"Assemblies\" },\n"
	    "            { 1, \"Namespaces\" },\n"
	    "            { 2, \"Help\" }\n"
	    "        };\n"
	    "    }";
	char options[] = "style=whitesmith, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, NotInTemplate)
{
	// The following statements were incorrectly flagged as templates.
	// This caused add-braces to attach the opening brace in the wrong place.
	// The function checkIfTemplateOpener() was corrected.
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    for(k=31; k>=0; k-=2)\n"
	    "    {\n"
	    "        if(hi & (1 << (k >> 1))) y32u += 1 << k;\n"
	    "        if(lo & (1 << (k >> 1))) y32u += 1 << (k-1);\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    for(k=31; k>=0; k-=2)\n"
	    "    {\n"
	    "        if(hi & (1 << (k >> 1))) {\n"
	    "            y32u += 1 << k;\n"
	    "        }\n"
	    "        if(lo & (1 << (k >> 1))) {\n"
	    "            y32u += 1 << (k-1);\n"
	    "        }\n"
	    "    }\n"
	    "}";
	char options[] = "add-braces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, PointerOrReferenceAtEndOfLine)
{
	// Test align-pointer=name mis-aligning a pointer followed by a space at end of line.
	// The following test has a space after the * and & at end of line.
	// It was causing the * or & to be attached to the type on the first format.
	// Following formats moved it to the correct position.
	char textIn[] =
	    "\nconst char * \n"
	    "foo1() const\n"
	    "{\n"
	    "    return bar1;\n"
	    "}\n"
	    "\n"
	    "const Path & \n"
	    "foo2() const\n"
	    "{\n"
	    "    return bar2;\n"
	    "}";
	char text[] =
	    "\nconst char *\n"
	    "foo1() const\n"
	    "{\n"
	    "    return bar1;\n"
	    "}\n"
	    "\n"
	    "const Path &\n"
	    "foo2() const\n"
	    "{\n"
	    "    return bar2;\n"
	    "}";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, ExtraSpaceLineComment_PadParen_DeleteEmptyLines)
{
	// Test pad paren and delete empty lines options.
	// The line before the empty line was receiving an extra space after the semi-colon.
	// The empty line had to be followed by a line comment line for this to happen.
	char textIn[] =
	    "\nvoid areaConstruction()\n"
	    "{\n"
	    "    QCOMPARE(toolViewsPrinter1, QString(\"\\\n"
	    "toolview1.1.1 [ left ]\\\n"
	    "toolview1.2.1 [ bottom ]\\\n"
	    "\"));\n"
	    "\n"
	    "    // line comment follows empty line\n"
	    "    AreaViewsPrinter viewsPrinter2;\n"
	    "}";
	char text[] =
	    "\nvoid areaConstruction()\n"
	    "{\n"
	    "    QCOMPARE ( toolViewsPrinter1, QString ( \"\\\n"
	    "toolview1.1.1 [ left ]\\\n"
	    "toolview1.2.1 [ bottom ]\\\n"
	    "\" ) );\n"
	    "    // line comment follows empty line\n"
	    "    AreaViewsPrinter viewsPrinter2;\n"
	    "}";
	char options[] = "pad-paren, delete-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, ExtraSpaceComment_PadParen_DeleteEmptyLines)
{
	// Test pad paren and delete empty lines options.
	// The line before the empty line was receiving an extra space after the semi-colon.
	// The empty line had to be followed by a comment line for this to happen.
	char textIn[] =
	    "\nvoid areaConstruction()\n"
	    "{\n"
	    "    QCOMPARE(toolViewsPrinter1, QString(\"\\\n"
	    "toolview1.1.1 [ left ]\\\n"
	    "toolview1.2.1 [ bottom ]\\\n"
	    "\"));\n"
	    "\n"
	    "    /* comment follows empty line */\n"
	    "    AreaViewsPrinter viewsPrinter2;\n"
	    "}";
	char text[] =
	    "\nvoid areaConstruction()\n"
	    "{\n"
	    "    QCOMPARE ( toolViewsPrinter1, QString ( \"\\\n"
	    "toolview1.1.1 [ left ]\\\n"
	    "toolview1.2.1 [ bottom ]\\\n"
	    "\" ) );\n"
	    "    /* comment follows empty line */\n"
	    "    AreaViewsPrinter viewsPrinter2;\n"
	    "}";
	char options[] = "pad-paren, delete-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, Switch_FillEmptyLines_BreakBlocks)
{
	// Test fill empty lines and break blocks options in a switch.
	// This bug was caused by the ASEnhancer object not being called for new empty lines.
	// The line added after "return" should be correctly filled.
	char textIn[] =
	    "\nbool foo()\n"
	    "{\n"
	    "    switch (type) {\n"
	    "    case WindowDeactivate:\n"
	    "    {\n"
	    "        if (insideThis(object))\n"
	    "            return false;\n"
	    "        break;\n"
	    "    }\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nbool foo()\n"
	    "{\n"
	    "    switch (type) {\n"
	    "    case WindowDeactivate:\n"
	    "    {\n"
	    "        if (insideThis(object))\n"
	    "            return false;\n"
	    "            \n"
	    "        break;\n"
	    "    }\n"
	    "    }\n"
	    "}";
	char options[] = "fill-empty-lines, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, AppendCharInsideCommentsPostPreprocessor)
{
	// An opening brace should not be appended to a preprocessor statement.
	// This bug occurred only when comments followed the preprocessor.
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "#if wxUSE_UXTHEME\n"
	    "    if (isFoo)\n"
	    "        bar1();\n"
	    "    else\n"
	    "#endif //wxUSE_UXTHEME\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nvoid foo() {\n"
	    "#if wxUSE_UXTHEME\n"
	    "    if (isFoo)\n"
	    "        bar1();\n"
	    "    else\n"
	    "#endif //wxUSE_UXTHEME\n"
	    "    {\n"
	    "        bar2();\n"
	    "    }\n"
	    "}";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, SwitchBraceInPreprocessor1)
{
	// Test that the brace before a preprocessor statement in a "switch" is recognized.
	// If enhance is called with the argument isInPreprocessor instead of isImmediatelyPostPreprocessor,
	// the preceding brace will not be recognized. This causes the "switch" statement closing
	// brace to be incorrectly indented.
	char text[] =
	    "\nvoid wxsListBox::OnBuildCreatingCode()\n"
	    "{\n"
	    "    switch(GetLanguage()) {\n"
	    "    case wxsCPP: {\n"
	    "        if(DefaultSelection == (int)i) {\n"
	    "            Codef(ASetSelection));\n"
	    "        }\n"
	    "#if wxCHECK_VERSION(2, 9, 0)\n"
	    "        Codef(ArrayChoices[i].wx_str());\n"
	    "#endif\n"
	    "        return;\n"
	    "    }\n"
	    "    } // possible wrong indent\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, SwitchBraceInPreprocessor2)
{
	// Test that the brace after a preprocessor statement in a "switch" is recognized.
	// If the variable isImmediatelyPostPreprocessor is not cleared at a line break
	// and braces are changed from attached to broken, a brace will be incorrectly indented.
	char textIn[] =
	    "\nvoid OnBuildCreatingCode() {\n"
	    "    switch (GetLanguage()) {\n"
	    "    case wxsCPP: {\n"
	    "        if (!Defaults) {\n"
	    "#if wxCHECK_VERSION(2, 9, 0)\n"
	    "            Codef(ColourDataName());\n"
	    "#endif\n"
	    "        } else {\n"
	    "            Codef(\"%C(%W);\");\n"
	    "        }\n"
	    "        return;\n"
	    "    }\n"
	    "    } // possible wrong indent\n"
	    "}";
	char text[] =
	    "\nvoid OnBuildCreatingCode()\n"
	    "{\n"
	    "    switch (GetLanguage())\n"
	    "    {\n"
	    "    case wxsCPP:\n"
	    "    {\n"
	    "        if (!Defaults)\n"
	    "        {\n"
	    "#if wxCHECK_VERSION(2, 9, 0)\n"
	    "            Codef(ColourDataName());\n"
	    "#endif\n"
	    "        }\n"
	    "        else\n"
	    "        {\n"
	    "            Codef(\"%C(%W);\");\n"
	    "        }\n"
	    "        return;\n"
	    "    }\n"
	    "    } // possible wrong indent\n"
	    "}";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, PopParenStackOnBrace)
{
	// Test that paren stack is popped when an attached brace preceding a comment is broken.
	// In the test case it caused the brace following line "public bool ShowingDialog"
	// to not be broken.
	char textIn[] =
	    "\nvoid OnRootMonitorDisposed() {\n"
	    "    eventThread.BeginInvoke (\n"
	    "    ( Action ) delegate {\n"
	    "        if ( rootMonitorIsDisposed ) { // ignore double dispose\n"
	    "                return;\n"
	    "        }\n"
	    "    });\n"
	    "}\n"
	    "\n"
	    "sealed class MonitorImpl : IProgressMonitor {\n"
	    "    public bool ShowingDialog\n"
	    "    {   get { return collector.ShowingDialog; }\n"
	    "\n"
	    "        set { collector.SetShowingDialog ( value ); }\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nvoid OnRootMonitorDisposed()\n"
	    "{   eventThread.BeginInvoke (\n"
	    "        ( Action ) delegate\n"
	    "    {   if ( rootMonitorIsDisposed )   // ignore double dispose\n"
	    "        {   return;\n"
	    "        }\n"
	    "    });\n"
	    "}\n"
	    "\n"
	    "sealed class MonitorImpl : IProgressMonitor\n"
	    "{   public bool ShowingDialog\n"
	    "    {   get\n"
	    "        {   return collector.ShowingDialog;\n"
	    "        }\n"
	    "\n"
	    "        set\n"
	    "        {   collector.SetShowingDialog ( value );\n"
	    "        }\n"
	    "    }\n"
	    "}";
	char options[] = "style=run-in, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, SharpBreakSingleLineStatements)
{
	// Test a breaking a sharp abstract method single line block.
	// Both of the ending braces should be broken.
	// TODO: The brace in-statement formatting could be improved.
	char textIn[] =
	    "\nvoid LoadToc()\n"
	    "{\n"
	    "    if (!IsLocalHelp) DataContext = null;\n"
	    "    else DataContext = new[] { new TocEntry(-1) {Title = StringParser.Parse(\"${HelpLibraryRootTitle}\")}};\n"
	    "}";
	char text[] =
	    "\nvoid LoadToc()\n"
	    "{\n"
	    "    if (!IsLocalHelp) DataContext = null;\n"
	    "    else DataContext = new[] { new TocEntry(-1) {\n"
	    "            Title = StringParser.Parse(\"${HelpLibraryRootTitle}\")\n"
	    "        }\n"
	    "    };\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, JavaBreakOneLineBlocks1)
{
	// This tests changes in ASFormatter::isOneLineBlockReached().
	char textIn[] =
	    "\npublic class MutableFileProperty extends FileProperty {\n"
	    "    public MutableFileProperty(String name, File initialFile, String help) {\n"
	    "        super(name,new Thunk<File>() { public File value() { return null; } }, help);\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\npublic class MutableFileProperty extends FileProperty {\n"
	    "    public MutableFileProperty(String name, File initialFile, String help) {\n"
	    "        super(name,new Thunk<File>() {\n"
	    "            public File value() {\n"
	    "                return null;\n"
	    "            }\n"
	    "        }, help);\n"
	    "    }\n"
	    "}";
	char options[] = "mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, JavaBreakOneLineBlocks2)
{
	// This tests changes in ASFormatter::isOneLineBlockReached().
	char textIn[] =
	    "\nprotected void makePopupMenuActions() {\n"
	    "    AbstractAction[] acts = new AbstractAction[] {\n"
	    "        new AbstractAction() { public void actionPerformed(ActionEvent e) { goToRegion(); } },\n"
	    "    };\n"
	    "}";
	char text[] =
	    "\nprotected void makePopupMenuActions() {\n"
	    "    AbstractAction[] acts = new AbstractAction[] {\n"
	    "    new AbstractAction() {\n"
	    "        public void actionPerformed(ActionEvent e) {\n"
	    "            goToRegion();\n"
	    "        }\n"
	    "    },\n"
	    "    };\n"
	    "}";
	char options[] = "mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, DontAttachBraceToComment)
{
	// This is for array type braces.
	// The one line brace following the comment should not be attached.
	char text[] =
	    "\nstatic Dictionary<Gdk.Key, string> keyStringMaps = new Dictionary<Gdk.Key, string> () {\n"
	    "    { Gdk.Key.Tab,    \"Tab\"   },\n"
	    "    { Gdk.Key.Return, \"Enter\" }, /* CR Return */\n"
	    "    { Gdk.Key.Escape, \"Esc\"   },\n"
	    "};";
	char options[] = "style=java, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, DontAttachBraceToLineComment)
{
	// This is for array type braces.
	// The one line brace following the line comment should not be attached.
	char text[] =
	    "\nstatic Dictionary<Gdk.Key, string> keyStringMaps = new Dictionary<Gdk.Key, string> () {\n"
	    "    { Gdk.Key.Tab,    \"Tab\"   },\n"
	    "    { Gdk.Key.Return, \"Enter\" }, // CR Return\n"
	    "    { Gdk.Key.Escape, \"Esc\"   },\n"
	    "};";
	char options[] = "style=java, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, SharpTemplateArrayDefinition)
{
	// The second brace should be identified as an array type.
	// The ending brace on the second line should not be broken.
	char text[] =
	    "\nstatic Dictionary<string, char> stringCharMaps = new Dictionary<string, char> () {\n"
	    "    { \"Nul\",   '0' },\n"
	    "    { \"Space\", '1'  },\n"
	    "    { \"CR\",    '2' },\n"
	    "};";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, RunInCommentEndsWithBrace)
{
	// Run-in braces did not break line if the line ends with a brace.
	char textIn[] =
	    "\npublic CSharpSpanParser ()\n"
	    "{\n"
	    "/*      foreach (Span span in mode.Spans) {\n"
	    "            preprocessorSpan = span;\n"
	    "        }\n"
	    "    }*/\n"
	    "}";
	char text[] =
	    "\npublic CSharpSpanParser ()\n"
	    "{   /*      foreach (Span span in mode.Spans) {\n"
	    "                preprocessorSpan = span;\n"
	    "            }\n"
	    "        }*/\n"
	    "}";
	char options[] = "style=run-in, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, JavaSingleLineAbstractMethod1)
{
	// Single line abstract method should break the closing brace.
	char textIn[] =
	    "\npublic void foo()\n"
	    "{\n"
	    "    new Runnable()\n"
	    "    { public void run() { } }\n"
	    "}";
	char text[] =
	    "\npublic void foo()\n"
	    "{\n"
	    "    new Runnable()\n"
	    "    {\n"
	    "        public void run() { }\n"
	    "    }\n"
	    "}";
	char options[] = "mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, JavaSingleLineAbstractMethod2)
{
	// Single line abstract method should break the closing brace.
	// Attached braces.
	char textIn[] =
	    "\npublic void foo()\n"
	    "{\n"
	    "    new Runnable()\n"
	    "    { public void run() { } }\n"
	    "}";
	char text[] =
	    "\npublic void foo()\n"
	    "{\n"
	    "    new Runnable() {\n"
	    "        public void run() { }\n"
	    "    }\n"
	    "}";
	char options[] = "style=kr, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, JavaStatementFollowsComment)
{
	// With break-blocks and delete-empty-lines this java
	// statement duplicated the "threadPanel, flipPanel);" line.
	// It causes an assert exception in debug configuration.
	char textIn[] =
	    "\nprivate void createWindow()\n"
	    "{\n"
	    "    flipPanel = new JPanel();\n"
	    "    {\n"
	    "        // do stuff\n"
	    "    }\n"
	    "\n"
	    "    /* JSplitPane */ mainPanel = new JSplitPane(VERTICAL_SPLIT,\n"
	    "            threadPanel, flipPanel);\n"
	    "\n"
	    "}";
	char text[] =
	    "\nprivate void createWindow()\n"
	    "{\n"
	    "    flipPanel = new JPanel();\n"
	    "    {\n"
	    "        // do stuff\n"
	    "    }\n"
	    "    /* JSplitPane */ mainPanel = new JSplitPane(VERTICAL_SPLIT,\n"
	    "            threadPanel, flipPanel);\n"
	    "}";
	char options[] = "break-blocks, delete-empty-lines, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, SharpQuestionMarkOperator)
{
	// With vs2010 this test caused a "string subscript out of range" debug assertion.
	// With a C# file the ? must be at the end of the line and pad-oper must be used.
	char text[] =
	    "\npublic string LocationName {\n"
	    "    get {\n"
	    "        return ValidForDeployment ?\n"
	    "               fileCopier.FriendlyLocation :\n"
	    "               GetString (\"Not set\");\n"
	    "    }\n"
	    "}";
	char options[] = "pad-oper, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, CommentEnclosesNoIndentLineComment)
{
	// With vs2010 this test caused a "string subscript out of range" debug assertion.
	// With vs2008 this test caused a null to be placed in column 5 of the empty line.
	// must have tab indent for comment
	// must have non-indent line comment
	// must have a line with indent less than comment start indent
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "	/*\n"
	    "//          no-indent line comment\n"
	    "\n"
	    "	*/\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    /*\n"
	    "    //          no-indent line comment\n"
	    "\n"
	    "    */\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, CheckSumError)
// Test with --break-blocks and --delete-empty-lines and missing closing brace
// Caused a checksum assert failure. This must be run in debug configuration.
// This test is also included in AStyleTestCon for the console build.
{
	char text[] =
	    // this file is missing a closing brace
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isBar)\n"
	    "        fooBar1();\n"
	    "\n"
	    "    fooBar2();";
	char options[] = "break-blocks, delete-empty-lines";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, CloseingBrace_FollowsEndComment)
{
	// A closing brace following a end comment
	// caused the previous line to be deleted.
	// In version 2.01 it caused an assert failure
	// with the checksum.
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (foo1) {\n"
	    "/*      closing brace following comment end\n"
	    "        this line should not be deleted\n"
	    "*/  }\n"
	    "\n"
	    "    if (foo2) {\n"
	    "/*      this line should not be deleted\n"
	    "*/}\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (foo1) {\n"
	    "        /*      closing brace following comment end\n"
	    "                this line should not be deleted\n"
	    "        */\n"
	    "    }\n"
	    "\n"
	    "    if (foo2) {\n"
	    "        /*      this line should not be deleted\n"
	    "        */\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, UnpadParens_ConvertTabs)
{
	// Unpad parens with convert tabs and a paren ending the line
	// caused a "string subscript out of range" with VS2010
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if(isFoo)\n"
	    "        Bar(\n"
	    "            foo + 1);\n"
	    "}";
	char options[] = "unpad-paren, convert-tabs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, DeleteEmptyLines_BreakBlocks)
{
	// a missing closing brace with delete-empty-lines and break-blocks
	// should not cause an assert error on the call to sourceIterator->peekNextLine()
	// in the function ASFormatter::commentAndHeaderFollows()
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar()\n"
	    "    {\n"
	    "\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar()\n"
	    "    {\n"
	    "    }";      // no end-of-line will be output
	char options[] = "delete-empty-lines, break-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, BreakBlocks_DeleteEmptyLines_Comment)
{
	// the following comment should not abort or duplicate code in the output
	// both break-blocks and delete-empty-lines must be used
	// problem is the beginning comments in the peekNextText() function
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "\n"
	    "/*//BEGIN debug\n"
	    "    kdDebug() << endl << endl;\n"
	    "//END debug*/\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "    /*//BEGIN debug\n"
	    "        kdDebug() << endl << endl;\n"
	    "    //END debug*/\n"
	    "}\n";
	char options[] = "break-blocks, delete-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, SharpLambdaOperatorIndent)
{
	// C# => is not an assignment operator
	// following lines should not be aligned on the =>
	char textIn[] =
	    "\npublic static bool Foo()\n"
	    "{\n"
	    "    return @class.Attributes(\n"
	    "               att =>\n"
	    "                    att.AttributeType() &&\n"
	    "                    att.PositionalArg == 2 &&\n"
	    "                    String.Equals(\"System\")\n"
	    "           );\n"
	    "}\n";
	char text[] =
	    "\npublic static bool Foo()\n"
	    "{\n"
	    "    return @class.Attributes(\n"
	    "               att =>\n"
	    "               att.AttributeType() &&\n"
	    "               att.PositionalArg == 2 &&\n"
	    "               String.Equals(\"System\")\n"
	    "           );\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, KeywordsNotHeaders)
{
	// header is not a keyword if part of a definition
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    ADD_KEYWORD(return, TK_RETURN);\n"
	    "    ADD_KEYWORD(switch, TK_SWITCH);\n"
	    "    ADD_KEYWORD(case,   TK_CASE);\n"
	    "    ADD_KEYWORD(default,TK_DEFAULT);\n"
	    "}\n";
	char options[] = "pad-header";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, TwoGreaterSymblolsClosingTemplate)
{
	// two >> symbols closing a template
	char text[] =
	    "\npublic Foo<KeyValuePair<string, string>> SpecialTypes {\n"
	    "    get {\n"
	    "        return typeConversionTable;\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, Col1ElseWithPreceedingBrace)
{
	// else in col 1 with preceding brace tests a seldom used branch
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if(isFoo)\n"
	    "    {\n"
	    "        bar1();\n"
	    "    }\n"
	    "else    // comment\n"
	    "        bar2();\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if(isFoo)\n"
	    "    {\n"
	    "        bar1();\n"
	    "    }\n"
	    "    else    // comment\n"
	    "        bar2();\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, TryCatchInHeader)
{
	// try-catch within a header
	// header must be restored from lastTempStack in ASBeautifier
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (foo1)\n"
	    "        bar1;\n"
	    "    else\n"
	    "        try {\n"
	    "            bar();\n"
	    "        } catch (int e) {\n"
	    "            cerr << \"error\" << endl;\n"
	    "        }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, TryCatchFinallyInHeader)
{
	// try-catch within a header
	// header must be restored from lastTempStack in ASBeautifier
	char text[] =
	    "\nprivate void foo()\n"
	    "{\n"
	    "    if (foo1)\n"
	    "        bar1;\n"
	    "    else\n"
	    "        try {\n"
	    "            bar();\n"
	    "        } catch (int e) {\n"
	    "            Console.WriteLine(\"error\");\n"
	    "        } finally (int e) {\n"
	    "            closefile();\n"
	    "        }\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, DoWhileInHeader)
{
	// do-while within a header
	// header must be restored from lastTempStack in ASBeautifier
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (foo1)\n"
	    "        bar1;\n"
	    "    else\n"
	    "        do {\n"
	    "            bar();\n"
	    "        } while (int x < 9);\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, TemplateASBeautifier)
{
	// template on multiple lines should be recognized by ASBeautifier
	// template within a template should be recognized by ASBeautifier
	char text[] =
	    "\ntemplate<typename T, template<typename E,\n"
	    "                              typename Allocator = allocator<E> >\n"
	    "         class Container = vector >\n"
	    "class Foo\n"
	    "{\n"
	    "};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, ExtraClosingBraces)
{
	// should not abort with extra closing braces
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        int bar = 1;\n"
	    "    }\n"
	    "}\n"
	    "}\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, ExtraClosingParens)
{
	// should not abort with extra closing parens
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo))))\n"
	    "    {\n"
	    "        bar()));\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, ExtraClosingSquareBrackets)
{
	// should not abort with extra closing square brackets
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo))))\n"
	    "    {\n"
	    "        fooBar = bar[2]]];\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, DefinitionsNotHeaders)
{
	// definitions are not headers
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    ADD_KEYWORD ( if, TK_IF );\n"
	    "    ADD_KEYWORD ( while, TK_WHILE );\n"
	    "    ADD_KEYWORD ( else );\n"
	    "    ADD_KEYWORD ( for );\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, SharpPeekNextTextMultiLineComment)
{
	// test C# peekNextText() with multi-line comment before the text
	char text[] =
	    "\npublic interface FooInterface {\n"
	    "    int FooGet {\n"
	    "        /* comment\n"
	    "           comment */\n"
	    "        get;\n"
	    "        set;\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, SharpNotPotentialHeader)
{
	// test C# isNextWordSharpNonParenHeader() for !isCharPotentialHeader()
	char text[] =
	    "\nprivate void foo()\n"
	    "{\n"
	    "    string[] lines = text.Split(new char[] {'.'});\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, EmptyLineComment)
{
	// test recognition of an empty line comment
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    //\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V201, ColZeroPointerOrReference)
{
	// test pointer or reference in column zero
	char textIn[] =
	    "\nvoid foo(char *foo1, char\n"
	    "*foo2, char *foo3)\n"
	    "{\n"
	    "    bar();\n"
	    "}\n"
	    "\n"
	    "void foo(char &foo1, char\n"
	    "&foo2, char &foo3)\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char text[] =
	    "\nvoid foo(char *foo1, char\n"
	    "         *foo2, char *foo3)\n"
	    "{\n"
	    "    bar();\n"
	    "}\n"
	    "\n"
	    "void foo(char &foo1, char\n"
	    "         &foo2, char &foo3)\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle version 1.24 TEST functions
//----------------------------------------------------------------------------

TEST(BugFix_V124, AddBracesRunInNestedIfStatements)
{
	// add on line braces to nested "if" statements
	// with keep one line braces
	// should not break the statement (a variable was not reset)
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isBar1)\n"
	    "        if (isBar2) return true;\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (isBar1)\n"
	    "        if (isBar2) { return true; }\n"
	    "}\n";
	char options[] = "add-braces, style=run-in, keep-one-line-blocks";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, ClassRunInComment)
{
	// handle special case of run-in comment in a class statement
	char text[] =
	    "\nclass Foo\n"
	    "{   /*enum ResolutionFlags {\n"
	    "           NoFlag = 0,\n"
	    "           HadTypedef = 1,\n"
	    "           HadAlias = 2\n"
	    "         };*/\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, ClassIndentRunInComment)
{
	// handle special case of run-in comment in an indented class statement
	char text[] =
	    "\nclass Foo\n"
	    "{   /*enum ResolutionFlags {\n"
	    "           NoFlag = 0,\n"
	    "           HadTypedef = 1,\n"
	    "           HadAlias = 2\n"
	    "         };*/\n"
	    "}\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, AppendAttachedBraceInsideCommentsLineBreak)
{
	// should not insert an empty line after appending a brace inside comments
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   switch(req) {\n"
	    "    case REQ_if:   // groff(7) \"IF\"\n"
	    "    {   /* .if c anything\n"
	    "         * .if N anything\n"
	    "         */\n"
	    "        c = c + j;\n"
	    "        break;\n"
	    "    }\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    switch(req) {\n"
	    "    case REQ_if: { // groff(7) \"IF\"\n"
	    "        /* .if c anything\n"
	    "         * .if N anything\n"
	    "         */\n"
	    "        c = c + j;\n"
	    "        break;\n"
	    "    }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, ElseAttachedToLineComment)
{
	// else should not be attached to a line comment
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if ( x == 'G')\n"
	    "        y = 1;\n"
	    "    else\n"
	    "//  if ( x == 'W')\n"
	    "//      y= 3;\n"
	    "//  else\n"
	    "        if ( x == 'H')\n"
	    "            y = 4;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BreakOneLineBlocks_Comment1)
{
	// comment should be moved to the previous line
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    { bar(); } // comment\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();    // comment\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BreakOneLineBlocks_Comment2)
{
	// comment should be moved to the previous line
	// option keep-one-line-statements is used
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    { bar(); } // comment\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();    // comment\n"
	    "    }\n"
	    "}\n";
	char options[] = "keep-one-line-statements";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, SharpDelegate)
{
	// sharp 'delegate' should be recognized as a keyword
	// the Linux braces should be attached
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    delegate {\n"
	    "        if (isFoo)\n"
	    "        {\n"
	    "            bar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    delegate {\n"
	    "        if (isFoo) {\n"
	    "            bar();\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, SharpAccessors)
{
	// get is preceded by []
	char text[] =
	    "\npublic static MyApplication Application\n"
	    "{\n"
	    "    [DebuggerStepThrough]\n"
	    "    get\n"
	    "    {\n"
	    "        if (isBar)\n"
	    "            bar();\n"
	    "        return application;\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, SharpNonParenHeader_UnEXPECT_TRUEed)
{
	// 'unEXPECT_TRUEed' should be recognized as a header, not an array
	char text[] =
	    "\npublic override void foo()\n"
	    "{\n"
	    "    unEXPECT_TRUEed {\n"
	    "        if (isBar)\n"
	    "            bar += 1;\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, SharpNonParenHeader_Delegate)
{
	// 'delegate' should be recognized as a header, not an array
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    int fooBar = delegate {\n"
	    "        if (isBar1) {\n"
	    "            bar = 1;\n"
	    "        } else if (isBar2) {\n"
	    "            bar = 2;\n"
	    "        } else if (isBar3) {\n"
	    "            bar = 3;\n"
	    "        }\n"
	    "    };\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, PadCommentBeforeTab)
{
	// space padding the brace should NOT pad a comment
	//     when the comment is preceded by a tab
	//     but should delete a space when preceded spaces
	char textIn[] =
	    "\nvoid foo() {\n"
	    "    if (isBar1){	// comment\n"
	    "        bar1();\n"
	    "    }\n"
	    "    if (isBar2){   // comment\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isBar1) {	// comment\n"
	    "        bar1();\n"
	    "    }\n"
	    "    if (isBar2) {  // comment\n"
	    "        bar2();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesBreak_PadParen)
{
	// break attached braces with pad-paren
	// comments should be moved with one padded space
	char textIn[] =
	    "\nvoid foo() { // comment0\n"
	    "    if ((isFoo())) { // comment1\n"
	    "        bar1();\n"
	    "        bar2(fooBar); // comment2\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2(){// comment0\n"
	    "    if ((isFoo())){// comment1\n"
	    "        bar1();\n"
	    "        bar2(fooBar);// comment2\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()   // comment0\n"
	    "{\n"
	    "    if ( ( isFoo() ) ) // comment1\n"
	    "    {\n"
	    "        bar1();\n"
	    "        bar2 ( fooBar ); // comment2\n"
	    "    }\n"
	    "}\n"
	    "\n"
	    "void foo2() // comment0\n"
	    "{\n"
	    "    if ( ( isFoo() ) ) // comment1\n"
	    "    {\n"
	    "        bar1();\n"
	    "        bar2 ( fooBar ); // comment2\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=allman, pad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesAttach_CommentsMisc1)
{
	// attach brace inside a line end comment
	// when multi-line comments follow a run-in brace
	char textIn[] =
	    "\nvoid foo2(bool isFoo) /* comment0 */\n"
	    "{   /* comment1\n"
	    "     *\n"
	    "     */\n"
	    "    if(isFoo) /* comment2 */\n"
	    "    {   /* comment3\n"
	    "         *\n"
	    "         */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo2(bool isFoo) { /* comment0 */\n"
	    "    /* comment1\n"
	    "     *\n"
	    "     */\n"
	    "    if(isFoo) { /* comment2 */\n"
	    "        /* comment3\n"
	    "         *\n"
	    "         */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesAttach_CommentMisc2)
{
	// do NOT attach brace inside a line end comment
	// when two comments are on the line
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isBar())   /* comment0 */ // comment0line\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesAttach_CommentMisc3)
{
	// when a brace is NOT attached
	// following run-in comments should be broken and correctly formatted
	char textIn[] =
	    "\nvoid foo() {\n"
	    "    if (isBar())   /* comment0 */ // comment0line\n"
	    "    {   /*\n"
	    "         * comment1\n"
	    "         */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isBar())   /* comment0 */ // comment0line\n"
	    "    {\n"
	    "        /*\n"
	    "         * comment1\n"
	    "         */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesAttach_CommentMisc4)
{
	// attached braces with following comments
	// the second comment should be correctly formatted
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        // comment1\n"
	    "        {\n"
	    "            bar1();\n"
	    "        }\n"
	    "        /*else\n"
	    "        {\n"
	    "            bar2();\n"
	    "        }*/\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo) {\n"
	    "        // comment1\n"
	    "        {\n"
	    "            bar1();\n"
	    "        }\n"
	    "        /*else\n"
	    "        {\n"
	    "            bar2();\n"
	    "        }*/\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_Tabs)
{
	// test run-in braces with tab indents
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    if (isFoo())\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo()\n"
	    "{	if (isFoo())\n"
	    "	{	bar();\n"
	    "	}\n"
	    "}\n";
	char options[] = "style=run-in, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_Array1)
{
	// test run-in braces with single line array
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    wxChar name[MAX_PATH] = {0};\n"
	    "    bar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo()\n"
	    "{   wxChar name[MAX_PATH] = {0};\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_Array2)
{
	// test run-in braces with structs and arrays
	char textIn[] =
	    "\nstruct runinClass2\n"
	    "{\n"
	    "    bool bar;\n"
	    "};\n"
	    "\n"
	    "const char *contributors[] =\n"
	    "{\n"
	    "    \"Bugs\",\n"
	    "    \"Daffy\",\n"
	    "};\n";
	char text[] =
	    "\nstruct runinClass2\n"
	    "{   bool bar;\n"
	    "};\n"
	    "\n"
	    "const char *contributors[] =\n"
	    "{   \"Bugs\",\n"
	    "    \"Daffy\",\n"
	    "};\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_Spaces1)
{
	// test run-in braces with extra spaces
	// extra spaces should be deleted
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{     if (isFoo())\n"
	    "      {     bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo()\n"
	    "{   if (isFoo())\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_Spaces2)
{
	// test multiple run-in braces runs
	// extra spaces should not be added on subsequent runs
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    if (isFoo())\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo()\n"
	    "{   if (isFoo())\n"
	    "    {   bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOne = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	char* textOut = AStyleMain(textOne, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOne;
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_Preprocessor)
{
	// test run-in braces with preprocessor
	// preprocessor should NOT be attached
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "#ifdef xxx\n"
	    "    bar1();\n"
	    "#else\n"
	    "    bar2();\n"
	    "#endif\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "#ifdef xxx\n"
	    "    bar1();\n"
	    "#else\n"
	    "    bar2();\n"
	    "#endif\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_EmptyLine)
{
	// test run-in braces with following empty line
	// empty line should NOT be deleted
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "\n"
	    "    if (isFoo())\n"
	    "        bar();\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_Comment1)
{
	// test run-in braces with following comment
	// second comment should NOT be attached to the first
	char textIn[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    // comment1\n"
	    "    // comment2\n"
	    "    if (isFoo())\n"
	    "        bar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo()\n"
	    "{   // comment1\n"
	    "    // comment2\n"
	    "    if (isFoo())\n"
	    "        bar();\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_Comment2)
{
	// test run-in braces with following comment in column 1
	// the comment should NOT be attached
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "// comment1 does not attach\n"
	    "// comment2\n"
	    "    if (isFoo())\n"
	    "        bar();\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_Comment3)
{
	// test run-in braces with following comment
	// the comment should NOT be attached to the previous line
	char text[] =
	    "\nvoid foo()\n"
	    "{   foo1();\n"
	    "    /* comment */\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_Comment4)
{
	// test run-in braces with following comment
	// the comment should NOT be attached to the previous line
	char text[] =
	    "\nvoid foo()\n"
	    "{   // comment1\n"
	    "    /*comment2*/\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_Comment5)
{
	// test run-in braces with following comment
	// the comment on unattached lines should be correctly indented
	char textIn[] =
	    "\nnamespace fooName\n"
	    "{\n"
	    "    /**\n"
	    "     * comment1\n"
	    "     */\n"
	    "    class fooClass\n"
	    "    {\n"
	    "        /**\n"
	    "         * comment1\n"
	    "         */\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nnamespace fooName\n"
	    "{\n"
	    "/**\n"
	    " * comment1\n"
	    " */\n"
	    "class fooClass\n"
	    "{   /**\n"
	    "     * comment1\n"
	    "     */\n"
	    "}\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_Comment6)
{
	// test run-in braces with following comment
	// the comment on unattached lines should be correctly indented
	char textIn[] =
	    "\nnamespace fooName\n"
	    "{\n"
	    "    /**\n"
	    "     * comment1\n"
	    "     */\n"
	    "    class fooClass\n"
	    "    {\n"
	    "        /**\n"
	    "         * comment1\n"
	    "         */\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nnamespace fooName\n"
	    "{\n"
	    "    /**\n"
	    "     * comment1\n"
	    "     */\n"
	    "    class fooClass\n"
	    "    {   /**\n"
	    "         * comment1\n"
	    "         */\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in, indent-namespaces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_Comment7)
{
	// test run-in braces with comment following line comment
	// the comment should NOT be attached to the previous line
	char textIn[] =
	    "\nvoid foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        // comment\n"
	    "/* FIXME comment in column 1 */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   // comment\n"
	    "        /* FIXME comment in column 1 */\n"
	    "        bar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_BreakAllBlocks1)
{
	// test run-in braces with break all blocks
	// the blocks should be correctly broken
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar1();\n"
	    "    if (isBar)  // comment\n"
	    "    {\n"
	    "        bar2();\n"
	    "        return;\n"
	    "    }\n"
	    "    else\n"
	    "    {\n"
	    "        bar3();\n"
	    "    }\n"
	    "    bar4();\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   bar1();\n"
	    "\n"
	    "    if (isBar)  // comment\n"
	    "    {   bar2();\n"
	    "        return;\n"
	    "    }\n"
	    "\n"
	    "    else\n"
	    "    {   bar3();\n"
	    "    }\n"
	    "\n"
	    "    bar4();\n"
	    "}\n";
	char options[] = "style=run-in, break-blocks=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_BreakAllBlocks2)
{
	// test run-in braces with break all blocks and delete empty lines
	// and comments separated by an empty line
	// the empty line should NOT be deleted
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    // comment1\n"
	    "\n"
	    "    // comment2\n"
	    "    if (isFoo)\n"
	    "        bar();\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   // comment1\n"
	    "\n"
	    "    // comment2\n"
	    "    if (isFoo)\n"
	    "        bar();\n"
	    "}\n";
	char options[] = "style=run-in, break-blocks=all, delete-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_UnpadParen1)
{
	// test run-in braces with unpad parens
	// the indent should NOT be removed
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if ( isBar )\n"
	    "    {\n"
	    "        ( *_err ) << endl; // comment1\n"
	    "        ( *_err ) << arg;  // comment2\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   if(isBar)\n"
	    "    {   (*_err) << endl;   // comment1\n"
	    "        (*_err) << arg;    // comment2\n"
	    "    }\n"
	    "}\n";
	char options[] = ", style=run-in, unpad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_UnpadParen2)
{
	// test run-in braces with unpad parens and pad-parens
	// the indent should NOT be removed
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isBar)\n"
	    "    {\n"
	    "        (*_err) << endl; // comment1\n"
	    "        (*_err) << arg;  // comment2\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   if ( isBar )\n"
	    "    {   ( *_err ) << endl; // comment1\n"
	    "        ( *_err ) << arg; // comment2\n"
	    "    }\n"
	    "}\n";
	char options[] = ", style=run-in, unpad-paren, pad-paren";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_UnpadParen3)
{
	// test run-in braces with unpad parens and pad-parens
	//	and tab indents
	// the indent should NOT be removed
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isBar)\n"
	    "    {\n"
	    "        (*_err) << endl; // comment1\n"
	    "        (*_err) << arg;  // comment2\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{	if ( isBar )\n"
	    "	{	( *_err ) << endl; // comment1\n"
	    "		( *_err ) << arg; // comment2\n"
	    "	}\n"
	    "}\n";
	char options[] = ", style=run-in, unpad-paren, pad-paren, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_SingleLineBlock1)
{
	// test run-in braces with single line block
	char textIn[] =
	    "\nvoid foo()\n"
	    "{ bar1(); bar2() }\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   bar1();\n"
	    "    bar2()\n"
	    "}\n";
	char options[] = ", style=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V124, BracesRunIn_SingleLineBlock2)
{
	// test run-in braces with single line block
	char text[] =
	    "\nvoid foo()\n"
	    "{ bar1(); bar2() }\n";
	char options[] = ", style=run-in, keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle version 1.23 TEST functions
//----------------------------------------------------------------------------

TEST(BugFix_V123, ExternIndent)
{
	// no extra indent when extern is used
	char text[] =
	    "\nextern void foo (bool bar2,\n"
	    "                 bool bar2);\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, StructBitIndent)
{
	// do not break line when struct bit declaration is used
	// lines following struct should have correct indent
	char text[] =
	    "\nstruct A {\n"
	    "    int a:1;\n"
	    "};\n"
	    "\n"
	    "struct X {\n"
	    "    field x : 1;\n"
	    "    field y : 2;\n"
	    "};\n"
	    "\n"
	    "typedef union _USB_DEVICE_STATUS\n"
	    "{\n"
	    "    byte _byte;\n"
	    "    struct\n"
	    "    {\n"
	    "        unsigned RemoteWakeup:1;\n"
	    "        unsigned ctrl_trf_mem:1;\n"
	    "    };\n"
	    "} USB_DEVICE_STATUS;\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, ClassBitIndent)
{
	// do not break line when struct bit declaration is used
	// lines following class should have correct indent
	char text[] =
	    "\nclass MainWindow\n"
	    "{\n"
	    "public:\n"
	    "    bool inDebugMode;\n"
	    "    uint guiStuffVisible : 1;\n"
	    "    uint editorsReadOnly : 1;\n"
	    "    uint savePluginPaths : 1;\n"
	    "    bool shStartDialog;\n"
	    "};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, StructIndent)
{
	// no extra indent when struct declaration is used
	char text[] =
	    "\nstruct foo* bar (void) {\n"
	    "}\n"
	    "\n"
	    "struct foo* bar\n"
	    "(void)\n"
	    "{\n"
	    "}\n"
	    "\n"
	    "struct axt *chainToAxt(struct chain *chain,\n"
	    "                       struct chain chain,\n"
	    "                       struct dnaSeq *qSeq)\n"
	    "/* Convert a chain to a list of axt's. This will break\n"
	    " * where there is a double-sided gap in chain.\n"
	    " */\n"
	    "{\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, PreprocessorErrorStatement)
{
	// the ' in mustn't causes end comment to separate
	// and continuation comments to misalign
	// when pad-oper is used.
	// it thinks the ' is an opening quote
	char text[] =
	    "\n#ifdef SLIM_CONFIG_USE_PLATE\n"
	    "#error You mustn't compile this file.\n"
	    "#  error You mustn't compile this file.\n"
	    "#endif\n"
	    "\n"
	    "/* @param\n"
	    " * callee has in_region's ownership.\n"
	    " */\n";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, SharpAccessorsWithElse)
{
	// test indent of getters and setters
	// #else causes a problem
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "#if FRAMEWORK_VER_2x\n"
	    "#else\n"
	    "#endif\n"
	    "\n"
	    "    private bool foo;\n"
	    "\n"
	    "    public int foo\n"
	    "    {\n"
	    "        get\n"
	    "        {\n"
	    "            return foo;\n"
	    "        }\n"
	    "        set\n"
	    "        {\n"
	    "            foo = 1;\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, BreakElseIfWithCatch)
{
	// break-elseifs should not break C# catch statement with parens
	char text[] =
	    "\nclass Test\n"
	    "{\n"
	    "    int foo()\n"
	    "    {\n"
	    "        try\n"
	    "        {\n"
	    "            bar();\n"
	    "        }\n"
	    "        catch (Exception e)\n"
	    "        {\n"
	    "            Console.WriteLine(e.message);\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "break-elseifs, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, WhitesmithInComment)
{
	// test whitesmith style with braces in comment
	// should not indent braces in comments
	char text[] =
	    "\nvoid foo()\n"
	    "    {\n"
	    "    /*if (client == NULL)\n"
	    "    {\n"
	    "        int found = -1;\n"
	    "    }*/\n"
	    "    }\n";
	char options[] = "style=whitesmith";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, BreakBlocksWithEmptyLine)
{
	// test break all blocks with an empty line following comments
	// an error in peekNextLine caused a line break before ++lineOpeningBlocksNum;
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    for (i = 0; i < 10; i++)\n"
	    "    {\n"
	    "        ++lineOpeningBlocksNum;\n"
	    "//        if (isInClassHeader)\n"
	    "//        isInClassHeader = false;\n"
	    "\n"
	    "        if (isInClassHeaderTab)\n"
	    "            isInClassHeaderTab = false;\n"
	    "    }\n"
	    "}\n";
	char options[] = "break-blocks=all";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, UnmatchedBracesInPreprocessor1)
{
	// unmatched braces in preprocessor directives
	// should not cause formatting problems on following lines
	char text[] =
	    "\n//-----------\n"
	    "namespace fooName\n"
	    "{\n"
	    "\n"
	    "#ifdef fooBar\n"
	    "void foo1()\n"
	    "{\n"
	    "#else\n"
	    "void foo1()\n"
	    "{\n"
	    "#endif\n"
	    "}\n"
	    "\n"
	    "void foo2()\n"
	    "{\n"
	    "}\n"
	    "\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, UnmatchedBracesInPreprocessor2)
{
	// unmatched braces in preprocessor directives
	// should not cause formatting problems on following lines
	char text[] =
	    "\nnamespace fooName\n"
	    "{\n"
	    "\n"
	    "#ifdef fooBar\n"
	    "void foo1()\n"
	    "{\n"
	    "#else\n"
	    "void foo1()\n"
	    "{\n"
	    "#endif\n"
	    "}\n"
	    "\n"
	    "void foo2()\n"
	    "{\n"
	    "}\n"
	    "\n"
	    "}\n";
	char options[] = "delete-empty-lines";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, DeleteLinesAfterPreprocessor)
{
	// empty lines after a preprocessor
	// should NOT be attached to the preprocessor
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "#if 0\n"
	    "\n"
	    "    {\n"
	    "        bar0 = 0;\n"
	    "    }\n"
	    "#endif\n"
	    "\n"
	    "\n"
	    "    {\n"
	    "        bar1 = 1;\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "#if 0\n"
	    "    {\n"
	    "        bar0 = 0;\n"
	    "    }\n"
	    "#endif\n"
	    "    {\n"
	    "        bar1 = 1;\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=kr, delete-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, CSharp_NullableTypes)
{
	// C# nullable types should not separate the ? from the variable
	// when pad-oper is used
	char text[] =
	    "\nclass MainClass\n"
	    "{\n"
	    "    static void Main()\n"
	    "    {\n"
	    "        // nullable types\n"
	    "        // any type may be used as a nullable type\n"
	    "        int? i = 10;\n"
	    "        double? d1 = 3.14;\n"
	    "        bool? flag = null;\n"
	    "        char? letter = 'a';\n"
	    "        int?[] arr = new int?[10];\n"
	    "    }\n"
	    "}\n";
	char options[] = "pad-oper, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, CSharp_QuestionQuestionOperator)
{
	// C# ?? operator should not separate when pad-oper is used
	char text[] =
	    "\nclass MainClass\n"
	    "{\n"
	    "    static void Main()\n"
	    "    {\n"
	    "        // ?? operator example.\n"
	    "        int? x = null;\n"
	    "        // y = x, unless x is null, in which case y = -1.\n"
	    "        int y = x ?? -1;\n"
	    "        int i = GetNullableInt() ?? defaultInt(int);\n"
	    "        string s = GetStringValue();\n"
	    "        Console.WriteLine(s ?? \"Unspecified\");\n"
	    "    }\n"
	    "}\n";
	char options[] = "pad-oper, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, CSharp_NonGenericDefault)
{
	// C# non-generic default statement should not un-indent the line
	char text[] =
	    "\nclass MainClass\n"
	    "{\n"
	    "    static void Main()\n"
	    "    {\n"
	    "        int i = GetNullableInt() ?? default(int);\n"
	    "    }\n"
	    "}\n";
	char options[] = "pad-oper, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, BreakBlocksWithPreprocessor)
{
	// empty lines should not be inserted after the #if
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if ( isFoo )\n"
	    "    {\n"
	    "        bar1();\n"
	    "    }\n"
	    "\n"
	    "#if 0\n"
	    "    bar2();\n"
	    "    bar3();\n"
	    "    bar4();\n"
	    "    bar5();\n"
	    "    bar6();\n"
	    "#endif\n"
	    "}\n";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, CSharp_BreakBlocks_KeepOneLineBlocks)
{
	// C# do NOT break before a block with keep one line blocks
	char text[] =
	    "\npublic class FooClass\n"
	    "{\n"
	    "    public bool Foo { get { return Count > 0; } }\n"
	    "}\n";
	char options[] = "break-blocks, keep-one-line-blocks, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, EnumDefinitionPadding)
{
	// enum should space pad before the definition
	// NOTE: the enum is an array type brace
	char textIn[] =
	    "\n// should space pad after the closing brace\n"
	    "typedef enum tagSQObjectType{\n"
	    "    OT_INTEGER = (_RT_INTEGER),\n"
	    "    OT_BOOL =    (_RT_BOOL),\n"
	    "}SQObjectType;\n"
	    "\n"
	    "// should NOT space pad before the closing semi-colon\n"
	    "typedef enum tagSQObjectType{\n"
	    "    OT_INTEGER = (_RT_INTEGER),\n"
	    "    OT_BOOL =    (_RT_BOOL),\n"
	    "};";
	char text[] =
	    "\n// should space pad after the closing brace\n"
	    "typedef enum tagSQObjectType {\n"
	    "    OT_INTEGER = (_RT_INTEGER),\n"
	    "    OT_BOOL =    (_RT_BOOL),\n"
	    "} SQObjectType;\n"
	    "\n"
	    "// should NOT space pad before the closing semi-colon\n"
	    "typedef enum tagSQObjectType {\n"
	    "    OT_INTEGER = (_RT_INTEGER),\n"
	    "    OT_BOOL =    (_RT_BOOL),\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, UnionDefinitionPadding)
{
	// union should space pad before the definition
	char textIn[] =
	    "\n// should space pad after the braces\n"
	    "typedef union tagSQObjectValue{\n"
	    "    struct SQTable *pTable;\n"
	    "    struct SQArray *pArray;\n"
	    "}SQObjectValue;\n"
	    "\n"
	    "// should NOT space pad before a semi-colon\n"
	    "typedef union tagSQObjectValue{\n"
	    "    struct SQTable *pTable;\n"
	    "    struct SQArray *pArray;\n"
	    "};";
	char text[] =
	    "\n// should space pad after the braces\n"
	    "typedef union tagSQObjectValue {\n"
	    "    struct SQTable *pTable;\n"
	    "    struct SQArray *pArray;\n"
	    "} SQObjectValue;\n"
	    "\n"
	    "// should NOT space pad before a semi-colon\n"
	    "typedef union tagSQObjectValue {\n"
	    "    struct SQTable *pTable;\n"
	    "    struct SQArray *pArray;\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BugFix_V123, StructDefinitionPadding)
{
	// struct should space pad before the definition
	char textIn[] =
	    "\n// should space pad after the braces\n"
	    "typedef struct tagSQStackInfos{\n"
	    "    const SQChar* funcname;\n"
	    "    const SQChar* source;\n"
	    "}SQStackInfos;\n"
	    "\n"
	    "// should NOT space pad before a semi-colon\n"
	    "typedef struct tagSQStackInfos{\n"
	    "    const SQChar* funcname;\n"
	    "    const SQChar* source;\n"
	    "};";
	char text[] =
	    "\n// should space pad after the braces\n"
	    "typedef struct tagSQStackInfos {\n"
	    "    const SQChar* funcname;\n"
	    "    const SQChar* source;\n"
	    "} SQStackInfos;\n"
	    "\n"
	    "// should NOT space pad before a semi-colon\n"
	    "typedef struct tagSQStackInfos {\n"
	    "    const SQChar* funcname;\n"
	    "    const SQChar* source;\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------

}  // namespace
