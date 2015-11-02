
// Interactive_plottingView.cpp : CInteractive_plottingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Interactive_plotting.h"
#endif

#include "Graph.h"
#include "MainFrm.h"
#include "Interactive_plottingDoc.h"
#include "Interactive_plottingView.h"

#include <cstdlib>
#include <ctime>
#include "DrawSettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CInteractive_plottingView

IMPLEMENT_DYNCREATE(CInteractive_plottingView, CView)

BEGIN_MESSAGE_MAP(CInteractive_plottingView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DRAW_SETTING, &CInteractive_plottingView::OnDrawSetting)
	ON_COMMAND(ID_GRAPH_LINE, &CInteractive_plottingView::OnGraphLine)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_LINE, &CInteractive_plottingView::OnUpdateGraphLine)
	ON_COMMAND(ID_GRAPH_RECTANGLE, &CInteractive_plottingView::OnGraphRectangle)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_RECTANGLE, &CInteractive_plottingView::OnUpdateGraphRectangle)
	ON_COMMAND(ID_GRAPH_ROUNDRECT, &CInteractive_plottingView::OnGraphRoundrect)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_ROUNDRECT, &CInteractive_plottingView::OnUpdateGraphRoundrect)
	ON_COMMAND(ID_GRAPH_CIRCLE, &CInteractive_plottingView::OnGraphCircle)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_CIRCLE, &CInteractive_plottingView::OnUpdateGraphCircle)
	ON_COMMAND(ID_GRAPH_ELLIPSE, &CInteractive_plottingView::OnGraphEllipse)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_ELLIPSE, &CInteractive_plottingView::OnUpdateGraphEllipse)
	ON_COMMAND(ID_GRAPH_POLYLINE, &CInteractive_plottingView::OnGraphPolyline)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_POLYLINE, &CInteractive_plottingView::OnUpdateGraphPolyline)
	ON_COMMAND(ID_GRAPH_POLYGON, &CInteractive_plottingView::OnGraphPolygon)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_POLYGON, &CInteractive_plottingView::OnUpdateGraphPolygon)
	ON_COMMAND(ID_GRAPH_TEXT, &CInteractive_plottingView::OnGraphText)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_TEXT, &CInteractive_plottingView::OnUpdateGraphText)
END_MESSAGE_MAP()

// CInteractive_plottingView 构造/析构

CInteractive_plottingView::CInteractive_plottingView()
{
	// TODO: 在此处添加构造代码	
}

CInteractive_plottingView::~CInteractive_plottingView()
{
}

BOOL CInteractive_plottingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CInteractive_plottingView 绘制

void CInteractive_plottingView::OnDraw(CDC* /*pDC*/)
{
	CInteractive_plottingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CDC* pDC = GetDC();												// 获取DC
	srand((unsigned int)time(0));			
	CPen pen(PS_SOLID, 10, RGB(rand() % 256, rand() % 256, rand() % 256)), *pOldPen;// 创建实心，10单位宽的笔，颜色随机
	CBrush brush(RGB(rand() % 256, rand() % 256, rand() % 256));	// 创建随机颜色刷子
	pOldPen = pDC->SelectObject(&pen);								// 设备上下文选择新笔，旧笔保存在pOldPen中
	pDC->SelectObject(&brush);										// 设备上下文选择新刷
	pDC->Ellipse(0, 0, m_iW, m_iH);									// 设置参数、绘制图形	
	pDC->SelectObject(pOldPen);										// 选择旧笔
	pen.DeleteObject();												// 删除新笔
	ReleaseDC(pDC);													// 释放DC
}


// CInteractive_plottingView 打印

BOOL CInteractive_plottingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CInteractive_plottingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CInteractive_plottingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CInteractive_plottingView 诊断

#ifdef _DEBUG
void CInteractive_plottingView::AssertValid() const
{
	CView::AssertValid();
}

void CInteractive_plottingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CInteractive_plottingDoc* CInteractive_plottingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CInteractive_plottingDoc)));
	return (CInteractive_plottingDoc*)m_pDocument;
}
#endif //_DEBUG


// CInteractive_plottingView 消息处理程序


void CInteractive_plottingView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_iW = cx;									//保存客户区大小
	m_iH = cy;
}


void CInteractive_plottingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CGraph::OnLButtonDown(this, nFlags, point);
	CView::OnLButtonDown(nFlags, point);
}


void CInteractive_plottingView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CGraph::OnMouseMove(this, nFlags, point);					// 将鼠标移动信息传给几何图形绘制的类
	StatusOnMouseMove(point);									// 更新状态栏信息
																// 状态栏中的相对位置信息来自CGraph，需先执行上面的函数
	CView::OnMouseMove(nFlags, point);
}


void CInteractive_plottingView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CGraph::OnLButtonUp(this, nFlags, point);					// 将鼠标移动信息传给几何图形绘制的类
	CView::OnLButtonUp(nFlags, point);
}


void CInteractive_plottingView::OnDrawSetting()
{
	// TODO: 在此添加命令处理程序代码
	CDrawSettingDlg drawSettingDlg;
	//m_sBrushPicPath = L"C:\\Users\\Public\\Pictures\\Sample Pictures\\菊花.jpg";
	drawSettingDlg.m_crPenCol = m_crPenCol;
	drawSettingDlg.m_crBrushCol = m_crBrushCol;
	drawSettingDlg.m_sBrushPicPath = m_sBrushPicPath;
	drawSettingDlg.m_iBrushPicWidth = m_iBrushPicWidth;
	drawSettingDlg.m_iBrushPicHeight = m_iBrushPicHeight;
	drawSettingDlg.m_iPenWidth = m_iPenWidth;
	drawSettingDlg.m_iPenStyle = m_iPenStyle;
	drawSettingDlg.m_iGraphStyle = m_iGraphStyle;
	drawSettingDlg.m_bGraphFill = m_bGraphFill;
	drawSettingDlg.m_iBrushStyle = m_iBrushStyle;
	drawSettingDlg.m_iBrushStripeStyle = m_iBrushStripeStyle;
	assert(0 <= m_iBrushStripeStyle && m_iBrushStripeStyle <= 5);
	if (drawSettingDlg.DoModal() == IDOK)
	{
		m_crPenCol = drawSettingDlg.m_crPenCol;//更新父类CGraph中的变量
		m_crBrushCol = drawSettingDlg.m_crBrushCol;
		m_sBrushPicPath = drawSettingDlg.m_sBrushPicPath;
		m_iBrushPicWidth = drawSettingDlg.m_iBrushPicWidth;
		m_iBrushPicHeight = drawSettingDlg.m_iBrushPicHeight;
		m_iPenWidth = drawSettingDlg.m_iPenWidth;
		m_iPenStyle = drawSettingDlg.m_iPenStyle;
		m_iGraphStyle = drawSettingDlg.m_iGraphStyle;
		m_bGraphFill = drawSettingDlg.m_bGraphFill;
		m_iBrushStyle = drawSettingDlg.m_iBrushStyle;
		m_iBrushStripeStyle = drawSettingDlg.m_iBrushStripeStyle;
		Refresh();							// 根据父类CGraph中的变量刷新父类CGraph中笔和刷子的类型
		assert(-1 <= m_iGraphStyle && m_iGraphStyle <= 7);//什么都不选为-1
		assert(0 <= m_iPenStyle && m_iPenStyle <= 6);
		assert(0 <= m_iBrushStyle && m_iBrushStyle <= 3);
		assert(0 <= m_iBrushStripeStyle && m_iBrushStripeStyle <= 5);
	}
}

void CInteractive_plottingView::StatusOnMouseMove(CPoint point) //鼠标移动过程中状态栏的更新，必须先用CGraph::OnMouseMove更新CGraph中的m_p0和m_pm
{
	wchar_t buf[20];
	int dx, dy;
	CMainFrame *pFrmWnd = (CMainFrame*)GetTopLevelFrame();
	_itow_s(point.x, buf, 20, 10);
	pFrmWnd->m_wndStatusBar.SetPaneText(pFrmWnd->xVal, buf);
	_itow_s(point.y, buf, 20, 10);
	pFrmWnd->m_wndStatusBar.SetPaneText(pFrmWnd->yVal, buf);
	CGraph::GetDxDy(dx, dy);
	_itow_s(dx, buf, 20, 10);
	pFrmWnd->m_wndStatusBar.SetPaneText(pFrmWnd->dxVal, buf);
	_itow_s(dy, buf, 20, 10);
	pFrmWnd->m_wndStatusBar.SetPaneText(pFrmWnd->dyVal, buf);
}

void CInteractive_plottingView::UpdateGraphStyle(const int & GraphStyleChose) // 根据工具栏中对图形的修改更新图形风格
{
	if (m_iGraphStyle == GraphStyleChose)
	{
		if (m_iGraphStyle == GS_POLYGON)
		{
			CDC* pDC = this->GetDC();				// 获取设备上下文
			RevokeDraw(pDC);
			this->ReleaseDC(pDC);					// 释放设备上下文
		}
		m_iGraphStyle = -1;
	}
	else
	{
		m_iGraphStyle = GraphStyleChose;
		GraphStyleRefresh();
	}
}

void CInteractive_plottingView::OnGraphLine()
{
	UpdateGraphStyle(GS_LINE);
}

void CInteractive_plottingView::OnUpdateGraphLine(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_iGraphStyle == GS_LINE);
}

void CInteractive_plottingView::OnGraphRectangle()
{
	UpdateGraphStyle(GS_RECTANGLE);
}

void CInteractive_plottingView::OnUpdateGraphRectangle(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_iGraphStyle == GS_RECTANGLE);
}

void CInteractive_plottingView::OnGraphRoundrect()
{
	UpdateGraphStyle(GS_ROUNDRECT);
}

void CInteractive_plottingView::OnUpdateGraphRoundrect(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_iGraphStyle == GS_ROUNDRECT);
}

void CInteractive_plottingView::OnGraphCircle()
{
	UpdateGraphStyle(GS_CIRCLE);
}

void CInteractive_plottingView::OnUpdateGraphCircle(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_iGraphStyle == GS_CIRCLE);
}

void CInteractive_plottingView::OnGraphEllipse()
{
	UpdateGraphStyle(GS_ELLIPSE);
}

void CInteractive_plottingView::OnUpdateGraphEllipse(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_iGraphStyle == GS_ELLIPSE);
}

void CInteractive_plottingView::OnGraphPolyline()
{
	UpdateGraphStyle(GS_POLYLINE);
}

void CInteractive_plottingView::OnUpdateGraphPolyline(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_iGraphStyle == GS_POLYLINE);
}

void CInteractive_plottingView::OnGraphPolygon()
{
	UpdateGraphStyle(GS_POLYGON);
}

void CInteractive_plottingView::OnUpdateGraphPolygon(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_iGraphStyle == GS_POLYGON);
}

void CInteractive_plottingView::OnGraphText()
{
	UpdateGraphStyle(GS_TEXT);
}

void CInteractive_plottingView::OnUpdateGraphText(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_iGraphStyle == GS_TEXT);
}
