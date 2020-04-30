/////////////////////////////////////////////////////////////////////////////
// Name:        previewwnd.h
// Purpose:     
// Author:      Kevin Wu
// Modified by: 
// Created:     07/04/2020 09:32:56
// RCS-ID:      
// Copyright:   (C) Kevin Wu
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _PREVIEWWND_H_
#define _PREVIEWWND_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/frame.h"
////@end includes

#include "wx/gdicmn.h""
#include "wx/taskbar.h"
#include "wx/dcgraph.h"

class PKTaskBarIcon : public wxTaskBarIcon
{
public:
#if defined(__WXOSX__) && wxOSX_USE_COCOA
	MyTaskBarIcon(wxTaskBarIconType iconType = wxTBI_DEFAULT_TYPE)
		: wxTaskBarIcon(iconType)
#else
	PKTaskBarIcon()
#endif
	{}

	void OnLeftButtonDClick(wxTaskBarIconEvent&);
	void OnMenuSettings(wxCommandEvent&);
	void OnMenuExit(wxCommandEvent&);
	virtual wxMenu *CreatePopupMenu();

	wxDECLARE_EVENT_TABLE();
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
#define ID_PREVIEWWND 10000
#define SYMBOL_PREVIEWWND_STYLE wxFRAME_NO_TASKBAR|wxSTAY_ON_TOP|wxNO_BORDER
#define SYMBOL_PREVIEWWND_TITLE _("Preview")
#define SYMBOL_PREVIEWWND_IDNAME ID_PREVIEWWND
#define SYMBOL_PREVIEWWND_SIZE wxSize(1280, 720)
#define SYMBOL_PREVIEWWND_POSITION wxDefaultPosition
////@end control identifiers

#define EVENT_HOOKED_KEY_PRESSED	14587
#define EVENT_TRAYICON_MENU			14588


/*!
 * PreviewWnd class declaration
 */

class PreviewWnd: public wxFrame
{    
    DECLARE_CLASS( PreviewWnd )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    PreviewWnd();
    PreviewWnd( wxWindow* parent, wxWindowID id = SYMBOL_PREVIEWWND_IDNAME, const wxString& caption = SYMBOL_PREVIEWWND_TITLE, const wxPoint& pos = SYMBOL_PREVIEWWND_POSITION, const wxSize& size = wxGetDisplaySize()/*SYMBOL_PREVIEWWND_SIZE*/, long style = SYMBOL_PREVIEWWND_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_PREVIEWWND_IDNAME, const wxString& caption = SYMBOL_PREVIEWWND_TITLE, const wxPoint& pos = SYMBOL_PREVIEWWND_POSITION, const wxSize& size = wxGetDisplaySize()/*SYMBOL_PREVIEWWND_SIZE*/, long style = SYMBOL_PREVIEWWND_STYLE );

    /// Destructor
    ~PreviewWnd();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin PreviewWnd event handler declarations

    /// wxEVT_PAINT event handler for ID_PREVIEWWND
    void OnPaint( wxPaintEvent& event );

    /// wxEVT_LEFT_DOWN event handler for ID_PREVIEWWND
    void OnLeftDown( wxMouseEvent& event );

    /// wxEVT_LEFT_UP event handler for ID_PREVIEWWND
    void OnLeftUp( wxMouseEvent& event );

    /// wxEVT_MOTION event handler for ID_PREVIEWWND
    void OnMotion( wxMouseEvent& event );

    /// wxEVT_KEY_DOWN event handler for ID_PREVIEWWND
    void OnKeyDown( wxKeyEvent& event );

////@end PreviewWnd event handler declarations

////@begin PreviewWnd member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end PreviewWnd member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin PreviewWnd member variables
////@end PreviewWnd member variables

	void onHookedKeyPressed(wxCommandEvent& event);
	void onTrayIconMenu(wxCommandEvent& event);

private:
	HINSTANCE m_hDll;
	HHOOK m_hKeyboardHook;

	PKTaskBarIcon   *m_taskBarIcon;
#if defined(__WXOSX__) && wxOSX_USE_COCOA
	PKTaskBarIcon   *m_dockIcon;
#endif

#if wxUSE_GRAPHICS_CONTEXT
	wxGraphicsRenderer* m_renderer;
#endif

private:
	wxImage bg;

public:

	static LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);
	static wxEvtHandler * m_pKeyEventHandler;
};

#endif
    // _PREVIEWWND_H_
