// ChangeKey.cpp : implementation file
//

#include "stdafx.h"
#include "TypingTest.h"
#include "ChangeKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeKey dialog


CChangeKey::CChangeKey(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeKey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeKey)
	m_strKeyNew = _T("");
	m_strKeyOK = _T("");
	//}}AFX_DATA_INIT
		char m_strSql[256];		//ע��������9.5.3��
	strcpy(m_strSql,"SELECT * FROM SysUser WHERE UserId='"+theApp.m_strUserID+"'" );//9.5.3

	//ע��������9.5.3��	
	m_pRecordset.CreateInstance("ADODB.Recordset");
	//ע��������9.5.3��
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");////ע��������9.5.3��
		m_pRecordset->Open((_variant_t)m_strSql,
			_variant_t((IDispatch *)theApp.m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);		//ע��������9.5.3��
	}
	catch(_com_error e)		//ע��������9.5.3��
	{
		AfxMessageBox("��ȡ���ݿ�ʧ��!");		//ע��������9.5.3��
	}

}


void CChangeKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeKey)
	DDX_Text(pDX, IDC_EDIT_KEYNEW, m_strKeyNew);
	DDX_Text(pDX, IDC_EDIT_KEYOK, m_strKeyOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeKey, CDialog)
	//{{AFX_MSG_MAP(CChangeKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeKey message handlers

void CChangeKey::OnOK() 
{
	// TODO: Add extra validation here
	_variant_t vUserID,vUserName,vUserKey,vUserRight;
	UpdateData(TRUE);				//ע��������9.5.3��
	if(m_strKeyNew!=m_strKeyOK)		//ע��������9.5.3��
	{
		MessageBox("�������벻һ��","���ֲ���ϵͳ",MB_OK);
		return;
	}
	vUserKey = m_strKeyNew;			//ע��������9.5.3��
	m_pRecordset->PutCollect("UserKey",vUserKey);	//ע��������9.5.3��
	m_pRecordset->Update();					//ע��������9.5.3��
	MessageBox("�����޸ĳɹ�","���ֲ���ϵͳ",MB_OK);
	
	CDialog::OnOK();
}
