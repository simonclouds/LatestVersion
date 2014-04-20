#pragma once
#pragma comment(lib, "simon\\lib\\libmysql.lib")
#include "include/mysql.h"

#define FAILED -1
#define SUCCEED 0

class CMysql
{
public:
	CMysql(void);
	~CMysql(void);

	int common_query(char *sentence);	//��ͨ�Ĳ�ѯ
	int select_query(char *sentence, MYSQL_RES **res);
	MYSQL obj_sql;	                    //�������ݿ�����

private:
	char db_name[30];
	char m_user[30];
	char m_password[30];
};

typedef struct Account
{
	char username[50];
	char entrytime[20];

	char filename[255];
	char filepath[255];
	int pages;
	int copies;
	
	int paymentmethod;
	float shouldpay;
	float moneypaid;
	float moneychanged;

	//����
	unsigned char printfinished;
	char exittime[20];
}ACCOUNT, *PAccount;

class CAutoPrintDB: public CMysql
{
public:
	//����˻���������
	int InsertAccount(ACCOUNT account);

	//������֧����Ϣ
	void UpdatePayment(int uid);

	//�������㡢�Ƿ��ӡ��ɡ��˳�ʱ��
	void UpdateDealStatus(int uid);
	
	//ɾ�����׼�¼
	void DeleteAccount(int uid);
};