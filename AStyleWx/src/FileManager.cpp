// FileManager.cpp
// Copyright (c) 2017 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include <wx/encconv.h>
#include <wx/file.h>
#include <wx/fontmap.h>

#include "Encoding.h"
#include "FileManager.h"

#ifdef __BORLANDC__
	#pragma warn -8004	// variable is assigned a value that is never used
#endif

//-----------------------------------------------------------------------------
// declarations
//-----------------------------------------------------------------------------

// Implement ASApp& wxGetApp()
DECLARE_APP(ASApp)

// static member variable
int FileManager::m_fileFilterIndex;

//-----------------------------------------------------------------------------
// FileManager Class
//-----------------------------------------------------------------------------

FileManager::FileManager()
	: m_frame(nullptr), m_notebook(nullptr), m_editor(nullptr), m_astyle(nullptr)
{
	m_frame = wxGetApp().GetFrame();
	assert(m_frame != nullptr);

	// __WXQT__ will bypass creating the notebook and stc
	// can remove the option when these are handled by wxWidgets WXQT
#ifndef __WXQT__
	m_notebook = m_frame->GetNotebook();
	assert(m_notebook != nullptr);
#endif

	m_astyle = m_frame->GetAStyle();
	assert(m_astyle != nullptr);
}

FileManager::~FileManager()
{}

int FileManager::AskAboutSave(bool saveAs /*false*/)
{
	wxString filename = m_editor->GetFileName();
	if (filename == wxEmptyString)
	{
		// get "Untitled" from notebook tab
		int page = m_notebook->GetSelection();
		wxString pageText = m_notebook->GetPageText(page);
		pageText = pageText.Mid(0, pageText.Len() - 2);
		filename = wxString::Format("(%s)", pageText.c_str());
	}
	wxString message = saveAs ? "SAVE AS" : "SAVE";
#ifdef TESTMODE1
	int reply = ShowMessageDialog(message + " for TESTMODE1.\n" +
	                              "Save changes to " + filename + "?",
	                              wxOK | wxCANCEL | wxICON_QUESTION);
#else
	int reply = ShowMessageDialog("Save changes to " + filename + "?",
	                              wxYES_NO | wxCANCEL | wxICON_QUESTION);
#endif
	return reply;
}

void FileManager::BuildNotebookPageNew()
{
	m_editor = m_frame->GetEditor();
	// if one unused editor is open don't open another
	if (m_notebook->GetPageCount() == 1
	        && m_editor->GetFileName() == wxEmptyString
	        && m_editor->wxStyledTextCtrl::GetTextLength() == 0)
		return;
	m_editor = nullptr;
	static int editorNum = 0;
	++editorNum;
	wxString pageName = wxString::Format("Untitled%d", editorNum);
	m_editor = new ASEditor(m_notebook);
	assert(m_editor != nullptr);
	InitializeEditor();
	m_notebook->AddPage(m_editor, pageName, true);
	// SetPageToolTip is documented in include\wx\aui\auibook.h
	int page = m_notebook->GetPageIndex(m_editor);
	m_notebook->SetPageToolTip(page, pageName);
	m_editor->SetFocus();
}

int FileManager::BuildNotebookPageWithFile(const wxString& filePathStr, bool select)
{
	wxFileName filePath(filePathStr);
	if (filePath.IsRelative())
		filePath.MakeAbsolute();
	// file must not be open in another tab
	if (FileIsOpen(filePath))
		return wxNOT_FOUND;
	m_editor = m_frame->GetEditor();
	// if there is one unused editor open, use it
	if (m_notebook->GetPageCount() == 1
	        && m_editor->GetFileName() == wxEmptyString
	        && m_editor->wxStyledTextCtrl::GetTextLength() == 0)
	{
		if (!LoadEditFile(filePath))
			return wxNOT_FOUND;
		wxString pageName = filePath.GetFullName();
		m_notebook->SetPageText(0, pageName);
	}
	else
	{
		m_editor = new ASEditor(m_notebook);
		assert(m_editor != nullptr);
		if (!LoadEditFile(filePath))
		{
			delete m_editor;
			return wxNOT_FOUND;
		}
		wxString pageName = filePath.GetFullName();
		m_notebook->AddPage(m_editor, pageName, select);
	}
	// SetPageToolTip is documented in include\wx\aui\auibook.h
	int page = m_notebook->GetPageIndex(m_editor);
	wxString pageToolTip = filePath.GetFullPath();
	m_notebook->SetPageToolTip(page, pageToolTip);
	m_editor->SetFocus();
	// return index of the added page
	return static_cast<int>(m_notebook->GetPageCount()) - 1;
}

void FileManager::CheckFileReload()
{
	// check the current active file
	m_editor = m_frame->GetEditor();
	if (m_editor == nullptr)
		return;

	static int dialogsOnScreen;
	if (0 == dialogsOnScreen && m_editor->FileNeedsReload())
	{
		dialogsOnScreen++;
		wxString message = "%s\nThis file has been modified outside the source editor."
		                   "\n\nReload file from disk?";
		if (m_frame->GetMenuBar()->IsEnabled(ID_FILE_SAVE))
			message.Append("  The unsaved changes will be lost.");
		int reply = ShowMessageDialog(wxString::Format(
		                                  message,
		                                  m_editor->GetFilePath().c_str()),
		                              wxYES_NO | wxICON_QUESTION);
		dialogsOnScreen--;
		if (reply == wxID_YES)
		{
			// save viewing position, don't redraw until finished
			int firstLine = m_editor->wxStyledTextCtrl::GetFirstVisibleLine();
			int xOffset = m_editor->wxStyledTextCtrl::GetXOffset();
			m_editor->Freeze();
			m_frame->SetCursor(*wxHOURGLASS_CURSOR);
			if (LoadEditFile(m_editor->GetFilePath()))
			{
				// return the viewing area, redraw the control
				m_editor->wxStyledTextCtrl::SetFirstVisibleLine(firstLine);
				m_editor->wxStyledTextCtrl::SetXOffset(xOffset);
				// set caret on first visible line
				int linePos = m_editor->wxStyledTextCtrl::PositionFromLine(firstLine);
				m_editor->wxStyledTextCtrl::GotoPos(linePos);
				m_editor->wxStyledTextCtrl::EmptyUndoBuffer();
				m_editor->wxStyledTextCtrl::SetSavePoint();
				m_frame->UpdateFrame();
			}
			m_frame->SetCursor(wxNullCursor);
			m_editor->Thaw();
		}
		m_editor->SetFocus();
	}
}

int FileManager::CloseFile()
{
	// close the current active file
	m_editor = m_frame->GetEditor();
	assert(m_editor != nullptr);
	int reply = SaveFileIfNeeded();
	if (reply == wxID_CANCEL)
		return reply;
	int page = m_notebook->GetSelection();
	m_notebook->DeletePage(page);
	return reply;
}

bool FileManager::FileIsOpen(const wxFileName& filePath) const
// check if file is open in another tab
{
	assert(filePath.IsAbsolute());
	size_t numPages = m_notebook->GetPageCount();
	for (size_t i = 0; i < numPages; i++)
	{
		ASEditor* editor = reinterpret_cast<ASEditor*>(m_notebook->GetPage(i));
		wxString editorFilePath = editor->GetFilePath();
		if (editorFilePath.Lower() == filePath.GetFullPath().Lower())
		{
			m_notebook->SetSelection(i);
			return true;
		}
	}
	return false;
}

void FileManager::InitializeEditor()
{
	m_editor->wxStyledTextCtrl::EmptyUndoBuffer();
	m_editor->wxStyledTextCtrl::SetSavePoint();
	m_editor->UpdateStcStyleOptions();
	m_editor->UpdateEditorFromViewMenuOptions();
	m_editor->UpdateEditorFromAStyleOptions(m_astyle);
	// frame and editor need separate drop targets
	ASDropTarget* editorDropTarget = new ASDropTarget;
	m_editor->wxStyledTextCtrl::SetDropTarget(editorDropTarget);
}

bool FileManager::LoadEditFile(const wxFileName& filepath)
{
	wxLogNull noLog;
	// check ok to open
	wxFile file(filepath.GetFullPath(), wxFile::read_write);
	if (!file.IsOpened())
	{
		if (!file.Exists(filepath.GetFullPath()))
		{
			ShowMessageDialog(wxString::Format(
			                      "Cannot open file:\n%s\n"
			                      "The file cannot be found by the system!",
			                      filepath.GetFullPath().c_str()),
			                  wxOK | wxICON_ERROR);
		}
		else
		{
			ShowMessageDialog(wxString::Format(
			                      "Cannot open file:\n%s\n"
			                      "The file cannot be opened as read/write!",
			                      filepath.GetFullPath().c_str()),
			                  wxOK | wxICON_ERROR);
		}
		return false;
	}

	// check file size
	long filesize = filepath.GetSize().ToULong();
	if (filesize > 40000000)
	{
		ShowMessageDialog(wxString::Format(
		                      "%s\nThe file is too large for the editor (%ld)!",
		                      filepath.GetFullPath().c_str(), filesize),
		                  wxOK | wxICON_ERROR);
		return false;
	}

	// encoding detector reads the file and detects the encoding
	// do not use wxStyledTextCtrl::LoadFile, it doesn't handle encoding
	Encoding encoding(filepath.GetFullPath());

	if (!encoding.IsOK())
	{
		ShowMessageDialog(wxString::Format(
		                      "%s\nThe file encoded with %s cannot be decoded!",
		                      filepath.GetFullPath().c_str(),
		                      wxFontMapper::GetEncodingName(encoding.GetFileEncoding()).c_str()),
		                  wxOK | wxICON_ERROR);
		return false;
	}

	// load the text string
	wxStatusBar* statusBar = m_frame->GetStatusBar();
	if (statusBar)
		statusBar->Freeze();
	wxString fileText = encoding.GetConvertedText();
	m_editor->DiscoverEOLSetting(fileText);
	m_editor->wxStyledTextCtrl::SetText(fileText);
	InitializeEditor();

	// set file variables
	m_editor->SetFileVariables(filepath, encoding.GetFileEncoding(), encoding.UsesBOM());

	// update display options
	m_editor->UpdateModeFromFileExtension();
	m_editor->UpdateStcStyleOptions();
	m_frame->UpdateFrame();
	if (statusBar)
		statusBar->Thaw();

	return true;
}

void FileManager::OpenFile()
{
	wxFileDialog dialog(m_frame,
	                    " Open File",
	                    wxEmptyString,		// use the default directory
	                    wxEmptyString,
	                    FILE_FILTER,
	                    wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);

	dialog.SetFilterIndex(m_fileFilterIndex);
	if (dialog.ShowModal() == wxID_OK)
	{
		m_frame->SetCursor(*wxHOURGLASS_CURSOR);
		wxArrayString filePaths;
		dialog.GetPaths(filePaths);
		for (size_t i = 0; i < filePaths.GetCount(); i++)
			BuildNotebookPageWithFile(filePaths[i], true);
		m_fileFilterIndex = dialog.GetFilterIndex();
		m_frame->SetCursor(wxNullCursor);
	}
}

bool FileManager::SaveEditFile(const wxFileName& filepath)
// Do not use wxStyledTextCtrl::SaveFile, it doesn't handle encoding.
{
	bool useBOM = m_editor->GetUseBOM();
	wxFontEncoding encoding = m_editor->GetEncoding();
	const char* BOM = nullptr;
	size_t BOMSize = 0;
	const wxString textOut = m_editor->wxStyledTextCtrl::GetText();

	if (useBOM)
	{
		switch (encoding)
		{
			case wxFONTENCODING_UTF8:
				BOM = "\xEF\xBB\xBF";
				BOMSize = 3;
				break;
			case wxFONTENCODING_UTF16BE:
				BOM = "\xFE\xFF";
				BOMSize = 2;
				break;
			case wxFONTENCODING_UTF16LE:
				BOM = "\xFF\xFE";
				BOMSize = 2;
				break;
			case wxFONTENCODING_UTF32BE:
				BOM = "\x00\x00\xFE\xFF";
				BOMSize = 4;
				break;
			case wxFONTENCODING_UTF32LE:
				BOM = "\xFF\xFE\x00\x00";
				BOMSize = 4;
				break;
			default:
				break;
		}
	}

	// encode the file
	wxCharBuffer mbBuff;
	size_t outlen = Encoding::EncodeText(encoding, textOut, mbBuff);

	// if conversion does not succeed, try UTF-8
	if (outlen == 0)
	{
		outlen = Encoding::EncodeText(wxFONTENCODING_UTF8, textOut, mbBuff);
		if (outlen == 0)
		{
			ShowMessageDialog(
			    "The file could not be saved because it contains characters "
			    "that can neither be represented in your current code page, "
			    "nor be converted to UTF-8.",
			    wxICON_ERROR | wxOK);
			return false;
		}
		ShowMessageDialog(
		    "The saved document contained characters\n"
		    "which were illegal in the selected encoding.\n\n"
		    "The file's encoding has been changed to UTF-8\n"
		    "to prevent you from losing data.",
		    wxICON_WARNING | wxOK);
		BOM = nullptr;
		BOMSize = 0;
		useBOM = false;
		encoding = wxFONTENCODING_UTF8;
	}

	// open the output file
	wxFile file(filepath.GetFullPath(), wxFile::write);
	if (!file.IsOpened())
	{
		ShowMessageDialog(wxString::Format(
		                      "Error in opening output file '%s'.",
		                      filepath.GetFullPath().c_str()),
		                  wxOK | wxICON_ERROR);
		return false;
	}

	// write the file
	bool isError = false;
	if (BOMSize > 0)
		isError = file.Write(BOM, BOMSize) != BOMSize;
	if (!isError)
		isError = file.Write(mbBuff, outlen) != outlen;
	file.Close();
	m_editor->SetFileVariables(filepath, encoding, useBOM);
	m_frame->UpdateFrame();
	//    wxStyledTextCtrl::EmptyUndoBuffer();  // ???????????????????????
	m_editor->wxStyledTextCtrl::SetSavePoint();

	// check this AFTER saving the modification time in SetFileVariables()
	if (isError)
	{
		ShowMessageDialog(wxString::Format(
		                      "Error in writing file '%s'.\n\nThe file is corrupted!",
		                      filepath.GetFullPath().c_str()),
		                  wxOK | wxICON_ERROR);
		return false;
	}

	return true;
}

int FileManager::SaveFile()
{
	// save the currently active file
	m_editor = m_frame->GetEditor();
	assert(m_editor != nullptr);
	int reply = wxID_NO;
	if (!m_editor->GetFileIsOk())
	{
		reply = SaveFileAs();
		return reply;
	}

#ifdef TESTMODE1
	reply = AskAboutSave();
	if (reply == wxID_CANCEL || reply == wxID_NO)
		return reply;
#endif
	SaveEditFile(m_editor->GetFilePath());
	int page = m_notebook->GetSelection();
	m_notebook->SetPageText(page, m_editor->GetFileName());
	return reply;
}

int FileManager::SaveFileAs()
{
	// save the currently active file
	m_editor = m_frame->GetEditor();
	assert(m_editor != nullptr);
	int reply = wxID_NO;
#ifdef TESTMODE1
	reply = AskAboutSave(true);
	if (reply == wxID_CANCEL || reply == wxID_NO)
		return reply;
#endif
	wxFileDialog dialog(m_frame,
	                    " Save File As",
	                    m_editor->GetCurrentDirectory(),
	                    m_editor->GetFileName(),
	                    "*",
	                    wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	dialog.SetIcons(m_frame->GetIconBundle());
	reply = dialog.ShowModal();
	if (reply == wxID_OK)
	{
		// the file extension may have changed
		wxFileName filepath(dialog.GetPath());
		SaveEditFile(filepath);
		m_editor->UpdateModeFromFileExtension();
		m_editor->UpdateStcStyleOptions();
		int page = m_notebook->GetSelection();
		m_notebook->SetPageText(page, filepath.GetFullName());
		m_frame->UpdateFrame();
	}
	return reply;
}

int FileManager::SaveFileIfNeeded()
{
	// save the currently active file
	m_editor = m_frame->GetEditor();
	assert(m_editor != nullptr);
	int reply = wxID_NO;
#ifndef TESTMODE1
	if (m_editor->GetModified())
	{
		reply = AskAboutSave();
		if (reply == wxID_YES)
			reply = SaveFile();
	}
#endif
	return reply;
}
