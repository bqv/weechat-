#pragma once

// CBufferCtrl

class CBufferCtrl : public CWnd
{
    DECLARE_DYNAMIC(CBufferCtrl)

protected:
    DECLARE_MESSAGE_MAP()
    CHARRANGE m_crRE;
    CHARFORMAT2 m_cfRE;
    SETTEXTEX m_st;

    // Constructors
public:
    CBufferCtrl();
    virtual ~CBufferCtrl();

    // Attributes
    TEXTRANGE m_trRE;
    LPSTR m_lpszChar;

    void SetSel(long nStartChar, long nEndChar);
    BOOL SetDefaultCharFormat(DWORD dwMask, COLORREF crTextColor, DWORD dwEffects, LPTSTR szFaceName, LONG yHeight, COLORREF crBackColor);
    void SetTextToControl(CString csText, int nSTFlags, int nSTCodepage);
    void GetTextRange(int ncharrMin, int ncharrMax);
    int ReplaceAllRtf(_In_ CStringA szNewRtf);
    int ReplaceSelRtf(_In_ CStringA szNewRtf);
    inline void LimitText(int nChars)
    { ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, EM_LIMITTEXT, nChars, 0); }
    inline BOOL SetCharFormat(DWORD dwChFmt, CHARFORMAT pChFmt)
    { ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, EM_SETCHARFORMAT, dwChFmt, (LPARAM)&pChFmt); }
    inline void ScrollCaret()
    { ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, EM_SCROLLCARET, 0, 0); }
    inline BOOL CanUndo() const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL)::SendMessage(m_hWnd, EM_CANUNDO, 0, 0); }
    inline BOOL CanRedo() const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL)::SendMessage(m_hWnd, EM_CANREDO, 0, 0); }
    inline UNDONAMEID GetUndoName() const
	{ ASSERT(::IsWindow(m_hWnd)); return (UNDONAMEID) ::SendMessage(m_hWnd, EM_GETUNDONAME, 0, 0); }
    inline UNDONAMEID GetRedoName() const
	{ ASSERT(::IsWindow(m_hWnd)); return (UNDONAMEID) ::SendMessage(m_hWnd, EM_GETREDONAME, 0, 0); }
    inline int GetLineCount() const
	{ ASSERT(::IsWindow(m_hWnd)); return (int)::SendMessage(m_hWnd, EM_GETLINECOUNT, 0, 0); }
    inline BOOL GetModify() const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL)::SendMessage(m_hWnd, EM_GETMODIFY, 0, 0); }
    inline void SetModify(_In_ BOOL bModified /* = TRUE */)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, EM_SETMODIFY, bModified, 0);}
    inline BOOL SetTextMode(_In_ UINT fMode)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, EM_SETTEXTMODE, (WPARAM) fMode, 0); }
    inline UINT GetTextMode() const
	{ ASSERT(::IsWindow(m_hWnd)); return (UINT) ::SendMessage(m_hWnd, EM_GETTEXTMODE, 0, 0); }
    inline void GetRect(_Out_ LPRECT lpRect) const
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, EM_GETRECT, 0, (LPARAM)lpRect); }
    inline CPoint GetCharPos(_In_ long lChar) const
	{ ASSERT(::IsWindow(m_hWnd)); CPoint pt; ::SendMessage(m_hWnd, EM_POSFROMCHAR, (WPARAM)&pt, (LPARAM)lChar); return pt;}
    inline UINT GetOptions() const
	{ ASSERT(::IsWindow(m_hWnd)); return (UINT) ::SendMessage(m_hWnd, EM_GETOPTIONS, 0, 0); }
    inline void SetOptions(_In_ WORD wOp, _In_ DWORD dwFlags)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, EM_SETOPTIONS, (WPARAM)wOp, (LPARAM)dwFlags); }
    inline BOOL SetAutoURLDetect(_In_ BOOL bEnable /* = TRUE */)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, EM_AUTOURLDETECT, (WPARAM) bEnable, 0); }
    inline void EmptyUndoBuffer()
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, EM_EMPTYUNDOBUFFER, 0, 0); }
    inline UINT SetUndoLimit(_In_ UINT nLimit)
	{ ASSERT(::IsWindow(m_hWnd)); return (UINT) ::SendMessage(m_hWnd, EM_SETUNDOLIMIT, (WPARAM) nLimit, 0); }
    inline void ReplaceSel(_In_z_ LPCTSTR lpszNewText, _In_ BOOL bCanUndo = FALSE)
	{ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, EM_REPLACESEL, (WPARAM) bCanUndo, (LPARAM)lpszNewText); }
    inline void SetRect(_In_ LPCRECT lpRect)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, EM_SETRECT, 0, (LPARAM)lpRect); }
    inline void StopGroupTyping()
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, EM_STOPGROUPTYPING, 0, 0); }
    inline BOOL Redo()
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, EM_REDO, 0, 0); }
    inline BOOL Undo()
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL)::SendMessage(m_hWnd, EM_UNDO, 0, 0); }
    inline void Clear()
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, WM_CLEAR, 0, 0); }
    inline void Copy()
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, WM_COPY, 0, 0); }
    inline void Cut()
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, WM_CUT, 0, 0); }
    inline void Paste()
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, WM_PASTE, 0, 0); }
    inline BOOL SetReadOnly(_In_ BOOL bReadOnly /* = TRUE */ )
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL)::SendMessage(m_hWnd, EM_SETREADONLY, bReadOnly, 0L); }
    inline int GetFirstVisibleLine() const
	{ ASSERT(::IsWindow(m_hWnd)); return (int)::SendMessage(m_hWnd, EM_GETFIRSTVISIBLELINE, 0, 0L); }
    inline BOOL DisplayBand(_In_ LPRECT pDisplayRect)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL)::SendMessage(m_hWnd, EM_DISPLAYBAND, 0, (LPARAM)pDisplayRect); }
    inline void GetSel(_Out_ CHARRANGE &cr) const
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, EM_EXGETSEL, 0, (LPARAM)&cr); }
    inline BOOL GetPunctuation(_In_ UINT fType, _Out_ PUNCTUATION* lpPunc) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, EM_GETPUNCTUATION, (WPARAM) fType, (LPARAM) lpPunc); }
    inline BOOL SetPunctuation(_In_ UINT fType, _In_ PUNCTUATION* lpPunc)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, EM_SETPUNCTUATION, (WPARAM) fType, (LPARAM) lpPunc); }
    inline void LimitText(_In_ long nChars)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, EM_EXLIMITTEXT, 0, nChars); }
    inline long LineFromChar(_In_ long nIndex) const
	{ ASSERT(::IsWindow(m_hWnd)); return (long)::SendMessage(m_hWnd, EM_EXLINEFROMCHAR, 0, nIndex); }
    inline CPoint PosFromChar(_In_ UINT nChar) const
	{ ASSERT(::IsWindow(m_hWnd)); POINTL pt; ::SendMessage(m_hWnd, EM_POSFROMCHAR, (WPARAM)&pt, nChar); return CPoint(pt.x, pt.y); }
    inline int CharFromPos(_In_ CPoint pt) const
	{ ASSERT(::IsWindow(m_hWnd)); POINTL ptl = {pt.x, pt.y}; return (int)::SendMessage(m_hWnd, EM_CHARFROMPOS, 0, (LPARAM)&ptl); }
    inline void SetSel(_In_ CHARRANGE &cr)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, EM_EXSETSEL, 0, (LPARAM)&cr); }
    inline DWORD FindWordBreak(_In_ UINT nCode, _In_ DWORD nStart) const
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD)::SendMessage(m_hWnd, EM_FINDWORDBREAK, (WPARAM) nCode, (LPARAM) nStart); }

#pragma push_macro("FindTextA")
#pragma push_macro("FindTextW")
#undef FindTextA
#undef FindTextW
    inline long FindText(_In_ DWORD dwFlags, _Out_ FINDTEXTEX* pFindText) const
	{ ASSERT(::IsWindow(m_hWnd)); return (long)::SendMessage(m_hWnd, EM_FINDTEXTEX, dwFlags, (LPARAM)pFindText); }
#pragma pop_macro("FindTextA")
#pragma pop_macro("FindTextW")

    inline long FormatRange(_In_ FORMATRANGE* pfr, _In_ BOOL bDisplay)
	{ ASSERT(::IsWindow(m_hWnd)); return (long)::SendMessage(m_hWnd, EM_FORMATRANGE, (WPARAM)bDisplay, (LPARAM)pfr); }

    inline long GetEventMask() const
	{ ASSERT(::IsWindow(m_hWnd)); return (long)::SendMessage(m_hWnd, EM_GETEVENTMASK, 0, 0L); }

    inline long GetLimitText() const
	{ ASSERT(::IsWindow(m_hWnd)); return (long)::SendMessage(m_hWnd, EM_GETLIMITTEXT, 0, 0L); }

#pragma warning(push)
#pragma warning(disable: 6054)
    inline long GetSelText(_Pre_notnull_ _Post_z_ LPSTR lpBuf) const
	{ ASSERT(::IsWindow(m_hWnd)); return (long)::SendMessage(m_hWnd, EM_GETSELTEXT, 0, (LPARAM)lpBuf); }
#pragma warning(pop)

    inline void HideSelection(_In_ BOOL bHide, _In_ BOOL bPerm)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, EM_HIDESELECTION, bHide, bPerm); }

    inline void RequestResize()
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, EM_REQUESTRESIZE, 0, 0L); }

    inline WORD GetSelectionType() const
	{ ASSERT(::IsWindow(m_hWnd)); return (WORD)::SendMessage(m_hWnd, EM_SELECTIONTYPE, 0, 0L); }

    inline UINT GetWordWrapMode() const
	{ ASSERT(::IsWindow(m_hWnd)); return (UINT) ::SendMessage(m_hWnd, EM_GETWORDWRAPMODE, 0, 0); }

    inline UINT SetWordWrapMode(_In_ UINT uFlags) const
	{ ASSERT(::IsWindow(m_hWnd)); return (UINT) ::SendMessage(m_hWnd, EM_SETWORDWRAPMODE, (WPARAM) uFlags, 0); }

    inline COLORREF SetBackgroundColor(_In_ BOOL bSysColor, _In_ COLORREF cr)
	{ ASSERT(::IsWindow(m_hWnd)); return (COLORREF)::SendMessage(m_hWnd, EM_SETBKGNDCOLOR, bSysColor, cr); }

    inline DWORD SetEventMask(_In_ DWORD dwEventMask)
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD)::SendMessage(m_hWnd, EM_SETEVENTMASK, 0, dwEventMask); }

    inline BOOL SetOLECallback(_In_ IRichEditOleCallback* pCallback)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL)::SendMessage(m_hWnd, EM_SETOLECALLBACK, 0, (LPARAM)pCallback); }

    inline BOOL SetTargetDevice(_In_ HDC hDC, _In_ long lLineWidth)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL)::SendMessage(m_hWnd, EM_SETTARGETDEVICE, (WPARAM)hDC, lLineWidth); }

    inline BOOL SetTargetDevice(_In_ CDC &dc, _In_ long lLineWidth)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL)::SendMessage(m_hWnd, EM_SETTARGETDEVICE, (WPARAM)dc.m_hDC, lLineWidth); }

    inline long StreamIn(_In_ int nFormat, EDITSTREAM &es)
	{ ASSERT(::IsWindow(m_hWnd)); return (long)::SendMessage(m_hWnd, EM_STREAMIN, nFormat, (LPARAM)&es); }

    inline long StreamOut(_In_ int nFormat, EDITSTREAM &es)
	{ ASSERT(::IsWindow(m_hWnd)); return (long)::SendMessage(m_hWnd, EM_STREAMOUT, nFormat, (LPARAM)&es); }

    inline long GetTextLength() const
	{ ASSERT(::IsWindow(m_hWnd)); return (long)::SendMessage(m_hWnd, WM_GETTEXTLENGTH, NULL, NULL); }

    // Message handlers
protected:
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void CBufferCtrl::OnPaint();

private:
    BOOL RegisterWndClass();
    static DWORD CALLBACK EditStreamCallback(_In_ DWORD_PTR dwCookie, _In_ LPBYTE pbBuff, _In_ LONG cb, _In_ LONG *pcb);
};
