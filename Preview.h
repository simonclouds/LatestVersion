#pragma once

#include "GdipButton.h"
#include "CFramerControl.h"
// CPreview dialog

class CPreview : public CDialogEx
{
	DECLARE_DYNAMIC(CPreview)

public:
	CPreview(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPreview();

// Dialog Data
	enum { IDD = IDD_DLG_PREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
//	CButton m_cBtnGoHome;
	CGdipButton m_cBtnPay2;
	CGdipButton m_cBtnSettings2;
	CGdipButton m_cBtnHome2;
	afx_msg void OnBnClickedBtnSettings2();

	void SetButtonBackGrounds(CDC* pDC);				//���ð�ť����
	void SetPicCtlBackGrounds();						//����������ͼ
	void SetOnePicBackGnd(LPCTSTR filepath, UINT ID);	//����һ����ͼ
protected:	
	HBITMAP m_hBitmap;

protected:
	HICON m_hIcon;
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnPay2();
	afx_msg void OnBnClickedBtnHome2();

	CString m_fileFullPathInPreview;					//��Ԥ�����ļ���ȫ·��
//	afx_msg void OnFramercontrolPreview();
	CFramerControl m_cFCPreview;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
