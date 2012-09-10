// DeleteUser.cpp : implementation file
//

#include "stdafx.h"
#include "TypingTest.h"
#include "DeleteUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteUser dialog


CDeleteUser::CDeleteUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeleteUser)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strSql="SELECT * FROM SysUser";//注释在书上9.3.3节
	m_strSql2="SELECT * FROM score "; //注释在书上9.3.3节
	m_nIndex=0;				//注释在书上9.3.3节
	m_strUserID=" ";			//注释在书上9.3.3节

}


void CDeleteUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteUser)
	DDX_Control(pDX, IDC_LIST_SCORE, m_ScoreList);
	DDX_Control(pDX, IDC_LIST_USER, m_UserList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeleteUser, CDialog)
	//{{AFX_MSG_MAP(CDeleteUser)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_USER, OnItemchangedListUser)
	ON_COMMAND(ID_USER_DEL, OnUserDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeleteUser message handlers

BOOL CDeleteUser::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pRecordset->Close();		//注释在书上9.3.3节
	m_pRecScore->Close();		//注释在书上9.3.3节
	
	return CDialog::DestroyWindow();
}

BOOL CDeleteUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//注释在书上9.3.3节
	m_UserList.InsertColumn(0,"用户代码",LVCFMT_LEFT,80,0);//注释在书上9.3.3节
	m_UserList.InsertColumn(1,"用户姓名",LVCFMT_LEFT,80,1); //注释在书上9.3.3节
	m_UserList.InsertColumn(2,"用户权限",LVCFMT_LEFT,80,2); //注释在书上9.3.3节限
	DWORD dwExStyle=LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES
		|LVS_EX_HEADERDRAGDROP|LVS_EX_TRACKSELECT; //注释在书上9.3.3节
//LVS_EX_TRACKSELECT 当鼠标指到某一项时便自动选择该项映射消息 LVN_ITEMCHANGED 
	m_UserList.SetExtendedStyle(dwExStyle);	///注释在书上9.3.3节
	//注释在书上9.3.3节
	m_ScoreList.InsertColumn(0,"测试日期",LVCFMT_LEFT,80,0);// 注释在书上9.3.3节
	m_ScoreList.InsertColumn(1,"测试时间",LVCFMT_LEFT,80,1); //注释在书上9.3.3节
	m_ScoreList.InsertColumn(2,"速度",LVCFMT_LEFT,80,2); // 注释在书上9.3.3节
	m_ScoreList.InsertColumn(3,"正确",LVCFMT_LEFT,80,2); //注释在书上9.3.3节
	m_ScoreList.InsertColumn(4,"错误",LVCFMT_LEFT,80,2); //注释在书上9.3.3节
	m_ScoreList.InsertColumn(5,"正确率",LVCFMT_LEFT,80,2); // 注释在书上9.3.3节
	m_ScoreList.InsertColumn(6,"测试文章",LVCFMT_LEFT,80,2); // 注释在书上9.3.3节
	m_ScoreList.InsertColumn(7,"用户代码",LVCFMT_LEFT,80,2); // 注释在书上9.3.3节
	//注释在书上9.3.3节
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");		//注释在书上9.3.3节
		//注释在书上9.3.3节
		m_pRecordset->Open((_variant_t)m_strSql,
			_variant_t((IDispatch *)theApp.m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);//注释在书上9.3.3节
	}
	catch(_com_error e)//注释在书上9.3.3节
	{
		AfxMessageBox("读取数据库失败!"); //注释在书上9.3.3节
	}

	int nItem;
	_variant_t vUserID,vUserName,vUserRight;
	CString temp;
	//注释在书上9.3.3节
	m_pRecordset->MoveFirst();			//注释在书上9.3.3节
	while(!m_pRecordset->adoEOF)			// 注释在书上9.3.3节
	{
		vUserID = m_pRecordset->GetCollect("UserId");		//注释在书上9.3.3节
		vUserName = m_pRecordset->GetCollect("UserName"); 	//注释在书上9.3.3节
		vUserRight = m_pRecordset->GetCollect("UserRight");	//注释在书上9.3.3节

		nItem=m_UserList.InsertItem(0xffff,(_bstr_t)vUserID); //注释在书上9.3.3节
		m_UserList.SetItem(nItem,0,1,(_bstr_t)vUserID,NULL,0,0,0); // 注释在书上9.3.3节
		m_UserList.SetItem(nItem,1,1,(_bstr_t)vUserName,NULL,0,0,0); //注释在书上9.3.3节
		m_UserList.SetItem(nItem,2,1,(_bstr_t)vUserRight.lVal,NULL,0,0,0); //注释在书上9.3.3节
		m_pRecordset->MoveNext();		//注释在书上9.3.3节
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDeleteUser::OnItemchangedListUser(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	POSITION pos = m_UserList.GetFirstSelectedItemPosition();	//注释在书上9.3.3节
	 m_nIndex = m_UserList.GetNextSelectedItem(pos);  //注释在书上9.3.3节

	 m_strUserID=m_UserList.GetItemText(m_nIndex,0); //注释在书上9.3.3节

	 m_ScoreList.DeleteAllItems(); 	//注释在书上9.3.3节

	//注释在书上9.3.3节

	try
	{
		m_pRecScore.CreateInstance("ADODB.Recordset");//注释在书上9.3.3节
		m_pRecScore->Open((_variant_t)m_strSql2,
			_variant_t((IDispatch *)theApp.m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText); // 注释在书上9.3.3节
	}
	catch(_com_error e) //注释在书上9.3.3节
	{
		AfxMessageBox("读取数据库失败!"); //注释在书上9.3.3节
		return;
	}

	int nItem;
	_variant_t vUserID,vTestDate,vTestTime,vSpeed,vRight,vWrong,vTestFile,vPercent;
	CString temp;
	if(!m_pRecScore->adoEOF)m_pRecScore->MoveFirst();		//注释在书上9.3.3节
	while(!m_pRecScore->adoEOF)							//注释在书上9.3.3节.
	{

		vUserID = m_pRecScore->GetCollect("UserId");//注释在书上9.3.3节
		if(m_strUserID==vUserID.bstrVal)		//注释在书上9.3.3节
		{
			vTestDate = m_pRecScore->GetCollect("TestDate");	//注释在书上9.3.3节
			vTestTime = m_pRecScore->GetCollect("EndTestTime");//注释在书上9.3.3节
			vSpeed = m_pRecScore->GetCollect("Speed");			//注释在书上9.3.3节
			vRight = m_pRecScore->GetCollect("Right");			//注释在书上9.3.3节
			vWrong = m_pRecScore->GetCollect("Wrong");			//注释在书上9.3.3节
			vPercent=m_pRecScore->GetCollect("Percent");		//注释在书上9.3.3节
			vTestFile   = m_pRecScore->GetCollect("TestFile");		//注释在书上9.3.3节
			//注释在书上9.3.3节
			nItem=m_ScoreList.InsertItem(0xffff,(_bstr_t)vTestDate);		//注释在书上9.3.3节
			m_ScoreList.SetItem(nItem,0,1,(_bstr_t)vTestDate,NULL,0,0,0);	//注释在书上9.3.3节
			m_ScoreList.SetItem(nItem,1,1,(_bstr_t)vTestTime,NULL,0,0,0); // 注释在书上9.3.3节
			m_ScoreList.SetItem(nItem,2,1,(_bstr_t)vSpeed,NULL,0,0,0); // 注释在书上9.3.3节
			m_ScoreList.SetItem(nItem,3,1,(_bstr_t)vRight,NULL,0,0,0); // 注释在书上9.3.3节
			m_ScoreList.SetItem(nItem,4,1,(_bstr_t)vWrong,NULL,0,0,0); // 注释在书上9.3.3节
			m_ScoreList.SetItem(nItem,5,1,(_bstr_t)vPercent,NULL,0,0,0); // 注释在书上9.3.3节
			m_ScoreList.SetItem(nItem,6,1,(_bstr_t)vTestFile,NULL,0,0,0); // 注释在书上9.3.3节
			m_ScoreList.SetItem(nItem,7,1,(_bstr_t)vUserID,NULL,0,0,0); //注释在书上9.3.3节

		}
		m_pRecScore->MoveNext();//注释在书上9.3.3节
	}	
	
	*pResult = 0;
}

void CDeleteUser::OnUserDel() 
{
	// TODO: Add your command handler code here
	_variant_t vUserID;
	if(m_nIndex >= 0)
	{
		try
		{
			// 注释在书上9.3.3节
			m_pRecordset->Move(m_nIndex,_variant_t((long)adBookmarkFirst));
			m_UserList.DeleteItem(m_nIndex);		// 注释在书上9.3.3节
			
			int count = m_UserList.GetItemCount();		//注释在书上9.3.3节
			if(count <= m_nIndex)
				m_nIndex = count-1;				// 注释在书上9.3.3节
			m_pRecordset->Delete(adAffectCurrent);	//注释在书上9.3.3节
			// 注释在书上9.3.3节
			m_pRecordset->Update();				// 注释在书上9.3.3节
			// 注释在书上9.3.3节
			if(!m_pRecScore->adoEOF)m_pRecScore->MoveFirst();		//注释在书上9.3.3节
			while(!m_pRecScore->adoEOF)			//注释在书上9.3.3节
			{
				vUserID = m_pRecScore->GetCollect("UserId");//注释在书上9.3.3节
				if(m_strUserID==vUserID.bstrVal) // 注释在书上9.3.3节
				{
					m_pRecScore->Delete(adAffectCurrent);	//注释在书上9.3.3节
				}
				m_pRecScore->MoveNext();	//注释在书上9.3.3节
		}	
		}
		catch(_com_error *e)
		{
			AfxMessageBox(e->ErrorMessage());
		}
		m_UserList.SetFocus();//注释在书上9.3.3节
	}
	m_strUserID=""; //注释在书上9.3.3节
	
}
