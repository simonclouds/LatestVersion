// MainPage.cpp : implementation file
//

#include "stdafx.h"
#include "autoPrint2.h"
#include "MainPage.h"
#include "afxdialogex.h"
#include "MemDC.h"
#include "global.h"

extern CTransaction transaction;
extern CEnvironment environment;


//for note cash acceptor
extern "C"  int  OpenNV9 (LPCTSTR lpFileName);
extern "C"  int SendCommand(char *cmd,unsigned char length);
extern "C"  void  ReadResult(const char *cmd,unsigned char *rsl_lenth);
extern "C"  int  CloseNV9 (void);
extern "C"  int EnableNV9ToRecvMoney();
extern "C"  int DisableNV9ToRecvMoney();



#define GETSCREENRECT(rc, control) CRect rc; control.GetWindowRect(rc); ScreenToClient(rc);
// CMainPage dialog

IMPLEMENT_DYNAMIC(CMainPage, CDialogEx)


CMainPage::CMainPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainPage::IDD, pParent)
{
	CSysLog sl;
	CString noteAcceptorCOMstr = environment.getCOMForNoteAcceptor();
	int openNV9Result = OpenNV9(noteAcceptorCOMstr);
	if (openNV9Result == 0)	{
		environment.SetNoteAcceptorStatus(true);
		sl.writeLog("打开纸币器成功",__FILE__,__FUNCTION__,__LINE__);
	} 
	else {
		sl.writeLog("打开纸币器失败",__FILE__,__FUNCTION__,__LINE__);
		environment.SetNoteAcceptorStatus(false);
	}
}

CMainPage::~CMainPage()
{
	CSysLog sl;
	int closeNV9Result = CloseNV9();

	if (closeNV9Result == 0) {
		sl.writeLog("纸币器关闭正常",__FILE__,__FUNCTION__,__LINE__);
	} 
	else {
		sl.writeLog("纸币器关闭异常",__FILE__,__FUNCTION__,__LINE__);
	}
}

void CMainPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_FILEPICK, m_cBtnFilePick);
	DDX_Control(pDX, IDC_BTN_PAY, m_cBtnPay);
	DDX_Control(pDX, IDC_BTN_SETTINGS, m_cBtnSettings);
	DDX_Control(pDX, IDC_CHILDDLGSWITCH, m_cPicChildDlgSwitch);
}


BEGIN_MESSAGE_MAP(CMainPage, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_FILEPICK, &CMainPage::OnBnClickedBtnFilepick)
	ON_BN_CLICKED(IDC_BTN_SETTINGS, &CMainPage::OnBnClickedBtnSettings)
	ON_BN_CLICKED(IDC_BTN_PAY, &CMainPage::OnBnClickedBtnPay)
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_CHILDSWITCH,OnChildDlgSwitchClicked)
//	ON_BN_DOUBLECLICKED(IDC_BTN_SETTINGS, &CMainPage::OnDoubleclickedBtnSettings)
//ON_REGISTERED_MESSAGE(WM_COMM_NOTECASHGET, &CMainPage::OnMoneyGetMessage)
ON_MESSAGE(WM_COMM_NOTECASHGET, &CMainPage::OnMoneyGetMessage)
END_MESSAGE_MAP()


// CMainPage message handlers


void CMainPage::OnBnClickedBtnFilepick()
{
	// TODO: Add your control notification handler code here
	::PostMessage(this->m_hWnd,WM_CHILDSWITCH, DLG_FILEPICK,0);
}


void CMainPage::OnBnClickedBtnSettings()
{
	// TODO: Add your control notification handler code here
	/*this->pDialog[DLG_PAY]->ShowWindow(SW_HIDE);
	this->pDialog[DLG_PREVIEW]->ShowWindow(SW_HIDE);
	this->pDialog[DLG_FILEPICK]->ShowWindow(SW_HIDE);
	this->pDialog[DLG_PRINTSETTING]->ShowWindow(SW_SHOW);
	*/
	::PostMessage(this->m_hWnd,WM_CHILDSWITCH,DLG_PRINTSETTING,0);
}


void CMainPage::OnBnClickedBtnPay()
{
	// TODO: Add your control notification handler code here
	/*this->pDialog[DLG_PRINTSETTING]->ShowWindow(SW_HIDE);
	this->pDialog[DLG_PREVIEW]->ShowWindow(SW_HIDE);
	this->pDialog[DLG_FILEPICK]->ShowWindow(SW_HIDE);
	this->pDialog[DLG_PAY]->ShowWindow(SW_SHOW);
	*/
	::PostMessage(this->m_hWnd, WM_CHILDSWITCH, DLG_PAY, 0);

}


BOOL CMainPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	this->m_cBtnFilePick.LoadStdImage(IDR_FILEPICK_MAINPAGE,_T("PNG"));
	this->m_cBtnSettings.LoadStdImage(IDR_SETTINGS_MAINPAGE,_T("PNG"));
	this->m_cBtnPay.LoadStdImage(IDR_PAY_MAINPAGE,_T("PNG"));


	GETSCREENRECT(rc,this->m_cPicChildDlgSwitch);

	this->FilePickDlg.Create(IDD_DLG_FILEPICK,this);
	this->PreviewDlg.Create(IDD_DLG_PREVIEW,this);
	this->PrintSettingsDlg.Create(IDD_DLG_SETTINGS,this);
	this->PayDlg.Create(IDD_DLG_PAY,this);

	this->FilePickDlg.MoveWindow(&rc);
	this->PreviewDlg.MoveWindow(&rc);
	this->PrintSettingsDlg.MoveWindow(&rc);
	this->PayDlg.MoveWindow(&rc);

	this->pDialog[0] = &this->FilePickDlg;
	this->pDialog[1] = &this->PreviewDlg;
	this->pDialog[2] = &this->PrintSettingsDlg;
	this->pDialog[3] = &this->PayDlg;

	this->m_CurSelDlg = DLG_FILEPICK;

	this->pDialog[DLG_FILEPICK]->ShowWindow(SW_SHOW);
	this->pDialog[DLG_PREVIEW]->ShowWindow(SW_HIDE);
	this->pDialog[DLG_PRINTSETTING]->ShowWindow(SW_HIDE);
	this->pDialog[DLG_PAY]->ShowWindow(SW_HIDE);


	HBITMAP		hBitmap			= NULL;
	HINSTANCE	hInstResource	= NULL;

	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BACKGROUND), RT_BITMAP);

	// Load bitmap In
	m_hBitmap = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(IDB_BACKGROUND), IMAGE_BITMAP, 0, 0, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CMainPage::OnEraseBkgnd(CDC* pDC)
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

void CMainPage::SetButtonBackGrounds(CDC *pDC)
{
	this->m_cBtnFilePick.SetBkGnd(pDC);
	this->m_cBtnSettings.SetBkGnd(pDC);
	this->m_cBtnPay.SetBkGnd(pDC);
}

/*
	当MainPage窗口有子窗口要切换，但是切换的控制在子窗口内部本身，发送一个消息给
	MainPage，然后MainPage接受这个消息，再处理切换相关的事务。
*/
LRESULT CMainPage::OnChildDlgSwitchClicked(WPARAM wParam, LPARAM lParam)
{
	CSysLog sl;
	PopupDialog pdlg;
	pdlg.SetTimeout(2);
	pdlg.SetButtonText("确  定");
	int file_total_pages = 0;
	switch(wParam) {
	case DLG_FILEPICK:
		this->pDialog[DLG_PAY]->ShowWindow(SW_HIDE);
		this->pDialog[DLG_PRINTSETTING]->ShowWindow(SW_HIDE);
		this->pDialog[DLG_PREVIEW]->ShowWindow(SW_HIDE);
		this->pDialog[DLG_FILEPICK]->ShowWindow(SW_SHOW);

		break;
	case DLG_PREVIEW:
		/////////////////////////////////暂时不支持预览/////////////////////////////////////////
		sl.writeLog("文件预览请求被点击");
		pdlg.SetMessage("即将支持的功能，请稍等!");
		pdlg.DoModal();
		return 0;
		/////////////////////////////////暂时不支持预览/////////////////////////////////////////
		this->pDialog[DLG_FILEPICK]->ShowWindow(SW_HIDE);
		//将要预览的文件传递给预览对话框
		//PreviewDlg.m_fileFullPathInPreview = FilePickDlg.m_cur_path +"\\"+ FilePickDlg.m_sFileNameSelected;
		PreviewDlg.m_fileFullPathInPreview = transaction.getFilenamePrinting();
		//PreviewDlg.m_fileFullPathInPreview = "H:\\新建文件夹\\WeiYongcheng UESTC.doc";
		this->pDialog[DLG_PREVIEW]->ShowWindow(SW_SHOW);
		this->pDialog[DLG_PRINTSETTING]->ShowWindow(SW_HIDE);
		this->pDialog[DLG_PAY]->ShowWindow(SW_HIDE);
		break;
	case DLG_PRINTSETTING:
		file_total_pages = GetPagesFromFileName(transaction.getFilenamePrinting());
		if ( file_total_pages > 0) {
			transaction.setFileTotalPages(file_total_pages);
		} 
		else if ( file_total_pages == 0) {
			pdlg.SetMessage("尚未选择文件，快去选择吧");
			if (pdlg.DoModal() == IDC_DLG_MYRETURN)
				::PostMessage(this->m_hWnd,WM_CHILDSWITCH,DLG_FILEPICK,0);
			else
				::PostMessage(this->m_hWnd,WM_CHILDSWITCH,DLG_FILEPICK,0);
		}
		else {
			pdlg.SetMessage("不能获得本Document对象，请重新选择!");
			if (pdlg.DoModal() == IDC_DLG_MYRETURN)
				OnOK();
		}
		this->pDialog[DLG_FILEPICK]->ShowWindow(SW_HIDE);
		this->pDialog[DLG_PREVIEW]->ShowWindow(SW_HIDE);
		this->pDialog[DLG_PAY]->ShowWindow(SW_HIDE);
		this->pDialog[DLG_PRINTSETTING]->ShowWindow(SW_SHOW);
		break;
	case DLG_PAY:
		if (transaction.getFilenamePrinting() == "") {
			pdlg.SetMessage("尚未选择文件，请重新选择文件。");
			//如果没有选择文件，则去选择文件呀
			if (pdlg.DoModal() == IDC_DLG_MYRETURN)
				::PostMessage(this->m_hWnd,WM_CHILDSWITCH,DLG_FILEPICK,0);
			else
				::PostMessage(this->m_hWnd,WM_CHILDSWITCH,DLG_FILEPICK,0);
			return 0;
		}
		//未对待打印的文件进行设置，则去设置呀
		
		if (transaction.getPrintingTotalPages() == 0 || transaction.getPrintingCopies() == 0)
		{
			if (!transaction.getFileSettingStr().IsEmpty())	{
				pdlg.SetMessage("设置页面范围错误，请重新设置");
			}
			else
				pdlg.SetMessage("还没进行设置打印参数，去设置吧");
			if (pdlg.DoModal() == IDC_DLG_MYRETURN)
				::PostMessage(this->m_hWnd, WM_CHILDSWITCH, DLG_PRINTSETTING,0);
			else
				::PostMessage(this->m_hWnd,WM_CHILDSWITCH, DLG_PRINTSETTING,0);
			return 0;
		}
		this->pDialog[DLG_FILEPICK]->ShowWindow(SW_HIDE);
		this->pDialog[DLG_PREVIEW]->ShowWindow(SW_HIDE);
		this->pDialog[DLG_PRINTSETTING]->ShowWindow(SW_HIDE);
		this->pDialog[DLG_PAY]->ShowWindow(SW_SHOW);
		break;
	default:
		//unknown fault
		;
	}
	return 0;
}


//将这个消息处理函数，升级成所有投币的消息handler,
//此消息函数，处理来自各种不同的支付方式获得支付时消息。
//Card Coid Cash weixin这些支付会发送消息到此
LRESULT CMainPage::OnMoneyGetMessage(WPARAM wParam, LPARAM lParam)
{
	CSysLog sl;
	int paymentM = (int)wParam;		//支付方式
	int moneyGet = (int)lParam;		//支付了多少，但是有可能是角币。。。注意。。。。
	//int paymentInAll = 0;			//在此不用统计支付方式的总和，在后面直接判断cashTotal,cardTotal,CoinTotal是不是为空
	switch (paymentM) {
	case PAYBYNOTE:
		transaction.setCashTotal(moneyGet);
		break;
	case PAYBYCARD:
		transaction.setCardTotal(moneyGet);
		break;
	case PAYBYCOIN:
		transaction.setCoinTotal(moneyGet);
		break;
	case PAYBYWEIXIN:
		transaction.setWeixinTotal(moneyGet);
		break;
	default:
		;
	}
	
	this->pDialog[DLG_PAY]->UpdateWindow();
	return 0;
}
