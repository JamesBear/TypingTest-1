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
	//注释在书上3.1.1节
	m_strMessage1="《轻松学通Visal C++》";
	m_strMessage2="编者语";
	m_strMessage3="    只要读者按书上所讲的去学，并且去做，学完一章就会做出";
	m_strMessage4="软件的一部分，是可执行文件，窗口界面，会有成就感！能激发";
	m_strMessage5="读者的兴趣，调动读者的积极性，读完全书。学完全书就会做出";
	m_strMessage6="完整的打字测试系统！读者可以自己用来测试自己的打字速度，";
	m_strMessage7="也可供朋友和同学使用。读者照着书多做几次，最后不看书能做";
	m_strMessage8="出软件，就能掌握VC的常用功能。如有问题，可和作者联系。";

	m_strMessage9="QQ:156567789";
	m_strMessage10="Email:YZDXWYP@126.COM";
	//注释在书上3.1.1节
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
