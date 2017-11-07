///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "EditorDlgBase.h"

///////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE( EditorDlgBase, wxDialog )
	EVT_TREEBOOK_PAGE_CHANGED( ID_EDITOR_NOTEBOOK, EditorDlgBase::_wxFB_OnNotebookPageChanged )
	EVT_LISTBOX( ID_STYLES, EditorDlgBase::_wxFB_OnListboxSelected )
	EVT_CHECKBOX( ID_BOLD, EditorDlgBase::_wxFB_OnBoldClick )
	EVT_CHECKBOX( ID_ITALIC, EditorDlgBase::_wxFB_OnItalicClick )
	EVT_BUTTON( wxID_RESET, EditorDlgBase::_wxFB_OnResetClick )
END_EVENT_TABLE()

EditorDlgBase::EditorDlgBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetExtraStyle( this->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
	
	m_editorDlgSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* notebookSizer;
	notebookSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_notebook = new wxTreebook( this, ID_EDITOR_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxNB_DEFAULT|wxCLIP_CHILDREN );
	m_optionsPage = new wxPanel( m_notebook, ID_OPTIONS_PAGE, wxDefaultPosition, wxDefaultSize, wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
	wxBoxSizer* optionsSizer;
	optionsSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* optionsSizer2;
	optionsSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_useBottomTabs = new wxCheckBox( m_optionsPage, ID_USE_BOTTOM_TABS, _("Use bottom tabs for main window"), wxDefaultPosition, wxDefaultSize, 0 );
	optionsSizer2->Add( m_useBottomTabs, 0, wxALIGN_LEFT|wxALL, 5 );
	
	m_useSmallToolbar = new wxCheckBox( m_optionsPage, ID_USE_SMALL_TOOLBAR, _("Use small toolbar images"), wxDefaultPosition, wxDefaultSize, 0 );
	optionsSizer2->Add( m_useSmallToolbar, 0, wxALIGN_LEFT|wxALL, 5 );
	
	m_showToolbarTooltips = new wxCheckBox( m_optionsPage, ID_TOOLBAR_TOOLTIPS, _("Show toolbar tooltips"), wxDefaultPosition, wxDefaultSize, 0 );
	optionsSizer2->Add( m_showToolbarTooltips, 0, wxALIGN_LEFT|wxALL, 5 );
	
	m_showDialogTooltips = new wxCheckBox( m_optionsPage, ID_DIALOG_TOOLTIPS, _("Show dialog tooltips"), wxDefaultPosition, wxDefaultSize, 0 );
	optionsSizer2->Add( m_showDialogTooltips, 0, wxALIGN_LEFT|wxALL, 5 );
	
	m_hideFind = new wxCheckBox( m_optionsPage, ID_HIDE_FIND, _("Hide find dialog"), wxDefaultPosition, wxDefaultSize, 0 );
	optionsSizer2->Add( m_hideFind, 0, wxALIGN_LEFT|wxALL, 5 );
	
	m_wrapSearch = new wxCheckBox( m_optionsPage, ID_WRAP_SEARCH, _("Wrap search"), wxDefaultPosition, wxDefaultSize, 0 );
	optionsSizer2->Add( m_wrapSearch, 0, wxALIGN_LEFT|wxALL, 5 );
	
	
	optionsSizer->Add( optionsSizer2, 0, wxALIGN_TOP|wxALL, 20 );
	
	
	m_optionsPage->SetSizer( optionsSizer );
	m_optionsPage->Layout();
	optionsSizer->Fit( m_optionsPage );
	m_notebook->AddPage( NULL, wxT("Editor Options"), false );
	m_notebook->AddSubPage( m_optionsPage, _("Options"), true );
	m_fontsPage = new wxPanel( m_notebook, ID_FONTS_PAGE, wxDefaultPosition, wxDefaultSize, wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
	wxBoxSizer* fontsSizer;
	fontsSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer5->Add( 5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_defaultHeader = new wxStaticText( m_fontsPage, wxID_STATIC, _("Default Font"), wxDefaultPosition, wxDefaultSize, 0 );
	m_defaultHeader->Wrap( -1 );
	bSizer5->Add( m_defaultHeader, 0, wxALIGN_LEFT|wxALL, 5 );
	
	wxBoxSizer* fontsSizer1;
	fontsSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_defaultFonts = new wxComboBox( m_fontsPage, ID_DEFAULT_FONTS, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), 0, NULL, wxCB_READONLY ); 
	fontsSizer1->Add( m_defaultFonts, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_defaultSizes = new wxComboBox( m_fontsPage, ID_DEFAULT_SIZES, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), 0, NULL, wxCB_READONLY ); 
	fontsSizer1->Add( m_defaultSizes, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer5->Add( fontsSizer1, 0, wxALIGN_CENTER_HORIZONTAL|wxLEFT|wxRIGHT, 20 );
	
	
	bSizer5->Add( 5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_commentHeader = new wxStaticText( m_fontsPage, wxID_STATIC, _("Comment Font"), wxDefaultPosition, wxDefaultSize, 0 );
	m_commentHeader->Wrap( -1 );
	bSizer5->Add( m_commentHeader, 0, wxALIGN_LEFT|wxALL, 5 );
	
	wxBoxSizer* fontsSizer2;
	fontsSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_commentFonts = new wxComboBox( m_fontsPage, ID_COMMENT_FONTS, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), 0, NULL, wxCB_READONLY ); 
	fontsSizer2->Add( m_commentFonts, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_commentSizes = new wxComboBox( m_fontsPage, ID_COMMENT_SIZES, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), 0, NULL, wxCB_READONLY ); 
	fontsSizer2->Add( m_commentSizes, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer5->Add( fontsSizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxLEFT|wxRIGHT, 20 );
	
	
	bSizer5->Add( 5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	
	fontsSizer->Add( bSizer5, 0, wxALIGN_TOP|wxALL, 10 );
	
	
	m_fontsPage->SetSizer( fontsSizer );
	m_fontsPage->Layout();
	fontsSizer->Fit( m_fontsPage );
	m_notebook->AddSubPage( m_fontsPage, _("Fonts"), false );
	m_stylesPage = new wxPanel( m_notebook, ID_STYLES_PAGE, wxDefaultPosition, wxDefaultSize, wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
	wxBoxSizer* stylesSizer;
	stylesSizer = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* bSizer9;
	bSizer9 = new wxFlexGridSizer( 1, 2, 0, 20 );
	bSizer9->SetFlexibleDirection( wxBOTH );
	bSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_styles = new wxListBox( m_stylesPage, ID_STYLES, wxDefaultPosition, wxSize( 150,150 ), 0, NULL, wxLB_NEEDED_SB|wxLB_SINGLE ); 
	bSizer9->Add( m_styles, 0, wxEXPAND|wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* stylesSizer2;
	stylesSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_foreground = new wxPanel( m_stylesPage, ID_FOREGROUND, wxDefaultPosition, wxSize( 80,35 ), wxSIMPLE_BORDER|wxTAB_TRAVERSAL );
	stylesSizer2->Add( m_foreground, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* stylesSizer3;
	stylesSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_bold = new wxCheckBox( m_stylesPage, ID_BOLD, _("Bold"), wxDefaultPosition, wxDefaultSize, 0 );
	stylesSizer3->Add( m_bold, 0, wxALIGN_LEFT|wxALL, 5 );
	
	m_italic = new wxCheckBox( m_stylesPage, ID_ITALIC, _("Italic"), wxDefaultPosition, wxDefaultSize, 0 );
	stylesSizer3->Add( m_italic, 0, wxALIGN_LEFT|wxALL, 5 );
	
	
	stylesSizer2->Add( stylesSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 10 );
	
	
	bSizer9->Add( stylesSizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	stylesSizer->Add( bSizer9, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 20 );
	
	
	m_stylesPage->SetSizer( stylesSizer );
	m_stylesPage->Layout();
	stylesSizer->Fit( m_stylesPage );
	m_notebook->AddSubPage( m_stylesPage, _("Styles"), false );
	
	notebookSizer->Add( m_notebook, 1, wxEXPAND|wxALL, 5 );
	
	
	m_editorDlgSizer->Add( notebookSizer, 1, wxEXPAND|wxALL, 5 );
	
	wxFlexGridSizer* buttonSizer;
	buttonSizer = new wxFlexGridSizer( 1, 2, 0, 0 );
	buttonSizer->AddGrowableCol( 1 );
	buttonSizer->SetFlexibleDirection( wxBOTH );
	buttonSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	m_reset  = new wxButton( this, wxID_RESET, _("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( m_reset , 0, wxALL, 5 );
	
	m_sdbSizer = new wxStdDialogButtonSizer();
	m_sdbSizerOK = new wxButton( this, wxID_OK );
	m_sdbSizer->AddButton( m_sdbSizerOK );
	m_sdbSizerCancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer->AddButton( m_sdbSizerCancel );
	m_sdbSizer->Realize();
	
	buttonSizer->Add( m_sdbSizer, 0, wxALL|wxEXPAND, 5 );
	
	
	m_editorDlgSizer->Add( buttonSizer, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( m_editorDlgSizer );
	this->Layout();
	m_editorDlgSizer->Fit( this );
}

EditorDlgBase::~EditorDlgBase()
{
}
