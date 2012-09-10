#if !defined(AFX_DELETEUSER_H__98D98292_AFE4_455B_AAD5_978227FCA3F4__INCLUDED_)
#define AFX_DELETEUSER_H__98D98292_AFE4_455B_AAD5_978227FCA3F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeleteUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeleteUser dialog

class CDeleteUser : public CDialog
{
// Construction
public:
	CDeleteUser(CWnd* pParent = NULL);   // standard constructor
	//注释在书上9.3.2节
	_RecordsetPtr m_pRecordset,m_pRecScore; 	//注释在书上9.3.2节
	CString m_strSql,m_strSql2;					//注释在书上9.3.2节
	CString m_strUserID;						//注释在书上9.3.2节
	int m_nIndex;							//注释在书上9.3.2节

// Dialog Data
	//{{AFX_DATA(CDeleteUser)
	enum { IDD = IDD_DIALOG_DELUSER };
	CListCtrl	m_ScoreList;
	CListCtrl	m_UserList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeleteUser)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeleteUser)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedListUser(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUserDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELETEUSER_H__98D98292_AFE4_455B_AAD5_978227FCA3F4__INCLUDED_)
