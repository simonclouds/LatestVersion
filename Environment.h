#pragma once
class CEnvironment
{
public:
	CEnvironment(void);
	~CEnvironment(void);
private:
	int m_papers_printed;		//已打印纸张数
	int m_papers_last;			//打印机中剩余纸张数
		
	int m_yuan_last;			//找零元剩余数
	int m_jiao_last;			//找零角剩余数

	bool m_ChangerYuanStatus;		//元币找零器状态
	bool m_ChangerJiaoStatus;		//角币找零器状态
	bool m_CoinAcceptorStatus;
	//bool m_CoinJiaoStatus;			//貌似现在投币器可以投1元，5角，1角
	bool m_CardTerminalStatus;				//刷卡器工作状态
	bool m_NoteAcceptorStatus;				//纸币器工作状态

	bool m_NetWorkStatus;			//网络是否联通
	bool m_PrinterStatus;			//打印机是否可用


private:
	//几个外设的串口号字符串：COMn，n表示具体数字
	CString m_COMnStrForChangerYuan;	//
	CString m_COMnStrForChangerJiao;
	CString m_COMnStrForNoteAcceptor;
	CString m_COMnStrForCoinAcceptor;
	CString m_COMnStrForCardTerminal;

private:
	bool m_bNoteAcceptorEnabled;

private:
	//检测网络是否可用，并将m_NetworkStatus赋值
	void checkNetwork();
	//检测打印机是否可用，并赋值m_PrinterStatus
	void checkPrinter();
	
public:
	//设置元币找零剩余量，当每次找零后会减少元币找零的剩余量,这几个变量置于文件中，或者数据库中保存
	void setYuanLast(int yuan);
	void setJiaoLast(int jiao);
	void setPapersLast(int papers);

	bool getNetworkStatus();
	bool getPrinterStatus();
	//预先检测交易是否能完成
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

