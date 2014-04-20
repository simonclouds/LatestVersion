#pragma once

#include "FilePick.h"
#include "PrintSettings.h"
#include "Preview.h"
#include "Pay.h"
#include "GdipButton.h"
// CMainPage dialog

class CMainPage : public CDialogEx
{
	DECLARE_DYNAMIC(CMainPage)

public:
	CMainPage(CWnd* pParent = NULL);   // standard constructor
	~CMainPage();

// Dialog Data
	enum { IDD = IDD_DLG_MAINPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	int m_CurSelDlg;

	CFilePick			FilePickDlg;
	CPreview			PreviewDlg;
	CPrintSettings		PrintSettingsDlg;
	CPay				PayDlg;
	
	CDialog * pDialog[4];

	CGdipButton m_cBtnFilePick;
	CGdipButton m_cBtnPay;
	CGdipButton m_cBtnSettings;
	CStatic m_cPicChildDlgSwitch;
	afx_msg void OnBnClickedBtnFilepick();
	afx_msg void OnBnClickedBtnSettings();
	afx_msg void OnBnClickedBtnPay();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnChildDlgSwitchClicked(WPARAM wParam, LPARAM lParam);

	void SetButtonBackGrounds(CDC* pDC);				//设置按钮背景
	void SetPicCtlBackGrounds();						//设置所有贴图
	void SetOnePicBackGnd(LPCTSTR filepath, UINT ID);	//设置一个贴图
protected:	
	HBITMAP m_hBitmap;
public:
//	afx_msg void OnDoubleclickedBtnSettings();
protected:
//	afx_msg LRESULT OnMoneyGetMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMoneyGetMessage(WPARAM wParam, LPARAM lParam);
};
