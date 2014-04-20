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

	//��Session���ݱ��������ݿ�
	//��һ��������������Ϣ�ڵ�4����ʼ��ʱˢ�£���д�����ݿ⡣
	//����ֵΪsessionid����ʵ�������ݿ���һ�����׵�ID
	UINT FlushSession();

	//�п����û�ѡ���ļ��ȵȺ����շ�����ӡ�����֮ǰд�����ݿ��ɾ����
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

	//User Information, ֻ���������ӡʱ��ʹ��
	CString username;
	CString login_time;

	//��ӡ���ļ���Ϣ;
	CString print_filename;
	CString filepath;
	int filesize;
	
	//��ӡ��ʽ
	bool is_direct_print;
	bool have_previewed;
	bool have_setted;

	//��ӡ����
	int print_pages;
	int print_copies;
	bool print_all_pages;
	
	float need_pay;
	float have_payed;
	float changed;

	int paymethod;
	bool deal_succeed;

private:
	//����ҳstepΪ1���ļ��鿴��stepΪ2����ӡ����Ϊ3����ӡstepΪ4.
	int m_step;
};

#endif