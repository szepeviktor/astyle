//  AStyleWx.h
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.txt describes the conditions under which this software may be distributed.

#ifndef _ASTYLEWX_H_
#define _ASTYLEWX_H_

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

// disable the wx.app.h "declaration hides class member" message in VS 14 CTP
// may be fixed in version 3.0.2
#ifdef _MSC_VER
	#if wxRELEASE_NUMBER < 2 || wxRELEASE_NUMBER > 9
		#pragma warning(disable: 4458)
	#endif
#endif

#include <wx/app.h>
#include <wx/arrstr.h>		// array string
#include <wx/aui/auibook.h>	// AUI notebook
#include <wx/dnd.h>			// drag and drop
#include <wx/fdrepdlg.h>	// find/replace dialog
#include <wx/filename.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statbmp.h>		// static bitmap
#include <wx/statusbr.h>
#include <wx/stc/stc.h>		// wxStyledTextCtrl
#include <wx/toolbar.h>

#include <vector>
using std::vector;

#include "AStyleIFace.h"
#include "Config.h"

#ifdef _MSC_VER
	#pragma warning(disable: 4996)  // secure version deprecation warnings
#endif

#ifdef __BORLANDC__
	#pragma warn -8022				// function hides virtual function
#endif

#ifdef __INTEL_COMPILER
	#pragma warning(disable: 1125)  // virtual function override intended?
#endif

#ifdef __clang__
	#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#endif

// -----------------------------------------------------------------------------
// constants
// -----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
	// class ASFrame ..........................
	ID_EDITOR = 1000,
	ID_NOTEBOOK,
	ID_STATUSBAR,
	ID_TOOLBAR,
	// file menu
	ID_FILE_NEW,
	ID_FILE_OPEN,
	ID_FILE_CLOSE,
	ID_FILE_SAVE,
	ID_FILE_SAVE_AS,
	ID_FILE_EXIT,
	// edit menu
	ID_EDIT_UNDO,
	ID_EDIT_REDO,
	ID_EDIT_CUT,
	ID_EDIT_COPY,
	ID_EDIT_PASTE,
	ID_EDIT_SELECTALL,
	ID_EDIT_SELECTTOSTART,
	ID_EDIT_SELECTTOEND,
	ID_EDIT_SELECTBLOCK,
	ID_EDIT_INCREASE_INDENT,
	ID_EDIT_DECREASE_INDENT,
	ID_EDIT_EDITOR_OPTIONS,
	// search menu
	ID_SEARCH_FIND,
	ID_SEARCH_FINDNEXT,
	ID_SEARCH_FINDPREVIOUS,
	ID_SEARCH_GOTOLINE,
	ID_SEARCH_MARKER1_NEXT,
	ID_SEARCH_MARKER1_PREV,
	ID_SEARCH_MARKER1_TOGGLE,
	ID_SEARCH_MARKER1_CLEAR,
	// view menu
	ID_VIEW_LINENUMBERS,
	ID_VIEW_MARGIN,
	ID_VIEW_WHITESPACE,
	ID_VIEW_ACTIVELINE,
	ID_VIEW_INDENTGUIDES,
	ID_VIEW_ENDLINE,
	ID_VIEW_WORDWRAP,
	ID_VIEW_MONOSPACE,
	ID_VIEW_TOOLBAR,
	ID_VIEW_STATUSBAR,
	// tool menu
	ID_TOOL_FORMATSELECT,
	ID_TOOL_FORMATSOURCE,
	ID_TOOL_TABSTOSPACES,
	ID_TOOL_TEXTTOSTRINGS,
	ID_TOOL_STRIPSPACES,
	// filemode menu, a tool submenu
	ID_FILEMODE_TEXT,
	ID_FILEMODE_CPP,
	ID_FILEMODE_OBJC,
	ID_FILEMODE_JAVA,
	ID_FILEMODE_SHARP,
	// lineend menu, a tool submenu
	ID_LINEEND_CRLF,
	ID_LINEEND_LF,
	ID_LINEEND_CR,
	// other tool menu
	ID_TOOL_TEST_OPTIONS,
	ID_TOOL_ASTYLE_SETTINGS,
	ID_TOOL_ASTYLE_OPTIONS,
	// help menu
	ID_HELP_ABOUT,
	ID_HELP_TEXT,
	// toolbar items
	ID_TB_FILE_NEW,
	ID_TB_FILE_OPEN,
	ID_TB_FILE_SAVE,
	ID_TB_FILE_CLOSE,
	ID_TB_EDIT_UNDO,
	ID_TB_EDIT_REDO,
	ID_TB_VIEW_WHITESPACE,
	ID_TB_EDIT_SELECTALL,
	ID_TB_EDIT_SELECTTOEND,
	ID_TB_EDIT_SELECTBLOCK,
	ID_TB_TOOL_FORMATSELECT,
	ID_TB_TOOL_FORMATSOURCE,
	// status bar items
	ID_SB_ASTYLE_BITMAP,		// for options dialog
	ID_SB_ASTYLE_SETTINGS,
	// caret-position menu, a statusbar popup
	ID_CARET_POS,
};

// IDs for the stc margins
enum
{
	STC_LINENUMBER_MARGIN = 0,
	STC_BOOKMARK_MARGIN  = 1,
};

// IDs for the statusbar areas
enum
{
	SB_SETTINGS,
	SB_BUTTON,		// for options dialog
	SB_FILEMODE,
	SB_EOL,
	SB_ENCODING,
	SB_LINES,
	SB_CARET,
	SB_INSERT,
	SB_END,
};

// IDs for bookmarks
enum
{
	BOOKMARK_1 = 1,
};

//-----------------------------------------------------------------------------
// ASEditor class
// This class cannot be named "Editor" because of a duplicate in wxStyledTextCtrl.
// It will cause problems with MinGW and Embarcadero compilers.
//-----------------------------------------------------------------------------

class ASEditor: public wxStyledTextCtrl
{
public:
	explicit ASEditor(wxWindow* notebook);
	virtual ~ASEditor();

	void BookmarkClearAll(int markerBookmark);
	void BookmarkNext(int markerBookmark);
	void BookmarkPrevious(int markerBookmark);
	void BookmarkToggle(int markerBookmark);
	void DiscoverEOLSetting(wxString& text);
	bool FileNeedsReload();
	void FindMatchingBrace(bool select);
	int  FindNext(const wxFindReplaceData& findData, bool reverseFind);
	void FormatSelection();
	void FormatSource();
	wxString GetAStyleVersion();
	wxString GetEncodingName() const;
	wxString GetSysEncodingName() const;
	wxString GetWordAtCaret();
	bool HeaderIsObjectiveC();
	void OnLineEndMenu(wxCommandEvent& event);
	void OnModeMenu(wxCommandEvent& event);
	void SelectBlock();
	void SelectToEnd();
	void SelectToStart();
	void SetFileVariables(const wxFileName& filepath, wxFontEncoding encoding, bool useBOM);
	bool ShowGotoLineDialog();
	void StripTrailingSpaces();
	void TabsToSpaces();
	void TextToStrings();
	void UpdateCommentFonts(wxFont newFont);
	void UpdateEditorFromAStyleOptions(const AStyleIFace* astyle);
	void UpdateEditorFromViewMenuOptions();
	void UpdateFormatSelectDisplay();
	void UpdateLineNumberMargin(bool showMargin);
	void UpdateModeFromFileExtension();
	void UpdateModeFromMenuSelection(int menuID);
	void UpdateMonospaceFontDisplay(bool useMonoFont);
	void UpdateSelectionMargin(bool showMargin);
	void UpdateStcStyleOptions();

public:
	wxString GetCurrentDirectory() const    { return m_filepath.GetPath(); }
	wxFontEncoding GetEncoding() const      { return m_encoding; }
	FileMode GetFileMode() const            { return m_fileMode; }
	bool GetFileIsOk() const                { return m_filepath.IsOk(); }
	bool GetFileIsDirty() const             { return m_isDirty; }
	wxString GetFileName() const            { return m_filepath.GetFullName(); }
	wxString GetFilePath() const            { return m_filepath.GetFullPath(); }
	bool GetModified() const                { return (wxStyledTextCtrl::GetModify()); }
	bool GetUseBOM() const                  { return m_useBOM; }

private:
	ASFrame* m_frame;                   // pointer to the frame object
	// file
	wxFileName m_filepath;              // full path (directory and file name)
	wxDateTime m_fileModTime;           // file modification time
	wxDateTime m_fileModLastAsk;        // time last asked for reload
	FileMode m_fileMode;                // C, Java, C#, ...
	bool m_useBOM;                      // use byte order mark for encoding
	wxFontEncoding m_encoding;          // font encoding
	wxFontEncoding m_sysEncoding;       // system default font encoding
	bool m_isDirty;                     // file has been changed
	// find dialog
	wxString m_lastFind;                // last search string to find
	bool m_wrapped;                     // the search has wrapped
	int  m_firstMatch;                  // text position of first match
	// other
	IndentType m_indentType;            // indent-type, not available in wxStyledTextCtrl

private:
	int  BraceAtCaret();
	void CountLineEnds(wxString& text, int& linesCR, int& linesLF, int& linesCRLF);
	void FormatFile(bool formatSelection);
	void OnMouseCaptureLost(wxMouseCaptureLostEvent&);
	void OnSTCChange(wxStyledTextEvent&);
	void OnSTCCharAdded(wxStyledTextEvent& event);
	void OnSTCContextMenu(wxContextMenuEvent&);
	void OnSTCDoubleClick(wxStyledTextEvent&);
	void OnSTCSavePointLeft(wxStyledTextEvent&);
	void OnSTCSavePointReached(wxStyledTextEvent&);
	void OnSTCUpdateUI(wxStyledTextEvent& event);

	// indent
	void AutomaticIndentation(int ch);
	int  GetIndentSize();
	int  GetIndentState(int line);
	int  GetLinePartsInStyle(int line, int style1, int style2, std::string sv[], int len);
	bool Includes(const std::string& symbols, const std::string& value);
	int  IndentOfBlock(int line);
	bool RangeIsAllWhitespace(int start, int end);
	void SetLineIndentation(int line, int indent);

private:
	DECLARE_EVENT_TABLE()
};

//-----------------------------------------------------------------------------
// ASFrame class
//-----------------------------------------------------------------------------
class Config;

class ASFrame : public wxFrame
{
public:
	ASFrame();
	virtual ~ASFrame();
	void BuildGuiControls(int argc_, wxChar** argv_);
	void FileDoCaption();
	wxFont FindCommentFont() const;
	wxFont FindDefaultFont() const;
	int  GetFileFilterIndex() const;
	wxString GetKeyWords(int fileMode) const;
	long GetNotebookStyle(bool useBottomTabs) const;
	bool OnDropFiles(const wxArrayString& filePaths);
	bool SetEditorOrViewOption(const wxString& entry, const wxString& value);
	void SetFileFilterIndex(int fileFilterIndex);
	void SetLdtpTestSize();
	void UpdateFrame();
	void UpdateMenuBarDisplay() const;
	void UpdateNotebookTabDisplay(bool needSave) const;
	void UpdateStatusBarDisplay();
	void UpdateToolBarDisplay();

public:
	AStyleIFace* GetAStyle() const                  { return m_astyle; }
	int GetAStyleDlgPage() const                    { return m_astyleDlgPage; }
	const wxFont& GetCommentFont() const            { return m_commentFont; }
	const wxFont& GetDefaultFont() const            { return m_defaultFont; }
	int GetEditorDlgPage() const                    { return m_editorDlgPage; }
	Config* GetConfig() const                       { return m_config; }
	ASEditor* GetEditor() const                     { return m_editor; }
	wxFindReplaceDialog* GetFindDialog() const      { return m_find; }
	bool GetHideFindAfterMatch() const              { return m_hideDialogAfterMatch; }
	const wxIconBundle& GetIconBundle() const       { return m_iconBundle; }
	wxAuiNotebook* GetNotebook() const              { return m_notebook; }
	wxStaticBitmap* GetOptionsBitmap() const        { return m_optionsBitmap; }
	bool GetShowToolTips() const                    { return m_showToolTips; }
	bool GetShowDialogTips() const                  { return m_showDialogTips; }
	const vector<TextStyle>& GetStyleVector() const { return m_styleVector; }
	const wxString& GetTestOptions() const          { return m_testOptions; }
	bool GetUseBottomTabs() const                   { return m_useBottomTabs; }
	bool GetUseSmallToolbar() const                 { return m_useSmallToolbar; }
	bool GetWrapSearch() const                      { return m_wrapSearch; }
	bool IsMenuItemChecked(int id) const            { return GetMenuBar()->IsChecked(id); }
	void SetAstyleSettings(wxString astyleSettings) { m_astyleSettings = astyleSettings; }
	void SetDialogTips(bool showDialogTips)         { m_showDialogTips = showDialogTips; }
	void SetStatusBarNeedsUpdate(bool needUpdate)   { m_statusBarNeedsUpdate = needUpdate; }
	void SetUseBottomTabs(bool useBottomTabs)       { m_useBottomTabs = useBottomTabs; }
	void SetUseSmallToolBar(bool useSmallToolbar)   { m_useSmallToolbar = useSmallToolbar; }

private:
	// pointers
	ASEditor*    m_editor;
	wxAuiNotebook* m_notebook;
	wxStaticBitmap* m_optionsBitmap;
	Config*      m_config;
	AStyleIFace* m_astyle;
	// toolbar and dialogs
	bool m_useBottomTabs;
	bool m_useSmallToolbar;
	bool m_viewStatusBar;
	bool m_showToolTips;
	bool m_showDialogTips;
	// wxStyledTextCtrl styles
	wxFont m_defaultFont;               // use only FaceName and PointSize
	wxFont m_commentFont;               // use only FaceName and PointSize
	vector<TextStyle> m_styleVector;    // element for each text style
	// find dialog
	wxFindReplaceData m_findData;
	wxFindReplaceDialog* m_find;
	bool m_wrapSearch;                  // the search should wrap
	bool m_hideDialogAfterMatch;        // hide find dialog after a match
	// other
	wxString m_astyleSettings;          // current astyle settings for status bar
	int m_statusWidth[SB_END];          // default widths of status bar fields
	int m_astyleDlgPage;                // astyle dialog notebook page
	int m_editorDlgPage;                // editor dialog notebook page
	int m_argc;                         // argc from wxApp
	wxChar** m_argv;                    // argv from wxApp
	bool m_statusBarNeedsUpdate;        // statusbar display needs updating
	bool m_checkFileReload;             // check if file has changed
	wxIconBundle m_iconBundle;          // the icon bundle
	wxString m_testOptions;             // test options

private:
	wxMenu* BuildLineEndMenu();
	void BuildMenuBar();
	wxMenu* BuildModeMenu();
	void BuildStatusBar();
	void BuildToolBar();
	void BuildToolTips(bool showToolTips);
	void CloseFindDialog();
	void CloseNotebook();
	wxBitmap CreateStatusBarOptionsBitmap(bool on = false);
	wxSize GetWindowSize() const;
	void OnApplicationClose(wxCloseEvent& event);
	void OnAStyleOptions(wxCommandEvent&);
	void OnAStyleSettings(wxCommandEvent&);
	void OnAuiNotebookDragDone(wxAuiNotebookEvent& event);
	void OnAuiNotebookPageChanged(wxAuiNotebookEvent& event);
	void OnAuiNotebookPageClose(wxAuiNotebookEvent&);
	void OnEditMenu(wxCommandEvent& event);
	void OnEditorOptions(wxCommandEvent&);
	void OnFileMenu(wxCommandEvent& event);
	void OnFindDialog(wxFindDialogEvent& event);
	void OnFrameActivate(wxActivateEvent&);
	void OnHelpAbout(wxCommandEvent& event);
	void OnHelpText(wxCommandEvent& event);
	void OnIdle(wxIdleEvent&);
	void OnMenuOpen(wxMenuEvent& event);
	void OnOptionsBitmapClick(wxMouseEvent& event);
	void OnSearchMenu(wxCommandEvent& event);
	void OnStatusBarClick(wxMouseEvent& event);
	void OnTestOptions(wxCommandEvent&);
	void OnToolMenu(wxCommandEvent& event);
	void OnViewMenu(wxCommandEvent& event);
	void ShowFindDialog();
	void StatusBarAdjustWidths();
	void UpdateLineEndMenu(wxMenu* lineEndMenu);
	void UpdateModeMenu(wxMenu* modeMenu);

private:
	DECLARE_EVENT_TABLE()
};

//-----------------------------------------------------------------------------
// ASDrop class
//-----------------------------------------------------------------------------

class ASDropTarget : public wxFileDropTarget
{
	bool OnDropFiles(wxCoord, wxCoord, const wxArrayString& filePaths);
};

//-----------------------------------------------------------------------------
// Global definitions
//-----------------------------------------------------------------------------

int  ShowMessageDialog(const wxString& message, long style);

//-----------------------------------------------------------------------------
// ASApp class
// Cannot be in a namespace or Linux apps cannot find main().
//-----------------------------------------------------------------------------

class ASApp : public wxApp
{
public:
	ASApp() : m_frame(nullptr) {}
	virtual ~ASApp() {}
	virtual bool OnInit();
	virtual int OnExit();
	ASFrame* GetFrame()   { return m_frame; }

private:
	ASFrame* m_frame;
};

#endif  // _ASTYLEWX_H_
