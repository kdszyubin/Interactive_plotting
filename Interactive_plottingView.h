
// Interactive_plottingView.h : CInteractive_plottingView ��Ľӿ�
//

#pragma once


class CInteractive_plottingView : public CView
{
protected: // �������л�����
	CInteractive_plottingView();
	DECLARE_DYNCREATE(CInteractive_plottingView)

// ����
public:
	CInteractive_plottingDoc* GetDocument() const;
	int m_iW, m_iH;
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
};

#ifndef _DEBUG  // Interactive_plottingView.cpp �еĵ��԰汾
inline CInteractive_plottingDoc* CInteractive_plottingView::GetDocument() const
   { return reinterpret_cast<CInteractive_plottingDoc*>(m_pDocument); }
#endif

