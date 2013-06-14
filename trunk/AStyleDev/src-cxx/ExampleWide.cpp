// Example.cpp

/* This program calls the Artistic Style GUI formatter (AStyleMain)
 * to format the astyle source files in a test-data directory.
 */

#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <iconv.h>
#endif

#if defined(__GNUC__)
#include <string.h>		// need both string and string.h for GCC
#endif

using namespace std;

// allow for different calling conventions in Linux and Windows
#ifdef _WIN32
#define STDCALL __stdcall
#else
#define STDCALL
#endif

// functions to call AStyleMain
extern "C"
char* STDCALL  AStyleMain(const char* pSourceIn,
                          const char* pOptions,
                          void(STDCALL* fpError)(int, char*),
                          char*(STDCALL* fpAlloc)(unsigned long));
void  STDCALL ASErrorHandler(int errorNumber, char* errorMessage);
char* STDCALL ASMemoryAlloc(unsigned long memoryNeeded);

// other functions
extern "C"
char* STDCALL  AStyleGetVersion();
wchar_t* ConvertUtf8ToWideChar(const char* utf8In);
char* ConvertWideCharToUtf8(const wchar_t* wcharIn);
void error(const char* why, string what = string(""));
string getProjectDirectory(string& subPath);
wchar_t* getText(string& filePath);
size_t Utf8LengthFromUtf16(const char* data, size_t tlen);
size_t Utf16LengthFromUtf8(const char* data, size_t len);
void setText(const wchar_t* textOut, string& filePathStr);


int main(int, char**)
{   // options to pass to AStyle
    string fileName[] = { "AStyleDev/test-data/ASBeautifier.cpp",
                          "AStyleDev/test-data/ASFormatter.cpp",
                          "AStyleDev/test-data/astyle.h"
                        };
    char* options = (char*)"-A2tOP";
    size_t arraySize = sizeof(fileName) / sizeof(fileName[0]);

    // Linux needs the default locale
    setlocale(LC_ALL,"");
    char* version = AStyleGetVersion();
    cout << "ExampleWide C++ - AStyle " << version << endl;

    // process the input files
    for (size_t i = 0; i < arraySize; i++)
    {   // get the text to format and convert to utf-8
        string filePath = getProjectDirectory(fileName[i]);
        wchar_t* wideIn = getText(filePath);
        char* utf8In = ConvertWideCharToUtf8(wideIn);
        if (utf8In == NULL)
            error("Cannot convert wide-char to utf-8", filePath);

        // call the Artistic Style formatting function
        char* utf8Out = AStyleMain(utf8In,
                                   options,
                                   ASErrorHandler,
                                   ASMemoryAlloc);
        // NULL pointer is an error
        // an error message has been displayed by the error handler
        if (utf8Out == NULL)
            error("Cannot format", filePath);

        delete [] wideIn;
        delete [] utf8In;
        wideIn = NULL;
        utf8In = NULL;

        // convert text to wide char and return it
        wchar_t* wideOut = ConvertUtf8ToWideChar(utf8Out);
        if (wideOut == NULL)
            error("Cannot convert utf-8 to wide-char", filePath);
        cout << "Formatted " << fileName[i] << endl;
        setText(wideOut, filePath);

        // must delete the temporary buffers
        delete [] utf8Out;
        delete [] wideOut;
    }
#ifdef __MINGW32__
    system("pause");
#endif
    return EXIT_SUCCESS;
}

void  STDCALL ASErrorHandler(int errorNumber, char* errorMessage)
// Error handler for the Artistic Style formatter.
{   cout << "astyle error " << errorNumber << "\n"
         << errorMessage << endl;
}

char* STDCALL ASMemoryAlloc(unsigned long memoryNeeded)
// Allocate memory for the Artistic Style formatter.
{   char* buffer = new(nothrow) char [memoryNeeded];
    return buffer;
}

#ifdef _WIN32
wchar_t* ConvertUtf8ToWideChar(const char* utf8In)
{   int wideLen = MultiByteToWideChar(CP_UTF8, 0, utf8In, -1, 0, 0);
    if (wideLen == 0)
        return NULL;
	///////////////////////////////////////////////////////////////////////////////////////////////
	int lenTest = Utf16LengthFromUtf8(utf8In, strlen(utf8In));
	lenTest /= 2;	// convert to wchar_t length
	cout << "  8 to 16  " << wideLen << "  " << lenTest << "  " << wideLen - lenTest << endl;
	///////////////////////////////////////////////////////////////////////////////////////////////
    wchar_t* wide = new(nothrow) wchar_t[wideLen];
    if (wide == NULL)
        return NULL;
    MultiByteToWideChar(CP_UTF8, 0, utf8In, -1, wide, wideLen);
    return wide;
}

char* ConvertWideCharToUtf8(const wchar_t* wcharIn)
{   int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wcharIn, -1, 0, 0, 0, 0);
    if (utf8Len == 0)
        return NULL;
	///////////////////////////////////////////////////////////////////////////////////////////////
	wstring wstr(wcharIn);
	int lenTest = Utf8LengthFromUtf16(reinterpret_cast<const char*>(wcharIn), wcslen(wcharIn) * 2);
	cout << "  16 to 8  " << utf8Len << "  " << lenTest << "  " << utf8Len - lenTest << endl;
	///////////////////////////////////////////////////////////////////////////////////////////////
    char* utf8 = new(nothrow) char[utf8Len];
    if (utf8 == NULL)
        return NULL;
    WideCharToMultiByte(CP_UTF8, 0, wcharIn, -1, utf8, utf8Len, 0, 0);
    return utf8;
}
#else
wchar_t* ConvertUtf8ToWideChar(const char* utf8In)
// wcharOut is processed as char although it is actually wchar_t.
{   iconv_t iconvh = iconv_open("UTF-32", "UTF-8//TRANSLIT");
    if (iconvh == reinterpret_cast<iconv_t>(-1))
        return NULL;
    size_t wcharMaxLen = (strlen(utf8In) + 2) * sizeof(wchar_t);
    char* wcharOut = new(nothrow) char[wcharMaxLen];
    if (wcharOut == NULL)
        return NULL;
    char* mbConv = const_cast<char*>(utf8In);
    size_t inLeft = strlen(utf8In) + 1;
    char* wcharConv = wcharOut;
    size_t outLeft = wcharMaxLen;
    size_t iconvval = iconv(iconvh, &mbConv, &inLeft, &wcharConv, &outLeft);
    if (iconvval == static_cast<size_t>(-1))
        return NULL;
    iconv_close(iconvh);
    return reinterpret_cast<wchar_t*>(wcharOut);
}

char* ConvertWideCharToUtf8(const wchar_t* wcharIn)
// wcharIn is processed as char although it is actually wchar_t.
{   iconv_t iconvh = iconv_open("UTF-8", "UTF-32//TRANSLIT");
    if (iconvh == reinterpret_cast<iconv_t>(-1))
        return NULL;
    size_t utf8MaxLen = wcslen(wcharIn) * 2;
    char* utf8 = new(nothrow) char[utf8MaxLen];
    if (utf8 == NULL)
        return NULL;
    char* wcConv = reinterpret_cast<char*>(const_cast<wchar_t*>(wcharIn));
    size_t inLeft = wcslen(wcharIn) * sizeof(wchar_t);
    char* utf8Conv = utf8;
    size_t outLeft = utf8MaxLen;
    size_t iconvval = iconv(iconvh, &wcConv, &inLeft, &utf8Conv, &outLeft);
    if (iconvval == static_cast<size_t>(-1))
        return NULL;
    iconv_close(iconvh);
    return utf8;
}
#endif	 // _WIN32

void error(const char* why, string what)
// Error message function for this example.
{   cout << why << ' ' << what << endl;
    cout << "The program has terminated!" << endl;
    exit(EXIT_FAILURE);
}

string getProjectDirectory(string& subPath)
// Prepend the project directory to the subpath.
// This may need to be changed for your directory structure.
{
#ifdef _WIN32
    char* homeDirectory = getenv("USERPROFILE");
#else
    char* homeDirectory = getenv("HOME");
#endif
    if (!homeDirectory)
        error("Cannot find HOME directory");
    string projectPath = string(homeDirectory) + "/Projects/" + subPath;
    return projectPath;
}

wchar_t* getText(string& filePath)
// Get the text to be formatted.
// Usually the text would be obtained from an edit control.
// In this case it is converted to Unicode using the system default codepage.
{   ifstream in(filePath.c_str());
    if (!in)
        error("Cannot open input file", filePath);

    // length of buffer
    const int bufferSizeIn = 131072;     // 128 KB

    // allocate memory
    char* mbIn = new(nothrow) char [bufferSizeIn];
    if (mbIn == NULL)
    {   in.close();
        error("Memory allocation failure on input");
    }

    // read data as a block
    in.read(mbIn, bufferSizeIn);
    // get actual size - must be smaller than buffer size
    int mbSizeIn = static_cast<int>(in.gcount());
    if (mbSizeIn > bufferSizeIn)
    {   in.close();
        error("Read buffer is too small");
    }
    mbIn[mbSizeIn] = '\0';
    in.close();

    // convert to Unicode using the system default encoding
    // ANSI conversion functions are multi-platform
    size_t wideLen = mbstowcs(0, mbIn, strlen(mbIn) + 1);
    wchar_t* wide = new(nothrow) wchar_t[wideLen + 1];
    if (wide == NULL)
        error("Memory allocation failure on input wchar-t conversion");
    mbstowcs(wide, mbIn, strlen(mbIn) + 1);
    return wide;
}

void setText(const wchar_t* wideOut, string& filePathStr)
// Return the formatted text.
// Usually the text would be returned to an edit control.
// In this case it is converted from Unicode using the system default codepage.
{   // convert from Unicode using the system default encoding
    // ANSI conversion functions are multi-platform
    size_t maxLen = (wcslen(wideOut) + 1) * 2;
    size_t mbLen = wcstombs(0, wideOut, maxLen);
    if (mbLen == static_cast<size_t>(-1))
        error("Invalid wide character in output");
    char* mbOut = new(nothrow) char [mbLen];
    if (mbOut == NULL)
        error("Memory allocation failure on output");
    wcstombs(mbOut, wideOut, mbLen + 1);

    // create a backup file
    const char* filePath = filePathStr.c_str();
    string origfilePathStr = filePathStr + ".orig";
    const char* origfilePath = origfilePathStr.c_str();
    remove(origfilePath);              // remove a pre-existing file
    if (rename(filePath, origfilePath) < 0)
        error("Cannot open input file", filePath);

    // write the text
    // open the output file
    ofstream out(filePath);
    if (!out)
        error("Cannot open output file", filePath);

    int mbSizeOut = strlen(mbOut);
    out.write(mbOut, mbSizeOut);
    out.close();
}

size_t Utf8LengthFromUtf16(const char* data, size_t tlen)
// Adapted from SciTE UniConversion.cxx.
// Copyright 1998-2001 by Neil Hodgson <neilh@scintilla.org>
// Modified for Artistic Style by Jim Pattee.
// Compute the length of an output utf-8 file given a utf-16 file.
// Input tlen is the size in BYTES (not wchar_t).
{
	enum { SURROGATE_LEAD_FIRST = 0xD800 };
	enum { SURROGATE_TRAIL_LAST = 0xDFFF };

	size_t len = 0;
	size_t wcharLen = tlen / 2;
	const short* uptr = reinterpret_cast<const short*>(data);
	for (size_t i = 0; i < wcharLen && uptr[i];)
	{
		size_t uch = uptr[i];
		if (uch < 0x80)
		{
			len++;
		}
		else if (uch < 0x800)
		{
			len += 2;
		}
		else if ((uch >= SURROGATE_LEAD_FIRST) && (uch <= SURROGATE_TRAIL_LAST))
		{
			len += 4;
			i++;
		}
		else
		{
			len += 3;
		}
		i++;
	}
	return len;
}

size_t Utf16LengthFromUtf8(const char* data, size_t len)
// Adapted from SciTE UniConversion.cxx.
// Copyright 1998-2001 by Neil Hodgson <neilh@scintilla.org>
// Modified for Artistic Style by Jim Pattee.
// Compute the length of an output utf-16 file given a utf-8 file.
// Return value is the size in BYTES (not wchar_t).
{
	size_t ulen = 0;
	size_t charLen;
	for (size_t i = 0; i < len;)
	{
		unsigned char ch = static_cast<unsigned char>(data[i]);
		if (ch < 0x80)
			charLen = 1;
		else if (ch < 0x80 + 0x40 + 0x20)
			charLen = 2;
		else if (ch < 0x80 + 0x40 + 0x20 + 0x10)
			charLen = 3;
		else
		{
			charLen = 4;
			ulen++;
		}
		i += charLen;
		ulen++;
	}
	// return value is the length in bytes (not wchar_t)
	return ulen * 2;
}
