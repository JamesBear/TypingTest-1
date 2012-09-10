// CreateNewUser.cpp : implementation file
//

#include "stdafx.h"
#include "TypingTest.h"
#include "CreateNewUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateNewUser dialog


CCreateNewUser::CCreateNewUser(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateNewUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateNewUser)
	m_strUserID = _T("");
	m_strUserKey = _T("");
	m_strUserKey2 = _T("");
	m_strUserName = _T("");
	//}}AFX_DATA_INIT
	m_strSql="SELECT * FROM SysUser ";//注释在书上9.1.3节
	//注释在书上9.1.3节
	m_pRecordset.CreateInstance("ADODB.Recordset");
	//注释在书上9.1.3节

	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");//注释在书上9.1.3节
		m_pRecordset->Open((_variant_t)m_strSql,
			_variant_t((IDispatch *)theApp.m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);//注释在书上9.1.3节 
	}
	catch(_com_error e)//注释在书上9.1.3节
	{
		AfxMessageBox("读取数据库失败!");//注释在书上9.1.3节
		return;
	}

}


void CCreateNewUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateNewUser)
	DDX_Text(pDX, IDC_NEWUSER_ID, m_strUserID);
	DDX_Text(pDX, IDC_NEWUSER_KEY, m_strUserKey);
	DDX_Text(pDX, IDC_NEWUSER_KEYY, m_strUserKey2);
	DDX_Text(pDX, IDC_NEWUSER_NAME, m_strUserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateNewUser, CDialog)
	//{{AFX_MSG_MAP(CCreateNewUser)
	ON_BN_CLICKED(IDC_NEW_ID_TEST, OnNewIdTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateNewUser message handlers

void CCreateNewUser::OnOK() 
{
	// TODO: Add extra validation here
	_variant_t vUserID,vUserName,vUserKey,vUserRight;
	UpdateData(TRUE);				//注释在书上9.1.3节
	if(m_strUserKey!=m_strUserKey2)	//注释在书上9.1.3节
	{
		MessageBox("两次密码不一致","打字测试系统",MB_OK);
		return;
	}

	m_pRecordset->MoveFirst();			//注释在书上9.1.3节
	while(!m_pRecordset->adoEOF)			//注释在书上9.1.3节
	{
		vUserID = m_pRecordset->GetCollect("UserId");	//注释在书上9.1.3节
		if(m_strUserID==vUserID.bstrVal)			//注释在书上9.1.3节
		{
			MessageBox("用户名已经有人使用,请更改!","打字测试系统!",MB_OK);
			return;
		}
		m_pRecordset->MoveNext();		//注释在书上9.1.3节
	}	
	//注释在书上9.1.3节
	m_pRecordset->AddNew();		//注释在书上9.1.3节
	if(!m_pRecordset->adoEOF )
	{
		vUserID = m_strUserID;		//注释在书上9.1.3节
		vUserName = m_strUserName;	//注释在书上9.1.3节
		vUserKey = m_strUserKey;	//注释在书上9.1.3节
		vUserRight=theApp.m_lUserRight;//注释在书上9.1.3节	
			
		m_pRecordset->PutCollect("UserId",vUserID);			//注释在书上9.1.3节
		m_pRecordset->PutCollect("UserName",vUserName);
		m_pRecordset->PutCollect("UserKey",vUserKey);
		m_pRecordset->PutCollect("UserRight",vUserRight);
		m_pRecordset->Update();

	} //注释在书上9.1.3节
	MessageBox("注册成功，返回重新登录!","打字测试系统!",MB_OK|MB_ICONWARNING);
	
	CDialog::OnOK();
}

void CCreateNewUser::OnNewIdTest() 
{
	// TODO: Add your control notification handler code here
	////注释在书上9.1.3节
	UpdateData(TRUE);					//注释在书上9.1.3节
	m_pRecordset->MoveFirst();			//注释在书上9.1.3节
	while(!m_pRecordset->adoEOF)			//注释在书上9.1.3节
	{
		_variant_t vUserID;
		vUserID = m_pRecordset->GetCollect("UserId");
		CString strTemp=vUserID.bstrVal;
		if(m_strUserID==strTemp)			//注释在书上9.1.3节
		{
			MessageBox("输入的用户名已经有人使用,请更改!","错误!",MB_OK|MB_ICONWARNING);
			m_strUserID.Empty();			//注释在书上9.1.3节
			GetDlgItem(IDC_NEWUSER_ID)->SetFocus();	//注释在书上9.1.3节
			UpdateData(FALSE);						//注释在书上9.1.3节
			return;
		}
		m_pRecordset->MoveNext();		//注释在书上9.1.3节
	}		
	MessageBox("输入的用户名没被人使用!", "继续!",MB_OK|MB_ICONWARNING);

	
}

BOOL CCreateNewUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
		if(m_strCaption.GetLength())		//注释在书上9.1.3节 
		SetWindowText(m_strCaption);	     //注释在书上9.1.3节

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
