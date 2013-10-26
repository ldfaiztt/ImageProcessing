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

void CViewTree::ClearShowFrame(CViewTree & tree, HTREEITEM hItem, CObject * target)
{
	stTreeItemInfo * item = (stTreeItemInfo *)tree.GetItemData(hItem);

	if (item->frame == target)
	{
		item->frame = NULL;
	}
}

typeImgPtr CViewTree::getImg(CViewTree & tree, HTREEITEM hItem, Transitions target)
{
	stTreeItemInfo * item = (stTreeItemInfo *)tree.GetItemData(hItem);

	if (item->tsType == target)
	{
		return item->img;
	}

	return NULL;
}

void CViewTree::OnCloseChildFrame( CObject * target)
{
	HTREEITEM hRoot = GetRootItem();
	while (hRoot)
	{
		TreeVisitForChildFrame(*this, hRoot, target);
		hRoot = GetNextItem(hRoot, TVGN_NEXT);
	}
}

typeImgPtr CViewTree::getImgOfSpecialTypeItem(Transitions target)
{
	HTREEITEM hRoot = GetRootItem();
	while (hRoot)
	{
		typeImgPtr ret = TreeVisitForImg(*this, hRoot, target);
		if (ret != NULL)
		{
			return ret;
		}
		hRoot = GetNextItem(hRoot, TVGN_NEXT);
	}

	return NULL;
}

void CViewTree::TreeVisitForChildFrame(CViewTree & tree, HTREEITEM hItem, CObject * target)
{
	ClearShowFrame(tree, hItem, target);
	if (tree.ItemHasChildren(hItem))
	{
		HTREEITEM hChildItem = tree.GetChildItem(hItem);
		while (hChildItem != NULL)
		{
			TreeVisitForChildFrame(tree, hChildItem, target);
			hChildItem = tree.GetNextItem(hChildItem, TVGN_NEXT);
		}
	}
}

typeImgPtr CViewTree::TreeVisitForImg(CViewTree & tree, HTREEITEM hItem, Transitions target)
{
	typeImgPtr ret = getImg(tree, hItem, target);
	if (ret != NULL)
	{
		return ret;
	}

	if (tree.ItemHasChildren(hItem))
	{
		HTREEITEM hChildItem = tree.GetChildItem(hItem);
		while (hChildItem != NULL)
		{
			ret = TreeVisitForImg(tree, hChildItem, target);
			if (ret != NULL)
			{
				return ret;
			}
			hChildItem = tree.GetNextItem(hChildItem, TVGN_NEXT);
		}
	}

	return NULL;
}