#pragma once
#include "GdipButton.h"

// CPrintSettings dialog


class CPrintSettings : public CDialogEx
{
	DECLARE_DYNAMIC(CPrintSettings)

public:
	CPrintSettings(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPrintSettings();

// Dialog Data
	enum { IDD = IDD_DLG_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:		//For ImageButton
	virtual BOOL OnInitDialog();
	CGdipButton m_cBtnAdd;
	CGdipButton m_cBtnHome3;
	CGdipButton m_cBtnPay3;
	CGdipButton m_cBtnSub;
	CGdipButton m_cBtnKey0;
	CGdipButton m_cBtnKey1;
	CGdipButton m_cBtnKey2;
	CGdipButton m_cBtnKey3;
	CGdipButton m_cBtnKey4;
	CGdipButton m_cBtnKey5;
	CGdipButton m_cBtnKey6;
	CGdipButton m_cBtnKey7;
	CGdipButton m_cBtnKey8;
	CGdipButton m_cBtnKey9;
	CGdipButton m_cBtnComma;
	CGdipButton m_cBtnDash;
	CGdipButton m_cBtnDelete;
	CGdipButton m_cBtnOkey;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
	void SetButtonBackGrounds(CDC* pDC);
	void SetPicCtlBackGrounds();
	void SetOnePicBackGnd(LPCTSTR filepath, UINT ID);
protected:
	HBITMAP m_hBitmap;

public:
	afx_msg void OnBnClickedBtnHome3();
	afx_msg void OnPaint();
protected:
	HICON m_hIcon;


public:
	afx_msg void OnBnClickedBtnPay3();
	afx_msg void OnBnClickedBtn1();
	afx_msg void OnBnClickedBtn2();
	afx_msg void OnBnClickedBtn3();
	afx_msg void OnBnClickedBtn4();
	afx_msg void OnBnClickedBtn5();
	afx_msg void OnBnClickedBtn6();
	afx_msg void OnBnClickedBtn7();
	afx_msg void OnBnClickedBtn8();
	afx_msg void OnBnClickedBtn9();
	afx_msg void OnBnClickedBtncomma();
	afx_msg void OnBnClickedBtn0();
	afx_msg void OnBnClickedBtndash();
	afx_msg void OnBnClickedBtndelete();
	afx_msg void OnBnClickedBtnokey();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	void FreshUserCStatic();
	void CheckPagesFromPageRangAnyway();
	CString m_PagesUserSelected;
	unsigned int m_copies;
	CStatic m_CopiesUserSelect;
	afx_msg void OnBnClickedBtnSub();
	afx_msg void OnBnClickedBtnAdd();
	CStatic m_CopiesTotal;
	afx_msg void OnBnClickedRadioAllpages();

public:
	int GetCountFromStr(CString str);
	BOOL IncludeInvaidCharGroup(CString str);
	int GetPagesFromString(CString str);
	int CString2Int(const CString str);
//	BOOL isOutOfPageRange(int inputPage, int fileTotalPage);
	BOOL isAllowedChar(char c);
	BOOL isDigit(char c);
	BOOL InputPageRangeValid(int inputPage, int fileTotalPage);
	CStatic m_cShowPagesSelect;
	

	afx_msg void OnBnClickedRadioUserpages();
};
