// FindScore.cpp : implementation file
//

#include "stdafx.h"
#include "TypingTest.h"
#include "FindScore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindScore dialog


CFindScore::CFindScore(CWnd* pParent /*=NULL*/)
	: CDialog(CFindScore::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindScore)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strSql="SELECT * FROM score ORDER BY UserId";//注释在书上9.4.3节
}


void CFindScore::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindScore)
	DDX_Control(pDX, IDC_LIST_SCORE, m_CtrlFindScore);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindScore, CDialog)
	//{{AFX_MSG_MAP(CFindScore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindScore message handlers

BOOL CFindScore::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pRecordset->Close();		//注释在书上9.4.3节
	delete this;				//注释在书上9.4.3节
	
	return CDialog::DestroyWindow();
}

BOOL CFindScore::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if ( m_strCaption.GetLength() )SetWindowText( m_strCaption );//注释在书上9.4.3节
	
	m_CtrlFindScore.InsertColumn(0,"测试日期",LVCFMT_LEFT,80,0); //注释在书上9.4.3节
	m_CtrlFindScore.InsertColumn(1,"测试时间",LVCFMT_LEFT,80,1);//注释在书上9.4.3节
	m_CtrlFindScore.InsertColumn(2,"速度",LVCFMT_LEFT,80,2);//注释在书上9.4.3节
	m_CtrlFindScore.InsertColumn(3,"正确",LVCFMT_LEFT,80,2);//注释在书上9.4.3节
	m_CtrlFindScore.InsertColumn(4,"错误",LVCFMT_LEFT,80,2);// 9.4.3错误列
	m_CtrlFindScore.InsertColumn(5,"正确率",LVCFMT_LEFT,80,2);// 9.4.3正确率列
	m_CtrlFindScore.InsertColumn(6,"测试文章",LVCFMT_LEFT,80,2);// 9.4.3文件名列
	DWORD dwExStyle=LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES 
		|LVS_EX_HEADERDRAGDROP|LVS_EX_TRACKSELECT; //9.4.3列表控件有网格线
	m_CtrlFindScore.SetExtendedStyle(dwExStyle);	//9.5.3设置扩展风格

	//【4-2】 创建Recordset对象的实例	
	m_pRecordset.CreateInstance("ADODB.Recordset");
	//【4-3】直接用Recordset对象进行查询取得记录集
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");//9.4.3创建Recordset对象
		m_pRecordset->Open((_variant_t)m_strSql,
			_variant_t((IDispatch *)theApp.m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);// 9.4.3取得记录集
	}
	catch(_com_error e)// 9.4.3捕捉异常
	{
		AfxMessageBox("读取数据库失败!");// 9.4.3显示错误信息
	}
	//【5】对记录集进行遍历
	int nItem;
	_variant_t vUserID,vTestDate,vTestTime,vSpeed,vRight,vWrong,vTestFile,vPercent;
	CString temp;
	m_pRecordset->MoveFirst();		//【5-1】移到首条记录
    if(!m_bFindAll)	//9.5.3查询所有用户的成绩
	{
		while(!m_pRecordset->adoEOF)		 //【5-2】遍历记录集看用户输入的用户名是否有人使用.
		{
			vUserID = m_pRecordset->GetCollect("UserId");		//【5-3】读取记录集中指定字段的值
			if(theApp.m_strUserID==vUserID.bstrVal)			//9.4.3如果是该用户
			{
				vTestDate = m_pRecordset->GetCollect("TestDate"); 	//9.4.3继续读其他字段
				vTestTime = m_pRecordset->GetCollect("EndTestTime");	//9.4.3取得测试时间
				vSpeed = m_pRecordset->GetCollect("Speed");	//9.4.3读取测试速度
				vRight = m_pRecordset->GetCollect("Right");	//9.4.3读取输入的字符正确数
				vWrong = m_pRecordset->GetCollect("Wrong");		//9.4.3读取输入的字符错误数
				vPercent=m_pRecordset->GetCollect("Percent");		//9.4.3读取输入的正确优选法
				vTestFile   = m_pRecordset->GetCollect("TestFile");		//9.4.3读取测试的文件名
				//9.5.3在成绩列有控件是显示该用户的记录
				nItem=m_CtrlFindScore.InsertItem(0xffff,(_bstr_t)vTestDate);	//9.4.3插入行
				//m_CtrlFindScore.SetItem(nItem,0,1,(_bstr_t)vTestDate,NULL,0,0,0); //设置该行的各列
				m_CtrlFindScore.SetItem(nItem,1,1,(_bstr_t)vTestTime,NULL,0,0,0);// 9.4.3显示时间
				m_CtrlFindScore.SetItem(nItem,2,1,(_bstr_t)vSpeed,NULL,0,0,0);// 9.4.3显示速度
				m_CtrlFindScore.SetItem(nItem,3,1,(_bstr_t)vRight,NULL,0,0,0);// 9.4.3显示正确字符数
				m_CtrlFindScore.SetItem(nItem,4,1,(_bstr_t)vWrong,NULL,0,0,0);// 9.4.3显示错误字符数
				m_CtrlFindScore.SetItem(nItem,5,1,(_bstr_t)vPercent,NULL,0,0,0);// 9.4.3显示正确率
				m_CtrlFindScore.SetItem(nItem,6,1,(_bstr_t)vTestFile,NULL,0,0,0);//在列表框上显示文件名 

			}
			m_pRecordset->MoveNext();		//【5-4】移到下一条记录
		}	
	}
	else		//9.4.3查询用户本人的成绩
	{
		m_CtrlFindScore.InsertColumn(7,"用户代码",LVCFMT_LEFT,80,0);

		while(!m_pRecordset->adoEOF)			//【5】对记录集进行遍历（成绩）.
		{
			vUserID = m_pRecordset->GetCollect("UserId");		//【5-3】读取记录集中指定字段的值
			vTestDate = m_pRecordset->GetCollect("TestDate");//【5-3】读取记录
			vTestTime = m_pRecordset->GetCollect("EndTestTime");//9.4.3测试时间 
			vSpeed = m_pRecordset->GetCollect("Speed");//9.4.3速度
			vRight = m_pRecordset->GetCollect("Right");//9.4.3正确数
			vWrong = m_pRecordset->GetCollect("Wrong");//9.4.3错误数
			vPercent=m_pRecordset->GetCollect("Percent");//9.4.3正确率
			vTestFile   = m_pRecordset->GetCollect("TestFile");//9.4.3读取范文的文件名
			//9.5.3在成绩列表控件中插入一行显示成绩行
		nItem=m_CtrlFindScore.InsertItem(0xffff,(_bstr_t)vUserID);// 9.4.3插入行
			m_CtrlFindScore.SetItem(nItem,7,1,(_bstr_t)vUserID,NULL,0,0,0);// 9.4.3设置该行其他列的值
			m_CtrlFindScore.SetItem(nItem,0,1,(_bstr_t)vTestDate,NULL,0,0,0);// 9.4.3显示日期
			m_CtrlFindScore.SetItem(nItem,1,1,(_bstr_t)vTestTime,NULL,0,0,0);// 9.4.3显示时间
			m_CtrlFindScore.SetItem(nItem,2,1,(_bstr_t)vSpeed,NULL,0,0,0);// 9.4.3显示速度
			m_CtrlFindScore.SetItem(nItem,3,1,(_bstr_t)vRight,NULL,0,0,0);// 9.4.3显示正确数
			m_CtrlFindScore.SetItem(nItem,4,1,(_bstr_t)vWrong,NULL,0,0,0);// 9.4.3显示错误数
			m_CtrlFindScore.SetItem(nItem,5,1,(_bstr_t)vPercent,NULL,0,0,0);//9.4.3显示正确率
			m_CtrlFindScore.SetItem(nItem,6,1,(_bstr_t)vTestFile,NULL,0,0,0);//9.4.3显示范文文件名
			m_pRecordset->MoveNext();		//【5-4】移到下一条记录
		}
	}	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
