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
	m_strSql="SELECT * FROM score ORDER BY UserId";//ע��������9.4.3��
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
	m_pRecordset->Close();		//ע��������9.4.3��
	delete this;				//ע��������9.4.3��
	
	return CDialog::DestroyWindow();
}

BOOL CFindScore::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if ( m_strCaption.GetLength() )SetWindowText( m_strCaption );//ע��������9.4.3��
	
	m_CtrlFindScore.InsertColumn(0,"��������",LVCFMT_LEFT,80,0); //ע��������9.4.3��
	m_CtrlFindScore.InsertColumn(1,"����ʱ��",LVCFMT_LEFT,80,1);//ע��������9.4.3��
	m_CtrlFindScore.InsertColumn(2,"�ٶ�",LVCFMT_LEFT,80,2);//ע��������9.4.3��
	m_CtrlFindScore.InsertColumn(3,"��ȷ",LVCFMT_LEFT,80,2);//ע��������9.4.3��
	m_CtrlFindScore.InsertColumn(4,"����",LVCFMT_LEFT,80,2);// 9.4.3������
	m_CtrlFindScore.InsertColumn(5,"��ȷ��",LVCFMT_LEFT,80,2);// 9.4.3��ȷ����
	m_CtrlFindScore.InsertColumn(6,"��������",LVCFMT_LEFT,80,2);// 9.4.3�ļ�����
	DWORD dwExStyle=LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES 
		|LVS_EX_HEADERDRAGDROP|LVS_EX_TRACKSELECT; //9.4.3�б�ؼ���������
	m_CtrlFindScore.SetExtendedStyle(dwExStyle);	//9.5.3������չ���

	//��4-2�� ����Recordset�����ʵ��	
	m_pRecordset.CreateInstance("ADODB.Recordset");
	//��4-3��ֱ����Recordset������в�ѯȡ�ü�¼��
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");//9.4.3����Recordset����
		m_pRecordset->Open((_variant_t)m_strSql,
			_variant_t((IDispatch *)theApp.m_pConnection,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);// 9.4.3ȡ�ü�¼��
	}
	catch(_com_error e)// 9.4.3��׽�쳣
	{
		AfxMessageBox("��ȡ���ݿ�ʧ��!");// 9.4.3��ʾ������Ϣ
	}
	//��5���Լ�¼�����б���
	int nItem;
	_variant_t vUserID,vTestDate,vTestTime,vSpeed,vRight,vWrong,vTestFile,vPercent;
	CString temp;
	m_pRecordset->MoveFirst();		//��5-1���Ƶ�������¼
    if(!m_bFindAll)	//9.5.3��ѯ�����û��ĳɼ�
	{
		while(!m_pRecordset->adoEOF)		 //��5-2��������¼�����û�������û����Ƿ�����ʹ��.
		{
			vUserID = m_pRecordset->GetCollect("UserId");		//��5-3����ȡ��¼����ָ���ֶε�ֵ
			if(theApp.m_strUserID==vUserID.bstrVal)			//9.4.3����Ǹ��û�
			{
				vTestDate = m_pRecordset->GetCollect("TestDate"); 	//9.4.3�����������ֶ�
				vTestTime = m_pRecordset->GetCollect("EndTestTime");	//9.4.3ȡ�ò���ʱ��
				vSpeed = m_pRecordset->GetCollect("Speed");	//9.4.3��ȡ�����ٶ�
				vRight = m_pRecordset->GetCollect("Right");	//9.4.3��ȡ������ַ���ȷ��
				vWrong = m_pRecordset->GetCollect("Wrong");		//9.4.3��ȡ������ַ�������
				vPercent=m_pRecordset->GetCollect("Percent");		//9.4.3��ȡ�������ȷ��ѡ��
				vTestFile   = m_pRecordset->GetCollect("TestFile");		//9.4.3��ȡ���Ե��ļ���
				//9.5.3�ڳɼ����пؼ�����ʾ���û��ļ�¼
				nItem=m_CtrlFindScore.InsertItem(0xffff,(_bstr_t)vTestDate);	//9.4.3������
				//m_CtrlFindScore.SetItem(nItem,0,1,(_bstr_t)vTestDate,NULL,0,0,0); //���ø��еĸ���
				m_CtrlFindScore.SetItem(nItem,1,1,(_bstr_t)vTestTime,NULL,0,0,0);// 9.4.3��ʾʱ��
				m_CtrlFindScore.SetItem(nItem,2,1,(_bstr_t)vSpeed,NULL,0,0,0);// 9.4.3��ʾ�ٶ�
				m_CtrlFindScore.SetItem(nItem,3,1,(_bstr_t)vRight,NULL,0,0,0);// 9.4.3��ʾ��ȷ�ַ���
				m_CtrlFindScore.SetItem(nItem,4,1,(_bstr_t)vWrong,NULL,0,0,0);// 9.4.3��ʾ�����ַ���
				m_CtrlFindScore.SetItem(nItem,5,1,(_bstr_t)vPercent,NULL,0,0,0);// 9.4.3��ʾ��ȷ��
				m_CtrlFindScore.SetItem(nItem,6,1,(_bstr_t)vTestFile,NULL,0,0,0);//���б������ʾ�ļ��� 

			}
			m_pRecordset->MoveNext();		//��5-4���Ƶ���һ����¼
		}	
	}
	else		//9.4.3��ѯ�û����˵ĳɼ�
	{
		m_CtrlFindScore.InsertColumn(7,"�û�����",LVCFMT_LEFT,80,0);

		while(!m_pRecordset->adoEOF)			//��5���Լ�¼�����б������ɼ���.
		{
			vUserID = m_pRecordset->GetCollect("UserId");		//��5-3����ȡ��¼����ָ���ֶε�ֵ
			vTestDate = m_pRecordset->GetCollect("TestDate");//��5-3����ȡ��¼
			vTestTime = m_pRecordset->GetCollect("EndTestTime");//9.4.3����ʱ�� 
			vSpeed = m_pRecordset->GetCollect("Speed");//9.4.3�ٶ�
			vRight = m_pRecordset->GetCollect("Right");//9.4.3��ȷ��
			vWrong = m_pRecordset->GetCollect("Wrong");//9.4.3������
			vPercent=m_pRecordset->GetCollect("Percent");//9.4.3��ȷ��
			vTestFile   = m_pRecordset->GetCollect("TestFile");//9.4.3��ȡ���ĵ��ļ���
			//9.5.3�ڳɼ��б�ؼ��в���һ����ʾ�ɼ���
		nItem=m_CtrlFindScore.InsertItem(0xffff,(_bstr_t)vUserID);// 9.4.3������
			m_CtrlFindScore.SetItem(nItem,7,1,(_bstr_t)vUserID,NULL,0,0,0);// 9.4.3���ø��������е�ֵ
			m_CtrlFindScore.SetItem(nItem,0,1,(_bstr_t)vTestDate,NULL,0,0,0);// 9.4.3��ʾ����
			m_CtrlFindScore.SetItem(nItem,1,1,(_bstr_t)vTestTime,NULL,0,0,0);// 9.4.3��ʾʱ��
			m_CtrlFindScore.SetItem(nItem,2,1,(_bstr_t)vSpeed,NULL,0,0,0);// 9.4.3��ʾ�ٶ�
			m_CtrlFindScore.SetItem(nItem,3,1,(_bstr_t)vRight,NULL,0,0,0);// 9.4.3��ʾ��ȷ��
			m_CtrlFindScore.SetItem(nItem,4,1,(_bstr_t)vWrong,NULL,0,0,0);// 9.4.3��ʾ������
			m_CtrlFindScore.SetItem(nItem,5,1,(_bstr_t)vPercent,NULL,0,0,0);//9.4.3��ʾ��ȷ��
			m_CtrlFindScore.SetItem(nItem,6,1,(_bstr_t)vTestFile,NULL,0,0,0);//9.4.3��ʾ�����ļ���
			m_pRecordset->MoveNext();		//��5-4���Ƶ���һ����¼
		}
	}	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
