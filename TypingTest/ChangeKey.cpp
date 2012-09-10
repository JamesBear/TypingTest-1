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
		char m_strSql[256];		//注释在书上9.5.3节
	strcpy(m_strSql,"SELECT * FROM SysUser WHERE UserId='"+theApp.m_strUserID+"'" );//9.5.3

	//注释在书上9.5.3节	
	m_pRecordset.CreateInstance("ADODB.Recordset");
	//注释在书上9.5.3节
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");////注释在书上9.5.3节
		m_pRecordset->Open((_variant_t)m_strSql,
			_variant_t((IDispatch *)theApp.m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);		//注释在书上9.5.3节
	}
	catch(_com_error e)		//注释在书上9.5.3节
	{
		AfxMessageBox("读取数据库失败!");		//注释在书上9.5.3节
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
	UpdateData(TRUE);				//注释在书上9.5.3节
	if(m_strKeyNew!=m_strKeyOK)		//注释在书上9.5.3节
	{
		MessageBox("两次密码不一致","打字测试系统",MB_OK);
		return;
	}
	vUserKey = m_strKeyNew;			//注释在书上9.5.3节
	m_pRecordset->PutCollect("UserKey",vUserKey);	//注释在书上9.5.3节
	m_pRecordset->Update();					//注释在书上9.5.3节
	MessageBox("密码修改成功","打字测试系统",MB_OK);
	
	CDialog::OnOK();
}
