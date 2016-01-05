// ShowStructDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BTree.h"
#include "BookManage.h"
#include "ShowStructDlg.h"
#include "afxdialogex.h"

// CShowStructDlg 对话框
IMPLEMENT_DYNAMIC(CShowStructDlg, CDialogEx)

CShowStructDlg::CShowStructDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowStructDlg::IDD, pParent)
{

}

CShowStructDlg::CShowStructDlg(pBTNode T):CDialogEx(CShowStructDlg::IDD)
{
	root=T;
}

CShowStructDlg::~CShowStructDlg()
{
}

void CShowStructDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_tree);
}

BEGIN_MESSAGE_MAP(CShowStructDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CShowStructDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	HTREEITEM btree=m_tree.InsertItem(_T("B树"),0,0);
	DisplayLine(root,btree);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CShowStructDlg::DisplayLine(pBTNode p,HTREEITEM list)
{
	int i;
	CString str;
	if(p!=NULL)
	{
		for(i=1;i<=p->keynum;i++)
		{
			str.Format(_T("%s%d "),str,p->key[i].no);
		}
		if(!str.IsEmpty())list=m_tree.InsertItem(str,0,0,list);
		for(i=0;i<=p->keynum;i++)DisplayLine(p->ptr[i],list);
	}
}
