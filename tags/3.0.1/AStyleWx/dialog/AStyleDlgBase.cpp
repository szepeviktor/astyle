///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "AStyleDlgBase.h"

///////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE( AStyleDlgBase, wxDialog )
	EVT_TREEBOOK_PAGE_CHANGED( ID_ASTYLE_NOTEBOOK, AStyleDlgBase::_wxFB_OnNotebookPageChanged )
	EVT_RADIOBUTTON( ID_STYLE_NONE, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_STYLE_ALLMAN, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_STYLE_JAVA, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_STYLE_KR, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_STYLE_STROUSTRUP, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_STYLE_WHITESMITH, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_STYLE_VTK, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_STYLE_BANNER, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_STYLE_GNU, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_STYLE_LINUX, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_STYLE_HORSTMANN, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_STYLE_1TBS, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_STYLE_GOOGLE, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_STYLE_MOZILLA, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_STYLE_PICO, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_STYLE_LISP, AStyleDlgBase::_wxFB_OnStyleClick )
	EVT_RADIOBUTTON( ID_INDENTWITH_SPACE, AStyleDlgBase::_wxFB_OnTabClick )
	EVT_RADIOBUTTON( ID_INDENTWITH_TAB, AStyleDlgBase::_wxFB_OnTabClick )
	EVT_RADIOBUTTON( ID_INDENTWITH_FTAB, AStyleDlgBase::_wxFB_OnTabClick )
	EVT_CHECKBOX( ID_USE_TAB_LENGTH, AStyleDlgBase::_wxFB_OnTabClick )
	EVT_BUTTON( ID_INDENT_LENGTH_DISPLAY, AStyleDlgBase::_wxFB_OnTabClick )
	EVT_CHECKBOX( ID_ATTACH_NAMESPACE, AStyleDlgBase::_wxFB_OnModifierClick )
	EVT_CHECKBOX( ID_ATTACH_CLASS, AStyleDlgBase::_wxFB_OnModifierClick )
	EVT_CHECKBOX( ID_ATTACH_INLINE, AStyleDlgBase::_wxFB_OnModifierClick )
	EVT_CHECKBOX( ID_ATTACH_EXTERN_C, AStyleDlgBase::_wxFB_OnModifierClick )
	EVT_CHECKBOX( ID_ATTACH_CLOSING_WHILE, AStyleDlgBase::_wxFB_OnModifierClick )
	EVT_CHECKBOX( ID_INDENT_CLASS, AStyleDlgBase::_wxFB_OnIndentClick )
	EVT_CHECKBOX( ID_INDENT_MODIFIER, AStyleDlgBase::_wxFB_OnIndentClick )
	EVT_CHECKBOX( ID_INDENT_SWITCH, AStyleDlgBase::_wxFB_OnIndentClick )
	EVT_CHECKBOX( ID_INDENT_CASE, AStyleDlgBase::_wxFB_OnIndentClick )
	EVT_CHECKBOX( ID_INDENT_NAMESPACE, AStyleDlgBase::_wxFB_OnIndentClick )
	EVT_CHECKBOX( ID_INDENT_AFTER_PAREN, AStyleDlgBase::_wxFB_OnIndentClick )
	EVT_CHECKBOX( ID_INDENT_CONTINUATION, AStyleDlgBase::_wxFB_OnIndentClick )
	EVT_CHECKBOX( ID_INDENT_GOTO, AStyleDlgBase::_wxFB_OnIndentClick )
	EVT_CHECKBOX( ID_INDENT_PREPROC_BLOCK, AStyleDlgBase::_wxFB_OnIndentClick )
	EVT_CHECKBOX( ID_INDENT_PREPROC_DEFINE, AStyleDlgBase::_wxFB_OnIndentClick )
	EVT_CHECKBOX( ID_INDENT_PREPROC_COND, AStyleDlgBase::_wxFB_OnIndentClick )
	EVT_CHECKBOX( ID_INDENT_COL1_COMMENT, AStyleDlgBase::_wxFB_OnIndentClick )
	EVT_BUTTON( ID_MIN_CONDITIONAL_DISPLAY, AStyleDlgBase::_wxFB_OnIndentClick )
	EVT_BUTTON( ID_MAX_CONTINUATION_DISPLAY, AStyleDlgBase::_wxFB_OnIndentClick )
	EVT_CHECKBOX( ID_BREAK_HEADER, AStyleDlgBase::_wxFB_OnPadClick )
	EVT_CHECKBOX( ID_BREAK_ALL, AStyleDlgBase::_wxFB_OnPadClick )
	EVT_CHECKBOX( ID_PAD_OPERATOR, AStyleDlgBase::_wxFB_OnPadClick )
	EVT_CHECKBOX( ID_PAD_COMMA, AStyleDlgBase::_wxFB_OnPadClick )
	EVT_CHECKBOX( ID_PAD_PAREN_OUT, AStyleDlgBase::_wxFB_OnPadClick )
	EVT_CHECKBOX( ID_PAD_PAREN_IN, AStyleDlgBase::_wxFB_OnPadClick )
	EVT_CHECKBOX( ID_PAD_FIRST_PAREN_OUT, AStyleDlgBase::_wxFB_OnPadClick )
	EVT_CHECKBOX( ID_PAD_HEADER, AStyleDlgBase::_wxFB_OnPadClick )
	EVT_CHECKBOX( ID_UNPAD_PAREN, AStyleDlgBase::_wxFB_OnPadClick )
	EVT_CHECKBOX( ID_DELETE_EMPTY_LINE, AStyleDlgBase::_wxFB_OnPadClick )
	EVT_CHECKBOX( ID_FILL_EMPTY_LINE, AStyleDlgBase::_wxFB_OnPadClick )
	EVT_CHOICE( ID_ALIGN_POINTER, AStyleDlgBase::_wxFB_OnPadClick )
	EVT_BUTTON( ID_ALIGN_POINTER_DISPLAY, AStyleDlgBase::_wxFB_OnPadClick )
	EVT_CHOICE( ID_ALIGN_REFERENCE, AStyleDlgBase::_wxFB_OnPadClick )
	EVT_BUTTON( ID_ALIGN_REFERENCE_DISPLAY, AStyleDlgBase::_wxFB_OnPadClick )
	EVT_CHECKBOX( ID_BREAK_CLOSING, AStyleDlgBase::_wxFB_OnFormatClick )
	EVT_CHECKBOX( ID_BREAK_ELSEIF, AStyleDlgBase::_wxFB_OnFormatClick )
	EVT_CHECKBOX( ID_BREAK_OL_HEADERS, AStyleDlgBase::_wxFB_OnFormatClick )
	EVT_CHECKBOX( ID_ADD_BRACES, AStyleDlgBase::_wxFB_OnFormatClick )
	EVT_CHECKBOX( ID_ADD_OL_BRACES, AStyleDlgBase::_wxFB_OnFormatClick )
	EVT_CHECKBOX( ID_REMOVE_BRACES, AStyleDlgBase::_wxFB_OnFormatClick )
	EVT_CHECKBOX( ID_KEEP_OL_BLOCKS, AStyleDlgBase::_wxFB_OnFormatClick )
	EVT_CHECKBOX( ID_KEEP_OL_STATEMENTS, AStyleDlgBase::_wxFB_OnFormatClick )
	EVT_CHECKBOX( ID_CONVERT_TABS, AStyleDlgBase::_wxFB_OnFormatClick )
	EVT_CHECKBOX( ID_CLOSE_TEMPLATES, AStyleDlgBase::_wxFB_OnFormatClick )
	EVT_CHECKBOX( ID_REMOVE_COMMENT_PREFIX, AStyleDlgBase::_wxFB_OnFormatClick )
	EVT_CHOICE( ID_MAX_CODE_LENGTH, AStyleDlgBase::_wxFB_OnFormatClick )
	EVT_BUTTON( ID_MAX_CODE_LENGTH_DISPLAY, AStyleDlgBase::_wxFB_OnFormatClick )
	EVT_CHECKBOX( ID_BREAK_AFTER_LOGICAL, AStyleDlgBase::_wxFB_OnFormatClick )
	EVT_CHECKBOX( ID_PAD_METHOD_PREFIX, AStyleDlgBase::_wxFB_OnOtherClick )
	EVT_CHECKBOX( ID_UNPAD_METHOD_PREFIX, AStyleDlgBase::_wxFB_OnOtherClick )
	EVT_CHECKBOX( ID_PAD_RETURN_TYPE, AStyleDlgBase::_wxFB_OnOtherClick )
	EVT_CHECKBOX( ID_UNPAD_RETURN_TYPE, AStyleDlgBase::_wxFB_OnOtherClick )
	EVT_CHECKBOX( ID_PAD_PARAM_TYPE, AStyleDlgBase::_wxFB_OnOtherClick )
	EVT_CHECKBOX( ID_UNPAD_PARAM_TYPE, AStyleDlgBase::_wxFB_OnOtherClick )
	EVT_CHECKBOX( ID_ALIGN_METHOD_COLON, AStyleDlgBase::_wxFB_OnOtherClick )
	EVT_CHOICE( ID_PAD_METHOD_COLON, AStyleDlgBase::_wxFB_OnOtherClick )
	EVT_BUTTON( ID_PAD_METHOD_COLON_DISPLAY, AStyleDlgBase::_wxFB_OnOtherClick )
	EVT_BUTTON( ID_RESET_ALL, AStyleDlgBase::_wxFB_OnResetAllClick )
	EVT_BUTTON( ID_NEW_SETTINGS, AStyleDlgBase::_wxFB_OnSettingsClick )
	EVT_BUTTON( wxID_OK, AStyleDlgBase::_wxFB_OnOkClick )
END_EVENT_TABLE()

AStyleDlgBase::AStyleDlgBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_astyleDlgSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* notebookSizer;
	notebookSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_notebook = new wxTreebook( this, ID_ASTYLE_NOTEBOOK, wxDefaultPosition, wxDefaultSize, 0|wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
	m_stylePage = new wxPanel( m_notebook, ID_STYLE_PAGE, wxPoint( -1,0 ), wxDefaultSize, wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
	wxBoxSizer* styleSizer;
	styleSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_styleSizer = new wxStaticBoxSizer( new wxStaticBox( m_stylePage, wxID_ANY, wxT("Brace Style") ), wxVERTICAL );
	
	wxStaticText* styleStaticTextBeg;
	styleStaticTextBeg = new wxStaticText( m_styleSizer->GetStaticBox(), wxID_ANY, wxT("Static box to wrap tab traversal"), wxDefaultPosition, wxDefaultSize, 0 );
	styleStaticTextBeg->Wrap( -1 );
	styleStaticTextBeg->Enable( false );
	styleStaticTextBeg->Hide();
	
	m_styleSizer->Add( styleStaticTextBeg, 0, wxALL, 5 );
	
	m_styleNone = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_NONE, wxT("&None"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	m_styleSizer->Add( m_styleNone, 0, wxALL, 5 );
	
	m_styleAllman = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_ALLMAN, wxT("&Allman"), wxDefaultPosition, wxDefaultSize, 0 );
	m_styleSizer->Add( m_styleAllman, 0, wxALL, 5 );
	
	m_styleJava = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_JAVA, wxT("&Java"), wxDefaultPosition, wxDefaultSize, 0 );
	m_styleSizer->Add( m_styleJava, 0, wxALL, 5 );
	
	m_styleKR = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_KR, wxT("&K && R"), wxDefaultPosition, wxDefaultSize, 0 );
	m_styleSizer->Add( m_styleKR, 0, wxALL, 5 );
	
	m_styleStroustrup = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_STROUSTRUP, wxT("&Stroustrup"), wxDefaultPosition, wxDefaultSize, 0 );
	m_styleSizer->Add( m_styleStroustrup, 0, wxALL, 5 );
	
	m_styleWhitesmith = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_WHITESMITH, wxT("&Whitesmith"), wxDefaultPosition, wxDefaultSize, 0 );
	m_styleSizer->Add( m_styleWhitesmith, 0, wxALL, 5 );
	
	m_styleVtk = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_VTK, wxT("&VTK"), wxDefaultPosition, wxDefaultSize, 0 );
	m_styleSizer->Add( m_styleVtk, 0, wxALL, 5 );
	
	m_styleBanner = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_BANNER, wxT("&Banner"), wxDefaultPosition, wxDefaultSize, 0 );
	m_styleSizer->Add( m_styleBanner, 0, wxALL, 5 );
	
	m_styleGnu = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_GNU, wxT("&GNU"), wxDefaultPosition, wxDefaultSize, 0 );
	m_styleSizer->Add( m_styleGnu, 0, wxALL, 5 );
	
	m_styleLinux = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_LINUX, wxT("Linu&x"), wxDefaultPosition, wxDefaultSize, 0 );
	m_styleSizer->Add( m_styleLinux, 0, wxALL, 5 );
	
	m_styleHorstmann = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_HORSTMANN, wxT("&Horstmann"), wxDefaultPosition, wxDefaultSize, 0 );
	m_styleSizer->Add( m_styleHorstmann, 0, wxALL, 5 );
	
	m_style1tbs = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_1TBS, wxT("&1TBS"), wxDefaultPosition, wxDefaultSize, 0 );
	m_styleSizer->Add( m_style1tbs, 0, wxALL, 5 );
	
	m_styleGoogle = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_GOOGLE, wxT("G&oogle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_styleSizer->Add( m_styleGoogle, 0, wxALL, 5 );
	
	m_styleMozilla = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_MOZILLA, wxT("&Mozilla"), wxDefaultPosition, wxDefaultSize, 0 );
	m_styleSizer->Add( m_styleMozilla, 0, wxALL, 5 );
	
	m_stylePico = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_PICO, wxT("&Pico"), wxDefaultPosition, wxDefaultSize, 0 );
	m_styleSizer->Add( m_stylePico, 0, wxALL, 5 );
	
	m_styleLisp = new wxRadioButton( m_styleSizer->GetStaticBox(), ID_STYLE_LISP, wxT("&Lisp"), wxDefaultPosition, wxDefaultSize, 0 );
	m_styleSizer->Add( m_styleLisp, 0, wxALL, 5 );
	
	wxStaticText* styleStaticTextEnd;
	styleStaticTextEnd = new wxStaticText( m_styleSizer->GetStaticBox(), wxID_ANY, wxT("Static box to wrap tab traversal"), wxDefaultPosition, wxDefaultSize, 0 );
	styleStaticTextEnd->Wrap( -1 );
	styleStaticTextEnd->Enable( false );
	styleStaticTextEnd->Hide();
	
	m_styleSizer->Add( styleStaticTextEnd, 0, wxALL, 5 );
	
	
	bSizer14->Add( m_styleSizer, 1, wxALL|wxEXPAND, 5 );
	
	m_stylePreviewSizer = new wxStaticBoxSizer( new wxStaticBox( m_stylePage, wxID_ANY, wxT("Preview") ), wxVERTICAL );
	
	m_stylePreviewSTC = new wxStyledTextCtrl( m_stylePreviewSizer->GetStaticBox(), ID_STYLE_PREVIEW_STC, wxDefaultPosition, wxSize( 220,280 ), wxSTATIC_BORDER, wxEmptyString );
	m_stylePreviewSTC->SetUseTabs( false );
	m_stylePreviewSTC->SetTabWidth( 4 );
	m_stylePreviewSTC->SetIndent( 4 );
	m_stylePreviewSTC->SetTabIndents( false );
	m_stylePreviewSTC->SetBackSpaceUnIndents( false );
	m_stylePreviewSTC->SetViewEOL( false );
	m_stylePreviewSTC->SetViewWhiteSpace( false );
	m_stylePreviewSTC->SetMarginWidth( 2, 0 );
	m_stylePreviewSTC->SetIndentationGuides( false );
	m_stylePreviewSTC->SetMarginWidth( 1, 0 );
	m_stylePreviewSTC->SetMarginWidth( 0, 0 );
	m_stylePreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_stylePreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_stylePreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_stylePreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_stylePreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_stylePreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_stylePreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_stylePreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_stylePreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_stylePreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_stylePreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_stylePreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_stylePreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_stylePreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_stylePreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_stylePreviewSTC->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_stylePreviewSTC->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	m_stylePreviewSizer->Add( m_stylePreviewSTC, 0, wxALL, 5 );
	
	
	bSizer14->Add( m_stylePreviewSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	styleSizer->Add( bSizer14, 1, wxALL|wxEXPAND, 5 );
	
	
	m_stylePage->SetSizer( styleSizer );
	m_stylePage->Layout();
	styleSizer->Fit( m_stylePage );
	m_notebook->AddPage( NULL, wxT("Artistic Style Options"), false );
	m_notebook->AddSubPage( m_stylePage, wxT("Brace Style"), false );
	m_tabPage = new wxPanel( m_notebook, ID_TABS_PAGE, wxPoint( -1,0 ), wxDefaultSize, wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
	wxBoxSizer* tabSizer;
	tabSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxVERTICAL );
	
	m_tabSizer = new wxStaticBoxSizer( new wxStaticBox( m_tabPage, wxID_ANY, wxT("Tabs/Spaces") ), wxVERTICAL );
	
	wxStaticText* tabStaticTextBeg;
	tabStaticTextBeg = new wxStaticText( m_tabSizer->GetStaticBox(), wxID_ANY, wxT("Static box to wrap tab traversal"), wxDefaultPosition, wxDefaultSize, 0 );
	tabStaticTextBeg->Wrap( -1 );
	tabStaticTextBeg->Enable( false );
	tabStaticTextBeg->Hide();
	
	m_tabSizer->Add( tabStaticTextBeg, 0, wxALL, 5 );
	
	m_spaceIndent = new wxRadioButton( m_tabSizer->GetStaticBox(), ID_INDENTWITH_SPACE, wxT("Indent with &spaces"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	m_tabSizer->Add( m_spaceIndent, 0, wxALL, 5 );
	
	m_tabIndent = new wxRadioButton( m_tabSizer->GetStaticBox(), ID_INDENTWITH_TAB, wxT("Indent with &tabs"), wxDefaultPosition, wxDefaultSize, 0 );
	m_tabSizer->Add( m_tabIndent, 0, wxALL, 5 );
	
	m_forceTabIndent = new wxRadioButton( m_tabSizer->GetStaticBox(), ID_INDENTWITH_FTAB, wxT("&Force indent with tabs"), wxDefaultPosition, wxDefaultSize, 0 );
	m_tabSizer->Add( m_forceTabIndent, 0, wxALL, 5 );
	
	wxBoxSizer* m_forceTabSizer;
	m_forceTabSizer = new wxBoxSizer( wxVERTICAL );
	
	m_useTabLength = new wxCheckBox( m_tabSizer->GetStaticBox(), ID_USE_TAB_LENGTH, wxT("Change spaces &per tab"), wxDefaultPosition, wxDefaultSize, 0 );
	m_forceTabSizer->Add( m_useTabLength, 0, wxALL, 5 );
	
	m_tabLength = new wxSpinCtrl( m_tabSizer->GetStaticBox(), ID_TAB_LENGTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	m_forceTabSizer->Add( m_tabLength, 0, wxALL, 5 );
	
	
	m_tabSizer->Add( m_forceTabSizer, 0, wxLEFT, 20 );
	
	
	m_tabSizer->Add( 0, 0, 0, wxBOTTOM, 5 );
	
	m_indentLengthText = new wxStaticText( m_tabSizer->GetStaticBox(), wxID_ANY, wxT("Spaces per &Indent"), wxDefaultPosition, wxDefaultSize, 0 );
	m_indentLengthText->Wrap( -1 );
	m_tabSizer->Add( m_indentLengthText, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxHORIZONTAL );
	
	m_indentLength = new wxSpinCtrl( m_tabSizer->GetStaticBox(), ID_INDENT_LENGTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	bSizer26->Add( m_indentLength, 0, wxALL, 5 );
	
	
	bSizer26->Add( 0, 0, 1, wxLEFT, 5 );
	
	m_indentLengthlDisplay = new wxButton( m_tabSizer->GetStaticBox(), ID_INDENT_LENGTH_DISPLAY, wxEmptyString, wxDefaultPosition, wxSize( 17,18 ), 0 );
	bSizer26->Add( m_indentLengthlDisplay, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5 );
	
	
	m_tabSizer->Add( bSizer26, 0, wxEXPAND, 5 );
	
	
	bSizer28->Add( m_tabSizer, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer28->Add( 0, 0, 0, wxALL, 5 );
	
	m_modifySizer = new wxStaticBoxSizer( new wxStaticBox( m_tabPage, wxID_ANY, wxT("Brace Modify") ), wxVERTICAL );
	
	m_attachNamespace = new wxCheckBox( m_modifySizer->GetStaticBox(), ID_ATTACH_NAMESPACE, wxT("Attach &namespaces"), wxDefaultPosition, wxDefaultSize, 0 );
	m_modifySizer->Add( m_attachNamespace, 0, wxALL, 5 );
	
	m_attachClass = new wxCheckBox( m_modifySizer->GetStaticBox(), ID_ATTACH_CLASS, wxT("Attach &classes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_modifySizer->Add( m_attachClass, 0, wxALL, 5 );
	
	m_attachInline = new wxCheckBox( m_modifySizer->GetStaticBox(), ID_ATTACH_INLINE, wxT("Attach in&lines"), wxDefaultPosition, wxDefaultSize, 0 );
	m_modifySizer->Add( m_attachInline, 0, wxALL, 5 );
	
	m_attachExternC = new wxCheckBox( m_modifySizer->GetStaticBox(), ID_ATTACH_EXTERN_C, wxT("Attach e&xtern C"), wxDefaultPosition, wxDefaultSize, 0 );
	m_modifySizer->Add( m_attachExternC, 0, wxALL, 5 );
	
	m_attachClosingWhile = new wxCheckBox( m_modifySizer->GetStaticBox(), ID_ATTACH_CLOSING_WHILE, wxT("Attach closing &while"), wxDefaultPosition, wxDefaultSize, 0 );
	m_modifySizer->Add( m_attachClosingWhile, 0, wxALL, 5 );
	
	
	bSizer28->Add( m_modifySizer, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer21->Add( bSizer28, 1, wxEXPAND, 5 );
	
	m_tabPreviewSizer = new wxStaticBoxSizer( new wxStaticBox( m_tabPage, wxID_ANY, wxT("Preview") ), wxVERTICAL );
	
	m_tabPreviewSTC = new wxStyledTextCtrl( m_tabPreviewSizer->GetStaticBox(), ID_TAB_PREVIEW_STC, wxDefaultPosition, wxSize( 220,280 ), wxSTATIC_BORDER, wxEmptyString );
	m_tabPreviewSTC->SetUseTabs( false );
	m_tabPreviewSTC->SetTabWidth( 4 );
	m_tabPreviewSTC->SetIndent( 4 );
	m_tabPreviewSTC->SetTabIndents( false );
	m_tabPreviewSTC->SetBackSpaceUnIndents( false );
	m_tabPreviewSTC->SetViewEOL( false );
	m_tabPreviewSTC->SetViewWhiteSpace( false );
	m_tabPreviewSTC->SetMarginWidth( 2, 0 );
	m_tabPreviewSTC->SetIndentationGuides( false );
	m_tabPreviewSTC->SetMarginWidth( 1, 0 );
	m_tabPreviewSTC->SetMarginWidth( 0, 0 );
	m_tabPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_tabPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_tabPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_tabPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_tabPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_tabPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_tabPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_tabPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_tabPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_tabPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_tabPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_tabPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_tabPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_tabPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_tabPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_tabPreviewSTC->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_tabPreviewSTC->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	m_tabPreviewSizer->Add( m_tabPreviewSTC, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer21->Add( m_tabPreviewSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	tabSizer->Add( bSizer21, 1, wxALL|wxEXPAND, 5 );
	
	
	m_tabPage->SetSizer( tabSizer );
	m_tabPage->Layout();
	tabSizer->Fit( m_tabPage );
	m_notebook->AddSubPage( m_tabPage, wxT("Tabs/Spaces"), false );
	m_indentPage = new wxPanel( m_notebook, ID_INDENT_PAGE, wxPoint( -1,0 ), wxSize( -1,-1 ), wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
	wxBoxSizer* indentSizer;
	indentSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	m_indentSizer = new wxStaticBoxSizer( new wxStaticBox( m_indentPage, wxID_ANY, wxT("Indentation") ), wxVERTICAL );
	
	m_indentClassBlocks = new wxCheckBox( m_indentSizer->GetStaticBox(), ID_INDENT_CLASS, wxT("Indent cl&ass blocks"), wxDefaultPosition, wxDefaultSize, 0 );
	m_indentSizer->Add( m_indentClassBlocks, 0, wxALL, 5 );
	
	m_indentAccessModifiers = new wxCheckBox( m_indentSizer->GetStaticBox(), ID_INDENT_MODIFIER, wxT("Indent access modifie&rs"), wxDefaultPosition, wxDefaultSize, 0 );
	m_indentSizer->Add( m_indentAccessModifiers, 0, wxALL, 5 );
	
	m_indentSwitchBlocks = new wxCheckBox( m_indentSizer->GetStaticBox(), ID_INDENT_SWITCH, wxT("Indent &switch blocks"), wxDefaultPosition, wxDefaultSize, 0 );
	m_indentSizer->Add( m_indentSwitchBlocks, 0, wxALL, 5 );
	
	m_indentCaseBlocks = new wxCheckBox( m_indentSizer->GetStaticBox(), ID_INDENT_CASE, wxT("Indent &case blocks"), wxDefaultPosition, wxDefaultSize, 0 );
	m_indentSizer->Add( m_indentCaseBlocks, 0, wxALL, 5 );
	
	m_indentNamespaceBlocks = new wxCheckBox( m_indentSizer->GetStaticBox(), ID_INDENT_NAMESPACE, wxT("Indent na&mespace blocks"), wxDefaultPosition, wxDefaultSize, 0 );
	m_indentSizer->Add( m_indentNamespaceBlocks, 0, wxALL, 5 );
	
	m_indentAfterParens = new wxCheckBox( m_indentSizer->GetStaticBox(), ID_INDENT_AFTER_PAREN, wxT("Indent after &parens"), wxDefaultPosition, wxDefaultSize, 0 );
	m_indentSizer->Add( m_indentAfterParens, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer191;
	bSizer191 = new wxBoxSizer( wxHORIZONTAL );
	
	m_indentContinuation = new wxCheckBox( m_indentSizer->GetStaticBox(), ID_INDENT_CONTINUATION, wxT("Indent contin&uation"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer191->Add( m_indentContinuation, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_indentContinuationLength = new wxSpinCtrl( m_indentSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_WRAP, 0, 10, 0 );
	bSizer191->Add( m_indentContinuationLength, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	
	m_indentSizer->Add( bSizer191, 1, 0, 5 );
	
	m_indentGotoLabels = new wxCheckBox( m_indentSizer->GetStaticBox(), ID_INDENT_GOTO, wxT("Indent &goto labels"), wxDefaultPosition, wxDefaultSize, 0 );
	m_indentSizer->Add( m_indentGotoLabels, 0, wxALL, 5 );
	
	m_indentPreprocBlock = new wxCheckBox( m_indentSizer->GetStaticBox(), ID_INDENT_PREPROC_BLOCK, wxT("Indent preproc bloc&k"), wxDefaultPosition, wxDefaultSize, 0 );
	m_indentSizer->Add( m_indentPreprocBlock, 0, wxALL, 5 );
	
	m_indentPreprocDefine = new wxCheckBox( m_indentSizer->GetStaticBox(), ID_INDENT_PREPROC_DEFINE, wxT("Indent preproc de&fine"), wxDefaultPosition, wxDefaultSize, 0 );
	m_indentSizer->Add( m_indentPreprocDefine, 0, wxALL, 5 );
	
	m_indentPreprocConditional = new wxCheckBox( m_indentSizer->GetStaticBox(), ID_INDENT_PREPROC_COND, wxT("Indent preproc con&ditional"), wxDefaultPosition, wxDefaultSize, 0 );
	m_indentSizer->Add( m_indentPreprocConditional, 0, wxALL, 5 );
	
	m_indentCol1comments = new wxCheckBox( m_indentSizer->GetStaticBox(), ID_INDENT_COL1_COMMENT, wxT("Indent col &one comments"), wxDefaultPosition, wxDefaultSize, 0 );
	m_indentSizer->Add( m_indentCol1comments, 0, wxALL, 5 );
	
	
	m_indentSizer->Add( 0, 0, 0, wxTOP, 5 );
	
	wxStaticText* staticText6;
	staticText6 = new wxStaticText( m_indentSizer->GetStaticBox(), wxID_ANY, wxT("Mi&nimum conditional option"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText6->Wrap( -1 );
	m_indentSizer->Add( staticText6, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString m_minConditionalChoices;
	m_minConditional = new wxChoice( m_indentSizer->GetStaticBox(), ID_MIN_CONDITIONAL, wxDefaultPosition, wxDefaultSize, m_minConditionalChoices, 0 );
	m_minConditional->SetSelection( 0 );
	bSizer19->Add( m_minConditional, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer19->Add( 0, 0, 1, wxLEFT, 5 );
	
	m_minConditionalDisplay = new wxButton( m_indentSizer->GetStaticBox(), ID_MIN_CONDITIONAL_DISPLAY, wxEmptyString, wxDefaultPosition, wxSize( 17,18 ), 0 );
	bSizer19->Add( m_minConditionalDisplay, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5 );
	
	
	m_indentSizer->Add( bSizer19, 0, wxEXPAND, 5 );
	
	wxStaticText* staticText7;
	staticText7 = new wxStaticText( m_indentSizer->GetStaticBox(), wxID_ANY, wxT("Ma&ximum continuation indent"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText7->Wrap( -1 );
	m_indentSizer->Add( staticText7, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString m_maxContinuationChoices;
	m_maxContinuation = new wxChoice( m_indentSizer->GetStaticBox(), ID_MAX_CONTINUATION, wxDefaultPosition, wxDefaultSize, m_maxContinuationChoices, 0 );
	m_maxContinuation->SetSelection( 0 );
	bSizer22->Add( m_maxContinuation, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer22->Add( 0, 0, 1, wxLEFT, 5 );
	
	m_maxContinuationDisplay = new wxButton( m_indentSizer->GetStaticBox(), ID_MAX_CONTINUATION_DISPLAY, wxEmptyString, wxDefaultPosition, wxSize( 17,18 ), 0 );
	bSizer22->Add( m_maxContinuationDisplay, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5 );
	
	
	m_indentSizer->Add( bSizer22, 0, wxEXPAND, 5 );
	
	
	bSizer18->Add( m_indentSizer, 1, wxALL|wxEXPAND, 5 );
	
	m_indentPreviewSizer = new wxStaticBoxSizer( new wxStaticBox( m_indentPage, wxID_ANY, wxT("Preview") ), wxVERTICAL );
	
	m_indentPreviewSTC = new wxStyledTextCtrl( m_indentPreviewSizer->GetStaticBox(), ID_INDENT_PREVIEW_STC, wxDefaultPosition, wxSize( 220,280 ), wxSTATIC_BORDER, wxEmptyString );
	m_indentPreviewSTC->SetUseTabs( false );
	m_indentPreviewSTC->SetTabWidth( 4 );
	m_indentPreviewSTC->SetIndent( 4 );
	m_indentPreviewSTC->SetTabIndents( false );
	m_indentPreviewSTC->SetBackSpaceUnIndents( false );
	m_indentPreviewSTC->SetViewEOL( false );
	m_indentPreviewSTC->SetViewWhiteSpace( false );
	m_indentPreviewSTC->SetMarginWidth( 2, 0 );
	m_indentPreviewSTC->SetIndentationGuides( false );
	m_indentPreviewSTC->SetMarginWidth( 1, 0 );
	m_indentPreviewSTC->SetMarginWidth( 0, 0 );
	m_indentPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_indentPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_indentPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_indentPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_indentPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_indentPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_indentPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_indentPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_indentPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_indentPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_indentPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_indentPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_indentPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_indentPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_indentPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_indentPreviewSTC->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_indentPreviewSTC->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	m_indentPreviewSizer->Add( m_indentPreviewSTC, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer18->Add( m_indentPreviewSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	indentSizer->Add( bSizer18, 1, wxALL|wxEXPAND, 5 );
	
	
	m_indentPage->SetSizer( indentSizer );
	m_indentPage->Layout();
	indentSizer->Fit( m_indentPage );
	m_notebook->AddSubPage( m_indentPage, wxT("Indentation"), true );
	m_padPage = new wxPanel( m_notebook, ID_PAD_PAGE, wxPoint( -1,0 ), wxDefaultSize, wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
	wxBoxSizer* padSizer;
	padSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	m_padSizer = new wxStaticBoxSizer( new wxStaticBox( m_padPage, wxID_ANY, wxT("Padding") ), wxVERTICAL );
	
	m_breakHeaderBlocks = new wxCheckBox( m_padSizer->GetStaticBox(), ID_BREAK_HEADER, wxT("Break header &blocks"), wxDefaultPosition, wxDefaultSize, 0 );
	m_padSizer->Add( m_breakHeaderBlocks, 0, wxALL, 5 );
	
	m_breakAllBlocks = new wxCheckBox( m_padSizer->GetStaticBox(), ID_BREAK_ALL, wxT("Break &all blocks"), wxDefaultPosition, wxDefaultSize, 0 );
	m_padSizer->Add( m_breakAllBlocks, 0, wxALL, 5 );
	
	m_padOperator = new wxCheckBox( m_padSizer->GetStaticBox(), ID_PAD_OPERATOR, wxT("Pad o&perator"), wxDefaultPosition, wxDefaultSize, 0 );
	m_padSizer->Add( m_padOperator, 0, wxALL, 5 );
	
	m_padComma = new wxCheckBox( m_padSizer->GetStaticBox(), ID_PAD_COMMA, wxT("Pad comma"), wxDefaultPosition, wxDefaultSize, 0 );
	m_padSizer->Add( m_padComma, 0, wxALL, 5 );
	
	m_padParenOutside = new wxCheckBox( m_padSizer->GetStaticBox(), ID_PAD_PAREN_OUT, wxT("Pad paren &outside"), wxDefaultPosition, wxDefaultSize, 0 );
	m_padSizer->Add( m_padParenOutside, 0, wxALL, 5 );
	
	m_padParenInside = new wxCheckBox( m_padSizer->GetStaticBox(), ID_PAD_PAREN_IN, wxT("Pad paren &inside"), wxDefaultPosition, wxDefaultSize, 0 );
	m_padSizer->Add( m_padParenInside, 0, wxALL, 5 );
	
	m_padFirstParenOut = new wxCheckBox( m_padSizer->GetStaticBox(), ID_PAD_FIRST_PAREN_OUT, wxT("Pad fi&rst paren outside"), wxDefaultPosition, wxDefaultSize, 0 );
	m_padSizer->Add( m_padFirstParenOut, 0, wxALL, 5 );
	
	m_padHeader = new wxCheckBox( m_padSizer->GetStaticBox(), ID_PAD_HEADER, wxT("Pad &header"), wxDefaultPosition, wxDefaultSize, 0 );
	m_padSizer->Add( m_padHeader, 0, wxALL, 5 );
	
	m_unpadParen = new wxCheckBox( m_padSizer->GetStaticBox(), ID_UNPAD_PAREN, wxT("U&npad paren"), wxDefaultPosition, wxDefaultSize, 0 );
	m_padSizer->Add( m_unpadParen, 0, wxALL, 5 );
	
	m_deleteEmptyLines = new wxCheckBox( m_padSizer->GetStaticBox(), ID_DELETE_EMPTY_LINE, wxT("&Delete empty lines"), wxDefaultPosition, wxDefaultSize, 0 );
	m_padSizer->Add( m_deleteEmptyLines, 0, wxALL, 5 );
	
	m_fillEmptyLines = new wxCheckBox( m_padSizer->GetStaticBox(), ID_FILL_EMPTY_LINE, wxT("&Fill empty lines"), wxDefaultPosition, wxDefaultSize, 0 );
	m_padSizer->Add( m_fillEmptyLines, 0, wxALL, 5 );
	
	
	m_padSizer->Add( 0, 0, 0, wxTOP, 5 );
	
	wxStaticText* staticText10;
	staticText10 = new wxStaticText( m_padSizer->GetStaticBox(), wxID_ANY, wxT("Align poin&ter"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText10->Wrap( -1 );
	m_padSizer->Add( staticText10, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString m_alignPointerChoices;
	m_alignPointer = new wxChoice( m_padSizer->GetStaticBox(), ID_ALIGN_POINTER, wxDefaultPosition, wxDefaultSize, m_alignPointerChoices, 0 );
	m_alignPointer->SetSelection( 0 );
	bSizer24->Add( m_alignPointer, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer24->Add( 0, 0, 1, wxLEFT, 5 );
	
	m_alignPointerDisplay = new wxButton( m_padSizer->GetStaticBox(), ID_ALIGN_POINTER_DISPLAY, wxEmptyString, wxDefaultPosition, wxSize( 17,18 ), 0 );
	bSizer24->Add( m_alignPointerDisplay, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5 );
	
	
	m_padSizer->Add( bSizer24, 0, wxEXPAND, 5 );
	
	wxStaticText* staticText11;
	staticText11 = new wxStaticText( m_padSizer->GetStaticBox(), wxID_ANY, wxT("Align &reference"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText11->Wrap( -1 );
	m_padSizer->Add( staticText11, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer241;
	bSizer241 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString m_alignReferenceChoices;
	m_alignReference = new wxChoice( m_padSizer->GetStaticBox(), ID_ALIGN_REFERENCE, wxDefaultPosition, wxDefaultSize, m_alignReferenceChoices, 0 );
	m_alignReference->SetSelection( 0 );
	bSizer241->Add( m_alignReference, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer241->Add( 0, 0, 1, wxLEFT, 5 );
	
	m_alignReferenceDisplay = new wxButton( m_padSizer->GetStaticBox(), ID_ALIGN_REFERENCE_DISPLAY, wxEmptyString, wxDefaultPosition, wxSize( 17,18 ), 0 );
	bSizer241->Add( m_alignReferenceDisplay, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5 );
	
	
	m_padSizer->Add( bSizer241, 0, wxEXPAND, 5 );
	
	
	m_padSizer->Add( 0, 0, 0, wxTOP, 5 );
	
	
	bSizer11->Add( m_padSizer, 1, wxALL|wxEXPAND, 5 );
	
	m_padPreviewSizer = new wxStaticBoxSizer( new wxStaticBox( m_padPage, wxID_ANY, wxT("Preview") ), wxVERTICAL );
	
	m_padPreviewSTC = new wxStyledTextCtrl( m_padPreviewSizer->GetStaticBox(), ID_PAD_PREVIEW_STC, wxDefaultPosition, wxSize( 220,280 ), wxSTATIC_BORDER, wxEmptyString );
	m_padPreviewSTC->SetUseTabs( false );
	m_padPreviewSTC->SetTabWidth( 4 );
	m_padPreviewSTC->SetIndent( 4 );
	m_padPreviewSTC->SetTabIndents( false );
	m_padPreviewSTC->SetBackSpaceUnIndents( false );
	m_padPreviewSTC->SetViewEOL( false );
	m_padPreviewSTC->SetViewWhiteSpace( false );
	m_padPreviewSTC->SetMarginWidth( 2, 0 );
	m_padPreviewSTC->SetIndentationGuides( false );
	m_padPreviewSTC->SetMarginWidth( 1, 0 );
	m_padPreviewSTC->SetMarginWidth( 0, 0 );
	m_padPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_padPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_padPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_padPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_padPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_padPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_padPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_padPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_padPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_padPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_padPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_padPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_padPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_padPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_padPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_padPreviewSTC->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_padPreviewSTC->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	m_padPreviewSizer->Add( m_padPreviewSTC, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer11->Add( m_padPreviewSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	padSizer->Add( bSizer11, 1, wxALL|wxEXPAND, 5 );
	
	
	m_padPage->SetSizer( padSizer );
	m_padPage->Layout();
	padSizer->Fit( m_padPage );
	m_notebook->AddSubPage( m_padPage, wxT("Padding"), false );
	m_formatPage = new wxPanel( m_notebook, ID_FOMAT_PAGE, wxPoint( -1,0 ), wxDefaultSize, wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
	wxBoxSizer* formatSizer;
	formatSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_formatSizer = new wxStaticBoxSizer( new wxStaticBox( m_formatPage, wxID_ANY, wxT("Formatting") ), wxVERTICAL );
	
	m_breakClosingBraces = new wxCheckBox( m_formatSizer->GetStaticBox(), ID_BREAK_CLOSING, wxT("Break &closing braces"), wxDefaultPosition, wxDefaultSize, 0 );
	m_formatSizer->Add( m_breakClosingBraces, 0, wxALL, 5 );
	
	m_breakElseIf = new wxCheckBox( m_formatSizer->GetStaticBox(), ID_BREAK_ELSEIF, wxT("Break &else/if statements"), wxDefaultPosition, wxDefaultSize, 0 );
	m_formatSizer->Add( m_breakElseIf, 0, wxALL, 5 );
	
	m_breakOneLineHeaders = new wxCheckBox( m_formatSizer->GetStaticBox(), ID_BREAK_OL_HEADERS, wxT("Break one line &headers"), wxDefaultPosition, wxDefaultSize, 0 );
	m_formatSizer->Add( m_breakOneLineHeaders, 0, wxALL, 5 );
	
	m_addBraces = new wxCheckBox( m_formatSizer->GetStaticBox(), ID_ADD_BRACES, wxT("&Add braces"), wxDefaultPosition, wxDefaultSize, 0 );
	m_formatSizer->Add( m_addBraces, 0, wxALL, 5 );
	
	m_addOneLineBraces = new wxCheckBox( m_formatSizer->GetStaticBox(), ID_ADD_OL_BRACES, wxT("Add &one line braces"), wxDefaultPosition, wxDefaultSize, 0 );
	m_formatSizer->Add( m_addOneLineBraces, 0, wxALL, 5 );
	
	m_removeBraces = new wxCheckBox( m_formatSizer->GetStaticBox(), ID_REMOVE_BRACES, wxT("&Remove braces"), wxDefaultPosition, wxDefaultSize, 0 );
	m_formatSizer->Add( m_removeBraces, 0, wxALL, 5 );
	
	m_keepOneLineBlocks = new wxCheckBox( m_formatSizer->GetStaticBox(), ID_KEEP_OL_BLOCKS, wxT("Keep one line &blocks"), wxDefaultPosition, wxDefaultSize, 0 );
	m_formatSizer->Add( m_keepOneLineBlocks, 0, wxALL, 5 );
	
	m_keepOneLineStatements = new wxCheckBox( m_formatSizer->GetStaticBox(), ID_KEEP_OL_STATEMENTS, wxT("Keep one line &statements"), wxDefaultPosition, wxDefaultSize, 0 );
	m_formatSizer->Add( m_keepOneLineStatements, 0, wxALL, 5 );
	
	m_convertTabs = new wxCheckBox( m_formatSizer->GetStaticBox(), ID_CONVERT_TABS, wxT("Convert &tabs"), wxDefaultPosition, wxDefaultSize, 0 );
	m_formatSizer->Add( m_convertTabs, 0, wxALL, 5 );
	
	m_closeTemplates = new wxCheckBox( m_formatSizer->GetStaticBox(), ID_CLOSE_TEMPLATES, wxT("Close tem&plates"), wxDefaultPosition, wxDefaultSize, 0 );
	m_formatSizer->Add( m_closeTemplates, 0, wxALL, 5 );
	
	m_removeCommentPrefix = new wxCheckBox( m_formatSizer->GetStaticBox(), ID_REMOVE_COMMENT_PREFIX, wxT("Remove co&mment prefix"), wxDefaultPosition, wxDefaultSize, 0 );
	m_formatSizer->Add( m_removeCommentPrefix, 0, wxALL, 5 );
	
	
	m_formatSizer->Add( 0, 0, 0, wxTOP, 5 );
	
	wxStaticText* staticText12;
	staticText12 = new wxStaticText( m_formatSizer->GetStaticBox(), wxID_ANY, wxT("&Maximum code length"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText12->Wrap( -1 );
	m_formatSizer->Add( staticText12, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer212;
	bSizer212 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString m_maxCodeLengthChoices;
	m_maxCodeLength = new wxChoice( m_formatSizer->GetStaticBox(), ID_MAX_CODE_LENGTH, wxDefaultPosition, wxDefaultSize, m_maxCodeLengthChoices, 0 );
	m_maxCodeLength->SetSelection( 0 );
	bSizer212->Add( m_maxCodeLength, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer212->Add( 0, 0, 1, wxLEFT, 5 );
	
	m_maxCodeLengthDisplay = new wxButton( m_formatSizer->GetStaticBox(), ID_MAX_CODE_LENGTH_DISPLAY, wxEmptyString, wxDefaultPosition, wxSize( 17,18 ), 0 );
	bSizer212->Add( m_maxCodeLengthDisplay, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5 );
	
	
	m_formatSizer->Add( bSizer212, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_breakAfterLogicalSizer;
	m_breakAfterLogicalSizer = new wxBoxSizer( wxVERTICAL );
	
	m_breakAfterLogical = new wxCheckBox( m_formatSizer->GetStaticBox(), ID_BREAK_AFTER_LOGICAL, wxT("Brea&k after logical"), wxDefaultPosition, wxDefaultSize, 0 );
	m_breakAfterLogicalSizer->Add( m_breakAfterLogical, 0, wxALL, 5 );
	
	
	m_formatSizer->Add( m_breakAfterLogicalSizer, 0, wxLEFT, 20 );
	
	
	bSizer12->Add( m_formatSizer, 1, wxALL|wxEXPAND, 5 );
	
	m_formatPreviewSizer = new wxStaticBoxSizer( new wxStaticBox( m_formatPage, wxID_ANY, wxT("Preview") ), wxVERTICAL );
	
	m_formatPreviewSTC = new wxStyledTextCtrl( m_formatPreviewSizer->GetStaticBox(), ID_FORMAT_PREVIEW_STC, wxDefaultPosition, wxSize( 220,280 ), wxSTATIC_BORDER, wxEmptyString );
	m_formatPreviewSTC->SetUseTabs( false );
	m_formatPreviewSTC->SetTabWidth( 4 );
	m_formatPreviewSTC->SetIndent( 4 );
	m_formatPreviewSTC->SetTabIndents( false );
	m_formatPreviewSTC->SetBackSpaceUnIndents( false );
	m_formatPreviewSTC->SetViewEOL( false );
	m_formatPreviewSTC->SetViewWhiteSpace( false );
	m_formatPreviewSTC->SetMarginWidth( 2, 0 );
	m_formatPreviewSTC->SetIndentationGuides( false );
	m_formatPreviewSTC->SetMarginWidth( 1, 0 );
	m_formatPreviewSTC->SetMarginWidth( 0, 0 );
	m_formatPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_formatPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_formatPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_formatPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_formatPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_formatPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_formatPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_formatPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_formatPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_formatPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_formatPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_formatPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_formatPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_formatPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_formatPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_formatPreviewSTC->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_formatPreviewSTC->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	m_formatPreviewSizer->Add( m_formatPreviewSTC, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer12->Add( m_formatPreviewSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	formatSizer->Add( bSizer12, 1, wxALL|wxEXPAND, 5 );
	
	
	m_formatPage->SetSizer( formatSizer );
	m_formatPage->Layout();
	formatSizer->Fit( m_formatPage );
	m_notebook->AddSubPage( m_formatPage, wxT("Formatting"), false );
	m_otherPage = new wxPanel( m_notebook, ID_OTHER_PAGE, wxPoint( -1,0 ), wxDefaultSize, wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
	wxBoxSizer* otherSizer;
	otherSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxHORIZONTAL );
	
	m_otherSizer = new wxStaticBoxSizer( new wxStaticBox( m_otherPage, wxID_ANY, wxT("Objective-C") ), wxVERTICAL );
	
	m_padMethodPrefix = new wxCheckBox( m_otherSizer->GetStaticBox(), ID_PAD_METHOD_PREFIX, wxT("Pad method &prefix"), wxDefaultPosition, wxDefaultSize, 0 );
	m_otherSizer->Add( m_padMethodPrefix, 0, wxALL, 5 );
	
	m_unpadMethodPrefix = new wxCheckBox( m_otherSizer->GetStaticBox(), ID_UNPAD_METHOD_PREFIX, wxT("Unpad method p&refix"), wxDefaultPosition, wxDefaultSize, 0 );
	m_otherSizer->Add( m_unpadMethodPrefix, 0, wxALL, 5 );
	
	m_padReturnType = new wxCheckBox( m_otherSizer->GetStaticBox(), ID_PAD_RETURN_TYPE, wxT("Pad return &type"), wxDefaultPosition, wxDefaultSize, 0 );
	m_otherSizer->Add( m_padReturnType, 0, wxALL, 5 );
	
	m_unpadReturnType = new wxCheckBox( m_otherSizer->GetStaticBox(), ID_UNPAD_RETURN_TYPE, wxT("Unpad return t&ype"), wxDefaultPosition, wxDefaultSize, 0 );
	m_otherSizer->Add( m_unpadReturnType, 0, wxALL, 5 );
	
	m_padParamType = new wxCheckBox( m_otherSizer->GetStaticBox(), ID_PAD_PARAM_TYPE, wxT("Pad param &type"), wxDefaultPosition, wxDefaultSize, 0 );
	m_padParamType->SetValue(true); 
	m_otherSizer->Add( m_padParamType, 0, wxALL, 5 );
	
	m_unpadParamType = new wxCheckBox( m_otherSizer->GetStaticBox(), ID_UNPAD_PARAM_TYPE, wxT("Unpad param t&ype"), wxDefaultPosition, wxDefaultSize, 0 );
	m_otherSizer->Add( m_unpadParamType, 0, wxALL, 5 );
	
	m_alignMethodColon = new wxCheckBox( m_otherSizer->GetStaticBox(), ID_ALIGN_METHOD_COLON, wxT("Align &method colons"), wxDefaultPosition, wxDefaultSize, 0 );
	m_otherSizer->Add( m_alignMethodColon, 0, wxALL, 5 );
	
	
	m_otherSizer->Add( 0, 0, 0, wxTOP, 5 );
	
	wxStaticText* staticText121;
	staticText121 = new wxStaticText( m_otherSizer->GetStaticBox(), wxID_ANY, wxT("Pad method &colons"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText121->Wrap( -1 );
	m_otherSizer->Add( staticText121, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer261;
	bSizer261 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString m_padMethodColonChoices;
	m_padMethodColon = new wxChoice( m_otherSizer->GetStaticBox(), ID_PAD_METHOD_COLON, wxDefaultPosition, wxDefaultSize, m_padMethodColonChoices, 0 );
	m_padMethodColon->SetSelection( 0 );
	bSizer261->Add( m_padMethodColon, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer261->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_padMethodColonDisplay = new wxButton( m_otherSizer->GetStaticBox(), ID_PAD_METHOD_COLON_DISPLAY, wxEmptyString, wxDefaultPosition, wxSize( 17,18 ), 0 );
	bSizer261->Add( m_padMethodColonDisplay, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5 );
	
	
	m_otherSizer->Add( bSizer261, 0, wxEXPAND, 5 );
	
	
	bSizer121->Add( m_otherSizer, 1, wxALL|wxEXPAND, 5 );
	
	m_otherPreviewSizer = new wxStaticBoxSizer( new wxStaticBox( m_otherPage, wxID_ANY, wxT("Preview") ), wxVERTICAL );
	
	m_otherPreviewSTC = new wxStyledTextCtrl( m_otherPreviewSizer->GetStaticBox(), ID_OTHER_PREVIEW_STC, wxDefaultPosition, wxSize( 220,280 ), wxSTATIC_BORDER, wxEmptyString );
	m_otherPreviewSTC->SetUseTabs( false );
	m_otherPreviewSTC->SetTabWidth( 4 );
	m_otherPreviewSTC->SetIndent( 4 );
	m_otherPreviewSTC->SetTabIndents( false );
	m_otherPreviewSTC->SetBackSpaceUnIndents( false );
	m_otherPreviewSTC->SetViewEOL( false );
	m_otherPreviewSTC->SetViewWhiteSpace( false );
	m_otherPreviewSTC->SetMarginWidth( 2, 0 );
	m_otherPreviewSTC->SetIndentationGuides( false );
	m_otherPreviewSTC->SetMarginWidth( 1, 0 );
	m_otherPreviewSTC->SetMarginWidth( 0, 0 );
	m_otherPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_otherPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_otherPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_otherPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_otherPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_otherPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_otherPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_otherPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_otherPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_otherPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_otherPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_otherPreviewSTC->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_otherPreviewSTC->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_otherPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_otherPreviewSTC->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_otherPreviewSTC->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_otherPreviewSTC->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	m_otherPreviewSizer->Add( m_otherPreviewSTC, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer121->Add( m_otherPreviewSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	otherSizer->Add( bSizer121, 1, wxALL|wxEXPAND, 5 );
	
	
	m_otherPage->SetSizer( otherSizer );
	m_otherPage->Layout();
	otherSizer->Fit( m_otherPage );
	m_notebook->AddSubPage( m_otherPage, wxT("Objective-C"), false );
	
	notebookSizer->Add( m_notebook, 1, wxEXPAND | wxALL, 5 );
	
	
	m_astyleDlgSizer->Add( notebookSizer, 0, wxEXPAND, 5 );
	
	wxBoxSizer* buttonSizer;
	buttonSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_resetAllButton = new wxButton( this, ID_RESET_ALL, wxT("Reset All"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( m_resetAllButton, 0, wxALL, 5 );
	
	m_newSettings = new wxButton( this, ID_NEW_SETTINGS, wxT("New Settings"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( m_newSettings, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );
	
	m_sdbSizer = new wxStdDialogButtonSizer();
	m_sdbSizerOK = new wxButton( this, wxID_OK );
	m_sdbSizer->AddButton( m_sdbSizerOK );
	m_sdbSizerCancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer->AddButton( m_sdbSizerCancel );
	m_sdbSizer->Realize();
	
	bSizer17->Add( m_sdbSizer, 0, wxALL|wxEXPAND, 5 );
	
	
	buttonSizer->Add( bSizer17, 1, wxEXPAND, 5 );
	
	
	m_astyleDlgSizer->Add( buttonSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( m_astyleDlgSizer );
	this->Layout();
	m_astyleDlgSizer->Fit( this );
	
	this->Centre( wxBOTH );
}

AStyleDlgBase::~AStyleDlgBase()
{
}
