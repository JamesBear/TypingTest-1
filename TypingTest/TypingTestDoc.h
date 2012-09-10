// TypingTestDoc.h : interface of the CTypingTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TYPINGTESTDOC_H__C37D4029_3545_4C33_AFFF_0764B4DE1810__INCLUDED_)
#define AFX_TYPINGTESTDOC_H__C37D4029_3545_4C33_AFFF_0764B4DE1810__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTypingTestDoc : public CDocument
{
protected: // create from serialization only
	CTypingTestDoc();
	DECLARE_DYNCREATE(CTypingTestDoc)

// Attributes
public:
	CString m_strMessage1,m_strMessage2,m_strMessage3,m_strMessage4,m_strMessage5;//注释在书上3.1.1节
	CString m_strMessage6,m_strMessage7,m_strMessage8,m_strMessage9,m_strMessage10;//注释在书上3.1.1节

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTypingTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTypingTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTypingTestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TYPINGTESTDOC_H__C37D4029_3545_4C33_AFFF_0764B4DE1810__INCLUDED_)
