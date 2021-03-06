
// ChildFrm.cpp : implementation of the CChildFrame class
//
#include "stdafx.h"
#include "ImageProcessing.h"

#include "ChildFrm.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()

// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	drwt = drawType::drawImg;
}

CChildFrame::~CChildFrame()
{

}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	cs.style &= ~(LONG)FWS_ADDTOTITLE;

	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

shared_ptr<MyImage> CChildFrame::showImg()
{
	if (img)
	{
		return img;
	}
	
	return ((CMainFrame *)AfxGetMainWnd())->getSelectedImg();
}

void CChildFrame::setImg(shared_ptr<MyImage> val)
{
	img = val;
}

// CChildFrame message handlers
void CChildFrame::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	((CMainFrame *)AfxGetMainWnd())->RefreshClassView(this);

	CMDIChildWndEx::OnClose();
}

drawType CChildFrame::getDrawType()
{
	return drwt;
}

void CChildFrame::setDrawType(drawType dt)
{
	drwt = dt;
}
