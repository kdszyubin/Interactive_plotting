
// Interactive_plottingView.h : CInteractive_plottingView 类的接口
//

#pragma once


class CInteractive_plottingView : public CView
{
protected: // 仅从序列化创建
	CInteractive_plottingView();
	DECLARE_DYNCREATE(CInteractive_plottingView)

// 特性
public:
	CInteractive_plottingDoc* GetDocument() const;
	int m_iW, m_iH;
	// 定义若干类变量：
	BOOL m_bLButtonDown, // 判断是否按下左鼠标键
		m_bErase; // 是否需要擦除图形
	CPoint p0, pm; // 记录直线起点和动态终点
	CPen *pGrayPen, *pLinePen; // 定义灰色和直线笔的对象指针
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CInteractive_plottingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Interactive_plottingView.cpp 中的调试版本
inline CInteractive_plottingDoc* CInteractive_plottingView::GetDocument() const
   { return reinterpret_cast<CInteractive_plottingDoc*>(m_pDocument); }
#endif

