#if !defined(AFX_CREATENEWUSER_H__9627D4DB_CE76_4D61_85FF_770283A9FEDE__INCLUDED_)
#define AFX_CREATENEWUSER_H__9627D4DB_CE76_4D61_85FF_770283A9FEDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CreateNewUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreateNewUser dialog

class CCreateNewUser : public CDialog
{
// Construction
public:
	CCreateNewUser(CWnd* pParent = NULL);   // standard constructor
	CString m_strCaption;			//ע��������9.1.2�� 
	_RecordsetPtr m_pRecordset; 	//ע��������9.1.2��
	CString m_strSql;				//ע��������9.1.2��

// Dialog Data
	//{{AFX_DATA(CCreateNewUser)
	enum { IDD = IDD_NEW_USER };
	CString	m_strUserID;
	CString	m_strUserKey;
	CString	m_strUserKey2;
	CString	m_strUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateNewUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCreateNewUser)
	virtual void OnOK();
	afx_msg void OnNewIdTest();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATENEWUSER_H__9627D4DB_CE76_4D61_85FF_770283A9FEDE__INCLUDED_)
