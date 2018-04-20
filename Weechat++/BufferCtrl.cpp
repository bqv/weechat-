// BufferCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "BufferCtrl.h"

// CBufferCtrl

IMPLEMENT_DYNAMIC(CBufferCtrl, CWnd)

CBufferCtrl::CBufferCtrl()
{
    //Register window class
    RegisterWndClass();
}

CBufferCtrl::~CBufferCtrl()
{
}

BEGIN_MESSAGE_MAP(CBufferCtrl, CWnd)
    ON_WM_SETFOCUS()
END_MESSAGE_MAP()

void CBufferCtrl::SetSel(long nStartChar, long nEndChar)
{
    ASSERT(::IsWindow(m_hWnd));

    m_crRE.cpMin = nStartChar;
    m_crRE.cpMax = nEndChar;
    SendMessage(EM_EXSETSEL, 0, (LPARAM)&m_crRE);
}

BOOL CBufferCtrl::SetDefaultCharFormat(DWORD dwMask, COLORREF crTextColor, DWORD dwEffects, LPTSTR  szFaceName, LONG yHeight, COLORREF crBackColor)
{
    ASSERT(::IsWindow(m_hWnd));

    //Set the text defaults.  CHARFORMAT2 m_cfStatus is declared in RichEditControl.h
    m_cfRE.cbSize = sizeof(CHARFORMAT2);
    m_cfRE.dwMask = dwMask;
    m_cfRE.crTextColor = crTextColor;
    m_cfRE.dwEffects = dwEffects;
    ::lstrcpy(m_cfRE.szFaceName, szFaceName);
    m_cfRE.yHeight = yHeight;
    m_cfRE.crBackColor = crBackColor;

    return (BOOL)SendMessage(EM_SETCHARFORMAT, 0, (LPARAM)&m_cfRE);
}

void CBufferCtrl::SetTextToControl(CString csText, int nSTFlags, int nSTCodepage)
{
    ASSERT(::IsWindow(m_hWnd));

    //Set the options. SETTEXTEX m_st declared in RichEditControl.h
    m_st.codepage = nSTCodepage;
    m_st.flags = nSTFlags;
    SendMessage(EM_SETTEXTEX, (WPARAM)&m_st, (LPARAM)(LPCTSTR)csText);
}
void CBufferCtrl::LimitText(int nChars)
{
    ASSERT(::IsWindow(m_hWnd));

    SendMessage(EM_LIMITTEXT, nChars, 0);
}

void CBufferCtrl::GetTextRange(int ncharrMin, int ncharrMax)
{
    ASSERT(::IsWindow(m_hWnd));

    //Set the CHARRANGE for the trRE = the characters sent by ENLINK 
    m_trRE.chrg.cpMin = ncharrMin;
    m_trRE.chrg.cpMax = ncharrMax;

    //Set the size of the character buffers, + 1 for null character
    int nLength = int((m_trRE.chrg.cpMax - m_trRE.chrg.cpMin + 1));

    //create an ANSI buffer and a Unicode (Wide Character) buffer
    m_lpszChar = new CHAR[nLength];
    LPWSTR lpszWChar = new WCHAR[nLength];

    //Set the trRE LPWSTR character buffer = Unicode buffer
    m_trRE.lpstrText = lpszWChar;

    //Get the Unicode text
    SendMessage(EM_GETTEXTRANGE, 0, (LPARAM)&m_trRE);

    // Convert the Unicode RTF text to ANSI.
    WideCharToMultiByte(CP_ACP, 0, lpszWChar, -1, m_lpszChar, nLength, NULL, NULL);

    //Release buffer memory
    delete lpszWChar;

    return;
}

BOOL CBufferCtrl::RegisterWndClass()
{
    WNDCLASS windowclass;
    HINSTANCE hInst = AfxGetInstanceHandle();

    static const LPCTSTR wndClassName = _T("BufferEdit");

    //Check weather the class is registerd already
    if (!(::GetClassInfo(hInst, wndClassName, &windowclass)))
    {
        //If not then we have to register the new class
        ::GetClassInfo(hInst, MSFTEDIT_CLASS, &windowclass);
        windowclass.lpszClassName = wndClassName;

        if (!AfxRegisterClass(&windowclass))
        {
            AfxThrowResourceException();
            return FALSE;
        }
    }

    return TRUE;
}


// CBufferCtrl message handlers

void CBufferCtrl::OnSetFocus(CWnd* pOldWnd)
{
    HideCaret();
}
