// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TypingTest.h"
#include "LoginDlg.h"

#include "CreateNewUser.h"  					//ע��������9.1.4��
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
	// ע��������4.2.4��
	nLoginNum=0;		//ע��������4.2.4��

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
	//ע��������9.1.4��
	CCreateNewUser NewUserDlg;				//ע��������9.1.4��
	NewUserDlg.m_strCaption="ע�����û�";	//ע��������9.1.4��
	NewUserDlg.DoModal();					//ע��������9.1.4��
	//ע��������9.1.4��
	
}

void CLoginDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CLoginDlg::OnOK() 
{
	// TODO: Add extra validation here
	//ע��������4.2.4��
	UpdateData(TRUE);			//ע��������4.2.4��
	char m_strSql[256];CString str = _T("");
	strcpy(m_strSql,"SELECT * FROM SysUser WHERE UserId='"+m_strUserID+"'"+" AND UserKey='"+m_strLoginPassWord+"'" );//ע��������4.2.4��

	//ע��������4.2.4��
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");		//ע��������4.2.4��
		m_pRecordset->Open((_variant_t)m_strSql,
			_variant_t((IDispatch *)theApp.m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);										// ע��������4.2.4��
	}
	catch(_com_error e)										//ע��������4.2.4��
	{
		CString errormessage;
		errormessage.Format("��ѯȡ�ü�¼��ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		MessageBox(m_strSql,errormessage,MB_OK);			//ע��������4.2.4��
	}
	if(m_pRecordset->adoEOF)								//ע��������4.2.4��
	{
	nLoginNum++;
		if(nLoginNum>=3){									//ע��������4.2.4�ڡ�
			MessageBox("�Ƿ��û�","���ֲ���ϵͳ",MB_OK);	//ע��������4.2.4��
			CDialog::OnCancel();
			return;
		}
		MessageBox("�û����������!","���ֲ���ϵͳ",MB_OK);	//ע��������4.2.4��
		GetDlgItem(IDC_EIDT_USERID)->SetFocus();			//ע��������4.2.4��
		return;
	}
	else
	{	//��ݺϷ�
		_variant_t vUserRight = m_pRecordset->GetCollect("UserRight");	//ע��������4.2.4��
		//ע��������4.2.4��
		_variant_t vUserName = m_pRecordset->GetCollect("UserName");	//ע��������4.2.4��
		m_lUserRight=vUserRight.lVal;		//ע��������4.2.4��
		m_strUserName=vUserName.bstrVal;	//ע��������4.2.4��
		m_pRecordset->Close();				//ע��������4.2.4��
	}
	
	CDialog::OnOK();
}


