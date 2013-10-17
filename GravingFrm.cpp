// FaultFileFrm.cpp : CFaultFileFrame ���ʵ��
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

// CFaultFileFrame ����/����

CGrayingFrame::CGrayingFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CGrayingFrame::~CGrayingFrame()
{

}


BOOL CGrayingFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CFaultFileFrame ���

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

// CFaultFileFrame ��Ϣ�������
void CGrayingFrame::OnFileClose() 
{
	// ��Ҫ�رտ�ܣ�ֻ�跢�� WM_CLOSE��
	// ���൱�ڴ�ϵͳ�˵���ѡ��رա�
	SendMessage(WM_CLOSE);
}

int CGrayingFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	//GetClientRect(rectDummy);
	rectDummy.SetRectEmpty();
	
	// ����һ����ͼ��ռ�ÿ�ܵĹ�����
	///*
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,rectDummy, this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("δ�ܴ�����ͼ����\n");
		return -1;
	}
	//*/

	/*
	if (!m_wndShowList.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT, rectDummy, this, 2))
	{
		TRACE0("δ�ܴ��������б�\n");
		return -1;      // δ�ܴ���
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
	// ����ͼ��һ�γ��Ը�����
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	{
		return TRUE;
	}
	
	// ����ִ��Ĭ�ϴ���
	return CMDIChildWndEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CGrayingFrame::OnUpdateRefresh(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(true);
}