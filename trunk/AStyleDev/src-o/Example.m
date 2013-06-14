// Example.m

/* This program calls the Artistic Style GUI formatter (AStyleMain)
 * to format the astyle source files in a test-data directory.
 */

#include <Foundation/Foundation.h>

// allow for different calling conventions in Linux and Windows
#ifdef _WIN32
#define STDCALL __stdcall
#else
#define STDCALL
#endif

// functions to call AStyleMain
char* STDCALL AStyleGetVersion();
char* STDCALL AStyleMain(const char* pSourceIn,
                         const char* pOptions,
                         void(STDCALL* fpError)(int, char*),
                         char* (STDCALL* fpAlloc)(unsigned long));
void  STDCALL ASErrorHandler(int errorNumber, char* errorMessage);
char* STDCALL ASMemoryAlloc(unsigned long memoryNeeded);

// other functions
void error(NSString* message);
NSString* getProjectDirectory(const NSString* subPath);
NSString* getText(NSString* filePath);
void  setText(const NSString* textOut, NSString* filePath);


// Main function for this example.
int main(int argc, const char* argv[])
{   NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    // options to pass to AStyle
    const NSArray* fileNames = [NSArray arrayWithObjects:
                                @"AStyleDev/test-data/ASBeautifier.cpp",
                                @"AStyleDev/test-data/ASFormatter.cpp",
                                @"AStyleDev/test-data/astyle.h",
                                nil];
    const NSString* options = @"-A2tOP";

    // get Artistic Style version
    const char* versionChar = AStyleGetVersion();
    NSLog(@"Example Obj-C - AStyle %s", versionChar);

    // process the input files
    for (NSString * fileName in fileNames)
    {   // get the text to format
        NSString* filePath = getProjectDirectory(fileName);
        NSString* textIn = getText(filePath);

        // call the Artistic Style formatting function
        char* textOutChar = AStyleMain([textIn UTF8String],
                                       [options UTF8String],
                                       ASErrorHandler,
                                       ASMemoryAlloc);

        // does not need to terminate on an error
        // an error message has been displayed by the error handler
        if (textOutChar == NULL)
            error([NSString stringWithFormat: @"Cannot format %@", fileName]);

        // return the formatted text
        NSString* textOut = [NSString stringWithUTF8String: textOutChar];
        NSLog(@"Formatted %@", fileName);
        setText(textOut, filePath);

        // free the buffer allocated with NSZoneMalloc
        NSZoneFree(NSDefaultMallocZone(), textOutChar);
        textOutChar = NULL;
    }

//    system("pause");
    [pool drain];
    return EXIT_SUCCESS;
}

// Error handler for the Artistic Style formatter.
void  STDCALL ASErrorHandler(int errorNumber, char* errorMessage)
{   NSLog(@"astyle error %d", errorNumber);
    NSLog(@"%s", errorMessage);
}

// Allocate memory for the Artistic Style formatter.
// A variable-sized object may not be initialized with alloc.
char* STDCALL ASMemoryAlloc(unsigned long memoryNeeded)
{   // if allocation fails a null pointer is returned
    // error condition is checked after the return from AStyleMain
    char* buffer = NSZoneMalloc(NSDefaultMallocZone(), memoryNeeded);
    return buffer;
}

// Error message function for this example.
void error(NSString* message)
{   NSLog(@"%@", message);
    NSLog(@"The program has terminated!");
    exit(EXIT_FAILURE);
}

// Prepend the project directory to the subpath.
// This may need to be changed for your directory structure.
NSString* getProjectDirectory(const NSString* subPath)
{
#ifdef _WIN32
    char* homeDirectoryChar = getenv("USERPROFILE");
#else
    char* homeDirectoryChar = getenv("HOME");
#endif
    if (!homeDirectoryChar)
        error(@"Cannot find HOME directory");
    NSString* homeDirectory = [NSString stringWithCString: homeDirectoryChar
                               encoding: [NSString defaultCStringEncoding]];
    NSString* projectPath = [NSString stringWithFormat: @"%@/%@/%@",
                             homeDirectory, @"Projects", subPath];
    return projectPath;
}

// Get the text to be formatted and convert to a NSString.
// Usually the text would be obtained from an edit control.
NSString* getText(NSString* filePath)
{   NSString* textIn = [NSString stringWithContentsOfFile: filePath];
    return textIn;
}

// Return the formatted text.
// Usually the text would be returned to an edit control.
void setText(const NSString* textOut, NSString* filePath)
{   // create a backup file
    NSString* origfilePath =  [NSString stringWithFormat: @"%@%@", filePath, @".orig"];
    [[NSFileManager defaultManager] movePath: filePath toPath: origfilePath handler: nil];
    // write the text
    [textOut writeToFile: filePath atomically: YES];
}
