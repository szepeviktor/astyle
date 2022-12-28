// Config.h
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

#ifndef _CONFIG_H_
#define _CONFIG_H_

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include <wx/config.h>

#include <vector>
using std::vector;

#include "Constants.h"

//-----------------------------------------------------------------------------
// Config class
//-----------------------------------------------------------------------------
class ASFrame;
class AStyleIFace;

class Config : public wxConfig
{
public:
	explicit Config(wxString appName, ASFrame* frame) : wxConfig(appName), m_frame(frame) {}
	void GetAStyleOptions(AStyleIFace* astyle);
	vector<TextStyle> GetDefaultStyleOptions();
	void GetEditorAndViewOptions();
	wxArrayString GetSessionFiles();
	vector<TextStyle> GetStcStyleOptions();
	void SaveAStyleOptions(AStyleIFace* astyle);
	void SaveEditorOptions();
	void SaveSessionFiles();
	void SaveStcStyleOptions(const vector<TextStyle>& styleVector);
	void SaveTestOptions(const wxString& testOptions);
	void SaveViewMenuOptions();

private:
	int  FindStyleVectorIndex(const wxString& groupPath, const vector<TextStyle>& styleVector);
	void InitializeConfigFile();
	virtual void ShowInvalidConfig(const wxString& entry);				// override for tests
	bool UpdateStyleEntry(const wxString& groupPath, vector<TextStyle>& styleVector);

private:
	ASFrame* m_frame;
};

#endif  // _CONFIG_H_
