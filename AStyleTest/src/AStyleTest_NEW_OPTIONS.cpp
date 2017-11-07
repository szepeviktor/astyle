// AStyleTest_NEW_OPTIONS.cpp
// Copyright (c) 2017 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

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
// This module is for testing new options.
// It will compile faster than if the tests were in another module.
// When the testing is complete move the tests to another module.
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// AStyle Break Return Type
//-------------------------------------------------------------------------

TEST(BreakReturnType, DISABLED_LongOption)
{
	// test break return type
	char textIn[] =
	    "\nvoid foo(bool isFoo)\n"
	    "{ }\n";
	char text[] =
	    "\nvoid\n"
	    "foo(bool isFoo)\n"
	    "{ }\n";
	char options[] = "break-return-type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakReturnType, DISABLED_ShortOption)
{
	// test break return type short option
	char textIn[] =
	    "\nvoid foo(bool isFoo)\n"
	    "{ }\n";
	char text[] =
	    "\nvoid\n"
	    "foo(bool isFoo)\n"
	    "{ }\n";
	char options[] = "-xB";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakReturnType, SansDefintion)
{
	// break return type definitions should not be broken
	char text[] =
	    "\nvoid foo(bool isFoo);";
	char options[] = "break-return-type";
	char* textOut = AStyleMain(text, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Break Return Type in Definitions
//-------------------------------------------------------------------------

TEST(BreakReturnTypeDef, DISABLED_LongOption)
{
	// test break return type in a definition
	char textIn[] =
	    "\nvoid foo(bool isFoo);";
	char text[] =
	    "\nvoid\n"
	    "foo(bool isFoo);";
	char options[] = "break-return-type-def";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(BreakReturnTypeDef, DISABLED_ShortOption)
{
	// test break return type short option in a definition
	char textIn[] =
	    "\nvoid foo(bool isFoo);";
	char text[] =
	    "\nvoid\n"
	    "foo(bool isFoo);";
	char options[] = "-xD";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Attach Return Type
//-------------------------------------------------------------------------

TEST(AttachReturnType, DISABLED_LongOption)
{
	// test break return type
	char textIn[] =
	    "\nvoid\n"
	    "foo(bool isFoo)\n"
	    "{ }\n";
	char text[] =
	    "\nvoid foo(bool isFoo)\n"
	    "{ }\n";
	char options[] = "attach-return-type";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachReturnType, DISABLED_ShortOption)
{
	// test break return type short option
	char textIn[] =
	    "\nvoid\n"
	    "foo(bool isFoo)\n"
	    "{ }\n";
	char text[] =
	    "\nvoid foo(bool isFoo)\n"
	    "{ }\n";
	char options[] = "-xf";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//-------------------------------------------------------------------------
// AStyle Attach Return Type in Definitions
//-------------------------------------------------------------------------

TEST(AttachReturnTypeDef, DISABLED_LongOption)
{
	// test break return type in a definition
	char textIn[] =
	    "\nvoid\n"
	    "foo(bool isFoo);";
	char text[] =
	    "\nvoid foo(bool isFoo);";
	char options[] = "attach-return-type-def";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

TEST(AttachReturnTypeDef, DISABLED_ShortOption)
{
	// test break return type short option in a definition
	char textIn[] =
	    "\nvoid\n"
	    "foo(bool isFoo);";
	char text[] =
	    "\nvoid foo(bool isFoo);";
	char options[] = "-xh";
	char* textOut = AStyleMain(textIn, options, errorHandler, memoryAlloc);
	EXPECT_STREQ(text, textOut);
	delete[] textOut;
}

//----------------------------------------------------------------------------

}  // namespace
