#include "stdafx.h"
#include "ViewTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
//	ON_WM_LBUTTONDBLCLK()
//	ON_WM_CONTEXTMENU()
//	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CViewTree::OnTvnSelchanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 消息处理程序

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

const DWORD_PTR CViewTree::getCurItemInfo(void)
{
	HTREEITEM curItem = GetSelectedItem();
	if (curItem == NULL)
	{
		return NULL;
	}

	DWORD_PTR curData = GetItemData(curItem);

	return curData;
}

const DWORD_PTR CViewTree::getParentItemInfo(void)
{
	HTREEITEM curItem = GetSelectedItem();
	if (curItem == NULL)
	{
		return NULL;
	}

	HTREEITEM parent = GetParentItem(curItem);
	if (parent == NULL)
	{
		return NULL;
	}

	DWORD_PTR data = GetItemData(parent);

	return data;
}

//void CViewTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	*pResult = 0;
//}
