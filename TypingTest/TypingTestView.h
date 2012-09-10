// TypingTestView.h : interface of the CTypingTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TYPINGTESTVIEW_H__682B5D9C_64E6_4B2A_B395_3FF41AE38859__INCLUDED_)
#define AFX_TYPINGTESTVIEW_H__682B5D9C_64E6_4B2A_B395_3FF41AE38859__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TypingTestDoc.h" 		//8.5.4视类要访问文档类

class CTypingTestView : public CView
{
protected: // create from serialization only
	CTypingTestView();
	DECLARE_DYNCREATE(CTypingTestView)
	//注释在书上3.1.2节
	CFont startFont1,startFont2,startFont3;		//注释在书上3.1.2节
	BOOL m_bTestRead;		//注释在书上3.1.2节
	
	//注释在书上5.2.2节
	BOOL m_bTestEnglish;	//注释在书上5.2.2节
	BOOL m_bTestBegin;		//注释在书上5.2.2节
	//7.1.1
	CFile openFileName;			//注释在书上7.1.1节
	TEXTMETRIC tm;				//注释在书上7.1.1节
	char m_OutBuf[12][83];		//注释在书上7.1.1节
	char m_InBuf[12][83];		//注释在书上7.1.1节 
	int iInH;					//注释在书上7.1.1节

    int currentLine,currentCol;	//注释在书上7.1.1节
    int height;					//注释在书上7.1.1节
	int width;					//注释在书上7.1.1节
	long inputRight,inputWrong,inputTotal;	//注释在书上7.1.1节
	long m_lTestTime;			//注释在书上7.1.1节
	char m_strTestFile[128];	//注释在书上7.1.1节
	CString strNoteMessage;		//注释在书上7.1.1节
	//7.3.1
	int coli;					//注释在书上7.3.1节
	int byte1;					//注释在书上7.3.1节
	CString strInCh,strOutCh;	//注释在书上7.3.1节
	BOOL bLastKeyIsBlank;       //处理测试单位为每分钟多少个单词,上一次输入的是空格
	BOOL bWordIsTrue;			//输入的单词是对的
	BOOL bWordCount;			//单词开始

// Attributes
public:
	CTypingTestDoc* GetDocument();

// Operations
public:
	void DisplayEnglish(CDC* pDC);		//注释在书上7.2.1节
	void DisplayChinese(CDC *pDC);		//注释在书上7.2.1节
	void TestEnd();						//注释在书上8.1.1节
	void OnCharEnglish(UINT nChar);		//注释在书上8.2.2节
		void OnCharChinese(UINT nChar);//注释在书上8.5.1节
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTypingTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTypingTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void LoadEnglisFile(LPCSTR strFileName);//注释在书上7.1.1节

// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	void DisplayState(CDC *pDC);
	//{{AFX_MSG(CTypingTestView)
	afx_msg void OnTestEnglish();
	afx_msg void OnTestChinese();
	afx_msg void OnScoreUnion();
	afx_msg void OnScorePersonall();
	afx_msg void OnTestStop();
	afx_msg void OnUserCreate();
	afx_msg void OnUserDel();
	afx_msg void OnUserLogout();
	afx_msg void OnUpdateUserLogout(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUserDel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUserCreate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTestStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTestEnglish(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTestChinese(CCmdUI* pCmdUI);
	afx_msg void OnUpdateScoreUnion(CCmdUI* pCmdUI);
	afx_msg void OnUpdateScorePersonall(CCmdUI* pCmdUI);
	afx_msg void OnChangeKey();
	afx_msg void OnUpdateChangeKey(CCmdUI* pCmdUI);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHelpFinder();
	//}}AFX_MSG
	afx_msg void OnRight(CCmdUI* pCmdUI) ;				//注释在书上6.3.3节
	afx_msg void OnWrong(CCmdUI* pCmdUI) ;				//注释在书上6.3.3节
	afx_msg void OnSpeed(CCmdUI* pCmdUI) ;				//注释在书上6.3.3节
	afx_msg void OnRightPercent(CCmdUI* pCmdUI) ;		//注释在书上6.3.3节
	afx_msg void OnTestTime(CCmdUI* pCmdUI) ;			//注释在书上6.3.3节
	afx_msg void OnTestFile(CCmdUI* pCmdUI) ;			//注释在书上6.3.3节
	afx_msg void OnUserName(CCmdUI* pCmdUI) ;			//注释在书上6.3.3节
	    afx_msg void OnNoteMessage(CCmdUI* pCmdUI) ;	//注释在书上6.3.3节

	DECLARE_MESSAGE_MAP()
	private:				//8.2.2

		CPoint PosCaret;	//注释在书上8.2.2节

};

#ifndef _DEBUG  // debug version in TypingTestView.cpp
inline CTypingTestDoc* CTypingTestView::GetDocument()
   { return (CTypingTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TYPINGTESTVIEW_H__682B5D9C_64E6_4B2A_B395_3FF41AE38859__INCLUDED_)
