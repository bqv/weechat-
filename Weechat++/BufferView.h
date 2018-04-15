#pragma once

class CBufferViewToolBar : public CMFCToolBar
{
    virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
    {
        CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
    }

    virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CBufferView : public CDockablePane
{
	DECLARE_DYNAMIC(CBufferView)

public:
	CBufferView();

    void AdjustLayout();

// Attributes
protected:

    CListBox m_wndBufferView;
    CBufferViewToolBar m_wndToolBar;

// Implementation
public:
	virtual ~CBufferView();

protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	DECLARE_MESSAGE_MAP()
};


