// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TypingTest.h"
#include "LoginDlg.h"

#include "CreateNewUser.h"  					//注释在书上9.1.4节
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_strUserID = _T("");
	m_strLoginPassWord = _T("");
	//}}AFX_DATA_INIT
	// 注释在书上4.2.4节
	nLoginNum=0;		//注释在书上4.2.4节

}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Text(pDX, IDC_EIDT_USERID, m_strUserID);
	DDX_Text(pDX, IDC_EDIT_LOGINPASSWORD, m_strLoginPassWord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_BN_CLICKED(IDC_BUTTON_NEWUSER, OnButtonNewuser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

void CLoginDlg::OnButtonNewuser() 
{
	// TODO: Add your control notification handler code here
	//注释在书上9.1.4节
	CCreateNewUser NewUserDlg;				//注释在书上9.1.4节
	NewUserDlg.m_strCaption="注册新用户";	//注释在书上9.1.4节
	NewUserDlg.DoModal();					//注释在书上9.1.4节
	//注释在书上9.1.4节
	
}

void CLoginDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CLoginDlg::OnOK() 
{
	// TODO: Add extra validation here
	//注释在书上4.2.4节
	UpdateData(TRUE);			//注释在书上4.2.4节
	char m_strSql[256];CString str = _T("");
	strcpy(m_strSql,"SELECT * FROM SysUser WHERE UserId='"+m_strUserID+"'"+" AND UserKey='"+m_strLoginPassWord+"'" );//注释在书上4.2.4节

	//注释在书上4.2.4节
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");		//注释在书上4.2.4节
		m_pRecordset->Open((_variant_t)m_strSql,
			_variant_t((IDispatch *)theApp.m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);										// 注释在书上4.2.4节
	}
	catch(_com_error e)										//注释在书上4.2.4节
	{
		CString errormessage;
		errormessage.Format("查询取得记录集失败!\r\n错误信息:%s",e.ErrorMessage());
		MessageBox(m_strSql,errormessage,MB_OK);			//注释在书上4.2.4节
	}
	if(m_pRecordset->adoEOF)								//注释在书上4.2.4节
	{
	nLoginNum++;
		if(nLoginNum>=3){									//注释在书上4.2.4节。
			MessageBox("非法用户","打字测试系统",MB_OK);	//注释在书上4.2.4节
			CDialog::OnCancel();
			return;
		}
		MessageBox("用户名或密码错!","打字测试系统",MB_OK);	//注释在书上4.2.4节
		GetDlgItem(IDC_EIDT_USERID)->SetFocus();			//注释在书上4.2.4节
		return;
	}
	else
	{	//身份合法
		_variant_t vUserRight = m_pRecordset->GetCollect("UserRight");	//注释在书上4.2.4节
		//注释在书上4.2.4节
		_variant_t vUserName = m_pRecordset->GetCollect("UserName");	//注释在书上4.2.4节
		m_lUserRight=vUserRight.lVal;		//注释在书上4.2.4节
		m_strUserName=vUserName.bstrVal;	//注释在书上4.2.4节
		m_pRecordset->Close();				//注释在书上4.2.4节
	}
	
	CDialog::OnOK();
}


