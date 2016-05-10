// AStyleTestLib_AStyleMain.cpp
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.txt describes the conditions under which this software may be distributed.

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

#ifdef _MSC_VER
	#pragma warning(disable: 4996)  // secure version deprecation warnings
	#pragma warning(disable: 4267)  // 64 bit signed/unsigned loss of data
#endif

//----------------------------------------------------------------------------
// support functions
//----------------------------------------------------------------------------

size_t utf16len(const utf16_t* utf16In)
// Return the length of utf-16 text.
// The length is in number of utf16_t.
{
	size_t length = 0;
	while (*utf16In++ != '\0')
		length++;
	return length;
}

int swap16Bit(int value)
// Swap the two low order bytes of a 16 bit integer value.
{
	return ( ((value & 0xff) << 8) | ((value & 0xff00) >> 8) );
}

void convertEndian(char* textIn, size_t textLen)
// reverse endian of the text
{
	// convert to wide char variables
	// short is 16 bytes in both Windows and Linux
	short* wcIn = reinterpret_cast<short*>(textIn);
	size_t wcLen = textLen;
	// convert
	for (size_t i = 0; i < wcLen; i++)
		wcIn[i] = static_cast<short>(swap16Bit(wcIn[i]));
}

void systemAbort(const string& message)
{
	cout << message << endl;
	exit(EXIT_FAILURE);
}

#ifdef _WIN32

utf16_t* Utf8ToWideChar(const char* utf8In)
// WINDOWS convert 8 bit utf-8 string to wide char string (16 bit)
// The calling program must delete the returned allocation.
{
	size_t wcLen = MultiByteToWideChar(CP_UTF8, 0, utf8In, -1, NULL, 0);
	if (!wcLen)
		systemAbort("Bad MultiByteToWideChar in Utf8ToWideCharStr()");
	wchar_t* wcOut = new wchar_t[wcLen];
	MultiByteToWideChar(CP_UTF8, 0, utf8In, -1, wcOut, wcLen);
	return reinterpret_cast<utf16_t*>(wcOut);
}

char* WideCharToUtf8(utf16_t* utf16In)
// WINDOWS convert wide char text (16 bit) to an 8 bit utf-8 string
// The calling program must delete the returned allocation.
{
	wchar_t* wcIn = reinterpret_cast<wchar_t*>(utf16In);
	size_t mbLen = WideCharToMultiByte(CP_UTF8, 0, wcIn, -1, NULL, 0, NULL, 0);
	if (!mbLen)
		systemAbort("Bad WideCharToMultiByte in WideCharToUtf8Str()");
	char* mbOut = new char[mbLen];
	WideCharToMultiByte(CP_UTF8, 0, wcIn, -1, mbOut, mbLen, NULL, 0);
	return mbOut;
}

#else

utf16_t* Utf8ToUtf16(char* utf8In)
// LINUX convert 8 bit utf-8 text to an 16 bit utf-16 text
// The calling program must delete the returned allocation.
{
	size_t mbLen = strlen(utf8In);
	iconv_t iconvh = iconv_open("UTF−16", "UTF−8");
	if (iconvh == reinterpret_cast<iconv_t>(-1))
		systemAbort("Bad iconv_open in Utf8ToUtf16()");
	// allocate memory for output
	size_t wcLen = (mbLen * sizeof(utf16_t)) + sizeof(utf16_t);
	char* wcOut = new(nothrow) char[wcLen];
	if (wcOut == NULL)
		systemAbort("Bad allocation in Utf8ToUtf16()");
	// convert to utf-8
	char* wcConv = wcOut;
	size_t wcLeft = wcLen;
	char* mbConv = utf8In;
	size_t mbLeft = mbLen;
	int iconvval = iconv(iconvh, &mbConv, &mbLeft, &wcConv, &wcLeft);
	if (iconvval == -1)
		systemAbort("Bad iconv in Utf8ToUtf16()");
	*wcConv = '\0';
	*(wcConv + 1) = '\0';
	iconv_close(iconvh);
	// Output iconv conversions to UTF-16 will have a BOM if a specific
	// endianness is not requested (UTF-16LE or UTF-16BE).
	// This will remove the BOM.
	utf16_t* wc16Out = reinterpret_cast<utf16_t*>(wcOut);
	if (wc16Out[0] == 0xfeff || wc16Out[0] == 0xfffe)
	{
//		cout << "REMOVING UTF-16 BOM" << endl;
		int wc16OutLen = utf16len(wc16Out) * sizeof(utf16_t);
		memmove(wc16Out, wc16Out + 1, wc16OutLen - 1);
	}
	return wc16Out;
}

char* Utf16ToUtf8(utf16_t* utf16In)
// LINUX convert 16 bit utf-16 text to an 8 bit utf-8 string
// The calling program must delete the returned allocation.
{
	size_t wcLen = utf16len(utf16In) * sizeof(utf16_t);
	iconv_t iconvh = iconv_open("UTF−8", "UTF−16");
	if (iconvh == reinterpret_cast<iconv_t>(-1))
		systemAbort("Bad iconv_open in Utf16ToUtf8()");
	// allocate memory for output
	size_t mbLen = wcLen * sizeof(utf16_t);
	char* mbOut = new(nothrow) char[mbLen];
	if (mbOut == NULL)
		systemAbort("Bad allocation in Utf16ToUtf8()");
	// convert to utf-8
	char* mbConv = mbOut;
	size_t mbLeft = mbLen;
	char* wcConv = reinterpret_cast<char*>(utf16In);
	size_t wcLeft = wcLen;
	int iconvval = iconv(iconvh, &wcConv, &wcLeft, &mbConv, &mbLeft);
	if (iconvval == -1)
		systemAbort("Bad iconv in Utf16ToUtf8()");
	*mbConv = '\0';
	iconv_close(iconvh);
	return mbOut;
}

#endif
//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {
//
//----------------------------------------------------------------------------
// Test error reporting conditions in AStyleMain
//----------------------------------------------------------------------------

struct AStyleMainF1 : public Test
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

struct AStyleMainUtf16F1 : public Test
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
	utf16_t* options16_ = library.convertUtf8ToUtf16(options, memoryAlloc);
	// test error handling for an invalid option
	int errorsIn = getErrorHandler2Calls();
	utf16_t* text16Out = ::AStyleMainUtf16(text16, options16_, errorHandler2, memoryAlloc);
	int errorsOut = getErrorHandler2Calls();
	EXPECT_EQ(errorsIn + 1, errorsOut);
	// convert text16Out to utf-8
	char* text8Out = library.convertUtf16ToUtf8(text16Out);
	EXPECT_STREQ(text, text8Out);
	delete [] options16_;
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
	EXPECT_CALL(library, convertUtf8ToUtf16(_, _))
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
// This uses fixtures and non-ascii characters.
//----------------------------------------------------------------------------

struct AStyleMainUtf16F2 : public Test
// Constructor variables are set using native functions.
// These will be compared to the variables computed by the AStyle functions.
{
	// variables values set using native functions
	char* text8;			//  8 bit text copied from c'tor
	utf16_t* text16;		// 16 bit text
	size_t text16Len;		// 16 bit length
	utf16_t* options16;	    // 16 bit options
	size_t options16Len;	// 16 bit length

	// c'tor - set the variables
	AStyleMainUtf16F2()
	{
		// initialize variables
		text8 = NULL;
		text16 = NULL;
		text16Len = 0;
		options16 = NULL;
		options16Len = 0;
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
		// create text8 values
		size_t text8Len = strlen(textIn);
		text8 = new char[text8Len + 1];
		strcpy(text8, textIn);
		// compute 16 bit values using native functions
#ifdef _WIN32
		text16 = Utf8ToWideChar(textIn);
		text16Len = utf16len(text16);
		options16 = Utf8ToWideChar(optionsIn);
		options16Len = utf16len(options16);
#else
		text16 = Utf8ToUtf16(textIn);
		text16Len = utf16len(text16);
		options16 = Utf8ToUtf16(optionsIn);
		options16Len = utf16len(options16);
#endif
	}	// end c'tor

	~AStyleMainUtf16F2()
	{
		delete [] text16;
		delete [] options16;
		delete [] text8;
	}
};

// OSX iconv cannot do iconv_open for "UTF−16" or "UTF−8".
// It aborts in the function Utf8ToUtf16().
#ifdef __APPLE__
	TEST_F(AStyleMainUtf16F2, DISABLED_FormatUtf16)
#else
	TEST_F(AStyleMainUtf16F2, FormatUtf16)
#endif
// NOTE: The conversion function uses the endianess of the computer
//       so LE and BE cannot both be tested.
//       The conversion function for BOTH ARE TESTED in the
//       Utf8_16_Class test functions in AStyleTestI18n_Utf16.cpp.
{
	// Test call AStyleMainUtf16() with utf-16 non-ascii characters.
	ASLibrary library;
	utf16_t* text16Out = library.formatUtf16(text16, options16, errorHandler, memoryAlloc);
	// must convert utf16 to utf8 using native functions for gtest comparison
#ifdef _WIN32
	char* text8Out = WideCharToUtf8(text16Out);
#else
	char* text8Out = Utf16ToUtf8(text16Out);
#endif
	EXPECT_STREQ(text8, text8Out);
	delete [] text8Out;
	delete [] text16Out;
}

//----------------------------------------------------------------------------

}  // namespace
