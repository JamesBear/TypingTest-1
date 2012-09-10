; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTypingTestView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TypingTest.h"
LastPage=0

ClassCount=10
Class1=CTypingTestApp
Class2=CTypingTestDoc
Class3=CTypingTestView
Class4=CMainFrame

ResourceCount=10
Resource1=IDD_DLGBAR
Resource2=CG_IDR_POPUP_TYPING_TEST_VIEW
Class5=CAboutDlg
Class6=CLoginDlg
Resource3=CG_IDR_POPUP_TYPING_TEST_VIEW1
Resource4=IDD_DIALOG_LOGIN
Resource5=IDD_ABOUTBOX
Resource6=IDD_DIALOG_CHANGEKEY
Resource7=IDD_NEW_USER
Resource8=IDR_MAINFRAME
Resource9=IDD_DIALOG_FINDSCORE
Class7=CCreateNewUser
Class8=CDeleteUser
Class9=CFindScore
Class10=CChangeKey
Resource10=IDD_DIALOG_DELUSER

[CLS:CTypingTestApp]
Type=0
HeaderFile=TypingTest.h
ImplementationFile=TypingTest.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CTypingTestApp

[CLS:CTypingTestDoc]
Type=0
HeaderFile=TypingTestDoc.h
ImplementationFile=TypingTestDoc.cpp
Filter=N

[CLS:CTypingTestView]
Type=0
HeaderFile=TypingTestView.h
ImplementationFile=TypingTestView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CTypingTestView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_HELP_FINDER
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=TypingTest.cpp
ImplementationFile=TypingTest.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_TEST_ENGLISH
Command2=ID_TEST_CHINESE
Command3=ID_TEST_STOP
Command4=ID_APP_EXIT
Command5=ID_USER_CREATE
Command6=ID_CHANGE_KEY
Command7=ID_USER_LOGOUT
Command8=ID_USER_DEL
Command9=ID_VIEW_TOOLBAR
Command10=ID_VIEW_STATUS_BAR
Command11=ID_SCORE_PERSONAL
Command12=ID_SCORE_UNION
Command13=ID_HELP_FINDER
Command14=ID_APP_ABOUT
CommandCount=14

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_SCORE_UNION
Command2=ID_TEST_CHINESE
Command3=ID_USER_DEL
Command4=ID_TEST_ENGLISH
Command5=ID_HELP_FINDER
Command6=ID_CHANGE_KEY
Command7=ID_USER_LOGOUT
Command8=ID_USER_CREATE
Command9=ID_SCORE_PERSONAL
Command10=ID_TEST_STOP
Command11=ID_APP_EXIT
CommandCount=11

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_TEST_CHINESE
Command2=ID_TEST_ENGLISH
Command3=ID_USER_CREATE
Command4=ID_USER_DEL
Command5=ID_CHANGE_KEY
Command6=ID_SCORE_PERSONAL
Command7=ID_SCORE_UNION
Command8=ID_USER_LOGOUT
Command9=ID_APP_ABOUT
Command10=ID_APP_EXIT
CommandCount=10

[DLG:IDD_DIALOG_LOGIN]
Type=1
Class=CLoginDlg
ControlCount=9
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342177283
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EIDT_USERID,edit,1350631552
Control6=IDC_EDIT_LOGINPASSWORD,edit,1350631584
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816
Control9=IDC_BUTTON_NEWUSER,button,1342242816

[CLS:CLoginDlg]
Type=0
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[MNU:CG_IDR_POPUP_TYPING_TEST_VIEW1]
Type=1
Class=?
Command1=ID_TEST_ENGLISH
Command2=ID_TEST_CHINESE
Command3=ID_USER_LOGOUT
CommandCount=3

[MNU:CG_IDR_POPUP_TYPING_TEST_VIEW]
Type=1
Class=?
Command1=ID_TEST_ENGLISH
Command2=ID_TEST_CHINESE
Command3=ID_USER_LOGOUT
CommandCount=3

[DLG:IDD_DLGBAR]
Type=1
Class=?
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_RIGHT,edit,1350631552
Control3=IDC_WRONG,edit,1350631552
Control4=IDC_RIGHT_PERCENT,edit,1350631552
Control5=IDC_TEST_TIME,edit,1350631552
Control6=IDC_TEST_FILE,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_SPEED,edit,1350631552
Control12=IDC_STATIC,static,1342308352

[DLG:IDD_NEW_USER]
Type=1
Class=CCreateNewUser
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_NEWUSER_ID,edit,1350631552
Control6=IDC_NEW_ID_TEST,button,1342242816
Control7=IDC_NEWUSER_NAME,edit,1350631552
Control8=IDC_NEWUSER_KEY,edit,1350631584
Control9=IDC_NEWUSER_KEYY,edit,1350631584
Control10=IDOK,button,1342242817
Control11=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_FINDSCORE]
Type=1
Class=CFindScore
ControlCount=1
Control1=IDC_LIST_SCORE,SysListView32,1350631425

[DLG:IDD_DIALOG_CHANGEKEY]
Type=1
Class=CChangeKey
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_KEYNEW,edit,1350631584
Control4=IDC_EDIT_KEYOK,edit,1350631584
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_DELUSER]
Type=1
Class=CDeleteUser
ControlCount=6
Control1=ID_USER_DEL,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_USER,SysListView32,1350631425
Control4=IDC_LIST_SCORE,SysListView32,1350631425
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CCreateNewUser]
Type=0
HeaderFile=CreateNewUser.h
ImplementationFile=CreateNewUser.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCreateNewUser

[CLS:CDeleteUser]
Type=0
HeaderFile=DeleteUser.h
ImplementationFile=DeleteUser.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDeleteUser

[CLS:CFindScore]
Type=0
HeaderFile=FindScore.h
ImplementationFile=FindScore.cpp
BaseClass=CDialog
Filter=D
LastObject=CFindScore
VirtualFilter=dWC

[CLS:CChangeKey]
Type=0
HeaderFile=ChangeKey.h
ImplementationFile=ChangeKey.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

