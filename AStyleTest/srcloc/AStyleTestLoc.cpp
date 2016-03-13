// AStyleTestLoc.cpp
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// Licensed under the MIT license.
// License.txt describes the conditions under which this software may be distributed.


// This module tests the Localizer and Translate classes.
//
// language ID http://msdn.microsoft.com/en-us/library/ee797784%28v=cs.20%29.aspx
//
// AStyleTestLoc tests the internationalization component of the ASConsole
// class only.

//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

#ifdef _WIN32
	#include <windows.h>
#endif

#include "gtest/gtest.h"

#include "ASLocalizer.h"

using namespace astyle;
using namespace testing;

//----------------------------------------------------------------------------
// anonymous namespace
//----------------------------------------------------------------------------

namespace {

//----------------------------------------------------------------------------
// AStyle test ASLocalizer class, setLanguageFromName
//----------------------------------------------------------------------------

TEST(ASLocalizerName, LanguageNameIdentification)
// Use French locale names to test the LINUX getLanguage() function.
// http://msdn.microsoft.com/en-us/library/ee797784%28v=cs.20%29.aspx
{
	char localeName[][20] = { "fr",
	                          "fr_BE",				// Belgium
	                          "fr_CA@euro",			// Canada
	                          "fr_FR",				// France
	                          "fr_LU.iso1252",		// Luxembourg
	                          "fr_MC",				// Monaco
	                          "fr_CH.iso1252@euro",	// Switzerland
	                        };
	size_t localeCount = sizeof(localeName) / sizeof(localeName[0]);
	for (size_t i = 0; i < localeCount; i++)
	{
		ASLocalizer localizer;
		localizer.setLanguageFromName(localeName[i]);
		string langID = localizer.getLanguageID();
		EXPECT_EQ("fr", langID);
	}
}

TEST(ASLocalizerName, UnrecognizedNameTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Unrecognized - default to English
	ASLocalizer localizer;
	localizer.setLanguageFromName("xx_XX");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("English") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, BulgarianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Bulgarian
	ASLocalizer localizer;
	localizer.setLanguageFromName("bg-BG");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Bulgarian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, ChineseSimplifiedTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	string className;
	bool foundClassName;
	// Chinese Simplified (China)
	ASLocalizer ChineseSimplifiedCN;
	ChineseSimplifiedCN.setLanguageFromName("zh_CN");
	translation = ChineseSimplifiedCN.getTranslationClass();
	className = typeid(*translation).name();
	foundClassName = className.find("ChineseSimplified") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
	// Chinese Simplified (Singapore)
	ASLocalizer ChineseSimplifiedSG;
	ChineseSimplifiedSG.setLanguageFromName("zh_SG");
	translation = ChineseSimplifiedSG.getTranslationClass();
	className = typeid(*translation).name();
	foundClassName = className.find("ChineseSimplified") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, ChineseTraditionalTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	string className;
	bool foundClassName;
	// Chinese (all other) - default to Chinese Traditional
	ASLocalizer ChineseAllOther;
	ChineseAllOther.setLanguageFromName("zh_XX");
	translation = ChineseAllOther.getTranslationClass();
	className = typeid(*translation).name();
	foundClassName = className.find("ChineseTraditional") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, DutchTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Dutch
	ASLocalizer localizer;
	localizer.setLanguageFromName("nl_NL");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Dutch") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, EnglishTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// English
	ASLocalizer localizer;
	localizer.setLanguageFromName("en_US");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("English") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, EstonianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Estonian
	ASLocalizer localizer;
	localizer.setLanguageFromName("et-EE");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Estonian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, FinnishTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Finnish
	ASLocalizer localizer;
	localizer.setLanguageFromName("fi_FI");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Finnish") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, FrenchTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// French
	ASLocalizer localizer;
	localizer.setLanguageFromName("fr_FR");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("French") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, GermanTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// German
	ASLocalizer localizer;
	localizer.setLanguageFromName("de_DE");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("German") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, GreekTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Greek
	ASLocalizer localizer;
	localizer.setLanguageFromName("el-GR");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Greek") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, HindiTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Hindi
	ASLocalizer localizer;
	localizer.setLanguageFromName("hi_IN");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Hindi") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, HungarianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	//  Hungarian
	ASLocalizer localizer;
	localizer.setLanguageFromName("hu-HU");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Hungarian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, ItalianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Italian
	ASLocalizer localizer;
	localizer.setLanguageFromName("it_IT");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Italian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, JapaneseTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Japanese
	ASLocalizer localizer;
	localizer.setLanguageFromName("ja_JP");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Japanese") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, KoreanTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Korean
	ASLocalizer localizer;
	localizer.setLanguageFromName("ko_KR");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Korean") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, NorwegianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Norwegian
	ASLocalizer localizer;
	localizer.setLanguageFromName("nn-NO");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Norwegian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, PolishTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Polish
	ASLocalizer localizer;
	localizer.setLanguageFromName("pl_PL");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Polish") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, PortugueseTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Portuguese
	ASLocalizer localizer;
	localizer.setLanguageFromName("pt_PT");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Portuguese") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, RomanianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Romanian
	ASLocalizer localizer;
	localizer.setLanguageFromName("ro-RO");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Romanian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, RussianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Korean
	ASLocalizer localizer;
	localizer.setLanguageFromName("ru_RU");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Russian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, SpanishTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Spanish
	ASLocalizer localizer;
	localizer.setLanguageFromName("es_ES");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Spanish") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, SwedishTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Swedish
	ASLocalizer localizer;
	localizer.setLanguageFromName("sv_SE");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Swedish") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

TEST(ASLocalizerName, UkrainianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromName();
// Uses "find" because of the different return values from typeid.
{
	const Translation* translation;
	// Ukrainian
	ASLocalizer localizer;
	localizer.setLanguageFromName("uk_UA");
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Ukrainian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
}

//----------------------------------------------------------------------------
// AStyle test ASLocalizer class, setLanguageFromLCID - Windows only
//----------------------------------------------------------------------------

TEST(ASLocalizerLCID, LanguageLCIDIdentification)
// Use French LCIDs to test the WINDOWS setLanguage() function.
// http://msdn.microsoft.com/en-us/library/0h88fahh%28v=vs.85%29.aspx
{
#ifdef _WIN32
	size_t lcid[] = { 1036,		// 0x040C  France
	                  2060,		// 0x080C  Belgium
	                  3084,		// 0x0C0C  Canada
	                  5132,		// 0x140C  Luxembourg
	                  4108,		// 0x100C  Switzerland
	                };
	size_t lcidCount = sizeof(lcid) / sizeof(lcid[0]);
	for (size_t i = 0; i < lcidCount; i++)
	{
		ASLocalizer localizer;
		localizer.setLanguageFromLCID(lcid[i]);
		string langID = localizer.getLanguageID();
		EXPECT_EQ("fr", langID);
	}
#endif
}

TEST(ASLocalizerLCID, UnrecognizedLCIDTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Unrecognized - default to English
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(9999);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("English") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, BulgarianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Bulgarian
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1026);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Bulgarian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, ChineseSimplifiedTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	string className;
	bool foundClassName;
	// Chinese Simplified (China)
	ASLocalizer ChineseSimplifiedCN;
	ChineseSimplifiedCN.setLanguageFromLCID(2052);
	translation = ChineseSimplifiedCN.getTranslationClass();
	className = typeid(*translation).name();
	foundClassName = className.find("ChineseSimplified") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
	// Chinese Simplified (Singapore)
	ASLocalizer ChineseSimplifiedSG;
	ChineseSimplifiedSG.setLanguageFromLCID(4100);
	translation = ChineseSimplifiedSG.getTranslationClass();
	className = typeid(*translation).name();
	foundClassName = className.find("ChineseSimplified") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, ChineseTraditionalTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	string className;
	bool foundClassName;
	// Chinese Traditional (Taiwan)
	ASLocalizer ChineseSimplifiedT;
	ChineseSimplifiedT.setLanguageFromLCID(1028);
	translation = ChineseSimplifiedT.getTranslationClass();
	className = typeid(*translation).name();
	foundClassName = className.find("ChineseTraditional") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
	// Chinese Traditional (Hong Kong)
	ASLocalizer ChineseSimplifiedHK;
	ChineseSimplifiedHK.setLanguageFromLCID(3076);
	translation = ChineseSimplifiedHK.getTranslationClass();
	className = typeid(*translation).name();
	foundClassName = className.find("ChineseTraditional") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
	// Chinese Traditional (Macao)
	ASLocalizer ChineseSimplifiedM;
	ChineseSimplifiedM.setLanguageFromLCID(5124);
	translation = ChineseSimplifiedM.getTranslationClass();
	className = typeid(*translation).name();
	foundClassName = className.find("ChineseTraditional") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, DutchTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Dutch
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1043);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Dutch") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, EnglishTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// English
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1033);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("English") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, EstonianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Estonian
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1061);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Estonian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, FinnishTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Finnish
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1035);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Finnish") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, FrenchTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// French
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1036);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("French") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, GermanTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// German
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1031);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("German") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, GreekTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Greek
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1032);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Greek") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, HindiTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Hindi
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1081);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Hindi") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, HungarianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	//  Hungarian
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1038);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Hungarian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, ItalianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Italian
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1040);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Italian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, JapaneseTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Japanese
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1041);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Japanese") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, KoreanTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Korean
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1042);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Korean") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, NorwegianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Norwegian
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1044);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Norwegian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, PolishTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Polish
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1045);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Polish") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, PortugueseTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Portuguese
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1046);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Portuguese") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, RomanianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Romanian
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1048);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Romanian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, RussianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Korean
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1049);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Russian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, SpanishTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Spanish
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1034);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Spanish") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, SwedishTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Swedish
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1053);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Swedish") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

TEST(ASLocalizerLCID, UkrainianTranslation)
// Check that the correct polymorphic class is set by setTranslationClass().
// setTranslationClass() is accessed thru setLanguageFromLCID();
// Uses "find" because of the different return values from typeid.
{
#ifdef _WIN32
	const Translation* translation;
	// Ukrainian
	ASLocalizer localizer;
	localizer.setLanguageFromLCID(1058);
	translation = localizer.getTranslationClass();
	string className = typeid(*translation).name();
	bool foundClassName = className.find("Ukrainian") != string::npos;
	EXPECT_TRUE(foundClassName) << className;
#endif
}

//----------------------------------------------------------------------------
// AStyle test Translate class and translation values
//----------------------------------------------------------------------------

struct TranslationF : public Test
{
	vector<string> m_ascii;

	TranslationF()
	{
		// use the script astyle-localizer.py to check these against astyle_main.cpp
		setlocale(LC_ALL, "C");
		m_ascii.push_back("Formatted  %s\n");		// should align with unchanged
		m_ascii.push_back("Unchanged  %s\n");		// should align with formatted
		m_ascii.push_back("Directory  %s\n");
		m_ascii.push_back("Exclude  %s\n");
		m_ascii.push_back("Exclude (unmatched)  %s\n");
		m_ascii.push_back(" %s formatted   %s unchanged   ");
		m_ascii.push_back(" seconds   ");
		m_ascii.push_back("%d min %d sec   ");
		m_ascii.push_back("%s lines\n");
		m_ascii.push_back("Using default options file %s\n");
		m_ascii.push_back("Opening HTML documentation %s\n");
		m_ascii.push_back("Invalid option file options:");
		m_ascii.push_back("Invalid command line options:");
		m_ascii.push_back("For help on options type 'astyle -h'");
		m_ascii.push_back("Cannot open options file");
		m_ascii.push_back("Cannot open directory");
		m_ascii.push_back("Cannot open HTML file %s\n");
		m_ascii.push_back("Command execute failure");
		m_ascii.push_back("Command is not installed");
		m_ascii.push_back("Missing filename in %s\n");
		m_ascii.push_back("Recursive option with no wildcard");
		m_ascii.push_back("Did you intend quote the filename");
		m_ascii.push_back("No file to process %s\n");
		m_ascii.push_back("Did you intend to use --recursive");
		m_ascii.push_back("Cannot process UTF-32 encoding");
		m_ascii.push_back("\nArtistic Style has terminated");
	}
	void getPrintSpecifiers(string& stringIn, vector<string>& specifiers)
	// Extract the print specifiers from a string.
	{
		for (size_t i = 0; i < stringIn.length(); i++)
		{
			i = stringIn.find('%', i);
			if (i == string::npos)
				break;
			size_t iStart = i;
			i = stringIn.find_first_not_of(" \t", i + 1);
			string specifier = stringIn.substr(iStart, i - iStart + 1);
			specifiers.push_back(specifier);
		}
	}
	void getPrintSpecifiers(wstring& stringIn, vector<wstring>& specifiers)
	// Extract the print specifiers from a WIDE string.
	{
		for (size_t i = 0; i < stringIn.length(); i++)
		{
			i = stringIn.find('%', i);
			if (i == string::npos)
				break;
			size_t iStart = i;
			i = stringIn.find_first_not_of(L" \t", i + 1);
			wstring specifier = stringIn.substr(iStart, i - iStart + 1);
			specifiers.push_back(specifier);
		}
	}
	int  getSpacesBeforeSpecifier(wstring& stringIn)
	// Get the number of WIDE string spaces before the print specifier.
	{
		int numSpaces = 0;	// spaces before a pront specifier
		size_t percent = stringIn.find('%', 0);
		if (percent != string::npos)
		{
			for (size_t i = --percent; i > 0; --i)
			{
				if (stringIn[i] != ' ')
					break;
				++numSpaces;
			}
		}
		return numSpaces;
	}
	vector<int> getSpacesConsecutive(wstring& stringIn)
	// Get the number of consecutive WIDE string spaces.
	{
		vector<int> translationSpaces;		// number of consecutive spaces
		bool countingSpaces = false;
		int numSpaces = 0;
		for (size_t i = 0; i < stringIn.length(); i++)
		{
			if (countingSpaces)
			{
				if (stringIn[i] == ' ')
				{
					++numSpaces;
				}
				else
				{
					translationSpaces.push_back(numSpaces);
					numSpaces = 0;
					countingSpaces = false;
				}
			}
			else
			{
				if (stringIn[i] == ' ')
				{
					++numSpaces;
					countingSpaces = true;
				}
			}
		}
		if (numSpaces > 0)
			translationSpaces.push_back(numSpaces);
		return translationSpaces;
	}
	template <typename T>	// string and wstring
	bool hasLineEnd(T& stringIn)
	// Check for a ending line end character.
	{
		size_t lastChar = stringIn.length() - 1;
		if (lastChar > 0 && stringIn[lastChar] == '\n')
			return true;
		return false;
	}
	string removeLineEnd(string& stringIn)
	// Remove an ending line end character.
	{
		string stringOut = stringIn;
		if (hasLineEnd(stringOut))
			stringOut.erase(stringOut.length() - 1);
		return stringOut;
	}
	void testTranslationFormat(Translation& language)
	// Call this to test a language translation.
	{
		// check size of vector
		// less than is OK since missing entries will be checked
		size_t numberOfTranslations = language.getTranslationVectorSize();
		EXPECT_GE(m_ascii.size(), numberOfTranslations) << "translations vector has extra entries";
		for (size_t i = 0; i < m_ascii.size(); i++)
		{
			// remove the line end for printing
			string asciiPrt = removeLineEnd(m_ascii[i]);
			// test that the string is found
			wstring translation;
			bool stringOk = language.getWideTranslation(m_ascii[i], translation);
//			stringOk = false;
			if (!stringOk)
			{
				EXPECT_TRUE(stringOk) << "string not found \"" << asciiPrt << "\"";
				continue;	// no more tests for this string
			}
			// test for line end
			bool asciiHasLineEnd = hasLineEnd(m_ascii[i]);
			bool translationHasLineEnd =  hasLineEnd(translation);
//			translationHasLineEnd = !asciiHasLineEnd;
			EXPECT_TRUE(asciiHasLineEnd == translationHasLineEnd) << "bad line end \"" << asciiPrt << "\"";
			// check the number of print specifiers
			vector<string> asciiSpecifiers;
			vector<wstring> translationSpecifiers;
			getPrintSpecifiers(m_ascii[i], asciiSpecifiers);
			getPrintSpecifiers(translation, translationSpecifiers);
			ASSERT_EQ(asciiSpecifiers.size(), translationSpecifiers.size()) << "number of print specifiers \"" << asciiPrt << "\"";
			// check the type of print specifiers
			for (size_t j = 0; j < asciiSpecifiers.size(); j++)
			{
				// conversion should be OK since specifiers are ascii
				string asciiSpecifier = asciiSpecifiers[j];
				string translationSpecifier = language.convertToMultiByte(translationSpecifiers[j]);
				ASSERT_EQ(asciiSpecifier, translationSpecifier)	<< "print specifiers value \"" << asciiPrt << "\"";
			}
		}
	}
	void testTranslationSpaces(Translation& language)
	// Call this to test the spaces on selected lines of a language translation.
	{
		wstring formattedTranslation;
		wstring unchangedTranslation;
		wstring directoryTranslation;
		wstring exclude1Translation;
		wstring exclude2Translation;
		wstring total1Translation;
		wstring total2Translation;
		wstring total3Translation;
		wstring total4Translation;
		// get the translation strings
		for (size_t i = 0; i < 10; i++)
		{
			// remove the line end for printing
			string asciiPrt = removeLineEnd(m_ascii[i]);
			// test that the string is found
			wstring translation;
			bool stringOk = language.getWideTranslation(m_ascii[i], translation);
			//			stringOk = false;
			if (!stringOk)
			{
				EXPECT_TRUE(stringOk) << "string not found \"" << asciiPrt << "\"";
				continue;	// no more tests for this string
			}
			if (i == 0)
			{
				EXPECT_TRUE(m_ascii[i].substr(0, 9) == "Formatted") << "Missing \"Formatted\" keyword";
				formattedTranslation = translation;
			}
			if (i == 1)
			{
				EXPECT_TRUE(m_ascii[i].substr(0, 9) == "Unchanged") << "Missing \"Unchanged\" keyword";
				unchangedTranslation = translation;
			}
			if (i == 2)
			{
				EXPECT_TRUE(m_ascii[i].substr(0, 9) == "Directory") << "Missing \"Unchanged\" keyword";
				directoryTranslation = translation;
			}
			if (i == 3)
			{
				EXPECT_TRUE(m_ascii[i].substr(0, 7) == "Exclude") << "Missing exclude 1 keyword";
				exclude1Translation = translation;
			}
			if (i == 4)
			{
				EXPECT_TRUE(m_ascii[i].substr(0, 7) == "Exclude") << "Missing exclude 2 keyword";
				exclude2Translation = translation;
			}
			if (i == 5)
			{
				EXPECT_TRUE(m_ascii[i].substr(4, 9) == "formatted") << "Missing total 1 keyword";
				total1Translation = translation;
			}
			if (i == 6)
			{
				EXPECT_TRUE(m_ascii[i].substr(1, 7) == "seconds") << "Missing total 2 keyword";
				total2Translation = translation;
			}
			if (i == 7)
			{
				EXPECT_TRUE(m_ascii[i].substr(3, 3) == "min") << "Missing total 3 keyword";
				total3Translation = translation;
			}
			if (i == 8)
			{
				EXPECT_TRUE(m_ascii[i].substr(3, 5) == "lines") << "Missing total 4 keyword";
				total4Translation = translation;
			}
		}
		int formattedSpaces = getSpacesBeforeSpecifier(formattedTranslation);
		int unchangedSpaces = getSpacesBeforeSpecifier(unchangedTranslation);
		EXPECT_TRUE(formattedSpaces >= 2 && unchangedSpaces >= 2)
		        << "Formatted/Unchanged alignment " << formattedSpaces << '/' << unchangedSpaces;
		EXPECT_TRUE(formattedSpaces == 2 || unchangedSpaces == 2)
		        << "Formatted/Unchanged alignment " << formattedSpaces << '/' << unchangedSpaces;
		int directorySpaces = getSpacesBeforeSpecifier(directoryTranslation);
		EXPECT_EQ(2, directorySpaces) << "Directory spaces";
		int exclude1Spaces = getSpacesBeforeSpecifier(exclude1Translation);
		EXPECT_EQ(2, exclude1Spaces) << "Exclude spaces";
		int exclude2Spaces = getSpacesBeforeSpecifier(exclude2Translation);
		EXPECT_EQ(2, exclude2Spaces) << "Exclude (unmatched) spaces";
		// test total line
		vector<int> translationSpaces;
		// test total line 1
		vector<int> total1Spaces = { 1, 1, 3, 1, 3 };
		// compilers have various formats for the type-name
		string typeName = typeid(language).name();
		if (typeName.find("Hindi") != string::npos)
			total1Spaces  = { 1, 1, 1, 3, 1, 3 };
		else if (typeName.find("Russian") != string::npos)
			total1Spaces = { 1, 1, 3, 1, 1, 3 };
		else if (typeName.find("Ukrainian") != string::npos)
			total1Spaces = { 1, 1, 3, 1, 1, 3 };
		translationSpaces = getSpacesConsecutive(total1Translation);
		EXPECT_EQ(total1Spaces, translationSpaces) << "Total line 1";
		// test total line 2
		vector<int> total2Spaces = { 1, 3 };
		translationSpaces = getSpacesConsecutive(total2Translation);
		EXPECT_EQ(total2Spaces, translationSpaces) << "Total line 2";
		// test total line 3
		vector<int> total3Spaces = { 1, 1, 1, 3 };
		translationSpaces = getSpacesConsecutive(total3Translation);
		EXPECT_EQ(total3Spaces, translationSpaces) << "Total line 3";
		// test total line 4
		vector<int> total4Spaces = { 1 };
		translationSpaces = getSpacesConsecutive(total4Translation);
		EXPECT_EQ(total4Spaces, translationSpaces) << "Total line 4";
	}
};	// struct TranslationF

TEST_F(TranslationF, Bulgarian)
// Test the Bulgarian translation.
{
	Bulgarian bulgarian;
	testTranslationFormat(bulgarian);
	testTranslationSpaces(bulgarian);
}

TEST_F(TranslationF, ChineseSimplified)
// Test the Chinese Simplified translation.
{
	ChineseSimplified chinese;
	testTranslationFormat(chinese);
	testTranslationSpaces(chinese);
}

TEST_F(TranslationF, ChineseTraditional)
// Test the Chinese Traditional translation.
{
	ChineseTraditional chinese;
	testTranslationFormat(chinese);
	testTranslationSpaces(chinese);
}

TEST_F(TranslationF, Dutch)
// Test the Dutch translation.
{
	Dutch dutch;
	testTranslationFormat(dutch);
	testTranslationSpaces(dutch);
}

TEST_F(TranslationF, English)
// Test the English translation.
{
	// English does NOT get translated.
	// The original value should be returned.
	English english;
	// check size of vector
	size_t numberOfTranslations = english.getTranslationVectorSize();
	EXPECT_TRUE(numberOfTranslations == 0) << "translations vector should be empty";
	for (size_t i = 0; i < m_ascii.size(); i++)
	{
		// remove the line end for printing
		string asciiPrt = removeLineEnd(m_ascii[i]);
		// use "translate" test that the original string is returned
		string translation = english.translate(m_ascii[i]);
		EXPECT_TRUE(m_ascii[i] == translation) << "translation error \"" << asciiPrt << "\"";
	}
}

TEST_F(TranslationF, Estonian)
// Test the Estonian translation.
{
	Estonian estonian;
	testTranslationFormat(estonian);
	testTranslationSpaces(estonian);
}

TEST_F(TranslationF, Finnish)
// Test the Finnish translation.
{
	Finnish finnish;
	testTranslationFormat(finnish);
	testTranslationSpaces(finnish);
}

TEST_F(TranslationF, French)
// Test the French translation.
{
	French french;
	testTranslationFormat(french);
	testTranslationSpaces(french);
}

TEST_F(TranslationF, German)
// Test the German translation.
{
	German german;
	testTranslationFormat(german);
	testTranslationSpaces(german);
}

TEST_F(TranslationF, Greek)
// Test the Greek translation.
{
	Greek greek;
	testTranslationFormat(greek);
	testTranslationSpaces(greek);
}

TEST_F(TranslationF, Hindi)
// Test the Hindi translation.
{
	Hindi hindi;
	testTranslationFormat(hindi);
	testTranslationSpaces(hindi);
}

TEST_F(TranslationF, Hungarian)
// Test the Hungarian translation.
{
	Hungarian hungarian;
	testTranslationFormat(hungarian);
	testTranslationSpaces(hungarian);
}

TEST_F(TranslationF, Italian)
// Test the Italian translation.
{
	Italian italian;
	testTranslationFormat(italian);
	testTranslationSpaces(italian);
}

TEST_F(TranslationF, Japanese)
// Test the Japanese translation.
{
	Japanese japanese;
	testTranslationFormat(japanese);
	testTranslationSpaces(japanese);
}

TEST_F(TranslationF, Korean)
// Test the Korean translation.
{
	Korean korean;
	testTranslationFormat(korean);
	testTranslationSpaces(korean);
}

TEST_F(TranslationF, Norwegian)
// Test the Norwegian translation.
{
	Norwegian norwegian;
	testTranslationFormat(norwegian);
	testTranslationSpaces(norwegian);
}

TEST_F(TranslationF, Polish)
// Test the Polish translation.
{
	Polish polish;
	testTranslationFormat(polish);
	testTranslationSpaces(polish);
}

TEST_F(TranslationF, Portuguese)
// Test the Portuguese translation.
{
	Portuguese portuguese;
	testTranslationFormat(portuguese);
	testTranslationSpaces(portuguese);
}

TEST_F(TranslationF, Romanian)
// Test the Romanian translation.
{
	Romanian romanian;
	testTranslationFormat(romanian);
	testTranslationSpaces(romanian);
}

TEST_F(TranslationF, Russian)
// Test the Russian translation.
{
	Russian russian;
	testTranslationFormat(russian);
	testTranslationSpaces(russian);
}

TEST_F(TranslationF, Spanish)
// Test the Spanish translation.
{
	Spanish spanish;
	testTranslationFormat(spanish);
	testTranslationSpaces(spanish);
}

TEST_F(TranslationF, Swedish)
// Test the Swedish translation.
{
	Swedish swedish;
	testTranslationFormat(swedish);
	testTranslationSpaces(swedish);
}

TEST_F(TranslationF, Ukrainian)
// Test the Ukrainian translation.
{
	Ukrainian ukrainian;
	testTranslationFormat(ukrainian);
	testTranslationSpaces(ukrainian);
}

//----------------------------------------------------------------------------

}  // namespace
