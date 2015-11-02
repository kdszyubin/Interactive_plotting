
// Interactive_plottingView.cpp : CInteractive_plottingView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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
	CDC* pDC = GetDC();												// ��ȡDC
	srand((unsigned int)time(0));			
	CPen pen(PS_SOLID, 10, RGB(rand() % 256, rand() % 256, rand() % 256)), *pOldPen;// ����ʵ�ģ�10��λ��ıʣ���ɫ���
	CBrush brush(RGB(rand() % 256, rand() % 256, rand() % 256));	// ���������ɫˢ��
	pOldPen = pDC->SelectObject(&pen);								// �豸������ѡ���±ʣ��ɱʱ�����pOldPen��
	pDC->SelectObject(&brush);										// �豸������ѡ����ˢ
	pDC->Ellipse(0, 0, m_iW, m_iH);									// ���ò���������ͼ��	
	pDC->SelectObject(pOldPen);										// ѡ��ɱ�
	pen.DeleteObject();												// ɾ���±�
	ReleaseDC(pDC);													// �ͷ�DC
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
	m_iW = cx;									//����ͻ�����С
	m_iH = cy;
}


void CInteractive_plottingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CGraph::OnLButtonDown(this, nFlags, point);
	CView::OnLButtonDown(nFlags, point);
}


void CInteractive_plottingView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CGraph::OnMouseMove(this, nFlags, point);					// ������ƶ���Ϣ��������ͼ�λ��Ƶ���
	StatusOnMouseMove(point);									// ����״̬����Ϣ
																// ״̬���е����λ����Ϣ����CGraph������ִ������ĺ���
	CView::OnMouseMove(nFlags, point);
}


void CInteractive_plottingView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CGraph::OnLButtonUp(this, nFlags, point);					// ������ƶ���Ϣ��������ͼ�λ��Ƶ���
	CView::OnLButtonUp(nFlags, point);
}


void CInteractive_plottingView::OnDrawSetting()
{
	// TODO: �ڴ���������������
	CDrawSettingDlg drawSettingDlg;
	//m_sBrushPicPath = L"C:\\Users\\Public\\Pictures\\Sample Pictures\\�ջ�.jpg";
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
		m_crPenCol = drawSettingDlg.m_crPenCol;//���¸���CGraph�еı���
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
		Refresh();							// ���ݸ���CGraph�еı���ˢ�¸���CGraph�бʺ�ˢ�ӵ�����
		assert(-1 <= m_iGraphStyle && m_iGraphStyle <= 7);//ʲô����ѡΪ-1
		assert(0 <= m_iPenStyle && m_iPenStyle <= 6);
		assert(0 <= m_iBrushStyle && m_iBrushStyle <= 3);
		assert(0 <= m_iBrushStripeStyle && m_iBrushStripeStyle <= 5);
	}
}

void CInteractive_plottingView::StatusOnMouseMove(CPoint point) //����ƶ�������״̬���ĸ��£���������CGraph::OnMouseMove����CGraph�е�m_p0��m_pm
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

void CInteractive_plottingView::UpdateGraphStyle(const int & GraphStyleChose) // ���ݹ������ж�ͼ�ε��޸ĸ���ͼ�η��
{
	if (m_iGraphStyle == GraphStyleChose)
	{
		if (m_iGraphStyle == GS_POLYGON)
		{
			CDC* pDC = this->GetDC();				// ��ȡ�豸������
			RevokeDraw(pDC);
			this->ReleaseDC(pDC);					// �ͷ��豸������
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
