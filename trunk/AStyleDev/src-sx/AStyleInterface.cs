// AStyleInterface.cs

using System;
using System.Runtime.InteropServices;

/// AStyleInterface contains methods to call the Artistic Style formatter.
public class AStyleInterface
{   // Disable warnings for 'Missing XML comment for publicly visible type or member'
#pragma warning disable 1591

    // bracketStyle valid bracket styles
    public const int STYLE_NONE       = 0;
    public const int STYLE_ALLMAN     = 1;
    public const int STYLE_JAVA       = 2;
    public const int STYLE_KandR      = 3;
    public const int STYLE_STROUSTRUP = 4;
    public const int STYLE_WHITESMITH = 5;
    public const int STYLE_BANNER     = 6;
    public const int STYLE_GNU        = 7;
    public const int STYLE_LINUX      = 8;
    public const int STYLE_HORSTMANN  = 9;
    public const int STYLE_1TBS       = 10;
    public const int STYLE_PICO       = 11;
    public const int STYLE_LISP       = 12;

    // indentType valid indent types
    public const int INDENT_SPACES = 0;
    public const int INDENT_TABS   = 1;
    public const int INDENT_FTABS  = 2;

    // minConditionalOption valid options
    public const int  MINCOND_ZERO = 0;
    public const int  MINCOND_ONE = 1;
    public const int  MINCOND_TWO = 2;
    public const int  MINCOND_ONEHALF = 3;

    // alignPointers valid pointer alignments
    public const int PTR_ALIGN_NONE     = 0;
    public const int PTR_ALIGN_TYPE     = 1;
    public const int PTR_ALIGN_MIDDLE   = 2;
    public const int PTR_ALIGN_NAME     = 3;

    // alignReference valid reference alignments
    public const int REF_ALIGN_NONE     = PTR_ALIGN_NONE;
    public const int REF_ALIGN_TYPE     = PTR_ALIGN_TYPE;
    public const int REF_ALIGN_MIDDLE   = PTR_ALIGN_MIDDLE;
    public const int REF_ALIGN_NAME     = PTR_ALIGN_NAME;
    public const int REF_SAME_AS_PTR    = PTR_ALIGN_NAME + 1;

    // maxCodeLength min and max
    public const int MAX_CODE_LENGTH_MIN = 50;
    public const int MAX_CODE_LENGTH_MAX = 200;

    // fileMode valid file modes
    public const int FILEMODE_CPP   = 0;
    public const int FILEMODE_JAVA  = 1;
    public const int FILEMODE_SHARP = 2;

    // Restore warnings for 'Missing XML comment for publicly visible type or member'
#pragma warning restore 1591

    // option variable names are ALMOST the same as Artistic Style
    // the initial value is the default value in Artistic Style
    // comments are the command line option used to set the variable

    // bracket style option
    private int  bracketStyle = STYLE_NONE;        // --style=?

    // tabs/spaces options
    private int  indentType   = INDENT_SPACES;     // --indent=?, --indent=force-tab=#
    private int  indentLength = 4;                 // --indent=?, --indent=force-tab=#
    private bool useTabLength = false;             // --indent=force-tab-x=#
    private int  tabLength    = 8;                 // --indent=force-tab-x=#

    // indentation options
    private bool classIndent         = false;      // --indent-classes
    private bool switchIndent        = false;      // --indent-switches
    private bool caseIndent          = false;      // --indent-cases
    private bool namespaceIndent     = false;      // --indent-namespaces
    private bool labelIndent         = false;      // --indent-labels
    private bool preprocessorIndent  = false;      // --indent-preprocessor
    private bool col1CommentIndent   = false;      // --indent-col1-comments
    private int maxInStatementIndent = 40;         // --max-instatement-indent=#
    private int minConditionalOption = MINCOND_TWO;// --min-conditional-indent=#

    // padding options
    private bool breakHeaderBlocks   = false;      // --break-blocks, --break-blocks=all
    private bool breakClosingBlocks  = false;      // --break-blocks=all
    private bool padOperator         = false;      // --pad-oper
    private bool padParenOutside     = false;      // --pad-paren, --pad-paren-out
    private bool padFirstParenOut    = false;      // --pad-first-paren-out
    private bool padParenInside      = false;      // --pad-paren, --pad-paren-in
    private bool padHeader           = false;      // --pad-header
    private bool unpadParen          = false;      // --unpad-paren
    private bool deleteEmptyLines    = false;      // --delete-empty-lines
    private bool fillEmptyLines      = false;      // --fill-empty-lines
    private int  alignPointer        = PTR_ALIGN_NONE;    // --align-pointer= none, type, middle, name
    private int  alignReference      = REF_SAME_AS_PTR;   // --align-reference= none, type, middle, name same as pointer

    // formatting options
    private bool breakCloseBrackets   = false;      // --break-closing-brackets
    private bool breakElseIfs         = false;      // --break-elseifs
    private bool addBrackets          = false;      // --add-brackets
    private bool addOneLineBrackets   = false;      // --add-one-line-brackets
    private bool breakOneLineStmts    = true;       // --keep-one-line-statements
    private bool breakOneLineBlocks   = true;       // --keep-one-line-blocks
    private bool convertTabs          = false;      // --convert-tabs
    private int  maxCodeLength        = 0;          // --max-code-length=#
    private bool breakAfterLogical    = false;      // --break-after-logical

    // file mode option
    private int     fileMode = FILEMODE_CPP;        // --mode=?

    // default values for integer variables, saved by constructor
    private int  defaultIndentLength;               // default indentLength
    private int  defaultTabLength;                  // default tabLength
    private int  defaultMaxInStatementIndent;       // default maxInStatementIndent
    private int  defaultMinConditionalOption;       // default minConditionalOption
//    private int  defaultMaxCodeLength;              // default maxCodeLength

    /// Constructor
    public AStyleInterface()
    {   // Declare callback functions
        AStyleMemAlloc = new AStyleMemAllocDelgate(OnAStyleMemAlloc);
        AStyleError = new AStyleErrorDelgate(OnAStyleError);
        // save integer default values
        defaultIndentLength         = indentLength;
        defaultTabLength            = tabLength;
        defaultMaxInStatementIndent = maxInStatementIndent;
        defaultMinConditionalOption = minConditionalOption;
//        defaultMaxCodeLength        = maxCodeLength;
    }

    /// Display error messages for the class.
    /// This method should be changed to display messages in a manner consistent
    /// with the rest of the user program (e.g. a message box).
    private void DisplayErrorMessage(String errorMessage)
    {   Console.WriteLine(errorMessage);
    }

    /// Build a string of options from the current option variables.
    /// An option is generated only if the current value is different
    /// than the default value.
    /// If an option variable is invalid, invalid text is sent to
    /// Artistic Style so the private ErrorHandler method will be called.
    public String GetOptions()
    {   String options = null;             // options to Artistic Style
        String separator = "\n";           // can be new-line, tab, space, or comma

        if (bracketStyle != STYLE_NONE)
        {   if (bracketStyle == STYLE_ALLMAN)
                options += "style=allman";
            else if (bracketStyle == STYLE_JAVA)
                options += "style=java";
            else if (bracketStyle == STYLE_KandR)
                options += "style=k&r";
            else if (bracketStyle == STYLE_STROUSTRUP)
                options += "style=stroustrup";
            else if (bracketStyle == STYLE_WHITESMITH)
                options += "style=whitesmith";
            else if (bracketStyle == STYLE_BANNER)
                options += "style=banner";
            else if (bracketStyle == STYLE_GNU)
                options += "style=gnu";
            else if (bracketStyle == STYLE_LINUX)
                options += "style=linux";
            else if (bracketStyle == STYLE_HORSTMANN)
                options += "style=horstmann";
            else if (bracketStyle == STYLE_1TBS)
                options += "style=1tbs";
            else if (bracketStyle == STYLE_PICO)
                options += "style=pico";
            else if (bracketStyle == STYLE_LISP)
                options += "style=lisp";
            else
                options += "bracketStyle="         // force an error message
                           + bracketStyle;
            options += separator;
        }
        // begin indent check
        if (indentType == INDENT_SPACES)           // space is the default
        {   if (indentLength != defaultIndentLength)
            {   options += "indent=spaces=" + indentLength;
                options += separator;
            }
        }
        else if (indentType == INDENT_TABS)        // tab is not the default
        {   // check conditions to use default tab setting
            if (indentLength == defaultIndentLength)
                options += "indent=tab";
            else
                options += "indent=tab=" + indentLength;
            options += separator;
        }
        else if (indentType == INDENT_FTABS)
        {   // check conditions to use default force-tab setting
            if (indentLength == defaultIndentLength)
            {   if (!useTabLength)
                {   options += "indent=force-tab";
                    options += separator;
                }
            }
            else
            {   options += "indent=force-tab=" + indentLength;
                options += separator;
            }
            // check conditions to use different tab setting
            if (useTabLength)
            {   if (tabLength == defaultTabLength)
                    options += "indent=force-tab-x";
                else
                    options += "indent=force-tab-x=" + tabLength;
                options += separator;
            }
        }
        else
        {   options += "indentType="               // force an error message
                       + indentType;
            options += separator;
        }
        // end indent check
        if (classIndent)
        {   options += "indent-classes";
            options += separator;
        }
        if (switchIndent)
        {   options += "indent-switches";
            options += separator;
        }
        if (caseIndent)
        {   options += "indent-cases";
            options += separator;
        }
        if (namespaceIndent)
        {   options += "indent-namespaces";
            options += separator;
        }
        if (labelIndent)
        {   options += "indent-labels";
            options += separator;
        }
        if (preprocessorIndent)
        {   options += "indent-preprocessor";
            options += separator;
        }
        if (col1CommentIndent)
        {   options += "indent-col1-comments";
            options += separator;
        }
        if (maxInStatementIndent != defaultMaxInStatementIndent)
        {   options += "max-instatement-indent="
                       + maxInStatementIndent;
            options += separator;
        }
        if (minConditionalOption != defaultMinConditionalOption)
        {   options += "min-conditional-indent="
                       + minConditionalOption;
            options += separator;
        }
        // begin break-blocks check
        if (breakClosingBlocks)
        {   options += "break-blocks=all";
            options += separator;
        }
        else if (breakHeaderBlocks)
        {   options += "break-blocks";
            options += separator;
        }
        // end break-blocks check
        if (padOperator)
        {   options += "pad-oper";
            options += separator;
        }
        // begin pad parens check
        if (padParenOutside && padParenInside)
        {   options += "pad-paren";
            options += separator;
        }
        else if (padParenOutside)
        {   options += "pad-paren-out";
            options += separator;
        }
        else if (padParenInside)
        {   options += "pad-paren-in";
            options += separator;
        }
        // end pad parens check
        if (padFirstParenOut)
        {   options += "pad-first-paren-out";
            options += separator;
        }
        if (padHeader)
        {   options += "pad-header";
            options += separator;
        }
        if (unpadParen)
        {   options += "unpad-paren";
            options += separator;
        }
        if (deleteEmptyLines)
        {   options += "delete-empty-lines";
            options += separator;
        }
        if (fillEmptyLines)
        {   options += "fill-empty-lines";
            options += separator;
        }
        if (alignPointer != PTR_ALIGN_NONE)
        {   if (alignPointer == PTR_ALIGN_TYPE)
                options += "align-pointer=type";
            else if (alignPointer == PTR_ALIGN_MIDDLE)
                options += "align-pointer=middle";
            else if (alignPointer == PTR_ALIGN_NAME)
                options += "align-pointer=name";
            else
            {   options += "align-pointer="        // force an error message
                           + alignPointer;
            }
            options += separator;
        }
        if (alignReference != REF_SAME_AS_PTR)
        {   if (alignReference == REF_ALIGN_NONE)
            {   options += "align-reference=none";
                options += separator;
            }
            else if (alignReference == REF_ALIGN_TYPE)
            {   if (alignPointer != PTR_ALIGN_TYPE)
                {   options += "align-reference=type";
                    options += separator;
                }
            }
            else if (alignReference == REF_ALIGN_MIDDLE)
            {   if (alignPointer != PTR_ALIGN_MIDDLE)
                {   options += "align-reference=middle";
                    options += separator;
                }
            }
            else if (alignReference == REF_ALIGN_NAME)
            {   if (alignPointer != PTR_ALIGN_NAME)
                {   options += "align-reference=name";
                    options += separator;
                }
            }
            else
            {   options += "align-reference="      // force an error message
                           + alignReference;
                options += separator;
            }
        }
        if (breakCloseBrackets)
        {   options += "break-closing-brackets";
            options += separator;
        }
        if (breakElseIfs)
        {   options += "break-elseifs";
            options += separator;
        }
        if (addBrackets)
        {   options += "add-brackets";
            options += separator;
        }
        if (addOneLineBrackets)
        {   options += "add-one-line-brackets";
            options += separator;
        }
        if (! breakOneLineStmts)               // default = true
        {   options += "keep-one-line-statements ";
            options += separator;
        }
        if (! breakOneLineBlocks)              // default = true
        {   options += "keep-one-line-blocks";
            options += separator;
        }
        if (convertTabs)
        {   options += "convert-tabs";
            options += separator;
        }
        if (maxCodeLength > 0)
        {   if (maxCodeLength >= MAX_CODE_LENGTH_MIN && maxCodeLength <= MAX_CODE_LENGTH_MAX)
                options += "max-code-length=" + maxCodeLength;
            else
                options += "maxCodeLength=" + maxCodeLength;
            options += separator;
            if (breakAfterLogical)
            {   options += "break-after-logical";
                options += separator;
            }
        }
        // add the file mode, default is C++
        if (fileMode == FILEMODE_CPP)
        {   if (options.Length > 0)            // delete the last separator
                options.TrimEnd('\n');
        }
        else if (fileMode == FILEMODE_JAVA)
            options += "mode=java";
        else if (fileMode == FILEMODE_SHARP)
            options += "mode=cs";
        else
            options += "fileMode=" + fileMode; // force an error message

        return options;
    }

    /// Set the fileMode variable from the input file extension.
    public void SetFileMode(String fileName)
    {   fileMode = FILEMODE_CPP;
        if (fileName.EndsWith(".java"))
            fileMode = FILEMODE_JAVA;
        else if (fileName.EndsWith(".cs"))
            fileMode = FILEMODE_SHARP;
    }

    /// Set options for testing.
    /// For test program only.
    /// Calls the private setTestOptionsX().
    public void setTestOptions()
    {   setTestOptionsX();
    }

    ///  Set option variables for testing.
    /// For test program only.
    /// This will not be used by an actual program.
    private void setTestOptionsX()
    {   // bracket Style options
        //~ bracketStyle = STYLE_ALLMAN;

        //~ // tabs / spaces options
        //~ indentType   = INDENT_TABS;
        //~ indentLength = 3;
        //~ useTabLength = true;
        //~ tabLength=6;

        //~ // indentation options
        //~ classIndent        = true;
        //~ switchIndent       = true;
        //~ caseIndent         = true;
        //~ namespaceIndent    = true;
        //~ labelIndent        = true;
        //~ preprocessorIndent = true;
        //~ col1CommentIndent  = true;
        //~ maxInStatementIndent = 50;
        //~ minConditionalOption = 0;

        //~ // padding options
        //~ breakHeaderBlocks  = true;
        //~ breakClosingBlocks = true;
        //~ padOperator        = true;
        //~ padParenOutside    = true;
        //~ padFirstParenOut   = true;
        //~ padParenInside     = true;
        //~ padHeader          = true;
        //~ unpadParen         = true;
        //~ deleteEmptyLines   = true;
        //~ fillEmptyLines     = true;
        //~ alignPointer       = PTR_ALIGN_TYPE;
        //~ alignReference     = REF_ALIGN_NAME;

        //~ // formatting options
        //~ breakCloseBrackets = true;
        //~ breakElseIfs       = true;
        //~ addBrackets        = true;
        //~ addOneLineBrackets = true;
        //~ breakOneLineStmts  = false;
        //~ breakOneLineBlocks = false;
        //~ convertTabs        = true;
        //~ maxCodeLength      = 100;
        //~ breakAfterLogical  = true;

        //~ // generate some errors
        //~ bracketStyle   = 20;
        //~ maxInStatementIndent = 90;
        //~ minConditionalOption = 50;
        //~ maxCodeLength = 500;
        //~ // cannot have both invalid indentLength and invalid indentType
        //~ indentLength      = 21;
        //~ indentType        = 6;

        // fileMode option - FILEMODE_SHARP is required for C# files
        fileMode = FILEMODE_SHARP;
    }

    // functions to call Artistic Style ---------------------------------------------------

    // Dll name
#if (DEBUG)
    private const String dllName = "astyled";
#else
    private const String dllName = "astyle";
#endif

    // Cannot use String as a return value because Mono runtime will attempt to
    // free the returned pointer resulting in a runtime crash.
    [DllImport(dllName, CallingConvention = CallingConvention.StdCall)]
    private static extern IntPtr AStyleGetVersion();

    // Cannot use String as a return value because Mono runtime will attempt to
    // free the returned pointer resulting in a runtime crash.
    [DllImport(dllName, CallingConvention = CallingConvention.StdCall)]
    private static extern IntPtr AStyleMain
    (
        [MarshalAs(UnmanagedType.LPStr)] String sIn,
        [MarshalAs(UnmanagedType.LPStr)] String sOptions,
        AStyleErrorDelgate errorFunc,
        AStyleMemAllocDelgate memAllocFunc
    );

    /// AStyleMain callbacks
    private delegate IntPtr AStyleMemAllocDelgate(int size);
    private delegate void AStyleErrorDelgate
    (
        int errorNum,
        [MarshalAs(UnmanagedType.LPStr)] String error
    );

    /// AStyleMain Delegates
    private AStyleMemAllocDelgate AStyleMemAlloc;
    private AStyleErrorDelgate AStyleError;

    /// Call the AStyleMain function in Artistic Style.
    /// An empty string is returned on error.
    public String FormatSource(String textIn)
    {   String options = GetOptions();
//        DisplayErrorMessage("--------------------\n"
//                           + options + "\n"
//                           + "--------------------" );
        // Return the allocated string
        // Memory space is allocated by OnAStyleMemAlloc, a callback function from AStyle
        String sTextOut = String.Empty;
        try
        {   IntPtr pText = AStyleMain(textIn, options, AStyleError, AStyleMemAlloc);
            if (pText != IntPtr.Zero)
            {   sTextOut = Marshal.PtrToStringAnsi(pText);
                Marshal.FreeHGlobal(pText);
            }
        }
        catch (BadImageFormatException e)
        {   DisplayErrorMessage(e.ToString());
            DisplayErrorMessage("You may be mixing 32 and 64 bit code!");
        }
        catch (DllNotFoundException)
        {   //DisplayErrorMessage(e.ToString());
            DisplayErrorMessage("Cannot load native library: " + dllName);
            DisplayErrorMessage("The program has terminated!");
            Environment.Exit(1);
        }
        catch (Exception e)
        {   DisplayErrorMessage(e.ToString());
        }
        return sTextOut;
    }

    /// Set fileMode and call the AStyleMain function in Artistic Style.
    public String FormatSource(String textIn, String fileName)
    {   SetFileMode(fileName);
        String textOut = FormatSource(textIn);
        return textOut;
    }

    /// Set fileMode and call the AStyleMain function in Artistic Style.
    public String FormatSource(String textIn, int fileModeArg)
    {   // set file mode before formatting source
        fileMode = fileModeArg;
        String textOut = FormatSource(textIn);
        return textOut;
    }

    /// Get the Artistic Style version number.
    /// Does not need to terminate on error.
    /// But the exception must be handled when a function is called.
    public String GetVersion()
    {   String sVersion = String.Empty;
        try
        {   IntPtr  pVersion = AStyleGetVersion();
            if (pVersion != IntPtr.Zero)
            {   sVersion = Marshal.PtrToStringAnsi(pVersion);
            }
        }
        catch (BadImageFormatException e)
        {   DisplayErrorMessage(e.ToString());
            DisplayErrorMessage("You may be mixing 32 and 64 bit code!");
            DisplayErrorMessage("The program has terminated!");
            Environment.Exit(1);
        }
        catch (DllNotFoundException)
        {   //DisplayErrorMessage(e.ToString());
            DisplayErrorMessage("Cannot load native library: " + dllName);
            DisplayErrorMessage("The program has terminated!");
            Environment.Exit(1);
        }
        catch (Exception e)
        {   DisplayErrorMessage(e.ToString());
            DisplayErrorMessage("The program has terminated!");
            Environment.Exit(1);
        }
        return sVersion;
    }

    /// Allocate the memory for the Artistic Style return string.
    private IntPtr OnAStyleMemAlloc(int size)
    {   return Marshal.AllocHGlobal(size);
    }

    /// Display errors from Artistic Style .
    private void OnAStyleError(int errorNumber, String errorMessage)
    {   DisplayErrorMessage("astyle error " + errorNumber + " - " + errorMessage);
    }

}   // class AStyleInterface
