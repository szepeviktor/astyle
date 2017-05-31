///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 11 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "AboutDlgBase.h"

///////////////////////////////////////////////////////////////////////////

AboutDlgBase::AboutDlgBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_aboutDlgSizer = new wxBoxSizer( wxVERTICAL );
	
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer21;
	fgSizer21 = new wxFlexGridSizer( 1, 2, 0, 0 );
	fgSizer21->AddGrowableCol( 0 );
	fgSizer21->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );
	
	m_title1 = new wxStaticText( this, wxID_ANY, wxT("title1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_title1->Wrap( -1 );
	fgSizer21->Add( m_title1, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_icon = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	fgSizer21->Add( m_icon, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer1->Add( fgSizer21, 0, wxBOTTOM|wxEXPAND|wxTOP, 15 );
	
	m_description = new wxStaticText( this, wxID_ANY, wxT("Description"), wxDefaultPosition, wxDefaultSize, 0 );
	m_description->Wrap( -1 );
	bSizer1->Add( m_description, 0, wxBOTTOM|wxEXPAND, 5 );
	
	m_license = new wxStaticText( this, wxID_ANY, wxT("License"), wxDefaultPosition, wxDefaultSize, 0 );
	m_license->Wrap( -1 );
	bSizer1->Add( m_license, 0, wxBOTTOM|wxEXPAND|wxTOP, 5 );
	
	m_astylewxVersion = new wxStaticText( this, wxID_ANY, wxT("AStyleWx version"), wxDefaultPosition, wxDefaultSize, 0 );
	m_astylewxVersion->Wrap( -1 );
	bSizer1->Add( m_astylewxVersion, 0, wxBOTTOM|wxEXPAND|wxTOP, 5 );
	
	m_wxVersion = new wxStaticText( this, wxID_ANY, wxT("wxWidgets version"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxVersion->Wrap( -1 );
	bSizer1->Add( m_wxVersion, 0, wxBOTTOM|wxEXPAND|wxTOP, 5 );
	
	wxStaticLine* staticline1;
	staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( staticline1, 0, wxBOTTOM|wxEXPAND|wxTOP, 5 );
	
	m_title2 = new wxStaticText( this, wxID_ANY, wxT("title2"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
	m_title2->Wrap( -1 );
	bSizer1->Add( m_title2, 0, wxBOTTOM|wxEXPAND|wxTOP, 5 );
	
	m_astyleVersion = new wxStaticText( this, wxID_ANY, wxT("AStyle version"), wxDefaultPosition, wxDefaultSize, 0 );
	m_astyleVersion->Wrap( -1 );
	bSizer1->Add( m_astyleVersion, 0, wxEXPAND|wxTOP, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_astyleWeblabel = new wxStaticText( this, wxID_ANY, wxT("Website"), wxDefaultPosition, wxDefaultSize, 0 );
	m_astyleWeblabel->Wrap( -1 );
	bSizer3->Add( m_astyleWeblabel, 0, wxEXPAND|wxRIGHT|wxTOP, 5 );
	
	m_astyleWebsite = new wxHyperlinkCtrl( this, wxID_ANY, wxT("website"), wxT("http://astyle.sourceforge.net/"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	
	m_astyleWebsite->SetHoverColour( wxColour( 255, 0, 0 ) );
	m_astyleWebsite->SetNormalColour( wxColour( 0, 0, 255 ) );
	m_astyleWebsite->SetVisitedColour( wxColour( 0, 0, 255 ) );
	bSizer3->Add( m_astyleWebsite, 0, 0, 5 );
	
	
	bSizer1->Add( bSizer3, 0, wxBOTTOM|wxEXPAND|wxTOP, 5 );
	
	wxStaticLine* staticline2;
	staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( staticline2, 0, wxBOTTOM|wxEXPAND|wxTOP, 5 );
	
	m_title3 = new wxStaticText( this, wxID_ANY, wxT("title3"), wxDefaultPosition, wxDefaultSize, 0 );
	m_title3->Wrap( -1 );
	bSizer1->Add( m_title3, 0, wxBOTTOM|wxEXPAND|wxTOP, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 1, 2, 0, 20 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_localeText = new wxStaticText( this, wxID_ANY, wxT("localeText"), wxDefaultPosition, wxDefaultSize, 0 );
	m_localeText->Wrap( -1 );
	fgSizer2->Add( m_localeText, 0, 0, 5 );
	
	m_localeData = new wxStaticText( this, wxID_ANY, wxT("localeData"), wxDefaultPosition, wxDefaultSize, 0 );
	m_localeData->Wrap( -1 );
	fgSizer2->Add( m_localeData, 0, 0, 5 );
	
	
	bSizer1->Add( fgSizer2, 1, wxBOTTOM|wxEXPAND|wxTOP, 5 );
	
	wxStaticLine* staticline3;
	staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( staticline3, 0, wxBOTTOM|wxEXPAND|wxTOP, 5 );
	
	m_ok = new wxButton( this, wxID_OK, wxT("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ok->SetDefault(); 
	bSizer1->Add( m_ok, 0, wxALIGN_RIGHT|wxBOTTOM|wxTOP, 10 );
	
	
	m_aboutDlgSizer->Add( bSizer1, 0, wxEXPAND|wxLEFT|wxRIGHT, 25 );
	
	
	this->SetSizer( m_aboutDlgSizer );
	this->Layout();
	m_aboutDlgSizer->Fit( this );
	
	this->Centre( wxBOTH );
}

AboutDlgBase::~AboutDlgBase()
{
}
