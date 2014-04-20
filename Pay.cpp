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
	pdlg.SetMessage("ȷ��Ҫ������ǰ��ӡ��");
	pdlg.SetTimeout(3);
	pdlg.SetButtonText("ȷ  ��");
	if (pdlg.DoModal() == IDC_DLG_MYRETURN)
	{
		//m_total_paid �Ǹ������������0�ȣ�������ʵ0.0000001Ҳ�����0��
		//ͶǮ��͵�λΪ1��0.1Ԫ���ֿ�����0.09999�����ģ�����ѡ���0.01�Ƚ�
		if (transaction.getTotalPaid() > 0.01 )
		{
			//������·��
		}
		transaction.cleanAll();
		::PostMessage(GetParent()->GetSafeHwnd(),WM_CLOSE,0,0);
	} 
	else
	{
		; //���ڱ�ҳ��ʲôҲ����
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
	//���� ��������
	float baseprice = transaction.getBasePrice();
	CString tmpStr = _T("");
	tmpStr.Format("%0.1f",baseprice);
	m_cStaticBasePrice.SetWindowText(tmpStr);

	//����Ӧ����
	float change = transaction.getChange();
	tmpStr.Empty();
	tmpStr.Format("%0.1f",change);
	m_cStaticChange.SetWindowText(tmpStr);

	//�����ܹ��Ѿ�֧�����ܶ�
	float paid = transaction.getTotalPaid();
	tmpStr.Empty();
	tmpStr.Format("%0.1f",paid);
	m_cStaticPaid.SetWindowText(tmpStr);

	//���ô�ӡ����
	int copies = transaction.getPrintingCopies();
	tmpStr.Empty();
	tmpStr.Format("%d",copies);
	m_cStaticPrintingCopies.SetWindowText(tmpStr);

	//������ʾ��ӡ���ļ���
	m_cStaticPrintingFileName.SetWindowText(transaction.getFilenamePrinting());

	//���ô�ӡ����ҳ��
	int pagesPerFile = transaction.getPrintingTotalPages();
	int totalInAll = pagesPerFile * copies;
	tmpStr.Empty();
	tmpStr.Format("%d",totalInAll);
	m_cStaticPrintingPages.SetWindowText(tmpStr);

	//����Ӧ֧���ܶ�
	transaction.setTotalShouldPay();
	float shouldPay = transaction.getTotalShouldPay();
	tmpStr.Empty();
	tmpStr.Format("%0.1f",shouldPay);
	m_cStaticTotalShouldPay.SetWindowText(tmpStr);

	//��������֧�����

	float unpaid = shouldPay - paid;
	tmpStr.Empty();
	tmpStr.Format("%0.1f",unpaid);
	m_cStaticUnPaid.SetWindowText(tmpStr);

	if ( totalInAll > 100)
	{
		PopupDialog pdlg;
		pdlg.SetMessage("���Ĵ�ӡ�ѳ���100ҳ���������־����Ż�");
		pdlg.SetTimeout(2);
		pdlg.SetButtonText("��֪����");
		pdlg.DoModal();
	}
}
void CPay::SetOnePicBackGnd(LPCTSTR filepath, UINT ID)
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
	popdlg.SetMessage("΢��֧�������ݲ�֧�֣��°淢����...");
	popdlg.SetButtonText("�� ��");
	popdlg.DoModal();
}


void CPay::OnBnClickedBtnPaybycard()
{
	// TODO: Add your control notification handler code here
	PopupDialog popdlg;
	CSysLog sl;
	popdlg.SetTimeout(0.5);
	popdlg.SetMessage("�л�����֧������ˢ��:-)");
	popdlg.SetButtonText("ȷ   ��");
	popdlg.DoModal();

	//���������֧����ʽ����ر�ֽ��ɨ���̣߳����ԡ�������
	int isNoteDisabled = DisableNV9ToRecvMoney();
	if (isNoteDisabled == 0)
	{
		environment.SetNoteAcceptorEnable(false);
		sl.writeLog("����ֽ����disable�ɹ�",__FILE__,__FUNCTION__,__LINE__);
		//CloseHandle(hThreadForScanNoteAcceptor);
	} 
	else
	{
		//�᲻������disable���ɹ�������ô�죿�û��Ѿ�ѡ��������֧����ʽ��
		sl.writeLog("����ֽ����disableʧ��",__FILE__,__FUNCTION__,__LINE__);
		//�Ͳ������ṩֽ�ҵķ�������
	}
	
}


void CPay::OnBnClickedBtnPaybycoincash()
{
	// TODO: Add your control notification handler code here
	PopupDialog popdlg;
	CSysLog sl;
	popdlg.SetTimeout(1);
	popdlg.SetMessage("���ֽ�֧������Ͷֽ�һ�Ӳ��:-)");
	bool noteAcceptorStatus = environment.GetNoteAcceptorStatus();
	bool noteAcceptorEnabled = environment.IsNoteAcceptorEnabled();
	//ֽ��Ͷ��������ʼ���˵���δ��ʹ��
	if (noteAcceptorStatus && !noteAcceptorEnabled)	{
		int isNoteEnabled = EnableNV9ToRecvMoney();
		if (isNoteEnabled == 0)	{
			//ʹ��ֽ�����ɹ�������environment�������̣߳�ɨ��ֽ�����Ƿ�Ͷ��ֽ��
			environment.SetNoteAcceptorEnable(true);
			sl.writeLog("����ֽ����enable�ɹ�",__FILE__,__FUNCTION__,__LINE__);
			//hThreadForScanNoteAcceptor = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ScanNoteAcceptorThreadFunc,(PVOID)NULL,0,NULL);
		} 
		else {
			//ʹ��ֽ����ʧ��
			environment.SetNoteAcceptorEnable(false);
			sl.writeLog("����ֽ����enableʧ��",__FILE__,__FUNCTION__,__LINE__);
		}
	} 
	else {//ֽ�ҽ���������ʼ���ˣ���ʹ�ܳɹ�
		popdlg.SetMessage("�л����ֽ�֧������Ͷ��Ӳ��:-)\nֽ����ͣʹ�ã�");
	}
	
	popdlg.SetButtonText("ȷ   ��");
	popdlg.DoModal();
}

//���ô���CStatic �ؼ�����͸��
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
					//֧����ʽͨ��wParam���ݣ�Ͷ�˶���Ǯͨ��lParam����
					//::PostMessage(this->GetParent()->m_hWnd,WM_COMM_NOTECASHGET,PAYBYNOTE,(LPARAM)recvbuf[i+1]);
					break;
				}
			}
		}
		Sleep(200);
	}
}
*/