// TypingTestDoc.cpp : implementation of the CTypingTestDoc class
//

#include "stdafx.h"
#include "TypingTest.h"

#include "TypingTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTypingTestDoc

IMPLEMENT_DYNCREATE(CTypingTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CTypingTestDoc, CDocument)
	//{{AFX_MSG_MAP(CTypingTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTypingTestDoc construction/destruction

CTypingTestDoc::CTypingTestDoc()
{
	// TODO: add one-time construction code here
	//ע��������3.1.1��
	m_strMessage1="������ѧͨVisal C++��";
	m_strMessage2="������";
	m_strMessage3="    ֻҪ���߰�����������ȥѧ������ȥ����ѧ��һ�¾ͻ�����";
	m_strMessage4="�����һ���֣��ǿ�ִ���ļ������ڽ��棬���гɾ͸У��ܼ���";
	m_strMessage5="���ߵ���Ȥ���������ߵĻ����ԣ�����ȫ�顣ѧ��ȫ��ͻ�����";
	m_strMessage6="�����Ĵ��ֲ���ϵͳ�����߿����Լ����������Լ��Ĵ����ٶȣ�";
	m_strMessage7="Ҳ�ɹ����Ѻ�ͬѧʹ�á�����������������Σ���󲻿�������";
	m_strMessage8="���������������VC�ĳ��ù��ܡ��������⣬�ɺ�������ϵ��";

	m_strMessage9="QQ:156567789";
	m_strMessage10="Email:YZDXWYP@126.COM";
	//ע��������3.1.1��
}

CTypingTestDoc::~CTypingTestDoc()
{
}

BOOL CTypingTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTypingTestDoc serialization

void CTypingTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTypingTestDoc diagnostics

#ifdef _DEBUG
void CTypingTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTypingTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTypingTestDoc commands
