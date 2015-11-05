// GraphStyleEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "Interactive_plotting.h"
#include "GraphStyleEdit.h"


// CGraphStyleEdit

IMPLEMENT_DYNAMIC(CGraphStyleEdit, CEdit)

CGraphStyleEdit::CGraphStyleEdit()
{

}

CGraphStyleEdit::~CGraphStyleEdit()
{
}


BEGIN_MESSAGE_MAP(CGraphStyleEdit, CEdit)
//	ON_WM_CHAR()
//	ON_CONTROL_REFLECT(EN_KILLFOCUS, &CGraphStyleEdit::OnEnKillfocus)
//	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

// CGraphStyleEdit 消息处理程序
//void CGraphStyleEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	CEdit::OnChar(nChar, nRepCnt, nFlags); 
//}

/*
////////////////////////////////////////////////////////////////////////// 
//绘制窗口。 
////////////////////////////////////////////////////////////////////////// 
void CMyEdit::OnPaint()
{
	PAINTSTRUCT ps;
	TEXTMETRIC tm;
	int nSelStart = 0, nSelEnd = 0, nDrawStart = 0, nDrawLen = 0, nTxtLen = 0;
	RECT r;
	CBitmap b;
	LPTSTR sz = (LPTSTR)calloc(1024, sizeof(TCHAR));
	CPaintDC* d2 = (CPaintDC*)BeginPaint(&ps);
	CDC d1;
	CFont f;
	CWnd* p = GetParent();
	nTxtLen = GetWindowText(sz, 1024);
	b.LoadBitmap(IDB_BITMAP1);
	d1.CreateCompatibleDC(p->GetDC());
	GetWindowRect(&r);
	p->ScreenToClient(&r);
	d1.SelectObject(b);
	d2->BitBlt(0, 0, r.right - r.left, r.bottom - r.top, &d1, r.left, r.top, SRCCOPY);
	f.CreateFontIndirect(&m_lf);
	d2->SelectObject(f);
	d2->SetBkMode(TRANSPARENT);
	d2->GetTextMetrics(&tm);
	GetSel(nSelStart, nSelEnd);
	if (r.right - r.left<nTxtLen*tm.tmAveCharWidth)
	{
		nDrawStart = 0 - tm.tmAveCharWidth*nSelStart;
		nDrawLen = (r.right - r.left) / tm.tmAveCharWidth;
	}
	else
	{
		nDrawStart = 0;
		nDrawLen = nTxtLen;
	}
	d2->TextOut(nDrawStart, 3, sz, nDrawLen);
	d2->SelectObject(GetStockObject(NULL_BRUSH));
	d2->SelectObject(CreatePen(PS_DOT, 1, RGB(255, 0, 0)));
	d2->Rectangle(0, 0, r.right - r.left, r.bottom - r.top);
	POINT pt;
	pt = GetCaretPos();
	pt.x = nDrawLen*tm.tmAveCharWidth;
	SetCaretPos(pt);
	delete sz;
	EndPaint(&ps);
}

////////////////////////////////////////////////////////////////////////// 
//暂不处理粘滞按键和功能键这2种情况。 
////////////////////////////////////////////////////////////////////////// 
void CMyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	TEXTMETRIC tm;
	int nSelStart = 0, nSelEnd = 0, nDrawStart = 0, nDrawLen = 0, nTxtLen = 0;
	RECT r;
	CBitmap b;
	LPTSTR sz = (LPTSTR)calloc(1024, sizeof(TCHAR));
	LPTSTR input = (LPTSTR)calloc(1024, sizeof(TCHAR));
	CClientDC d2(this);
	CDC d1;
	CFont f;
	CWnd* p = GetParent();
	nTxtLen = GetWindowText(sz, 1024);
	wsprintf(input, L"%c", nChar);
	lstrcat(sz, input);
	SetWindowText(sz);
	b.LoadBitmap(IDB_BITMAP1);
	d1.CreateCompatibleDC(p->GetDC());
	GetWindowRect(&r);
	p->ScreenToClient(&r);
	d1.SelectObject(b);
	d2.BitBlt(0, 0, r.right - r.left, r.bottom - r.top, &d1, r.left, r.top, SRCCOPY);
	f.CreateFontIndirect(&m_lf);
	d2.SelectObject(f);
	d2.SetBkMode(TRANSPARENT);
	d2.GetTextMetrics(&tm);
	GetSel(nSelStart, nSelEnd);
	if (r.right - r.left<nTxtLen*tm.tmAveCharWidth)
	{
		nDrawStart = 0 - tm.tmAveCharWidth*nSelStart;
		nDrawLen = (r.right - r.left) / tm.tmAveCharWidth;
	}
	else
	{
		nDrawStart = 0;
		nDrawLen = nTxtLen;
	}
	d2.TextOut(nDrawStart, 3, sz, nDrawLen);
	d2.SelectObject(GetStockObject(NULL_BRUSH));
	d2.SelectObject(CreatePen(PS_DOT, 1, RGB(255, 0, 0)));
	d2.Rectangle(0, 0, r.right - r.left, r.bottom - r.top);
	POINT pt;
	pt = GetCaretPos();
	pt.x = nDrawLen*tm.tmAveCharWidth;
	SetCaretPos(pt);
	delete sz;
	delete input;
	//CEdit::OnChar(nChar, nRepCnt, nFlags); 
}
*/

//void CGraphStyleEdit::OnEnKillfocus()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	//GetDC()->SetBkMode(TRANSPARENT);
//	RECT rect;
//	GetClientRect(&rect);
//	CDC *pDC = GetDC();
//	CBrush bx;
//	bx.CreateSolidBrush(RGB(10, 10, 10));
//	pDC->SelectObject(&bx);
//	//pDC->SelectStockObject(NULL_BRUSH);
//	//pDC->Rectangle(&rect);
//	ReleaseDC(pDC);
//	EnableWindow(false);
//}


//void CGraphStyleEdit::OnKillFocus(CWnd* pNewWnd)
//{
//	CEdit::OnKillFocus(pNewWnd);
//
//	// TODO: 在此处添加消息处理程序代码
//	//EnableWindow(false);
//}
