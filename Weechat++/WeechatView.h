
// WeechatView.h : interface of the CWeechatView class
//

#pragma once

#include "WndResizer.h"


class CWeechatView : public CFormView
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
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

// Implementation
public:
    enum { IDD = IDD_WEECHAT_FORM };
	virtual ~CWeechatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
private:
    CWndResizer m_resizer;
    CSize m_szDesignTimeSize;

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WeechatView.cpp
inline CWeechatDoc* CWeechatView::GetDocument() const
   { return reinterpret_cast<CWeechatDoc*>(m_pDocument); }
#endif

