// PopupDialog.cpp : implementation file
//

#include "stdafx.h"
#include "autoPrint2.h"
#include "resource.h"
#include "PopupDialog.h"
#include "MemDC.h"
#include "global.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PopupDialog dialog


PopupDialog::PopupDialog(CWnd* pParent /*=NULL*/)
	: CDialog(PopupDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(PopupDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_CountDownForOperating = 2;
	strcpy(m_message, "没有发现可移动存储设备，请重新返回主页插入设备进行打印！");
}


void PopupDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PopupDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PopupDialog, CDialog)
	//{{AFX_MSG_MAP(PopupDialog)
	ON_BN_CLICKED(IDC_BTN_GOHOME, OnBtnGohome)
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PopupDialog message handlers

void PopupDialog::OnBtnGohome() 
{
	// TODO: Add your control notification handler code here
	//SendMessage(WM_CLOSE);
	//OnOK();
	EndDialog(IDC_DLG_MYRETURN);
}

int PopupDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO: Add your specialized creation code here
	SetTimer(21,1000,NULL);
	return 0;
}

BOOL PopupDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	//加载本窗口背景
	HBITMAP		hBitmap			= NULL;
	HINSTANCE	hInstResource	= NULL;
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_POPDLGBKG), RT_BITMAP);
	m_hBitmap = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(IDB_POPDLGBKG), IMAGE_BITMAP, 0, 0, 0);
	
	
	CStatic * pWnd=(CStatic *)GetDlgItem(IDC_TIPS);
	if (pWnd != NULL )
		pWnd->SetWindowText(m_message);
	CButton * pBtn = (CButton *)GetDlgItem(IDC_BTN_GOHOME);
	if (pBtn != NULL )
		pBtn->SetWindowText(m_textonBtn);
	return TRUE;
}
//函数功能:	设置当没有发现移动存储设备，对话框5秒后自动关闭
void PopupDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 21)
	{
		if (m_CountDownForOperating == 0)
		{
			KillTimer(21);
			//SendMessage(WM_CLOSE);
			OnOK();
		}

		//char strOnBtn[500] = "返 回 主 页";
		//char strOnBtn[BTNTEXT_MAXLEN] = m_textonBtn;
		char strOnBtn[BTNTEXT_MAXLEN];
		memset(strOnBtn,0,BTNTEXT_MAXLEN);
		strncpy(strOnBtn,m_textonBtn,BTNTEXT_MAXLEN-1);

		sprintf(strOnBtn,"%s( %d )",strOnBtn,m_CountDownForOperating);
		SetDlgItemText(IDC_BTN_GOHOME,strOnBtn);
		m_CountDownForOperating --;
	}
	
	CDialog::OnTimer(nIDEvent);
}

void PopupDialog::SetMessage(char *string)
{
	memset(m_message, 0, MSG_MAXLEN);
	strncpy(m_message, string, MSG_MAXLEN-1);
}

void PopupDialog::SetButtonText( char *string )
{
	memset(m_textonBtn, 0, BTNTEXT_MAXLEN);
	strncpy(m_textonBtn, string, BTNTEXT_MAXLEN-1);
}


BOOL PopupDialog::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnEraseBkgnd(pDC);
	CRect rect;
	GetClientRect(rect);

	CMemDC_S pDevC(pDC, rect);

	if (m_hBitmap)
	{
		pDevC->SelectObject(m_hBitmap);
	}
	SetButtonBackGrounds(pDevC);
	return TRUE;
}

void PopupDialog::SetButtonBackGrounds( CDC *pDC )
{

}



//设置弹出框上提示文字的背景透明
HBRUSH PopupDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_DLG)
	{
		hbr = (HBRUSH)::CreateSolidBrush(RGB(146,161,202));
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		//pDC->SetTextColor(RGB(255,255,255));
		return HBRUSH(GetStockObject((HOLLOW_BRUSH)));
	}
	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
