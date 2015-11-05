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
	void PenStyleRefresh();					//根据变量刷新笔风格
	void GraphStyleRefresh(CDC *pDC, const int & GraphStyleChose = -1);				//根据变量更新图标风格记录（与记录不同，则需更新nCount)
	void BrushStyleRefresh();				//根据变量更新刷子风格
	void Refresh(CDC *pDC);							//调用前面三个函数

	void GetDxDy(int &dx, int &dy);			//获取鼠标当前位置和按下左键时的位置的相对距离
	void RevokeDraw(CDC *pDC);

	void RemoveEdit(CDC * pDC);


	COLORREF m_crPenCol;					//保存笔的颜色
	COLORREF m_crBrushCol;					//保存刷子颜色
	CString m_sBrushPicPath;				//保存刷子图案类型所选图片的地址，默认为空
	int m_iBrushPicWidth;					//刷子图案类型所选图片尺寸，默认为0
	int m_iBrushPicHeight;
	int m_iPenWidth;						//保存笔宽
	int m_iPenStyle;						//保存笔的类型
	int m_iGraphStyle;						//保存几何图形的类型
	BOOL m_bGraphFill;						//填充布尔值
	int m_iBrushStyle;						//保存刷子的类型
	int m_iBrushStripeStyle;				//保存刷子条纹类型的风格

	int m_iOldGraphStyle = -1;

	CGraphStyleEdit *m_pEdit;
private:
	BOOL m_bLButtonDown,				// 判断是否按下左鼠标键
		m_bErase;						// 是否需要擦除图形
	CPoint m_p0, m_pm;					// 记录最近两个点，起点和终点
	CPen m_MovingPen;					//图形移动过程中的笔和刷子类型，默认为灰色点线笔和空刷，见类初始化函数
	CBrush m_MovingBrush;
	CPen m_TargetPen;					//图形目标状态的笔类型
	CBrush m_TargetBrush;				//图形目标状态的刷子类型
	
	POINT m_aPoints[MAX_NCOUNT];		//保存绘图过程中所有的点
	int nCount = 0;						//绘制过程中的点的数量

	void MovingDraw(CDC* pDC);			//移动时进行绘图
	void TargetDraw(CDC* pDC);			//目标位置绘图，除折线和多边形外，其他图形的TargetDraw与MovingDraw一样
};


