// TypingTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TypingTest.h"

#include "MainFrm.h"
#include "TypingTestDoc.h"
#include "TypingTestView.h"
#include "LoginDlg.h"		//注释在书上4.2.5节

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTypingTestApp

BEGIN_MESSAGE_MAP(CTypingTestApp, CWinApp)
	//{{AFX_MSG_MAP(CTypingTestApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTypingTestApp construction

CTypingTestApp::CTypingTestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	SYSTEMTIME lpSystemTime;		//注释在书上6.2.2节
	GetSystemTime(&lpSystemTime);   //注释在书上6.2.2节
	m_strDate.Format("%ld-%ld-%ld",
		lpSystemTime.wYear,lpSystemTime.wMonth,lpSystemTime.wDay);	//注释在书上6.2.2节

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTypingTestApp object

CTypingTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTypingTestApp initialization

BOOL CTypingTestApp::InitInstance()
{
	

	//注释在书上7.1.5节
	//注释在书上7.1.5节
	char szFilePath[MAX_PATH],szUser[MAX_PATH],szEngl[MAX_PATH],szChina[MAX_PATH];
	char *p;
	GetModuleFileName(NULL, szFilePath, MAX_PATH);		//注释在书上7.1.5节
	//注释在书上7.1.5节
	p = szFilePath;
		while(strchr(p,'\\')) { 			//注释在书上7.1.5节
			p = strchr(p,'\\');				//注释在书上7.1.5节
		p++;								//注释在书上7.1.5节
	}
	*p = '\0';								//注释在书上7.1.5节
	//注释在书上7.1.5节。
	SetCurrentDirectory(szFilePath);		//注释在书上7.1.5节

	strcpy(szUser,szFilePath);strcpy(szEngl,szFilePath);strcpy(szChina,szFilePath);
	strcat(szUser,"USER.MDB");strcat(szEngl, "English.txt");
	strcat(szChina, "Chinese.txt");
	//注释在书上7.1.5节
	FILE *File = NULL;			//注释在书上7.1.5节 
	File = fopen(szUser,"r");	//注释在书上7.1.5节 
	if (!File)					//注释在书上7.1.5节 
	{ 
		MessageBox(NULL,"没有数据库文件USER.MDB","出错信息",MB_OK);	//注释在书上7.1.5节
		ExitProcess(EXIT_FAILURE);	//注释在书上7.1.5节
	} 
	File = fopen(szEngl,"r"); 	// 注释在书上7.1.5节 
	if (!File) 					// 注释在书上7.1.5节
	{ 
		MessageBox(NULL,"没有英文打字测试范文文件English.txt","出错信息",MB_OK);	//注释在书上7.1.5节
		ExitProcess(EXIT_FAILURE);		//注释在书上7.1.5节
	} 
	File = fopen(szChina,"r"); 			// 注释在书上7.1.5节 
	if (!File) 							// 注释在书上7.1.5节 
	{ 
		MessageBox(NULL,"没有中文打字测试范文文件Chinese.txt","出错信息",MB_OK);	//注释在书上7.1.5节
		ExitProcess(EXIT_FAILURE);		//注释在书上7.1.5节
	} 		//注释在书上7.1.5节


	//注释在书上2.4.3节

	int ScrWidth=GetSystemMetrics(SM_CXSCREEN);//注释在书上2.4.3节
	if(ScrWidth<1024)  //注释在书上2.4.3节
	{
		MessageBox(NULL,"本软件运行在屏幕分辨率高于1024*768以上","出错信息",MB_OK);
		ExitProcess(EXIT_FAILURE);//注释在书上2.4.3节
		return FALSE;
	}
	 //注释在书上2.4.3节
	//注释在书上4.2.4节
	if (!AfxOleInit())
	{
		AfxMessageBox("初始化COM库失败");
		return FALSE;
	}
	//注释在书上4.2.5节
	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");//注释在书上4.2.5节
		if(SUCCEEDED(hr))
		{
			CHAR HD[]="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=User.mdb;Persist security info=False;Jet OLEDB:Database Password=815815";
			hr = m_pConnection->Open(HD,"","",adModeUnknown);
			//注释在书上4.2.5节
			//注释在书上4.2.5节 
		}
	}
	catch(_com_error e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信息
		return false;
	}
	//注释在书上4.2.5节
	//注释在书上4.2.5节
	CLoginDlg LoginDlg;
	if (LoginDlg.DoModal()==IDOK)
	{
		m_lUserRight=LoginDlg.m_lUserRight;			//注释在书上4.2.5节
		 m_strUserName=LoginDlg.m_strUserName;		//注释在书上4.2.5节
		 m_strUserID=LoginDlg.m_strUserID;			//注释在书上4.2.5节
	}
	else
	{
    	return false;
	}
	//注释在书上4.2.5节

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTypingTestDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CTypingTestView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CTypingTestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CTypingTestApp message handlers


int CTypingTestApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pConnection->Close();//注释在书上4.2.6节	
	return CWinApp::ExitInstance();
}
