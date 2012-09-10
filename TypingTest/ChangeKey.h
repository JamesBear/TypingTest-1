#if !defined(AFX_CHANGEKEY_H__B3974CD2_DEA9_404E_BCE0_D59C6303524A__INCLUDED_)
#define AFX_CHANGEKEY_H__B3974CD2_DEA9_404E_BCE0_D59C6303524A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeKey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangeKey dialog

class CChangeKey : public CDialog
{
// Construction
public:
	CChangeKey(CWnd* pParent = NULL);   // standard constructor
	_RecordsetPtr m_pRecordset,m_pRecScore; //注释在书上9.5.2节
// Dialog Data
	//{{AFX_DATA(CChangeKey)
	enum { IDD = IDD_DIALOG_CHANGEKEY };
	CString	m_strKeyNew;
	CString	m_strKeyOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangeKey)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEKEY_H__B3974CD2_DEA9_404E_BCE0_D59C6303524A__INCLUDED_)
