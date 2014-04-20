// Preview.cpp : implementation file
//

#include "stdafx.h"
#include "autoPrint2.h"
#include "Preview.h"
#include "afxdialogex.h"
#include "global.h"
#include "MemDC.h"
#include "msword.h"
// CPreview dialog

IMPLEMENT_DYNAMIC(CPreview, CDialogEx)

CPreview::CPreview(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPreview::IDD, pParent)
{
}

CPreview::~CPreview()
{
	//m_framerctl_preview.Close();
}


void CPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BTN_HOME2, m_cBtnGoHome);
	DDX_Control(pDX, IDC_BTN_PAY2, m_cBtnPay2);
	DDX_Control(pDX, IDC_BTN_SETTINGS2, m_cBtnSettings2);
	DDX_Control(pDX, IDC_BTN_HOME2, m_cBtnHome2);
	DDX_Control(pDX, IDC_FRAMERCONTROL_PREVIEW, m_cFCPreview);
}


BEGIN_MESSAGE_MAP(CPreview, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_SETTINGS2, &CPreview::OnBnClickedBtnSettings2)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_PAY2, &CPreview::OnBnClickedBtnPay2)
	ON_BN_CLICKED(IDC_BTN_HOME2, &CPreview::OnBnClickedBtnHome2)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

// CPreview message handlers


BOOL CPreview::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnEraseBkgnd(pDC);
	CRect rect;
	GetClientRect(rect);

	CMemDC_S pDevC(pDC, rect);

	/////////////////////////////////////////////////////////////////////////////////
	// just put something in the background - unrelated to GdipButton
	/////////////////////////////////////////////////////////////////////////////////
	if (m_hBitmap)
	{
		pDevC->SelectObject(m_hBitmap);
	}
	/////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////
	// Since this function just painted the background into the memory DC,
	// this is the correct information that can be provided to the buttons
	/////////////////////////////////////////////////////////////////////////////////
	SetButtonBackGrounds(pDevC);
	/////////////////////////////////////////////////////////////////////////////////
	return TRUE;
}


BOOL CPreview::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	this->m_cBtnHome2.LoadStdImage(IDR_BTN_HOME,_T("PNG"));
	this->m_cBtnSettings2.LoadStdImage(IDR_BTN_SETTINGS,_T("PNG"));
	this->m_cBtnPay2.LoadStdImage(IDR_BTN_PAY,_T("PNG"));

	HBITMAP		hBitmap			= NULL;
	HINSTANCE	hInstResource	= NULL;
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_CHILDBKGND), RT_BITMAP);
	m_hBitmap = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(IDB_CHILDBKGND), IMAGE_BITMAP, 0, 0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPreview::OnBnClickedBtnSettings2()
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->GetSafeHwnd(),WM_CHILDSWITCH,DLG_PRINTSETTING,0);
}


void CPreview::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	SetPicCtlBackGrounds();

	////由于此窗口创建的时候，还没有选择要预览的文件，所以在OnPaint里做显示文件预览

}

void CPreview::SetOnePicBackGnd(LPCTSTR filepath, UINT ID)
{
	CImage image; //创建图片类
	CRect rect;//定义矩形类

	image.Load(filepath); //根据图片路径加载图片
	int cx = image.GetWidth();//获取图片宽度
	int cy = image.GetHeight();//获取图片高度

	GetDlgItem(ID)->GetWindowRect(&rect);//将窗口矩形选中到picture控件上
	ScreenToClient(&rect);//将客户区选中到Picture控件表示的矩形区域内
	GetDlgItem(ID)->MoveWindow(rect.left, rect.top, cx, cy, TRUE);//将窗口移动到Picture控件表示的矩形区域

	CWnd *pWnd=GetDlgItem(ID);//获得pictrue控件窗口的句柄
	pWnd->GetClientRect(&rect);//获得pictrue控件所在的矩形区域
	CDC *pDC=pWnd->GetDC();//获得pictrue控件的DC
	image.Draw(pDC->m_hDC, rect); //将图片画到Picture控件表示的矩形区域

	ReleaseDC(pDC);//释放picture控件的DC
}

void CPreview::SetButtonBackGrounds(CDC* pDC)
{
	this->m_cBtnHome2.SetBkGnd(pDC);
	this->m_cBtnSettings2.SetBkGnd(pDC);
	this->m_cBtnPay2.SetBkGnd(pDC);
}

void CPreview::SetPicCtlBackGrounds()
{
	LPCTSTR arrPath[] = {	_T("res\\PreviewTitle.png")
						};
		UINT arrID[] = {IDC_PREVIEWTITLE
						};
	for(int i = 0; i < 1; i ++)
		SetOnePicBackGnd(arrPath[i],arrID[i]);
}

void CPreview::OnBnClickedBtnPay2()
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->GetSafeHwnd(),WM_CHILDSWITCH,DLG_PAY,0);
}


void CPreview::OnBnClickedBtnHome2()
{
	// TODO: Add your control notification handler code here
	m_cFCPreview.Close();
	::PostMessage(GetParent()->GetSafeHwnd(),WM_CLOSE,0,0);
}



void CPreview::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here

	//预览文件总是死机，另找解决办法
	//COleVariant url(m_fileFullPathInPreview);
	//COleVariant covTrue((short)TRUE),
	//	covFalse((short)FALSE),
	//	covNULL("none"),
	//	covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR);
	//m_cFCPreview.Open(url,covTrue,covOptional,covOptional,covOptional);

	//m_cFCPreview.PrintPreview();	//预览文档

}
