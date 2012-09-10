// TypingTest.h : main header file for the TYPINGTEST application
//

#if !defined(AFX_TYPINGTEST_H__B3A5DA84_4A94_47B4_9C52_6B5271C9C22B__INCLUDED_)
#define AFX_TYPINGTEST_H__B3A5DA84_4A94_47B4_9C52_6B5271C9C22B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTypingTestApp:
// See TypingTest.cpp for the implementation of this class
//

class CTypingTestApp : public CWinApp
{
public:
	CTypingTestApp();
	//注释在书上4.2.4节
	//注释在书上4.2.4节
	_ConnectionPtr m_pConnection;
	CString m_strUserName;		//注释在书上4.2.4节
	long m_lUserRight;			//注释在书上4.2.4节
	CString m_strUserID;		//注释在书上4.2.4节
	CString m_strDate;  		//注释在书上6.2.2节
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTypingTestApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTypingTestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CTypingTestApp theApp;//4.2.4为CTypingTestView类访问应用程序类作准备。
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TYPINGTEST_H__B3A5DA84_4A94_47B4_9C52_6B5271C9C22B__INCLUDED_)
