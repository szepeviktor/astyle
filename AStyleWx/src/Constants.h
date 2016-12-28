//  Constants.h
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.txt describes the conditions under which this software may be distributed.

#ifndef ASTYLEWX_CONSTANTS_H
#define ASTYLEWX_CONSTANTS_H

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include <wx/colour.h>
#include <wx/string.h>

//-----------------------------------------------------------------------------
// astylewx constants
//-----------------------------------------------------------------------------

// NOTE: enumerators are always static

enum BracketStyle
{
	STYLE_NONE,
	STYLE_ALLMAN,
	STYLE_JAVA,
	STYLE_KR,
	STYLE_STROUSTRUP,
	STYLE_WHITESMITH,
	STYLE_VTK,
	STYLE_BANNER,
	STYLE_GNU,
	STYLE_LINUX,
	STYLE_HORSTMANN,
	STYLE_1TBS,
	STYLE_GOOGLE,
	STYLE_MOZILLA,
	STYLE_PICO,
	STYLE_LISP,
	STYLE_END
};

enum IndentType
{
	INDENT_SPACES,
	INDENT_TABS,
	INDENT_FTABS,
	INDENT_END
};

// these MUST be the same as Artistic Style
enum MinConditional
{
	MINCOND_ZERO,
	MINCOND_ONE,
	MINCOND_TWO,
	MINCOND_ONEHALF,
	MINCOND_END
};

enum BreakBlocks
{
	BREAK_NONE,
	BREAK_OPEN,
	BREAK_ALL
};

enum PadParens
{
	PAD_NONE,
	PAD_OUTSIDE,
	PAD_INSIDE,
	PAD_ALL
};

// these MUST be the same as Artistic Style
enum PointerAlign
{
	PTR_ALIGN_NONE,
	PTR_ALIGN_TYPE,
	PTR_ALIGN_MIDDLE,
	PTR_ALIGN_NAME,
	PTR_ALIGN_END
};

// these MUST be the same as Artistic Style
enum ReferenceAlign
{
	REF_ALIGN_NONE = PTR_ALIGN_NONE,
	REF_ALIGN_TYPE = PTR_ALIGN_TYPE,
	REF_ALIGN_MIDDLE = PTR_ALIGN_MIDDLE,
	REF_ALIGN_NAME = PTR_ALIGN_NAME,
	REF_SAME_AS_PTR,
	REF_ALIGN_END
};

enum MaxCodeLength
{
	MAX_CODE_LENGTH_MIN = 50,
	MAX_CODE_LENGTH_MAX = 200
};

enum FileMode
{
	FILEMODE_NONE,
	FILEMODE_CPP,
	FILEMODE_OBJC,
	FILEMODE_JAVA,
	FILEMODE_SHARP,
};

// these MUST be the same as Artistic Style
enum PadMethodColon
{
	COLON_PAD_NO_CHANGE,
	COLON_PAD_NONE,
	COLON_PAD_ALL,
	COLON_PAD_AFTER,
	COLON_PAD_BEFORE,
	COLON_PAD_END,
};

//-----------------------------------------------------------------------------
// struct for text styles - used in style vectors
//-----------------------------------------------------------------------------

struct TextStyle
{
	wxString name;
	int      style;
	wxColor  fore;
	wxColor  back;
	bool     bold;
	bool     italic;
};

//----------------------------------------------------------------------------
// Editor and View option string constants for config file keys
//----------------------------------------------------------------------------

// String Defines
#define asTRUE		"true"
#define asFALSE		"false"

// Editor and View Option Keys
#define ACTIVE_LINE			"active-line"
#define ASTYLE_DLG_PAGE		"astyle-dlg-page"
#define COMMENT_FONT_FACE	"comment-font-face"
#define COMMENT_FONT_SIZE	"comment-font-size"
#define DEFAULT_FONT_FACE	"default-font-face"
#define DEFAULT_FONT_SIZE	"default-font-size"
#define DIALOG_TOOLTIPS     "dialog-tooltips"
#define EDITOR_DLG_PAGE     "editor-dlg-page"
#define END_OF_LINE         "end-of-line"
#define FILE_FILTER_INDEX   "file-filter-index"
#define FRAME_MAXIMIZED     "frame-maximized"
#define HIDE_FIND           "hide-find"
#define INDENT_GUIDES       "indent-guides"
#define LINE_NUMBERS        "line-numbers"
#define MONOSPACE           "monospace"
#define SELECTION_MARGIN    "selection-margin"
#define SHOW_STATUSBAR      "show-statusbar"
#define SHOW_TOOLBAR        "show-toolbar"
#define TEST_OPTIONS        "test-options"
#define TOOLBAR_TOOLTIPS    "toolbar-tooltips"
#define USE_BOTTOM_TABS     "use-bottom-tabs"
#define USE_SMALL_TOOLBAR   "use-small-toolbar"
#define WHITESPACE          "whitespace"
#define WORD_WRAP           "word-wrap"
#define WRAP_SEARCH         "wrap-search"

//-----------------------------------------------------------------------------
// AStyle string constants for config file keys
// in the same order as the documentation
//-----------------------------------------------------------------------------

// bracket style options
#define STYLE                       "style"
#define ALLMAN                      "allman"
#define JAVA                        "java"
#define KandR                       "kr"
#define STROUSTRUP                  "stroustrup"
#define WHITESMITH                  "whitesmith"
#define VTK                         "vtk"
#define BANNER                      "banner"
#define GNU                         "gnu"
#define LINUXX                      "linux"     // LINUX is defined by Intel compiler
#define HORSTMANN                   "horstmann"
#define oneTBS                      "1tbs"
#define GOOGLE                      "google"
#define MOZILLA                     "mozilla"
#define PICO                        "pico"
#define LISP                        "lisp"
// tabs/spaces config keys
#define INDENT_TYPE                 "indent-type"
#define INDENT_LENGTH               "indent-length"
#define USE_TAB_LENGTH              "use-tab-length"
#define TAB_LENGTH                  "tab-length"
#define INDENT_TYPE_SPACES          "spaces"
#define INDENT_TYPE_TAB             "tab"
#define INDENT_TYPE_FTAB            "force-tab"
// tabs/spaces options
#define INDENT_OPT_SPACES           "indent=spaces"
#define INDENT_OPT_TAB              "indent=tab"
#define INDENT_OPT_FTAB             "indent=force-tab"
#define INDENT_OPT_FTAB_X           "indent=force-tab-x"
// bracket modifier options
#define ATTACH_NAMESPACES           "attach-namespaces"
#define ATTACH_CLASSES              "attach-classes"
#define ATTACH_INLINES              "attach-inlines"
#define ATTACH_EXTERNC              "attach-extern-c"
// indentation options
#define INDENT_CLASSES              "indent-classes"
#define INDENT_MODIFIERS            "indent-modifiers"
#define INDENT_SWITCHES             "indent-switches"
#define INDENT_CASES                "indent-cases"
#define INDENT_NAMESPACES           "indent-namespaces"
#define INDENT_CONTINUATION         "indent-continuation"
#define INDENT_LABELS               "indent-labels"
#define INDENT_PREPROC_BLOCK        "indent-preproc-block"
#define INDENT_PREPROC_DEFINE       "indent-preproc-define"
#define INDENT_PREPROC_COND         "indent-preproc-cond"
#define INDENT_COL1_COMMENTS        "indent-col1-comments"
#define MIN_CONDITIONAL_INDENT      "min-conditional-indent"	// TODO: indent or option?
#define MAX_INSTATEMENT_INDENT      "max-instatement-indent"
// padding options
#define BREAK_BLOCKS                "break-blocks"
#define BREAK_BLOCKS_ALL            "break-blocks=all"
#define PAD_OPER                    "pad-oper"
#define PAD_COMMA                   "pad-comma"
#define PAD_PAREN                   "pad-paren"
#define PAD_PAREN_OUT               "pad-paren-out"
#define PAD_PAREN_IN                "pad-paren-in"
#define PAD_FIRST_PAREN_OUT         "pad-first-paren-out"
#define PAD_HEADER                  "pad-header"
#define UNPAD_PAREN                 "unpad-paren"
#define DELETE_EMPTY_LINES          "delete-empty-lines"
#define FILL_EMPTY_LINES            "fill-empty-lines"
#define ALIGN_POINTER               "align-pointer"
#define ALIGN_POINTER_TYPE          "align-pointer=type"
#define ALIGN_POINTER_MIDDLE        "align-pointer=middle"
#define ALIGN_POINTER_NAME          "align-pointer=name"
#define ALIGN_REFERENCE             "align-reference"
#define ALIGN_REFERENCE_NONE        "align-reference=none"
#define ALIGN_REFERENCE_TYPE        "align-reference=type"
#define ALIGN_REFERENCE_MIDDLE      "align-reference=middle"
#define ALIGN_REFERENCE_NAME        "align-reference=name"
// formatting options
#define BREAK_CLOSING_BRACKETS		"break-closing-brackets"
#define BREAK_ELSEIFS				"break-elseifs"
#define BREAK_ONE_LINE_HEADERS		"break-one-line-headers"
#define ADD_BRACKETS				"add-brackets"
#define ADD_ONE_LINE_BRACKETS		"add-one-line-brackets"
#define REMOVE_BRACKETS				"remove-brackets"
#define KEEP_ONE_LINE_BLOCKS		"keep-one-line-blocks"
#define KEEP_ONE_LINE_STATEMENTS	"keep-one-line-statements"
#define CONVERT_TABS				"convert-tabs"
#define CLOSE_TEMPLATES				"close-templates"
#define REMOVE_COMMENT_PREFIX		"remove-comment-prefix"
#define MAX_CODE_LENGTH				"max-code-length"
#define BREAK_AFTER_LOGICAL			"break-after-logical"
#define MODE_CPP					"mode=c"		// this is the default
#define MODE_JAVA					"mode=java"
#define MODE_CS						"mode=cs"
// other options
#define PAD_METHOD_PREFIX			"pad-method-prefix"
#define UNPAD_METHOD_PREFIX			"unpad-method-prefix"
#define PAD_RETURN_TYPE				"pad-return-type"
#define UNPAD_RETURN_TYPE			"unpad-return-type"
#define PAD_PARAM_TYPE				"pad-param-type"
#define UNPAD_PARAM_TYPE			"unpad-param-type"
#define ALIGN_METHOD_COLON			"align-method-colon"
#define PAD_METHOD_COLON			"pad-method-colon"

#endif	//	ASTYLEWX_CONSTANTS_H
