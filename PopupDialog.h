#if !defined(AFX_PopupDialog_H__9DD8D1C5_1B01_46BA_9E7E_975A7442B0C2__INCLUDED_)
#define AFX_PopupDialog_H__9DD8D1C5_1B01_46BA_9E7E_975A7442B0C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PopupDialog.h : header file
//
#include "resource.h"
#include "GdipButton.h"
/////////////////////////////////////////////////////////////////////////////
// PopupDialog dialog

#define MSG_MAXLEN 500
#define BTNTEXT_MAXLEN 50


class PopupDialog : public CDialog
{
// Construction
public:
	int m_CountDownForOperating;
	PopupDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PopupDialog)
	enum { IDD = IDD_DLG_MYPOPUPDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PopupDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(PopupDialog)
	afx_msg void OnBtnGohome();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:	
	HBITMAP m_hBitmap;
public:
	
	void SetTimeout(unsigned int time){m_CountDownForOperating = time;};
	void SetMessage(char *string);
	void SetNoTimer();
	//设置Button上显示的文字
	void SetButtonText(char *string);
	void SetButtonBackGrounds(CDC *pDC);
private:
	int m_timeout;
	char m_message[MSG_MAXLEN];
	char m_textonBtn[BTNTEXT_MAXLEN];
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PopupDialog_H__9DD8D1C5_1B01_46BA_9E7E_975A7442B0C2__INCLUDED_)
