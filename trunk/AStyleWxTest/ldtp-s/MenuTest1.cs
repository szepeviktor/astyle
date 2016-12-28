using System;
using NUnit.Framework;

/// <summary>
/// Summary description for MenuTest1
/// </summary>

[TestFixture]
public class MenuTest1
{
	Ldtp.Ldtp ldtp = null;

	[TestFixtureSetUp]
	public void MenuSetUp()
	{
		ldtp = LibraryClass.GetLdtpObject();
		LibraryClass.LaunchAStyleWxLdtp();
	}

	[TestFixtureTearDown]
	public void MenuTearDown()
	{
		LibraryClass.CloseAStyleWxLdtp(ldtp);
	}

	//# FILE MENU

	[Test]
	public void FileNew()
	{
		int fileNewEnabled = ldtp.MenuItemEnabled("mnuFile;mnuNew");
		Assert.That(fileNewEnabled, Is.EqualTo(1));
	}

	[Test]
	public void FileOpen()
	{
		int fileOpenEnabled = ldtp.MenuItemEnabled("mnuFile;mnuOpen");
		Assert.That(fileOpenEnabled, Is.EqualTo(1));
	}

	[Test]
	public void FileClose()
	{
		int fileCloseEnabled = ldtp.MenuItemEnabled("mnuFile;mnuClose");
		Assert.That(fileCloseEnabled, Is.EqualTo(1));
	}

	[Test]
	public void FileSave()
	{
		int fileSaveEnabled = ldtp.MenuItemEnabled("mnuFile;mnuSave");
		Assert.That(fileSaveEnabled, Is.Not.EqualTo(1));
	}

	[Test]
	public void FileSaveAs()
	{
		int fileSaveAsEnabled = ldtp.MenuItemEnabled("mnuFile;mnuSaveAs");
		Assert.That(fileSaveAsEnabled, Is.EqualTo(1));
	}

	[Test]
	public void FileExit()
	{
		int fileExiEnabled = ldtp.MenuItemEnabled("mnuFile;mnuExit");
		Assert.That(fileExiEnabled, Is.EqualTo(1));
	}

	//# EDIT MENU

	[Test]
	public void EditUndo()
	{
		int editUndoEnabled = ldtp.MenuItemEnabled("mnuEdit;mnuUndo");
		Assert.That(editUndoEnabled, Is.Not.EqualTo(1));
	}

	[Test]
	public void EditRedo()
	{
		int editRedoEnabled = ldtp.MenuItemEnabled("mnuEdit;mnuRedo");
		Assert.That(editRedoEnabled, Is.Not.EqualTo(1));
	}

	[Test]
	public void EditCut()
	{
		int editCutEnabled = ldtp.MenuItemEnabled("mnuEdit;mnuCut");
		Assert.That(editCutEnabled, Is.Not.EqualTo(1));
	}

	[Test]
	public void EditCopy()
	{
		int editCopyEnabled = ldtp.MenuItemEnabled("mnuEdit;mnuCopy");
		Assert.That(editCopyEnabled, Is.Not.EqualTo(1));
	}

	[Test]
	public void EditPaste()
	{
		// paste may or may not be enabled depending on if something is in the clipboard
		// the only thing that can be checked for sure is if the menu exists
		int editPasteExists = ldtp.DoesSelectMenuItemExist("mnuEdit;mnuPaste");
		Assert.That(editPasteExists, Is.EqualTo(1));
	}

	[Test]
	public void EditSelectAll()
	{
		int editSelectAllEnabled = ldtp.MenuItemEnabled("mnuEdit;mnuSelectAll");
		Assert.That(editSelectAllEnabled, Is.EqualTo(1));
	}

	[Test]
	public void EditSelectToStart()
	{
		int editSelectToStartEnabled = ldtp.MenuItemEnabled("mnuEdit;mnuSelecttoStart");
		Assert.That(editSelectToStartEnabled, Is.EqualTo(1));
	}

	[Test]
	public void EditSelectToEnd()
	{
		int editSelectToEndEnabled = ldtp.MenuItemEnabled("mnuEdit;mnuSelecttoEnd");
		Assert.That(editSelectToEndEnabled, Is.EqualTo(1));
	}

	[Test]
	public void EditSelectBlock()
	{
		int editSelectBlockEnabled = ldtp.MenuItemEnabled("mnuEdit;mnuSelectBlock");
		Assert.That(editSelectBlockEnabled, Is.Not.EqualTo(1));
	}

	[Test]
	public void EditIncreaseIndent()
	{
		int editIncreaseIndentEnabled = ldtp.MenuItemEnabled("mnuEdit;mnuIncreaseIndent");
		Assert.That(editIncreaseIndentEnabled, Is.EqualTo(1));
	}

	[Test]
	public void EditDecreaseIndent()
	{
		int editDecreaseIndentEnabled = ldtp.MenuItemEnabled("mnuEdit;mnuDecreaseIndent");
		Assert.That(editDecreaseIndentEnabled, Is.EqualTo(1));
	}

	[Test]
	public void EditOptions()
	{
		int editOoptionsEnabled = ldtp.MenuItemEnabled("mnuEdit;mnuOptions");
		Assert.That(editOoptionsEnabled, Is.EqualTo(1));
	}

	//# SEARCH MENU

	[Test]
	public void SearchFind()
	{
		int searchFindEnabled = ldtp.MenuItemEnabled("mnuSearch;mnuFind");
		Assert.That(searchFindEnabled, Is.EqualTo(1));
	}

	[Test]
	public void SearchFindNext()
	{
		int searchFindNextEnabled = ldtp.MenuItemEnabled("mnuSearch;mnuFindNext");
		Assert.That(searchFindNextEnabled, Is.Not.EqualTo(1));
	}

	[Test]
	public void SearchFindPrevious()
	{
		int searchFindPreviousEnabled = ldtp.MenuItemEnabled("mnuSearch;mnuFindPrevious");
		Assert.That(searchFindPreviousEnabled, Is.Not.EqualTo(1));
	}

	[Test]
	public void SearchGoToLine()
	{
		int searchGoToLineEnabled = ldtp.MenuItemEnabled("mnuSearch;mnuGotoLine");
		Assert.That(searchGoToLineEnabled, Is.EqualTo(1));
	}

	[Test]
	public void SearchNextBookmark()
	{
		int searchNextBookmarkEnabled = ldtp.MenuItemEnabled("mnuSearch;mnuNextBookmark");
		Assert.That(searchNextBookmarkEnabled, Is.EqualTo(1));
	}

	[Test]
	public void SearchPreviousBookmark()
	{
		int searchPreviousBookmarkEnabled = ldtp.MenuItemEnabled("mnuSearch;mnuPreviousBookmark");
		Assert.That(searchPreviousBookmarkEnabled, Is.EqualTo(1));
	}

	[Test]
	public void SearchToggleBookmark()
	{
		int searchToggleBookmarkEnabled = ldtp.MenuItemEnabled("mnuSearch;mnuToggleBookmark");
		Assert.That(searchToggleBookmarkEnabled, Is.EqualTo(1));
	}

	[Test]
	public void SearchClearAllBookmarks()
	{
		int searchClearAllBokmarksEnabled = ldtp.MenuItemEnabled("mnuSearch;mnuClearAllBookmarks");
		Assert.That(searchClearAllBokmarksEnabled, Is.EqualTo(1));
	}

	//# VIEW MENU

	[Test]
	public void ViewLineNumbers()
	{
		int viewLineNumbersEnabled = ldtp.MenuItemEnabled("mnuView;mnuLineNumbers");
		Assert.That(viewLineNumbersEnabled, Is.EqualTo(1));
	}

	[Test]
	public void ViewMargin()
	{
		int viewMarginEnabled = ldtp.MenuItemEnabled("mnuView;mnuMargin");
		Assert.That(viewMarginEnabled, Is.EqualTo(1));
	}

	[Test]
	public void ViewWhiteSpace()
	{
		int viewWhiteSspaceEenabled = ldtp.MenuItemEnabled("mnuView;mnuWhitespace");
		Assert.That(viewWhiteSspaceEenabled, Is.EqualTo(1));
	}

	[Test]
	public void ViewActiveLine()
	{
		int viewActiveLineEnabled = ldtp.MenuItemEnabled("mnuView;mnuActiveLine");
		Assert.That(viewActiveLineEnabled, Is.EqualTo(1));
	}

	[Test]
	public void ViewIndentGuides()
	{
		int viewIndentGuidesEabled = ldtp.MenuItemEnabled("mnuView;mnuIndentGuides");
		Assert.That(viewIndentGuidesEabled, Is.EqualTo(1));
	}

	[Test]
	public void ViewEndOfLine()
	{
		int viewEndOfLineEnabled = ldtp.MenuItemEnabled("mnuView;mnuEndofLine");
		Assert.That(viewEndOfLineEnabled, Is.EqualTo(1));
	}

	[Test]
	public void ViewWordWrap()
	{
		int viewWordWrapEnabled = ldtp.MenuItemEnabled("mnuView;mnuWordWrap");
		Assert.That(viewWordWrapEnabled, Is.EqualTo(1));
	}

	[Test]
	public void ViewToolBar()
	{
		int viewToolBarEnabled = ldtp.MenuItemEnabled("mnuView;mnuToolBar");
		Assert.That(viewToolBarEnabled, Is.EqualTo(1));
	}

	[Test]
	public void ViewStatusBar()
	{
		int viewStatusBarEnabled = ldtp.MenuItemEnabled("mnuView;mnuStatusBar");
		Assert.That(viewStatusBarEnabled, Is.EqualTo(1));
	}

	//# TOOLS MENU

	[Test]
	public void ToolsFileMode()
	{
		int toolsFileModeEnabled = ldtp.MenuItemEnabled("mnuTools;mnuFileMode");
		Assert.That(toolsFileModeEnabled, Is.EqualTo(1));
	}

	[Test]
	public void ToolsLineEnds()
	{
		int toolsLineEndEnabled = ldtp.MenuItemEnabled("mnuTools;mnuLineEnds");
		Assert.That(toolsLineEndEnabled, Is.EqualTo(1));
	}

	[Test]
	public void ToolsFormatSelection()
	{
		int toolsFormatSelectionEnabled = ldtp.MenuItemEnabled("mnuTools;mnuFormatSelection");
		Assert.That(toolsFormatSelectionEnabled, Is.Not.EqualTo(1));
	}

	[Test]
	public void ToolsFormatSource()
	{
		int toolsFormatSourceEnabled = ldtp.MenuItemEnabled("mnuTools;mnuFormatSource");
		Assert.That(toolsFormatSourceEnabled, Is.EqualTo(1));
	}

	[Test]
	public void ToolsTabsToSpaces()
	{
		int toolsTabsToSpacesEnabled = ldtp.MenuItemEnabled("mnuTools;mnuTabstoSpaces");
		Assert.That(toolsTabsToSpacesEnabled, Is.EqualTo(1));
	}

	[Test]
	public void ToolsStripTrailingSpaces()
	{
		int toolsStripTrailingSpacesEnabled = ldtp.MenuItemEnabled("mnuTools;mnuStripTrailingSpaces");
		Assert.That(toolsStripTrailingSpacesEnabled, Is.EqualTo(1));
	}

	[Test]
	public void ToolsAStyleSettings()
	{
		int toolsAStyleSettingsEnabled = ldtp.MenuItemEnabled("mnuTools;mnuAStyleSettings");
		Assert.That(toolsAStyleSettingsEnabled, Is.EqualTo(1));
	}

	[Test]
	public void ToolsTestOptions()
	{
		int toolsTestOptionsEnabled = ldtp.MenuItemEnabled("mnuTools;mnuTestOptions");
		Assert.That(toolsTestOptionsEnabled, Is.EqualTo(1));
	}

	[Test]
	public void ToolsAStyleOptions()
	{
		int toolsAStyleOptionsEnabled = ldtp.MenuItemEnabled("mnuTools;mnuAStyleOptions");
		Assert.That(toolsAStyleOptionsEnabled, Is.EqualTo(1));
	}

	//# HELP MENU

	[Test]
	public void HelpHelp()
	{
		int helpHelpEnabled = ldtp.MenuItemEnabled("mnuHelp;mnuHelp");
		Assert.That(helpHelpEnabled, Is.EqualTo(1));
	}

	[Test]
	public void HelpAbout()
	{
		int helpAboutEnabled = ldtp.MenuItemEnabled("mnuHelp;mnuAbout");
		Assert.That(helpAboutEnabled, Is.EqualTo(1));
	}
}
