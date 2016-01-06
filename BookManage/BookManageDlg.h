
// BookManageDlg.h : 头文件
//
#pragma once
#include "afxcmn.h"
#include "RunTimer.h"
#include "BTree.h"

// CBookManageDlg 对话框
class CBookManageDlg : public CDialogEx
{
public:
	CBookManageDlg(CWnd* pParent = NULL);// 标准构造函数
	enum { IDD = IDD_BOOKMANAGE_DIALOG };// 对话框数据
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedInsert();
	afx_msg void OnBnClickedReflash();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedShowStruct();
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
private:
	BTree *tree;
	CListCtrl m_list;//图书ListView
	CString m_timer;//计时
	void DisplayList(pBTNode T);
	void EndTime(RunTimer &timer);
};
