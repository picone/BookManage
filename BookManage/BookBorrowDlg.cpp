// BookBorrowDlg.cpp : 实现文件
#include "stdafx.h"
#include "BTree.h"
#include "BookManage.h"
#include "BookBorrowDlg.h"
#include "afxdialogex.h"
// CBookBorrowDlg 对话框
IMPLEMENT_DYNAMIC(CBookBorrowDlg, CDialogEx)

CBookBorrowDlg::CBookBorrowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBookBorrowDlg::IDD, pParent)
	, m_name(_T(""))
	, m_num(_T(""))
	, m_no(0)
	, m_date(0)
{

}

CBookBorrowDlg::CBookBorrowDlg(DataType *data):CDialogEx(CBookBorrowDlg::IDD)
{
	book=data;
}

CBookBorrowDlg::~CBookBorrowDlg()
{
}

void CBookBorrowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BOOK_NAME, m_name);
	DDX_Text(pDX, IDC_BOOK_NUM, m_num);
	DDX_Text(pDX, IDC_EDIT2, m_no);
	DDV_MinMaxInt(pDX, m_no, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT1, m_date);
	DDV_MinMaxInt(pDX, m_date, 0, 99991231);
}

BOOL CBookBorrowDlg::OnInitDialog()
{
	SYSTEMTIME sys_time;
	CString str;
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	GetLocalTime(&sys_time);
	now_time=sys_time.wYear*10000+sys_time.wMonth*100+sys_time.wDay;
	m_name=(*book).name;
	str.Format(_T("%d"),(*book).current_num);
	m_num=str;
	m_no=0;
	m_date=now_time;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BEGIN_MESSAGE_MAP(CBookBorrowDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CBookBorrowDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CBookBorrowDlg 消息处理程序
void CBookBorrowDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	Borrow borrow;
	UpdateData();
	if(m_no==0)
	{
		AfxMessageBox(_T("请输入阅读证号"));
		return;
	}
	if(m_date==0)
	{
		AfxMessageBox(_T("请输入归还日期"));
		return;
	}
	borrow.no=m_no;
	borrow.start_time=now_time;
	borrow.end_time=m_date;
	(*book).borrow.push_back(borrow);
	(*book).current_num--;
	CDialogEx::OnOK();
}
