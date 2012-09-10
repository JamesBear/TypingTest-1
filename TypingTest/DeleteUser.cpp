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
	m_strSql="SELECT * FROM SysUser";//ע��������9.3.3��
	m_strSql2="SELECT * FROM score "; //ע��������9.3.3��
	m_nIndex=0;				//ע��������9.3.3��
	m_strUserID=" ";			//ע��������9.3.3��

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
	m_pRecordset->Close();		//ע��������9.3.3��
	m_pRecScore->Close();		//ע��������9.3.3��
	
	return CDialog::DestroyWindow();
}

BOOL CDeleteUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//ע��������9.3.3��
	m_UserList.InsertColumn(0,"�û�����",LVCFMT_LEFT,80,0);//ע��������9.3.3��
	m_UserList.InsertColumn(1,"�û�����",LVCFMT_LEFT,80,1); //ע��������9.3.3��
	m_UserList.InsertColumn(2,"�û�Ȩ��",LVCFMT_LEFT,80,2); //ע��������9.3.3����
	DWORD dwExStyle=LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES
		|LVS_EX_HEADERDRAGDROP|LVS_EX_TRACKSELECT; //ע��������9.3.3��
//LVS_EX_TRACKSELECT �����ָ��ĳһ��ʱ���Զ�ѡ�����ӳ����Ϣ LVN_ITEMCHANGED 
	m_UserList.SetExtendedStyle(dwExStyle);	///ע��������9.3.3��
	//ע��������9.3.3��
	m_ScoreList.InsertColumn(0,"��������",LVCFMT_LEFT,80,0);// ע��������9.3.3��
	m_ScoreList.InsertColumn(1,"����ʱ��",LVCFMT_LEFT,80,1); //ע��������9.3.3��
	m_ScoreList.InsertColumn(2,"�ٶ�",LVCFMT_LEFT,80,2); // ע��������9.3.3��
	m_ScoreList.InsertColumn(3,"��ȷ",LVCFMT_LEFT,80,2); //ע��������9.3.3��
	m_ScoreList.InsertColumn(4,"����",LVCFMT_LEFT,80,2); //ע��������9.3.3��
	m_ScoreList.InsertColumn(5,"��ȷ��",LVCFMT_LEFT,80,2); // ע��������9.3.3��
	m_ScoreList.InsertColumn(6,"��������",LVCFMT_LEFT,80,2); // ע��������9.3.3��
	m_ScoreList.InsertColumn(7,"�û�����",LVCFMT_LEFT,80,2); // ע��������9.3.3��
	//ע��������9.3.3��
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");		//ע��������9.3.3��
		//ע��������9.3.3��
		m_pRecordset->Open((_variant_t)m_strSql,
			_variant_t((IDispatch *)theApp.m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);//ע��������9.3.3��
	}
	catch(_com_error e)//ע��������9.3.3��
	{
		AfxMessageBox("��ȡ���ݿ�ʧ��!"); //ע��������9.3.3��
	}

	int nItem;
	_variant_t vUserID,vUserName,vUserRight;
	CString temp;
	//ע��������9.3.3��
	m_pRecordset->MoveFirst();			//ע��������9.3.3��
	while(!m_pRecordset->adoEOF)			// ע��������9.3.3��
	{
		vUserID = m_pRecordset->GetCollect("UserId");		//ע��������9.3.3��
		vUserName = m_pRecordset->GetCollect("UserName"); 	//ע��������9.3.3��
		vUserRight = m_pRecordset->GetCollect("UserRight");	//ע��������9.3.3��

		nItem=m_UserList.InsertItem(0xffff,(_bstr_t)vUserID); //ע��������9.3.3��
		m_UserList.SetItem(nItem,0,1,(_bstr_t)vUserID,NULL,0,0,0); // ע��������9.3.3��
		m_UserList.SetItem(nItem,1,1,(_bstr_t)vUserName,NULL,0,0,0); //ע��������9.3.3��
		m_UserList.SetItem(nItem,2,1,(_bstr_t)vUserRight.lVal,NULL,0,0,0); //ע��������9.3.3��
		m_pRecordset->MoveNext();		//ע��������9.3.3��
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDeleteUser::OnItemchangedListUser(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	POSITION pos = m_UserList.GetFirstSelectedItemPosition();	//ע��������9.3.3��
	 m_nIndex = m_UserList.GetNextSelectedItem(pos);  //ע��������9.3.3��

	 m_strUserID=m_UserList.GetItemText(m_nIndex,0); //ע��������9.3.3��

	 m_ScoreList.DeleteAllItems(); 	//ע��������9.3.3��

	//ע��������9.3.3��

	try
	{
		m_pRecScore.CreateInstance("ADODB.Recordset");//ע��������9.3.3��
		m_pRecScore->Open((_variant_t)m_strSql2,
			_variant_t((IDispatch *)theApp.m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText); // ע��������9.3.3��
	}
	catch(_com_error e) //ע��������9.3.3��
	{
		AfxMessageBox("��ȡ���ݿ�ʧ��!"); //ע��������9.3.3��
		return;
	}

	int nItem;
	_variant_t vUserID,vTestDate,vTestTime,vSpeed,vRight,vWrong,vTestFile,vPercent;
	CString temp;
	if(!m_pRecScore->adoEOF)m_pRecScore->MoveFirst();		//ע��������9.3.3��
	while(!m_pRecScore->adoEOF)							//ע��������9.3.3��.
	{

		vUserID = m_pRecScore->GetCollect("UserId");//ע��������9.3.3��
		if(m_strUserID==vUserID.bstrVal)		//ע��������9.3.3��
		{
			vTestDate = m_pRecScore->GetCollect("TestDate");	//ע��������9.3.3��
			vTestTime = m_pRecScore->GetCollect("EndTestTime");//ע��������9.3.3��
			vSpeed = m_pRecScore->GetCollect("Speed");			//ע��������9.3.3��
			vRight = m_pRecScore->GetCollect("Right");			//ע��������9.3.3��
			vWrong = m_pRecScore->GetCollect("Wrong");			//ע��������9.3.3��
			vPercent=m_pRecScore->GetCollect("Percent");		//ע��������9.3.3��
			vTestFile   = m_pRecScore->GetCollect("TestFile");		//ע��������9.3.3��
			//ע��������9.3.3��
			nItem=m_ScoreList.InsertItem(0xffff,(_bstr_t)vTestDate);		//ע��������9.3.3��
			m_ScoreList.SetItem(nItem,0,1,(_bstr_t)vTestDate,NULL,0,0,0);	//ע��������9.3.3��
			m_ScoreList.SetItem(nItem,1,1,(_bstr_t)vTestTime,NULL,0,0,0); // ע��������9.3.3��
			m_ScoreList.SetItem(nItem,2,1,(_bstr_t)vSpeed,NULL,0,0,0); // ע��������9.3.3��
			m_ScoreList.SetItem(nItem,3,1,(_bstr_t)vRight,NULL,0,0,0); // ע��������9.3.3��
			m_ScoreList.SetItem(nItem,4,1,(_bstr_t)vWrong,NULL,0,0,0); // ע��������9.3.3��
			m_ScoreList.SetItem(nItem,5,1,(_bstr_t)vPercent,NULL,0,0,0); // ע��������9.3.3��
			m_ScoreList.SetItem(nItem,6,1,(_bstr_t)vTestFile,NULL,0,0,0); // ע��������9.3.3��
			m_ScoreList.SetItem(nItem,7,1,(_bstr_t)vUserID,NULL,0,0,0); //ע��������9.3.3��

		}
		m_pRecScore->MoveNext();//ע��������9.3.3��
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
			// ע��������9.3.3��
			m_pRecordset->Move(m_nIndex,_variant_t((long)adBookmarkFirst));
			m_UserList.DeleteItem(m_nIndex);		// ע��������9.3.3��
			
			int count = m_UserList.GetItemCount();		//ע��������9.3.3��
			if(count <= m_nIndex)
				m_nIndex = count-1;				// ע��������9.3.3��
			m_pRecordset->Delete(adAffectCurrent);	//ע��������9.3.3��
			// ע��������9.3.3��
			m_pRecordset->Update();				// ע��������9.3.3��
			// ע��������9.3.3��
			if(!m_pRecScore->adoEOF)m_pRecScore->MoveFirst();		//ע��������9.3.3��
			while(!m_pRecScore->adoEOF)			//ע��������9.3.3��
			{
				vUserID = m_pRecScore->GetCollect("UserId");//ע��������9.3.3��
				if(m_strUserID==vUserID.bstrVal) // ע��������9.3.3��
				{
					m_pRecScore->Delete(adAffectCurrent);	//ע��������9.3.3��
				}
				m_pRecScore->MoveNext();	//ע��������9.3.3��
		}	
		}
		catch(_com_error *e)
		{
			AfxMessageBox(e->ErrorMessage());
		}
		m_UserList.SetFocus();//ע��������9.3.3��
	}
	m_strUserID=""; //ע��������9.3.3��
	
}
