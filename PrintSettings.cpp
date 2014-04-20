// PrintSettings.cpp : implementation file
//

#include "stdafx.h"
#include "autoPrint2.h"
#include "PrintSettings.h"
#include "afxdialogex.h"
#include "global.h"
#include "MemDC.h"

// CPrintSettings dialog
extern CTransaction transaction;

IMPLEMENT_DYNAMIC(CPrintSettings, CDialogEx)

CPrintSettings::CPrintSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPrintSettings::IDD, pParent)
{
	m_PagesUserSelected = _T("");
	//  m_CopiesUserSelected = _T("");
	m_copies = 1;
}

CPrintSettings::~CPrintSettings()
{
}

void CPrintSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_ADD, m_cBtnAdd);
	DDX_Control(pDX, IDC_BTN_HOME3, m_cBtnHome3);
	DDX_Control(pDX, IDC_BTN_PAY3, m_cBtnPay3);
	DDX_Control(pDX, IDC_BTN_SUB, m_cBtnSub);
	DDX_Control(pDX, IDC_BTN0, m_cBtnKey0);
	DDX_Control(pDX, IDC_BTN1, m_cBtnKey1);
	DDX_Control(pDX, IDC_BTN2, m_cBtnKey2);
	DDX_Control(pDX, IDC_BTN3, m_cBtnKey3);
	DDX_Control(pDX, IDC_BTN4, m_cBtnKey4);
	DDX_Control(pDX, IDC_BTN5, m_cBtnKey5);
	DDX_Control(pDX, IDC_BTN6, m_cBtnKey6);
	DDX_Control(pDX, IDC_BTN7, m_cBtnKey7);
	DDX_Control(pDX, IDC_BTN8, m_cBtnKey8);
	DDX_Control(pDX, IDC_BTN9, m_cBtnKey9);
	DDX_Control(pDX, IDC_BTNCOMMA, m_cBtnComma);
	DDX_Control(pDX, IDC_BTNDASH, m_cBtnDash);
	DDX_Control(pDX, IDC_BTNDELETE, m_cBtnDelete);
	DDX_Control(pDX, IDC_BTNOKEY, m_cBtnOkey);

	DDX_Text(pDX, IDC_STATIC_SELPGSBYUSER, m_PagesUserSelected);
	DDV_MaxChars(pDX, m_PagesUserSelected, 30);
	DDX_Control(pDX, IDC_STATIC_COPIES, m_CopiesUserSelect);
	DDX_Control(pDX, IDC_STATIC_COPYS2, m_CopiesTotal);
	DDX_Control(pDX, IDC_STATIC_ALLPAGES, m_cShowPagesSelect);
	
}


BEGIN_MESSAGE_MAP(CPrintSettings, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_HOME3, &CPrintSettings::OnBnClickedBtnHome3)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_PAY3, &CPrintSettings::OnBnClickedBtnPay3)
	ON_BN_CLICKED(IDC_BTN1, &CPrintSettings::OnBnClickedBtn1)
	ON_BN_CLICKED(IDC_BTN2, &CPrintSettings::OnBnClickedBtn2)
	ON_BN_CLICKED(IDC_BTN3, &CPrintSettings::OnBnClickedBtn3)
	ON_BN_CLICKED(IDC_BTN4, &CPrintSettings::OnBnClickedBtn4)
	ON_BN_CLICKED(IDC_BTN5, &CPrintSettings::OnBnClickedBtn5)
	ON_BN_CLICKED(IDC_BTN6, &CPrintSettings::OnBnClickedBtn6)
	ON_BN_CLICKED(IDC_BTN7, &CPrintSettings::OnBnClickedBtn7)
	ON_BN_CLICKED(IDC_BTN8, &CPrintSettings::OnBnClickedBtn8)
	ON_BN_CLICKED(IDC_BTN9, &CPrintSettings::OnBnClickedBtn9)
	ON_BN_CLICKED(IDC_BTNCOMMA, &CPrintSettings::OnBnClickedBtncomma)
	ON_BN_CLICKED(IDC_BTN0, &CPrintSettings::OnBnClickedBtn0)
	ON_BN_CLICKED(IDC_BTNDASH, &CPrintSettings::OnBnClickedBtndash)
	ON_BN_CLICKED(IDC_BTNDELETE, &CPrintSettings::OnBnClickedBtndelete)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_SUB, &CPrintSettings::OnBnClickedBtnSub)
	ON_BN_CLICKED(IDC_BTN_ADD, &CPrintSettings::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_RADIO_ALLPAGES, &CPrintSettings::OnBnClickedRadioAllpages)
	ON_BN_CLICKED(IDC_BTNOKEY, &CPrintSettings::OnBnClickedBtnokey)
	ON_BN_CLICKED(IDC_RADIO_USERPAGES, &CPrintSettings::OnBnClickedRadioUserpages)
END_MESSAGE_MAP()


// CPrintSettings message handlers


BOOL CPrintSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	this->m_cBtnKey0.LoadStdImage(IDR_KEY0,_T("PNG"));
	this->m_cBtnKey1.LoadStdImage(IDR_KEY1,_T("PNG"));
	this->m_cBtnKey2.LoadStdImage(IDR_KEY2,_T("PNG"));
	this->m_cBtnKey3.LoadStdImage(IDR_KEY3,_T("PNG"));
	this->m_cBtnKey4.LoadStdImage(IDR_KEY4,_T("PNG"));
	this->m_cBtnKey5.LoadStdImage(IDR_KEY5,_T("PNG"));
	this->m_cBtnKey6.LoadStdImage(IDR_KEY6,_T("PNG"));
	this->m_cBtnKey7.LoadStdImage(IDR_KEY7,_T("PNG"));
	this->m_cBtnKey8.LoadStdImage(IDR_KEY8,_T("PNG"));
	this->m_cBtnKey9.LoadStdImage(IDR_KEY9,_T("PNG"));
	this->m_cBtnComma.LoadStdImage(IDR_KEYCOMMA,_T("PNG"));
	this->m_cBtnDash.LoadStdImage(IDR_KEYDASH,_T("PNG"));
	this->m_cBtnDelete.LoadStdImage(IDR_KEYDELETE,_T("PNG"));
	this->m_cBtnOkey.LoadStdImage(IDR_KEYOKEY,_T("PNG"));
	this->m_cBtnSub.LoadStdImage(IDR_KEYSUB,_T("PNG"));
	this->m_cBtnAdd.LoadStdImage(IDR_KEYADD,_T("PNG"));

	this->m_cBtnHome3.LoadStdImage(IDR_BTN_HOME,_T("PNG"));
	this->m_cBtnPay3.LoadStdImage(IDR_BTN_PAY,_T("PNG"));

	((CButton *)GetDlgItem(IDC_RADIO_ALLPAGES))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_RADIO_USERPAGES))->SetCheck(FALSE);
	m_CopiesTotal.SetWindowText(_T("1"));
	m_CopiesUserSelect.SetWindowText(_T("1"));
	//默认当前打印交易的文档打印1份
	transaction.setPrintingCopies(1);

	HBITMAP		hBitmap			= NULL;
	HINSTANCE	hInstResource	= NULL;

	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_CHILDBKGND), RT_BITMAP);

	// Load bitmap In
	m_hBitmap = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(IDB_CHILDBKGND), IMAGE_BITMAP, 0, 0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CPrintSettings::OnEraseBkgnd(CDC* pDC)
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

void CPrintSettings::SetButtonBackGrounds(CDC *pDC)
{
	this->m_cBtnKey0.SetBkGnd(pDC);
	this->m_cBtnKey1.SetBkGnd(pDC);
	this->m_cBtnKey2.SetBkGnd(pDC);
	this->m_cBtnKey3.SetBkGnd(pDC);
	this->m_cBtnKey4.SetBkGnd(pDC);
	this->m_cBtnKey5.SetBkGnd(pDC);
	this->m_cBtnKey6.SetBkGnd(pDC);
	this->m_cBtnKey7.SetBkGnd(pDC);
	this->m_cBtnKey8.SetBkGnd(pDC);
	this->m_cBtnKey9.SetBkGnd(pDC);
	this->m_cBtnComma.SetBkGnd(pDC);
	this->m_cBtnDash.SetBkGnd(pDC);
	this->m_cBtnDelete.SetBkGnd(pDC);
	this->m_cBtnOkey.SetBkGnd(pDC);
	this->m_cBtnSub.SetBkGnd(pDC);
	this->m_cBtnAdd.SetBkGnd(pDC);
	this->m_cBtnHome3.SetBkGnd(pDC);
	this->m_cBtnPay3.SetBkGnd(pDC);
	
}

void CPrintSettings::OnBnClickedBtnHome3()
{
	// TODO: Add your control notification handler code here
	
	PopupDialog pdlg;
	pdlg.SetMessage("确定放弃当前设置吗？");
	pdlg.SetButtonText("确  定");
	pdlg.SetTimeout(2);
	if (pdlg.DoModal() == IDC_DLG_MYRETURN)
	{
		//transaction 应设置清理函数
		transaction.setFileNamePrinting("");
		transaction.setFileTotalPages(0);
		transaction.setPrintingCopies(0);
		transaction.setPrintingTotalPages(0);
		//transaction.set
		::PostMessage(GetParent()->GetSafeHwnd(),WM_CLOSE,0,0);
	}
	else		//超时
		return ;//do nothing
}


void CPrintSettings::OnPaint()
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
	//页数统计初始化
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();

	if (i_check == 1)
	{
		CString fileTotalPageStr = _T("");
		int filetotalpages = transaction.getFileTotalPages();
		fileTotalPageStr.Format("%d",filetotalpages);
		m_cShowPagesSelect.SetWindowText(fileTotalPageStr);
		//默认打印整个文档
		transaction.setPrintingTotalPages(filetotalpages);
	}
}


void CPrintSettings::SetPicCtlBackGrounds()
{
		LPCTSTR arrPath[] = {	_T("res\\SettingsTitle.png"),
								_T("res\\PrintRange.png"),
								_T("res\\SelectAllPage.png"),
								_T("res\\SelectUserDefine.png"),
								_T("res\\TotalPage1.png"),
								_T("res\\TotalPage2.png"),
								_T("res\\PrintCopySet.png"),
								_T("res\\TotalCopy1.png"),
								_T("res\\TotalCopy2.png"),
								_T("res\\Tips1.png"),
								_T("res\\Tips2.png")
						};
		UINT arrID[] = {	IDC_SETTINGSTITLE,
							IDC_PIRNTRANGE,
							IDC_SELECTALLPAGE,
							IDC_SELECTUSERDEFINE,
							IDC_TOTALPAGE1,
							IDC_TOTALPAGE2,
							IDC_SETPRINTCOPY,
							IDC_TOTALCOPY1,
							IDC_TOTALCOPY2,
							IDC_PICTIPS1,
							IDC_PICTIPS2
						};
	for(int i = 0; i < 11; i ++)
		SetOnePicBackGnd(arrPath[i],arrID[i]);

}
void CPrintSettings::SetOnePicBackGnd(LPCTSTR filepath, UINT ID)
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

//设置完成后去支付打印
void CPrintSettings::OnBnClickedBtnPay3()
{
	// TODO: Add your control notification handler code here
	
	::PostMessage(GetParent()->GetSafeHwnd(),WM_CHILDSWITCH,DLG_PAY,0);
}

static inline void AppendCharToCString(CString *str, char c)
{
	int len = str->GetLength();
	str->Insert(len,(TCHAR)c);
}
static inline void DeleteLastOfCString(CString *str)
{
	if (str->GetLength() > 0)
		str->Delete(str->GetLength()-1,1);
}



void CPrintSettings::OnBnClickedBtn1()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//如果全部打印被选中,则不响应按键
		return ;
	AppendCharToCString(&m_PagesUserSelected,'1');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn2()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//如果全部打印被选中,则不响应按键
		return ;
	AppendCharToCString(&m_PagesUserSelected,'2');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn3()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//如果全部打印被选中,则不响应按键
		return ;
	AppendCharToCString(&m_PagesUserSelected,'3');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn4()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//如果全部打印被选中,则不响应按键
		return ;
	AppendCharToCString(&m_PagesUserSelected,'4');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn5()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//如果全部打印被选中,则不响应按键
		return ;
	AppendCharToCString(&m_PagesUserSelected,'5');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn6()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//如果全部打印被选中,则不响应按键
		return ;
	AppendCharToCString(&m_PagesUserSelected,'6');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn7()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//如果全部打印被选中,则不响应按键
		return ;
	AppendCharToCString(&m_PagesUserSelected,'7');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn8()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//如果全部打印被选中,则不响应按键
		return ;
	AppendCharToCString(&m_PagesUserSelected,'8');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn9()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//如果全部打印被选中,则不响应按键
		return ;
	AppendCharToCString(&m_PagesUserSelected,'9');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtncomma()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//如果全部打印被选中,则不响应按键
		return ;
	AppendCharToCString(&m_PagesUserSelected,',');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn0()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//如果全部打印被选中,则不响应按键
		return ;
	AppendCharToCString(&m_PagesUserSelected,'0');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtndash()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//如果全部打印被选中,则不响应按键
		return ;
	AppendCharToCString(&m_PagesUserSelected,'-');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtndelete()
{
	// TODO: Add your control notification handler code here
	DeleteLastOfCString(&m_PagesUserSelected);
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtnokey()
{
	// TODO: Add your control notification handler code here
	int pagesUserSelect = GetPagesFromString(m_PagesUserSelected);
	PopupDialog pdg;
	if (pagesUserSelect < 0)
	{
		switch (pagesUserSelect)
		{
		case SETTINGERROR_BIGLITTLE:
			pdg.SetMessage("指定页面范围应从小到大！");
			break;
		case SETTINGERROR_INVALIDCHAR:
			pdg.SetMessage("指定范围包含非法字符！");
			break;
		case SETTINGERROR_OUTOFRANGE:
			pdg.SetMessage("指定页面超出文档自身范围！");
			break;
		case SETTINGERROR_WRONGFORMAT:
			pdg.SetMessage("指定的格式不正确！");
			break;
		default:
			;//do nothing
		}
		pdg.SetButtonText("确  定");
		pdg.SetTimeout(0.5);
		pdg.DoModal();
		return ;
	}
	CString pagesUserSelectStr = _T("");
	pagesUserSelectStr.Format("%d",pagesUserSelect);
	m_cShowPagesSelect.SetWindowText(pagesUserSelectStr);
	//点击了ok按钮，则将计算出的要打印的总页数记录下来
	transaction.setPrintingTotalPages(pagesUserSelect);
}

//设置CStatic控件字体和背景透明
HBRUSH CPrintSettings::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	//if (nCtlColor == CTLCOLOR_STATIC)
	//{
	//	pDC->SetBkMode(TRANSPARENT);
	//	pDC->SetTextColor(RGB(255,0,0));
	//	return HBRUSH(GetStockObject((HOLLOW_BRUSH)));
	//}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CPrintSettings::FreshUserCStatic()
{
	CWnd *pStaticPageRange = (CStatic * )GetDlgItem(IDC_STATIC_SELPGSBYUSER);
	
	if (pStaticPageRange != NULL)
	{
		pStaticPageRange->SetWindowTextA(m_PagesUserSelected);
	}
}


void CPrintSettings::OnBnClickedBtnSub()
{
	// TODO: Add your control notification handler code here
	if (m_copies > 1)
		m_copies--;

	CString copyStr = _T("");
	copyStr.Format("%d",m_copies);
	m_CopiesUserSelect.SetWindowText(copyStr);
	m_CopiesTotal.SetWindowText(copyStr);
	transaction.setPrintingCopies(m_copies);
}


void CPrintSettings::OnBnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	m_copies ++;

	CString copyStr = _T("");
	copyStr.Format("%d",m_copies);
	m_CopiesUserSelect.SetWindowText(copyStr);
	m_CopiesTotal.SetWindowText(copyStr);
	transaction.setPrintingCopies(m_copies);
}

//当全部打印radio被选中
void CPrintSettings::OnBnClickedRadioAllpages()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//如果全部打印被选中,则清空自选页范围
	{
		m_PagesUserSelected = _T("");
		FreshUserCStatic();
	}
	//页数统计初始化
	CString fileTotalPageStr = _T("");
	int totalfilepages = transaction.getFileTotalPages();
	fileTotalPageStr.Format("%d",totalfilepages);
	m_cShowPagesSelect.SetWindowText(fileTotalPageStr);
	//打印整个文档，那么printingtotalpages == filetotalpages
	transaction.setFileSettingStr("");	//自定义打印页面范围的字符串设置为空
	transaction.setPrintingTotalPages(totalfilepages);
}

//当自选radio被选中
void CPrintSettings::OnBnClickedRadioUserpages()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_USERPAGES))->GetCheck();
	//当用户选中自定义页范围的时候，并且此时尚未输入任何范围
	if (i_check == 1 && m_PagesUserSelected.GetLength()== 0)
	{
		CString tmp = _T("0");
		m_cShowPagesSelect.SetWindowText(tmp);
		//当第一次点击了这个自设范围的radio，那么设置printingtotalpage = 0
		transaction.setPrintingTotalPages(0);
	}
}

//函数功能: 从单个字段中检测其包含的待打印页数
//			从"2","3-12"这样的字符串中提取出其中包含的页数，分别为1,10页
//			此处还应该检测是否包含"3-5-8"这样的错误输入
//输入参数:	CString str 待检测的字符串
//返回值:	正常则这个字段中包含的页数，有异常负整数
int CPrintSettings::GetCountFromStr( CString str )
{
	int pages = 0;
	if (str == "") 
		return pages;
	//类似"12"这样的不包含"-"的情况，直接记页数加1
	if (str.Find("-") == -1) {
		int thispage = CString2Int(str);
		if (!InputPageRangeValid(thispage,transaction.getFileTotalPages())) {
			return SETTINGERROR_OUTOFRANGE;
		}
		pages += 1;
	}
	//类似"3-10"这样的情况
	else {
		int firstDash = str.Find("-");
		//把第一个'-'字符后面的字符串提取出来，查看是否还包含"-"("3-5-8")。如果包含，则是非法输入串
		CString tailString = str.Right(str.GetLength() - firstDash - 1);
		//尾部字符串不包含'-'了，则计算这个str包含的页数
		if (tailString.Find("-") == -1) {
			//提取firstDash左边的子串，从1开始计数
			CString firstNumStr = str.Left(firstDash);
			int firstNum = CString2Int(firstNumStr);
			if (firstNum <= 0) {
				return SETTINGERROR_OUTOFRANGE;
			}
			//提取firstDash 右边的子串，并判断是否超出文档的最大页数
			CString secondNumStr = tailString;
			int secondNum = CString2Int(secondNumStr);
			int fileTotalPage = transaction.getFileTotalPages();
			if (!InputPageRangeValid(secondNum, fileTotalPage)) {
				return SETTINGERROR_OUTOFRANGE;
			}
			//'-'左边的数字必须小于等于右边数字
			if (firstNum <= secondNum) {
				pages = secondNum - firstNum + 1;
			}
			else {
				return SETTINGERROR_BIGLITTLE;		//像 "5-3"这样的输入串，判错
			}
		}
		else {
			return SETTINGERROR_WRONGFORMAT;			//像 "3-5-8"这样的输入串，判错
		}
	}
	return pages;
}

//函数功能：检测字符串中是否包含"--"|"-,"|",-"|",,"这样的影响计算页数的非法字符组合
//输入参数：CString str 待检测的字符串
//返回值：	BOOL 包含则返回TRUE，不包含返回FALSE   
//Note:		***注意返回值的意义***
BOOL CPrintSettings::IncludeInvaidCharGroup( CString str )
{
	if (str == "") 
		return TRUE;
	if (str.Find("--") != -1) 
		return TRUE;
	else if (str.Find("-,") != -1) 
		return TRUE;
	else if (str.Find(",,") != -1) 
		return TRUE;
	else if (str.Find(",-") != -1) 
		return TRUE;
	else if (!isDigit(str.GetAt(0)) ) 
		return TRUE;
	else if (!isDigit(str.GetAt(str.GetLength() - 1)))
		return TRUE;
	else 
		return FALSE;
}

//函数功能：从字符串中提取页数
//输入参数：CString str：包含页数的字符串，如"2-5,7,10"
//返回值：	int ，页数
int CPrintSettings::GetPagesFromString( CString str )
{
	int pages = 0;
	int strLen = str.GetLength();
	int indexOfStr = 0;
	//是否含有非法字符,即除(0-9)|(-)|(,)这三种字符以外的字符
	while (indexOfStr != strLen) {
		char c = str.GetAt(indexOfStr);		//first from zero ?
		BOOL validChar = (isDigit(c) || isAllowedChar(c));	//该字符是数字或者'-'.','
		if (validChar) {
			indexOfStr ++;
		}
		else {
			return SETTINGERROR_INVALIDCHAR;
		}	
	}
	/*
	* 全都是合法字符的情况下
	* 是否含有非法字符组合"--","-,",",-",",,",在此函数内部同时排除了首字母和尾字母不是数字的情况
	*/
	BOOL validStr = IncludeInvaidCharGroup(str);
	if (validStr) {
		return SETTINGERROR_WRONGFORMAT;
	}
	CString workStr = str;
	//从字符串中计算页数开始
	/*
	*  从原字符串中不断分离一个个的段（用逗号分隔），然后循环每次处理一个段
	*  每个段中包含的页数，相加就是总的要打印的页数
	*/
	while (TRUE) {
		int subpages = 0;
		if (workStr.Find(",") == -1) {			//workStr 直接是 "23"这样的单页输入串，或者"2-3"这样的
			subpages = GetCountFromStr(workStr);
			if (subpages > 0) {
				pages += subpages;
			}
			else {
				return subpages;		//如果出错，那么错误码在subpages变量中
			}
			break;								//同时是while的出口
		}
		//workStr包含多个','的情况，则分割处理。每次分割头部的一个子串出来
		else {
			int indexOfComma = workStr.Find(",");
			CString headStr = workStr.Left(indexOfComma);
			subpages = GetCountFromStr(headStr);
			if (subpages > 0) {
				pages += subpages;
			}
			else {
				return subpages;
			}
			//将此逗号后面的部分继续处理
			int workStrLen = workStr.GetLength();
			workStr = workStr.Right(workStrLen - indexOfComma - 1);
		}
	}
	return pages;
}
//函数功能：将一个只有数字(多位数)的字符串转换成整数
int CPrintSettings::CString2Int( const CString str )
{
	int num = 0;
	if (str != "") 
		num = ::atoi(str);			//此处不大确定计算结果
	return num;
}

//函数功能：查看输入字符串中的单个页数，是否超过文档最大页数
//BOOL CPrintSettings::isOutOfPageRange( int inputPage, int fileTotalPage )
//{
//	if (inputPage > fileTotalPage) 
//		return TRUE;
//	return FALSE;	
//}
//函数功能：看是不是允许输入的字符'-'和','
BOOL CPrintSettings::isAllowedChar( char c )
{
	if (c == '-' || c == ',') 
		return TRUE;
	else
		return FALSE;
}

BOOL CPrintSettings::isDigit( char c )
{
	if ('0' <= c && c <= '9') 
		return TRUE;
	else 
		return FALSE;
}
//函数功能：判断输入的页面数，是否超过文档自身的最大页码
//返回值：	正确的范围应该是 [0,max]
BOOL CPrintSettings::InputPageRangeValid( int inputPage, int fileTotalPage )
{
	if (inputPage <= 0) 
		return FALSE;
	else if (inputPage > fileTotalPage) 
		return FALSE;
	else
		return TRUE;
}

//每一次按键点击都去检测当前的页数总和，如果设置范围非法也更新给transaction,同时打印页数设置为0
void CPrintSettings::CheckPagesFromPageRangAnyway()
{
	int pagesUserSelect = GetPagesFromString(m_PagesUserSelected);
	CString pagesUserSelectStr = _T("");
	transaction.setFileSettingStr(m_PagesUserSelected);
	//如果设置非法则设为0
	if (pagesUserSelect < 0) {
		pagesUserSelectStr.Format("%d",0);
		m_cShowPagesSelect.SetWindowText(pagesUserSelectStr);
		transaction.setPrintingTotalPages(0);
	}
	else {
		pagesUserSelectStr.Format("%d",pagesUserSelect);
		m_cShowPagesSelect.SetWindowText(pagesUserSelectStr);
		//点击了ok按钮，则将计算出的要打印的总页数记录下来
		transaction.setPrintingTotalPages(pagesUserSelect);
	}
}






