#pragma once
#include "afxwin.h"


// CDrawSettingDlg 对话框

class CDrawSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDrawSettingDlg)
public:
	CDrawSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDrawSettingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAW_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();						//初始化对话框内容

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedPenColorShowStatic();	
	afx_msg void OnStnClickedBrushColorShowStatic();
	afx_msg void OnStnClickedBrushPictureShowStatic();
	CStatic m_picPen;						// 显示笔的颜色
	CStatic m_picBrush;						// 显示刷子颜色
	COLORREF m_crPenCol;					// 保存笔的颜色
	COLORREF m_crBrushCol;					// 保存刷子颜色
	CStatic m_picBrushPicShow;				// 显示刷子图案类型所选图片
	CString m_sBrushPicPath;				// 保存刷子图案类型所选图片的地址，默认为空
	int m_iBrushPicWidth;					// 刷子图案类型所选图片尺寸，默认为0
	int m_iBrushPicHeight;
	int m_iPenWidth;						// 保存笔宽
	int m_iPenStyle;						// 保存笔的类型
	int m_iGraphStyle;						// 保存几何图形的类型
	BOOL m_bGraphFill;						// 填充布尔值
	int m_iBrushStyle;						// 保存刷子的类型
	int m_iBrushStripeStyle;				// 保存刷子条纹类型的风格
private:
	void ShowPictureOnBrushPictureShowStatic();// 在对应的图片控件上显示图片
public:
	afx_msg void OnPaint();
};
