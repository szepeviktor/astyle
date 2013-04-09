//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleTest.h"

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace
{

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
//----------------------------------------------------------------------------

}  // namespace
