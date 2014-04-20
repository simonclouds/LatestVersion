// FilePick.cpp : implementation file
//

#include "stdafx.h"
#include "autoPrint2.h"
#include "FilePick.h"
#include "afxdialogex.h"
#include "global.h"

#include "MemDC.h"				//button贴图使用到

extern CTransaction transaction;

// CFilePick dialog

IMPLEMENT_DYNAMIC(CFilePick, CDialogEx)

CFilePick::CFilePick(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFilePick::IDD, pParent)
{
	m_fileExtention = ".doc|.docx|.pdf";
	m_cur_path = "";
	m_selected_index = 0;
}

CFilePick::~CFilePick()
{
}

void CFilePick::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_PAY1, m_cBtnPay1);
	DDX_Control(pDX, IDC_BTN_PREVIEW1, m_cBtnPreview1);
	DDX_Control(pDX, IDC_BTN_SETTINGS1, m_cBtnSettings1);
	DDX_Control(pDX, IDC_BTN_HOME, m_cBtnGoHome1);
	DDX_Control(pDX, IDC_LIST_FILEPICK, m_cListFilePick);
}


BEGIN_MESSAGE_MAP(CFilePick, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_HOME, &CFilePick::OnBnClickedBtnHome)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_PREVIEW1, &CFilePick::OnBnClickedBtnPreview1)
	ON_BN_CLICKED(IDC_BTN_SETTINGS1, &CFilePick::OnBnClickedBtnSettings1)
	ON_BN_CLICKED(IDC_BTN_PAY1, &CFilePick::OnBnClickedBtnPay1)
	ON_NOTIFY(NM_CLICK, IDC_LIST_FILEPICK, &CFilePick::OnClickListFilepick)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FILEPICK, &CFilePick::OnDblclkListFilepick)
END_MESSAGE_MAP()


// CFilePick message handlers


BOOL CFilePick::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//加载按钮背景
	this->m_cBtnGoHome1.LoadStdImage(IDR_BTN_HOME,_T("PNG"));
	this->m_cBtnPay1.LoadStdImage(IDR_BTN_PAY,_T("PNG"));
	this->m_cBtnPreview1.LoadStdImage(IDR_BTN_PREVIEW,_T("PNG"));
	this->m_cBtnSettings1.LoadStdImage(IDR_BTN_SETTINGS,_T("PNG"));

	//加载本窗口背景
	HBITMAP		hBitmap			= NULL;
	HINSTANCE	hInstResource	= NULL;
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_CHILDBKGND), RT_BITMAP);
	m_hBitmap = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(IDB_CHILDBKGND), IMAGE_BITMAP, 0, 0, 0);


	LONG lStyle; 
	lStyle = GetWindowLong(m_cListFilePick.m_hWnd, GWL_STYLE);//获取当前窗口style 
	//lStyle = lStyle | LVS_SHOWSELALWAYS;

	SetWindowLong(m_cListFilePick.m_hWnd, GWL_STYLE, lStyle);//设置style 
	//   DWORD dwStyle = m_listWordFiles.GetExtendedStyle(); 
	//   dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl） 

	//dwStyle |= LVS_EX_CHECKBOXES|LVS_EX_GRIDLINES ;//item前生成checkbox控件 
	//m_listWordFiles.SetExtendedStyle(dwStyle); //设置扩展风格 
	CImageList *pCil;
	pCil = new CImageList();
	pCil->Create(36,36,ILC_COLOR32|ILC_MASK,0,4);

	m_word_icon = pCil->Add(AfxGetApp()->LoadIcon(IDI_ICON_WORD));
	m_folder_icon = pCil->Add(AfxGetApp()->LoadIcon(IDI_FLODER));
	m_cListFilePick.SetImageList(pCil,LVSIL_SMALL);

	/*设置每一列的宽度*/
	m_cListFilePick.SetColumnWidth(1,500);
	
	TransferFile(m_cur_path);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CFilePick::OnEraseBkgnd(CDC* pDC)
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

void CFilePick::SetButtonBackGrounds(CDC *pDC)
{
	this->m_cBtnGoHome1.SetBkGnd(pDC);
	this->m_cBtnPay1.SetBkGnd(pDC);
	this->m_cBtnPreview1.SetBkGnd(pDC);
	this->m_cBtnSettings1.SetBkGnd(pDC);
}


void CFilePick::SetPicCtlBackGrounds()
{
		LPCTSTR arrPath[] = {	_T("res\\FilePickTitle1.png"),
								_T("res\\FilePickTitle2.png")
						};
		UINT arrID[] = {IDC_PIC_TITLEFILEPICK};
	//for(int i = 0; i < 12; i ++)
		//SetOnePicBackGnd(arrPath[i],arrID[i]);

		//根据用户点击移动设备还是云端文件进行选择
		if (this->m_bIsMovable)
			SetOnePicBackGnd(arrPath[0],arrID[0]);
		else
			SetOnePicBackGnd(arrPath[1],arrID[0]);
}
void CFilePick::SetOnePicBackGnd(LPCTSTR filepath, UINT ID)
{
	CImage image; 	//创建图片类
	CRect rect;		//定义矩形类

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

void CFilePick::OnPaint()
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
}

/*
	进入打印预览页面
*/
void CFilePick::OnBnClickedBtnPreview1()
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->GetSafeHwnd(),WM_CHILDSWITCH,DLG_PREVIEW,0);
}

/*
	返回主页按钮单击事件
*/
void CFilePick::OnBnClickedBtnHome()
{
	// TODO: Add your control notification handler code here
	PopupDialog pdlg;
	pdlg.SetMessage("确认放弃当前文件选择？");
	pdlg.SetTimeout(2);
	pdlg.SetButtonText("确  认");
	if (pdlg.DoModal() == IDC_DLG_MYRETURN)
	{
		transaction.setFileNamePrinting(CString(""));
		transaction.setFileTotalPages(0);
		::PostMessage(GetParent()->GetSafeHwnd(),WM_CLOSE,0,0);
	}
}

void CFilePick::OnBnClickedBtnSettings1()
{
	// TODO: Add your control notification handler code 

	::PostMessage(GetParent()->GetSafeHwnd(),WM_CHILDSWITCH,DLG_PRINTSETTING,0);
}


void CFilePick::OnBnClickedBtnPay1()
{
	// TODO: Add your control notification handler code here

	::PostMessage(GetParent()->GetSafeHwnd(),WM_CHILDSWITCH,DLG_PAY,0);
}

void CFilePick::TransferFile( CString path )
{
	m_cListFilePick.DeleteAllItems();
	m_selected_index = 0;

	if(strchr(path, '\\') != NULL)
		m_cListFilePick.InsertItem(0,"返回上级目录",m_folder_icon);

	CString strTemp;		
	if ( path.Right(1) !="\\") {
		strTemp.Format("%s\\*.*",path);
	}
	else {
		strTemp.Format("%s*.*",path);
	}

	CFileFind findFile;
	BOOL bFind = findFile.FindFile(strTemp);
	while(bFind) {
		bFind = findFile.FindNextFile();
		CString curFileName = findFile.GetFileName();
		if (CompareExtention(curFileName,m_fileExtention)) {
			int nCount = m_cListFilePick.GetItemCount();
			m_cListFilePick.InsertItem(nCount,curFileName,m_word_icon);
		}
		if (findFile.IsDirectory() && !findFile.IsDots()) {
			int nCount = m_cListFilePick.GetItemCount();
			m_cListFilePick.InsertItem(nCount,curFileName,m_folder_icon);
		}
	}
}


void CFilePick::OnClickListFilepick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	

	int i;
	int mark;
	bool selected = false;
	CSysLog syslog;

	//找出当前点击的那一行
	for(i=0; i<m_cListFilePick.GetItemCount(); i++) { 
		if(m_cListFilePick.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			break;
	}
	//获取当前选中行内容。
	TCHAR szBuf[255]; 
	LVITEM lvi; 
	lvi.iItem = i; 
	lvi.iSubItem = 0; 
	lvi.mask = LVIF_TEXT; 
	lvi.pszText = szBuf; 
	lvi.cchTextMax = 255; 
	m_cListFilePick.GetItem(&lvi); 

	if(strstr(szBuf, ".doc")==NULL && strstr(szBuf, ".docx")==NULL && strstr(szBuf, ".pdf")==NULL){
		m_selected_index = 0;
		return;
	}
	mark = i;

	m_selected[0] = mark;
	m_selected_index = 1;
	m_sFileNameSelected = szBuf;
	CString fileFullName = m_cur_path;
	fileFullName.Insert(m_cur_path.GetLength(),'\\');
	fileFullName.Insert(fileFullName.GetLength(),m_sFileNameSelected);
	//不要在这里计算页数，计算页数会打开word文档，导致点击一下文件名，会卡顿一下。
	//int fileTotalPage = GetPagesFromFileName(fileFullName);
	transaction.setFileNamePrinting(fileFullName);
	//transaction.setFileTotalPages(fileTotalPage);

	syslog.writeLog(fileFullName);

	////将之前选中的同时选上，如果之前选中的中有当前的行，则取消其选中。
	//for(i=0; i<m_selected_index; i++)
	//{
	//	if(m_selected[i] == mark)
	//	{
	//		m_listWordFiles.SetItemState(mark, 0, LVIS_SELECTED|LVIS_FOCUSED); 
	//		selected = true;
	//		m_selected_index--;
	//		continue;
	//	}
	//	m_listWordFiles.SetItemState(m_selected[i], LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	//}
	//if(!selected)
	//{
	//	m_selected[m_selected_index++] = mark;
	//	//m_listWordFiles.SetItemState(mark, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	//}
	*pResult = 0;
}


void CFilePick::OnDblclkListFilepick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	CString str; 
	int i;
	for(i=0; i<m_cListFilePick.GetItemCount(); i++) { 
		if(m_cListFilePick.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			break;
	}
	TCHAR szBuf[255]; 
	LVITEM lvi; 
	lvi.iItem = i; 
	lvi.iSubItem = 0; 
	lvi.mask = LVIF_TEXT; 
	lvi.pszText = szBuf; 
	lvi.cchTextMax = 255; 
	m_cListFilePick.GetItem(&lvi); 

	//双击的是文件夹
	if(strstr( szBuf, ".doc")==NULL && strstr(szBuf, ".docx")==NULL && strstr(szBuf, ".pdf")==NULL)
	{
		if(strcmp(szBuf, "返回上级目录")==0) {
			int index;
			if((index=m_cur_path.ReverseFind('\\'))!=-1) {
				m_cur_path = m_cur_path.Left(index);
				TransferFile(m_cur_path);
			}
		}
		else {
			m_cur_path = m_cur_path + "\\" + szBuf;
			TransferFile(m_cur_path);
		}
	}
	else {
		//进入打印设置
	}
	*pResult = 0;
}
