#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewTree 窗口
#include <memory>
#include "ChildFrm.h"
#include "TransImage.h"

using namespace std;

struct stTreeItemInfo
{
	shared_ptr<CChildFrame> frame;
	shared_ptr<CImage> img;
	bool NeedToUpdate;
	Transitions tsType;
	CString strType;

	stTreeItemInfo()
	{
		frame.reset();
		img.reset();
		tsType = Transitions::none;
		NeedToUpdate = true;
		strType = _T("");
	}

	stTreeItemInfo(CChildFrame * f, shared_ptr<CImage> i, Transitions t, bool ntu = true)
	{
		frame = shared_ptr<CChildFrame>(f);
		img = i;
		tsType = t;
		NeedToUpdate = ntu;

		switch (tsType)
		{
		case Transitions::graying:
			strType = _T("graying");
			break;

		case Transitions::subsampling:
			strType = _T("subsampling");
			break;

		default:
			strType = _T("");
			break;
		}
	}
};

class CViewTree : public CTreeCtrl
{
// 构造
public:
	CViewTree();

// 重写
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// 实现
public:
	virtual ~CViewTree();

protected:
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	const DWORD_PTR getCurItemInfo(void);
	const DWORD_PTR getParentItemInfo(void);
	//afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};
