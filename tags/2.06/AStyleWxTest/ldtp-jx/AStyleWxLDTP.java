import java.io.File;
import com.cobra.ldtp.Ldtp;

public class AStyleWxLDTP
{
	public static void main(String[] args)
	{
		String exepath = "C:\\Users\\jimp\\Projects\\AStyleWx\\build\\vs2013_3.0\\debug\\AStyleWxd.exe";
		String[] noargs = { "" };

		System.out.println("Running C#");
		System.out.println("Creating ldtp");
		Ldtp ldtp = new Ldtp("*AStyleWx");
		if (ldtp == null)
		{
			System.out.println("Cannot create ldtp object");
			System.out.println("The program has terminated!");
			System.exit(1);
		}

		if (!new File(exepath).isFile())
		{
			System.out.println("Cannot find executable: " + exepath);
			System.out.println("The program has terminated!");
			System.exit(1);
		}

		System.out.println("Launching AStyleWx");
		try
		{
			ldtp.launchApp(exepath, noargs);
		}
		catch (Exception e)
		{
			System.out.println("Error in launchapp: " + exepath);
			System.out.println(e.getMessage());
			System.out.println("The program has terminated!");
			System.exit(1);

		}
		if (ldtp.waitTillGuiExist() == 0)
		{
			System.out.println("Error in WaitTillGuiExist");
			System.out.println("The program has terminated!");
			System.exit(1);
		}

		String[] SubMenus = new String[20];
		System.out.println("\nFile");
		SubMenus = ldtp.listSubMenus("mnuFile");
		PrintSubMenus(SubMenus);
		System.out.println("\nEdit");
		SubMenus = ldtp.listSubMenus("mnuEdit");
		PrintSubMenus(SubMenus);
		System.out.println("\nSearch");
		SubMenus = ldtp.listSubMenus("mnuSearch");
		PrintSubMenus(SubMenus);
		System.out.println("\nView");
		SubMenus = ldtp.listSubMenus("mnuView");
		PrintSubMenus(SubMenus);
		System.out.println("\nTools");
		SubMenus = ldtp.listSubMenus("mnuTools");
		PrintSubMenus(SubMenus);
		System.out.println("\nHelp");
		SubMenus = ldtp.listSubMenus("mnuHelp");
		PrintSubMenus(SubMenus);
		System.out.println();

		System.out.println("Closing AStyleWx");
		ldtp.selectMenuItem("mnuFile;mnuExit");
		if (ldtp.waitTillGuiNotExist("frmAStyleWx") == 0)
		{
			System.out.println("Error in WaitTillGuiNotExist: " + exepath);
			System.out.println("The program has terminated!");
			System.exit(1);
		}

		System.out.println("End of program!");
	}

	private static void PrintSubMenus(String[] subMenus)
	{
		for (String subMenu : subMenus)
		{
			if (subMenu != subMenus[0])
				System.out.print(", ");
			System.out.print(subMenu);
		}
		System.out.print("\n");
	}
}
