#include "stdafx.h"
#include "Graph.h"
#include "GraphStyleEdit.h"

#define BS_HOLLOW 0
#define BS_SOLID 1
#define BS_STRIPE 2
#define BS_PICTURE 3
#define IDC_EDITX 9090

CGraph::CGraph()					// ��ʼ��������������ͨ������������ʼ���ʺ�ˢ������
{
	m_bLButtonDown = FALSE;			// ������������Ϊ��
	m_bErase = FALSE;				// ����Ҫ����Ϊ��
	m_crPenCol = RGB(255, 0, 0);	// ��ʼ����Ϊ��ɫ
	m_crBrushCol = RGB(0, 255, 0);	// ��ʼ��ˢΪ��ɫ
	m_sBrushPicPath = L"";			// ��ʼ��ͼƬ��ַΪ��
	m_iBrushPicWidth = 0;
	m_iBrushPicHeight = 0;
	m_iPenWidth = 5;				// ��ʼ���ʿ�Ϊ5
	m_iPenStyle = PS_SOLID;			// ʼ����Ϊʵ��
	m_iGraphStyle = GS_ELLIPSE;		// ��ʼ��ͼ��Ϊ��Բ
	m_bGraphFill = FALSE;			// ��ʼ�����Ϊ��
	m_iBrushStyle = BS_SOLID;		//��֪���꣬ˢΪʵ��
	m_iBrushStripeStyle = HS_HORIZONTAL; //��ʼ��ˢ���Ʒ��
	
	m_MovingPen.CreatePen(PS_DOT, 0, RGB(128, 128, 128));	// Ĭ���ƶ��еı�Ϊ��ɫ���
	m_MovingBrush.CreateStockObject(NULL_BRUSH);			// Ĭ���ƶ���ˢ��Ϊ��ˢ
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
	pWnd->SetCapture();							// ������겶��
	m_bLButtonDown = TRUE;						// ������������Ϊ��
	m_p0 = point;								// �������
	m_pm = point;								// ��ʼ���յ�������
	if (nCount == 0)							// �������ߺͶ���Σ�
		m_aPoints[nCount++] = point;			//nCount==0���ʾ�տ�ʼ��ͼ���豣���ʼ��
	else
		m_p0 = m_aPoints[nCount - 1];			//�Ǹտ�ʼ��ͼ�����ʼ��Ϊ��һ����
	SetCursor(LoadCursor(NULL, IDC_CROSS)); // �������Ϊʮ��
}

void CGraph::OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point)
{
	if (m_bLButtonDown) {						// ����������Ϊ�棨�϶���ͼ��
		CDC* pDC = pWnd->GetDC();				// ��ȡ�豸������
		pDC->SelectObject(&m_MovingPen);		// ѡȡ�ƶ�ʱ�ı�
		pDC->SetROP2(R2_XORPEN);				// ����Ϊ����ͼ��ʽ
		pDC->SetBkMode(TRANSPARENT);			// ����͸������ģʽ
		pDC->SelectObject(&m_MovingBrush);		// ѡ���ƶ�ˢ��
												// �ƶ�ʱĬ�Ͽ�ˢ�����ڶ�̬�����ͼ�Σ�����Ρ���Բ�ȣ�
		if (m_bErase)							// ��Ҫ����Ϊ��
			MovingDraw(pDC);
		else									// ��Ҫ����Ϊ��
			m_bErase = TRUE;					// ����Ҫ����Ϊ��
		m_pm = point;							// �����յ�
		MovingDraw(pDC);						// ����ͼ��
		pWnd->ReleaseDC(pDC);					// �ͷ��豸������
	}
}

void CGraph::OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	ReleaseCapture();							// �ͷ���겶��
	SetCursor(LoadCursor(NULL, IDC_ARROW));		// �������Ϊָ��
	if (m_bLButtonDown) {						// ����������Ϊ��
		CDC* pDC = pWnd->GetDC();				// ��ȡ�豸������
		pDC->SelectObject(&m_MovingPen);		// ѡ���ƶ�ʱ�ı�
		pDC->SetROP2(R2_XORPEN);				// ����Ϊ����ͼ��ʽ
		pDC->SetBkMode(TRANSPARENT);			// ����͸������ģʽ
		pDC->SelectObject(&m_MovingBrush);		// ѡ���ƶ�ˢ��
												// �ƶ�ʱĬ�Ͽ�ˢ�����ڶ�̬�����ͼ�Σ�����Ρ���Բ�ȣ�
		if (m_bErase) 							// ��Ҫ����Ϊ��
			MovingDraw(pDC);

		pDC->SelectObject(&m_TargetPen);		// ѡ��Ŀ��״̬�ı�
		pDC->SelectObject(&m_TargetBrush);		// ѡ��Ŀ��״̬��ˢ��
		pDC->SetROP2(R2_COPYPEN);				// ����Ϊ���ǻ�ͼ��ʽ
		m_pm = point;							// �����յ�
		m_aPoints[nCount++] = point;			// ��¼��
		TargetDraw(pDC);						// �������յ�ͼ��
		m_bLButtonDown = FALSE;					// ��������������Ϊ��
		m_bErase = FALSE;						// ����Ҫ����Ϊ��
		pWnd->ReleaseDC(pDC);					// �ͷ��豸������
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
		assert(nCount == 2);//��������ͼ�Σ���ͼ���õĵ��ȻΪ2
		nCount = 0;
		break;
	case GS_POLYLINE:
		MovingDraw(pDC);
		break;
	case GS_POLYGON:
		pDC->SetROP2(R2_XORPEN);					// ����Ϊ����ͼ��ʽ
		rect.SetRect(m_aPoints[0], m_aPoints[nCount - 1]);
		d = max(abs(rect.Width()), abs(rect.Height()));
		if (d <= (m_iPenWidth + 1) * 2 && nCount - 1 >= 3)	// ����ε�������Ϊ����
															// ���һ�������ʼ����һ����Χ����ڱ�ʾͬһ����
															// �ܵ���ΪnCount - 1
		{
			pDC->Polyline(m_aPoints, nCount - 1);		// �������ƹ����е�����
			pDC->SetROP2(R2_COPYPEN);					// ����Ϊ���ǻ�ͼ��ʽ
			pDC->Polygon(m_aPoints, nCount - 1);		// �������յĶ����
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
	default:											// ����û��ѡ��ͼ��ʱ�ĵ�ļ�¼
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
	pDC->SetBkMode(TRANSPARENT);			// ����͸������ģʽ
	pDC->SelectObject(&m_TargetPen);		// ѡ��Ŀ��״̬�ı�
	pDC->SelectObject(&m_TargetBrush);		// ѡ��Ŀ��״̬��ˢ��
	pDC->SetROP2(R2_XORPEN);					// ����Ϊ����ͼ��ʽ
	pDC->Polyline(m_aPoints, nCount);			// �������ƹ����е�����
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
