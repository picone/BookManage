
// BookManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BookManage.h"
#include "BookManageDlg.h"
#include "InputBookDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBookManageDlg 对话框




CBookManageDlg::CBookManageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBookManageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBookManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOOK, m_list);
}

BEGIN_MESSAGE_MAP(CBookManageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CBookManageDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_INSERT, &CBookManageDlg::OnBnClickedInsert)
	ON_BN_CLICKED(IDC_REFLASH, &CBookManageDlg::OnBnClickedReflash)
END_MESSAGE_MAP()


// CBookManageDlg 消息处理程序

BOOL CBookManageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	/*初始化ListView*/
	//整行选择+显示网格线
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0,_T("书号"),LVCFMT_LEFT,100);
	m_list.InsertColumn(1,_T("书名"),LVCFMT_LEFT,110);
	m_list.InsertColumn(2,_T("著者"),LVCFMT_LEFT,100);
	m_list.InsertColumn(3,_T("现存量"),LVCFMT_LEFT,60);
	m_list.InsertColumn(4,_T("总存量"),LVCFMT_LEFT,60);
	return TRUE;// 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBookManageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBookManageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBookManageDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CBookManageDlg::OnBnClickedInsert()
{
	// TODO: 在此添加控件通知处理程序代码
	CInputBookDlg dlg;
	DataType data;
	if(dlg.DoModal()==IDOK)
	{
		data.no=dlg.book_no;
		data.name=dlg.book_name;
		data.author=dlg.book_author;
		data.current_num=data.total_num=dlg.book_num;
		//插入到B树
		if(tree.InsertBTree(data)==OK)
		{
			//插入到ListControl
			int row=m_list.GetItemCount();
			CString s;
			s.Format(_T("%d"),data.no);
			m_list.InsertItem(row,s);
			m_list.SetItemText(row,1,data.name);
			m_list.SetItemText(row,2,data.author);
			s.Format(_T("%d"),data.current_num);
			m_list.SetItemText(row,3,s);
			s.Format(_T("%d"),data.total_num);
			m_list.SetItemText(row,4,s);
		}
		else
		{
			AfxMessageBox(_T("此书号已存在"));
		}
	}
}

void CBookManageDlg::DisplayList(pBTNode T)
{
	int i,row;
	CString s;
	DataType data;
	if(T!=NULL)
	{
		for(i=1;i<=T->keynum;i++)
		{
			data=T->key[i];
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
		for(i=0;i<=T->keynum;i++)DisplayList(T->ptr[i]);
	}
}


void CBookManageDlg::OnBnClickedReflash()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.SetRedraw(FALSE);
	m_list.DeleteAllItems();
	DisplayList(tree.GetRoot());
	m_list.SetRedraw(TRUE);
}
