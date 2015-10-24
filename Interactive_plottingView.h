
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
};

#ifndef _DEBUG  // Interactive_plottingView.cpp 中的调试版本
inline CInteractive_plottingDoc* CInteractive_plottingView::GetDocument() const
   { return reinterpret_cast<CInteractive_plottingDoc*>(m_pDocument); }
#endif

