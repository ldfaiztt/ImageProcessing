
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

// MyImageProcessingView

IMPLEMENT_DYNCREATE(CImageProcessingView, CView)

BEGIN_MESSAGE_MAP(CImageProcessingView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageProcessingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// MyImageProcessingView construction/destruction

CImageProcessingView::CImageProcessingView()
{
	// TODO: add construction code here

}

CImageProcessingView::~CImageProcessingView()
{
}

BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//SetScrollSizes(MM_LOENGLISH, CSize(2000, 2000));
	return CView::PreCreateWindow(cs);
}

// MyImageProcessingView drawing

void CImageProcessingView::OnDraw(CDC* pDC)
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CChildFrame * cframe = (CChildFrame *)GetParentFrame();
	typeImgPtr img = cframe->showImg();
	if (img != NULL && !img->IsNull())
	{
		switch (cframe->getDrawType())
		{
		case drawType::drawImg:
			DrawImg(pDC, img);
			break;

		case drawType::drawHistogram:
			DrawHistogram(pDC, cframe->maps,cframe->statistic_max, cframe->scale_max);
			break;

		default:
			DrawImg(pDC, img);
			break;
		}
	}
}

void CImageProcessingView::DrawImg(CDC * pDC, typeImgPtr img)
{
	img->Draw(pDC->m_hDC, 0, 0);
}

void CImageProcessingView::DrawHistogram(CDC* pDC, std::vector<std::shared_ptr<type_statistic_map>> & maps, int max_num, int max_val)
{
	using namespace std;

	CRect rect;
	GetWindowRect(&rect);

	//创建黑色画笔用于绘制坐标
	CPen* pPenblack = new CPen;
	pPenblack->CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pPengary = new CPen;
	pPengary->CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	CGdiObject* pOldPen = pDC->SelectObject(pPenblack);

	CPoint LeftBottom(10, rect.Height() - 20);
	CPoint LeftTop(10, 10);
	CPoint RightBottom(rect.Width() - 20, rect.Height() - 20);
	CPoint RightTop(rect.Width() - 20, 10);
	int width = RightBottom.x - LeftBottom.x;
	int height = LeftBottom.y - LeftTop.y;
	int ZeroX = LeftBottom.x + 5;
	//绘制坐标轴
	pDC->MoveTo(LeftBottom); //绘图区左下角定义的原点。
	pDC->LineTo(LeftTop);    //绘制y轴
	pDC->MoveTo(LeftBottom);
	pDC->LineTo(RightBottom);//绘制x轴
	//绘制y轴箭头
	pDC->MoveTo(LeftTop);
	pDC->LineTo(LeftTop.x - 6, LeftTop.y + 6);
	pDC->MoveTo(LeftTop);
	pDC->LineTo(LeftTop.x + 6, LeftTop.y + 6);
	//绘制x轴箭头
	pDC->MoveTo(RightBottom);
	pDC->LineTo(RightBottom.x - 6, RightBottom.y + 6);
	pDC->MoveTo(RightBottom);
	pDC->LineTo(RightBottom.x - 6, RightBottom.y - 6);
	
	CString str;

	//x坐标
	int x_num = 4 < max_val ? 4 : max_val;

	pDC->TextOut(ZeroX - 8, LeftBottom.y + 4, L"0");
	pDC->MoveTo(ZeroX, LeftBottom.y);
	pDC->LineTo(ZeroX, LeftBottom.y + 4);

	for (int i = 1; i <= x_num; i++)
	{
		int m = width * i / x_num;
		int n = max_val * i / x_num;
		str.Format(L"%d", n);
		pDC->TextOut(ZeroX + m - 8, LeftBottom.y + 4, str);
		pDC->MoveTo(ZeroX + m, LeftBottom.y);
		pDC->LineTo(ZeroX + m, LeftBottom.y + 4);
	}

	//y坐标
	pDC->SelectObject(pPengary);
	int y_num = 5;
	for (int j = 1; j <= y_num; j++)
	{
		int m = height * j / y_num;
		int n = max_num * j/ y_num;
		str.Format(L"%d", n);
		pDC->TextOut(LeftBottom.x + 2, LeftBottom.y - m, str);
		pDC->MoveTo(LeftBottom.x, LeftBottom.y - m);
		pDC->LineTo(RightBottom.x, LeftBottom.y - m);
	}
	pDC->SelectObject(pOldPen);
	delete pPenblack;
	delete pPengary;

	COLORREF color[6] = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(255, 255, 0), RGB(255, 0, 255), RGB(0, 255, 255) };
	int count = 0;
	for each (shared_ptr<type_statistic_map> map in maps)
	{
		CPen* pPenblue = new CPen;
		pPenblue->CreatePen(PS_SOLID, 1, color[count++ % 6]);
		CGdiObject* pOldPen2 = pDC->SelectObject(pPenblue);

		for (int k = 0; k < max_val; k++)
		{
			int a = width * k / max_val;
			int m_count = 0;
			type_statistic_map::iterator it = map->find(k);
			if (it != map->end())
			{
				m_count = it->second;
			}
			else
			{
				m_count = 0;
			}
			int b = height * m_count / max_num;
			pDC->MoveTo(ZeroX + a, LeftBottom.y);
			pDC->LineTo(ZeroX + a, LeftBottom.y - b);
		}
		pDC->SelectObject(pOldPen2);
		delete pPenblue;
	}
}


// MyImageProcessingView printing


void CImageProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CImageProcessingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageProcessingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// MyImageProcessingView diagnostics

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// MyImageProcessingView message handlers


void CImageProcessingView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText(L"Original");
}
