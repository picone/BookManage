#pragma once


// CInputBookDlg 对话框

class CInputBookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInputBookDlg)

public:
	CInputBookDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInputBookDlg();

// 对话框数据
	enum { IDD = IDD_INPUT_BOOK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int book_no;
	CString book_name;
	CString book_author;
	int book_num;
	afx_msg void OnBnClickedOk();
};
