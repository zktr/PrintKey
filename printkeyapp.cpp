/////////////////////////////////////////////////////////////////////////////
// Name:        printkeyapp.cpp
// Purpose:     
// Author:      Kevin Wu
// Modified by: 
// Created:     07/04/2020 09:31:50
// RCS-ID:      
// Copyright:   (C) Kevin Wu
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/stdpaths.h"
#include "wx/wfstream.h"
#include "wx/fileconf.h"

#include "wx/msw/registry.h"
#include "wx/msw/private.h"

////@begin includes
////@end includes

#include "printkeyapp.h"

////@begin XPM images
////@end XPM images


/*
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( PrintKeyApp )
////@end implement app


/*
 * PrintKeyApp type definition
 */

IMPLEMENT_CLASS( PrintKeyApp, wxApp )


/*
 * PrintKeyApp event table definition
 */

BEGIN_EVENT_TABLE( PrintKeyApp, wxApp )

////@begin PrintKeyApp event table entries
////@end PrintKeyApp event table entries

END_EVENT_TABLE()


/*
 * Constructor for PrintKeyApp
 */

PrintKeyApp::PrintKeyApp()
{
    Init();
}


/*
 * Member initialisation
 */

void PrintKeyApp::Init()
{
////@begin PrintKeyApp member initialisation
////@end PrintKeyApp member initialisation
}

/*
 * Initialisation for PrintKeyApp
 */

bool PrintKeyApp::OnInit()
{
#ifndef _DEBUG
	wxLog::EnableLogging(false);
#endif

	if (m_locale.Init(wxLANGUAGE_DEFAULT, wxLOCALE_LOAD_DEFAULT))
	{
		wxString resDir = wxPathOnly(wxStandardPaths::Get().GetExecutablePath()) + wxFILE_SEP_PATH + wxT("lang");

		m_locale.AddCatalogLookupPathPrefix(resDir);
		m_locale.AddCatalog(wxT("printkey"));
	}
	else
	{
		wxLogDebug("Initialize wxLocale FALSE.");
	}

	m_configFilePath = wxPathOnly(wxStandardPaths::Get().GetUserLocalDataDir()) + wxFILE_SEP_PATH + wxT("PrintKey");

	if (!::wxDirExists(m_configFilePath))
	{
		::wxMkdir(m_configFilePath);
	}

	m_configFilePath += wxFILE_SEP_PATH;
	m_configFilePath += wxT("printkey.ini");

	LoadConfig();

////@begin PrintKeyApp initialisation
	// Remove the comment markers above and below this block
	// to make permanent changes to the code.

#if wxUSE_XPM
	wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif
	PreviewWnd* mainWindow = new PreviewWnd( NULL );
//	mainWindow->ShowFullScreen(true);
	mainWindow->Show(false);
////@end PrintKeyApp initialisation

    return true;
}


/*
 * Cleanup for PrintKeyApp
 */

int PrintKeyApp::OnExit()
{    
////@begin PrintKeyApp cleanup
	return wxApp::OnExit();
////@end PrintKeyApp cleanup
}

void PrintKeyApp::LoadConfig()
{
	wxString userPicturesPath = wxPathOnly(wxStandardPaths::Get().GetDocumentsDir()) + wxFILE_SEP_PATH + wxT("Pictures");
	if (!wxDirExists(userPicturesPath))
	{
		userPicturesPath = wxPathOnly(wxStandardPaths::Get().GetDocumentsDir()) + wxFILE_SEP_PATH + wxT("Documents");

		if (!wxDirExists(userPicturesPath))
			userPicturesPath = wxPathOnly(wxStandardPaths::Get().GetDocumentsDir());
	}

	m_config.imagePath = userPicturesPath;
	m_config.hotKey = wxT("PrtSc");

	if (::wxFileExists(m_configFilePath))
	{
		wxFileInputStream fis(m_configFilePath);
		wxFileConfig config(fis);

		config.SetPath(wxT("/PrintKey"));
		config.Read(wxT("ImagePage"), &m_config.imagePath, userPicturesPath);
		config.Read(wxT("HotKey"), &m_config.hotKey, wxT("PrtSc"));
	}

	GetAutoStart();
}

void PrintKeyApp::SaveConfig()
{
	wxFileConfig* pConfig = NULL;

	if (!wxFileName::FileExists(m_configFilePath))
	{
		wxFileOutputStream out(m_configFilePath);
	}

	{
		wxFileInputStream in(m_configFilePath);
		pConfig = new wxFileConfig(in);
	}

	pConfig->SetPath(wxT("/PrintKey"));
	pConfig->Write(wxT("ImagePage"), m_config.imagePath);
	pConfig->Write(wxT("HotKey"), m_config.hotKey);

	wxFileOutputStream out(m_configFilePath);
	pConfig->Save(out);

	delete pConfig;

	SetAutoStart();
}


void PrintKeyApp::GetAutoStart()
{
	m_config.autoStart = false;

	wxRegKey key(wxRegKey::HKCU, wxT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));

	if (key.HasValue(wxT("PrintKey")))
	{
		wxString strExecFullName = wxGetFullModuleName();
		wxString strRegValue;

		if (key.QueryValue(wxT("PrintKey"), strRegValue))
		{
			if (strRegValue.CmpNoCase(strExecFullName) == 0)
			{
				m_config.autoStart = true;
			}
		}
	}
}

void PrintKeyApp::SetAutoStart()
{
	wxRegKey key(wxRegKey::HKCU, wxT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));

	if (!m_config.autoStart)
	{
		bool bExist = key.HasValue(wxT("PrintKey"));

		if (bExist)
		{
			bExist = key.DeleteValue(wxT("PrintKey"));
		}
	}
	else
	{
		wxString strExecFullName = wxGetFullModuleName();
		key.SetValue(wxT("PrintKey"), strExecFullName);
	}
}