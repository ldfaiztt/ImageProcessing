
#include "stdafx.h"
#include "MainFrm.h"
#include "ClassView.h"
#include "Resource.h"
#include "ImageProcessing.h"
#include "TransImage.h"

class CClassViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CClassView;

	DECLARE_SERIAL(CClassViewMenuButton)

public:
	CClassViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CClassViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClassView::CClassView()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}

CClassView::~CClassView()
{
}

BEGIN_MESSAGE_MAP(CClassView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLASS_ADD_MEMBER_FUNCTION, OnClassAddMemberFunction)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_VARIABLE, OnClassAddMemberVariable)
	ON_COMMAND(ID_CLASS_DEFINITION, OnClassDefinition)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassView message handlers

int CClassView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create views:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndClassView.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("Failed to create Class View\n");
		return -1;      // fail to create
	}

	// Load images:
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_SORT);

	m_wndToolBar.ReplaceButton(ID_SORT_MENU, CClassViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
		pButton->SetMessageWnd(this);
	}

	// Fill in some static tree view data (dummy code, nothing magic here)
	FillClassView();

	return 0;
}

void CClassView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CClassView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// Select clicked item:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_SORT);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}

void CClassView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndClassView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CClassView::OnTvnSelchanged()
{
	//LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	//*pResult = 0;
	int r = 0;
}

BOOL CClassView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONDBLCLK && pMsg->hwnd == m_wndClassView.GetSafeHwnd())
	{
		OnLButtonDblClk(pMsg->wParam, pMsg->pt);

		::TranslateMessage(pMsg);
		::DispatchMessage(pMsg);

		//return   TRUE;//   TRUE,   msg   is   processed   
	}

	if (pMsg->message == TVN_SELCHANGED && pMsg->hwnd == m_wndClassView.GetSafeHwnd())
	{
		OnTvnSelchanged();

		::TranslateMessage(pMsg);
		::DispatchMessage(pMsg);

		//return   TRUE;//   TRUE,   msg   is   processed   
	}


	//   FALSE,   for   further   process   
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CClassView::OnSort(UINT id)
{
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->SetImage(GetCmdMgr()->GetCmdImage(id));
		m_wndToolBar.Invalidate();
		m_wndToolBar.UpdateWindow();
	}
}

void CClassView::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}

void CClassView::OnClassAddMemberFunction()
{
	AfxMessageBox(_T("Add member function..."));
}

void CClassView::OnClassAddMemberVariable()
{
	// TODO: Add your command handler code here
}

void CClassView::OnClassDefinition()
{
	// TODO: Add your command handler code here
}

void CClassView::OnClassProperties()
{
	// TODO: Add your command handler code here
}

void CClassView::OnNewFolder()
{
	AfxMessageBox(_T("New Folder..."));
}

void CClassView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_wndClassView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CClassView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndClassView.SetFocus();
}

void CClassView::OnChangeVisualStyle()
{
	m_ClassViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_ClassViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_ClassViewImages.Add(&bmp, RGB(255, 0, 0));

	m_wndClassView.SetImageList(&m_ClassViewImages, TVSIL_NORMAL);

	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* Locked */);
}

stTreeItemInfo * CClassView::TransImg(shared_ptr<stImgPara> imgP)
{
	stTreeItemInfo * item = (stTreeItemInfo *)m_wndClassView.getCurItemInfo();

	if (item == NULL)
	{
		return NULL;
	}

	if (item->NeedToUpdate == true || item->img == NULL)
	{
		stTreeItemInfo * parent = (stTreeItemInfo *)m_wndClassView.getParentItemInfo();
		if (parent == NULL)
		{
			if (!(item->img == NULL))
			{
				item->img = TransImage::transit_img(item->img, item->tsType,imgP);
			}
		}
		else
		{
			item->img = TransImage::transit_img(parent->img, item->tsType,imgP);
		}

		CString count;
		count.Format(L"%d", ((CImageProcessingApp *)AfxGetApp())->img_count++);
		CString name = _T("processing_img");
		name += count;
		name += _T(".jpg");
		item->img->Save(name);

		item->NeedToUpdate = false;
	}

	OnShowChildFrame(item);
}

void CClassView::Refresh(shared_ptr<stImgPara> imgP)
{
	stTreeItemInfo * item = (stTreeItemInfo *)m_wndClassView.getCurItemInfo();
	item->NeedToUpdate = true;
	TransImg(imgP);
}

void CClassView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	TransImg(NULL);

	CDockablePane::OnLButtonDblClk(nFlags, point);
}

void CClassView::OnShowChildFrame(stTreeItemInfo * item)
{
	((CMainFrame *)AfxGetMainWnd())->RefreshChildFrm(item);
}

void CClassView::FillClassView()
{
	shared_ptr<CImage> img = make_shared<CImage>(((CImageProcessingApp *)AfxGetApp())->img);
	HTREEITEM hRoot = m_wndClassView.InsertItem(_T("graying"), 0, 0);
	m_wndClassView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	m_wndClassView.SetItemData(hRoot, (DWORD_PTR)(new stTreeItemInfo(NULL, img, Transitions::graying, true)));

	HTREEITEM hZoom = m_wndClassView.InsertItem(_T("subsampling"), 1, 1, hRoot);
	m_wndClassView.SetItemData(hZoom, (DWORD_PTR)(new stTreeItemInfo(NULL, NULL, Transitions::subsampling, true)));
	HTREEITEM h2 = m_wndClassView.InsertItem(_T("replication method upsampling"), 3, 3, hZoom);
	m_wndClassView.SetItemData(h2, (DWORD_PTR)(new stTreeItemInfo(NULL, NULL, Transitions::replication, true)));
	HTREEITEM h3 = m_wndClassView.InsertItem(_T("nearest neighbor method upsampling"), 3, 3, hZoom);
	m_wndClassView.SetItemData(h3, (DWORD_PTR)(new stTreeItemInfo(NULL, NULL, Transitions::nearest_neighbor, true)));
	HTREEITEM h4 = m_wndClassView.InsertItem(_T("bilinear interpolation method upsampling"), 3, 3, hZoom);
	m_wndClassView.SetItemData(h4, (DWORD_PTR)(new stTreeItemInfo(NULL, NULL, Transitions::bilinear_interpolation, true)));


	HTREEITEM hGrayL = m_wndClassView.InsertItem(_T("graylevel"), 1, 1, hRoot);
	m_wndClassView.SetItemData(hGrayL, (DWORD_PTR)(new stTreeItemInfo(NULL, NULL, Transitions::gray_level, true)));

	HTREEITEM hPow = m_wndClassView.InsertItem(_T("pow scale"), 1, 1, hRoot);
	m_wndClassView.SetItemData(hPow, (DWORD_PTR)(new stTreeItemInfo(NULL, NULL, Transitions::pow_scale, true)));

	HTREEITEM hLog = m_wndClassView.InsertItem(_T("log scale"), 1, 1, hRoot);
	m_wndClassView.SetItemData(hLog, (DWORD_PTR)(new stTreeItemInfo(NULL, NULL, Transitions::log_scale, true)));

	HTREEITEM hHeq = m_wndClassView.InsertItem(_T("Histogram equal"), 1, 1, hRoot);
	m_wndClassView.SetItemData(hHeq, (DWORD_PTR)(new stTreeItemInfo(NULL, NULL, Transitions::histogram_eq, true)));

	HTREEITEM hHmc = m_wndClassView.InsertItem(_T("Histogram match"), 1, 1, hRoot);
	m_wndClassView.SetItemData(hHmc, (DWORD_PTR)(new stTreeItemInfo(NULL, NULL, Transitions::histogram_match, true)));

	HTREEITEM hHloc = m_wndClassView.InsertItem(_T("Histogram local"), 1, 1, hRoot);
	m_wndClassView.SetItemData(hHloc, (DWORD_PTR)(new stTreeItemInfo(NULL, NULL, Transitions::histogram_local, true)));

	m_wndClassView.Expand(hZoom, TVE_EXPAND);
	m_wndClassView.Expand(hRoot, TVE_EXPAND);
}