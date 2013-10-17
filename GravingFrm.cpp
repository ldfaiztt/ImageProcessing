// FaultFileFrm.cpp : CFaultFileFrame 类的实现
//

#include "stdafx.h"
#include "GravingFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFaultFileFrame

IMPLEMENT_DYNCREATE(CGrayingFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CGrayingFrame, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_CLOSE, &CGrayingFrame::OnFileClose)
	//ON_COMMAND(ID_REFRESH,OnRefresh)
	//ON_UPDATE_COMMAND_UI(ID_REFRESH,OnUpdateRefresh)
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
	//ON_WM_CONTEXTMENU()
	//ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CFaultFileFrame 构造/析构

CGrayingFrame::CGrayingFrame()
{
	// TODO: 在此添加成员初始化代码
}

CGrayingFrame::~CGrayingFrame()
{

}


BOOL CGrayingFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CFaultFileFrame 诊断

#ifdef _DEBUG
void CGrayingFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CGrayingFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CFaultFileFrame 消息处理程序
void CGrayingFrame::OnFileClose() 
{
	// 若要关闭框架，只需发送 WM_CLOSE，
	// 这相当于从系统菜单中选择关闭。
	SendMessage(WM_CLOSE);
}

int CGrayingFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	//GetClientRect(rectDummy);
	rectDummy.SetRectEmpty();
	
	// 创建一个视图以占用框架的工作区
	///*
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,rectDummy, this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("未能创建视图窗口\n");
		return -1;
	}
	//*/

	/*
	if (!m_wndShowList.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT, rectDummy, this, 2))
	{
		TRACE0("未能创建故障列表\n");
		return -1;      // 未能创建
	}
	
	m_wndShowList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_wndShowList.ModifyStyleEx(0,WS_EX_CLIENTEDGE);
	m_wndShowList.EnableMarkSortedColumn();
	m_wndShowList.EnableMultipleSort();
	*/

	
	//AdjustLayout();
	//InitFaultFileFrmList();

	return 0;
}

void CGrayingFrame::AdjustLayout(void)
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect frameClient;
	CRect viewClient;
	GetClientRect(frameClient);
	m_wndView.GetClientRect(viewClient);
	//m_wndShowList.SetWindowPos(NULL, frameClient.left, frameClient.top, frameClient.Width(), frameClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);	
}

void CGrayingFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWndEx::OnSetFocus(pOldWnd);

	m_wndView.SetFocus();
}

BOOL CGrayingFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// 让视图第一次尝试该命令
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	{
		return TRUE;
	}
	
	// 否则，执行默认处理
	return CMDIChildWndEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CGrayingFrame::OnUpdateRefresh(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(true);
}