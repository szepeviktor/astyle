///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ASTYLEDLGBASE_H__
#define __ASTYLEDLGBASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stc/stc.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/treebook.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define ID_ASTYLE_DLG 1000
#define ID_ASTYLE_NOTEBOOK 1001
#define ID_STYLE_PAGE 1002
#define ID_STYLE_NONE 1003
#define ID_STYLE_ALLMAN 1004
#define ID_STYLE_JAVA 1005
#define ID_STYLE_KR 1006
#define ID_STYLE_STROUSTRUP 1007
#define ID_STYLE_WHITESMITH 1008
#define ID_STYLE_VTK 1009
#define ID_STYLE_BANNER 1010
#define ID_STYLE_GNU 1011
#define ID_STYLE_LINUX 1012
#define ID_STYLE_HORSTMANN 1013
#define ID_STYLE_1TBS 1014
#define ID_STYLE_GOOGLE 1015
#define ID_STYLE_MOZILLA 1016
#define ID_STYLE_PICO 1017
#define ID_STYLE_LISP 1018
#define ID_STYLE_PREVIEW_STC 1019
#define ID_TABS_PAGE 1020
#define ID_INDENTWITH_SPACE 1021
#define ID_INDENTWITH_TAB 1022
#define ID_INDENTWITH_FTAB 1023
#define ID_USE_TAB_LENGTH 1024
#define ID_TAB_LENGTH 1025
#define ID_INDENT_LENGTH 1026
#define ID_INDENT_LENGTH_DISPLAY 1027
#define ID_ATTACH_NAMESPACE 1028
#define ID_ATTACH_CLASS 1029
#define ID_ATTACH_INLINE 1030
#define ID_ATTACH_EXTERN_C 1031
#define ID_ATTACH_CLOSING_WHILE 1032
#define ID_TAB_PREVIEW_STC 1033
#define ID_INDENT_PAGE 1034
#define ID_INDENT_CLASS 1035
#define ID_INDENT_MODIFIER 1036
#define ID_INDENT_SWITCH 1037
#define ID_INDENT_CASE 1038
#define ID_INDENT_NAMESPACE 1039
#define ID_INDENT_AFTER_PAREN 1040
#define ID_INDENT_CONTINUATION 1041
#define ID_INDENT_GOTO 1042
#define ID_INDENT_PREPROC_BLOCK 1043
#define ID_INDENT_PREPROC_DEFINE 1044
#define ID_INDENT_PREPROC_COND 1045
#define ID_INDENT_COL1_COMMENT 1046
#define ID_MIN_CONDITIONAL 1047
#define ID_MIN_CONDITIONAL_DISPLAY 1048
#define ID_MAX_CONTINUATION 1049
#define ID_MAX_CONTINUATION_DISPLAY 1050
#define ID_INDENT_PREVIEW_STC 1051
#define ID_PAD_PAGE 1052
#define ID_BREAK_HEADER 1053
#define ID_BREAK_ALL 1054
#define ID_PAD_OPERATOR 1055
#define ID_PAD_COMMA 1056
#define ID_PAD_PAREN_OUT 1057
#define ID_PAD_PAREN_IN 1058
#define ID_PAD_FIRST_PAREN_OUT 1059
#define ID_PAD_HEADER 1060
#define ID_UNPAD_PAREN 1061
#define ID_DELETE_EMPTY_LINE 1062
#define ID_FILL_EMPTY_LINE 1063
#define ID_ALIGN_POINTER 1064
#define ID_ALIGN_POINTER_DISPLAY 1065
#define ID_ALIGN_REFERENCE 1066
#define ID_ALIGN_REFERENCE_DISPLAY 1067
#define ID_PAD_PREVIEW_STC 1068
#define ID_FOMAT_PAGE 1069
#define ID_BREAK_CLOSING 1070
#define ID_BREAK_ELSEIF 1071
#define ID_BREAK_OL_HEADERS 1072
#define ID_ADD_BRACES 1073
#define ID_ADD_OL_BRACES 1074
#define ID_REMOVE_BRACES 1075
#define ID_KEEP_OL_BLOCKS 1076
#define ID_KEEP_OL_STATEMENTS 1077
#define ID_CONVERT_TABS 1078
#define ID_CLOSE_TEMPLATES 1079
#define ID_REMOVE_COMMENT_PREFIX 1080
#define ID_MAX_CODE_LENGTH 1081
#define ID_MAX_CODE_LENGTH_DISPLAY 1082
#define ID_BREAK_AFTER_LOGICAL 1083
#define ID_FORMAT_PREVIEW_STC 1084
#define ID_OTHER_PAGE 1085
#define ID_PAD_METHOD_PREFIX 1086
#define ID_UNPAD_METHOD_PREFIX 1087
#define ID_PAD_RETURN_TYPE 1088
#define ID_UNPAD_RETURN_TYPE 1089
#define ID_PAD_PARAM_TYPE 1090
#define ID_UNPAD_PARAM_TYPE 1091
#define ID_ALIGN_METHOD_COLON 1092
#define ID_PAD_METHOD_COLON 1093
#define ID_PAD_METHOD_COLON_DISPLAY 1094
#define ID_OTHER_PREVIEW_STC 1095
#define ID_RESET_ALL 1096
#define ID_NEW_SETTINGS 1097

///////////////////////////////////////////////////////////////////////////////
/// Class AStyleDlgBase
///////////////////////////////////////////////////////////////////////////////
class AStyleDlgBase : public wxDialog 
{
	DECLARE_EVENT_TABLE()
	private:
		
		// Private event handlers
		void _wxFB_OnNotebookPageChanged( wxTreebookEvent& event ){ OnNotebookPageChanged( event ); }
		void _wxFB_OnStyleClick( wxCommandEvent& event ){ OnStyleClick( event ); }
		void _wxFB_OnTabClick( wxCommandEvent& event ){ OnTabClick( event ); }
		void _wxFB_OnModifierClick( wxCommandEvent& event ){ OnModifierClick( event ); }
		void _wxFB_OnIndentClick( wxCommandEvent& event ){ OnIndentClick( event ); }
		void _wxFB_OnPadClick( wxCommandEvent& event ){ OnPadClick( event ); }
		void _wxFB_OnFormatClick( wxCommandEvent& event ){ OnFormatClick( event ); }
		void _wxFB_OnOtherClick( wxCommandEvent& event ){ OnOtherClick( event ); }
		void _wxFB_OnResetAllClick( wxCommandEvent& event ){ OnResetAllClick( event ); }
		void _wxFB_OnSettingsClick( wxCommandEvent& event ){ OnSettingsClick( event ); }
		void _wxFB_OnOkClick( wxCommandEvent& event ){ OnOkClick( event ); }
		
	
	protected:
		wxBoxSizer* m_astyleDlgSizer;
		wxTreebook* m_notebook;
		wxPanel* m_stylePage;
		wxStaticBoxSizer* m_styleSizer;
		wxRadioButton* m_styleNone;
		wxRadioButton* m_styleAllman;
		wxRadioButton* m_styleJava;
		wxRadioButton* m_styleKR;
		wxRadioButton* m_styleStroustrup;
		wxRadioButton* m_styleWhitesmith;
		wxRadioButton* m_styleVtk;
		wxRadioButton* m_styleBanner;
		wxRadioButton* m_styleGnu;
		wxRadioButton* m_styleLinux;
		wxRadioButton* m_styleHorstmann;
		wxRadioButton* m_style1tbs;
		wxRadioButton* m_styleGoogle;
		wxRadioButton* m_styleMozilla;
		wxRadioButton* m_stylePico;
		wxRadioButton* m_styleLisp;
		wxStaticBoxSizer* m_stylePreviewSizer;
		wxStyledTextCtrl* m_stylePreviewSTC;
		wxPanel* m_tabPage;
		wxStaticBoxSizer* m_tabSizer;
		wxRadioButton* m_spaceIndent;
		wxRadioButton* m_tabIndent;
		wxRadioButton* m_forceTabIndent;
		wxCheckBox* m_useTabLength;
		wxSpinCtrl* m_tabLength;
		wxStaticText* m_indentLengthText;
		wxSpinCtrl* m_indentLength;
		wxButton* m_indentLengthlDisplay;
		wxStaticBoxSizer* m_modifySizer;
		wxCheckBox* m_attachNamespace;
		wxCheckBox* m_attachClass;
		wxCheckBox* m_attachInline;
		wxCheckBox* m_attachExternC;
		wxCheckBox* m_attachClosingWhile;
		wxStaticBoxSizer* m_tabPreviewSizer;
		wxStyledTextCtrl* m_tabPreviewSTC;
		wxPanel* m_indentPage;
		wxStaticBoxSizer* m_indentSizer;
		wxCheckBox* m_indentClassBlocks;
		wxCheckBox* m_indentAccessModifiers;
		wxCheckBox* m_indentSwitchBlocks;
		wxCheckBox* m_indentCaseBlocks;
		wxCheckBox* m_indentNamespaceBlocks;
		wxCheckBox* m_indentAfterParens;
		wxCheckBox* m_indentContinuation;
		wxSpinCtrl* m_indentContinuationLength;
		wxCheckBox* m_indentGotoLabels;
		wxCheckBox* m_indentPreprocBlock;
		wxCheckBox* m_indentPreprocDefine;
		wxCheckBox* m_indentPreprocConditional;
		wxCheckBox* m_indentCol1comments;
		wxChoice* m_minConditional;
		wxButton* m_minConditionalDisplay;
		wxChoice* m_maxContinuation;
		wxButton* m_maxContinuationDisplay;
		wxStaticBoxSizer* m_indentPreviewSizer;
		wxStyledTextCtrl* m_indentPreviewSTC;
		wxPanel* m_padPage;
		wxStaticBoxSizer* m_padSizer;
		wxCheckBox* m_breakHeaderBlocks;
		wxCheckBox* m_breakAllBlocks;
		wxCheckBox* m_padOperator;
		wxCheckBox* m_padComma;
		wxCheckBox* m_padParenOutside;
		wxCheckBox* m_padParenInside;
		wxCheckBox* m_padFirstParenOut;
		wxCheckBox* m_padHeader;
		wxCheckBox* m_unpadParen;
		wxCheckBox* m_deleteEmptyLines;
		wxCheckBox* m_fillEmptyLines;
		wxChoice* m_alignPointer;
		wxButton* m_alignPointerDisplay;
		wxChoice* m_alignReference;
		wxButton* m_alignReferenceDisplay;
		wxStaticBoxSizer* m_padPreviewSizer;
		wxStyledTextCtrl* m_padPreviewSTC;
		wxPanel* m_formatPage;
		wxStaticBoxSizer* m_formatSizer;
		wxCheckBox* m_breakClosingBraces;
		wxCheckBox* m_breakElseIf;
		wxCheckBox* m_breakOneLineHeaders;
		wxCheckBox* m_addBraces;
		wxCheckBox* m_addOneLineBraces;
		wxCheckBox* m_removeBraces;
		wxCheckBox* m_keepOneLineBlocks;
		wxCheckBox* m_keepOneLineStatements;
		wxCheckBox* m_convertTabs;
		wxCheckBox* m_closeTemplates;
		wxCheckBox* m_removeCommentPrefix;
		wxChoice* m_maxCodeLength;
		wxButton* m_maxCodeLengthDisplay;
		wxCheckBox* m_breakAfterLogical;
		wxStaticBoxSizer* m_formatPreviewSizer;
		wxStyledTextCtrl* m_formatPreviewSTC;
		wxPanel* m_otherPage;
		wxStaticBoxSizer* m_otherSizer;
		wxCheckBox* m_padMethodPrefix;
		wxCheckBox* m_unpadMethodPrefix;
		wxCheckBox* m_padReturnType;
		wxCheckBox* m_unpadReturnType;
		wxCheckBox* m_padParamType;
		wxCheckBox* m_unpadParamType;
		wxCheckBox* m_alignMethodColon;
		wxChoice* m_padMethodColon;
		wxButton* m_padMethodColonDisplay;
		wxStaticBoxSizer* m_otherPreviewSizer;
		wxStyledTextCtrl* m_otherPreviewSTC;
		wxButton* m_resetAllButton;
		wxButton* m_newSettings;
		wxStdDialogButtonSizer* m_sdbSizer;
		wxButton* m_sdbSizerOK;
		wxButton* m_sdbSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnNotebookPageChanged( wxTreebookEvent& event ) { event.Skip(); }
		virtual void OnStyleClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTabClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnModifierClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnIndentClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPadClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFormatClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOtherClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnResetAllClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSettingsClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOkClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		AStyleDlgBase( wxWindow* parent, wxWindowID id = ID_ASTYLE_DLG, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~AStyleDlgBase();
	
};

#endif //__ASTYLEDLGBASE_H__
