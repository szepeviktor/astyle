//
//  FILE ENCODING IS UTF-8 WITHOUT A BOM.
//  русский    中文（简体）    日本    한국의
//
//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleTestLib.h"
#include "astyle_main.h"
using namespace astyle;

#ifdef _WIN32
#include <windows.h>
#else
#include <iconv.h>
#endif

#ifndef __BORLANDC__        // can't use gmock
// for gmock macros
using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;
#endif

#ifdef _MSC_VER
#pragma warning(disable: 4996)  // secure version deprecation warnings
#pragma warning(disable: 4267)  // 64 bit signed/unsigned loss of data
#endif

//----------------------------------------------------------------------------
// support functions
//----------------------------------------------------------------------------

void systemAbort(const string& message)
{
	cout << message << endl;
	exit(EXIT_FAILURE);
}

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {

//----------------------------------------------------------------------------
// Test error reporting conditions in AStyleMain
//----------------------------------------------------------------------------

struct AStyleMainF1 : public ::testing::Test
// Constructor variables are set using native functions.
// These will be compared to the variables computed by the AStyle functions.
{
	// variables values
	char* text8;		// 8 bit text
	char* options8;		// 8 bit options

	// c'tor - set the variables
	AStyleMainF1()
	{
		char text[] =
			"\nvoid foo()\n"
			"{\n"
			"    bar();\n"
			"}\n";
		char options[] = "";
		// initialize variables
		text8 = NULL;
		options8 = NULL;
		// copy 8 bit values
		size_t text8Len = strlen(text) + 1;
		text8 = new char[text8Len];
		strcpy(text8, text);
		size_t options8Len = strlen(options) + 1;
		options8 = new char[options8Len];
		strcpy(options8, options);
	}	// end c'tor

	~AStyleMainF1()
	{
		delete [] text8;
		delete [] options8;
	}
};

TEST_F(AStyleMainF1, NullPointerToSource)
{
	// test error handling for NULL pointer to source
	int errorsIn = getErrorHandler2Calls();
	char* textOut = ::AStyleMain(NULL, options8, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut == NULL);
}

TEST_F(AStyleMainF1, NullPointerToOptions)
{
	// test error handling for NULL pointer to options
	int errorsIn = getErrorHandler2Calls();
	char* textOut = ::AStyleMain(text8, NULL, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut == NULL);
}

TEST_F(AStyleMainF1, NullPointerToErrorHandler)
{
	// test error handling for NULL error handler pointer
	// this cannot call the error handler, EXPECT_TRUE only for NULL return
	char* textOut = ::AStyleMain(text8, options8, NULL, memoryAlloc);
	EXPECT_TRUE(textOut == NULL);
}

TEST_F(AStyleMainF1, NullPointerToMemoryAlloc)
{
	// test error handling for NULL memory allocation pointer
	int errorsIn = getErrorHandler2Calls();
	char* textOut = ::AStyleMain(text8, options8, errorHandler2, NULL);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(textOut == NULL);
}

TEST_F(AStyleMainF1, InvalidOption)
{
	// test error handling for an invalid option
	// memory HAS been allocated for this error
	// the source will be formatted without the option
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"\tbar();\n"
		"}\n";
	char options[] = "invalid-option, indent=tab";
	int errorsIn = getErrorHandler2Calls();
	char* textOut = ::AStyleMain(text8, options, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_STREQ(text, textOut);
	delete [] textOut;
}

//----------------------------------------------------------------------------
// Test error reporting conditions in AStyleMainUtf16
//----------------------------------------------------------------------------

struct AStyleMainUtf16F1 : public ::testing::Test
// Constructor variables are set using native functions.
// These will be compared to the variables computed by the AStyle functions.
{
	// variables values
	utf16_t* text16;		// 16 bit text
	utf16_t* options16;		// 16 bit options
	char*    text8;			//  8 bit text

	// c'tor - set the variables
	AStyleMainUtf16F1()
	{
		char text[] =
			"\nvoid foo()\n"
			"{\n"
			"    bar();\n"
			"}\n";
		char options[] = "";
		// initialize variables
		text16 = NULL;
		options16 = NULL;
		text8 = NULL;
		// convert 16 bit
		ASLibrary library;
		text16 = library.convertUtf8ToUtf16(text, memoryAlloc);
		options16 = library.convertUtf8ToUtf16(options, memoryAlloc);
		// copy 8 bit
		size_t text8Len = strlen(text) + 1;
		text8 = new char[text8Len];
		strcpy(text8, text);
	}	// end c'tor

	~AStyleMainUtf16F1()
	{
		delete [] text16;
		delete [] options16;
		delete [] text8;
	}
};

TEST_F(AStyleMainUtf16F1, NullPointerToSource)
{
	// test error handling for NULL pointer to source
	int errorsIn = getErrorHandler2Calls();
	utf16_t* text16Out = ::AStyleMainUtf16(NULL, options16, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(text16Out == NULL);
}

TEST_F(AStyleMainUtf16F1, NullPointerToOptions)
{
	// test error handling for NULL pointer to options
	int errorsIn = getErrorHandler2Calls();
	utf16_t* text16Out = ::AStyleMainUtf16(text16, NULL, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(text16Out == NULL);
}

TEST_F(AStyleMainUtf16F1, NullPointerToErrorHandler)
{
	// test error handling for NULL pointer to error handler pointer
	// this cannot call the error handler
	utf16_t* text16Out = ::AStyleMainUtf16(text16, options16, NULL, memoryAlloc);
	EXPECT_TRUE(text16Out == NULL);
}

TEST_F(AStyleMainUtf16F1, NullPointerToMemoryAlloc)
{
	// test error handling for NULL pointer to memory allocator
	int errorsIn = getErrorHandler2Calls();
	utf16_t* text16Out = ::AStyleMainUtf16(text16, options16, errorHandler2, NULL);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_TRUE(text16Out == NULL);
}

TEST_F(AStyleMainUtf16F1, InvalidOption)
{
	// test error handling for an invalid option
	// the source will be formatted without the option
	char text[] =
		"\nvoid foo()\n"
		"{\n"
		"\tbar();\n"
		"}\n";
	char options[] = "invalid-option, indent=tab";
	// convert 16 bit options
	ASLibrary library;
	utf16_t* options16 = library.convertUtf8ToUtf16(options, memoryAlloc);
	// test error handling for an invalid option
	int errorsIn = getErrorHandler2Calls();
	utf16_t* text16Out = ::AStyleMainUtf16(text16, options16, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	// convert text16Out to utf-8
	char* text8Out = library.convertUtf16ToUtf8(text16Out);
	EXPECT_STREQ(text, text8Out);
	delete [] options16;
	delete [] text16Out;
	delete [] text8Out;
}

//----------------------------------------------------------------------------
// Test FormatUtf16 in ASLibrary
// This uses mocks and fixtures.
//----------------------------------------------------------------------------

struct ASLibrary_Mock8 : public ASLibrary
{
	MOCK_CONST_METHOD1(convertUtf16ToUtf8, char* (const utf16_t*));
};

struct ASLibrary_Mock16 : public ASLibrary
{
	MOCK_CONST_METHOD2(convertUtf8ToUtf16, utf16_t* (const char*, fpAlloc));
};

TEST_F(AStyleMainUtf16F1, NullConvertSource)
{
	// Test formatUtf16() error handling for source.
#ifndef __BORLANDC__        // can't use gmock
	ASLibrary_Mock8 library;
	EXPECT_CALL(library, convertUtf16ToUtf8(_))
	.WillOnce(Return(static_cast<char*>(NULL)));
	// test the error handling
	int errorsIn = getErrorHandler2Calls();
	utf16_t* textOut = library.formatUtf16(text16, options16, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_EQ(NULL, textOut);
#endif
}

TEST_F(AStyleMainUtf16F1, NullConvertOptions)
{
	// Test formatUtf16() error handling for options.
#ifndef __BORLANDC__        // can't use gmock
	ASLibrary_Mock8 library;
	// don't use convertUtf16ToUtf8() here, it will be mocked
	// deleted by the error procedure in formatUtf16()
	char* utf8Formatted = new char[strlen(text8) + 1];
	strcpy(utf8Formatted, text8);
	InSequence s;			// the following returns must occur in sequence
	EXPECT_CALL(library, convertUtf16ToUtf8(_))
	.WillOnce(Return(utf8Formatted))
	.WillOnce(Return(static_cast<char*>(NULL)));
	// test the error handling
	int errorsIn = getErrorHandler2Calls();
	utf16_t* textOut = library.formatUtf16(text16, options16, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_EQ(NULL, textOut);
#endif
}

TEST_F(AStyleMainUtf16F1, NullConvertFormattedText)
{
	// Test formatUtf16() error handling for converting formatted text to utf-16.
#ifndef __BORLANDC__        // can't use gmock
	ASLibrary_Mock16 library;
	// this method returns an error
	EXPECT_CALL(library, convertUtf8ToUtf16(_,_))
	.WillOnce(Return(static_cast<utf16_t*>(NULL)));
	// test the error handling
	int errorsIn = getErrorHandler2Calls();
	utf16_t* textOut = library.formatUtf16(text16, options16, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	EXPECT_EQ(NULL, textOut);
#endif
}

//----------------------------------------------------------------------------
// Test FormatUtf16 in ASLibrary
// This uses mocks and fixtures and non-ascii characters.
//----------------------------------------------------------------------------

struct AStyleMainUtf16F2 : public ::testing::Test
// Constructor variables are set using native functions.
// These will be compared to the variables computed by the AStyle functions.
{
	// variables values
	utf16_t* text16;		// 16 bit text
	utf16_t* options16;	    // 16 bit options
	char*    text8;			//  8 bit text

	// c'tor - set the variables
	AStyleMainUtf16F2()
	{
		// initialize variables
		text16 = NULL;
		options16 = NULL;
		text8 = NULL;
		// set textOut variables
		char textIn[] =
			"\nprivate void foo()\n"
			"{\n"
			"    // 文件已经 被修改\n"		// Chinese
			"    Chinese(\"导出结束\");\n"
			"\n"
			"    // アイウオ カキク\n"		// Japanese
			"    Japanese(\"スセタチ\");\n"
			"\n"
			"    // 선택된 컨트롤\n"		// Korean
			"    Korean(\"비트맵 에디터\");\n"
			"\n"
			"    // ΓΔΘΛ αβγλ\n"			// Greek
			"    Greek(\"ξπρσ ΞΦΨΩ\");\n"
			"\n"
			"    // АБВГ ДЕЁЖ\n"			// Russian
			"    Russian(\"ЗИЙК ЛПФЦ\");\n"
			"\n"
			"    // ÄÄ ÖÖ ÜÜ ßßßß\n"		// German (ß can cause problem with conversions)
			"    German(\"ää öö üü\");\n"
			"}\n";
		char optionsIn[] = "style=allman, mode=cs";
		// convert 8 bit to 16 bit
		ASLibrary library;
		text16 = library.convertUtf8ToUtf16(textIn, memoryAlloc);
		options16 = library.convertUtf8ToUtf16(optionsIn, memoryAlloc);
		size_t text8Len = strlen(textIn);
		text8 = new char[text8Len + 1];
		strcpy(text8, textIn);
//		cout << strlen(textIn) << " c'tor" << endl;
//		cout << strlen(optionsIn) << " c'tor" <<  endl;
	}	// end c'tor

	~AStyleMainUtf16F2()
	{
		delete [] text16;
		delete [] options16;
		delete [] text8;
	}
};

TEST_F(AStyleMainUtf16F2, FormatUtf16Ok)
{
	// Test call AStyleMainUtf16() with non-ascii characters.
	ASLibrary library;
	utf16_t* text16Out = library.formatUtf16(text16, options16, errorHandler, memoryAlloc);
	// must convert utf16 to utf8 for gtest comparison
	char* text8Out = library.convertUtf16ToUtf8(text16Out);
	EXPECT_STREQ(text8, text8Out);
	delete [] text16Out;
	delete [] text8Out;
}

//----------------------------------------------------------------------------

}  // namespace
