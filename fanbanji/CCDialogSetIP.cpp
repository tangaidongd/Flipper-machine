// CCDialogSetIP.cpp: 实现文件
//
#include "stdafx.h"
#include "fanbanji.h"
#include "CCDialogSetIP.h"
#include "afxdialogex.h"


// CCDialogSetIP 对话框


CCDialogSetIP::CCDialogSetIP(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SET_IP, pParent)
	, m_strPort(_T(""))
{
	m_pAnalyzeNetwork = NULL;
}

CCDialogSetIP::~CCDialogSetIP()
{
}

void CCDialogSetIP::SetAnalyzeNetwork(CAnalyzeNetwork* pAnalyzeNetwork)
{
	m_pAnalyzeNetwork = pAnalyzeNetwork;
}

void CCDialogSetIP::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_strPort);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipAddressCtrl);
}


BEGIN_MESSAGE_MAP(CCDialogSetIP, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCDialogSetIP::OnBnClickedOk)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CCDialogSetIP 消息处理程序


void CCDialogSetIP::OnBnClickedOk()
{
	if (!m_pAnalyzeNetwork)
		return;

	UpdateData(true);
	int nIP1 = 0;
	int nIP2 = 0;
	int nIP3 = 0;
	int nIP4 = 0;

	DWORD dwAddress = 0;

	m_ipAddressCtrl.GetAddress(dwAddress);
	nIP4 = dwAddress & 0xff;
	nIP3 = dwAddress>>8 & 0xff;
	nIP2 = dwAddress >> 16 & 0xff;
	nIP1 = dwAddress >> 24 & 0xff;

	if (nIP1 != 192 || nIP2 != 168)
	{
		MessageBox(L"IP格式为192.168.xxx.xxx");
		return;
	}

	if (nIP4 < 1 || nIP4 > 255)
	{
		MessageBox(L"IP最后位范围1-255");
		return;
	}

	int nPort = _ttoi(m_strPort);
	if (nPort < 1 || nPort > 65535)
	{
		MessageBox(L"端口范围1-65535");
		return;
	}

	m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_185, nIP3);
	m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_186, nIP4);
	m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_187, nPort);
	m_pAnalyzeNetwork->SynchronizeNetworkData(EM_PRO_TAG_186, EM_PRO_TAG_187);

	MessageBox(L"设置IP成功，断电重启生效");
	CDialogEx::OnOK();
}


void CCDialogSetIP::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	unsigned int nIP3;
	unsigned int nIP4;
	CString strPort;
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_185, nIP3);
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_186, nIP4);
	m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_187, strPort);

	m_ipAddressCtrl.SetAddress(BYTE(192), BYTE(168), BYTE(nIP3 & 0xff), BYTE(nIP4 & 0xff));

	m_strPort = strPort;
	UpdateData(false);
}


BOOL CCDialogSetIP::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ipAddressCtrl.SetAddress(BYTE(192), BYTE(168), BYTE(0), BYTE(0));
	m_ipAddressCtrl.SetFieldRange(0, BYTE(0), BYTE(255));
	m_ipAddressCtrl.SetFieldRange(1, BYTE(0), BYTE(255));
	m_ipAddressCtrl.SetFieldRange(2, BYTE(0), BYTE(255));
	m_ipAddressCtrl.SetFieldRange(3, BYTE(0), BYTE(255));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
