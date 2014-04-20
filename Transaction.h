#pragma once
#include "global.h"
#include "stdafx.h"
class CTransaction
{
public:
	CTransaction(void);
	~CTransaction(void);
private:
	CString m_file_printing;	
	CString m_setting_str;						//保存自定义设置打印页面范围的字符串
	unsigned int m_printing_totalpages;			//单份待打印的总页数
	unsigned int m_printing_copies;				//待打印的文档的份数
	unsigned int m_file_totalpages;				//整个文件的页数
	float m_base_price;							//基础单价
	unsigned int m_discount_pages;		//打折起始页数
	float m_discount_rate;				//若打折，折扣几何
	unsigned int m_transactionId;		//交易流水ID
	int m_transactionStatus;			//交易是否成功，或其他状态，未完成，超时，意外，，，取消
	
	float m_total_shouldpay;			//此笔交易应支付总额
	float m_total_paid;				//此笔交易已支付总额
	float m_total_coin;				//此笔交易从硬币投币获取总额
	float m_total_cash;				//从现金投入总额
	float m_total_card;				//从刷卡获取总额
	float m_total_weixin;			//从微信支付总额
	float m_change; 					//找零总额

private:
	void setBasePrice();
	void setDiscountPages();
	void setDiscountRate();

public:
	void setPrintingTotalPages(unsigned int pages);
	void setFileTotalPages(unsigned int pages);
	void setPrintingCopies(unsigned int copies);
	void setFileNamePrinting(CString filename);
	void setFileSettingStr(CString str);
	void setTotalShouldPay();			//根据总页数，单价，折扣计算
	void setTotalPaid();				//根据每次收到入账消息更新
	void setCoinTotal(float coinInput);		//硬币投入消息事件handler中调用
	void setCashTotal(float cashInput);		//纸币投入消息事件handler中调用
	void setCardTotal(float cardInput);		//刷卡消息事件handler中调用
	void setWeixinTotal(float weixinInput);

	bool enough();						//判断是否已付金额大于应付金额

	float getChange();					//返回应找零数目
	float getTotalShouldPay();
	float getTotalPaid();
	CString getFilenamePrinting();
	CString getFileSettingStr();
	bool CheckFileStringStrValidation();
	int getPrintingTotalPages();
	int getFileTotalPages();
	int getPrintingCopies();
	float getBasePrice();
	void cleanAll();
};