// BufferView.cpp : implementation file
//

#include "stdafx.h"
#include "BufferView.h"
#include "Main.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "CodePoint.h"

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
    ON_MESSAGE(WM_UPDATE_BUFFERS, &CBufferView::OnUpdateBuffers)
    ON_NOTIFY(NM_RCLICK, IDC_BUFFER_TREE, &CBufferView::OnRclickTree)
    ON_NOTIFY(NM_CLICK, IDC_BUFFER_TREE, &CBufferView::OnClickTree)
    ON_NOTIFY(NM_DBLCLK, IDC_BUFFER_TREE, &CBufferView::OnDblclkTree)
END_MESSAGE_MAP()

// CBufferView message handlers

int CBufferView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDockablePane::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rectDummy;
    rectDummy.SetRectEmpty();

    // Create view:
    const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

    if (!m_wndBufferView.Create(dwViewStyle, rectDummy, this, IDC_BUFFER_TREE))
    {
        TRACE0("Failed to create buffer view\n");
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
    ASSERT_VALID(&m_wndBufferView);

    if (pWnd != &m_wndBufferView)
    {
        CDockablePane::OnContextMenu(pWnd, point);
        return;
    }

    if (point != CPoint(-1, -1))
    {
        // Select clicked item:
        CPoint ptTree = point;
        m_wndBufferView.ScreenToClient(&ptTree);

        UINT flags = 0;
        HTREEITEM hTreeItem = m_wndBufferView.HitTest(ptTree, &flags);
        if (hTreeItem != nullptr)
        {
            m_wndBufferView.SelectItem(hTreeItem);
        }
    }

    m_wndBufferView.SetFocus();
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

LRESULT CBufferView::OnUpdateBuffers(WPARAM wp, LPARAM lp)
{
    switch (wp)
    {
    case 0:
    {
        CList<CWeechatBuffer>* newBuffers = reinterpret_cast<CList<CWeechatBuffer>*>(lp);
        m_wndBufferView.DeleteAllItems();
        CMap<CString, LPCTSTR, HTREEITEM, HTREEITEM&> roots;
        POSITION pos = newBuffers->GetHeadPosition();
        while (pos != NULL)
        {
            CWeechatBuffer buffer = newBuffers->GetNext(pos);
            int i = 0;
            CList<CString> path;
            CString subpath = buffer.m_name.Tokenize(_T("."), i);
            path.AddTail(subpath);
            subpath = buffer.m_name.Tokenize(_T(""), i);
            if (!subpath.IsEmpty())
            {
                path.AddTail(subpath);
            }
            if (path.GetSize() == 1)
            {
                HTREEITEM item = m_wndBufferView.InsertItem(buffer.m_name, 0, 0);
                m_buffers.SetAt(item, buffer);
            }
            else if (path.GetSize() == 2)
            {
                POSITION pos = path.GetHeadPosition();
                CString pathHead = path.GetNext(pos);
                if (pathHead == "server")
                {
                    CString name = path.GetNext(pos);
                    if (!roots.PLookup(pathHead))
                    {
                        HTREEITEM root = m_wndBufferView.InsertItem(name, 1, 1);
                        m_buffers.SetAt(root, buffer);
                        roots.SetAt(name, root);
                    }
                }
                else
                {
                    HTREEITEM root;
                    if (roots.Lookup(pathHead, root))
                    {
                        HTREEITEM item = m_wndBufferView.InsertItem(path.GetNext(pos), 0, 0, root);
                        m_buffers.SetAt(item, buffer);
                        m_wndBufferView.Expand(root, TVE_EXPAND);
                    }
                    else
                    {
                        root = m_wndBufferView.InsertItem(pathHead, 1, 1);
                        roots.SetAt(pathHead, root);
                        HTREEITEM item = m_wndBufferView.InsertItem(path.GetNext(pos), 0, 0, root);
                        m_buffers.SetAt(item, buffer);
                        m_wndBufferView.Expand(root, TVE_EXPAND);
                    }
                }
            }
            else
            {
                AfxThrowInvalidArgException();
            }
        }
        m_wndBufferView.SendMessage(WM_VSCROLL, SB_TOP, 0);
        return LRESULT();
    }
    default:
        return LRESULT();
    }
}

void CBufferView::OnRclickTree(NMHDR * pNMHDR, LRESULT * pResult)
{
}

void CBufferView::OnClickTree(NMHDR * pNMHDR, LRESULT * pResult)
{
}

void CBufferView::OnDblclkTree(NMHDR * pNMHDR, LRESULT * pResult)
{
    HTREEITEM item = m_wndBufferView.GetSelectedItem();
    CMap<HTREEITEM, HTREEITEM, CWeechatBuffer, CWeechatBuffer&>::CPair* pair;
    if (item && (pair = m_buffers.PLookup(item)))
    {
        CWeechatBuffer* pBuffer = new CWeechatBuffer(pair->value);
        ASSERT_VALID(pBuffer);
        POSITION pos = theApp.GetFirstDocTemplatePosition();
        CDocTemplate* pT = theApp.GetNextDocTemplate(pos);
        CChildFrame* pFrame = (CChildFrame*)pT->CreateNewFrame(pBuffer, NULL);
        if (pFrame)
        {
            pBuffer->SetTitle(pBuffer->m_name);
            pFrame->SetWindowText(pBuffer->m_name);
            CStringA pointer = CSTOUTF8(pBuffer->m_pointer);
            CStringA var_last_line_range;
            var_last_line_range.Format(VAR_LAST_LINE"(-%d)", 200);
            ((CMainFrame*)theApp.m_pMainWnd)->m_relayHandler.hdatasync(HDATA_BUFFER, pointer.GetString(), { VAR_LINES, var_last_line_range.GetString(), VAR_DATA }, {}, { pointer.GetString() }, { /*SYNC_BUFFER, SYNC_NICKLIST*/ }, [=](Packet* p) {
                auto ProtocolAssert = [&](bool b) { return ((CMainFrame*)theApp.m_pMainWnd)->ProtocolAssert(b); };
                ProtocolAssert(p->objects.size() == 1);
                ProtocolAssert(std::visit(ID(), p->objects[0]) == hda_t::ID);
                hda_t hdata = std::get<hda_t>(p->objects[0]);
                ProtocolAssert(hdata.hpath == std::vector<std::string>({ HDATA_BUFFER, HPATH_LINES, HPATH_LINE, HPATH_LINE_DATA }));
                ProtocolAssert(hdata.keys.size() == 13);

                std::vector<std::pair<std::map<std::string, ptr_t>, std::map<std::string, obj_t>>> entries;
                for (const auto& entry : hdata.values)
                {
                    int i = 0;
                    std::map<std::string, ptr_t> entry_pointers;
                    ProtocolAssert(entry.first.size() == 4);
                    for (const auto& path : hdata.hpath)
                    {
                        entry_pointers.insert({ path,{ entry.first[i++] } });
                    }

                    int j = 0;
                    std::map<std::string, obj_t> entry_values;
                    ProtocolAssert(entry.second.size() == 13);
                    for (const auto& key : hdata.keys)
                    {
                        obj_t object = entry.second[j++];
                        const char *id = std::visit(ID(), object);
                        ProtocolAssert(id && key.second.compare(0, 3, id) == 0);
                        entry_values.insert({ key.first, object });
                    }

                    entries.push_back({ entry_pointers, entry_values });
                }

                CList<CBufferLine> lines;
                for (const auto& entry : entries)
                {
                    CBufferLine line;
                    try
                    {
                        ProtocolAssert(entry.first.at(HDATA_BUFFER).data.c_str() == pBuffer->m_pointer);
                        (void)entry.first.at(HPATH_LINES).data.c_str();
                        (void)entry.first.at(HPATH_LINE).data.c_str();
                        line.pointer = entry.first.at(HPATH_LINE_DATA).data.c_str();
                        (void)std::get<int_t>(entry.second.at(LINE_DATA_PREFIX_LENGTH)).data;
                        auto prefix = std::get<str_t>(entry.second.at(LINE_DATA_PREFIX)).data;
                        if (prefix)
                            line.prefix = UTF8TOCS(prefix.value().c_str());
                        line.displayed = std::get<chr_t>(entry.second.at(LINE_DATA_DISPLAYED)).data;
                        auto message = std::get<str_t>(entry.second.at(LINE_DATA_MESSAGE)).data;
                        if (message)
                            line.message = UTF8TOCS(message.value().c_str());
                        (void)std::get<chr_t>(entry.second.at(LINE_DATA_REFRESH_NEEDED)).data;
                        auto strTime = std::get<str_t>(entry.second.at(LINE_DATA_STR_TIME)).data;
                        if (strTime)
                            (void)UTF8TOCS(strTime.value().c_str());
                        line.date = std::get<tim_t>(entry.second.at(LINE_DATA_DATE)).data;
                        (void)std::get<int_t>(entry.second.at(LINE_DATA_TAGS_COUNT)).data;
                        line.datePrinted = std::get<tim_t>(entry.second.at(LINE_DATA_DATE_PRINTED)).data;
                        auto tagsArray = std::get<arr_t>(entry.second.at(LINE_DATA_TAGS_ARRAY)).values;
                        ProtocolAssert(strncmp(std::get<arr_t>(entry.second.at(LINE_DATA_TAGS_ARRAY)).type, str_t::ID, 3) == 0);
                        for (const auto& tag : tagsArray)
                            line.tagsArray.AddTail(UTF8TOCS(std::get<str_t>(tag).data.value().c_str()));
                        line.buffer = std::get<ptr_t>(entry.second.at(LINE_DATA_BUFFER)).data.c_str();
                        line.highlight = std::get<chr_t>(entry.second.at(LINE_DATA_HIGHLIGHT)).data;
                        (void)std::get<int_t>(entry.second.at(LINE_DATA_Y)).data;
                    }
                    catch (std::bad_variant_access&)
                    {
                        ProtocolAssert(false);
                    }
                    catch (std::out_of_range&)
                    {
                        ProtocolAssert(false);
                    }
                    lines.AddHead(line);
                }
                POSITION pos = pBuffer->GetFirstViewPosition();
                while (pos != NULL)
                {
                    CWeechatView* pView = (CWeechatView*)pBuffer->GetNextView(pos);
                    pView->SetLines(lines);
                    pView->UpdateWindow();
                }

                pT->AddDocument(pBuffer);
                pT->InitialUpdateFrame(pFrame, pBuffer, TRUE);
                pFrame->ShowWindow(SW_SHOW);
                pFrame->UpdateWindow();
            });
        }
    }
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
