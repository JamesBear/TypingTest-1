#if !defined(AFX_FINDSCORE_H__5FD23FA5_B9F5_4B5B_89FE_F3BA7D6634C8__INCLUDED_)
#define AFX_FINDSCORE_H__5FD23FA5_B9F5_4B5B_89FE_F3BA7D6634C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindScore.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindScore dialog

class CFindScore : public CDialog
{
// Construction
public:
	CFindScore(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bFindAll;//注释在书上9.4.2节 
	CString m_strCaption;	//注释在书上9.4.2节
	_RecordsetPtr m_pRecordset; //注释在书上9.4.2节
	CString m_strSql;			//注释在书上9.4.2节

// Dialog Data
	//{{AFX_DATA(CFindScore)
	enum { IDD = IDD_DIALOG_FINDSCORE };
	CListCtrl	m_CtrlFindScore;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindScore)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindScore)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDSCORE_H__5FD23FA5_B9F5_4B5B_89FE_F3BA7D6634C8__INCLUDED_)
