#pragma once
class CEnvironment
{
public:
	CEnvironment(void);
	~CEnvironment(void);
private:
	int m_papers_printed;		//�Ѵ�ӡֽ����
	int m_papers_last;			//��ӡ����ʣ��ֽ����
		
	int m_yuan_last;			//����Ԫʣ����
	int m_jiao_last;			//�����ʣ����

	bool m_ChangerYuanStatus;		//Ԫ��������״̬
	bool m_ChangerJiaoStatus;		//�Ǳ�������״̬
	bool m_CoinAcceptorStatus;
	//bool m_CoinJiaoStatus;			//ò������Ͷ��������Ͷ1Ԫ��5�ǣ�1��
	bool m_CardTerminalStatus;				//ˢ��������״̬
	bool m_NoteAcceptorStatus;				//ֽ��������״̬

	bool m_NetWorkStatus;			//�����Ƿ���ͨ
	bool m_PrinterStatus;			//��ӡ���Ƿ����


private:
	//��������Ĵ��ں��ַ�����COMn��n��ʾ��������
	CString m_COMnStrForChangerYuan;	//
	CString m_COMnStrForChangerJiao;
	CString m_COMnStrForNoteAcceptor;
	CString m_COMnStrForCoinAcceptor;
	CString m_COMnStrForCardTerminal;

private:
	bool m_bNoteAcceptorEnabled;

private:
	//��������Ƿ���ã�����m_NetworkStatus��ֵ
	void checkNetwork();
	//����ӡ���Ƿ���ã�����ֵm_PrinterStatus
	void checkPrinter();
	
public:
	//����Ԫ������ʣ��������ÿ�����������Ԫ�������ʣ����,�⼸�����������ļ��У��������ݿ��б���
	void setYuanLast(int yuan);
	void setJiaoLast(int jiao);
	void setPapersLast(int papers);

	bool getNetworkStatus();
	bool getPrinterStatus();
	//Ԥ�ȼ�⽻���Ƿ������
	//bool checkTransactionSuccessful(int papersInPrinting,int yuanChange,int jiaoChange);
	int getPapersLast();
	int getYuanLast();
	int getJiaoLast();

	CString getCOMForChangerYuan();
	CString getCOMForChangerJiao();
	CString getCOMForNoteAcceptor();
	CString getCOMForCoinAcceptor();
	CString getCOMForCardTerminal();

	void SetChangerYuanStatus(bool status);
	void SetChangerJiaoStatus(bool status);
	void SetNoteAcceptorStatus(bool status);
	void SetCoinAcceptorStatus(bool status);
	void SetCardTerminalStatus(bool status);

	void SetNoteAcceptorEnable(bool status);

	bool GetChangerYuanStatus();
	bool GetChangerJiaoStatus();
	bool GetNoteAcceptorStatus();
	bool GetCoinAcceptorStatus();
	bool GetCardTerminalStatus();
	
	bool IsNoteAcceptorEnabled();
};

