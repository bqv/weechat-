
// WeechatView.h : interface of the CWeechatView class
//

#pragma once


class CWeechatView : public CView
{
protected: // create from serialization only
	CWeechatView();
	DECLARE_DYNCREATE(CWeechatView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_TEST_FORM };
#endif

// Attributes
public:
	CWeechatDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CWeechatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    afx_msg void OnFilePrintPreview();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WeechatView.cpp
inline CWeechatDoc* CWeechatView::GetDocument() const
   { return reinterpret_cast<CWeechatDoc*>(m_pDocument); }
#endif

