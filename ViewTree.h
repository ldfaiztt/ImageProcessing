#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewTree 窗口
#include <memory>
#include "ChildFrm.h"
#include "TransImage.h"

using namespace std;

struct stTreeItemInfo
{
	CChildFrame * frame;
	typeImgPtr img;
	bool NeedToUpdate;
	Transitions tsType;
	CString strType;

	stTreeItemInfo()
	{
		frame = NULL;
		img.reset();
		tsType = Transitions::none;
		NeedToUpdate = true;
		strType = _T("");
	}

	stTreeItemInfo(CChildFrame * f, typeImgPtr i, Transitions t, bool ntu = true)
	{
		frame = f;
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

		case Transitions::smoothing:
			strType = _T("smoothing");
			break;

		case Transitions::median:
			strType = _T("median");
			break;

		case Transitions::sharpening_laplacian:
			strType = _T("sharpening_laplacian");
			break;

		case Transitions::high_boosting:
			strType = _T("high_boosting");
			break;

		case Transitions::bit_slicing:
			strType = _T("bit_slicing");
			break;

		case Transitions::max:
			strType = _T("max");
			break;

		case Transitions::min:
			strType = _T("min");
			break;

		case Transitions::midpoint:
			strType = _T("midpoint");
			break;

		case Transitions::arithmetic:
			strType = _T("arithmetic");
			break;

		case Transitions::geometic:
			strType = _T("geometic");
			break;

		case Transitions::harmonic:
			strType = _T("harmonic");
			break;

		case Transitions::contraharmonic:
			strType = _T("contraharmonic");
			break;

		case Transitions::alpha_trimmed:
			strType = _T("alpha_trimmed");
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
	void ClearShowFrame(CViewTree & tree, HTREEITEM hItem, CObject * target);
	typeImgPtr getImg(CViewTree & tree, HTREEITEM hItem, Transitions target);
	void TreeVisitForChildFrame(CViewTree & tree, HTREEITEM hItem, CObject * target);
	typeImgPtr TreeVisitForImg(CViewTree & tree, HTREEITEM hItem, Transitions target);
public:
	const DWORD_PTR getCurItemInfo(void);
	const DWORD_PTR getParentItemInfo(void);
	void OnCloseChildFrame(CObject * target);
	typeImgPtr getImgOfSpecialTypeItem(Transitions target);
};
