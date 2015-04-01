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

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {

//----------------------------------------------------------------------------
// AStyle DetectEncoding
//----------------------------------------------------------------------------

TEST(DetectEncoding, Detect_8Bit)
// test AStyle detectEncoding function for 8 bit encoding
{
	const char text8Bit[] = "Detect Encoding Test";
	FileEncoding encoding8Bit = g_console->detectEncoding(text8Bit, strlen(text8Bit));
	EXPECT_TRUE(encoding8Bit == ENCODING_8BIT);
}

TEST(DetectEncoding, Detect_8Bit_ZeroLength)
// test AStyle detectEncoding function for 8 bit encoding
{
	const char text8Bit[] = "\0";
	FileEncoding encoding8Bit = g_console->detectEncoding(text8Bit, strlen(text8Bit));
	EXPECT_TRUE(encoding8Bit == ENCODING_8BIT);
}

TEST(DetectEncoding, Detect_Utf8)
// test AStyle detectEncoding function for 8 bit encoding
{
	const char text8Bit[] = "\xEF\xBB\xBF";
	FileEncoding encoding8Bit = g_console->detectEncoding(text8Bit, strlen(text8Bit));
	EXPECT_TRUE(encoding8Bit == ENCODING_8BIT);
}

TEST(DetectEncoding, Detect_Utf16LE)
// test AStyle detectEncoding function for 16 bit LE encoding
{
	const char Bom16LE[] = "\xFF\xFE";
	FileEncoding encoding16LE = g_console->detectEncoding(Bom16LE, strlen(Bom16LE));
	EXPECT_TRUE(encoding16LE == UTF_16LE);
}

TEST(DetectEncoding, Detect_Utf16BE)
// test AStyle detectEncoding function for 16 bit BE encoding
{
	const char Bom16BE[] = "\xFE\xFF";
	FileEncoding encoding16BE = g_console->detectEncoding(Bom16BE, strlen(Bom16BE));
	EXPECT_TRUE(encoding16BE == UTF_16BE);
}

TEST(DetectEncoding, Detect_Utf32LE)
// test AStyle detectEncoding function for 32 bit LE encoding
// strlen does NOT work with 32 bit BOMs
{
	const char Bom32LE[] = "\xFF\xFE\x00\x00";
	FileEncoding encoding32LE = g_console->detectEncoding(Bom32LE, 4);
	EXPECT_TRUE(encoding32LE == UTF_32LE);
}

TEST(DetectEncoding, Detect_Utf32BE)
// test AStyle detectEncoding function for 32 bit BE encoding
// strlen does NOT work with 32 bit BOMs
{
	const char Bom32BE[] = "\x00\x00\xFE\xFF";
	FileEncoding encoding32BE = g_console->detectEncoding(Bom32BE, 4);
	EXPECT_TRUE(encoding32BE == UTF_32BE);
}

//----------------------------------------------------------------------------
// AStyle test UTF-32 file processing - 32 bit abort
//----------------------------------------------------------------------------

struct ProcessUtf32F : public Test
{
	ASFormatter formatter;
	vector<string> fileNames;

	// build fileNames vector and write the output files
	ProcessUtf32F()
	{
		cleanTestDirectory(getTestDirectory());
		createConsoleGlobalObject(formatter);
	}

	~ProcessUtf32F()
	{
		deleteConsoleGlobalObject();
	}
};

TEST_F(ProcessUtf32F, Utf32LE_Abort)
// test rejection of UTF-32 files
{
	ASSERT_TRUE(g_console != NULL) << "Console object not initialized.";
	// initialize variables
	g_console->setIsQuiet(true);		// change this to see results
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	g_console->processOptions(astyleOptionsVector);
	// call astyle processFiles()
	// NOTE: some string functions don't work with NULLs (e.g. length())
	char textIn[] = "this text will not be readable";
	int textsize = sizeof(textIn);
	char textBOM[50];
	// UTF-32LE
	memcpy(textBOM, "\xFF\xFE\x00\x00", 4);
	memcpy(textBOM + 4, textIn, sizeof(textIn));
	fileNames.push_back(getTestDirectory() + "/UTF-32LE.cpp");
	createTestFile(fileNames.back(), textBOM, textsize);
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	EXPECT_EXIT(g_console->processFiles(),
	            ExitedWithCode(EXIT_FAILURE),
	            "Cannot process UTF-32 encoding");
#endif
}

TEST_F(ProcessUtf32F, Utf32BE_Abort)
// test rejection of UTF-32 files
{
	ASSERT_TRUE(g_console != NULL) << "Console object not initialized.";
	// initialize variables
	g_console->setIsQuiet(true);		// change this to see results
	// call astyle processOptions()
	vector<string> astyleOptionsVector;
	astyleOptionsVector.push_back(getTestDirectory() + "/*.cpp");
	g_console->processOptions(astyleOptionsVector);
	// call astyle processFiles()
	// NOTE: some string functions don't work with NULLs (e.g. length())
	char textIn[] = "this text will not be readable";
	int textsize = sizeof(textIn);
	char textBOM[50];
	// UTF-32BE
	memcpy(textBOM, "\x00\x00\xFE\xFF", 4);
	memcpy(textBOM + 4, textIn, sizeof(textIn));
	fileNames.push_back(getTestDirectory() + "/UTF-32BE.cpp");
	createTestFile(fileNames.back(), textBOM, textsize);
	// cannot use death test with leak finder
#if GTEST_HAS_DEATH_TEST && !(LEAK_DETECTOR || LEAK_FINDER)
	EXPECT_EXIT(g_console->processFiles(),
	            ExitedWithCode(EXIT_FAILURE),
	            "Cannot process UTF-32 encoding");
#endif
}

//----------------------------------------------------------------------------

}  // namespace
