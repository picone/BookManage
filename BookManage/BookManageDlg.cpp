// BookManageDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "BookManage.h"
#include "BookManageDlg.h"
#include "InputBookDlg.h"
#include "ShowStructDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBookManageDlg 对话框
CBookManageDlg::CBookManageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBookManageDlg::IDD, pParent)
	, m_timer(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBookManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOOK, m_list);
	DDX_Text(pDX, IDC_TIMER, m_timer);
}

BEGIN_MESSAGE_MAP(CBookManageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CBookManageDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_INSERT, &CBookManageDlg::OnBnClickedInsert)
	ON_BN_CLICKED(IDC_REFLASH, &CBookManageDlg::OnBnClickedReflash)
	ON_BN_CLICKED(IDC_DELETE, &CBookManageDlg::OnBnClickedDelete)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SHOW_STRUCT, &CBookManageDlg::OnBnClickedShowStruct)
END_MESSAGE_MAP()
// CBookManageDlg 消息处理程序
BOOL CBookManageDlg::OnInitDialog()
{
	CFile file;
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
	/*载入记录*/
	tree=new BTree();
	if(file.Open(_T("record.dat"),CFile::modeRead|CFile::modeNoTruncate|CFile::modeCreate)==TRUE)
	{
		file.SeekToBegin();
		CArchive loader(&file,CArchive::load);
		tree=((BTree*)loader.ReadObject((*tree).GetRuntimeClass()));
		loader.Close();
		OnBnClickedReflash();
	}
	/*初始化日志文件写入指针*/
	log_file.Open(_T("log.txt"),CFile::modeNoTruncate|CFile::modeWrite);
	log_file.SeekToEnd();
	WriteLog(_T("系统启动"));
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
		WriteLog(_T("增加图书")+data.name);
		//插入到B树
		RunTimer timer;
		if((*tree).InsertBTree(data)==OK)
		{
			//插入到ListControl
			EndTime(timer);
			CString s;
			int row=m_list.GetItemCount();
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
			result res=(*tree).SearchBTree(data.no);
			res.pt->key[res.i].current_num+=data.current_num;
			res.pt->key[res.i].total_num+=data.total_num;
			AfxMessageBox(_T("已增加数量"));
			OnBnClickedReflash();
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
	RunTimer timer;
	DisplayList((*tree).GetRoot());
	EndTime(timer);
	m_list.SetRedraw(TRUE);
}

void CBookManageDlg::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos=m_list.GetFirstSelectedItemPosition();
	int row;
	KeyType key;
	if(pos!=NULL)
	{
		row=(int)m_list.GetNextSelectedItem(pos);
		if(row>=0&&AfxMessageBox(_T("你确定要删除")+m_list.GetItemText(row,1)+_T("吗?"),MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
		{
			key=_ttoi(m_list.GetItemText(row,0));
			RunTimer timer;
			if((*tree).DeleteBTree(key)==OK)
			{
				EndTime(timer);
				WriteLog(_T("删除图书")+m_list.GetItemText(row,1));
				m_list.DeleteItem(row);
				AfxMessageBox(_T("删除成功!"));
			}
			else
			{
				AfxMessageBox(_T("删除失败"));
			}
		}
	}
}

void CBookManageDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
	/*把所有记录保存*/
	WriteLog(_T("系统关闭"));
	CFile file(_T("record.dat"),CFile::modeCreate|CFile::modeReadWrite);
	CArchive store(&file,CArchive::store);
	store.WriteObject(tree);
	store.Flush();
	store.Close();
	delete tree;
	log_file.Flush();
	log_file.Close();
}

void CBookManageDlg::EndTime(RunTimer &timer)
{
	timer.end();
	CString s;
	timer.get_str_time(s);
	m_timer=s;
	UpdateData(FALSE);
}

void CBookManageDlg::OnBnClickedShowStruct()
{
	// TODO: 在此添加控件通知处理程序代码
	CShowStructDlg dlg((*tree).GetRoot());
	dlg.DoModal();
}

void CBookManageDlg::WriteLog(LPCTSTR msg)
{
	SYSTEMTIME sys_time;
	CString str;
	GetLocalTime(&sys_time);
	str.Format(_T("%4d年%2d月%2d日 %2d:%2d:%2d %s\r\n"),sys_time.wYear,sys_time.wMonth,sys_time.wDay,sys_time.wHour,sys_time.wMinute,sys_time.wSecond,msg);
	log_file.Write(str,str.GetLength()*sizeof(wchar_t));
}
