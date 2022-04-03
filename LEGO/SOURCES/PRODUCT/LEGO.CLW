; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRVWeightsDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "lego.h"
LastPage=0

ClassCount=10
Class1=CLegoApp
Class2=CAboutDlg
Class3=CLegoDoc
Class4=CLegoView
Class5=CMainFrame
Class6=MxLegoCitizenView
Class7=MxLegoEditorView
Class8=MxLegoView
Class9=CRealismDlg
Class10=CRVWeightsDlg

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_REALISM
Resource4=IDD_REALTIMEVIEW_WEIGHTS

[CLS:CLegoApp]
Type=0
BaseClass=CWinApp
HeaderFile=Lego.h
ImplementationFile=Lego.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Lego.cpp
ImplementationFile=Lego.cpp
Filter=D
LastObject=CAboutDlg

[CLS:CLegoDoc]
Type=0
BaseClass=CDocument
HeaderFile=Legodoc.h
ImplementationFile=Legodoc.cpp

[CLS:CLegoView]
Type=0
BaseClass=CView
HeaderFile=LegoView.h
ImplementationFile=LegoView.cpp
Filter=C
LastObject=CLegoView

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=Mainfrm.h
ImplementationFile=Mainfrm.cpp

[CLS:MxLegoCitizenView]
Type=0
BaseClass=MxLegoView
HeaderFile=MxLegoCitizenView.h
ImplementationFile=MxLegoCitizenView.cpp

[CLS:MxLegoEditorView]
Type=0
BaseClass=MxLegoView
HeaderFile=MxLegoEditorView.h
ImplementationFile=MxLegoEditorView.cpp

[CLS:MxLegoView]
Type=0
BaseClass=TglWnd
HeaderFile=MxLegoView.h
ImplementationFile=MxLegoView.cpp

[CLS:CRealismDlg]
Type=0
BaseClass=CDialog
HeaderFile=RealismDlg.h
ImplementationFile=RealismDlg.cpp

[CLS:CRVWeightsDlg]
Type=0
BaseClass=CDialog
HeaderFile=RVWeightsDlg.h
ImplementationFile=RVWeightsDlg.cpp
Filter=D
LastObject=CRVWeightsDlg
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_REALISM]
Type=1
Class=CRealismDlg
ControlCount=15
Control1=IDC_REALISM,msctls_trackbar32,1342242825
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC_RENDERTIME,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC_RENDERRATE,static,1342308352
Control12=IDC_STATIC_RENDERRATE_CURRENT,static,1342308352
Control13=IDC_STATIC_RENDERTIME_CURRENT,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352

[DLG:IDD_REALTIMEVIEW_WEIGHTS]
Type=1
Class=CRVWeightsDlg
ControlCount=25
Control1=IDC_STATIC,static,1342308353
Control2=IDC_WEIGHT_SIZE,msctls_trackbar32,1342242827
Control3=IDC_STATIC_WEIGHT_SIZE,static,1342308352
Control4=IDC_STATIC,static,1342308353
Control5=IDC_WEIGHT_ACCURACY,msctls_trackbar32,1342242827
Control6=IDC_STATIC_WEIGHT_ACCURACY,static,1342308352
Control7=IDC_STATIC,static,1342308353
Control8=IDC_WEIGHT_SEMANTIC,msctls_trackbar32,1342242827
Control9=IDC_STATIC_WEIGHT_SEMANTIC,static,1342308352
Control10=IDC_STATIC,static,1342308353
Control11=IDC_WEIGHT_FOCUS,msctls_trackbar32,1342242827
Control12=IDC_STATIC_WEIGHT_FOCUS,static,1342308352
Control13=IDC_STATIC,static,1342308353
Control14=IDC_WEIGHT_MOTION,msctls_trackbar32,1342242827
Control15=IDC_STATIC_WEIGHT_MOTION,static,1342308352
Control16=IDC_STATIC,static,1342308353
Control17=IDC_WEIGHT_HYSTERESIS,msctls_trackbar32,1342242827
Control18=IDC_STATIC_WEIGHT_HYSTERESIS,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_SENSITIVITY_TEXT,static,1342308352
Control21=IDC_SENSITIVITY,msctls_updown32,1342242852
Control22=IDC_BUTTON1,button,1342242816
Control23=IDC_SLIDER_NLISTS,msctls_trackbar32,1342242825
Control24=IDC_STATIC_WEIGHT_FOCUS2,static,1342308352
Control25=IDC_STATIC_BEST_LIST_SIZE,static,1342308352

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDITOR_LOAD
Command15=ID_EDITOR_REMOVE
Command16=ID_EDITOR_REMOVE_ALL
Command17=ID_EDITOR_SELECTPREVIOUS
Command18=ID_EDITOR_SELECTNEXT
Command19=ID_VIEW_TOOLBAR
Command20=ID_VIEW_STATUS_BAR
Command21=ID_VIEW_REALTIMEVIEW_WEIGHTS
Command22=ID_VIEW_REALISM
Command23=ID_VIEW_RENDERWHENNOTACTIVE
Command24=ID_VIEW_PLAYER
Command25=ID_VIEW_EDITOR
Command26=ID_VIEW_CITYPLANNER
Command27=ID_TOWN_LOADMODEL
Command28=ID_TOWN_LOADPILLARS
Command29=ID_TOWN_NEWGEOMETRY
Command30=ID_TOWN_DELETEGEOMETRY
Command31=ID_APP_ABOUT
CommandCount=31

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

