// DrawSettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Interactive_plotting.h"
#include "DrawSettingDlg.h"
#include "afxdialogex.h"


#define MAX_PENWIDTH 100
// CDrawSettingDlg �Ի���

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


// CDrawSettingDlg ��Ϣ�������
BOOL CDrawSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//������
	SetDlgItemInt(IDC_PEN_LINE_WIDTH, m_iPenWidth);
	CSpinButtonCtrl *pSpin =
		(CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_PEN_LINE_WIDTH);
	pSpin->SetRange(0, MAX_PENWIDTH);

	//ͼ������
	CComboBox* pCB = (CComboBox*)GetDlgItem(IDC_PEN_LINE_STYLE);
	pCB->SetCurSel(m_iPenStyle);
	CheckRadioButton(IDC_GRAPH_LINE, IDC_GRAPH_TEXT, IDC_GRAPH_LINE + m_iGraphStyle);//Ĭ��ѡ��ͼ������Ϊֱ��
	CheckDlgButton(IDC_GRAPH_FILL, m_bGraphFill);

	//ˢ������
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
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
					   //������ɫ�������
	CRect rect;
	m_picPen.GetClientRect(&rect);//��ȡ�ռ�����
	FillRect(m_picPen.GetDC()->GetSafeHdc(), &rect, CBrush(m_crPenCol));//����������ɫ
	m_picBrush.GetClientRect(&rect);//��ȡ�ռ�����
	FillRect(m_picBrush.GetDC()->GetSafeHdc(), &rect, CBrush(m_crBrushCol));//����������ɫ
	ShowPictureOnBrushPictureShowStatic();//ˢ������->ͼ���ߴ�
}

void CDrawSettingDlg::OnStnClickedPenColorShowStatic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ��ɫ
	CColorDialog colDlg(m_crPenCol, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK)
		m_crPenCol = colDlg.GetColor();
	//������ɫ�������
	CRect rect;
	m_picPen.GetClientRect(&rect);//��ȡ�ռ�����

	FillRect(m_picPen.GetDC()->GetSafeHdc(), &rect, CBrush(m_crPenCol));//����������ɫ
}


void CDrawSettingDlg::OnStnClickedBrushColorShowStatic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CColorDialog colDlg(m_crBrushCol, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK)
		m_crBrushCol = colDlg.GetColor();
	//������ɫ�������
	CRect rect;
	m_picBrush.GetClientRect(&rect);//��ȡ�ռ�����

	FillRect(m_picBrush.GetDC()->GetSafeHdc(), &rect, CBrush(m_crBrushCol));//����������ɫ
}


void CDrawSettingDlg::OnStnClickedBrushPictureShowStatic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	wchar_t *filters = L"λͼ�ļ�(*.bmp)|*.bmp|�ɽ���ͼ�θ�ʽ�ļ�(*.gif) | *.gif | ����ͼ��ר�����ļ�(*.jpg; *.jpe) | *.jpg; *.jpe | �����ļ�(*.*) | *.* || ";
	CFileDialog fileDlg(TRUE, L"bmp", L"*.bmp",
		OFN_HIDEREADONLY, filters);
	if (fileDlg.DoModal() == IDOK)
	{
		m_sBrushPicPath = fileDlg.GetPathName();
		//MessageBox(m_sBrushPicPath, L"�û�ѡ����ļ�");
		ShowPictureOnBrushPictureShowStatic();
	}
}

void CDrawSettingDlg::ShowPictureOnBrushPictureShowStatic()
{
	CRect rect;
	m_picBrushPicShow.GetClientRect(&rect);
	CImage image;       //ʹ��ͼƬ��  
	if (!image.Load(m_sBrushPicPath))   //װ��·����ͼƬ��Ϣ��ͼƬ�� 
	{
		//MessageBox(m_sBrushPicPath);
		CDC* pDC = m_picBrushPicShow.GetWindowDC();    //�����ʾ�ؼ���DC  
		image.Draw(pDC->m_hDC, rect);      //ͼƬ���ͼƬ����Draw���� 
		ReleaseDC(pDC);
		//��ʾͼƬ�ߴ�
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

