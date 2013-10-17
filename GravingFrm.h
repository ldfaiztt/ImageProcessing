// FaultFileFrm.h : CFaultFileFrame 类的接口
//

#pragma once
#include "GravingView.h"

class CGrayingFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CGrayingFrame)
public:
	CGrayingFrame();

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual ~CGrayingFrame();

public:
	CGrayingView m_wndView;
	CImage img;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成的消息映射函数
protected:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnFileClose();
	//afx_msg void OnRefresh();
	afx_msg void OnUpdateRefresh(CCmdUI * pCmdUI);
	DECLARE_MESSAGE_MAP()
public:
	//void RefreshFaultFileList(int stationIndex, int devIndex);
	void AdjustLayout(void);

	void OnOpenLocalMenu(void);
};
