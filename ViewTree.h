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
	typeImgPtr img;
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

	stTreeItemInfo(CChildFrame * f, typeImgPtr i, Transitions t, bool ntu = true)
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

		case Transitions::replication:
			strType = _T("replication");
			break;

		case Transitions::nearest_neighbor:
			strType = _T("nearest_neighbor");
			break;

		case Transitions::bilinear_interpolation:
			strType = _T("bilinear_interpolation");
			break;

		case Transitions::gray_level:
			strType = _T("gray_level");
			break;

		case Transitions::pow_scale:
			strType = _T("pow_scale");
			break;

		case Transitions::log_scale:
			strType = _T("log_scale");
			break;

		case Transitions::histogram_eq:
			strType = _T("histogram_eq");
			break;

		case Transitions::histogram_match:
			strType = _T("histogram_match");
			break;

		case Transitions::histogram_local:
			strType = _T("histogram_local");
			break;

		default:
			strType = _T("processing_img");
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
