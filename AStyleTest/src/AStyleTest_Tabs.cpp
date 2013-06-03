//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleTest.h"

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {

//-----------------------------------------------------------------------------
// AStyle Tab Options
//-----------------------------------------------------------------------------

TEST(Tabs, DefaultNone)
{
	// test default indent of 4 spaces per tab
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        bar();\n"
		"    }\n"
		"    else\n"
		"        anotherBar();\n"
		"}\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, Default)
{
	// test default indent of 4 spaces per tab
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        bar();\n"
		"    }\n"
		"    else\n"
		"        anotherBar();\n"
		"}\n";
	char options[] = "indent=spaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, DefaultShort)
{
	// test default indent of 4 spaces per tab
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        bar();\n"
		"    }\n"
		"    else\n"
		"        anotherBar();\n"
		"}\n";
	char options[] = "-s";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, Spaces_8)
{
	// test indent of 8 spaces per tab
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"        if (isFoo)\n"
		"        {\n"
		"                bar();\n"
		"        }\n"
		"        else\n"
		"                anotherBar();\n"
		"}\n";
	char options[] = "indent=spaces=8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, Spaces_Short8)
{
	// test indent of 8 spaces per tab
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"        if (isFoo)\n"
		"        {\n"
		"                bar();\n"
		"        }\n"
		"        else\n"
		"                anotherBar();\n"
		"}\n";
	char options[] = "s8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, Spaces_Invalid1)
{
	// test with an invalid indent
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"}\n";
	char options[] = "indent=spaces=x";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != NULL);
	delete [] textOut;
}

TEST(Tabs, Spaces_Invalid2)
{
	// test with an indent that is below minimum
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"}\n";
	char options[] = "indent=spaces=1";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != NULL);
	delete [] textOut;
}

TEST(Tabs, Spaces_Invalid3)
{
	// test with an indent that is above maximum
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"}\n";
	char options[] = "indent=spaces=21";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != NULL);
	delete [] textOut;
}

TEST(Tabs, Spaces_CSharpLambda)
{
	// test C# with a lambda indent
	// TODO: doesn't work, should be indented like textIn
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
		"}\n";
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
		"}\n";
	char options[] = "indent=spaces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, Tab_Default)
{
	// test default tab indent of 4 spaces per tab
	// the '&& isBar' line will be indented with 2 tab widths or 8 spaces
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"	if (isFoo\n"
		"	        && isBar)\n"
		"	{\n"
		"		bar();\n"
		"	}\n"
		"	else\n"
		"		anotherBar();\n"
		"}\n";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, Tab_DefaultShort)
{
	// test default tab indent of 4 spaces per tab
	// the '&& isBar' line will be indented with 2 tab widths or 8 spaces
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"	if (isFoo\n"
		"	        && isBar)\n"
		"	{\n"
		"		bar();\n"
		"	}\n"
		"	else\n"
		"		anotherBar();\n"
		"}\n";
	char options[] = "t";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, Tab_8)
{
	// test tab indent of 8 spaces per tab
	// the '&& isBar' line will be indented with 2 tab widths or 16 spaces
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"	if (isFoo\n"
		"	                && isBar)\n"
		"	{\n"
		"		bar();\n"
		"	}\n"
		"	else\n"
		"		anotherBar();\n"
		"}\n";
	char options[] = "indent=tab=8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, Tab_Short8)
{
	// test tab indent of 8 spaces per tab
	// the '&& isBar' line will be indented with 2 tab widths or 16 spaces
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"	if (isFoo\n"
		"	                && isBar)\n"
		"	{\n"
		"		bar();\n"
		"	}\n"
		"	else\n"
		"		anotherBar();\n"
		"}\n";
	char options[] = "t8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, Tab_Invalid1)
{
	// test with an invalid indent
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"}\n";
	char options[] = "indent=tab=x";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != NULL);
	delete [] textOut;
}

TEST(Tabs, Tab_Invalid2)
{
	// test with an indent that is below minimum
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"}\n";
	char options[] = "indent=tab=1";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != NULL);
	delete [] textOut;
}

TEST(Tabs, Tab_Invalid3)
{
	// test with an indent that is above maximum
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"}\n";
	char options[] = "indent=tab=21";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != NULL);
	delete [] textOut;
}

TEST(Tabs, Tab_CSharpLambda)
{
	// test C# with a lambda indent
	// TODO: doesn't work, should be indented like textIn
	char textIn[] =
		"\nvoid UpdateErrorList(IEnumerable<CompilerError> errors)\n"
		"{\n"
		"	Dispatcher.Invoke(\n"
		"	    (Action)(\n"
		"	        () =>\n"
		"	        {\n"
		"		        var tasks = errors.Select(error => new Task()).ToList();\n"
		"		        if (tasks.Count > 0)\n"
		"		        {\n"
		"			        TaskService.ClearExceptCommentTasks();\n"
		"			        TaskService.AddRange(tasks);\n"
		"		        }\n"
		"	        }\n"
		"	    )\n"
		"	);\n"
		"}\n";
	char text[] =
		"\nvoid UpdateErrorList(IEnumerable<CompilerError> errors)\n"
		"{\n"
		"	Dispatcher.Invoke(\n"
		"	    (Action)(\n"
		"	        () =>\n"
		"	{\n"
		"		var tasks = errors.Select(error => new Task()).ToList();\n"
		"		if (tasks.Count > 0)\n"
		"		{\n"
		"			TaskService.ClearExceptCommentTasks();\n"
		"			TaskService.AddRange(tasks);\n"
		"		}\n"
		"	}\n"
		"	    )\n"
		"	);\n"
		"}\n";
	char options[] = "indent=tab, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTab_Default)
{
	// test default force tab indent of 4 spaces per tab
	// the '&& isBar' line will be indented with 2 tabs instead of 8 spaces
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"	if (isFoo\n"
		"			&& isBar)\n"
		"	{\n"
		"		bar();\n"
		"	}\n"
		"	else\n"
		"		anotherBar();\n"
		"}\n";
	char options[] = "indent=force-tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTab_DefaultShort)
{
	// test default force tab indent of 4 spaces per tab
	// the '&& isBar' line will be indented with 2 tabs instead of 8 spaces
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"	if (isFoo\n"
		"			&& isBar)\n"
		"	{\n"
		"		bar();\n"
		"	}\n"
		"	else\n"
		"		anotherBar();\n"
		"}\n";
	char options[] = "-T";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTab_8)
{
	// test default force tab indent of 8 spaces per tab
	// the result of this test is the same as the default option
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"	if (isFoo\n"
		"			&& isBar)\n"
		"	{\n"
		"		bar();\n"
		"	}\n"
		"	else\n"
		"		anotherBar();\n"
		"}\n";
	char options[] = "indent=force-tab=8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTab_Short8)
{
	// test default force tab indent of 8 spaces per tab
	// the result of this test is the same as the default option
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"	if (isFoo\n"
		"			&& isBar)\n"
		"	{\n"
		"		bar();\n"
		"	}\n"
		"	else\n"
		"		anotherBar();\n"
		"}\n";
	char options[] = "T8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTab_Invalid1)
{
	// test with an invalid indent
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"}\n";
	char options[] = "indent=force-tab=x";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != NULL);
	delete [] textOut;
}

TEST(Tabs, ForceTab_Invalid2)
{
	// test with an indent that is below minimum
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"}\n";
	char options[] = "indent=force-tab=1";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != NULL);
	delete [] textOut;
}

TEST(Tabs, ForceTab_Invalid3)
{
	// test with an indent that is above maximum
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"}\n";
	char options[] = "indent=force-tab=21";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = AStyleMain(text, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut != NULL);
	delete [] textOut;
}

TEST(Tabs, ForceTab_CSharpLambda)
{
	// test C# with a lambda indent
	// TODO: doesn't work, should be indented like textIn
	char textIn[] =
		"\nvoid UpdateErrorList(IEnumerable<CompilerError> errors)\n"
		"{\n"
		"	Dispatcher.Invoke(\n"
		"		(Action)(\n"
		"			() =>\n"
		"			{\n"
		"				var tasks = errors.Select(error => new Task()).ToList();\n"
		"				if (tasks.Count > 0)\n"
		"				{\n"
		"					TaskService.ClearExceptCommentTasks();\n"
		"					TaskService.AddRange(tasks);\n"
		"				}\n"
		"			}\n"
		"		)\n"
		"	);\n"
		"}\n";
	char text[] =
		"\nvoid UpdateErrorList(IEnumerable<CompilerError> errors)\n"
		"{\n"
		"	Dispatcher.Invoke(\n"
		"		(Action)(\n"
		"			() =>\n"
		"	{\n"
		"		var tasks = errors.Select(error => new Task()).ToList();\n"
		"		if (tasks.Count > 0)\n"
		"		{\n"
		"			TaskService.ClearExceptCommentTasks();\n"
		"			TaskService.AddRange(tasks);\n"
		"		}\n"
		"	}\n"
		"		)\n"
		"	);\n"
		"}\n";
	char options[] = "indent=force-tab, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTabX_Default)
{
	// Test force-tab with the default tab-size of 8 spaces
	// and the default indent of 4 spaces.
	// The indents will be mixed tabs and spaces.
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo\n"
		"	    && isBar)\n"
		"    {\n"
		"	bar();\n"
		"    }\n"
		"    else\n"
		"	anotherBar();\n"
		"}\n";
	char options[] = "indent=force-tab-x";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTabX_DefaultShort)
{
	// Test force-tab short option with the default tab-size of 8 spaces
	// and the default indent of 4 spaces.
	// The indents will be mixed tabs and spaces.
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo\n"
		"	    && isBar)\n"
		"    {\n"
		"	bar();\n"
		"    }\n"
		"    else\n"
		"	anotherBar();\n"
		"}\n";
	char options[] = "-xT";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTabX_6)
{
	// Test option with a tab length of 6 spaces
	// and a default indentof 3 spaces.
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"   if (isFoo\n"
		"	   && isBar)\n"
		"   {\n"
		"	bar();\n"
		"   }\n"
		"   else\n"
		"	anotherBar();\n"
		"}\n";
	char options[] = "indent=force-tab-x=6, indent=force-tab=3";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTabX_Short6)
{
	// Test short option with a tab length of 6 spaces
	// and a default indentof 3 spaces.
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"   if (isFoo\n"
		"	   && isBar)\n"
		"   {\n"
		"	bar();\n"
		"   }\n"
		"   else\n"
		"	anotherBar();\n"
		"}\n";
	char options[] = "xT6, T3";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTabX_Indent1)
{
	// Test force-tab with tab-size of 4 spaces
	// and an indent size of 8 spaces.
	// There will be two tabs per indent.
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"		if (isFoo\n"
		"						&& isBar)\n"
		"		{\n"
		"				bar();\n"
		"		}\n"
		"		else\n"
		"				anotherBar();\n"
		"}\n";
	char options[] = "indent=force-tab-x=4, indent=force-tab=8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTabX_Indent2)
{
	// Test force-tab with tab-size of 4 spaces
	// and an indent size of 8 spaces.
	// There will be two tabs per indent.
	// The options are reversed from above. Should still work.
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"		if (isFoo\n"
		"						&& isBar)\n"
		"		{\n"
		"				bar();\n"
		"		}\n"
		"		else\n"
		"				anotherBar();\n"
		"}\n";
	char options[] = ", indent=force-tab=8, indent=force-tab-x=4";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTabX_Indent3)
{
	// Test force-tab with tab-size of 6 spaces
	// and an indent size of 4 spaces.
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"    if (isFoo\n"
		"		&& isBar)\n"
		"    {\n"
		"	  bar();\n"
		"    }\n"
		"    else\n"
		"	  anotherBar();\n"
		"}\n";
	char options[] = "indent=force-tab-x=6, indent=force-tab=4";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTabX_Indent4)
{
	// Test force-tab with tab-size of 4 spaces
	// and an indent size of 6 spaces.
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{\n"
		"	  if (isFoo\n"
		"				  && isBar)\n"
		"	  {\n"
		"			bar();\n"
		"	  }\n"
		"	  else\n"
		"			anotherBar();\n"
		"}\n";
	char options[] = "indent=force-tab-x=4, indent=force-tab=6";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTabX_Horstmann1)
{
	// Test force-tab option with Horstmann brackets.
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{   if (isFoo\n"
		"	    && isBar)\n"
		"    {   bar();\n"
		"    }\n"
		"    else\n"
		"	anotherBar();\n"
		"}\n";
	char options[] = "indent=force-tab-x, style=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTabX_Horstmann2)
{
	// Test force-tab option with Horstmann brackets.
	// A Comment in a switch statement requires 2 indents.
	char text[] =
		"\nvoid Foo()\n"
		"{   switch (foo)\n"
		"    {	// comment1\n"
		"	case 1:\n"
		"	    a += 1;\n"
		"	    break;\n"
		"    }\n"
		"}\n";
	char options[] = "indent-switches, indent=force-tab-x, style=horstmann";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTabX_Horstmann3)
{
	// Test force-tab option with Horstmann brackets
	// with a tab-size of 4 spaces and an indent size of 8 spaces.
	// There will be two tabs per indent.
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{		if (isFoo\n"
		"						&& isBar)\n"
		"		{		bar();\n"
		"		}\n"
		"		else\n"
		"				anotherBar();\n"
		"}\n";
	char options[] = "style=horstmann, indent=force-tab-x=4, indent=force-tab=8";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Tabs, ForceTabX_Horstmann4)
{
	// Test force-tab option with Horstmann brackets
	// with atab-size of 6 spaces and an indent size of 4 spaces.
	char text[] =
		"\nvoid Foo(bool isFoo)\n"
		"{   if (isFoo\n"
		"		&& isBar)\n"
		"    {   bar();\n"
		"    }\n"
		"    else\n"
		"	  anotherBar();\n"
		"}\n";
	char options[] = "style=horstmann, indent=force-tab-x=6, indent=force-tab=4";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-----------------------------------------------------------------------------
// AStyle Attach Namespaces Option
//-----------------------------------------------------------------------------

TEST(AttachNamespaces, LongOption)
{
	// test attach namespaces long option
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"}";
	char text[] =
		"\nnamespace FooName {\n"
		"\n"
		"}";
	char options[] = "attach-namespaces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachNamespaces, ShortOption)
{
	// test attach namespaces short option
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"}";
	char text[] =
		"\nnamespace FooName {\n"
		"\n"
		"}";
	char options[] = "-xn";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachNamespaces, BreakBrackets)
{
	// test attach namespaces with break brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"}";
	char text[] =
		"\nnamespace FooName {\n"
		"\n"
		"}";
	char options[] = "attach-namespaces, brackets=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachNamespaces, AttachBrackets)
{
	// test attach namespaces with attach brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"}";
	char text[] =
		"\nnamespace FooName {\n"
		"\n"
		"}";
	char options[] = "attach-namespaces, brackets=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachNamespaces, LinuxBrackets)
{
	// test attach namespaces with linux brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"}";
	char text[] =
		"\nnamespace FooName {\n"
		"\n"
		"}";
	char options[] = "attach-namespaces, brackets=linux";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachNamespaces, StroustrupBrackets)
{
	// test attach namespaces with stroustrup brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"}";
	char text[] =
		"\nnamespace FooName {\n"
		"\n"
		"}";
	char options[] = "attach-namespaces, brackets=stroustrup";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachNamespaces, RunInBrackets)
{
	// test attach namespaces with run-in brackets
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"}";
	char text[] =
		"\nnamespace FooName {\n"
		"\n"
		"}";
	char options[] = "attach-namespaces, brackets=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachNamespaces, NestedNamespace)
{
	// test attach namespaces with nested namespaces
	char textIn[] =
		"\nnamespace A\n"
		"{\n"
		"namespace B\n"
		"{\n"
		"namespace C\n"
		"{\n"
		"}\n"
		"}\n"
		"}\n";
	char text[] =
		"\nnamespace A {\n"
		"namespace B {\n"
		"namespace C {\n"
		"}\n"
		"}\n"
		"}\n";
	char options[] = "attach-namespaces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachNamespaces, SharpNamespace)
{
	// test attach namespaces with nested namespaces
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"}";
	char text[] =
		"\nnamespace FooName {\n"
		"}";
	char options[] = "attach-namespaces, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

//-----------------------------------------------------------------------------
// AStyle Attach Classes Option
//-----------------------------------------------------------------------------

TEST(AttachClasses, LongOption)
{
	// test attach classes long option
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"};";
	char text[] =
		"\nclass FooClass {\n"
		"};";
	char options[] = "attach-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachClasses, ShortOption)
{
	// test attach classes short option
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"};";
	char text[] =
		"\nclass FooClass {\n"
		"};";
	char options[] = "-xc";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachClasses, BreakBrackets)
{
	// test attach classes with break brackets
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"};";
	char text[] =
		"\nclass FooClass {\n"
		"};";
	char options[] = "attach-classes, brackets=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachClasses, AttachBrackets)
{
	// test attach classes with attach brackets
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"};";
	char text[] =
		"\nclass FooClass {\n"
		"};";
	char options[] = "attach-classes, brackets=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachClasses, LinuxBrackets)
{
	// test attach classes with linux brackets
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"};";
	char text[] =
		"\nclass FooClass {\n"
		"};";
	char options[] = "attach-classes, brackets=linux";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachClasses, StroustrupBrackets)
{
	// test attach classes with stroustrup brackets
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"};";
	char text[] =
		"\nclass FooClass {\n"
		"};";
	char options[] = "attach-classes, brackets=stroustrup";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachClasses, RunInBrackets)
{
	// test attach classes with run-in brackets
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"};";
	char text[] =
		"\nclass FooClass {\n"
		"};";
	char options[] = "attach-classes, brackets=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachClasses, NestedClasses)
{
	// test attach classes with nested classes
	char textIn[] =
		"\nclass A\n"
		"{\n"
		"class B\n"
		"{\n"
		"class C\n"
		"{\n"
		"};\n"
		"};\n"
		"};\n";
	char text[] =
		"\nclass A {\n"
		"    class B {\n"
		"        class C {\n"
		"        };\n"
		"    };\n"
		"};\n";
	char options[] = "attach-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachClasses, AttachNamespaces)
{
	// test attach classes with attach namespaces
	char textIn[] =
		"\nnamespace FooName\n"
		"{\n"
		"class  FooClass\n"
		"{\n"
		"};\n"
		"};\n";
	char text[] =
		"\nnamespace FooName {\n"
		"class  FooClass {\n"
		"};\n"
		"};\n";
	char options[] = "attach-classes, attach-namespaces";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachClasses, JavaClass)
{
	// test attach classes with a Java class
	char textIn[] =
		"\npublic class FooClass\n"
		"{\n"
		"}\n";
	char text[] =
		"\npublic class FooClass {\n"
		"}\n";
	char options[] = "attach-classes, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachClasses, SharpClass)
{
	// test attach classes with a C# class
	char textIn[] =
		"\npublic class FooClass\n"
		"{\n"
		"}\n";
	char text[] =
		"\npublic class FooClass {\n"
		"}\n";
	char options[] = "attach-classes, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachClasses, SharpInterface)
{
	// test attach classes with a C# interface
	char textIn[] =
		"public interface FooInterface\n"
		"{\n"
		"}";
	char text[] =
		"public interface FooInterface {\n"
		"}";
	char options[] = "attach-classes, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

//-----------------------------------------------------------------------------
// AStyle Attach Inlines Option
//-----------------------------------------------------------------------------

TEST(AttachInlines, LongOption)
{
	// test attach inlines long option
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"    bool Foo(char ch)\n"
		"    {\n"
		"        if (isFoo1(ch))\n"
		"        {\n"
		"            if (isFoo2(ch))\n"
		"            {\n"
		"                return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"    bool Foo(char ch) {\n"
		"        if (isFoo1(ch)) {\n"
		"            if (isFoo2(ch)) {\n"
		"                return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"};";
	char options[] = "attach-inlines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachInlines, ShortOption)
{
	// test attach inlines short option
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"    bool Foo(char ch)\n"
		"    {\n"
		"        if (isFoo1(ch))\n"
		"        {\n"
		"            if (isFoo2(ch))\n"
		"            {\n"
		"                return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"    bool Foo(char ch) {\n"
		"        if (isFoo1(ch)) {\n"
		"            if (isFoo2(ch)) {\n"
		"                return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"};";
	char options[] = "-xl";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachInlines, BreakBrackets)
{
	// test attach inlines with break brackets
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"    bool Foo(char ch)\n"
		"    {\n"
		"        if (isFoo1(ch))\n"
		"        {\n"
		"            if (isFoo2(ch))\n"
		"            {\n"
		"                return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"    bool Foo(char ch) {\n"
		"        if (isFoo1(ch)) {\n"
		"            if (isFoo2(ch)) {\n"
		"                return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"};";
	char options[] = "attach-inlines, brackets=break";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachInlines, AttachBrackets)
{
	// test attach inlines with attach brackets
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"    bool Foo(char ch)\n"
		"    {\n"
		"        if (isFoo1(ch))\n"
		"        {\n"
		"            if (isFoo2(ch))\n"
		"            {\n"
		"                return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"};";
	char text[] =
		"\nclass FooClass {\n"
		"    bool Foo(char ch) {\n"
		"        if (isFoo1(ch)) {\n"
		"            if (isFoo2(ch)) {\n"
		"                return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"};";
	char options[] = "attach-inlines, brackets=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachInlines, LinuxBrackets)
{
	// test attach inlines with linux brackets
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"    bool Foo(char ch)\n"
		"    {\n"
		"        if (isFoo1(ch))\n"
		"        {\n"
		"            if (isFoo2(ch))\n"
		"            {\n"
		"                return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"    bool Foo(char ch) {\n"
		"        if (isFoo1(ch)) {\n"
		"            if (isFoo2(ch)) {\n"
		"                return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"};";
	char options[] = "attach-inlines, brackets=linux";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachInlines, StroustrupBrackets)
{
	// test attach inlines with stroustrup brackets
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"    bool Foo(char ch)\n"
		"    {\n"
		"        if (isFoo1(ch))\n"
		"        {\n"
		"            if (isFoo2(ch))\n"
		"            {\n"
		"                return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"};";
	char text[] =
		"\nclass FooClass {\n"
		"    bool Foo(char ch) {\n"
		"        if (isFoo1(ch)) {\n"
		"            if (isFoo2(ch)) {\n"
		"                return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"};";
	char options[] = "attach-inlines, brackets=stroustrup";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachInlines, RunInBrackets)
{
	// test attach inlines with run-in brackets
	// run-in brackets should NOT be attached
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"    bool Foo(char ch)\n"
		"    {\n"
		"        if (isFoo1(ch))\n"
		"        {\n"
		"            if (isFoo2(ch))\n"
		"            {\n"
		"                return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{   bool Foo(char ch)\n"
		"    {   if (isFoo1(ch))\n"
		"        {   if (isFoo2(ch))\n"
		"            {   return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"};";
	char options[] = "attach-inlines, brackets=run-in";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachInlines, StructInClass)
{
	// test attach inlines with a struct in a class
	// the brackets are attached
	char textIn[] =
		"\nclass FooClass\n"
		"{\n"
		"    struct switchVariables\n"
		"    {\n"
		"        int  switchBracketCount;\n"
		"        int  Foo()\n"
		"        {\n"
		"            bool unindentCase;\n"
		"        }\n"
		"    }\n"
		"};";
	char text[] =
		"\nclass FooClass\n"
		"{\n"
		"    struct switchVariables\n"
		"    {\n"
		"        int  switchBracketCount;\n"
		"        int  Foo() {\n"
		"            bool unindentCase;\n"
		"        }\n"
		"    }\n"
		"};";
	char options[] = "attach-inlines";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachInlines, JavaClass)
{
	// test attach inlines with a Java class
	// Java class should NOT be changed
	char text[] =
		"\npublic class FooClass\n"
		"{\n"
		"    public bool Foo(char ch)\n"
		"    {\n"
		"        if (isFoo1(ch))\n"
		"        {\n"
		"            if (isFoo2(ch))\n"
		"            {\n"
		"                return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"}";
	char options[] = "attach-inlines, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(AttachInlines, SharpClass)
{
	// test attach inlines with a C# class
	// C# class should NOT be changed
	char text[] =
		"\npublic class FooClass\n"
		"{\n"
		"    public bool Foo(char ch)\n"
		"    {\n"
		"        if (isFoo1(ch))\n"
		"        {\n"
		"            if (isFoo2(ch))\n"
		"            {\n"
		"                return false;\n"
		"            }\n"
		"            return true;\n"
		"        }\n"
		"        return false;\n"
		"    }\n"
		"}";
	char options[] = "attach-inlines, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------

}  // namespace
