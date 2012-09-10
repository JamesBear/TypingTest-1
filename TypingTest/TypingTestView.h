// TypingTestView.h : interface of the CTypingTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TYPINGTESTVIEW_H__682B5D9C_64E6_4B2A_B395_3FF41AE38859__INCLUDED_)
#define AFX_TYPINGTESTVIEW_H__682B5D9C_64E6_4B2A_B395_3FF41AE38859__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TypingTestDoc.h" 		//8.5.4����Ҫ�����ĵ���

class CTypingTestView : public CView
{
protected: // create from serialization only
	CTypingTestView();
	DECLARE_DYNCREATE(CTypingTestView)
	//ע��������3.1.2��
	CFont startFont1,startFont2,startFont3;		//ע��������3.1.2��
	BOOL m_bTestRead;		//ע��������3.1.2��
	
	//ע��������5.2.2��
	BOOL m_bTestEnglish;	//ע��������5.2.2��
	BOOL m_bTestBegin;		//ע��������5.2.2��
	//7.1.1
	CFile openFileName;			//ע��������7.1.1��
	TEXTMETRIC tm;				//ע��������7.1.1��
	char m_OutBuf[12][83];		//ע��������7.1.1��
	char m_InBuf[12][83];		//ע��������7.1.1�� 
	int iInH;					//ע��������7.1.1��

    int currentLine,currentCol;	//ע��������7.1.1��
    int height;					//ע��������7.1.1��
	int width;					//ע��������7.1.1��
	long inputRight,inputWrong,inputTotal;	//ע��������7.1.1��
	long m_lTestTime;			//ע��������7.1.1��
	char m_strTestFile[128];	//ע��������7.1.1��
	CString strNoteMessage;		//ע��������7.1.1��
	//7.3.1
	int coli;					//ע��������7.3.1��
	int byte1;					//ע��������7.3.1��
	CString strInCh,strOutCh;	//ע��������7.3.1��
	BOOL bLastKeyIsBlank;       //������Ե�λΪÿ���Ӷ��ٸ�����,��һ��������ǿո�
	BOOL bWordIsTrue;			//����ĵ����ǶԵ�
	BOOL bWordCount;			//���ʿ�ʼ

// Attributes
public:
	CTypingTestDoc* GetDocument();

// Operations
public:
	void DisplayEnglish(CDC* pDC);		//ע��������7.2.1��
	void DisplayChinese(CDC *pDC);		//ע��������7.2.1��
	void TestEnd();						//ע��������8.1.1��
	void OnCharEnglish(UINT nChar);		//ע��������8.2.2��
		void OnCharChinese(UINT nChar);//ע��������8.5.1��
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
	void LoadEnglisFile(LPCSTR strFileName);//ע��������7.1.1��

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
	afx_msg void OnRight(CCmdUI* pCmdUI) ;				//ע��������6.3.3��
	afx_msg void OnWrong(CCmdUI* pCmdUI) ;				//ע��������6.3.3��
	afx_msg void OnSpeed(CCmdUI* pCmdUI) ;				//ע��������6.3.3��
	afx_msg void OnRightPercent(CCmdUI* pCmdUI) ;		//ע��������6.3.3��
	afx_msg void OnTestTime(CCmdUI* pCmdUI) ;			//ע��������6.3.3��
	afx_msg void OnTestFile(CCmdUI* pCmdUI) ;			//ע��������6.3.3��
	afx_msg void OnUserName(CCmdUI* pCmdUI) ;			//ע��������6.3.3��
	    afx_msg void OnNoteMessage(CCmdUI* pCmdUI) ;	//ע��������6.3.3��

	DECLARE_MESSAGE_MAP()
	private:				//8.2.2

		CPoint PosCaret;	//ע��������8.2.2��

};

#ifndef _DEBUG  // debug version in TypingTestView.cpp
inline CTypingTestDoc* CTypingTestView::GetDocument()
   { return (CTypingTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TYPINGTESTVIEW_H__682B5D9C_64E6_4B2A_B395_3FF41AE38859__INCLUDED_)
