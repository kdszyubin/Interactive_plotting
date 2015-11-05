#include "stdafx.h"
#include "Graph.h"
#include "GraphStyleEdit.h"

#define BS_HOLLOW 0
#define BS_SOLID 1
#define BS_STRIPE 2
#define BS_PICTURE 3
#define IDC_EDITX 9090

CGraph::CGraph()					// 初始化公共变量，并通过公共变量初始化笔和刷子类型
{
	m_bLButtonDown = FALSE;			// 设左鼠标键按下为假
	m_bErase = FALSE;				// 设需要擦除为假
	m_crPenCol = RGB(255, 0, 0);	// 初始化笔为红色
	m_crBrushCol = RGB(0, 255, 0);	// 初始化刷为绿色
	m_sBrushPicPath = L"";			// 初始化图片地址为空
	m_iBrushPicWidth = 0;
	m_iBrushPicHeight = 0;
	m_iPenWidth = 5;				// 初始化笔宽为5
	m_iPenStyle = PS_SOLID;			// 始化笔为实心
	m_iGraphStyle = GS_ELLIPSE;		// 初始化图形为椭圆
	m_bGraphFill = FALSE;			// 初始化填充为假
	m_iBrushStyle = BS_SOLID;		//不知道宏，刷为实心
	m_iBrushStripeStyle = HS_HORIZONTAL; //初始化刷条纹风格
	
	m_MovingPen.CreatePen(PS_DOT, 0, RGB(128, 128, 128));	// 默认移动中的笔为灰色点笔
	m_MovingBrush.CreateStockObject(NULL_BRUSH);			// 默认移动中刷子为空刷
	m_TargetPen.CreatePen(m_iPenStyle, m_iPenWidth, m_crPenCol); 
	m_TargetBrush.CreateSolidBrush(m_crBrushCol);
	nCount = 0;
	m_pEdit = NULL;
}


CGraph::~CGraph()
{
}

void CGraph::OnLButtonDown(CWnd* pWnd, UINT nFlags, CPoint point)
{
	pWnd->SetCapture();							// 设置鼠标捕获
	m_bLButtonDown = TRUE;						// 设左鼠标键按下为真
	m_p0 = point;								// 保存起点
	m_pm = point;								// 初始是终点等于起点
	if (nCount == 0)							// 对于折线和多边形，
		m_aPoints[nCount++] = point;			//nCount==0则表示刚开始绘图，需保存初始点
	else
		m_p0 = m_aPoints[nCount - 1];			//非刚开始绘图，则初始点为上一个点
	SetCursor(LoadCursor(NULL, IDC_CROSS)); // 设置鼠标为十字
}

void CGraph::OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point)
{
	if (m_bLButtonDown) {						// 左鼠标键按下为真（拖动画图）
		CDC* pDC = pWnd->GetDC();				// 获取设备上下文
		pDC->SelectObject(&m_MovingPen);		// 选取移动时的笔
		pDC->SetROP2(R2_XORPEN);				// 设置为异或绘图方式
		pDC->SetBkMode(TRANSPARENT);			// 设置透明背景模式
		pDC->SelectObject(&m_MovingBrush);		// 选入移动刷，
												// 移动时默认空刷，用于动态画封闭图形（如矩形、椭圆等）
		if (m_bErase)							// 需要擦除为真
			MovingDraw(pDC);
		else									// 需要擦除为假
			m_bErase = TRUE;					// 设需要擦除为真
		m_pm = point;							// 更新终点
		MovingDraw(pDC);						// 绘制图形
		pWnd->ReleaseDC(pDC);					// 释放设备上下文
	}
}

void CGraph::OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	ReleaseCapture();							// 释放鼠标捕获
	SetCursor(LoadCursor(NULL, IDC_ARROW));		// 设置鼠标为指针
	if (m_bLButtonDown) {						// 左鼠标键按下为真
		CDC* pDC = pWnd->GetDC();				// 获取设备上下文
		pDC->SelectObject(&m_MovingPen);		// 选入移动时的笔
		pDC->SetROP2(R2_XORPEN);				// 设置为异或绘图方式
		pDC->SetBkMode(TRANSPARENT);			// 设置透明背景模式
		pDC->SelectObject(&m_MovingBrush);		// 选入移动刷，
												// 移动时默认空刷，用于动态画封闭图形（如矩形、椭圆等）
		if (m_bErase) 							// 需要擦除为真
			MovingDraw(pDC);

		pDC->SelectObject(&m_TargetPen);		// 选择目标状态的笔
		pDC->SelectObject(&m_TargetBrush);		// 选择目标状态的刷子
		pDC->SetROP2(R2_COPYPEN);				// 设置为覆盖绘图方式
		m_pm = point;							// 更新终点
		m_aPoints[nCount++] = point;			// 记录点
		TargetDraw(pDC);						// 绘制最终的图形
		m_bLButtonDown = FALSE;					// 重设左鼠标键按下为假
		m_bErase = FALSE;						// 重需要擦除为假
		pWnd->ReleaseDC(pDC);					// 释放设备上下文
	}
}

void CGraph::TargetDraw(CDC * pDC)
{
	
	CRect rect(m_p0, m_pm);
	int d;
	switch (m_iGraphStyle)
	{
	case GS_LINE:
	case GS_RECTANGLE:
	case GS_ROUNDRECT:
	case GS_CIRCLE:
	case GS_ELLIPSE:
		MovingDraw(pDC);
		assert(nCount == 2);//对于以上图形，绘图所用的点必然为2
		nCount = 0;
		break;
	case GS_POLYLINE:
		MovingDraw(pDC);
		break;
	case GS_POLYGON:
		pDC->SetROP2(R2_XORPEN);					// 设置为异或绘图方式
		rect.SetRect(m_aPoints[0], m_aPoints[nCount - 1]);
		d = max(abs(rect.Width()), abs(rect.Height()));
		if (d <= (m_iPenWidth + 1) * 2 && nCount - 1 >= 3)	// 多边形点数至少为三，
															// 最后一个点与初始点以一定范围误差内表示同一个点
															// 总点数为nCount - 1
		{
			pDC->Polyline(m_aPoints, nCount - 1);		// 擦除绘制过程中的折线
			pDC->SetROP2(R2_COPYPEN);					// 设置为覆盖绘图方式
			pDC->Polygon(m_aPoints, nCount - 1);		// 绘制最终的多边形
			nCount = 0;									
		}
		else
		{
			pDC->Polyline(m_aPoints, nCount - 1);
			pDC->Polyline(m_aPoints, nCount);
		}
		break;
	case GS_TEXT:
		RemoveEdit(pDC);
		if (nCount == 2 && m_p0 != m_pm)
		{
			m_pEdit = new CGraphStyleEdit();
			m_pEdit->Create(WS_VISIBLE | ES_LEFT, rect, pDC->GetWindow(), IDC_EDITX);
			m_pEdit->SetFocus();
		}
		nCount = 0;
		break;
	default:											// 撤销没有选择图形时的点的记录
		nCount = 0;
	}
}

void CGraph::MovingDraw(CDC* pDC)
{
	CRect rect(m_p0, m_pm);
	int d = 0;
	CPoint ptemp;
	switch (m_iGraphStyle)
	{
	case GS_LINE:
		pDC->MoveTo(m_p0); pDC->LineTo(m_pm);
		break;
	case GS_RECTANGLE:
		pDC->Rectangle(&rect);
		break;
	case GS_ROUNDRECT:
		d = min(rect.Width(), rect.Height()) / 4;
		pDC->RoundRect(&rect, CPoint(d, d));
		break;
	case GS_CIRCLE:
		d = min(abs(rect.Width()), abs(rect.Height()));
		if (rect.Width() < 0)
			ptemp.x = m_p0.x - d;
		else
			ptemp.x = m_p0.x + d;
		if (rect.Height() < 0)
			ptemp.y = m_p0.y - d;
		else
			ptemp.y = m_p0.y + d;
		rect.SetRect(m_p0, ptemp);
		pDC->Ellipse(&rect);
		break;
	case GS_ELLIPSE:
		pDC->Ellipse(&rect);
		break;
	case GS_POLYLINE:
	case GS_POLYGON:
		pDC->MoveTo(m_p0); pDC->LineTo(m_pm);
		break;
	case GS_TEXT:
		pDC->Rectangle(&rect);
		break;
	}
}

void CGraph::PenStyleRefresh()
{
	m_TargetPen.DeleteObject();
	m_TargetPen.CreatePen(m_iPenStyle, m_iPenWidth, m_crPenCol);
}

void CGraph::GraphStyleRefresh(CDC *pDC, const int & GraphStyleChose)
{
	if (GraphStyleChose != -1)
	{
		if (m_iGraphStyle == GraphStyleChose)
			m_iGraphStyle = -1;
		else
			m_iGraphStyle = GraphStyleChose;
	}
	if (m_iOldGraphStyle != m_iGraphStyle)
	{
		switch (m_iOldGraphStyle)
		{
		case GS_POLYGON:
			RevokeDraw(pDC);
			break;
		case GS_TEXT:
			RemoveEdit(pDC);
			break;
		}
		m_iOldGraphStyle = m_iGraphStyle;
		nCount = 0;
	}
}

void CGraph::BrushStyleRefresh()
{
	CImage img;
	CBitmap bitmap;
	HBITMAP   hBitmap;
	if (!img.Load(m_sBrushPicPath))
	{
		hBitmap = (HBITMAP)img.operator HBITMAP();
		bitmap.DeleteObject();
		BOOL temp = bitmap.Attach(hBitmap);
		assert(temp);
	}
	m_TargetBrush.DeleteObject();
	switch (m_iBrushStyle)
	{
	case BS_HOLLOW:
		m_TargetBrush.CreateStockObject(NULL_BRUSH);
		break;
	case BS_SOLID:
		m_TargetBrush.CreateSolidBrush(m_crBrushCol);
		break;
	case BS_STRIPE:
		m_TargetBrush.CreateHatchBrush(m_iBrushStripeStyle, m_crBrushCol);
		break;
	case BS_PICTURE:
		m_TargetBrush.CreatePatternBrush(&bitmap);
		break;
	}
}

void CGraph::Refresh(CDC *pDC)
{
	PenStyleRefresh();
	GraphStyleRefresh(pDC);
	BrushStyleRefresh();
}

void CGraph::GetDxDy(int & dx, int & dy)
{
	CRect rect(m_p0, m_pm);
	dx = rect.Width();
	dy = rect.Height();
}

void CGraph::RevokeDraw(CDC *pDC)
{
	pDC->SetBkMode(TRANSPARENT);			// 设置透明背景模式
	pDC->SelectObject(&m_TargetPen);		// 选择目标状态的笔
	pDC->SelectObject(&m_TargetBrush);		// 选择目标状态的刷子
	pDC->SetROP2(R2_XORPEN);					// 设置为异或绘图方式
	pDC->Polyline(m_aPoints, nCount);			// 擦除绘制过程中的折线
	nCount = 0;
}

void CGraph::RemoveEdit(CDC *pDC)
{
	RECT rectofEdit;
	CString textofEdit;
	if (m_pEdit != NULL)
	{
		m_pEdit->GetWindowRect(&rectofEdit);
		pDC->GetWindow()->ScreenToClient(&rectofEdit);
		m_pEdit->GetWindowText(textofEdit);
		delete m_pEdit;
		m_pEdit = NULL;
		pDC->TextOut(rectofEdit.left, rectofEdit.top, textofEdit);
	}
};
