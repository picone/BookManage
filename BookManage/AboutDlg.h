#pragma once
// CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAboutDlg)
public:
	CAboutDlg(CWnd* pParent = NULL);// ��׼���캯��
	virtual ~CAboutDlg();
	enum { IDD = IDD_ABOUTDLG };// �Ի�������
protected:
	virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
};