#include "StdAfx.h"
#include "Session.h"

Session::Session()
{
	m_step = 1;
	SessionRestart();
}

void Session::SessionStart()
{
	m_step=2; 
	GetCurrentTime(&login_time);
}

void Session::SessionEnd()
{
	FlushSession();
}

void Session::SessionRestart()
{
	
	CFileConfig fc;
	discount_rate = fc.getFloatByString("DiscountRate");
	//discount_pages = fc.getIntByString("DiscountPages");
	base_price = fc.getFloatByString("BasePricePerPage");

	username = "";
	login_time = "";

	//打印的文件信息;
	print_filename = "";
	filepath = "";
	filesize = 0;
	
	//打印方式
	is_direct_print = false;
	have_previewed = false;
	have_setted = false;

	//打印进程
	print_pages = 0;
	print_copies = 0;
	print_all_pages = false;
	
	need_pay = 0.0;
	have_payed = 0.0;
	changed = 0.0;

	paymethod = PAYBYCOIN;
	deal_succeed = false;
}

UINT Session::FlushSession()
{
	//CString sql = "insert into"
	return 1;
}