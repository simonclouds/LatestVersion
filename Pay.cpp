// Pay.cpp : implementation file
//

#include "stdafx.h"
#include "autoPrint2.h"
#include "Pay.h"
#include "afxdialogex.h"
#include "MemDC.h"
#include "PopupDialog.h"
#include "global.h"

// CPay dialog

extern CTransaction transaction;
extern CEnvironment environment;

extern "C"  int EnableNV9ToRecvMoney();
extern "C"  int DisableNV9ToRecvMoney();
extern "C"  int SendCommand(char *cmd,unsigned char length);
extern "C"  void  ReadResult(const char *cmd,unsigned char *rsl_lenth);

CPay::CPay(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPay::IDD, pParent)
{

}

CPay::~CPay()
{
}

void CPay::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_HOME4, m_cBtnGoHome);
	DDX_Control(pDX, IDC_BTN_PAYBYCARD, m_cBtnPayByCard);
	DDX_Control(pDX, IDC_BTN_PAYBYCOINCASH, m_cBtnPayByCoinCash);
	DDX_Control(pDX, IDC_BTN_PAYBYWEIXIN, m_cBtnPayByWeixin);
	DDX_Control(pDX, IDC_BTN_PRINTING, m_cBtnPrinting);
	DDX_Control(pDX, IDC_STATIC_BASEPRICE, m_cStaticBasePrice);
	DDX_Control(pDX, IDC_STATIC_CHANGE, m_cStaticChange);
	DDX_Control(pDX, IDC_STATIC_LAST, m_cStaticUnPaid);
	DDX_Control(pDX, IDC_STATIC_PAID, m_cStaticPaid);
	DDX_Control(pDX, IDC_STATIC_PRINTINGCOPIES, m_cStaticPrintingCopies);
	DDX_Control(pDX, IDC_STATIC_PRINTINGFILENAME, m_cStaticPrintingFileName);
	DDX_Control(pDX, IDC_STATIC_PRITINGPAGES, m_cStaticPrintingPages);
	DDX_Control(pDX, IDC_STATIC_TOTALSHOULDPAY, m_cStaticTotalShouldPay);
}


BEGIN_MESSAGE_MAP(CPay, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_HOME4, &CPay::OnBnClickedBtnHome4)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_PAYBYWEIXIN, &CPay::OnBnClickedBtnPaybyweixin)
	ON_BN_CLICKED(IDC_BTN_PAYBYCARD, &CPay::OnBnClickedBtnPaybycard)
	ON_BN_CLICKED(IDC_BTN_PAYBYCOINCASH, &CPay::OnBnClickedBtnPaybycoincash)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPay message handlers


BOOL CPay::OnEraseBkgnd(CDC* pDC)
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

void CPay::SetButtonBackGrounds(CDC *pDC)
{
	this->m_cBtnGoHome.SetBkGnd(pDC);
	this->m_cBtnPrinting.SetBkGnd(pDC);
	this->m_cBtnPayByCard.SetBkGnd(pDC);
	this->m_cBtnPayByCoinCash.SetBkGnd(pDC);
	this->m_cBtnPayByWeixin.SetBkGnd(pDC);
}


BOOL CPay::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	this->m_cBtnGoHome.LoadStdImage(IDR_BTN_HOME,_T("PNG"));
	this->m_cBtnPayByCoinCash.LoadStdImage(IDR_BTN_PAYBYCOINCASH,_T("PNG"));
	this->m_cBtnPayByCard.LoadStdImage(IDR_BTN_PAYBYCARD,_T("PNG"));
	this->m_cBtnPayByWeixin.LoadStdImage(IDR_BTN_PAYBYWEIXIN,_T("PNG"));
	this->m_cBtnPrinting.LoadStdImage(IDR_BTN_PRINTINGFLAG,_T("PNG"));

	HBITMAP		hBitmap			= NULL;
	HINSTANCE	hInstResource	= NULL;

	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_CHILDBKGND), RT_BITMAP);

	// Load bitmap In
	m_hBitmap = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(IDB_CHILDBKGND), IMAGE_BITMAP, 0, 0, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPay::OnBnClickedBtnHome4()
{
	// TODO: Add your control notification handler code here
	PopupDialog pdlg;
	pdlg.SetMessage("确定要放弃当前打印吗？");
	pdlg.SetTimeout(3);
	pdlg.SetButtonText("确  定");
	if (pdlg.DoModal() == IDC_DLG_MYRETURN)
	{
		//m_total_paid 是浮点数，如果和0比，可能其实0.0000001也会大于0，
		//投钱最低单位为1角0.1元，又可能是0.09999这样的，于是选择和0.01比较
		if (transaction.getTotalPaid() > 0.01 )
		{
			//走找零路径
		}
		transaction.cleanAll();
		::PostMessage(GetParent()->GetSafeHwnd(),WM_CLOSE,0,0);
	} 
	else
	{
		; //留在本页，什么也不做
	}
	
}


void CPay::OnPaint()
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
	//设置 基础单价
	float baseprice = transaction.getBasePrice();
	CString tmpStr = _T("");
	tmpStr.Format("%0.1f",baseprice);
	m_cStaticBasePrice.SetWindowText(tmpStr);

	//设置应找零
	float change = transaction.getChange();
	tmpStr.Empty();
	tmpStr.Format("%0.1f",change);
	m_cStaticChange.SetWindowText(tmpStr);

	//设置总共已经支付的总额
	float paid = transaction.getTotalPaid();
	tmpStr.Empty();
	tmpStr.Format("%0.1f",paid);
	m_cStaticPaid.SetWindowText(tmpStr);

	//设置打印份数
	int copies = transaction.getPrintingCopies();
	tmpStr.Empty();
	tmpStr.Format("%d",copies);
	m_cStaticPrintingCopies.SetWindowText(tmpStr);

	//设置显示打印的文件名
	m_cStaticPrintingFileName.SetWindowText(transaction.getFilenamePrinting());

	//设置打印的总页数
	int pagesPerFile = transaction.getPrintingTotalPages();
	int totalInAll = pagesPerFile * copies;
	tmpStr.Empty();
	tmpStr.Format("%d",totalInAll);
	m_cStaticPrintingPages.SetWindowText(tmpStr);

	//设置应支付总额
	transaction.setTotalShouldPay();
	float shouldPay = transaction.getTotalShouldPay();
	tmpStr.Empty();
	tmpStr.Format("%0.1f",shouldPay);
	m_cStaticTotalShouldPay.SetWindowText(tmpStr);

	//设置仍需支付金额

	float unpaid = shouldPay - paid;
	tmpStr.Empty();
	tmpStr.Format("%0.1f",unpaid);
	m_cStaticUnPaid.SetWindowText(tmpStr);

	if ( totalInAll > 100)
	{
		PopupDialog pdlg;
		pdlg.SetMessage("您的打印已超过100页，超过部分九折优惠");
		pdlg.SetTimeout(2);
		pdlg.SetButtonText("我知道了");
		pdlg.DoModal();
	}
}
void CPay::SetOnePicBackGnd(LPCTSTR filepath, UINT ID)
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

void CPay::SetPicCtlBackGrounds()
{
	LPCTSTR arrPath[] = {	_T("res\\PayTitle.png"),
							_T("res\\PayInfoShowUp.png"),
							_T("res\\PayInfoShowDown.png"),
							_T("res\\PayTips.png")
					};
	UINT arrID[] = {	IDC_PAYTITLE,
						IDC_PAYINFOSHOWUP,
						IDC_PAYINFOSHOWDOWN,
						IDC_PAYTIPS
					};
	for(int i = 0; i < 4; i ++)
		SetOnePicBackGnd(arrPath[i],arrID[i]);
}

void CPay::OnBnClickedBtnPaybyweixin()
{
	// TODO: Add your control notification handler code here
	PopupDialog popdlg;
	popdlg.SetTimeout(1);
	popdlg.SetMessage("微信支付功能暂不支持，新版发布中...");
	popdlg.SetButtonText("返 回");
	popdlg.DoModal();
}


void CPay::OnBnClickedBtnPaybycard()
{
	// TODO: Add your control notification handler code here
	PopupDialog popdlg;
	CSysLog sl;
	popdlg.SetTimeout(0.5);
	popdlg.SetMessage("切换至卡支付，请刷卡:-)");
	popdlg.SetButtonText("确   定");
	popdlg.DoModal();

	//点击了其他支付方式，则关闭纸币扫描线程，测试。。。。
	int isNoteDisabled = DisableNV9ToRecvMoney();
	if (isNoteDisabled == 0)
	{
		environment.SetNoteAcceptorEnable(false);
		sl.writeLog("设置纸币器disable成功",__FILE__,__FUNCTION__,__LINE__);
		//CloseHandle(hThreadForScanNoteAcceptor);
	} 
	else
	{
		//会不会设置disable不成功，那怎么办？用户已经选择了其他支付方式，
		sl.writeLog("设置纸币器disable失败",__FILE__,__FUNCTION__,__LINE__);
		//就不能再提供纸币的服务啦！
	}
	
}


void CPay::OnBnClickedBtnPaybycoincash()
{
	// TODO: Add your control notification handler code here
	PopupDialog popdlg;
	CSysLog sl;
	popdlg.SetTimeout(1);
	popdlg.SetMessage("至现金支付，请投纸币或硬币:-)");
	bool noteAcceptorStatus = environment.GetNoteAcceptorStatus();
	bool noteAcceptorEnabled = environment.IsNoteAcceptorEnabled();
	//纸币投币器被初始化了但是未被使能
	if (noteAcceptorStatus && !noteAcceptorEnabled)	{
		int isNoteEnabled = EnableNV9ToRecvMoney();
		if (isNoteEnabled == 0)	{
			//使能纸币器成功，这是environment，创建线程，扫描纸币器是否投入纸币
			environment.SetNoteAcceptorEnable(true);
			sl.writeLog("设置纸币器enable成功",__FILE__,__FUNCTION__,__LINE__);
			//hThreadForScanNoteAcceptor = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ScanNoteAcceptorThreadFunc,(PVOID)NULL,0,NULL);
		} 
		else {
			//使能纸币器失败
			environment.SetNoteAcceptorEnable(false);
			sl.writeLog("设置纸币器enable失败",__FILE__,__FUNCTION__,__LINE__);
		}
	} 
	else {//纸币接收器被初始化了，且使能成功
		popdlg.SetMessage("切换至现金支付，请投入硬币:-)\n纸币暂停使用！");
	}
	
	popdlg.SetButtonText("确   定");
	popdlg.DoModal();
}

//设置窗口CStatic 控件背景透明
HBRUSH CPay::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	if (nCtlColor == CTLCOLOR_DLG)
	{
		hbr = (HBRUSH)::CreateSolidBrush(RGB(146,161,202));
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		//pDC->SetTextColor(RGB(100,255,100));
		return HBRUSH(GetStockObject((HOLLOW_BRUSH)));
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

/*void ScanNoteAcceptorThreadFunc()
{
	char recvbuf[32] ="";
	unsigned char len=0;
	while(1) {	
		memset(recvbuf,0,sizeof(recvbuf));
		ReadResult(recvbuf,&len);
		if(recvbuf[0] != 0)	{
			for(int i=0;i<5;i++) {
				if((unsigned char)recvbuf[i] == 0xee) {
					//支付方式通过wParam传递，投了多少钱通过lParam传递
					//::PostMessage(this->GetParent()->m_hWnd,WM_COMM_NOTECASHGET,PAYBYNOTE,(LPARAM)recvbuf[i+1]);
					break;
				}
			}
		}
		Sleep(200);
	}
}
*/