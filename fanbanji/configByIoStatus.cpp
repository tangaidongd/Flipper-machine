// configByIoStatus.cpp: 实现文件
//

#include "stdafx.h"
#include "fanbanji.h"
#include "configByIoStatus.h"
#include "afxdialogex.h"
#include "publicFun.h"


// configByIoStatus 对话框

IMPLEMENT_DYNAMIC(CConfigByIoStatus, CDialogEx)

CConfigByIoStatus::CConfigByIoStatus(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IO_STATUS, pParent)
{
	m_nIoStatus = 0;
	m_pSerialPort = NULL;
}


CConfigByIoStatus::CConfigByIoStatus(unsigned int nIoStatus, CSerialPort* pSerialPort, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IO_STATUS, pParent)
{
	m_nIoStatus = nIoStatus;
	m_pSerialPort = pSerialPort;
}

CConfigByIoStatus::~CConfigByIoStatus()
{
}



void CConfigByIoStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	int nCheckIndex = 0;
	for (int i = 0; i < 16; ++i)
	{
		DDX_Control(pDX, IDC_CHECK18 + i, m_zCusCheckBox[nCheckIndex++]);
	}

}


BEGIN_MESSAGE_MAP(CConfigByIoStatus, CDialogEx)
	ON_BN_CLICKED(IDOK, &CConfigByIoStatus::OnBnClickedOk)
END_MESSAGE_MAP()


// configByIoStatus 消息处理程序

bool CConfigByIoStatus::SendIoStatus(unsigned int nIoStatus)
{
	unsigned char zSendBuf[32] = { 0 };
	unsigned char zRevBuf[32] = { 0 };

	zSendBuf[0] = 0xAA;
	zSendBuf[1] = 0x10;
	zSendBuf[2] = nIoStatus & 0xff;
	zSendBuf[3] = nIoStatus>>8 & 0xff;;
	zSendBuf[4] = CalcCrc8(&zSendBuf[1], 3);
	zSendBuf[5] = 0xEE;
	if (m_pSerialPort && m_pSerialPort->IsOpen())
	{
		char zRevData[32] = { 0 };
		int nMaxRev = 6;
		int nRev = m_pSerialPort->SendAndRev(zSendBuf, 6, zRevData, nMaxRev);
		if (nRev != 4)
			return false;

		return TRUE;
	}
	return false;
}

void CConfigByIoStatus::OnBnClickedOk()
{
	if (m_pSerialPort && !m_pSerialPort->IsOpen())
	{
		MessageBox(L"串口未打开");
		return;
	}

	unsigned int nIoStatus = 0;
	for (int i = 0; i < 16; ++i)
	{
		bool bStatus = ((CCusCheckBox*)GetDlgItem(IDC_CHECK18 + i))->GetChecked();
		nIoStatus = nIoStatus | bStatus << i;
	}

	if (!SendIoStatus(nIoStatus))
	{
		MessageBox(L"设置状态失败");
		return;
	}
	
	MessageBox(L"设置状态成功");

	CDialogEx::OnOK();
}




BOOL CConfigByIoStatus::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	for (int i = 0; i < 16; ++i)
	{
		bool bCheck = m_nIoStatus >> i & 0x00001;
		((CCusCheckBox*)GetDlgItem(IDC_CHECK18 + i))->SetChecked(bCheck);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
