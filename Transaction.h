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
	CString m_setting_str;						//�����Զ������ô�ӡҳ�淶Χ���ַ���
	unsigned int m_printing_totalpages;			//���ݴ���ӡ����ҳ��
	unsigned int m_printing_copies;				//����ӡ���ĵ��ķ���
	unsigned int m_file_totalpages;				//�����ļ���ҳ��
	float m_base_price;							//��������
	unsigned int m_discount_pages;		//������ʼҳ��
	float m_discount_rate;				//�����ۣ��ۿۼ���
	unsigned int m_transactionId;		//������ˮID
	int m_transactionStatus;			//�����Ƿ�ɹ���������״̬��δ��ɣ���ʱ�����⣬����ȡ��
	
	float m_total_shouldpay;			//�˱ʽ���Ӧ֧���ܶ�
	float m_total_paid;				//�˱ʽ�����֧���ܶ�
	float m_total_coin;				//�˱ʽ��״�Ӳ��Ͷ�һ�ȡ�ܶ�
	float m_total_cash;				//���ֽ�Ͷ���ܶ�
	float m_total_card;				//��ˢ����ȡ�ܶ�
	float m_total_weixin;			//��΢��֧���ܶ�
	float m_change; 					//�����ܶ�

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
	void setTotalShouldPay();			//������ҳ�������ۣ��ۿۼ���
	void setTotalPaid();				//����ÿ���յ�������Ϣ����
	void setCoinTotal(float coinInput);		//Ӳ��Ͷ����Ϣ�¼�handler�е���
	void setCashTotal(float cashInput);		//ֽ��Ͷ����Ϣ�¼�handler�е���
	void setCardTotal(float cardInput);		//ˢ����Ϣ�¼�handler�е���
	void setWeixinTotal(float weixinInput);

	bool enough();						//�ж��Ƿ��Ѹ�������Ӧ�����

	float getChange();					//����Ӧ������Ŀ
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