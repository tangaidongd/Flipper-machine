// CDialogFunCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "fanbanji.h"
#include "CDialogFunCfg.h"
#include "afxdialogex.h"


// CDialogFunCfg 对话框

IMPLEMENT_DYNAMIC(CDialogFunCfg, CDialogEx)

CDialogFunCfg::CDialogFunCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogFunCfg::IDD, pParent)
	, m_nOutAdjust(0)
	, m_nInAdjust(0)
	, m_nEnableAdjust(0)
	, m_nInSuccessAdjust(0)
	, m_nNoSignEnableAdjust(0)
	, m_nNoSignAction(0)
	, m_nNoSignAdjustLen(0)
	, m_nAheadRoll(0)
	, m_nOutSuccessAdjust(0)
	, m_nNoSignActionAdjust(0)
	, m_nSensorValid(0)
	, m_nSignSendTime(0)
	, m_bEnableBit5(FALSE)
	, m_bEnableBit6(FALSE)
	, m_bEnableBit7(FALSE)
{
	m_pAnalyzeNetwork = NULL;
}

CDialogFunCfg::~CDialogFunCfg()
{
}

void CDialogFunCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nOutAdjust);
	DDX_Radio(pDX, IDC_RADIO4, m_nInAdjust);
	DDX_Radio(pDX, IDC_RADIO6, m_nEnableAdjust);

	DDX_Radio(pDX, IDC_RADIO12, m_nInSuccessAdjust);
	DDX_Radio(pDX, IDC_RADIO14, m_nNoSignEnableAdjust);
	DDX_Radio(pDX, IDC_RADIO16, m_nNoSignAction);
	DDX_Radio(pDX, IDC_RADIO18, m_nNoSignAdjustLen);
	DDX_Radio(pDX, IDC_RADIO22, m_nAheadRoll);
	DDX_Radio(pDX, IDC_RADIO9, m_nOutSuccessAdjust);
	DDX_Radio(pDX, IDC_RADIO24, m_nNoSignActionAdjust);
	DDX_Radio(pDX, IDC_RADIO26, m_nSensorValid);
	DDX_Radio(pDX, IDC_RADIO28, m_nSignSendTime);
	DDX_Check(pDX, IDC_CHECK1, m_bEnableBit5);
	DDX_Check(pDX, IDC_CHECK78, m_bEnableBit6);
	DDX_Check(pDX, IDC_CHECK79, m_bEnableBit7);
}


BEGIN_MESSAGE_MAP(CDialogFunCfg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SET, &CDialogFunCfg::OnBnClickedBtnSet)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_EXIT, &CDialogFunCfg::OnBnClickedBtnExit)
END_MESSAGE_MAP()


// CDialogFunCfg 消息处理程序


void CDialogFunCfg::UpdateCtrlValue()
{
	if(!m_pAnalyzeNetwork)
		return;

	int nBitIndex = 0;
	unsigned int nTagValue = 0;
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_106, nTagValue);
	m_nOutAdjust = (nTagValue >> nBitIndex++) & 0x00000001;
	m_nInAdjust = (nTagValue >> nBitIndex++) & 0x00000001;
	m_nEnableAdjust = (nTagValue >> nBitIndex++) & 0x00000001;
	m_nSensorValid = (nTagValue >> nBitIndex++) & 0x00000001;
	m_nSignSendTime = (nTagValue >> nBitIndex++) & 0x00000001;
	m_bEnableBit5	= (nTagValue >> nBitIndex++) & 0x00000001;
	m_bEnableBit6 = (nTagValue >> nBitIndex++) & 0x00000001;
	m_bEnableBit7 = (nTagValue >> nBitIndex++) & 0x00000001;

	nBitIndex = 0;
	nTagValue = 0;
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_107, nTagValue);
	m_nOutSuccessAdjust = (nTagValue >> nBitIndex++) & 0x00000001;
	m_nInSuccessAdjust = (nTagValue >> nBitIndex++) & 0x00000001;
	m_nNoSignEnableAdjust = (nTagValue >> nBitIndex++) & 0x00000001;
	m_nNoSignAction = (nTagValue >> nBitIndex++) & 0x00000001;
	m_nNoSignActionAdjust = (nTagValue >> nBitIndex++) & 0x00000001;
	m_nNoSignAdjustLen = (nTagValue >> nBitIndex++) & 0x00000003;
	nBitIndex++;  // m_nNoSignAdjustLen占了两位
	m_nAheadRoll = (nTagValue >> nBitIndex++) & 0x00000001;

	UpdateData(false);
}



void CDialogFunCfg::OnBnClickedBtnSet()
{
	if(!m_pAnalyzeNetwork)
		return;

	UpdateData(true);

	int nBitIndex = 0;
	int nTagValue = 0;
	nTagValue = nTagValue | m_nOutAdjust << nBitIndex++;
	nTagValue = nTagValue | m_nInAdjust << nBitIndex++;
	nTagValue = nTagValue | m_nEnableAdjust << nBitIndex++;
	nTagValue = nTagValue | m_nSensorValid << nBitIndex++;
	nTagValue = nTagValue | m_nSignSendTime << nBitIndex++;
	nTagValue = nTagValue | m_bEnableBit5 << nBitIndex++;
	nTagValue = nTagValue | m_bEnableBit6 << nBitIndex++;
	nTagValue = nTagValue | m_bEnableBit7 << nBitIndex++;

	m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_106, nTagValue);

	nBitIndex = 0;
	nTagValue = 0;
	nTagValue = nTagValue | m_nOutSuccessAdjust << nBitIndex++;
	nTagValue = nTagValue | m_nInSuccessAdjust << nBitIndex++;
	nTagValue = nTagValue | m_nNoSignEnableAdjust << nBitIndex++;
	nTagValue = nTagValue | m_nNoSignAction << nBitIndex++;
	nTagValue = nTagValue | m_nNoSignActionAdjust << nBitIndex++;
	nTagValue = nTagValue | m_nNoSignAdjustLen << nBitIndex++;
	nBitIndex++	;	// 位5-6保存一个数据
	nTagValue = nTagValue | m_nAheadRoll << nBitIndex++;

	m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_107, nTagValue);

	// 同步数据到翻版机主板  
	m_pAnalyzeNetwork->SynchronizeNetworkData(EM_PRO_TAG_106, EM_PRO_TAG_107);
	
}


void CDialogFunCfg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	UpdateCtrlValue();
}




void CDialogFunCfg::OnBnClickedBtnExit()
{
	
}
