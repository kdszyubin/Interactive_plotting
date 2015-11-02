
// Interactive_plottingView.h : CInteractive_plottingView 类的接口
//

#pragma once

#include "Graph.h"
class CInteractive_plottingView : public CView, public CGraph
{
protected: // 仅从序列化创建
	CInteractive_plottingView();
	DECLARE_DYNCREATE(CInteractive_plottingView)

// 特性
public:
	CInteractive_plottingDoc* GetDocument() const;
	int m_iW, m_iH;
	// 定义若干类变量：
	

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
	afx_msg void OnDrawSetting();
	afx_msg void OnGraphLine();
	afx_msg void OnUpdateGraphLine(CCmdUI *pCmdUI);
	afx_msg void OnGraphRectangle();
	afx_msg void OnUpdateGraphRectangle(CCmdUI *pCmdUI);
	afx_msg void OnGraphRoundrect();
	afx_msg void OnUpdateGraphRoundrect(CCmdUI *pCmdUI);
	afx_msg void OnGraphCircle();
	afx_msg void OnUpdateGraphCircle(CCmdUI *pCmdUI);
	afx_msg void OnGraphEllipse();
	afx_msg void OnUpdateGraphEllipse(CCmdUI *pCmdUI);
	afx_msg void OnGraphPolyline();
	afx_msg void OnUpdateGraphPolyline(CCmdUI *pCmdUI);
	afx_msg void OnGraphPolygon();
	afx_msg void OnUpdateGraphPolygon(CCmdUI *pCmdUI);
	afx_msg void OnGraphText();
	afx_msg void OnUpdateGraphText(CCmdUI *pCmdUI);
private:
	void StatusOnMouseMove(CPoint point);	//鼠标移动过程中状态栏的更新，必须先用CGraph::OnMouseMove更新CGraph中的m_p0和m_pm
	void UpdateGraphStyle(const int &GraphStyleChose);
};

#ifndef _DEBUG  // Interactive_plottingView.cpp 中的调试版本
inline CInteractive_plottingDoc* CInteractive_plottingView::GetDocument() const
   { return reinterpret_cast<CInteractive_plottingDoc*>(m_pDocument); }
#endif

