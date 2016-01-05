// BookRevertDlg.cpp : 实现文件
#include "stdafx.h"
#include "BTree.h"
#include "BookManage.h"
#include "BookRevertDlg.h"
#include "afxdialogex.h"
// CBookRevertDlg 对话框
IMPLEMENT_DYNAMIC(CBookRevertDlg, CDialogEx)

CBookRevertDlg::CBookRevertDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBookRevertDlg::IDD, pParent)
	, m_no(0)
	, m_name(_T(""))
{

}

CBookRevertDlg::CBookRevertDlg(DataType *data):CDialogEx(CBookRevertDlg::IDD,NULL),m_no(0),m_name(_T(""))
{
	book=data;
}

CBookRevertDlg::~CBookRevertDlg()
{
}

void CBookRevertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BORROW_NO, m_no);
	DDV_MinMaxUInt(pDX, m_no, 0, UINT_MAX);
	DDX_Text(pDX, IDC_BOOK_NAME, m_name);
}

BOOL CBookRevertDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	m_name=(*book).name;
	m_no=0;
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BEGIN_MESSAGE_MAP(CBookRevertDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CBookRevertDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CBookRevertDlg 消息处理程序
void CBookRevertDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL flag=FALSE;
	UpdateData();
	if(m_no==0)
	{
		AfxMessageBox(_T("请输入阅读证号"));
		return;
	}
	for(vector<Borrow>::iterator it=(*book).borrow.begin();it!=(*book).borrow.end();)
	{
		if((*it).no==m_no)
		{
			(*book).borrow.erase(it);
			(*book).current_num++;
			flag=TRUE;
			break;
		}
		else
		{
			it++;
		}
	}
	if(flag)
	{
		AfxMessageBox(_T("归还成功"));
		CDialogEx::OnOK();
	}
	else
	{
		AfxMessageBox(_T("此人没有借书"));
	}
}
