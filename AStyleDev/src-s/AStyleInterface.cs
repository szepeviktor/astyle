// AStyleInterface.cs

using System;
using System.Runtime.InteropServices;

/// AStyleInterface contains methods to call the Artistic Style formatter.
public class AStyleInterface
{   // Dll name
#if (WINDOWS)
// Windows will NOT attach an extension to a filename containing dots (.).
#if (DEBUG)
    private const string DllName = "astyle-2.06d.dll";
#else
    private const string DllName = "astyle-2.06.dll";
#endif
#else
#if (DEBUG)
    private const string DllName = "astyle-2.06d";
#else
    private const string DllName = "astyle-2.06";
#endif
#endif
    /// AStyleGetVersion DllImport.
    /// Cannot use string as a return value because Mono runtime will attempt to
    /// free the returned pointer resulting in a runtime crash.
    /// NOTE: CharSet.Unicode is NOT used here.
    [DllImport(DllName)]
    private static extern IntPtr AStyleGetVersion();

    /// AStyleMainUtf16 DllImport.
    /// Cannot use string as a return value because Mono runtime will attempt to
    /// free the returned pointer resulting in a runtime crash.
    /// NOTE: CharSet.Unicode and wide strings are used here.
    [DllImport(DllName, CharSet = CharSet.Unicode)]
    private static extern IntPtr AStyleMainUtf16(
        [MarshalAs(UnmanagedType.LPWStr)] string sIn,
        [MarshalAs(UnmanagedType.LPWStr)] string sOptions,
        AStyleErrorDelgate errorFunc,
        AStyleMemAllocDelgate memAllocFunc
    );

    /// AStyleMainUtf16 callbacks.
    /// NOTE: Wide strings are NOT used here.
    private delegate IntPtr AStyleMemAllocDelgate(int size);
    private delegate void AStyleErrorDelgate(
        int errorNum,
        [MarshalAs(UnmanagedType.LPStr)] string error
    );

    /// AStyleMainUtf16 Delegates.
    private AStyleMemAllocDelgate AStyleMemAlloc;
    private AStyleErrorDelgate AStyleError;

    /// Declare callback functions.
    public AStyleInterface()
    {   AStyleMemAlloc = new AStyleMemAllocDelgate(OnAStyleMemAlloc);
        AStyleError = new AStyleErrorDelgate(OnAStyleError);
    }

    /// Call the AStyleMainUtf16 function in Artistic Style.
    /// An empty string is returned on error.
    public string FormatSource(string textIn, string options)
    {   // Return the allocated string
        // Memory space is allocated by OnAStyleMemAlloc, a callback function
        string sTextOut = string.Empty;
        try
        {   IntPtr pText = AStyleMainUtf16(textIn, options, AStyleError, AStyleMemAlloc);
            if (pText != IntPtr.Zero)
            {   sTextOut = Marshal.PtrToStringUni(pText);
                Marshal.FreeHGlobal(pText);
            }
        }
        catch (BadImageFormatException e)
        {   Console.WriteLine(e.ToString());
            Console.WriteLine("You may be mixing 32 and 64 bit code!");
        }
        catch (DllNotFoundException)
        {   //Console.WriteLine(e.ToString());
            Console.WriteLine("Cannot load native library: " + DllName);
            Console.WriteLine("The program has terminated!");
            Environment.Exit(1);
        }
        catch (Exception e)
        {   Console.WriteLine(e.ToString());
        }
        return sTextOut;
    }

    /// Get the Artistic Style version number.
    /// Does not need to terminate on error.
    /// But the exception must be handled when a function is called.
    public string GetVersion()
    {   string sVersion = string.Empty;
        try
        {   IntPtr pVersion = AStyleGetVersion();
            if (pVersion != IntPtr.Zero)
            {   sVersion = Marshal.PtrToStringAnsi(pVersion);
            }
        }
        catch (BadImageFormatException e)
        {   Console.WriteLine(e.ToString());
            Console.WriteLine("You may be mixing 32 and 64 bit code!");
            Console.WriteLine("The program has terminated!");
            Environment.Exit(1);
        }
        catch (DllNotFoundException)
        {   //Console.WriteLine(e.ToString());
            Console.WriteLine("Cannot load native library: " + DllName);
            Console.WriteLine("The program has terminated!");
            Environment.Exit(1);
        }
        catch (Exception e)
        {   Console.WriteLine(e.ToString());
            Console.WriteLine("The program has terminated!");
            Environment.Exit(1);
        }
        return sVersion;
    }

    /// Allocate the memory for the Artistic Style return string.
    private IntPtr OnAStyleMemAlloc(int size)
    {   return Marshal.AllocHGlobal(size);
    }

    /// Display errors from Artistic Style .
    private void OnAStyleError(int errorNumber, string errorMessage)
    {   Console.WriteLine("AStyle error " + errorNumber + "\n" + errorMessage);
    }

}   // class AStyleInterface
