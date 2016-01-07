// BookSearchDlg.cpp : 实现文件
#include "stdafx.h"
#include "BTree.h"
#include "BookManage.h"
#include "BookSearchDlg.h"
#include "afxdialogex.h"

// CBookSearchDlg 对话框
IMPLEMENT_DYNAMIC(CBookSearchDlg, CDialogEx)

CBookSearchDlg::CBookSearchDlg(CWnd* pParent /*=NULL*/)
	:CDialogEx(CBookSearchDlg::IDD, pParent)
	, m_author(_T(""))
{

}

CBookSearchDlg::~CBookSearchDlg()
{
}

void CBookSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_AUTHOR, m_author);
	DDX_Control(pDX, IDC_BOOK, m_list);
}

BEGIN_MESSAGE_MAP(CBookSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SEARCH, &CBookSearchDlg::OnBnClickedSearch)
END_MESSAGE_MAP()

BOOL CBookSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0,_T("书号"),LVCFMT_LEFT,100);
	m_list.InsertColumn(1,_T("书名"),LVCFMT_LEFT,110);
	m_list.InsertColumn(2,_T("著者"),LVCFMT_LEFT,100);
	m_list.InsertColumn(3,_T("现存量"),LVCFMT_LEFT,60);
	m_list.InsertColumn(4,_T("总存量"),LVCFMT_LEFT,60);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// CBookSearchDlg 消息处理程序
void CBookSearchDlg::OnBnClickedSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	pBookList p;
	CString s;
	int row;
	DataType data;
	result res;
	UpdateData();
	m_list.DeleteAllItems();
	if(map->Lookup(m_author,p))
	{
		while(p)
		{
			res=tree->SearchBTree(p->no);
			if(res.tag==TRUE)
			{
				data=res.pt->key[res.i];
				row=m_list.GetItemCount();
				s.Format(_T("%d"),data.no);
				m_list.InsertItem(row,s);
				m_list.SetItemText(row,1,data.name);
				m_list.SetItemText(row,2,data.author);
				s.Format(_T("%d"),data.current_num);
				m_list.SetItemText(row,3,s);
				s.Format(_T("%d"),data.total_num);
				m_list.SetItemText(row,4,s);
			}
			p=p->next;
		}
	}
	else
	{
		AfxMessageBox(_T("没有找到该著者"));
	}
}
