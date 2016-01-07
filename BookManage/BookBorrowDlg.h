#pragma once
// CBookBorrowDlg 对话框
class CBookBorrowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBookBorrowDlg)
public:
	CBookBorrowDlg(CWnd* pParent = NULL);   // 标准构造函数
	CBookBorrowDlg(DataType *data);
	virtual ~CBookBorrowDlg();
	enum { IDD = IDD_BOOKBORROW };// 对话框数据
	afx_msg void OnBnClickedOk();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
private:
	DataType *book;
	CString m_name;
	CString m_num;
	UINT m_no;
	UINT m_date;
	UINT now_time;
};
