#include "StdAfx.h"
#include "global.h"

#if !defined(AFX_SESSION_H__BFDCABCE_3ADA_4283_A26D_C4E907032DB5__INCLUDED_)
#define AFX_SESSION_H__BFDCABCE_3ADA_4283_A26D_C4E907032DB5__INCLUDED_

class Session
{
public:
	Session();
	void SessionStart();
	void SessionEnd();
	void SessionRestart();

	bool IsSessionStarted(){return m_step>1;}
	void AddStep(){m_step++;}
	void BackStep(){m_step--;}
	void SkipToPrint(){m_step = 4;}

	//将Session内容保存至数据库
	//第一步至第三步的信息在第4步初始化时刷新，并写入数据库。
	//返回值为sessionid，其实就是数据库中一条交易的ID
	UINT FlushSession();

	//有可能用户选择文件等等后，最终放弃打印，则把之前写入数据库的删除。
	void DeleteSession();

public:
	UINT sessionid;
	//U disks
	int m_udisks;
	CString m_udisk_string;

	//Price And Discount
	float discount_rate;
	float base_price;
	int discount_pages;

	//User Information, 只有在网络打印时才使用
	CString username;
	CString login_time;

	//打印的文件信息;
	CString print_filename;
	CString filepath;
	int filesize;
	
	//打印方式
	bool is_direct_print;
	bool have_previewed;
	bool have_setted;

	//打印进程
	int print_pages;
	int print_copies;
	bool print_all_pages;
	
	float need_pay;
	float have_payed;
	float changed;

	int paymethod;
	bool deal_succeed;

private:
	//在主页step为1，文件查看器step为2，打印设置为3，打印step为4.
	int m_step;
};

#endif