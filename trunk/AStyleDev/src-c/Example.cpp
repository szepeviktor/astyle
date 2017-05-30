// Example.cpp

/* This program calls the Artistic Style formatter (AStyleMain)
 * to format the astyle source files in a test-data directory.
 */

#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#if defined(__GNUC__)
    #include <string.h>     // need both string and string.h for GCC
#endif

using namespace std;

// allow for different calling conventions in Linux and Windows
#ifdef _WIN32
    #define STDCALL __stdcall
#else
    #define STDCALL
#endif

// functions to call AStyleMain
extern "C" const char* STDCALL AStyleGetVersion(void);
extern "C" char* STDCALL AStyleMain(const char* sourceIn,
                                    const char* optionsIn,
                                    void (STDCALL* fpError)(int, const char*),
                                    char* (STDCALL* fpAlloc)(unsigned long));
void  STDCALL ASErrorHandler(int errorNumber, const char* errorMessage);
char* STDCALL ASMemoryAlloc(unsigned long memoryNeeded);

// other functions
void error(const string message);
string getProjectDirectory(const string& subPath);
char* getText(const string& filePath);
void setText(const char* textOut, const string& filePathStr);


// Main function for this example.
int main(int, char**)
{   // options to pass to AStyle
    const string fileName[] = { "AStyleDev/test-data/ASBeautifier.cpp",
                                "AStyleDev/test-data/ASFormatter.cpp",
                                "AStyleDev/test-data/astyle.h"
                              };
    const char* options = "-A2tOP";
    size_t arraySize = sizeof(fileName) / sizeof(fileName[0]);

    // get Artistic Style version
    const char* version = AStyleGetVersion();
    cout << "Example C++ - AStyle " << version << endl;

    // process the input files
    for (size_t i = 0; i < arraySize; i++)
    {   // get the text to format
        string filePath = getProjectDirectory(fileName[i]);
        char* textIn = getText(filePath);

        // call the Artistic Style formatting function
        char* textOut = AStyleMain(textIn,
                                   options,
                                   ASErrorHandler,
                                   ASMemoryAlloc);

        // does not need to terminate on an error
        // an error message has been displayed by the error handler
        if (textOut == NULL)
            error(string("Cannot format " + filePath));

        // return the formatted text
        cout << "Formatted " << fileName[i] << endl;
        setText(textOut, filePath);

        // must delete the temporary buffers
        delete [] textIn;
        delete [] textOut;
    }

//    system("pause");
    return EXIT_SUCCESS;
}

// Error handler for the Artistic Style formatter.
void STDCALL ASErrorHandler(int errorNumber, const char* errorMessage)
{   cout << "astyle error " << errorNumber << "\n"
         << errorMessage << endl;
}

// Allocate memory for the Artistic Style formatter.
char* STDCALL ASMemoryAlloc(unsigned long memoryNeeded)
{   // error condition is checked after return from AStyleMain
    char* buffer = new (nothrow) char [memoryNeeded];
    return buffer;
}

// Error message function for this example.
void error(string message)
{   cout << message << endl;
    cout << "The program has terminated!" << endl;
    exit(EXIT_FAILURE);
}

// Prepend the project directory to the subpath.
// This may need to be changed for your directory structure.
string getProjectDirectory(const string& subPath)
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

// Get the text to be formatted.
// Usually the text would be obtained from an edit control.
char* getText(const string& filePath)
{   // open input file
    ifstream in(filePath.c_str());
    if (!in)
        error("Cannot open input file " + filePath);

    // get length of buffer
    const int bufferSizeIn = 131072;     // 128 KB

    // allocate memory
    char* bufferIn = new (nothrow) char [bufferSizeIn];
    if (bufferIn == NULL)
    {   in.close();
        error("Memory allocation failure on input");
    }

    // read data as a block
    in.read(bufferIn, bufferSizeIn);
    // get actual size - must be smaller than buffer size
    int textSizeIn = static_cast<int>(in.gcount());
    if (textSizeIn > bufferSizeIn)
    {   in.close();
        error("Read buffer is too small");
    }
    bufferIn[textSizeIn] = '\0';
    in.close();

    return bufferIn;
}

// Return the formatted text.
// Usually the text would be returned to an edit control.
void setText(const char* textOut, const string& filePathStr)
{   // create a backup file
    const char* filePath = filePathStr.c_str();
    string origfilePathStr = filePathStr + ".orig";
    const char* origfilePath = origfilePathStr.c_str();
    remove(origfilePath);              // remove a pre-existing file

    if (rename(filePath, origfilePath) < 0)
        error("Cannot open input file " + filePathStr);

    // open the output file
    ofstream out(filePath);
    if (!out)
        error("Cannot open output file " + filePathStr);

    // write the text
    size_t textSizeOut = strlen(textOut);
    out.write(textOut, static_cast<streamsize>(textSizeOut));
    out.close();
}
