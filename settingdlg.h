/////////////////////////////////////////////////////////////////////////////
// Name:        settingdlg.h
// Purpose:     
// Author:      Kevin Wu
// Modified by: 
// Created:     07/04/2020 09:35:54
// RCS-ID:      
// Copyright:   (C) Kevin Wu
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _SETTINGDLG_H_
#define _SETTINGDLG_H_


/*!
 * Includes
 */

////@begin includes
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_SETTINGDLG 10000
#define ID_TEXTCTRL 10001
#define ID_BUTTON 10002
#define ID_TEXTCTRL1 10003
#define ID_CHECKBOX1 10005
#define ID_CHECKBOX2 10006
#define ID_CHECKBOX3 10007
#define ID_BUTTON1 10008
#define ID_CHECKBOX 10004
#define SYMBOL_SETTINGDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_SETTINGDLG_TITLE _("Print Key Settings")
#define SYMBOL_SETTINGDLG_IDNAME ID_SETTINGDLG
#define SYMBOL_SETTINGDLG_SIZE wxSize(400, 300)
#define SYMBOL_SETTINGDLG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * SettingDlg class declaration
 */

class SettingDlg: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( SettingDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    SettingDlg();
    SettingDlg( wxWindow* parent, wxWindowID id = SYMBOL_SETTINGDLG_IDNAME, const wxString& caption = SYMBOL_SETTINGDLG_TITLE, const wxPoint& pos = SYMBOL_SETTINGDLG_POSITION, const wxSize& size = SYMBOL_SETTINGDLG_SIZE, long style = SYMBOL_SETTINGDLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_SETTINGDLG_IDNAME, const wxString& caption = SYMBOL_SETTINGDLG_TITLE, const wxPoint& pos = SYMBOL_SETTINGDLG_POSITION, const wxSize& size = SYMBOL_SETTINGDLG_SIZE, long style = SYMBOL_SETTINGDLG_STYLE );

    /// Destructor
    ~SettingDlg();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin SettingDlg event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
    void OnButtonClick( wxCommandEvent& event );

    /// wxEVT_KEY_DOWN event handler for ID_TEXTCTRL1
    void OnKeyDown( wxKeyEvent& event );

    /// wxEVT_SET_FOCUS event handler for ID_TEXTCTRL1
    void OnSetFocus( wxFocusEvent& event );

    /// wxEVT_KILL_FOCUS event handler for ID_TEXTCTRL1
    void OnKillFocus( wxFocusEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1
    void OnButton1Click( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOkClick( wxCommandEvent& event );

////@end SettingDlg event handler declarations

////@begin SettingDlg member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end SettingDlg member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin SettingDlg member variables
    wxTextCtrl* m_path;
    wxButton* m_browse;
    wxTextCtrl* m_key;
    wxStaticText* m_hint;
    wxCheckBox* m_shift;
    wxCheckBox* m_ctrl;
    wxCheckBox* m_alt;
    wxButton* m_prtsc;
    wxCheckBox* m_autostart;
////@end SettingDlg member variables

};

#endif
    // _SETTINGDLG_H_
