// AStyleTestI18n_Utf16.cpp
// Copyright (c) 2015 by Jim Pattee <jimp03@email.com>.
// Licensed under the MIT license.
// License.txt describes the conditions under which this software may be distributed.


// This module tests the utf-8 and utf-16 file encodings.
//
// AStyleTestI18n tests the internationalization component of the ASConsole
// class only. It uses the following source files from AStyleTestCon and
// AStyleTest: AStyleTestCon.h, TersePrinter.h AStyleTestCon_Main.cpp,
// AStyleTest_leakFinder.cpp, and TersePrinter.cpp.

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "AStyleTestCon.h"
#ifdef _WIN32
	#include <windows.h>
#else
	#include <iconv.h>
#endif

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {

//----------------------------------------------------------------------------
// support functions
//----------------------------------------------------------------------------

bool isLittleEndian()
// Return true if an int is little endian.
{
	short int word = 0x0001;
	char* byte = (char*)&word;
	return (byte[0] ? true : false);
}

int swap16Bit(int value)
// Swap the two low order bytes of a 16 bit integer value.
{
	return ( ((value & 0xff) << 8) | ((value & 0xff00) >> 8) );
}

void convertEndian(char* textIn, size_t textLen)
// convert 16 bit little endian text to big endian format
{
	// convert to wide char variables
	// short is 16 bytes in both Windows and Linux
	short* wcIn = reinterpret_cast<short*>(textIn);
	size_t wcLen = textLen / 2;
	// convert
	for (size_t i = 0; i < wcLen; i++)
		wcIn[i] = static_cast<short>(swap16Bit(wcIn[i]));
}

#ifdef _WIN32
string WideCharToUtf8Str(wchar_t* wcIn)
// WINDOWS convert wide char text (16 bit) to an 8 bit utf-8 string
{
	size_t mbLen = WideCharToMultiByte(CP_UTF8, 0, wcIn, -1, NULL, 0, NULL, 0);
	if (!mbLen)
		systemAbort("Bad WideCharToMultiByte in Utf16ToUtf8Str()");
	char* mbOut = new char[mbLen];
	WideCharToMultiByte(CP_UTF8, 0, wcIn, -1, mbOut, mbLen, NULL, 0);
	string mbStr(mbOut);
	delete []mbOut;
	return mbStr;
}
#else

//  LINUX define utf16_t
typedef unsigned short utf16_t;

size_t utf16len(const utf16_t* utf16In)
// LINUX return the length of a utf-16 C string.
// The length is in number of utf16_t.
{
	size_t length = 0;
	while (*utf16In++ != '\0')
		length++;
	return length;
}

string WideCharToUtf8Str(wchar_t* wcIn)
// LINUX convert wide char text (32 bit) to an 8 bit utf-8 string
{
	// Linux wchar_t is 32 bits
	size_t wcLen = wcslen(wcIn);
	iconv_t iconvh = iconv_open("UTF−8", "UTF−32LE");
	if (iconvh == reinterpret_cast<iconv_t>(-1))
	{
		if (errno == EINVAL)
			cout << "Conversion not supported by the implementation" << endl;
		systemAbort("Bad iconv_open in WideCharToUtf8Str()");
	}
	// allocate memory for output
	size_t mbLen = wcLen * sizeof(wchar_t);
	char* mbOut = new char[mbLen];
	// convert to utf-8
	char* mbConv = mbOut;
	size_t mbLeft = mbLen;
	char* wcConv = reinterpret_cast<char*>(wcIn);
	size_t wcLeft = wcLen * sizeof(wchar_t);
	int iconvval = iconv(iconvh, &wcConv, &wcLeft, &mbConv, &mbLeft);
	if (iconvval == -1)
		systemAbort("Bad iconv in Utf16ToUtf8Str()");
	*mbConv = '\0';
	iconv_close(iconvh);
	string mbStr(mbOut);
	delete []mbOut;
	return mbStr;
}

size_t WideCharToUtf16LE(wchar_t* wcIn, size_t wcLen, char* w16Out, size_t w16Buf)
// LINUX convert wide char text (32 bit) to 16 bit little endian text
{
	// Linux wchar_t is 32 bits
	iconv_t iconvh = iconv_open("UTF−16LE", "UTF−32LE");
	if (iconvh == reinterpret_cast<iconv_t>(-1))
	{
		if (errno == EINVAL)
			cout << "Conversion not supported by the implementation" << endl;
		systemAbort("Bad iconv_open in WideCharToUtf16()");
	}
	// convert to utf-16
	char* w16Conv = w16Out;
	size_t w16Left = w16Buf;
	char* wcConv = reinterpret_cast<char*>(wcIn);
	size_t wcLeft = wcLen * sizeof(wchar_t);
	int iconvval = iconv(iconvh, &wcConv, &wcLeft, &w16Conv, &w16Left);
	if (iconvval == -1)
		systemAbort("Bad iconv in WideCharToUtf16()");
	*w16Conv = '\0';
	*(w16Conv + 1) = '\0';
	iconv_close(iconvh);
	return w16Buf - w16Left;
}

string Utf16LEToUtf8Str(utf16_t* wcIn)
// LINUX convert utf-16LE text (16 bit) to an 8 bit utf-8 string
{
	size_t wcLen = utf16len(wcIn) * sizeof(utf16_t);
	iconv_t iconvh = iconv_open("UTF−8", "UTF−16LE");
	if (iconvh == reinterpret_cast<iconv_t>(-1))
	{
		if (errno == EINVAL)
			cout << "Conversion not supported by the implementation" << endl;
		systemAbort("Bad iconv_open in Utf16LEToUtf8Str()");
	}
	// allocate memory for output
	size_t mbLen = wcLen * sizeof(utf16_t);
	char* mbOut = new(nothrow) char[mbLen];
	if (mbOut == NULL)
		systemAbort("Bad allocation in Utf16LEToUtf8Str()");
	// convert to utf-8
	char* mbConv = mbOut;
	size_t mbLeft = mbLen;
	char* wcConv = reinterpret_cast<char*>(wcIn);
	size_t wcLeft = wcLen;
	int iconvval = iconv(iconvh, &wcConv, &wcLeft, &mbConv, &mbLeft);
	if (iconvval == -1)
		systemAbort("Bad iconv in Utf16LEToUtf8Str()");
	*mbConv = '\0';
	iconv_close(iconvh);
	string mbStr(mbOut);
	delete []mbOut;
	return mbStr;
}

#endif

//----------------------------------------------------------------------------
// AStyle test UTF8_16 conversion class
//----------------------------------------------------------------------------

struct Utf8_16_Class : public Test
// Constructor variables are set using native functions.
// These will be compared to the values computed by the AStyle functions.
{
	// variables values set using native functions
	string text8BitStr;		// 8 bit text string
	const char* text8Bit;	// 8 bit text char*
	size_t text8Len;		// 8 bit length
	char* text16Bit;		// 16 bit text char* (not wchar_t*)
	size_t text16Len;		// 16 bit length in chars (not wchar_t)

	// c'tor - set the variables
	Utf8_16_Class()
	{
		// initialize variables
		text8Bit = NULL;
		text8Len = 0;
		text16Bit = NULL;
		text16Len = 0;
		// set textOut variables
		wchar_t textIn[] =
		    L"\xfeff"						// 16 or 32 bit LE byte order mark (BOM)
		    L"\nvoid foo()\n"
		    L"{\n"
		    L"    // 文件已经 被修改\n"		// Chinese
		    L"    Chinese(\"导出结束\");\n"
		    L"\n"
		    L"    // アイウオ カキク\n"		// Japanese
		    L"    Japanese(\"スセタチ\");\n"
		    L"\n"
		    L"    // 선택된 컨트롤\n"		// Korean
		    L"    Korean(\"비트맵 에디터\");\n"
		    L"\n"
		    L"    // ΓΔΘΛ αβγλ\n"			// Greek
		    L"    Greek(\"ξπρσ ΞΦΨΩ\");\n"
		    L"\n"
		    L"    // АБВГ ДЕЁЖ\n"			// Russian
		    L"    Russian(\"ЗИЙК ЛПФЦ\");\n"
		    L"\n"
		    L"    // ÄÄ ÖÖ ÜÜ ßßßß\n"		// German (ß can cause problem with conversions)
		    L"    German(\"ää öö üü\");\n"
		    L"}\n";
		// compute 8 bit values using native functions
		text8BitStr = WideCharToUtf8Str(textIn);
		text8Bit = text8BitStr.c_str();
		text8Len = text8BitStr.length();
		// compute 16 bit values using native functions
		size_t text16Buf = (wcslen(textIn) * sizeof(wchar_t)) + sizeof(wchar_t);
		text16Bit = new char[text16Buf];
#ifdef _WIN32
		// Windows wchar_t is 16 bits and does not need conversion
		wcscpy(reinterpret_cast<wchar_t*>(text16Bit), textIn);
		text16Len = wcslen(reinterpret_cast<wchar_t*>(text16Bit)) * sizeof(wchar_t);
#else
		// Linux wchar_t is 32 bits and must be converted to 16 bits
		text16Len = WideCharToUtf16LE(textIn, wcslen(textIn), text16Bit, text16Buf);
#endif
	}	// end c'tor

	~Utf8_16_Class()
	{
		delete []text16Bit;
	}
};

// OSX iconv cannot do iconv_open for "UTF−16" or "UTF−8".
// It aborts in the function Utf8ToUtf16().
#ifdef __APPLE__
	TEST_F(Utf8_16_Class, DISABLED_Utf8_To_Utf16_LE)
#else
	TEST_F(Utf8_16_Class, Utf8_To_Utf16_LE)
#endif
// test AStyle Utf8 to Utf16 LE conversion functions
{
	ASSERT_TRUE(isLittleEndian()) << "Test assumes a little endian computer.";
	int sizeofUtf16 = sizeof(unsigned short);
	astyle::Utf8_16 utf8_16;
	bool isBigEndian = false;
	// test Astyle Utf16Length() function
	size_t utf16ComputedSize = utf8_16.Utf16LengthFromUtf8(text8Bit, text8Len);
	EXPECT_EQ(text16Len, utf16ComputedSize);
	// test Astyle Utf8ToUtf16() function return
	char* utf16Out = new char[utf16ComputedSize + sizeofUtf16];
	size_t utf16ConvertedSize = utf8_16.Utf8ToUtf16(const_cast<char*>(text8Bit),
	                                                text8Len + 1, isBigEndian, utf16Out);
	EXPECT_EQ(text16Len + sizeofUtf16, utf16ConvertedSize);
	// must convert utf16 to utf8 using native functions for gtest comparison
#ifdef _WIN32
	string text8OutStr = WideCharToUtf8Str(reinterpret_cast<wchar_t*>(utf16Out));
#else
	string text8OutStr = Utf16LEToUtf8Str(reinterpret_cast<utf16_t*>(utf16Out));
#endif
	EXPECT_STREQ(text8Bit, text8OutStr.c_str());
	delete []utf16Out;
}

// OSX iconv cannot do iconv_open for "UTF−16" or "UTF−8".
// It aborts in the function Utf8ToUtf16().
#ifdef __APPLE__
	TEST_F(Utf8_16_Class, DISABLED_Utf8_To_Utf16_BE)
#else
	TEST_F(Utf8_16_Class, Utf8_To_Utf16_BE)
#endif
// test AStyle Utf8 to Utf16 BE conversion functions
{
	ASSERT_TRUE(isLittleEndian()) << "Test assumes a little endian computer.";
	int sizeofUtf16 = sizeof(unsigned short);
	astyle::Utf8_16 utf8_16;
	bool isBigEndian = true;
	convertEndian(text16Bit, text16Len);
	// test Astyle Utf16Length() function
	size_t utf16ComputedSize = utf8_16.Utf16LengthFromUtf8(text8Bit, text8Len);
	EXPECT_EQ(text16Len, utf16ComputedSize);
	// test Astyle Utf8ToUtf16() function return
	char* utf16Out = new char[utf16ComputedSize + sizeofUtf16];
	size_t utf16ConvertedSize = utf8_16.Utf8ToUtf16(const_cast<char*>(text8Bit),
	                                                text8Len + 1, isBigEndian, utf16Out);
	EXPECT_EQ(text16Len + sizeofUtf16, utf16ConvertedSize);
	// must convert utf16 to utf8 using native functions for gtest comparison
#ifdef _WIN32
	convertEndian(utf16Out, text16Len);	// convert back to LE for native function
	string text8OutStr = WideCharToUtf8Str(reinterpret_cast<wchar_t*>(utf16Out));
#else
	convertEndian(utf16Out, text16Len);	// convert back to LE for native function
	string text8OutStr = Utf16LEToUtf8Str(reinterpret_cast<utf16_t*>(utf16Out));
#endif
	EXPECT_STREQ(text8Bit, text8OutStr.c_str());
	delete []utf16Out;
}

// OSX iconv cannot do iconv_open for "UTF−16" or "UTF−8".
// It aborts in the function Utf8ToUtf16().
#ifdef __APPLE__
	TEST_F(Utf8_16_Class, DISABLED_Utf16_LE_To_Utf8)
#else
	TEST_F(Utf8_16_Class, Utf16_LE_To_Utf8)
#endif
// test AStyle Utf16 LE to Utf8 conversion functions
{
	ASSERT_TRUE(isLittleEndian()) << "Test assumes a little endian computer.";
	astyle::Utf8_16 utf8_16;
	bool isBigEndian = false;
	// test Astyle Utf8Length() function
	size_t utf8ComputedSize = utf8_16.Utf8LengthFromUtf16(text16Bit, text16Len, isBigEndian);
	EXPECT_EQ(text8Len, utf8ComputedSize);
	// test Astyle Utf16ToUtf8() function return
	char* utf8Out = new char[utf8ComputedSize + 1];
	size_t utf8ConvertedSize = utf8_16.Utf16ToUtf8(const_cast<char*>(text16Bit),
	                                               text16Len + 1, isBigEndian, true, utf8Out);
	EXPECT_EQ(text8Len + 1, utf8ConvertedSize);
	// test Astyle Utf16ToUtf8() function text conversion
	EXPECT_STREQ(utf8Out, text8Bit);
	delete []utf8Out;
}

// OSX iconv cannot do iconv_open for "UTF−16" or "UTF−8".
// It aborts in the function Utf8ToUtf16().
#ifdef __APPLE__
	TEST_F(Utf8_16_Class, DISABLED_Utf16_BE_To_Utf8)
#else
	TEST_F(Utf8_16_Class, Utf16_BE_To_Utf8)
#endif
// test AStyle Utf16 BE to Utf8 conversion functions
{
	ASSERT_TRUE(isLittleEndian()) << "Test assumes a little endian computer.";
	astyle::Utf8_16 utf8_16;
	bool isBigEndian = true;
	convertEndian(text16Bit, text16Len);
	// test Astyle Utf8Length() function
	size_t utf8ComputedSize = utf8_16.Utf8LengthFromUtf16(text16Bit, text16Len, isBigEndian);
	EXPECT_EQ(text8Len, utf8ComputedSize);
	// test Astyle Utf16ToUtf8() function return
	char* utf8Out = new char[utf8ComputedSize + 1];
	size_t utf8ConvertedSize = utf8_16.Utf16ToUtf8(const_cast<char*>(text16Bit),
	                                               text16Len + 1, isBigEndian, true, utf8Out);
	EXPECT_EQ(text8Len + 1, utf8ConvertedSize);
	// test Astyle Utf16ToUtf8() function text conversion
	EXPECT_TRUE(strncmp(utf8Out, text8Bit, text8Len) == 0);
	delete []utf8Out;
}

//----------------------------------------------------------------------------
// AStyle test UTF-16 file processing
//----------------------------------------------------------------------------

struct ProcessUtf16F : public Test
// Constructor variables are set using native functions.
// These will be compared to the values computed by the AStyle functions.
// These test the processFiles function.
{
	ASFormatter formatter;
	vector<string> fileNames;
	// variables values set using native functions
	string text8BitStr;		// 8 bit text string
	const char* text8Bit;	// 8 bit text char*
	size_t text8Len;		// 8 bit length
	char* text16Bit;		// 16 bit text char* (not wchar_t*)
	size_t text16Len;		// 16 bit length in chars (not wchar_t)

	// c'tor - set the variables
	ProcessUtf16F()
	{
		// initialize variables
		text8Bit = NULL;
		text8Len = 0;
		text16Bit = NULL;
		text16Len = 0;
		// set textOut variables
		wchar_t textIn[] =
		    L"\xfeff"						// 16 or 32 bit LE byte order mark (BOM)
		    L"\nvoid foo()\n"
		    L"{\n"
		    L"    // 文件已经 被修改\n"		// Chinese
		    L"    Chinese(\"导出结束\");\n"
		    L"\n"
		    L"    // アイウオ カキク\n"		// Japanese
		    L"    Japanese(\"スセタチ\");\n"
		    L"\n"
		    L"    // 선택된 컨트롤\n"		// Korean
		    L"    Korean(\"비트맵 에디터\");\n"
		    L"\n"
		    L"    // ΓΔΘΛ αβγλ\n"			// Greek
		    L"    Greek(\"ξπρσ ΞΦΨΩ\");\n"
		    L"\n"
		    L"    // АБВГ ДЕЁЖ\n"			// Russian
		    L"    Russian(\"ЗИЙК ЛПФЦ\");\n"
		    L"\n"
		    L"    // ÄÄ ÖÖ ÜÜ ßßßß\n"		// German (ß can cause problem with conversions)
		    L"    German(\"ää öö üü\");\n"
		    L"}\n";
		// compute 8 bit values using native functions
		text8BitStr = WideCharToUtf8Str(textIn);
		text8Bit = text8BitStr.c_str();
		text8Len = text8BitStr.length();
		// compute 16 bit values using native functions
		size_t text16Buf = wcslen(textIn) * sizeof(wchar_t) + sizeof(wchar_t);
		text16Bit = new char[text16Buf];
#ifdef _WIN32
		// Windows wchar_t is 16 bits and does not need conversion
		wcscpy(reinterpret_cast<wchar_t*>(text16Bit), textIn);
		text16Len = wcslen(reinterpret_cast<wchar_t*>(text16Bit)) * sizeof(wchar_t);
#else
		// Linux wchar_t is 32 bits and must be converted to 16 bits
		text16Len = WideCharToUtf16LE(textIn, wcslen(textIn), text16Bit, text16Buf);
#endif
		cleanTestDirectory(getTestDirectory());
		createConsoleGlobalObject(formatter);
	}	// end c'tor

	~ProcessUtf16F()
	{
		delete []text16Bit;
		deleteConsoleGlobalObject();
	}
};

// OSX iconv cannot do iconv_open for "UTF−16" or "UTF−8".
// It aborts in the function Utf8ToUtf16().
#ifdef __APPLE__
	TEST_F(ProcessUtf16F, DISABLED_Utf16LE_Processing)
#else
	TEST_F(ProcessUtf16F, Utf16LE_Processing)
#endif
// Test processing of UTF-16LE files
{
	ASSERT_TRUE(isLittleEndian()) << "Test assumes a little endian computer.";
	ASSERT_TRUE(g_console != NULL) << "Console object not initialized.";
	// initialize variables
	g_console->setIsQuiet(true);		// change this to see results
	g_console->setIsRecursive(true);
	formatter.setFormattingStyle(STYLE_JAVA);  // to format the file
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	g_console->processOptions(astyleOptionsVector);
	// call astyle processFiles()
	fileNames.push_back(getTestDirectory() + "/UTF-16LE.cpp");
	createTestFile(fileNames.back(), text16Bit, text16Len);
	g_console->processFiles();
	// check for .orig file
	string origFileName = fileNames.back() + ".orig";
	struct stat stBuf;
	// display error if .orig file is not present
	if (stat(origFileName.c_str(), &stBuf) == -1)
		EXPECT_EQ("\"no file\"", origFileName.c_str());
	// check output BOM for UTF_16LE
	const int BomSize = 2;
	ifstream fin(fileNames.back().c_str(), ios::binary);
	char Bom16LE[BomSize];
	fin.read(Bom16LE, BomSize);
	FileEncoding encoding16LE = g_console->detectEncoding(Bom16LE, BomSize);
	EXPECT_TRUE(encoding16LE == UTF_16LE);
}

// OSX iconv cannot do iconv_open for "UTF−16" or "UTF−8".
// It aborts in the function Utf8ToUtf16().
#ifdef __APPLE__
	TEST_F(ProcessUtf16F, DISABLED_Utf16BE_Processing)
#else
	TEST_F(ProcessUtf16F, Utf16BE_Processing)
#endif
// Test processing of UTF-16BE files
{
	ASSERT_TRUE(isLittleEndian()) << "Test assumes a little endian computer.";
	ASSERT_TRUE(g_console != NULL) << "Console object not initialized.";
	// initialize variables
	g_console->setIsQuiet(true);		// change this to see results
	g_console->setIsRecursive(true);
	formatter.setFormattingStyle(STYLE_JAVA);	// to format the file
	// call astyle processOptions()
	convertEndian(text16Bit, text16Len);
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	g_console->processOptions(astyleOptionsVector);
	// call astyle processFiles()
	fileNames.push_back(getTestDirectory() + "/UTF-16BE.cpp");
	createTestFile(fileNames.back(), text16Bit, text16Len);
	g_console->processFiles();
	// check for .orig file
	string origFileName = fileNames.back() + ".orig";
	struct stat stBuf;
	// display error if .orig file is not present
	if (stat(origFileName.c_str(), &stBuf) == -1)
		EXPECT_EQ("\"no file\"", origFileName.c_str());
	// check output BOM for UTF_16BE
	const int BomSize = 2;
	ifstream fin(fileNames.back().c_str(), ios::binary);
	char Bom16BE[BomSize];
	fin.read(Bom16BE, BomSize);
	FileEncoding encoding16BE = g_console->detectEncoding(Bom16BE, BomSize);
	EXPECT_TRUE(encoding16BE == UTF_16BE);
}

//----------------------------------------------------------------------------

}  // namespace
