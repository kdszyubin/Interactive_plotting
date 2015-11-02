#pragma once
#include "afxwin.h"


// CDrawSettingDlg �Ի���

class CDrawSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDrawSettingDlg)
public:
	CDrawSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrawSettingDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAW_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();						//��ʼ���Ի�������

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedPenColorShowStatic();	
	afx_msg void OnStnClickedBrushColorShowStatic();
	afx_msg void OnStnClickedBrushPictureShowStatic();
	CStatic m_picPen;						// ��ʾ�ʵ���ɫ
	CStatic m_picBrush;						// ��ʾˢ����ɫ
	COLORREF m_crPenCol;					// ����ʵ���ɫ
	COLORREF m_crBrushCol;					// ����ˢ����ɫ
	CStatic m_picBrushPicShow;				// ��ʾˢ��ͼ��������ѡͼƬ
	CString m_sBrushPicPath;				// ����ˢ��ͼ��������ѡͼƬ�ĵ�ַ��Ĭ��Ϊ��
	int m_iBrushPicWidth;					// ˢ��ͼ��������ѡͼƬ�ߴ磬Ĭ��Ϊ0
	int m_iBrushPicHeight;
	int m_iPenWidth;						// ����ʿ�
	int m_iPenStyle;						// ����ʵ�����
	int m_iGraphStyle;						// ���漸��ͼ�ε�����
	BOOL m_bGraphFill;						// ��䲼��ֵ
	int m_iBrushStyle;						// ����ˢ�ӵ�����
	int m_iBrushStripeStyle;				// ����ˢ���������͵ķ��
private:
	void ShowPictureOnBrushPictureShowStatic();// �ڶ�Ӧ��ͼƬ�ؼ�����ʾͼƬ
public:
	afx_msg void OnPaint();
};
