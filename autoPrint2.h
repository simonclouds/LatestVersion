// autoPrint2.h : main header file for the AUTOPRINT2 application
//
#if !defined(AFX_AUTOPRINT2_H__82FB0742_F6B2_4431_BD3B_0838A51C1D30__INCLUDED_)
#define AFX_AUTOPRINT2_H__82FB0742_F6B2_4431_BD3B_0838A51C1D30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif


#include "resource.h"		// main symbols
//#include "global.h"

//#define		WM_COMM_PRINT		WM_USER+100				//���û�֧���ɹ��󣬷��������Ϣ��PrintPreview�Ե��ô�ӡ����
//#define		WM_COMM_CHANGE		WM_USER+101				//��Ͷ��֧���ɹ��󣬷�����Ϣ���Ա�����
//#define		WM_COMM_NOTECASHGET	WM_USER+102				//�ڽ���ֽ�ҵĲ�ѯ���߳��У���������ֽ��Ͷ�룬���ʹ���Ϣ

/////////////////////////////////////////////////////////////////////////////
// CAutoPrint2App:
// See autoPrint2.cpp for the implementation of this class
//

class CAutoPrint2App : public CWinApp
{
public:
	//PrintPreview pp;
//	static BOOL CompareExtention(CString path, CString ext);
//	static int GetPagesFromFileName(const CString fileName);
//	static void FindFilesByExtentionForDlg(CString path,CString extention, CListCtrl * list);
////	CString m_uSelected;
//	static CString ScanRemoveable();
	CAutoPrint2App();
	ULONG_PTR m_gdiplusToken;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoPrint2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAutoPrint2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//globals 
//PrintPreview printPreivewDlg;




#endif // !defined(AFX_AUTOPRINT2_H__82FB0742_F6B2_4431_BD3B_0838A51C1D30__INCLUDED_)
