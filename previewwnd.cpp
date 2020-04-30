/////////////////////////////////////////////////////////////////////////////
// Name:        previewwnd.cpp
// Purpose:     
// Author:      Kevin Wu
// Modified by: 
// Created:     07/04/2020 09:32:56
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

#include "wx/mstream.h"
#include "wx/display.h"
#include "wx/utils.h"
#include "wx/tokenzr.h"
#include "wx/dcbuffer.h"

////@begin includes
////@end includes

#include "previewwnd.h"
#include "settingdlg.h"
#include "printkeyapp.h"

////@begin XPM images
////@end XPM images




// ----------------------------------------------------------------------------
// MyTaskBarIcon implementation
// ----------------------------------------------------------------------------

enum
{
	PU_SETTINGS = 10001,
	PU_EXIT
};


BEGIN_EVENT_TABLE(PKTaskBarIcon, wxTaskBarIcon)
	EVT_MENU(PU_SETTINGS, PKTaskBarIcon::OnMenuSettings)
	EVT_MENU(PU_EXIT, PKTaskBarIcon::OnMenuExit)
	EVT_TASKBAR_LEFT_DCLICK(PKTaskBarIcon::OnLeftButtonDClick)
END_EVENT_TABLE()

void PKTaskBarIcon::OnMenuSettings(wxCommandEvent&)
{
	wxCommandEvent evt(wxEVT_NULL, EVENT_TRAYICON_MENU);
	evt.SetInt(PU_SETTINGS);
	::wxPostEvent(PreviewWnd::m_pKeyEventHandler, evt);
}

void PKTaskBarIcon::OnMenuExit(wxCommandEvent&)
{
	wxCommandEvent evt(wxEVT_NULL, EVENT_TRAYICON_MENU);
	evt.SetInt(PU_EXIT);
	::wxPostEvent(PreviewWnd::m_pKeyEventHandler, evt);
}

// Overridables
wxMenu *PKTaskBarIcon::CreatePopupMenu()
{
	wxMenu *menu = new wxMenu;
	menu->Append(PU_SETTINGS, _("Settings"));

	/* OSX has built-in quit menu for the dock menu, but not for the status item */
#ifdef __WXOSX__ 
	if (OSXIsStatusItem())
#endif

	menu->AppendSeparator();
	menu->Append(PU_EXIT, _("Exit"));
	return menu;
}

void PKTaskBarIcon::OnLeftButtonDClick(wxTaskBarIconEvent&)
{
	wxCommandEvent evt(wxEVT_NULL, EVENT_TRAYICON_MENU);
	evt.SetInt(PU_SETTINGS);
	::wxPostEvent(PreviewWnd::m_pKeyEventHandler, evt);
}

/*
 * PreviewWnd type definition
 */

IMPLEMENT_CLASS( PreviewWnd, wxFrame )


/*
 * PreviewWnd event table definition
 */

BEGIN_EVENT_TABLE( PreviewWnd, wxFrame )

////@begin PreviewWnd event table entries
    EVT_PAINT( PreviewWnd::OnPaint )
    EVT_LEFT_DOWN( PreviewWnd::OnLeftDown )
    EVT_LEFT_UP( PreviewWnd::OnLeftUp )
    EVT_MOTION( PreviewWnd::OnMotion )
    EVT_KEY_DOWN( PreviewWnd::OnKeyDown )
////@end PreviewWnd event table entries

	EVT_COMMAND(EVENT_HOOKED_KEY_PRESSED, wxEVT_NULL, PreviewWnd::onHookedKeyPressed)
	EVT_COMMAND(EVENT_TRAYICON_MENU, wxEVT_NULL, PreviewWnd::onTrayIconMenu)

END_EVENT_TABLE()

wxEvtHandler * PreviewWnd::m_pKeyEventHandler = NULL;

/*
 * PreviewWnd constructors
 */

PreviewWnd::PreviewWnd()
{
    Init();
}

PreviewWnd::PreviewWnd( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}


/*
 * PreviewWnd creator
 */

bool PreviewWnd::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin PreviewWnd creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end PreviewWnd creation
    return true;
}


/*
 * PreviewWnd destructor
 */

PreviewWnd::~PreviewWnd()
{
////@begin PreviewWnd destruction
////@end PreviewWnd destruction

	delete m_taskBarIcon;

#if defined(__WXCOCOA__)
	delete m_dockIcon;
#endif

	if (m_hKeyboardHook)
		UnhookWindowsHookEx(m_hKeyboardHook);

	if (m_hDll)
		FreeLibrary(m_hDll);
}


/*
 * Member initialisation
 */

void PreviewWnd::Init()
{
////@begin PreviewWnd member initialisation
////@end PreviewWnd member initialisation
	m_hDll = NULL;
	m_hKeyboardHook = 0;
	m_pKeyEventHandler = GetEventHandler();

	m_hDll = LoadLibrary(_T("User32.dll"));

	m_hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)&PreviewWnd::KeyboardHookProc, m_hDll, 0);

	m_taskBarIcon = new PKTaskBarIcon();

#ifdef WIN32
	wxIcon icon(wxT("WXICON_AAA"), wxBITMAP_TYPE_ICO_RESOURCE);
	SetIcon(icon);
#endif

	m_taskBarIcon->SetIcon(GetIcon(), _("Press PrtSc Key on Keybaord to Print Screen"));

#if defined(__WXOSX__) && wxOSX_USE_COCOA
	m_dockIcon = new MyTaskBarIcon(wxTBI_DOCK);
	m_dockIcon->SetIcon(wxICON(sample));
#endif

#if wxUSE_GRAPHICS_CONTEXT
	m_renderer = wxGraphicsRenderer::GetDefaultRenderer();
#endif
}


/*
 * Control creation for PreviewWnd
 */

void PreviewWnd::CreateControls()
{    
////@begin PreviewWnd content construction
    PreviewWnd* itemFrame1 = this;

////@end PreviewWnd content construction
}


/*
 * Should we show tooltips?
 */

bool PreviewWnd::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap PreviewWnd::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin PreviewWnd bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end PreviewWnd bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon PreviewWnd::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin PreviewWnd icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end PreviewWnd icon retrieval
}




/*
 * wxEVT_LEFT_DOWN event handler for ID_PREVIEWWND
 */

void PreviewWnd::OnLeftDown( wxMouseEvent& event )
{
}


/*
 * wxEVT_LEFT_UP event handler for ID_PREVIEWWND
 */

void PreviewWnd::OnLeftUp( wxMouseEvent& event )
{
////@begin wxEVT_LEFT_UP event handler for ID_PREVIEWWND in PreviewWnd.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_LEFT_UP event handler for ID_PREVIEWWND in PreviewWnd. 
}


/*
 * wxEVT_MOTION event handler for ID_PREVIEWWND
 */

void PreviewWnd::OnMotion( wxMouseEvent& event )
{
////@begin wxEVT_MOTION event handler for ID_PREVIEWWND in PreviewWnd.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_MOTION event handler for ID_PREVIEWWND in PreviewWnd. 
}


/*
 * wxEVT_PAINT event handler for ID_PREVIEWWND
 */

void PreviewWnd::OnPaint( wxPaintEvent& event )
{
	wxBufferedPaintDC pdc(this);

#if wxUSE_GRAPHICS_CONTEXT
	wxGCDC gdc;

	if (m_renderer)
	{
		wxGraphicsContext* context;
		context = m_renderer->CreateContext(pdc);

		gdc.SetBackground(GetBackgroundColour());
		gdc.SetGraphicsContext(context);
	}

	wxDC &dc = m_renderer ? static_cast<wxDC&>(gdc) : pdc;
#else
	wxDC &dc = pdc;
#endif

	PrepareDC(dc);
	dc.Clear();

	//dc.SetBackgroundMode(wxSOLID);//*/wxTRANSPARENT);
	//dc.SetBackground(*wxBLACK_BRUSH);

	dc.DrawBitmap(bg, 0, 0, false);

	wxRect rc = GetClientRect();

#if wxUSE_GRAPHICS_CONTEXT
	dc.SetPen(*wxTRANSPARENT_PEN);
	dc.SetBrush(wxBrush(wxColour(0, 0, 0, 150)));
	dc.DrawRectangle(rc);
#endif

	dc.SetPen(wxPen(wxColour(255, 210, 2), 4));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	dc.DrawRectangle(rc);

	//int cx, cy;
	//GetClientSize(&cx, &cy);
	//dc.DrawLine(0, 0, 0, cy);
	//dc.DrawLine(0, cy, cx, cy);
	//dc.DrawLine(0, 0, cx, 0);
	//dc.DrawLine(cx, 0, cx, cy);
}


/*
 * wxEVT_KEY_DOWN event handler for ID_PREVIEWWND
 */

void PreviewWnd::OnKeyDown( wxKeyEvent& event )
{
	if (event.GetKeyCode() == VK_ESCAPE)
	{
		Hide();
	}
}

LRESULT CALLBACK PreviewWnd::KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *pkh = (KBDLLHOOKSTRUCT *)lParam;
	if (nCode >= 0)
	{
		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
		{
			if (!(pkh->flags & LLKHF_INJECTED) && PreviewWnd::m_pKeyEventHandler)
			{
				wxArrayString keys = wxStringTokenize(wxGetApp().m_config.hotKey, wxT("+"));

				wxString hotKey = keys.Last();
				bool shift = false;
				bool ctrl = false;
				bool alt = false;

				for (int i = 0; i < keys.Count(); i++)
				{
					if (keys[i] == wxT("Shift"))
						shift = true;
					else if (keys[i] == wxT("Ctrl"))
						ctrl = true;
					else if (keys[i] == wxT("Alt"))
						alt = true;
				}

				wxString keyString = wxEmptyString;

				switch (pkh->vkCode)
				{
				case VK_SNAPSHOT:
					keyString = wxT("PrtSc");
					break;
				case VK_F1:
					keyString = wxT("F1");
					break;
				case VK_F2:
					keyString = wxT("F2");
					break;
				case VK_F3:
					keyString = wxT("F3");
					break;
				case VK_F4:
					keyString = wxT("F4");
					break;
				case VK_F5:
					keyString = wxT("F5");
					break;
				case VK_F6:
					keyString = wxT("F6");
					break;
				case VK_F7:
					keyString = wxT("F7");
					break;
				case VK_F8:
					keyString = wxT("F8");
					break;
				case VK_F9:
					keyString = wxT("F9");
					break;
				case VK_F10:
					keyString = wxT("F10");
					break;
				default:
					if ((pkh->vkCode >= 0x30 && pkh->vkCode <= 0x39) || (pkh->vkCode >= 0x41 && pkh->vkCode <= 0x5c))
					{
						TCHAR key = MapVirtualKey(pkh->vkCode, MAPVK_VK_TO_CHAR);
						keyString = key;
					}
				}

				bool shift_pressed = GetAsyncKeyState(VK_SHIFT) & 0x8000;
				bool ctrl_pressed = GetAsyncKeyState(VK_CONTROL) & 0x8000;
				bool alt_pressed = GetAsyncKeyState(VK_MENU) & 0x8000;

				if (shift == shift_pressed &&
					ctrl == ctrl_pressed &&
					alt == alt_pressed &&
					keyString == hotKey)
				{
					wxCommandEvent evt(wxEVT_NULL, EVENT_HOOKED_KEY_PRESSED);
					evt.SetInt(1);
					::wxPostEvent(PreviewWnd::m_pKeyEventHandler, evt);
				}
			}
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void PreviewWnd::onHookedKeyPressed(wxCommandEvent& event)
{
	if (IsShown())
		return;
	
	// get the active screen where current mouse point stay
	wxPoint mouse = wxGetMousePosition();
	wxDisplay active(wxDisplay::GetFromPoint(mouse));

	wxRect rc = active.GetGeometry();

	POINT pt;
	pt.x = mouse.x;
	pt.y = mouse.y;

	HMONITOR hMonitor = ::MonitorFromPoint(pt, NULL);

	MONITORINFOEX mi;
	mi.cbSize = sizeof(mi);
	::GetMonitorInfo(hMonitor, &mi);
	std::wstring monitorName = mi.szDevice;
	
	HDC hDC = ::CreateDC(monitorName.c_str(), monitorName.c_str(), NULL, NULL);
	int bpp = ::GetDeviceCaps(hDC, BITSPIXEL) * ::GetDeviceCaps(hDC, PLANES);

	if (bpp < 24)
		return;	// can only handle RGB or RGBA format

	int imageSize = rc.width * rc.height * bpp / 8;

	BITMAPINFO bi = { 0 };
	BITMAPINFOHEADER *bih = &bi.bmiHeader;
	bih->biSize = sizeof(BITMAPINFOHEADER);
	bih->biBitCount = bpp;
	bih->biWidth = rc.width;
	bih->biHeight = rc.height;
	bih->biSizeImage = imageSize;
	bih->biPlanes = 1;
	bih->biClrImportant = 0;
	bih->biClrUsed = 0;
	bih->biCompression = 0;
	bih->biXPelsPerMeter = 0;
	bih->biYPelsPerMeter = 0;

	BYTE* bits;
	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP membmp = CreateDIBSection(hMemDC, &bi,
		DIB_RGB_COLORS, (void**)&bits,
		NULL, 0);
	HBITMAP old_bmp = (HBITMAP) SelectObject(hMemDC, membmp);

	BOOL bRet = ::BitBlt(hMemDC, 0, 0, rc.width, rc.height, hDC, 0, 0, SRCCOPY | CAPTUREBLT);

	if (!bRet)
		return;

	void *pData = malloc(imageSize);
	memcpy(pData, bits, imageSize);

	if (hMemDC)
	{
		SelectObject(hMemDC, old_bmp);
		DeleteDC(hMemDC);
		DeleteObject(membmp);
	}

	if (hDC)
	{
		DeleteDC(hDC);
	}

	if (bpp == 32)
	{
		// change RGBA to RGB
		BYTE * data = (BYTE*) pData;
		for (int i = 1; i < rc.width*rc.height; i++)
		{
			data[i * 3] = data[i * 4 + 2];
			data[i * 3 + 1] = data[i * 4 + 1];
			data[i * 3 + 2] = data[i * 4];
		}
	}

	//void *pAlpha = malloc(rc.width*rc.height);
	//memset(pAlpha, 128, rc.width*rc.height);

	//wxImage screen(rc.width, rc.height, (BYTE*) pData, (BYTE*) pAlpha, false);
	wxImage screen(rc.width, rc.height, (BYTE*) pData, false);

	bg = screen.Mirror(false);

	//bg.SaveFile("d:\\test.bmp");
	SetSize(rc);
	Move(rc.x, rc.y);
	//SetWindowStyle()

	Show(true);
	//ShowFullScreen(true);
}

void PreviewWnd::onTrayIconMenu(wxCommandEvent& event)
{
	switch (event.GetInt())
	{
	case PU_SETTINGS:
		{
			if (IsShown())
				return;

			SettingDlg setting(this);
			if (setting.ShowModal() == wxID_OK)
			{
				// if hot key changed, reload keyboardhook
			}
		}
		break;
	case PU_EXIT:
		Destroy();
		break;
	}
}

