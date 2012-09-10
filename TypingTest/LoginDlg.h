#if !defined(AFX_LOGINDLG_H__7F742436_2020_4290_8B2F_5A66ABF44BF0__INCLUDED_)
#define AFX_LOGINDLG_H__7F742436_2020_4290_8B2F_5A66ABF44BF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog

class CLoginDlg : public CDialog
{
	//ע��������4.2.4��
	_RecordsetPtr m_pRecordset; 	//ע��������4.2.4��
	int nLoginNum;					//ע��������4.2.4��
// Construction
public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor
	
	long m_lUserRight;				//ע��������4.2.4��
	CString m_strUserName; 			//ע��������4.2.4��

// Dialog Data
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_DIALOG_LOGIN };
	CString	m_strUserID;
	CString	m_strLoginPassWord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginDlg)
	afx_msg void OnButtonNewuser();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__7F742436_2020_4290_8B2F_5A66ABF44BF0__INCLUDED_)
