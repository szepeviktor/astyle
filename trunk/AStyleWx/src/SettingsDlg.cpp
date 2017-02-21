// SettingsDlg.cpp
// Copyright (c) 2017 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include "SettingsDlg.h"

//-----------------------------------------------------------------------------
// declarations
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// SettingsDlg class
//-----------------------------------------------------------------------------

SettingsDlg::SettingsDlg(wxWindow* parent, ASFrame* frame, AStyleIFace* astyle)
	: SettingsDlgBase(parent)
{
	// get system default GUI font
	wxFont font(*wxNORMAL_FONT);;
	int size = font.GetPointSize();
	size++;
	font.SetPointSize(size);
	m_shortOptions->SetFont(font);
	m_longOptions->SetFont(font);
	// show the options
	wxString shortOptions = astyle->GetOptions(true);
	wxString testOptions = frame->GetTestOptions();
	if (testOptions != wxEmptyString)
	{
		if (shortOptions != wxEmptyString)
			shortOptions.Append("\n");
		shortOptions.Append("+");
	}
	if (shortOptions != wxEmptyString)
	{
		m_shortOptions->SetLabel(shortOptions);
		wxString longOptions = astyle->GetOptions();
		if (testOptions != wxEmptyString)
		{
			if (longOptions != wxEmptyString)
				longOptions.Append("\n");
			longOptions.Append(testOptions);
		}
		m_longOptions->SetLabel(longOptions);
	}
	else
	{
		m_shortOptions->SetLabel("( No settings to display )");
		m_longOptions->Destroy();
	}
	this->SetSizer(m_settingsDlgSizer);
	this->Layout();
	m_settingsDlgSizer->Fit(this);
	// set the default button
	m_ok->SetDefault();
}

SettingsDlg::~SettingsDlg()
{
}
