#pragma once

#include "ImageProcessingDoc.h"

class CGrayingView : public CView
{
public: // create from serialization only
	CGrayingView();
	DECLARE_DYNCREATE(CGrayingView)

	// Attributes
public:
	CImageProcessingDoc* GetDocument() const;

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
	virtual ~CGrayingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
public:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImageProcessingView.cpp
inline CImageProcessingDoc* CGrayingView::GetDocument() const
{
	return reinterpret_cast<CImageProcessingDoc*>(m_pDocument);
}
#endif

