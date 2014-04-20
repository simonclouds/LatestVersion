#include "stdafx.h"
#include "Transaction.h"


CTransaction::CTransaction(void)
{
	m_base_price = 0;
	m_change = 0;
	m_discount_pages = 0;
	m_discount_rate = 0;
	//memset(m_file_printing,0,FILENAME_MAXLEN);
	m_file_printing = _T("");
	m_setting_str = _T("");
	m_total_card = 0;
	m_total_cash = 0;
	m_total_coin = 0;
	m_printing_totalpages = 0;
	m_total_paid = 0;
	m_total_shouldpay = 0;
	m_total_weixin = 0;
	m_transactionId = 0;//��ʱ��+u��pid; ʱ��+userId������

	setDiscountPages();
	setDiscountRate();
	setBasePrice();
}


CTransaction::~CTransaction(void)
{
}

static CSysLog sl;
void CTransaction::setPrintingTotalPages( unsigned int pages )
{
	m_printing_totalpages = pages;
}

void CTransaction::setBasePrice()
{
	CFileConfig fc;
	m_base_price = fc.getFloatByString("BasePricePerPage");
}


void CTransaction::setDiscountPages()
{
	CFileConfig fc;
	m_discount_pages = fc.getIntByString("DiscountPages");
}

void CTransaction::setDiscountRate()
{
	CFileConfig fc;
	m_discount_rate = fc.getFloatByString("DiscountRate");
}

void CTransaction::setTotalShouldPay()
{
	//��ӡ��ҳ������������ʼҳ��������ô�������ִ������ۣ�ǰ��ҳ����������
	//��ҳ��= ÿ�ݵ�ҳ��*����
	int totalInAll = m_printing_copies * m_printing_totalpages;
	if (m_discount_pages < totalInAll) {
		m_total_shouldpay = m_discount_pages * m_base_price + \
			(totalInAll - m_discount_pages)*m_base_price*m_discount_rate;
	}
	else {
		m_total_shouldpay = totalInAll * m_base_price;
	}
}

void CTransaction::setTotalPaid()
{
	m_total_paid = m_total_card + m_total_cash + m_total_coin + m_total_weixin;
}


//ע�⣬����ʹ���ļ����ĵط���Ҫʹ�� char filename[FILENAME_MAXLEN]�����Ķ��巽ʽ��
//��Ȼ�˴�Ҫ�������࿽��һЩ��Ч�ַ���
void CTransaction::setFileNamePrinting( CString filename )
{
	//strncpy(m_file_printing,filename,FILENAME_MAXLEN-1);
	m_file_printing = filename;
}

void CTransaction::setCoinTotal( float coinInput )
{
	m_total_coin += coinInput;
}

void CTransaction::setCashTotal( float cashInput )
{
	m_total_cash += cashInput;
}

void CTransaction::setCardTotal( float cardInput )
{
	m_total_card += cardInput;
}

void CTransaction::setWeixinTotal( float weixinInput )
{
	m_total_weixin += weixinInput;
}
//�ж�֧���Ƿ��㹻
bool CTransaction::enough()
{
	if (m_total_shouldpay > m_total_paid)
		return false;
	else 
		return true;
}

float CTransaction::getChange()
{
	if (enough())
		return (m_total_paid - m_total_shouldpay);
	else 
		return (0.0);
}

float CTransaction::getTotalPaid()
{
	return m_total_paid;
}

float CTransaction::getTotalShouldPay()
{
	return m_total_shouldpay;
}

CString CTransaction::getFilenamePrinting()
{
	return m_file_printing;
}

int CTransaction::getPrintingTotalPages()
{
	return m_printing_totalpages;
}

void CTransaction::setFileTotalPages( unsigned int pages )
{
	m_file_totalpages = pages;
}

int CTransaction::getFileTotalPages()
{
	return m_file_totalpages;
}

void CTransaction::setPrintingCopies( unsigned int copies )
{
	m_printing_copies = copies;
}

int CTransaction::getPrintingCopies()
{
	return m_printing_copies;
}

float CTransaction::getBasePrice()
{
	return m_base_price;
}

//�������õ�transaction�����г�Ա�������
void CTransaction::cleanAll()
{
	m_file_printing.Empty();
	m_setting_str.Empty();
	m_file_totalpages = 0;
	m_printing_copies = 0;
	m_printing_totalpages = 0;
	m_total_card = 0;
	m_total_cash = 0;
	m_total_coin = 0;
	m_total_paid = 0;
	m_total_shouldpay = 0;
	m_total_weixin = 0;
	m_transactionId = 0;
}

void CTransaction::setFileSettingStr( CString str )
{
	m_setting_str = str;
}

CString CTransaction::getFileSettingStr()
{
	return m_setting_str;
}

bool CTransaction::CheckFileStringStrValidation()
{
	if ((!m_setting_str.IsEmpty()) && (m_printing_totalpages == 0))
		return false;
	else
		return true;
}


