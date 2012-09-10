// TypingTestView.cpp : implementation of the CTypingTestView class
//

#include "stdafx.h"
#include "TypingTest.h"

#include "TypingTestDoc.h"
#include "TypingTestView.h"

#include "MainFrm.h"  //ע��������7.1.4��
#include "CreateNewUser.h"  		//ע��������9.2��
#include "DeleteUser.h"  //ע��������9.3.4��
#include "FindScore.h"  //ע��������9.4.4��
#include "ChangeKey.h"  //ע��������9.5.4��
#include "LoginDlg.h"	//ע��������9.6��
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
	ON_UPDATE_COMMAND_UI(IDC_RIGHT, OnRight)				//ע��������6.3.3��
	ON_UPDATE_COMMAND_UI(IDC_WRONG, OnWrong)				//ע��������6.3.3��
	ON_UPDATE_COMMAND_UI(IDC_RIGHT_PERCENT, OnRightPercent)	//ע��������6.3.3��
	ON_UPDATE_COMMAND_UI(IDC_TEST_TIME, OnTestTime)			//ע��������6.3.3��
	ON_UPDATE_COMMAND_UI(IDC_TEST_FILE, OnTestFile)			//ע��������6.3.3��
	ON_UPDATE_COMMAND_UI(IDC_SPEED, OnSpeed)				//ע��������6.3.3��
	ON_UPDATE_COMMAND_UI(ID_SEPARATOR, OnNoteMessage)		//ע��������6.3.3��

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTypingTestView construction/destruction

CTypingTestView::CTypingTestView()
{
	// TODO: add construction code here
	//ע��������3.1.2��
	if(!(startFont1.CreateFont(50,			//1.ע��������3.1.2�� 
		0,							//2.ע��������3.1.2��
		0,							//3.ע��������3.1.2��
		0,							//4.ע��������3.1.2��
		FW_BOLD,					//5.ע��������3.1.2��
		0,							//6.ע��������3.1.2��
		1,							//7.ע��������3.1.2��
		0,							//8.ע��������3.1.2��
		ANSI_CHARSET,				//9.���������ַ���
		OUT_DEFAULT_PRECIS,			//10.ע��������3.1.2��
		CLIP_DEFAULT_PRECIS,		//11.ע��������3.1.2��
		DEFAULT_QUALITY,			//12.ע��������3.1.2��
		FIXED_PITCH,				//13.ע��������3.1.2��
		"new Font1")))				//14.ע��������3.1.2��
	{	//ע��������3.1.2��
		startFont1.CreateStockObject(SYSTEM_FIXED_FONT);//ע��������3.1.2��
	}
	if(!(startFont2.CreateFont(33,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,//ע��������3.1.2��
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FIXED_PITCH,
		"new Font2")))	//ע��������3.1.2��
	{
		startFont2.CreateStockObject(SYSTEM_FIXED_FONT); //ע��������3.1.2��
	}
	if(!(startFont3.CreateFont(22,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,		//ע��������3.1.2��
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FIXED_PITCH,
		"new Font3")))
	{
		startFont3.CreateStockObject(SYSTEM_FIXED_FONT); //ע��������3.1.2��
	}
	m_bTestRead=FALSE;			//ע��������3.1.2��
	//ע��������3.1.2��
	m_bTestBegin=FALSE;			//ע��������5.2.2��
	m_bTestEnglish=FALSE;		//ע��������5.2.2��
	
	iInH=4;				//ע��������7.1.2��
    currentLine=0;		//ע��������7.1.2��
	currentCol=0;		//ע��������7.1.2��
	strcpy(m_strTestFile,"");//ע��������7.1.2��
	inputRight=inputWrong=inputTotal=0;		//ע��������8.2.1��
	m_lTestTime=0;							//ע��������8.2.1��
	byte1=0;								//ע��������8.2.1��

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
	//ע��������3.1.2��
	if(m_bTestRead) //ע��������3.1.2��
	{
		if(m_bTestEnglish)DisplayEnglish(pDC);//ע��������7.3.3��
		else DisplayChinese(pDC);			//ע��������7.3.3��
	}
	else 
	   DisplayState(pDC);//ע��������3.1.2��

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
	//ע��������3.1.2��
	CTypingTestDoc* pDoc = GetDocument();	//ע��������3.1.2��
	CFont *pStartOldFont;					//ע��������3.1.2��
	CRect rect;								//ע��������3.1.2��
	GetClientRect(&rect);					//ע��������3.1.2��
	pStartOldFont=(CFont *)pDC->SelectObject(&startFont1);	//ע��������3.1.2��
	pDC->SetTextAlign(TA_CENTER);							//ע��������3.1.2��
	pDC->SetTextColor(RGB(255,0,0));						//ע��������3.1.2��
	pDC->TextOut(rect.right/2,50,pDoc->m_strMessage1);		//ע��������3.1.2��
	pDC->SelectObject(&startFont2);							//ע��������3.1.2��
	pDC->TextOut(rect.right/2,110,pDoc->m_strMessage2); 	//ע��������3.1.2��

	pDC->SetTextColor(RGB(0,0,255));						//ע��������3.1.2��
	pDC->SetTextAlign(TA_LEFT);								//ע��������3.1.2��
	pDC->TextOut(5,175,pDoc->m_strMessage3);				//ע��������3.1.2��
	pDC->TextOut(5,175+50,pDoc->m_strMessage4);				//ע��������3.1.2��
	pDC->TextOut(5,175+100,pDoc->m_strMessage5);			//ע��������3.1.2��
	pDC->TextOut(5,175+150,pDoc->m_strMessage6);			//ע��������3.1.2��
	pDC->TextOut(5,175+200,pDoc->m_strMessage7);			//ע��������3.1.2��
	pDC->TextOut(5,175+250,pDoc->m_strMessage8);			//ע��������3.1.2��

	pDC->TextOut(rect.right/3+100,500,pDoc->m_strMessage9);		//ע��������3.1.2��
	pDC->TextOut(rect.right/3+100,500+30,pDoc->m_strMessage10);	//ע��������3.1.2��

	CPen pen(PS_SOLID,5,RGB(255,0,0));				//ע��������3.1.2��
	CPen *pOldPen;									//ע��������3.1.2��
	pOldPen=pDC->SelectObject(&pen);				//ע��������3.1.2��
	pDC->MoveTo(10,150);							//ע��������3.1.2��
	pDC->LineTo(rect.right-10,150);					//ע��������3.1.2��
	pDC->MoveTo(10,500-10);							//ע��������3.1.2��
	pDC->LineTo(rect.right-10,500-10);				//ע��������3.1.2��

	pDC->SelectObject(pStartOldFont);				//ע��������3.1.2��
	pDC->SelectObject(pOldPen);						//ע��������3.1.2��
	pDC->SetTextColor(RGB(0,0,0));					//ע��������3.1.2��
	pDC->SetTextAlign(TA_LEFT);						//ע��������3.1.2��
	//ע��������3.1.2��

}

void CTypingTestView::OnTestEnglish() 
{
	// TODO: Add your command handler code here
	m_bTestBegin=FALSE; 		//ע��������8.4.2��
	m_bTestRead=TRUE;			//ע��������5.2.2��
	m_bTestEnglish=TRUE;		//ע��������5.2.2��
	inputRight=inputWrong=inputTotal=0;	//ע��������7.1.4��
	currentLine=currentCol=0;			//ע��������7.1.4��
	m_lTestTime=0;						//ע��������7.1.4��

	strcpy(m_strTestFile,"English.txt");
	LoadEnglisFile(m_strTestFile);			//ע��������7.1.4�ڡ�
	((CMainFrame *)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(0,"Ӣ�Ĵ��ֲ���׼�����������ո����ʼ���ԡ�");		//ע��������7.1.4��
	Invalidate();						//ע��������7.1.4�ڡ�	
	
}

void CTypingTestView::OnTestChinese() 
{
	// TODO: Add your command handler code here
	m_bTestRead=TRUE;		//ע��������5.2.2��
    m_bTestEnglish=FALSE;		//ע��������5.2.2��
	m_bTestBegin=FALSE;		//ע��������5.2.2��
	inputRight=inputWrong=inputTotal=0;	//7.3.3�����:��,��,�ܹ�����Ŀ
	currentLine=currentCol=0;	//ע��������7.3.3��
	m_lTestTime=0;				//ע��������7.3.3��
	strNoteMessage="׼�����������ո����ʼ���ԡ�";//ע��������7.3.3��
	strcpy(m_strTestFile,"Chinese.txt");//ע��������7.3.3��
	LoadEnglisFile(m_strTestFile);		///ע��������7.3.3�ڡ�
	((CMainFrame *)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(0,strNoteMessage);
	Invalidate();					//ע��������7.3.3�ڡ�
	
}

void CTypingTestView::OnScoreUnion() 
{
	// TODO: Add your command handler code here
	//ע��������9.4.4��
	CFindScore *Dlg=new CFindScore(this);	//ע��������9.4.4��
	Dlg->m_strCaption ="�����û��ɼ�";		//ע��������9.4.4��

	Dlg->m_bFindAll=TRUE;				//ע��������9.4.4��
	Dlg->Create(IDD_DIALOG_FINDSCORE);	//ע��������9.4.4��
	Dlg->ShowWindow(SW_SHOW);				//ע��������9.4.4��
	
}

void CTypingTestView::OnScorePersonall() 
{
	// TODO: Add your command handler code here
	//ע��������9.4.4��
	CFindScore *Dlg=new CFindScore(this);			//ע��������9.4.4��
	CString temp="�Ĳ��Գɼ�";					//ע��������9.4.4��
	Dlg->m_strCaption =theApp.m_strUserName+temp;	//ע��������9.4.4��
	Dlg->m_bFindAll=FALSE;					//ע��������9.4.4��
	Dlg->Create(IDD_DIALOG_FINDSCORE);	//ע��������9.4.4��
	Dlg->ShowWindow(SW_SHOW);				//ע��������9.4.4��
	
}

void CTypingTestView::OnTestStop() 
{
	// TODO: Add your command handler code here
	HideCaret();	//ע��������8.3.2��
	TestEnd();		//ע��������8.3.2�ڡ�
}

void CTypingTestView::OnUserCreate() 
{
	// TODO: Add your command handler code here
	//ע��������9.2��
	CCreateNewUser NewUserDlg;				//ע��������9.2��
	NewUserDlg.m_strCaption="���������û�";  //ע��������9.2��
	NewUserDlg.DoModal();					//ע��������9.2��
	
}

void CTypingTestView::OnUserDel() 
{
	// TODO: Add your command handler code here
	//ע��������9.3.4��
	CDeleteUser DelUserDlg;		//ע��������9.3.4��
	DelUserDlg.DoModal();		//ע��������9.3.4��
	
}

void CTypingTestView::OnUserLogout() 
{
	// TODO: Add your command handler code here
	//ע��������9.6��
	
	CLoginDlg LoginDlg;
	if (LoginDlg.DoModal()==IDOK)
	{
		theApp.m_lUserRight=LoginDlg.m_lUserRight;			//ע��������9.6��
		 theApp.m_strUserName=LoginDlg.m_strUserName;		//ע��������9.6��
		 theApp.m_strUserID=LoginDlg.m_strUserID;			//ע��������9.6��
	}
	else
	{
    	return ;//9.6
	}
	//ע��������9.6��
	
}

void CTypingTestView::OnUpdateUserLogout(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bTestBegin);		//ע��������5.2.2��	
}

void CTypingTestView::OnUpdateUserDel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bTestBegin&&theApp.m_lUserRight);		//ע��������5.2.2��	
}

void CTypingTestView::OnUpdateUserCreate(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bTestBegin&&theApp.m_lUserRight);		//ע��������5.2.2��	
}

void CTypingTestView::OnUpdateTestStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_bTestBegin);	//ע��������5.2.2��	
}

void CTypingTestView::OnUpdateTestEnglish(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bTestRead&&m_bTestEnglish);	//ע��������5.2.2��
	pCmdUI->Enable(!m_bTestBegin);					//ע��������5.2.2��
	
}

void CTypingTestView::OnUpdateTestChinese(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bTestRead&&!m_bTestEnglish);		//ע��������5.2.2��
	pCmdUI->Enable(!m_bTestBegin);						//ע��������5.2.2��
	
}

void CTypingTestView::OnUpdateScoreUnion(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bTestBegin&&theApp.m_lUserRight);		//ע��������5.2.2��	
}

void CTypingTestView::OnUpdateScorePersonall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bTestBegin);		//ע��������5.2.2��	
}

void CTypingTestView::OnChangeKey() 
{
	// TODO: Add your command handler code here
	CChangeKey ChKeyDlg;//ע��������9.5.4��
	ChKeyDlg.DoModal();//ע��������9.5.4��
	
}

void CTypingTestView::OnUpdateChangeKey(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bTestBegin);		//ע��������5.2.2��	
}
void CTypingTestView::OnContextMenu(CWnd*, CPoint point)
{
	// CG: This block was added by the Pop-up Menu component
	{
	if (point.x == -1 && point.y == -1){
		//ע��������5.2.2��
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);
		point = rect.TopLeft();
		point.Offset(5, 5);
	}
	//ע��������5.2.2��
	CMenu menu;
	VERIFY(menu.LoadMenu(CG_IDR_POPUP_TYPING_TEST_VIEW));
	//ע��������5.2.2��
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;
	//ע��������5.2.2��
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
	//ע��������5.2.2��
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
	 point.x, point.y,pWndPopupOwner);
	}
}
//ע��������6.3.3��
void CTypingTestView::OnNoteMessage(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(strNoteMessage);//8.4.1��������Ϣ������ʾ��Ϣ
}
//ע��������6.3.3��
void CTypingTestView::OnRight(CCmdUI *pCmdUI)
{
	CString str;					//ע��������8.4.1��
	str.Format("%3d",inputRight);	//ע��������8.4.1��
	pCmdUI->SetText(str);		//ע��������8.4.1��

}
//ע��������6.3.3��
void CTypingTestView::OnRightPercent(CCmdUI *pCmdUI)
{
	CString str1,str2("%");//ע��������8.4.1��
	if(inputTotal==0)	//ע��������8.4.1��
		str1="";	//ע��������8.4.1��
	else
		str1.Format("%3d",inputRight*100/inputTotal);	//ע��������8.4.1��
	pCmdUI->SetText(str1+str2);//ע��������8.4.1��

}
//ע��������6.3.3��
void CTypingTestView::OnWrong(CCmdUI *pCmdUI)
{
	CString str2;//ע��������8.4.1��
	str2.Format("%3d",inputWrong); //ע��������8.4.1��
	pCmdUI->SetText(str2); //ע��������8.4.1��

}
//ע��������6.3.3��
void CTypingTestView::OnSpeed(CCmdUI *pCmdUI)
{
	CString str3; //ע��������8.4.1��
	if(m_lTestTime==0)str3="";	//ע��������8.4.1��
	else
		str3.Format("%3d",inputRight*60/m_lTestTime);	//ע��������8.4.1��
	pCmdUI->SetText(str3); //ע��������8.4.1��

}
//ע��������6.3.3��
void CTypingTestView::OnTestTime(CCmdUI *pCmdUI)
{
	CString str4; //8.4.1
	str4.Format("%2d:%2d",m_lTestTime/60,m_lTestTime%60); //8.4.1
	pCmdUI->SetText(str4); //ע��������8.4.1��

}
//ע��������6.3.3��
void CTypingTestView::OnTestFile(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(m_strTestFile);		//ע��������7.2.4��
}
void CTypingTestView::LoadEnglisFile(LPCSTR strFileName)
{	
	//ע��������7.1.3��
	srand((unsigned)time(NULL));		//ע��������7.1.3��
	long uID=rand() % 10;				//ע��������7.1.3��
	uID=uID*200;						//ע��������7.1.3��
	//ע��������7.1.3��
	int line,col;						//ע��������7.1.3��
	//ע��������7.1.3��
	for(line=0;line<12;line++)			 //ע��������7.1.3��
	{
		for(col=0;col<82;col++) 		//ע��������7.1.3��
		{
			m_OutBuf[line][col]=' ';	//ע��������7.1.3��
			m_InBuf[line][col]=' ';		//ע��������7.1.3��
		}	//ע��������7.1.3��
	}//ע��������7.1.3��

	try
	{
		openFileName.Open(strFileName,CFile::modeRead|CFile::shareDenyWrite);	//ע��������7.1.3��
		openFileName.Seek(uID,CFile::begin);									//ע��������7.1.3��
	}
	catch(CFileException *e)
	{
		AfxMessageBox(e->m_cause);
		return;
	}
	//ע��������7.1.3��
	for(line=0;line<12;line++)	//ע��������7.1.3��
	{
		for(col=0;col<82;col++)	//ע��������7.1.3��
		{
			openFileName.Read(&m_OutBuf[line][col],1);					//ע��������7.1.3��
			if(m_OutBuf[line][col]=='\r'||m_OutBuf[line][col]=='\n')	//ע��������7.1.3��
			{
				m_OutBuf[line][col]=' ';								//ע��������7.1.3��
				col--;													//ע��������7.1.3��
			}
		}//ע��������7.1.3��
		m_OutBuf[line][82]='\0';	//ע��������7.1.3��
	}	//ע��������7.1.3��
}
void CTypingTestView::DisplayEnglish(CDC *pDC)
{	
	//ע��������7.2.2��
	CFont *pOldFont;									//ע��������7.2.2��
	pOldFont=(CFont *)pDC->SelectObject(&startFont3);	//ע��������7.2.2��
	pDC->GetTextMetrics(&tm);							//ע��������7.2.2��
	height=tm.tmHeight+tm.tmExternalLeading+3;			//ע��������7.2.2��
	width=tm.tmAveCharWidth;		//ע��������7.2.2��
	for(int line=0;line<12;line++)	//ע��������7.2.2��
	{
		for(int col=0;col<82;col++)	//ע��������7.2.2��
		{
			pDC->TextOut(col*width,line*height*2,m_OutBuf[line][col]);	//ע��������7.2.2��
			//ע��������7.2.2��
			if(m_InBuf[line][col]!=' '||col-1>=0&&m_InBuf[line][col-1]!=' '&&m_InBuf[line][col]==' ')
				pDC->SetBkColor(RGB(0,255,0));//ע��������7.2.2��
			pDC->TextOut(col*width,line*height*2+height-iInH,m_InBuf[line][col]);
			pDC->SetBkColor(RGB(255,255,255));//ע��������7.2.2��
			//ע��������7.2.2��
			//ע��������7.2.2��
		}
	}
	
	//ע��������8.2.4��
	for(line=0;line<=currentLine;line++)	//ע��������8.2.4��
	{
		for(int col=0;col<82;col++)		//ע��������8.2.4��
		{
			if((line==currentLine)&&(col==currentCol))//ע��������8.2.4��
				break;							//ע��������8.2.4��
			if(m_OutBuf[line][col]==m_InBuf[line][col])//ע��������8.2.4��
			{
				pDC->SetBkColor(RGB(255,0,0));//ע��������8.2.4��
				pDC->TextOut(col*width,line*height*2,m_OutBuf[line][col]);//ע��������8.2.4��
				pDC->SetBkColor(RGB(255,255,255));//ע��������8.2.4��
			}
			else //ע��������8.2.4��
			{
				pDC->SetBkColor(RGB(0,0,255));//ע��������8.2.4��
				pDC->TextOut(col*width,line*height*2,m_OutBuf[line][col]);//ע��������8.2.4��
				pDC->SetBkColor(RGB(255,255,255));//ע��������8.2.4��
			}
				
		}

		PosCaret.x=currentCol*width;//urrentCol*width+width;	//ע��������8.2.4��
		PosCaret.y=currentLine*height*2+2*height-iInH;		//ע��������8.2.4��
		SetCaretPos(PosCaret);			//ע��������8.2.4��
		if(m_bTestBegin)ShowCaret();				//ע��������8.2.4��
	} //ע��������8.2.4��
	//ע��������8.5.3��
	for(line=0;line<=currentLine;line++)	//ע��������8.5.3��
	{
		for(int col=0;col<82;col++)	//ע��������8.5.3��
		{
			if((line==currentLine)&&(col==currentCol))	//ע��������8.5.3��
				break;	//ע��������8.5.3��
			if(col%2==0)
			{
				strInCh=m_OutBuf[line][col];//ע��������8.5.3��
				coli=col;//ע��������8.5.3��
			}
			else //ע��������8.5.3��
			{
				strInCh+=m_OutBuf[line][col];//ע��������8.5.3��
				if(m_OutBuf[line][col]==m_InBuf[line][col])//ע��������8.5.3��
				{
					pDC->SetBkColor(RGB(255,0,0));//ע��������8.5.3��
					pDC->TextOut(coli*width,line*height*2,strInCh);//ע��������8.5.3��
					//ע��������8.5.3��
					pDC->SetBkColor(RGB(255,255,255));
				}
				else  //ע��������8.5.3��
				{
					pDC->SetBkColor(RGB(0,255,0));//ע��������8.5.3��
					pDC->TextOut(coli*width,line*height*2,strInCh);//ע��������8.5.3��
					//ע��������8.5.3��
					pDC->SetBkColor(RGB(255,255,255));
				}
			}
		}//ע��������8.5.3��
	}//ע��������8.5.3��

	pDC->SelectObject(pOldFont);		//ע��������7.2.2��
	//ע��������7.2.2��
}
void CTypingTestView::DisplayChinese(CDC *pDC)
{    
	//ע��������7.3.2��
	CFont *pOldFont;									//ע��������7.3.2��
	pOldFont=(CFont *)pDC->SelectObject(&startFont3);	//ע��������7.3.2��
	pDC->GetTextMetrics(&tm);							//ע��������7.3.2��
	height=tm.tmHeight+tm.tmExternalLeading+3;			//ע��������7.3.2��
	width=tm.tmAveCharWidth;							//ע��������7.3.2��
	for(int line=0;line<12;line++)				//ע��������7.3.2��
	{
		for(int col=0;col<82;col++)				//ע��������7.3.2��
		{
			if(col%2==0)						//ע��������7.3.2��
			{   
				strInCh=m_InBuf[line][col];		// ע��������7.3.2��
				strOutCh=m_OutBuf[line][col];	//ע��������7.3.2��
			     coli=col;						//ע��������7.3.2��
			}
			else				//ע��������7.3.2��
			{	
				strInCh+=m_InBuf[line][col];		//ע��������7.3.2��
				strOutCh+=m_OutBuf[line][col];		//ע��������7.3.2��
				//ע��������7.3.2��
				pDC->TextOut(coli*width,line*height*2,strOutCh);	//ע��������7.3.2��
				//ע��������7.3.2��
				if(m_InBuf[line][col]!=' '||col-1>=0&&m_InBuf[line][col-1]!=' '&&m_InBuf[line][col]==' ')
				pDC->SetBkColor(RGB(0,255,0));		//ע��������7.3.2��
				pDC->TextOut(coli*width,line*height*2+height- iInH,strInCh);	//ע��������7.3.2��
				pDC->SetBkColor(RGB(255,255,255));		//ע��������7.3.2��
			}
		}
	}

	pDC->SelectObject(pOldFont);	//ע��������7.3.2��
	//ע��������7.3.2��
}
void CTypingTestView::TestEnd()
{

	m_bTestBegin=FALSE;		//ע��������8.1.2��
	m_bTestRead=FALSE;		//ע��������8.1.2��
	KillTimer(2);			//ע��������8.1.2��


	CString strTestScore;		//ע��������8.1.2��
	strTestScore.Format("�˴β��Գɼ�Ϊ��%d���ַ�/����",inputRight*60/m_lTestTime);//ע��������8.1.2��
	strNoteMessage="����";
	if(MessageBox(strTestScore,"���ֲ���ϵͳ",MB_YESNO)==IDNO)
	{   	
		Invalidate();	//ע��������8.1.2��
		return;
	}
	Invalidate();			//ע��������8.1.2��
	_variant_t vUserId,vTestDate,vSpeed,vRight,vWrong;
	_variant_t vPercent,vTestTime,vTestFile,vEndTestTime;
	//ע��������8.1.2��
	_RecordsetPtr m_pRecordset; CString m_strSql;
	m_strSql="SELECT * FROM score";
	//ע��������8.1.2��
	m_pRecordset.CreateInstance("ADODB.Recordset");
	//ע��������8.1.2��
	try
	{
		m_pRecordset->Open((_variant_t)m_strSql,
			_variant_t((IDispatch *)theApp.m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);//ע��������8.1.2��
	}
	catch(_com_error e)///ע��������8.1.2��
	{
		AfxMessageBox("��ȡ���ݿ�ʧ��!");//ע��������8.1.2��
	}
	
//	AfxMessageBox("��sdafd�Ӽ�¼�ɹ�!");//111ע��������8.1.2��

	//ע��������8.1.2��

	m_pRecordset->AddNew();//ע��������8.1.2�ڣ�
	//	AfxMessageBox("���Ӽ�¼�ɹ�!");//222ע��������8.1.2��

	if(!m_pRecordset->adoEOF )
	{
		vUserId = theApp.m_strUserID;		//ע��������8.1.2��
		vTestDate=theApp.m_strDate;			//ע��������8.1.2��
		if(m_lTestTime==0.0)m_lTestTime=1;	//ע��������8.1.2��
		vSpeed =inputTotal*60/m_lTestTime;	//ע��������8.1.2��
		vRight = inputRight;				//ע��������8.1.2��
		vWrong = inputWrong;				//ע��������8.1.2��
		vPercent= inputRight*100/inputTotal;	//ע��������8.1.2��
		vEndTestTime=((CMainFrame *)AfxGetMainWnd())->m_strTime;//ע��������8.1.2��
		vTestFile=m_strTestFile;			//ע��������8.1.2��
		vTestTime=m_lTestTime;				//ע��������8.1.2��
		//ע��������8.1.2�ڣ�
		m_pRecordset->PutCollect("UserId",vUserId);		//ע��������8.1.2��
		m_pRecordset->PutCollect("TestDate",vTestDate);	//ע��������8.1.2��

		m_pRecordset->PutCollect("Speed",vSpeed);			//ע��������8.1.2��
		m_pRecordset->PutCollect("Right",vRight);			//ע��������8.1.2��
		m_pRecordset->PutCollect("Wrong",vWrong);			//ע��������8.1.2��
		m_pRecordset->PutCollect("Percent",vPercent);		//ע��������8.1.2��
		m_pRecordset->PutCollect("TestTime",vTestTime);	//ע��������8.1.2��
		m_pRecordset->PutCollect("TestFile",vTestFile);	//ע��������8.1.2��
		m_pRecordset->PutCollect("EndTestTime",vEndTestTime);//ע��������8.1.2��
		m_pRecordset->Update();		//ע��������8.1.2��
	}
	//ע��������8.1.2��
	//ע��������8.1.2��
	m_pRecordset->Close();//ע��������8.1.2�ڡ�
	((CMainFrame *)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(0,"����");//ע��������8.1.2��
}
//ע��������8.1.2��

//ע��������8.2.3��
void CTypingTestView::OnCharEnglish(UINT nChar)
{
	CTypingTestDoc* pDoc = GetDocument();	//8.2.3�����ĵ���ĳ�Ա
	CreateSolidCaret(width,2);				//8.2.3���������
	ShowCaret();							//8.2.3��ʾ�����
	if(!m_bTestRead)return;					//8.2.3�����׼����Ϊ�٣���û����Ӣ�Ĳ��Ծͷ���
	CClientDC dc(this);						//8.2.3����ͻ������豸�������
	dc.SelectObject(&startFont3);				//8.2.3ѡ���Զ�������3
	if(nChar==VK_RETURN)				//8.2.3���س���
		return;						//8.2.3���أ����Իس���������
	if(nChar==VK_ESCAPE)				//8.2.3�����ESC������ʾ�Ƿ��˳���ϰ����;����
	{
		if(MessageBox("ȷ��Ҫ����������?","��ʾ!",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
		{	//8.2.3������ʾ�Ի��򣬵�����ȷ����������������
			TestEnd();						//8.2.3��������,���ý��������� 
			HideCaret(); 					//8.2.3 ���Խ���������Ҫ������ʾ�������ز�����
			return;//����
		}
		else
			return;						//8.2.3������ʾ�Ի��򵥻���ȡ��Ϣ���ͷ���
	}

	if(nChar==VK_BACK)			//8.2.3�������������˸�������ǰһ�ַ�
	{
        MessageBox("�����޸Ĵ���!");
		return;
	}
/*
	{
		if(currentCol!=0)			//8.2.3��ǰ��겻������������ǰһ�ַ�
		{
			currentCol--;			//8.2.3�±��һ,ʹ���Ϊǰһ�ַ�
			inputTotal--;			//8.2.3�����ַ�������һ
			if(m_InBuf[currentLine][currentCol]==m_OutBuf[currentLine][currentCol])
				inputRight--;		// 8.2.3����Ե�������һ
			else
				inputWrong--;		//8.2.3������������һ
			m_InBuf[currentLine][currentCol]=' ';	//8.2.3������������Ǹ�Ԫ�����
			dc.TextOut(currentCol*width,currentLine*height*2+height 
				-iInH,m_InBuf[currentLine][currentCol]);	
			//8.2.3����Ļ�ϲ��������ǰһ�ַ�
			dc.TextOut(coli*width-width,currentLine*height*2+height-iInH,"  ");
			PosCaret.x=currentCol*width;//urrentCol*width+width;	//8.2.3���ò�����µ�x����
			PosCaret.y=currentLine*height*2+2*height-iInH;		//8.2.3���ò�����µ�y����
			SetCaretPos(PosCaret);			//8.2.3���ò�����µ�λ��
			ShowCaret();					//8.2.3���µ�λ����ʾ�����
			dc.SetBkColor(RGB(255,255,255));//8.2.3���ñ���ɫΪ��ɫ
			dc.TextOut(currentCol*width,currentLine*height*2,m_OutBuf[currentLine][currentCol]);
			//�����ǰ������ڵ��к��еķ���
			
			return;
		}
		else			//��ÿ�������������
		
		{
			if(currentLine>0){
				currentLine--;
				//currentLine--;

				currentCol=81;	//8.2.3���к󣬵�ǰ��λ��������Ϊ0
				m_InBuf[currentLine][currentCol]=' ';	//8.2.3������������Ǹ�Ԫ�����
				dc.SetBkColor(RGB(255,255,255));		//8.2.3�ָ�����ɫΪ��ɫ

			    dc.TextOut(currentCol*width,currentLine*height*2,m_OutBuf[currentLine][currentCol]);
				dc.TextOut(currentCol*width,currentLine*height*2+height-iInH,"  ");

				PosCaret.x=currentCol*width;//urrentCol*width+width;	//8.2.3���ò�����µ�x����
				PosCaret.y=currentLine*height*2-2*height-iInH; //8.2.3���ò�����µ�y����
				SetCaretPos(PosCaret); //8.2.3���ò�����µ�λ��
//							char out[13];
//			sprintf(out,"first:%c",m_InBuf[currentLine][currentCol]);
//			MessageBox(out);
		}

			return;
		}
	}
	*/
  if((!bLastKeyIsBlank) && m_OutBuf[currentLine][currentCol]==VK_SPACE)  //�ϴ�������ַ����ǿո�,���������ǿո�,�������������
	{
	     inputTotal++;				//����ĵ���������һ
		 if(bWordIsTrue)inputRight++;	
		 else inputWrong++;
		 bWordIsTrue=FALSE;
		 bWordCount=FALSE;
		 bLastKeyIsBlank=TRUE;
	}
	if(bLastKeyIsBlank && !(m_OutBuf[currentLine][currentCol]==VK_SPACE))  //�ϴ�������ǿո�,�������Ĳ��ǿո�,���ʼ�����ʼ.
	{

		bWordCount=TRUE;		//���ʶԴ��鿪ʼ
		bWordIsTrue=TRUE;		//������ǵ����ǶԵ�
		bLastKeyIsBlank=FALSE;

		//���ʼ�����ʼ
	}

	m_InBuf[currentLine][currentCol]=(char)nChar;//�����յ����ַ���������ַ������浽��������Ԫ����
	dc.SetBkColor(RGB(0,255,0));//�����ַ��ı���ɫΪ��ɫ
	dc.TextOut(currentCol*width,currentLine*height*2+height,m_InBuf[currentLine][currentCol]);//���������ַ�
	PosCaret.x=currentCol*width+width; //8.2.3���ò�����µ�x����
	PosCaret.y=currentLine*height*2+2*height-iInH; //8.4.3���ò�����µ�y����


	if(m_InBuf[currentLine][currentCol]==m_OutBuf[currentLine][currentCol])//8.2.3��������ַ��ͷ�����һ����
	{	
		
		//inputRight++;						//8.2.3�����ַ������ǵ�,�������ַ��Ե�������һ
		dc.SetBkColor(RGB(255,0,0));			//8.2.3���ñ���ɫΪ��ɫ
		dc.TextOut(currentCol*width,currentLine*height*2,m_OutBuf[currentLine][currentCol]);//8.2.3���������
		dc.SetBkColor(RGB(255,255,255));		//8.2.3�ָ�����ɫΪ��ɫ
	}
	else
	{
		if(bWordIsTrue)bWordIsTrue=FALSE;
		//inputWrong++;			//8.2.3������������һ
		if(bWordIsTrue) bWordIsTrue=FALSE;
		dc.SetBkColor(RGB(0,0,255));//2.3.3���ñ���ɫΪ��ɫ
		dc.TextOut(currentCol*width,currentLine*height*2,m_OutBuf[currentLine][currentCol]);//8.2.3�������
		dc.SetBkColor(RGB(255,255,255));//8.3.3�ָ�����ɫ
	}
	currentCol++;//8.2.3��ǰ���λ���м�һ

  

	

	if(currentCol>=82)		//8.2.3�����ұ��Զ�����
	{
		dc.TextOut(currentCol*width+1,currentLine*height*2+height," ");//8.2.3һ��������һ���ո�
		currentLine++;	//8.2.3��ǰ���λ���м�һ
		if(currentLine==12)
		{
			TestEnd();	//8.2.3һҳ���꣬��������,����������������������
			HideCaret(); 					//8.2.3 ���Խ���������Ҫ������ʾ�������ز�����
		}
		currentCol=0;	//8.2.3���к󣬵�ǰ��λ��������Ϊ0
		PosCaret.x=0;	//8.2.3���ò�����µ�x����
		PosCaret.y=currentLine*height*2+2*height-iInH; //8.2.3���ò�����µ�y����
	 }
	SetCaretPos(PosCaret); //8.2.3���ò�����µ�λ��

}
//ע��������8.2.3��

void CTypingTestView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bTestEnglish)				//ע��������8.4.2��
		CreateSolidCaret(width,2);		//ע��������8.4.2��
	else						//ע��������8.4.2��
		CreateSolidCaret(2*width,2);	//ע��������8.4.2��
	if(!m_bTestRead)return;	//ע��������8.4.2��
	CClientDC dc(this); //ע��������8.4.2��
	  dc.SelectObject(&startFont3);//ע��������8.4.2��

	if(m_bTestBegin)				//ע��������8.4.2��
	{
		if(m_bTestEnglish)			//ע��������8.4.2��
			OnCharEnglish(nChar);
		else 
			OnCharChinese(nChar);	//8.5.4������պ������룬ע����8.5��ǰӦ����ע�͵���
	}
	else 						//ע��������8.4.2��
	{
		if(nChar==VK_SPACE)		//ע��������8.4.2��
		{
			strNoteMessage="�����ڽ����У���ESC����ֹ��";		//ע��������8.4.2��
			((CMainFrame *)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(0,"�����ڽ����У���ESC����ֹ��");
			SetTimer(2,1000,NULL);			//ע��������8.4.2��
			m_bTestBegin=TRUE;			//ע��������8.4.2��
			PosCaret.x=0;					//ע��������8.4.2��
			PosCaret.y=2*height-iInH;			//ע��������8.4.2��
			ShowCaret();		//ע��������8.4.2��
			SetCaretPos(PosCaret);	//ע��������8.4.2��
		}
		else			//ע��������8.4.2��
			MessageBox("׼������,���ո����ʼ��ʱ!","��ʾ",MB_OK|MB_ICONINFORMATION);
	}
	//ע��������8.4.2��
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CTypingTestView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_lTestTime++;//8.4.1����ʱ���1��
	CView::OnTimer(nIDEvent);
}
//ע��������8.5.2��
void CTypingTestView::OnCharChinese(UINT nChar)
{
	CreateSolidCaret(2*width,2);	//ע��������8.5.2��
	ShowCaret();				//ע��������8.5.2��

	if(nChar<=127)	//ע��������8.5.2��
	{	
		if(nChar==VK_ESCAPE||nChar==VK_BACK);//ע��������8.5.2��
	    else return;//ע��������8.5.2��
	}
	
	if(!m_bTestRead)return;	//ע��������8.5.2��
	CClientDC dc(this);	//ע��������8.5.2��
	dc. SelectObject(&startFont3);	//ע��������8.5.2��
	if(nChar==VK_RETURN)	//ע��������8.5.2��
			return;
	if(nChar==VK_ESCAPE)	//ע��������8.5.2��
	{
		if(MessageBox("ȷ��Ҫ������ϰ��?","��ʾ!",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
		{
			TestEnd();		//ע��������8.5.2��
			HideCaret(); 	//ע��������8.5.2��
			return;
		}
		else		//ע��������8.5.2��
			return;
	}
	
	if(nChar==VK_BACK)				//ע��������8.5.2��
	{
		HideCaret();				//ע��������8.5.2��
		if(currentCol!=0)			//ע��������8.5.2��
		{

			currentCol--;			//ע��������8.5.2��
			coli=currentCol;			//ע��������8.5.2��
			currentCol--;			//ע��������8.5.2��
			inputTotal--;			//ע��������8.5.2��
			if(m_InBuf[currentLine][currentCol]==m_OutBuf[currentLine][currentCol])
				inputRight--;		// ע��������8.5.2��
			else
			    inputWrong--;		//ע��������8.5.2��
			m_InBuf[currentLine][coli]=' ';//ע��������8.5.2��
			m_InBuf[currentLine][currentCol]=' ';//ע��������8.5.2��

			dc.TextOut(currentCol*width,currentLine*height*2+height,m_InBuf[currentLine][currentCol]);	
										//ע��������8.5.2��
			dc.TextOut(coli*width,currentLine*height*2+height,m_InBuf[currentLine][coli]);	
										//ע��������8.5.2��
			PosCaret.x=currentCol*width;	//ע��������8.5.2��
			PosCaret.y=currentLine*height*2+2*height-iInH;		//ע��������8.5.2��
			SetCaretPos(PosCaret);			//ע��������8.5.2��
			ShowCaret();					//ע��������8.5.2��
			dc.SetTextColor(RGB(0,0,0));//ע��������8.5.2��
			strInCh=m_OutBuf[currentLine][currentCol];//ע��������8.5.2��
			strInCh+=m_OutBuf[currentLine][coli];//ע��������8.5.2��
			dc.TextOut(currentCol*width,currentLine*height*2,strInCh);//ע��������8.5.2��
			return;	//ע��������8.5.2��
		}
		else						//ע��������8.5.2��
		{
			MessageBeep(-1);		//����
			return;
		}
	}
	if(byte1==0)//ע��������8.5.2��
	{
		coli=currentCol;//ע��������8.5.2��
		m_InBuf[currentLine][currentCol]=(char)nChar;//ע��������8.5.2��
		strInCh=(char)nChar;//ע��������8.5.2��
		byte1++;//ע��������8.5.2��
	}
	else //ע��������8.5.2��
	{
		m_InBuf[currentLine][currentCol]=(char)nChar;// ע��������8.5.2��
		strInCh+=(char)nChar;// ע��������8.5.2��
		dc.SetBkColor(RGB(0,255,0));//ע��������8.5.2��
		dc.TextOut(coli*width,currentLine*height*2+height-iInH,strInCh);//ע��������8.5.2��
		PosCaret.x=currentCol*width+width; //ע��������8.5.2��
		PosCaret.y=currentLine*height*2+2*height-iInH; //ע��������8.5.2��

		byte1=0;//ע��������8.5.2��
		inputTotal++;				//ע��������8.5.2��

		strOutCh=m_OutBuf[currentLine][currentCol-1];//ע��������8.5.2��
		strOutCh+=m_OutBuf[currentLine][currentCol];//ע��������8.5.2��

		if(m_InBuf[currentLine][currentCol]==m_OutBuf[currentLine][currentCol])//ע��������8.5.2��
		{
		    inputRight++;						//ע��������8.5.2��
			dc.SetBkColor(RGB(255,0,0));			//ע��������8.5.2��
		    dc.TextOut((currentCol-1)*width,currentLine*height*2,strOutCh);	//ע��������8.5.2��
			dc.SetBkColor(RGB(255,255,255));		//ע��������8.5.2��
		}
	    else						//ע��������8.5.2��
		{
		    inputWrong++;			//ע��������8.5.2��
			dc.SetBkColor(RGB(0,255,0));	//ע��������8.5.2��
		    dc.TextOut((currentCol-1)*width,currentLine*height*2,strOutCh);	//ע��������8.5.2��
			dc.SetBkColor(RGB(255,255,255));		//ע��������8.5.2��

		}
	}
	currentCol++;//ע��������8.5.2��
	if(currentCol==82)		//ע��������8.5.2��
	{
		dc.TextOut(currentCol*width+1,currentLine*height*2+height," ");//ע��������8.5.2��
		currentLine++;//ע��������8.5.2��
		if(currentLine==14)
		{
			TestEnd();		//ע��������8.5.2��
			HideCaret(); 	//ע��������8.5.2��
		}
		currentCol=0;//ע��������8.5.2��
		PosCaret.x=0;	//ע��������8.5.2��
		PosCaret.y=currentLine*height*2+2*height-iInH; //ע��������8.5.2��
	}
	SetCaretPos(PosCaret);//ע��������8.5.2��
}
//ע��������8.5.2��

void CTypingTestView::OnHelpFinder() 
{
	// TODO: Add your command handler code here
	// ע��������10.7�� 
	char exeFullPath[MAX_PATH];		//ע��������10.7�� 
	CString strPath;					//ע��������10.7�� 
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);	//ע��������10.7�� 
	strPath = CString(exeFullPath);		//ע��������10.7�� 
	strPath = strPath.Left(strPath.ReverseFind('\\'));		//ע��������10.7�� 
	strPath += "\\TypingTest.chm";					//ע��������10.7�� 
	char cCommandLine[MAX_PATH];				//ע��������10.7�� 
	::strcpy(cCommandLine, strPath);				//ע��������10.7�� 
	// ע��������10.7�� 
	HtmlHelp(GetSafeHwnd(), cCommandLine, HH_DISPLAY_TOPIC, 0);	//ע��������10.7�� 
	
}
