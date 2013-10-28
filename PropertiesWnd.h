
#pragma once
#include "MyImage.h"
#include <unordered_map>

typedef std::basic_string<TCHAR> tstring;

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
// Construction
public:
	CPropertiesWnd();

	void AdjustLayout();

// Attributes
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;

	CMFCPropertyGridProperty* pHeight;
	CMFCPropertyGridProperty* pWidth;
	CMFCPropertyGridProperty* pMaskSize;
	CMFCPropertyGridProperty* pMaskType;
	CMFCPropertyGridProperty* pLaplacianType;
	CMFCPropertyGridProperty* pBitSize;
	CMFCPropertyGridProperty* pBitMask;
	CMFCPropertyGridProperty* pC;
	CMFCPropertyGridProperty* pY;
	CMFCPropertyGridProperty* pA;
	CMFCPropertyGridProperty* pPath;

	std::unordered_map<tstring, maskType> maskType_map;

// Implementation
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnPropertiesHistogram();
	afx_msg void OnUpdatePropertiesHistogram(CCmdUI* pCmdUI);
	afx_msg void OnPropertiesFlash();
	afx_msg void OnUpdatePropertiesFlash(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();

	int m_nComboHeight;
};

