
// WeechatView.cpp : implementation of the CWeechatView class
//

#include "stdafx.h"
#include <iostream>
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Main.h"
#endif

#include "WeechatDoc.h"
#include "WeechatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWeechatView

IMPLEMENT_DYNCREATE(CWeechatView, CFormView)

BEGIN_MESSAGE_MAP(CWeechatView, CFormView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CWeechatView construction/destruction

CWeechatView::CWeechatView()
	: CFormView(CWeechatView::IDD)
{
    m_szDesignTimeSize.SetSize(0, 0);
}

CWeechatView::~CWeechatView()
{
}

void CWeechatView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CWeechatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CWeechatView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

    BOOL bOk = m_resizer.Hook(this);
    ASSERT(bOk);

    bOk = m_resizer.SetAnchor(IDC_INPUT, ANCHOR_HORIZONTALLY | ANCHOR_BOTTOM);
    ASSERT(bOk);

    bOk = m_resizer.SetAnchor(IDC_NICKLIST, ANCHOR_RIGHT | ANCHOR_VERTICALLY);
    ASSERT(bOk);

    bOk = m_resizer.SetAnchor(IDC_BUFFER, ANCHOR_ALL);
    ASSERT(bOk);
    
    bOk = m_resizer.SetAnchor(IDC_BUFLIST, ANCHOR_LEFT | ANCHOR_VERTICALLY);
    ASSERT(bOk);
    
    bOk = m_resizer.SetAnchor(IDC_TOPIC, ANCHOR_HORIZONTALLY | ANCHOR_TOP);
    ASSERT(bOk);

    bOk = m_resizer.InvokeOnResized();
    ASSERT(bOk);

    CString sDebug = m_resizer.GetDebugInfo();
    OutputDebugString(sDebug);
}


// CWeechatView printing

BOOL CWeechatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWeechatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWeechatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CWeechatView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

int CWeechatView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFormView::OnCreate(lpCreateStruct) == -1)
        return -1;

    m_szDesignTimeSize.SetSize(lpCreateStruct->cx, lpCreateStruct->cy);

    return 0;
}


// CWeechatView diagnostics

#ifdef _DEBUG
void CWeechatView::AssertValid() const
{
	CFormView::AssertValid();
}

void CWeechatView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CWeechatDoc* CWeechatView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWeechatDoc)));
	return (CWeechatDoc*)m_pDocument;
}
#endif //_DEBUG


// CWeechatView message handlers
