// FilePick.cpp : implementation file
//

#include "stdafx.h"
#include "autoPrint2.h"
#include "FilePick.h"
#include "afxdialogex.h"
#include "global.h"

#include "MemDC.h"				//button��ͼʹ�õ�

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
	//���ذ�ť����
	this->m_cBtnGoHome1.LoadStdImage(IDR_BTN_HOME,_T("PNG"));
	this->m_cBtnPay1.LoadStdImage(IDR_BTN_PAY,_T("PNG"));
	this->m_cBtnPreview1.LoadStdImage(IDR_BTN_PREVIEW,_T("PNG"));
	this->m_cBtnSettings1.LoadStdImage(IDR_BTN_SETTINGS,_T("PNG"));

	//���ر����ڱ���
	HBITMAP		hBitmap			= NULL;
	HINSTANCE	hInstResource	= NULL;
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_CHILDBKGND), RT_BITMAP);
	m_hBitmap = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(IDB_CHILDBKGND), IMAGE_BITMAP, 0, 0, 0);


	LONG lStyle; 
	lStyle = GetWindowLong(m_cListFilePick.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style 
	//lStyle = lStyle | LVS_SHOWSELALWAYS;

	SetWindowLong(m_cListFilePick.m_hWnd, GWL_STYLE, lStyle);//����style 
	//   DWORD dwStyle = m_listWordFiles.GetExtendedStyle(); 
	//   dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl�� 

	//dwStyle |= LVS_EX_CHECKBOXES|LVS_EX_GRIDLINES ;//itemǰ����checkbox�ؼ� 
	//m_listWordFiles.SetExtendedStyle(dwStyle); //������չ��� 
	CImageList *pCil;
	pCil = new CImageList();
	pCil->Create(36,36,ILC_COLOR32|ILC_MASK,0,4);

	m_word_icon = pCil->Add(AfxGetApp()->LoadIcon(IDI_ICON_WORD));
	m_folder_icon = pCil->Add(AfxGetApp()->LoadIcon(IDI_FLODER));
	m_cListFilePick.SetImageList(pCil,LVSIL_SMALL);

	/*����ÿһ�еĿ��*/
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

		//�����û�����ƶ��豸�����ƶ��ļ�����ѡ��
		if (this->m_bIsMovable)
			SetOnePicBackGnd(arrPath[0],arrID[0]);
		else
			SetOnePicBackGnd(arrPath[1],arrID[0]);
}
void CFilePick::SetOnePicBackGnd(LPCTSTR filepath, UINT ID)
{
	CImage image; 	//����ͼƬ��
	CRect rect;		//���������

	image.Load(filepath); //����ͼƬ·������ͼƬ
	int cx = image.GetWidth();//��ȡͼƬ���
	int cy = image.GetHeight();//��ȡͼƬ�߶�

	GetDlgItem(ID)->GetWindowRect(&rect);//�����ھ���ѡ�е�picture�ؼ���
	ScreenToClient(&rect);//���ͻ���ѡ�е�Picture�ؼ���ʾ�ľ���������
	GetDlgItem(ID)->MoveWindow(rect.left, rect.top, cx, cy, TRUE);//�������ƶ���Picture�ؼ���ʾ�ľ�������

	CWnd *pWnd=GetDlgItem(ID);//���pictrue�ؼ����ڵľ��
	pWnd->GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������
	CDC *pDC=pWnd->GetDC();//���pictrue�ؼ���DC
	image.Draw(pDC->m_hDC, rect); //��ͼƬ����Picture�ؼ���ʾ�ľ�������

	ReleaseDC(pDC);//�ͷ�picture�ؼ���DC
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
	�����ӡԤ��ҳ��
*/
void CFilePick::OnBnClickedBtnPreview1()
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->GetSafeHwnd(),WM_CHILDSWITCH,DLG_PREVIEW,0);
}

/*
	������ҳ��ť�����¼�
*/
void CFilePick::OnBnClickedBtnHome()
{
	// TODO: Add your control notification handler code here
	PopupDialog pdlg;
	pdlg.SetMessage("ȷ�Ϸ�����ǰ�ļ�ѡ��");
	pdlg.SetTimeout(2);
	pdlg.SetButtonText("ȷ  ��");
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
		m_cListFilePick.InsertItem(0,"�����ϼ�Ŀ¼",m_folder_icon);

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

	//�ҳ���ǰ�������һ��
	for(i=0; i<m_cListFilePick.GetItemCount(); i++) { 
		if(m_cListFilePick.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			break;
	}
	//��ȡ��ǰѡ�������ݡ�
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
	//��Ҫ���������ҳ��������ҳ�����word�ĵ������µ��һ���ļ������Ῠ��һ�¡�
	//int fileTotalPage = GetPagesFromFileName(fileFullName);
	transaction.setFileNamePrinting(fileFullName);
	//transaction.setFileTotalPages(fileTotalPage);

	syslog.writeLog(fileFullName);

	////��֮ǰѡ�е�ͬʱѡ�ϣ����֮ǰѡ�е����е�ǰ���У���ȡ����ѡ�С�
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

	//˫�������ļ���
	if(strstr( szBuf, ".doc")==NULL && strstr(szBuf, ".docx")==NULL && strstr(szBuf, ".pdf")==NULL)
	{
		if(strcmp(szBuf, "�����ϼ�Ŀ¼")==0) {
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
		//�����ӡ����
	}
	*pResult = 0;
}
