
#ifndef ASTYLE_INTERFACE_H
#define ASTYLE_INTERFACE_H

#include <string>
using namespace std;

// allow for different calling conventions in Linux and Windows
#if defined(_WIN32) && !defined(ASTYLE_STATIC)
#define STDCALL __stdcall
#else
#define STDCALL
#endif

// external functions calls in Artistic Style shared or static library
extern "C"
{   char* STDCALL  AStyleGetVersion();
    char* STDCALL  AStyleMain(const char* textIn,
                              const char* options,
                              void(STDCALL* errorHandler)(int, const char*),
                              char*(STDCALL* memoryAlloc)(unsigned long));
}

/**
 * The AStyleInterface class contains the variables and methods to call the
 * Artistic Style shared library to format a source file.
 */

class AStyleInterface
{
public:
    // NOTE: enumerators are always static

    enum BracketStyle  { STYLE_NONE,
                         STYLE_ALLMAN,
                         STYLE_JAVA,
                         STYLE_KandR,
                         STYLE_STROUSTRUP,
                         STYLE_WHITESMITH,
                         STYLE_BANNER,
                         STYLE_GNU,
                         STYLE_LINUX,
                         STYLE_HORSTMANN,
                         STYLE_1TBS,
                         STYLE_PICO,
                         STYLE_LISP
                       };

    enum IndentType { INDENT_SPACES,
                      INDENT_TABS,
                      INDENT_FTABS
                    };

    enum MinConditional { MINCOND_ZERO = 0,
                          MINCOND_ONE = 1,
                          MINCOND_TWO = 2,
                          MINCOND_ONEHALF = 3,
                          MINCOND_END
                        };

    // these MUST be the same as Artistic Style
    enum PointerAlign { PTR_ALIGN_NONE,
                        PTR_ALIGN_TYPE,
                        PTR_ALIGN_MIDDLE,
                        PTR_ALIGN_NAME,
                        PTR_ALIGN_END
                      };

    // these MUST be the same as Artistic Style
    enum ReferenceAlign { REF_ALIGN_NONE = PTR_ALIGN_NONE,
                          REF_ALIGN_TYPE = PTR_ALIGN_TYPE,
                          REF_ALIGN_MIDDLE = PTR_ALIGN_MIDDLE,
                          REF_ALIGN_NAME = PTR_ALIGN_NAME,
                          REF_SAME_AS_PTR,
                          REF_ALIGN_END
                        };

    enum MaxCodeLength { MAX_CODE_LENGTH_MIN = 50,
                         MAX_CODE_LENGTH_MAX = 200
                       };

    enum FileMode { FILEMODE_CPP,
                    FILEMODE_JAVA,
                    FILEMODE_SHARP
                  };

public:
    // public functions
    AStyleInterface();
    char* formatSource(const char* textIn);
    char* formatSource(const char* textIn, string& filePath);
    char* formatSource(const char* textIn, FileMode fileModeArg);
    void  setFileMode(string fileName);
    void  setTestOptions();

private:
    // option variable names are ALMOST the same as Artistic Style
    // the initial value is the default value in Artistic Style
    // comments are the command line option used to set the variable

    // bracket style option
    BracketStyle bracketStyle;          // --style=?

    // tabs/spaces options
    IndentType indentType;              // --indent=*
    int  indentLength;                  // --indent=*
    bool useTabLength;                  // --indent=force-tab-x=#
    int  tabLength;                     // --indent=force-tab-x=#

    // indentation options
    bool classIndent;                   // --indent-classes
    bool switchIndent;                  // --indent-switches
    bool caseIndent;                    // --indent-cases
    bool namespaceIndent;               // --indent-namespaces
    bool labelIndent;                   // --indent-labels
    bool preprocessorIndent;            // --indent-preprocessor
    bool col1CommentIndent;             // --indent-col1-comments
    int  minConditionalOption;          // --min-conditional-indent=#
    int  maxInStatementIndent;          // --max-instatement-indent=#

    // padding options
    bool breakHeaderBlocks;             // --break-blocks, --break-blocks=all
    bool breakClosingBlocks;            // --break-blocks=all
    bool padOperator;                   // --pad-oper
    bool padParenOutside;               // --pad-paren, --pad-paren-out
    bool padFirstParenOut;              // --pad-first-paren-out
    bool padParenInside;                // --pad-paren, --pad-paren-in
    bool padHeader;                     // --pad-header
    bool unpadParen;                    // --unpad-paren
    bool deleteEmptyLines;              // --delete-empty-lines
    bool fillEmptyLines;                // --fill-empty-lines
    PointerAlign alignPointer;          // --align-pointer= none, type, middle, name
    ReferenceAlign alignReference;      // --align-reference= none, type, middle, name same as pointer

    // formatting options
    bool breakCloseBrackets;            // --break-closing-brackets
    bool breakElseIfs;                  // --break-elseifs
    bool addBrackets;                   // --add-brackets
    bool addOneLineBrackets;            // --add-one-line-brackets
    bool breakOneLineBlocks;            // --keep-one-line-blocks
    bool breakOneLineStmts;             // --keep-one-line-statements
    bool convertTabs;                   // --convert-tabs
    int  maxCodeLength;                 // --max-code-length=#
    bool breakAfterLogical;             // --break-after-logical

    // file mode option
    FileMode fileMode;                  // --mode=?

    // default values for integer variables, saved by constructor
    int defaultIndentLength;            // default indentLength
    int defaultTabLength;               // default tabLength
    int defaultMinConditionalOption;    // default minConditionalIndent
    int defaultMaxInStatementIndent;    // default maxInStatementIndent
//    int defaultMaxCodeLength;           // default maxCodeLength

private:
    // private functions
    static void  displayErrorMessage(string errorMessage);
    string getOptions() const;
    static string intToString(int intValue);
    // callback functions for Artistic Style
    static void  STDCALL errorHandler(int errorNumber, const char* errorMessage);
    static char* STDCALL memoryAlloc(unsigned long memoryNeeded);

};  // class AStyleInterface

#endif      // closes ASTYLE_INTERFACE_H
