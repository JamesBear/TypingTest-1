// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TypingTest.h"

#include "MainFrm.h"
#include "TypingTestView.h"		//8.5.4������������

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_USERNAME, OnUserName)	 //ע��������6.2.2��
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,				// status line indicator
	ID_INDICATOR_DATE,			//ע��������6.2.2��
	ID_INDICATOR_TIME,		    //ע��������6.2.2��
	ID_INDICATOR_USERNAME,		//ע��������6.2.2��


	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	//ע��������6.3.2��
	if (!m_wndDlgBar.Create(this, IDD_DLGBAR,     //ע��������6.3.2��
		WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS 
			| CBRS_FLYBY | CBRS_SIZE_DYNAMIC, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}
	//ע��������6.3.2��

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	SetWindowPos(&wndTopMost,0,0,1004,730,SWP_NOMOVE);//ע��������2.4.3��
	CenterWindow();									//ע��������2.4.3��
	m_wndStatusBar.SetPaneText(1,theApp.m_strDate);	//ע��������6.2.2��
	SetTimer(1,1000,NULL);							//ע��������6.2.2��
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &=~(WS_SIZEBOX|WS_MAXIMIZEBOX);	//ע��������2.4.3��
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CTime time;						//ע��������6.2.2��
	struct tm *osTime;				//ע��������6.2.2��
	time=CTime::GetCurrentTime();	//ע��������6.2.2��
	osTime=time.GetLocalTm(NULL);	//ע��������6.2.2��
	//ע��������6.2.2��
	m_strTime.Format("%2d:%2d:%2d",osTime->tm_hour,osTime->tm_min,osTime->tm_sec);
	m_wndStatusBar.SetPaneText(2,m_strTime);		//ע��������6.2.2��
	if(osTime->tm_sec%2)SetClassLong(m_hWnd,GCL_HICON,(LONG)LoadIcon(theApp.m_hInstance,
		MAKEINTRESOURCE(IDR_MAINFRAME)));		//ע��������6.2.2��
	else
		SetClassLong(m_hWnd,GCL_HICON,(LONG)LoadIcon(theApp.m_hInstance,MAKEINTRESOURCE(IDI_KEY)));
	
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
//8.5.4�ڲ����е����˴��ڹرհ�ť�Ĵ�����뿪ʼ
CTypingTestView *pView=(CTypingTestView *)GetActiveView(); //8.5.4�ڿ������η�����ͼ��
if(pView->m_bTestBegin) //8.5.4��ͼ�Ŀ�ʼ�����Ƿ�Ϊ�棬��Ϊ��˵�����ڲ���
{
		MessageBox("�ڲ����У������˳�����Ҫ�˳����밴Esc	���������ԣ����˳���","���ֲ���ϵͳ",MB_OK);
		return;
}
 //8.5.4�ڲ����е����˹رհ�ť�Ĵ��������

	KillTimer(1);								//ע��������6.2.2��
	CFrameWnd::OnClose();
}
void CMainFrame::OnUserName(CCmdUI *pCmdUI)		//ע��������6.2.2��
{
		pCmdUI->SetText("������:"+theApp.m_strUserName);	//ע��������6.2.2��
}
