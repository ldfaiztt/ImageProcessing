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

void CViewTree::ClearShowFrame(CViewTree & tree, HTREEITEM hItem, CChildFrame * target)
{
	stTreeItemInfo * item = (stTreeItemInfo *)tree.GetItemData(hItem);

	if (item->frame == target)
	{
		item->frame = NULL;
	}
}

void CViewTree::ClearShowPtr( CChildFrame * target)
{
	HTREEITEM hRoot = GetRootItem();
	while (hRoot)
	{
		TreeVisit(*this, hRoot, target);
		hRoot = GetNextItem(hRoot, TVGN_NEXT);
	}
}

void CViewTree::TreeVisit(CViewTree & tree, HTREEITEM hItem, CChildFrame * target)
{
	ClearShowFrame(tree, hItem, target);
	if (tree.ItemHasChildren(hItem))
	{
		HTREEITEM hChildItem = tree.GetChildItem(hItem);
		while (hChildItem != NULL)
		{
			TreeVisit(tree, hChildItem, target);
			hChildItem = tree.GetNextItem(hChildItem, TVGN_NEXT);
		}
	}
}
