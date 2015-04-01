//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleTest.h"

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {

//----------------------------------------------------------------------------
// AStyle Objective-C Styles
//----------------------------------------------------------------------------

struct ObjCStyleF : public Test
{
	string textStr;
	const char* textIn;

	ObjCStyleF()
	{
		textStr =
			"\n@interface Foo : NSObject {\n"
			"    NSString* var1;\n"
			"    NSString* var2;\n"
			"}\n"
			"@end\n"
			"\n"
			"@implementation Foo\n"
			"\n"
			"- (void) foo\n"
			"{\n"
			"    if (isFoo)\n"
			"    {\n"
			"        bar();\n"
			"    }\n"
			"}\n"
			"\n"
			"- (void) foo : (int) icon\n"
			"    ofSize : (int) size {\n"
			"    if (isFoo) {\n"
			"        bar();\n"
			"    }\n"
			"}\n"
			"\n"
			"@end\n";
		textIn = textStr.c_str();
	}
};

TEST_F(ObjCStyleF, Default)
{
	// test default style option
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(textIn, textOut);
	delete [] textOut;
}

TEST_F(ObjCStyleF, Allman)
{
	// test allman style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"}\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        bar();\n"
		"    }\n"
		"}\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"    ofSize : (int) size\n"
		"{\n"
		"    if (isFoo)\n"
		"    {\n"
		"        bar();\n"
		"    }\n"
		"}\n"
		"\n"
		"@end\n";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(ObjCStyleF, Java)
{
	// test java style option
	char text[] =
		"\n@interface Foo : NSObject {\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"}\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"}\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"    ofSize : (int) size {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"}\n"
		"\n"
		"@end\n";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(ObjCStyleF, KR)
{
	// test k&r style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"}\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo\n"
		"{\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"}\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"    ofSize : (int) size\n"
		"{\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"}\n"
		"\n"
		"@end\n";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(ObjCStyleF, Stroustrup)
{
	// test stroustrup style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"     NSString* var1;\n"
		"     NSString* var2;\n"
		"}\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo\n"
		"{\n"
		"     if (isFoo) {\n"
		"          bar();\n"
		"     }\n"
		"}\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"     ofSize : (int) size\n"
		"{\n"
		"     if (isFoo) {\n"
		"          bar();\n"
		"     }\n"
		"}\n"
		"\n"
		"@end\n";
	char options[] = "style=stroustrup, indent=spaces=5";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(ObjCStyleF, Whitesmith)
{
	// test whitesmith style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"    {\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"    }\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo\n"
		"    {\n"
		"    if (isFoo)\n"
		"        {\n"
		"        bar();\n"
		"        }\n"
		"    }\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"    ofSize : (int) size\n"
		"    {\n"
		"    if (isFoo)\n"
		"        {\n"
		"        bar();\n"
		"        }\n"
		"    }\n"
		"\n"
		"@end\n";
	char options[] = "style=whitesmith";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(ObjCStyleF, VTK)
{
	// test vtk style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"}\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo\n"
		"{\n"
		"    if (isFoo)\n"
		"        {\n"
		"        bar();\n"
		"        }\n"
		"}\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"    ofSize : (int) size\n"
		"{\n"
		"    if (isFoo)\n"
		"        {\n"
		"        bar();\n"
		"        }\n"
		"}\n"
		"\n"
		"@end\n";
	char options[] = "style=vtk";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST_F(ObjCStyleF, Banner)
{
	// test banner style option
	char text[] =
		"\n@interface Foo : NSObject {\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"    }\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"        }\n"
		"    }\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"    ofSize : (int) size {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"        }\n"
		"    }\n"
		"\n"
		"@end\n";
	char options[] = "style=banner";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(ObjCStyleF, Gnu)
{
	// test gnu style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"  NSString* var1;\n"
		"  NSString* var2;\n"
		"}\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo\n"
		"{\n"
		"  if (isFoo)\n"
		"    {\n"
		"      bar();\n"
		"    }\n"
		"}\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"  ofSize : (int) size\n"
		"{\n"
		"  if (isFoo)\n"
		"    {\n"
		"      bar();\n"
		"    }\n"
		"}\n"
		"\n"
		"@end\n";
	char options[] = "style=gnu, indent=spaces=2";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(ObjCStyleF, Linux)
{
	// test linux style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"        NSString* var1;\n"
		"        NSString* var2;\n"
		"}\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo\n"
		"{\n"
		"        if (isFoo) {\n"
		"                bar();\n"
		"        }\n"
		"}\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"        ofSize : (int) size\n"
		"{\n"
		"        if (isFoo) {\n"
		"                bar();\n"
		"        }\n"
		"}\n"
		"\n"
		"@end\n";
	char options[] = "style=linux, indent=spaces=8";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(ObjCStyleF, Horstmann)
{
	// test horstmann style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{  NSString* var1;\n"
		"   NSString* var2;\n"
		"}\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo\n"
		"{  if (isFoo)\n"
		"   {  bar();\n"
		"   }\n"
		"}\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"   ofSize : (int) size\n"
		"{  if (isFoo)\n"
		"   {  bar();\n"
		"   }\n"
		"}\n"
		"\n"
		"@end\n";
	char options[] = "style=horstmann, indent=spaces=3";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(ObjCStyleF, 1TBS)
{
	// test 1tbs style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"}\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo\n"
		"{\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"}\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"    ofSize : (int) size\n"
		"{\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"}\n"
		"\n"
		"@end\n";
	char options[] = "style=1tbs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(ObjCStyleF, Google)
{
	// test google style option
	char text[] =
		"\n@interface Foo : NSObject {\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"}\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"}\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"    ofSize : (int) size {\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"}\n"
		"\n"
		"@end\n";
	char options[] = "style=google";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(ObjCStyleF, Pico)
{
	// test pico style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{   NSString* var1;\n"
		"    NSString* var2; }\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo\n"
		"{   if (isFoo)\n"
		"    {   bar(); } }\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"    ofSize : (int) size\n"
		"{   if (isFoo)\n"
		"    {   bar(); } }\n"
		"\n"
		"@end\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(ObjCStyleF, Lisp)
{
	// test lisp style option
	char text[] =
		"\n@interface Foo : NSObject {\n"
		"    NSString* var1;\n"
		"    NSString* var2; }\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo {\n"
		"    if (isFoo) {\n"
		"        bar(); } }\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"    ofSize : (int) size {\n"
		"    if (isFoo) {\n"
		"        bar(); } }\n"
		"\n"
		"@end\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Objective-C Align Method Colon
//-------------------------------------------------------------------------

TEST(ObjCAlignMethodColon, LongOption)
{
	// Test align-method-colon long option.
	char text[] =
		"\n"
		"- (BOOL)tableView:(NSTableView *)tableView\n"
		"       acceptDrop:(id <NSDraggingInfo>)info\n"
		"              row:(int)row";
	char options[] = "align-method-colon";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCAlignMethodColon, ShortOption)
{
	// Test align-method-colon short option.
	char text[] =
		"\n"
		"- (BOOL)tableView:(NSTableView *)tableView\n"
		"       acceptDrop:(id <NSDraggingInfo>)info\n"
		"              row:(int)row";
	char options[] = "-xM";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCAlignMethodColon, Headers)
{
	// Test align-method-colon headers.
	char text[] =
		"\n"
		"- (BOOL)tableView:(NSTableView *)tableView\n"
		"       acceptDrop:(id <NSDraggingInfo>)info\n"
		"              row:(int)row;\n"
		"\n"
		"- (id)tableView:(NSTableView *)aTableView\n"
		"    objectValueForTableColumn:(NSTableColumn *)aTableColumn\n"
		"            row:(int)rowIndex;\n"
		"\n"
		"- (BOOL)openFile:(NSString *)fullPath\n"
		" withApplication:(NSString *)appname\n"
		"   andDeactivate:(BOOL)flag;";
	char options[] = "align-method-colon";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCAlignMethodColon, MethodsBreak)
{
	// Test align-method-colon methods with broken brackets.
	char text[] =
		"\n"
		"- (BOOL)tableView:(NSTableView *)tableView\n"
		"       acceptDrop:(id <NSDraggingInfo>)info\n"
		"              row:(int)row\n"
		"{ }\n"
		"\n"
		"- (id)tableView:(NSTableView *)aTableView\n"
		"    objectValueForTableColumn:(NSTableColumn *)aTableColumn\n"
		"            row:(int)rowIndex\n"
		"{ }\n"
		"\n"
		"- (BOOL)openFile:(NSString *)fullPath\n"
		" withApplication:(NSString *)appname\n"
		"   andDeactivate:(BOOL)flag\n"
		"{ }\n";
	char options[] = "align-method-colon";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCAlignMethodColon, MethodsAttach)
{
	// Test align-method-colon methods with attached brackets.
	char text[] =
		"\n"
		"- (BOOL)tableView:(NSTableView *)tableView\n"
		"       acceptDrop:(id <NSDraggingInfo>)info\n"
		"              row:(int)row {\n"
		"}\n"
		"\n"
		"- (id)tableView:(NSTableView *)aTableView\n"
		"    objectValueForTableColumn:(NSTableColumn *)aTableColumn\n"
		"            row:(int)rowIndex {\n"
		"}\n"
		"\n"
		"- (BOOL)openFile:(NSString *)fullPath\n"
		" withApplication:(NSString *)appname\n"
		"   andDeactivate:(BOOL)flag {\n"
		"}\n";
	char options[] = "align-method-colon";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCAlignMethodColon, Define1)
{
	// Test align-method-colon methods with a define.
	// The define should not be formatted.
	char text[] =
		"\n"
		"#define BZ_UPDATE_CRC(crcVar,cha)            \\\n"
		"{                                            \\\n"
		"   crcVar = (crcVar << 8) ^                  \\\n"
		"            BZ2_crc32Table[(crcVar >> 24) ^  \\\n"
		"                           ((UChar)cha)];    \\\n"
		"}";
	char options[] = "align-method-colon";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCAlignMethodColon, Define2)
{
	// Test align-method-colon methods with an indented define.
	// The define should be formatted correctly.
	char textIn[] =
		"\n"
		"#define BZ_UPDATE_CRC(crcVar,cha)            \\\n"
		"{                                            \\\n"
		"   crcVar = (crcVar << 8) ^                  \\\n"
		"            BZ2_crc32Table[(crcVar >> 24) ^  \\\n"
		"                           ((UChar)cha)];    \\\n"
		"}";
	char text[] =
		"\n"
		"#define BZ_UPDATE_CRC(crcVar,cha)            \\\n"
		"    {                                            \\\n"
		"        crcVar = (crcVar << 8) ^                  \\\n"
		"                 BZ2_crc32Table[(crcVar >> 24) ^  \\\n"
		"                                ((UChar)cha)];    \\\n"
		"    }";
	char options[] = "align-method-colon, indent-preproc-define";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Objective-C Pad Method Prefix
//-------------------------------------------------------------------------

TEST(ObjCPadMethodPrefix, LongOption)
{
	// Test pad method prefix long option.
	char textIn[] =
		"\n"
		"-(void)Foo1;\n"
		"+ (void)Foo2;\n"
		"-    (void)Foo3;\n"
		"\n"
		"-(void)Foo4\n"
		"{ }";
	char text[] =
		"\n"
		"- (void)Foo1;\n"
		"+ (void)Foo2;\n"
		"- (void)Foo3;\n"
		"\n"
		"- (void)Foo4\n"
		"{ }";
	char options[] = "pad-method-prefix";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodPrefix, ShortOption)
{
	// Test pad method prefix short option.
	char textIn[] =
		"\n"
		"-(void)Foo1;\n"
		"+ (void)Foo2;\n"
		"-    (void)Foo3;\n"
		"\n"
		"-(void)Foo4\n"
		"{ }";
	char text[] =
		"\n"
		"- (void)Foo1;\n"
		"+ (void)Foo2;\n"
		"- (void)Foo3;\n"
		"\n"
		"- (void)Foo4\n"
		"{ }";
	char options[] = "-xQ";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodPrefix, UnPadMethodPrefix)
{
	// Test objective-c with pad-method-prefix and unpad-method-prefix.
	// The result should be pad-method-prefix.
	char textIn[] =
		"\n"
		"-(void)Foo1;\n"
		"+ (void)Foo2;\n"
		"-    (void)Foo3;\n"
		"\n"
		"-(void)Foo4\n"
		"{ }";
	char text[] =
		"\n"
		"- (void)Foo1;\n"
		"+ (void)Foo2;\n"
		"- (void)Foo3;\n"
		"\n"
		"- (void)Foo4\n"
		"{ }";
	char options[] = "pad-method-prefix, unpad-method-prefix";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodPrefix, SansPadUnPad)
{
	// Test objective-c with no method prefix option.
	// The result should be no change.
	char text[] =
		"\n"
		"-(void)Foo1;\n"
		"+ (void)Foo2;\n"
		"-    (void)Foo3;\n"
		"\n"
		"-(void)Foo4\n"
		"{ }";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodPrefix, Comments)
{
	// Test pad method prefix with comments.
	// The comment alignment should be maintained.
	char textIn[] =
		"\n"
		"-(void)Foo1;       // comment\n"
		"+ (void)Foo2;      // comment\n"
		"-    (void)Foo3;   /* comment */\n"
		"\n"
		"-(void)Foo4        // comment\n"
		"{ }";
	char text[] =
		"\n"
		"- (void)Foo1;      // comment\n"
		"+ (void)Foo2;      // comment\n"
		"- (void)Foo3;      /* comment */\n"
		"\n"
		"- (void)Foo4       // comment\n"
		"{ }";
	char options[] = "pad-method-prefix";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCPadMethodPrefix, PadParenOutComments)
{
	// Test pad method prefix with pad-paren-out.
	// The comment alignment should be maintained.
	char textIn[] =
		"\n"
		"-(void)Foo1;       // comment\n"
		"+ (void)Foo2;      // comment\n"
		"-    (void)Foo3;   /* comment */\n"
		"\n"
		"-(void)Foo4        // comment\n"
		"{ }";
	char text[] =
		"\n"
		"- (void) Foo1;     // comment\n"
		"+ (void) Foo2;     // comment\n"
		"- (void) Foo3;     /* comment */\n"
		"\n"
		"- (void) Foo4      // comment\n"
		"{ }";
	char options[] = "pad-method-prefix, pad-paren-out";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Objective-C UnPad Method Prefix
//-------------------------------------------------------------------------

TEST(ObjCUnPadMethodPrefix, LongOption)
{
	// Test unpad-method-prefix long option.
	char textIn[] =
		"\n"
		"-(void)Foo1;\n"
		"+ (void)Foo2;\n"
		"-    (void)Foo3;\n"
		"\n"
		"-(void)Foo4\n"
		"{ }";
	char text[] =
		"\n"
		"-(void)Foo1;\n"
		"+(void)Foo2;\n"
		"-(void)Foo3;\n"
		"\n"
		"-(void)Foo4\n"
		"{ }";
	char options[] = "unpad-method-prefix";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCUnPadMethodPrefix, ShortOption)
{
	// Test unpad method prefix short option.
	char textIn[] =
		"\n"
		"-(void)Foo1;\n"
		"+ (void)Foo2;\n"
		"-    (void)Foo3;\n"
		"\n"
		"-(void)Foo4\n"
		"{ }";
	char text[] =
		"\n"
		"-(void)Foo1;\n"
		"+(void)Foo2;\n"
		"-(void)Foo3;\n"
		"\n"
		"-(void)Foo4\n"
		"{ }";
	char options[] = "-xR";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCUnPadMethodPrefix, Comments)
{
	// Test unpad-method-prefix with comments.
	// The comment alignment should be maintained.
	char textIn[] =
		"\n"
		"-(void)Foo1;       // comment\n"
		"+ (void)Foo2;      // comment\n"
		"-    (void)Foo3;   /* comment */\n"
		"\n"
		"-(void)Foo4        // comment\n"
		"{ }";
	char text[] =
		"\n"
		"-(void)Foo1;       // comment\n"
		"+(void)Foo2;       // comment\n"
		"-(void)Foo3;       /* comment */\n"
		"\n"
		"-(void)Foo4        // comment\n"
		"{ }";
	char options[] = "unpad-method-prefix";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCUnPadMethodPrefix, PadParenOutComments)
{
	// Test unpad method prefix with pad-paren-out.
	// The comment alignment should be maintained.
	char textIn[] =
		"\n"
		"-(void)Foo1;       // comment\n"
		"+ (void)Foo2;      // comment\n"
		"-    (void)Foo3;   /* comment */\n"
		"\n"
		"-(void)Foo4        // comment\n"
		"{ }";
	char text[] =
		"\n"
		"-(void) Foo1;      // comment\n"
		"+(void) Foo2;      // comment\n"
		"-(void) Foo3;      /* comment */\n"
		"\n"
		"-(void) Foo4       // comment\n"
		"{ }";
	char options[] = "unpad-method-prefix, pad-paren-out";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Objective-C Pad Return Type
//-------------------------------------------------------------------------

TEST(ObjCPadReturnType, LongOption)
{
	// Test pad return type long option.
	char textIn[] =
		"\n"
		"-(void)Foo1;\n"
		"+(void)   Foo2;\n"
		"\n"
		"-(void)Foo3\n"
		"{ }";
	char text[] =
		"\n"
		"-(void) Foo1;\n"
		"+(void) Foo2;\n"
		"\n"
		"-(void) Foo3\n"
		"{ }";
	char options[] = "pad-return-type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCPadReturnType, ShortOption)
{
	// Test pad return type short option.
	char textIn[] =
		"\n"
		"-(void)Foo1;\n"
		"+(void)   Foo2;\n"
		"\n"
		"-(void)Foo3\n"
		"{ }";
	char text[] =
		"\n"
		"-(void) Foo1;\n"
		"+(void) Foo2;\n"
		"\n"
		"-(void) Foo3\n"
		"{ }";
	char options[] = "-xq";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCPadReturnType, UnPadReturnType)
{
	// Test objective-c with pad-return-type and unpad-return-type.
	// The result should be pad-return-type.
	char textIn[] =
		"\n"
		"-(void) Foo1;\n"
		"+(void)   Foo2;\n"
		"\n"
		"-(void) Foo3\n"
		"{ }";
	char text[] =
		"\n"
		"-(void) Foo1;\n"
		"+(void) Foo2;\n"
		"\n"
		"-(void) Foo3\n"
		"{ }";
	char options[] = "pad-return-type, unpad-return-type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCPadReturnType, SansPadUnPad)
{
	// Test objective-c with no return type option.
	// The result should be no change.
	char text[] =
		"\n"
		"-(void)Foo1;\n"
		"+(void) Foo2;\n"
		"\n"
		"-(void)  Foo3\n"
		"{ }";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCPadReturnType, Comments)
{
	// Test pad return type with comments.
	// The comment alignment should be maintained.
	char textIn[] =
		"\n"
		"-(void)Foo1;       // comment\n"
		"+(void)   Foo2;    /* comment */\n"
		"\n"
		"-(void)Foo3        // comment\n"
		"{ }";
	char text[] =
		"\n"
		"-(void) Foo1;      // comment\n"
		"+(void) Foo2;      /* comment */\n"
		"\n"
		"-(void) Foo3       // comment\n"
		"{ }";
	char options[] = "pad-return-type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCPadReturnType, PadParenOutComments)
{
	// Test pad return type with pad-paren-out.
	// The comment alignment should be maintained.
	char textIn[] =
		"\n"
		"-(void)Foo1;       // comment\n"
		"+(void)   Foo2;    /* comment */\n"
		"\n"
		"-(void)Foo3        // comment\n"
		"{ }";
	char text[] =
		"\n"
		"- (void) Foo1;     // comment\n"
		"+ (void) Foo2;     /* comment */\n"
		"\n"
		"- (void) Foo3      // comment\n"
		"{ }";
	char options[] = "pad-return-type, pad-paren-out";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Objective-C UnPad Return Type
//-------------------------------------------------------------------------

TEST(ObjCUnPadReturnType, LongOption)
{
	// Test unpad return type long option.
	char textIn[] =
		"\n"
		"-(void)   Foo1;\n"
		"+(void)Foo2;\n"
		"\n"
		"-(void) Foo3\n"
		"{ }";
	char text[] =
		"\n"
		"-(void)Foo1;\n"
		"+(void)Foo2;\n"
		"\n"
		"-(void)Foo3\n"
		"{ }";
	char options[] = "unpad-return-type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCUnPadReturnType, ShortOption)
{
	// Test unpad return type short option.
	char textIn[] =
		"\n"
		"-(void)   Foo1;\n"
		"+(void)Foo2;\n"
		"\n"
		"-(void) Foo3\n"
		"{ }";
	char text[] =
		"\n"
		"-(void)Foo1;\n"
		"+(void)Foo2;\n"
		"\n"
		"-(void)Foo3\n"
		"{ }";
	char options[] = "-xr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCUnPadReturnType, Comments)
{
	// Test unpad return type with comments.
	// The comment alignment should be maintained.
	char textIn[] =
		"\n"
		"-(void)   Foo1;    // comment\n"
		"+(void)Foo2;       /* comment */\n"
		"\n"
		"-(void) Foo3       // comment\n"
		"{ }";
	char text[] =
		"\n"
		"-(void)Foo1;       // comment\n"
		"+(void)Foo2;       /* comment */\n"
		"\n"
		"-(void)Foo3        // comment\n"
		"{ }";
	char options[] = "unpad-return-type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCUnPadReturnType, PadParenOutComments)
{
	// Test unpad return type with pad-paren-out.
	// The comment alignment should be maintained.
	char textIn[] =
		"\n"
		"-(void)Foo1;       // comment\n"
		"+(void)   Foo2;    /* comment */\n"
		"\n"
		"-(void)Foo3        // comment\n"
		"{ }";
	char text[] =
		"\n"
		"- (void)Foo1;      // comment\n"
		"+ (void)Foo2;      /* comment */\n"
		"\n"
		"- (void)Foo3       // comment\n"
		"{ }";
	char options[] = "unpad-return-type, pad-paren-out";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Objective-C Pad Method Colon
//-------------------------------------------------------------------------

TEST(ObjCPadMethodColon, NoOption)
{
	// Test without pad-method-colon option.
	// Statements should not change.
	char text[] =
		"\n"
		"-(void)foo1:(int)row;\n"
		"-(void)foo2 : (int)row;\n"
		"-(void)foo3: (int)row;\n"
		"-(void)foo4 :(int)row;";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, LongOptionNone)
{
	// Test pad-method-colon=none long option.
	char textIn[] =
		"\n"
		"-(void)foo1:(int)row;\n"
		"-(void)foo2 : (int)row;\n"
		"-(void)foo3: (int)row;\n"
		"-(void)foo4 :(int)row;";
	char text[] =
		"\n"
		"-(void)foo1:(int)row;\n"
		"-(void)foo2:(int)row;\n"
		"-(void)foo3:(int)row;\n"
		"-(void)foo4:(int)row;";
	char options[] = "pad-method-colon=none";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, LongOptionAll)
{
	// Test pad-method-colon=all long option.
	char textIn[] =
		"\n"
		"-(void)foo1:(int)row;\n"
		"-(void)foo2 : (int)row;\n"
		"-(void)foo3: (int)row;\n"
		"-(void)foo4 :(int)row;";
	char text[] =
		"\n"
		"-(void)foo1 : (int)row;\n"
		"-(void)foo2 : (int)row;\n"
		"-(void)foo3 : (int)row;\n"
		"-(void)foo4 : (int)row;";
	char options[] = "pad-method-colon=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, LongOptionAfter)
{
	// Test pad-method-colon=after long option.
	char textIn[] =
		"\n"
		"-(void)foo1:(int)row;\n"
		"-(void)foo2 : (int)row;\n"
		"-(void)foo3: (int)row;\n"
		"-(void)foo4 :(int)row;";
	char text[] =
		"\n"
		"-(void)foo1: (int)row;\n"
		"-(void)foo2: (int)row;\n"
		"-(void)foo3: (int)row;\n"
		"-(void)foo4: (int)row;";
	char options[] = "pad-method-colon=after";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, LongOptionBefore)
{
	// Test pad-method-colon=before long option.
	char textIn[] =
		"\n"
		"-(void)foo1:(int)row;\n"
		"-(void)foo2 : (int)row;\n"
		"-(void)foo3: (int)row;\n"
		"-(void)foo4 :(int)row;";
	char text[] =
		"\n"
		"-(void)foo1 :(int)row;\n"
		"-(void)foo2 :(int)row;\n"
		"-(void)foo3 :(int)row;\n"
		"-(void)foo4 :(int)row;";
	char options[] = "pad-method-colon=before";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, ShortOptionNone)
{
	// Test pad-method-colon=none short option.
	char textIn[] =
		"\n"
		"-(void)foo1:(int)row;\n"
		"-(void)foo2 : (int)row;\n"
		"-(void)foo3: (int)row;\n"
		"-(void)foo4 :(int)row;";
	char text[] =
		"\n"
		"-(void)foo1:(int)row;\n"
		"-(void)foo2:(int)row;\n"
		"-(void)foo3:(int)row;\n"
		"-(void)foo4:(int)row;";
	char options[] = "-xP0";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, ShortOptionAll)
{
	// Test pad-method-colon=all short option.
	char textIn[] =
		"\n"
		"-(void)foo1:(int)row;\n"
		"-(void)foo2 : (int)row;\n"
		"-(void)foo3: (int)row;\n"
		"-(void)foo4 :(int)row;";
	char text[] =
		"\n"
		"-(void)foo1 : (int)row;\n"
		"-(void)foo2 : (int)row;\n"
		"-(void)foo3 : (int)row;\n"
		"-(void)foo4 : (int)row;";
	char options[] = "-xP1";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, ShortOptionAfter)
{
	// Test pad-method-colon=after short option.
	char textIn[] =
		"\n"
		"-(void)foo1:(int)row;\n"
		"-(void)foo2 : (int)row;\n"
		"-(void)foo3: (int)row;\n"
		"-(void)foo4 :(int)row;";
	char text[] =
		"\n"
		"-(void)foo1: (int)row;\n"
		"-(void)foo2: (int)row;\n"
		"-(void)foo3: (int)row;\n"
		"-(void)foo4: (int)row;";
	char options[] = "-xP2";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, ShortOptionBefore)
{
	// Test pad-method-colon=before short option.
	char textIn[] =
		"\n"
		"-(void)foo1:(int)row;\n"
		"-(void)foo2 : (int)row;\n"
		"-(void)foo3: (int)row;\n"
		"-(void)foo4 :(int)row;";
	char text[] =
		"\n"
		"-(void)foo1 :(int)row;\n"
		"-(void)foo2 :(int)row;\n"
		"-(void)foo3 :(int)row;\n"
		"-(void)foo4 :(int)row;";
	char options[] = "-xP3";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, MultipleSpacesNone)
{
	// Test pad-method-colon=none with multiple spaces.
	// This and pad-method-colon=all will test all options.
	char textIn[] =
		"\n"
		"-(void)foo  :   (int)row;";
	char text[] =
		"\n"
		"-(void)foo:(int)row;";
	char options[] = "pad-method-colon=none";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, MultipleSpacesAll)
{
	// Test pad-method-colon=all with multiple spaces.
	// This and pad-method-colon=none will test all options.
	char textIn[] =
		"\n"
		"-(void)foo  :   (int)row;";
	char text[] =
		"\n"
		"-(void)foo : (int)row;";
	char options[] = "pad-method-colon=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, LimitsNone)
{
	// Test pad-method-colon=none with 'for' and 'while' loop limits.
	// This should not cause an exception.
	// This and pad-method-colon=all will test all options.
	char textIn[] =
		"\n-(void)readHeader\n"
		"{\n"
		"    NSData *data = [file dataOfLength\n"
		"    : HEADLEN\n"
		"    atOffset :\n"
		"    [NSNumber numberWithUnsignedLong\n"
		":\n"
		"    0L]];\n"
		"}";
	char text[] =
		"\n-(void)readHeader\n"
		"{\n"
		"    NSData *data = [file dataOfLength\n"
		"                    :HEADLEN\n"
		"                    atOffset:\n"
		"                    [NSNumber numberWithUnsignedLong\n"
		"                     :\n"
		"                     0L]];\n"
		"}";
	char options[] = "pad-method-colon=none";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, LimitsAll)
{
	// Test pad-method-colon=all with 'for' and 'while' loop limits.
	// This should not cause an exception.
	// This and pad-method-colon=none will test all options.
	char textIn[] =
		"\n-(void)readHeader\n"
		"{\n"
		"    NSData *data = [file dataOfLength\n"
		"    :HEADLEN\n"
		"    atOffset:\n"
		"    [NSNumber numberWithUnsignedLong\n"
		":\n"
		"    0L]];\n"
		"}";
	char text[] =
		"\n-(void)readHeader\n"
		"{\n"
		"    NSData *data = [file dataOfLength\n"
		"                    : HEADLEN\n"
		"                    atOffset :\n"
		"                    [NSNumber numberWithUnsignedLong\n"
		"                     :\n"
		"                     0L]];\n"
		"}";
	char options[] = "pad-method-colon=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, SingleCharFollowsNone)
{
	// Test pad-method-colon=none 'for' and 'while' loop limits.
	// The single char following the colon should be recognized.
	// This and pad-method-colon=all will test all options.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [[matrix cellAtRow:0 column:0] setTitle: NSLocalizedString(@\"Name\")];\n"
		"    [[matrix cellAtRow: 1 column: 0] setTitle : NSLocalizedString(@\"Type\")];\n"
		"    [[matrix cellAtRow:   2 column:   0] setTitle: NSLocalizedString(@\"Date\")];\n"
		"    [[matrix cellAtRow   :3 column   :0] setTitle :NSLocalizedString(@\"Size\")];\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [[matrix cellAtRow:0 column:0] setTitle:NSLocalizedString(@\"Name\")];\n"
		"    [[matrix cellAtRow:1 column:0] setTitle:NSLocalizedString(@\"Type\")];\n"
		"    [[matrix cellAtRow:2 column:0] setTitle:NSLocalizedString(@\"Date\")];\n"
		"    [[matrix cellAtRow:3 column:0] setTitle:NSLocalizedString(@\"Size\")];\n"
		"}";
	char options[] = "pad-method-colon=none";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, SingleCharFollowsAll)
{
	// Test pad-method-colon=all 'for' and 'while' loop limits.
	// The single char following the colon should be recognized.
	// This and pad-method-colon=none will test all options.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [[matrix cellAtRow:0 column:0] setTitle: NSLocalizedString(@\"Name\")];\n"
		"    [[matrix cellAtRow: 1 column: 0] setTitle : NSLocalizedString(@\"Type\")];\n"
		"    [[matrix cellAtRow:   2 column:   0] setTitle: NSLocalizedString(@\"Date\")];\n"
		"    [[matrix cellAtRow   :3 column   :0] setTitle :NSLocalizedString(@\"Size\")];\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [[matrix cellAtRow : 0 column : 0] setTitle : NSLocalizedString(@\"Name\")];\n"
		"    [[matrix cellAtRow : 1 column : 0] setTitle : NSLocalizedString(@\"Type\")];\n"
		"    [[matrix cellAtRow : 2 column : 0] setTitle : NSLocalizedString(@\"Date\")];\n"
		"    [[matrix cellAtRow : 3 column : 0] setTitle : NSLocalizedString(@\"Size\")];\n"
		"}";
	char options[] = "pad-method-colon=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, EndOfLineFollowsNone)
{
	// The colon is at end-of-line.
	// This and pad-method-colon=all will test all options.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [(NSMutableData *)data appendData :\n"
		"     [handle readDataOfLength : nbytes]];\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [(NSMutableData *)data appendData:\n"
		"     [handle readDataOfLength:nbytes]];\n"
		"}";
	char options[] = "pad-method-colon=none";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, EndOfLineFollowsAll)
{
	// The colon is at end-of-line.
	// This and pad-method-colon=none will test all options.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [(NSMutableData *)data appendData:\n"
		"     [handle readDataOfLength:nbytes]];\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [(NSMutableData *)data appendData :\n"
		"     [handle readDataOfLength : nbytes]];\n"
		"}";
	char options[] = "pad-method-colon=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, NoneComment)
{
	// Test pad-method-colon=none with following comments.
	char textIn[] =
		"\n"
		"-(void)foo1:(int)row;     // comment\n"
		"-(void)foo2 : (int)row;   // comment\n"
		"-(void)foo3: (int)row;    /* comment */\n"
		"-(void)foo4 :(int)row;    // comment\n";
	char text[] =
		"\n"
		"-(void)foo1:(int)row;     // comment\n"
		"-(void)foo2:(int)row;     // comment\n"
		"-(void)foo3:(int)row;     /* comment */\n"
		"-(void)foo4:(int)row;     // comment\n";
	char options[] = "pad-method-colon=none";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCPadMethodColon, AllComment)
{
	// Test pad-method-colon=none with following comments.
	char textIn[] =
		"\n"
		"-(void)foo1:(int)row;     // comment\n"
		"-(void)foo2 : (int)row;   // comment\n"
		"-(void)foo3: (int)row;    /* comment */\n"
		"-(void)foo4 :(int)row;    // comment\n";
	char text[] =
		"\n"
		"-(void)foo1 : (int)row;   // comment\n"
		"-(void)foo2 : (int)row;   // comment\n"
		"-(void)foo3 : (int)row;   /* comment */\n"
		"-(void)foo4 : (int)row;   // comment\n";
	char options[] = "pad-method-colon=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCPadMethodColon, AfterComment)
{
	// Test pad-method-colon=none with following comments.
	char textIn[] =
		"\n"
		"-(void)foo1:(int)row;     // comment\n"
		"-(void)foo2 : (int)row;   // comment\n"
		"-(void)foo3:  (int)row;   /* comment */\n"
		"-(void)foo4 :(int)row;    // comment\n";
	char text[] =
		"\n"
		"-(void)foo1: (int)row;    // comment\n"
		"-(void)foo2: (int)row;    // comment\n"
		"-(void)foo3: (int)row;    /* comment */\n"
		"-(void)foo4: (int)row;    // comment\n";
	char options[] = "pad-method-colon=after";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCPadMethodColon, BeforeComment)
{
	// Test pad-method-colon=none with following comments.
	char textIn[] =
		"\n"
		"-(void)foo1:(int)row;     // comment\n"
		"-(void)foo2  : (int)row;  // comment\n"
		"-(void)foo3: (int)row;    /* comment */\n"
		"-(void)foo4 :(int)row;    // comment\n";
	char text[] =
		"\n"
		"-(void)foo1 :(int)row;    // comment\n"
		"-(void)foo2 :(int)row;    // comment\n"
		"-(void)foo3 :(int)row;    /* comment */\n"
		"-(void)foo4 :(int)row;    // comment\n";
	char options[] = "pad-method-colon=before";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCPadMethodColon, Selector)
{
	// Test pad-method-colon=all within a @selector.
	// The ending colon should not be padded.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    cutTitleSel = @selector(cutTitle:toFitWidth:);\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    cutTitleSel = @selector(cutTitle : toFitWidth:);\n"
		"}";
	char options[] = "pad-method-colon=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, ParenFollowsNone)
{
	// Test pad-method-colon=none with a following ')'.
	// The ending colon should not be padded.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [panel setAction:@selector(colorChoosen : )];\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [panel setAction:@selector(colorChoosen:)];\n"
		"}";
	char options[] = "pad-method-colon=none";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, ParenFollowsAll)
{
	// Test pad-method-colon=all with a following ')'.
	// The ending colon should not be padded.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [panel setAction : @selector(colorChoosen : )];\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [panel setAction : @selector(colorChoosen:)];\n"
		"}";
	char options[] = "pad-method-colon=all";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, ParenFollowsAfter)
{
	// Test pad-method-colon=after with a following ')'.
	// The ending colon should not be padded.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [panel setAction : @selector(colorChoosen : )];\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [panel setAction: @selector(colorChoosen:)];\n"
		"}";
	char options[] = "pad-method-colon=after";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, ParenFollowsBefore)
{
	// Test pad-method-colon=before with a following ')'.
	// The ending colon should not be padded.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [panel setAction : @selector(colorChoosen : )];\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [panel setAction :@selector(colorChoosen:)];\n"
		"}";
	char options[] = "pad-method-colon=before";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, QuestionColon1)
{
	// Test pad-method-colon=none with '?' and ':'.
	// This should not remove the padding.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [caseSensButt setState : ([entry boolValue] ? NSOnState : NSOffState)];\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [caseSensButt setState:([entry boolValue] ? NSOnState : NSOffState)];\n"
		"}";
	char options[] = "pad-method-colon=none";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, QuestionColon2)
{
	// Test pad-method-colon=none with '?' and ':'.
	// This should not remove the padding for '? :'.
	// But should remove for the method call.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    fsfilter = fsattribute ? [info objectForKey : @\"fsfilter\"] : nil;\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    fsfilter = fsattribute ? [info objectForKey:@\"fsfilter\"] : nil;\n"
		"}";
	char options[] = "pad-method-colon=none";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, QuestionColon3)
{
	// Test pad-method-colon=none with '?' and ':'.
	// This should not remove the padding for '? :'.
	// But should remove for the method call.
	char textIn[] =
		"\nvoid Foo()\n"
		"{\n"
		"    FSNode *pnode = (i == 0) ? nil : [components objectAtIndex : (i-1)];\n"
		"}";
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    FSNode *pnode = (i == 0) ? nil : [components objectAtIndex:(i-1)];\n"
		"}";
	char options[] = "pad-method-colon=none";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, ScopeResolution)
{
	// pad-method-colon should not pad a scope resolution operator.
	char text[] =
		"\nconst char* TiXmlBase::errorString[TiXmlBase::TIXML_ERROR_STRING_COUNT] =\n"
		"{\n"
		"};\n"
		"\n"
		"void GetDetectorState(DetectorState[nsUniversalDetector::NumDetectors], PRUint32& offset )\n"
		"{\n"
		"    ListStyles style[Logger::num_levels];\n"
		"}";
	char options[] = "pad-method-colon=all";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCPadMethodColon, CSharpFile)
{
	// pad-method-colon should not pad in a C# file.
	char text[] =
		"\n[global::System.Diagnostics.DebuggerNonUserCodeAttribute()]\n"
		"[global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]\n"
		"\n"
		"[assembly: AssemblyTitle(\"TreeMaps\")]\n"
		"[assembly: AssemblyDescription("")]\n"
		"\n"
		"[field: NonSerialized]\n"
		"public class GitVersion: IDocumentVersion\n"
		"{\n"
		"    [param: MarshalAs(UnmanagedType.Currency)]\n"
		"    [return: MarshalAs(UnmanagedType.Bool)]\n"
		"}";
	char options[] = "pad-method-colon=all, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//-------------------------------------------------------------------------
// AStyle Objective-C Other Tests
//-------------------------------------------------------------------------

TEST(ObjCOther, 1TBSAddBrackets)
{
	// test 1tbs style option with added brackets
	char textIn[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"}\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo\n"
		"{\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"}\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"    ofSize : (int) size {\n"
		"    if (isFoo)\n"
		"        bar();\n"
		"}\n"
		"\n"
		"@end\n";
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"}\n"
		"@end\n"
		"\n"
		"@implementation Foo\n"
		"\n"
		"- (void) foo\n"
		"{\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"}\n"
		"\n"
		"- (void) foo : (int) icon\n"
		"    ofSize : (int) size\n"
		"{\n"
		"    if (isFoo) {\n"
		"        bar();\n"
		"    }\n"
		"}\n"
		"\n"
		"@end\n";
	char options[] = "style=1tbs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, GoogleWithAccessModifiers)
{
	// test google style option with access modifiers
	char text[] =
		"\n@interface Foo : NSObject {\n"
		"  @public\n"
		"    bool var1;\n"
		"  @protected\n"
		"    bool var2;\n"
		"  @private\n"
		"    bool var3;\n"
		"}\n"
		"@end\n";
	char options[] = "style=google";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, GoogleWithMultilineInterface)
{
	// test google style option with a multi-line interface
	char text[] =
		"\n@interface Foo\n"
		"    : NSObject {\n"
		"    bool var1;\n"
		"    bool var2;\n"
		"}\n"
		"@end\n";
	char options[] = "style=google";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, HeaderData)
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
		"+void removeComponentsOfPath(NSString *path,\n"
		"                             pcomp *base);\n"
		"\n"
		"-(void)writeData:(NSData *)data\n"
		"    atOffset:(NSNumber *)offset;\n"
		"\n"
		"-(void)method2;\n"
		"\n"
		"@end";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, InterfaceContinuation1)
{
	// test an Objective-C header with continuation lines
	// no bracket
	char text[] =
		"\n@interface Foo1 :\n"
		"    NSObject\n"
		"@end\n"
		"\n"
		"@interface Foo2\n"
		"    : NSObject\n"
		"@end\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, InterfaceContinuation2)
{
	// test google style option with a multi-line interface
	// attached bracket
	char text[] =
		"\n@interface Foo1 :\n"
		"    NSObject {\n"
		"}\n"
		"@end\n"
		"\n"
		"@interface Foo2\n"
		"    : NSObject {\n"
		"}\n"
		"@end\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, InterfaceContinuation3)
{
	// test google style option with a multi-line interface
	// broken bracket
	char text[] =
		"\n@interface Foo1 :\n"
		"    NSObject\n"
		"{\n"
		"}\n"
		"@end\n"
		"\n"
		"@interface Foo2\n"
		"    : NSObject\n"
		"{\n"
		"}\n"
		"@end\n";
	char options[] = "";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, MethodCallIndent)
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

TEST(ObjCOther, NSExceptionMacros)
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

TEST(ObjCOther, OtherColonIndent)
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

TEST(ObjCOther, MethodCallHeader)
{
	// test method call containing a header (default)
	// the header should not be recognized
	// break-blocks tests ASFormatter, indentation tests ASBeautifier
	char text[] =
		"\nvoid Foo()\n"
		"{\n"
		"    [[NSNotificationCenter default Center]\n"
		"     postNotificationName:myNotification\n"
		"     object:self\n"
		"     userinfo:nil];\n"
		"}";
	char options[] = "break-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, AutoreleasepoolBreak)
{
	// Precommand header autoreleasepoolwith broken brackets.
	char text[] =
		"\nvirtual void foo()\n"
		"{\n"
		"    @autoreleasepool\n"
		"    {\n"
		"        bar()\n"
		"    }\n"
		"}\n";
	char options[] = "style=break";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCOther, AutoreleasepoolAttach)
{
	// Precommand header autoreleasepoolwith attached brackets.
	char textIn[] =
		"\nvirtual void foo()\n"
		"{\n"
		"    @autoreleasepool\n"
		"    {\n"
		"        bar()\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvirtual void foo() {\n"
		"    @autoreleasepool {\n"
		"        bar()\n"
		"    }\n"
		"}\n";
	char options[] = "style=attach";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCOther, AutoreleasepoolKandR)
{
	// Precommand header autoreleasepoolwith K&R brackets.
	char textIn[] =
		"\nvirtual void foo()\n"
		"{\n"
		"    @autoreleasepool\n"
		"    {\n"
		"        bar()\n"
		"    }\n"
		"}\n";
	char text[] =
		"\nvirtual void foo()\n"
		"{\n"
		"    @autoreleasepool {\n"
		"        bar()\n"
		"    }\n"
		"}\n";
	char options[] = "style=k&r";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(ObjCOther, IndentClasses)
{
	// test google style option with indent classes
	// classes should NOT be indented
	char text[] =
		"\n@interface Foo : NSObject {\n"
		"@public\n"
		"    bool var1;\n"
		"@protected\n"
		"    bool var2;\n"
		"@private\n"
		"    bool var3;\n"
		"}\n"
		"@end\n";
	char options[] = "indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, IndentModifiers)
{
	// test google style option with indent classes
	char text[] =
		"\n@interface Foo : NSObject {\n"
		"  @public\n"
		"    bool var1;\n"
		"  @protected\n"
		"    bool var2;\n"
		"  @private\n"
		"    bool var3;\n"
		"}\n"
		"@end\n";
	char options[] = "indent-modifiers";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, InStatementIndent1)
{
	// test method containing a long indent
	// the in-statement indent must be increased for correct alignment
	char text[] =
		"\n-(void) Foo\n"
		"{\n"
		"    NSDateComponents* components = [calendar components:(NSYearCalendarUnit |\n"
		"                                                         NSMonthCalendarUnit |\n"
		"                                                         NSDayCalendarUnit)\n"
		"                                    fromDate:today];\n"
		"}";
	char options[] = "max-instatement-indent=60";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, InStatementIndent2)
{
	// The first function has no ending ';' and the ending '}' is followed by a comment.
	// The next objective statement should NOT be flagged as a 'isNonInStatementArray'.
	// If it is the indentation will be wrong.
	char text[] =
		"\nvoid Foo2()\n"
		"{\n"
		"    dict = [[NSDictionary alloc] initWithObjects:@\"foo\", @\"bar\", @\"baz\"]\n"
		"}	// p 277\n"
		"\n"
		"-(void) Foo\n"
		"{\n"
		"    NSDateComponents* components = [calendar components:(NSYearCalendarUnit |\n"
		"                                                         NSDayCalendarUnit)\n"
		"                                    fromDate:today];\n"
		"}";
	char options[] = "max-instatement-indent=60";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, AlignPointer)
{
	// Test align-pointer=name option.
	// The (*) should not change.
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    [icons sortUsingFunction: (int (*)(id, id, void*))compareWithExtType\n"
		"     context: (void*)NULL];\n"
		"}";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    [icons sortUsingFunction: (int (*)(id, id, void *))compareWithExtType\n"
		"     context: (void *)NULL];\n"
		"}";
	char options[] = "align-pointer=name";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, PadInterfaceColon1)
{
	// test padding a @interface statement.
	char textIn[] =
		"\n@interface Foo:NSObject\n"
		"{\n"
		"}\n"
		"\n"
		"@interface Foo:NSObject\n"
		"\n"
		"-(void)method1;\n";
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"}\n"
		"\n"
		"@interface Foo : NSObject\n"
		"\n"
		"-(void)method1;\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, PadInterfaceColon2)
{
	// test limits in padding a @interface statement.
	char textIn[] =
		"\n@interface Foo:\n"
		"NSObject\n"
		"@end\n"
		"\n"
		"@interface Foo\n"
		":NSObject\n"
		"@end\n";
	char text[] =
		"\n@interface Foo :\n"
		"    NSObject\n"
		"@end\n"
		"\n"
		"@interface Foo\n"
		"    : NSObject\n"
		"@end\n";
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, PadOperator1)
{
	// Test methods with pad-oper option.
	// Statements should not change.
	char text[] =
		"\n"
		"-(void)foo1:(int)row\n"
		"{\n"
		"    [[NSNotificationCenter default Center]\n"
		"     postNotificationName:myNotification\n"
		"     object:self\n"
		"     userinfo:nil];\n"
		"}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, PadOperator2)
{
	// Test selector with pad-oper option.
	// Statement should not change.
	char text[] =
		"\n"
		"-(void)foo1:(int)row\n"
		"{\n"
		"    cutTitleSel = @selector(cutTitle:toFitWidth:);\n"
		"}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, PadOperator3)
{
	// Test 'or' with pad-oper option.
	// The 'or' at the end should not be padded.
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    leafpos = [[LeafPosition alloc] initWithPosX:x posY:y relativeToPoint:or];\n"
		"}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, PadOperator4)
{
	// Test pad-oper question.
	// Don't pad '?:' within the '[]'.
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    fsfilter = fsattribute?[info objectForKey:@\"fsfilter\"]:nil;\n"
		"    FSNode *pnode = (i == 0)?nil:[components objectAtIndex:(i)];\n"
		"}";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    fsfilter = fsattribute ? [info objectForKey:@\"fsfilter\"] : nil;\n"
		"    FSNode *pnode = (i == 0) ? nil : [components objectAtIndex:(i)];\n"
		"}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(ObjCOther, PadOperator5)
{
	// Test pad-oper question.
	// Test the questionMarkStack with multiple '(' and '['.
	char textIn[] =
		"\nvoid foo()\n"
		"{\n"
		"    caseSensitive = Attribute(\"CaseSensitive\")?atol(Attribute(\"CaseSensitive\")) != 0:false;\n"
		"    tabPoints[5].y = HasFlag?(tabPoints[4].y):tabPoints[4].y;\n"
		"}";
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"    caseSensitive = Attribute(\"CaseSensitive\") ? atol(Attribute(\"CaseSensitive\")) != 0 : false;\n"
		"    tabPoints[5].y = HasFlag ? (tabPoints[4].y) : tabPoints[4].y;\n"
		"}";
	char options[] = "pad-oper";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------

}  // namespace
