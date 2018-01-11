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
	explicit Config(wxString appName) : wxConfig(appName) {}
	virtual ~Config() {}
	void GetAStyleOptions(AStyleIFace* astyle);
	vector<TextStyle> GetDefaultStyleOptions();
	void GetEditorAndViewMenuOptions(ASFrame* frame);
	vector<TextStyle> GetStcStyleOptions();
	void InitializeConfigFile(ASFrame* frame);
	void SaveAStyleOptions(AStyleIFace* astyle);
	void SaveEditorOptions(ASFrame* frame);
	void SaveStcStyleOptions(const vector<TextStyle>& styleVector);
	void SaveTestOptions(const wxString& testOptions);
	void SaveViewMenuOptions(ASFrame* frame);

private:
	int  FindStyleVectorIndex(const wxString& groupPath, const vector<TextStyle>& styleVector);
	virtual void ShowInvalidConfig(const wxString& entry);								// override for tests
	bool UpdateStyleEntry(const wxString& groupPath, vector<TextStyle>& styleVector);
};

#endif  // _CONFIG_H_
