
// WeechatView.cpp : implementation of the CWeechatView class
//

#include "stdafx.h"
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

IMPLEMENT_DYNCREATE(CWeechatView, CView)

BEGIN_MESSAGE_MAP(CWeechatView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWeechatView::OnFilePrintPreview)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CWeechatView construction/destruction

CWeechatView::CWeechatView()
{
    // TODO: add construction code here

}

CWeechatView::~CWeechatView()
{
}

BOOL CWeechatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View drawing

void CWeechatView::OnDraw(CDC* /*pDC*/)
{
    CWeechatDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: add draw code for native data here
}


// CWeechatView printing


void CWeechatView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
    AFXPrintPreview(this);
#endif
}

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

void CWeechatView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CWeechatView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CWeechatView diagnostics

#ifdef _DEBUG
void CWeechatView::AssertValid() const
{
	CView::AssertValid();
}

void CWeechatView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWeechatDoc* CWeechatView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWeechatDoc)));
	return (CWeechatDoc*)m_pDocument;
}
#endif //_DEBUG


// CWeechatView message handlers
