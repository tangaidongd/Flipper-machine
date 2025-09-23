// CDialogMsgBox.cpp: 实现文件
//

#include "stdafx.h"
#include "fanbanji.h"
#include "CDialogMsgBox.h"
#include "afxdialogex.h"


// CDialogMsgBox 对话框

IMPLEMENT_DYNAMIC(CDialogMsgBox, CDialogEx)

CDialogMsgBox::CDialogMsgBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CUS_MSG, pParent)
{

}

CDialogMsgBox::~CDialogMsgBox()
{
}

void CDialogMsgBox::SetDisplayMsg(CString strMsg)
{
	((CButton*)GetDlgItem(IDC_STATIC_MSG))->SetWindowText(strMsg);
}

void CDialogMsgBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogMsgBox, CDialogEx)
END_MESSAGE_MAP()


// CDialogMsgBox 消息处理程序
