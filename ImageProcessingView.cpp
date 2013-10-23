
// ImageProcessingView.cpp : implementation of the MyImageProcessingView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#include <memory>
#include "ChildFrm.h"

// MyImageProcessingView

IMPLEMENT_DYNCREATE(MyImageProcessingView, CView)

BEGIN_MESSAGE_MAP(MyImageProcessingView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &MyImageProcessingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// MyImageProcessingView construction/destruction

MyImageProcessingView::MyImageProcessingView()
{
	// TODO: add construction code here

}

MyImageProcessingView::~MyImageProcessingView()
{
}

BOOL MyImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//SetScrollSizes(MM_LOENGLISH, CSize(2000, 2000));
	return CView::PreCreateWindow(cs);
}

// MyImageProcessingView drawing

void MyImageProcessingView::OnDraw(CDC* pDC)
{
	using namespace std;
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CChildFrame * cframe = (CChildFrame *)GetParentFrame();
	if (cframe->showImg() != NULL && !cframe->showImg()->IsNull())
	{
		cframe->showImg()->Draw(pDC->m_hDC, 0, 0);
	}
}


// MyImageProcessingView printing


void MyImageProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL MyImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void MyImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void MyImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void MyImageProcessingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void MyImageProcessingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// MyImageProcessingView diagnostics

#ifdef _DEBUG
void MyImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void MyImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingDoc* MyImageProcessingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// MyImageProcessingView message handlers
