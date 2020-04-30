/////////////////////////////////////////////////////////////////////////////
// Name:        settingdlg.cpp
// Purpose:     
// Author:      Kevin Wu
// Modified by: 
// Created:     07/04/2020 09:35:54
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

#include "wx/tokenzr.h"

////@begin includes
////@end includes

#include "settingdlg.h"
#include "printkeyapp.h"

////@begin XPM images
////@end XPM images


/*
 * SettingDlg type definition
 */

IMPLEMENT_DYNAMIC_CLASS( SettingDlg, wxDialog )


/*
 * SettingDlg event table definition
 */

BEGIN_EVENT_TABLE( SettingDlg, wxDialog )

////@begin SettingDlg event table entries
    EVT_BUTTON( ID_BUTTON, SettingDlg::OnButtonClick )
    EVT_BUTTON( ID_BUTTON1, SettingDlg::OnButton1Click )
    EVT_BUTTON( wxID_OK, SettingDlg::OnOkClick )
////@end SettingDlg event table entries

END_EVENT_TABLE()


/*
 * SettingDlg constructors
 */

SettingDlg::SettingDlg()
{
    Init();
}

SettingDlg::SettingDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * SettingDlg creator
 */

bool SettingDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin SettingDlg creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();

    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }

    Centre();
////@end SettingDlg creation
    return true;
}


/*
 * SettingDlg destructor
 */

SettingDlg::~SettingDlg()
{
////@begin SettingDlg destruction
////@end SettingDlg destruction
}


/*
 * Member initialisation
 */

void SettingDlg::Init()
{
////@begin SettingDlg member initialisation
    m_path = NULL;
    m_browse = NULL;
    m_key = NULL;
    m_hint = NULL;
    m_shift = NULL;
    m_ctrl = NULL;
    m_alt = NULL;
    m_prtsc = NULL;
    m_autostart = NULL;
////@end SettingDlg member initialisation
}


/*
 * Control creation for SettingDlg
 */

void SettingDlg::CreateControls()
{    
////@begin SettingDlg content construction
    SettingDlg* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(itemBoxSizer1, 1, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer2 = new wxFlexGridSizer(4, 3, 0, 0);
    itemBoxSizer1->Add(itemFlexGridSizer2, 0, wxGROW|wxALL, 0);

    wxStaticText* itemStaticText3 = new wxStaticText( itemDialog1, wxID_STATIC, _("Save Path"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer2->Add(itemStaticText3, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_path = new wxTextCtrl( itemDialog1, ID_TEXTCTRL, wxEmptyString, wxDefaultPosition, wxSize(200, -1), 0 );
    itemFlexGridSizer2->Add(m_path, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_browse = new wxButton( itemDialog1, ID_BUTTON, _("..."), wxDefaultPosition, wxSize(20, -1), 0 );
    itemFlexGridSizer2->Add(m_browse, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Hot Key"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer2->Add(itemStaticText6, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_key = new wxTextCtrl( itemDialog1, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
    itemFlexGridSizer2->Add(m_key, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer2->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer2->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_hint = new wxStaticText( itemDialog1, wxID_STATIC, _("Press Key or Key Combination"), wxDefaultPosition, wxDefaultSize, 0 );
    m_hint->SetForegroundColour(wxColour(0, 128, 255));
    itemFlexGridSizer2->Add(m_hint, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    itemFlexGridSizer2->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer2->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemFlexGridSizer2->Add(itemBoxSizer3, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("Or"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText4->SetForegroundColour(wxColour(0, 128, 255));
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_shift = new wxCheckBox( itemDialog1, ID_CHECKBOX1, _("Shift"), wxDefaultPosition, wxDefaultSize, 0 );
    m_shift->SetValue(false);
    m_shift->SetForegroundColour(wxColour(0, 128, 255));
    itemBoxSizer3->Add(m_shift, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_ctrl = new wxCheckBox( itemDialog1, ID_CHECKBOX2, _("Ctrl"), wxDefaultPosition, wxDefaultSize, 0 );
    m_ctrl->SetValue(false);
    m_ctrl->SetForegroundColour(wxColour(0, 128, 255));
    itemBoxSizer3->Add(m_ctrl, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_alt = new wxCheckBox( itemDialog1, ID_CHECKBOX3, _("Alt"), wxDefaultPosition, wxDefaultSize, 0 );
    m_alt->SetValue(false);
    m_alt->SetForegroundColour(wxColour(0, 128, 255));
    itemBoxSizer3->Add(m_alt, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_prtsc = new wxButton( itemDialog1, ID_BUTTON1, _("PrtSc"), wxDefaultPosition, wxSize(50, 20), 0 );
    m_prtsc->SetForegroundColour(wxColour(0, 128, 255));
    itemBoxSizer3->Add(m_prtsc, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    itemFlexGridSizer2->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_autostart = new wxCheckBox( itemDialog1, ID_CHECKBOX, _("Auto Start Up"), wxDefaultPosition, wxDefaultSize, 0 );
    m_autostart->SetValue(false);
    itemBoxSizer1->Add(m_autostart, 0, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer13 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer13, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxButton* itemButton14 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer13->AddButton(itemButton14);

    wxButton* itemButton15 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer13->AddButton(itemButton15);

    itemStdDialogButtonSizer13->Realize();

    // Connect events and objects
    m_key->Connect(ID_TEXTCTRL1, wxEVT_KEY_DOWN, wxKeyEventHandler(SettingDlg::OnKeyDown), NULL, this);
    m_key->Connect(ID_TEXTCTRL1, wxEVT_SET_FOCUS, wxFocusEventHandler(SettingDlg::OnSetFocus), NULL, this);
    m_key->Connect(ID_TEXTCTRL1, wxEVT_KILL_FOCUS, wxFocusEventHandler(SettingDlg::OnKillFocus), NULL, this);
////@end SettingDlg content construction

	m_path->SetValue(wxGetApp().m_config.imagePath);
	m_key->SetValue(wxGetApp().m_config.hotKey);
	m_autostart->SetValue(wxGetApp().m_config.autoStart);

	wxArrayString keys = wxStringTokenize(wxGetApp().m_config.hotKey, wxT("+"));

	wxString hotKey = keys.Last();

	if (hotKey == wxT("PrtSc"))
	{
		for (int i = 0; i < keys.Count(); i++)
		{
			if (keys[i] == wxT("Shift"))
				m_shift->SetValue(true);
			else if (keys[i] == wxT("Ctrl"))
				m_ctrl->SetValue(true);
			else if (keys[i] == wxT("Alt"))
				m_alt->SetValue(true);
		}

	}

}


/*
 * Should we show tooltips?
 */

bool SettingDlg::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap SettingDlg::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin SettingDlg bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end SettingDlg bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon SettingDlg::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin SettingDlg icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end SettingDlg icon retrieval
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
 */

void SettingDlg::OnButtonClick(wxCommandEvent& event)
{
	wxString caption = _("Please choose a directory");

	wxDirDialog dlg(this, caption);
	dlg.SetPath(m_path->GetValue());
	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		m_path->SetValue(dlg.GetPath());
	}
}

/*
 * wxEVT_KEY_DOWN event handler for ID_TEXTCTRL1
 */

void SettingDlg::OnKeyDown( wxKeyEvent& event )
{
	wxString keyString = wxEmptyString;
	wxChar uc = event.GetUnicodeKey(); 
	if (uc == WXK_NONE)
	{
		switch (event.GetKeyCode())
		{
		case WXK_SNAPSHOT:
			keyString = wxT("PrtSc");
			break;
		case WXK_F1:
			keyString = wxT("F1");
			break;
		case WXK_F2:
			keyString = wxT("F2");
			break;
		case WXK_F3:
			keyString = wxT("F3");
			break;
		case WXK_F4:
			keyString = wxT("F4");
			break;
		case WXK_F5:
			keyString = wxT("F5");
			break;
		case WXK_F6:
			keyString = wxT("F6");
			break;
		case WXK_F7:
			keyString = wxT("F7");
			break;
		case WXK_F8:
			keyString = wxT("F8");
			break;
		case WXK_F9:
			keyString = wxT("F9");
			break;
		case WXK_F10:
			keyString = wxT("F10");
			break;
		case WXK_CONTROL:
		case WXK_SHIFT:
		case WXK_ALT:
			return;
		default:
			m_hint->SetForegroundColour(wxColour(128, 0, 0));
			m_hint->SetLabel(_("Unsupported Key"));
			return;
		}
	}
	else
	{
		wxLogDebug(wxString(uc));
		if ((uc >= '0' && uc <= '9') || (uc >= 'A' && uc <= 'Z'))
		{
			keyString += uc;
		}
		else
		{
			m_hint->SetForegroundColour(wxColour(128, 0, 0));
			m_hint->SetLabel(_("Unsupported Key"));
			return;
		}
	}
		
	m_hint->SetForegroundColour(wxColour(0, 128, 255));
	m_hint->SetLabel(_("Press Key or Key Combination"));
	
	wxString key;

	if (event.ShiftDown())
		key += wxT("Shift+");

	if (event.ControlDown())
		key += wxT("Ctrl+");

	if (event.AltDown())
		key += wxT("Alt+");

	key += keyString;

	m_key->SetValue(key);
}


/*
 * wxEVT_SET_FOCUS event handler for ID_TEXTCTRL1
 */

void SettingDlg::OnSetFocus( wxFocusEvent& event )
{
////@begin wxEVT_SET_FOCUS event handler for ID_TEXTCTRL1 in SettingDlg.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_SET_FOCUS event handler for ID_TEXTCTRL1 in SettingDlg. 
}


/*
 * wxEVT_KILL_FOCUS event handler for ID_TEXTCTRL1
 */

void SettingDlg::OnKillFocus( wxFocusEvent& event )
{
////@begin wxEVT_KILL_FOCUS event handler for ID_TEXTCTRL1 in SettingDlg.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_KILL_FOCUS event handler for ID_TEXTCTRL1 in SettingDlg. 
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
 */

void SettingDlg::OnOkClick( wxCommandEvent& event )
{
	wxString hotkey = m_key->GetValue();

	if (!m_path->GetValue().IsEmpty())
		wxGetApp().m_config.imagePath = m_path->GetValue();

	wxGetApp().m_config.hotKey = hotkey;
	wxGetApp().m_config.autoStart = m_autostart->GetValue();

	wxGetApp().SaveConfig();

	EndModal(wxID_OK);
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1
 */

void SettingDlg::OnButton1Click( wxCommandEvent& event )
{
	m_hint->SetForegroundColour(wxColour(0, 128, 255));
	m_hint->SetLabel(_("Press Key or Key Combination"));

	wxString key;

	if (m_shift->GetValue())
		key += wxT("Shift+");

	if (m_ctrl->GetValue())
		key += wxT("Ctrl+");

	if (m_alt->GetValue())
		key += wxT("Alt+");

	key += wxT("PrtSc");

	m_key->SetValue(key);
}

