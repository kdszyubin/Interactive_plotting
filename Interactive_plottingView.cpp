
// Interactive_plottingView.cpp : CInteractive_plottingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Interactive_plotting.h"
#endif

#include "Interactive_plottingDoc.h"
#include "Interactive_plottingView.h"

#include <cstdlib>
#include <ctime>

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
END_MESSAGE_MAP()

// CInteractive_plottingView 构造/析构

CInteractive_plottingView::CInteractive_plottingView()
{
	// TODO: 在此处添加构造代码
	m_bLButtonDown = FALSE; // 设左鼠标键按下为假
	m_bErase = FALSE; // 设需要擦除为假
	pGrayPen = new CPen(PS_DOT, 0, RGB(128, 128, 128)); // 创建灰色点线笔
	pLinePen = new CPen(PS_SOLID, 10, RGB(255, 0, 0)); // 创建红色的直线笔

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
	CDC* pDC = GetDC(); // 获取DC
	srand(time(0));			
	CPen pen(PS_SOLID, 10, RGB(rand() % 256, rand() % 256, rand() % 256)), *pOldPen;//创建实心，10单位宽的笔，颜色随机
	CBrush brush(RGB(rand() % 256, rand() % 256, rand() % 256));		//创建随机颜色刷子
	pOldPen = pDC->SelectObject(&pen);								//设备上下文选择新笔，旧笔保存在pOldPen中
	pDC->SelectObject(&brush);										//设备上下文选择新刷
	pDC->Ellipse(0, 0, m_iW, m_iH);//设置参数、绘制图形	
	pDC->SelectObject(pOldPen);										//选择旧笔
	pen.DeleteObject();												//删除新笔
	ReleaseDC(pDC); // 释放DC
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
	m_iW = cx;//保存客户区大小
	m_iH = cy;
}


void CInteractive_plottingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCapture(); // 设置鼠标捕获
	m_bLButtonDown = TRUE; // 设左鼠标键按下为真
	p0 = point; // 保存直线的起点
	pm = p0; // 让直线的终点等于起点

	SetCursor(LoadCursor(NULL, IDC_CROSS)); // 设置鼠标为十字
	CView::OnLButtonDown(nFlags, point);
}


void CInteractive_plottingView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bLButtonDown) { // 左鼠标键按下为真（拖动画图）
		CDC* pDC = GetDC(); // 获取设备上下文
		pDC->SelectObject(pGrayPen); // 选取灰色点线笔
		pDC->SetROP2(R2_XORPEN); // 设置为异或绘图方式
		pDC->SetBkMode(TRANSPARENT); // 设置透明背景模式
									 //pDC->SelectStockObject(NULL_BRUSH); // 选入空刷
									 // 用于动态画封闭图形（如矩形、椭圆等）
		if (m_bErase) { // 需要擦除为真
			pDC->MoveTo(p0); pDC->LineTo(pm); // 擦除原直线
		}
		else // 需要擦除为假
			m_bErase = TRUE; // 设需要擦除为真
		pDC->MoveTo(p0); pDC->LineTo(point); // 绘制新直线
		pm = point; // 更新老终点
		ReleaseDC(pDC); // 释放设备上下文
	}
	CView::OnMouseMove(nFlags, point);
}


void CInteractive_plottingView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ReleaseCapture(); // 释放鼠标捕获
	SetCursor(LoadCursor(NULL, IDC_ARROW)); // 设置鼠标为十字
	if (m_bLButtonDown) { // 左鼠标键按下为真
		CDC* pDC = GetDC(); // 获取设备上下文
		pDC->SelectObject(pGrayPen); // 选入灰色点线笔
		pDC->SetROP2(R2_XORPEN); // 设置为异或绘图方式
		pDC->SetBkMode(TRANSPARENT); // 设置透明背景模式
									 // pDC->SelectStockObject(NULL_BRUSH); // 选入空刷
									 // 用于动态画封闭图形（如矩形、椭圆等）
		pDC->MoveTo(p0); pDC->LineTo(pm); // 擦除原直线
		pDC->SelectObject(pLinePen); // 选择直线笔
		pDC->SetROP2(R2_COPYPEN); // 设置为覆盖绘图方式
		pDC->MoveTo(p0); pDC->LineTo(point); // 绘制最终的直线
		m_bLButtonDown = FALSE; // 重设左鼠标键按下为假
		m_bErase = FALSE; // 重需要擦除为假
		ReleaseDC(pDC); // 释放设备上下文
	}
	CView::OnLButtonUp(nFlags, point);
}
