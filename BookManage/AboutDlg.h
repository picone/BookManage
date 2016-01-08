#pragma once
// CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAboutDlg)
public:
	CAboutDlg(CWnd* pParent = NULL);// 标准构造函数
	virtual ~CAboutDlg();
	enum { IDD = IDD_ABOUTDLG };// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
};
