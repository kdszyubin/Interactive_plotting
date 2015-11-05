#pragma once
#include "GraphStyleEdit.h"
#define MAX_NCOUNT 500
#define GS_LINE 0
#define GS_RECTANGLE 1
#define GS_ROUNDRECT 2
#define GS_CIRCLE 3
#define GS_ELLIPSE 4
#define GS_POLYLINE 5
#define GS_POLYGON 6
#define GS_TEXT 7

class CGraph
{
public:
	CGraph();
	~CGraph();
	void OnLButtonDown(CWnd* pWnd, UINT nFlags, CPoint point);
	void OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point);
	void OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point);
	void PenStyleRefresh();					//���ݱ���ˢ�±ʷ��
	void GraphStyleRefresh(CDC *pDC, const int & GraphStyleChose = -1);				//���ݱ�������ͼ�����¼�����¼��ͬ���������nCount)
	void BrushStyleRefresh();				//���ݱ�������ˢ�ӷ��
	void Refresh(CDC *pDC);							//����ǰ����������

	void GetDxDy(int &dx, int &dy);			//��ȡ��굱ǰλ�úͰ������ʱ��λ�õ���Ծ���
	void RevokeDraw(CDC *pDC);

	void RemoveEdit(CDC * pDC);


	COLORREF m_crPenCol;					//����ʵ���ɫ
	COLORREF m_crBrushCol;					//����ˢ����ɫ
	CString m_sBrushPicPath;				//����ˢ��ͼ��������ѡͼƬ�ĵ�ַ��Ĭ��Ϊ��
	int m_iBrushPicWidth;					//ˢ��ͼ��������ѡͼƬ�ߴ磬Ĭ��Ϊ0
	int m_iBrushPicHeight;
	int m_iPenWidth;						//����ʿ�
	int m_iPenStyle;						//����ʵ�����
	int m_iGraphStyle;						//���漸��ͼ�ε�����
	BOOL m_bGraphFill;						//��䲼��ֵ
	int m_iBrushStyle;						//����ˢ�ӵ�����
	int m_iBrushStripeStyle;				//����ˢ���������͵ķ��

	int m_iOldGraphStyle = -1;

	CGraphStyleEdit *m_pEdit;
private:
	BOOL m_bLButtonDown,				// �ж��Ƿ���������
		m_bErase;						// �Ƿ���Ҫ����ͼ��
	CPoint m_p0, m_pm;					// ��¼��������㣬�����յ�
	CPen m_MovingPen;					//ͼ���ƶ������еıʺ�ˢ�����ͣ�Ĭ��Ϊ��ɫ���߱ʺͿ�ˢ�������ʼ������
	CBrush m_MovingBrush;
	CPen m_TargetPen;					//ͼ��Ŀ��״̬�ı�����
	CBrush m_TargetBrush;				//ͼ��Ŀ��״̬��ˢ������
	
	POINT m_aPoints[MAX_NCOUNT];		//�����ͼ���������еĵ�
	int nCount = 0;						//���ƹ����еĵ������

	void MovingDraw(CDC* pDC);			//�ƶ�ʱ���л�ͼ
	void TargetDraw(CDC* pDC);			//Ŀ��λ�û�ͼ�������ߺͶ�����⣬����ͼ�ε�TargetDraw��MovingDrawһ��
};


