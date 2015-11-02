// DrawSettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Interactive_plotting.h"
#include "DrawSettingDlg.h"
#include "afxdialogex.h"


#define MAX_PENWIDTH 100
// CDrawSettingDlg 对话框

IMPLEMENT_DYNAMIC(CDrawSettingDlg, CDialogEx)

CDrawSettingDlg::CDrawSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DRAW_SETTING, pParent)
	, m_iBrushPicWidth(0)
	, m_iBrushPicHeight(0)
	, m_iPenWidth(0)
	, m_iPenStyle(0)
	, m_iGraphStyle(0)
	, m_bGraphFill(FALSE)
	, m_iBrushStyle(0)
	, m_iBrushStripeStyle(0)
{

}

CDrawSettingDlg::~CDrawSettingDlg()
{
}

void CDrawSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PEN_COLOR_SHOW_STATIC, m_picPen);
	DDX_Control(pDX, IDC_BRUSH_COLOR_SHOW_STATIC, m_picBrush);
	DDX_Control(pDX, IDC_BRUSH_PICTURE_SHOW_STATIC, m_picBrushPicShow);
	DDX_Text(pDX, IDC_BRUSH_PICTURE_WIDTH_STATIC, m_iBrushPicWidth);
	DDX_Text(pDX, IDC_BRUSH_PICTURE_HEIGHT_STATIC, m_iBrushPicHeight);
	DDX_Text(pDX, IDC_PEN_LINE_WIDTH, m_iPenWidth);
	DDV_MinMaxInt(pDX, m_iPenWidth, 0, MAX_PENWIDTH);
	DDX_CBIndex(pDX, IDC_PEN_LINE_STYLE, m_iPenStyle);
	DDX_Radio(pDX, IDC_GRAPH_LINE, m_iGraphStyle);
	DDX_Check(pDX, IDC_GRAPH_FILL, m_bGraphFill);
	DDX_Radio(pDX, IDC_BRUSH_HOLLOW, m_iBrushStyle);
	DDX_CBIndex(pDX, IDC_BRUSH_STRIPE_STYLE, m_iBrushStripeStyle);
}


BEGIN_MESSAGE_MAP(CDrawSettingDlg, CDialogEx)
	ON_STN_CLICKED(IDC_PEN_COLOR_SHOW_STATIC, &CDrawSettingDlg::OnStnClickedPenColorShowStatic)
	ON_STN_CLICKED(IDC_BRUSH_COLOR_SHOW_STATIC, &CDrawSettingDlg::OnStnClickedBrushColorShowStatic)
	ON_STN_CLICKED(IDC_BRUSH_PICTURE_SHOW_STATIC, &CDrawSettingDlg::OnStnClickedBrushPictureShowStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDrawSettingDlg 消息处理程序
BOOL CDrawSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//笔设置
	SetDlgItemInt(IDC_PEN_LINE_WIDTH, m_iPenWidth);
	CSpinButtonCtrl *pSpin =
		(CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_PEN_LINE_WIDTH);
	pSpin->SetRange(0, MAX_PENWIDTH);

	//图形设置
	CComboBox* pCB = (CComboBox*)GetDlgItem(IDC_PEN_LINE_STYLE);
	pCB->SetCurSel(m_iPenStyle);
	CheckRadioButton(IDC_GRAPH_LINE, IDC_GRAPH_TEXT, IDC_GRAPH_LINE + m_iGraphStyle);//默认选中图形类型为直线
	CheckDlgButton(IDC_GRAPH_FILL, m_bGraphFill);

	//刷子设置
	pCB = (CComboBox*)GetDlgItem(IDC_BRUSH_STRIPE_STYLE);
	pCB->SetCurSel(m_iBrushStripeStyle);
	/*
	char buf[20];
	for (int i = 0; i < 20; ++i)
		buf[i] = 0;
	_itoa_s(m_iPenStyle, buf, 10);
	MessageBox(CString(buf));*/
	CheckRadioButton(IDC_BRUSH_HOLLOW, IDC_BRUSH_PICTURE, IDC_BRUSH_HOLLOW + m_iBrushStyle);
	
	return TRUE;
}

void CDrawSettingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
					   //将笔颜色区域填充
	CRect rect;
	m_picPen.GetClientRect(&rect);//获取空间区域
	FillRect(m_picPen.GetDC()->GetSafeHdc(), &rect, CBrush(m_crPenCol));//填充该区域颜色
	m_picBrush.GetClientRect(&rect);//获取空间区域
	FillRect(m_picBrush.GetDC()->GetSafeHdc(), &rect, CBrush(m_crBrushCol));//填充该区域颜色
	ShowPictureOnBrushPictureShowStatic();//刷子设置->图案尺寸
}

void CDrawSettingDlg::OnStnClickedPenColorShowStatic()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取颜色
	CColorDialog colDlg(m_crPenCol, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK)
		m_crPenCol = colDlg.GetColor();
	//将笔颜色区域填充
	CRect rect;
	m_picPen.GetClientRect(&rect);//获取空间区域

	FillRect(m_picPen.GetDC()->GetSafeHdc(), &rect, CBrush(m_crPenCol));//填充该区域颜色
}


void CDrawSettingDlg::OnStnClickedBrushColorShowStatic()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CColorDialog colDlg(m_crBrushCol, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK)
		m_crBrushCol = colDlg.GetColor();
	//将笔颜色区域填充
	CRect rect;
	m_picBrush.GetClientRect(&rect);//获取空间区域

	FillRect(m_picBrush.GetDC()->GetSafeHdc(), &rect, CBrush(m_crBrushCol));//填充该区域颜色
}


void CDrawSettingDlg::OnStnClickedBrushPictureShowStatic()
{
	// TODO: 在此添加控件通知处理程序代码
	wchar_t *filters = L"位图文件(*.bmp)|*.bmp|可交换图形格式文件(*.gif) | *.gif | 联合图像专家组文件(*.jpg; *.jpe) | *.jpg; *.jpe | 所有文件(*.*) | *.* || ";
	CFileDialog fileDlg(TRUE, L"bmp", L"*.bmp",
		OFN_HIDEREADONLY, filters);
	if (fileDlg.DoModal() == IDOK)
	{
		m_sBrushPicPath = fileDlg.GetPathName();
		//MessageBox(m_sBrushPicPath, L"用户选择的文件");
		ShowPictureOnBrushPictureShowStatic();
	}
}

void CDrawSettingDlg::ShowPictureOnBrushPictureShowStatic()
{
	CRect rect;
	m_picBrushPicShow.GetClientRect(&rect);
	CImage image;       //使用图片类  
	if (!image.Load(m_sBrushPicPath))   //装载路径下图片信息到图片类 
	{
		//MessageBox(m_sBrushPicPath);
		CDC* pDC = m_picBrushPicShow.GetWindowDC();    //获得显示控件的DC  
		image.Draw(pDC->m_hDC, rect);      //图片类的图片绘制Draw函数 
		ReleaseDC(pDC);
		//显示图片尺寸
		m_iBrushPicWidth = image.GetWidth();
		m_iBrushPicHeight = image.GetHeight();
	}
	else
	{
		m_iBrushPicWidth = 0;
		m_iBrushPicHeight = 0;
	}
	CString temp;
	temp.Format(_T("%d"), m_iBrushPicWidth);
	GetDlgItem(IDC_BRUSH_PICTURE_WIDTH_STATIC)->SetWindowText(temp);
	temp.Format(_T("%d"), m_iBrushPicHeight);
	GetDlgItem(IDC_BRUSH_PICTURE_HEIGHT_STATIC)->SetWindowText(temp);
}

