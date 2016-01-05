// BookInfoDlg.cpp : 实现文件
#include "stdafx.h"
#include "BTree.h"
#include "BookManage.h"
#include "BookInfoDlg.h"
#include "afxdialogex.h"

// CBookInfoDlg 对话框
IMPLEMENT_DYNAMIC(CBookInfoDlg, CDialogEx)

CBookInfoDlg::CBookInfoDlg(CWnd* pParent /*=NULL*/):CDialogEx(CBookInfoDlg::IDD, pParent)
, m_no(0)
, m_name(_T(""))
, m_author(_T(""))
, m_current_num(0)
, m_total_num(0)
, m_ids(_T(""))
{

}

CBookInfoDlg::CBookInfoDlg(DataType *data):CDialogEx(CBookInfoDlg::IDD,NULL)
, m_no(0)
, m_name(_T(""))
, m_author(_T(""))
, m_current_num(0)
, m_total_num(0)
{
	book=data;
}

CBookInfoDlg::~CBookInfoDlg()
{
}

void CBookInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BOOK_NO, m_no);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_AUTHOR, m_author);
	DDX_Text(pDX, IDC_CUR_NUM, m_current_num);
	DDX_Text(pDX, IDC_TOTAL_NUM, m_total_num);
	DDX_Control(pDX, IDC_LIST_BORROW,m_list);
	DDX_Text(pDX, IDC_BORROW_IDS, m_ids);
}

BOOL CBookInfoDlg::OnInitDialog()
{
	int i=0,min_date=INT_MAX;
	CString s;
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	m_no=(*book).no;
	m_name=(*book).name;
	m_author=(*book).author;
	m_current_num=(*book).current_num;
	m_total_num=(*book).total_num;
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0,_T("阅读证号"),LVCFMT_LEFT,100);
	m_list.InsertColumn(1,_T("借阅时间"),LVCFMT_LEFT,100);
	m_list.InsertColumn(2,_T("归还时间"),LVCFMT_LEFT,100);
	for(vector<Borrow>::iterator it=(*book).borrow.begin();it!=(*book).borrow.end();)
	{
		s.Format(_T("%d"),(*it).no);
		m_list.InsertItem(i,s);
		s.Format(_T("%d"),(*it).start_time);
		m_list.SetItemText(i,1,s);
		s.Format(_T("%d"),(*it).end_time);
		m_list.SetItemText(i,2,s);
		if((*it).end_time<min_date)
		{
			min_date=(*it).end_time;
		}
		it++;
		i++;
	}
	if(min_date<INT_MAX)
	{
		for(vector<Borrow>::iterator it=(*book).borrow.begin();it!=(*book).borrow.end();)
		{
			m_ids.Format(_T("%s%d "),m_ids,(*it).no);
			it++;
		}
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BEGIN_MESSAGE_MAP(CBookInfoDlg, CDialogEx)
END_MESSAGE_MAP()
