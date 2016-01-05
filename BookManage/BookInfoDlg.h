#pragma once
#include "afxcmn.h"
// CBookInfoDlg 对话框
class CBookInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBookInfoDlg)
public:
	CBookInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	CBookInfoDlg(DataType *data);
	virtual ~CBookInfoDlg();
	enum { IDD = IDD_BOOKINFODLG };// 对话框数据
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
private:
	DataType *book;
	int m_no;
	CString m_name;
	CString m_author;
	int m_current_num;
	int m_total_num;
	CListCtrl m_list;
	CString m_ids;
};
