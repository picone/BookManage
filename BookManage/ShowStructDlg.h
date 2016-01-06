#pragma once
#include "afxcmn.h"


// CShowStructDlg 对话框

class CShowStructDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShowStructDlg)
public:
	CShowStructDlg(CWnd* pParent = NULL);// 标准构造函数
	CShowStructDlg(pBTNode T);
	virtual ~CShowStructDlg();
	enum { IDD = IDD_SHOWSTRUCT };// 对话框数据
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
private:
	pBTNode root;
	CTreeCtrl m_tree;
	void DisplayLine(pBTNode p,HTREEITEM list);
};
