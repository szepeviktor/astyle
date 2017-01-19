// AStyleTest_Other.cpp
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
// AStyle indent-off tag
//----------------------------------------------------------------------------

TEST(DisableFormatting, IndentOffTagLineComments)
{
	// indent-off tags with line comments
	// should NOT be unindented
	// the unpadded operators should NOT be padded
	char textIn[] =
	    "\nvoid SetSystemInfo()\n"
	    "{\n"
	    "m_localeText->SetLabel(localeText);\n"
	    "            // *INDENT-OFF* - should not pad-oper\n"
	    "            wxString localeData=\n"
	    "                        osDesc + lineend+\n"
	    "                        langDesc + lineend +\n"
	    "                        bits + lineend;\n"
	    "            // *INDENT-ON* - end should not pad-oper\n"
	    "m_localeData->SetLabel(localeData);\n"
	    "}";
	char text[] =
	    "\nvoid SetSystemInfo()\n"
	    "{\n"
	    "    m_localeText->SetLabel(localeText);\n"
	    "            // *INDENT-OFF* - should not pad-oper\n"
	    "            wxString localeData=\n"
	    "                        osDesc + lineend+\n"
	    "                        langDesc + lineend +\n"
	    "                        bits + lineend;\n"
	    "            // *INDENT-ON* - end should not pad-oper\n"
	    "    m_localeData->SetLabel(localeData);\n"
	    "}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(DisableFormatting, IndentOffTagComments)
{
	// indent-off tags with comments
	// should NOT be unindented
	// the unpadded operators should NOT be padded
	char textIn[] =
	    "\nvoid SetSystemInfo()\n"
	    "{\n"
	    "m_localeText->SetLabel(localeText);\n"
	    "            /*INDENT-OFF* - should not pad-oper*/\n"
	    "            wxString localeData=\n"
	    "                        osDesc + lineend+\n"
	    "                        langDesc + lineend +\n"
	    "                        bits + lineend;\n"
	    "            /*INDENT-ON*/\n"
	    "m_localeData->SetLabel(localeData);\n"
	    "}";
	char text[] =
	    "\nvoid SetSystemInfo()\n"
	    "{\n"
	    "    m_localeText->SetLabel(localeText);\n"
	    "            /*INDENT-OFF* - should not pad-oper*/\n"
	    "            wxString localeData=\n"
	    "                        osDesc + lineend+\n"
	    "                        langDesc + lineend +\n"
	    "                        bits + lineend;\n"
	    "            /*INDENT-ON*/\n"
	    "    m_localeData->SetLabel(localeData);\n"
	    "}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(DisableFormatting, IndentOffTagCommentsSans)
{
	// indent-off tags with invalid comments that are NOT single line
	// indent-off tags are ignored and the text is unindented
	// the unpadded operators should be padded
	char textIn[] =
	    "\nvoid SetSystemInfo()\n"
	    "{\n"
	    "    m_localeText->SetLabel(localeText);\n"
	    "            /* *INDENT-OFF*\n"
	    "            */\n"
	    "            wxString localeData=\n"
	    "                        osDesc + lineend+\n"
	    "                        langDesc + lineend +\n"
	    "                        bits + lineend;\n"
	    "            /* *INDENT-ON*\n"
	    "            */\n"
	    "    m_localeData->SetLabel(localeData);\n"
	    "}";
	char text[] =
	    "\nvoid SetSystemInfo()\n"
	    "{\n"
	    "    m_localeText->SetLabel(localeText);\n"
	    "    /* *INDENT-OFF*\n"
	    "    */\n"
	    "    wxString localeData =\n"
	    "        osDesc + lineend +\n"
	    "        langDesc + lineend +\n"
	    "        bits + lineend;\n"
	    "    /* *INDENT-ON*\n"
	    "    */\n"
	    "    m_localeData->SetLabel(localeData);\n"
	    "}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(DisableFormatting, IndentOffFirstInFile)
{
	// indent-off tag is the first line in the file
	char text[] =
	    "// *INDENT-OFF*\n"
	    "#ifdef _WIN32\n"
	    "       #define STDCALL __stdcall\n"
	    "#endif\n"
	    "// *INDENT-ON*\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(DisableFormatting, IndentOnLastInFile)
{
	// indent-on tag is the last line in the file with no LF
	char text[] =
	    "\n// *INDENT-OFF*\n"
	    "#ifdef _WIN32\n"
	    "       #define STDCALL __stdcall\n"
	    "#endif\n"
	    "// *INDENT-ON*";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(DisableFormatting, IndentOffArray1)
{
	// indent-off tags with an array
	// should NOT change the indent
	char text[] =
	    "\n// *INDENT-OFF*\n"
	    "const wxCmdLineEntryDesc cmdLineDesc[] =\n"
	    "{\n"
	    "    { wxCMD_LINE_SWITCH, CMD_ENTRY(\"h\"), CMD_ENTRY(\"help\"),\n"
	    "      wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },\n"
	    "    { wxCMD_LINE_SWITCH, CMD_ENTRY(\" ? \"), CMD_ENTRY(\" ? \"),\n"
	    "      wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP }\n"
	    "};\n"
	    "// *INDENT-ON*\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(DisableFormatting, IndentOffArray2)
{
	// indent-off tags with a C# array
	// should NOT change the indent
	char text[] =
	    "\nclass Foo\n"
	    "{\n"
	    "    void testAkAppend_data()\n"
	    "    {\n"
	    "        // *INDENT-OFF*\n"
	    "        updateParts(parts, { { \"Random Data\", 11 },\n"
	    "                             { \"Test Data\", 9 }\n"
	    "        });\n"
	    "        // *INDENT-ON*\n"
	    "    }\n"
	    "};\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(DisableFormatting, IndentPreprocBlock)
{
	// indent-off tags with indent-preproc-block
	// should NOT be indented
	char text[] =
	    "\n// *INDENT-OFF*\n"
	    "#ifdef _WIN32\n"
	    "#define STDCALL __stdcall\n"
	    "#else\n"
	    "#define STDCALL\n"
	    "#endif\n"
	    "// *INDENT-ON*\n";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(DisableFormatting, IndentPreprocBlockPartial)
{
	// indent-off tags with partial indent-preproc-block
	// should NOT be indented after the tag
	char textIn[] =
	    "\n#ifdef _WIN32\n"
	    "#define STDCALL __stdcall\n"
	    "// *INDENT-OFF*\n"
	    "#else\n"
	    "#define STDCALL\n"
	    "#endif\n"
	    "// *INDENT-ON*\n";
	char text[] =
	    "\n#ifdef _WIN32\n"
	    "    #define STDCALL __stdcall\n"
	    "// *INDENT-OFF*\n"
	    "#else\n"
	    "#define STDCALL\n"
	    "#endif\n"
	    "// *INDENT-ON*\n";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(DisableFormatting, IndentPreprocConditional)
{
	// indent-off tags with indent-preproc-cond
	// should NOT be indented
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    // *INDENT-OFF*\n"
	    "#if wxUSE_UNICODE\n"
	    "    m_convertedText = wxString(wideBuff);\n"
	    "#else\n"
	    "    m_convertedText = wxString(buffer);\n"
	    "#endif\n"
	    "    // *INDENT-ON*\n"
	    "}\n";
	char options[] = "indent-preproc-cond";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(DisableFormatting, IndentPreprocDefineLineComments)
{
	// indent-off tags using line comments with indent-preproc-define
	// should NOT be indented
	char textIn[] =
	    "\n// *INDENT-OFF*\n"
	    "#define GTEST_DECLARE_int32_(name) \\\n"
	    "        GTEST_API_ extern ::testing::internal::Int32 GTEST_FLAG(name)\n"
	    "// *INDENT-ON*\n"
	    "#define GTEST_DECLARE_string_(name) \\\n"
	    "        GTEST_API_ extern ::std::string GTEST_FLAG(name)\n";
	char text[] =
	    "\n// *INDENT-OFF*\n"
	    "#define GTEST_DECLARE_int32_(name) \\\n"
	    "        GTEST_API_ extern ::testing::internal::Int32 GTEST_FLAG(name)\n"
	    "// *INDENT-ON*\n"
	    "#define GTEST_DECLARE_string_(name) \\\n"
	    "    GTEST_API_ extern ::std::string GTEST_FLAG(name)\n";

	char options[] = "indent-preproc-define";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(DisableFormatting, IndentPreprocDefineComments)
{
	// indent-off tags using comments with indent-preproc-define
	// should NOT be indented
	char textIn[] =
	    "\n/*INDENT-OFF*/\n"
	    "#define GTEST_DECLARE_int32_(name) \\\n"
	    "        GTEST_API_ extern ::testing::internal::Int32 GTEST_FLAG(name)\n"
	    "/*INDENT-ON*/\n"
	    "#define GTEST_DECLARE_string_(name) \\\n"
	    "        GTEST_API_ extern ::std::string GTEST_FLAG(name)\n";
	char text[] =
	    "\n/*INDENT-OFF*/\n"
	    "#define GTEST_DECLARE_int32_(name) \\\n"
	    "        GTEST_API_ extern ::testing::internal::Int32 GTEST_FLAG(name)\n"
	    "/*INDENT-ON*/\n"
	    "#define GTEST_DECLARE_string_(name) \\\n"
	    "    GTEST_API_ extern ::std::string GTEST_FLAG(name)\n";

	char options[] = "indent-preproc-define";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(DisableFormatting, MissingIndentOffTag)
{
	// indent-on without an preceding indent-off
	// should NOT get a checksum error
	char text[] =
	    "\n//\n"
	    "#ifdef _WIN32\n"
	    "#define STDCALL __stdcall\n"
	    "#else\n"
	    "#define STDCALL\n"
	    "#endif\n"
	    "// *INDENT-ON*\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(DisableFormatting, MissingIndentOnTag1)
{
	// indent-off without a following indent-on
	char text[] =
	    "\n// *INDENT-OFF*\n"
	    "#ifdef _WIN32\n"
	    "#define STDCALL __stdcall\n"
	    "#else\n"
	    "#define STDCALL\n"
	    "#endif\n"
	    "//\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(DisableFormatting, MissingIndentOnTag2)
{
	// indent-off without a following indent-on and no ending carriage return
	char text[] =
	    "\n// *INDENT-OFF*\n"
	    "#ifdef _WIN32\n"
	    "#define STDCALL __stdcall\n"
	    "#else\n"
	    "#define STDCALL\n"
	    "#endif\n"
	    "//";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle indent-off line tag
//----------------------------------------------------------------------------

TEST(DisableLineFormatting, LineTagOperators)
{
	// indent-off line tag for operators
	// first set of operators should NOT be padded
	// second set of identical operators should be padded
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    x = (int) -1;       // *NOPAD*\n"
	    "    x = (char*) -1;     // *NOPAD*\n"
	    "    x = a*b-((c*d)/e);  // *NOPAD*\n"
	    "    x = a&b;            /* *NOPAD* */\n"
	    "    x = (a&b);          /*NOPAD*/\n"
	    "    if (iPages*ROWS != iDatas)  //*NOPAD*\n"
	    "        iPages+=1;              // *NOPAD*\n"
	    "    if (age<3.0f&&age>0.0f)     // *NOPAD*\n"
	    "        setValue(age/3.0f);     // *NOPAD*\n"
	    "\n"
	    "    x = (int) -1;\n"
	    "    x = (char*) -1;\n"
	    "    x = a*b-((c*d)/e);\n"
	    "    x = a&b;\n"
	    "    x = (a&b);\n"
	    "    if (iPages*ROWS != iDatas)\n"
	    "        iPages+=1;\n"
	    "    if (age<3.0f&&age>0.0f)\n"
	    "        setValue(age/3.0f);\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    x = (int) -1;       // *NOPAD*\n"
	    "    x = (char*) -1;     // *NOPAD*\n"
	    "    x = a*b-((c*d)/e);  // *NOPAD*\n"
	    "    x = a&b;            /* *NOPAD* */\n"
	    "    x = (a&b);          /*NOPAD*/\n"
	    "    if (iPages*ROWS != iDatas)  //*NOPAD*\n"
	    "        iPages+=1;              // *NOPAD*\n"
	    "    if (age<3.0f&&age>0.0f)     // *NOPAD*\n"
	    "        setValue(age/3.0f);     // *NOPAD*\n"
	    "\n"
	    "    x = (int) - 1;\n"
	    "    x = (char*) - 1;\n"
	    "    x = a * b - ((c * d) / e);\n"
	    "    x = a & b;\n"
	    "    x = (a & b);\n"
	    "    if (iPages * ROWS != iDatas)\n"
	    "        iPages += 1;\n"
	    "    if (age < 3.0f && age > 0.0f)\n"
	    "        setValue(age / 3.0f);\n"
	    "}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(DisableLineFormatting, LineTagPointersAndReferences)
{
	// indent-off line tag for pointers and references
	// first set of pointers and references should NOT be padded
	// second set of identical pointers and references should be padded
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    string*bar;     // *NOPAD*\n"
	    "    string&bar;     /* *NOPAD* */\n"
	    "    string**bar;    /*NOPAD*/\n"
	    "    string&&bar;    // *NOPAD*\n"
	    "\n"
	    "    string*bar;\n"
	    "    string&bar;\n"
	    "    string**bar;\n"
	    "    string&&bar;\n"
	    "}";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    string*bar;     // *NOPAD*\n"
	    "    string&bar;     /* *NOPAD* */\n"
	    "    string**bar;    /*NOPAD*/\n"
	    "    string&&bar;    // *NOPAD*\n"
	    "\n"
	    "    string* bar;\n"
	    "    string &bar;\n"
	    "    string** bar;\n"
	    "    string &&bar;\n"
	    "}";
	char options[] = "align-pointer=type, align-reference=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle Macro formatting
// Test wxWidgets, Qt, MFC, and Boost macros recognized by AStyle
//----------------------------------------------------------------------------

TEST(Macro, wxWidgetsEventHandler)
{
	// wxWidgets event handler should be indented
	char text[] =
	    "\nBEGIN_EVENT_TABLE(JP5Frm,wxFrame)\n"
	    "    EVT_CLOSE(JP5Frm::WindowClose)\n"
	    "    EVT_PAINT(JP5Frm::WindowPaint)\n"
	    "    EVT_MENU(ID_MENU_FILE_OPEN, JP5Frm::MenuFileOpen)\n"
	    "    EVT_MENU(ID_MENU_FILE_EXIT, JP5Frm::MenuFileExit)\n"
	    "END_EVENT_TABLE()\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, wxWidgetsEventHandlerNonIndentComment)
{
	// wxWidgets event handler should be indented
	// but not the comments
	char text[] =
	    "\nBEGIN_EVENT_TABLE(JP5Frm,wxFrame)\n"
	    "//    EVT_CLOSE(JP5Frm::WindowClose)\n"
	    "    EVT_PAINT(JP5Frm::WindowPaint)\n"
	    "    EVT_MENU(ID_MENU_FILE_OPEN, JP5Frm::MenuFileOpen)\n"
	    "//    EVT_MENU(ID_MENU_FILE_EXIT, JP5Frm::MenuFileExit)\n"
	    "END_EVENT_TABLE()\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, wxWidgetsIndentForceTabX)
{
	// wxWidgets event handler should be indented correctly with indent=force-tab-x
	char text[] =
	    "\nBEGIN_EVENT_TABLE(JP5Frm,wxFrame)\n"
	    "    EVT_MENU(ID_MENU_FILE_OPEN, JP5Frm::MenuFileOpen)\n"
	    "    EVT_MENU(ID_MENU_FILE_EXIT, JP5Frm::MenuFileExit)\n"
	    "END_EVENT_TABLE()\n"
	    "\n"
	    "void Foo()\n"
	    "{\n"
	    "    BEGIN_EVENT_TABLE(JP5Frm,wxFrame)\n"
	    "	EVT_MENU(ID_MENU_FILE_OPEN, JP5Frm::MenuFileOpen)\n"
	    "	EVT_MENU(ID_MENU_FILE_EXIT, JP5Frm::MenuFileExit)\n"
	    "    END_EVENT_TABLE()\n"
	    "\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "	BEGIN_EVENT_TABLE(JP5Frm,wxFrame)\n"
	    "	    EVT_MENU(ID_MENU_FILE_OPEN, JP5Frm::MenuFileOpen)\n"
	    "	    EVT_MENU(ID_MENU_FILE_EXIT, JP5Frm::MenuFileExit)\n"
	    "	END_EVENT_TABLE()\n"
	    "    }\n"
	    "}";
	char options[] = "indent=force-tab-x";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, wxWidgetsFillEmptyLines)
{
	// test fill empty lines in an event table
	char textIn[] =
	    "\nBEGIN_EVENT_TABLE(JP5Frm,wxFrame)\n"
	    "    EVT_PAINT(JP5Frm::WindowPaint)\n"
	    "\n"
	    "\n"
	    "    EVT_MENU(ID_MENU_FILE_OPEN, JP5Frm::MenuFileOpen)\n"
	    "END_EVENT_TABLE()\n";
	char text[] =
	    "\nBEGIN_EVENT_TABLE(JP5Frm,wxFrame)\n"
	    "    EVT_PAINT(JP5Frm::WindowPaint)\n"
	    "    \n"
	    "    \n"
	    "    EVT_MENU(ID_MENU_FILE_OPEN, JP5Frm::MenuFileOpen)\n"
	    "END_EVENT_TABLE()\n";
	char options[] = "fill-empty-lines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, WxWidgetsPreprocessor)
{
	// preprocessor should NOT be indented
	char text[] =
	    "\nBEGIN_EVENT_TABLE(ClassWizardDlg, wxDialog)\n"
	    "    EVT_BUTTON(XRCID(\"btnCommonDir\"), ClassWizardDlg::OnCommonDirClick)\n"
	    "#ifdef LOGGING\n"
	    "    EVT_EXPECT_TRUEBOX(XRCID(\"chkLowerCase\"), ClassWizardDlg::OnLowerCaseClick)\n"
	    "    EVT_BUTTON(XRCID(\"btnIncludeDir\"), ClassWizardDlg::OnIncludeDirClick)\n"
	    "#endif\n"
	    "    EVT_BUTTON(XRCID(\"btnImplDir\"), ClassWizardDlg::OnImplDirClick)\n"
	    "END_EVENT_TABLE()\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, WxWidgetsIndentPreprocBlock)
{
	// test indent preprocessor block in a wxWidgets event table
	// should be indented as code, not as a preprocessor block
	char text[] =
	    "\nBEGIN_EVENT_TABLE(DropDown, wxTransientWindow)\n"
	    "    EVT_MOUSE_EVENTS(DropDownPopup::OnMouse)\n"
	    "#if USE_POPUP_TIMER\n"
	    "    EVT_TIMER(wxID_ANY, DropDownPopup::OnTimer)\n"
	    "#endif // USE_POPUP_TIMER\n"
	    "    EVT_IDLE(DropDownPopup::OnIdle) // use Connect/Disconnect instead\n"
	    "END_EVENT_TABLE()";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, WxWidgetsIndentPreprocBlockSans)
{
	// test indent preprocessor block in a wxWidgets event table
	// the block will NOT be indented because it is in a un-indentable preprocessor
	char text[] =
	    "\n#ifdef __BORLANDC__\n"
	    "    #pragma hdrstop\n"
	    "#endif\n"
	    "\n"
	    "#if wxUSE_POPUPWIN\n"
	    "\n"
	    "BEGIN_EVENT_TABLE(DropDown, wxTransientWindow)\n"
	    "    EVT_MOUSE_EVENTS(DropDownPopup::OnMouse)\n"
	    "#if USE_POPUP_TIMER\n"
	    "    EVT_TIMER(wxID_ANY, DropDownPopup::OnTimer)\n"
	    "#endif // USE_POPUP_TIMER\n"
	    "    EVT_IDLE(DropDownPopup::OnIdle) // use Connect/Disconnect instead\n"
	    "END_EVENT_TABLE()\n"
	    "\n"
	    "void Foo()\n"
	    "{}\n"
	    "\n"
	    "#endif // wxUSE_POPUPWIN";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, WxWidgetsIndentNamespace)
{
	// test indent preprocessor block in a indented namespace
	// should be indented as code
	char text[] =
	    "\nnamespace ScriptBindings\n"
	    "{\n"
	    "    BEGIN_EVENT_TABLE(XrcDialog, wxScrollingDialog)\n"
	    "        EVT_CHOICE(-1, XrcDialog::OnButton)\n"
	    "        EVT_COMBOBOX(-1, XrcDialog::OnButton)\n"
	    "        EVT_CHECKBOX(-1, XrcDialog::OnButton)\n"
	    "    END_EVENT_TABLE()\n"
	    "}";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, WxWidgetsIndentNamespaceSans)
{
	// test indent preprocessor block in a indented namespace
	// should be indented as code
	char text[] =
	    "\nnamespace ScriptBindings\n"
	    "{\n"
	    "BEGIN_EVENT_TABLE(XrcDialog, wxScrollingDialog)\n"
	    "    EVT_CHOICE(-1, XrcDialog::OnButton)\n"
	    "    EVT_COMBOBOX(-1, XrcDialog::OnButton)\n"
	    "    EVT_CHECKBOX(-1, XrcDialog::OnButton)\n"
	    "END_EVENT_TABLE()\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, WxWidgetsIndentNamespaceIndentPreprocBlock)
{
	// test indent preprocessor block in a indented namespace
	// includes a preprocessor statement
	char text[] =
	    "\nnamespace ScriptBindings\n"
	    "{\n"
	    "    BEGIN_EVENT_TABLE(XrcDialog, wxScrollingDialog)\n"
	    "        EVT_CHOICE(-1, XrcDialog::OnButton)\n"
	    "#if USE_POPUP_TIMER\n"
	    "        EVT_COMBOBOX(-1, XrcDialog::OnButton)\n"
	    "#endif // USE_POPUP_TIMER\n"
	    "        EVT_CHECKBOX(-1, XrcDialog::OnButton)\n"
	    "    END_EVENT_TABLE()\n"
	    "}";
	char options[] = "indent-namespaces, indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, WxWidgetsIndentNamespaceSansIndentPreprocBlock)
{
	// test indent preprocessor block in a NON-indented namespace
	// includes a preprocessor statement
	char text[] =
	    "\nnamespace ScriptBindings\n"
	    "{\n"
	    "BEGIN_EVENT_TABLE(XrcDialog, wxScrollingDialog)\n"
	    "    EVT_CHOICE(-1, XrcDialog::OnButton)\n"
	    "#if USE_POPUP_TIMER\n"
	    "    EVT_COMBOBOX(-1, XrcDialog::OnButton)\n"
	    "#endif // USE_POPUP_TIMER\n"
	    "    EVT_CHECKBOX(-1, XrcDialog::OnButton)\n"
	    "END_EVENT_TABLE()\n"
	    "}";
	char options[] = "indent-preproc-block";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, QtForeach1)
{
	// Qt Q_FOREACH macro indent
	char text[] =
	    "\nint foo()\n"
	    "{\n"
	    "    Q_FOREACH(const Foo &f, list)\n"
	    "        qDebug() << f.a << f.b << f.c;\n"
	    "\n"
	    "    Q_FOREACH(const Foo &f, list)\n"
	    "        {\n"
	    "            qDebug() << f.a << f.b << f.c;\n"
	    "        }\n"
	    "}";
	char options[] = "style=gnu";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, QtForeach2)
{
	// Qt foreach macro indent
	char text[] =
	    "\nint foo()\n"
	    "{\n"
	    "    foreach(const Foo &f, list)\n"
	    "        qDebug() << f.a << f.b << f.c;\n"
	    "\n"
	    "    foreach(const Foo &f, list)\n"
	    "        {\n"
	    "            qDebug() << f.a << f.b << f.c;\n"
	    "        }\n"
	    "}";
	char options[] = "style=gnu";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, QtForeachPadHeader)
{
	// Qt foreach macro should pad header
	char textIn[] =
	    "\nint foo()\n"
	    "{\n"
	    "    Q_FOREACH(const Foo &f, list)\n"
	    "        qDebug() << f.a << f.b << f.c;\n"
	    "\n"
	    "    foreach(const Foo &f, list)\n"
	    "        qDebug() << f.a << f.b << f.c;\n"
	    "}";
	char text[] =
	    "\nint foo()\n"
	    "{\n"
	    "    Q_FOREACH (const Foo &f, list)\n"
	    "        qDebug() << f.a << f.b << f.c;\n"
	    "\n"
	    "    foreach (const Foo &f, list)\n"
	    "        qDebug() << f.a << f.b << f.c;\n"
	    "}";
	char options[] = "pad-header";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, QtForeachAlignPointer)
{
	// Qt foreach macro should default to pointer
	char textIn[] =
	    "\nint foo()\n"
	    "{\n"
	    "    Q_FOREACH(const Foo &f, list)\n"
	    "        qDebug() << f.a << f.b << f.c;\n"
	    "\n"
	    "    foreach(const Foo &f, list)\n"
	    "        qDebug() << f.a << f.b << f.c;\n"
	    "}";
	char text[] =
	    "\nint foo()\n"
	    "{\n"
	    "    Q_FOREACH(const Foo& f, list)\n"
	    "        qDebug() << f.a << f.b << f.c;\n"
	    "\n"
	    "    foreach(const Foo& f, list)\n"
	    "        qDebug() << f.a << f.b << f.c;\n"
	    "}";
	char options[] = "align-pointer=type, pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, QtForeachSans)
{
	// Qt foreach may be used as a variable in C++.
	// Brackets should not attach.
	// The following line should be indented correctly.
	char text[] =
	    "\nvoid astyle_bug()\n"
	    "{\n"
	    "    const bool foreach = true;\n"
	    "    const bool xxxxxxx = true;\n"
	    "}";
	char options[] = "add-braces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, QtForever1)
{
	// Qt Q_FOREVER macro indent
	char text[] =
	    "\nint foo()\n"
	    "{\n"
	    "    Q_FOREVER\n"
	    "        break;\n"
	    "\n"
	    "    Q_FOREVER\n"
	    "        {\n"
	    "            break;;\n"
	    "        }\n"
	    "}";
	char options[] = "style=gnu";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, QtForever2)
{
	// Qt forever macro indent
	char text[] =
	    "\nint foo()\n"
	    "{\n"
	    "    forever\n"
	    "        break;\n"
	    "\n"
	    "    forever\n"
	    "        {\n"
	    "            break;;\n"
	    "        }\n"
	    "}";
	char options[] = "style=gnu";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, QtForeverSans)
{
	// Qt forever may be used as a variable in C++.
	// Brackets should not attach.
	char text[] =
	    "\nvoid astyle_bug()\n"
	    "{\n"
	    "    const bool forever = true;\n"
	    "}";
	char options[] = "add-braces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, MfcDispatchMap)
{
	// MFC dispatch map should be indented
	char text[] =
	    "\nBEGIN_DISPATCH_MAP(CblahCtrl, COleControl)\n"
	    "    DISP_FUNCTION_ID(CMySink,\"Quit\",2,OnObjQuit,VT_EMPTY,VTS_I4 VTS_I4)\n"
	    "    DISP_FUNCTION_ID(CblahCtrl,\"AboutBox\",2,AboutBox,VT_EMPTY,VTS_NONE)\n"
	    "END_DISPATCH_MAP()\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, MfcEventMap)
{
	// MFC event map should be indented
	char text[] =
	    "\nBEGIN_EVENT_MAP(CDataqSdkCtrl, COleControl)\n"
	    "    EVENT_CUSTOM(\"NewData\", FireNewData, VTS_I2)\n"
	    "    EVENT_CUSTOM(\"OverRun\", FireOverRun, VTS_NONE)\n"
	    "    EVENT_CUSTOM(\"ControlError\", FireControlError, VTS_I4)\n"
	    "END_EVENT_MAP()\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, MfcMessageMap)
{
	// MFC message map should be indented
	char text[] =
	    "\nBEGIN_MESSAGE_MAP(CMainJPWnd, CFrameWnd)\n"
	    "    ON_WM_CLOSE()\n"
	    "    ON_WM_PAINT()\n"
	    "    ON_COMMAND(IDM_ABOUT, OnAbout)\n"
	    "    ON_COMMAND(IDM_EXIT,  OnExit)\n"
	    "END_MESSAGE_MAP()\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Macro, MfcPropertyPages)
{
	// MFC property pages should be indented
	char text[] =
	    "\nBEGIN_PROPPAGEIDS(CblahCtrl, 1)\n"
	    "    PROPPAGEID( CLSID_CFontPropPage )\n"
	    "    PROPPAGEID( CLSID_CColorPropPage )\n"
	    "END_PROPPAGEIDS(CblahCtrl)\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle Character Set Tests
//----------------------------------------------------------------------------

TEST(CharacterSet, ExtendedCharacterSet)
{
	// Clang issues a compiler warning for "illegal character encoding".
#ifndef __clang__
	// multi-byte characters (c) and ü should not cause assert error with
	//     Visual Studio isalpha(), isalnum(), ispunct(), etc.
	// will happen only in the debug build
	char text[] =
	    "\n// © is character 169\n"
	    "\n// ü is character 252\n"
	    "void foo()\n"
	    "{\n"
	    "    ©bar1();\n"
	    "    barü2();\n"
	    "    bar3©();\n"
	    "    ba©r4(ü);\n"
	    "    cout << \"©ü\" << endl;\n"
	    "    ©\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
#endif
}

TEST(CharacterSet, UnicodeCharacterSet)
{
	// unicode characters should not cause assert error with
	//     Visual Studio isalpha(), isalnum(), ispunct(), etc.
	// will happen only in the debug build
	char text[] =
	    "\n// \xF0\x80\xA0\xB0 is a unicode UTF-8 character\n"
	    "void foo()\n"
	    "{\n"
	    "    \xF0\x80\xA0\xB0\x62\x61r1();\n"
	    "    bar\xF0\x80\xA0\xB0\x32();\n"
	    "    bar3(\xF0\x80\xA0\xB0);\n"
	    "    ba\xF0\x80\xA0\xB0r4();\n"
	    "    cout << \"\xF0\x80\xA0\xB0\" << endl;\n"
	    "    \xF0\x80\xA0\xB0\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(CharacterSet, UTF8WithBOM)
{
	// UTF-8 BOM should not cause assert error with
	//     Visual Studio isalpha(), isalnum(), ispunct(), etc.
	//     and should recognize "namespace" as a keyword
	// will happen only in the debug build
	char textIn[] =
	    "\xEF\xBB\xBFnamespace {\n"
	    "}\n";
	char text[] =
	    "\xEF\xBB\xBFnamespace\n"
	    "{\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle short options beginning with x for errors.
// This tests the error conditions.
//----------------------------------------------------------------------------

TEST(ExtraShortOption, ErrorXSans)
{
	// test the x short option used by itself
	// should get an error
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-x";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ExtraShortOption, ErrorExtraX1)
{
	// test the xx short option
	// should get an error
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-xx";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ExtraShortOption, ErrorExtraX2)
{
	// test the x short option followed by xd
	// should get an error
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-xxd";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ExtraShortOption, ErrorNumericX)
{
	// test the x short option followed by a number
	// should get an error
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-x1";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle short options used only by console
// should get an error unless they have been duplicated by another option
//----------------------------------------------------------------------------

TEST(ConsoleShortOption, SuffixNoneShort)
{
	// test suffix=none short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-n";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, Recursive1Short)
{
	// test recursive short option1
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-r";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, Recursive2Short)
{
	// test recursive short option2
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-R";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, IgnoreExcludeErrorsShort)
{
	// test ignore-exclude-errors short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-i";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, IgnoreExcludeErrorsXShort)
{
	// test ignore-exclude-errors-x short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-xi";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, ErrorsToStdoutShort)
{
	// test errors-to-stdout short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-X";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, PreserveDateShort)
{
	// test preserve-date short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-Z";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, VerboseShort)
{
	// test verbose short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-v";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, FormattedShort)
{
	// test formatted short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-Q";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, QuietShort)
{
	// test quiet short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-q";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, LineEndWindowsShort)
{
	// test lineend=windows short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-z1";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, LineEndLinuxShort)
{
	// test lineend=linux short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-z2";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, LineEndMacOldShort)
{
	// test lineend=macold short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-z3";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, AsciiShort)
{
	// test ascii short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-I";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, VersionShort)
{
	// test version short option
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-V";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, Help1Short)
{
	// test help short option1
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-h";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

TEST(ConsoleShortOption, Help2Short)
{
	// test help short option2
	// should get an error unless it has been duplicated by another option
	// the source will be formatted without the option
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bar();\n"
	    "}\n";
	char options[] = "-?";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != nullptr);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle default line ends
// there are other tests in AStyleTestCon
//----------------------------------------------------------------------------

struct LineEndsDefaultF : public Test
{
	string textLinuxStr;
	string textWindowsStr;
	string textMacOldStr;
	const char* textLinux;
	const char* textWindows;
	const char* textMacOld;

	LineEndsDefaultF()
	{
		textLinuxStr =
		    "\nvoid foo()\n"
		    "{\n"
		    "    bar()\n"
		    "}\n";
		textWindowsStr =
		    "\r\nvoid foo()\r\n"
		    "{\r\n"
		    "    bar()\r\n"
		    "}\r\n";
		textMacOldStr =
		    "\rvoid foo()\r"
		    "{\r"
		    "    bar()\r"
		    "}\r";
		textLinux = textLinuxStr.c_str();
		textWindows = textWindowsStr.c_str();
		textMacOld = textMacOldStr.c_str();
	}
};

TEST_F(LineEndsDefaultF, DefaultLinux)
{
	// test default Linux line ends
	char options[] = "";
	char* textOut = AStyleMain(textLinux, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(textLinux, textOut);
	delete[] textOut;
}

TEST_F(LineEndsDefaultF, DefaultWindows)
{
	// test default Windows line ends
	char options[] = "";
	char* textOut = AStyleMain(textWindows, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(textWindows, textOut);
	delete[] textOut;
}

TEST_F(LineEndsDefaultF, DefaultMacOld)
{
	// test default MacOld line ends
	char options[] = "";
	char* textOut = AStyleMain(textMacOld, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(textMacOld, textOut);
	delete[] textOut;
}

TEST_F(LineEndsDefaultF, DefaultBadWindows)
{
	// test default Windows with line end characters reversed
	// should be converted to Windows
	char textBadWindows[] =
	    "\n\rvoid foo()\n\r"
	    "{\n\r"
	    "    bar()\n\r"
	    "}\n\r";
	char options[] = "";
	char* textOut = AStyleMain(textBadWindows, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(textWindows, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle Quotes
//----------------------------------------------------------------------------

TEST(Quote, Continuation)
{
	// test quotes
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    char* quote = \"this	is a quote \\\n"
	    "  	quote	continuation  \\\n"
	    "	quote continuation\";\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Quote, Single)
{
	// test single quotes
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (ch == \'\\r\')\n"
	    "        eolWindows++;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Quote, Sharp_Verbatim1)
{
	// test C# verbatim quotes
	// whitespace should not change
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    string program = @\"using System;\n"   // begin string
	    "class Test {\n"
	    "  void M(DerivedClass d) {\n"
	    "    \n"
	    "  }\n"
	    "}\n"
	    "class BaseClass<T> {\n"
	    "	public T value;\n"
	    "}\n"
	    "class DerivedClass : BaseClass<string> {\n"
	    "			\n"
	    "}\n"
	    "\";\n"                                     // end of string
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Quote, CSharp_Verbatim2)
{
	// test C# verbatim quotes with """" and ""
	// whitespace should not change
	char text[] =
	    "\nstring Resource = @\"using System;\n"    // begin string
	    "class A {\n"
	    "    void B()\n"
	    "    {\n"
	    "        ResourceManager mgr = new ResourceManager(\"\"\"\", GetAssembly());\n"
	    "        mgr.GetString(\"\"TestKey\"\");\n"
	    "    }\n"
	    "}\n"
	    "\";";                                      // end of string
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Quote, CSharp_Empty)
{
	// test C# empty quotes with """"
	// whitespace should not change
	char text[] =
	    "\npublic static string GetString(string key)\n"
	    "{\n"
	    "    return \"\"\"\";\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Quote, CSharp_Misc1)
{
	// test C# strange looking quotes with """
	// whitespace should not change
	char text[] =
	    "\npublic void TestString()\n"
	    "{\n"
	    "    EXPECT_TRUEToken(@\"@\"\"-->\"\"\"\"<--\"\"\", @\"-->\"\"<--\");\n"
	    "    EXPECT_TRUEToken(@\"\"\"-->\\\"\"<--\"\"\", \"-->\\\"<--\");\n"
	    "\n"
	    "    EXPECT_TRUEToken(@\"\"\"\\U00000041\"\"\", \"\\U00000041\");\n"
	    "    EXPECT_TRUEToken(@\"\"\"\\U00010041\"\"\", \"\\U00010041\");\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Quote, CSharp_Misc2)
{
	// test C# strange looking quotes from SharpDevelop strings test
	// whitespace should not change
	char text[] =
	    "\n"
	    "void Strings(string s = \"\")\n"
	    "{\n"
	    "    s = @\"\"\"\n"
	    "can't escape a verbatim string \\\";\n"
	    "    s = @\"\" \"not in verbatim anymore\n"
	    "        ;\n"
	    "    s = \"\";\n"
	    "    s = \"\\\\\";\n"
	    "    s = \"\\\\\\\\\\\\\\\"\";\n"
	    "    s = \" // syntax error, but on the next line we start with the previous state\n"
	    "        ;\n"
	    "    s = \"'c\\'\";\n"
	    "    string concat = \"line 1\" +\n"
	    "                    \"line 2\" +\n"
	    "                    \"line 3\";\n"
	    "\n"
	    "    var c = '\\\\';\n"
	    "    c = '\\'';\n"
	    "    c = ' // syntax error, but on the next line we start with the previous state\n"
	    "        ;\n"
	    "    c = ';';\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle Enum
//----------------------------------------------------------------------------

TEST(Enum, Namespace1)
{
	// test indent of enum in a namespace
	char text[] =
	    "\nnamespace fooName\n"
	    "{\n"
	    "enum dStyle\n"
	    "{\n"
	    "    OK = 0,\n"
	    "    YES_NO,\n"
	    "};\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, Namespace2)
{
	// test indent of enum in a namespace
	// with in-statement indent
	char text[] =
	    "\nnamespace fooName\n"
	    "{\n"
	    "enum dStyle { OK = 0,\n"
	    "              YES_NO,\n"
	    "            };\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, NamespaceIndent1)
{
	// test indent of enum in an indented namespace
	char text[] =
	    "\nnamespace fooName\n"
	    "{\n"
	    "    enum dStyle\n"
	    "    {\n"
	    "        OK = 0,\n"
	    "        YES_NO,\n"
	    "    };\n"
	    "}\n";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, NamespaceIndent2)
{
	// test indent of enum in an indented namespace
	// with in-statement indent
	char text[] =
	    "\nnamespace fooName\n"
	    "{\n"
	    "    enum dStyle { OK = 0,\n"
	    "                  YES_NO,\n"
	    "                };\n"
	    "}\n";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, ClassTypeSafe)
{
	// type safe enum class should be formatted as an enum
	char text[] =
	    "\nenum class Day\n"
	    "{\n"
	    "    NoDays=0,\n"
	    "    Sunday=1,\n"
	    "    Monday,\n"
	    "    FirstDay = Day::Sunday\n"
	    "};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, Class1)
{
	// test indent of enum in a class
	char text[] =
	    "\nclass fooClass\n"
	    "{\n"
	    "public:\n"
	    "    enum dStyle\n"
	    "    {\n"
	    "        OK = 0,\n"
	    "        YES_NO,\n"
	    "    };\n"
	    "};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, Class2)
{
	// test indent of enum in a class
	// enum has a colon (:) and no brackets
	char text[] =
	    "\n"
	    "class TestClass : public ParentClass {\n"
	    "protected:\n"
	    "    enum Registers : uint16_t;\n"
	    "public:\n"
	    "    void testFunction();\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, Class3)
{
	// test indent of enum in a class
	// with in-statement indent
	char text[] =
	    "\nclass fooClass\n"
	    "{\n"
	    "public:\n"
	    "    enum dStyle { OK = 0,\n"
	    "                  YES_NO,\n"
	    "                };\n"
	    "};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, ClassTab1)
{
	// test tab indent of enum in a class
	char text[] =
	    "\nclass fooClass\n"
	    "{\n"
	    "public:\n"
	    "\tenum dStyle\n"
	    "\t{\n"
	    "\t\tOK = 0,\n"
	    "\t\tYES_NO,\n"
	    "\t};\n"
	    "};\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, ClassTab2)
{
	// test tab indent of enum in a class
	// with in-statement indent
	char text[] =
	    "\nclass fooClass\n"
	    "{\n"
	    "public:\n"
	    "\tenum dStyle { OK = 0,\n"
	    "\t              YES_NO,\n"
	    "\t            };\n"
	    "};\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, ClassIndent1)
{
	// test indent of enum in an indented class
	char text[] =
	    "\nclass fooClass\n"
	    "{\n"
	    "    public:\n"
	    "        enum dStyle\n"
	    "        {\n"
	    "            OK = 0,\n"
	    "            YES_NO,\n"
	    "        };\n"
	    "};\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, ClassIndent2)
{
	// test indent of enum in an indented class
	// with in-statement indent
	char text[] =
	    "\nclass fooClass\n"
	    "{\n"
	    "    public:\n"
	    "        enum dStyle { OK = 0,\n"
	    "                      YES_NO,\n"
	    "                    };\n"
	    "};\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, ClassIndent3)
{
	// test indent of enum in an indented class
	// within a #else preprocessor
	char text[] =
	    "\n#if VERSION(2)\n"
	    "#else\n"
	    "class fooClass\n"
	    "{\n"
	    "    public:\n"
	    "        enum wxPaneState\n"
	    "        {\n"
	    "            optionFloating = 1 << 0,\n"
	    "            optionHidden   = 1 << 1,\n"
	    "        };\n"
	    "};\n"
	    "#endif\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, InStatementIndent1)
{
	// test in-statement indent of an enum
	char text[] =
	    "\nenum {\n"
	    "    A_REMAINDER_OF_LONG_NAME = 0x01,\n"
	    "    B_REMAINDER_OF_LONG_NAME = 0x02,\n"
	    "    AB_REMAINDER_OF_LONG_NAME =\n"
	    "        A_REMAINDER_OF_LONG_NAME |\n"
	    "        B_REMAINDER_OF_LONG_NAME,\n"
	    "    C_REMAINDER_OF_LONG_NAME = 0x01,\n"
	    "    D_REMAINDER_OF_LONG_NAME =  A_REMAINDER_OF_LONG_NAME |\n"
	    "                                C_REMAINDER_OF_LONG_NAME,\n"
	    "    E_REMAINDER_OF_LONG_NAME,\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, InStatementIndent2)
{
	// test in-statement indent of an enum
	char text[] =
	    "\nenum { A_REMAINDER_OF_LONG_NAME = 0x01,\n"
	    "       B_REMAINDER_OF_LONG_NAME = 0x02,\n"
	    "       AB_REMAINDER_OF_LONG_NAME =\n"
	    "           A_REMAINDER_OF_LONG_NAME |\n"
	    "           B_REMAINDER_OF_LONG_NAME,\n"
	    "       C_REMAINDER_OF_LONG_NAME = 0x01,\n"
	    "       D_REMAINDER_OF_LONG_NAME =  A_REMAINDER_OF_LONG_NAME |\n"
	    "                                   C_REMAINDER_OF_LONG_NAME,\n"
	    "       E_REMAINDER_OF_LONG_NAME,\n"
	    "     };";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, InStatementIndentTab1)
{
	// test tab indent of an enum
	char text[] =
	    "\nenum {\n"
	    "\tA_REMAINDER_OF_LONG_NAME = 0x01,\n"
	    "\tB_REMAINDER_OF_LONG_NAME = 0x02,\n"
	    "\tAB_REMAINDER_OF_LONG_NAME =\n"
	    "\t    A_REMAINDER_OF_LONG_NAME |\n"
	    "\t    B_REMAINDER_OF_LONG_NAME,\n"
	    "\tC_REMAINDER_OF_LONG_NAME = 0x01,\n"
	    "\tD_REMAINDER_OF_LONG_NAME =  A_REMAINDER_OF_LONG_NAME |\n"
	    "\t                            C_REMAINDER_OF_LONG_NAME,\n"
	    "\tE_REMAINDER_OF_LONG_NAME,\n"
	    "};";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, InStatementIndentTab2)
{
	// test in-statement tab indent of an enum
	char text[] =
	    "\nenum { A_REMAINDER_OF_LONG_NAME = 0x01,\n"
	    "       B_REMAINDER_OF_LONG_NAME = 0x02,\n"
	    "       AB_REMAINDER_OF_LONG_NAME =\n"
	    "           A_REMAINDER_OF_LONG_NAME |\n"
	    "           B_REMAINDER_OF_LONG_NAME,\n"
	    "       C_REMAINDER_OF_LONG_NAME = 0x01,\n"
	    "       D_REMAINDER_OF_LONG_NAME =  A_REMAINDER_OF_LONG_NAME |\n"
	    "                                   C_REMAINDER_OF_LONG_NAME,\n"
	    "       E_REMAINDER_OF_LONG_NAME,\n"
	    "     };";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, LeadingComma1)
{
	// test enum with leading commas
	char text[] =
	    "\nenum myCodes[] = {\n"
	    "    KEY_F4 = 0x013E\n"
	    "    , KEY_F5 = 0x013F\n"
	    "    , KEY_F6 = 0x0140\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, LeadingComma2)
{
	// test enum with leading commas and multiple '=' per line
	char text[] =
	    "\nstruct YesNoAuto {\n"
	    "    enum {\n"
	    "        Auto = 1, Auto = 2, Auto = 3\n"
	    "        , Yes\n"
	    "        , No\n"
	    "    };\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, EnumReturnType)
{
	// an enum return type is NOT an enumeration
	// the pointer dereference should not change
	char text[] =
	    "\nenum SomeEnum SomeFunc(int _var)\n"
	    "{\n"
	    "    assert(frame && *len);\n"
	    "    bar();\n"
	    "    *_var = 1;\n"
	    "}";
	char options[] = "align-pointer=type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, EnumArgument1)
{
	// An enum argument is NOT an enum.
	// The return statement will be indented incorrectly if
	// it is incorrectly flagged.
	char text[] =
	    "\nint MSG(enum a type)\n"
	    "{\n"
	    "    switch (type) {\n"
	    "    case 1:\n"
	    "        return 1;\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, EnumArgument2)
{
	// An enum argument is NOT an enum.
	// The case statements will get an extra indent if
	// it is incorrectly flagged.
	char text[] =
	    "\nint Foo(enum type_t var)\n"
	    "{\n"
	    "    switch (var) {\n"
	    "    case VALUE_1:\n"
	    "    case VALUE_2:\n"
	    "    case VALUE_3:\n"
	    "        return 1;\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, EnumArgument3)
{
	// An enum argument is NOT an enum.
	// The brackets will be changed if it is incorrectly flagged.
	char text[] =
	    "\nvoid cliConsoleDiagnostic (struct Command* chain,\n"
	    "                           enum ErrorType errtype,\n"
	    "                           size_t argstr_len)\n"
	    "{\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, Misc1)
{
	// Enum is on a separate line.
	char text[] =
	    "\nenum\n"
	    "FooType\n"
	    "{\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Enum, Java)
{
	// test indent of java enum
	char text[] =
	    "\npublic enum KeyboardCommand\n"
	    "{   NONE,\n"
	    "    TAB_OUT_FORWARD,\n"
	    "    TAB_OUT_BACK\n"
	    "}\n";
	char options[] = "mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle Struct
//----------------------------------------------------------------------------

TEST(Struct, Break)
{
	// struct with broken brackets
	char text[] =
	    "\nstruct\n"
	    "{\n"
	    "    const char *name;\n"
	    "    int id;\n"
	    "} idmTable[] =\n"
	    "{\n"
	    "    {\"IDM_MRUFILE\", IDM_MRUFILE},\n"
	    "    {\"IDM_TOOLS\",   IDM_TOOLS},\n"
	    "};\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Struct, Attach)
{
	// struct with attached brackets
	char text[] =
	    "\nstruct {\n"
	    "    const char *name;\n"
	    "    int id;\n"
	    "} idmTable[] = {\n"
	    "    {\"IDM_MRUFILE\", IDM_MRUFILE},\n"
	    "    {\"IDM_TOOLS\",   IDM_TOOLS},\n"
	    "};\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Struct, RunIn)
{
	// struct with attached brackets
	char text[] =
	    "\nstruct\n"
	    "{   const char *name;\n"
	    "    int id;\n"
	    "} idmTable[] =\n"
	    "{   {\"IDM_MRUFILE\", IDM_MRUFILE},\n"
	    "    {\"IDM_TOOLS\",   IDM_TOOLS},\n"
	    "};\n";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle PreCommandHeaders
//----------------------------------------------------------------------------

TEST(PreCommandHeaders, ConstVolatile)
{
	// Test with "const volatile".
	// The keyword "Volatile" used as a  type qualifier caused the data after the "if"
	// statement to receive 1 less indent than needed.
	char text[] =
	    "\nbool MDMsgBatchManager::IsReindexRequired () const volatile\n"
	    "{\n"
	    "    bool result = false;\n"
	    "    if (isReindexed)\n"
	    "    {\n"
	    "        result = true;\n"
	    "    }\n"
	    "    return result;\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(PreCommandHeaders, VolatileConst)
{
	// Test with "volatile const".
	// The keyword "Volatile" used as a  type qualifier caused the data after the "if"
	// statement to receive 1 less indent than needed.
	char text[] =
	    "\nbool MDMsgBatchManager::IsReindexRequired () volatile const\n"
	    "{\n"
	    "    bool result = false;\n"
	    "    if (isReindexed)\n"
	    "    {\n"
	    "        result = true;\n"
	    "    }\n"
	    "    return result;\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(PreCommandHeaders, VolatileOnly1)
{
	// Test with "volatile" only.
	// The keyword "Volatile" used as a  type qualifier caused the data after the "if"
	// statement to receive 1 less indent than needed.
	char text[] =
	    "\nbool MDMsgBatchManager::IsReindexRequired () volatile\n"
	    "{\n"
	    "    bool result = false;\n"
	    "    if (isReindexed)\n"
	    "    {\n"
	    "        result = true;\n"
	    "    }\n"
	    "    return result;\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(PreCommandHeaders, VolatileOnly2)
{
	// Test with "volatile" only.
	// The keyword "Volatile" used as a  type qualifier caused the second
	// parameter line (b_variable) to receive 1 less indent than needed.
	char text[] =
	    "\nvoid fooFunction() volatile\n"
	    "{\n"
	    "    foo(a_variable,\n"
	    "        b_variable);\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(PreCommandHeaders, ConstSealedOverride1)
{
	// Precommand headers const, sealed, and override, with const first.
	char text[] =
	    "\nclass AStyleTest\n"
	    "{\n"
	    "    virtual void foo() const {\n"
	    "        if ( x ) {\n"
	    "            do1();\n"
	    "            do2();\n"
	    "        }\n"
	    "    }\n"
	    "\n"
	    "    virtual void foo_override() const override {\n"
	    "        if ( x ) {\n"
	    "            do1();\n"
	    "            do2();\n"
	    "        }\n"
	    "    }\n"
	    "\n"
	    "    virtual void foo_sealed() const sealed override {\n"
	    "        if ( x ) {\n"
	    "            do1();\n"
	    "            do2();\n"
	    "        }\n"
	    "    }\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(PreCommandHeaders, ConstSealedOverride2)
{
	// Precommand headers const, sealed, and override, with const last.
	char text[] =
	    "\nclass AStyleTest\n"
	    "{\n"
	    "    virtual void foo_override() override const {\n"
	    "        if ( x ) {\n"
	    "            do1();\n"
	    "            do2();\n"
	    "        }\n"
	    "    }\n"
	    "\n"
	    "    virtual void foo_sealed() sealed override const {\n"
	    "        if ( x ) {\n"
	    "            do1();\n"
	    "            do2();\n"
	    "        }\n"
	    "    }\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(PreCommandHeaders, SealedOverride)
{
	// Precommand headers sealed and override, with NO const.
	char text[] =
	    "\nclass AStyleTest\n"
	    "{\n"
	    "    virtual void foo_override() override {\n"
	    "        if ( x ) {\n"
	    "            do1();\n"
	    "            do2();\n"
	    "        }\n"
	    "    }\n"
	    "\n"
	    "    virtual void foo_sealed() sealed override {\n"
	    "        if ( x ) {\n"
	    "            do1();\n"
	    "            do2();\n"
	    "        }\n"
	    "    }\n"
	    "};";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(PreCommandHeaders, Interrupt)
{
	// Precommand header interrupt.
	char text[] =
	    "\nclass AStyleTest\n"
	    "{\n"
	    "    virtual void foo_interrupt1() interrupt 1\n"
	    "    {\n"
	    "        if ( x ) {\n"
	    "            do1();\n"
	    "            do2();\n"
	    "        }\n"
	    "    }\n"
	    "};\n"
	    "\n"
	    "virtual void foo_interrupt2() interrupt 2\n"
	    "{\n"
	    "    if ( x ) {\n"
	    "        do1();\n"
	    "        do2();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=k&r";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(PreCommandHeaders, NoExcept)
{
	// Precommand header noexcept.
	char text[] =
	    "\nclass c\n"
	    "{\n"
	    "public:\n"
	    "    int f3 () noexcept\n"
	    "    {\n"
	    "    }\n"
	    "\n"
	    "    int f3 () noexcept(false)\n"
	    "    {\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=k&r";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle Preprocessor
//----------------------------------------------------------------------------

TEST(Preprocessor, CppExternCBracket1)
{
	// Preprocessor C++ definition defined as 'extern "C"' with a bracket,
	// the bracket should NOT cause an indentation.
	char text[] =
	    "\n#ifdef __cplusplus\n"
	    "extern \"C\" {\n"
	    "#endif\n"
	    "\n"
	    "int main()\n"
	    "{\n"
	    "    return 0;\n"
	    "}\n"
	    "\n"
	    "#ifdef __cplusplus\n"
	    "}\n"
	    "#endif";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, CppExternCBracket2)
{
	// Preprocessor C++ definition defined as 'extern "C"' with a bracket,
	// the bracket should NOT cause an indentation.
	// The bracket is broken.
	char text[] =
	    "\n#ifdef __cplusplus\n"
	    "extern \"C\"\n"
	    "{\n"
	    "#endif\n"
	    "\n"
	    "int main()\n"
	    "{\n"
	    "    return 0;\n"
	    "}\n"
	    "\n"
	    "#ifdef __cplusplus\n"
	    "}\n"
	    "#endif";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, CppExternCBracket3)
{
	// Preprocessor C++ definition defined as 'extern "C"' with a bracket,
	// the bracket should NOT cause an indentation.
	// "defined" is used instead of "ifdef".
	char text[] =
	    "\n#if  defined ( __cplusplus )\n"
	    "extern \"C\"\n"
	    "{\n"
	    "#endif\n"
	    "\n"
	    "int main()\n"
	    "{\n"
	    "    return 0;\n"
	    "}\n"
	    "\n"
	    "##if  defined ( __cplusplus )\n"
	    "}\n"
	    "#endif";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, CppExternCBracket4)
{
	// Preprocessor C++ definition defined as 'extern "C"' with a bracket,
	// the bracket should NOT cause an indentation.
	// Has indented namespace after the "endif".
	char text[] =
	    "\n#ifdef __cplusplus\n"
	    "extern \"C\" {\n"
	    "#endif\n"
	    "\n"
	    "int foo()\n"
	    "{\n"
	    "    return 0;\n"
	    "}\n"
	    "\n"
	    "#ifdef __cplusplus\n"
	    "}\n"
	    "#endif\n"
	    "\n"
	    "namespace FooBar {\n"
	    "    int bar()\n"
	    "    {\n"
	    "        return 0;\n"
	    "    }\n"
	    "}   // end namespace";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, CppExternCBracket5)
{
	// Preprocessor C++ definition defined as 'extern "C"' with a bracket,
	// the bracket should NOT cause an indentation.
	// The define has additional data.
	char text[] =
	    "\n#ifdef __cplusplus\n"
	    "\n"
	    "#define SQSTD_STREAM_TYPE_TAG 0x80000000\n"
	    "\n"
	    "struct SQStream {\n"
	    "    virtual SQInteger Len() = 0;\n"
	    "};\n"
	    "\n"
	    "extern \"C\" {\n"
	    "#endif\n"
	    "\n"
	    "int foo()\n"
	    "{\n"
	    "    return 0;\n"
	    "}\n"
	    "\n"
	    "#ifdef __cplusplus\n"
	    "}\n"
	    "#endif\n"
	    "\n"
	    "namespace FooBar {\n"
	    "    int bar()\n"
	    "    {\n"
	    "        return 0;\n"
	    "    }\n"
	    "}   // end namespace";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, CppExternCSansBracket1)
{
	// Preprocessor C++ definition defined as 'extern "C"' WITHOUT a bracket,
	// Following functions should NOT be de-indented.
	char text[] =
	    "\n#ifdef __cplusplus\n"
	    "extern \"C\" void A(void);\n"
	    "#else\n"
	    "void A(void);\n"
	    "#endif\n"
	    "\n"
	    "void B(void)\n"
	    "{\n"
	    "    A();\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, CppExternCSansBracket2)
{
	// Preprocessor C++ definition defined as 'extern "C"' WITHOUT a bracket,
	// Comments added.
	// Following functions should NOT be de-indented.
	char text[] =
	    "\n#if defined(__cplusplus) // comment1\n"
	    "extern \"C\" // comment 2\n"
	    "void A(void); // comment 3\n"
	    "#else\n"
	    "void A(void);\n"
	    "#endif\n"
	    "\n"
	    "void B(void)\n"
	    "{\n"
	    "    A();\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, CommandType)
{
	// EXPECT_TRUE indentation
	// correctly identifying as a COMMND_TYPE bracket
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "#if wxUSE_UNICODE\n"
	    "        if (c < 128)\n"
	    "#else\n"
	    "        if (c < 256)\n"
	    "#endif\n"
	    "        {\n"
	    "            w += 1000;\n"
	    "        }\n"
	    "        else\n"
	    "        {\n"
	    "            w += 2000;\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, FollowsConditional)
{
	// A preprocessor directive follows an unbracketed conditional.
	// Tests the indent following the conditional statement.
	// After the #endif should be aligned under the if().
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "#ifdef __cplusplus\n"
	    "        bar1;\n"
	    "#else\n"
	    "        bar2;\n"
	    "#endif\n"
	    "    isFoo = false;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, Elif)
{
	// #elif updates the waitingBeautifierStack
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "#if USE64\n"
	    "        if (c < 64)\n"
	    "#elif USE128\n"
	    "        if (c < 128)\n"
	    "#elif USE256\n"
	    "        if (c < 256)\n"
	    "#endif\n"
	    "        {\n"
	    "            w += 1000;\n"
	    "        }\n"
	    "        else\n"
	    "        {\n"
	    "            w += 2000;\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, PragmaRegionEndRegion)
{
	// C++ #region and #endregion should be indented with the code
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    #pragma region ILineManager\n"
	    "    // <value>\n"
	    "    // A collection of all line segments\n"
	    "    #pragma endregion\n"
	    "\n"
	    "    #pragma region Nested enumerator class\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    #pragma endregion\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, SharpRegionEndRegion)
{
	// C# #region and #endregion should be indented with the code
	char text[] =
	    "\npublic interface IDocument\n"
	    "{\n"
	    "    #region ILineManager interface\n"
	    "    /// <value>\n"
	    "    /// A collection of all line segments\n"
	    "    #endregion\n"
	    "\n"
	    "    #region Nested enumerator class\n"
	    "    private sealed class Enumerator : IEnumerator, IPluginCollectionEnumerator\n"
	    "    {\n"
	    "        private readonly PluginCollection m_collection;\n"
	    "    }\n"
	    "    #endregion\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, PragmaOpenMP)
{
	// C++ "#pragma omp" should be indented with the code
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    #pragma omp parallel for\n"
	    "    for (int i = 0; i < 10; i++) {\n"
	    "        // do nothing\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, PragmaOpenMPSans)
{
	// C++ not "#pragma omp" branches
	// Will not be indented.
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "#pragma\n"
	    "    for (int i = 0; i < 10; i++) {\n"
	    "        // do nothing\n"
	    "    }\n"
	    "# pragma  om\n"
	    "    for (int i = 0; i < 10; i++) {\n"
	    "        // do nothing\n"
	    "    }\n"
	    "# pragma  omx\n"
	    "    for (int i = 0; i < 10; i++) {\n"
	    "        // do nothing\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, NestedIfElse1)
{
	// nested #if, #else, updates a different waitingBeautifierStack entry
	char text[] =
	    "\nvoid MyClass::MyFunc()\n"
	    "{\n"
	    "#ifdef DEF_1\n"
	    "    do1();\n"
	    "#else\n"
	    "    if(featureEnabled)\n"
	    "    {\n"
	    "        do3();\n"
	    "#ifdef DEF_2\n"
	    "        do4();\n"
	    "#else\n"
	    "        do5(); // This line should be aligned with do4().\n"
	    "#endif\n"
	    "    }\n"
	    "#endif\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, NestedIfElse2)
{
	// nested #if, #else, updates a different waitingBeautifierStack entry
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "#if 0\n"
	    "    int a = 0;\n"
	    "#else\n"
	    "    int b = 0;\n"
	    "    {\n"
	    "#if 0\n"
	    "        int c = 0;\n"
	    "#else\n"
	    "        int d = 0;   // This line should be aligned.\n"
	    "#endif\n"
	    "        int e = 0;\n"
	    "    }\n"
	    "#endif\n"
	    "    int f = 0;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, EndOnEmptyLine)
{
	// preprocessor define ends with an empty line
	// the empty line should not be padded
	char text[] =
	    "\n#define ITEM_ITERATION_UVC_LOOP_END(BOTTOMY) \\\n"
	    "    } while ( p->m_y < BOTTOMY ); \\\n"
	    "\n"
	    "\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, Assembler)
{
	// can have preprocessor in a assembler block
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    __asm {\n"
	    "        mov eax, fs:[0x8]\n"
	    "#ifdef _WIN32\n"
	    "        mov dx, 0xD007\n"
	    "#else\n"
	    "        mov dx, 0xD008\n"
	    "#endif\n"
	    "        out dx, al\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, MissingOpener)
{
	// #else with missing #if
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    int foo = 1;\n"
	    "#else\n"
	    "    int foo = 2;\n"
	    "#endif\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, Detached_Elif)
{
	// The # may be detached from the following directive
	// # elif updates the waitingBeautifierStack
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "# if USE64\n"
	    "        if (c < 64)\n"
	    "#    elif USE128\n"
	    "        if (c < 128)\n"
	    "#    elif USE256\n"
	    "        if (c < 256)\n"
	    "# endif\n"
	    "        {\n"
	    "            w += 1000;\n"
	    "        }\n"
	    "        else\n"
	    "        {\n"
	    "            w += 2000;\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, DetachedPragmaRegionEndRegion)
{
	// The # may be detached from the following directive
	// C++ #region and #endregion should be indented with the code
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    # pragma region ILineManager\n"
	    "    // <value>\n"
	    "    // A collection of all line segments\n"
	    "    # pragma endregion\n"
	    "\n"
	    "    #  pragma   region Nested enumerator class\n"
	    "    if (isFoo)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    #  pragma   endregion\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, Detached_SharpRegionEndRegion)
{
	// The # may be detached from the following directive
	// C# # region and # endregion should be indented with the code
	char text[] =
	    "\npublic interface IDocument\n"
	    "{\n"
	    "    # region ILineManager interface\n"
	    "    /// <value>\n"
	    "    /// A collection of all line segments\n"
	    "    # endregion\n"
	    "\n"
	    "    #  region Nested enumerator class\n"
	    "    private sealed class Enumerator : IEnumerator, IPluginCollectionEnumerator\n"
	    "    {\n"
	    "        private readonly PluginCollection m_collection;\n"
	    "    }\n"
	    "    #  endregion\n"
	    "}\n";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, Detached_PragmaOpenMP)
{
	// The # may be detached from the following directive
	// C++ "# pragma omp" should be indented with the code
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    # pragma omp parallel for\n"
	    "    for (int i = 0; i < 10; i++) {\n"
	    "        // do nothing\n"
	    "    }\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, LineStatement1)
{
	// If the #line statement is not recognized the LambdaExpression
	// line will be incorrectly indented.
	char text[] =
	    "\nvoid case_544()\n"
	    "#line 3902 \"cs-parser.jay\"\n"
	    "{\n"
	    "    if (!async_block) {\n"
	    "        if (current_anonymous_method is\n"
	    "                LambdaExpression) {\n"
	    "            report.Error (4034);\n"
	    "        }\n"
	    "    }\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, LineStatement2)
{
	// The #line statement should be trimmed of extra spaces at the end.
	char textIn[] =
	    "\nvoid case_544()\n"
	    "#line 3902 \"cs-parser.jay\"  \n"	// line has ending spaces
	    "{\n"
	    "    if (current_anonymous_method is LambdaExpression) {\n"
	    "        report.Error (4034);\n"
	    "    }\n"
	    "}";
	char text[] =
	    "\nvoid case_544()\n"
	    "#line 3902 \"cs-parser.jay\"\n"	// line has no ending spaces
	    "{\n"
	    "    if (current_anonymous_method is LambdaExpression) {\n"
	    "        report.Error (4034);\n"
	    "    }\n"
	    "}";
	char options[] = "mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, LineStatement3)
{
	// The #line statement with break-blocks should not add extra empty lines.
	char textIn[] =
	    "\nvoid case_544()\n"
	    "{\n"
	    "    if ( la.kind == 11 ) {\n"
	    "        lexer.NextToken();\n"
	    "    }\n"
	    "#line  402 \"cs.ATG\"\n"
	    "    newType.EndLocation = t.EndLocation;\n"
	    "    BlockEnd();\n"
	    "}";
	char text[] =
	    "\nvoid case_544()\n"
	    "{\n"
	    "    if ( la.kind == 11 ) {\n"
	    "        lexer.NextToken();\n"
	    "    }\n"
	    "\n"
	    "#line  402 \"cs.ATG\"\n"
	    "    newType.EndLocation = t.EndLocation;\n"
	    "    BlockEnd();\n"
	    "}";
	char options[] = "break-blocks, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, ArrayType)
{
	// EXPECT_TRUE indentation
	// correctly identifying as an ARRAY_TYPE bracket
	char text[] =
	    "\nstatic SQRegFunction base_funcs[] = {\n"
	    "    {_SC(\"seterrorhandler\"),base_seterrorhandler,2, NULL},\n"
	    "    {_SC(\"setdebughook\"),base_setdebughook,2, NULL},\n"
	    "#ifndef NO_GARBAGE_COLLECTOR\n"
	    "    {_SC(\"collectgarbage\"),base_collectgarbage,1, NULL},\n"
	    "#endif\n"
	    "    {0,0}\n"
	    "};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, ArrayMissingOpener)
{
	// array #else with missing #if
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
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, ArrayRunIn_Break)
{
	// EXPECT_TRUE broken brackets to run-in
	// should NOT run-in a preprocessor directive
	char text[] =
	    "\nchar *section_list[] =\n"
	    "{\n"
	    "#ifdef Q_OS_SOLARIS\n"
	    "    // for Solaris\n"
	    "    \"1B\", \"SunOS/BSD\",\n"
	    "#else\n"
	    "    // Other OS\n"
	    "    \"2\", \"System Calls\",\n"
	    "#endif\n"
	    "};\n";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, ArrayRunIn_Attach)
{
	// EXPECT_TRUE attached brackets to run-in
	// should NOT run-in a preprocessor directive
	char textIn[] =
	    "\nchar *section_list[] = {\n"
	    "#ifdef Q_OS_SOLARIS\n"
	    "    // for Solaris\n"
	    "    \"1B\", \"SunOS/BSD\",\n"
	    "#else\n"
	    "    // Other OS\n"
	    "    \"2\", \"System Calls\",\n"
	    "#endif\n"
	    "};\n";
	char text[] =
	    "\nchar *section_list[] =\n"
	    "{\n"
	    "#ifdef Q_OS_SOLARIS\n"
	    "    // for Solaris\n"
	    "    \"1B\", \"SunOS/BSD\",\n"
	    "#else\n"
	    "    // Other OS\n"
	    "    \"2\", \"System Calls\",\n"
	    "#endif\n"
	    "};\n";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, ArrayRunIn_RunIn)
{
	// EXPECT_TRUE run-in brackets to run-in
	// should NOT run-in a preprocessor directive
	char text[] =
	    "\nchar *section_list[] =\n"
	    "{\n"
	    "#ifdef Q_OS_SOLARIS\n"
	    "    // for Solaris\n"
	    "    \"1B\", \"SunOS/BSD\",\n"
	    "#else\n"
	    "    // Other OS\n"
	    "    \"2\", \"System Calls\",\n"
	    "#endif\n"
	    "};\n";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, CommentContinuation1)
{
	//  Comments within a preprocessor definition line can be
	//  continued without the backslash/newline.
	char text[] =
	    "\n#define MACRO(X,Y) \\\n"
	    "{                  \\\n"
	    "    /*  This comment breaks the indent engine.\n"
	    "     *  Compilers are ok with it */  \\\n"
	    "    {                      \\\n"
	    "        printf(X, Y);      \\\n"
	    "    }";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Preprocessor, CommentContinuation2)
{
	//  Comments within a preprocessor definition line can be
	//  continued without the backslash/newline.
	char text[] =
	    "\n#define MACRO(X,Y) \\\n"
	    "{                  \\\n"
	    "    /*  This comment breaks the indent engine.\n"
	    "     *  Another line.\n"
	    "     *  Compilers are ok with it */  \\\n"
	    "    {                      \\\n"
	    "        printf(X, Y);      \\\n"
	    "    }";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle Comments
//----------------------------------------------------------------------------

TEST(Comment, BracketsNone_NamespaceClassIndent_None)
{
	// comments should indent with namespaces and classes
	// brackets=none with default brackets
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "/*\n"
	    " * comment0\n"
	    " */\n"
	    "class FooClass\n"
	    "{\n"
	    "public:\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "void foo()\n"
	    "{\n"
	    "/*\n"
	    " * comment2\n"
	    " */\n"
	    "}\n"
	    "};\n"
	    "}\n";
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "    /*\n"
	    "     * comment0\n"
	    "     */\n"
	    "    class FooClass\n"
	    "    {\n"
	    "        public:\n"
	    "            /*\n"
	    "             * comment1\n"
	    "             */\n"
	    "            void foo()\n"
	    "            {\n"
	    "                /*\n"
	    "                 * comment2\n"
	    "                 */\n"
	    "            }\n"
	    "    };\n"
	    "}\n";
	char options[] = "indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, BracketsNone_NamespaceClassIndent_Break)
{
	// comments should indent with namespaces and classes
	// brackets=none with broken brackets
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "/*\n"
	    " * comment0\n"
	    " */\n"
	    "class FooClass\n"
	    "{\n"
	    "public:\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "void foo()\n"
	    "{\n"
	    "/*\n"
	    " * comment2\n"
	    " */\n"
	    "}\n"
	    "};\n"
	    "}\n";
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "    /*\n"
	    "     * comment0\n"
	    "     */\n"
	    "    class FooClass\n"
	    "    {\n"
	    "        public:\n"
	    "            /*\n"
	    "             * comment1\n"
	    "             */\n"
	    "            void foo()\n"
	    "            {\n"
	    "                /*\n"
	    "                 * comment2\n"
	    "                 */\n"
	    "            }\n"
	    "    };\n"
	    "}\n";
	char options[] = "indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, BracketsNone_NamespaceClassIndent_Attach)
{
	// comments should indent with namespaces and classes
	// brackets=none with attached brackets
	char textIn[] =
	    "\nnamespace FooName {\n"
	    "/*\n"
	    " * comment0\n"
	    " */\n"
	    "class FooClass {\n"
	    "public:\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "void foo() {\n"
	    "/*\n"
	    " * comment2\n"
	    " */\n"
	    "}\n"
	    "};\n"
	    "}\n";
	char text[] =
	    "\nnamespace FooName {\n"
	    "    /*\n"
	    "     * comment0\n"
	    "     */\n"
	    "    class FooClass {\n"
	    "        public:\n"
	    "            /*\n"
	    "             * comment1\n"
	    "             */\n"
	    "            void foo() {\n"
	    "                /*\n"
	    "                 * comment2\n"
	    "                 */\n"
	    "            }\n"
	    "    };\n"
	    "}\n";
	char options[] = "indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, BracketsNone_NamespaceClassIndent_RunIn)
{
	// comments should indent with namespaces and classes
	// brackets=none with run-in brackets
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "class FooClass\n"
	    "{\n"
	    "public:\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "void foo()\n"
	    "{/*\n"
	    "  * comment2\n"
	    "  */\n"
	    "}\n"
	    "};\n"
	    "}\n";
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "    class FooClass\n"
	    "    {\n"
	    "        public:\n"
	    "            /*\n"
	    "             * comment1\n"
	    "             */\n"
	    "            void foo()\n"
	    "            {   /*\n"
	    "                 * comment2\n"
	    "                 */\n"
	    "            }\n"
	    "    };\n"
	    "}\n";
	char options[] = "indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, BracketsBreak_NamespaceClassIndent_Break)
{
	// comments should indent with namespaces and classes
	// style=allman with broken brackets
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "/*\n"
	    " * comment0\n"
	    " */\n"
	    "class FooClass\n"
	    "{\n"
	    "public:\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "void foo()\n"
	    "{\n"
	    "/*\n"
	    " * comment2\n"
	    " */\n"
	    "}\n"
	    "};\n"
	    "}\n";
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "    /*\n"
	    "     * comment0\n"
	    "     */\n"
	    "    class FooClass\n"
	    "    {\n"
	    "        public:\n"
	    "            /*\n"
	    "             * comment1\n"
	    "             */\n"
	    "            void foo()\n"
	    "            {\n"
	    "                /*\n"
	    "                 * comment2\n"
	    "                 */\n"
	    "            }\n"
	    "    };\n"
	    "}\n";
	char options[] = "style=allman, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, BracketsBreak_NamespaceClassIndent_Attach)
{
	// comments should indent with namespaces and classes
	// style=allman with attached brackets
	char textIn[] =
	    "\nnamespace FooName {\n"
	    "/*\n"
	    " * comment0\n"
	    " */\n"
	    "class FooClass {\n"
	    "public:\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "void foo() {\n"
	    "/*\n"
	    " * comment2\n"
	    " */\n"
	    "}\n"
	    "};\n"
	    "}\n";
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "    /*\n"
	    "     * comment0\n"
	    "     */\n"
	    "    class FooClass\n"
	    "    {\n"
	    "        public:\n"
	    "            /*\n"
	    "             * comment1\n"
	    "             */\n"
	    "            void foo()\n"
	    "            {\n"
	    "                /*\n"
	    "                 * comment2\n"
	    "                 */\n"
	    "            }\n"
	    "    };\n"
	    "}\n";
	char options[] = "style=allman, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, BracketsBreak_NamespaceClassIndent_RunIn)
{
	// comments should indent with namespaces and classes
	// style=allman with run-in brackets
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "class FooClass\n"
	    "{\n"
	    "public:\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "void foo()\n"
	    "{/*\n"
	    "  * comment2\n"
	    "  */\n"
	    "}\n"
	    "};\n"
	    "}\n";
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "    class FooClass\n"
	    "    {\n"
	    "        public:\n"
	    "            /*\n"
	    "             * comment1\n"
	    "             */\n"
	    "            void foo()\n"
	    "            {\n"
	    "                /*\n"
	    "                 * comment2\n"
	    "                 */\n"
	    "            }\n"
	    "    };\n"
	    "}\n";
	char options[] = "style=allman, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, BracketsAttach_NamespaceClassIndent_Break)
{
	// comments should indent with namespaces and classes
	// style=java with broken brackets
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "/*\n"
	    " * comment0\n"
	    " */\n"
	    "class FooClass\n"
	    "{\n"
	    "public:\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "void foo()\n"
	    "{\n"
	    "/*\n"
	    " * comment2\n"
	    " */\n"
	    "}\n"
	    "};\n"
	    "}\n";
	char text[] =
	    "\nnamespace FooName {\n"
	    "    /*\n"
	    "     * comment0\n"
	    "     */\n"
	    "    class FooClass {\n"
	    "        public:\n"
	    "            /*\n"
	    "             * comment1\n"
	    "             */\n"
	    "            void foo() {\n"
	    "                /*\n"
	    "                 * comment2\n"
	    "                 */\n"
	    "            }\n"
	    "    };\n"
	    "}\n";
	char options[] = "style=java, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, BracketsAttach_NamespaceClassIndent_Attach)
{
	// comments should indent with namespaces and classes
	// style=java with attached brackets
	char textIn[] =
	    "\nnamespace FooName {\n"
	    "/*\n"
	    " * comment0\n"
	    " */\n"
	    "class FooClass {\n"
	    "public:\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "void foo() {\n"
	    "/*\n"
	    " * comment2\n"
	    " */\n"
	    "}\n"
	    "};\n"
	    "}\n";
	char text[] =
	    "\nnamespace FooName {\n"
	    "    /*\n"
	    "     * comment0\n"
	    "     */\n"
	    "    class FooClass {\n"
	    "        public:\n"
	    "            /*\n"
	    "             * comment1\n"
	    "             */\n"
	    "            void foo() {\n"
	    "                /*\n"
	    "                 * comment2\n"
	    "                 */\n"
	    "            }\n"
	    "    };\n"
	    "}\n";
	char options[] = "style=java, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, BracketsAttach_NamespaceClassIndent_RunIn)
{
	// comments should indent with namespaces and classes
	// style=java with run-in brackets
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "class FooClass\n"
	    "{\n"
	    "public:\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "void foo()\n"
	    "{/*\n"
	    "  * comment2\n"
	    "  */\n"
	    "}\n"
	    "};\n"
	    "}\n";
	char text[] =
	    "\nnamespace FooName {\n"
	    "    class FooClass {\n"
	    "        public:\n"
	    "            /*\n"
	    "             * comment1\n"
	    "             */\n"
	    "            void foo() {\n"
	    "                /*\n"
	    "                 * comment2\n"
	    "                 */\n"
	    "            }\n"
	    "    };\n"
	    "}\n";
	char options[] = "style=java, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, BracketsRunIn_NamespaceClassIndent_Break)
{
	// comments should indent with namespaces and classes
	// style=horstmann with broken brackets
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "class FooClass\n"
	    "{\n"
	    "public:\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "void foo()\n"
	    "{\n"
	    "/*\n"
	    " * comment2\n"
	    " */\n"
	    "}\n"
	    "};\n"
	    "}\n";
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "    class FooClass\n"
	    "    {   public:\n"
	    "            /*\n"
	    "             * comment1\n"
	    "             */\n"
	    "            void foo()\n"
	    "            {   /*\n"
	    "                 * comment2\n"
	    "                 */\n"
	    "            }\n"
	    "    };\n"
	    "}\n";
	char options[] = "style=horstmann, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, BracketsRunIn_NamespaceClassIndent_Attach)
{
	// comments should indent with namespaces and classes
	// style=horstmann with attached brackets
	char textIn[] =
	    "\nnamespace FooName {\n"
	    "class FooClass {\n"
	    "public:\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "void foo() {\n"
	    "/*\n"
	    " * comment2\n"
	    " */\n"
	    "}\n"
	    "};\n"
	    "}\n";
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "    class FooClass\n"
	    "    {   public:\n"
	    "            /*\n"
	    "             * comment1\n"
	    "             */\n"
	    "            void foo()\n"
	    "            {   /*\n"
	    "                 * comment2\n"
	    "                 */\n"
	    "            }\n"
	    "    };\n"
	    "}\n";
	char options[] = "style=horstmann, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, BracketsRunIn_NamespaceClassIndent_RunIn)
{
	// comments should indent with namespaces and classes
	// style=horstmann with run-in brackets
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "class FooClass\n"
	    "{\n"
	    "public:\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "void foo()\n"
	    "{/*\n"
	    "  * comment2\n"
	    "  */\n"
	    "}\n"
	    "};\n"
	    "}\n";
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "    class FooClass\n"
	    "    {   public:\n"
	    "            /*\n"
	    "             * comment1\n"
	    "             */\n"
	    "            void foo()\n"
	    "            {   /*\n"
	    "                 * comment2\n"
	    "                 */\n"
	    "            }\n"
	    "    };\n"
	    "}\n";
	char options[] = "style=horstmann, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, Namespace_Misc1)
{
	// comments should indent with namespaces
	// comments precede the brackets
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "class FooClass\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "{\n"
	    "public:\n"
	    "void foo()\n"
	    "/*\n"
	    " * comment2\n"
	    " */\n"
	    "{\n"
	    "}\n"
	    "};\n"
	    "}\n";
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "    class FooClass\n"
	    "    /*\n"
	    "     * comment1\n"
	    "     */\n"
	    "    {\n"
	    "    public:\n"
	    "        void foo()\n"
	    "        /*\n"
	    "         * comment2\n"
	    "         */\n"
	    "        {\n"
	    "        }\n"
	    "    };\n"
	    "}\n";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, Namespace_ClassMisc2)
{
	// comments should indent with namespaces and classes
	// comments precede the brackets
	char textIn[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "class FooClass\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "{\n"
	    "public:\n"
	    "void foo()\n"
	    "/*\n"
	    " * comment2\n"
	    " */\n"
	    "{\n"
	    "}\n"
	    "};\n"
	    "}\n";
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "    class FooClass\n"
	    "    /*\n"
	    "     * comment1\n"
	    "     */\n"
	    "    {\n"
	    "        public:\n"
	    "            void foo()\n"
	    "            /*\n"
	    "             * comment2\n"
	    "             */\n"
	    "            {\n"
	    "            }\n"
	    "    };\n"
	    "}\n";
	char options[] = "indent-namespaces, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, NestedClass_Misc3)
{
	// comments should indent with classes
	// comments precede the brackets
	char text[] =
	    "\nclass A\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "{\n"
	    "public:\n"
	    "    int foo1;\n"
	    "    class B\n"
	    "    /*\n"
	    "     * comment1\n"
	    "     */\n"
	    "    {\n"
	    "    public:\n"
	    "        int foo2;\n"
	    "        class C\n"
	    "        /*\n"
	    "         * comment1\n"
	    "         */\n"
	    "        {\n"
	    "        public:\n"
	    "        };\n"
	    "    };\n"
	    "};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, NestedClass_Misc4)
{
	// comments should indent with classes
	// comments precede the brackets in indented classes
	char text[] =
	    "\nclass A\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "{\n"
	    "    public:\n"
	    "        int foo1;\n"
	    "        class B\n"
	    "        /*\n"
	    "         * comment1\n"
	    "         */\n"
	    "        {\n"
	    "            public:\n"
	    "                int foo2;\n"
	    "                class C\n"
	    "                /*\n"
	    "                 * comment1\n"
	    "                 */\n"
	    "                {\n"
	    "                    public:\n"
	    "                };\n"
	    "        };\n"
	    "};\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, NamespaceClass_Misc5)
{
	// comments should indent with classes with inheritance
	// comments precede the brackets
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "class FooClass\n"
	    "    : public FooBase\n"
	    "/*\n"
	    " * comment1\n"
	    " */\n"
	    "{\n"
	    "public:\n"
	    "    void foo()\n"
	    "    /*\n"
	    "     * comment2\n"
	    "     */\n"
	    "    {\n"
	    "    }\n"
	    "};\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, NamespaceClass_Misc6)
{
	// comments should indent with classes with inheritance
	// comments precede the brackets
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "    class FooClass\n"
	    "        : public FooBase\n"
	    "    /*\n"
	    "     * comment1\n"
	    "     */\n"
	    "    {\n"
	    "    public:\n"
	    "        void foo()\n"
	    "        /*\n"
	    "         * comment2\n"
	    "         */\n"
	    "        {\n"
	    "        }\n"
	    "    };\n"
	    "}\n";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, BeforeStatement_Misc7)
{
	// comments before a statement should not be broken
	char text[] =
	    "\nvoid Foo()\n"
	    "{\n"
	    "    if (isBar) {\n"
	    "        /*bool result =*/ Bar();\n"
	    "        return;\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, NamespaceClass_Misc8)
{
	// line comments should indent with classes with inheritance
	// line comments precede the brackets
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "class FooClass\n"
	    "    : public FooBase\n"
	    "// comment1\n"
	    "{\n"
	    "public:\n"
	    "    void foo()\n"
	    "    // comment2\n"
	    "    {\n"
	    "    }\n"
	    "};\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, NamespaceClass_Misc9)
{
	// line comments should indent with classes with inheritance
	// line comments precede the brackets
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "    class FooClass\n"
	    "        : public FooBase\n"
	    "    // comment1\n"
	    "    {\n"
	    "    public:\n"
	    "        void foo()\n"
	    "        // comment2\n"
	    "        {\n"
	    "        }\n"
	    "    };\n"
	    "}\n";
	char options[] = "indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, LeadingSpaceCorrection1)
{
	// comment where the leading spaces need correction
	// will adjust the first line
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "       /*   EXEC SQL INSERT\n"
	    "    INTO   branch (branch_id, branch_name, branch_addr,\n"
	    "             branch_city, branch_phone)\n"
	    "    VALUES (:bid, :bname, :baddr:baddr_ind);\n"
	    "    */\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    /*   EXEC SQL INSERT\n"
	    "    INTO   branch (branch_id, branch_name, branch_addr,\n"
	    "          branch_city, branch_phone)\n"
	    "    VALUES (:bid, :bname, :baddr:baddr_ind);\n"
	    "    */\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, LeadingSpaceCorrection2)
{
	// comment where the leading spaces need correction
	// text has tabs
	// will adjust the first line
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "	   /*   EXEC SQL INSERT\n"
	    "	INTO   branch (branch_id, branch_name, branch_addr,\n"
	    "	         branch_city, branch_phone)\n"
	    "    VALUES (:bid, :bname, :baddr:baddr_ind);\n"
	    "	*/\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    /*   EXEC SQL INSERT\n"
	    "    INTO   branch (branch_id, branch_name, branch_addr,\n"
	    "             branch_city, branch_phone)\n"
	    "    VALUES (:bid, :bname, :baddr:baddr_ind);\n"
	    "    */\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Comment, LeadingSpaceCorrection3)
{
	// comment where the leading spaces need correction
	// and indent needs adjusting
	// will adjust the first line
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "         /*   EXEC SQL INSERT\n"
	    "      INTO   branch (branch_id, branch_name, branch_addr,\n"
	    "               branch_city, branch_phone)\n"
	    "      VALUES (:bid, :bname, :baddr:baddr_ind);\n"
	    "      */\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    /*   EXEC SQL INSERT\n"
	    "    INTO   branch (branch_id, branch_name, branch_addr,\n"
	    "          branch_city, branch_phone)\n"
	    "    VALUES (:bid, :bname, :baddr:baddr_ind);\n"
	    "    */\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle Continuation Lines
//----------------------------------------------------------------------------

TEST(Continuation, BracketsNone_Break)
{
	// continuation lines
	// brackets=none and input of broken brackets
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo1())\n"
	    "    {\n"
	    "        wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2())\n"
	    "    {\n"
	    "        wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Continuation, BracketsNone_Attach)
{
	// continuation lines
	// brackets=none and input of attached brackets
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo1()) {\n"
	    "        wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2()) {\n"
	    "        wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Continuation, BracketsNone_RunIn)
{
	// continuation lines
	// brackets=none and input of run-in brackets
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo1())\n"
	    "    {   wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2())\n"
	    "    {   wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Continuation, BracketsBreak_Break)
{
	// continuation lines
	// style=allman and input of broken brackets
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo1())\n"
	    "    {\n"
	    "        wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2())\n"
	    "    {\n"
	    "        wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Continuation, BracketsBreak_Attach)
{
	// continuation lines
	// style=allman and input of attached brackets
	char textIn[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo1()) {\n"
	    "        wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2()) {\n"
	    "        wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo1())\n"
	    "    {\n"
	    "        wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2())\n"
	    "    {\n"
	    "        wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Continuation, BracketsBreak_RunIn)
{
	// continuation lines
	// style=allman and input of run-in brackets
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo1())\n"
	    "    {   wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2())\n"
	    "    {   wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo1())\n"
	    "    {\n"
	    "        wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2())\n"
	    "    {\n"
	    "        wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Continuation, BracketsAttach_Break)
{
	// continuation lines
	// style=java and input of broken brackets
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo1())\n"
	    "    {\n"
	    "        wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2())\n"
	    "    {\n"
	    "        wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo1()) {\n"
	    "        wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2()) {\n"
	    "        wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Continuation, BracketsAttach_Attach)
{
	// continuation lines
	// style=java and input of attached brackets
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo1()) {\n"
	    "        wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2()) {\n"
	    "        wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Continuation, BracketsAttach_RunIn)
{
	// continuation lines
	// style=java and input of run-in brackets
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo1())\n"
	    "    {   wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2())\n"
	    "    {   wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo1()) {\n"
	    "        wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2()) {\n"
	    "        wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Continuation, BracketsRunIn_Break)
{
	// continuation lines
	// style=horstmann and input of broken brackets
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo1())\n"
	    "    {\n"
	    "        wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2())\n"
	    "    {\n"
	    "        wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo1())\n"
	    "    {   wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2())\n"
	    "    {   wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Continuation, BracketsRunIn_Attach)
{
	// continuation lines
	// style=horstmann and input of attached brackets
	char textIn[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo1()) {\n"
	    "        wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2()) {\n"
	    "        wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo1())\n"
	    "    {   wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2())\n"
	    "    {   wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Continuation, BracketsRunIn_RunIn)
{
	// continuation lines
	// style=horstmann and input of run-in brackets
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo1())\n"
	    "    {   wxPoint bar(Xpos,\n"
	    "                    Ypos);\n"
	    "    }\n"
	    "    if (isFoo2())\n"
	    "    {   wxPoint bar ( Xpos,\n"
	    "                      Ypos);\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Continuation, InlineTab1)
{
	// continuation lines
	// with inline tabs
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo1())\n"
	    "    {\n"
	    "        wxPointx	barx	( Xpos,\n"
	    "                              Ypos );\n"
	    "\n"
	    "        wxPointxx	barxx	( Xpos,\n"
	    "                              Ypos );\n"
	    "\n"
	    "        wxPointxxx	barxxx	( Xpos,\n"
	    "                              Ypos );\n"
	    "\n"
	    "        wxPointxxxx	barxxxx	( Xpos,\n"
	    "                              Ypos );\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Continuation, InlineTab2)
{
	// continuation lines with tabs after the paren
	// with inline tabs
	// NOTE: this all aligns when the quotes are removed
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    if (isFoo1())\n"
	    "    {\n"
	    "        wxPoint bar (	Xpos,\n"
	    "                        Ypos );\n"
	    "\n"
	    "        wxPoint barx (	Xpos,\n"
	    "                        Ypos );\n"
	    "\n"
	    "        wxPoint barxx (	Xpos,\n"
	    "                        Ypos );\n"
	    "\n"
	    "        wxPoint barxxx (	Xpos,\n"
	    "                            Ypos );\n"
	    "\n"
	    "        wxPoint barxx (		Xpos,\n"
	    "                            Ypos );\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle Continuation Lines with Tabs
//----------------------------------------------------------------------------

TEST(ContinuationTab, BracketsNone_Break)
{
	// continuation lines with tabs
	// brackets=none and input of broken brackets
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "	if (isFoo1())\n"
	    "	{\n"
	    "		wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2())\n"
	    "	{\n"
	    "		wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ContinuationTab, BracketsNone_Attach)
{
	// continuation lines with tabs
	// brackets=none and input of attached brackets
	char text[] =
	    "\nvoid foo() {\n"
	    "	if (isFoo1()) {\n"
	    "		wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2()) {\n"
	    "		wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ContinuationTab, BracketsNone_RunIn)
{
	// continuation lines with tabs
	// brackets=none and input of run-in brackets
	char text[] =
	    "\nvoid foo()\n"
	    "{	if (isFoo1())\n"
	    "	{	wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2())\n"
	    "	{	wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ContinuationTab, BracketsBreak_Break)
{
	// continuation lines with tabs
	// style=allman and input of broken brackets
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "	if (isFoo1())\n"
	    "	{\n"
	    "		wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2())\n"
	    "	{\n"
	    "		wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char options[] = "style=allman, indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ContinuationTab, BracketsBreak_Attach)
{
	// continuation lines with tabs
	// style=allman and input of attached brackets
	char textIn[] =
	    "\nvoid foo() {\n"
	    "	if (isFoo1()) {\n"
	    "		wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2()) {\n"
	    "		wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "    }\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "	if (isFoo1())\n"
	    "	{\n"
	    "		wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2())\n"
	    "	{\n"
	    "		wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char options[] = "style=allman, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ContinuationTab, BracketsBreak_RunIn)
{
	// continuation lines with tabs
	// style=allman and input of run-in brackets
	char textIn[] =
	    "\nvoid foo()\n"
	    "{	if (isFoo1())\n"
	    "	{	wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2())\n"
	    "	{	wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "	if (isFoo1())\n"
	    "	{\n"
	    "		wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2())\n"
	    "	{\n"
	    "		wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char options[] = "style=allman, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ContinuationTab, BracketsAttach_Break)
{
	// continuation lines with tabs
	// style=java and input of broken brackets
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "	if (isFoo1())\n"
	    "	{\n"
	    "		wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2())\n"
	    "	{\n"
	    "		wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "	if (isFoo1()) {\n"
	    "		wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2()) {\n"
	    "		wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char options[] = "style=java, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ContinuationTab, BracketsAttach_Attach)
{
	// continuation lines with tabs
	// style=java and input of attached brackets
	char text[] =
	    "\nvoid foo() {\n"
	    "	if (isFoo1()) {\n"
	    "		wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2()) {\n"
	    "		wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char options[] = "style=java, indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ContinuationTab, BracketsAttach_RunIn)
{
	// continuation lines with tabs
	// style=java and input of run-in brackets
	char textIn[] =
	    "\nvoid foo()\n"
	    "{	if (isFoo1())\n"
	    "	{	wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2())\n"
	    "	{	wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "	if (isFoo1()) {\n"
	    "		wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2()) {\n"
	    "		wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char options[] = "style=java, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ContinuationTab, BracketsRunIn_Break)
{
	// continuation lines with tabs
	// style=horstmann and input of broken brackets
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "	if (isFoo1())\n"
	    "	{\n"
	    "		wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2())\n"
	    "	{\n"
	    "		wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{	if (isFoo1())\n"
	    "	{	wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2())\n"
	    "	{	wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char options[] = "style=horstmann, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ContinuationTab, BracketsRunIn_Attach)
{
	// continuation lines with tabs
	// style=horstmann and input of attached brackets
	char textIn[] =
	    "\nvoid foo() {\n"
	    "	if (isFoo1()) {\n"
	    "		wxPoint bar(Xpos,\n"
	    "	            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2()) {\n"
	    "		wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{	if (isFoo1())\n"
	    "	{	wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2())\n"
	    "	{	wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char options[] = "style=horstmann, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ContinuationTab, BracketsRunIn_RunIn)
{
	// continuation lines with tabs
	// style=horstmann and input of run-in brackets
	char text[] =
	    "\nvoid foo()\n"
	    "{	if (isFoo1())\n"
	    "	{	wxPoint bar(Xpos,\n"
	    "		            Ypos);\n"
	    "	}\n"
	    "	if (isFoo2())\n"
	    "	{	wxPoint bar ( Xpos,\n"
	    "		              Ypos);\n"
	    "	}\n"
	    "}\n";
	char options[] = "style=horstmann, indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ContinuationTab, InlineTab1)
{
	// continuation lines with tabs
	// with inline tabs
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "	if (isFoo1())\n"
	    "	{\n"
	    "		wxPointx	barx	( Xpos,\n"
	    "		                      Ypos );\n"
	    "\n"
	    "		wxPointxx	barxx	( Xpos,\n"
	    "		                      Ypos );\n"
	    "\n"
	    "		wxPointxxx	barxxx	( Xpos,\n"
	    "		                      Ypos );\n"
	    "\n"
	    "		wxPointxxxx	barxxxx	( Xpos,\n"
	    "		                      Ypos );\n"
	    "	}\n"
	    "}\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ContinuationTab, InlineTab2)
{
	// continuation lines with tabs
	// with inline tabs after the paren
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "	if (isFoo1())\n"
	    "	{\n"
	    "		wxPoint bar (	Xpos,\n"
	    "		                Ypos );\n"
	    "\n"
	    "		wxPoint barx (	Xpos,\n"
	    "		                Ypos );\n"
	    "\n"
	    "		wxPoint barxx (	Xpos,\n"
	    "		                Ypos );\n"
	    "\n"
	    "		wxPoint barxxx (	Xpos,\n"
	    "		                    Ypos );\n"
	    "\n"
	    "		wxPoint barxx (		Xpos,\n"
	    "		                    Ypos );\n"
	    "	}\n"
	    "}\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ContinuationForceTab, InlineTab1)
{
	// continuation lines with force tabs
	// with inline tabs
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "	if (isFoo1())\n"
	    "	{\n"
	    "		wxPointx	barx	( Xpos,\n"
	    "							  Ypos );\n"
	    "\n"
	    "		wxPointxx	barxx	( Xpos,\n"
	    "							  Ypos );\n"
	    "\n"
	    "		wxPointxxx	barxxx	( Xpos,\n"
	    "							  Ypos );\n"
	    "\n"
	    "		wxPointxxxx	barxxxx	( Xpos,\n"
	    "							  Ypos );\n"
	    "	}\n"
	    "}\n";
	char options[] = "indent=force-tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ContinuationForceTab, InlineTab2)
{
	// continuation lines with force tabs
	// with inline tabs after the paren
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "	if (isFoo1())\n"
	    "	{\n"
	    "		wxPoint bar (	Xpos,\n"
	    "						Ypos );\n"
	    "\n"
	    "		wxPoint barx (	Xpos,\n"
	    "						Ypos );\n"
	    "\n"
	    "		wxPoint barxx (	Xpos,\n"
	    "						Ypos );\n"
	    "\n"
	    "		wxPoint barxxx (	Xpos,\n"
	    "							Ypos );\n"
	    "\n"
	    "		wxPoint barxx (		Xpos,\n"
	    "							Ypos );\n"
	    "	}\n"
	    "}\n";
	char options[] = "indent=force-tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// C++ operators << and >>
//----------------------------------------------------------------------------

TEST(AlignmentOperator, Cout)
{
	// Alignment of the operator<<
	char text[] =
	    "\nvoid foo(std::ostream& os)\n"
	    "{\n"
	    "    os << \"Foo\"\n"
	    "       << \"Bar\"\n"
	    "       << std::endl;\n"
	    "\n"
	    "    cout << \"Foo\"\n"
	    "         << \"Bar\"\n"
	    "         << std::endl;\n"
	    "\n"
	    "    helpText << wxT(\"text1\")\n"
	    "             << wxT(\"text2\")\n"
	    "             << wxT(\"text3\");\n"
	    "\n"
	    "    int i = 0;\n"
	    "    if (i)\n"
	    "        i = 0;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignmentOperator, Cin)
{
	// Alignment of the operator<<
	char text[] =
	    "\nvoid foo(std::istream& someinputstream)\n"
	    "{\n"
	    "    someinputstream >> \"Foo\"\n"
	    "                    >> \"Bar\"\n"
	    "                    >> std::endl;\n"
	    "\n"
	    "    cin >> \"Foo\"\n"
	    "        >> \"Bar\"\n"
	    "        >> std::endl;\n"
	    "\n"
	    "    int i = 0;\n"
	    "    if (i)\n"
	    "        i = 0;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignmentOperator, CoutBeginLine)
{
	// Alignment of the operator<< when it begins the line
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    Context->m_EventsConnectingCode\n"
	    "            << _T(\"Connect(\")\n"
	    "            << m_EventArray[i].Type\n"
	    "            << _T(\");\") << endl;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AlignmentOperator, Cout2)
{
	// Alignment of the operator<<
	char text[] =
	    "\nstd::ostream& operator<<(std::ostream& os)\n"
	    "{\n"
	    "    os << foo\n"
	    "       << std::endl;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle SQL
//----------------------------------------------------------------------------

TEST(SQL, Standard)
{
	// standard SQL statements
	char text[] =
	    "\nEXEC SQL INCLUDE sqlca;\n"
	    "\n"
	    "void Connect()\n"
	    "{\n"
	    "    EXEC SQL BEGIN DECLARE SECTION;\n"
	    "        char userid[64];\n"
	    "        char password[64];\n"
	    "        char *DBname = \"@ug\";\n"
	    "    EXEC SQL END DECLARE SECTION;\n"
	    "\n"
	    "    EXEC SQL CONECT :userid IDENTIFIED BY :password;\n"
	    "}\n"
	    "\n"
	    "void Insert_Branch()\n"
	    "{\n"
	    "    EXEC SQL INSERT\n"
	    "             INTO   branch (branch_id, branch_name, branch_addr,\n"
	    "                            branch_city, branch_phone)\n"
	    "             VALUES (:bid, :bname, :baddr:baddr_ind);\n"
	    "\n"
	    "    EXEC SQL COMMIT WORK;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(SQL, Comment)
{
	// SQL statements with comment
	char text[] =
	    "\nvoid Insert_Branch()\n"
	    "{\n"
	    "    EXEC SQL INSERT\n"
	    "             /*\n"
	    "              *\n"
	    "              */\n"
	    "             INTO   branch (branch_id, branch_name, branch_addr,\n"
	    "                            branch_city, branch_phone)\n"
	    "             VALUES (:bid, :bname, :baddr:baddr_ind);\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(SQL, LineComment)
{
	// SQL statements with line comment
	char text[] =
	    "\nvoid Insert_Branch()\n"
	    "{\n"
	    "    EXEC SQL INSERT\n"
	    "             //\n"
	    "             INTO   branch (branch_id, branch_name, branch_addr,\n"
	    "                            branch_city, branch_phone)\n"
	    "             VALUES (:bid, :bname, :baddr:baddr_ind);\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(SQL, NonIndentingTabs)
{
	// SQL statements with non-indenting tabs
	char textIn[] =
	    "\nvoid Insert_Branch()\n"
	    "{\n"
	    "  	 	  EXEC SQL INSERT\n"
	    "	           INTO   branch (branch_id, branch_name, branch_addr,\n"
	    "	 	  	   		  branch_city, branch_phone)\n"
	    "    	       VALUES (:bid, :bname, :baddr:baddr_ind);\n"
	    "}\n";
	char text[] =
	    "\nvoid Insert_Branch()\n"
	    "{\n"
	    "    EXEC SQL INSERT\n"
	    "         INTO   branch (branch_id, branch_name, branch_addr,\n"
	    "                branch_city, branch_phone)\n"
	    "         VALUES (:bid, :bname, :baddr:baddr_ind);\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(SQL, NonHangingIndent)
{
	// SQL statements with a non-hanging indent
	// should format as a block
	char textIn[] =
	    "\nvoid Insert_Branch()\n"
	    "{\n"
	    "          EXEC SQL INSERT\n"
	    "      INTO   branch (branch_id, branch_name, branch_addr,\n"
	    "             branch_city, branch_phone)\n"
	    "      VALUES (:bid, :bname, :baddr:baddr_ind);\n"
	    "}\n";
	char text[] =
	    "\nvoid Insert_Branch()\n"
	    "{\n"
	    "    EXEC SQL INSERT\n"
	    "    INTO   branch (branch_id, branch_name, branch_addr,\n"
	    "       branch_city, branch_phone)\n"
	    "    VALUES (:bid, :bname, :baddr:baddr_ind);\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(SQL, LowerCaseExtraSpaces)
{
	// SQL statements in lower case with extra spaces
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "      exec  sql   begin   declare   section;\n"
	    "      char userid[64];\n"
	    "      char password[64];\n"
	    "      exeC  SqL   End   Declare  Section;\n"
	    "\n"
	    "      Exec   Sql SELECT BLP_PIN_TYPE\n"
	    "                 INTO :m_Pin_Type;\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    exec  sql   begin   declare   section;\n"
	    "        char userid[64];\n"
	    "        char password[64];\n"
	    "    exeC  SqL   End   Declare  Section;\n"
	    "\n"
	    "    Exec   Sql SELECT BLP_PIN_TYPE\n"
	    "               INTO :m_Pin_Type;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(SQL, EndOfLine)
{
	// SQL statements with EXEC SQL at end of line
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    EXEC SQL\n"
	    "         SELECT BLP_PIN_TYPE\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(SQL, BreakAfterSemi)
{
	// SQL statements should break line after the semi-colon
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    {\n"
	    "        EXEC SQL SELECT BLP_PIN_TYPE,\n"
	    "             INTO :m_Pin_Type;}\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    {\n"
	    "        EXEC SQL SELECT BLP_PIN_TYPE,\n"
	    "             INTO :m_Pin_Type;\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(SQL, Switch)
{
	// SQL statements in switch
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "    case 1:\n"
	    "        EXEC SQL SELECT BLP_PIN_TYPE\n"
	    "             INTO :m_Pin_Type;\n"
	    "\n"
	    "    case 2:\n"
	    "    {\n"
	    "        EXEC SQL SELECT BLP_PIN_TYPE\n"
	    "             INTO :m_Pin_Type;\n"
	    "    }\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(SQL, SwitchIndentCase)
{
	// SQL statements in switch with indent case
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    switch (foo)\n"
	    "    {\n"
	    "    case 1:\n"
	    "        EXEC SQL SELECT BLP_PIN_TYPE\n"
	    "             INTO :m_Pin_Type;\n"
	    "\n"
	    "    case 2:\n"
	    "        {\n"
	    "            EXEC SQL SELECT BLP_PIN_TYPE\n"
	    "                 INTO :m_Pin_Type;\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "indent-cases";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(SQL, BracketsRunIn)
{
	// SQL statements in run-in brackets
	char text[] =
	    "\nvoid foo()\n"
	    "{   EXEC SQL SELECT BLP_PIN_TYPE\n"
	    "             INTO :m_Pin_Type;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(SQL, Sans)
{
	// not SQL statements (macros?)
	// SQL statements will not be changed
	char textIn[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    EXEC\n"
	    "        bar1();\n"
	    "    EXEC SQX\n"
	    "        bar2();\n"
	    "}\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    EXEC\n"
	    "    bar1();\n"
	    "    EXEC SQX\n"
	    "    bar2();\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle Assembler
//----------------------------------------------------------------------------

TEST(Assembler, Embedded1)
{
	// embedded assembler
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    asm (\"\n"
	    "         movl -4(%ebp), %eax	; comment1\n"
	    "         sarl %ebx				; comment2\n"
	    "         \");\n"
	    "\n"
	    "    if (foo()) {\n"
	    "        asm(\"int3\"); /*trap*/\n"
	    "    }\n"
	    "\n"
	    "    int data;\n"
	    "    asm volatile (\"mcr\t\" \"14, 0, %0, c1, c0\"::\"r\" (data));\n"
	    "\n"
	    "    if (bar())\n"
	    "    { asm(\"int3\"); }\n"
	    "}\n";
	char options[] = "keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Assembler, Embedded2)
{
	// embedded assembler
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    asm (\"sar1 %1\n"
	    "         movl %1, %0\": \"=r\"(res[i]) :\"r\" (res[i]), \"memory\");\n"
	    "\n"
	    "    __asm__ (\"sarl %0\"\n"
	    "             : \"=r\" (res[i]) :\"r\" (num[i]), \"r\" (num[i]): \"memory\");\n"
	    "\n"
	    "    asm (\"addl %%ebx, %%eax;\"\n"
	    "         : \"=a\" (add)\n"
	    "         : \"a\" (arg1), \"b\" (arg2) );\n"
	    "\n"
	    "    __asm__ (\"addl %%ebx, %%eax;\" : \"=a\" (add) : \"a\" (arg1), \"b\" (arg2));\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Assembler, MS1)
{
	// microsoft specific embedded assembler
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    _asm mov eax, fs:[0x8]\n"
	    "    __asm push edp\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Assembler, MS2)
{
	// microsoft specific embedded assembler
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    _asm {\n"
	    "        mov eax, fs:[0x8]\n"
	    "        mov dx, 0xD007\n"
	    "        out dx, al\n"
	    "    }\n"
	    "\n"
	    "    __asm {\n"
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

TEST(Assembler, NoParensOrSemiColons)
{
	// assembler
	char text[] =
	    "\nvoid FOO()\n"
	    "{\n"
	    "    __asm__ {\n"
	    "        emit 0Fh    // Store low  32-bits of counter in EAX.\n"
	    "        emit 31h    // Store high 32-bits of counter in EDX.\n"
	    "        ret\n"
	    "    }\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// AStyle Multiple Variables separated by commas
//----------------------------------------------------------------------------

TEST(MultipleVariableAssignments, Standard)
{
	// multiple assignments are aligned on the first variable
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bool bName  = false,\n"
	    "         bFile  = true,\n"
	    "         bSize  = true,\n"
	    "         bWidth = false;\n"
	    "\n"
	    "    m_x = (D*E - B*F) / G,\n"
	    "    m_y = (A*F - C*E) / G,\n"
	    "    m_z = (A*G - F*B) / G;\n"
	    "\n"
	    "    double rstep = Red() / size, rf = 0,\n"
	    "           gstep = Green() / size, gf = 0,\n"
	    "           bstep = Blue() / size, bf = 0;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariableAssignments, Comments)
{
	// multiple assignments are aligned on the first variable
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    bool bName   =  false,   // comment1\n"
	    "         bFile   =  true,    // comment2\n"
	    "         bSize   =  true,    // comment3\n"
	    "         bWidth  =  false;   // comment4\n"
	    "\n"
	    "    bool bName   =  false,   /* comment1 */\n"
	    "         bFile   =  true,    /* comment2 */\n"
	    "         bSize   =  true,    /* comment3 */\n"
	    "         bWidth  =  false;   /* comment4 */\n"
	    "\n"
	    "    bool bName   =  /* comment1 */ false,\n"
	    "         bFile   =  /* comment2 */  true,\n"
	    "         bSize   = true  /* comment3 */,\n"
	    "         bWidth  = false /* comment3 */;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariableAssignments, Sans)
{
	// these are not multiple assignments
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    // functions are not multiple assignments\n"
	    "    int code = GetCode(m_Header,\n"
	    "                       m_Code,\n"
	    "                       m_Language,\n"
	    "                       false);\n"
	    "\n"
	    "    // arrays are not multiple assignments\n"
	    "    bar[] = \"one\",\n"
	    "            \"two\";\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, Standard)
{
	// multiple variables are aligned on first variable
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    int var1,\n"
	    "        var2,   // comment1\n"
	    "        var3;   /* comment2 */\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, MultipleStatementsPerLine)
{
	// multiple variables with multiple statements per line
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    wxString m_bar1, m_bar2,\n"
	    "             m_bar3, m_bar4,\n"
	    "             m_bar5, m_bar6;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, MultipleSpacesToName)
{
	// multiple variables with multiple spaces before the name
	char text[] =
	    "\nstruct foo\n"
	    "{\n"
	    "    char   bl: 4,\n"
	    "           bh: 4;\n"
	    "};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, ClassHeader)
{
	// class headers are aligned on first variable
	// last line with brackets should be indented
	char text[] =
	    "\nclass ASBeautifier\n"
	    "    : protected ASResource1,\n"
	    "      protected ASResource2,\n"
	    "      protected ASBase {};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, ClassHeaderCommaFirst1)
{
	// "comma first" class headers are aligned on the colon
	char text[] =
	    "\nclass ASBeautifier\n"
	    "    : protected ASResource1\n"
	    "    ,  protected ASResource2\n"
	    "    ,  protected ASBase\n"
	    "{};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, ClassHeaderCommaFirst2)
{
	// "comma first" class headers are aligned on the colon
	char text[] =
	    "\nclass ASBeautifier\n"
	    "    : protected ASResource1\n"
	    "    ,  protected ASResource2\n"
	    "    ,  protected ASBase {};\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, ClassInitializer1)
{
	// class initializers are aligned on first variable
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : m_bar1(0),\n"
	    "      m_bar2(this, id),\n"
	    "      m_bar3(0)\n"
	    "{\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, ClassInitializer2)
{
	// class initializers are aligned on first variable
	// colon on previous line
	char text[] =
	    "\nFoo::Foo() :\n"
	    "    m_bar1(0),\n"
	    "    m_bar2(this, id),\n"
	    "    m_bar3(0)\n"
	    "{\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, ClassInitializer3)
{
	// class initializers are aligned on first variable
	// multiple variables per line
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : m_bar1(0), m_bar2(0),\n"
	    "      m_bar3(0), m_bar4(0), m_bar5(0),\n"
	    "      m_bar6(-100), m_bar7(50)\n"
	    "{\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, ClassInitializer4)
{
	// class initializers are aligned on first variable
	// comments after comma
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : m_FileGroups(*fgam), // comment\n"
	    "      m_pOrigFileGroups(fgam),\n"
	    "      m_LastListSelection(0)\n"
	    "{\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, ClassInitializer5)
{
	// class initializers are aligned on first variable
	// last line with brackets should be indented
	char text[] =
	    "\nFooBar::FooBar(int width = 1, int style = wxSOLID,\n"
	    "               int cap = wxCAP_ROUND)\n"
	    "    : m_bar1(0), m_bar2(0),\n"
	    "      m_bar3(0), m_bar4(0),\n"
	    "      m_bar5(0), m_bar6(NULL) {}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, ClassInitializer6)
{
	// class initializers are aligned on first variable
	// isInStatement should be reset for the initializer
	// it was NOT if the initializer followed an "extern" statement
	// m_bar(0) was aligned with the colon instead of the variable
	char text[] =
	    "\nextern \"C\" {\n"
	    "    int fubar_c();\n"
	    "}\n"
	    "\n"
	    "Fubar::Fubar(void)\n"
	    "    : m_foo(0),\n"
	    "      m_bar(0)\n"
	    "{\n"
	    "}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, ClassInitializer7)
{
	// class initializers are aligned on first variable
	// this EXPECT_TRUEs if the variables have been reset
	char text[] =
	    "\nFoo1::Foo1()\n"
	    "    : bar1(cmd),\n"
	    "      bar2(driver),\n"
	    "{}\n"
	    "\n"
	    "Foo2::Foo2()\n"
	    "    : bar3(branch),\n"
	    "      bar4(tree)\n"
	    "{}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, ClassInitializerCommaFirst1)
{
	// "comma first" class initializers are aligned on the colon
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : m_bar1(0)\n"
	    "    ,  m_bar2(this, id)\n"
	    "    ,  m_bar3(0)\n"
	    "{}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, ClassInitializerCommaFirst2)
{
	// "comma first" class initializers are aligned on the colon
	char text[] =
	    "\nFoo::Foo()\n"
	    "    : m_bar1(0),\n"
	    "    ,  m_bar2(this, id),\n"
	    "    ,  m_bar3(0) {}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, Misc1)
{
	// this EXPECT_TRUEs if the inStatementIndentStack is correctly popped
	char text[] =
	    "\nListBoxImpl::ListBoxImpl()\n"
	    "    : unicodeMode(false),\n"
	    "      desiredVisibleRows(5)\n"
	    "{\n"
	    "}\n"
	    "\n"
	    "void ListBoxImpl::Create (Window &parent,\n"
	    "                          int lineHeight_) {\n"
	    "    lineHeight =  lineHeight_;\n"
	    "}\n"
	    "\n"
	    "long Platform::SendScintilla(WindowID w,\n"
	    "                             unsigned long wParam,\n"
	    "                             long lParam) {\n"
	    "    wxScintilla* sci = (wxScintilla*)w;\n"
	    "    return sci->SendMsg(msg, wParam, lParam);\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(MultipleVariable, Misc2)
{
	// this EXPECT_TRUEs for various conditions in getInStatementIndentComma()
	char text[] =
	    "\nvoid foo()\n"
	    "{\n"
	    "    int\n"
	    "    var1\n"
	    "    ,\n"
	    "    var2;\n"
	    "}\n"
	    "\n"
	    "void foo()\n"
	    "{\n"
	    "    int\n"
	    "    var1,\n"
	    "    var2\n"
	    "    , var3;\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------
// Other Tests
//----------------------------------------------------------------------------

TEST(Other, VirginLineBrackets)
{
	// test bracket on second line
	// linux bracket should not attach
	char text[] =
	    "void Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo)\n"
	    "        bar();\n"
	    "}\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(Other, MaintainAssignmenPadding)
{
	// assignment and other padding should be maintained
	char text[] =
	    "void Foo()\n"
	    "{\n"
	    "    // align by =\n"
	    "    pointerAlignment       = PTR_ALIGN_NONE;\n"
	    "    shouldPadOperators     = false;\n"
	    "    shouldPadParensOutside = false;\n"
	    "\n"
	    "    // align by ==\n"
	    "    if (one           == STYLE_ALLMAN\n"
	    "            ||  three == STYLE_KR\n"
	    "            ||  five  == STYLE_WHITESMITH)\n"
	    "    {}\n"
	    "\n"
	    "    // align by m_ (and =)\n"
	    "    int    m_int    = 1;\n"
	    "    char   m_char   = 'x';\n"
	    "    string m_string = \"string\";\n"
	    "\n"
	    "    // align by period (and =)\n"
	    "    Environment.Exit      = 1;\n"
	    "    Console    .WriteLine = \"line\";\n"
	    "}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}


//----------------------------------------------------------------------------

}  // namespace
