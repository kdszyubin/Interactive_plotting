
// Interactive_plottingView.h : CInteractive_plottingView ��Ľӿ�
//

#pragma once

#include "Graph.h"
class CInteractive_plottingView : public CView, public CGraph
{
protected: // �������л�����
	CInteractive_plottingView();
	DECLARE_DYNCREATE(CInteractive_plottingView)

// ����
public:
	CInteractive_plottingDoc* GetDocument() const;
	int m_iW, m_iH;
	// ���������������
	

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CInteractive_plottingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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
	void StatusOnMouseMove(CPoint point);	//����ƶ�������״̬���ĸ��£���������CGraph::OnMouseMove����CGraph�е�m_p0��m_pm
	void UpdateGraphStyle(const int &GraphStyleChose);
};

#ifndef _DEBUG  // Interactive_plottingView.cpp �еĵ��԰汾
inline CInteractive_plottingDoc* CInteractive_plottingView::GetDocument() const
   { return reinterpret_cast<CInteractive_plottingDoc*>(m_pDocument); }
#endif

