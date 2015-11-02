
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "Interactive_plotting.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

/*
static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};
*/

static UINT indicators[] =
{
	ID_SEPARATOR, //提示 nIndex = 0
	//ID_SEPARATOR, //进度条 nIndex = 1
	ID_SEPARATOR, //“x:” nIndex = 1
	ID_SEPARATOR, //x值 nIndex = 2
	ID_SEPARATOR, //“y:” nIndex = 3
	ID_SEPARATOR, //y值 nIndex = 4
	ID_SEPARATOR, //“dx:” nIndex =5
	ID_SEPARATOR, //dx值 nIndex = 6
	ID_SEPARATOR, //“dy:” nIndex = 7
	ID_SEPARATOR,//dy值 nIndex = 8
};
// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneInfo(0, prompt, SBPS_STRETCH, 0); //提示
	m_wndStatusBar.SetPaneInfo(1, xName, SBPS_NOBORDERS, 8); //"x:"
	m_wndStatusBar.SetPaneText(xName, L"x:");
	m_wndStatusBar.SetPaneInfo(2, xVal, SBPS_NORMAL, 36); //x值
	m_wndStatusBar.SetPaneInfo(3, yName, SBPS_NOBORDERS, 8);//"y:"
	m_wndStatusBar.SetPaneText(yName, L"y:");
	m_wndStatusBar.SetPaneInfo(4, yVal, SBPS_NORMAL, 36); //y值
	m_wndStatusBar.SetPaneInfo(5, dxName, SBPS_NOBORDERS, 16); //"x:"
	m_wndStatusBar.SetPaneText(dxName, L"dx:");
	m_wndStatusBar.SetPaneInfo(6, dxVal, SBPS_NORMAL, 36); //x值
	m_wndStatusBar.SetPaneInfo(7, dyName, SBPS_NOBORDERS, 16);//"y:"
	m_wndStatusBar.SetPaneText(dyName, L"dy:");
	m_wndStatusBar.SetPaneInfo(8, dyVal, SBPS_NORMAL, 36); //y值

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

