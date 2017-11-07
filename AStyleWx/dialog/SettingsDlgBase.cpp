///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SettingsDlgBase.h"

///////////////////////////////////////////////////////////////////////////

SettingsDlgBase::SettingsDlgBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	m_settingsDlgSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 1, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_shortOptions = new wxStaticText( this, ID_SHORTOPTIONS, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_shortOptions->Wrap( -1 );
	fgSizer1->Add( m_shortOptions, 0, wxALL, 5 );
	
	m_longOptions = new wxStaticText( this, ID_LONGOPTION, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_longOptions->Wrap( -1 );
	fgSizer1->Add( m_longOptions, 0, wxALL, 5 );
	
	
	bSizer2->Add( fgSizer1, 1, wxEXPAND|wxLEFT|wxRIGHT, 10 );
	
	
	m_settingsDlgSizer->Add( bSizer2, 0, wxALL|wxEXPAND, 10 );
	
	m_ok = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ok->SetDefault(); 
	m_settingsDlgSizer->Add( m_ok, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM, 10 );
	
	
	this->SetSizer( m_settingsDlgSizer );
	this->Layout();
	m_settingsDlgSizer->Fit( this );
	
	this->Centre( wxBOTH );
}

SettingsDlgBase::~SettingsDlgBase()
{
}
