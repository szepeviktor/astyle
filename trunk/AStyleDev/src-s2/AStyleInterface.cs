// AStyleInterface.cs

using System;
using System.IO;
using System.Runtime.InteropServices;

interface NativeLibrary
{   void FreeLibrary(IntPtr handle);
    IntPtr GetProcAddress(IntPtr handle, string procName);
    IntPtr LoadLibrary(string fileName);
}

/// Windows native methods.
internal class NativeLibraryWindows : NativeLibrary
{   void NativeLibrary.FreeLibrary(IntPtr handle)
    {   FreeLibrary(handle);
    }

    IntPtr NativeLibrary.GetProcAddress(IntPtr handle, string procName)
    {   return GetProcAddress(handle, procName);
    }

    IntPtr NativeLibrary.LoadLibrary(string fileName)
    {   return LoadLibrary(fileName);
    }

    [DllImport("kernel32.dll")]
    private static extern IntPtr LoadLibrary(string fileName);

    [DllImport("kernel32.dll")]
    private static extern int FreeLibrary(IntPtr handle);

    [DllImport("kernel32.dll")]
    private static extern IntPtr GetProcAddress(IntPtr handle, string procName);
}


/// Linux native methods.
internal class NativeLibraryLinux : NativeLibrary
{   public void FreeLibrary(IntPtr handle)
    {   dlclose(handle);
    }

    public IntPtr GetProcAddress(IntPtr handle, string procName)
    {   dlerror();      // clear previous errors if any
        var res = dlsym(handle, procName);
        var errPtr = dlerror();
        if (errPtr != IntPtr.Zero)
            Console.WriteLine("dlsym: " + Marshal.PtrToStringAnsi(errPtr));
        return res;
    }

    public IntPtr LoadLibrary(string fileName)
    {   dlerror();      // clear previous errors if any
        var res = dlopen(fileName, RTLD_NOW);
        var errPtr = dlerror();
        if (errPtr != IntPtr.Zero)
            Console.WriteLine("dlopen: " + Marshal.PtrToStringAnsi(errPtr));
        return res;
    }

    const int RTLD_NOW = 2;

    [DllImport("libdl")]
    private static extern IntPtr dlopen(string fileName, int flags);

    [DllImport("libdl")]
    private static extern IntPtr dlsym(IntPtr handle, string symbol);

    [DllImport("libdl")]
    private static extern int dlclose(IntPtr handle);

    [DllImport("libdl")]
    private static extern IntPtr dlerror();
}

/// AStyleInterface contains methods to load the C shared libraries
/// and call the Artistic Style formatter.
public class AStyleInterface
{   /// AStyleGetVersion function call.
    /// NOTE: Wide strings are NOT returned here.
    delegate IntPtr AStyleGetVersion();

    /// AStyleError callback in AStyle.
    /// NOTE: Wide strings are NOT used here.
    delegate void AStyleErrorDelgate(int errorNumber,
                                     [MarshalAs(UnmanagedType.LPStr)] string error);

    /// AStyleMemAlloc callback in AStyle.
    delegate IntPtr AStyleMemAllocDelgate(int size);

    /// AStyleMainUtf16 function call.
    /// NOTE: Wide strings ARE used here (UTF-16 in BOTH Windows and Linux).
    delegate IntPtr AStyleMainUtf16([MarshalAs(UnmanagedType.LPWStr)] string textIn,
                                    [MarshalAs(UnmanagedType.LPWStr)] string options,
                                    AStyleErrorDelgate AStyleError,
                                    AStyleMemAllocDelgate AStyleMemAlloc);

    private NativeLibrary astyle = null;

    private IntPtr astyleHandle = IntPtr.Zero;

    private AStyleMainUtf16 fpAStyleMainUtf16 = null;

    private AStyleGetVersion fpAStyleGetVersion = null;

    /// The constructor will load the native Artistic Style library and
    /// get the procedure addresses to call functions in the library.
    /// LoadLibrary has a reference count and will load the library only when needed.
    public AStyleInterface()
    {   astyle = IsWindows()
                 ? (NativeLibrary)new NativeLibraryWindows()
                 : new NativeLibraryLinux();

        // must indicate the current directory for the Linux shared object
        string libraryName = "./" + GetLibraryName();
        // load the library
        // loadLibrary has a reference count and will load the library only when needed
        if (!File.Exists(libraryName))
        {   Error("Cannot find native library " + libraryName);
        }
        astyleHandle = astyle.LoadLibrary(libraryName);
        if (astyleHandle == IntPtr.Zero)
        {   Console.WriteLine("Cannot load the native library " + libraryName);
            Error("You may be mixing 32 and 64 bit code!");
        }

        // get the procedure address for AStyleGetVersion
        var astyleVersionHandle = astyle.GetProcAddress(astyleHandle, "AStyleGetVersion");
        if (astyleVersionHandle == IntPtr.Zero)
        {   Console.WriteLine("Cannot find the symbol AStyleGetVersion in " + libraryName);
            Error("The function must be undecorated in the library.");
        }
        fpAStyleGetVersion = (AStyleGetVersion)Marshal.GetDelegateForFunctionPointer(
                                 astyleVersionHandle, typeof(AStyleGetVersion));

        // get the procedure address for AStyleMainUtf16
        var astyleMainUtf16Handle = astyle.GetProcAddress(astyleHandle, "AStyleMainUtf16");
        if (astyleMainUtf16Handle == IntPtr.Zero)
        {   Console.WriteLine("Cannot find the symbol AStyleMainUtf16 in " + libraryName);
            Error("The function must be undecorated in the library.");
        }
        fpAStyleMainUtf16 = (AStyleMainUtf16)Marshal.GetDelegateForFunctionPointer(
                                astyleMainUtf16Handle, typeof(AStyleMainUtf16));
    }

    /// The destructor will free the native Artistic Style library.
    /// FreeLibrary has a reference count and will free the library only when needed.
    ~AStyleInterface()
    {   astyle.FreeLibrary(astyleHandle);
    }

    /// Error handler to abort the program.
    private void Error(string message)
    {   Console.WriteLine(message);
        Console.WriteLine("The program has terminated!");
        Environment.Exit(1);
    }

    /// Call the AStyleMainUtf16 function in Artistic Style.
    /// An empty string is returned on error.
    public string FormatSource(string textIn, string options)
    {   // Return the allocated string
        // Memory space is allocated by AStyleMemAlloc, a callback function
        string textOut = String.Empty;
        try
        {   // NOTE: a Unicode string IS returned here.
            IntPtr fpText = fpAStyleMainUtf16(textIn, options,
                                              AStyleError, AStyleMemAlloc);
            if (fpText != IntPtr.Zero)
            {   textOut = Marshal.PtrToStringUni(fpText);
                Marshal.FreeHGlobal(fpText);
            }
        }
        catch (Exception e)
        {   Console.WriteLine(e.ToString());
        }
        return textOut;
    }

    /// Called by constructor to get the shared library name.
    /// This will get any version of the library in the executable's directory.
    /// Usually a specific version would be obtained, in which case a constant
    /// could be used for the library name.
    private string GetLibraryName()
    {   // get a library name in the executable's directory (any platform)
        // the following example will allow different library names for x86 and x64
        //if (IsWindows())
        //    libraryName = IntPtr.Size == 8 ? "AStyle64-2.06.dll" : "AStyle32-2.06.dll";
        //else
        //    libraryName = IntPtr.Size == 8 ? "libastyle64-2.06.so" : "libastyle32-2.06.so";
        string libraryName = null;
        string appDirectory = System.AppDomain.CurrentDomain.BaseDirectory;
        string[] files = Directory.GetFiles(appDirectory, "*.*");
        foreach (string filePath in files)
        {   string fileName = Path.GetFileName(filePath).ToLower();
            if ((fileName.EndsWith(".dll")
                    || fileName.Contains(".so")
                    || fileName.EndsWith(".dylib"))
                    && (fileName.StartsWith("astyle")
                        || fileName.StartsWith("libastyle")))
            {   libraryName = Path.GetFileName(filePath);
                break;
            }
        }
        if (libraryName == null)
        {   Error("Cannot find astyle native library in " + appDirectory);
        }
        return libraryName;
    }

    /// Get the Artistic Style version number.
    public string GetVersion()
    {   string version = String.Empty;
        try
        {   // NOTE: a Unicode string is NOT returned here.
            IntPtr fpVersion = fpAStyleGetVersion();
            if (fpVersion != IntPtr.Zero)
            {   version = Marshal.PtrToStringAnsi(fpVersion);
            }
        }
        catch (Exception e)
        {   Error(e.ToString());
        }
        return version;
    }

    /// Determine if this is a Linux platform.
    private bool IsLinux()
    {   var p = (int)Environment.OSVersion.Platform;
        return (p == 4) || (p == 6) || (p == 128);
    }

    /// Determine if this is a Windows platform.
    private bool IsWindows()
    {   var p = (int)Environment.OSVersion.Platform;
        return (p != 4) && (p != 6) && (p != 128);
    }

    /// AStyleMainUtf16 callback to allocate memory for the return string.
    private IntPtr AStyleMemAlloc(int size)
    {   return Marshal.AllocHGlobal(size);
    }

    /// AStyleMainUtf16 callback to display errors from Artistic Style.
    private void AStyleError(int errorNumber, string error)
    {   Console.WriteLine("AStyle error " + errorNumber + "\n" + error);
    }

}   // class AStyleInterface
