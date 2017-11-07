///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ABOUTDLGBASE_H__
#define __ABOUTDLGBASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/hyperlink.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class AboutDlgBase
///////////////////////////////////////////////////////////////////////////////
class AboutDlgBase : public wxDialog 
{
	private:
	
	protected:
		wxBoxSizer* m_aboutDlgSizer;
		wxBoxSizer* bSizer1;
		wxStaticText* m_title1;
		wxStaticBitmap* m_icon;
		wxStaticText* m_description;
		wxStaticText* m_license;
		wxStaticText* m_astylewxVersion;
		wxStaticText* m_wxVersion;
		wxStaticText* m_title2;
		wxStaticText* m_astyleVersion;
		wxStaticText* m_astyleWeblabel;
		wxHyperlinkCtrl* m_astyleWebsite;
		wxStaticText* m_title3;
		wxStaticText* m_localeText;
		wxStaticText* m_localeData;
		wxButton* m_ok;
	
	public:
		
		AboutDlgBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~AboutDlgBase();
	
};

#endif //__ABOUTDLGBASE_H__
