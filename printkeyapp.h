/////////////////////////////////////////////////////////////////////////////
// Name:        printkeyapp.h
// Purpose:     
// Author:      Kevin Wu
// Modified by: 
// Created:     07/04/2020 09:31:50
// RCS-ID:      
// Copyright:   (C) Kevin Wu
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _PRINTKEYAPP_H_
#define _PRINTKEYAPP_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
#include "previewwnd.h"
////@end includes


struct PKConfig {
	wxString	imagePath;
	wxString	hotKey;
	bool		autoStart;
};

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
////@end control identifiers

/*!
 * PrintKeyApp class declaration
 */

class PrintKeyApp: public wxApp
{    
    DECLARE_CLASS( PrintKeyApp )
    DECLARE_EVENT_TABLE()

protected:
	wxLocale	m_locale;

public:
    /// Constructor
    PrintKeyApp();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin PrintKeyApp event handler declarations

////@end PrintKeyApp event handler declarations

////@begin PrintKeyApp member function declarations

////@end PrintKeyApp member function declarations

////@begin PrintKeyApp member variables
////@end PrintKeyApp member variables

public:
	PKConfig m_config;
	wxString m_configFilePath;

	void LoadConfig();
	void SaveConfig();
	void GetAutoStart();
	void SetAutoStart();
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(PrintKeyApp)
////@end declare app

#endif
    // _PRINTKEYAPP_H_
