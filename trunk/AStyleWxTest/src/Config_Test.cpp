// AStyleConfig_Test.cpp
// Copyright (c) 2017 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#include "Config_Test.h"

// for gmock macros
using namespace testing;

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
// anonymous namespace
//----------------------------------------------------------------------------

namespace {
//
//-------------------------------------------------------------------------
// AStyle Config Tests for Invalid Keys
//-------------------------------------------------------------------------

TEST(Config_AStyle, GetAStyleOptions_InvalidKeys)
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
	// Expect SetAStyleOptionFromConfig to be called once for each config file key.
	// The return value of false will indicate that the key is invalid.
	// AStyleIFace methods are tested in the AStyleIFace_Test module.
	for (size_t i = 0; i < keys.GetCount(); i++)
	{
		EXPECT_CALL(config, ShowInvalidConfig(keys[i])).Times(1);
		EXPECT_CALL(astyle, SetAStyleOptionFromConfig(keys[i], _)).Times(1);
		ON_CALL(astyle, SetAStyleOptionFromConfig(keys[i], _)).WillByDefault(Return(false));
	}
	// test the function
	config.GetAStyleOptions(&astyle);
	// verify that all config file keys were deleted
	config.SetPath("/AStyle");
	EXPECT_EQ(0U, config.GetNumberOfEntries());
}

TEST(Config_AStyle, GetAStyleOptions_InvalidValues)
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
	// Expect SetAStyleOptionFromConfig to not be called for Windows.
	// Expect it to be called twice for Linux.
	// Windows uses the registry. Linux uses a config file.
#ifdef __WXMSW__
	EXPECT_CALL(astyle, SetAStyleOptionFromConfig(_, _)).Times(0);
#else
	EXPECT_CALL(astyle, SetAStyleOptionFromConfig(_, _)).Times(2);
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
	// Expect SetAStyleOptionFromConfig to not be called for Windows.
	// Expect it to be called twice for Linux.
	// Windows uses the registry. Linux uses a config file.
#ifdef __WXMSW__
	EXPECT_CALL(astyle, SetAStyleOptionFromConfig(_, _)).Times(0);
#else
	EXPECT_CALL(astyle, SetAStyleOptionFromConfig(_, _)).Times(2);
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

TEST(Config_AStyle, GetAStyleOptions)
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
	// Expect SetAStyleOptionFromConfig to be called once for each config file key.
	// The return value of true will indicate that the key is valid.
	// AStyleIFace methods are tested in the AStyleIFace_Test module.
	for (size_t i = 0; i < keys.GetCount(); i++)
	{
		EXPECT_CALL(config, ShowInvalidConfig(keys[i])).Times(0);
		EXPECT_CALL(astyle, SetAStyleOptionFromConfig(keys[i], _)).Times(1);
		ON_CALL(astyle, SetAStyleOptionFromConfig(keys[i], _)).WillByDefault(Return(true));
	}
	// test the function
	config.GetAStyleOptions(&astyle);
}

//-------------------------------------------------------------------------
// AStyle Config Tests for Style Options
//-------------------------------------------------------------------------

TEST(Config_AStyle_Styles, SaveAStyleOptions_StylesAll)
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
		{ STYLE_BANNER,     BANNER     },
		{ STYLE_GNU,        GNU        },
		{ STYLE_LINUX,      LINUXX     },
		{ STYLE_HORSTMANN,  HORSTMANN  },
		{ STYLE_1TBS,       oneTBS     },
		{ STYLE_GOOGLE,     GOOGLE     },
		{ STYLE_MOZILLA,    MOZILLA    },
		{ STYLE_PICO,       PICO       },
		{ STYLE_LISP,       LISP       }
	};

	// test style options
	key = STYLE;
	size_t numStyles = sizeof(style) / sizeof(style[0]);
	for (size_t i = 0; i < numStyles; i++)
	{
		astyle.setBraceStyle(style[i].styleNum);
		config.SaveAStyleOptions(&astyle);
		config.SetPath("/AStyle");
		config.Read(key, &value);
		EXPECT_EQ(style[i].styleName, value)
		        << "Failure for style = " << style[i].styleName;
	}

	// test style none
	key = STYLE;
	astyle.setBraceStyle(STYLE_NONE);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for style = none";

	// test invalid style
	key = STYLE;
	astyle.setBraceStyle(STYLE_END);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid style";
}

//-------------------------------------------------------------------------
// AStyle Config Tests for Tab Options
//-------------------------------------------------------------------------

TEST(Config_AStyle_Tabs, SaveAStyleOptions_IndentSpaces_Default)
// Test the default indent spaces options.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// indent 4 spaces, no entries for indent-type and indent-length
	astyle.setIndentType(INDENT_SPACES);
	astyle.setIndentLength(4);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(INDENT_TYPE, &value));
	EXPECT_FALSE(config.Read(INDENT_LENGTH, &value));
	EXPECT_FALSE(config.Read(USE_TAB_LENGTH, &value));
	EXPECT_FALSE(config.Read(TAB_LENGTH, &value));
}

TEST(Config_AStyle_Tabs, SaveAStyleOptions_IndentTabs_Default)
// Test the default indent tabs options.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// indent 4 tabs, no entry for indent-length
	astyle.setIndentType(INDENT_TABS);
	astyle.setIndentLength(4);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_TRUE(config.Read(INDENT_TYPE, &value));
	EXPECT_STREQ(INDENT_TYPE_TAB, value);
	EXPECT_FALSE(config.Read(INDENT_LENGTH, &value));
	EXPECT_FALSE(config.Read(USE_TAB_LENGTH, &value));
	EXPECT_FALSE(config.Read(TAB_LENGTH, &value));
}

TEST(Config_AStyle_Tabs, SaveAStyleOptions_IndentForce_Default)
// Test the default indent force tabs options.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// indent 4 force-tabs, no entry for indent-length
	astyle.setIndentType(INDENT_FTABS);
	astyle.setIndentLength(4);
	astyle.setUseTabLength(false);		// do not use indent=force-tab-x
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_TRUE(config.Read(INDENT_TYPE, &value));
	EXPECT_STREQ(INDENT_TYPE_FTAB, value);
	EXPECT_FALSE(config.Read(INDENT_LENGTH, &value));
	EXPECT_FALSE(config.Read(USE_TAB_LENGTH, &value));
	EXPECT_FALSE(config.Read(TAB_LENGTH, &value));
}

TEST(Config_AStyle_Tabs, SaveAStyleOptions_Indent)
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
		astyle.setIndentType(indent[i].indentNum);
		astyle.setIndentLength(indent[i].indentLen);
		astyle.setUseTabLength(false);
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

TEST(Config_AStyle_Tabs, SaveAStyleOptions_Indent_ForceTab_X)
// Test config file writes for astyle indent-force-tab-x options
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// indent 4, tab-length 8, no entry for  tab-length or indent-length
	astyle.setIndentType(INDENT_FTABS);
	astyle.setIndentLength(4);
	astyle.setUseTabLength(true);
	astyle.setTabLength(8);
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
	astyle.setIndentType(INDENT_FTABS);
	astyle.setIndentLength(4);
	astyle.setUseTabLength(true);
	astyle.setTabLength(4);
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
	astyle.setIndentType(INDENT_FTABS);
	astyle.setIndentLength(5);
	astyle.setUseTabLength(true);
	astyle.setTabLength(5);
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
	astyle.setIndentType(INDENT_FTABS);
	astyle.setIndentLength(3);
	astyle.setUseTabLength(true);
	astyle.setTabLength(6);
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

TEST(Config_AStyle_Tabs, SaveAStyleOptions_Indent_UseTabLen_Sans)
// Test config file writes for astyle when useTabLength should have no effect.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// indent spaces, no entry for tab-length even if useTabLength is set
	astyle.setIndentType(INDENT_SPACES);
	astyle.setIndentLength(3);
	astyle.setUseTabLength(true);
	astyle.setTabLength(6);
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
	astyle.setIndentType(INDENT_TABS);
	astyle.setIndentLength(5);
	astyle.setUseTabLength(true);
	astyle.setTabLength(10);
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
	astyle.setIndentType(INDENT_FTABS);
	astyle.setIndentLength(5);
	astyle.setUseTabLength(false);
	astyle.setTabLength(10);
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

TEST(Config_AStyle_Modifier, SaveAStyleOptions_AttachNamespace)
// Test config file writes for astyle attachNamespace option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ATTACH_NAMESPACES;
	astyle.setAttachNamespace(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setAttachNamespace(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Modifier, SaveAStyleOptions_AttachClass)
// Test config file writes for astyle attachClass option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ATTACH_CLASSES;
	astyle.setAttachClass(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setAttachClass(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Modifier, SaveAStyleOptions_AttachInline)
// Test config file writes for astyle attachInline option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ATTACH_INLINES;
	astyle.setAttachInline(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setAttachInline(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Modifier, SaveAStyleOptions_AttachExternC)
// Test config file writes for astyle attachExternC option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ATTACH_EXTERN_C;
	astyle.setAttachExternC(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setAttachExternC(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Modifier, SaveAStyleOptions_AttachClosingWhile)
// Test config file writes for astyle attachClosingWhile option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ATTACH_CLOSING_WHILE;
	astyle.setAttachClosingWhile(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setAttachClosingWhile(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

//-------------------------------------------------------------------------
// AStyle Config Tests for Indentation Options
//-------------------------------------------------------------------------

TEST(Config_AStyle_Indent, SaveAStyleOptions_AfterParenIndent)
// Test config file writes for astyle afterParenIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_AFTER_PARENS;
	astyle.setAfterParenIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setAfterParenIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Indent, SaveAStyleOptions_CaseIndent)
// Test config file writes for astyle caseIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_CASES;
	astyle.setCaseIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setCaseIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Indent, SaveAStyleOptions_ClassIndent)
// Test config file writes for astyle classIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_CLASSES;
	astyle.setClassIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setClassIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Indent, SaveAStyleOptions_Col1CommentIndent)
// Test config file writes for astyle col1CommentIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_COL1_COMMENTS;
	astyle.setCol1CommentIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setCol1CommentIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Indent, SaveAStyleOptions_ContinuationIndent)
// Test config file writes for astyle continuation indent
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// test continuation indent
	key = INDENT_CONTINUATION;
	astyle.setContinuationIndent(2);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("2", value)
	        << "Failure for continuation indent";

	// test continuation indent default
	int defaultContinuationIndent = astyle.getDefaultContinuationIndent();
	EXPECT_TRUE(defaultContinuationIndent == 1);
	key = INDENT_CONTINUATION;
	astyle.setContinuationIndent(defaultContinuationIndent);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for default continuation indent";

	// test invalid minimum for continuation indent
	key = INDENT_CONTINUATION;
	astyle.setContinuationIndent(-1);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid continuation indent" << value;

	// test invalid maximum for continuation indent
	key = INDENT_CONTINUATION;
	astyle.setContinuationIndent(5);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid continuation indent";
}

TEST(Config_AStyle_Indent, SaveAStyleOptions_LabelIndent)
// Test config file writes for astyle labelIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_LABELS;
	astyle.setLabelIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setLabelIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Indent, SaveAStyleOptions_MaxContinuation)
// Test config file writes for astyle max continuation indent
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// test max code length
	key = MAX_CONTINUATION_INDENT;
	astyle.setMaxContinuationIndent(50);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("50", value)
	        << "Failure for max continuation indent";

	// test max continuation default
	int defaultMaxInStatementIndent = astyle.getDefaultMaxContinuationIndent();
	EXPECT_TRUE(defaultMaxInStatementIndent == 40);
	key = MAX_CONTINUATION_INDENT;
	astyle.setMaxContinuationIndent(defaultMaxInStatementIndent);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for default max continuation indent";

	// test invalid minimum for max continuation, should use minimum (default)
	key = MAX_CONTINUATION_INDENT;
	astyle.setMaxContinuationIndent(39);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid max continuation indent";

	// test invalid maximum for max continuation, should use maximum
	key = MAX_CONTINUATION_INDENT;
	astyle.setMaxContinuationIndent(121);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	wxString maxIndentEnum = wxString::Format("%d", 120);
	EXPECT_EQ(maxIndentEnum, value)
	        << "Failure for invalid max continuation indent";
}

TEST(Config_AStyle_Indent, SaveAStyleOptions_MinConditionalOpt)
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
		astyle.setMinConditionalOption(minOption[i]);
		config.SaveAStyleOptions(&astyle);
		config.SetPath("/AStyle");
		config.Read(key, &value);
		wxString minOptionEnum = wxString::Format("%d", minOption[i]);
		EXPECT_EQ(minOptionEnum, value)
		        << "Failure for min conditional option = " << minOption[i];
	}

	// test min conditional option default
	MinConditional defaultMinConditionalOption = astyle.getDefaultMinConditionalOption();
	EXPECT_TRUE(defaultMinConditionalOption == MINCOND_TWO);
	key = MIN_CONDITIONAL_INDENT;
	astyle.setMinConditionalOption(defaultMinConditionalOption);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for default min conditional option";

	// test invalid min conditional option, should use default
	key = MIN_CONDITIONAL_INDENT;
	astyle.setMinConditionalOption(MINCOND_END);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid min conditional option";
}

TEST(Config_AStyle_Indent, SaveAStyleOptions_ModifierIndent)
// Test config file writes for astyle modifierIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_MODIFIERS;
	astyle.setModifierIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setModifierIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Indent, SaveAStyleOptions_NamespaceIndent)
// Test config file writes for astyle namespaceIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_NAMESPACES;
	astyle.setNamespaceIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setNamespaceIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Indent, SaveAStyleOptions_PreprocBlockIndent)
// Test config file writes for astyle preprocBlockIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_PREPROC_BLOCK;
	astyle.setPreprocBlockIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setPreprocBlockIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Indent, SaveAStyleOptions_PreprocCondIndent)
// Test config file writes for astyle preprocCondIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_PREPROC_COND;
	astyle.setPreprocCondIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setPreprocCondIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Indent, SaveAStyleOptions_PreprocDefineIndent)
// Test config file writes for astyle preprocDefineIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_PREPROC_DEFINE;
	astyle.setPreprocDefineIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setPreprocDefineIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Indent, SaveAStyleOptions_SwitchIIndent)
// Test config file writes for astyle switchIndent option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_SWITCHES;
	astyle.setSwitchIndent(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setSwitchIndent(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

//-------------------------------------------------------------------------
// AStyle Config Tests for Padding Options
//-------------------------------------------------------------------------

TEST(Config_AStyle_Pad, SaveAStyleOptions_AlignPointer)
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
		astyle.setAlignPointer(alignPointer[i]);
		config.SaveAStyleOptions(&astyle);
		config.SetPath("/AStyle");
		config.Read(key, &value);
		wxString alignPointerEnum = wxString::Format("%d", alignPointer[i]);
		EXPECT_EQ(alignPointerEnum, value)
		        << "Failure for align pointer = " << alignPointer[i];
	}

	// test align pointer none (default)
	key = ALIGN_POINTER;
	astyle.setAlignPointer(PTR_ALIGN_NONE);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for default align pointer";

	// test invalid align pointer, should use default
	key = ALIGN_POINTER;
	astyle.setAlignPointer(PTR_ALIGN_END);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid align pointer";

	// test invalid align pointer, should use default
	key = ALIGN_POINTER;
	astyle.setAlignPointer(PTR_ALIGN_END);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid align pointer";
}

TEST(Config_AStyle_Pad, SaveAStyleOptions_AlignReference)
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
		astyle.setAlignReference(alignReference[i]);
		config.SaveAStyleOptions(&astyle);
		config.SetPath("/AStyle");
		config.Read(key, &value);
		wxString alignReferenceEnum = wxString::Format("%d", alignReference[i]);
		EXPECT_EQ(alignReferenceEnum, value)
		        << "Failure for align reference = " << alignReference[i];
	}

	// test align reference same as pointer (default)
	key = ALIGN_REFERENCE;
	astyle.setAlignReference(REF_SAME_AS_PTR);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for default align reference";

	// test invalid align reference, should use default
	key = ALIGN_REFERENCE;
	astyle.setAlignReference(REF_ALIGN_END);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid align reference";

	// test invalid align reference, should use default
	key = ALIGN_REFERENCE;
	astyle.setAlignReference(REF_ALIGN_END);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid align reference";
}

TEST(Config_AStyle_Pad, SaveAStyleOptions_BreakBlocks)
// Test config file writes for astyle break blocks options
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// test break all blocks
	key = BREAK_BLOCKS;
	astyle.setBreakHeaderBlocks(true);
	astyle.setBreakClosingBlocks(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("all", value)
	        << "Failure for break all blocks";

	// test break header blocks
	key = BREAK_BLOCKS;
	astyle.setBreakHeaderBlocks(true);
	astyle.setBreakClosingBlocks(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("open", value)
	        << "Failure for break header blocks";

	// test invalid break header blocks
	key = BREAK_BLOCKS;
	astyle.setBreakHeaderBlocks(false);
	astyle.setBreakClosingBlocks(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value))
	        << "Failure for invalid break header blocks";
}

TEST(Config_AStyle_Pad, SaveAStyleOptions_DeleteEmptyLines)
// Test config file writes for astyle deleteEmptyLines option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = DELETE_EMPTY_LINES;
	astyle.setDeleteEmptyLines(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setDeleteEmptyLines(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Pad, SaveAStyleOptions_FillEmptyLines)
// Test config file writes for astyle fillEmptyLines option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = FILL_EMPTY_LINES;
	astyle.setFillEmptyLines(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setFillEmptyLines(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Pad, SaveAStyleOptions_PadComma)
// Test config file writes for astyle padComma option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = PAD_COMMA;
	astyle.setPadComma(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setPadComma(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Pad, SaveAStyleOptions_PadFirstParenOut)
// Test config file writes for astyle padFirstParenOut option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = PAD_FIRST_PAREN_OUT;
	astyle.setPadFirstParenOut(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setPadFirstParenOut(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Pad, SaveAStyleOptions_PadHeader)
// Test config file writes for astyle padHeader option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = PAD_HEADER;
	astyle.setPadHeader(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setPadHeader(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Pad, SaveAStyleOptions_PadOperator)
// Test config file writes for astyle padOperator option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = PAD_OPER;
	astyle.setPadOperator(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setPadOperator(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Pad, SaveAStyleOptions_PadParen)
// Test config file writes for astyle pad paren options
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// test pad paren all
	key = PAD_PAREN;
	astyle.setPadParenOutside(true);
	astyle.setPadParenInside(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("all", value)
	        << "Failure for pad paren all";

	// test pad paren outside
	key = PAD_PAREN;
	astyle.setPadParenOutside(true);
	astyle.setPadParenInside(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("out", value)
	        << "Failure for pad paren outside";

	// test pad paren inside
	key = PAD_PAREN;
	astyle.setPadParenOutside(false);
	astyle.setPadParenInside(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("in", value)
	        << "Failure for pad paren inside";
}

TEST(Config_AStyle_Pad, SaveAStyleOptions_UnpadParen)
// Test config file writes for astyle unpadParen option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = UNPAD_PAREN;
	astyle.setUnpadParen(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setUnpadParen(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

//-------------------------------------------------------------------------
// AStyle Config Tests for Formatting Options
//-------------------------------------------------------------------------

TEST(Config_AStyle_Format, SaveAStyleOptions_AddBraces)
// Test config file writes for astyle addBraces option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ADD_BRACES;
	astyle.setAddBraces(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setAddBraces(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Format, SaveAStyleOptions_AddOneLineBraces)
// Test config file writes for astyle addOneLineBraces option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ADD_ONE_LINE_BRACES;
	astyle.setAddOneLineBraces(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setAddOneLineBraces(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Format, SaveAStyleOptions_BreakCloseBraces)
// Test config file writes for astyle breakCloseBraces option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = BREAK_CLOSING_BRACES;
	astyle.setBreakClosingBraces(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setBreakClosingBraces(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Format, SaveAStyleOptions_BreakElseIfs)
// Test config file writes for astyle breakElseIfs option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = BREAK_ELSEIFS;
	astyle.setBreakElseIfs(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setBreakElseIfs(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Format, SaveAStyleOptions_BreakOneLineHeaders)
// Test config file writes for astyle breakOneLineHeaders option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = BREAK_ONE_LINE_HEADERS;
	astyle.setBreakOneLineHeaders(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setBreakOneLineHeaders(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Format, SaveAStyleOptions_CloseTemplates)
// Test config file writes for astyle closeTemplates option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = CLOSE_TEMPLATES;
	astyle.setCloseTemplates(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setCloseTemplates(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Format, SaveAStyleOptions_ConvertTabs)
// Test config file writes for astyle convertTabs option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = CONVERT_TABS;
	astyle.setConvertTabs(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setConvertTabs(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Format, SaveAStyleOptions_KeepOneLineBlocks)
// Test config file writes for astyle breakOneLineBlocks option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test false
	key = KEEP_ONE_LINE_BLOCKS;
	astyle.setBreakOneLineBlocks(false);	// default is false to keep
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test true (delete key)
	astyle.setBreakOneLineBlocks(true);		// default is true to break
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Format, SaveAStyleOptions_KeepOneLineStmts)
// Test config file writes for astyle breakOneLineStmts option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = KEEP_ONE_LINE_STATEMENTS;
	astyle.setBreakOneLineStmts(false);		// default is false to keep
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setBreakOneLineStmts(true);		// default is true to break
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Format, SaveAStyleOptions_MaxCodeLength)
// Test config file writes for astyle max code length
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// style key
	wxString value;				// value of config key

	// test max continuation indent
	key = MAX_CODE_LENGTH;
	astyle.setMaxCodeLength(100);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	EXPECT_STREQ("100", value) << "Failure for max code length";

	// test max code length default
	int defaultMaxCodeLength = astyle.getDefaultMaxCodeLength();
	EXPECT_EQ(0, defaultMaxCodeLength);
	key = MAX_CODE_LENGTH;
	astyle.setMaxCodeLength(defaultMaxCodeLength);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	EXPECT_FALSE(config.Read(key, &value)) << "Failure for default max code length";

	// test invalid minimum for max code length, should use minimum (default)
	key = MAX_CODE_LENGTH;
	astyle.setMaxCodeLength(MAX_CODE_LENGTH_MIN - 1);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	wxString maxCodeLengthMinValue = wxString::Format("%d", MAX_CODE_LENGTH_MIN);
	EXPECT_EQ(maxCodeLengthMinValue, value) << "Failure for invalid max code length";

	// test invalid maximum for max code length, should use maximum
	key = MAX_CODE_LENGTH;
	astyle.setMaxCodeLength(MAX_CODE_LENGTH_MAX + 1);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	config.Read(key, &value);
	wxString maxCodeLengthMaxValue = wxString::Format("%d", MAX_CODE_LENGTH_MAX);
	EXPECT_EQ(maxCodeLengthMaxValue, value) << "Failure for invalid max code length";
}

TEST(Config_AStyle_Format, SaveAStyleOptions_RemoveBraces)
// Test config file writes for astyle removeBraces option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = REMOVE_BRACES;
	astyle.setRemoveBraces(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setRemoveBraces(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Format, SaveAStyleOptions_RemoveCommentPrefix)
// Test config file writes for astyle removeCommentPrefix option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = REMOVE_COMMENT_PREFIX;
	astyle.setRemoveCommentPrefix(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setRemoveCommentPrefix(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

//-------------------------------------------------------------------------
// AStyle Config Tests for Other Options
//-------------------------------------------------------------------------

TEST(Config_AStyle_Other, SaveAStyleOptions_PadMethodPrefix)
// Test config file writes for astyle padMethodPrefix option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = PAD_METHOD_PREFIX;
	astyle.setPadMethodPrefix(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setPadMethodPrefix(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Other, SaveAStyleOptions_UnpadMethodPrefix)
// Test config file writes for astyle unpadMethodPrefix option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = UNPAD_METHOD_PREFIX;
	astyle.setUnpadMethodPrefix(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setUnpadMethodPrefix(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Other, SaveAStyleOptions_PadReturnType)
// Test config file writes for astyle padReturnType option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = PAD_RETURN_TYPE;
	astyle.setPadReturnType(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setPadReturnType(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Other, SaveAStyleOptions_UnpadReturnType)
// Test config file writes for astyle unpadReturnType option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = UNPAD_RETURN_TYPE;
	astyle.setUnpadReturnType(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setUnpadReturnType(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Other, SaveAStyleOptions_AlignMethodColon)
// Test config file writes for astyle alignMethodColon option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ALIGN_METHOD_COLON;
	astyle.setAlignMethodColon(true);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	astyle.setAlignMethodColon(false);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_AStyle_Other, SaveAStyleOptions_PadMethodColon)
// Test config file writes for astyle padMethodColon option
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	AStyleIFace_Test astyle;	// uses getters and setters from AStyleIFace
	wxString key;				// config key
	wxString value;				// value of config key

	// test pad method colon options
	key = PAD_METHOD_COLON;
	astyle.setPadMethodColon(COLON_PAD_NONE);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ("none", value);
	astyle.setPadMethodColon(COLON_PAD_ALL);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ("all", value);
	astyle.setPadMethodColon(COLON_PAD_AFTER);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ("after", value);
	astyle.setPadMethodColon(COLON_PAD_BEFORE);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ("before", value);

	// test invalid pad method colon option, should not write
	astyle.setPadMethodColon(COLON_PAD_NO_CHANGE);
	config.SaveAStyleOptions(&astyle);
	config.SetPath("/AStyle");
	ASSERT_FALSE(config.Read(key, &value));
}

//-------------------------------------------------------------------------
// Editor and View Menu Config Tests
//-------------------------------------------------------------------------

TEST(Config_Frame, InitializeFile)
// Test if config file is initialized if there are no entries.
// This tests the function void Config::InitializeConfigFile().
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	ASSERT_TRUE(frame.GetCommentFont().IsOk());
	ASSERT_TRUE(frame.GetDefaultFont().IsOk());

	// build keys array
	// these keys are always added to the config file
	wxArrayString keys;
	keys.Add(LINE_NUMBERS);
	keys.Add(TOOLBAR_TOOLTIPS);
	keys.Add(DIALOG_TOOLTIPS);
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
	config.GetEditorAndViewMenuOptions(&frame);

	// verify keys were added by Config::InitializeConfigFile()
	config.SetPath("/");
	wxString value;
	for (size_t i = 0; i < keys.GetCount(); i++)
		EXPECT_TRUE(config.Read(keys[i], &value));
	ASSERT_EQ(keys.GetCount(), config.GetNumberOfEntries(true));
}

TEST(Config_Frame, GetEditorAndViewMenuOptions)
// Test config file gets for editor and view options.
// GetNextEntry is used for the read so only a few options are checked.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);

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
	config.GetEditorAndViewMenuOptions(&frame);

	// verify no config file keys were deleted
	config.SetPath("/");
	EXPECT_EQ(keys.GetCount(), config.GetNumberOfEntries());
}

TEST(Config_Frame, GetEditorAndViewMenuOptions_InvalidKeys)
// Test config file gets for editor and view options.
// Invalid keys in the config file should be deleted.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);

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
	config.GetEditorAndViewMenuOptions(&frame);
	// verify that all config file keys were deleted
	config.SetPath("/");
	EXPECT_EQ(0U, config.GetNumberOfEntries());
}

TEST(Config_Frame, GetEditorAndViewMenuOptions_InvalidValues)
// Test config file gets for editor and view options.
// Invalid values in the config file should be deleted.
// NOTE: Float and double values are written to config as strings.
{
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);

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
	config.GetEditorAndViewMenuOptions(&frame);
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
	config.GetEditorAndViewMenuOptions(&frame);
	// verify that all long config file keys were deleted
	config.SetPath("/AStyle");
	EXPECT_EQ(0U, config.GetNumberOfEntries());
}

//-------------------------------------------------------------------------
// Editor Tests
//-------------------------------------------------------------------------

TEST(Config_Editor, SaveEditorOptions_AlwaysSaved)
// Test config file writes for editor options that are always saved
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
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
	config.SaveEditorOptions(&frame);

	// check the saves
	config.SetPath("/");
	for (size_t i = 0; i < keys.GetCount(); i++)
		EXPECT_TRUE(config.Read(keys[i], &value)) << keys[i].c_str();
	// verify the number of config file keys checked
	EXPECT_EQ(keys.GetCount(), config.GetNumberOfEntries());
}

TEST(Config_Editor, SaveEditorOptions_HideFindAfterMatch)
// Test config file writes for editor option m_hideDialogAfterMatch
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = HIDE_FIND;
	frame.SetFrameBoolReturn(true);	// set return value for getter
	config.SaveEditorOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveEditorOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_Editor, SaveEditorOptions_IsMaximized)
// Test config file writes for frame wxTopLevelWindow function IsMaximized
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = FRAME_MAXIMIZED;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveEditorOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveEditorOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_Editor, SaveEditorOptions_ShowDialogTips)
// Test config file writes for frame option m_showDialogTips
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = DIALOG_TOOLTIPS;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveEditorOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveEditorOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_Editor, SaveEditorOptions_ShowToolTips)
// Test config file writes for frame option m_showToolTips
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = TOOLBAR_TOOLTIPS;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveEditorOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveEditorOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_Editor, SaveEditorOptions_TestOptions)
// Test config file writes for frame option m_testOptions.
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
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

TEST(Config_Editor, SaveEditorOptions_UseBottomTabs)
// Test config file writes for frame option m_useBottomTabs
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = USE_BOTTOM_TABS;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveEditorOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveEditorOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_Editor, SaveEditorOptions_UseSmallToolbar)
// Test config file writes for frame option m_useSmallToolbar
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = USE_SMALL_TOOLBAR;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveEditorOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveEditorOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_Editor, SaveEditorOptions_WrapSearch)
// Test config file writes for editor option m_wrapSearch
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = WRAP_SEARCH;
	frame.SetFrameBoolReturn(true);	// set return value for getter
	config.SaveEditorOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveEditorOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

//-------------------------------------------------------------------------
// View Menu Config Tests
//-------------------------------------------------------------------------

TEST(Config_ViewMenu, SaveViewMenuOptions_ActiveLine)
// Test config file writes for menu option ID_VIEW_ACTIVELINE
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = ACTIVE_LINE;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_ViewMenu, SaveViewMenuOptions_EndOfLine)
// Test config file writes for menu option ID_VIEW_ENDLINE
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = END_OF_LINE;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_ViewMenu, SaveViewMenuOptions_IndentGuides)
// Test config file writes for menu option ID_VIEW_INDENTGUIDES
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = INDENT_GUIDES;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_ViewMenu, SaveViewMenuOptions_LineNumbers)
// Test config file writes for menu option ID_VIEW_LINENUMBERS
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = LINE_NUMBERS;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_ViewMenu, SaveViewMenuOptions_MonoSpace)
// Test config file writes for menu option ID_VIEW_MONOSPACE
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = MONOSPACE;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_ViewMenu, SaveViewMenuOptions_SelectionMargin)
// Test config file writes for menu option ID_VIEW_MARGIN
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = SELECTION_MARGIN;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_ViewMenu, SaveViewMenuOptions_StatusBar)
// Test config file writes for menu option ID_VIEW_STATUSBAR
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = SHOW_STATUSBAR;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_ViewMenu, SaveViewMenuOptions_Toolbar)
// Test config file writes for menu option ID_VIEW_TOOLBAR
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = SHOW_TOOLBAR;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_ViewMenu, SaveViewMenuOptions_WhiteSpace)
// Test config file writes for menu option ID_VIEW_WHITESPACE
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = WHITESPACE;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

TEST(Config_ViewMenu, SaveViewMenuOptions_WordWrap)
// Test config file writes for menu option ID_VIEW_WORDWRAP
{
	// create objects
	Config_Test config(CONFIG_TEST_NAME);
	ASEditor editor;
	ASFrame frame(&editor);
	wxString key;				// config key
	wxString value;				// value of config key

	// test true
	key = WORD_WRAP;
	frame.SetFrameBoolReturn(true);		// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_TRUE(config.Read(key, &value));
	EXPECT_STREQ(asTRUE, value);

	// test false (delete key)
	frame.SetFrameBoolReturn(false);	// set return value for getter
	config.SaveViewMenuOptions(&frame);
	config.SetPath("/");
	ASSERT_FALSE(config.Read(key, &value));
}

//-------------------------------------------------------------------------
// Styles Config Tests
//-------------------------------------------------------------------------

TEST(Config_Styles, GetStcStyleOptions_Default)
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

TEST(Config_Styles, GetStcStyleOptions)
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

TEST(Config_Styles, GetStcStyleOptions_NoEntries)
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

TEST(Config_Styles, GetStcStyleOptions_InvalidStyleNumber)
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

TEST(Config_Styles, GetStcStyleOptions_ExtraStyleNumber)
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

TEST(Config_Styles, GetStcStyleOptions_InvalidForeColor)
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

TEST(Config_Styles, GetStcStyleOptions_InvalidBackColor)
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

TEST(Config_Styles, GetStcStyleOptions_InvalidKey)
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

TEST(Config_Styles, GetStcStyleOptions_InvalidSeparator)
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

TEST(Config_Styles, GetStcStyleOptions_NonNumericStyle)
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

TEST(Config_Styles, SaveStcStyleOptions_GroupNumber)
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

TEST(Config_Styles, SaveStcStyleOptions_GroupNames)
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

TEST(Config_Styles, SaveStcStyleOptions_Entries)
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

//----------------------------------------------------------------------------

}  // anonymous namespace
