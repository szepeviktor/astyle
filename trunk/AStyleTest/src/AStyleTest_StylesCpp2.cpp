//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleTest.h"

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {

//----------------------------------------------------------------------------
// AStyle C++ text for style tests
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// AStyle C++ Linux Style
// Additional tests are in the linux brackets tests
//----------------------------------------------------------------------------

struct StyleLinuxCppF : public Test
{
	string textStr;
	const char* textIn;

	StyleLinuxCppF()
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
		    "    if (isFoo)\n"
		    "    {\n"
		    "        bar();\n"
		    "    }\n"
		    "    else\n"
		    "        anotherBar();\n"
		    "}\n"
		    "\n"
		    "}   // end FooName\n";
		textIn = textStr.c_str();
	}
};

TEST_F(StyleLinuxCppF, LongOption1)
{
	// test linux style option
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "class FooClass\n"
	    "{\n"
	    "private:\n"
	    "        bool var1;\n"
	    "        void func1();\n"
	    "protected:\n"
	    "        bool var2;\n"
	    "        void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo)\n"
	    "{\n"
	    "        if (isFoo) {\n"
	    "                bar();\n"
	    "        } else\n"
	    "                anotherBar();\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=linux, indent=spaces=8";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(StyleLinuxCppF, LongOption2)
{
	// test linux style option
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "class FooClass\n"
	    "{\n"
	    "private:\n"
	    "        bool var1;\n"
	    "        void func1();\n"
	    "protected:\n"
	    "        bool var2;\n"
	    "        void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo)\n"
	    "{\n"
	    "        if (isFoo) {\n"
	    "                bar();\n"
	    "        } else\n"
	    "                anotherBar();\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=knf, indent=spaces=8";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(StyleLinuxCppF, ShortOption)
{
	// test linux style short option
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "class FooClass\n"
	    "{\n"
	    "private:\n"
	    "        bool var1;\n"
	    "        void func1();\n"
	    "protected:\n"
	    "        bool var2;\n"
	    "        void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo)\n"
	    "{\n"
	    "        if (isFoo) {\n"
	    "                bar();\n"
	    "        } else\n"
	    "                anotherBar();\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "-A8, indent=spaces=8";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, SpaceIndent)
{
	// test linux style option with space indent of 6
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "      if (isFoo\n"
	    "          && isBar) {\n"
	    "            bar();\n"
	    "      } else\n"
	    "            anotherBar();\n"
	    "}\n";
	char options[] = "style=linux, indent=spaces=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, Tab)
{
	// test linux style option with tab indent
	// default indent is 8
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "	    && isBar) {\n"
	    "		bar();\n"
	    "	} else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "style=linux, indent=tab=8";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, TabIndent)
{
	// test linux style option with tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "	    && isBar) {\n"
	    "		bar();\n"
	    "	} else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "style=linux, indent=tab=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, ForceTab)
{
	// test linux style option with force tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "	    && isBar) {\n"
	    "		bar();\n"
	    "	} else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "style=linux, indent=force-tab=8";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, ForceTabIndent)
{
	// test linux style option with force tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "	    && isBar) {\n"
	    "		bar();\n"
	    "	} else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "style=linux, indent=force-tab=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, MinConditionalIndent1)
{
	// Linux should use a default setting of MINCOND_ONEHALF
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "                    && isBar)\n"
	    "    {\n"
	    "            bar();\n"
	    "    }\n"
	    "    else\n"
	    "            anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "        if (isFoo\n"
	    "            && isBar) {\n"
	    "                bar();\n"
	    "        } else\n"
	    "                anotherBar();\n"
	    "}\n";
	char options[] = "style=linux, indent=spaces=8";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, MinConditionalIndent2)
{
	// test linux style option with min conditional indent
	// Linux should ignore setting and use MINCOND_ONEHALF
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "                    && isBar)\n"
	    "    {\n"
	    "            bar();\n"
	    "    }\n"
	    "    else\n"
	    "            anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "        if (isFoo\n"
	    "            && isBar) {\n"
	    "                bar();\n"
	    "        } else\n"
	    "                anotherBar();\n"
	    "}\n";
	char options[] = "style=linux, min-conditional-indent=2, indent=spaces=8";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, NestedClass)
{
	// test nested classes
	char text[] =
	    "\nclass A\n"
	    "{\n"
	    "public:\n"
	    "    int foo1;\n"
	    "    class B\n"
	    "    {\n"
	    "    public:\n"
	    "        int foo2;\n"
	    "        class C\n"
	    "        {\n"
	    "        public:\n"
	    "            void foo(bool isFoo)\n"
	    "            {\n"
	    "                if (isFoo) {\n"
	    "                    bar();\n"
	    "                } else\n"
	    "                    anotherBar();\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=linux, indent=spaces=4";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, NestedClass_IndentClass)
{
	// test nested classes with indented classes
	char text[] =
	    "\nclass A\n"
	    "{\n"
	    "    public:\n"
	    "        int foo1;\n"
	    "        class B\n"
	    "        {\n"
	    "            public:\n"
	    "                int foo2;\n"
	    "                class C\n"
	    "                {\n"
	    "                    public:\n"
	    "                        void foo(bool isFoo)\n"
	    "                        {\n"
	    "                            if (isFoo) {\n"
	    "                                bar();\n"
	    "                            } else\n"
	    "                                anotherBar();\n"
	    "                        }\n"
	    "                }\n"
	    "        }\n"
	    "}\n";
	char options[] = "style=linux, indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, NestedNamespace)
{
	// test nested namespaces
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "namespace B\n"
	    "{\n"
	    "namespace C\n"
	    "{\n"
	    "void foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else\n"
	    "        anotherBar();\n"
	    "}\n"
	    "}\n"
	    "}\n"
	    "}\n";
	char options[] = "style=linux, indent=spaces=4";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, NestedNamespace_IndentNamespace)
{
	// test nested indented namespaces
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "    namespace B\n"
	    "    {\n"
	    "        namespace C\n"
	    "        {\n"
	    "            void foo(bool isFoo)\n"
	    "            {\n"
	    "                if (isFoo) {\n"
	    "                    bar();\n"
	    "                } else\n"
	    "                    anotherBar();\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=linux, indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, NestedNamespaceClass)
{
	// test namespaces within a class
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
	    "            void foo(bool isFoo)\n"
	    "            {\n"
	    "                if (isFoo) {\n"
	    "                    bar();\n"
	    "                } else\n"
	    "                    anotherBar();\n"
	    "            }\n"
	    "        }\n"
	    "        }\n"
	    "    }\n"
	    "    }\n"
	    "}\n"
	    "}\n";
	char options[] = "style=linux, indent=spaces=4";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, NestedNamespaceClass_IndentNamespace)
{
	// test indented namespaces within a class
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "    class A\n"
	    "    {\n"
	    "    public:\n"
	    "        namespace B\n"
	    "        {\n"
	    "            class B\n"
	    "            {\n"
	    "            public:\n"
	    "                namespace C\n"
	    "                {\n"
	    "                    class C\n"
	    "                    {\n"
	    "                    public:\n"
	    "                        void foo(bool isFoo)\n"
	    "                        {\n"
	    "                            if (isFoo) {\n"
	    "                                bar();\n"
	    "                            } else\n"
	    "                                anotherBar();\n"
	    "                        }\n"
	    "                    }\n"
	    "                }\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=linux, indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, NestedNamespaceClass_IndentNamespaceClass)
{
	// test indented namespaces within an indented class
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "    class A\n"
	    "    {\n"
	    "        public:\n"
	    "            namespace B\n"
	    "            {\n"
	    "                class B\n"
	    "                {\n"
	    "                    public:\n"
	    "                        namespace C\n"
	    "                        {\n"
	    "                            class C\n"
	    "                            {\n"
	    "                                public:\n"
	    "                                    void foo(bool isFoo)\n"
	    "                                    {\n"
	    "                                        if (isFoo) {\n"
	    "                                            bar();\n"
	    "                                        } else\n"
	    "                                            anotherBar();\n"
	    "                                    }\n"
	    "                            }\n"
	    "                        }\n"
	    "                }\n"
	    "            }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=linux, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, Pico)
{
	// test linux style with pico brackets
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar1();\n"
	    "        bar2(); }\n"
	    "    else\n"
	    "    {   anotherBar1();\n"
	    "        anotherBar2(); } }\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar1();\n"
	    "        bar2();\n"
	    "    } else {\n"
	    "        anotherBar1();\n"
	    "        anotherBar2();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=linux";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLinuxCpp, PicoOneLine)
{
	// test linux style with pico brackets and one-line blocks
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar(); }\n"
	    "    else\n"
	    "    {   anotherBar(); } }\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=linux";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle C++ Horstmann Style
// Additional tests are in the run-in brackets tests
//----------------------------------------------------------------------------

struct StyleHorstmannCppF : public Test
{
	string textStr;
	const char* textIn;

	StyleHorstmannCppF()
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
		    "    if (isFoo)\n"
		    "    {\n"
		    "        bar();\n"
		    "    }\n"
		    "    else\n"
		    "        anotherBar();\n"
		    "}\n"
		    "\n"
		    "}   // end FooName\n";
		textIn = textStr.c_str();
	}
};

TEST_F(StyleHorstmannCppF, LongOption)
{
	// test horstmann style option
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "class FooClass\n"
	    "{\n"
	    "private:\n"
	    "   bool var1;\n"
	    "   void func1();\n"
	    "protected:\n"
	    "   bool var2;\n"
	    "   void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo)\n"
	    "{  if (isFoo)\n"
	    "   {  bar();\n"
	    "   }\n"
	    "   else\n"
	    "      anotherBar();\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=horstmann, indent=spaces=3";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}


TEST_F(StyleHorstmannCppF, ShortOption)
{
	// test horstmann style short option
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "\n"
	    "class FooClass\n"
	    "{\n"
	    "private:\n"
	    "   bool var1;\n"
	    "   void func1();\n"
	    "protected:\n"
	    "   bool var2;\n"
	    "   void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo)\n"
	    "{  if (isFoo)\n"
	    "   {  bar();\n"
	    "   }\n"
	    "   else\n"
	    "      anotherBar();\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "-A9, indent=spaces=3";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, SpaceIndent)
{
	// test horstmann style option with space indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{     if (isFoo\n"
	    "                  && isBar)\n"
	    "      {     bar();\n"
	    "      }\n"
	    "      else\n"
	    "            anotherBar();\n"
	    "}\n";
	char options[] = "style=horstmann, indent=spaces=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, Tab)
{
	// test horstmann style option with tab indent
	// default indent is 3
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{	if (isFoo\n"
	    "	      && isBar)\n"
	    "	{	bar();\n"
	    "	}\n"
	    "	else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "style=horstmann, indent=tab=3";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, TabIndent)
{
	// test horstmann style option with tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{	if (isFoo\n"
	    "	            && isBar)\n"
	    "	{	bar();\n"
	    "	}\n"
	    "	else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "style=horstmann, indent=tab=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, ForceTab)
{
	// test horstmann style option with force tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{	if (isFoo\n"
	    "			&& isBar)\n"
	    "	{	bar();\n"
	    "	}\n"
	    "	else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "style=horstmann, indent=force-tab=3";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, ForceTabIndent)
{
	// test horstmann style option with force tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{	if (isFoo\n"
	    "			&& isBar)\n"
	    "	{	bar();\n"
	    "	}\n"
	    "	else\n"
	    "		anotherBar();\n"
	    "}\n";
	char options[] = "style=horstmann, indent=force-tab=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, MinConditionalIndent1)
{
	// horstmann should use a default setting of MINCOND_TWO
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{  if (isFoo\n"
	    "         && isBar)\n"
	    "   {  bar();\n"
	    "   }\n"
	    "   else\n"
	    "      anotherBar();\n"
	    "}\n";
	char options[] = "style=horstmann, indent=spaces=3";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, MinConditionalIndent2)
{
	// test horstmann style option with min conditional indent 0
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{  if (isFoo\n"
	    "       && isBar)\n"
	    "   {  bar();\n"
	    "   }\n"
	    "   else\n"
	    "      anotherBar();\n"
	    "}\n";
	char options[] = "style=horstmann, min-conditional-indent=0, indent=spaces=3";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, IndentedSwitchBlock)
{
	// test horstmann style with automatic switch block indent
	char text[] =
	    "\nvoid Foo(int fooBar)\n"
	    "{  switch (fooBar)\n"
	    "   {  case 1:\n"
	    "         fooBar = 1;\n"
	    "         break;\n"
	    "      case 2:\n"
	    "      {  fooBar = 2;\n"
	    "      }\n"
	    "      break;\n"
	    "      default:\n"
	    "         break;\n"
	    "   }\n"
	    "   int bar = true;\n"
	    "}\n";
	char options[] = "style=horstmann, indent=spaces=3";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, NestedClass)
{
	// test nested classes
	char text[] =
	    "\nclass A\n"
	    "{\n"
	    "public:\n"
	    "    int foo1;\n"
	    "    class B\n"
	    "    {\n"
	    "    public:\n"
	    "        int foo2;\n"
	    "        class C\n"
	    "        {\n"
	    "        public:\n"
	    "            void foo(bool isFoo)\n"
	    "            {   if (isFoo)\n"
	    "                {   bar();\n"
	    "                }\n"
	    "                else\n"
	    "                    anotherBar();\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=horstmann, indent=spaces=4";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, NestedClass_IndentClass)
{
	// test nested classes with indented classes
	char text[] =
	    "\nclass A\n"
	    "{   public:\n"
	    "        int foo1;\n"
	    "        class B\n"
	    "        {   public:\n"
	    "                int foo2;\n"
	    "                class C\n"
	    "                {   public:\n"
	    "                        void foo(bool isFoo)\n"
	    "                        {   if (isFoo)\n"
	    "                            {   bar();\n"
	    "                            }\n"
	    "                            else\n"
	    "                                anotherBar();\n"
	    "                        }\n"
	    "                }\n"
	    "        }\n"
	    "}\n";
	char options[] = "style=horstmann, indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, NestedNamespace)
{
	// test nested namespaces
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "namespace B\n"
	    "{\n"
	    "namespace C\n"
	    "{\n"
	    "void foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n"
	    "}\n"
	    "}\n"
	    "}\n";
	char options[] = "style=horstmann, indent=spaces=4";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, NestedNamespace_IndentNamespace)
{
	// test nested indented namespaces
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "    namespace B\n"
	    "    {\n"
	    "        namespace C\n"
	    "        {   void foo(bool isFoo)\n"
	    "            {   if (isFoo)\n"
	    "                {   bar();\n"
	    "                }\n"
	    "                else\n"
	    "                    anotherBar();\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=horstmann, indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, NestedNamespaceClass)
{
	// test namespaces within a class
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
	    "            void foo(bool isFoo)\n"
	    "            {   if (isFoo)\n"
	    "                {   bar();\n"
	    "                }\n"
	    "                else\n"
	    "                    anotherBar();\n"
	    "            }\n"
	    "        }\n"
	    "        }\n"
	    "    }\n"
	    "    }\n"
	    "}\n"
	    "}\n";
	char options[] = "style=horstmann, indent=spaces=4";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, NestedNamespaceClass_IndentNamespace)
{
	// test indented namespaces within a class
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "    class A\n"
	    "    {\n"
	    "    public:\n"
	    "        namespace B\n"
	    "        {\n"
	    "            class B\n"
	    "            {\n"
	    "            public:\n"
	    "                namespace C\n"
	    "                {\n"
	    "                    class C\n"
	    "                    {\n"
	    "                    public:\n"
	    "                        void foo(bool isFoo)\n"
	    "                        {   if (isFoo)\n"
	    "                            {   bar();\n"
	    "                            }\n"
	    "                            else\n"
	    "                                anotherBar();\n"
	    "                        }\n"
	    "                    }\n"
	    "                }\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=horstmann, indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, NestedNamespaceClass_IndentNamespaceClass)
{
	// test indented namespaces within an indented class
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "    class A\n"
	    "    {   public:\n"
	    "            namespace B\n"
	    "            {\n"
	    "                class B\n"
	    "                {   public:\n"
	    "                        namespace C\n"
	    "                        {\n"
	    "                            class C\n"
	    "                            {   public:\n"
	    "                                    void foo(bool isFoo)\n"
	    "                                    {   if (isFoo)\n"
	    "                                        {   bar();\n"
	    "                                        }\n"
	    "                                        else\n"
	    "                                            anotherBar();\n"
	    "                                    }\n"
	    "                            }\n"
	    "                        }\n"
	    "                }\n"
	    "            }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=horstmann, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, Pico)
{
	// test horstmann style with pico brackets
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar1();\n"
	    "        bar2(); }\n"
	    "    else\n"
	    "    {   anotherBar1();\n"
	    "        anotherBar2(); } }\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar1();\n"
	    "        bar2();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar1();\n"
	    "        anotherBar2();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleHorstmannCpp, PicoOneLine)
{
	// test horstmann style with pico brackets and one-line blocks
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar(); }\n"
	    "    else\n"
	    "    {   anotherBar(); } }\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar();\n"
	    "    }\n"
	    "    else\n"
	    "    {   anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=horstmann";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle C++ 1TBS Style
// Additional tests are in the break brackets tests
//----------------------------------------------------------------------------

struct Style1TBSCppF : public Test
{
	string textStr;
	const char* textIn;

	Style1TBSCppF()
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
		    "    if (isFoo)\n"
		    "    {\n"
		    "        bar();\n"
		    "    }\n"
		    "    else\n"
		    "        anotherBar();\n"
		    "}\n"
		    "\n"
		    "}   // end FooName\n";
		textIn = textStr.c_str();
	}
};

TEST_F(Style1TBSCppF, LongOption)
{
	// test 1tbs style option
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
	char options[] = "style=1tbs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(Style1TBSCppF, Alt)
{
	// test 1tbs style alternate otbs option
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
	char options[] = "style=otbs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(Style1TBSCppF, Short)
{
	// test 1tbs style short option
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
	char options[] = "-A10";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(Style1TBSCppF, AddOneLineBrackets)
{
	// add-one-line-brackets implies keep-one-line-blocks
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
	    "    } else\n"
	    "    { anotherBar(); }\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";;
	char options[] = "style=1tbs, add-one-line-brackets";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, SpaceIndent)
{
	// test 1tbs style option with space indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "      if (isFoo\n"
	    "                  && isBar) {\n"
	    "            bar();\n"
	    "      } else {\n"
	    "            anotherBar();\n"
	    "      }\n"
	    "}\n";
	char options[] = "style=1tbs, indent=spaces=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, Tab)
{
	// test 1tbs style option with tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "	        && isBar) {\n"
	    "		bar();\n"
	    "	} else {\n"
	    "		anotherBar();\n"
	    "	}\n"
	    "}\n";
	char options[] = "style=1tbs, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, TabIndent)
{
	// test 1tbs style option with tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "	            && isBar) {\n"
	    "		bar();\n"
	    "	} else {\n"
	    "		anotherBar();\n"
	    "	}\n"
	    "}\n";
	char options[] = "style=1tbs, indent=tab=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, ForceTab)
{
	// test 1tbs style option with force tab
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "			&& isBar) {\n"
	    "		bar();\n"
	    "	} else {\n"
	    "		anotherBar();\n"
	    "	}\n"
	    "}\n";
	char options[] = "style=1tbs, indent=force-tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, ForceTabIndent)
{
	// test 1tbs style option with force tab
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "	if (isFoo\n"
	    "			&& isBar) {\n"
	    "		bar();\n"
	    "	} else {\n"
	    "		anotherBar();\n"
	    "	}\n"
	    "}\n";
	char options[] = "style=1tbs, indent=force-tab=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, MinConditionalIndent1)
{
	// 1tbs should use a default setting of MINCOND_TWO
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=1tbs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, MinConditionalIndent2)
{
	// test 1tbs style option with min conditional indent 0
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "        && isBar) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=1tbs, min-conditional-indent=0";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, AddOneLineBrackets)
{
	// test 1tbs style option with add one line brackets
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar) {\n"
	    "        bar();\n"
	    "    } else\n"
	    "    { anotherBar(); }\n"
	    "}\n";
	char options[] = "style=1tbs, add-one-line-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, NestedClass)
{
	// test nested classes
	char text[] =
	    "\nclass A\n"
	    "{\n"
	    "public:\n"
	    "    int foo1;\n"
	    "    class B\n"
	    "    {\n"
	    "    public:\n"
	    "        int foo2;\n"
	    "        class C\n"
	    "        {\n"
	    "        public:\n"
	    "            void foo(bool isFoo)\n"
	    "            {\n"
	    "                if (isFoo) {\n"
	    "                    bar();\n"
	    "                } else {\n"
	    "                    anotherBar();\n"
	    "                }\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=1tbs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, NestedClass_IndentClass)
{
	// test nested classes with indented classes
	char text[] =
	    "\nclass A\n"
	    "{\n"
	    "    public:\n"
	    "        int foo1;\n"
	    "        class B\n"
	    "        {\n"
	    "            public:\n"
	    "                int foo2;\n"
	    "                class C\n"
	    "                {\n"
	    "                    public:\n"
	    "                        void foo(bool isFoo)\n"
	    "                        {\n"
	    "                            if (isFoo) {\n"
	    "                                bar();\n"
	    "                            } else {\n"
	    "                                anotherBar();\n"
	    "                            }\n"
	    "                        }\n"
	    "                }\n"
	    "        }\n"
	    "}\n";
	char options[] = "style=1tbs, indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, NestedNamespace)
{
	// test nested namespaces
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "namespace B\n"
	    "{\n"
	    "namespace C\n"
	    "{\n"
	    "void foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n"
	    "}\n"
	    "}\n"
	    "}\n";
	char options[] = "style=1tbs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, NestedNamespace_IndentNamespace)
{
	// test nested indented namespaces
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "    namespace B\n"
	    "    {\n"
	    "        namespace C\n"
	    "        {\n"
	    "            void foo(bool isFoo)\n"
	    "            {\n"
	    "                if (isFoo) {\n"
	    "                    bar();\n"
	    "                } else {\n"
	    "                    anotherBar();\n"
	    "                }\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=1tbs, indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, NestedNamespaceClass)
{
	// test namespaces within a class
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
	    "            void foo(bool isFoo)\n"
	    "            {\n"
	    "                if (isFoo) {\n"
	    "                    bar();\n"
	    "                } else {\n"
	    "                    anotherBar();\n"
	    "                }\n"
	    "            }\n"
	    "        }\n"
	    "        }\n"
	    "    }\n"
	    "    }\n"
	    "}\n"
	    "}\n";
	char options[] = "style=1tbs";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, NestedNamespaceClass_IndentNamespace)
{
	// test indented namespaces within a class
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "    class A\n"
	    "    {\n"
	    "    public:\n"
	    "        namespace B\n"
	    "        {\n"
	    "            class B\n"
	    "            {\n"
	    "            public:\n"
	    "                namespace C\n"
	    "                {\n"
	    "                    class C\n"
	    "                    {\n"
	    "                    public:\n"
	    "                        void foo(bool isFoo)\n"
	    "                        {\n"
	    "                            if (isFoo) {\n"
	    "                                bar();\n"
	    "                            } else {\n"
	    "                                anotherBar();\n"
	    "                            }\n"
	    "                        }\n"
	    "                    }\n"
	    "                }\n"
	    "            }\n"
	    "        }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=1tbs, indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, NestedNamespaceClass_IndentNamespaceClass)
{
	// test indented namespaces within an indented class
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "    class A\n"
	    "    {\n"
	    "        public:\n"
	    "            namespace B\n"
	    "            {\n"
	    "                class B\n"
	    "                {\n"
	    "                    public:\n"
	    "                        namespace C\n"
	    "                        {\n"
	    "                            class C\n"
	    "                            {\n"
	    "                                public:\n"
	    "                                    void foo(bool isFoo)\n"
	    "                                    {\n"
	    "                                        if (isFoo) {\n"
	    "                                            bar();\n"
	    "                                        } else {\n"
	    "                                            anotherBar();\n"
	    "                                        }\n"
	    "                                    }\n"
	    "                            }\n"
	    "                        }\n"
	    "                }\n"
	    "            }\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=1tbs, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, Pico)
{
	// test 1tbs style with pico brackets
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar1();\n"
	    "        bar2(); }\n"
	    "    else\n"
	    "        anotherBar1(); }\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar1();\n"
	    "        bar2();\n"
	    "    } else {\n"
	    "        anotherBar1();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=1tbs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(Style1TBSCpp, PicoOneLine)
{
	// test 1tbs style with pico brackets and one-line blocks
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar(); }\n"
	    "    else\n"
	    "        anotherBar(); }\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else {\n"
	    "        anotherBar();\n"
	    "    }\n"
	    "}\n";
	char options[] = "style=1tbs";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle C++ Google Style
// Additional tests are in the attach brackets tests
//----------------------------------------------------------------------------

struct StyleGoogleCppF : public Test
{
	string textStr;
	const char* textIn;

	StyleGoogleCppF()
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
		    "    if (isFoo)\n"
		    "    {\n"
		    "        bar();\n"
		    "    }\n"
		    "    else\n"
		    "        anotherBar();\n"
		    "}\n"
		    "\n"
		    "}   // end FooName\n";
		textIn = textStr.c_str();
	}
};

TEST_F(StyleGoogleCppF, LongOption)
{
	// test google style option
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "class FooClass {\n"
	    "  private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "  protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else\n"
	    "        anotherBar();\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=google";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(StyleGoogleCppF, Short)
{
	// test google style short option
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "class FooClass {\n"
	    "  private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "  protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar();\n"
	    "    } else\n"
	    "        anotherBar();\n"
	    "}\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "-A14";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleGoogleCpp, SpaceIndent)
{
	// test google style option with space indent
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "  private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "  protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};\n";
	char text[] =
	    "\nclass FooClass {\n"
	    "   private:\n"
	    "      bool var1;\n"
	    "      void func1();\n"
	    "   protected:\n"
	    "      bool var2;\n"
	    "      void func2();\n"
	    "};\n";
	char options[] = "style=google, indent=spaces=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleGoogleCpp, Tab)
{
	// test google style option with tab indent
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "  private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "  protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};\n";
	char text[] =
	    "\nclass FooClass {\n"
	    "  private:\n"
	    "	bool var1;\n"
	    "	void func1();\n"
	    "  protected:\n"
	    "	bool var2;\n"
	    "	void func2();\n"
	    "};\n";
	char options[] = "style=google, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleGoogleCpp, TabIndent)
{
	// test google style option with tab indent
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "  private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "  protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};\n";
	char text[] =
	    "\nclass FooClass {\n"
	    "   private:\n"
	    "	bool var1;\n"
	    "	void func1();\n"
	    "   protected:\n"
	    "	bool var2;\n"
	    "	void func2();\n"
	    "};\n";
	char options[] = "style=google, indent=tab=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleGoogleCpp, ForceTab)
{
	// test google style option with force tab
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "  private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "  protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};\n";
	char text[] =
	    "\nclass FooClass {\n"
	    "  private:\n"
	    "	bool var1;\n"
	    "	void func1();\n"
	    "  protected:\n"
	    "	bool var2;\n"
	    "	void func2();\n"
	    "};\n";
	char options[] = "style=google, indent=force-tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleGoogleCpp, ForceTabIndent)
{
	// test google style option with force tab
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "  private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "  protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};\n";
	char text[] =
	    "\nclass FooClass {\n"
	    "   private:\n"
	    "	bool var1;\n"
	    "	void func1();\n"
	    "   protected:\n"
	    "	bool var2;\n"
	    "	void func2();\n"
	    "};\n";
	char options[] = "style=google, indent=force-tab=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleGoogleCpp, IndentClasses)
{
	// test google style with indent classes
	// classes should NOT be indented
	char textIn[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "  private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "  protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};\n";
	char text[] =
	    "\nclass FooClass {\n"
	    "  private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "  protected:\n"
	    "    bool var2;\n"
	    "    void func2();\n"
	    "};\n";
	char options[] = "style=google, indent-classes";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle C++ Pico Style
//----------------------------------------------------------------------------

struct StylePicoCppF : public Test
{
	string textStr;
	const char* textIn;

	StylePicoCppF()
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
		    "    if (isFoo)\n"
		    "    {\n"
		    "        bar();\n"
		    "    }\n"
		    "    else\n"
		    "        anotherBar();\n"
		    "}\n"
		    "\n"
		    "}   // end FooName\n";
		textIn = textStr.c_str();
	}
};

TEST_F(StylePicoCppF, LongOption)
{
	// test pico style option
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
	    "    void func2(); };\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar(); }\n"
	    "    else\n"
	    "        anotherBar(); }\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(StylePicoCppF, ShortOption)
{
	// test pico style short option
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
	    "    void func2(); };\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar(); }\n"
	    "    else\n"
	    "        anotherBar(); }\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "-A11";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, SpaceIndent)
{
	// test pico style option with space indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{     if (isFoo\n"
	    "                  && isBar)\n"
	    "      {     bar(); }\n"
	    "      else\n"
	    "            anotherBar(); }\n";
	char options[] = "style=pico, indent=spaces=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, Tab)
{
	// test pico style option with tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{	if (isFoo\n"
	    "	        && isBar)\n"
	    "	{	bar(); }\n"
	    "	else\n"
	    "		anotherBar(); }\n";
	char options[] = "style=pico, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, TabIndent)
{
	// test pico style option with tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{	if (isFoo\n"
	    "	            && isBar)\n"
	    "	{	bar(); }\n"
	    "	else\n"
	    "		anotherBar(); }\n";
	char options[] = "style=pico, indent=tab=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, ForceTab)
{
	// test pico style option with force tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{	if (isFoo\n"
	    "			&& isBar)\n"
	    "	{	bar(); }\n"
	    "	else\n"
	    "		anotherBar(); }\n";
	char options[] = "style=pico, indent=force-tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, ForceTabIndent)
{
	// test pico style option with force tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{	if (isFoo\n"
	    "			&& isBar)\n"
	    "	{	bar(); }\n"
	    "	else\n"
	    "		anotherBar(); }\n";
	char options[] = "style=pico, indent=force-tab=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, MinConditionalIndent1)
{
	// pico should use a default setting of MINCOND_TWO
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo\n"
	    "            && isBar)\n"
	    "    {   bar(); }\n"
	    "    else\n"
	    "        anotherBar(); }\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, MinConditionalIndent2)
{
	// test pico style option with min conditional indent 0
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{   if (isFoo\n"
	    "        && isBar)\n"
	    "    {   bar(); }\n"
	    "    else\n"
	    "        anotherBar(); }\n";
	char options[] = "style=pico, min-conditional-indent=0";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, SwitchBlock1)
{
	// test pico style with switch blocks
	char text[] =
	    "\nvoid Foo(int fooBar)\n"
	    "{   switch (fooBar)\n"
	    "    {   case 1:\n"
	    "            fooBar = 1;\n"
	    "            break;\n"
	    "        case 2:\n"
	    "        {   fooBar = 2; }\n"
	    "        break;\n"
	    "        default:\n"
	    "        {   break; } }\n"
	    "    int bar = true; }\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, SwitchBlock2)
{
	// test pico style with multiple switch block endings on a line
	char text[] =
	    "\nwxString foo()\n"
	    "{   switch ( Lang )\n"
	    "    {   case wxsCPP:\n"
	    "        {   switch ( ch )\n"
	    "            {   case 2:\n"
	    "                    break; } } }\n"
	    "    return wxEmptyString; }\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, SwitchBlock3)
{
	// test pico style with switch blocks
	// this was a problem with the indent of the line after 'default'
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (isBar)\n"
	    "    {   switch (foobar)\n"
	    "        {   case:\n"
	    "            {   break; }\n"
	    "            default:\n"
	    "            {   isErr(); } }\n"
	    "\n"
	    "    } }\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, SwitchBlock_OneLine)
{
	// test pico style with switch blocks with one line statements
	// the 'for' statement should be indented correctly
	char text[] =
	    "\nvoid foo()\n"
	    "{   switch ( id )\n"
	    "    {   case myID_CHARSETMAC:\n"
	    "        {   switch ( event.GetId() )\n"
	    "            {   case myID_CHARSETANSI: {charset = wxSCI_CHARSET_ANSI; break;}\n"
	    "                case myID_CHARSETMAC:  {charset = wxSCI_CHARSET_ANSI; break;} }\n"
	    "\n"
	    "            for ( Nr = 0; Nr < wxSCI_STYLE_LASTPREDEFINED; Nr++ )\n"
	    "            {   stcCtrl->StyleSetCharacterSet ( Nr, charset ); }\n"
	    "\n"
	    "            break; } //case\n"
	    "    } }\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, KeepOneLineBlocks1)
{
	// pico style implies keep-one-line-blocks
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (isBar)\n"
	    "    { x = 1; y = 2; } }\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, KeepOneLineBlocks2)
{
	// keep the following one line block
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (ifFoo) {;/*OK Use exe path*/ } }\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, KeepOneLineStatements)
{
	// pico style implies keep-one-line-statements
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo)\n"
	    "    {   isFoo1=false; isBar1=true;\n"
	    "        isFoo2=false; isBa2r=true; } }\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, AddBrackets1)
{
	// pico style add-brackets implies add-one-line-brackets
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo)\n"
	    "        isFoo1=false; }\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo)\n"
	    "    { isFoo1=false; } }\n";
	char options[] = "style=pico, add-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, AddBrackets2)
{
	// pico style add-brackets implies add-one-line-brackets
	// add-brackets with this will not format correctly
	// it must be converted to add-one-line-brackets
	char textIn[] =
	    "\nbool foo()\n"
	    "{   // comment\n"
	    "    if (isFoo)\n"
	    "        return;    // true;\n"
	    "}\n";
	char text[] =
	    "\nbool foo()\n"
	    "{   // comment\n"
	    "    if (isFoo)\n"
	    "    { return; }    // true;\n"
	    "}\n";
	char options[] = "style=pico, add-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, AddOneLineBrackets)
{
	// pico style does support add-one-line-brackets
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo)\n"
	    "        isFoo1=false; }\n";
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo)\n"
	    "    { isFoo1=false; } }\n";
	char options[] = "style=pico, add-one-line-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, BreakNamespaceClass)
{
	// always break a namespace and class
	char textIn[] =
	    "\nnamespace FooName {\n"
	    "class FooClass\n"
	    "{   bool foo()\n"
	    "    {   return false; } }; }\n";
	char text[] =
	    "\nnamespace FooName\n"
	    "{\n"
	    "class FooClass\n"
	    "{   bool foo()\n"
	    "    {   return false; } }; }\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, NestedClass)
{
	// test nested classes
	char text[] =
	    "\nclass A\n"
	    "{\n"
	    "public:\n"
	    "    int foo1;\n"
	    "    class B\n"
	    "    {\n"
	    "    public:\n"
	    "        int foo2;\n"
	    "        class C\n"
	    "        {\n"
	    "        public:\n"
	    "            void foo(bool isFoo)\n"
	    "            {   if (isFoo)\n"
	    "                {   bar(); }\n"
	    "                else\n"
	    "                    anotherBar(); } } } }\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, NestedClass_IndentClass)
{
	// test nested classes with indented classes
	char text[] =
	    "\nclass A\n"
	    "{   public:\n"
	    "        int foo1;\n"
	    "        class B\n"
	    "        {   public:\n"
	    "                int foo2;\n"
	    "                class C\n"
	    "                {   public:\n"
	    "                        void foo(bool isFoo)\n"
	    "                        {   if (isFoo)\n"
	    "                            {   bar(); }\n"
	    "                            else\n"
	    "                                anotherBar(); } } } }\n";
	char options[] = "style=pico, indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, NestedNamespace)
{
	// test nested namespaces
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "namespace B\n"
	    "{\n"
	    "namespace C\n"
	    "{\n"
	    "void foo(bool isFoo)\n"
	    "{   if (isFoo)\n"
	    "    {   bar(); }\n"
	    "    else\n"
	    "        anotherBar(); } } } }\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, NestedNamespace_IndentNamespace)
{
	// test nested indented namespaces
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "    namespace B\n"
	    "    {\n"
	    "        namespace C\n"
	    "        {   void foo(bool isFoo)\n"
	    "            {   if (isFoo)\n"
	    "                {   bar(); }\n"
	    "                else\n"
	    "                    anotherBar(); } } } }\n";
	char options[] = "style=pico, indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, NestedNamespaceClass)
{
	// test namespaces within a class
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
	    "            void foo(bool isFoo)\n"
	    "            {   if (isFoo)\n"
	    "                {   bar(); }\n"
	    "                else\n"
	    "                    anotherBar(); } } } } } } }\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, NestedNamespaceClass_IndentNamespace)
{
	// test indented namespaces within a class
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "    class A\n"
	    "    {\n"
	    "    public:\n"
	    "        namespace B\n"
	    "        {\n"
	    "            class B\n"
	    "            {\n"
	    "            public:\n"
	    "                namespace C\n"
	    "                {\n"
	    "                    class C\n"
	    "                    {\n"
	    "                    public:\n"
	    "                        void foo(bool isFoo)\n"
	    "                        {   if (isFoo)\n"
	    "                            {   bar(); }\n"
	    "                            else\n"
	    "                                anotherBar(); } } } } } } }\n";
	char options[] = "style=pico, indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, NestedNamespaceClass_IndentNamespaceClass)
{
	// test indented namespaces within an indented class
	char text[] =
	    "\nnamespace A\n"
	    "{\n"
	    "    class A\n"
	    "    {   public:\n"
	    "            namespace B\n"
	    "            {\n"
	    "                class B\n"
	    "                {   public:\n"
	    "                        namespace C\n"
	    "                        {\n"
	    "                            class C\n"
	    "                            {   public:\n"
	    "                                    void foo(bool isFoo)\n"
	    "                                    {   if (isFoo)\n"
	    "                                        {   bar(); }\n"
	    "                                        else\n"
	    "                                            anotherBar(); } } } } } } }\n";
	char options[] = "style=pico, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, KeepOneLineNamespace)
{
	// the following namespace should not be broken
	char text[] =
	    "\nnamespace compatibility { typedef long int>::eval tree_cookie_t; }\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, AttachedClosingNamespace1)
{
	// the final line should be correctly indented
	char text[] =
	    "\nnamespace\n"
	    "{\n"
	    "class FooClass\n"
	    "{\n"
	    "public:\n"
	    "    int foo;\n"
	    "    // comment\n"
	    "}; }\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, AttachedClosingNamespace2)
{
	// the final line should be correctly indented
	char text[] =
	    "\ntemplate< typename T1, typename T2 > struct Convert\n"
	    "{   inline T2 operator()( const T1& val ) { return (T2)val; } };\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, AfterPreprocessor1)
{
	// closing brackets should not be broken after a preprocessor statement
	char text[] =
	    "\n#ifdef __WIN32__\n"
	    "void foo() { SetEnvironmentVariable (k, v); }\n"
	    "#endif\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, AfterPreprocessor2)
{
	// closing brackets should not be broken after a preprocessor statement
	char text[] =
	    "\nvoid foo()\n"
	    "{   if (isFoo)\n"
	    "    {\n"
	    "#endif\n"
	    "        if (isBar) { QueryValue(m_MasterPath); } } }\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, UserData)
{
	// test from user requesting the style
	char text[] =
	    "\nddhisttohistogram(struct tgl l, int size, void *data)\n"
	    "{ // adds the data to the histogram (l->g).\n"
	    "  int i, j, *q;\n"
	    "  if (data != NULL)\n"
	    "  { if ((size > sizeof(int)) && (l != NULL))\n"
	    "    { q = &(((int *)data)[1]);\n"
	    "      j = size / sizeof(int) - 1;\n"
	    "      if (j > l->samples)j = l->samples;\n"
	    "      if(l->logscale==1)\n"
	    "      { pthread_mutex_lock(&(l->update));\n"
	    "        for (i = 0; i < j; i++)\n"
	    "          a[i] += q[i];\n"
	    "        pthread_mutex_unlock(&(l->update)); }\n"
	    "      else\n"
	    "      { pthread_mutex_lock(&(l->update));\n"
	    "        for (i = 0; i < j; i++)\n"
	    "          a[i] += q[i];\n"
	    "        pthread_mutex_unlock(&(l->update)); } }\n"
	    "    free(data); } }\n";
	char options[] = "style=pico, indent=spaces=2";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, SansPreprocessor)
{
	// don't attach to a preprocessor line
	char text[] =
	    "\nvoid foo()\n"
	    "{   A = 0;\n"
	    "#ifdef ERR1\n"
	    "    B = 1;\n"
	    "#endif\n"
	    "}\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, SansPreprocessorBreak)
{
	// don't break empty brackets after a preprocessor
	char text[] =
	    "\nclass FooClass\n"
	    "{\n"
	    "#ifdef DEBUG_chardet\n"
	    "    void foo() { }\n"
	    "#endif\n"
	    "}\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, SansLineComment1)
{
	// don't attach to a end-of-line comment
	char text[] =
	    "\nvoid foo()\n"
	    "{   A = 0;\n"
	    "    B = 1;\n"
	    "    // comment\n"
	    "}\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, SansLineComment2)
{
	// don't attach to a end-of-line comment
	char text[] =
	    "\nvoid foo()\n"
	    "{   A = 0;\n"
	    "    B = 1;  // comment\n"
	    "}\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, SansComment1)
{
	// don't attach to a  comment
	char text[] =
	    "\nvoid foo()\n"
	    "{   A = 0;\n"
	    "    B = 1;\n"
	    "    /* comment */\n"
	    "}\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, SansComment2)
{
	// don't attach to a  comment
	char text[] =
	    "\nvoid foo()\n"
	    "{   A = 0;\n"
	    "    B = 1;  /* comment */\n"
	    "}\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, SansEmptyLine)
{
	// don't attach to a empty line
	char text[] =
	    "\nvoid foo()\n"
	    "{   A = 0;\n"
	    "    B = 1;\n"
	    "\n"
	    "}\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StylePicoCpp, IndentArray1)
{
	// test array indentation
	char textIn[] =
	    "\nFooArray[] =\n"
	    "{\n"
	    "    { 1,  5,  10 },\n"
	    "    { 2,  6,  11 },\n"
	    "    { 3,  6,  12 }\n"
	    "};\n";
	char text[] =
	    "\nFooArray[] =\n"
	    "{   { 1,  5,  10 },\n"
	    "    { 2,  6,  11 },\n"
	    "    { 3,  6,  12 } };\n";
	char options[] = "style=pico";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// AStyle C++ Lisp Style
//----------------------------------------------------------------------------

struct StyleLispCppF : public Test
{
	string textStr;
	const char* textIn;

	StyleLispCppF()
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
		    "    if (isFoo)\n"
		    "    {\n"
		    "        bar();\n"
		    "    }\n"
		    "    else\n"
		    "        anotherBar();\n"
		    "}\n"
		    "\n"
		    "}   // end FooName\n";
		textIn = textStr.c_str();
	}
};

TEST_F(StyleLispCppF, LispOption)
{
	// test lisp style long option
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "class FooClass {\n"
	    "private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "protected:\n"
	    "    bool var2;\n"
	    "    void func2(); };\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar(); }\n"
	    "    else\n"
	    "        anotherBar(); }\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(StyleLispCppF, PythonOption)
{
	// test lisp style python option
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "class FooClass {\n"
	    "private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "protected:\n"
	    "    bool var2;\n"
	    "    void func2(); };\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar(); }\n"
	    "    else\n"
	    "        anotherBar(); }\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "style=python";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST_F(StyleLispCppF, ShortOption)
{
	// test lisp style short option
	char text[] =
	    "\nnamespace FooName {\n"
	    "\n"
	    "class FooClass {\n"
	    "private:\n"
	    "    bool var1;\n"
	    "    void func1();\n"
	    "protected:\n"
	    "    bool var2;\n"
	    "    void func2(); };\n"
	    "\n"
	    "void FooClass::Foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar(); }\n"
	    "    else\n"
	    "        anotherBar(); }\n"
	    "\n"
	    "}   // end FooName\n";
	char options[] = "-A12";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, SpaceIndent)
{
	// test lisp style option with space indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo) {\n"
	    "      if (isFoo\n"
	    "                  && isBar) {\n"
	    "            bar(); }\n"
	    "      else\n"
	    "            anotherBar(); }\n";
	char options[] = "style=lisp, indent=spaces=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, Tab)
{
	// test lisp style option with tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo) {\n"
	    "	if (isFoo\n"
	    "	        && isBar) {\n"
	    "		bar(); }\n"
	    "	else\n"
	    "		anotherBar(); }\n";
	char options[] = "style=lisp, indent=tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, TabIndent)
{
	// test lisp style option with tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo) {\n"
	    "	if (isFoo\n"
	    "	            && isBar) {\n"
	    "		bar(); }\n"
	    "	else\n"
	    "		anotherBar(); }\n";
	char options[] = "style=lisp, indent=tab=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, ForceTab)
{
	// test lisp style option with force tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo) {\n"
	    "	if (isFoo\n"
	    "			&& isBar) {\n"
	    "		bar(); }\n"
	    "	else\n"
	    "		anotherBar(); }\n";
	char options[] = "style=lisp, indent=force-tab";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, ForceTabIndent)
{
	// test lisp style option with force tab indent
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo) {\n"
	    "	if (isFoo\n"
	    "			&& isBar) {\n"
	    "		bar(); }\n"
	    "	else\n"
	    "		anotherBar(); }\n";
	char options[] = "style=lisp, indent=force-tab=6";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, MinConditionalIndent1)
{
	// pico should use a default setting of MINCOND_TWO
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo) {\n"
	    "    if (isFoo\n"
	    "            && isBar) {\n"
	    "        bar(); }\n"
	    "    else\n"
	    "        anotherBar(); }\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, MinConditionalIndent2)
{
	// test lisp style option with min conditional indent 0
	char textIn[] =
	    "\nvoid Foo(bool isFoo)\n"
	    "{\n"
	    "    if (isFoo\n"
	    "            && isBar)\n"
	    "    {\n"
	    "        bar();\n"
	    "    }\n"
	    "    else\n"
	    "        anotherBar();\n"
	    "}\n";
	char text[] =
	    "\nvoid Foo(bool isFoo) {\n"
	    "    if (isFoo\n"
	    "        && isBar) {\n"
	    "        bar(); }\n"
	    "    else\n"
	    "        anotherBar(); }\n";
	char options[] = "style=lisp, min-conditional-indent=0";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, SwitchBlock1)
{
	// test lisp style with switch blocks
	char text[] =
	    "\nvoid Foo(int fooBar) {\n"
	    "    switch (fooBar) {\n"
	    "    case 1:\n"
	    "        fooBar = 1;\n"
	    "        break;\n"
	    "    case 2: {\n"
	    "        fooBar = 2; }\n"
	    "    break;\n"
	    "    default: {\n"
	    "        break; } }\n"
	    "    int bar = true; }\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, SwitchBlock2)
{
	// test lisp style with multiple switch block endings on a line
	char text[] =
	    "\nwxString foo() {\n"
	    "    switch ( Lang ) {\n"
	    "    case wxsCPP: {\n"
	    "        switch ( ch ) {\n"
	    "        case 2:\n"
	    "            break; } } }\n"
	    "    return wxEmptyString; }\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, SwitchBlock3)
{
	// test lisp style with switch blocks
	// this was a problem with the indent of the line after 'default'
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isBar) {\n"
	    "        switch (foobar) {\n"
	    "        case: {\n"
	    "            break; }\n"
	    "        default: {\n"
	    "            isErr(); } }\n"
	    "\n"
	    "    } }\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, SwitchBlock_OneLine)
{
	// test lisp style with switch blocks with one line statements
	// the 'for' statement should be indented correctly
	char textIn[] =
	    "\nvoid foo() {\n"
	    "    switch ( id ) {\n"
	    "    case myID_CHARSETMAC: {\n"
	    "        switch ( event.GetId() ) {\n"
	    "        case myID_CHARSETANSI: {charset = wxSCI_CHARSET_ANSI; break;}\n"
	    "        case myID_CHARSETMAC:  {charset = wxSCI_CHARSET_ANSI; break;} }\n"
	    "\n"
	    "        for ( Nr = 0; Nr < wxSCI_STYLE_LASTPREDEFINED; Nr++ ) {\n"
	    "            stcCtrl->StyleSetCharacterSet ( Nr, charset ); }\n"
	    "\n"
	    "        break; } //case\n"
	    "    } }\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    switch ( id ) {\n"
	    "    case myID_CHARSETMAC: {\n"
	    "        switch ( event.GetId() ) {\n"
	    "        case myID_CHARSETANSI: {\n"
	    "            charset = wxSCI_CHARSET_ANSI;\n"
	    "            break; }\n"
	    "        case myID_CHARSETMAC:  {\n"
	    "            charset = wxSCI_CHARSET_ANSI;\n"
	    "            break; } }\n"
	    "\n"
	    "        for ( Nr = 0; Nr < wxSCI_STYLE_LASTPREDEFINED; Nr++ ) {\n"
	    "            stcCtrl->StyleSetCharacterSet ( Nr, charset ); }\n"
	    "\n"
	    "        break; } //case\n"
	    "    } }\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, SwitchBlock_KeepOneLine)
{
	// test lisp style with switch blocks with keep-one-line-blocks
	char text[] =
	    "\nvoid foo() {\n"
	    "    switch ( id ) {\n"
	    "    case myID_CHARSETMAC: {\n"
	    "        switch ( event.GetId() ) {\n"
	    "        case myID_CHARSETANSI: {charset = wxSCI_CHARSET_ANSI; break;}\n"
	    "        case myID_CHARSETMAC:  {charset = wxSCI_CHARSET_ANSI; break;} }\n"
	    "\n"
	    "        for ( Nr = 0; Nr < wxSCI_STYLE_LASTPREDEFINED; Nr++ ) {\n"
	    "            stcCtrl->StyleSetCharacterSet ( Nr, charset ); }\n"
	    "\n"
	    "        break; } //case\n"
	    "    } }\n";
	char options[] = "style=lisp, keep-one-line-blocks";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, KeepOneLineBlocks1)
{
	// lisp style should NOT imply keep-one-line-blocks
	char textIn[] =
	    "\nvoid foo() {\n"
	    "    if (isBar)\n"
	    "    { x = 1; y = 2; } }\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isBar) {\n"
	    "        x = 1;\n"
	    "        y = 2; } }\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, KeepOneLineBlocks2)
{
	// don't keep the following one line block
	char textIn[] =
	    "\nvoid foo()\n"
	    "{   if (ifFoo) {;/*OK Use exe path*/ } }\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (ifFoo) {\n"
	    "        ;/*OK Use exe path*/\n"
	    "    } }\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, KeepOneLineStatements)
{
	// lisp style implies keep-one-line-statements
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo) {\n"
	    "        isFoo1=false; isBar1=true;\n"
	    "        isFoo2=false; isBa2r=true; } }\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, AddBrackets1)
{
	// lisp style add-brackets does NOT imply add-one-line-brackets
	char textIn[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo)\n"
	    "        isFoo1=false; }\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo) {\n"
	    "        isFoo1=false; } }\n";
	char options[] = "style=lisp, add-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, AddBrackets2)
{
	// lisp style add-one-line-brackets implies add-brackets
	char textIn[] =
	    "\nbool foo() {\n"
	    "    // comment\n"
	    "    if (isFoo)\n"
	    "        return;    // true;\n"
	    "}\n";
	char text[] =
	    "\nbool foo() {\n"
	    "    // comment\n"
	    "    if (isFoo) {\n"
	    "        return; }    // true;\n"
	    "}\n";
	char options[] = "style=lisp, add-one-line-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, AddOneLineBrackets)
{
	// lisp style does NOT support add-one-line-brackets
	// they are converted to add-brackets
	char textIn[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo)\n"
	    "        isFoo1=false; }\n";
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo) {\n"
	    "        isFoo1=false; } }\n";
	char options[] = "style=lisp, add-one-line-brackets";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, AttachNamespaceClass)
{
	// always attach a namespace and class
	char textIn[] =
	    "\nnamespace FooName {\n"
	    "class FooClass\n"
	    "{   bool foo()\n"
	    "    {   return false; } }; }\n";
	char text[] =
	    "\nnamespace FooName {\n"
	    "class FooClass {\n"
	    "    bool foo() {\n"
	    "        return false; } }; }\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, NestedClass)
{
	// test nested classes
	char text[] =
	    "\nclass A {\n"
	    "public:\n"
	    "    int foo1;\n"
	    "    class B {\n"
	    "    public:\n"
	    "        int foo2;\n"
	    "        class C {\n"
	    "        public:\n"
	    "            void foo(bool isFoo) {\n"
	    "                if (isFoo) {\n"
	    "                    bar(); }\n"
	    "                else\n"
	    "                    anotherBar(); } } } }\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, NestedClass_IndentClass)
{
	// test nested classes with indented classes
	char text[] =
	    "\nclass A {\n"
	    "    public:\n"
	    "        int foo1;\n"
	    "        class B {\n"
	    "            public:\n"
	    "                int foo2;\n"
	    "                class C {\n"
	    "                    public:\n"
	    "                        void foo(bool isFoo) {\n"
	    "                            if (isFoo) {\n"
	    "                                bar(); }\n"
	    "                            else\n"
	    "                                anotherBar(); } } } }\n";
	char options[] = "style=lisp, indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, NestedNamespace)
{
	// test nested namespaces
	char text[] =
	    "\nnamespace A {\n"
	    "namespace B {\n"
	    "namespace C {\n"
	    "void foo(bool isFoo) {\n"
	    "    if (isFoo) {\n"
	    "        bar(); }\n"
	    "    else\n"
	    "        anotherBar(); } } } }\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, NestedNamespace_IndentNamespace)
{
	// test nested indented namespaces
	char text[] =
	    "\nnamespace A {\n"
	    "    namespace B {\n"
	    "        namespace C {\n"
	    "            void foo(bool isFoo) {\n"
	    "                if (isFoo) {\n"
	    "                    bar(); }\n"
	    "                else\n"
	    "                    anotherBar(); } } } }\n";
	char options[] = "style=lisp, indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, NestedNamespaceClass)
{
	// test namespaces within a class
	char text[] =
	    "\nnamespace A {\n"
	    "class A {\n"
	    "public:\n"
	    "    namespace B {\n"
	    "    class B {\n"
	    "    public:\n"
	    "        namespace C {\n"
	    "        class C {\n"
	    "        public:\n"
	    "            void foo(bool isFoo) {\n"
	    "                if (isFoo) {\n"
	    "                    bar(); }\n"
	    "                else\n"
	    "                    anotherBar(); } } } } } } }\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, NestedNamespaceClass_IndentNamespace)
{
	// test indented namespaces within a class
	char text[] =
	    "\nnamespace A {\n"
	    "    class A {\n"
	    "    public:\n"
	    "        namespace B {\n"
	    "            class B {\n"
	    "            public:\n"
	    "                namespace C {\n"
	    "                    class C {\n"
	    "                    public:\n"
	    "                        void foo(bool isFoo) {\n"
	    "                            if (isFoo) {\n"
	    "                                bar(); }\n"
	    "                            else\n"
	    "                                anotherBar(); } } } } } } }\n";
	char options[] = "style=lisp, indent-namespaces";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, NestedNamespaceClass_IndentNamespaceClass)
{
	// test indented namespaces within an indented class
	char text[] =
	    "\nnamespace A {\n"
	    "    class A {\n"
	    "        public:\n"
	    "            namespace B {\n"
	    "                class B {\n"
	    "                    public:\n"
	    "                        namespace C {\n"
	    "                            class C {\n"
	    "                                public:\n"
	    "                                    void foo(bool isFoo) {\n"
	    "                                        if (isFoo) {\n"
	    "                                            bar(); }\n"
	    "                                        else\n"
	    "                                            anotherBar(); } } } } } } }\n";
	char options[] = "style=lisp, indent-namespaces, indent-classes";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, KeepOneLineNamespace)
{
	// the following namespace should be broken
	char textIn[] =
	    "\nnamespace compatibility { typedef long int>::eval tree_cookie_t; }\n";
	char text[] =
	    "\nnamespace compatibility {\n"
	    "typedef long int>::eval tree_cookie_t; }\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, AttachedClosingNamespace1)
{
	// the final line should be correctly indented
	char text[] =
	    "\nnamespace {\n"
	    "class FooClass {\n"
	    "public:\n"
	    "    int foo;\n"
	    "    // comment\n"
	    "}; }\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, AttachedClosingNamespace2)
{
	// the final line should be correctly indented
	char text[] =
	    "\ntemplate< typename T1, typename T2 > struct Convert {\n"
	    "    inline T2 operator()( const T1& val ) {\n"
	    "        return (T2)val; } };\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, AfterPreprocessor1)
{
	// closing brackets should not be broken after a preprocessor statement
	char textIn[] =
	    "\n#ifdef __WIN32__\n"
	    "void foo() { SetEnvironmentVariable (k, v); }\n"
	    "#endif\n";
	char text[] =
	    "\n#ifdef __WIN32__\n"
	    "void foo() {\n"
	    "    SetEnvironmentVariable (k, v); }\n"
	    "#endif\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, AfterPreprocessor2)
{
	// closing brackets should not be broken after a preprocessor statement
	char text[] =
	    "\nvoid foo() {\n"
	    "    if (isFoo) {\n"
	    "#endif\n"
	    "        if (isBar) {\n"
	    "            QueryValue(m_MasterPath); } } }\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, UserData)
{
	// test from user requesting the pico style
	char text[] =
	    "\nddhisttohistogram(struct tgl l, int size, void *data) {\n"
	    "  // adds the data to the histogram (l->g).\n"
	    "  int i, j, *q;\n"
	    "  if (data != NULL) {\n"
	    "    if ((size > sizeof(int)) && (l != NULL)) {\n"
	    "      q = &(((int *)data)[1]);\n"
	    "      j = size / sizeof(int) - 1;\n"
	    "      if (j > l->samples)j = l->samples;\n"
	    "      if(l->logscale==1) {\n"
	    "        pthread_mutex_lock(&(l->update));\n"
	    "        for (i = 0; i < j; i++)\n"
	    "          a[i] += q[i];\n"
	    "        pthread_mutex_unlock(&(l->update)); }\n"
	    "      else {\n"
	    "        pthread_mutex_lock(&(l->update));\n"
	    "        for (i = 0; i < j; i++)\n"
	    "          a[i] += q[i];\n"
	    "        pthread_mutex_unlock(&(l->update)); } }\n"
	    "    free(data); } }\n";
	char options[] = "style=lisp, indent=spaces=2";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, SansPreprocessor)
{
	// don't attach to a preprocessor line
	char text[] =
	    "\nvoid foo() {\n"
	    "    A = 0;\n"
	    "#ifdef ERR1\n"
	    "    B = 1;\n"
	    "#endif\n"
	    "}\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, SansPreprocessorBreak)
{
	// don't break empty brackets after a preprocessor
	char text[] =
	    "\nclass FooClass {\n"
	    "#ifdef DEBUG_chardet\n"
	    "    void foo() { }\n"
	    "#endif\n"
	    "}\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, SansLineComment1)
{
	// don't attach to a end-of-line comment
	char text[] =
	    "\nvoid foo() {\n"
	    "    A = 0;\n"
	    "    B = 1;\n"
	    "    // comment\n"
	    "}\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, SansLineComment2)
{
	// don't attach to a end-of-line comment
	char text[] =
	    "\nvoid foo() {\n"
	    "    A = 0;\n"
	    "    B = 1;  // comment\n"
	    "}\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, SansComment1)
{
	// don't attach to a  comment
	char text[] =
	    "\nvoid foo() {\n"
	    "    A = 0;\n"
	    "    B = 1;\n"
	    "    /* comment */\n"
	    "}\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, SansComment2)
{
	// don't attach to a  comment
	char text[] =
	    "\nvoid foo() {\n"
	    "    A = 0;\n"
	    "    B = 1;  /* comment */\n"
	    "}\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, SansEmptyLine)
{
	// don't attach to a empty line
	char text[] =
	    "\nvoid foo() {\n"
	    "    A = 0;\n"
	    "    B = 1;\n"
	    "\n"
	    "}\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

TEST(StyleLispCpp, IndentArray1)
{
	// test array indentation
	char textIn[] =
	    "\nFooArray[] =\n"
	    "{\n"
	    "    { 1,  5,  10 },\n"
	    "    { 2,  6,  11 },\n"
	    "    { 3,  6,  12 }\n"
	    "};\n";
	char text[] =
	    "\nFooArray[] = {\n"
	    "    { 1,  5,  10 },\n"
	    "    { 2,  6,  11 },\n"
	    "    { 3,  6,  12 } };\n";
	char options[] = "style=lisp";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------

}  // namespace
