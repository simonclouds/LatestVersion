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

	int common_query(char *sentence);	//普通的查询
	int select_query(char *sentence, MYSQL_RES **res);
	MYSQL obj_sql;	                    //保存数据库连接

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

	//结束
	unsigned char printfinished;
	char exittime[20];
}ACCOUNT, *PAccount;

class CAutoPrintDB: public CMysql
{
public:
	//针对账户表达操作。
	int InsertAccount(ACCOUNT account);

	//更新已支付信息
	void UpdatePayment(int uid);

	//更新找零、是否打印完成、退出时间
	void UpdateDealStatus(int uid);
	
	//删除交易记录
	void DeleteAccount(int uid);
};