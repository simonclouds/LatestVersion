// autoPrint2.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "autoPrint2.h"
#include "autoPrint2Dlg.h"
//#include "msword.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoPrint2App

BEGIN_MESSAGE_MAP(CAutoPrint2App, CWinApp)
	//{{AFX_MSG_MAP(CAutoPrint2App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoPrint2App construction

CAutoPrint2App::CAutoPrint2App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAutoPrint2App object

CAutoPrint2App theApp;
//PrintPreview printPreview;
//��ϵͳ�еĶԻ���������ȫ�ֵ��ˣ���֪�������Ľṹ���
//PrintPreview			printPreviewDlg;
//PayByCard				payByCardDlg;
//PayByCash				payByCashDlg;
//SelectU					selectUDlg;
//USBFileList			USBFileListDlg;
//ShowExcelFiles			showExcelFilesDlg;


/////////////////////////////////////////////////////////////////////////////
// CAutoPrint2App initialization

BOOL CAutoPrint2App::InitInstance()
{

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CAutoPrint2Dlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

//�������ܣ�ɨ��ϵͳ��ǰ���ƶ��洢�豸������⵽���ƶ��洢�豸�ľ��ŵ�һ�𷵻ظ�������
//����ֵ:	"H:G:"�������ַ�������ʾH�̺�G�����ƶ��洢���
//Note:	��ʱ������ɨ�赽�ƶ�Ӳ�̡�
//		����Ҫ����ƶ�Ӳ�̣�˼·����ɨ��һ��δ�����ƶ�Ӳ�̣��������е��̷���
//		��ɨ��һ�β����ƶ�Ӳ�̺󣬶Ա���������Щ���ƶ�Ӳ�̣���Щ�Ǳ��صġ�
//CString CAutoPrint2App::ScanRemoveable()
//{
//	char buf[50];
//	::memset(buf,0,50);
//	CString str,strReturn="";
//	/*	��ȡϵͳ�����д��̾�꣬������buf��
//	*	buf�ڵĸ�ʽΪ��c:\<null>d:\<null><null>
//	*	Ȼ���Լ����������̾��
//	*/
//	int nDrives = ::GetLogicalDriveStrings(50,buf);		
//	
//	for (int i = 0; i < nDrives/4; i++) {
//		char temp[4];
//		for (int j = 0; j < 4 ; j++){
//			temp[j] = buf[i*4 + j];
//		}
//		CString str(temp);
//		int driveType = ::GetDriveType(str);
//		switch(driveType) {
//		case DRIVE_REMOVABLE:
//			strReturn += temp[0];
//			strReturn += ":";
//			break;
//		case DRIVE_FIXED:
//			break;
//		default:
//			break;
//		}
//	}
//	return strReturn;
//}
////�������ܣ������ļ���׺���ݹ���ҵ�ָ���ļ����µ��ļ���Ȼ����ӵ�list�ؼ���ȥ
////���������
////		CString path:pathָ��Ҫ������·��
////		CString extention:ָ��Ҫ���ҵ��ļ����ͺ�׺��
////		CListCtrl *list:ָ��Ҫ���ļ��������list�ؼ�
////��չ����ʽ: doc|docx,Ҳ�п�����һ����׺��pdf,txt��
//void CAutoPrint2App::FindFilesByExtentionForDlg(CString path, CString extention, CListCtrl *list)
//{
//	/*Ϊÿ���ļ����ͼ��*/
// 	CImageList *pCil;
// 	pCil = new CImageList();
// 	pCil->Create(36,36,ILC_COLOR32|ILC_MASK,0,4);
//	//CBitmap wordIcon;
//	//wordIcon.LoadBitmap(IDI_ICON_WORD);
//	pCil->Add(AfxGetApp()->LoadIcon(IDI_ICON_WORD));
// 	list->SetImageList(pCil,LVSIL_SMALL);
//	/*����ÿһ�еĿ��*/
//	list->SetColumnWidth(1,500);
//
//	if (path == "" || extention == "") {
//		return ;
//	}
//	/*	����path��û�С�\����β,����Ҫ���ҵ��ַ�����
//	*	����Ϊ���е��ļ������ҵ���Ȼ��ͨ���Ƚ��ļ�����׺���жϡ�����Ч����Ե��£����ԸĽ�����
//	*/
//	CString strTemp;		
//	if ( path.Right(1) !="\\") {
//		strTemp.Format("%s\\*.*",path);
//	}
//	else {
//		strTemp.Format("%s*.*",path);
//	}
//
//	CFileFind findFile;
//	BOOL bFind = findFile.FindFile(strTemp);
//	while(bFind) {
//		bFind = findFile.FindNextFile();
//		CString curFileName = findFile.GetFileName();
//		if (CompareExtention(curFileName,extention)) {
//			int i = list->GetItemCount();
//			CString found = findFile.GetFilePath();	
//			list->InsertItem(i,found);
//		}
//		if (findFile.IsDirectory() && !findFile.IsDots()) {
//			FindFilesByExtentionForDlg(findFile.GetFilePath(),extention,list);
//		}
//	}
//}
////�������ܣ���WORD�ĵ��ж�ȡ����ҳ��
////���������const CString fileName:ָ��Ҫ��ȡ��ҳ�����ļ�
////Note:		���������������ͨ���ԣ�����ֻ�ܼ���word�ĵ���ҳ����������ʽ��pdf��ʱ�޷�֧��
////����ֵ��	��ȷ������ļ�����ҳ����
//int CAutoPrint2App::GetPagesFromFileName(const CString fileName)
//{
//	//���ݺ�׺����ȷ����λ�ȡҳ��
//	//����������
//	int pages = 0;
//	if (fileName == "")
//	{
//		return pages;
//	}
//	if (fileName.Right(4) == "docx" || fileName.Right(4) == ".doc")
//	{
//		//this is a word document
//		_Application objWord;
//		COleVariant covTrue((short)TRUE),
//					covFalse((short)FALSE),
//					covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR);
//
//		//�õ�IDispatch ָ�벢���ӵ�OBJWORD������
//		if (!objWord.CreateDispatch("Word.Application")) {
//			AfxMessageBox("���ܻ��word����");
//			return -1;
//		}
//	
//		objWord.SetVisible(FALSE);
//		Documents docs(objWord.GetDocuments());
//		_Document testDoc;
//	
//		testDoc.AttachDispatch(docs.Open(
//							COleVariant(fileName,VT_BSTR),
//							covFalse,
//							covTrue,
//							covFalse,
//							covOptional,
//							covOptional,
//							covFalse,
//							covOptional,
//							covOptional,
//							covOptional,
//							covOptional,
//							covTrue,
//							covOptional,
//							covOptional,
//							COleVariant((long)0),
//							covOptional
//							)
//							);
//		pages = testDoc.ComputeStatistics(2,covOptional);//2 == wdStatisticPages
//		
//		/*
//		http://msdn.microsoft.com/en-us/library/office/ff192582.aspx
//		Name  							Value  			Description
//		wdStatisticCharacters			3				Count of characters.
//		wdStatisticCharactersWithSpaces	5				Count of characters including spaces.
//		wdStatisticFarEastCharacters	6				Count of characters for Asian languages.
//		wdStatisticLines				1				Count of lines.
//		wdStatisticPages				2				Count of pages.
//		wdStatisticParagraphs			4				Count of paragraphs.
//		wdStatisticWords				0				Count of words.
//		*/
//		/*CString outMsg ;
//		outMsg.Format("pages of word:%d",pages);
//		AfxMessageBox(outMsg);*/
//		//docs.Close();
//		objWord.Quit(	covFalse,  // SaveChanges.
//						covTrue,   // OriginalFormat.
//						covFalse   // RouteDocument.
//					);
//		}
//	
//	return pages;
//}
////�������ܣ��ж�path �ĺ�׺�����Ƿ��ں�׺���ַ���ext�С�
////���뺯����	CString path:	���ַ���
////				CString ext:	ĸ�ַ���
////����ֵ��		BOOL		:	path ��ext�з���TRUE�����򷵻�FALSE��
////Note:		��׺���ַ���ext�����׺���ָ���'|'
////			��Ϊ��׺���ַ���ext�ͺ�׺��path�����Լ��ֶ���ֵ�ģ���ʡ�ԺϷ��Լ��
//BOOL CAutoPrint2App::CompareExtention(CString path, CString ext)
//{
//	if (path == "" || ext == "") {
//		return FALSE;
//	}
//	CString workStr = ext;
//	while(TRUE) {
//		if (workStr.Find("|") == -1) { //workStr��ֻ��һ����׺����
//			int len = workStr.GetLength();
//			if (path.Right(len) == workStr) {
//				return TRUE;
//			}
//			return FALSE;		//���Ѿ������һ����׺���ˣ�������ȵĻ�����ʾpath����ļ��ĺ�׺������ext��
//		}
//		else {	
//			int verticalBarIndex = workStr.Find("|");		//���߷ָ������
//			CString curExtention = workStr.Left(verticalBarIndex);
//			int curLen = curExtention.GetLength();
//			if ( path.Right(curLen) == curExtention) {
//				return TRUE;
//			}
//			else {		//�����ext��ȡ�����ĺ�׺����path��׺����ƥ�䣬����
//				workStr = workStr.Right(workStr.GetLength() - (curLen + 1));
//			}
//		}
//	}
//}
