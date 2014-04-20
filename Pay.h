#pragma once
#include "GdipButton.h"

// CPay dialog

class CPay : public CDialogEx
{
	//DECLARE_DYNAMIC(CPay)

public:
	CPay(CWnd* pParent = NULL);   // standard constructor
	~CPay();

// Dialog Data
	enum { IDD = IDD_DLG_PAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CGdipButton m_cBtnGoHome;
	CGdipButton m_cBtnPayByCard;
	CGdipButton m_cBtnPayByCoinCash;
	CGdipButton m_cBtnPayByWeixin;
	CGdipButton m_cBtnPrinting;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
	void SetButtonBackGrounds(CDC* pDC);
	void SetPicCtlBackGrounds();
	void SetOnePicBackGnd(LPCTSTR filepath, UINT ID);
protected:
	HBITMAP m_hBitmap;
	HICON m_hIcon;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnHome4();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnPaybyweixin();
	afx_msg void OnBnClickedBtnPaybycard();
	afx_msg void OnBnClickedBtnPaybycoincash();
	CStatic m_cStaticBasePrice;
	CStatic m_cStaticChange;
	CStatic m_cStaticUnPaid;
	CStatic m_cStaticPaid;
	CStatic m_cStaticPrintingCopies;
	CStatic m_cStaticPrintingFileName;
	CStatic m_cStaticPrintingPages;
	CStatic m_cStaticTotalShouldPay;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

public:
	//HANDLE hThreadForScanNoteAcceptor;
	//void ScanNoteAcceptorThreadFunc();

};
