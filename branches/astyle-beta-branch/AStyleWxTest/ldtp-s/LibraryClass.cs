using NUnit.Framework;
using System;
using System.Diagnostics;
using System.IO;


[SetUpFixture]
public class LibraryClass
{
	// Visual Studio release - activate only one
	//static string VS_RELEASE = "vs2010";
	//static string VS_RELEASE = "vs2012";
	static string VS_RELEASE = "vs2013";
	//static string VS_RELEASE = "vs2015";

	// wxWidgets release - activate only one
	//static string WX_RELEASE = "2.8";
	static string WX_RELEASE = "3.0";

	static Ldtp.Ldtp ldtp = null;

	/// Setup method for the all the menu test fixtures.
	/// The SetUp method in this class is executed once before
	/// any of the fixtures contained in its namespace.
	[SetUp]
	public static void MenuSetUpFixture()
	{
		// display warning messages
		Console.WriteLine("\nThis test MUST be run as an administrator.");
		Console.WriteLine("Otherwise the WinLdtpService will not work.");
		Console.WriteLine("And an \"Unable to connect...\" exception will be thrown.");
		Console.WriteLine("Do NOT use the mouse while this test is running.\n");

		//  create ldtp
		// failure does not throw a catchable object
		// it will fail at ldtp.LaunchApp() in LaunchAStyleWxLdtp()
		Console.WriteLine("Creating ldtp object");
		ldtp = new Ldtp.Ldtp("*AStyleWx");

		// compile astylewx
		Console.WriteLine("Compiling astylewx");
		LibraryClass.CompileWindowsAStyleWxExe("DLL Debug");
	}

	public static void CloseAStyleWxLdtp(Ldtp.Ldtp ldtp)
	{
		// Console.WriteLine("Closing AStyleWx");
		ldtp.SelectMenuItem("mnuFile;mnuExit");
		if (ldtp.WaitTillGuiNotExist() != 1)
		{
			Console.WriteLine("Error in WaitTillGuiNotExist");
			Environment.Exit(1);
		}
	}

	public static void CompileWindowsAStyleWxExe(string config)
	{
		string slnpath = GetAStyleWxPath()
		                 + @"\build\"
		                 + VS_RELEASE + "_" + WX_RELEASE
		                 + @"\AStyleWx_" + WX_RELEASE
		                 + ".sln";

		// call MSBuild
		string compver = "12.0";
		if (string.Compare(VS_RELEASE, "vs2015", true) >= 0)
			compver = "14.0";

		string buildpath = @"C:\Program Files (x86)\MSBuild\"
		                   + compver
		                   + @"\Bin\MSBuild.exe";

		if (!File.Exists(buildpath))
		{
			Console.WriteLine("\nCannot find build path: " + buildpath);
			Environment.Exit(1);
		}

		string configProp = @"/property:Configuration=" + config;
		string platformProp = @"/property:Platform=Win32";
		// quote every argument in the build command
		string buildArgs = string.Format("\"{0}\" \"{1}\" \"{2}\"",
		                                 configProp, platformProp, slnpath);

		ProcessStartInfo astylewx = new ProcessStartInfo();
		astylewx.FileName = buildpath;
		astylewx.Arguments = buildArgs;
		astylewx.WindowStyle = ProcessWindowStyle.Hidden;
		astylewx.CreateNoWindow = true;

		int retval = 0;
		using (Process proc = Process.Start(astylewx))
		{
			proc.WaitForExit();
			retval = proc.ExitCode;
		}
		if (retval != 0)
		{
			Console.WriteLine("\nBad msbuild return: " + retval);
			Environment.Exit(1);
		}
	}

	public static string GetAStyleWxPath()
	{
		// get executable filepath for the dll
		string dllpath = Directory.GetCurrentDirectory();
		int end = dllpath.IndexOf("AStyleWxTest");
		string exepath = dllpath.Substring(0, end) + @"AStyleWx";
		return exepath;
	}

	public static Ldtp.Ldtp GetLdtpObject()
	{
		return ldtp;
	}

	public static Ldtp.Ldtp LaunchAStyleWxLdtp()
	{
		string exepath = GetAStyleWxPath()
		                 + @"\build\"
		                 + VS_RELEASE  + "_" + WX_RELEASE
		                 + @"\debug\AStyleWxd_dll.exe";
		string[] exeargs = new string[1] { "--ldtp_test" };

		try
		{
			ldtp.LaunchApp(exepath, exeargs);
		}
		catch (Exception e)
		{
			Console.WriteLine('\n' + e.Message);
			Console.WriteLine("This test MUST be run as an administrator.\n");
			Environment.Exit(1);
		}

		if (ldtp.WaitTillGuiExist() == 0)
		{
			Console.WriteLine("Error in WaitTillGuiExist");
			Environment.Exit(1);
		}

		return ldtp;
	}
}
