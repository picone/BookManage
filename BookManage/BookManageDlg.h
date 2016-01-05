
// BookManageDlg.h : 头文件
//
#pragma once
#include "afxcmn.h"
#include "BTree.h"

// CBookManageDlg 对话框
class CBookManageDlg : public CDialogEx
{
// 构造
public:
	CBookManageDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BOOKMANAGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;// 图书ListView
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedInsert();
private:
	BTree tree;
};
