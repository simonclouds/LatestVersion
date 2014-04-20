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
	//Ĭ�ϵ�ǰ��ӡ���׵��ĵ���ӡ1��
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
	pdlg.SetMessage("ȷ��������ǰ������");
	pdlg.SetButtonText("ȷ  ��");
	pdlg.SetTimeout(2);
	if (pdlg.DoModal() == IDC_DLG_MYRETURN)
	{
		//transaction Ӧ����������
		transaction.setFileNamePrinting("");
		transaction.setFileTotalPages(0);
		transaction.setPrintingCopies(0);
		transaction.setPrintingTotalPages(0);
		//transaction.set
		::PostMessage(GetParent()->GetSafeHwnd(),WM_CLOSE,0,0);
	}
	else		//��ʱ
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
	//ҳ��ͳ�Ƴ�ʼ��
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();

	if (i_check == 1)
	{
		CString fileTotalPageStr = _T("");
		int filetotalpages = transaction.getFileTotalPages();
		fileTotalPageStr.Format("%d",filetotalpages);
		m_cShowPagesSelect.SetWindowText(fileTotalPageStr);
		//Ĭ�ϴ�ӡ�����ĵ�
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
	CImage image; //����ͼƬ��
	CRect rect;//���������

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

//������ɺ�ȥ֧����ӡ
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
	if (i_check == 1)	//���ȫ����ӡ��ѡ��,����Ӧ����
		return ;
	AppendCharToCString(&m_PagesUserSelected,'1');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn2()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//���ȫ����ӡ��ѡ��,����Ӧ����
		return ;
	AppendCharToCString(&m_PagesUserSelected,'2');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn3()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//���ȫ����ӡ��ѡ��,����Ӧ����
		return ;
	AppendCharToCString(&m_PagesUserSelected,'3');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn4()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//���ȫ����ӡ��ѡ��,����Ӧ����
		return ;
	AppendCharToCString(&m_PagesUserSelected,'4');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn5()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//���ȫ����ӡ��ѡ��,����Ӧ����
		return ;
	AppendCharToCString(&m_PagesUserSelected,'5');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn6()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//���ȫ����ӡ��ѡ��,����Ӧ����
		return ;
	AppendCharToCString(&m_PagesUserSelected,'6');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn7()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//���ȫ����ӡ��ѡ��,����Ӧ����
		return ;
	AppendCharToCString(&m_PagesUserSelected,'7');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn8()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//���ȫ����ӡ��ѡ��,����Ӧ����
		return ;
	AppendCharToCString(&m_PagesUserSelected,'8');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn9()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//���ȫ����ӡ��ѡ��,����Ӧ����
		return ;
	AppendCharToCString(&m_PagesUserSelected,'9');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtncomma()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//���ȫ����ӡ��ѡ��,����Ӧ����
		return ;
	AppendCharToCString(&m_PagesUserSelected,',');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtn0()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//���ȫ����ӡ��ѡ��,����Ӧ����
		return ;
	AppendCharToCString(&m_PagesUserSelected,'0');
	FreshUserCStatic();
	CheckPagesFromPageRangAnyway();
}

void CPrintSettings::OnBnClickedBtndash()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//���ȫ����ӡ��ѡ��,����Ӧ����
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
			pdg.SetMessage("ָ��ҳ�淶ΧӦ��С����");
			break;
		case SETTINGERROR_INVALIDCHAR:
			pdg.SetMessage("ָ����Χ�����Ƿ��ַ���");
			break;
		case SETTINGERROR_OUTOFRANGE:
			pdg.SetMessage("ָ��ҳ�泬���ĵ�����Χ��");
			break;
		case SETTINGERROR_WRONGFORMAT:
			pdg.SetMessage("ָ���ĸ�ʽ����ȷ��");
			break;
		default:
			;//do nothing
		}
		pdg.SetButtonText("ȷ  ��");
		pdg.SetTimeout(0.5);
		pdg.DoModal();
		return ;
	}
	CString pagesUserSelectStr = _T("");
	pagesUserSelectStr.Format("%d",pagesUserSelect);
	m_cShowPagesSelect.SetWindowText(pagesUserSelectStr);
	//�����ok��ť���򽫼������Ҫ��ӡ����ҳ����¼����
	transaction.setPrintingTotalPages(pagesUserSelect);
}

//����CStatic�ؼ�����ͱ���͸��
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

//��ȫ����ӡradio��ѡ��
void CPrintSettings::OnBnClickedRadioAllpages()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_ALLPAGES))->GetCheck();
	if (i_check == 1)	//���ȫ����ӡ��ѡ��,�������ѡҳ��Χ
	{
		m_PagesUserSelected = _T("");
		FreshUserCStatic();
	}
	//ҳ��ͳ�Ƴ�ʼ��
	CString fileTotalPageStr = _T("");
	int totalfilepages = transaction.getFileTotalPages();
	fileTotalPageStr.Format("%d",totalfilepages);
	m_cShowPagesSelect.SetWindowText(fileTotalPageStr);
	//��ӡ�����ĵ�����ôprintingtotalpages == filetotalpages
	transaction.setFileSettingStr("");	//�Զ����ӡҳ�淶Χ���ַ�������Ϊ��
	transaction.setPrintingTotalPages(totalfilepages);
}

//����ѡradio��ѡ��
void CPrintSettings::OnBnClickedRadioUserpages()
{
	// TODO: Add your control notification handler code here
	int i_check = ((CButton*)GetDlgItem(IDC_RADIO_USERPAGES))->GetCheck();
	//���û�ѡ���Զ���ҳ��Χ��ʱ�򣬲��Ҵ�ʱ��δ�����κη�Χ
	if (i_check == 1 && m_PagesUserSelected.GetLength()== 0)
	{
		CString tmp = _T("0");
		m_cShowPagesSelect.SetWindowText(tmp);
		//����һ�ε����������跶Χ��radio����ô����printingtotalpage = 0
		transaction.setPrintingTotalPages(0);
	}
}

//��������: �ӵ����ֶ��м��������Ĵ���ӡҳ��
//			��"2","3-12"�������ַ�������ȡ�����а�����ҳ�����ֱ�Ϊ1,10ҳ
//			�˴���Ӧ�ü���Ƿ����"3-5-8"�����Ĵ�������
//�������:	CString str �������ַ���
//����ֵ:	����������ֶ��а�����ҳ�������쳣������
int CPrintSettings::GetCountFromStr( CString str )
{
	int pages = 0;
	if (str == "") 
		return pages;
	//����"12"�����Ĳ�����"-"�������ֱ�Ӽ�ҳ����1
	if (str.Find("-") == -1) {
		int thispage = CString2Int(str);
		if (!InputPageRangeValid(thispage,transaction.getFileTotalPages())) {
			return SETTINGERROR_OUTOFRANGE;
		}
		pages += 1;
	}
	//����"3-10"���������
	else {
		int firstDash = str.Find("-");
		//�ѵ�һ��'-'�ַ�������ַ�����ȡ�������鿴�Ƿ񻹰���"-"("3-5-8")��������������ǷǷ����봮
		CString tailString = str.Right(str.GetLength() - firstDash - 1);
		//β���ַ���������'-'�ˣ���������str������ҳ��
		if (tailString.Find("-") == -1) {
			//��ȡfirstDash��ߵ��Ӵ�����1��ʼ����
			CString firstNumStr = str.Left(firstDash);
			int firstNum = CString2Int(firstNumStr);
			if (firstNum <= 0) {
				return SETTINGERROR_OUTOFRANGE;
			}
			//��ȡfirstDash �ұߵ��Ӵ������ж��Ƿ񳬳��ĵ������ҳ��
			CString secondNumStr = tailString;
			int secondNum = CString2Int(secondNumStr);
			int fileTotalPage = transaction.getFileTotalPages();
			if (!InputPageRangeValid(secondNum, fileTotalPage)) {
				return SETTINGERROR_OUTOFRANGE;
			}
			//'-'��ߵ����ֱ���С�ڵ����ұ�����
			if (firstNum <= secondNum) {
				pages = secondNum - firstNum + 1;
			}
			else {
				return SETTINGERROR_BIGLITTLE;		//�� "5-3"���������봮���д�
			}
		}
		else {
			return SETTINGERROR_WRONGFORMAT;			//�� "3-5-8"���������봮���д�
		}
	}
	return pages;
}

//�������ܣ�����ַ������Ƿ����"--"|"-,"|",-"|",,"������Ӱ�����ҳ���ķǷ��ַ����
//���������CString str �������ַ���
//����ֵ��	BOOL �����򷵻�TRUE������������FALSE   
//Note:		***ע�ⷵ��ֵ������***
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

//�������ܣ����ַ�������ȡҳ��
//���������CString str������ҳ�����ַ�������"2-5,7,10"
//����ֵ��	int ��ҳ��
int CPrintSettings::GetPagesFromString( CString str )
{
	int pages = 0;
	int strLen = str.GetLength();
	int indexOfStr = 0;
	//�Ƿ��зǷ��ַ�,����(0-9)|(-)|(,)�������ַ�������ַ�
	while (indexOfStr != strLen) {
		char c = str.GetAt(indexOfStr);		//first from zero ?
		BOOL validChar = (isDigit(c) || isAllowedChar(c));	//���ַ������ֻ���'-'.','
		if (validChar) {
			indexOfStr ++;
		}
		else {
			return SETTINGERROR_INVALIDCHAR;
		}	
	}
	/*
	* ȫ���ǺϷ��ַ��������
	* �Ƿ��зǷ��ַ����"--","-,",",-",",,",�ڴ˺����ڲ�ͬʱ�ų�������ĸ��β��ĸ�������ֵ����
	*/
	BOOL validStr = IncludeInvaidCharGroup(str);
	if (validStr) {
		return SETTINGERROR_WRONGFORMAT;
	}
	CString workStr = str;
	//���ַ����м���ҳ����ʼ
	/*
	*  ��ԭ�ַ����в��Ϸ���һ�����ĶΣ��ö��ŷָ�����Ȼ��ѭ��ÿ�δ���һ����
	*  ÿ�����а�����ҳ������Ӿ����ܵ�Ҫ��ӡ��ҳ��
	*/
	while (TRUE) {
		int subpages = 0;
		if (workStr.Find(",") == -1) {			//workStr ֱ���� "23"�����ĵ�ҳ���봮������"2-3"������
			subpages = GetCountFromStr(workStr);
			if (subpages > 0) {
				pages += subpages;
			}
			else {
				return subpages;		//���������ô��������subpages������
			}
			break;								//ͬʱ��while�ĳ���
		}
		//workStr�������','���������ָ��ÿ�ηָ�ͷ����һ���Ӵ�����
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
			//���˶��ź���Ĳ��ּ�������
			int workStrLen = workStr.GetLength();
			workStr = workStr.Right(workStrLen - indexOfComma - 1);
		}
	}
	return pages;
}
//�������ܣ���һ��ֻ������(��λ��)���ַ���ת��������
int CPrintSettings::CString2Int( const CString str )
{
	int num = 0;
	if (str != "") 
		num = ::atoi(str);			//�˴�����ȷ��������
	return num;
}

//�������ܣ��鿴�����ַ����еĵ���ҳ�����Ƿ񳬹��ĵ����ҳ��
//BOOL CPrintSettings::isOutOfPageRange( int inputPage, int fileTotalPage )
//{
//	if (inputPage > fileTotalPage) 
//		return TRUE;
//	return FALSE;	
//}
//�������ܣ����ǲ�������������ַ�'-'��','
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
//�������ܣ��ж������ҳ�������Ƿ񳬹��ĵ���������ҳ��
//����ֵ��	��ȷ�ķ�ΧӦ���� [0,max]
BOOL CPrintSettings::InputPageRangeValid( int inputPage, int fileTotalPage )
{
	if (inputPage <= 0) 
		return FALSE;
	else if (inputPage > fileTotalPage) 
		return FALSE;
	else
		return TRUE;
}

//ÿһ�ΰ��������ȥ��⵱ǰ��ҳ���ܺͣ�������÷�Χ�Ƿ�Ҳ���¸�transaction,ͬʱ��ӡҳ������Ϊ0
void CPrintSettings::CheckPagesFromPageRangAnyway()
{
	int pagesUserSelect = GetPagesFromString(m_PagesUserSelected);
	CString pagesUserSelectStr = _T("");
	transaction.setFileSettingStr(m_PagesUserSelected);
	//������÷Ƿ�����Ϊ0
	if (pagesUserSelect < 0) {
		pagesUserSelectStr.Format("%d",0);
		m_cShowPagesSelect.SetWindowText(pagesUserSelectStr);
		transaction.setPrintingTotalPages(0);
	}
	else {
		pagesUserSelectStr.Format("%d",pagesUserSelect);
		m_cShowPagesSelect.SetWindowText(pagesUserSelectStr);
		//�����ok��ť���򽫼������Ҫ��ӡ����ҳ����¼����
		transaction.setPrintingTotalPages(pagesUserSelect);
	}
}






