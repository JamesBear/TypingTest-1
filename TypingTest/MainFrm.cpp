// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TypingTest.h"

#include "MainFrm.h"
#include "TypingTestView.h"		//8.5.4框架类访问视类

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
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_USERNAME, OnUserName)	 //注释在书上6.2.2节
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,				// status line indicator
	ID_INDICATOR_DATE,			//注释在书上6.2.2节
	ID_INDICATOR_TIME,		    //注释在书上6.2.2节
	ID_INDICATOR_USERNAME,		//注释在书上6.2.2节


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
	//注释在书上6.3.2节
	if (!m_wndDlgBar.Create(this, IDD_DLGBAR,     //注释在书上6.3.2节
		WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS 
			| CBRS_FLYBY | CBRS_SIZE_DYNAMIC, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}
	//注释在书上6.3.2节

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

	SetWindowPos(&wndTopMost,0,0,1004,730,SWP_NOMOVE);//注释在书上2.4.3节
	CenterWindow();									//注释在书上2.4.3节
	m_wndStatusBar.SetPaneText(1,theApp.m_strDate);	//注释在书上6.2.2节
	SetTimer(1,1000,NULL);							//注释在书上6.2.2节
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &=~(WS_SIZEBOX|WS_MAXIMIZEBOX);	//注释在书上2.4.3节
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
	CTime time;						//注释在书上6.2.2节
	struct tm *osTime;				//注释在书上6.2.2节
	time=CTime::GetCurrentTime();	//注释在书上6.2.2节
	osTime=time.GetLocalTm(NULL);	//注释在书上6.2.2节
	//注释在书上6.2.2节
	m_strTime.Format("%2d:%2d:%2d",osTime->tm_hour,osTime->tm_min,osTime->tm_sec);
	m_wndStatusBar.SetPaneText(2,m_strTime);		//注释在书上6.2.2节
	if(osTime->tm_sec%2)SetClassLong(m_hWnd,GCL_HICON,(LONG)LoadIcon(theApp.m_hInstance,
		MAKEINTRESOURCE(IDR_MAINFRAME)));		//注释在书上6.2.2节
	else
		SetClassLong(m_hWnd,GCL_HICON,(LONG)LoadIcon(theApp.m_hInstance,MAKEINTRESOURCE(IDI_KEY)));
	
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
//8.5.4在测试中单击了窗口关闭按钮的处理代码开始
CTypingTestView *pView=(CTypingTestView *)GetActiveView(); //8.5.4在框架里如何访问视图。
if(pView->m_bTestBegin) //8.5.4视图的开始变量是否为真，如为真说明正在测试
{
		MessageBox("在测试中，不能退出，如要退出，请按Esc	键结束测试，再退出。","打字测试系统",MB_OK);
		return;
}
 //8.5.4在测试中单击了关闭按钮的处理代码完

	KillTimer(1);								//注释在书上6.2.2节
	CFrameWnd::OnClose();
}
void CMainFrame::OnUserName(CCmdUI *pCmdUI)		//注释在书上6.2.2节
{
		pCmdUI->SetText("测试人:"+theApp.m_strUserName);	//注释在书上6.2.2节
}
