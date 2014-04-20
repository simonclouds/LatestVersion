#pragma once
#include "StdAfx.h"

#include "Session.h"
#include "PopupDialog.h"
#include "resource.h"
#include "simon\FileConfig.h"
#include "simon\SysLog.h"
#include "simon\MySQL.h"

#include "Transaction.h"
#include "Environment.h"



#include <time.h>


/** \brief ֧����ʽö��
 */
enum PaymentMethod {PAYBYCOIN=1, PAYBYNOTE=2,PAYBYCARD=4,PAYBYWEIXIN=8,COINNOTE=3,NOTECARD=6,COINCARD=5,NOTECARDCOIN=7};

void GetCurrentTimeStr(char *ts);
const char * GetFilenameFromPath(const char *path);

BOOL CompareExtention(CString path, CString ext);
int GetPagesFromFileName(const CString fileName);
void FindFilesByExtentionForDlg(CString path,CString extention, CListCtrl * list);
CString ScanRemoveable();



//Resource.h����Ҳ�ж��壬ע��
#define		WM_COMM_PRINT		WM_USER+100				//���û�֧���ɹ��󣬷��������Ϣ��PrintPreview�Ե��ô�ӡ����
#define		WM_COMM_CHANGE		WM_USER+101				//��Ͷ��֧���ɹ��󣬷�����Ϣ���Ա�����
#define		WM_COMM_NOTECASHGET	WM_USER+102				//�ڽ���ֽ�ҵĲ�ѯ���߳��У���������ֽ��Ͷ�룬���ʹ���Ϣ

#define		WM_COMM_MONEYACCEPTED	WM_USER+103		//���յ�Ǯ�Һ���ǰ̨�ȴ�֧�����洰�ڷ��͵���Ϣ

#define		WM_CHILDSWITCH		WM_USER+104

/*
	��MainPage�д����л��Ĵ��ڴ��ű�ʾ����
*/
#define		DLG_FILEPICK		0
#define		DLG_PREVIEW			1
#define		DLG_PRINTSETTING	2
#define		DLG_PAY				3

#define		FILENAME_MAXLEN		100

#define		SETTINGERROR_OUTOFRANGE -1
#define		SETTINGERROR_INVALIDCHAR -2
#define		SETTINGERROR_WRONGFORMAT -3
#define		SETTINGERROR_BIGLITTLE -4

#define		IDC_DLG_MYRETURN	1000
