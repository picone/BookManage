#pragma once
// CBookRevertDlg 对话框
class CBookRevertDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBookRevertDlg)
public:
	CBookRevertDlg(CWnd* pParent = NULL);   // 标准构造函数
	CBookRevertDlg(DataType *data);
	virtual ~CBookRevertDlg();
	enum { IDD = IDD_BOOKREVERTDLG };// 对话框数据
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
private:
	DataType *book;
	CString m_name;
	UINT m_no;
};
