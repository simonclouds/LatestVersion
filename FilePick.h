#pragma once

#include "GdipButton.h"

// CFilePick dialog

class CFilePick : public CDialogEx
{
	DECLARE_DYNAMIC(CFilePick)

public:
	CFilePick(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFilePick();

// Dialog Data
	enum { IDD = IDD_DLG_FILEPICK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CGdipButton m_cBtnPay1;			//跳转到支付的按钮
	CGdipButton m_cBtnPreview1;		//跳转到文件预览
	CGdipButton m_cBtnSettings1;	//跳转到文件打印设置
	CGdipButton m_cBtnGoHome1;		//回主页

	CListCtrl m_cListFilePick;		//待打印文件选择空间

	virtual BOOL OnInitDialog();

	void SetButtonBackGrounds(CDC* pDC);				//设置按钮背景
	void SetPicCtlBackGrounds();						//设置所有贴图
	void SetOnePicBackGnd(LPCTSTR filepath, UINT ID);	//设置一个贴图
protected:	
	HBITMAP m_hBitmap;

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedBtnHome();

public:
	CString m_fileExtention;				//控件显示的文件类型，多个扩展名放在一个字符串中
	CString m_cur_path;						//当前路径
	CString m_sFileNameSelected;			//单选状态，选定的文件
	int m_word_icon;
	int m_folder_icon;
	int m_selected[50];						//这两个变量组成一个栈，保存多选状态下已选中文件的下标
	int m_selected_index;					//栈顶，目前只做了单选，不支持多选
	BOOL m_bIsMovable;						//用户点击的是移动设备打印么?



	afx_msg void OnPaint();
protected:
	HICON m_hIcon;
public:
	afx_msg void OnBnClickedBtnPreview1();
	afx_msg void OnBnClickedBtnSettings1();
	afx_msg void OnBnClickedBtnPay1();
	void TransferFile(CString path);			//查找path下的文件并显示
	afx_msg void OnClickListFilepick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListFilepick(NMHDR *pNMHDR, LRESULT *pResult);
};
