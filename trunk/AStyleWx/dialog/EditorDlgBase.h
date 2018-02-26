///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __EDITORDLGBASE_H__
#define __EDITORDLGBASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/listbox.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class EditorDlgBase
///////////////////////////////////////////////////////////////////////////////
class EditorDlgBase : public wxDialog 
{
	DECLARE_EVENT_TABLE()
	private:
		
		// Private event handlers
		void _wxFB_OnNotebookPageChanged( wxNotebookEvent& event ){ OnNotebookPageChanged( event ); }
		void _wxFB_OnListboxSelected( wxCommandEvent& event ){ OnListboxSelected( event ); }
		void _wxFB_OnBoldClick( wxCommandEvent& event ){ OnBoldClick( event ); }
		void _wxFB_OnItalicClick( wxCommandEvent& event ){ OnItalicClick( event ); }
		void _wxFB_OnResetClick( wxCommandEvent& event ){ OnResetClick( event ); }
		
	
	protected:
		enum
		{
			ID_EDITOR_DLG = 1000,
			ID_EDITOR_NOTEBOOK,
			ID_OPTIONS_PAGE,
			ID_USE_BOTTOM_TABS,
			ID_USE_SMALL_TOOLBAR,
			ID_TOOLBAR_TOOLTIPS,
			ID_DIALOG_TOOLTIPS,
			ID_LOAD_SESSION,
			ID_HIDE_FIND,
			ID_WRAP_SEARCH,
			ID_FONTS_PAGE,
			ID_DEFAULT_FONTS,
			ID_DEFAULT_SIZES,
			ID_COMMENT_FONTS,
			ID_COMMENT_SIZES,
			ID_STYLES_PAGE,
			ID_STYLES,
			ID_FOREGROUND,
			ID_BOLD,
			ID_ITALIC
		};
		
		wxBoxSizer* m_editorDlgSizer;
		wxNotebook* m_notebook;
		wxPanel* m_optionsPage;
		wxCheckBox* m_useBottomTabs;
		wxCheckBox* m_useSmallToolbar;
		wxCheckBox* m_showToolbarTooltips;
		wxCheckBox* m_showDialogTooltips;
		wxCheckBox* m_loadSession;
		wxCheckBox* m_hideFind;
		wxCheckBox* m_wrapSearch;
		wxPanel* m_fontsPage;
		wxStaticText* m_defaultHeader;
		wxComboBox* m_defaultFonts;
		wxComboBox* m_defaultSizes;
		wxStaticText* m_commentHeader;
		wxComboBox* m_commentFonts;
		wxComboBox* m_commentSizes;
		wxPanel* m_stylesPage;
		wxListBox* m_styles;
		wxPanel* m_foreground;
		wxCheckBox* m_bold;
		wxCheckBox* m_italic;
		wxButton* m_reset ;
		wxStdDialogButtonSizer* m_sdbSizer;
		wxButton* m_sdbSizerOK;
		wxButton* m_sdbSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnNotebookPageChanged( wxNotebookEvent& event ) { event.Skip(); }
		virtual void OnListboxSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBoldClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnItalicClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnResetClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		EditorDlgBase( wxWindow* parent, wxWindowID id = ID_EDITOR_DLG, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~EditorDlgBase();
	
};

#endif //__EDITORDLGBASE_H__
