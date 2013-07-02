//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleTest.h"

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {

//----------------------------------------------------------------------------
// AStyle Objective-C Files
// Additional tests are in the brackets tests
//----------------------------------------------------------------------------

struct FileObjCHeaderF : public ::testing::Test
{
	string textStr;
	const char* textIn;

	FileObjCHeaderF()
	{
		textStr =
			"\n@interface Foo : NSObject {\n"
			"    NSString* var1;\n"
			"    NSString* var2;\n"
			"}\n"
			"@end";
		textIn = textStr.c_str();
	}
};

TEST_F(FileObjCHeaderF, Default)
{
	// test default style option
	char options[] = "";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(textIn, textOut);
	delete [] textOut;
}

TEST_F(FileObjCHeaderF, Allman)
{
	// test allman style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"}\n"
		"@end";
	char options[] = "style=allman";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileObjCHeaderF, Java)
{
	// test java style option
	char text[] =
		"\n@interface Foo : NSObject {\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"}\n"
		"@end";
	char options[] = "style=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileObjCHeaderF, KR)
{
	// test k&r style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"}\n"
		"@end";
	char options[] = "style=kr";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileObjCHeaderF, Stroustrup)
{
	// test stroustrup style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"     NSString* var1;\n"
		"     NSString* var2;\n"
		"}\n"
		"@end";
	char options[] = "style=stroustrup, indent=spaces=5";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileObjCHeaderF, Whitesmith)
{
	// test whitesmith style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"    {\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"    }\n"
		"@end";
	char options[] = "style=whitesmith";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileObjCHeaderF, Banner)
{
	// test banner style option
	char text[] =
		"\n@interface Foo : NSObject {\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"    }\n"
		"@end";
	char options[] = "style=banner";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileObjCHeaderF, Gnu)
{
	// test gnu style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"  NSString* var1;\n"
		"  NSString* var2;\n"
		"}\n"
		"@end";
	char options[] = "style=gnu, indent=spaces=2";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileObjCHeaderF, Linux)
{
	// test linux style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"        NSString* var1;\n"
		"        NSString* var2;\n"
		"}\n"
		"@end";
	char options[] = "style=linux, indent=spaces=8";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileObjCHeaderF, Horstmann)
{
	// test horstmann style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{  NSString* var1;\n"
		"   NSString* var2;\n"
		"}\n"
		"@end";
	char options[] = "style=horstmann, indent=spaces=3";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileObjCHeaderF, 1TBS)
{
	// test 1tbs style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{\n"
		"    NSString* var1;\n"
		"    NSString* var2;\n"
		"}\n"
		"@end";
	char options[] = "style=1tbs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileObjCHeaderF, Pico)
{
	// test pico style option
	char text[] =
		"\n@interface Foo : NSObject\n"
		"{   NSString* var1;\n"
		"    NSString* var2; }\n"
		"@end";
	char options[] = "style=pico";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileObjCHeaderF, Lisp)
{
	// test lisp style option
	char text[] =
		"\n@interface Foo : NSObject {\n"
		"    NSString* var1;\n"
		"    NSString* var2; }\n"
		"@end";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle Java Files
// Additional tests are in the brackets tests
//----------------------------------------------------------------------------

struct FileJavaF : public ::testing::Test
{
	string textStr;
	const char* textIn;

	FileJavaF()
	{
		textStr =
			"\npublic class FooClass\n"
			"{\n"
			"    private bool var1;\n"
			"    private bool var2;\n"
			"\n"
			"    public void foo(bool isFoo)\n"
			"    {\n"
			"        if (isFoo)\n"
			"        {\n"
			"            bar();\n"
			"        }\n"
			"        else\n"
			"            anotherBar();\n"
			"    }\n"
			"}\n";
		textIn = textStr.c_str();
	}
};

TEST_F(FileJavaF, Allman)
{
	// test allman style option
	char text[] =
		"\npublic class FooClass\n"
		"{\n"
		"    private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo)\n"
		"    {\n"
		"        if (isFoo)\n"
		"        {\n"
		"            bar();\n"
		"        }\n"
		"        else\n"
		"            anotherBar();\n"
		"    }\n"
		"}\n";
	char options[] = "style=allman, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileJavaF, Java)
{
	// test java style option
	char text[] =
		"\npublic class FooClass {\n"
		"    private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo) {\n"
		"        if (isFoo) {\n"
		"            bar();\n"
		"        } else\n"
		"            anotherBar();\n"
		"    }\n"
		"}\n";
	char options[] = "style=java, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileJavaF, KR)
{
	// test k&r style option
	char text[] =
		"\npublic class FooClass\n"
		"{\n"
		"    private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo)\n"
		"    {\n"
		"        if (isFoo) {\n"
		"            bar();\n"
		"        } else\n"
		"            anotherBar();\n"
		"    }\n"
		"}\n";
	char options[] = "style=kr, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileJavaF, Stroustrup)
{
	// test stroustrup style option
	char text[] =
		"\npublic class FooClass {\n"
		"     private bool var1;\n"
		"     private bool var2;\n"
		"\n"
		"     public void foo(bool isFoo)\n"
		"     {\n"
		"          if (isFoo) {\n"
		"               bar();\n"
		"          } else\n"
		"               anotherBar();\n"
		"     }\n"
		"}\n";
	char options[] = "style=stroustrup, indent=spaces=5, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileJavaF, Whitesmith)
{
	// test whitesmith style option
	char text[] =
		"\npublic class FooClass\n"
		"    {\n"
		"    private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo)\n"
		"        {\n"
		"        if (isFoo)\n"
		"            {\n"
		"            bar();\n"
		"            }\n"
		"        else\n"
		"            anotherBar();\n"
		"        }\n"
		"    }\n";
	char options[] = "style=whitesmith, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileJavaF, Banner)
{
	// test banner style option
	char text[] =
		"\npublic class FooClass {\n"
		"    private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo) {\n"
		"        if (isFoo) {\n"
		"            bar();\n"
		"            }\n"
		"        else\n"
		"            anotherBar();\n"
		"        }\n"
		"    }\n";
	char options[] = "style=banner, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileJavaF, Gnu)
{
	// test gnu style option
	char text[] =
		"\npublic class FooClass\n"
		"{\n"
		"  private bool var1;\n"
		"  private bool var2;\n"
		"\n"
		"  public void foo(bool isFoo)\n"
		"  {\n"
		"    if (isFoo)\n"
		"      {\n"
		"        bar();\n"
		"      }\n"
		"    else\n"
		"      anotherBar();\n"
		"  }\n"
		"}\n";
	char options[] = "style=gnu, indent=spaces=2, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileJavaF, Linux)
{
	// test linux style option
	char text[] =
		"\npublic class FooClass\n"
		"{\n"
		"        private bool var1;\n"
		"        private bool var2;\n"
		"\n"
		"        public void foo(bool isFoo)\n"
		"        {\n"
		"                if (isFoo) {\n"
		"                        bar();\n"
		"                } else\n"
		"                        anotherBar();\n"
		"        }\n"
		"}\n";
	char options[] = "style=linux, indent=spaces=8, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileJavaF, Horstmann)
{
	// test horstmann style option
	char text[] =
		"\npublic class FooClass\n"
		"{  private bool var1;\n"
		"   private bool var2;\n"
		"\n"
		"   public void foo(bool isFoo)\n"
		"   {  if (isFoo)\n"
		"      {  bar();\n"
		"      }\n"
		"      else\n"
		"         anotherBar();\n"
		"   }\n"
		"}\n";
	char options[] = "style=horstmann, indent=spaces=3, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileJavaF, 1TBS)
{
	// test 1tbs style option
	char text[] =
		"\npublic class FooClass\n"
		"{\n"
		"    private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo)\n"
		"    {\n"
		"        if (isFoo) {\n"
		"            bar();\n"
		"        } else {\n"
		"            anotherBar();\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "style=1tbs, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileJavaF, Pico)
{
	// test pico style option
	char text[] =
		"\npublic class FooClass\n"
		"{   private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo)\n"
		"    {   if (isFoo)\n"
		"        {   bar(); }\n"
		"        else\n"
		"            anotherBar(); } }\n";
	char options[] = "style=pico, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileJavaF, Lisp)
{
	// test lisp style option
	char text[] =
		"\npublic class FooClass {\n"
		"    private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo) {\n"
		"        if (isFoo) {\n"
		"            bar(); }\n"
		"        else\n"
		"            anotherBar(); } }\n";
	char options[] = "style=lisp, mode=java";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileJava, Whitesmith_Interface)
{
	// test whitesmith style with interface
	char text[] =
		"\npublic interface FooIF\n"
		"    {\n"
		"    public void foo1();\n"
		"    public void foo2();\n"
		"    }\n";
	char options[] = "style=whitesmith, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileJava, Whitesmith_NestedClass)
{
	// test whitesmith style with nested classes
	char text[] =
		"\npublic class A\n"
		"    {\n"
		"    public int foo1;\n"
		"    public class B\n"
		"        {\n"
		"        public int foo2;\n"
		"        public class C\n"
		"            {\n"
		"            public void foo(bool isFoo)\n"
		"                {\n"
		"                if (isFoo)\n"
		"                    {\n"
		"                    bar();\n"
		"                    }\n"
		"                else\n"
		"                    anotherBar();\n"
		"                }\n"
		"            }\n"
		"        }\n"
		"    }\n";
	char options[] = "style=whitesmith, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileJava, Whitesmith_StaticConstructor)
{
	// test whitesmith style with static constructor
	// should NOT indent the method opening bracket
	char text[] =
		"\npublic class FooClass\n"
		"    {\n"
		"    private bool foo;\n"
		"    private int  bar;\n"
		"\n"
		"    static\n"
		"        {\n"
		"        if (foo)\n"
		"            {\n"
		"            bar = 0;\n"
		"            }\n"
		"        else\n"
		"            bar = 1;\n"
		"        }\n"
		"    }\n"
		"\n";
	char options[] = "style=whitesmith, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileJava, Whitesmith_Throws)
{
	// test whitesmith style with throws statement
	// should be recognized as a block opener
	char text[] =
		"\npublic class FooClass\n"
		"    {\n"
		"    static private bool foo;\n"
		"    static private int  bar;\n"
		"\n"
		"    public void fooBar() throws IOException\n"
		"        {\n"
		"        if (foo)\n"
		"            {\n"
		"            throw new IOException(bar);\n"
		"            }\n"
		"        }\n"
		"    }\n";
	char options[] = "style=whitesmith, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileJava, Banner_Interface)
{
	// test banner style with interface
	char text[] =
		"\npublic interface FooIF {\n"
		"    public void foo1();\n"
		"    public void foo2();\n"
		"    }\n";
	char options[] = "style=banner, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileJava, Banner_NestedClass)
{
	// test banner style with nested classes
	char text[] =
		"\npublic class A  {\n"
		"    public int foo1;\n"
		"    public class B  {\n"
		"        public int foo2;\n"
		"        public class C  {\n"
		"            public void foo(bool isFoo)  {\n"
		"                if (isFoo)  {\n"
		"                    bar();\n"
		"                    }\n"
		"                else\n"
		"                    anotherBar();\n"
		"                }\n"
		"            }\n"
		"        }\n"
		"    }\n";
	char options[] = "style=banner, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileJava, Banner_StaticConstructor)
{
	// test banner style with static constructor
	// should NOT indent the method opening bracket
	char text[] =
		"\npublic class FooClass {\n"
		"    private bool foo;\n"
		"    private int  bar;\n"
		"\n"
		"    static {\n"
		"        if (foo) {\n"
		"            bar = 0;\n"
		"            }\n"
		"        else\n"
		"            bar = 1;\n"
		"        }\n"
		"    }\n"
		"\n";
	char options[] = "style=banner, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileJava, Banner_Throws)
{
	// test banner style with throws statement
	// should be recognized as a block opener
	char text[] =
		"\npublic class FooClass {\n"
		"    static private bool foo;\n"
		"    static private int  bar;\n"
		"\n"
		"    public void fooBar() throws IOException {\n"
		"        if (foo) {\n"
		"            throw new IOException(bar);\n"
		"            }\n"
		"        }\n"
		"    }\n";
	char options[] = "style=banner, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileJava, Gnu_Interface)
{
	// test gnu style with interface
	// should not indent the interface
	char text[] =
		"\npublic interface FooIF\n"
		"{\n"
		"    public void foo1();\n"
		"    public void foo2();\n"
		"}\n";
	char options[] = "style=gnu, indent=spaces=4, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileJava, Gnu_NestedClass)
{
	// test gnu style with nested classes
	char text[] =
		"\npublic class A\n"
		"{\n"
		"    public int foo1;\n"
		"    public class B\n"
		"    {\n"
		"        public int foo2;\n"
		"        public class C\n"
		"        {\n"
		"            public void foo(bool isFoo)\n"
		"            {\n"
		"                if (isFoo)\n"
		"                    {\n"
		"                        bar();\n"
		"                    }\n"
		"                else\n"
		"                    anotherBar();\n"
		"            }\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "style=gnu, indent=spaces=4, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileJava, Gnu_StaticConstructor)
{
	// test gnu style with static constructor
	// sould NOT indent the method opening bracket
	char text[] =
		"\npublic class FooClass\n"
		"{\n"
		"    private bool foo;\n"
		"    private int  bar;\n"
		"\n"
		"    static\n"
		"    {\n"
		"        if (foo)\n"
		"            {\n"
		"                bar = 0;\n"
		"            }\n"
		"        else\n"
		"            bar = 1;\n"
		"    }\n"
		"}\n"
		"\n";
	char options[] = "style=gnu, indent=spaces=4, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileJava, Gnu_Throws)
{
	// test gnu style with a throws statement
	// should be recognized as a block opener
	char text[] =
		"\npublic class FooClass\n"
		"{\n"
		"    private bool foo;\n"
		"    private int  bar;\n"
		"\n"
		"    public void fooBar() throws IOException\n"
		"    {\n"
		"        if (foo)\n"
		"            {\n"
		"                throw new IOException(bar);\n"
		"            }\n"
		"    }\n"
		"}\n";
	char options[] = "style=gnu, indent=spaces=4, mode=java";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle C# Files
// Additional tests are in the brackets tests
//----------------------------------------------------------------------------

struct FileSharpF : public ::testing::Test
{
	string textStr;
	const char* textIn;

	FileSharpF()
	{
		textStr =
			"\nnamespace FooName\n"
			"{\n"
			"\n"
			"public class FooClass\n"
			"{\n"
			"    private bool var1;\n"
			"    private bool var2;\n"
			"\n"
			"    public void foo(bool isFoo)\n"
			"    {\n"
			"        if (isFoo)\n"
			"        {\n"
			"            bar();\n"
			"        }\n"
			"        else\n"
			"            anotherBar();\n"
			"    }\n"
			"}\n"
			"\n"
			"}   // end FooName\n";
		textIn = textStr.c_str();
	}
};

TEST_F(FileSharpF, Allman)
{
	// test allman style option
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"public class FooClass\n"
		"{\n"
		"    private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo)\n"
		"    {\n"
		"        if (isFoo)\n"
		"        {\n"
		"            bar();\n"
		"        }\n"
		"        else\n"
		"            anotherBar();\n"
		"    }\n"
		"}\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "style=allman, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileSharpF, Java)
{
	// test java style option
	char text[] =
		"\nnamespace FooName {\n"
		"\n"
		"public class FooClass {\n"
		"    private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo) {\n"
		"        if (isFoo) {\n"
		"            bar();\n"
		"        } else\n"
		"            anotherBar();\n"
		"    }\n"
		"}\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "style=java, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileSharpF, KR)
{
	// test k&r style option
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"public class FooClass\n"
		"{\n"
		"    private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo)\n"
		"    {\n"
		"        if (isFoo) {\n"
		"            bar();\n"
		"        } else\n"
		"            anotherBar();\n"
		"    }\n"
		"}\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "style=kr, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileSharpF, Stroustrup)
{
	// test stroustrup style option
	char text[] =
		"\nnamespace FooName {\n"
		"\n"
		"public class FooClass {\n"
		"     private bool var1;\n"
		"     private bool var2;\n"
		"\n"
		"     public void foo(bool isFoo)\n"
		"     {\n"
		"          if (isFoo) {\n"
		"               bar();\n"
		"          } else\n"
		"               anotherBar();\n"
		"     }\n"
		"}\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "style=stroustrup, indent=spaces=5, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileSharpF, Whitesmith)
{
	// test whitesmith style option
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"public class FooClass\n"
		"    {\n"
		"    private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo)\n"
		"        {\n"
		"        if (isFoo)\n"
		"            {\n"
		"            bar();\n"
		"            }\n"
		"        else\n"
		"            anotherBar();\n"
		"        }\n"
		"    }\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "style=whitesmith, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileSharpF, Banner)
{
	// test banner style option
	char text[] =
		"\nnamespace FooName {\n"
		"\n"
		"public class FooClass {\n"
		"    private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo) {\n"
		"        if (isFoo) {\n"
		"            bar();\n"
		"            }\n"
		"        else\n"
		"            anotherBar();\n"
		"        }\n"
		"    }\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "style=banner, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileSharpF, Gnu)
{
	// test gnu style option
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"public class FooClass\n"
		"{\n"
		"  private bool var1;\n"
		"  private bool var2;\n"
		"\n"
		"  public void foo(bool isFoo)\n"
		"  {\n"
		"    if (isFoo)\n"
		"      {\n"
		"        bar();\n"
		"      }\n"
		"    else\n"
		"      anotherBar();\n"
		"  }\n"
		"}\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "style=gnu, indent=spaces=2, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileSharpF, Linux)
{
	// test linux style option
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"public class FooClass\n"
		"{\n"
		"        private bool var1;\n"
		"        private bool var2;\n"
		"\n"
		"        public void foo(bool isFoo)\n"
		"        {\n"
		"                if (isFoo) {\n"
		"                        bar();\n"
		"                } else\n"
		"                        anotherBar();\n"
		"        }\n"
		"}\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "style=linux, indent=spaces=8, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileSharpF, Horstmann)
{
	// test horstmann style option
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"public class FooClass\n"
		"{  private bool var1;\n"
		"   private bool var2;\n"
		"\n"
		"   public void foo(bool isFoo)\n"
		"   {  if (isFoo)\n"
		"      {  bar();\n"
		"      }\n"
		"      else\n"
		"         anotherBar();\n"
		"   }\n"
		"}\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "style=horstmann, indent=spaces=3, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileSharpF, 1TBS)
{
	// test 1tbs style option
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"public class FooClass\n"
		"{\n"
		"    private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo)\n"
		"    {\n"
		"        if (isFoo) {\n"
		"            bar();\n"
		"        } else {\n"
		"            anotherBar();\n"
		"        }\n"
		"    }\n"
		"}\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "style=1tbs, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileSharpF, Pico)
{
	// test pico style option
	char text[] =
		"\nnamespace FooName\n"
		"{\n"
		"\n"
		"public class FooClass\n"
		"{   private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo)\n"
		"    {   if (isFoo)\n"
		"        {   bar(); }\n"
		"        else\n"
		"            anotherBar(); } }\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "style=pico, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(FileSharpF, Lisp)
{
	// test lisp style option
	char text[] =
		"\nnamespace FooName {\n"
		"\n"
		"public class FooClass {\n"
		"    private bool var1;\n"
		"    private bool var2;\n"
		"\n"
		"    public void foo(bool isFoo) {\n"
		"        if (isFoo) {\n"
		"            bar(); }\n"
		"        else\n"
		"            anotherBar(); } }\n"
		"\n"
		"}   // end FooName\n";
	char options[] = "style=lisp, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Whitesmith_Where)
{
	// test whitesmith style with a method that contains a where statement
	// should be recognized as a block opener
	char text[] =
		"\nvoid SetParent<T> (List<T> list) where T : INode\n"
		"    {\n"
		"    if (list != null)\n"
		"        {\n"
		"        foreach (T x in list)\n"
		"            {\n"
		"            x.Parent = parent;\n"
		"            }\n"
		"        }\n"
		"    }\n";
	char options[] = "style=whitesmith, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Whitesmith_WhereClass)
{
	// test whitesmith style with a class that contains a where statement
	char text[] =
		"\npublic sealed class Foo<A, B> : FooBar\n"
		"    where A : Bar1\n"
		"    where B : Bar2\n"
		"    {\n"
		"    int a;\n"
		"    int b;\n"
		"\n"
		"    protected override void Foo1()\n"
		"        {\n"
		"        if foo()\n"
		"            {\n"
		"            FooBar1();\n"
		"            }\n"
		"        }\n"
		"    }\n";
	char options[] = "style=whitesmith, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Whitesmith_NestedClass)
{
	// test whitesmith style with nested classes
	char text[] =
		"\npublic class A\n"
		"    {\n"
		"    public int foo1;\n"
		"    public class B\n"
		"        {\n"
		"        public int foo2;\n"
		"        public class C\n"
		"            {\n"
		"            public void foo(bool isFoo)\n"
		"                {\n"
		"                if (isFoo)\n"
		"                    {\n"
		"                    bar();\n"
		"                    }\n"
		"                else\n"
		"                    anotherBar();\n"
		"                }\n"
		"            }\n"
		"        }\n"
		"    }\n";
	char options[] = "style=whitesmith, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Whitesmith_NestedNamespace)
{
	// test whitesmith style with nested namespaces
	char text[] =
		"\nnamespace A\n"
		"{\n"
		"namespace B\n"
		"{\n"
		"namespace C\n"
		"{\n"
		"public class fooClass\n"
		"    {\n"
		"    void foo(bool isFoo)\n"
		"        {\n"
		"        if (isFoo)\n"
		"            {\n"
		"            bar();\n"
		"            }\n"
		"        else\n"
		"            anotherBar();\n"
		"        }\n"
		"    }\n"
		"}\n"
		"}\n"
		"}\n";
	char options[] = "style=whitesmith, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Whitesmith_NestedNamespace_IndentNamespaces)
{
	// test whitesmith style with nested indented namespaces
	char text[] =
		"\nnamespace A\n"
		"    {\n"
		"    namespace B\n"
		"        {\n"
		"        namespace C\n"
		"            {\n"
		"            public class fooClass\n"
		"                {\n"
		"                void foo(bool isFoo)\n"
		"                    {\n"
		"                    if (isFoo)\n"
		"                        {\n"
		"                        bar();\n"
		"                        }\n"
		"                    else\n"
		"                        anotherBar();\n"
		"                    }\n"
		"                }\n"
		"            }\n"
		"        }\n"
		"    }\n";
	char options[] = "style=whitesmith, indent-namespaces, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Whitesmith_NonInStatementArray1)
{
	// The isNonInStatementArray should NOT be cleared if a one-line statement is created.
	// If cleared the GetComponentType line is not indented.
	char textIn[] =
		"\npublic void ResolveIdentifier()\n"
		"{\n"
		"    ResolveResult groupByResolve = visitor(GroupBy);\n"
		"    DomReturnType resolved = new DomReturnType(GetType(new IReturnType[] {\n"
		"        GetComponentType(initializerResolve), groupByResolve}));\n"
		"}";
	char text[] =
		"\npublic void ResolveIdentifier()\n"
		"    {\n"
		"    ResolveResult groupByResolve = visitor(GroupBy);\n"
		"    DomReturnType resolved = new DomReturnType(GetType(new IReturnType[]\n"
		"        {\n"
		"        GetComponentType(initializerResolve), groupByResolve\n"
		"        }));\n"
		"    }";
	char options[] = "style=whitesmith, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Whitesmith_NonInStatementArray2)
{
	// The following "help" line should be indented.
	// A line beginning with '{' caused isNonInStatementArray to be cleared.
	char text[] =
		"\npublic static int Main ( string[] args )\n"
		"    {\n"
		"    optionSet = new OptionSet ()\n"
		"        {\n"
		"            { \"a=\", ( s, p ) => ProcessorValues[s] = p },\n"
		"            { \"h|?|help\", s => ShowHelp ( false ) }\n"
		"        };\n"
		"    }";
	char options[] = "style=whitesmith, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Banner_Where)
{
	// test banner style with a method that contains a where statement
	// should be recognized as a block opener
	char text[] =
		"\nvoid SetParent<T> (List<T> list) where T : INode {\n"
		"    if (list != null) {\n"
		"        foreach (T x in list) {\n"
		"            x.Parent = parent;\n"
		"            }\n"
		"        }\n"
		"    }\n";
	char options[] = "style=banner, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Banner_WhereClass)
{
	// test banner style with a class that contains a where statement
	char text[] =
		"\npublic sealed class Foo<A, B> : FooBar\n"
		"    where A : Bar1\n"
		"    where B : Bar2 {\n"
		"    int a;\n"
		"    int b;\n"
		"\n"
		"    protected override void Foo1() {\n"
		"        if foo() {\n"
		"            FooBar1();\n"
		"            }\n"
		"        }\n"
		"    }\n";
	char options[] = "style=banner, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Banner_NestedClass)
{
	// test banner style with nested classes
	char text[] =
		"\npublic class A {\n"
		"    public int foo1;\n"
		"    public class B {\n"
		"        public int foo2;\n"
		"        public class C {\n"
		"            public void foo(bool isFoo) {\n"
		"                if (isFoo) {\n"
		"                    bar();\n"
		"                    }\n"
		"                else\n"
		"                    anotherBar();\n"
		"                }\n"
		"            }\n"
		"        }\n"
		"    }\n";
	char options[] = "style=banner, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Banner_NestedNamespace)
{
	// test banner style with nested namespaces
	char text[] =
		"\nnamespace A {\n"
		"namespace B {\n"
		"namespace C {\n"
		"public class fooClass {\n"
		"    void foo(bool isFoo) {\n"
		"        if (isFoo) {\n"
		"            bar();\n"
		"            }\n"
		"        else\n"
		"            anotherBar();\n"
		"        }\n"
		"    }\n"
		"}\n"
		"}\n"
		"}\n";
	char options[] = "style=banner, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Banner_NestedNamespace_IndentNamespaces)
{
	// test banner style with nested indented namespaces
	char text[] =
		"\nnamespace A {\n"
		"    namespace B {\n"
		"        namespace C {\n"
		"            public class fooClass {\n"
		"                void foo(bool isFoo) {\n"
		"                    if (isFoo) {\n"
		"                        bar();\n"
		"                        }\n"
		"                    else\n"
		"                        anotherBar();\n"
		"                    }\n"
		"                }\n"
		"            }\n"
		"        }\n"
		"    }\n";
	char options[] = "style=banner, indent-namespaces, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Banner_NonInStatementArray1)
{
	// The isNonInStatementArray should NOT be cleared if a one-line statement is created.
	// If cleared the GetComponentType line is not indented.
	char textIn[] =
		"\npublic void ResolveIdentifier()\n"
		"{\n"
		"    ResolveResult groupByResolve = visitor(GroupBy);\n"
		"    DomReturnType resolved = new DomReturnType(GetType(new IReturnType[] {\n"
		"        GetComponentType(initializerResolve), groupByResolve}));\n"
		"}";
	char text[] =
		"\npublic void ResolveIdentifier() {\n"
		"    ResolveResult groupByResolve = visitor(GroupBy);\n"
		"    DomReturnType resolved = new DomReturnType(GetType(new IReturnType[] {\n"
		"        GetComponentType(initializerResolve), groupByResolve\n"
		"        }));\n"
		"    }";
	char options[] = "style=banner, mode=cs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Banner_NonInStatementArray2)
{
	// The following "help" line should be indented.
	// A line beginning with '{' caused isNonInStatementArray to be cleared.
	char text[] =
		"\npublic static int Main ( string[] args ) {\n"
		"    optionSet = new OptionSet () {\n"
		"            { \"a=\", ( s, p ) => ProcessorValues[s] = p },\n"
		"            { \"h|?|help\", s => ShowHelp ( false ) }\n"
		"        };\n"
		"    }";
	char options[] = "style=banner, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Gnu_Where)
{
	// test gnu style with a method that contains a where statement
	// should be recognized as a block opener
	char text[] =
		"\nvoid SetParent<T> (List<T> list) where T : INode\n"
		"{\n"
		"    if (list != null)\n"
		"        {\n"
		"            foreach (T x in list)\n"
		"                {\n"
		"                    x.Parent = parent;\n"
		"                }\n"
		"        }\n"
		"}\n";
	char options[] = "style=gnu, indent=spaces=4, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Gnu_WhereClass)
{
	// test gnu style with a class that contains a where statement
	char text[] =
		"\npublic sealed class Foo<A, B> : FooBar\n"
		"    where A : Bar1\n"
		"    where B : Bar2\n"
		"{\n"
		"    int a;\n"
		"    int b;\n"
		"\n"
		"    protected override void Foo1()\n"
		"    {\n"
		"        if foo()\n"
		"            {\n"
		"                FooBar1();\n"
		"            }\n"
		"    }\n"
		"}\n";
	char options[] = "style=gnu, indent=spaces=4, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Gnu_NestedClass)
{
	// test gnu style with interface and nested classes
	char text[] =
		"\npublic class A\n"
		"{\n"
		"    public int foo1;\n"
		"    public class B\n"
		"    {\n"
		"        public int foo2;\n"
		"        public class C\n"
		"        {\n"
		"            public void foo(bool isFoo)\n"
		"            {\n"
		"                if (isFoo)\n"
		"                    {\n"
		"                        bar();\n"
		"                    }\n"
		"                else\n"
		"                    anotherBar();\n"
		"            }\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "style=gnu, indent=spaces=4, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Gnu_NestedNamespace)
{
	// test gnu style with nested namespaces
	char text[] =
		"\nnamespace A\n"
		"{\n"
		"namespace B\n"
		"{\n"
		"namespace C\n"
		"{\n"
		"public class fooClass\n"
		"{\n"
		"    void foo(bool isFoo)\n"
		"    {\n"
		"        if (isFoo)\n"
		"            {\n"
		"                bar();\n"
		"            }\n"
		"        else\n"
		"            anotherBar();\n"
		"    }\n"
		"}\n"
		"}\n"
		"}\n"
		"}\n";
	char options[] = "style=gnu, indent=spaces=4, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(FileSharp, Gnu_NestedNamespace_IndentNamespace)
{
	// test gnu style with nested indented namespaces
	char text[] =
		"\nnamespace A\n"
		"{\n"
		"    namespace B\n"
		"    {\n"
		"        namespace C\n"
		"        {\n"
		"            public class fooClass\n"
		"            {\n"
		"                void foo(bool isFoo)\n"
		"                {\n"
		"                    if (isFoo)\n"
		"                        {\n"
		"                            bar();\n"
		"                        }\n"
		"                    else\n"
		"                        anotherBar();\n"
		"                }\n"
		"            }\n"
		"        }\n"
		"    }\n"
		"}\n";
	char options[] = "style=gnu, indent-namespaces, indent=spaces=4, mode=cs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	ASSERT_STREQ(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------

}  // namespace
