// AStyleConfig_Test.cpp
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

/* ----------------------------------------------------------------------------
TO ADD A NEW ASTYLE OPTION
Add new test function to "Config_AStyle_*, SaveAStyleOptions_*".

TO ADD A NEW EDITOR AND VIEW OPTION
If necessary #define a test value in Config_Test.h.
If necessary add a "getter" to the fake Editor or ASFrame class in Config_Test.h.
If an entry is always written in the config file add a test to
    "Config_Frame, InitializeFile" or "Config_Editor, SaveEditorOptions_AlwaysSaved".
If an entry is NOT always written in the config file add a test to
    the appropriate "Get" and "Save" options for Editor or Styles.
---------------------------------------------------------------------------- */

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include <wx/app.h>
#include <wx/frame.h>

#include "Config_Test.h"

// for gmock macros
using namespace testing;

//----------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------

#ifdef __WXMSW__
	#define CONFIG_TEST_NAME  "AStyleWxTest"
#else
	#define CONFIG_TEST_NAME  "astylewxtest"
#endif

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {
//
//-------------------------------------------------------------------------
// AStyle Config Tests for Invalid Keys
//-------------------------------------------------------------------------

struct Config_AStyleF : public Test
{
	// Need this setup because of wxWidgets wxIMPLEMENT_APP_NO_MAIN.
	// It must be done to create a wxFrame object.
	// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
	// See the wxWidgets sample program mfctest.cpp.
	Config_AStyleF()
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = nullptr;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != nullptr);	// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
	}
	virtual ~Config_AStyleF()
	// Need this because of wxIMPLEMENT_APP_NO_MAIN.
	// See the wxWidgets sample program mfctest.cpp.
	{
		wxTheApp->OnExit();			// call wxApp::OnExit()
		wxEntryCleanup();			// free resources from wxEntryStart
	}
};

TEST_F(Config_AStyleF, GetAStyleOptions_InvalidKeys)
// Test config file gets for AStyle options.
// Invalid keys in the config file should be deleted.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;

	// build keys array
	wxArrayString keys;
	keys.Add("invalid-key-1");
	keys.Add("invalid-key-2");
	keys.Add("invalid-key-3");
	keys.Add("invalid-key-4");
	// write keys to config
	config.SetPath("/AStyle");
	for (size_t i = 0; i < keys.GetCount(); i++)
		config.Write(keys[i], asTRUE);
	// verify the number of config file keys
	ASSERT_EQ(keys.GetCount(), config.GetNumberOfEntries());

	// Expect ShowInvalidConfig to be called once for each config file key.
	// Expect SetAStyleOption to be called once for each config file key.
	// The return value of false will indicate that the key is invalid.
	// AStyleIFace methods are tested in the AStyleIFace_Test module.
	for (size_t i = 0; i < keys.GetCount(); i++)
	{
		EXPECT_CALL(config, ShowInvalidConfig(keys[i])).Times(1);
		EXPECT_CALL(astyle, SetAStyleOption(keys[i], _)).Times(1);
		ON_CALL(astyle, SetAStyleOption(keys[i], _)).WillByDefault(Return(false));
	}
	// test the function
	config.GetAStyleOptions(&astyle);
	// verify that all config file keys were deleted
	config.SetPath("/AStyle");
	EXPECT_EQ(0U, config.GetNumberOfEntries());
}

TEST_F(Config_AStyleF, GetAStyleOptions_InvalidValues)
// Test config file gets for AStyle options.
// Invalid values in the config file should be deleted.
// NOTE: Float and double values are written to config as strings.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;

	// test reading bool values
	config.SetPath("/AStyle");
	config.Write(INDENT_CLASSES, true);
	config.Write(INDENT_SWITCHES, false);
	ASSERT_EQ(2U, config.GetNumberOfEntries());
	// Expect SetAStyleOption to not be called for Windows.
	// Expect it to be called twice for Linux.
	// Windows uses the registry. Linux uses a config file.
#ifdef __WXMSW__
	EXPECT_CALL(astyle, SetAStyleOption(_, _)).Times(0);
#else
	EXPECT_CALL(astyle, SetAStyleOption(_, _)).Times(2);
#endif
	// Expect ShowInvalidConfig to be called once for each config file key.
	// AStyleIFace methods are tested in the AStyleIFace_Test module.
	EXPECT_CALL(config, ShowInvalidConfig(_)).Times(2);
	// test the function
	config.GetAStyleOptions(&astyle);
	// verify that all bool config file keys were deleted
	config.SetPath("/AStyle");
	EXPECT_EQ(0U, config.GetNumberOfEntries());

	// test reading long values
	long valueLong;
	config.SetPath("/AStyle");
	valueLong = 1;
	config.Write(INDENT_CLASSES, valueLong);
	valueLong = 2;
	config.Write(INDENT_SWITCHES, valueLong);
	ASSERT_EQ(2U, config.GetNumberOfEntries());
	// Expect SetAStyleOption to not be called for Windows.
	// Expect it to be called twice for Linux.
	// Windows uses the registry. Linux uses a config file.
#ifdef __WXMSW__
	EXPECT_CALL(astyle, SetAStyleOption(_, _)).Times(0);
#else
	EXPECT_CALL(astyle, SetAStyleOption(_, _)).Times(2);
#endif
	// Expect ShowInvalidConfig to be called once for each config file key.
	// AStyleIFace methods are tested in the AStyleIFace_Test module.
	EXPECT_CALL(config, ShowInvalidConfig(_)).Times(2);
	// test the function
	config.GetAStyleOptions(&astyle);
	// verify that all long config file keys were deleted
	config.SetPath("/AStyle");
	EXPECT_EQ(0U, config.GetNumberOfEntries());
}

TEST_F(Config_AStyleF, GetAStyleOptions)
// Test config file gets for AStyle options.
// GetNextEntry is used for the read so only a few options are checked.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;

	// build keys array
	wxArrayString keys;
	keys.Add(INDENT_CLASSES);
	keys.Add(INDENT_SWITCHES);
	keys.Add(INDENT_CASES);
	keys.Add(INDENT_NAMESPACES);

	// write test values
	config.SetPath("/AStyle");
	for (size_t i = 0; i < keys.GetCount(); i++)
		config.Write(keys[i], asTRUE);
	ASSERT_EQ(keys.GetCount(), config.GetNumberOfEntries());

	// Expect ShowInvalidConfig to not be called.
	// Expect SetAStyleOption to be called once for each config file key.
	// The return value of true will indicate that the key is valid.
	// AStyleIFace methods are tested in the AStyleIFace_Test module.
	for (size_t i = 0; i < keys.GetCount(); i++)
	{
		EXPECT_CALL(config, ShowInvalidConfig(keys[i])).Times(0);
		EXPECT_CALL(astyle, SetAStyleOption(keys[i], _)).Times(1);
		ON_CALL(astyle, SetAStyleOption(keys[i], _)).WillByDefault(Return(true));
	}
	// test the function
	config.GetAStyleOptions(&astyle);
}

//-------------------------------------------------------------------------
// AStyle Config Tests for Style Options
//-------------------------------------------------------------------------

struct Config_AStyleF_Styles : public Test
{
	// Need this setup because of wxWidgets wxIMPLEMENT_APP_NO_MAIN.
	// It must be done to create a wxFrame object.
	// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
	// See the wxWidgets sample program mfctest.cpp.
	Config_AStyleF_Styles()
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = nullptr;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != nullptr);	// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
	}
	virtual ~Config_AStyleF_Styles()
	// Need this because of wxIMPLEMENT_APP_NO_MAIN.
	// See the wxWidgets sample program mfctest.cpp.
	{
		wxTheApp->OnExit();			// call wxApp::OnExit()
		wxEntryCleanup();			// free resources from wxEntryStart
	}
};

TEST_F(Config_AStyleF_Styles, SaveAStyleOptions_StylesAll)
// Test config file writes for astyle brace style options
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	struct StyleStruct
	{
		BraceStyle styleNum;
		wxString styleName;
	};

	StyleStruct style[] =
	{
		{ STYLE_ALLMAN,     ALLMAN     },
		{ STYLE_JAVA,       JAVA       },
		{ STYLE_KR,         KandR      },
		{ STYLE_STROUSTRUP, STROUSTRUP },
		{ STYLE_WHITESMITH, WHITESMITH },
		{ STYLE_RATLIFF,    RATLIFF    },
		{ STYLE_GNU,        GNU        },
		{ STYLE_LINUX,      LINUXX     },
		{ STYLE_HORSTMANN,  HORSTMANN  },
		{ STYLE_1TBS,       oneTBS     },
		{ STYLE_GOOGLE,     GOOGLE     },
		{ STYLE_MOZILLA,    MOZILLA    },
		{ STYLE_WEBKIT,     WEBKIT     },
		{ STYLE_PICO,       PICO       },
		{ STYLE_LISP,       LISP       }
	};

	// test style options
	key = STYLE;
	size_t numStyles = sizeof(style) / sizeof(style[0]);
	for (size_t i = 0; i < numStyles; i++)
	{
		astyle.SetBraceStyle(style[i].styleNum);
		config.SaveAStyleOptions(&astyle);
		config.SetPath("/AStyle");
		config.Read(key, &value);
		EXPECT_EQ(style[i].styleName.ToStdString(), value.ToStdString())
		        << "Failure for style = " << style[i].styleName;
	}

	// test style none
	key = STYLE;
	astyle.SetBraceStyle(STYLE_NONE);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for style = none";

	// test invalid style
	key = STYLE;
	astyle.SetBraceStyle(STYLE_END);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid style";
}

//-------------------------------------------------------------------------
// AStyle Config Tests for Tab Options
//-------------------------------------------------------------------------

struct Config_AStyleF_Tabs : public Test
{
	// Need this setup because of wxWidgets wxIMPLEMENT_APP_NO_MAIN.
	// It must be done to create a wxFrame object.
	// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
	// See the wxWidgets sample program mfctest.cpp.
	Config_AStyleF_Tabs()
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = nullptr;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != nullptr);	// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
	}
	virtual ~Config_AStyleF_Tabs()
	// Need this because of wxIMPLEMENT_APP_NO_MAIN.
	// See the wxWidgets sample program mfctest.cpp.
	{
		wxTheApp->OnExit();			// call wxApp::OnExit()
		wxEntryCleanup();			// free resources from wxEntryStart
	}
};

TEST_F(Config_AStyleF_Tabs, SaveAStyleOptions_IndentSpaces_Default)
// Test the default indent spaces options.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// indent 4 spaces, no entries for indent-type and indent-length
	astyle.SetIndentType(INDENT_SPACES);
	astyle.SetIndentLength(4);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(INDENT_TYPE, &value));
	EXPECT_FALSE(config.Read(INDENT_LENGTH, &value));
	EXPECT_FALSE(config.Read(USE_TAB_LENGTH, &value));
	EXPECT_FALSE(config.Read(TAB_LENGTH, &value));
}

TEST_F(Config_AStyleF_Tabs, SaveAStyleOptions_IndentTabs_Default)
// Test the default indent tabs options.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// indent 4 tabs, no entry for indent-length
	astyle.SetIndentType(INDENT_TABS);
	astyle.SetIndentLength(4);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_TRUE(config.Read(INDENT_TYPE, &value));
	EXPECT_STREQ(INDENT_TYPE_TAB, value);
	EXPECT_FALSE(config.Read(INDENT_LENGTH, &value));
	EXPECT_FALSE(config.Read(USE_TAB_LENGTH, &value));
	EXPECT_FALSE(config.Read(TAB_LENGTH, &value));
}

TEST_F(Config_AStyleF_Tabs, SaveAStyleOptions_IndentForce_Default)
// Test the default indent force tabs options.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// indent 4 force-tabs, no entry for indent-length
	astyle.SetIndentType(INDENT_FTABS);
	astyle.SetIndentLength(4);
	astyle.SetUseTabLength(false);		// do not use indent=force-tab-x
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_TRUE(config.Read(INDENT_TYPE, &value));
	EXPECT_STREQ(INDENT_TYPE_FTAB, value);
	EXPECT_FALSE(config.Read(INDENT_LENGTH, &value));
	EXPECT_FALSE(config.Read(USE_TAB_LENGTH, &value));
	EXPECT_FALSE(config.Read(TAB_LENGTH, &value));
}

TEST_F(Config_AStyleF_Tabs, SaveAStyleOptions_Indent)
// Test config file writes for astyle indent type and indent length options.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	struct IndentStruct
	{
		IndentType indentNum;
		int        indentLen;
		wxString   indentName;
		wxString   indentLength;
	};

	IndentStruct indent[] =
	{
		// indent=force-tab-x is in a separate test
		{ INDENT_SPACES, 3, "spaces",    "3"  },
		{ INDENT_TABS,   5, "tab",       "5"  },
		{ INDENT_FTABS,  6, "force-tab", "6"  },
		{ INDENT_SPACES, 1, "spaces",    "2"  },	// invalid min changed to 2
		{ INDENT_TABS,  -1, "tab",       "2"  },	// invalid min changed to 2
		{ INDENT_FTABS, 21, "force-tab", "20" },	// invalid max changed to 20
	};

	// test indent options
	size_t numIndents = sizeof(indent) / sizeof(indent[0]);
	for (size_t i = 0; i < numIndents; i++)
	{
		astyle.SetIndentType(indent[i].indentNum);
		astyle.SetIndentLength(indent[i].indentLen);
		astyle.SetUseTabLength(false);
		config.SaveAStyleOptions(&astyle);
		config.SetPath("/AStyle");
		config.Read(INDENT_TYPE, &value);
		EXPECT_EQ(indent[i].indentName, value)
		        << "Failure for indent_type " << indent[i].indentName;
		config.Read(INDENT_LENGTH, &value);
		EXPECT_EQ(indent[i].indentLength, value)
		        << "Failure for indent length " << indent[i].indentLength;
		EXPECT_FALSE(config.Read(USE_TAB_LENGTH, &value))
		        << "Failure for use tab length";
		EXPECT_FALSE(config.Read(TAB_LENGTH, &value))
		        << "Failure for tab length";
	}
}

TEST_F(Config_AStyleF_Tabs, SaveAStyleOptions_Indent_ForceTab_X)
// Test config file writes for astyle indent-force-tab-x options
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// indent 4, tab-length 8, no entry for  tab-length or indent-length
	astyle.SetIndentType(INDENT_FTABS);
	astyle.SetIndentLength(4);
	astyle.SetUseTabLength(true);
	astyle.SetTabLength(8);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_TRUE(config.Read(INDENT_TYPE, &value))
	        << "Failure for force-tab indent-type";
	EXPECT_STREQ(INDENT_TYPE_FTAB, value)
	        << "Failure for force-tab indent-type";
	EXPECT_FALSE(config.Read(INDENT_LENGTH, &value))
	        << "Failure for force-tab indent-length";
	EXPECT_TRUE(config.Read(USE_TAB_LENGTH, &value))
	        << "Failure for force-tab use-tab-length";
	EXPECT_FALSE(config.Read(TAB_LENGTH, &value))
	        << "Failure for force-tab tab-length";
	// indent 4, tab-length 4, no entry for indent-length, entry for tab-length
	astyle.SetIndentType(INDENT_FTABS);
	astyle.SetIndentLength(4);
	astyle.SetUseTabLength(true);
	astyle.SetTabLength(4);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_TRUE(config.Read(INDENT_TYPE, &value))
	        << "Failure for force-tab indent-type";
	EXPECT_STREQ(INDENT_TYPE_FTAB, value)
	        << "Failure for force-tab indent-type";
	EXPECT_FALSE(config.Read(INDENT_LENGTH, &value))
	        << "Failure for force-tab indent-length";
	EXPECT_TRUE(config.Read(USE_TAB_LENGTH, &value))
	        << "Failure for force-tab use-tab-length";
	EXPECT_TRUE(config.Read(TAB_LENGTH, &value))
	        << "Failure for force-tab tab-length";
	EXPECT_STREQ("4", value)
	        << "Failure for force-tab tab-length";
	// indent 5, tab-length 5, equal indent and tab, entry for indent-length and tab-length
	astyle.SetIndentType(INDENT_FTABS);
	astyle.SetIndentLength(5);
	astyle.SetUseTabLength(true);
	astyle.SetTabLength(5);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_TRUE(config.Read(INDENT_TYPE, &value))
	        << "Failure for force-tab indent-type";
	EXPECT_STREQ(INDENT_TYPE_FTAB, value)
	        << "Failure for force-tab indent-type";
	EXPECT_TRUE(config.Read(INDENT_LENGTH, &value))
	        << "Failure for force-tab indent-length";
	EXPECT_STREQ("5", value)
	        << "Failure for force-tab indent-length";
	EXPECT_TRUE(config.Read(USE_TAB_LENGTH, &value))
	        << "Failure for force-tab use-tab-length";
	EXPECT_TRUE(config.Read(TAB_LENGTH, &value))
	        << "Failure for force-tab tab-length";
	EXPECT_STREQ("5", value)
	        << "Failure for force-tab tab-length";
	// indent 3 tab-length 6, entry for indent-length and tab-length
	astyle.SetIndentType(INDENT_FTABS);
	astyle.SetIndentLength(3);
	astyle.SetUseTabLength(true);
	astyle.SetTabLength(6);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_TRUE(config.Read(INDENT_TYPE, &value))
	        << "Failure for default force-tab indent-type";
	EXPECT_STREQ(INDENT_TYPE_FTAB, value)
	        << "Failure for default force-tab indent-type";
	EXPECT_TRUE(config.Read(INDENT_LENGTH, &value))
	        << "Failure for force-tab indent-length";
	EXPECT_STREQ("3", value)
	        << "Failure for force-tab indent-length";
	EXPECT_TRUE(config.Read(USE_TAB_LENGTH, &value))
	        << "Failure for force-tab use-tab-length";
	EXPECT_TRUE(config.Read(TAB_LENGTH, &value))
	        << "Failure for force-tab tab-length";
	EXPECT_STREQ("6", value)
	        << "Failure for force-tab tab-length";
}

TEST_F(Config_AStyleF_Tabs, SaveAStyleOptions_Indent_UseTabLen_Sans)
// Test config file writes for astyle when useTabLength should have no effect.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// indent spaces, no entry for tab-length even if useTabLength is set
	astyle.SetIndentType(INDENT_SPACES);
	astyle.SetIndentLength(3);
	astyle.SetUseTabLength(true);
	astyle.SetTabLength(6);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_TRUE(config.Read(INDENT_TYPE, &value))
	        << "Failure for spaces indent type";
	EXPECT_TRUE(config.Read(INDENT_LENGTH, &value))
	        << "Failure for spaces indent length";
	EXPECT_FALSE(config.Read(USE_TAB_LENGTH, &value))
	        << "Failure for spaces use-tab-length";
	EXPECT_FALSE(config.Read(TAB_LENGTH, &value))
	        << "Failure for spaces tab length";
	// indent tabs, no entry for tab-length even if useTabLength is set
	astyle.SetIndentType(INDENT_TABS);
	astyle.SetIndentLength(5);
	astyle.SetUseTabLength(true);
	astyle.SetTabLength(10);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_TRUE(config.Read(INDENT_TYPE, &value))
	        << "Failure for tab indent type";
	EXPECT_TRUE(config.Read(INDENT_LENGTH, &value))
	        << "Failure for tab indent length";
	EXPECT_FALSE(config.Read(USE_TAB_LENGTH, &value))
	        << "Failure for tab use-tab-length";
	EXPECT_FALSE(config.Read(TAB_LENGTH, &value))
	        << "Failure for tab tab length";
	// indent force-tabs, no entry for tab-length when useTabLength is not set
	astyle.SetIndentType(INDENT_FTABS);
	astyle.SetIndentLength(5);
	astyle.SetUseTabLength(false);
	astyle.SetTabLength(10);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_TRUE(config.Read(INDENT_TYPE, &value))
	        << "Failure for tab indent type";
	EXPECT_TRUE(config.Read(INDENT_LENGTH, &value))
	        << "Failure for tab indent length";
	EXPECT_FALSE(config.Read(USE_TAB_LENGTH, &value))
	        << "Failure for force-tab use-tab-length";
	EXPECT_FALSE(config.Read(TAB_LENGTH, &value))
	        << "Failure for tab tab length";
}

//-------------------------------------------------------------------------
// AStyle Config Tests for Brace Modifier Options
//-------------------------------------------------------------------------

struct Config_AStyleF_Modifier : public Test
{
	// Need this setup because of wxWidgets wxIMPLEMENT_APP_NO_MAIN.
	// It must be done to create a wxFrame object.
	// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
	// See the wxWidgets sample program mfctest.cpp.
	Config_AStyleF_Modifier()
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = nullptr;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != nullptr);	// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
	}
	virtual ~Config_AStyleF_Modifier()
	// Need this because of wxIMPLEMENT_APP_NO_MAIN.
	// See the wxWidgets sample program mfctest.cpp.
	{
		wxTheApp->OnExit();			// call wxApp::OnExit()
		wxEntryCleanup();			// free resources from wxEntryStart
	}
};

TEST_F(Config_AStyleF_Modifier, SaveAStyleOptions_AttachNamespace)
// Test config file writes for astyle attachNamespace option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ATTACH_NAMESPACES;
	astyle.SetAttachNamespace(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetAttachNamespace(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Modifier, SaveAStyleOptions_AttachClass)
// Test config file writes for astyle attachClass option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ATTACH_CLASSES;
	astyle.SetAttachClass(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetAttachClass(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Modifier, SaveAStyleOptions_AttachInline)
// Test config file writes for astyle attachInline option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ATTACH_INLINES;
	astyle.SetAttachInline(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetAttachInline(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Modifier, SaveAStyleOptions_AttachExternC)
// Test config file writes for astyle attachExternC option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ATTACH_EXTERN_C;
	astyle.SetAttachExternC(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetAttachExternC(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Modifier, SaveAStyleOptions_AttachClosingWhile)
// Test config file writes for astyle attachClosingWhile option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ATTACH_CLOSING_WHILE;
	astyle.SetAttachClosingWhile(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetAttachClosingWhile(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

//-------------------------------------------------------------------------
// AStyle Config Tests for Indentation Options
//-------------------------------------------------------------------------

struct Config_AStyleF_Indent : public Test
{
	// Need this setup because of wxWidgets wxIMPLEMENT_APP_NO_MAIN.
	// It must be done to create a wxFrame object.
	// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
	// See the wxWidgets sample program mfctest.cpp.
	Config_AStyleF_Indent()
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = nullptr;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != nullptr);	// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
	}
	virtual ~Config_AStyleF_Indent()
	// Need this because of wxIMPLEMENT_APP_NO_MAIN.
	// See the wxWidgets sample program mfctest.cpp.
	{
		wxTheApp->OnExit();			// call wxApp::OnExit()
		wxEntryCleanup();			// free resources from wxEntryStart
	}
};

TEST_F(Config_AStyleF_Indent, SaveAStyleOptions_AfterParenIndent)
// Test config file writes for astyle afterParenIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_AFTER_PARENS;
	astyle.SetAfterParenIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetAfterParenIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Indent, SaveAStyleOptions_CaseIndent)
// Test config file writes for astyle caseIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_CASES;
	astyle.SetCaseIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetCaseIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Indent, SaveAStyleOptions_ClassIndent)
// Test config file writes for astyle classIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_CLASSES;
	astyle.SetClassIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetClassIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Indent, SaveAStyleOptions_Col1CommentIndent)
// Test config file writes for astyle col1CommentIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_COL1_COMMENTS;
	astyle.SetCol1CommentIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetCol1CommentIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Indent, SaveAStyleOptions_ContinuationIndent)
// Test config file writes for astyle continuation indent
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// test continuation indent
	key = INDENT_CONTINUATION;
	astyle.SetContinuationIndent(2);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("2", value)
	        << "Failure for continuation indent";

	// test continuation indent default
	int defaultContinuationIndent = astyle.GetDefaultContinuationIndent();
	EXPECT_TRUE(defaultContinuationIndent == 1);
	key = INDENT_CONTINUATION;
	astyle.SetContinuationIndent(defaultContinuationIndent);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for default continuation indent";

	// test invalid minimum for continuation indent
	key = INDENT_CONTINUATION;
	astyle.SetContinuationIndent(-1);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid continuation indent" << value;

	// test invalid maximum for continuation indent
	key = INDENT_CONTINUATION;
	astyle.SetContinuationIndent(5);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid continuation indent";
}

TEST_F(Config_AStyleF_Indent, SaveAStyleOptions_LabelIndent)
// Test config file writes for astyle labelIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_LABELS;
	astyle.SetLabelIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetLabelIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Indent, SaveAStyleOptions_MaxContinuation)
// Test config file writes for astyle max continuation indent
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// test max code length
	key = MAX_CONTINUATION_INDENT;
	astyle.SetMaxContinuationIndent(50);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("50", value)
	        << "Failure for max continuation indent";

	// test max continuation default
	int defaultMaxInStatementIndent = astyle.GetDefaultMaxContinuationIndent();
	EXPECT_TRUE(defaultMaxInStatementIndent == 40);
	key = MAX_CONTINUATION_INDENT;
	astyle.SetMaxContinuationIndent(defaultMaxInStatementIndent);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for default max continuation indent";

	// test invalid minimum for max continuation, should use minimum (default)
	key = MAX_CONTINUATION_INDENT;
	astyle.SetMaxContinuationIndent(39);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid max continuation indent";

	// test invalid maximum for max continuation, should use maximum
	key = MAX_CONTINUATION_INDENT;
	astyle.SetMaxContinuationIndent(121);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	wxString maxIndentEnum = wxString::Format("%d", 120);
	EXPECT_EQ(maxIndentEnum, value)
	        << "Failure for invalid max continuation indent";
}

TEST_F(Config_AStyleF_Indent, SaveAStyleOptions_MinConditionalOpt)
// Test config file writes for astyle min conditional option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	MinConditional minOption[] =
	{
		MINCOND_ZERO,
		MINCOND_ONE,
		MINCOND_ONEHALF,
	};

	// test min conditional options
	key = MIN_CONDITIONAL_INDENT;
	size_t numOptions = sizeof(minOption) / sizeof(minOption[0]);
	for (size_t i = 0; i < numOptions; i++)
	{
		astyle.SetMinConditionalOption(minOption[i]);
		config.SaveAStyleOptions(&astyle);
		config.SetPath("/AStyle");
		config.Read(key, &value);
		wxString minOptionEnum = wxString::Format("%d", minOption[i]);
		EXPECT_EQ(minOptionEnum, value)
		        << "Failure for min conditional option = " << minOption[i];
	}

	// test min conditional option default
	MinConditional defaultMinConditionalOption = astyle.GetDefaultMinConditionalOption();
	EXPECT_TRUE(defaultMinConditionalOption == MINCOND_TWO);
	key = MIN_CONDITIONAL_INDENT;
	astyle.SetMinConditionalOption(defaultMinConditionalOption);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for default min conditional option";

	// test invalid min conditional option, should use default
	key = MIN_CONDITIONAL_INDENT;
	astyle.SetMinConditionalOption(MINCOND_END);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid min conditional option";
}

TEST_F(Config_AStyleF_Indent, SaveAStyleOptions_ModifierIndent)
// Test config file writes for astyle modifierIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_MODIFIERS;
	astyle.SetModifierIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetModifierIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Indent, SaveAStyleOptions_NamespaceIndent)
// Test config file writes for astyle namespaceIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_NAMESPACES;
	astyle.SetNamespaceIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetNamespaceIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Indent, SaveAStyleOptions_PreprocBlockIndent)
// Test config file writes for astyle preprocBlockIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_PREPROC_BLOCK;
	astyle.SetPreprocBlockIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetPreprocBlockIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Indent, SaveAStyleOptions_PreprocCondIndent)
// Test config file writes for astyle preprocCondIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_PREPROC_COND;
	astyle.SetPreprocCondIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetPreprocCondIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Indent, SaveAStyleOptions_PreprocDefineIndent)
// Test config file writes for astyle preprocDefineIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_PREPROC_DEFINE;
	astyle.SetPreprocDefineIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetPreprocDefineIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Indent, SaveAStyleOptions_SwitchIIndent)
// Test config file writes for astyle switchIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_SWITCHES;
	astyle.SetSwitchIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetSwitchIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

//-------------------------------------------------------------------------
// AStyle Config Tests for Padding Options
//-------------------------------------------------------------------------

struct Config_AStyleF_Pad : public Test
{
	// Need this setup because of wxWidgets wxIMPLEMENT_APP_NO_MAIN.
	// It must be done to create a wxFrame object.
	// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
	// See the wxWidgets sample program mfctest.cpp.
	Config_AStyleF_Pad()
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = nullptr;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != nullptr);	// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
	}
	virtual ~Config_AStyleF_Pad()
	// Need this because of wxIMPLEMENT_APP_NO_MAIN.
	// See the wxWidgets sample program mfctest.cpp.
	{
		wxTheApp->OnExit();			// call wxApp::OnExit()
		wxEntryCleanup();			// free resources from wxEntryStart
	}
};

TEST_F(Config_AStyleF_Pad, SaveAStyleOptions_AlignPointer)
// Test config file writes for astyle align pointer option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	PointerAlign alignPointer[] =
	{
		PTR_ALIGN_TYPE,
		PTR_ALIGN_MIDDLE,
		PTR_ALIGN_NAME,
	};

	// test align pointer options
	key = ALIGN_POINTER;
	size_t numOptions = sizeof(alignPointer) / sizeof(alignPointer[0]);
	for (size_t i = 0; i < numOptions; i++)
	{
		astyle.SetAlignPointer(alignPointer[i]);
		config.SaveAStyleOptions(&astyle);
		config.SetPath("/AStyle");
		config.Read(key, &value);
		wxString alignPointerEnum = wxString::Format("%d", alignPointer[i]);
		EXPECT_EQ(alignPointerEnum, value)
		        << "Failure for align pointer = " << alignPointer[i];
	}

	// test align pointer none (default)
	key = ALIGN_POINTER;
	astyle.SetAlignPointer(PTR_ALIGN_NONE);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for default align pointer";

	// test invalid align pointer, should use default
	key = ALIGN_POINTER;
	astyle.SetAlignPointer(PTR_ALIGN_END);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid align pointer";

	// test invalid align pointer, should use default
	key = ALIGN_POINTER;
	astyle.SetAlignPointer(PTR_ALIGN_END);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid align pointer";
}

TEST_F(Config_AStyleF_Pad, SaveAStyleOptions_AlignReference)
// Test config file writes for astyle align reference option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	ReferenceAlign alignReference[] =
	{
		REF_ALIGN_NONE,
		REF_ALIGN_TYPE,
		REF_ALIGN_MIDDLE,
		REF_ALIGN_NAME,
	};

	// test align reference options
	key = ALIGN_REFERENCE;
	size_t numOptions = sizeof(alignReference) / sizeof(alignReference[0]);
	for (size_t i = 0; i < numOptions; i++)
	{
		astyle.SetAlignReference(alignReference[i]);
		config.SaveAStyleOptions(&astyle);
		config.SetPath("/AStyle");
		config.Read(key, &value);
		wxString alignReferenceEnum = wxString::Format("%d", alignReference[i]);
		EXPECT_EQ(alignReferenceEnum, value)
		        << "Failure for align reference = " << alignReference[i];
	}

	// test align reference same as pointer (default)
	key = ALIGN_REFERENCE;
	astyle.SetAlignReference(REF_SAME_AS_PTR);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for default align reference";

	// test invalid align reference, should use default
	key = ALIGN_REFERENCE;
	astyle.SetAlignReference(REF_ALIGN_END);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid align reference";

	// test invalid align reference, should use default
	key = ALIGN_REFERENCE;
	astyle.SetAlignReference(REF_ALIGN_END);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid align reference";
}

TEST_F(Config_AStyleF_Pad, SaveAStyleOptions_BreakBlocks)
// Test config file writes for astyle break blocks options
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// test break all blocks
	key = BREAK_BLOCKS;
	astyle.SetBreakHeaderBlocks(true);
	astyle.SetBreakClosingBlocks(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("all", value)
	        << "Failure for break all blocks";

	// test break header blocks
	key = BREAK_BLOCKS;
	astyle.SetBreakHeaderBlocks(true);
	astyle.SetBreakClosingBlocks(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("open", value)
	        << "Failure for break header blocks";

	// test invalid break header blocks
	key = BREAK_BLOCKS;
	astyle.SetBreakHeaderBlocks(false);
	astyle.SetBreakClosingBlocks(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid break header blocks";
}

TEST_F(Config_AStyleF_Pad, SaveAStyleOptions_DeleteEmptyLines)
// Test config file writes for astyle deleteEmptyLines option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = DELETE_EMPTY_LINES;
	astyle.SetDeleteEmptyLines(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetDeleteEmptyLines(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Pad, SaveAStyleOptions_FillEmptyLines)
// Test config file writes for astyle fillEmptyLines option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = FILL_EMPTY_LINES;
	astyle.SetFillEmptyLines(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetFillEmptyLines(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Pad, SaveAStyleOptions_PadComma)
// Test config file writes for astyle padComma option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = PAD_COMMA;
	astyle.SetPadComma(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetPadComma(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Pad, SaveAStyleOptions_PadFirstParenOut)
// Test config file writes for astyle padFirstParenOut option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = PAD_FIRST_PAREN_OUT;
	astyle.SetPadFirstParenOut(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetPadFirstParenOut(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Pad, SaveAStyleOptions_PadHeader)
// Test config file writes for astyle padHeader option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = PAD_HEADER;
	astyle.SetPadHeader(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetPadHeader(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Pad, SaveAStyleOptions_PadOperator)
// Test config file writes for astyle padOperator option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = PAD_OPER;
	astyle.SetPadOperator(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetPadOperator(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Pad, SaveAStyleOptions_PadParen)
// Test config file writes for astyle pad paren options
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// test pad paren all
	key = PAD_PAREN;
	astyle.SetPadParenOutside(true);
	astyle.SetPadParenInside(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("all", value)
	        << "Failure for pad paren all";

	// test pad paren outside
	key = PAD_PAREN;
	astyle.SetPadParenOutside(true);
	astyle.SetPadParenInside(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("out", value)
	        << "Failure for pad paren outside";

	// test pad paren inside
	key = PAD_PAREN;
	astyle.SetPadParenOutside(false);
	astyle.SetPadParenInside(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("in", value)
	        << "Failure for pad paren inside";
}

TEST_F(Config_AStyleF_Pad, SaveAStyleOptions_UnpadParen)
// Test config file writes for astyle unpadParen option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = UNPAD_PAREN;
	astyle.SetUnpadParen(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetUnpadParen(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

//-------------------------------------------------------------------------
// AStyle Config Tests for Formatting Options
//-------------------------------------------------------------------------

struct Config_AStyleF_Format : public Test
{
	// Need this setup because of wxWidgets wxIMPLEMENT_APP_NO_MAIN.
	// It must be done to create a wxFrame object.
	// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
	// See the wxWidgets sample program mfctest.cpp.
	Config_AStyleF_Format()
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = nullptr;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != nullptr);	// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
	}
	virtual ~Config_AStyleF_Format()
	// Need this because of wxIMPLEMENT_APP_NO_MAIN.
	// See the wxWidgets sample program mfctest.cpp.
	{
		wxTheApp->OnExit();			// call wxApp::OnExit()
		wxEntryCleanup();			// free resources from wxEntryStart
	}
};

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_AddBraces)
// Test config file writes for astyle addBraces option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ADD_BRACES;
	astyle.SetAddBraces(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetAddBraces(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_AddOneLineBraces)
// Test config file writes for astyle addOneLineBraces option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ADD_ONE_LINE_BRACES;
	astyle.SetAddOneLineBraces(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetAddOneLineBraces(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_AttachReturnType)
// Test config file writes for astyle attachReturnType option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ATTACH_RETURN_TYPE;
	astyle.SetAttachReturnType(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetAttachReturnType(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_AttachReturnTypeDecl)
// Test config file writes for astyle attachReturnTypeDecl option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ATTACH_RETURN_TYPE_DECL;
	astyle.SetAttachReturnTypeDecl(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetAttachReturnTypeDecl(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_BreakCloseBraces)
// Test config file writes for astyle breakCloseBraces option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = BREAK_CLOSING_BRACES;
	astyle.SetBreakClosingBraces(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetBreakClosingBraces(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_BreakElseIfs)
// Test config file writes for astyle breakElseIfs option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = BREAK_ELSEIFS;
	astyle.SetBreakElseIfs(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetBreakElseIfs(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_BreakOneLineHeaders)
// Test config file writes for astyle breakOneLineHeaders option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = BREAK_ONE_LINE_HEADERS;
	astyle.SetBreakOneLineHeaders(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetBreakOneLineHeaders(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_BreakReturnType)
// Test config file writes for astyle breakReturnType option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = BREAK_RETURN_TYPE;
	astyle.SetBreakReturnType(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetBreakReturnType(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_BreakReturnTypeDecl)
// Test config file writes for astyle breakReturnTypeDecl option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = BREAK_RETURN_TYPE_DECL;
	astyle.SetBreakReturnTypeDecl(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetBreakReturnTypeDecl(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_CloseTemplates)
// Test config file writes for astyle closeTemplates option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = CLOSE_TEMPLATES;
	astyle.SetCloseTemplates(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetCloseTemplates(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_ConvertTabs)
// Test config file writes for astyle convertTabs option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = CONVERT_TABS;
	astyle.SetConvertTabs(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetConvertTabs(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_KeepOneLineBlocks)
// Test config file writes for astyle breakOneLineBlocks option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test false
	key = KEEP_ONE_LINE_BLOCKS;
	astyle.SetBreakOneLineBlocks(false);	// default is false to keep
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test true (delete key)
	astyle.SetBreakOneLineBlocks(true);		// default is true to break
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_KeepOneLineStmts)
// Test config file writes for astyle breakOneLineStmts option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = KEEP_ONE_LINE_STATEMENTS;
	astyle.SetBreakOneLineStmts(false);		// default is false to keep
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetBreakOneLineStmts(true);		// default is true to break
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_MaxCodeLength)
// Test config file writes for astyle max code length
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// test max continuation indent
	key = MAX_CODE_LENGTH;
	astyle.SetMaxCodeLength(100);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("100", value) << "Failure for max code length";

	// test max code length default
	int defaultMaxCodeLength = astyle.GetDefaultMaxCodeLength();
	EXPECT_EQ(0, defaultMaxCodeLength);
	key = MAX_CODE_LENGTH;
	astyle.SetMaxCodeLength(defaultMaxCodeLength);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value)) << "Failure for default max code length";

	// test invalid minimum for max code length, should use minimum (default)
	key = MAX_CODE_LENGTH;
	astyle.SetMaxCodeLength(MAX_CODE_LENGTH_MIN - 1);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	wxString maxCodeLengthMinValue = wxString::Format("%d", MAX_CODE_LENGTH_MIN);
	EXPECT_EQ(maxCodeLengthMinValue, value) << "Failure for invalid max code length";

	// test invalid maximum for max code length, should use maximum
	key = MAX_CODE_LENGTH;
	astyle.SetMaxCodeLength(MAX_CODE_LENGTH_MAX + 1);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	wxString maxCodeLengthMaxValue = wxString::Format("%d", MAX_CODE_LENGTH_MAX);
	EXPECT_EQ(maxCodeLengthMaxValue, value) << "Failure for invalid max code length";
}

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_RemoveBraces)
// Test config file writes for astyle removeBraces option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = REMOVE_BRACES;
	astyle.SetRemoveBraces(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetRemoveBraces(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Format, SaveAStyleOptions_RemoveCommentPrefix)
// Test config file writes for astyle removeCommentPrefix option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = REMOVE_COMMENT_PREFIX;
	astyle.SetRemoveCommentPrefix(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetRemoveCommentPrefix(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

//-------------------------------------------------------------------------
// AStyle Config Tests for Other Options
//-------------------------------------------------------------------------

struct Config_AStyleF_Other : public Test
{
	// Need this setup because of wxWidgets wxIMPLEMENT_APP_NO_MAIN.
	// It must be done to create a wxFrame object.
	// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
	// See the wxWidgets sample program mfctest.cpp.
	Config_AStyleF_Other()
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = nullptr;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != nullptr);	// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
	}
	virtual ~Config_AStyleF_Other()
	// Need this because of wxIMPLEMENT_APP_NO_MAIN.
	// See the wxWidgets sample program mfctest.cpp.
	{
		wxTheApp->OnExit();			// call wxApp::OnExit()
		wxEntryCleanup();			// free resources from wxEntryStart
	}
};

TEST_F(Config_AStyleF_Other, SaveAStyleOptions_PadMethodPrefix)
// Test config file writes for astyle padMethodPrefix option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = PAD_METHOD_PREFIX;
	astyle.SetPadMethodPrefix(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetPadMethodPrefix(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Other, SaveAStyleOptions_UnpadMethodPrefix)
// Test config file writes for astyle unpadMethodPrefix option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = UNPAD_METHOD_PREFIX;
	astyle.SetUnpadMethodPrefix(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetUnpadMethodPrefix(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Other, SaveAStyleOptions_PadReturnType)
// Test config file writes for astyle padReturnType option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = PAD_RETURN_TYPE;
	astyle.SetPadReturnType(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetPadReturnType(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Other, SaveAStyleOptions_UnpadReturnType)
// Test config file writes for astyle unpadReturnType option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = UNPAD_RETURN_TYPE;
	astyle.SetUnpadReturnType(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetUnpadReturnType(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Other, SaveAStyleOptions_AlignMethodColon)
// Test config file writes for astyle alignMethodColon option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ALIGN_METHOD_COLON;
	astyle.SetAlignMethodColon(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.SetAlignMethodColon(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_AStyleF_Other, SaveAStyleOptions_PadMethodColon)
// Test config file writes for astyle padMethodColon option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test pad method colon options
	key = PAD_METHOD_COLON;
	astyle.SetPadMethodColon(COLON_PAD_NONE);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ("none", value);
	astyle.SetPadMethodColon(COLON_PAD_ALL);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ("all", value);
	astyle.SetPadMethodColon(COLON_PAD_AFTER);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ("after", value);
	astyle.SetPadMethodColon(COLON_PAD_BEFORE);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ("before", value);

	// test invalid pad method colon option, should not write
	astyle.SetPadMethodColon(COLON_PAD_NO_CHANGE);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

//-------------------------------------------------------------------------
// StyledTextCtrl Styles Config Tests
//-------------------------------------------------------------------------

struct Config_StcStylesF : public Test
{
	// Need this setup because of wxWidgets wxIMPLEMENT_APP_NO_MAIN.
	// It must be done to create a wxFrame object.
	// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
	// See the wxWidgets sample program mfctest.cpp.
	Config_StcStylesF()
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = nullptr;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != nullptr);	// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
	}
	virtual ~Config_StcStylesF()
	// Need this because of wxIMPLEMENT_APP_NO_MAIN.
	// See the wxWidgets sample program mfctest.cpp.
	{
		wxTheApp->OnExit();			// call wxApp::OnExit()
		wxEntryCleanup();			// free resources from wxEntryStart
	}
};

TEST_F(Config_StcStylesF, GetStcStyleOptions_Default)
// Test GetStcStyleOptions initialization
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	// get the default style vector
	vector<TextStyle> defaults = config.GetDefaultStyleOptions();

	// test the "get" function - should get the default values
	vector<TextStyle> styles = config.GetStcStyleOptions();

	// verify the number of styles
	ASSERT_EQ(defaults.size(), styles.size());

	// verify the default vector
	for (size_t i = 0; i < defaults.size(); i++)
		ASSERT_EQ(defaults[i].style, styles[i].style);
}

TEST_F(Config_StcStylesF, GetStcStyleOptions)
// Test GetStcStyleOptions
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	// get the default style vector
	vector<TextStyle> styles = config.GetDefaultStyleOptions();

	// change the entries
	for (size_t i = 0; i < styles.size(); i++)
	{
		styles[i].bold = true;
		styles[i].italic = false;
		styles[i].fore = wxColor(248, 248, 255);    // ghostwhite
	}

	// save the updated styles
	config.SaveStcStyleOptions(styles);

	// test the "get" function - should get the updated values
	vector<TextStyle> stylesNew = config.GetStcStyleOptions();

	// verify the updated styles - will have the values from the config file
	for (size_t i = 0; i < stylesNew.size(); i++)
	{
		ASSERT_TRUE(stylesNew[i].bold == true);
		ASSERT_TRUE(stylesNew[i].italic == false);
		ASSERT_TRUE(stylesNew[i].fore == wxColor(248, 248, 255));   // ghostwhite
	}
}

TEST_F(Config_StcStylesF, GetStcStyleOptions_NoEntries)
// In GetStcStyleOptions a group has no entries.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	// get the default style vector
	vector<TextStyle> styles = config.GetDefaultStyleOptions();
	// save the default styles
	config.SaveStcStyleOptions(styles);

	// write a group with no entries
	config.SetPath("/Styles/Style-03");
	ASSERT_TRUE(config.DeleteEntry("bold", false));
	ASSERT_TRUE(config.DeleteEntry("italic", false));
	ASSERT_TRUE(config.DeleteEntry("fore", false));
	ASSERT_TRUE(config.DeleteEntry("back", false));
	ASSERT_EQ(0U, config.GetNumberOfEntries());

	// Expect ShowInvalidConfig to be called once for each config file key.
	EXPECT_CALL(config, ShowInvalidConfig(_)).Times(1);
	// test the function
	styles = config.GetStcStyleOptions();
	// the group with no entries should be deleted
	config.SetPath("/Styles");
	EXPECT_EQ(styles.size() - 1, config.GetNumberOfGroups());
}

TEST_F(Config_StcStylesF, GetStcStyleOptions_InvalidStyleNumber)
// In GetStcStyleOptions a style number is invalid.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	// get the default style vector
	vector<TextStyle> styles = config.GetDefaultStyleOptions();
	// save the default styles
	config.SaveStcStyleOptions(styles);

	// write an invalid style number
	ASSERT_TRUE(config.DeleteGroup("/Styles/Style-05"));
	config.SetPath("/Styles/Style-99");		// invalid style number
	config.Write("bold", asTRUE);
	config.Write("italic", asFALSE);
	config.Write("fore", "rgb(248 ,248, 255)");

	// Expect ShowInvalidConfig to be called once for each config file group.
	EXPECT_CALL(config, ShowInvalidConfig(_)).Times(1);
	// test the function
	styles = config.GetStcStyleOptions();

	// the invalid should be deleted
	config.SetPath("/Styles");
	EXPECT_EQ(styles.size() - 1, config.GetNumberOfGroups());
}

TEST_F(Config_StcStylesF, GetStcStyleOptions_ExtraStyleNumber)
// In GetStcStyleOptions there is an extra style number.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	// get the default style vector
	vector<TextStyle> styles = config.GetDefaultStyleOptions();
	// save the default styles
	config.SaveStcStyleOptions(styles);

	// write an extra group
	config.SetPath("/Styles/Style-50");
	config.Write("bold", asTRUE);
	config.Write("italic", asFALSE);
	config.Write("fore", "rgb(248 ,248, 255)");
	// should have an extra group
	config.SetPath("/Styles");
	ASSERT_EQ(styles.size() + 1, config.GetNumberOfGroups());

	// Expect ShowInvalidConfig to be called once for each config group.
	EXPECT_CALL(config, ShowInvalidConfig(_)).Times(1);
	// test the function
	styles = config.GetStcStyleOptions();
	// the invalid should be deleted
	config.SetPath("/Styles");
	EXPECT_EQ(styles.size(), config.GetNumberOfGroups());
}

TEST_F(Config_StcStylesF, GetStcStyleOptions_InvalidForeColor)
// In GetStyleUpdates a fore color is invalid.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	// get the default style vector
	vector<TextStyle> styles = config.GetDefaultStyleOptions();
	// save the default styles
	config.SaveStcStyleOptions(styles);

	// write an invalid color format
	// NOTE: an invalid color value will be changed to 255
	config.SetPath("/Styles/Style-07");
	config.Write("fore", "rgb(0, 0");    // invalid color

	// Expect ShowInvalidConfig to be called once for each config file key.
	EXPECT_CALL(config, ShowInvalidConfig(_)).Times(1);
	// test the function
	styles = config.GetStcStyleOptions();
	// the "fore" entry should be deleted
	config.SetPath("/Styles/Style-07");
	EXPECT_EQ(3U, config.GetNumberOfEntries());
}

TEST_F(Config_StcStylesF, GetStcStyleOptions_InvalidBackColor)
// In GetStyleUpdates a fore color is invalid.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	// get the default style vector
	vector<TextStyle> styles = config.GetDefaultStyleOptions();
	// save the default styles
	config.SaveStcStyleOptions(styles);

	// write an invalid color format
	// NOTE: an invalid color value will be changed to 255
	config.SetPath("/Styles/Style-07");
	config.Write("back", "rgb(0, 0");    // invalid color

	// Expect ShowInvalidConfig to be called once for each config file key.
	EXPECT_CALL(config, ShowInvalidConfig(_)).Times(1);
	// test the function
	styles = config.GetStcStyleOptions();
	// the "back" entry should be deleted
	config.SetPath("/Styles/Style-07");
	EXPECT_EQ(3U, config.GetNumberOfEntries());
}

TEST_F(Config_StcStylesF, GetStcStyleOptions_InvalidKey)
// In GetStyleUpdates a key is invalid.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	// get the default style vector
	vector<TextStyle> styles = config.GetDefaultStyleOptions();
	// save the default styles
	config.SaveStcStyleOptions(styles);

	// write an invalid key
	config.SetPath("/Styles/Style-09");
	config.DeleteEntry("bold", false);
	config.Write("bolf", asTRUE);

	// Expect ShowInvalidConfig to be called once for each config file key.
	EXPECT_CALL(config, ShowInvalidConfig(_)).Times(1);
	// test the function
	styles = config.GetStcStyleOptions();

	// the invalid entry should be deleted
	config.SetPath("/Styles/Style-09");
	EXPECT_EQ(3U, config.GetNumberOfEntries());
}

TEST_F(Config_StcStylesF, GetStcStyleOptions_InvalidSeparator)
// In GetStcStyleOptions invalid separator for the style number.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	// get the default style vector
	vector<TextStyle> styles = config.GetDefaultStyleOptions();
	// save the default styles
	config.SaveStcStyleOptions(styles);

	// write an invalid separator (no dash) in a group name
	config.DeleteGroup("/Styles/Style-02");
	config.SetPath("/Styles/Style 02");
	config.Write("bold", asTRUE);
	config.Write("italic", asFALSE);
	config.Write("bold", "rgb(0, 0, 0)");

	// Expect ShowInvalidConfig to be called once for each config group.
	EXPECT_CALL(config, ShowInvalidConfig(_)).Times(1);
	// test the function
	styles = config.GetStcStyleOptions();
	// the entire invalid group should be deleted
	config.SetPath("/Styles");
	EXPECT_EQ(styles.size() - 1, config.GetNumberOfGroups());
}

TEST_F(Config_StcStylesF, GetStcStyleOptions_NonNumericStyle)
// In GetStcStyleOptions a non-numeric style number.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	// get the default style vector
	vector<TextStyle> styles = config.GetDefaultStyleOptions();
	// save the default styles
	config.SaveStcStyleOptions(styles);

	// write an invalid color value
	config.DeleteGroup("/Styles/Style-04");
	config.SetPath("/Styles/Style-XX");
	config.Write("bold", asTRUE);
	config.Write("italic", asFALSE);
	config.Write("bold", "rgb(0, 0, 0)");

	// Expect ShowInvalidConfig to be called once for each config file key.
	EXPECT_CALL(config, ShowInvalidConfig(_)).Times(1);
	// test the function
	styles = config.GetStcStyleOptions();
	// the entire invalid group should be deleted
	config.SetPath("/Styles");
	EXPECT_EQ(styles.size() - 1, config.GetNumberOfGroups());
}

TEST_F(Config_StcStylesF, SaveStcStyleOptions_GroupNumber)
// Test config file writes for number of groups
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);

	// build the default style vector
	vector<TextStyle> styles = config.GetDefaultStyleOptions();

	// test the function
	config.SaveStcStyleOptions(styles);

	// verify 1 group for "Styles" directory
	config.SetPath("/");
	EXPECT_EQ(1U, config.GetNumberOfGroups())
	        << "Missing Styles directory";

	// verify 1 group for each style
	config.SetPath("/Styles");
	EXPECT_EQ(styles.size(), config.GetNumberOfGroups());
}

TEST_F(Config_StcStylesF, SaveStcStyleOptions_GroupNames)
// Test config file writes for the names of groups
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);

	// enumeration variables
	wxString group;		// style group
	long index;			// don't use this

	// build the default style vector
	vector<TextStyle> styles = config.GetDefaultStyleOptions();

	// test the function
	config.SaveStcStyleOptions(styles);

	// verify group names have a valid two digit style number
	config.SetPath("/Styles");
	bool hasMoreGroups = config.GetFirstGroup(group, index);
	while (hasMoreGroups)
	{
		// verify two digit style number
		int lastDash = group.Find('-', true);
		ASSERT_TRUE(lastDash != wxNOT_FOUND)
		        << "Group name style number not found";
		wxString styleStr = group.Mid(lastDash + 1);
		long styleID;
		ASSERT_TRUE(styleStr.ToLong(&styleID))
		        << "Group name style number not numeric";
		// find style ID in the vector
		int vectorStyleID = -1;
		for (size_t i = 0; i < styles.size(); i++)
		{
			if (styleID == styles[i].style)
			{
				vectorStyleID = styles[i].style;
				break;
			}
		}
		EXPECT_EQ(styleID, vectorStyleID)
		        << "Group name style number not in vector";
		// get the next entry
		hasMoreGroups = config.GetNextGroup(group, index);
	}
}

TEST_F(Config_StcStylesF, SaveStcStyleOptions_Entries)
// Test config file writes for valid entries
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);

	// enumeration variables
	wxString group;		// style group
	long index;			// don't use this

	// build the default style vector
	vector<TextStyle> styles = config.GetDefaultStyleOptions();

	// test the function
	config.SaveStcStyleOptions(styles);

	// verify key names and values for each group
	wxString value;
	wxColour color;
	config.SetPath("/Styles");
	bool hasMoreGroups = config.GetFirstGroup(group, index);
	while (hasMoreGroups)
	{
		config.SetPath("/Styles/" + group);
		// verify 4 entries for each group
		ASSERT_EQ(4U, config.GetNumberOfEntries()) << "Wrong number of styles entries";
		// verify each entry
		ASSERT_TRUE(config.Read("bold", &value)) << "Missing key for bold";
		ASSERT_TRUE(value == asTRUE || value == asFALSE) << "Bad value for bold";
		ASSERT_TRUE(config.Read("italic", &value)) << "Missing key for italic";
		ASSERT_TRUE(value == asTRUE || value == asFALSE) << "Bad value for italic'";
		ASSERT_TRUE(config.Read("fore", &value)) << "Missing key for fore";
		ASSERT_TRUE(color.Set(value)) << "Bad value for fore";
		ASSERT_TRUE(config.Read("back", &value)) << "Missing key for back";
		ASSERT_TRUE(color.Set(value)) << "Bad value for back";
		config.SetPath("/Styles");
		hasMoreGroups = config.GetNextGroup(group, index);
	}
}

//-------------------------------------------------------------------------
// Frame Config Tests
//-------------------------------------------------------------------------

struct Config_FrameF : public Test
{
	// Need this setup because of wxWidgets wxIMPLEMENT_APP_NO_MAIN.
	// It must be done to create a wxFrame object.
	// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
	// See the wxWidgets sample program mfctest.cpp.
	Config_FrameF()
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = nullptr;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != nullptr);	// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
	}
	virtual ~Config_FrameF()
	// Need this because of wxIMPLEMENT_APP_NO_MAIN.
	// See the wxWidgets sample program mfctest.cpp.
	{
		wxTheApp->OnExit();			// call wxApp::OnExit()
		wxEntryCleanup();			// free resources from wxEntryStart
	}
};

TEST_F(Config_FrameF, InitializeFile)
// Test if config file is initialized if there are no entries.
// This tests the function void Config::InitializeConfigFile().
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	ASSERT_TRUE(frame.GetCommentFont().IsOk());
	ASSERT_TRUE(frame.GetDefaultFont().IsOk());

	// build keys array
	// these keys are always added to the config file
	wxArrayString keys;
	keys.Add(LINE_NUMBERS);
	keys.Add(TOOLBAR_TOOLTIPS);
	keys.Add(DIALOG_TOOLTIPS);
	keys.Add(LOAD_SESSION);
	keys.Add(SHOW_TOOLBAR);
	keys.Add(SHOW_STATUSBAR);
	keys.Add(DEFAULT_FONT_FACE);
	keys.Add(DEFAULT_FONT_SIZE);
	keys.Add(COMMENT_FONT_FACE);
	keys.Add(COMMENT_FONT_SIZE);

	// verify no keys are present in config file
	config.SetPath("/");
	ASSERT_EQ(0U, config.GetNumberOfEntries(true));

	// Expect ShowInvalidConfig to not be called.
	// Expect SetEditorOrViewOption to be called once for each config file key.
	// The return value of true will indicate that the key is invalid.
	for (size_t i = 0; i < keys.GetCount(); i++)
	{
		EXPECT_CALL(config, ShowInvalidConfig(keys[i])).Times(0);
		EXPECT_CALL(frame, SetEditorOrViewOption(keys[i], _)).Times(1);
		ON_CALL(frame, SetEditorOrViewOption(keys[i], _)).WillByDefault(Return(true));
	}

	// test the function, InitializeFile should be called
	config.GetEditorAndViewOptions();

	// verify keys were added by Config::InitializeConfigFile()
	config.SetPath("/");
	wxString value;
	for (size_t i = 0; i < keys.GetCount(); i++)
		EXPECT_TRUE(config.Read(keys[i], &value));
	ASSERT_EQ(keys.GetCount(), config.GetNumberOfEntries(true));
}

TEST_F(Config_FrameF, GetEditorAndViewOptions)
// Test config file gets for editor and view options.
// GetNextEntry is used for the read so only a few options are checked.
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);

	// build keys array
	wxArrayString keys;
	keys.Add(TOOLBAR_TOOLTIPS);
	keys.Add(DIALOG_TOOLTIPS);
	keys.Add(LINE_NUMBERS);
	keys.Add(WHITESPACE);
	keys.Add(MONOSPACE);

	// write test values
	config.SetPath("/");
	for (size_t i = 0; i < keys.GetCount(); i++)
		config.Write(keys[i], asTRUE);
	ASSERT_EQ(keys.GetCount(), config.GetNumberOfEntries());

	// Expect ShowInvalidConfig to not be called.
	// Expect SetEditorOrViewOption to be called once for each config file key.
	// The return value of true will indicate that the key is valid.
	for (size_t i = 0; i < keys.GetCount(); i++)
	{
		EXPECT_CALL(config, ShowInvalidConfig(keys[i])).Times(0);
		EXPECT_CALL(frame, SetEditorOrViewOption(keys[i], _)).Times(1);
		ON_CALL(frame, SetEditorOrViewOption(keys[i], _)).WillByDefault(Return(true));
	}

	// test the function
	config.GetEditorAndViewOptions();

	// verify no config file keys were deleted
	config.SetPath("/");
	EXPECT_EQ(keys.GetCount(), config.GetNumberOfEntries());
}

TEST_F(Config_FrameF, GetEditorAndViewOptions_InvalidKeys)
// Test config file gets for editor and view options.
// Invalid keys in the config file should be deleted.
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);

	// build keys array
	wxArrayString keys;
	keys.Add("invalid-key-1");
	keys.Add("invalid-key-2");
	keys.Add("invalid-key-3");
	keys.Add("invalid-key-4");
	// write keys to config
	config.SetPath("/");
	for (size_t i = 0; i < keys.GetCount(); i++)
		config.Write(keys[i], asTRUE);
	// verify the number of config file keys
	ASSERT_EQ(keys.GetCount(), config.GetNumberOfEntries());

	// Expect ShowInvalidConfig to be called once for each config file key.
	// Expect SetEditorOrViewOption to be called once for each config file key.
	// The return value of false will indicate that the key is invalid.
	for (size_t i = 0; i < keys.GetCount(); i++)
	{
		EXPECT_CALL(config, ShowInvalidConfig(keys[i])).Times(1);
		EXPECT_CALL(frame, SetEditorOrViewOption(keys[i], _)).Times(1);
		ON_CALL(frame, SetEditorOrViewOption(keys[i], _)).WillByDefault(Return(false));
	}

	// test the function
	config.GetEditorAndViewOptions();
	// verify that all config file keys were deleted
	config.SetPath("/");
	EXPECT_EQ(0U, config.GetNumberOfEntries());
}

TEST_F(Config_FrameF, GetEditorAndViewOptions_InvalidValues)
// Test config file gets for editor and view options.
// Invalid values in the config file should be deleted.
// NOTE: Float and double values are written to config as strings.
{
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);

	// test reading bool values
	config.SetPath("/");
	config.Write(TOOLBAR_TOOLTIPS, true);
	config.Write(LINE_NUMBERS, false);
	ASSERT_EQ(2U, config.GetNumberOfEntries());
	// Expect SetEditorOrViewOption to not be called for Windows.
	// Expect it to be called twice for Linux.
	// Windows uses the registry. Linux uses a config file.
#ifdef __WXMSW__
	EXPECT_CALL(frame, SetEditorOrViewOption(_, _)).Times(0);
#else
	EXPECT_CALL(frame, SetEditorOrViewOption(_, _)).Times(2);
#endif
	// Expect ShowInvalidConfig to be called once for each config file key.
	// EditorAndViewMenuOptions are tested in another module.
	EXPECT_CALL(config, ShowInvalidConfig(_)).Times(2);
	// test the function
	config.GetEditorAndViewOptions();
	// verify that all bool config file keys were deleted
	config.SetPath("/");
	EXPECT_EQ(0U, config.GetNumberOfEntries());

	// test reading long values
	long valueLong;
	config.SetPath("/");
	valueLong = 1;
	config.Write(TOOLBAR_TOOLTIPS, valueLong);
	valueLong = 2;
	config.Write(LINE_NUMBERS, valueLong);
	ASSERT_EQ(2U, config.GetNumberOfEntries());
	// Expect SetEditorOrViewOption to not be called for Windows.
	// Expect it to be called twice for Linux.
	// Windows uses the registry. Linux uses a config file.
#ifdef __WXMSW__
	EXPECT_CALL(frame, SetEditorOrViewOption(_, _)).Times(0);
#else
	EXPECT_CALL(frame, SetEditorOrViewOption(_, _)).Times(2);
#endif
	// Expect ShowInvalidConfig to be called once for each config file key.
	// EditorAndViewMenuOptions are tested in another module.
	EXPECT_CALL(config, ShowInvalidConfig(_)).Times(2);
	// test the function
	config.GetEditorAndViewOptions();
	// verify that all long config file keys were deleted
	config.SetPath("/AStyle");
	EXPECT_EQ(0U, config.GetNumberOfEntries());
}

//-------------------------------------------------------------------------
// Editor Config Tests
//-------------------------------------------------------------------------

struct Config_EditorF : public Test
{
	// Need this setup because of wxWidgets wxIMPLEMENT_APP_NO_MAIN.
	// It must be done to create a wxFrame object.
	// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
	// See the wxWidgets sample program mfctest.cpp.
	Config_EditorF()
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = nullptr;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != nullptr);	// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
	}
	virtual ~Config_EditorF()
	// Need this because of wxIMPLEMENT_APP_NO_MAIN.
	// See the wxWidgets sample program mfctest.cpp.
	{
		wxTheApp->OnExit();			// call wxApp::OnExit()
		wxEntryCleanup();			// free resources from wxEntryStart
	}
};

TEST_F(Config_EditorF, SaveEditorOptions_AlwaysSaved)
// Test config file writes for editor options that are always saved
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	ASSERT_TRUE(frame.GetCommentFont().IsOk());
	ASSERT_TRUE(frame.GetDefaultFont().IsOk());
	wxString value;				// value of config key

	// build keys for editor options that are always saved
	wxArrayString keys;
	keys.Add(ASTYLE_DLG_PAGE);
	keys.Add(COMMENT_FONT_FACE);
	keys.Add(COMMENT_FONT_SIZE);
	keys.Add(DEFAULT_FONT_FACE);
	keys.Add(DEFAULT_FONT_SIZE);
	keys.Add(EDITOR_DLG_PAGE);
	keys.Add(FILE_FILTER_INDEX);

	// test saves - the Editor fake test object has the default values
	frame.SetFrameBoolReturn(false);		// set return value getters
	ASSERT_EQ(0U, config.GetNumberOfEntries());
	config.SaveEditorOptions();

	// check the saves
	config.SetPath("/");
	for (size_t i = 0; i < keys.GetCount(); i++)
		EXPECT_TRUE(config.Read(keys[i], &value)) << keys[i].c_str();
	// verify the number of config file keys checked
	EXPECT_EQ(keys.GetCount(), config.GetNumberOfEntries());
}

TEST_F(Config_EditorF, SaveEditorOptions_HideFindAfterMatch)
// Test config file writes for editor option m_hideDialogAfterMatch
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = HIDE_FIND;
	frame.SetFrameBoolReturn(true);	// set return value for getter
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_EditorF, SaveEditorOptions_IsMaximized)
// Test config file writes for frame wxTopLevelWindow function IsMaximized
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = FRAME_MAXIMIZED;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_EditorF, SaveEditorOptions_LoadSession)
// Test config file writes for frame wxTopLevelWindow function loadSession
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = LOAD_SESSION;
	frame.SetFrameLoadSession(true);
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameLoadSession(false);
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_EditorF, SaveEditorOptions_ShowDialogTips)
// Test config file writes for frame option m_showDialogTips
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = DIALOG_TOOLTIPS;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_EditorF, SaveEditorOptions_ShowToolTips)
// Test config file writes for frame option m_showToolTips
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = TOOLBAR_TOOLTIPS;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_EditorF, SaveEditorOptions_TestOptions)
// Test config file writes for frame option m_testOptions.
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test write
	key = TEST_OPTIONS;
	wxString testOptions = "option";
	config.SaveTestOptions(testOptions);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(testOptions.wc_str(), value.wc_str());

	// test delete
	config.SaveTestOptions(wxEmptyString);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_EditorF, SaveEditorOptions_UseBottomTabs)
// Test config file writes for frame option m_useBottomTabs
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = USE_BOTTOM_TABS;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_EditorF, SaveEditorOptions_UseSmallToolbar)
// Test config file writes for frame option m_useSmallToolbar
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = USE_SMALL_TOOLBAR;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_EditorF, SaveEditorOptions_WrapSearch)
// Test config file writes for editor option m_wrapSearch
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = WRAP_SEARCH;
	frame.SetFrameBoolReturn(true);	// set return value for getter
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveEditorOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

//-------------------------------------------------------------------------
// View Menu Config Tests
//-------------------------------------------------------------------------

struct Config_ViewMenuF : public Test
{
	// Need this setup because of wxWidgets wxIMPLEMENT_APP_NO_MAIN.
	// It must be done to create a wxFrame object.
	// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
	// See the wxWidgets sample program mfctest.cpp.
	Config_ViewMenuF()
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = nullptr;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != nullptr);	// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
	}
	virtual ~Config_ViewMenuF()
	// Need this because of wxIMPLEMENT_APP_NO_MAIN.
	// See the wxWidgets sample program mfctest.cpp.
	{
		wxTheApp->OnExit();			// call wxApp::OnExit()
		wxEntryCleanup();			// free resources from wxEntryStart
	}

};

TEST_F(Config_ViewMenuF, SaveViewMenuOptions_ActiveLine)
// Test config file writes for menu option ID_VIEW_ACTIVELINE
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ACTIVE_LINE;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_ViewMenuF, SaveViewMenuOptions_EndOfLine)
// Test config file writes for menu option ID_VIEW_ENDLINE
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = END_OF_LINE;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_ViewMenuF, SaveViewMenuOptions_IndentGuides)
// Test config file writes for menu option ID_VIEW_INDENTGUIDES
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_GUIDES;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_ViewMenuF, SaveViewMenuOptions_LineNumbers)
// Test config file writes for menu option ID_VIEW_LINENUMBERS
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = LINE_NUMBERS;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_ViewMenuF, SaveViewMenuOptions_MonoSpace)
// Test config file writes for menu option ID_VIEW_MONOSPACE
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = MONOSPACE;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_ViewMenuF, SaveViewMenuOptions_SelectionMargin)
// Test config file writes for menu option ID_VIEW_MARGIN
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = SELECTION_MARGIN;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_ViewMenuF, SaveViewMenuOptions_StatusBar)
// Test config file writes for menu option ID_VIEW_STATUSBAR
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = SHOW_STATUSBAR;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_ViewMenuF, SaveViewMenuOptions_Toolbar)
// Test config file writes for menu option ID_VIEW_TOOLBAR
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = SHOW_TOOLBAR;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_ViewMenuF, SaveViewMenuOptions_WhiteSpace)
// Test config file writes for menu option ID_VIEW_WHITESPACE
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = WHITESPACE;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST_F(Config_ViewMenuF, SaveViewMenuOptions_WordWrap)
// Test config file writes for menu option ID_VIEW_WORDWRAP
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = WORD_WRAP;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions();
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

//-------------------------------------------------------------------------
// Session Config Tests
//-------------------------------------------------------------------------

struct Config_SessionF : public Test
{
	// Need this setup because of wxWidgets wxIMPLEMENT_APP_NO_MAIN.
	// It must be done to create a wxFrame object.
	// Without it a SEH exception with code 0xc0000005 is thrown in the test body.
	// See the wxWidgets sample program mfctest.cpp.
	Config_SessionF()
	{
		// initialize wxWidgets
		int argc = 0;
		wxChar** argv = nullptr;
		wxEntryStart(argc, argv);		// initialize wxWidgets
		wxASSERT(wxTheApp != nullptr);	// check wxApp*
		wxTheApp->CallOnInit();			// call wxApp::OnInit()
	}
	virtual ~Config_SessionF()
	// Need this because of wxIMPLEMENT_APP_NO_MAIN.
	// See the wxWidgets sample program mfctest.cpp.
	{
		wxTheApp->OnExit();			// call wxApp::OnExit()
		wxEntryCleanup();			// free resources from wxEntryStart
	}
	void AddTestFilesToConfig(Config_Test* config, wxArrayString& filePaths)
	{
		config->SetPath("/Session");
		// save keys to config file
		for (size_t i = 0; i < filePaths.GetCount(); i++)
		{
			wxFileName filePath = filePaths[i];
			wxString key = SESSION_FILE + wxString::Format("%d", static_cast<int>(i + 1));
			config->Write(key, filePath.GetFullPath());
		}
		ASSERT_EQ(filePaths.GetCount(), config->GetNumberOfEntries());
	}
	wxArrayString BuildExistingTestFiles(int numFiles)
	{
#ifdef _WIN32
		wxString filePathStr = "C:\\Users\\UserName\\existing%d.cpp";
#else
		wxString filePathStr = "/home/username/existing%d.cpp";
#endif
		wxArrayString filePaths;
		for (int i = 0; i < numFiles; i++)
			filePaths.Add(wxString::Format(filePathStr, i + 1));
		return filePaths;
	}
	wxArrayString BuildNewTestFiles(int numFiles)
	{
#ifdef _WIN32
		wxString filePathStr = "C:\\Users\\UserName\\newfile%d.cpp";
#else
		wxString filePathStr = "/home/username/newfile%d.cpp";
#endif
		wxArrayString filePaths;
		for (int i = 0; i < numFiles; i++)
			filePaths.Add(wxString::Format(filePathStr, i + 1));
		return filePaths;
	}
	void VerifyConfigEntries(Config_Test* config, wxArrayString& filePaths)
	{
		config->SetPath("/Session");
		int fileCount = filePaths.GetCount();
		int configCount = config->GetNumberOfEntries();
		wxString key;
		wxString value;
		int i = 0;
		for (i = 0; i < configCount; i++)
		{
			key = SESSION_FILE + wxString::Format("%d", i + 1);
			if (config->Read(key, &value))
				EXPECT_EQ(value.ToStdString(), filePaths[i].ToStdString())
				        << "Value is not correct path";
			else
				EXPECT_EQ(key.ToStdString(), "")
				        << "Key not found in config";
		}
		// report missing entries
		for (; i < fileCount; i++)
			EXPECT_EQ(filePaths[1].ToStdString(), "")
			        << "Value not found in config";
	}
};

TEST_F(Config_SessionF, GetSessionFiles)
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);

	// verify no keys are present in config file
	config.SetPath("/");
	ASSERT_EQ(0U, config.GetNumberOfEntries(true)) << "Config not empty";
	config.SetPath("/Session");
	// build existing files
	const size_t numExisting = 2;
	wxArrayString existingFilePaths = BuildExistingTestFiles(numExisting);
	// add existing files to config
	AddTestFilesToConfig(&config, existingFilePaths);
	ASSERT_EQ(numExisting, config.GetNumberOfEntries(true)) << "Config not initialized";

	// call method under test, filePaths contains 2 entries
	frame.SetFrameLoadSession(true);
	wxArrayString filePaths = config.GetSessionFiles();
	EXPECT_EQ(numExisting, filePaths.GetCount());
}

TEST_F(Config_SessionF, GetSessionFiles_NoOptionSet)
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);

	// verify no keys are present in config file
	config.SetPath("/");
	ASSERT_EQ(0U, config.GetNumberOfEntries(true)) << "Config not empty";
	config.SetPath("/Session");
	// build existing files
	const size_t numExisting = 2;
	wxArrayString existingFilePaths = BuildExistingTestFiles(numExisting);
	// add existing files to config
	AddTestFilesToConfig(&config, existingFilePaths);
	ASSERT_EQ(numExisting, config.GetNumberOfEntries(true)) << "Config not initialized";

	// call method under test, filePaths contains 0 entries
	frame.SetFrameLoadSession(false);
	wxArrayString filePaths = config.GetSessionFiles();
	EXPECT_EQ(0U, filePaths.GetCount());
}

TEST_F(Config_SessionF, SaveSessionFiles_AddFiles)
// Test SaveSessionFiles with 0 entries in config
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);

	// verify no keys are present in config file
	config.SetPath("/");
	ASSERT_EQ(0U, config.GetNumberOfEntries(true)) << "Config not empty";
	config.SetPath("/Session");
	// build new files
	const size_t numNew = 2;
	wxArrayString newFilePaths = BuildNewTestFiles(numNew);
	// add files to fake notebook
	frame.SetFrameNewFilePaths(newFilePaths);
	frame.SetFrameLoadSession(true);

	// call method under test, config contains 0 entries
	ASSERT_EQ(0U, config.GetNumberOfEntries(true)) << "Config not initialized";
	config.SaveSessionFiles();

	// verify keys added by Config::InitializeConfigFile()
	EXPECT_EQ(numNew, config.GetNumberOfEntries());
	VerifyConfigEntries(&config, newFilePaths);
}

TEST_F(Config_SessionF, SaveSessionFiles_ReplaceAndDeleteFiles)
// Test SaveSessionFiles with entries in config
// Config entries must be replaced and the excess deleted
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);

	// verify no keys are present in config file
	config.SetPath("/");
	ASSERT_EQ(0U, config.GetNumberOfEntries(true)) << "Config not empty";
	config.SetPath("/Session");
	// build existing files
	const size_t numExisting = 3;
	wxArrayString existingFilePaths = BuildExistingTestFiles(numExisting);
	// add existing files to config
	AddTestFilesToConfig(&config, existingFilePaths);
	// build new files
	const size_t numNew = 2;
	wxArrayString newFilePaths = BuildNewTestFiles(numNew);
	// add new files to fake notebook
	frame.SetFrameNewFilePaths(newFilePaths);
	frame.SetFrameLoadSession(true);

	// call method under test, config contains 3 entries
	ASSERT_EQ(numExisting, config.GetNumberOfEntries(true)) << "Config not initialized";
	config.SaveSessionFiles();

	// verify keys added by Config::InitializeConfigFile()
	EXPECT_EQ(numNew, config.GetNumberOfEntries());
	VerifyConfigEntries(&config, newFilePaths);
}

TEST_F(Config_SessionF, SaveSessionFiles_DeleteAllFiles)
// Test SaveSessionFiles with entries in config
// Config entries must be deleted because of 0 new files
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);

	// verify no keys are present in config file
	config.SetPath("/");
	ASSERT_EQ(0U, config.GetNumberOfEntries(true)) << "Config not empty";
	config.SetPath("/Session");
	// build existing files
	const size_t numExisting = 3;
	wxArrayString existingFilePaths = BuildExistingTestFiles(numExisting);
	// add existing files to config
	AddTestFilesToConfig(&config, existingFilePaths);
	// no files added to fake notebook
	frame.SetFrameLoadSession(true);

	// call method under test, config contains 3 entries
	ASSERT_EQ(numExisting, config.GetNumberOfEntries(true)) << "Config not initialized";
	config.SaveSessionFiles();

	// verify all keys and group header deleted by Config::InitializeConfigFile()
	config.SetPath("/");
	EXPECT_EQ(0U, config.GetNumberOfEntries());
	wxArrayString emptyArray;
	VerifyConfigEntries(&config, emptyArray);
}

TEST_F(Config_SessionF, SaveSessionFiles_NoOptionSet)
// Test SaveSessionFiles with entries in config
// Config entries must be deleted because of loadSession not set
{
	// create objects
	ASEditor editor;
	ASFrame frame(&editor);
	Config_Test config(CONFIG_TEST_NAME, &frame);

	// verify no keys are present in config file
	config.SetPath("/");
	ASSERT_EQ(0U, config.GetNumberOfEntries(true)) << "Config not empty";
	config.SetPath("/Session");
	// build existing files
	const size_t numExisting = 2;
	wxArrayString existingFilePaths = BuildExistingTestFiles(numExisting);
	// add existing files to config
	AddTestFilesToConfig(&config, existingFilePaths);
	// build new files
	const size_t numNew = 2;
	wxArrayString newFilePaths = BuildNewTestFiles(numNew);
	// add new files to fake notebook
	// these will not be added to config because of false loadSession option
	frame.SetFrameNewFilePaths(newFilePaths);
	frame.SetFrameLoadSession(false);

	// call method under test, config contains 2 entries
	ASSERT_EQ(numExisting, config.GetNumberOfEntries(true)) << "Config not initialized";
	config.SaveSessionFiles();

	// verify all keys and group header deleted by Config::InitializeConfigFile()
	config.SetPath("/");
	EXPECT_EQ(0U, config.GetNumberOfEntries());
	wxArrayString emptyArray;
	VerifyConfigEntries(&config, emptyArray);
}

//----------------------------------------------------------------------------

}  // anonymous namespace
