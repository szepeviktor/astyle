///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __SETTINGSDLGBASE_H__
#define __SETTINGSDLGBASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class SettingsDlgBase
///////////////////////////////////////////////////////////////////////////////
class SettingsDlgBase : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_SHORTOPTIONS = 1000,
			ID_LONGOPTION
		};
		
		wxBoxSizer* m_settingsDlgSizer;
		wxStaticText* m_shortOptions;
		wxStaticText* m_longOptions;
		wxButton* m_ok;
	
	public:
		
		SettingsDlgBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~SettingsDlgBase();
	
};

#endif //__SETTINGSDLGBASE_H__
