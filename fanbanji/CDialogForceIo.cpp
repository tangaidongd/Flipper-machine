// CDialogForceIo.cpp : 实现文件
//

#include "stdafx.h"
#include "fanbanji.h"
#include "CDialogForceIo.h"
#include "afxdialogex.h"


// CDialogForceIo 对话框

IMPLEMENT_DYNAMIC(CDialogForceIo, CDialogEx)

CDialogForceIo::CDialogForceIo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogForceIo::IDD, pParent)
	, m_checkIoForceType(0)
{
	m_pAnalyzeNetwork = NULL;

	for (int i = 0; i <  CHECKBOX_FORCE_NUM; ++i)
	{
		m_zForceIOStatus[i].m_clrUnEnableText = RGB(115,115,115);
	}

}

CDialogForceIo::~CDialogForceIo()
{
}

void CDialogForceIo::SetAnalyzeNetwork(CAnalyzeNetwork *pAnalyzeNetwork)
{
	m_pAnalyzeNetwork = pAnalyzeNetwork;
}


void CDialogForceIo::SetCtrlValue2Buf()
{
	// jout1234
	int nIoOut12 = 0;
	for (int i = 0; i < 8; ++i)
	{
		bool bStatus = ((CCusCheckBox*)GetDlgItem(IDC_CHECK34 + i))->GetCheck();
		nIoOut12 = nIoOut12 | bStatus << i;
	}

	int nIoOut34 = 0;
	for (int i = 0; i < 8; ++i)
	{
		bool bStatus = ((CCusCheckBox*)GetDlgItem(IDC_CHECK42 + i))->GetChecked();
		nIoOut34 = nIoOut34 | bStatus << i;
	}

	// 伺服传输旋转
	int nTransAndRotateIO = 0;
	int nIndex = 0;
	bool bStatus = ((CCusCheckBox*)GetDlgItem(IDC_CHECK53))->GetChecked();
	nTransAndRotateIO = nTransAndRotateIO | bStatus<<nIndex++;
	bStatus = ((CCusCheckBox*)GetDlgItem(IDC_CHECK54))->GetChecked();
	nTransAndRotateIO = nTransAndRotateIO | bStatus<<nIndex++;

	bStatus = ((CCusCheckBox*)GetDlgItem(IDC_CHECK58))->GetChecked();
	nTransAndRotateIO = nTransAndRotateIO | bStatus<<nIndex++;
	bStatus = ((CCusCheckBox*)GetDlgItem(IDC_CHECK59))->GetChecked();
	nTransAndRotateIO = nTransAndRotateIO | bStatus<<nIndex++;

	// out5 借用198
	for(int i = 0; i < 4; ++i)
	{
		bool bStatus = ((CCusCheckBox*)GetDlgItem(IDC_CHECK70 + i))->GetChecked();
		nTransAndRotateIO = nTransAndRotateIO | bStatus<<nIndex++;
	}
	
	// 发送服务器
	int nValue195 = m_checkIoForceType + 1;
	if (nValue195 == 1)
	{
		m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_196, nIoOut12);
		m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_197, nIoOut34);
		m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_198, nTransAndRotateIO);

		// 未选择IO强制，将信号归0
		if (nIoOut12 == 0 && nIoOut34 == 0 && nTransAndRotateIO == 0)
		{
			nValue195 = 0;
		}
	}

	m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_195, nValue195);
	
}

void CDialogForceIo::EnableCtrlStatus(int nChoiceType)
{
	bool bEnableCheck = false;
	if (nChoiceType == 0)
		bEnableCheck = true;

	int nCheckIndex = 0;
	for (int i = 0; i < 24 && nCheckIndex < CHECKBOX_FORCE_NUM; ++i)
	{
		m_zForceIOStatus[nCheckIndex].EnableWindow(bEnableCheck);
		m_zForceIOStatus[nCheckIndex].Invalidate();
		nCheckIndex++;
	}

	bool bEnableNetwork = false;
	if (nChoiceType == 3)
		bEnableNetwork = true;

	GetDlgItem(IDC_EDIT_CONNET_NUM)->EnableWindow(bEnableNetwork);
	GetDlgItem(IDC_BTN_NETWORK_START)->EnableWindow(bEnableNetwork);
	GetDlgItem(IDC_BTN_NETWORK_STOP)->EnableWindow(bEnableNetwork);
}

void CDialogForceIo::UpdateCtrlValue()
{
	if(!m_pAnalyzeNetwork)
		return;


	//	IO强制输出1
	unsigned int nValue196 = 0;
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_196, nValue196);

	//	IO强制输出2
	unsigned int nValue197 = 0;
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_197, nValue197);

	//	IO强制输出3
	unsigned int nValue198 = 0;
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_198, nValue198);

	//	IO强制使能
	unsigned int nValue195 = 0;
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_195, nValue195);
	if (nValue195 != 0)
		m_checkIoForceType = nValue195 - 1;
	else
		m_checkIoForceType = 0;

	// jout12
	for (int i = 0; i < 8; ++i)
	{
		bool bStatus = nValue196>>i & 0x00000001;
		((CCusCheckBox*)GetDlgItem(IDC_CHECK34 + i))->SetChecked(bStatus);
	}

	// jout34
	for (int i = 0; i < 8; ++i)
	{
		bool bStatus = nValue197>>i & 0x00000001;
		((CCusCheckBox*)GetDlgItem(IDC_CHECK42 + i))->SetChecked(bStatus);
	}

	// 伺服IO
	int nIndex = 0;
	bool bStatus = (nValue198>>nIndex++) & 0x00000001;
	((CCusCheckBox*)GetDlgItem(IDC_CHECK53))->SetChecked(bStatus);
	bStatus = (nValue198>>nIndex++) & 0x00000001;
	((CCusCheckBox*)GetDlgItem(IDC_CHECK54))->SetChecked(bStatus);
	bStatus = (nValue198>>nIndex++) & 0x00000001;
	((CCusCheckBox*)GetDlgItem(IDC_CHECK58))->SetChecked(bStatus);
	bStatus = (nValue198>>nIndex++) & 0x00000001;
	((CCusCheckBox*)GetDlgItem(IDC_CHECK59))->SetChecked(bStatus);

	// nIndex = 4;
	for(int i = 0; i < 4; ++i)
	{
		bStatus = (nValue198>>nIndex++) & 0x00000001;
		((CCusCheckBox*)GetDlgItem(IDC_CHECK70+i))->SetChecked(bStatus);
	}
}


void CDialogForceIo::SignleAutoRunDisplayIo(bool bIsAuto)
{
	CString strValue;
	// jout5_1
	strValue = bIsAuto ? L"上报切换完成" : L"预留";
	GetDlgItem(IDC_CHECK70)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK70)->Invalidate();

	// jout5_2
	strValue = bIsAuto ? L"收放机切换" : L"预留";
	GetDlgItem(IDC_CHECK71)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK71)->Invalidate();
}

void CDialogForceIo::DoDataExchange(CDataExchange* pDX)
{
	int nCheckIndex = 0;
	for (int i = 0; i < 16 && nCheckIndex < CHECKBOX_FORCE_NUM; ++i)
	{
		DDX_Control(pDX, IDC_CHECK34 + i, m_zForceIOStatus[nCheckIndex++]);
	}
	DDX_Control(pDX, IDC_CHECK53, m_zForceIOStatus[nCheckIndex++]);
	DDX_Control(pDX, IDC_CHECK54, m_zForceIOStatus[nCheckIndex++]);
	DDX_Control(pDX, IDC_CHECK58, m_zForceIOStatus[nCheckIndex++]);
	DDX_Control(pDX, IDC_CHECK59, m_zForceIOStatus[nCheckIndex++]);

	DDX_Control(pDX, IDC_CHECK70, m_zForceIOStatus[nCheckIndex++]);
	DDX_Control(pDX, IDC_CHECK71, m_zForceIOStatus[nCheckIndex++]);
	DDX_Control(pDX, IDC_CHECK72, m_zForceIOStatus[nCheckIndex++]);
	DDX_Control(pDX, IDC_CHECK73, m_zForceIOStatus[nCheckIndex++]);


	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_checkIoForceType);
}


BEGIN_MESSAGE_MAP(CDialogForceIo, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_SET_IO, &CDialogForceIo::OnBnClickedBtnSetIo)
	ON_BN_CLICKED(IDC_RADIO1, &CDialogForceIo::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDialogForceIo::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CDialogForceIo::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CDialogForceIo::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_BTN_NETWORK_START, &CDialogForceIo::OnBnClickedBtnNetworkStart)
	ON_BN_CLICKED(IDC_BTN_NETWORK_STOP, &CDialogForceIo::OnBnClickedBtnNetworkStop)
END_MESSAGE_MAP()



void CDialogForceIo::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	UpdateCtrlValue();

	EnableCtrlStatus(m_checkIoForceType);

	UpdateData(false);
}


void CDialogForceIo::OnBnClickedBtnSetIo()
{
	if(!m_pAnalyzeNetwork)
		return;
	UpdateData(TRUE);

	SetCtrlValue2Buf();

	m_pAnalyzeNetwork->SynchronizeNetworkData(EM_PRO_TAG_195, EM_PRO_TAG_198);
}


void CDialogForceIo::OnBnClickedRadio1()
{
	UpdateData(true);
	EnableCtrlStatus(m_checkIoForceType);
}


void CDialogForceIo::OnBnClickedRadio2()
{
	UpdateData(true);
	EnableCtrlStatus(m_checkIoForceType);
}


void CDialogForceIo::OnBnClickedRadio3()
{
	UpdateData(true);
	EnableCtrlStatus(m_checkIoForceType);
}


BOOL CDialogForceIo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_EDIT_CONNET_NUM)->SetWindowText(L"50");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogForceIo::OnBnClickedRadio4()
{
	UpdateData(true);
	EnableCtrlStatus(m_checkIoForceType);
}


void CDialogForceIo::OnBnClickedBtnNetworkStart()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialogForceIo::OnBnClickedBtnNetworkStop()
{
	// TODO: 在此添加控件通知处理程序代码
}
