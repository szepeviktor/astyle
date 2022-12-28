// FileManager.h
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include <wx/filedlg.h>

#include "AStyleWx.h"

// -----------------------------------------------------------------------------
// constants
// -----------------------------------------------------------------------------

const wxString FILE_FILTER =
    "All Files|*|"
    "Source Files|*.c;*.cc;*.cpp;*.cxx;*.m;*.mm;*.h;*.hpp;*.hxx;*.cs;*.java;*.jav|"
    "C/C++ Files|*.c;*.cc;*.cpp;*.cxx;*.h;*.hpp;*.hxx|"
    "Obj-C Files|*.m;*.mm;*.h|"
    "C# Files|*.cs|"
    "Java Files|*.java;*.jav";

//-----------------------------------------------------------------------------
// FileManager Class
//-----------------------------------------------------------------------------

class FileManager
{
public:
	FileManager();
	void BuildNotebookPageNew();
	int  BuildNotebookPageWithFile(const wxString& filePathStr, bool select);
	void CheckFileReload();
	int  CloseFile();
	void OpenFile();
	int  SaveFile();
	int  SaveFileAs();

public:	// static methods
	static int  GetFileFilterIndex()                    { return m_fileFilterIndex; }
	static void SetFileFilterIndex(int fileFilterIndex) { m_fileFilterIndex = fileFilterIndex; }

private:
	ASFrame* m_frame{};
	wxAuiNotebook* m_notebook{};
	ASEditor* m_editor{};
	AStyleIFace* m_astyle{};

private:
	int  AskAboutSave(bool saveAs = false);
	bool FileIsOpen(const wxFileName& filePath) const;
	void InitializeEditor();
	bool LoadEditFile(const wxFileName& filepath);
	bool SaveEditFile(const wxFileName& filepath);
	int  SaveFileIfNeeded();

private:	// static member variable
	static int m_fileFilterIndex;
};

#endif  // _FILE_MANAGER_H_
