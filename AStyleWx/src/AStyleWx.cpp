// AStyleWx.cpp
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.txt describes the conditions under which this software may be distributed.

//-----------------------------------------------------------------------------
// defines for testing
//-----------------------------------------------------------------------------

// the following are defined in _DEBUG only
#ifdef NDEBUG
	#ifdef TESTMODE1
		#error All test mode defines must be 0
	#endif
#endif

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include <wx/dcmemory.h>
#include <wx/msgdlg.h>
#include <wx/stdpaths.h>
#include <wx/textdlg.h>

#include "AboutDlg.h"
#include "AStyleDlg.h"
#include "AStyleWx.h"
#include "EditorDlg.h"
#include "FileManager.h"
#include "SettingsDlg.h"

// define this to use XPMs everywhere except on Windows
// BMPs use less space, but aren't compiled into the executable on other platforms
#ifndef __WXMSW__
	// program icon
	#include "AStyle_16.xpm"
	#include "AStyle_32.xpm"

	// 16x16 toolbar xpm files
	#include "New_16.xpm"
	#include "Open_16.xpm"
	#include "Save_16.xpm"
	#include "Close_16.xpm"
	#include "Undo_16.xpm"
	#include "Redo_16.xpm"
	#include "White_16.xpm"
	#include "All_16.xpm"
	#include "ToEnd_16.xpm"
	#include "Block_16.xpm"
	#include "Select_16.xpm"
	#include "Source_16.xpm"

	// 24x24 toolbar xpm files
	#include "New_24.xpm"
	#include "Open_24.xpm"
	#include "Save_24.xpm"
	#include "Close_24.xpm"
	#include "Undo_24.xpm"
	#include "Redo_24.xpm"
	#include "White_24.xpm"
	#include "All_24.xpm"
	#include "ToEnd_24.xpm"
	#include "Block_24.xpm"
	#include "Select_24.xpm"
	#include "Source_24.xpm"

#endif

//-----------------------------------------------------------------------------
// declarations
//-----------------------------------------------------------------------------

// Implement ASApp& wxGetApp()
DECLARE_APP(ASApp)

//-----------------------------------------------------------------------------
// ASFrame event table
//-----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(ASFrame, wxFrame)
	EVT_MENU_OPEN(						ASFrame::OnMenuOpen)
	// file menu
	EVT_MENU(ID_FILE_NEW,				ASFrame::OnFileMenu)
	EVT_MENU(ID_FILE_OPEN,				ASFrame::OnFileMenu)
	EVT_MENU(ID_FILE_CLOSE,				ASFrame::OnFileMenu)
	EVT_MENU(ID_FILE_SAVE,				ASFrame::OnFileMenu)
	EVT_MENU(ID_FILE_SAVE_AS,			ASFrame::OnFileMenu)
	EVT_MENU(ID_FILE_EXIT,				ASFrame::OnFileMenu)
#ifdef __WXOSX__
	// osx needs for system menu
	EVT_MENU(wxID_EXIT,					ASFrame::OnFileMenu)
#endif
	// edit menu
	EVT_MENU(ID_EDIT_UNDO,				ASFrame::OnEditMenu)
	EVT_MENU(ID_EDIT_REDO,				ASFrame::OnEditMenu)
	EVT_MENU(ID_EDIT_CUT,				ASFrame::OnEditMenu)
	EVT_MENU(ID_EDIT_COPY,				ASFrame::OnEditMenu)
	EVT_MENU(ID_EDIT_PASTE,				ASFrame::OnEditMenu)
	EVT_MENU(ID_EDIT_SELECTALL,			ASFrame::OnEditMenu)
	EVT_MENU(ID_EDIT_SELECTBLOCK,		ASFrame::OnEditMenu)
	EVT_MENU(ID_EDIT_SELECTTOEND,		ASFrame::OnEditMenu)
	EVT_MENU(ID_EDIT_SELECTTOSTART,		ASFrame::OnEditMenu)
	EVT_MENU(ID_EDIT_INCREASE_INDENT,	ASFrame::OnEditMenu)
	EVT_MENU(ID_EDIT_DECREASE_INDENT,	ASFrame::OnEditMenu)
	EVT_MENU(ID_EDIT_EDITOR_OPTIONS,	ASFrame::OnEditMenu)
#ifdef __WXOSX__
	// osx needs for system menu
	EVT_MENU(wxID_PREFERENCES,			ASFrame::OnEditMenu)
#endif
	// search menu
	EVT_MENU(ID_SEARCH_FIND,			ASFrame::OnSearchMenu)
	EVT_MENU(ID_SEARCH_FINDNEXT,		ASFrame::OnSearchMenu)
	EVT_MENU(ID_SEARCH_FINDPREVIOUS,	ASFrame::OnSearchMenu)
	EVT_MENU(ID_SEARCH_GOTOLINE,		ASFrame::OnSearchMenu)
	EVT_MENU(ID_SEARCH_MARKER1_NEXT,	ASFrame::OnSearchMenu)
	EVT_MENU(ID_SEARCH_MARKER1_PREV,	ASFrame::OnSearchMenu)
	EVT_MENU(ID_SEARCH_MARKER1_TOGGLE,	ASFrame::OnSearchMenu)
	EVT_MENU(ID_SEARCH_MARKER1_CLEAR,	ASFrame::OnSearchMenu)
	// view menu
	EVT_MENU(ID_VIEW_LINENUMBERS,		ASFrame::OnViewMenu)
	EVT_MENU(ID_VIEW_MARGIN,			ASFrame::OnViewMenu)
	EVT_MENU(ID_VIEW_WHITESPACE,		ASFrame::OnViewMenu)
	EVT_MENU(ID_VIEW_ACTIVELINE,		ASFrame::OnViewMenu)
	EVT_MENU(ID_VIEW_INDENTGUIDES,		ASFrame::OnViewMenu)
	EVT_MENU(ID_VIEW_ENDLINE,			ASFrame::OnViewMenu)
	EVT_MENU(ID_VIEW_WORDWRAP,			ASFrame::OnViewMenu)
	EVT_MENU(ID_VIEW_MONOSPACE,			ASFrame::OnViewMenu)
	EVT_MENU(ID_VIEW_TOOLBAR,			ASFrame::OnViewMenu)
	EVT_MENU(ID_VIEW_STATUSBAR,			ASFrame::OnViewMenu)
	// tool menu
	EVT_MENU(ID_TOOL_FORMATSELECT,		ASFrame::OnToolMenu)
	EVT_MENU(ID_TOOL_FORMATSOURCE,		ASFrame::OnToolMenu)
	EVT_MENU(ID_TOOL_TABSTOSPACES,		ASFrame::OnToolMenu)
	EVT_MENU(ID_TOOL_TEXTTOSTRINGS,		ASFrame::OnToolMenu)
	EVT_MENU(ID_TOOL_STRIPSPACES,		ASFrame::OnToolMenu)
	// filemode menu, a tool submenu
	EVT_MENU(ID_FILEMODE_TEXT,			ASFrame::OnToolMenu)
	EVT_MENU(ID_FILEMODE_CPP,			ASFrame::OnToolMenu)
	EVT_MENU(ID_FILEMODE_OBJC,			ASFrame::OnToolMenu)
	EVT_MENU(ID_FILEMODE_JAVA,			ASFrame::OnToolMenu)
	EVT_MENU(ID_FILEMODE_SHARP,			ASFrame::OnToolMenu)
	// lineend menu, a tool submenu
	EVT_MENU(ID_LINEEND_CRLF,			ASFrame::OnToolMenu)
	EVT_MENU(ID_LINEEND_LF,				ASFrame::OnToolMenu)
	EVT_MENU(ID_LINEEND_CR,				ASFrame::OnToolMenu)
	// other tool menu
	EVT_MENU(ID_TOOL_TEST_OPTIONS,		ASFrame::OnToolMenu)
	EVT_MENU(ID_TOOL_ASTYLE_SETTINGS,	ASFrame::OnToolMenu)
	EVT_MENU(ID_TOOL_ASTYLE_OPTIONS,	ASFrame::OnToolMenu)
	// help menu
	EVT_MENU(ID_HELP_ABOUT,				ASFrame::OnHelpAbout)
#ifdef __WXOSX__
	// osx needs for system menu
	EVT_MENU(wxID_ABOUT,				ASFrame::OnHelpAbout)
#endif
	EVT_MENU(ID_HELP_TEXT,				ASFrame::OnHelpText)
	// toolbar events
	EVT_TOOL(ID_TB_FILE_NEW,			ASFrame::OnFileMenu)
	EVT_TOOL(ID_TB_FILE_OPEN,			ASFrame::OnFileMenu)
	EVT_TOOL(ID_TB_FILE_SAVE,			ASFrame::OnFileMenu)
	EVT_TOOL(ID_TB_FILE_CLOSE,			ASFrame::OnFileMenu)
	EVT_TOOL(ID_TB_EDIT_UNDO,			ASFrame::OnEditMenu)
	EVT_TOOL(ID_TB_EDIT_REDO,			ASFrame::OnEditMenu)
	EVT_TOOL(ID_TB_VIEW_WHITESPACE,		ASFrame::OnViewMenu)
	EVT_TOOL(ID_TB_EDIT_SELECTALL,		ASFrame::OnEditMenu)
	EVT_TOOL(ID_TB_EDIT_SELECTTOEND,	ASFrame::OnEditMenu)
	EVT_TOOL(ID_TB_EDIT_SELECTBLOCK,	ASFrame::OnEditMenu)
	EVT_TOOL(ID_TB_TOOL_FORMATSELECT,	ASFrame::OnToolMenu)
	EVT_TOOL(ID_TB_TOOL_FORMATSOURCE,	ASFrame::OnToolMenu)
	// find events
	EVT_FIND(wxID_ANY,					ASFrame::OnFindDialog)
	EVT_FIND_NEXT(wxID_ANY,				ASFrame::OnFindDialog)
	EVT_FIND_CLOSE(wxID_ANY,			ASFrame::OnFindDialog)
	// auinotebook events are in include\wx\aui\auibook.h
	EVT_AUINOTEBOOK_DRAG_DONE(ID_NOTEBOOK,    ASFrame::OnAuiNotebookDragDone)
	EVT_AUINOTEBOOK_PAGE_CHANGED(ID_NOTEBOOK, ASFrame::OnAuiNotebookPageChanged)
	EVT_AUINOTEBOOK_PAGE_CLOSE(ID_NOTEBOOK,   ASFrame::OnAuiNotebookPageClose)
	// other events
	EVT_ACTIVATE(						ASFrame::OnFrameActivate)
	EVT_CLOSE(							ASFrame::OnApplicationClose)
	EVT_IDLE(							ASFrame::OnIdle)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
// ASFrame Class
//-----------------------------------------------------------------------------

ASFrame::ASFrame()
{
	// initialize variables
	m_editor               = nullptr;
	m_notebook             = nullptr;
	m_optionsBitmap        = nullptr;
	m_config               = nullptr;
	m_astyle               = nullptr;
	m_useBottomTabs        = false;
	m_useSmallToolbar      = false;
	m_viewStatusBar        = false;
	m_showToolTips         = false;
	m_showDialogTips       = false;
	// initialize find dialog
	m_find                 = nullptr;
	m_findData.SetFlags(wxFR_DOWN);
	m_wrapSearch           = false;
	m_hideDialogAfterMatch = false;
	// initialize other variables
	for (int i = 0; i < SB_END; i++)
		m_statusWidth[i]   = 0;
	m_astyleDlgPage        = 0;
	m_editorDlgPage        = 0;
	m_argsProcessed        = false;
	m_statusBarNeedsUpdate = false;
	m_checkFileReload      = false;
}

ASFrame::~ASFrame()
{
}

void ASFrame::BuildGuiControls(int argc_, wxChar** argv_)
{
	m_argc = argc_;
	m_argv = argv_;
	// create config file
	// must be first so the configs are available
	// data is written to the registry (Windows) or HOME (Linux)
#ifdef __WXGTK__
	m_config = new Config(wxGetApp().GetAppName().MakeLower());
#else
	m_config = new Config(wxGetApp().GetAppName());
#endif
	assert(m_config != nullptr);

	// create astyle interface object with values from config
	m_astyle = new AStyleIFace();
	assert(m_astyle != nullptr);
	m_config->GetAStyleOptions(m_astyle);
	m_astyleSettings = m_astyle->GetOptions(true, false);
	// get style options from config
	m_styleVector = m_config->GetStcStyleOptions();
	assert(m_styleVector.size() > 0);

	// create main window
	Create(nullptr,
	       wxID_ANY,
	       wxGetApp().GetAppName(),
	       wxDefaultPosition,
	       GetWindowSize(),
	       wxDEFAULT_FRAME_STYLE);
	SetMinSize(wxSize(350, 200));


	// build menubar
	BuildMenuBar();

	// Get the config editor and view menu options.
	// Do after BuildMenu and before BuildToolBar and BuildStatusBar.
	m_config->GetEditorAndViewMenuOptions(this);

	// build toolbar and status bar
	BuildToolBar();
	BuildStatusBar();

	// set icon bundle
	// wxICON macro for Linux (xpm) or Windows (icon)
	wxIcon icon((wxICON(AStyle_16)));
	m_iconBundle.AddIcon(icon);
	icon = wxICON(AStyle_32);
	m_iconBundle.AddIcon(icon);
	SetIcons(m_iconBundle);

	// additional accelerator keys
	// others are defined in BuildMenuBar()
	const int numAccel = 6;		// should not exceed the number of entries
	wxAcceleratorEntry entries[numAccel];
	entries[0].Set(wxACCEL_CTRL,                  WXK_F12,   ID_FILE_SAVE_AS);
	entries[1].Set(wxACCEL_CTRL,                 (int) 'Q',  ID_FILE_EXIT);
	entries[2].Set(wxACCEL_ALT,                   WXK_F4,    ID_FILE_EXIT);
	entries[3].Set(wxACCEL_ALT,                   WXK_BACK,  ID_EDIT_UNDO);
	entries[4].Set(wxACCEL_ALT  | wxACCEL_SHIFT,  WXK_BACK,  ID_EDIT_REDO);
	entries[5].Set(wxACCEL_CTRL | wxACCEL_SHIFT, (int) 'Z',  ID_EDIT_REDO);
	wxAcceleratorTable accel(numAccel, entries);
	SetAcceleratorTable(accel);

	// frame and editor need separate drop targets because of class delete
	ASDropTarget* frameDropTarget = new ASDropTarget;
	this->SetDropTarget(frameDropTarget);

	// __WXQT__ will bypass creating the notebook and stc
	// can remove the option when these are handled by wxWidgets WXQT
#ifndef __WXQT__
	long style = GetNotebookStyle(m_useBottomTabs);
	m_notebook = new wxAuiNotebook(this,
	                               ID_NOTEBOOK,
	                               wxDefaultPosition,
	                               wxDefaultSize,
	                               style);

	// initialize the window
	this->Center();
	this->Show();

	// display first notebook page
	// argc and argv are processed by the OnIdle() event
	wxString firstArgvFile = GetFirstArgvFile();
	FileManager fm;
	fm.BuildNotebookPageNew();
	if (firstArgvFile != wxEmptyString)
		fm.BuildNotebookPageWithFile(firstArgvFile, true);
	m_editor->SetFocus();
#else
	m_notebook = nullptr;
	m_editor = nullptr;
	this->Center();
	this->Show();
	this->SetFocus();
#endif // __WXQT__
}

wxMenu* ASFrame::BuildLineEndMenu()
{
	// the line-end menu is both a menubar menu and a popup menu
	wxMenu* lineEndMenu = new wxMenu();
	lineEndMenu->AppendRadioItem(ID_LINEEND_CRLF, "&Windows (CRLF)");
	lineEndMenu->AppendRadioItem(ID_LINEEND_LF, "&Linux (LF)");
	lineEndMenu->AppendRadioItem(ID_LINEEND_CR, "&Mac OS 9 (CR)");
	return lineEndMenu;
}

void ASFrame::BuildMenuBar()
{
	// create menubar and associate it with the frame
	wxMenuBar* menuBar =  new wxMenuBar();
	// file menu
	wxMenu* fileMenu = new wxMenu();
	fileMenu->Append(ID_FILE_NEW, "&New \tCtrl+N");
	fileMenu->Append(ID_FILE_OPEN, "&Open... \tCtrl+O");
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_FILE_CLOSE, "&Close \tCtrl+W");
	fileMenu->Append(ID_FILE_SAVE, "&Save \tCtrl+S");
	fileMenu->Append(ID_FILE_SAVE_AS, "Save &As... \tCtrl+Shift+S");
	// do this before attaching the "Exit" menu item
#ifdef __WXOSX__
	wxApp::s_macExitMenuItemId = ID_FILE_EXIT;
#else
	fileMenu->AppendSeparator();
#endif
	fileMenu->Append(ID_FILE_EXIT, "E&xit");
	menuBar->Append(fileMenu, "&File");

	// edit menu
	wxMenu* editMenu = new wxMenu();
	editMenu->Append(ID_EDIT_UNDO, "&Undo \tCtrl+Z");
#ifdef __WXOSX__
	editMenu->Append(ID_EDIT_REDO, "&Redo \tCtrl+Shift+Z");
#else
	editMenu->Append(ID_EDIT_REDO, "&Redo \tCtrl+Y");
#endif
	editMenu->AppendSeparator();
	editMenu->Append(ID_EDIT_CUT, "&Cut \tCtrl+X");
	editMenu->Append(ID_EDIT_COPY, "&Copy \tCtrl+C");
	editMenu->Append(ID_EDIT_PASTE, "&Paste \tCtrl+V");
	editMenu->AppendSeparator();
	editMenu->Append(ID_EDIT_SELECTALL, "Select &All \tCtrl+A");
	editMenu->Append(ID_EDIT_SELECTTOSTART, "Select to S&tart");
	editMenu->Append(ID_EDIT_SELECTTOEND, "Select to E&nd");
	editMenu->Append(ID_EDIT_SELECTBLOCK, "Select &Block");
	editMenu->AppendSeparator();
	editMenu->Append(ID_EDIT_INCREASE_INDENT, "&Increase Indent \tTab");
	editMenu->Append(ID_EDIT_DECREASE_INDENT, "&Decrease Indent \tShift+Tab");
	// do this before attaching the "Options" menu item
#ifdef __WXOSX__
	wxApp::s_macPreferencesMenuItemId = ID_EDIT_EDITOR_OPTIONS;
#else
	editMenu->AppendSeparator();
#endif
	editMenu->Append(ID_EDIT_EDITOR_OPTIONS, "&Options...");
	menuBar->Append(editMenu, "&Edit");

	// search menu
	wxMenu* searchMenu = new wxMenu();
	searchMenu->Append(ID_SEARCH_FIND, "&Find... \tCtrl+F");
	searchMenu->Append(ID_SEARCH_FINDNEXT, "Find &Next \tF3");
	searchMenu->Append(ID_SEARCH_FINDPREVIOUS, "Find &Previous \tShift+F3");
	searchMenu->Append(ID_SEARCH_GOTOLINE, "&Go to Line... \tCtrl+G");
	searchMenu->AppendSeparator();
	searchMenu->Append(ID_SEARCH_MARKER1_NEXT, "Next Bookmark \tF2");
	searchMenu->Append(ID_SEARCH_MARKER1_PREV, "Previous Bookmark \tShift+F2");
	searchMenu->Append(ID_SEARCH_MARKER1_TOGGLE, "Toggle Bookmark \tCtrl+F2");
	searchMenu->Append(ID_SEARCH_MARKER1_CLEAR, "Clear All Bookmarks");
	menuBar->Append(searchMenu, "&Search");

	// view menu
	wxMenu* viewMenu = new wxMenu();
	viewMenu->AppendCheckItem(ID_VIEW_LINENUMBERS, "&Line Numbers");
	viewMenu->AppendCheckItem(ID_VIEW_MARGIN, "&Margin");
	viewMenu->AppendCheckItem(ID_VIEW_WHITESPACE, "&Whitespace");
	viewMenu->AppendCheckItem(ID_VIEW_ACTIVELINE, "&Active Line");
	viewMenu->AppendCheckItem(ID_VIEW_INDENTGUIDES, "&Indent Guides");
	viewMenu->AppendCheckItem(ID_VIEW_ENDLINE, "&End of Line");
	viewMenu->AppendCheckItem(ID_VIEW_WORDWRAP, "Word W&rap");
	viewMenu->AppendCheckItem(ID_VIEW_MONOSPACE, "Mo&nospace");
	viewMenu->AppendSeparator();
	viewMenu->AppendCheckItem(ID_VIEW_TOOLBAR, "&Tool Bar");
	viewMenu->AppendCheckItem(ID_VIEW_STATUSBAR, "&Status Bar");
	menuBar->Append(viewMenu, "&View");

	// tools menu
	wxMenu* toolsMenu = new wxMenu();
	// mode submenu
	wxMenu* modeMenu = BuildModeMenu();
	toolsMenu->AppendSubMenu(modeMenu, "File &Mode");
	// line end submenu
	wxMenu* lineEndMenu = BuildLineEndMenu();
	toolsMenu->AppendSubMenu(lineEndMenu, "&Line Ends");
	toolsMenu->AppendSeparator();
	// format options
	toolsMenu->Append(ID_TOOL_FORMATSELECT, "Format S&election");
	toolsMenu->Append(ID_TOOL_FORMATSOURCE, "Format S&ource");
	toolsMenu->Append(ID_TOOL_TABSTOSPACES, "&Tabs to Spaces \tCtrl+T");
	toolsMenu->Append(ID_TOOL_TEXTTOSTRINGS, "Text to Strings \tCtrl+R");
	toolsMenu->Append(ID_TOOL_STRIPSPACES, "Stri&p Trailing Spaces \tCtrl+P");
	toolsMenu->AppendSeparator();
	// settings and options menu
	toolsMenu->Append(ID_TOOL_ASTYLE_SETTINGS, "AStyle &Settings...");
#ifdef TESTMODE1
	toolsMenu->Append(ID_TOOL_TEST_OPTIONS, "Test O&ptions...");
#endif
	toolsMenu->Append(ID_TOOL_ASTYLE_OPTIONS, "&AStyle Options...");
	menuBar->Append(toolsMenu, "&Tools");

	// do this before attaching the "Help" menu
#ifdef __WXOSX__
	wxApp::s_macHelpMenuTitleName = "&Help";
	wxApp::s_macAboutMenuItemId = ID_HELP_ABOUT;
#endif // __WXOSX__

	// help menu
	wxMenu* helpMenu = new wxMenu();
	helpMenu->Append(ID_HELP_TEXT, "&Help \tF1",
	                 " " + wxGetApp().GetAppName() + " Help");
	helpMenu->Append(ID_HELP_ABOUT, "&About... ",
	                 " About " + wxGetApp().GetAppName());
	// append this last to remove the "about" on OSX
	menuBar->Append(helpMenu, "&Help");

	// NOTE: disable until help doc is ready
	menuBar->Enable(ID_HELP_TEXT, false);

	// do this last for OSX
	SetMenuBar(menuBar);
}

wxMenu* ASFrame::BuildModeMenu()
{
	// the mode menu is both a menubar menu and a popup menu
	wxMenu* modeMenu = new wxMenu();
	modeMenu->AppendRadioItem(ID_FILEMODE_TEXT, "&Text");
	modeMenu->AppendRadioItem(ID_FILEMODE_CPP, "C/C&++");
	modeMenu->AppendRadioItem(ID_FILEMODE_OBJC, "&Obj-C");
	modeMenu->AppendRadioItem(ID_FILEMODE_JAVA, "&Java");
	modeMenu->AppendRadioItem(ID_FILEMODE_SHARP, "C&#");
	return modeMenu;
}

void ASFrame::BuildStatusBar()
{
	wxStatusBar* statusBar = GetStatusBar();
	if (!IsMenuItemChecked(ID_VIEW_STATUSBAR))
	{
		if (m_optionsBitmap)
		{
			delete m_optionsBitmap;
			m_optionsBitmap = nullptr;
		}
		if (statusBar)
		{
			delete statusBar;
			SetStatusBar(nullptr);
		}
		return;
	}

	// create statusbar and associate it with the frame
	statusBar = CreateStatusBar(SB_END, wxSTB_DEFAULT_STYLE, ID_STATUSBAR);
	// create a settings bitmap button
	m_optionsBitmap = new wxStaticBitmap(statusBar, ID_SB_ASTYLE_BITMAP, CreateStatusBarOptionsBitmap(),
	                                     wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT | wxBORDER_NONE);
	// the reason for wxHAS_EVENT_BIND is described in AStyleDlg.cpp
#ifdef wxHAS_EVENT_BIND
	// bind status bar to the context menu handler function
	statusBar->Bind(wxEVT_LEFT_UP, &ASFrame::OnStatusBarClick, this);
	// bind options bitmap to the handler function
	m_optionsBitmap->Bind(wxEVT_LEFT_UP, &ASFrame::OnOptionsBitmapClick, this);
#endif
	// set field sizes
	int h;
	statusBar->GetTextExtent("xxxxxxxxxxxxxxxxxxxx ", &m_statusWidth[SB_SETTINGS], &h);
	wxSize optionsBmpSize = m_optionsBitmap->GetSize();
	m_statusWidth[SB_BUTTON] = optionsBmpSize.GetWidth();
	statusBar->GetTextExtent("xC/C++x ", &m_statusWidth[SB_FILEMODE], &h);
	statusBar->GetTextExtent("xCRLFx ", &m_statusWidth[SB_EOL], &h);
	statusBar->GetTextExtent("xWINDOWS-1252xx ", &m_statusWidth[SB_ENCODING], &h);
	statusBar->GetTextExtent("xLines: 1234x ", &m_statusWidth[SB_LINES], &h);
	statusBar->GetTextExtent("xLine: 1234, Col: 123x/123x ", &m_statusWidth[SB_CARET], &h);
	statusBar->GetTextExtent("xOverwritex ",  &m_statusWidth[SB_INSERT], &h);

	statusBar->SetFieldsCount(SB_END);
	statusBar->SetStatusWidths(SB_END, m_statusWidth);

	// reset bitmap width after the statusbar widths are set
	wxRect statusRect = statusBar->GetRect();
	m_statusWidth[SB_BUTTON] = statusRect.GetHeight();	// set width = height
#ifndef __WXMSW__
	m_statusWidth[SB_BUTTON] += 4;
#endif
	statusBar->SetStatusWidths(SB_END, m_statusWidth);

	// display status bar
	SetStatusBarPane(-1);		//  disable menu help display
	StatusBarAdjustWidths();
	UpdateStatusBarDisplay();
}

void ASFrame::BuildToolBar()
{
	// delete the toolbar
	wxToolBar* toolBar = GetToolBar();
	if (toolBar != nullptr)
	{
		delete toolBar;
		SetToolBar(nullptr);
	}
	if (!IsMenuItemChecked(ID_VIEW_TOOLBAR))
		return;
	// create toolbar and associate it with the frame
	toolBar = CreateToolBar(wxTB_DEFAULT_STYLE, ID_TOOLBAR);

	// Set up toolbar
	enum
	{
		tool_new,
		tool_open,
		tool_save,
		tool_close,
		tool_undo,
		tool_redo,
		tool_white,
		tool_all,
		tool_toend,
		tool_block,
		tool_select,
		tool_source,
		tool_Max
	};

	// wxBITMAP macro for Linux (xpm) or Windows (bmp)
	wxBitmap toolBarBitmaps[tool_Max];
	if (GetUseSmallToolbar())
	{
		toolBarBitmaps[tool_new] = wxBITMAP(New_16);
		toolBarBitmaps[tool_open] = wxBITMAP(Open_16);
		toolBarBitmaps[tool_save] = wxBITMAP(Save_16);
		toolBarBitmaps[tool_close] = wxBITMAP(Close_16);
		toolBarBitmaps[tool_undo] = wxBITMAP(Undo_16);
		toolBarBitmaps[tool_redo] = wxBITMAP(Redo_16);
		toolBarBitmaps[tool_white] = wxBITMAP(White_16);
		toolBarBitmaps[tool_all] = wxBITMAP(All_16);
		toolBarBitmaps[tool_toend] = wxBITMAP(ToEnd_16);
		toolBarBitmaps[tool_block] = wxBITMAP(Block_16);
		toolBarBitmaps[tool_select] = wxBITMAP(Select_16);
		toolBarBitmaps[tool_source] = wxBITMAP(Source_16);
	}
	else
	{
		toolBarBitmaps[tool_new] = wxBITMAP(New_24);
		toolBarBitmaps[tool_open] = wxBITMAP(Open_24);
		toolBarBitmaps[tool_save] = wxBITMAP(Save_24);
		toolBarBitmaps[tool_close] = wxBITMAP(Close_24);
		toolBarBitmaps[tool_undo] = wxBITMAP(Undo_24);
		toolBarBitmaps[tool_redo] = wxBITMAP(Redo_24);
		toolBarBitmaps[tool_white] = wxBITMAP(White_24);
		toolBarBitmaps[tool_all] = wxBITMAP(All_24);
		toolBarBitmaps[tool_toend] = wxBITMAP(ToEnd_24);
		toolBarBitmaps[tool_block] = wxBITMAP(Block_24);
		toolBarBitmaps[tool_select] = wxBITMAP(Select_24);
		toolBarBitmaps[tool_source] = wxBITMAP(Source_24);
	}

	// set size
	int w = toolBarBitmaps[tool_open].GetWidth();
	int h = toolBarBitmaps[tool_open].GetHeight();
	toolBar->SetToolBitmapSize(wxSize(w, h));

	// build toolbar

	toolBar->AddSeparator();

	toolBar->AddTool(ID_TB_FILE_NEW,
	                 wxEmptyString,
	                 toolBarBitmaps[tool_new]);

	toolBar->AddTool(ID_TB_FILE_OPEN,
	                 wxEmptyString,
	                 toolBarBitmaps[tool_open]);

	toolBar->AddTool(ID_TB_FILE_SAVE,
	                 wxEmptyString,
	                 toolBarBitmaps[tool_save]);

	toolBar->AddTool(ID_TB_FILE_CLOSE,
	                 wxEmptyString,
	                 toolBarBitmaps[tool_close]);

	toolBar->AddSeparator();

	toolBar->AddTool(ID_TB_EDIT_UNDO,
	                 wxEmptyString,
	                 toolBarBitmaps[tool_undo]);

	toolBar->AddTool(ID_TB_EDIT_REDO,
	                 wxEmptyString,
	                 toolBarBitmaps[tool_redo]);

	toolBar->AddSeparator();

	toolBar->AddCheckTool(ID_TB_VIEW_WHITESPACE,
	                      wxEmptyString,
	                      toolBarBitmaps[tool_white]);

	toolBar->AddTool(ID_TB_EDIT_SELECTALL,
	                 wxEmptyString,
	                 toolBarBitmaps[tool_all]);

	toolBar->AddTool(ID_TB_EDIT_SELECTTOEND,
	                 wxEmptyString,
	                 toolBarBitmaps[tool_toend]);

	toolBar->AddTool(ID_TB_EDIT_SELECTBLOCK,
	                 wxEmptyString,
	                 toolBarBitmaps[tool_block]);

	toolBar->AddSeparator();

	toolBar->AddTool(ID_TB_TOOL_FORMATSELECT,
	                 wxEmptyString,
	                 toolBarBitmaps[tool_select]);

	toolBar->AddTool(ID_TB_TOOL_FORMATSOURCE,
	                 wxEmptyString,
	                 toolBarBitmaps[tool_source]);

	BuildToolTips(m_showToolTips);
	toolBar->SetToolSeparation(200);
	toolBar->Realize();
	UpdateToolBarDisplay();
}

void ASFrame::BuildToolTips(bool showToolTips)
{
	wxToolBar* toolBar = GetToolBar();
	if (toolBar == nullptr)
		return;
	m_showToolTips = showToolTips;
	if (showToolTips)
	{
		toolBar->SetToolShortHelp(ID_TB_FILE_NEW, "New File");
		toolBar->SetToolShortHelp(ID_TB_FILE_OPEN, "Open File");
		toolBar->SetToolShortHelp(ID_TB_FILE_SAVE, "Save File");
		toolBar->SetToolShortHelp(ID_TB_FILE_CLOSE, "Close File");
		toolBar->SetToolShortHelp(ID_TB_EDIT_UNDO, "Undo");
		toolBar->SetToolShortHelp(ID_TB_EDIT_REDO, "Redo");
		toolBar->SetToolShortHelp(ID_TB_VIEW_WHITESPACE, "View Whitespace");
		toolBar->SetToolShortHelp(ID_TB_EDIT_SELECTALL, "Select All");
		toolBar->SetToolShortHelp(ID_TB_EDIT_SELECTTOEND, "Select to End");
		toolBar->SetToolShortHelp(ID_TB_EDIT_SELECTBLOCK, "Select Block");
		toolBar->SetToolShortHelp(ID_TB_TOOL_FORMATSELECT, "Format Selection");
		toolBar->SetToolShortHelp(ID_TB_TOOL_FORMATSOURCE, "Format Source");
	}
	else
	{
		toolBar->SetToolShortHelp(ID_TB_FILE_OPEN, wxEmptyString);
		toolBar->SetToolShortHelp(ID_TB_FILE_SAVE, wxEmptyString);
		toolBar->SetToolShortHelp(ID_TB_FILE_CLOSE, wxEmptyString);
		toolBar->SetToolShortHelp(ID_TB_EDIT_UNDO, wxEmptyString);
		toolBar->SetToolShortHelp(ID_TB_EDIT_REDO, wxEmptyString);
		toolBar->SetToolShortHelp(ID_TB_VIEW_WHITESPACE, wxEmptyString);
		toolBar->SetToolShortHelp(ID_TB_EDIT_SELECTALL, wxEmptyString);
		toolBar->SetToolShortHelp(ID_TB_EDIT_SELECTTOEND, wxEmptyString);
		toolBar->SetToolShortHelp(ID_TB_EDIT_SELECTBLOCK, wxEmptyString);
		toolBar->SetToolShortHelp(ID_TB_TOOL_FORMATSELECT, wxEmptyString);
		toolBar->SetToolShortHelp(ID_TB_TOOL_FORMATSOURCE, wxEmptyString);
	}
}

void ASFrame::CloseFindDialog()
{
	m_find->Destroy();
	m_find = nullptr;
}

void ASFrame::CloseNotebook()
{
	// the notebook has zero pages
	assert(m_notebook->GetPageCount() == 0);
	m_notebook->Hide();
	m_editor = nullptr;
	UpdateFrame();
}

wxBitmap ASFrame::CreateStatusBarOptionsBitmap(bool on /*false*/)
{
	const int BMP_RADIUS = 5;
	const wxColour MAGENTA(255, 0, 255);
	wxBitmap bitmap((BMP_RADIUS * 2) + 4, (BMP_RADIUS * 2) + 4);
	wxMemoryDC dc;
	dc.SelectObject(bitmap);
	dc.SetBrush(on ? wxColour(180, 0, 0) : wxColour(0, 180, 180));
	dc.SetBackground(MAGENTA);
	dc.Clear();
	dc.DrawCircle(BMP_RADIUS + 2, BMP_RADIUS + 2, BMP_RADIUS);
	// reset the device control
	dc.SelectObject(wxNullBitmap);
	// set background to transparent
	wxBitmap mask = bitmap;
	bitmap.SetMask(new wxMask(mask, MAGENTA));

	return bitmap;
}

void ASFrame::FileDoCaption()
{
	wxString caption;
	if (m_editor && m_editor->GetFileName() != wxEmptyString)
	{
		caption = m_editor->GetFileName() + " - ";
		caption.Append(wxGetApp().GetAppName());
	}
	else
		caption = wxGetApp().GetAppName();
	this->SetTitle(caption);
}

wxFont ASFrame::FindCommentFont() const
{
	// try to get these fonts
	wxFont commentFont;
#ifdef __WXMSW__
	if (commentFont.SetFaceName("Verdana"))
		commentFont.SetPointSize(10);
	else if (commentFont.SetFaceName("Arial"))
		commentFont.SetPointSize(10);
#elif __WXOSX__
	if (commentFont.SetFaceName("Verdana"))
		commentFont.SetPointSize(14);
	else if (commentFont.SetFaceName("Arial"))
		commentFont.SetPointSize(15);
#else
	if (commentFont.SetFaceName("DejaVu Sans"))
		commentFont.SetPointSize(11);
	else if (commentFont.SetFaceName("Bitstream Vera Sans"))
		commentFont.SetPointSize(11);
	else if (commentFont.SetFaceName("Verdana"))
		commentFont.SetPointSize(10);
#endif  // __WXMSW__
	// default wxFONTFAMILY_SWISS is a (proportional) sans-serif font
	// usually Arial on Windows, Sans on Linux
	if (!commentFont.IsOk())
	{
		commentFont = wxFont(10,
		                     wxFONTFAMILY_SWISS,
		                     wxFONTSTYLE_NORMAL,
		                     wxFONTWEIGHT_NORMAL);
	}
	return commentFont;
}

wxFont ASFrame::FindDefaultFont() const
{
	// try to get these fonts
	wxFont defaultFont;
#ifdef __WXMSW__
	if (defaultFont.SetFaceName("Consolas"))
		defaultFont.SetPointSize(11);
	else if (defaultFont.SetFaceName("Lucida Sans Typewriter"))
		defaultFont.SetPointSize(10);
#elif __WXOSX__
	if (defaultFont.SetFaceName("Monaco"))
		defaultFont.SetPointSize(13);
	else if (defaultFont.SetFaceName("Menlo"))
		defaultFont.SetPointSize(14);
#else
	if (defaultFont.SetFaceName("DejaVu Sans Mono"))
		defaultFont.SetPointSize(11);
	else if (defaultFont.SetFaceName("Bitstream Vera Sans Mono"))
		defaultFont.SetPointSize(11);
	else if (defaultFont.SetFaceName("Monospace"))
		defaultFont.SetPointSize(10);
#endif  // __WXMSW__
	// default wxFONTFAMILY_MODERN is a fixed pitch font
	// usually Courier New on Windows, Monospace on Linux
	if (!defaultFont.IsOk())
	{
		defaultFont = wxFont(11,
		                     wxFONTFAMILY_MODERN,
		                     wxFONTSTYLE_NORMAL,
		                     wxFONTWEIGHT_NORMAL);
	}
	return defaultFont;
}

int ASFrame::GetFileFilterIndex() const
{
	return FileManager::GetFileFilterIndex();
}

wxString ASFrame::GetFirstArgvFile()
{
	// error message will be displayed by OnIdle()
	wxLogNull noLog;
	// argv[0] is the program name
	for (int i = 1; i < m_argc; i++)
	{
		// skip non-file options
		wxString currentArg = m_argv[i];
		if (currentArg[0] == '-')
			continue;
		// skip if not a valid file
		// error message will be displayed by OnIdle()
		wxFileName filepath = currentArg;
		wxFile file(filepath.GetFullPath(), wxFile::read_write);
		if (file.Exists(filepath.GetFullPath()))
			return currentArg;
	}
	return wxEmptyString;
}

wxString ASFrame::GetKeyWords(int fileMode) const
{
	wxString keyWords;
	switch (fileMode)
	{
		case FILEMODE_CPP:
		case FILEMODE_OBJC:
			keyWords = "and and_eq asm auto bitand bitor bool \
			break case catch char class compl \
			const const_cast continue default delete do double dynamic_cast else enum \
			explicit export extern false float for friend goto if inline int long \
			mutable namespace new not not_eq operator or or_eq private protected \
			public register reinterpret_cast return short signed sizeof static \
			static_cast struct switch template this throw true try typedef typeid \
			typename union unsigned using virtual void volatile wchar_t while xor xor_eq \
			@class @end @implementation @interface @property";		// Objective_C keywords
			break;

		case FILEMODE_JAVA:
			keyWords = "abstract assert boolean break byte case \
			catch char class \
			const continue default do double else extends final finally float for future \
			generic goto if implements import inner instanceof int interface long \
			native new null outer package private protected public rest \
			return short static super switch synchronized this throw throws \
			transient try var void volatile while";
			break;

		case FILEMODE_SHARP:
			keyWords = "abstract as base bool break byte \
			case catch char checked class \
			const continue decimal default delegate do double else enum \
			event explicit extern false finally fixed float for foreach goto if \
			implicit in int interface internal is lock long namespace new null \
			object operator out override params private protected public \
			readonly ref return sbyte sealed short sizeof stackalloc static \
			string struct switch this throw true try typeof uint ulong \
			unchecked unsafe ushort using virtual void while";
			break;

		default:
			ShowMessageDialog(wxString::Format(
			                      "Cannot identify file type for keywords \"%d\".", fileMode),
			                  wxOK | wxICON_ERROR);
			keyWords = wxEmptyString;
			break;
	}

	return keyWords;
}

long ASFrame::GetNotebookStyle(bool useBottomTabs) const
{
	// As of wxWidgets version 3.1.0 cannot use wxAUI_NB_TAB_MOVE
	// and wxAUI_NB_TAB_SPLIT at the same time.
	long style = wxAUI_NB_TAB_MOVE |
	             //wxAUI_NB_TAB_SPLIT |
	             wxAUI_NB_SCROLL_BUTTONS |
	             wxAUI_NB_WINDOWLIST_BUTTON |
	             wxAUI_NB_CLOSE_ON_ACTIVE_TAB |
	             wxAUI_NB_MIDDLE_CLICK_CLOSE |
	             wxCLIP_CHILDREN;

	if (useBottomTabs)
		style |= wxAUI_NB_BOTTOM;
	else
		style |= wxAUI_NB_TOP;
	return style;
}

wxSize ASFrame::GetWindowSize() const
{
	int sx = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
	int sy = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);
	int width = sx * 5 / 8;
	int height = sy * 11 / 16;
	return wxSize(width, height);
}

void ASFrame::OnApplicationClose(wxCloseEvent&)
{
	FileManager fm;
	while (m_notebook->GetPageCount() > 0)
	{
		if (fm.CloseFile() == wxID_CANCEL)
			return;
	}
	CloseNotebook();
	m_config->SaveEditorOptions(this);
	m_config->SaveStcStyleOptions(m_styleVector);
	delete (m_astyle);
	delete (m_config);	// config object is NOT part of the frame
	Destroy();
}

void ASFrame::OnAStyleOptions(wxCommandEvent&)
{
	Config* config = GetConfig();
	AStyleIFace* astyle = GetAStyle();
	AStyleDlg dialog(this, astyle, m_astyleDlgPage);
	dialog.SetTitle(" Artistic Style Options");
	dialog.SetIcons(GetIconBundle());
	dialog.Centre();

	if (dialog.ShowModal() == wxID_OK)
	{
		m_astyleDlgPage = dialog.GetPage();
		config->SaveAStyleOptions(astyle);
		if (m_editor)
			m_editor->UpdateEditorFromAStyleOptions(m_astyle);
		wxString astyleSettings = astyle->GetOptions(true, false);
		SetAstyleSettings(astyleSettings);
		StatusBarAdjustWidths();
		UpdateStatusBarDisplay();
	}
}

void ASFrame::OnAStyleSettings(wxCommandEvent&)
{
	AStyleIFace* astyle = GetAStyle();
	SettingsDlg dialog(this, this, astyle);
	dialog.SetTitle(" Settings");
	dialog.SetIcons(GetIconBundle());
	dialog.Centre();
	dialog.ShowModal();
}

void ASFrame::OnAuiNotebookDragDone(wxAuiNotebookEvent& event)
// This is needed because of a bug in wxWidgets 3.1.0 and less.
{
	// change selection from the old position to the new drop position
	m_notebook->SetSelection(event.GetSelection());
}

void ASFrame::OnAuiNotebookPageChanged(wxAuiNotebookEvent& event)
// AuiNotebook events are in include\wx\aui\auibook.h
// Called when a page is added or selected.
// Called for the new selection when a page is deleted.
// Will NOT be called after the last page is deleted.
// The new page has not yet been displayed.
{
	if (m_notebook->GetPageCount() == 1 && !m_notebook->IsShown())
		m_notebook->Show();
	int sel = event.GetSelection();
	m_editor = reinterpret_cast<ASEditor*>(m_notebook->GetPage(sel));
	m_editor->UpdateStcStyleOptions();
	m_editor->UpdateEditorFromViewMenuOptions();
	m_editor->UpdateEditorFromAStyleOptions(m_astyle);
	UpdateFrame();
	// file reload is checked in idle time so the new page will be displayed
	m_checkFileReload = true;
}

void ASFrame::OnAuiNotebookPageClose(wxAuiNotebookEvent& event)
// AuiNotebook events are in include\wx\aui\auibook.h
// Called when a page is deleted.
{
	event.Veto();
	FileManager fm;
	fm.CloseFile();
	// EVT_AUINOTEBOOK_PAGE_CHANGED is not called if no pages
	if (m_notebook->GetPageCount() == 0)
		CloseNotebook();
}

bool ASFrame::OnDropFiles(const wxArrayString& filePaths)
// This is NOT event activated. It is called by the ASDropTarget class.
{
	const int MAX_DROP = 9;
	int numFiles = filePaths.GetCount();
	if (numFiles > MAX_DROP)
	{
		ShowMessageDialog(wxString::Format("Cannot drop more than %d files.", MAX_DROP), wxOK | wxICON_ERROR);
		return false;
	}
	SetCursor(*wxHOURGLASS_CURSOR);
	FileManager fm;
	for (int i = 0; i < numFiles; i++)
		fm.BuildNotebookPageWithFile(filePaths[i], true);
	SetCursor(wxNullCursor);
	return true;
}

void ASFrame::OnEditMenu(wxCommandEvent& event)
{
	switch (event.GetId())
	{
		case ID_EDIT_UNDO:
		case ID_TB_EDIT_UNDO:
		{
			wxStatusBar* statusBar = GetStatusBar();
			if (statusBar)
				statusBar->Freeze();
			m_editor->wxStyledTextCtrl::Undo();
#if wxCHECK_VERSION(2, 9, 0)
			// fix a bug in version 3.0.0 of STC
			// can possibly be removed in the future
			m_editor->wxStyledTextCtrl::Refresh();
#endif
			UpdateToolBarDisplay();
			if (statusBar)
				statusBar->Thaw();
		}
		break;

		case ID_EDIT_REDO:
		case ID_TB_EDIT_REDO:
		{
			wxStatusBar* statusBar = GetStatusBar();
			if (statusBar)
				statusBar->Freeze();
			m_editor->wxStyledTextCtrl::Redo();
#if wxCHECK_VERSION(2, 9, 0)
			// fix a bug in version 3.0.0 of STC
			// can possibly be removed in the future
			m_editor->wxStyledTextCtrl::Refresh();
#endif
			UpdateToolBarDisplay();
			if (statusBar)
				statusBar->Thaw();
		}
		break;

		case ID_EDIT_CUT:
			m_editor->wxStyledTextCtrl::Cut();
			UpdateToolBarDisplay();
			break;

		case ID_EDIT_COPY:
			m_editor->wxStyledTextCtrl::Copy();
			break;

		case ID_EDIT_PASTE:
			m_editor->wxStyledTextCtrl::Paste();
			UpdateToolBarDisplay();
			break;

		case ID_EDIT_SELECTALL:
		case ID_TB_EDIT_SELECTALL:
			m_editor->wxStyledTextCtrl::SelectAll();
			break;

		case ID_EDIT_SELECTTOSTART:
			m_editor->SelectToStart();
			break;

		case ID_EDIT_SELECTTOEND:
		case ID_TB_EDIT_SELECTTOEND:
			m_editor->SelectToEnd();
			break;

		case ID_EDIT_SELECTBLOCK:
		case ID_TB_EDIT_SELECTBLOCK:
			m_editor->SelectBlock();
			break;

		case ID_EDIT_INCREASE_INDENT:
			m_editor->wxStyledTextCtrl::CmdKeyExecute(wxSTC_CMD_TAB);
#if wxCHECK_VERSION(2, 9, 0)
			// fix a bug in version 3.0.0 of STC
			// can possibly be removed in the future
			m_editor->wxStyledTextCtrl::Refresh();
#endif
			break;

		case ID_EDIT_DECREASE_INDENT:
			m_editor->wxStyledTextCtrl::CmdKeyExecute(wxSTC_CMD_BACKTAB);
#if wxCHECK_VERSION(2, 9, 0)
			// fix a bug in version 3.0.0 of STC
			// can possibly be removed in the future
			m_editor->wxStyledTextCtrl::Refresh();
#endif
			break;

		case ID_EDIT_EDITOR_OPTIONS:
		case wxID_PREFERENCES:
			OnEditorOptions(event);
			break;

		default:
			ShowMessageDialog("Unrecognized edit menu event "
			                  + wxString::Format("%d", event.GetId()),
			                  wxOK | wxICON_ERROR);
			break;
	}
}

void ASFrame::OnEditorOptions(wxCommandEvent&)
{
	EditorDlg dialog(this, m_editorDlgPage);
	dialog.SetTitle(" Editor Options");
	dialog.SetIcons(GetIconBundle());
	dialog.Centre();

	if (dialog.ShowModal() == wxID_OK)
	{
		m_editorDlgPage = dialog.GetPage();
		// useBottomTabs
		bool useBottomTabsPrev = GetUseBottomTabs();
		bool useBottomTabs = dialog.GetUseBottomTabs();
		SetUseBottomTabs(useBottomTabs);
		if (useBottomTabs != useBottomTabsPrev)
		{
			long style = GetNotebookStyle(useBottomTabs);
			m_notebook->SetWindowStyleFlag(style);
		}
		// useSmallToolbar
		bool useSmallToolbarPrev = GetUseSmallToolbar();
		bool useSmallToolbar = dialog.GetUseSmallToolbar();
		SetUseSmallToolBar(useSmallToolbar);
		if (useSmallToolbar != useSmallToolbarPrev)
			BuildToolBar();
		// redraw the frame
		this->Refresh();
		// showToolTips
		bool showToolTips = dialog.GetShowToolbarTooltips();
		BuildToolTips(showToolTips);
		// showDialogTips
		bool showDialogTips = dialog.GetShowDialogTooltips();
		SetDialogTips(showDialogTips);
		// other options
		m_wrapSearch = dialog.GetWrapSearch();
		m_hideDialogAfterMatch = dialog.GetHideFind();
		m_defaultFont = dialog.GetDefaultFont();
		m_commentFont = dialog.GetCommentFont();
		// update config file
		m_styleVector = dialog.GetNewStyleVector();
		if (m_editor)
			m_editor->UpdateStcStyleOptions();
		GetConfig()->SaveEditorOptions(this);
		GetConfig()->SaveStcStyleOptions(m_styleVector);
	}
}

void ASFrame::OnFileMenu(wxCommandEvent& event)
{
	FileManager fm;
	switch (event.GetId())
	{
		case ID_FILE_NEW:
		case ID_TB_FILE_NEW:
			fm.BuildNotebookPageNew();
			break;

		case ID_FILE_OPEN:
		case ID_TB_FILE_OPEN:
			fm.OpenFile();
			break;

		case ID_FILE_CLOSE:
		case ID_TB_FILE_CLOSE:
			fm.CloseFile();
			// EVT_AUINOTEBOOK_PAGE_CHANGED is not called if no pages
			if (m_notebook->GetPageCount() == 0)
				CloseNotebook();
			break;

		case ID_FILE_SAVE:
		case ID_TB_FILE_SAVE:
			fm.SaveFile();
			break;

		case ID_FILE_SAVE_AS:
			fm.SaveFileAs();
			break;

		case ID_FILE_EXIT:
		case wxID_EXIT:
			Close(false);	// generate a wxCloseEvent
			break;

		default:
			ShowMessageDialog("Unrecognized file menu event "
			                  + wxString::Format("%d", event.GetId()),
			                  wxOK | wxICON_ERROR);
			break;
	}
}

void ASFrame::OnFindDialog(wxFindDialogEvent& event)
{
	wxEventType type = event.GetEventType();

	if (type == wxEVT_COMMAND_FIND || type == wxEVT_COMMAND_FIND_NEXT)
	{
		bool reverseFind = (m_findData.GetFlags() & wxFR_DOWN) == 0;
		m_editor->FindNext(m_findData, reverseFind);
		if (m_hideDialogAfterMatch && m_find != nullptr)
			CloseFindDialog();
	}
	else if (type == wxEVT_COMMAND_FIND_CLOSE)
	{
		CloseFindDialog();
	}
	else
	{
		ShowMessageDialog("Unknown find dialog event!",
		                  wxOK | wxICON_ERROR);
	}
}

void ASFrame::OnFrameActivate(wxActivateEvent& event)
{
	// call event.Skip() as not doing so can result in strange effects
	if (event.GetActive() && m_editor)
	{
		if (this->IsIconized())
		{
			this->Iconize(false);
			wxMilliSleep(400);	// let the new page display
		}
		m_checkFileReload = true;
	}
	event.Skip();
}

void ASFrame::OnHelpAbout(wxCommandEvent&)
{
	wxString astyleVersion = m_editor->GetAStyleVersion();
	AboutDlg dialog(this);
	dialog.SetAboutDlgValues(astyleVersion, &m_iconBundle);
	dialog.SetTitle(" About " + wxGetApp().GetAppName());
	dialog.SetIcons(m_iconBundle);
	dialog.Centre();
	dialog.ShowModal();
}

void ASFrame::OnHelpText(wxCommandEvent&)
// Load the documentation HTML file.
{
	const wxStandardPathsBase& sp = wxStandardPaths::Get();
	wxString exePath = sp.GetExecutablePath();
	wxString docPath;
#ifdef __WXMSW__
	// should be in the doc directory of the executable path
	wxString docSubPath = "\\doc\\FrameL.html";
	wxString buildDir = "\\build\\";
	docPath = exePath.Mid(0, exePath.Find('\\', true));
	if (docPath != exePath)
		docPath = docPath +  docSubPath;
	else
		docPath = wxEmptyString;
#else
	wxString docSubPath = "/doc/FrameL.html";
	wxString buildDir = "/build/";
	docPath = "/usr/share/astyle/FrameL.html";
#endif
	wxFileName fn = docPath;
	if (!fn.FileExists())
	{
		// check for the build directory (testing from the IDE)
		wxString docAltPath = exePath.Mid(0, exePath.Find(buildDir));
		if (docAltPath != exePath)
			docAltPath = docAltPath + docSubPath;
		else
			docAltPath = wxEmptyString;
		fn = docAltPath;
		// cannot find the file, display the default location
		if (!fn.FileExists())
		{
			ShowMessageDialog("Cannot find documentation file:\n" + docPath, wxOK | wxICON_ERROR);
			return;
		}
	}

	// open the file in the default browser
	wxLogNull noLog;
	wxString docUrl = "file:///" + fn.GetFullPath();
	if (!wxLaunchDefaultBrowser(docUrl))
	{
		ShowMessageDialog("Unable to launch default browser.\nApplication not found!",
		                  wxOK | wxICON_ERROR);
		return;
	}
}

void ASFrame::OnIdle(wxIdleEvent&)
{
	if (m_statusBarNeedsUpdate)
	{
		// do this first on Linux!
		SetStatusBarNeedsUpdate(false);
		UpdateStatusBarDisplay();
	}
	// check for reload after a notebook page change
	if (m_checkFileReload)
	{
		// do this first on Linux!
		m_checkFileReload = false;
		FileManager fm;
		fm.CheckFileReload();
	}
	// __WXQT__ will bypass creating the notebook and stc
	// can remove the option when these are handled by wxWidgets WXQT
#ifndef __WXQT__
	// argc and argc are processed here one time only
	// wxApp::OnInit must end for the toolbar to be displayed
	// loading here provides a better appearance
	if (!m_argsProcessed)
	{
		// do this first on Linux!
		m_argsProcessed = true;
		// open the files - argv[0] is the program name
		FileManager fm;
		for (int i = 1; i < m_argc; i++)
		{
			if (m_argv[i][0] == '-')
			{
				if (m_argv[i] == wxString("--ldtp_test"))
					SetLdtpTestSize();
				continue;
			}
			fm.BuildNotebookPageWithFile(m_argv[i], false);
		}
		m_notebook->SetSelection(0);
		m_editor->SetFocus();
		m_argc = 0;
		m_argv = nullptr;
	}
#endif // __WXQT__
}

void ASFrame::OnMenuOpen(wxMenuEvent&)
{
	wxMenuBar* menuBar = this->GetMenuBar();
	// EDIT MENU
	// update undo and redo in the menu
	if (m_editor)
	{
		menuBar->Enable(ID_EDIT_UNDO, m_editor->wxStyledTextCtrl::CanUndo());
		menuBar->Enable(ID_EDIT_REDO, m_editor->wxStyledTextCtrl::CanRedo());
		// check for selection
		int selection = m_editor->wxStyledTextCtrl::GetSelectionStart() - m_editor->wxStyledTextCtrl::GetSelectionEnd();
		bool haveSelection = selection == 0 ? false : true;
		menuBar->Enable(ID_EDIT_CUT, haveSelection);
		menuBar->Enable(ID_EDIT_COPY, haveSelection);
		// check for paste
		bool canPaste = m_editor->wxStyledTextCtrl::CanPaste() ? true : false;
		menuBar->Enable(ID_EDIT_PASTE, canPaste);
	}
	else
	{
		menuBar->Enable(ID_EDIT_UNDO, false);
		menuBar->Enable(ID_EDIT_REDO, false);
		menuBar->Enable(ID_EDIT_CUT, false);
		menuBar->Enable(ID_EDIT_COPY, false);
		menuBar->Enable(ID_EDIT_PASTE, false);
	}
	// SEARCH MENU
	if (m_findData.GetFindString() != wxEmptyString)
	{
		menuBar->Enable(ID_SEARCH_FINDNEXT, true);
		menuBar->Enable(ID_SEARCH_FINDPREVIOUS, true);
	}
	else
	{
		menuBar->Enable(ID_SEARCH_FINDNEXT, false);
		menuBar->Enable(ID_SEARCH_FINDPREVIOUS, false);
	}
	// TOOLS MENU
	wxMenu* modeMenu = nullptr;
	menuBar->FindItem(ID_FILEMODE_CPP, &modeMenu);
	UpdateModeMenu(modeMenu);
	wxMenu* lineEndMenu = nullptr;
	menuBar->FindItem(ID_LINEEND_CRLF, &lineEndMenu);
	UpdateLineEndMenu(lineEndMenu);
}

void ASFrame::OnOptionsBitmapClick(wxMouseEvent&)
{
	m_optionsBitmap->SetBitmap(CreateStatusBarOptionsBitmap(true));
	// create a command event with ID_SB_ASTYLE_BITMAP as the ID
	wxCommandEvent buttonClicked(wxEVT_COMMAND_BUTTON_CLICKED, ID_SB_ASTYLE_BITMAP);
	OnAStyleOptions(buttonClicked);
	m_optionsBitmap->SetBitmap(CreateStatusBarOptionsBitmap(false));
}

void ASFrame::OnSearchMenu(wxCommandEvent& event)
{
	switch (event.GetId())
	{
		case ID_SEARCH_FIND:
			ShowFindDialog();
			break;

		case ID_SEARCH_FINDNEXT:
			m_editor->FindNext(m_findData, false);
			break;

		case ID_SEARCH_FINDPREVIOUS:
			m_editor->FindNext(m_findData, true);
			break;

		case ID_SEARCH_GOTOLINE:
			m_editor->ShowGotoLineDialog();
			break;

		case ID_SEARCH_MARKER1_CLEAR:
			m_editor->BookmarkClearAll(BOOKMARK_1);
			break;

		case ID_SEARCH_MARKER1_NEXT:
			m_editor->BookmarkNext(BOOKMARK_1);
			break;

		case ID_SEARCH_MARKER1_PREV:
			m_editor->BookmarkPrevious(BOOKMARK_1);
			break;

		case ID_SEARCH_MARKER1_TOGGLE:
			m_editor->BookmarkToggle(BOOKMARK_1);
			break;

		default:
			ShowMessageDialog("Unrecognized search menu event "
			                  + wxString::Format("%d", event.GetId()),
			                  wxOK | wxICON_ERROR);
			break;
	}
}

void ASFrame::OnStatusBarClick(wxMouseEvent& event)
// Display the correct context menu for the status bar field clicked.
// Activated by a "Connect" or "Bind" event handler.
{
	long x, y;
	event.GetPosition(&x, &y);
	wxStatusBar* statusBar = GetStatusBar();
	if (m_editor)
	{
		// check for status bar settings field
		wxRect settings;
		statusBar->GetFieldRect(SB_SETTINGS, settings);
		if (x >= settings.GetLeft() && x <= settings.GetRight()
		        && y >= settings.GetTop() && y <= settings.GetBottom())
		{
			// create a command event with ID_SB_ASTYLE_SETTINGS as the ID
			wxCommandEvent buttonClicked(wxEVT_COMMAND_BUTTON_CLICKED, ID_SB_ASTYLE_SETTINGS);
			OnAStyleSettings(buttonClicked);
			return;
		}
		// check for status bar options field
		wxRect options;
		statusBar->GetFieldRect(SB_BUTTON, options);
		if (x >= options.GetLeft() && x <= options.GetRight()
		        && y >= options.GetTop() && y <= options.GetBottom())
		{
			// create a mouse event
			wxMouseEvent buttonClicked(wxEVT_LEFT_UP);
			OnOptionsBitmapClick(buttonClicked);
			return;
		}
		// check for status bar filemode field
		wxRect mode;
		statusBar->GetFieldRect(SB_FILEMODE, mode);
		if (x >= mode.GetLeft() && x <= mode.GetRight()
		        && y >= mode.GetTop() && y <= mode.GetBottom())
		{
			wxMenu* modeMenu = BuildModeMenu();
			UpdateModeMenu(modeMenu);
			PopupMenu(modeMenu);
			delete modeMenu;
			return;
		}
		// check for status bar line-end field
		wxRect lineEnd;
		statusBar->GetFieldRect(SB_EOL, lineEnd);
		if (x >= lineEnd.GetLeft() && x <= lineEnd.GetRight()
		        && y >= lineEnd.GetTop() && y <= lineEnd.GetBottom())
		{
			wxMenu* lineEndMenu = BuildLineEndMenu();
			UpdateLineEndMenu(lineEndMenu);
			PopupMenu(lineEndMenu);
			delete lineEndMenu;
			return;
		}
		// check for status bar caret-position field
		wxRect caret;
		statusBar->GetFieldRect(SB_CARET, caret);
		if (x >= caret.GetLeft() && x <= caret.GetRight()
		        && y >= caret.GetTop() && y <= caret.GetBottom())
		{
			wxMenu* caretMenu = new wxMenu();
			int currentPos = m_editor->wxStyledTextCtrl::GetCurrentPos();
			wxString msg = wxString::Format("Position:  %d", currentPos);
			caretMenu->Append(ID_CARET_POS, msg);
			PopupMenu(caretMenu);
			delete caretMenu;
			return;
		}
	}
}

void ASFrame::OnTestOptions(wxCommandEvent&)
{
	Config* config = GetConfig();
	wxString msg = "For options which have not been added to the GUI.\n"
	               "Multiple short or long options may be entered.\n"
	               "They are indicated as an ending '+' on the statusbar.\n"
	               "They are displayed with an ending '+' in the Settings.\n"
	               "There is no editing until Artistic Style is called.\n"
	               "The options must be deleted using this dialog.\n";
	wxTextEntryDialog dialog(this, msg);
	dialog.SetTitle(" Artistic Style Test Options");
	dialog.SetIcons(GetIconBundle());
	dialog.SetValue(m_testOptions);
	dialog.Centre();

	if (dialog.ShowModal() == wxID_OK)
	{
		m_testOptions = dialog.GetValue();
		m_testOptions = m_testOptions.Trim();
		config->SaveTestOptions(m_testOptions);
		StatusBarAdjustWidths();
		UpdateStatusBarDisplay();
	}
}

void ASFrame::OnToolMenu(wxCommandEvent& event)
{
	switch (event.GetId())
	{
		case ID_TOOL_ASTYLE_OPTIONS:
			OnAStyleOptions(event);
			break;

		case ID_TOOL_ASTYLE_SETTINGS:
			OnAStyleSettings(event);
			break;

		case ID_FILEMODE_TEXT:
		case ID_FILEMODE_CPP:
		case ID_FILEMODE_OBJC:
		case ID_FILEMODE_JAVA:
		case ID_FILEMODE_SHARP:
			m_editor->OnModeMenu(event);
			break;

		case ID_LINEEND_CRLF:
		case ID_LINEEND_LF:
		case ID_LINEEND_CR:
			m_editor->OnLineEndMenu(event);
			break;

		case ID_TOOL_TEST_OPTIONS:
			OnTestOptions(event);
			break;

		case ID_TOOL_FORMATSELECT:
		case ID_TB_TOOL_FORMATSELECT:
			SetCursor(*wxHOURGLASS_CURSOR);
			m_editor->FormatSelection();
			SetCursor(wxNullCursor);
			break;

		case ID_TOOL_FORMATSOURCE:
		case ID_TB_TOOL_FORMATSOURCE:
			SetCursor(*wxHOURGLASS_CURSOR);
			m_editor->FormatSource();
			SetCursor(wxNullCursor);
			break;

		case ID_TOOL_TABSTOSPACES:
			SetCursor(*wxHOURGLASS_CURSOR);
			m_editor->TabsToSpaces();
			SetCursor(wxNullCursor);
			break;

		case ID_TOOL_TEXTTOSTRINGS:
			SetCursor(*wxHOURGLASS_CURSOR);
			m_editor->TextToStrings();
			SetCursor(wxNullCursor);
			break;

		case ID_TOOL_STRIPSPACES:
			SetCursor(*wxHOURGLASS_CURSOR);
			m_editor->StripTrailingSpaces();
			SetCursor(wxNullCursor);
			break;

		default:
			ShowMessageDialog("Unrecognized tools menu event "
			                  + wxString::Format("%d", event.GetId()),
			                  wxOK | wxICON_ERROR);
			break;
	}
}

void ASFrame::OnViewMenu(wxCommandEvent& event)
{
	switch (event.GetId())
	{
		case ID_VIEW_LINENUMBERS:
			if (m_editor)
				m_editor->UpdateEditorFromViewMenuOptions();
			break;

		case ID_VIEW_MARGIN:
			if (m_editor)
				m_editor->UpdateEditorFromViewMenuOptions();
			break;

		case ID_VIEW_WHITESPACE:
		case ID_TB_VIEW_WHITESPACE:
			GetMenuBar()->Check(ID_VIEW_WHITESPACE, event.IsChecked());
			UpdateToolBarDisplay();
			if (m_editor)
				m_editor->UpdateEditorFromViewMenuOptions();
			break;

		case ID_VIEW_ACTIVELINE:
			if (m_editor)
				m_editor->UpdateEditorFromViewMenuOptions();
			break;

		case ID_VIEW_INDENTGUIDES:
			if (m_editor)
				m_editor->UpdateEditorFromViewMenuOptions();
			break;

		case ID_VIEW_ENDLINE:
			if (m_editor)
				m_editor->UpdateEditorFromViewMenuOptions();
			break;

		case ID_VIEW_WORDWRAP:
			if (m_editor)
				m_editor->UpdateEditorFromViewMenuOptions();
			break;

		case ID_VIEW_MONOSPACE:
			if (m_editor)
				m_editor->UpdateEditorFromViewMenuOptions();
			break;

		case ID_VIEW_TOOLBAR:
			BuildToolBar();
			break;

		case ID_VIEW_STATUSBAR:
			BuildStatusBar();
			break;

		default:
			ShowMessageDialog(wxString::Format(
			                      "Unrecognized view menu event %d.",
			                      event.GetId()),
			                  wxOK | wxICON_ERROR);
			break;
	}
	m_config->SaveViewMenuOptions(this);
}

bool ASFrame::SetEditorOrViewOption(const wxString& key, const wxString& value)
// Set the Editor option and View menu status from a config file entry.
// Parameter is the config file key.
{
	wxMenuBar* menuBar = GetMenuBar();
	if (key == LINE_NUMBERS)
		menuBar->Check(ID_VIEW_LINENUMBERS, true);
	else if (key == SELECTION_MARGIN)
		menuBar->Check(ID_VIEW_MARGIN, true);
	else if (key == WHITESPACE)
		menuBar->Check(ID_VIEW_WHITESPACE, true);
	else if (key == ACTIVE_LINE)
		// Setting the active line doesn't highlight brace matches.
#if wxCHECK_VERSION(2, 9, 0)
		menuBar->Check(ID_VIEW_ACTIVELINE, true);
#else
		menuBar->Check(ID_VIEW_ACTIVELINE, false);
#endif
	else if (key == INDENT_GUIDES)
		menuBar->Check(ID_VIEW_INDENTGUIDES, true);
	else if (key == END_OF_LINE)
		menuBar->Check(ID_VIEW_ENDLINE, true);
	else if (key == WORD_WRAP)
		menuBar->Check(ID_VIEW_WORDWRAP, true);
	else if (key == SHOW_STATUSBAR)
		menuBar->Check(ID_VIEW_STATUSBAR, true);
	else if (key == MONOSPACE)
		menuBar->Check(ID_VIEW_MONOSPACE, true);
	else if (key == SHOW_TOOLBAR)
		menuBar->Check(ID_VIEW_TOOLBAR, true);
	else if (key == USE_BOTTOM_TABS)
		m_useBottomTabs = true;
	else if (key == USE_SMALL_TOOLBAR)
		m_useSmallToolbar =  true;
	else if (key == DIALOG_TOOLTIPS)
		m_showDialogTips = true;
	else if (key == TOOLBAR_TOOLTIPS)
		m_showToolTips = true;
	else if (key == WRAP_SEARCH)
		m_wrapSearch = true;
	else if (key == HIDE_FIND)
		m_hideDialogAfterMatch = true;
	else if (key == DEFAULT_FONT_FACE)
		m_defaultFont.SetFaceName(value);
	else if (key == DEFAULT_FONT_SIZE)
	{
		m_defaultFont.SetPointSize(11);
		long intValue;
		if (!value.ToLong(&intValue))
			return false;
		m_defaultFont.SetPointSize(intValue);
	}
	else if (key == COMMENT_FONT_FACE)
		m_commentFont.SetFaceName(value);
	else if (key == COMMENT_FONT_SIZE)
	{
		m_commentFont.SetPointSize(10);
		long intValue;
		if (!value.ToLong(&intValue))
			return false;
		m_commentFont.SetPointSize(intValue);
	}
	else if (key == FILE_FILTER_INDEX)
	{
		long intValue;
		if (!value.ToLong(&intValue))
			return false;
		SetFileFilterIndex(intValue);
	}
	else if (key == FRAME_MAXIMIZED)
		this->Maximize();
	else if (key == ASTYLE_DLG_PAGE)
	{
		long intValue;
		if (!value.ToLong(&intValue))
			intValue = 0;
		m_astyleDlgPage = intValue;
	}
	else if (key == EDITOR_DLG_PAGE)
	{
		long intValue;
		if (!value.ToLong(&intValue))
			intValue = 0;
		m_editorDlgPage = intValue;
	}
	else if (key == TEST_OPTIONS)
#ifdef TESTMODE1
		m_testOptions = value;
#else
		m_testOptions = wxEmptyString;
#endif
	else
	{
		// do NOT delete the key here
		// it causes an error in the while loop index
		return false;
	}
	return true;
}

void ASFrame::SetFileFilterIndex(int fileFilterIndex)
{
	FileManager::SetFileFilterIndex(fileFilterIndex);
}

void ASFrame::SetLdtpTestSize()
{
	// change window size and position for ldtp test
	int width = 400;
	int height = 300;
	int x = (wxSystemSettings::GetMetric(wxSYS_SCREEN_X) / 2) + 40;
	int y = (wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) - height) * 7 / 16;
	wxGetApp().GetFrame()->SetSize(x, y, width, height);
}

void ASFrame::ShowFindDialog()
{
	if (m_find)
	{
		delete m_find;
		m_find = nullptr;
	}
	wxString selectedText = m_editor->GetWordAtCaret();
	m_findData.SetFindString(selectedText);
	m_find = new wxFindReplaceDialog(this, &m_findData, "Find");
	assert(m_find);
	m_find->Show(true);
}

void ASFrame::StatusBarAdjustWidths()
{
	wxStatusBar* statusBar = GetStatusBar();
	if (!statusBar)
		return;
	// set default widths
	const int* defaultWidth = m_statusWidth;
	int statusWidth[SB_END];			// new status bar widths
	for (int i = 0; i < SB_END; i++)
		statusWidth[i] = defaultWidth[i];
	// adjust the settings width
	int width, h;
	statusBar->GetTextExtent(m_astyleSettings, &width, &h);
	width += 20;
	if (statusWidth[SB_SETTINGS] < width)
		statusWidth[SB_SETTINGS] = width;
#ifdef __WXMSW__
	statusWidth[SB_SETTINGS] += 10;
#endif
	statusBar->SetStatusWidths(SB_END, statusWidth);
	// position the settings bitmap
	wxRect bmpFieldRect;
	statusBar->GetFieldRect(SB_BUTTON, bmpFieldRect);
	wxStaticBitmap* optionsBitmap = GetOptionsBitmap();
	wxSize settingsSize = optionsBitmap->GetSize();
	optionsBitmap->Move(bmpFieldRect.x + ((bmpFieldRect.width - settingsSize.x) / 2),
	                    bmpFieldRect.y + ((bmpFieldRect.height - settingsSize.y) / 2));
}

void ASFrame::UpdateFrame()
{
	UpdateMenuBarDisplay();
	UpdateToolBarDisplay();
	UpdateStatusBarDisplay();
	FileDoCaption();
}

void ASFrame::UpdateLineEndMenu(wxMenu* lineEndMenu)
{
	int eolMode;
	if (m_editor && m_editor->wxStyledTextCtrl::IsEnabled())
		eolMode = m_editor->wxStyledTextCtrl::GetEOLMode();
	else
		eolMode = wxSTC_EOL_CRLF;
	if (eolMode == wxSTC_EOL_CRLF)
		lineEndMenu->Check(ID_LINEEND_CRLF, true);
	if (eolMode == wxSTC_EOL_LF)
		lineEndMenu->Check(ID_LINEEND_LF, true);
	if (eolMode == wxSTC_EOL_CR)
		lineEndMenu->Check(ID_LINEEND_CR, true);
}

void ASFrame::UpdateMenuBarDisplay() const
// Disable menu items if a file is not open.
// Enable menu items when a file is opened.
{
	wxMenuBar* menuBar = this->GetMenuBar();
	bool isOpen = m_editor != nullptr;

	// these are always disabled initially
	menuBar->Enable(ID_FILE_SAVE, false);
	menuBar->Enable(ID_EDIT_SELECTBLOCK, false);
	menuBar->Enable(ID_TOOL_FORMATSELECT, false);

	// these are enabled if a file is open
	menuBar->Enable(ID_FILE_CLOSE, isOpen);
	menuBar->Enable(ID_FILE_SAVE, isOpen && m_editor->GetFileIsDirty());
	menuBar->Enable(ID_FILE_SAVE_AS, isOpen);
	menuBar->Enable(ID_EDIT_SELECTALL, isOpen);
	menuBar->Enable(ID_EDIT_SELECTTOSTART, isOpen);
	menuBar->Enable(ID_EDIT_SELECTTOEND, isOpen);
	menuBar->Enable(ID_EDIT_INCREASE_INDENT, isOpen);
	menuBar->Enable(ID_EDIT_DECREASE_INDENT, isOpen);
	menuBar->Enable(ID_SEARCH_FIND, isOpen);
	menuBar->Enable(ID_SEARCH_FINDNEXT, isOpen);
	menuBar->Enable(ID_SEARCH_FINDPREVIOUS, isOpen);
	menuBar->Enable(ID_SEARCH_GOTOLINE, isOpen);
	menuBar->Enable(ID_SEARCH_MARKER1_NEXT, isOpen);
	menuBar->Enable(ID_SEARCH_MARKER1_PREV, isOpen);
	menuBar->Enable(ID_SEARCH_MARKER1_TOGGLE, isOpen);
	menuBar->Enable(ID_SEARCH_MARKER1_CLEAR, isOpen);
	menuBar->Enable(ID_TOOL_TABSTOSPACES, isOpen);
	menuBar->Enable(ID_TOOL_TEXTTOSTRINGS, isOpen);
	menuBar->Enable(ID_TOOL_STRIPSPACES, isOpen);
	menuBar->Enable(ID_FILEMODE_TEXT, isOpen);
	menuBar->Enable(ID_FILEMODE_CPP, isOpen);
	menuBar->Enable(ID_FILEMODE_OBJC, isOpen);
	menuBar->Enable(ID_FILEMODE_JAVA, isOpen);
	menuBar->Enable(ID_FILEMODE_SHARP, isOpen);
	menuBar->Enable(ID_LINEEND_CRLF, isOpen);
	menuBar->Enable(ID_LINEEND_LF, isOpen);
	menuBar->Enable(ID_LINEEND_CR, isOpen);

	// the file-mode menu may not be current
	menuBar->Enable(ID_TOOL_FORMATSOURCE, isOpen);
	if (menuBar->IsEnabled(ID_TOOL_FORMATSOURCE))
		if (!m_editor || m_editor->GetFileMode() == FILEMODE_NONE)
			menuBar->Enable(ID_TOOL_FORMATSOURCE, false);
}

void ASFrame::UpdateModeMenu(wxMenu* modeMenu)
{
	int fileMode;
	if (m_editor && m_editor->wxStyledTextCtrl::IsEnabled())
		fileMode = m_editor->GetFileMode();
	else
		fileMode = FILEMODE_NONE;
	if (fileMode == FILEMODE_CPP)
		modeMenu->Check(ID_FILEMODE_CPP, true);
	else if (fileMode == FILEMODE_OBJC)
		modeMenu->Check(ID_FILEMODE_OBJC, true);
	else if (fileMode == FILEMODE_JAVA)
		modeMenu->Check(ID_FILEMODE_JAVA, true);
	else if (fileMode == FILEMODE_SHARP)
		modeMenu->Check(ID_FILEMODE_SHARP, true);
	else
		modeMenu->Check(ID_FILEMODE_TEXT, true);
}

void ASFrame::UpdateNotebookTabDisplay(bool needSave) const
// Update the notebook tab when the file needs to be saved.
{
	int curPage = m_notebook->GetSelection();
	wxString pageText = m_notebook->GetPageText(curPage);
	if (needSave)
	{
		if (!pageText.EndsWith(" *"))
			m_notebook->SetPageText(curPage, pageText + " *");
	}
	else
	{
		wxString sansSuffix;
		if (pageText.EndsWith(" *", &sansSuffix))
			m_notebook->SetPageText(curPage, sansSuffix);
	}
}

void ASFrame::UpdateStatusBarDisplay()
{
	wxStatusBar* statusBar = GetStatusBar();
	if (!statusBar)
		return;

	wxString astyleSettings = " " + m_astyleSettings;
	if (m_testOptions != wxEmptyString)
		astyleSettings += "+";

	// astyle settings
	statusBar->SetStatusText(astyleSettings, SB_SETTINGS);

	// only if the window is shown
	if (m_editor)
	{
		// file type
		wxString ft;
		FileMode fileMode = m_editor->GetFileMode();
		if (fileMode == FILEMODE_CPP)
			ft = " C/C++";
		else if (fileMode == FILEMODE_OBJC)
			ft = " Obj-C";
		else if (fileMode == FILEMODE_JAVA)
			ft = "  Java";
		else if (fileMode == FILEMODE_SHARP)
			ft = "   C#";
		else
			ft = "  Text";
		statusBar->SetStatusText(ft, SB_FILEMODE);

		// line ends
		int eol = m_editor->wxStyledTextCtrl::GetEOLMode();
		wxString eolMsg = " CRLF";
		if (eol == wxSTC_EOL_LF)
			eolMsg = "  LF";
		else if (eol == wxSTC_EOL_CR)
			eolMsg = "  CR";
		statusBar->SetStatusText(eolMsg, SB_EOL);

		// encoding
		wxString encodingText;
		wxString encodingName = m_editor->GetEncodingName();
		wxString sysEncodingName = m_editor->GetSysEncodingName();
		if (encodingName != sysEncodingName)
		{
			encodingText = " " + encodingName;
			if (m_editor->GetUseBOM())
				encodingText.Append("  (B)");
		}
		statusBar->SetStatusText(encodingText, SB_ENCODING);

		// line count
		int lineCount = m_editor->wxStyledTextCtrl::GetLineCount();
		wxString lc = wxString::Format(" Lines: %d", lineCount);
		statusBar->SetStatusText(lc, SB_LINES);

		// current caret position
		int line = m_editor->wxStyledTextCtrl::GetCurrentLine();
		int pos = m_editor->wxStyledTextCtrl::GetCurrentPos();
		wxString posMsg =
		    wxString::Format(" Line: %d, Col: %d/%d", line + 1,
		                     m_editor->wxStyledTextCtrl::GetColumn(pos) + 1,
		                     m_editor->wxStyledTextCtrl::GetColumn(
		                         m_editor->wxStyledTextCtrl::GetLineEndPosition(line)) + 1);
		statusBar->SetStatusText(posMsg, SB_CARET);

		// insert or overwrite
		bool overtype = m_editor->wxStyledTextCtrl::GetOvertype();
		statusBar->SetStatusText(overtype ? " Overwrite" : " Insert", SB_INSERT);
	}
	else
	{
		statusBar->SetStatusText(wxEmptyString, SB_FILEMODE);
		statusBar->SetStatusText(wxEmptyString, SB_ENCODING);
		statusBar->SetStatusText(wxEmptyString, SB_EOL);
		statusBar->SetStatusText(wxEmptyString, SB_LINES);
		statusBar->SetStatusText(wxEmptyString, SB_CARET);
		statusBar->SetStatusText(wxEmptyString, SB_INSERT);
	}
}

void ASFrame::UpdateToolBarDisplay()
{
	bool enabled;     // the menu enabled state
	bool checked;     // the menu check state
	wxMenuBar* menuBar = GetMenuBar();
	wxToolBar* toolBar = GetToolBar();
	if (toolBar == nullptr)
		return;

	// update toolbar from the menu
	enabled = menuBar->IsEnabled(ID_FILE_SAVE);
	toolBar->EnableTool(ID_TB_FILE_SAVE, enabled);
	enabled = menuBar->IsEnabled(ID_FILE_CLOSE);
	toolBar->EnableTool(ID_TB_FILE_CLOSE, enabled);
	enabled = menuBar->IsEnabled(ID_EDIT_SELECTALL);
	toolBar->EnableTool(ID_TB_EDIT_SELECTALL, enabled);
	enabled = menuBar->IsEnabled(ID_EDIT_SELECTBLOCK);
	toolBar->EnableTool(ID_TB_EDIT_SELECTBLOCK, enabled);
	enabled = menuBar->IsEnabled(ID_EDIT_SELECTTOEND);
	toolBar->EnableTool(ID_TB_EDIT_SELECTTOEND, enabled);
	checked = menuBar->IsChecked(ID_VIEW_WHITESPACE);
	toolBar->ToggleTool(ID_TB_VIEW_WHITESPACE, checked);
	enabled = menuBar->IsEnabled(ID_TOOL_FORMATSELECT);
	toolBar->EnableTool(ID_TB_TOOL_FORMATSELECT, enabled);
	enabled = menuBar->IsEnabled(ID_TOOL_FORMATSOURCE);
	toolBar->EnableTool(ID_TB_TOOL_FORMATSOURCE, enabled);

	// update toolbar from wxStyledTextCtrl
	if (m_editor)
	{
		toolBar->EnableTool(ID_TB_EDIT_UNDO, m_editor->wxStyledTextCtrl::CanUndo());
		toolBar->EnableTool(ID_TB_EDIT_REDO, m_editor->wxStyledTextCtrl::CanRedo());
	}
	else
	{
		toolBar->EnableTool(ID_TB_EDIT_UNDO, false);
		toolBar->EnableTool(ID_TB_EDIT_REDO, false);
	}
}

//-----------------------------------------------------------------------------
// ASDropTarget
//-----------------------------------------------------------------------------

bool ASDropTarget::OnDropFiles(wxCoord, wxCoord, const wxArrayString& filePaths)
{
	return wxGetApp().GetFrame()->OnDropFiles(filePaths);
}

//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------

int ShowMessageDialog(const wxString& message, long style)
// Returns wxID_OK, wxID_CANCEL, wxID_YES, wxID_NO.
{
	wxMessageDialog dialog(wxGetApp().GetFrame(),
	                       message,
	                       wxGetApp().GetAppName(),
	                       style,
	                       wxDefaultPosition);

	int reply = dialog.ShowModal();
	return reply;
}
