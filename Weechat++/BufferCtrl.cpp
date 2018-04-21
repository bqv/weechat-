// BufferCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "BufferCtrl.h"

#include <streambuf>
#include <istream>

struct membuf : std::streambuf
{
    membuf(char* begin, char* end) {
        this->setg(begin, begin, end);
    }
};

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
    ON_WM_PAINT()
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

int CBufferCtrl::ReplaceAllRtf(CStringA szNewRtf)
{
    ASSERT(::IsWindow(m_hWnd));

    char* buffer = (char*)szNewRtf.GetString();
    size_t length = szNewRtf.GetLength();

    membuf streambuf(buffer, buffer + (length * sizeof(TCHAR)));

    EDITSTREAM es;
    es.dwError = 0;
    es.dwCookie = (DWORD_PTR)&streambuf;
    es.pfnCallback = &CBufferCtrl::EditStreamCallback;

    int ret = SendMessage(EM_STREAMIN, SF_RTF/* | SFF_PLAINRTF*/, (LPARAM)&es);

    if (es.dwError)
    {
        LPTSTR lpMsgBuf;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, es.dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
        AfxMessageBox((LPTSTR)lpMsgBuf);
        LocalFree(lpMsgBuf);
    }

    return ret;
}

int CBufferCtrl::ReplaceSelRtf(CStringA szNewRtf)
{
    ASSERT(::IsWindow(m_hWnd));

    char* buffer = (char*)szNewRtf.GetString();
    size_t length = szNewRtf.GetLength();

    membuf streambuf(buffer, buffer + (length * sizeof(TCHAR)));

    EDITSTREAM es;
    es.dwError = 0;
    es.dwCookie = (DWORD_PTR)&streambuf;
    es.pfnCallback = &CBufferCtrl::EditStreamCallback;

    int ret = SendMessage(EM_STREAMIN, SF_RTF/* | SFF_PLAINRTF*/ | SFF_SELECTION, (LPARAM)&es);

    if (es.dwError)
    {
        LPVOID lpMsgBuf;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, es.dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
        LocalFree(lpMsgBuf);
    }

    return ret;
}

DWORD CBufferCtrl::EditStreamCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb)
{
    membuf* stream = (membuf*)dwCookie;
    char* buffer = (char*)pbBuff;

    if (stream->in_avail() < cb)
    { // streambuf smaller than buffer
        *pcb = static_cast<LONG>(stream->in_avail());
        if (*pcb == 0)
        {
            //return 1;
        }
    }
    else
    { // streambuf larger than buffer
        *pcb = cb;
    }

    stream->sgetn(buffer, *pcb);

    return 0;
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
    CWnd::OnSetFocus(pOldWnd);
    HideCaret();
}

void CBufferCtrl::OnPaint()
{
    CWnd::OnPaint();
    OutputDebugString(_T("ONPAINT"));
}
