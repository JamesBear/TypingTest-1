// TypingTestView.cpp : implementation of the CTypingTestView class
//

#include "stdafx.h"
#include "TypingTest.h"

#include "TypingTestDoc.h"
#include "TypingTestView.h"

#include "MainFrm.h"  //注释在书上7.1.4节
#include "CreateNewUser.h"  		//注释在书上9.2节
#include "DeleteUser.h"  //注释在书上9.3.4节
#include "FindScore.h"  //注释在书上9.4.4节
#include "ChangeKey.h"  //注释在书上9.5.4节
#include "LoginDlg.h"	//注释在书上9.6节
#include "htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTypingTestView

IMPLEMENT_DYNCREATE(CTypingTestView, CView)
BEGIN_MESSAGE_MAP(CTypingTestView, CView)
	ON_WM_CONTEXTMENU()

	//{{AFX_MSG_MAP(CTypingTestView)
	ON_COMMAND(ID_TEST_ENGLISH, OnTestEnglish)
	ON_COMMAND(ID_TEST_CHINESE, OnTestChinese)
	ON_COMMAND(ID_SCORE_UNION, OnScoreUnion)
	ON_COMMAND(ID_SCORE_PERSONAL, OnScorePersonall)
	ON_COMMAND(ID_TEST_STOP, OnTestStop)
	ON_COMMAND(ID_USER_CREATE, OnUserCreate)
	ON_COMMAND(ID_USER_DEL, OnUserDel)
	ON_COMMAND(ID_USER_LOGOUT, OnUserLogout)
	ON_UPDATE_COMMAND_UI(ID_USER_LOGOUT, OnUpdateUserLogout)
	ON_UPDATE_COMMAND_UI(ID_USER_DEL, OnUpdateUserDel)
	ON_UPDATE_COMMAND_UI(ID_USER_CREATE, OnUpdateUserCreate)
	ON_UPDATE_COMMAND_UI(ID_TEST_STOP, OnUpdateTestStop)
	ON_UPDATE_COMMAND_UI(ID_TEST_ENGLISH, OnUpdateTestEnglish)
	ON_UPDATE_COMMAND_UI(ID_TEST_CHINESE, OnUpdateTestChinese)
	ON_UPDATE_COMMAND_UI(ID_SCORE_UNION, OnUpdateScoreUnion)
	ON_UPDATE_COMMAND_UI(ID_SCORE_PERSONAL, OnUpdateScorePersonall)
	ON_COMMAND(ID_CHANGE_KEY, OnChangeKey)
	ON_UPDATE_COMMAND_UI(ID_CHANGE_KEY, OnUpdateChangeKey)
	ON_WM_CHAR()
	ON_WM_TIMER()
	ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(IDC_RIGHT, OnRight)				//注释在书上6.3.3节
	ON_UPDATE_COMMAND_UI(IDC_WRONG, OnWrong)				//注释在书上6.3.3节
	ON_UPDATE_COMMAND_UI(IDC_RIGHT_PERCENT, OnRightPercent)	//注释在书上6.3.3节
	ON_UPDATE_COMMAND_UI(IDC_TEST_TIME, OnTestTime)			//注释在书上6.3.3节
	ON_UPDATE_COMMAND_UI(IDC_TEST_FILE, OnTestFile)			//注释在书上6.3.3节
	ON_UPDATE_COMMAND_UI(IDC_SPEED, OnSpeed)				//注释在书上6.3.3节
	ON_UPDATE_COMMAND_UI(ID_SEPARATOR, OnNoteMessage)		//注释在书上6.3.3节

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTypingTestView construction/destruction

CTypingTestView::CTypingTestView()
{
	// TODO: add construction code here
	//注释在书上3.1.2节
	if(!(startFont1.CreateFont(50,			//1.注释在书上3.1.2节 
		0,							//2.注释在书上3.1.2节
		0,							//3.注释在书上3.1.2节
		0,							//4.注释在书上3.1.2节
		FW_BOLD,					//5.注释在书上3.1.2节
		0,							//6.注释在书上3.1.2节
		1,							//7.注释在书上3.1.2节
		0,							//8.注释在书上3.1.2节
		ANSI_CHARSET,				//9.字体所属字符集
		OUT_DEFAULT_PRECIS,			//10.注释在书上3.1.2节
		CLIP_DEFAULT_PRECIS,		//11.注释在书上3.1.2节
		DEFAULT_QUALITY,			//12.注释在书上3.1.2节
		FIXED_PITCH,				//13.注释在书上3.1.2节
		"new Font1")))				//14.注释在书上3.1.2节
	{	//注释在书上3.1.2节
		startFont1.CreateStockObject(SYSTEM_FIXED_FONT);//注释在书上3.1.2节
	}
	if(!(startFont2.CreateFont(33,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,//注释在书上3.1.2节
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FIXED_PITCH,
		"new Font2")))	//注释在书上3.1.2节
	{
		startFont2.CreateStockObject(SYSTEM_FIXED_FONT); //注释在书上3.1.2节
	}
	if(!(startFont3.CreateFont(22,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,		//注释在书上3.1.2节
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FIXED_PITCH,
		"new Font3")))
	{
		startFont3.CreateStockObject(SYSTEM_FIXED_FONT); //注释在书上3.1.2节
	}
	m_bTestRead=FALSE;			//注释在书上3.1.2节
	//注释在书上3.1.2节
	m_bTestBegin=FALSE;			//注释在书上5.2.2节
	m_bTestEnglish=FALSE;		//注释在书上5.2.2节
	
	iInH=4;				//注释在书上7.1.2节
    currentLine=0;		//注释在书上7.1.2节
	currentCol=0;		//注释在书上7.1.2节
	strcpy(m_strTestFile,"");//注释在书上7.1.2节
	inputRight=inputWrong=inputTotal=0;		//注释在书上8.2.1节
	m_lTestTime=0;							//注释在书上8.2.1节
	byte1=0;								//注释在书上8.2.1节

}

CTypingTestView::~CTypingTestView()
{
}

BOOL CTypingTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTypingTestView drawing

void CTypingTestView::OnDraw(CDC* pDC)
{
	CTypingTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//注释在书上3.1.2节
	if(m_bTestRead) //注释在书上3.1.2节
	{
		if(m_bTestEnglish)DisplayEnglish(pDC);//注释在书上7.3.3节
		else DisplayChinese(pDC);			//注释在书上7.3.3节
	}
	else 
	   DisplayState(pDC);//注释在书上3.1.2节

}

/////////////////////////////////////////////////////////////////////////////
// CTypingTestView diagnostics

#ifdef _DEBUG
void CTypingTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTypingTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTypingTestDoc* CTypingTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTypingTestDoc)));
	return (CTypingTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTypingTestView message handlers

void CTypingTestView::DisplayState(CDC *pDC)
{
	//注释在书上3.1.2节
	CTypingTestDoc* pDoc = GetDocument();	//注释在书上3.1.2节
	CFont *pStartOldFont;					//注释在书上3.1.2节
	CRect rect;								//注释在书上3.1.2节
	GetClientRect(&rect);					//注释在书上3.1.2节
	pStartOldFont=(CFont *)pDC->SelectObject(&startFont1);	//注释在书上3.1.2节
	pDC->SetTextAlign(TA_CENTER);							//注释在书上3.1.2节
	pDC->SetTextColor(RGB(255,0,0));						//注释在书上3.1.2节
	pDC->TextOut(rect.right/2,50,pDoc->m_strMessage1);		//注释在书上3.1.2节
	pDC->SelectObject(&startFont2);							//注释在书上3.1.2节
	pDC->TextOut(rect.right/2,110,pDoc->m_strMessage2); 	//注释在书上3.1.2节

	pDC->SetTextColor(RGB(0,0,255));						//注释在书上3.1.2节
	pDC->SetTextAlign(TA_LEFT);								//注释在书上3.1.2节
	pDC->TextOut(5,175,pDoc->m_strMessage3);				//注释在书上3.1.2节
	pDC->TextOut(5,175+50,pDoc->m_strMessage4);				//注释在书上3.1.2节
	pDC->TextOut(5,175+100,pDoc->m_strMessage5);			//注释在书上3.1.2节
	pDC->TextOut(5,175+150,pDoc->m_strMessage6);			//注释在书上3.1.2节
	pDC->TextOut(5,175+200,pDoc->m_strMessage7);			//注释在书上3.1.2节
	pDC->TextOut(5,175+250,pDoc->m_strMessage8);			//注释在书上3.1.2节

	pDC->TextOut(rect.right/3+100,500,pDoc->m_strMessage9);		//注释在书上3.1.2节
	pDC->TextOut(rect.right/3+100,500+30,pDoc->m_strMessage10);	//注释在书上3.1.2节

	CPen pen(PS_SOLID,5,RGB(255,0,0));				//注释在书上3.1.2节
	CPen *pOldPen;									//注释在书上3.1.2节
	pOldPen=pDC->SelectObject(&pen);				//注释在书上3.1.2节
	pDC->MoveTo(10,150);							//注释在书上3.1.2节
	pDC->LineTo(rect.right-10,150);					//注释在书上3.1.2节
	pDC->MoveTo(10,500-10);							//注释在书上3.1.2节
	pDC->LineTo(rect.right-10,500-10);				//注释在书上3.1.2节

	pDC->SelectObject(pStartOldFont);				//注释在书上3.1.2节
	pDC->SelectObject(pOldPen);						//注释在书上3.1.2节
	pDC->SetTextColor(RGB(0,0,0));					//注释在书上3.1.2节
	pDC->SetTextAlign(TA_LEFT);						//注释在书上3.1.2节
	//注释在书上3.1.2节

}

void CTypingTestView::OnTestEnglish() 
{
	// TODO: Add your command handler code here
	m_bTestBegin=FALSE; 		//注释在书上8.4.2节
	m_bTestRead=TRUE;			//注释在书上5.2.2节
	m_bTestEnglish=TRUE;		//注释在书上5.2.2节
	inputRight=inputWrong=inputTotal=0;	//注释在书上7.1.4节
	currentLine=currentCol=0;			//注释在书上7.1.4节
	m_lTestTime=0;						//注释在书上7.1.4节

	strcpy(m_strTestFile,"English.txt");
	LoadEnglisFile(m_strTestFile);			//注释在书上7.1.4节。
	((CMainFrame *)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(0,"英文打字测试准备就绪，按空格键开始测试。");		//注释在书上7.1.4节
	Invalidate();						//注释在书上7.1.4节。	
	
}

void CTypingTestView::OnTestChinese() 
{
	// TODO: Add your command handler code here
	m_bTestRead=TRUE;		//注释在书上5.2.2节
    m_bTestEnglish=FALSE;		//注释在书上5.2.2节
	m_bTestBegin=FALSE;		//注释在书上5.2.2节
	inputRight=inputWrong=inputTotal=0;	//7.3.3输入的:对,错,总共的数目
	currentLine=currentCol=0;	//注释在书上7.3.3节
	m_lTestTime=0;				//注释在书上7.3.3节
	strNoteMessage="准备就绪，按空格键开始测试。";//注释在书上7.3.3节
	strcpy(m_strTestFile,"Chinese.txt");//注释在书上7.3.3节
	LoadEnglisFile(m_strTestFile);		///注释在书上7.3.3节。
	((CMainFrame *)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(0,strNoteMessage);
	Invalidate();					//注释在书上7.3.3节。
	
}

void CTypingTestView::OnScoreUnion() 
{
	// TODO: Add your command handler code here
	//注释在书上9.4.4节
	CFindScore *Dlg=new CFindScore(this);	//注释在书上9.4.4节
	Dlg->m_strCaption ="所有用户成绩";		//注释在书上9.4.4节

	Dlg->m_bFindAll=TRUE;				//注释在书上9.4.4节
	Dlg->Create(IDD_DIALOG_FINDSCORE);	//注释在书上9.4.4节
	Dlg->ShowWindow(SW_SHOW);				//注释在书上9.4.4节
	
}

void CTypingTestView::OnScorePersonall() 
{
	// TODO: Add your command handler code here
	//注释在书上9.4.4节
	CFindScore *Dlg=new CFindScore(this);			//注释在书上9.4.4节
	CString temp="的测试成绩";					//注释在书上9.4.4节
	Dlg->m_strCaption =theApp.m_strUserName+temp;	//注释在书上9.4.4节
	Dlg->m_bFindAll=FALSE;					//注释在书上9.4.4节
	Dlg->Create(IDD_DIALOG_FINDSCORE);	//注释在书上9.4.4节
	Dlg->ShowWindow(SW_SHOW);				//注释在书上9.4.4节
	
}

void CTypingTestView::OnTestStop() 
{
	// TODO: Add your command handler code here
	HideCaret();	//注释在书上8.3.2节
	TestEnd();		//注释在书上8.3.2节。
}

void CTypingTestView::OnUserCreate() 
{
	// TODO: Add your command handler code here
	//注释在书上9.2节
	CCreateNewUser NewUserDlg;				//注释在书上9.2节
	NewUserDlg.m_strCaption="建立超级用户";  //注释在书上9.2节
	NewUserDlg.DoModal();					//注释在书上9.2节
	
}

void CTypingTestView::OnUserDel() 
{
	// TODO: Add your command handler code here
	//注释在书上9.3.4节
	CDeleteUser DelUserDlg;		//注释在书上9.3.4节
	DelUserDlg.DoModal();		//注释在书上9.3.4节
	
}

void CTypingTestView::OnUserLogout() 
{
	// TODO: Add your command handler code here
	//注释在书上9.6节
	
	CLoginDlg LoginDlg;
	if (LoginDlg.DoModal()==IDOK)
	{
		theApp.m_lUserRight=LoginDlg.m_lUserRight;			//注释在书上9.6节
		 theApp.m_strUserName=LoginDlg.m_strUserName;		//注释在书上9.6节
		 theApp.m_strUserID=LoginDlg.m_strUserID;			//注释在书上9.6节
	}
	else
	{
    	return ;//9.6
	}
	//注释在书上9.6节
	
}

void CTypingTestView::OnUpdateUserLogout(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bTestBegin);		//注释在书上5.2.2节	
}

void CTypingTestView::OnUpdateUserDel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bTestBegin&&theApp.m_lUserRight);		//注释在书上5.2.2节	
}

void CTypingTestView::OnUpdateUserCreate(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bTestBegin&&theApp.m_lUserRight);		//注释在书上5.2.2节	
}

void CTypingTestView::OnUpdateTestStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_bTestBegin);	//注释在书上5.2.2节	
}

void CTypingTestView::OnUpdateTestEnglish(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bTestRead&&m_bTestEnglish);	//注释在书上5.2.2节
	pCmdUI->Enable(!m_bTestBegin);					//注释在书上5.2.2节
	
}

void CTypingTestView::OnUpdateTestChinese(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bTestRead&&!m_bTestEnglish);		//注释在书上5.2.2节
	pCmdUI->Enable(!m_bTestBegin);						//注释在书上5.2.2节
	
}

void CTypingTestView::OnUpdateScoreUnion(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bTestBegin&&theApp.m_lUserRight);		//注释在书上5.2.2节	
}

void CTypingTestView::OnUpdateScorePersonall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bTestBegin);		//注释在书上5.2.2节	
}

void CTypingTestView::OnChangeKey() 
{
	// TODO: Add your command handler code here
	CChangeKey ChKeyDlg;//注释在书上9.5.4节
	ChKeyDlg.DoModal();//注释在书上9.5.4节
	
}

void CTypingTestView::OnUpdateChangeKey(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bTestBegin);		//注释在书上5.2.2节	
}
void CTypingTestView::OnContextMenu(CWnd*, CPoint point)
{
	// CG: This block was added by the Pop-up Menu component
	{
	if (point.x == -1 && point.y == -1){
		//注释在书上5.2.2节
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);
		point = rect.TopLeft();
		point.Offset(5, 5);
	}
	//注释在书上5.2.2节
	CMenu menu;
	VERIFY(menu.LoadMenu(CG_IDR_POPUP_TYPING_TEST_VIEW));
	//注释在书上5.2.2节
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;
	//注释在书上5.2.2节
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
	//注释在书上5.2.2节
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
	 point.x, point.y,pWndPopupOwner);
	}
}
//注释在书上6.3.3节
void CTypingTestView::OnNoteMessage(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(strNoteMessage);//8.4.1更新在信息栏的提示信息
}
//注释在书上6.3.3节
void CTypingTestView::OnRight(CCmdUI *pCmdUI)
{
	CString str;					//注释在书上8.4.1节
	str.Format("%3d",inputRight);	//注释在书上8.4.1节
	pCmdUI->SetText(str);		//注释在书上8.4.1节

}
//注释在书上6.3.3节
void CTypingTestView::OnRightPercent(CCmdUI *pCmdUI)
{
	CString str1,str2("%");//注释在书上8.4.1节
	if(inputTotal==0)	//注释在书上8.4.1节
		str1="";	//注释在书上8.4.1节
	else
		str1.Format("%3d",inputRight*100/inputTotal);	//注释在书上8.4.1节
	pCmdUI->SetText(str1+str2);//注释在书上8.4.1节

}
//注释在书上6.3.3节
void CTypingTestView::OnWrong(CCmdUI *pCmdUI)
{
	CString str2;//注释在书上8.4.1节
	str2.Format("%3d",inputWrong); //注释在书上8.4.1节
	pCmdUI->SetText(str2); //注释在书上8.4.1节

}
//注释在书上6.3.3节
void CTypingTestView::OnSpeed(CCmdUI *pCmdUI)
{
	CString str3; //注释在书上8.4.1节
	if(m_lTestTime==0)str3="";	//注释在书上8.4.1节
	else
		str3.Format("%3d",inputRight*60/m_lTestTime);	//注释在书上8.4.1节
	pCmdUI->SetText(str3); //注释在书上8.4.1节

}
//注释在书上6.3.3节
void CTypingTestView::OnTestTime(CCmdUI *pCmdUI)
{
	CString str4; //8.4.1
	str4.Format("%2d:%2d",m_lTestTime/60,m_lTestTime%60); //8.4.1
	pCmdUI->SetText(str4); //注释在书上8.4.1节

}
//注释在书上6.3.3节
void CTypingTestView::OnTestFile(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(m_strTestFile);		//注释在书上7.2.4节
}
void CTypingTestView::LoadEnglisFile(LPCSTR strFileName)
{	
	//注释在书上7.1.3节
	srand((unsigned)time(NULL));		//注释在书上7.1.3节
	long uID=rand() % 10;				//注释在书上7.1.3节
	uID=uID*200;						//注释在书上7.1.3节
	//注释在书上7.1.3节
	int line,col;						//注释在书上7.1.3节
	//注释在书上7.1.3节
	for(line=0;line<12;line++)			 //注释在书上7.1.3节
	{
		for(col=0;col<82;col++) 		//注释在书上7.1.3节
		{
			m_OutBuf[line][col]=' ';	//注释在书上7.1.3节
			m_InBuf[line][col]=' ';		//注释在书上7.1.3节
		}	//注释在书上7.1.3节
	}//注释在书上7.1.3节

	try
	{
		openFileName.Open(strFileName,CFile::modeRead|CFile::shareDenyWrite);	//注释在书上7.1.3节
		openFileName.Seek(uID,CFile::begin);									//注释在书上7.1.3节
	}
	catch(CFileException *e)
	{
		AfxMessageBox(e->m_cause);
		return;
	}
	//注释在书上7.1.3节
	for(line=0;line<12;line++)	//注释在书上7.1.3节
	{
		for(col=0;col<82;col++)	//注释在书上7.1.3节
		{
			openFileName.Read(&m_OutBuf[line][col],1);					//注释在书上7.1.3节
			if(m_OutBuf[line][col]=='\r'||m_OutBuf[line][col]=='\n')	//注释在书上7.1.3节
			{
				m_OutBuf[line][col]=' ';								//注释在书上7.1.3节
				col--;													//注释在书上7.1.3节
			}
		}//注释在书上7.1.3节
		m_OutBuf[line][82]='\0';	//注释在书上7.1.3节
	}	//注释在书上7.1.3节
}
void CTypingTestView::DisplayEnglish(CDC *pDC)
{	
	//注释在书上7.2.2节
	CFont *pOldFont;									//注释在书上7.2.2节
	pOldFont=(CFont *)pDC->SelectObject(&startFont3);	//注释在书上7.2.2节
	pDC->GetTextMetrics(&tm);							//注释在书上7.2.2节
	height=tm.tmHeight+tm.tmExternalLeading+3;			//注释在书上7.2.2节
	width=tm.tmAveCharWidth;		//注释在书上7.2.2节
	for(int line=0;line<12;line++)	//注释在书上7.2.2节
	{
		for(int col=0;col<82;col++)	//注释在书上7.2.2节
		{
			pDC->TextOut(col*width,line*height*2,m_OutBuf[line][col]);	//注释在书上7.2.2节
			//注释在书上7.2.2节
			if(m_InBuf[line][col]!=' '||col-1>=0&&m_InBuf[line][col-1]!=' '&&m_InBuf[line][col]==' ')
				pDC->SetBkColor(RGB(0,255,0));//注释在书上7.2.2节
			pDC->TextOut(col*width,line*height*2+height-iInH,m_InBuf[line][col]);
			pDC->SetBkColor(RGB(255,255,255));//注释在书上7.2.2节
			//注释在书上7.2.2节
			//注释在书上7.2.2节
		}
	}
	
	//注释在书上8.2.4节
	for(line=0;line<=currentLine;line++)	//注释在书上8.2.4节
	{
		for(int col=0;col<82;col++)		//注释在书上8.2.4节
		{
			if((line==currentLine)&&(col==currentCol))//注释在书上8.2.4节
				break;							//注释在书上8.2.4节
			if(m_OutBuf[line][col]==m_InBuf[line][col])//注释在书上8.2.4节
			{
				pDC->SetBkColor(RGB(255,0,0));//注释在书上8.2.4节
				pDC->TextOut(col*width,line*height*2,m_OutBuf[line][col]);//注释在书上8.2.4节
				pDC->SetBkColor(RGB(255,255,255));//注释在书上8.2.4节
			}
			else //注释在书上8.2.4节
			{
				pDC->SetBkColor(RGB(0,0,255));//注释在书上8.2.4节
				pDC->TextOut(col*width,line*height*2,m_OutBuf[line][col]);//注释在书上8.2.4节
				pDC->SetBkColor(RGB(255,255,255));//注释在书上8.2.4节
			}
				
		}

		PosCaret.x=currentCol*width;//urrentCol*width+width;	//注释在书上8.2.4节
		PosCaret.y=currentLine*height*2+2*height-iInH;		//注释在书上8.2.4节
		SetCaretPos(PosCaret);			//注释在书上8.2.4节
		if(m_bTestBegin)ShowCaret();				//注释在书上8.2.4节
	} //注释在书上8.2.4节
	//注释在书上8.5.3节
	for(line=0;line<=currentLine;line++)	//注释在书上8.5.3节
	{
		for(int col=0;col<82;col++)	//注释在书上8.5.3节
		{
			if((line==currentLine)&&(col==currentCol))	//注释在书上8.5.3节
				break;	//注释在书上8.5.3节
			if(col%2==0)
			{
				strInCh=m_OutBuf[line][col];//注释在书上8.5.3节
				coli=col;//注释在书上8.5.3节
			}
			else //注释在书上8.5.3节
			{
				strInCh+=m_OutBuf[line][col];//注释在书上8.5.3节
				if(m_OutBuf[line][col]==m_InBuf[line][col])//注释在书上8.5.3节
				{
					pDC->SetBkColor(RGB(255,0,0));//注释在书上8.5.3节
					pDC->TextOut(coli*width,line*height*2,strInCh);//注释在书上8.5.3节
					//注释在书上8.5.3节
					pDC->SetBkColor(RGB(255,255,255));
				}
				else  //注释在书上8.5.3节
				{
					pDC->SetBkColor(RGB(0,255,0));//注释在书上8.5.3节
					pDC->TextOut(coli*width,line*height*2,strInCh);//注释在书上8.5.3节
					//注释在书上8.5.3节
					pDC->SetBkColor(RGB(255,255,255));
				}
			}
		}//注释在书上8.5.3节
	}//注释在书上8.5.3节

	pDC->SelectObject(pOldFont);		//注释在书上7.2.2节
	//注释在书上7.2.2节
}
void CTypingTestView::DisplayChinese(CDC *pDC)
{    
	//注释在书上7.3.2节
	CFont *pOldFont;									//注释在书上7.3.2节
	pOldFont=(CFont *)pDC->SelectObject(&startFont3);	//注释在书上7.3.2节
	pDC->GetTextMetrics(&tm);							//注释在书上7.3.2节
	height=tm.tmHeight+tm.tmExternalLeading+3;			//注释在书上7.3.2节
	width=tm.tmAveCharWidth;							//注释在书上7.3.2节
	for(int line=0;line<12;line++)				//注释在书上7.3.2节
	{
		for(int col=0;col<82;col++)				//注释在书上7.3.2节
		{
			if(col%2==0)						//注释在书上7.3.2节
			{   
				strInCh=m_InBuf[line][col];		// 注释在书上7.3.2节
				strOutCh=m_OutBuf[line][col];	//注释在书上7.3.2节
			     coli=col;						//注释在书上7.3.2节
			}
			else				//注释在书上7.3.2节
			{	
				strInCh+=m_InBuf[line][col];		//注释在书上7.3.2节
				strOutCh+=m_OutBuf[line][col];		//注释在书上7.3.2节
				//注释在书上7.3.2节
				pDC->TextOut(coli*width,line*height*2,strOutCh);	//注释在书上7.3.2节
				//注释在书上7.3.2节
				if(m_InBuf[line][col]!=' '||col-1>=0&&m_InBuf[line][col-1]!=' '&&m_InBuf[line][col]==' ')
				pDC->SetBkColor(RGB(0,255,0));		//注释在书上7.3.2节
				pDC->TextOut(coli*width,line*height*2+height- iInH,strInCh);	//注释在书上7.3.2节
				pDC->SetBkColor(RGB(255,255,255));		//注释在书上7.3.2节
			}
		}
	}

	pDC->SelectObject(pOldFont);	//注释在书上7.3.2节
	//注释在书上7.3.2节
}
void CTypingTestView::TestEnd()
{

	m_bTestBegin=FALSE;		//注释在书上8.1.2节
	m_bTestRead=FALSE;		//注释在书上8.1.2节
	KillTimer(2);			//注释在书上8.1.2节


	CString strTestScore;		//注释在书上8.1.2节
	strTestScore.Format("此次测试成绩为：%d个字符/分钟",inputRight*60/m_lTestTime);//注释在书上8.1.2节
	strNoteMessage="就绪";
	if(MessageBox(strTestScore,"打字测试系统",MB_YESNO)==IDNO)
	{   	
		Invalidate();	//注释在书上8.1.2节
		return;
	}
	Invalidate();			//注释在书上8.1.2节
	_variant_t vUserId,vTestDate,vSpeed,vRight,vWrong;
	_variant_t vPercent,vTestTime,vTestFile,vEndTestTime;
	//注释在书上8.1.2节
	_RecordsetPtr m_pRecordset; CString m_strSql;
	m_strSql="SELECT * FROM score";
	//注释在书上8.1.2节
	m_pRecordset.CreateInstance("ADODB.Recordset");
	//注释在书上8.1.2节
	try
	{
		m_pRecordset->Open((_variant_t)m_strSql,
			_variant_t((IDispatch *)theApp.m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);//注释在书上8.1.2节
	}
	catch(_com_error e)///注释在书上8.1.2节
	{
		AfxMessageBox("读取数据库失败!");//注释在书上8.1.2节
	}
	
//	AfxMessageBox("增sdafd加记录成功!");//111注释在书上8.1.2节

	//注释在书上8.1.2节

	m_pRecordset->AddNew();//注释在书上8.1.2节：
	//	AfxMessageBox("增加记录成功!");//222注释在书上8.1.2节

	if(!m_pRecordset->adoEOF )
	{
		vUserId = theApp.m_strUserID;		//注释在书上8.1.2节
		vTestDate=theApp.m_strDate;			//注释在书上8.1.2节
		if(m_lTestTime==0.0)m_lTestTime=1;	//注释在书上8.1.2节
		vSpeed =inputTotal*60/m_lTestTime;	//注释在书上8.1.2节
		vRight = inputRight;				//注释在书上8.1.2节
		vWrong = inputWrong;				//注释在书上8.1.2节
		vPercent= inputRight*100/inputTotal;	//注释在书上8.1.2节
		vEndTestTime=((CMainFrame *)AfxGetMainWnd())->m_strTime;//注释在书上8.1.2节
		vTestFile=m_strTestFile;			//注释在书上8.1.2节
		vTestTime=m_lTestTime;				//注释在书上8.1.2节
		//注释在书上8.1.2节：
		m_pRecordset->PutCollect("UserId",vUserId);		//注释在书上8.1.2节
		m_pRecordset->PutCollect("TestDate",vTestDate);	//注释在书上8.1.2节

		m_pRecordset->PutCollect("Speed",vSpeed);			//注释在书上8.1.2节
		m_pRecordset->PutCollect("Right",vRight);			//注释在书上8.1.2节
		m_pRecordset->PutCollect("Wrong",vWrong);			//注释在书上8.1.2节
		m_pRecordset->PutCollect("Percent",vPercent);		//注释在书上8.1.2节
		m_pRecordset->PutCollect("TestTime",vTestTime);	//注释在书上8.1.2节
		m_pRecordset->PutCollect("TestFile",vTestFile);	//注释在书上8.1.2节
		m_pRecordset->PutCollect("EndTestTime",vEndTestTime);//注释在书上8.1.2节
		m_pRecordset->Update();		//注释在书上8.1.2节
	}
	//注释在书上8.1.2节
	//注释在书上8.1.2节
	m_pRecordset->Close();//注释在书上8.1.2节、
	((CMainFrame *)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(0,"就绪");//注释在书上8.1.2节
}
//注释在书上8.1.2节

//注释在书上8.2.3节
void CTypingTestView::OnCharEnglish(UINT nChar)
{
	CTypingTestDoc* pDoc = GetDocument();	//8.2.3访问文档类的成员
	CreateSolidCaret(width,2);				//8.2.3创建插入符
	ShowCaret();							//8.2.3显示插入符
	if(!m_bTestRead)return;					//8.2.3如测试准备好为假，即没单击英文测试就返回
	CClientDC dc(this);						//8.2.3定义客户区的设备环境句柄
	dc.SelectObject(&startFont3);				//8.2.3选择自定义字体3
	if(nChar==VK_RETURN)				//8.2.3按回车键
		return;						//8.2.3返回，即对回车不作处理
	if(nChar==VK_ESCAPE)				//8.2.3如果是ESC键则提示是否退出练习，中途结束
	{
		if(MessageBox("确定要结束测试吗?","提示!",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
		{	//8.2.3如在提示对话框，单击了确定，后作结束处理
			TestEnd();						//8.2.3结束测试,调用结束处理函数 
			HideCaret(); 					//8.2.3 测试结束，不需要输入提示，故隐藏插入光标
			return;//返回
		}
		else
			return;						//8.2.3如在提示对话框单击了取消息，就返回
	}

	if(nChar==VK_BACK)			//8.2.3如果是输入的是退格键则清除前一字符
	{
        MessageBox("不能修改错误!");
		return;
	}
/*
	{
		if(currentCol!=0)			//8.2.3当前光标不在最左边则清除前一字符
		{
			currentCol--;			//8.2.3下标减一,使其变为前一字符
			inputTotal--;			//8.2.3输入字符总数减一
			if(m_InBuf[currentLine][currentCol]==m_OutBuf[currentLine][currentCol])
				inputRight--;		// 8.2.3输入对的总数减一
			else
				inputWrong--;		//8.2.3输入错的总数减一
			m_InBuf[currentLine][currentCol]=' ';	//8.2.3将输入数组的那个元素清空
			dc.TextOut(currentCol*width,currentLine*height*2+height 
				-iInH,m_InBuf[currentLine][currentCol]);	
			//8.2.3在屏幕上擦除输入的前一字符
			dc.TextOut(coli*width-width,currentLine*height*2+height-iInH,"  ");
			PosCaret.x=currentCol*width;//urrentCol*width+width;	//8.2.3设置插入符新的x坐标
			PosCaret.y=currentLine*height*2+2*height-iInH;		//8.2.3设置插入符新的y坐标
			SetCaretPos(PosCaret);			//8.2.3设置插入符新的位置
			ShowCaret();					//8.2.3在新的位置显示插入符
			dc.SetBkColor(RGB(255,255,255));//8.2.3设置背景色为白色
			dc.TextOut(currentCol*width,currentLine*height*2,m_OutBuf[currentLine][currentCol]);
			//输出当前光标所在的行和列的范文
			
			return;
		}
		else			//在每行最左边则响铃
		
		{
			if(currentLine>0){
				currentLine--;
				//currentLine--;

				currentCol=81;	//8.2.3换行后，当前标位置列设置为0
				m_InBuf[currentLine][currentCol]=' ';	//8.2.3将输入数组的那个元素清空
				dc.SetBkColor(RGB(255,255,255));		//8.2.3恢复背景色为白色

			    dc.TextOut(currentCol*width,currentLine*height*2,m_OutBuf[currentLine][currentCol]);
				dc.TextOut(currentCol*width,currentLine*height*2+height-iInH,"  ");

				PosCaret.x=currentCol*width;//urrentCol*width+width;	//8.2.3设置插入符新的x坐标
				PosCaret.y=currentLine*height*2-2*height-iInH; //8.2.3设置插入符新的y坐标
				SetCaretPos(PosCaret); //8.2.3设置插入符新的位置
//							char out[13];
//			sprintf(out,"first:%c",m_InBuf[currentLine][currentCol]);
//			MessageBox(out);
		}

			return;
		}
	}
	*/
  if((!bLastKeyIsBlank) && m_OutBuf[currentLine][currentCol]==VK_SPACE)  //上次输入的字符不是空格,这次输入的是空格,单词输入完记数
	{
	     inputTotal++;				//输入的单词总数加一
		 if(bWordIsTrue)inputRight++;	
		 else inputWrong++;
		 bWordIsTrue=FALSE;
		 bWordCount=FALSE;
		 bLastKeyIsBlank=TRUE;
	}
	if(bLastKeyIsBlank && !(m_OutBuf[currentLine][currentCol]==VK_SPACE))  //上次输入的是空格,这次输入的不是空格,单词记数开始.
	{

		bWordCount=TRUE;		//单词对错检查开始
		bWordIsTrue=TRUE;		//输入的是单词是对的
		bLastKeyIsBlank=FALSE;

		//单词记数开始
	}

	m_InBuf[currentLine][currentCol]=(char)nChar;//将接收到的字符（输入的字符）保存到输入数组元数中
	dc.SetBkColor(RGB(0,255,0));//输入字符的背景色为绿色
	dc.TextOut(currentCol*width,currentLine*height*2+height,m_InBuf[currentLine][currentCol]);//输出输入的字符
	PosCaret.x=currentCol*width+width; //8.2.3设置插入符新的x坐标
	PosCaret.y=currentLine*height*2+2*height-iInH; //8.4.3设置插入符新的y坐标


	if(m_InBuf[currentLine][currentCol]==m_OutBuf[currentLine][currentCol])//8.2.3如输入的字符和范文是一样的
	{	
		
		//inputRight++;						//8.2.3输入字符是正角的,则输入字符对的总数加一
		dc.SetBkColor(RGB(255,0,0));			//8.2.3设置背景色为红色
		dc.TextOut(currentCol*width,currentLine*height*2,m_OutBuf[currentLine][currentCol]);//8.2.3输出范范文
		dc.SetBkColor(RGB(255,255,255));		//8.2.3恢复背景色为白色
	}
	else
	{
		if(bWordIsTrue)bWordIsTrue=FALSE;
		//inputWrong++;			//8.2.3否则错的总数加一
		if(bWordIsTrue) bWordIsTrue=FALSE;
		dc.SetBkColor(RGB(0,0,255));//2.3.3设置背景色为绿色
		dc.TextOut(currentCol*width,currentLine*height*2,m_OutBuf[currentLine][currentCol]);//8.2.3输出范文
		dc.SetBkColor(RGB(255,255,255));//8.3.3恢复背景色
	}
	currentCol++;//8.2.3当前光标位置列加一

  

	

	if(currentCol>=82)		//8.2.3到最右边自动换行
	{
		dc.TextOut(currentCol*width+1,currentLine*height*2+height," ");//8.2.3一行最后输出一个空格
		currentLine++;	//8.2.3当前光标位置行加一
		if(currentLine==12)
		{
			TestEnd();	//8.2.3一页输完，结束测试,并作结束处理，正常结束出
			HideCaret(); 					//8.2.3 测试结束，不需要输入提示，故隐藏插入光标
		}
		currentCol=0;	//8.2.3换行后，当前标位置列设置为0
		PosCaret.x=0;	//8.2.3设置插入符新的x坐标
		PosCaret.y=currentLine*height*2+2*height-iInH; //8.2.3设置插入符新的y坐标
	 }
	SetCaretPos(PosCaret); //8.2.3设置插入符新的位置

}
//注释在书上8.2.3节

void CTypingTestView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bTestEnglish)				//注释在书上8.4.2节
		CreateSolidCaret(width,2);		//注释在书上8.4.2节
	else						//注释在书上8.4.2节
		CreateSolidCaret(2*width,2);	//注释在书上8.4.2节
	if(!m_bTestRead)return;	//注释在书上8.4.2节
	CClientDC dc(this); //注释在书上8.4.2节
	  dc.SelectObject(&startFont3);//注释在书上8.4.2节

	if(m_bTestBegin)				//注释在书上8.4.2节
	{
		if(m_bTestEnglish)			//注释在书上8.4.2节
			OnCharEnglish(nChar);
		else 
			OnCharChinese(nChar);	//8.5.4否则接收汉字输入，注：在8.5节前应将其注释掉。
	}
	else 						//注释在书上8.4.2节
	{
		if(nChar==VK_SPACE)		//注释在书上8.4.2节
		{
			strNoteMessage="测试在进行中，按ESC键终止。";		//注释在书上8.4.2节
			((CMainFrame *)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(0,"测试在进行中，按ESC键终止。");
			SetTimer(2,1000,NULL);			//注释在书上8.4.2节
			m_bTestBegin=TRUE;			//注释在书上8.4.2节
			PosCaret.x=0;					//注释在书上8.4.2节
			PosCaret.y=2*height-iInH;			//注释在书上8.4.2节
			ShowCaret();		//注释在书上8.4.2节
			SetCaretPos(PosCaret);	//注释在书上8.4.2节
		}
		else			//注释在书上8.4.2节
			MessageBox("准备就绪,按空格键开始计时!","提示",MB_OK|MB_ICONINFORMATION);
	}
	//注释在书上8.4.2节
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CTypingTestView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_lTestTime++;//8.4.1测试时间加1秒
	CView::OnTimer(nIDEvent);
}
//注释在书上8.5.2节
void CTypingTestView::OnCharChinese(UINT nChar)
{
	CreateSolidCaret(2*width,2);	//注释在书上8.5.2节
	ShowCaret();				//注释在书上8.5.2节

	if(nChar<=127)	//注释在书上8.5.2节
	{	
		if(nChar==VK_ESCAPE||nChar==VK_BACK);//注释在书上8.5.2节
	    else return;//注释在书上8.5.2节
	}
	
	if(!m_bTestRead)return;	//注释在书上8.5.2节
	CClientDC dc(this);	//注释在书上8.5.2节
	dc. SelectObject(&startFont3);	//注释在书上8.5.2节
	if(nChar==VK_RETURN)	//注释在书上8.5.2节
			return;
	if(nChar==VK_ESCAPE)	//注释在书上8.5.2节
	{
		if(MessageBox("确定要结束练习吗?","提示!",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
		{
			TestEnd();		//注释在书上8.5.2节
			HideCaret(); 	//注释在书上8.5.2节
			return;
		}
		else		//注释在书上8.5.2节
			return;
	}
	
	if(nChar==VK_BACK)				//注释在书上8.5.2节
	{
		HideCaret();				//注释在书上8.5.2节
		if(currentCol!=0)			//注释在书上8.5.2节
		{

			currentCol--;			//注释在书上8.5.2节
			coli=currentCol;			//注释在书上8.5.2节
			currentCol--;			//注释在书上8.5.2节
			inputTotal--;			//注释在书上8.5.2节
			if(m_InBuf[currentLine][currentCol]==m_OutBuf[currentLine][currentCol])
				inputRight--;		// 注释在书上8.5.2节
			else
			    inputWrong--;		//注释在书上8.5.2节
			m_InBuf[currentLine][coli]=' ';//注释在书上8.5.2节
			m_InBuf[currentLine][currentCol]=' ';//注释在书上8.5.2节

			dc.TextOut(currentCol*width,currentLine*height*2+height,m_InBuf[currentLine][currentCol]);	
										//注释在书上8.5.2节
			dc.TextOut(coli*width,currentLine*height*2+height,m_InBuf[currentLine][coli]);	
										//注释在书上8.5.2节
			PosCaret.x=currentCol*width;	//注释在书上8.5.2节
			PosCaret.y=currentLine*height*2+2*height-iInH;		//注释在书上8.5.2节
			SetCaretPos(PosCaret);			//注释在书上8.5.2节
			ShowCaret();					//注释在书上8.5.2节
			dc.SetTextColor(RGB(0,0,0));//注释在书上8.5.2节
			strInCh=m_OutBuf[currentLine][currentCol];//注释在书上8.5.2节
			strInCh+=m_OutBuf[currentLine][coli];//注释在书上8.5.2节
			dc.TextOut(currentCol*width,currentLine*height*2,strInCh);//注释在书上8.5.2节
			return;	//注释在书上8.5.2节
		}
		else						//注释在书上8.5.2节
		{
			MessageBeep(-1);		//响铃
			return;
		}
	}
	if(byte1==0)//注释在书上8.5.2节
	{
		coli=currentCol;//注释在书上8.5.2节
		m_InBuf[currentLine][currentCol]=(char)nChar;//注释在书上8.5.2节
		strInCh=(char)nChar;//注释在书上8.5.2节
		byte1++;//注释在书上8.5.2节
	}
	else //注释在书上8.5.2节
	{
		m_InBuf[currentLine][currentCol]=(char)nChar;// 注释在书上8.5.2节
		strInCh+=(char)nChar;// 注释在书上8.5.2节
		dc.SetBkColor(RGB(0,255,0));//注释在书上8.5.2节
		dc.TextOut(coli*width,currentLine*height*2+height-iInH,strInCh);//注释在书上8.5.2节
		PosCaret.x=currentCol*width+width; //注释在书上8.5.2节
		PosCaret.y=currentLine*height*2+2*height-iInH; //注释在书上8.5.2节

		byte1=0;//注释在书上8.5.2节
		inputTotal++;				//注释在书上8.5.2节

		strOutCh=m_OutBuf[currentLine][currentCol-1];//注释在书上8.5.2节
		strOutCh+=m_OutBuf[currentLine][currentCol];//注释在书上8.5.2节

		if(m_InBuf[currentLine][currentCol]==m_OutBuf[currentLine][currentCol])//注释在书上8.5.2节
		{
		    inputRight++;						//注释在书上8.5.2节
			dc.SetBkColor(RGB(255,0,0));			//注释在书上8.5.2节
		    dc.TextOut((currentCol-1)*width,currentLine*height*2,strOutCh);	//注释在书上8.5.2节
			dc.SetBkColor(RGB(255,255,255));		//注释在书上8.5.2节
		}
	    else						//注释在书上8.5.2节
		{
		    inputWrong++;			//注释在书上8.5.2节
			dc.SetBkColor(RGB(0,255,0));	//注释在书上8.5.2节
		    dc.TextOut((currentCol-1)*width,currentLine*height*2,strOutCh);	//注释在书上8.5.2节
			dc.SetBkColor(RGB(255,255,255));		//注释在书上8.5.2节

		}
	}
	currentCol++;//注释在书上8.5.2节
	if(currentCol==82)		//注释在书上8.5.2节
	{
		dc.TextOut(currentCol*width+1,currentLine*height*2+height," ");//注释在书上8.5.2节
		currentLine++;//注释在书上8.5.2节
		if(currentLine==14)
		{
			TestEnd();		//注释在书上8.5.2节
			HideCaret(); 	//注释在书上8.5.2节
		}
		currentCol=0;//注释在书上8.5.2节
		PosCaret.x=0;	//注释在书上8.5.2节
		PosCaret.y=currentLine*height*2+2*height-iInH; //注释在书上8.5.2节
	}
	SetCaretPos(PosCaret);//注释在书上8.5.2节
}
//注释在书上8.5.2节

void CTypingTestView::OnHelpFinder() 
{
	// TODO: Add your command handler code here
	// 注释在书上10.7节 
	char exeFullPath[MAX_PATH];		//注释在书上10.7节 
	CString strPath;					//注释在书上10.7节 
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);	//注释在书上10.7节 
	strPath = CString(exeFullPath);		//注释在书上10.7节 
	strPath = strPath.Left(strPath.ReverseFind('\\'));		//注释在书上10.7节 
	strPath += "\\TypingTest.chm";					//注释在书上10.7节 
	char cCommandLine[MAX_PATH];				//注释在书上10.7节 
	::strcpy(cCommandLine, strPath);				//注释在书上10.7节 
	// 注释在书上10.7节 
	HtmlHelp(GetSafeHwnd(), cCommandLine, HH_DISPLAY_TOPIC, 0);	//注释在书上10.7节 
	
}
