using System;
using Ldtp;

class Program
{
	static void Main(string[] args)
	{
		string exepath = @"C:\Users\jimp\Projects\AStyleWx\build\vs2013_3.0\debug\AStyleWxd.exe";
		string[] noargs = new string[1] { "" };

		Console.WriteLine("Running C#");
		Console.WriteLine("Creating ldtp");
		Ldtp.Ldtp ldtp = new Ldtp.Ldtp("*AStyleWx");
		if (ldtp == null)
		{
			Console.WriteLine("Cannot create ldtp object");
			Console.WriteLine("The program has terminated!");
			Environment.Exit(1);
		}

		if (!System.IO.File.Exists(exepath))
		{
			Console.WriteLine("Cannot find executable: " + exepath);
			Console.WriteLine("The program has terminated!");
			Environment.Exit(1);
		}

		Console.WriteLine("Launching AStyleWx");
		try
		{
			ldtp.LaunchApp(exepath, noargs);
		}
		catch (Exception e)
		{
			Console.WriteLine("Error in launchapp: " + exepath);
			Console.WriteLine(e.Message);
			Console.WriteLine("The program has terminated!");
			Environment.Exit(1);

		}
		if (ldtp.WaitTillGuiExist() == 0)
		{
			Console.WriteLine("Error in WaitTillGuiExist");
			Console.WriteLine("The program has terminated!");
			Environment.Exit(1);
		}

		string[] SubMenus = new string[20];
		Console.WriteLine("\nFile");
		SubMenus = ldtp.ListSubMenus("mnuFile");
		PrintSubMenus(SubMenus);
		Console.WriteLine("\nEdit");
		SubMenus = ldtp.ListSubMenus("mnuEdit");
		PrintSubMenus(SubMenus);
		Console.WriteLine("\nSearch");
		SubMenus = ldtp.ListSubMenus("mnuSearch");
		PrintSubMenus(SubMenus);
		Console.WriteLine("\nView");
		SubMenus = ldtp.ListSubMenus("mnuView");
		PrintSubMenus(SubMenus);
		Console.WriteLine("\nTools");
		SubMenus = ldtp.ListSubMenus("mnuTools");
		PrintSubMenus(SubMenus);
		Console.WriteLine("\nHelp");
		SubMenus = ldtp.ListSubMenus("mnuHelp");
		PrintSubMenus(SubMenus);
		Console.WriteLine();

		Console.WriteLine("Closing AStyleWx");
		ldtp.SelectMenuItem("mnuFile;mnuExit");
		if (ldtp.WaitTillGuiNotExist("frmAStyleWx") == 0)
		{
			Console.WriteLine("Error in WaitTillGuiNotExist: " + exepath);
			Console.WriteLine("The program has terminated!");
			Environment.Exit(1);
		}

		Console.WriteLine("End of program!");
	}

	private static void PrintSubMenus(string[] subMenus)
	{
		foreach (string subMenu in subMenus)
		{
			if (subMenu != subMenus[0])
				Console.Write(", ");
			Console.Write(subMenu);
		}
		Console.Write("\n");
	}
}
