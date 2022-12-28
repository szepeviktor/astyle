// ASApp.cpp
// Copyright (c) 2018 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.md describes the conditions under which this software may be distributed.

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include "AStyleWx.h"
#include "AStyleFormat.h"

#if wxMAJOR_VERSION < 3
	#error wxWidgets is not version 3 or greater.
#endif // wxMAJOR_VERSION

//-----------------------------------------------------------------------------
// ASApp
//-----------------------------------------------------------------------------

// Create a ASApp object
wxIMPLEMENT_APP(ASApp);

bool ASApp::OnInit()
{
	wxLocale loc;
	loc.Init();
	// create main window
#if !defined(ASTYLE_DYLIB)
	SetAppName("AStyleWx");
#elif defined(__WXMSW__)
	SetAppName("AStyleWxDll");
#elif defined(__WXOSX__)
	SetAppName("AStyleWxDy");
#else
	SetAppName("AStyleWxSo");
#endif
	m_frame = new ASFrame;
	assert(m_frame != nullptr);
	m_frame->BuildGuiControls(argc, argv);
#ifdef ASTYLE_DYLIB
	AStyleFormat::LoadDynamicLibrary();
#endif
	return true;
}

int ASApp::OnExit()
{
#ifdef ASTYLE_DYLIB
	AStyleFormat::UnloadDynamicLibrary();
#endif
	return 0;
}
