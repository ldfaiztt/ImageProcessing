
#include "stdafx.h"
#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "ImageProcessing.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar
const WCHAR str1_9[] = L"{{1,1,1},{1,1,1},{1,1,1}}";
const WCHAR str1_16[] = L"{{1,2,1},{2,4,2},{1,2,1}}";
const WCHAR strNeg4[] = L"{{0,1,0},{1,-4,1},{0,1,0}}";
const WCHAR strPos4[] = L"{{0,-1,0},{-1,4,-1},{0,1,0}}";
const WCHAR strNeg8[] = L"{{1,1,1},{1,-8,1},{1,1,1}}";
const WCHAR strPos8[] = L"{{-1,-1,-1},{-1,8,-1},{-1,-1,-1}}";

CPropertiesWnd::CPropertiesWnd()
{
	m_nComboHeight = 0;
	
	maskType_map[str1_9] = maskType::average_1_9;
	maskType_map[str1_16] = maskType::average_1_16;
	maskType_map[strNeg4] = maskType::laplacian_nag4;
	maskType_map[strNeg8] = maskType::laplacian_nag8;
	maskType_map[strPos4] = maskType::laplacian_pos4;
	maskType_map[strPos8] = maskType::laplacian_pos8;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnPropertiesFlash)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdatePropertiesFlash)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar message handlers

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() -(m_nComboHeight+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create combo:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("Failed to create Properties Combo \n");
		return -1;      // fail to create
	}

	m_wndObjectCombo.AddString(_T("Application"));
	m_wndObjectCombo.AddString(_T("Properties Window"));
	m_wndObjectCombo.SetCurSel(0);

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect (&rectCombo);

	m_nComboHeight = rectCombo.Height();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1;      // fail to create
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* Is locked */);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* Locked */);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: Add your command handler code here
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: Add your command update UI handler code here
}

void CPropertiesWnd::OnPropertiesFlash()
{
	CString strH = pHeight->GetValue();
	CString strW = pWidth->GetValue();
	CString strC = pC->GetValue();
	CString strY = pY->GetValue();
	CString strA = pA->GetValue();
	CString strPath = pPath->GetValue();
	CString strMaskSize = pMaskSize->GetValue();
	CString strBitSize = pBitSize->GetValue();
	CString strBitMask = pBitMask->GetValue();
	tstring strMaskType = (CString)pMaskType->GetValue();

	typeImgParaPtr imgP(new stImgPara);
	imgP->height = _wtoi(strH);
	imgP->width = _wtoi(strW);
	imgP->bit_size = _wtoi(strBitSize);
	if (strMaskType.length() < 3)
	{
		imgP->bit_mask = _wtoi(strBitMask);
	} 
	else
	{
		strBitMask.MakeReverse();
		imgP->bit_mask = 0;
		for (int i = 0; i < 8 && i < strBitMask.GetLength(); i++)
		{
			if (strBitMask.GetAt(i) != '0')
			{
				imgP->bit_mask |= ByteMask[i];
			}
		}
	}
	imgP->mask_size = _wtoi(strMaskSize);
	imgP->c = _wtof(strC);
	imgP->y = _wtof(strY);
	imgP->A = _wtof(strA);
	imgP->mask_type = maskType_map[strMaskType];
	imgP->filePath = strPath;

	((CMainFrame *)AfxGetMainWnd())->RefreshClassView(imgP);
}

void CPropertiesWnd::OnUpdatePropertiesFlash(CCmdUI* /*pCmdUI*/)
{
	// TODO: Add your command update UI handler code here
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	//CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Appearance"));

	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("3D Look"), (_variant_t) false, _T("Specifies the window's font will be non-bold and controls will have a 3D border")));

	//CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("Border"), _T("Dialog Frame"), _T("One of: None, Thin, Resizable, or Dialog Frame"));
	//pProp->AddOption(_T("None"));
	//pProp->AddOption(_T("Thin"));
	//pProp->AddOption(_T("Resizable"));
	//pProp->AddOption(_T("Dialog Frame"));
	//pProp->AllowEdit(FALSE);

	//pGroup1->AddSubItem(pProp);
	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Caption"), (_variant_t)_T("About"), _T("Specifies the text that will be displayed in the window's title bar")));

	//m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("Image Size"), 0, TRUE);
	pHeight = new CMFCPropertyGridProperty(_T("Height"), (_variant_t)320l, _T("Specifies the img's height"));
	pHeight->EnableSpinControl(TRUE, 0, 1280);
	pSize->AddSubItem(pHeight);
	pWidth = new CMFCPropertyGridProperty( _T("Width"), (_variant_t) 240l, _T("Specifies the img's width"));
	pWidth->EnableSpinControl(TRUE, 0, 960);
	pSize->AddSubItem(pWidth);
	pSize->Expand(TRUE);
	m_wndPropList.AddProperty(pSize);

	CMFCPropertyGridProperty* pMask = new CMFCPropertyGridProperty(_T("Mask"));
	pMaskSize = new CMFCPropertyGridProperty(_T("Mask size"), (_variant_t)3l, _T("Specifies the img filter's Mask size"));
	pMaskSize->EnableSpinControl(TRUE, 1, 16);
	pMask->AddSubItem(pMaskSize);
	pMask->Expand(TRUE);
	m_wndPropList.AddProperty(pMask);

	pMaskType = new CMFCPropertyGridProperty(_T("Mask type"), str1_9, _T("all the mask types are here, but some of them are for special filters. mixed using mask type and filter will fail and cause using default para."));
	pMaskType->AddOption(str1_9);
	pMaskType->AddOption(str1_16);
	pMaskType->AddOption(strNeg4);
	pMaskType->AddOption(strNeg8);
	pMaskType->AddOption(strPos4);
	pMaskType->AddOption(strPos8);
	pMaskType->AllowEdit(FALSE);
	pMask->AddSubItem(pMaskType);

	CMFCPropertyGridProperty* pBitOp = new CMFCPropertyGridProperty(_T("Bit Operation"));

	pBitSize = new CMFCPropertyGridProperty(_T("Bit size"), (_variant_t)8l, _T("Specifies the img's gray level"));
	pBitSize->EnableSpinControl(TRUE, 1, 8);
	pBitOp->AddSubItem(pBitSize);

	pBitMask = new CMFCPropertyGridProperty(_T("Bit Mask"), (_variant_t)11111111l, _T("Specifies the img's Bit-Plane Slicing, binary format. 0xff as all planes, 0x01 as lowest order 0x80 as highest order plane"));
	pBitMask->EnableSpinControl(TRUE, 0, 255);
	pBitOp->AddSubItem(pBitMask);

	pBitOp->Expand(TRUE);
	m_wndPropList.AddProperty(pBitOp);

	CMFCPropertyGridProperty* pConst = new CMFCPropertyGridProperty(_T("filter func Const"));

	pC = new CMFCPropertyGridProperty(_T("C"), (_variant_t)1.0, _T("Specifies the img's Pow or Log coefficient"));
	pConst->AddSubItem(pC);

	pY = new CMFCPropertyGridProperty(_T("Y"), (_variant_t)1.0, _T("Specifies the img's Pow or Log coefficient"));
	pConst->AddSubItem(pY);

	pA = new CMFCPropertyGridProperty(_T("A"), (_variant_t)1.7, _T("Specifies the img's high boosting coefficient"));
	pConst->AddSubItem(pA);
	
	pConst->Expand(TRUE);
	m_wndPropList.AddProperty(pConst);

	//CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("Font"));

	//LOGFONT lf;
	//CFont* font = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	//font->GetLogFont(&lf);

	//lstrcpy(lf.lfFaceName, _T("Arial"));

	//pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("Font"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("Specifies the default font for the window")));
	//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Use System Font"), (_variant_t) true, _T("Specifies that the window uses MS Shell Dlg font")));

	//m_wndPropList.AddProperty(pGroup2);

	//CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("Misc"));
	//CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("(Name)"), _T("Application"));
	//pProp->Enable(FALSE);
	//pGroup3->AddSubItem(pProp);

	//CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("Window Color"), RGB(210, 192, 254), NULL, _T("Specifies the default window color"));
	//pColorProp->EnableOtherButton(_T("Other..."));
	//pColorProp->EnableAutomaticButton(_T("Default"), ::GetSysColor(COLOR_3DFACE));
	//pGroup3->AddSubItem(pColorProp);

	CMFCPropertyGridProperty* pFile = new CMFCPropertyGridProperty(_T("Misc"));

	static const TCHAR szFilter[] = _T("Icon Files(*.jpg)|*.jpg|All Files(*.*)|*.*||");
	pPath = new CMFCPropertyGridFileProperty(_T("Match Img"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("Specifies the window icon"));
	pFile->AddSubItem(pPath);

	pConst->Expand(TRUE);
	m_wndPropList.AddProperty(pFile);

	//CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("Hierarchy"));

	//CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("First sub-level"));
	//pGroup4->AddSubItem(pGroup41);

	//CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("Second sub-level"));
	//pGroup41->AddSubItem(pGroup411);

	//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 1"), (_variant_t)_T("Value 1"), _T("This is a description")));
	//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 2"), (_variant_t)_T("Value 2"), _T("This is a description")));
	//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 3"), (_variant_t)_T("Value 3"), _T("This is a description")));

	//pGroup4->Expand(FALSE);
	//m_wndPropList.AddProperty(pGroup4);
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}


void CPropertiesWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_RETURN)
	{
		OnPropertiesFlash();
	}

	CDockablePane::OnKeyDown(nChar, nRepCnt, nFlags);
}
