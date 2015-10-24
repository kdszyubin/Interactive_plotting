
// Interactive_plottingView.cpp : CInteractive_plottingView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CInteractive_plottingView ����/����

CInteractive_plottingView::CInteractive_plottingView()
{
	// TODO: �ڴ˴���ӹ������

}

CInteractive_plottingView::~CInteractive_plottingView()
{
}

BOOL CInteractive_plottingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CInteractive_plottingView ����

void CInteractive_plottingView::OnDraw(CDC* /*pDC*/)
{
	CInteractive_plottingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CDC* pDC = GetDC(); // ��ȡDC
	srand(time(0));			
	CPen pen(PS_SOLID, 10, RGB(rand() % 256, rand() % 256, rand() % 256)), *pOldPen;//����ʵ�ģ�10��λ��ıʣ���ɫ���
	CBrush brush(RGB(rand() % 256, rand() % 256, rand() % 256));		//���������ɫˢ��
	pOldPen = pDC->SelectObject(&pen);								//�豸������ѡ���±ʣ��ɱʱ�����pOldPen��
	pDC->SelectObject(&brush);										//�豸������ѡ����ˢ
	pDC->Ellipse(0, 0, m_iW, m_iH);//���ò���������ͼ��	
	pDC->SelectObject(pOldPen);										//ѡ��ɱ�
	pen.DeleteObject();												//ɾ���±�
	ReleaseDC(pDC); // �ͷ�DC
}


// CInteractive_plottingView ��ӡ

BOOL CInteractive_plottingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CInteractive_plottingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CInteractive_plottingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CInteractive_plottingView ���

#ifdef _DEBUG
void CInteractive_plottingView::AssertValid() const
{
	CView::AssertValid();
}

void CInteractive_plottingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CInteractive_plottingDoc* CInteractive_plottingView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CInteractive_plottingDoc)));
	return (CInteractive_plottingDoc*)m_pDocument;
}
#endif //_DEBUG


// CInteractive_plottingView ��Ϣ�������


void CInteractive_plottingView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	m_iW = cx;//����ͻ�����С
	m_iH = cy;
}
