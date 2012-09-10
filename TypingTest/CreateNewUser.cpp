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
	m_strSql="SELECT * FROM SysUser ";//ע��������9.1.3��
	//ע��������9.1.3��
	m_pRecordset.CreateInstance("ADODB.Recordset");
	//ע��������9.1.3��

	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");//ע��������9.1.3��
		m_pRecordset->Open((_variant_t)m_strSql,
			_variant_t((IDispatch *)theApp.m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);//ע��������9.1.3�� 
	}
	catch(_com_error e)//ע��������9.1.3��
	{
		AfxMessageBox("��ȡ���ݿ�ʧ��!");//ע��������9.1.3��
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
	UpdateData(TRUE);				//ע��������9.1.3��
	if(m_strUserKey!=m_strUserKey2)	//ע��������9.1.3��
	{
		MessageBox("�������벻һ��","���ֲ���ϵͳ",MB_OK);
		return;
	}

	m_pRecordset->MoveFirst();			//ע��������9.1.3��
	while(!m_pRecordset->adoEOF)			//ע��������9.1.3��
	{
		vUserID = m_pRecordset->GetCollect("UserId");	//ע��������9.1.3��
		if(m_strUserID==vUserID.bstrVal)			//ע��������9.1.3��
		{
			MessageBox("�û����Ѿ�����ʹ��,�����!","���ֲ���ϵͳ!",MB_OK);
			return;
		}
		m_pRecordset->MoveNext();		//ע��������9.1.3��
	}	
	//ע��������9.1.3��
	m_pRecordset->AddNew();		//ע��������9.1.3��
	if(!m_pRecordset->adoEOF )
	{
		vUserID = m_strUserID;		//ע��������9.1.3��
		vUserName = m_strUserName;	//ע��������9.1.3��
		vUserKey = m_strUserKey;	//ע��������9.1.3��
		vUserRight=theApp.m_lUserRight;//ע��������9.1.3��	
			
		m_pRecordset->PutCollect("UserId",vUserID);			//ע��������9.1.3��
		m_pRecordset->PutCollect("UserName",vUserName);
		m_pRecordset->PutCollect("UserKey",vUserKey);
		m_pRecordset->PutCollect("UserRight",vUserRight);
		m_pRecordset->Update();

	} //ע��������9.1.3��
	MessageBox("ע��ɹ����������µ�¼!","���ֲ���ϵͳ!",MB_OK|MB_ICONWARNING);
	
	CDialog::OnOK();
}

void CCreateNewUser::OnNewIdTest() 
{
	// TODO: Add your control notification handler code here
	////ע��������9.1.3��
	UpdateData(TRUE);					//ע��������9.1.3��
	m_pRecordset->MoveFirst();			//ע��������9.1.3��
	while(!m_pRecordset->adoEOF)			//ע��������9.1.3��
	{
		_variant_t vUserID;
		vUserID = m_pRecordset->GetCollect("UserId");
		CString strTemp=vUserID.bstrVal;
		if(m_strUserID==strTemp)			//ע��������9.1.3��
		{
			MessageBox("������û����Ѿ�����ʹ��,�����!","����!",MB_OK|MB_ICONWARNING);
			m_strUserID.Empty();			//ע��������9.1.3��
			GetDlgItem(IDC_NEWUSER_ID)->SetFocus();	//ע��������9.1.3��
			UpdateData(FALSE);						//ע��������9.1.3��
			return;
		}
		m_pRecordset->MoveNext();		//ע��������9.1.3��
	}		
	MessageBox("������û���û����ʹ��!", "����!",MB_OK|MB_ICONWARNING);

	
}

BOOL CCreateNewUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
		if(m_strCaption.GetLength())		//ע��������9.1.3�� 
		SetWindowText(m_strCaption);	     //ע��������9.1.3��

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
