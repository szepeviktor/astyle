//-----------------------------------------------------------------------------
// AStyle C# Bracket Options
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include "AStyleTest.h"

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {

//-----------------------------------------------------------------------------
// AStyle Objective-C Bracket Options
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// AStyle Objective-C Default Bracket Options
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// AStyle Objective-C Break Bracket Options
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// AStyle Objective-C Attach Bracket Options
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// AStyle Objective-C Linux Bracket Options
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// AStyle Objective-C RunIn Bracket Options
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// AStyle Objective-C Other Bracket Options
//-----------------------------------------------------------------------------

TEST(BracketsOtherObjC, Header)
{
	// test a header with Objective-C statements
	char text[] =
		"\n#include <Foundation/Foundation.h>\n"
		"\n"
		"@class FooClass;\n"
		"\n"
		"@interface Foo : NSObject\n"
		"{\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"}\n"
		"@property(retain)NSString* var3;\n"
		"\n"
		"-(void)method1;\n"
		"\n"
		"-(void)methodWithArg1:(NSString*)param1;\n"
		"\n"
		"+(void)methodWithArg2:(NSString*)param2;\n"
		"\n"
		"@end";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BracketsOtherObjC, MethodCallIndent)
{
	// test indent of method call containing a colon
	char text[] =
		"\n- (void) Foo\n"
		"{\n"
		"    NSString* homeDirectory = [NSString stringWithUTF8String: homeDirectoryChar];\n"
		"    NSString* projectPath = [NSString stringWithFormat: @\"%@/%@/%@\",\n"
		"                             homeDirectory, @\"Projects\", subPath];\n"
		"}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BracketsOtherObjC, NSExceptionMacros)
{
	// test indent of NSException macros NS_DURING and NS_HANDLER
	// tabs are used to check the continuation line indent
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"	NS_DURING\n"
		"	{\n"
		"		[[NSWorkspace sharedWorkspace] openFile: path\n"
		"		 withApplication: [node name]];\n"
		"	}\n"
		"	NS_HANDLER\n"
		"	{\n"
		"		NSRunAlertPanel(NSLocalizedString(@\"error\", @\"\"),\n"
		"		                [NSString stringWithFormat: @\"%@ %@!\"]);\n"
		"	}\n"
		"	NS_ENDHANDLER\n"
		"}";
	char options[] = "indent=tab";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(BracketsOtherObjC, OtherColonIndent)
{
	// test indent of other troublesome objects containing a colon
	char text[] =
		"\n- (void) Foo\n"
		"{\n"
		"    if (pathCompareSel == NULL) {\n"
		"        pathCompareSel = @selector(compare:);\n"
		"    }\n"
		"    if (initialized == NO) {\n"
		"        cutTitleSel = @selector(cutTitle:toFitWidth:);\n"
		"        cutTitle = (cutIMP)[self instanceMethodForSelector: cutTitleSel];\n"
		"    }\n"
		"    return (([paths count] > 0) ? [paths makeImmutableCopyOnFail: NO] : nil);\n"
		"}";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

//-----------------------------------------------------------------------------

}  // namespace
