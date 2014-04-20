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
//将系统中的对话框都声明成全局的了，不知道这样的结构如何
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

//函数功能：扫描系统当前的移动存储设备，将检测到的移动存储设备的卷标放到一起返回给调用者
//返回值:	"H:G:"这样的字符串，表示H盘和G盘是移动存储卷标
//Note:	暂时并不能扫描到移动硬盘。
//		若需要检测移动硬盘，思路：先扫描一次未插入移动硬盘，记下所有的盘符，
//		再扫描一次插入移动硬盘后，对比来分析哪些是移动硬盘，哪些是本地的。
//CString CAutoPrint2App::ScanRemoveable()
//{
//	char buf[50];
//	::memset(buf,0,50);
//	CString str,strReturn="";
//	/*	获取系统内所有磁盘卷标，并放入buf中
//	*	buf内的格式为：c:\<null>d:\<null><null>
//	*	然后自己解析出磁盘卷标
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
////函数功能：根据文件后缀名递归地找到指定文件夹下的文件，然后添加到list控件中去
////输入参数：
////		CString path:path指定要搜索的路径
////		CString extention:指定要查找的文件类型后缀名
////		CListCtrl *list:指定要将文件添加至的list控件
////扩展名格式: doc|docx,也有可能是一个后缀名pdf,txt等
//void CAutoPrint2App::FindFilesByExtentionForDlg(CString path, CString extention, CListCtrl *list)
//{
//	/*为每个文件添加图标*/
// 	CImageList *pCil;
// 	pCil = new CImageList();
// 	pCil->Create(36,36,ILC_COLOR32|ILC_MASK,0,4);
//	//CBitmap wordIcon;
//	//wordIcon.LoadBitmap(IDI_ICON_WORD);
//	pCil->Add(AfxGetApp()->LoadIcon(IDI_ICON_WORD));
// 	list->SetImageList(pCil,LVSIL_SMALL);
//	/*设置每一列的宽度*/
//	list->SetColumnWidth(1,500);
//
//	if (path == "" || extention == "") {
//		return ;
//	}
//	/*	根据path有没有‘\’结尾,设置要查找的字符串。
//	*	设置为所有的文件都查找到，然后通过比较文件名后缀来判断。但是效率相对低下，可以改进性能
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
////函数功能：从WORD文档中读取其总页数
////输入参数：const CString fileName:指定要获取总页数的文件
////Note:		这个函数并不具有通用性，而是只能计算word文档的页数，其他格式如pdf暂时无法支持
////返回值：	正确则这个文件的总页数，
//int CAutoPrint2App::GetPagesFromFileName(const CString fileName)
//{
//	//根据后缀名来确定如何获取页数
//	//输入参数检测
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
//		//得到IDispatch 指针并附加到OBJWORD对象中
//		if (!objWord.CreateDispatch("Word.Application")) {
//			AfxMessageBox("不能获得word对象");
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
////函数功能：判断path 的后缀名，是否在后缀名字符串ext中。
////输入函数：	CString path:	子字符串
////				CString ext:	母字符串
////返回值：		BOOL		:	path 在ext中返回TRUE，否则返回FALSE；
////Note:		后缀名字符串ext多个后缀名分割用'|'
////			因为后缀名字符串ext和后缀名path都是自己手动赋值的，就省略合法性检测
//BOOL CAutoPrint2App::CompareExtention(CString path, CString ext)
//{
//	if (path == "" || ext == "") {
//		return FALSE;
//	}
//	CString workStr = ext;
//	while(TRUE) {
//		if (workStr.Find("|") == -1) { //workStr中只有一个后缀名了
//			int len = workStr.GetLength();
//			if (path.Right(len) == workStr) {
//				return TRUE;
//			}
//			return FALSE;		//这已经是最后一个后缀名了，还不相等的话，表示path这个文件的后缀名不在ext中
//		}
//		else {	
//			int verticalBarIndex = workStr.Find("|");		//竖线分割符索引
//			CString curExtention = workStr.Left(verticalBarIndex);
//			int curLen = curExtention.GetLength();
//			if ( path.Right(curLen) == curExtention) {
//				return TRUE;
//			}
//			else {		//这次在ext提取出来的后缀名和path后缀名不匹配，继续
//				workStr = workStr.Right(workStr.GetLength() - (curLen + 1));
//			}
//		}
//	}
//}
