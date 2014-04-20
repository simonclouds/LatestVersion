#include "StdAfx.h"
#include "MySQL.h"
#include "FileConfig.h"
#include "SysLog.h"

CMysql::CMysql(void)
{
	//初始化对象
	mysql_init(&obj_sql);

	//初始化用户名和密码
	CFileConfig cf;
	memset(m_user, 0, 30);
	memset(m_password, 0, 30);
	memset(db_name, 0, 30);
	cf.getStringByString("USERNAME", m_user);
	cf.getStringByString("PASSWORD", m_password);
	cf.getStringByString("DATABASE", db_name);
	//m_res_ptr = NULL;

	//设置字符集
	int ret=mysql_options(&obj_sql,MYSQL_SET_CHARSET_NAME,"gb2312");

	if(ret==0)
		WRITE_LOG("MySQL options success!");
	else
		WRITE_LOG("Options failed!");
	//默认连接某数据库
	//connect(db_name);
	if(mysql_real_connect(&obj_sql,NULL,m_user,m_password,db_name,0,NULL,0))
	{
		WRITE_LOG("connect to database succeed");
	}
	else
	{
		const char* error_code=0;
		error_code=mysql_error(&obj_sql);
		char error[200];
		sprintf(error, "failed to connect database and Error Code:%s\n",error_code);
		WRITE_LOG(error);
	}
}


CMysql::~CMysql(void)
{
	mysql_close(&obj_sql);
}

int CMysql::common_query(char *sentence)
{
	//这里有时会抛出异常。。
	int ret = mysql_real_query(&obj_sql, sentence, strlen(sentence));
	if(ret == 0)
	{
		return SUCCEED;
	}
	else
	{
		const char* error_code=0;
		error_code=mysql_error(&obj_sql);
		char error[100];
		sprintf(error, "Error Code:%d\n", error_code);

		WRITE_LOG("Failed to query in common_query");
		WRITE_LOG(sentence);
		WRITE_LOG(error);

		return FAILED;
	}
}

int CMysql::select_query(char *sentence, MYSQL_RES **res)
{
	//查询
	int len = strlen(sentence);
	unsigned long ret;

	ret=mysql_real_query(&obj_sql,sentence,len);
	if(ret!=0)
	{
		//_asm int 3;
		const char* error_code=0;
		error_code=mysql_error(&obj_sql);
		char error[100];
		sprintf(error, "Error Code:%d\n", error_code);

		WRITE_LOG("Failed to query in query_select\t");
		WRITE_LOG(sentence);
		WRITE_LOG(error);

		return FAILED;
	}

	//获取查询结果
	*res=mysql_store_result(&obj_sql);

	if(*res)
	{
		ret = (unsigned long)mysql_num_rows(*res);  //行数
		return ret;
	}
}


int CAutoPrintDB::InsertAccount(ACCOUNT account)
{
	/*CString sql = "insert into accounts(username,entrytime,filename,filepath \
	,pages,copies,paymentmethod,shouldpay,moneypaid,moneychanged,printfinished,exittime)values(";

*/
	return 1;

}

//更新已支付信息
void CAutoPrintDB::UpdatePayment(int uid)
{

}
//更新找零、是否打印完成、退出时间
void CAutoPrintDB::UpdateDealStatus(int uid)
{

}	
//删除交易记录
void CAutoPrintDB::DeleteAccount(int uid)
{

}