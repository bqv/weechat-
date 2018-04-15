// BufferView.cpp : implementation file
//

#include "stdafx.h"
#include "BufferView.h"
#include "Main.h"

// CBufferView

IMPLEMENT_DYNAMIC(CBufferView, CDockablePane)

CBufferView::CBufferView()
{

}

CBufferView::~CBufferView()
{
}


BEGIN_MESSAGE_MAP(CBufferView, CDockablePane)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()



// CBufferView message handlers

int CBufferView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDockablePane::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rectDummy;
    rectDummy.SetRectEmpty();

    // Create view:
    const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE;

    if (!m_wndBufferView.Create(dwViewStyle, rectDummy, this, 4))
    {
        TRACE0("Failed to create file view\n");
        return -1;      // fail to create
    }

    m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_MENU_IMAGES);
    m_wndToolBar.LoadToolBar(IDR_MENU_IMAGES, 0, 0, TRUE /* Is locked */);

    m_wndToolBar.CleanUpLockedImages();
    m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : IDR_MENU_IMAGES, 0, 0, TRUE /* Locked */);

    m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

    m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

    m_wndToolBar.SetOwner(this);

    // All commands will be routed via this control , not via the parent frame:
    m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

    ///
    m_wndBufferView.AddString(_T("weechat"));
    m_wndBufferView.AddString(_T("server.freenode"));
    m_wndBufferView.AddString(_T("freenode.#example1"));
    m_wndBufferView.AddString(_T("freenode.#example2"));
    m_wndBufferView.AddString(_T("freenode.#example3"));
    ///
    AdjustLayout();

    return 0;
}

void CBufferView::OnSize(UINT nType, int cx, int cy)
{
    CDockablePane::OnSize(nType, cx, cy);
    AdjustLayout();
}

void CBufferView::OnContextMenu(CWnd* pWnd, CPoint point)
{
    CListCtrl* pWndList = (CListCtrl*)&m_wndBufferView;
    ASSERT_VALID(pWndList);

    if (pWnd != pWndList)
    {
        CDockablePane::OnContextMenu(pWnd, point);
        return;
    }

    if (point != CPoint(-1, -1))
    {
        // Select clicked item:
        CPoint ptList = point;
        pWndList->ScreenToClient(&ptList);

        UINT flags = 0;
        int hListItem = pWndList->HitTest(ptList, &flags);
        if (hListItem != -1)
        {
            pWndList->SetHotItem(hListItem);
        }
    }

    pWndList->SetFocus();
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

void CBufferView::AdjustLayout()
{
    if (GetSafeHwnd() == nullptr)
    {
        return;
    }

    CRect rectClient;
    GetClientRect(rectClient);

    int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

    m_wndToolBar.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
    m_wndBufferView.SetWindowPos(nullptr, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}




