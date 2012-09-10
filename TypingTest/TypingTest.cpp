// TypingTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TypingTest.h"

#include "MainFrm.h"
#include "TypingTestDoc.h"
#include "TypingTestView.h"
#include "LoginDlg.h"		//ע��������4.2.5��

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
	SYSTEMTIME lpSystemTime;		//ע��������6.2.2��
	GetSystemTime(&lpSystemTime);   //ע��������6.2.2��
	m_strDate.Format("%ld-%ld-%ld",
		lpSystemTime.wYear,lpSystemTime.wMonth,lpSystemTime.wDay);	//ע��������6.2.2��

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTypingTestApp object

CTypingTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTypingTestApp initialization

BOOL CTypingTestApp::InitInstance()
{
	

	//ע��������7.1.5��
	//ע��������7.1.5��
	char szFilePath[MAX_PATH],szUser[MAX_PATH],szEngl[MAX_PATH],szChina[MAX_PATH];
	char *p;
	GetModuleFileName(NULL, szFilePath, MAX_PATH);		//ע��������7.1.5��
	//ע��������7.1.5��
	p = szFilePath;
		while(strchr(p,'\\')) { 			//ע��������7.1.5��
			p = strchr(p,'\\');				//ע��������7.1.5��
		p++;								//ע��������7.1.5��
	}
	*p = '\0';								//ע��������7.1.5��
	//ע��������7.1.5�ڡ�
	SetCurrentDirectory(szFilePath);		//ע��������7.1.5��

	strcpy(szUser,szFilePath);strcpy(szEngl,szFilePath);strcpy(szChina,szFilePath);
	strcat(szUser,"USER.MDB");strcat(szEngl, "English.txt");
	strcat(szChina, "Chinese.txt");
	//ע��������7.1.5��
	FILE *File = NULL;			//ע��������7.1.5�� 
	File = fopen(szUser,"r");	//ע��������7.1.5�� 
	if (!File)					//ע��������7.1.5�� 
	{ 
		MessageBox(NULL,"û�����ݿ��ļ�USER.MDB","������Ϣ",MB_OK);	//ע��������7.1.5��
		ExitProcess(EXIT_FAILURE);	//ע��������7.1.5��
	} 
	File = fopen(szEngl,"r"); 	// ע��������7.1.5�� 
	if (!File) 					// ע��������7.1.5��
	{ 
		MessageBox(NULL,"û��Ӣ�Ĵ��ֲ��Է����ļ�English.txt","������Ϣ",MB_OK);	//ע��������7.1.5��
		ExitProcess(EXIT_FAILURE);		//ע��������7.1.5��
	} 
	File = fopen(szChina,"r"); 			// ע��������7.1.5�� 
	if (!File) 							// ע��������7.1.5�� 
	{ 
		MessageBox(NULL,"û�����Ĵ��ֲ��Է����ļ�Chinese.txt","������Ϣ",MB_OK);	//ע��������7.1.5��
		ExitProcess(EXIT_FAILURE);		//ע��������7.1.5��
	} 		//ע��������7.1.5��


	//ע��������2.4.3��

	int ScrWidth=GetSystemMetrics(SM_CXSCREEN);//ע��������2.4.3��
	if(ScrWidth<1024)  //ע��������2.4.3��
	{
		MessageBox(NULL,"�������������Ļ�ֱ��ʸ���1024*768����","������Ϣ",MB_OK);
		ExitProcess(EXIT_FAILURE);//ע��������2.4.3��
		return FALSE;
	}
	 //ע��������2.4.3��
	//ע��������4.2.4��
	if (!AfxOleInit())
	{
		AfxMessageBox("��ʼ��COM��ʧ��");
		return FALSE;
	}
	//ע��������4.2.5��
	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");//ע��������4.2.5��
		if(SUCCEEDED(hr))
		{
			CHAR HD[]="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=User.mdb;Persist security info=False;Jet OLEDB:Database Password=815815";
			hr = m_pConnection->Open(HD,"","",adModeUnknown);
			//ע��������4.2.5��
			//ע��������4.2.5�� 
		}
	}
	catch(_com_error e)///��׽�쳣
	{
		CString errormessage;
		errormessage.Format("�������ݿ�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///��ʾ������Ϣ
		return false;
	}
	//ע��������4.2.5��
	//ע��������4.2.5��
	CLoginDlg LoginDlg;
	if (LoginDlg.DoModal()==IDOK)
	{
		m_lUserRight=LoginDlg.m_lUserRight;			//ע��������4.2.5��
		 m_strUserName=LoginDlg.m_strUserName;		//ע��������4.2.5��
		 m_strUserID=LoginDlg.m_strUserID;			//ע��������4.2.5��
	}
	else
	{
    	return false;
	}
	//ע��������4.2.5��

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
	m_pConnection->Close();//ע��������4.2.6��	
	return CWinApp::ExitInstance();
}
