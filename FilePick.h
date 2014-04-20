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
	CGdipButton m_cBtnPay1;			//��ת��֧���İ�ť
	CGdipButton m_cBtnPreview1;		//��ת���ļ�Ԥ��
	CGdipButton m_cBtnSettings1;	//��ת���ļ���ӡ����
	CGdipButton m_cBtnGoHome1;		//����ҳ

	CListCtrl m_cListFilePick;		//����ӡ�ļ�ѡ��ռ�

	virtual BOOL OnInitDialog();

	void SetButtonBackGrounds(CDC* pDC);				//���ð�ť����
	void SetPicCtlBackGrounds();						//����������ͼ
	void SetOnePicBackGnd(LPCTSTR filepath, UINT ID);	//����һ����ͼ
protected:	
	HBITMAP m_hBitmap;

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedBtnHome();

public:
	CString m_fileExtention;				//�ؼ���ʾ���ļ����ͣ������չ������һ���ַ�����
	CString m_cur_path;						//��ǰ·��
	CString m_sFileNameSelected;			//��ѡ״̬��ѡ�����ļ�
	int m_word_icon;
	int m_folder_icon;
	int m_selected[50];						//�������������һ��ջ�������ѡ״̬����ѡ���ļ����±�
	int m_selected_index;					//ջ����Ŀǰֻ���˵�ѡ����֧�ֶ�ѡ
	BOOL m_bIsMovable;						//�û���������ƶ��豸��ӡô?



	afx_msg void OnPaint();
protected:
	HICON m_hIcon;
public:
	afx_msg void OnBnClickedBtnPreview1();
	afx_msg void OnBnClickedBtnSettings1();
	afx_msg void OnBnClickedBtnPay1();
	void TransferFile(CString path);			//����path�µ��ļ�����ʾ
	afx_msg void OnClickListFilepick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListFilepick(NMHDR *pNMHDR, LRESULT *pResult);
};
