// AutoPrint2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "autoPrint2.h"
#include "AutoPrint2Dlg.h"
#include "afxdialogex.h"

#include "PopupDialog.h"
#include "global.h"
#include "MemDC.h"
#include <Dbt.h>

#include "MainPage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CAutoPrint2Dlg dialog

IMPLEMENT_DYNAMIC(CAutoPrint2Dlg, CDialog)

CAutoPrint2Dlg::CAutoPrint2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoPrint2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAutoPrint2Dlg)
	// NOTE: the ClassWizard will add member initialization here

	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CAutoPrint2Dlg::~CAutoPrint2Dlg()
{
}

void CAutoPrint2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAutoPrint2Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON_MOVABLEDEVICES, m_cBtnMovableDevices);
	DDX_Control(pDX, IDC_BTN_NetPrint, m_cBtnNetprint);
}


BEGIN_MESSAGE_MAP(CAutoPrint2Dlg, CDialog)
	//{{AFX_MSG_MAP(CAutoPrint2Dlg)
	//}}AFX_MSG_MAP
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_NetPrint, &CAutoPrint2Dlg::OnBnClickedBtnNetprint)
	ON_BN_CLICKED(IDC_BUTTON_MOVABLEDEVICES, &CAutoPrint2Dlg::OnBnClickedButtonMovableDevices)
END_MESSAGE_MAP()


// CAutoPrint2Dlg message handlers

extern Session g_session;

BOOL CAutoPrint2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	this->m_cBtnMovableDevices.LoadStdImage(IDR_MOVABLE,_T("PNG"));
	this->m_cBtnNetprint.LoadStdImage(IDR_CLOUD,_T("PNG"));
	


	HBITMAP		hBitmap			= NULL;
	HINSTANCE	hInstResource	= NULL;

	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BACKGROUND), RT_BITMAP);

	// Load bitmap In
	m_hBitmap = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(IDB_BACKGROUND), IMAGE_BITMAP, 0, 0, 0);
	
	u_count = 0;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAutoPrint2Dlg::OnPaint() 
{
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
//�������ܣ���Ϣ�������������ƶ��洢�豸�Ĳ�����γ�
LRESULT CAutoPrint2Dlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	CSysLog slog;
	if (message == WM_DEVICECHANGE) {
		CString str;
		DEV_BROADCAST_HDR* dhr = (DEV_BROADCAST_HDR *)lParam;
		switch(wParam) {
		case DBT_DEVICEARRIVAL:
			if (dhr->dbch_devicetype == DBT_DEVTYP_VOLUME) {
				PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)dhr;
				if (lpdbv->dbcv_flags == 0) {
					//AfxMessageBox("�����ƶ��洢�豸");
					
					slog.writeLog("Found Movable Device.\n");
					u_count++;
					g_session.m_udisks = u_count;

					if(g_session.IsSessionStarted())
					{
						//ֱ�ӵ�������ҳ��
						CString str = ScanRemoveable();		
						g_session.m_udisk_string = str;
						return NULL;
					}
					g_session.SessionStart();
					
					//ֱ�ӵ�������ҳ��
					CString str = ScanRemoveable();		
					g_session.m_udisk_string = str;
					
					//�Զ��������U�̺󣬽����ƶ��豸��ӡģʽ
				}
			}
			break;
		case DBT_DEVICEREMOVECOMPLETE:
			if (dhr->dbch_devicetype == DBT_DEVTYP_VOLUME) {
				PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)dhr;
				if (lpdbv->dbcv_flags == 0) {
					//AfxMessageBox("�ƶ��洢�豸���Ƴ�");
					slog.writeLog("Movable Device Deleted!\n");
					u_count--;
					g_session.m_udisks = u_count;
					if(u_count == 0)	//ǿ�ƽ�����ҳ
					{
						//listUFilesDlg.EndDialog(0);
						//��������ƶ��豸��ӡģʽ�����У���û�������Ĵ�ӡ���ڣ���Ϊ�ύ����ӡ����
						//��ʱ����γ�U�̣���ô�ر�MainPage
						g_session.SessionEnd();
					}
				}
			}
			break;
		default:
			break;
		}
	}
	return CDialog::WindowProc(message, wParam, lParam);
}


void CAutoPrint2Dlg::OnBnClickedBtnNetprint()
{
	//MessageBoxA("����Ŭ��������...", "��ʾ��", 0);
	/*PopupDialog PopupDialogDlg;
	PopupDialogDlg.SetTimeout(1);
	char tips[] = "����Ŭ��������...";
	PopupDialogDlg.SetMessage(tips);
	PopupDialogDlg.DoModal();*/

	CSysLog syslog;
	syslog.writeLog("Net Print Clicked\n");
	CString temp = "F:";
	CMainPage mainPageDlg;
	mainPageDlg.FilePickDlg.m_cur_path=temp;
	mainPageDlg.FilePickDlg.m_bIsMovable = FALSE;
	mainPageDlg.DoModal();
}

void CAutoPrint2Dlg::OnBnClickedButtonMovableDevices()
{
	//TODO: Add your control notification handler code here
	//CString str = ScanRemoveable();
	//if (str.IsEmpty() == TRUE) {	//δ��⵽U��
	//	PopupDialog PopupDialogDlg;
	//	PopupDialogDlg.DoModal();
	//}
	//else {							//�Ի����оټ�⵽��U���̷�
	//	//��ʼ�Ự
	//	if(g_session.IsSessionStarted())
	//		return;
	//	g_session.SessionStart();
	//	////ֱ�ӵ�������ҳ��
	//	CString str = ScanRemoveable();	
	//	g_session.m_udisk_string = str;

	//	listUFilesDlg.m_uSelected = str.GetAt(0);
	//	listUFilesDlg.DoModal();
	//}
	CString movableSelected ="";
	CSysLog syslog;
	movableSelected = ScanRemoveable();
	if (movableSelected == "")
	{
		syslog.writeLog("No Movable Devices Detected\n");
		PopupDialog popupDialog;
		popupDialog.SetTimeout(2);
		char tips[] = "û���ҵ��κ��ƶ��豸�������ƶ��豸��";
		popupDialog.SetMessage(tips);
		popupDialog.SetButtonText("��    ��");
		popupDialog.DoModal();
	}
	else {
		syslog.writeLog("Go To Movable Device\n");
		CMainPage MainPageDlg;
		MainPageDlg.FilePickDlg.m_cur_path = movableSelected;
		MainPageDlg.FilePickDlg.m_bIsMovable = TRUE;
		MainPageDlg.DoModal();
	}	
}


BOOL CAutoPrint2Dlg::OnEraseBkgnd(CDC* pDC)
{
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

void CAutoPrint2Dlg::SetButtonBackGrounds(CDC *pDC)
{
	this->m_cBtnMovableDevices.SetBkGnd(pDC);
	this->m_cBtnNetprint.SetBkGnd(pDC);
}



void CAutoPrint2Dlg::SetPicCtlBackGrounds()
{
	LPCTSTR arrPath[] = {	_T("res\\title.png"),
							_T("res\\tipsleft.png"),
							_T("res\\tipsright.png"),
							_T("res\\undermovable.png"),
							_T("res\\undercloud.png"),
							_T("res\\followus.png"),
							_T("res\\2dcode.png"),
							_T("res\\contactus.png"),
							_T("res\\contactdetail.png"),
							_T("res\\serviceforu.png"),
							_T("res\\serviceleft.png"),
							_T("res\\serviceright.png")
						};
	UINT arrID[] = {IDC_TITLE,
					IDC_TIPSLEFT,
					IDC_TIPSRIGHT,
					IDC_UNDERMOVABLE,
					IDC_UNDERCLOUD,
					IDC_FOLLOWUS,
					IDC_2DCODE,
					IDC_CONTACTUS,
					IDC_CONTACTDETAIL,
					IDC_SERVICEFORU,
					IDC_SERVICELEFT,
					IDC_SERVICERIGHT
	};
	for(int i = 0; i < 12; i ++)
		SetOnePicBackGnd(arrPath[i],arrID[i]);
}

void CAutoPrint2Dlg::SetOnePicBackGnd(LPCTSTR filepath, UINT ID)
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