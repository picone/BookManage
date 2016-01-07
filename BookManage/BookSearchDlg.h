#pragma once
#include "afxcmn.h"


// CBookSearchDlg 对话框

class CBookSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBookSearchDlg)
public:
	CBookSearchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBookSearchDlg();
	enum { IDD = IDD_BOOKSEARCHDLG };// 对话框数据
	BTree *tree;
	CMap<CString,LPCTSTR,pBookList,pBookList> *map;
	afx_msg void OnBnClickedSearch();
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
private:
	CString m_author;
	CListCtrl m_list;
};
