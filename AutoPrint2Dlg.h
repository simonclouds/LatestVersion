/*#pragma once


// CAutoPrint2Dlg dialog

class CAutoPrint2Dlg : public CDialog
{
	DECLARE_DYNAMIC(CAutoPrint2Dlg)

public:
	CAutoPrint2Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAutoPrint2Dlg();

// Dialog Data
	enum { IDD = IDD_AUTOPRINT2_DLG_HOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

// autoPrint2Dlg.h : header file
//
*/
#if !defined(AFX_AUTOPRINT2DLG_H__33959C67_8453_41B6_88B3_542925125169__INCLUDED_)
#define AFX_AUTOPRINT2DLG_H__33959C67_8453_41B6_88B3_542925125169__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GdipButton.h"
/////////////////////////////////////////////////////////////////////////////
// CAutoPrint2Dlg dialog

class CAutoPrint2Dlg : public CDialog
{
	DECLARE_DYNAMIC(CAutoPrint2Dlg)
// Construction
public:
	CString m_CurrentTime;
	CString m_uSelected;
	CAutoPrint2Dlg(CWnd* pParent = NULL);	// standard constructor
	~CAutoPrint2Dlg();
// Dialog Data
	//{{AFX_DATA(CAutoPrint2Dlg)
	enum { IDD = IDD_AUTOPRINT2_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoPrint2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAutoPrint2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBTNUPrint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int u_count;	//count the number of U disk.
public:
	afx_msg void OnBnClickedBtnNetprint();
	afx_msg void OnBnClickedUpanSelected();
	afx_msg void OnBnClickedButtonMovableDevices();

	//simon added for load png for button
	//void SetButtonBackGrounds(CDC *pDC);

public:
	CGdipButton m_cBtnMovableDevices;
	CGdipButton m_cBtnNetprint;

	CStatic m_cPicTitle;

public:
	void SetButtonBackGrounds(CDC* pDC);
	void SetPicCtlBackGrounds();
	void SetOnePicBackGnd(LPCTSTR filepath, UINT ID);
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	HBITMAP m_hBitmap;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOPRINT2DLG_H__33959C67_8453_41B6_88B3_542925125169__INCLUDED_)
