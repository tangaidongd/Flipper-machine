// CDialogIoReplace.cpp : 实现文件
//

#include "stdafx.h"
#include "fanbanji.h"
#include "CDialogIoReplace.h"
#include "afxdialogex.h"


// CDialogIoReplace 对话框

IMPLEMENT_DYNAMIC(CDialogIoReplace, CDialogEx)

CDialogIoReplace::CDialogIoReplace(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogIoReplace::IDD, pParent)
	, m_nRadioInput(0)
	, m_nRadioOutput(0)
{

}

CDialogIoReplace::~CDialogIoReplace()
{
}

void CDialogIoReplace::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO49, m_nRadioInput);
	DDX_Radio(pDX, IDC_RADIO50, m_nRadioOutput);
}


BEGIN_MESSAGE_MAP(CDialogIoReplace, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_IO_REPLACE, &CDialogIoReplace::OnBnClickedBtnIoReplace)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CDialogIoReplace 消息处理程序


void CDialogIoReplace::UpdateCtrlValue()
{
	m_nRadioInput = 0;
	m_nRadioOutput = 0;
	if(m_pAnalyzeNetwork)
	{
		unsigned int nValueInput = 0;
		unsigned int nValueOut = 0;
		// JIN4-4替代输入IO
		m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_192, nValueInput);
		// JOUT2-2替代输出IO
		m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_193, nValueOut);

		m_nRadioInput = nValueInput;
		m_nRadioOutput = nValueOut;
	}

	UpdateData(false);
}


void CDialogIoReplace::SignleAutoRunDisplayIo(bool bIsAuto)
{
	CString strValue;
	// jin7_1
	strValue = bIsAuto ? L"收放机出板感应" : L"预留";
	GetDlgItem(IDC_RADIO55)->SetWindowText(strValue);
	
	// jin7_2
	strValue = bIsAuto ? L"收放机出板滚动" : L"预留";
	GetDlgItem(IDC_RADIO56)->SetWindowText(strValue);

	// jin7_3
	strValue = bIsAuto ? L"收放机报警" : L"预留";
	GetDlgItem(IDC_RADIO57)->SetWindowText(strValue);

	// jin7_4
	strValue = bIsAuto ? L"收放机完板" : L"预留";
	GetDlgItem(IDC_RADIO58)->SetWindowText(strValue);


	// jout5_1
	strValue = bIsAuto ? L"上报切换完成" : L"预留";
	GetDlgItem(IDC_RADIO63)->SetWindowText(strValue);

	// jout5_2
	strValue = bIsAuto ? L"收放机切换" : L"预留";
	GetDlgItem(IDC_RADIO64)->SetWindowText(strValue);
}


void CDialogIoReplace::OnBnClickedBtnIoReplace()
{
	if(!m_pAnalyzeNetwork)
		return;

	UpdateData(true);

	if(m_nRadioInput < 0 || m_nRadioInput > 40)
	{
		MessageBox(L"输入信号区间错误");
		return;
	}

	if(m_nRadioOutput < 0 || m_nRadioOutput > 27)
	{
		MessageBox(L"输出信号区间错误");
		return;
	}

	// JIN4-4替代输入IO
	m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_192, m_nRadioInput);
	// JOUT2-2替代输出IO
	m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_193, m_nRadioOutput);

	m_pAnalyzeNetwork->SynchronizeNetworkData(EM_PRO_TAG_192, EM_PRO_TAG_193);
}


void CDialogIoReplace::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	UpdateCtrlValue();
}
