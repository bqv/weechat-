// BufferCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "BufferCtrl.h"

// CBufferCtrl

IMPLEMENT_DYNAMIC(CBufferCtrl, CWnd)

const LPCTSTR CBufferCtrl::wndClassName = _T("BufferEdit");

CBufferCtrl::CBufferCtrl()
{
    //Register window class
    RegisterWndClass();
}

CBufferCtrl::~CBufferCtrl()
{
}

BEGIN_MESSAGE_MAP(CBufferCtrl, CWnd)
    ON_MESSAGE(BM_LINES, &CBufferCtrl::OnLines)
    ON_WM_LBUTTONDOWN()
    ON_WM_KILLFOCUS()
    ON_WM_SETFOCUS()
    ON_WM_GETDLGCODE()
    ON_WM_KEYDOWN()
    ON_WM_CHAR()
    ON_WM_ERASEBKGND()
    ON_WM_PAINT()
    ON_WM_MOUSEWHEEL()
    ON_WM_SIZE()
    ON_WM_VSCROLL()
    ON_WM_NCDESTROY()
END_MESSAGE_MAP()

void CBufferCtrl::SetLines(CList<CBufferLine>& lines)
{
    CDC memDC;
    memDC.CreateCompatibleDC(NULL);

    m_lines.RemoveAll();
    for (POSITION pos = lines.GetHeadPosition(); pos != NULL; )
    {
        CBufferLine& line = lines.GetNext(pos);
        if (::IsWindow(m_hWnd))
        {
            SIZE size;

            CString timeStr = line.date.Format(m_timeFormat);
            GetTextExtentPoint(memDC, timeStr, timeStr.GetLength(), &size);
            m_timeWidth = max(m_timeWidth, size.cx);

            CString prefixStr = line.prefix.GetPlain() + " ";
            GetTextExtentPoint(memDC, prefixStr, prefixStr.GetLength(), &size);
            m_prefixWidth = max(m_prefixWidth, size.cx);

            m_lineHeight = size.cy;
        }
        m_lines.AddTail(line);
    }
    RegenerateDocument(&memDC);
}

void CBufferCtrl::AddLine(CBufferLine& line)
{
    CDC memDC;
    memDC.CreateCompatibleDC(NULL);
    SIZE size;

    CString timeStr = line.date.Format(m_timeFormat);
    GetTextExtentPoint(memDC, timeStr, timeStr.GetLength(), &size);
    m_timeWidth = max(m_timeWidth, size.cx);

    CString prefixStr = line.prefix.GetPlain();
    GetTextExtentPoint(memDC, prefixStr, prefixStr.GetLength(), &size);
    m_prefixWidth = max(m_prefixWidth, size.cx);

    m_lineHeight = size.cy;
    m_lines.AddTail(line);
    AppendDocument(&memDC, line);
}

LRESULT CBufferCtrl::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    CWnd* pWnd;

    pWnd = CWnd::FromHandlePermanent(hWnd);
    if (pWnd == NULL) {
        pWnd = new CBufferCtrl();
        pWnd->Attach(hWnd);
    }
    ASSERT(pWnd->m_hWnd == hWnd);
    ASSERT(pWnd == CWnd::FromHandlePermanent(hWnd));
    return AfxCallWndProc(pWnd, hWnd, msg, wParam, lParam);
}

LRESULT CBufferCtrl::OnLines(WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    case BUF_ADDLINE:
        AddLine(*(CBufferLine*)lParam);
        return TRUE;
    case BUF_SETLINES:
        SetLines(*(CList<CBufferLine>*)lParam);
        return TRUE;
    default:
        return FALSE;
    }
}

void CBufferCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    SetFocus();
}

void CBufferCtrl::OnKillFocus(CWnd * pNewWnd)
{
    HideCaret();
    DestroyCaret();
}

void CBufferCtrl::OnSetFocus(CWnd * pOldWnd)
{
    RECT r;
    GetClientRect(&r);
    // Create a solid black caret. 
    CreateSolidCaret(2, r.bottom - r.top);

    ShowCaret();
    //Redraw();
}

UINT CBufferCtrl::OnGetDlgCode()
{
    return DLGC_WANTALLKEYS | DLGC_WANTARROWS;
}

void CBufferCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    //switch (wParam)
    //{
    //}
}

void CBufferCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

BOOL CBufferCtrl::OnEraseBkgnd(CDC * pDC)
{
    CRect rcClient;
    GetClientRect(rcClient);

    if (m_document.dimensions.Height() < rcClient.Height())
        pDC->FillSolidRect(rcClient, GetSysColor(COLOR_WINDOW));

    return TRUE;
}

void CBufferCtrl::OnPaint()
{
    CPaintDC dc(this);

    //Draw Items needed to be drawn
    RedrawVisibleElements(&dc);
}

BOOL CBufferCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    if (zDelta < 0)
        OnVScroll(SB_LINEDOWN, abs(zDelta), NULL);
    else
        OnVScroll(SB_LINEUP, abs(zDelta), NULL);

    return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CBufferCtrl::OnSize(UINT nType, int cx, int cy)
{
    CDC memDC;
    memDC.CreateCompatibleDC(NULL);
    RegenerateDocument(&memDC);
    CWnd::OnSize(nType, cx, cy);
}

void CBufferCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar)
{
    if ((GetStyle() & WS_VSCROLL) == 0)
        return;

    // Get the minimum and maximum scroll-bar positions.
    int minpos;
    int maxpos;
    GetScrollRange(SB_VERT, &minpos, &maxpos);
    maxpos = GetScrollLimit(SB_VERT);

    // Get the current position of scroll box.
    int curpos = GetScrollPos(SB_VERT);
    int iOldPos = curpos;

    // Determine the new position of scroll box.
    switch (nSBCode)
    {
    case SB_LEFT:      // Scroll to far left.
        curpos = minpos;
        break;

    case SB_RIGHT:      // Scroll to far right.
        curpos = maxpos;
        break;

    case SB_ENDSCROLL:   // End scroll.
        break;

    case SB_LINELEFT:      // Scroll left.
        if (curpos > minpos)
            curpos--;
        break;

    case SB_LINERIGHT:   // Scroll right.
        if (curpos < maxpos)
            curpos++;
        break;

    case SB_PAGELEFT:    // Scroll one page left.
    {
        // Get the page size. 
        SCROLLINFO info;
        GetScrollInfo(SB_VERT, &info, SIF_ALL);

        if (curpos > minpos)
            curpos = max(minpos, curpos - (int)info.nPage);
        break;
    }

    case SB_PAGERIGHT:      // Scroll one page right.
    {
        // Get the page size. 
        SCROLLINFO info;
        GetScrollInfo(SB_VERT, &info, SIF_ALL);

        if (curpos < maxpos)
            curpos = min(maxpos, curpos + (int)info.nPage);
        break;
    }

    case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
        curpos = nPos;      // of the scroll box at the end of the drag operation.
        break;

    case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
        curpos = nPos;     // position that the scroll box has been dragged to.
        break;
    }

    int iScrolled = iOldPos - curpos;

    if (iScrolled != 0)
    {
        CRect rcClient;
        GetClientRect(&rcClient);
        
        ScrollWindowEx(0, m_lineHeight * iScrolled, rcClient, NULL, NULL, NULL, SW_SMOOTHSCROLL | SW_ERASE);

        m_follow = (curpos == maxpos);

        Invalidate(FALSE);
        UpdateWindow();
    }

    SetScrollPos(SB_VERT, curpos);
    CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CBufferCtrl::OnNcDestroy()
{
    delete this;
}

void CBufferCtrl::RegenerateDocument(CDC* pDC)
{
    CRect clientRect = {0,0,GetDeviceCaps(*pDC, HORZRES),GetDeviceCaps(*pDC, VERTRES)};
    if (::IsWindow(m_hWnd))
    {
        GetClientRect(&clientRect);

        m_document.elements.RemoveAll();
        m_document.dimensions.SetRectEmpty();

        POSITION pos = m_lines.GetHeadPosition();
        const int count = m_lines.GetSize();
        int i = 0;
        while (pos != NULL)
        {
            const CBufferLine& line = m_lines.GetNext(pos);
            TRACE(_T("REGENERATING %d/%d\n"), ++i, count);

            AppendDocument(pDC, line);
        }

        int documentLines = m_document.dimensions.Height() / m_lineHeight;
        SCROLLINFO siv;
        siv.cbSize = sizeof(SCROLLINFO);
        GetScrollInfo(SB_VERT, &siv);
        siv.nMin = 0;
        siv.nMax = documentLines - 1;
        siv.nPage = clientRect.Height() / m_lineHeight;
        SetScrollInfo(SB_VERT, &siv);
    }
}

void CBufferCtrl::AppendDocument(CDC* pDC, const CBufferLine& line)
{
    CRect clientRect = {0,0,GetDeviceCaps(*pDC, HORZRES),GetDeviceCaps(*pDC, VERTRES)};
    if (::IsWindow(m_hWnd))
    {
        GetClientRect(&clientRect);

        CRect timeRect(
            m_margin,
            m_document.dimensions.bottom,
            m_margin + m_timeWidth,
            m_document.dimensions.bottom + m_lineHeight);
        TextElement* timeElement = new TextElement(line.date.Format(m_timeFormat), timeRect, true);
        TRACE(_T("STRING '%s' AT (%d,%d,%d,%d)\n"), timeElement->text.GetPlain(),
            timeElement->rect.left,
            timeElement->rect.top,
            timeElement->rect.right,
            timeElement->rect.bottom);
        m_document.elements.AddTail(std::shared_ptr<TextElement>(timeElement));

        CRect prefixRect(
            m_margin + m_timeWidth + m_margin,
            m_document.dimensions.bottom,
            m_margin + m_timeWidth + m_margin + m_prefixWidth,
            m_document.dimensions.bottom + m_lineHeight);
        TextElement* prefixElement = new TextElement(line.prefix.GetRaw(), prefixRect, true);
        TRACE(_T("STRING '%s' AT (%d,%d,%d,%d)\n"), prefixElement->text.GetPlain(),
            prefixElement->rect.left,
            prefixElement->rect.top,
            prefixElement->rect.right,
            prefixElement->rect.bottom);
        m_document.elements.AddTail(std::shared_ptr<TextElement>(prefixElement));

        CRect messageRect(
            m_margin + m_timeWidth + m_margin + m_prefixWidth + m_margin,
            m_document.dimensions.bottom,
            clientRect.right - m_margin,
            m_document.dimensions.bottom + m_lineHeight);
        TextElement* messageElement = new TextElement(line.message.GetRaw(), messageRect, false);
        messageElement->rect = messageElement->draw(pDC, true);
        TRACE(_T("STRING '%s' AT (%d,%d,%d,%d)\n"), messageElement->text.GetPlain(),
            messageElement->rect.left,
            messageElement->rect.top,
            messageElement->rect.right,
            messageElement->rect.bottom);
        m_document.elements.AddTail(std::shared_ptr<TextElement>(messageElement));
        m_document.dimensions |= messageElement->rect;
    }
}

void CBufferCtrl::RedrawVisibleElements(CDC* pDC)
{
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);

    CRect rcClient;
    GetClientRect(&rcClient);

    CBitmap bitmap, *oldBitmap;
    bitmap.CreateCompatibleBitmap(pDC, rcClient.Width(), m_document.dimensions.Height());
    oldBitmap = memDC.SelectObject(&bitmap);

    int yOrigin;
    if (m_document.dimensions.Height() < rcClient.Height())
    {
        yOrigin = m_document.dimensions.Height() - rcClient.Height();
    }
    else
    {
        SCROLLINFO siv;
        siv.cbSize = sizeof(siv);
        GetScrollInfo(SB_VERT, &siv);
        int pageStart = GetScrollPos(SB_VERT);
        int pageEnd = pageStart + siv.nPage;
        yOrigin = pageStart * m_lineHeight;
        rcClient.OffsetRect(0, yOrigin);
    }

    memDC.FillSolidRect(rcClient, GetSysColor(COLOR_WINDOW));

    POSITION pos = m_document.elements.GetHeadPosition();
    while (pos != NULL)
    {
        DisplayElement& element = *m_document.elements.GetNext(pos);
        if (!(rcClient & element.rect).IsRectEmpty())
            element.draw(&memDC);
    }

    pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &memDC, 0, yOrigin, SRCCOPY);

    memDC.SelectObject(oldBitmap);
}

BOOL CBufferCtrl::RegisterWndClass()
{
    WNDCLASS windowclass;
    HINSTANCE hInst = AfxGetInstanceHandle();

    //Check weather the class is registerd already
    if (!(::GetClassInfo(hInst, wndClassName, &windowclass)))
    {
        //If not then we have to register the new class
        windowclass.style = CS_DBLCLKS;// | CS_HREDRAW | CS_VREDRAW;
        windowclass.lpfnWndProc = CBufferCtrl::WndProc;
        windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
        windowclass.hInstance = hInst;
        windowclass.hIcon = NULL;
        windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
        windowclass.lpszMenuName = NULL;
        windowclass.lpszClassName = wndClassName;

        if (!AfxRegisterClass(&windowclass))
        {
            AfxThrowResourceException();
            return FALSE;
        }
    }

    return TRUE;
}

DisplayElement::DisplayElement(const CRect rect)
    : rect(rect)
{
}

TextElement::TextElement(const CString text, const CRect rect, bool singleLine)
    : text(text), DisplayElement(rect)
{
    if (singleLine)
    {
        dwDTFormat = DT_END_ELLIPSIS | DT_SINGLELINE | DT_NOPREFIX;
    }
    else
    {
        dwDTFormat = DT_WORDBREAK | DT_NOPREFIX;
    }
}

CRect TextElement::draw(CDC* pDC, bool calcRect)
{
    struct SubElementInfo
    {
        CString text;
        CRect rect;
        // Styles
    };

    DRAWTEXTPARAMS dtp;
    dtp.cbSize = sizeof(dtp);
    dtp.iLeftMargin = 0;
    dtp.iRightMargin = 0;
    dtp.iTabLength = 4;
    dtp.uiLengthDrawn = 0;

    CList<SubElementInfo> subElements;
    CPoint origin = { 0, 0 };
    for (const auto& match : text)
    {
        CString szLine(match.str().c_str());
        switch (szLine[0])
        {
        case '\x19':
            break;
        case '\x1A':
            break;
        case '\x1B':
            break;
        case '\x1C':
            break;
        default:
        {
            wrap:
            int chcount = szLine.GetLength();
            int lineCharCount = 0;
            int* arr = new int[chcount];
            SIZE size = { 0, 0 };
            BOOL ret = GetTextExtentExPoint(*pDC, szLine, chcount, rect.Width() - origin.x, &lineCharCount, arr, &size);
            ASSERT(ret);

            if (lineCharCount < chcount)
            {
                CString substr = szLine.Left(lineCharCount);
                CString rest = szLine.Right(chcount - lineCharCount);
                int breakIdx = substr.ReverseFind(_T(' '));
                if (breakIdx < 0)
                { // No available break point - use full substring
                    SIZE extent = { arr[lineCharCount - 1], size.cy };
                    CRect displayRect = { origin, origin + extent };
                    SubElementInfo info = { substr, displayRect };
                    subElements.AddTail(info);
                }
                else
                {
                    substr = szLine.Left(breakIdx);
                    rest = szLine.Right(chcount - breakIdx);
                    rest.TrimLeft();
                    if (substr.IsEmpty())
                    {
                        szLine = rest;
                        delete[] arr;
                        goto wrap;
                    }
                    SIZE extent = { arr[breakIdx], size.cy };
                    CRect displayRect = { origin, origin + extent };
                    SubElementInfo info = { substr, displayRect };
                    subElements.AddTail(info);
                }
                origin.x = 0;
                origin.y += size.cy;
                if (!rest.IsEmpty())
                {
                    szLine = rest;
                    delete[] arr;
                    goto wrap;
                }
            }
            else
            {
                CRect displayRect = { origin, origin + size };
                SubElementInfo info = { szLine, displayRect };
                subElements.AddTail(info);
                origin.x += size.cx;
            }

            delete[] arr;
            break;
        }
        }
    }

    CRect fullRect = rect;
    POSITION pos = subElements.GetHeadPosition();
    while (pos != NULL)
    {
        const SubElementInfo info = subElements.GetNext(pos);
        CRect subRect = info.rect;
        subRect.OffsetRect(fullRect.left, fullRect.top);
        TRACE(_T("Drawing '%s' to (%d, %d, %d, %d)\n"), info.text, subRect.left, subRect.top, subRect.right, subRect.bottom);
        if (calcRect)
            pDC->DrawTextEx(info.text, &subRect, dwDTFormat | DT_CALCRECT, &dtp);
        else
            pDC->DrawTextEx(info.text, &subRect, dwDTFormat, &dtp);
        fullRect |= subRect;
    }
    return fullRect;
}
