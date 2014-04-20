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


/** \brief 支付方式枚举
 */
enum PaymentMethod {PAYBYCOIN=1, PAYBYNOTE=2,PAYBYCARD=4,PAYBYWEIXIN=8,COINNOTE=3,NOTECARD=6,COINCARD=5,NOTECARDCOIN=7};

void GetCurrentTimeStr(char *ts);
const char * GetFilenameFromPath(const char *path);

BOOL CompareExtention(CString path, CString ext);
int GetPagesFromFileName(const CString fileName);
void FindFilesByExtentionForDlg(CString path,CString extention, CListCtrl * list);
CString ScanRemoveable();



//Resource.h里面也有定义，注意
#define		WM_COMM_PRINT		WM_USER+100				//当用户支付成功后，发送这个消息给PrintPreview以调用打印动作
#define		WM_COMM_CHANGE		WM_USER+101				//当投币支付成功后，发送消息，以便找零
#define		WM_COMM_NOTECASHGET	WM_USER+102				//在接收纸币的查询的线程中，若发现有纸币投入，则发送此消息

#define		WM_COMM_MONEYACCEPTED	WM_USER+103		//接收到钱币后向前台等待支付界面窗口发送的消息

#define		WM_CHILDSWITCH		WM_USER+104

/*
	在MainPage中窗口切换的窗口代号表示定义
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
