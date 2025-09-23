// CDialogIoReplace.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "fanbanji.h"
#include "CDialogIoReplace.h"
#include "afxdialogex.h"


// CDialogIoReplace �Ի���

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


// CDialogIoReplace ��Ϣ�������


void CDialogIoReplace::UpdateCtrlValue()
{
	m_nRadioInput = 0;
	m_nRadioOutput = 0;
	if(m_pAnalyzeNetwork)
	{
		unsigned int nValueInput = 0;
		unsigned int nValueOut = 0;
		// JIN4-4�������IO
		m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_192, nValueInput);
		// JOUT2-2������IO
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
	strValue = bIsAuto ? L"�շŻ������Ӧ" : L"Ԥ��";
	GetDlgItem(IDC_RADIO55)->SetWindowText(strValue);
	
	// jin7_2
	strValue = bIsAuto ? L"�շŻ��������" : L"Ԥ��";
	GetDlgItem(IDC_RADIO56)->SetWindowText(strValue);

	// jin7_3
	strValue = bIsAuto ? L"�շŻ�����" : L"Ԥ��";
	GetDlgItem(IDC_RADIO57)->SetWindowText(strValue);

	// jin7_4
	strValue = bIsAuto ? L"�շŻ����" : L"Ԥ��";
	GetDlgItem(IDC_RADIO58)->SetWindowText(strValue);


	// jout5_1
	strValue = bIsAuto ? L"�ϱ��л����" : L"Ԥ��";
	GetDlgItem(IDC_RADIO63)->SetWindowText(strValue);

	// jout5_2
	strValue = bIsAuto ? L"�շŻ��л�" : L"Ԥ��";
	GetDlgItem(IDC_RADIO64)->SetWindowText(strValue);
}


void CDialogIoReplace::OnBnClickedBtnIoReplace()
{
	if(!m_pAnalyzeNetwork)
		return;

	UpdateData(true);

	if(m_nRadioInput < 0 || m_nRadioInput > 40)
	{
		MessageBox(L"�����ź��������");
		return;
	}

	if(m_nRadioOutput < 0 || m_nRadioOutput > 27)
	{
		MessageBox(L"����ź��������");
		return;
	}

	// JIN4-4�������IO
	m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_192, m_nRadioInput);
	// JOUT2-2������IO
	m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_193, m_nRadioOutput);

	m_pAnalyzeNetwork->SynchronizeNetworkData(EM_PRO_TAG_192, EM_PRO_TAG_193);
}


void CDialogIoReplace::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	UpdateCtrlValue();
}
