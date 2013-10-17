
// ImageProcessingView.cpp : implementation of the CImageProcessingView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "GravingView.h"
#include "GravingFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#include <memory>
#include "ChildFrm.h"

// CImageProcessingView

IMPLEMENT_DYNCREATE(CGrayingView, CView)

BEGIN_MESSAGE_MAP(CGrayingView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGrayingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CImageProcessingView construction/destruction

CGrayingView::CGrayingView()
{
	// TODO: add construction code here

}

CGrayingView::~CGrayingView()
{
}

BOOL CGrayingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//SetScrollSizes(MM_LOENGLISH, CSize(2000, 2000));
	return CView::PreCreateWindow(cs);
}

// CImageProcessingView drawing

void CGrayingView::OnDraw(CDC* pDC)
{
	// TODO: add draw code for native data here
	//if (!pDoc->img.IsNull()) pDoc->img.Draw(pDC->m_hDC, 0, 0);

	CGrayingFrame * gframe = (CGrayingFrame * )GetParentFrame();
	if (!((gframe->img).IsNull()))
	{
		(gframe->img).BitBlt(pDC->m_hDC, 0, 0);
	}
}


// CImageProcessingView printing


void CGrayingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGrayingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGrayingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGrayingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CGrayingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGrayingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageProcessingView diagnostics

#ifdef _DEBUG
void CGrayingView::AssertValid() const
{
	CView::AssertValid();
}

void CGrayingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingDoc* CGrayingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingView message handlers
