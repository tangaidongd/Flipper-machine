// dataByPollingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "fanbanji.h"
#include "dataByPollingDlg.h"
#include "afxdialogex.h"
#include "AlarmLog.h"


// CDataByPollingDlg 对话框

#define  MS_UINT   0.65					// ms的一般单位
#define  MS_UINT_SPECIAL 0.69			// ms的一般单位
#define  DEF_PRECISION   0.5			// 精确度调整

IMPLEMENT_DYNAMIC(CDataByPollingDlg, CDialogEx)

CDataByPollingDlg::CDataByPollingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataByPollingDlg::IDD, pParent)
{
	m_pSerialThread = NULL;
	m_pSerialPort = NULL;
	m_pAnalyzeProtocol = NULL;
	m_vIoStatus.clear();
	m_vInputStatus.clear();
	m_vOutPutStatus.clear();
	m_vAlarmLog.clear();
}

CDataByPollingDlg::~CDataByPollingDlg()
{
	
}

//void CDataByPollingDlg::StartPolling()
//{
//	if(m_pSerialPort && m_pSerialPort->IsOpen())
//	{
//		m_pSerialThread = new CSerialThread();
//		//m_pSerialThread = (CSerialThread*)AfxBeginThread(RUNTIME_CLASS(CSerialThread), THREAD_PRIORITY_NORMAL, NULL, CREATE_SUSPENDED);
//		m_pSerialThread->CreateThread(CREATE_SUSPENDED);
//		m_pSerialThread->SetRunStatus(TRUE);
//		m_pSerialThread->SetSerialDev(m_pSerialPort);
//		m_pSerialThread->SetParentHand(GetSafeHwnd());
//		m_pSerialThread->SetPutSerialDataPoint(&m_PutSerialData);
//		// 计数为0会自动释放
//		//m_pSerialThread->m_bAutoDelete;
//		m_pSerialThread->ResumeThread();
//	}
//}

//void CDataByPollingDlg::StopPolling()
//{
//	if(m_pSerialThread)
//	{
//		m_pSerialThread->SetRunStatus(FALSE);
//		m_pSerialThread = NULL;
//	}
//	
//}

void CDataByPollingDlg::SetSerialPort(CSerialPort* pSerialPort)
{
	if (pSerialPort)
	{
		m_pSerialPort = pSerialPort;		
	}
	
}

void CDataByPollingDlg::SetSerialThread(CSerialThread* pSerialThread)
{
	if (pSerialThread)
	{
		m_pSerialThread = pSerialThread;
	}
}

void CDataByPollingDlg::SetAnalyzeProtocol(CAnalyzeProtocol* pAnalyzeProtocol)
{
	if (pAnalyzeProtocol)
	{
		m_pAnalyzeProtocol = pAnalyzeProtocol;
	}
}


void CDataByPollingDlg::GetControlValue(std::map<int, STCFData>& mapConfigData)
{
	// 获取控件值
	CString strValue1, strValue2, strValue3;
	STCFData stCFData;
	((CStatic*)GetDlgItem(IDC_STATIC_ROLL1))->GetWindowTextW(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_ROLL2))->GetWindowTextW(strValue2);
	((CStatic*)GetDlgItem(IDC_STATIC_ROLL3))->GetWindowTextW(strValue3);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_ROLL_SPEED;
	stCFData.strCFName = "入/出滚轮速度";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	stCFData.vCmdValue.push_back(_ttoi(strValue2));
	stCFData.vCmdValue.push_back(_ttoi(strValue3));
	mapConfigData[EM_WRITE_ROLL_SPEED] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_ACTION1))->GetWindowTextW(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_ACTION2))->GetWindowTextW(strValue2);
	((CStatic*)GetDlgItem(IDC_STATIC_ACTION3))->GetWindowTextW(strValue3);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_ACTION_TIME;
	stCFData.strCFName = "各动作时间";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	stCFData.vCmdValue.push_back(_ttoi(strValue2));
	stCFData.vCmdValue.push_back(_ttoi(strValue3));
	mapConfigData[EM_WRITE_ACTION_TIME] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_FLIP1))->GetWindowTextW(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_FLIP2))->GetWindowTextW(strValue2);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_FLIP_SPEED;
	stCFData.strCFName = "翻转速度";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	stCFData.vCmdValue.push_back(_ttoi(strValue2));
	mapConfigData[EM_WRITE_FLIP_SPEED] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_PULSES1))->GetWindowTextW(strValue1);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_PULSES_COUNT;
	stCFData.strCFName = "快速翻转角度（回板脉冲）";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	mapConfigData[EM_WRITE_PULSES_COUNT] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_DELAY1))->GetWindowTextW(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_DELAY2))->GetWindowTextW(strValue2);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_COMPLETE_SIGNAL_DELAY;
	stCFData.strCFName = "入板开始/出板完成信号延时";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	stCFData.vCmdValue.push_back(_ttoi(strValue2));
	mapConfigData[EM_WRITE_COMPLETE_SIGNAL_DELAY] = stCFData;
}

void CDataByPollingDlg::SetControlValue(std::map<int, STCFData>& mapConfigData)
{
	for (auto iter = mapConfigData.begin(); iter != mapConfigData.end(); ++iter)
	{
		switch(iter->first)
		{
		case EM_WRITE_ROLL_SPEED:
			if (iter->second.vCmdValue.size() > 2)
			{
				SendRoll(iter->second.vCmdValue.at(0), iter->second.vCmdValue.at(1), iter->second.vCmdValue.at(2), false);
			}
			break;
		case EM_WRITE_FLIP_SPEED:
			if (iter->second.vCmdValue.size() > 1)
			{
				SendFlip(iter->second.vCmdValue.at(0), iter->second.vCmdValue.at(1), false);
			}
			break;
		case EM_WRITE_PULSES_COUNT:
			if (iter->second.vCmdValue.size() > 0)
			{
				SentPulses(iter->second.vCmdValue.at(0), false);
			}
			break;
		case EM_WRITE_ACTION_TIME:
			if (iter->second.vCmdValue.size() > 2)
			{
				SentAction(iter->second.vCmdValue.at(0), iter->second.vCmdValue.at(1), iter->second.vCmdValue.at(2), false);
			}
			break;
		case EM_WRITE_COMPLETE_SIGNAL_DELAY:
			if (iter->second.vCmdValue.size() > 1)
			{
				SentDelay(iter->second.vCmdValue.at(0), iter->second.vCmdValue.at(1), false);
			}
			break;
		default:
			break;
		}
	}
}

void CDataByPollingDlg::RefreshControlValue()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_ROLL_SPEED);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_ACTION_TIME);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_FLIP_SPEED);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_COMPLETE_SIGNAL_DELAY);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_PULSES_COUNT);
	}
}

void CDataByPollingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_CONTROL1, m_checkboxControl1);
	DDX_Control(pDX, IDC_CHECK_STATUS1, m_checkboxStatus);
	//DDX_Control(pDX, IDC_CHECK33, m_cusCheckBox33);
	//DDX_Control(pDX, IDC_CHECK32, m_cusCheckBox32);

	int nCheckIndex = 0;
	for (int i = 0; i < CHECKBOX_NUM; ++i)
	{
		DDX_Control(pDX, IDC_CHECK2 + i, m_zCusCheckBox[nCheckIndex++]);
	}
}

BEGIN_MESSAGE_MAP(CDataByPollingDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON13, &CDataByPollingDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BTN_ROLL1, &CDataByPollingDlg::OnBnClickedBtnRoll1)
	ON_BN_CLICKED(IDC_BTN_FLIP1, &CDataByPollingDlg::OnBnClickedBtnFlip1)
	ON_BN_CLICKED(IDC_BTN_PULSES1, &CDataByPollingDlg::OnBnClickedBtnPulses1)
	ON_BN_CLICKED(IDC_BTN_ACTION1, &CDataByPollingDlg::OnBnClickedBtnAction1)
	ON_BN_CLICKED(IDC_BTN_DELAY1, &CDataByPollingDlg::OnBnClickedBtnDelay1)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK_CONTROL1, &CDataByPollingDlg::OnBnClickedCheckControl1)
	ON_BN_CLICKED(IDC_BTN_ROLL_REFRESH, &CDataByPollingDlg::OnBnClickedBtnRollRefresh)
	ON_BN_CLICKED(IDC_BTN_ACTION_REFRESH, &CDataByPollingDlg::OnBnClickedBtnActionRefresh)
	ON_BN_CLICKED(IDC_BTN_FLIB_REFRESH, &CDataByPollingDlg::OnBnClickedBtnFlibRefresh)
	ON_BN_CLICKED(IDC_BTN_DELAY_REFRESH, &CDataByPollingDlg::OnBnClickedBtnDelayRefresh)
	ON_BN_CLICKED(IDC_BTN_PULESE_REFRESH, &CDataByPollingDlg::OnBnClickedBtnPuleseRefresh)
	ON_BN_CLICKED(IDC_CHECK_STATUS1, &CDataByPollingDlg::OnBnClickedCheckStatus1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDataByPollingDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CDataByPollingDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CDataByPollingDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CDataByPollingDlg::OnBnClickedButtonRefresh)
	// 增加一个修改颜色
	ON_BN_CLICKED(IDC_BTN_IO_STATUS, &CDataByPollingDlg::OnBnClickedBtnIoStatus)
	ON_BN_CLICKED(IDC_BTN_CLEAN, &CDataByPollingDlg::OnBnClickedBtnClean)
END_MESSAGE_MAP()


// CDataByPollingDlg 消息处理程序


void CDataByPollingDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	int a = 10;
	// TODO: 在此处添加消息处理程序代码
}

void  CDataByPollingDlg::OnRevCmdMsg(STComData& stComData)
{
	// 校验包数据
	if (!m_pAnalyzeProtocol->CheckRevCmd(stComData))
	{
		return;
	}

	switch(stComData.chTag)
	{
	case EM_SHAKE_HANDS:
		ShkeHands(stComData);
		break;
	case EM_QUERY_VERSION:
		QueryVersion(stComData);
		break;
	case EM_QUERY_INPUT:
		QueryInput(stComData);
		break;
	case EM_QUERY_OUTPUT:
		QueryOutput(stComData);
		break;
	case EM_QUERY_IO_STATUS:
		QueryIoStatus(stComData);
		break;
	case EM_QUERY_WORK_STATUS:
		QueryWorkStatus(stComData);
		break;
	case EM_QUERY_ROLL_SPEED:
		QueryRollSpeed(stComData);
		break;
	case EM_QUERY_FLIP_SPEED:
		QueryFlipSpeed(stComData);
		break;
	case EM_QUERY_PULSES_COUNT:
		QueryPulsesCount(stComData);
		break;
	case EM_QUERY_ACTION_TIME:
		QueryActionTime(stComData);
		break;
	case EM_QUERY_COMPLETE_SIGNAL_DELAY:
		QueryCompleteSignalDelay(stComData);
		break;
	case EM_QUERY_LAST_TIME_CONSUMING:
		QueryLastTimeConsuming(stComData);
		break;
	case EM_QUERY_ALARM_NUM:
		QueryAlarmNum(stComData);
		break;
	case EM_QUERY_ALARM_LOG:
		//QueryAlarmLog(stComData);
		break;
	default:
		break;
	}

	// 转换结果方便查看
	/*u8 zRevDataFinal[MAX_DATA_LEN*2] = {0};
	u8* pRevDataFinal = zRevDataFinal;
	Hex2Str((u8*)stComData.zData, &pRevDataFinal, stComData.nDataLen);
	CStringA strRevA = (char*)zRevDataFinal;
	strRevA = "\r\n" + strRevA;
	OutputDebugStringA(strRevA);*/
}	




void CDataByPollingDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDataByPollingDlg::InitControlPoint()
{
	// io输入状态
	for (int i = 0; i < 16; ++i)
	{
		CCusCheckBox* pIoStatus = (CCusCheckBox*)GetDlgItem(IDC_CHECK2 + i);
		pIoStatus->EnableWindow(FALSE);
		m_vInputStatus.push_back(pIoStatus);
	}

	// io输出状态
	for (int i = 0; i < 16; ++i)
	{
		CCusCheckBox* pIoStatus = (CCusCheckBox*)GetDlgItem(IDC_CHECK18 + i);
		pIoStatus->EnableWindow(FALSE);
		m_vOutPutStatus.push_back(pIoStatus);
	}

	// 伺服IO状态
	for (int i = 0; i < 16; ++i)
	{
		CCusCheckBox* pIoStatus = (CCusCheckBox*)GetDlgItem(IDC_CHECK34 + i);
		pIoStatus->EnableWindow(FALSE);
		m_vIoStatus.push_back(pIoStatus);
	}
}

void CDataByPollingDlg::ShkeHands(STComData &stComData)
{
	static int nHanks = 1;
	nHanks = nHanks++%3;

	CString strHand;
	strHand.Format(_T("%d"), nHanks);
	((CStatic*)GetDlgItem(IDC_STATIC_HAND))->SetWindowText(strHand); 
}

void CDataByPollingDlg::QueryVersion(STComData &stComData)
{
	// 查询版本
	u8* pRealData = stComData.zData + 2;
	CString strVersion;
	int nVersion =  (pRealData[0]& 0x00ff);
	int nFuncVersion = (pRealData[1]&0x00ff);
	strVersion.Format(_T("%02x  %02x"), nVersion, nFuncVersion);

	((CStatic*)GetDlgItem(IDC_STATIC_VERSION))->SetWindowText(strVersion);
}

void CDataByPollingDlg::QueryInput(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u8 chInput1 = pRealData[0];
	u8 chInput2 = pRealData[1];

	for (int i = 0; i < 8; ++i)
	{
		u32 nValue = (chInput1>>(7-i)) & 0x01;
		m_vInputStatus.at(i)->SetChecked(nValue);
	}

	for (int i = 8; i < 16; ++i)
	{
		u32 nValue = (chInput2>>(15-i)) & 0x01;
		m_vInputStatus.at(i)->SetChecked(nValue);
	}
}

void CDataByPollingDlg::QueryOutput(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u8 chInput1 = pRealData[0];
	u8 chInput2 = pRealData[1];

	for (int i = 0; i < 8; ++i)
	{
		u32 nValue = (chInput1>>(7-i)) & 0x01;
		m_vOutPutStatus.at(i)->SetChecked(nValue);
	}

	for (int i = 8; i < 16; ++i)
	{
		u32 nValue = (chInput2>>(15-i)) & 0x01;
		m_vOutPutStatus.at(i)->SetChecked(nValue);
	}
}

void CDataByPollingDlg::QueryIoStatus(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u8 chInput1 = pRealData[0];
	u8 chInput2 = pRealData[1];

	for (int i = 0; i < 8; ++i)
	{
		u32 nValue = (chInput1>>(7-i)) & 0x01;
		m_vIoStatus.at(i)->SetChecked(nValue);
	}

	for (int i = 8; i < 16; ++i)
	{
		u32 nValue = (chInput2>>(15-i)) & 0x01;
		m_vIoStatus.at(i)->SetChecked(nValue);
	}
}

void CDataByPollingDlg::QueryWorkStatus(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u8 chInput1 = pRealData[0];
	u8 chInput2 = pRealData[1];
	u8 chInput3 = pRealData[2];

	u32 nInput1 = chInput1&0xff;
	u32 nInput2 = chInput2&0xff;
	u32 nInput3 = chInput3&0xff;

	CString strCurStatus = m_pAnalyzeProtocol->GetWorkStatus(nInput1);
	CString strProStatus = m_pAnalyzeProtocol->GetWorkStatus(nInput2);
	CString strErrorStatus = m_pAnalyzeProtocol->GetWorkStatus(nInput3, true);

	((CStatic*)GetDlgItem(IDC_STATIC_WORK1))->SetWindowText(strCurStatus);
	((CStatic*)GetDlgItem(IDC_STATIC_WORK2))->SetWindowText(strProStatus);
	((CStatic*)GetDlgItem(IDC_STATIC_WORK3))->SetWindowText(strErrorStatus);
}

void CDataByPollingDlg::QueryRollSpeed(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u32 nRollSpeed1 = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);
	u32 nRollSpeed2 = (pRealData[2]<<8 & 0xffff) | (pRealData[3]&0xffff);
	u32 nRollSpeed3 = (pRealData[4]<<8 & 0xffff) | (pRealData[5]&0xffff);

	// 速度计算公式：3150/V （V为滚轮速度单位1m/s，默认入板9m/s，出板16m/s）速度取值范围3m/s-35m/s，
	// 对应写入值1050-90，值小于90则按90写入。（两字节采取大端格式）
	if (nRollSpeed1 != 0)
	{
		CString strValue1;
		strValue1.Format(_T("%d"), 3150/nRollSpeed1);
		((CStatic*)GetDlgItem(IDC_STATIC_ROLL1))->SetWindowText(strValue1);
		((CStatic*)GetDlgItem(IDC_EDIT_ROLL1))->SetWindowText(strValue1);
	}
	if (nRollSpeed2 != 0)
	{
		CString strValue2;
		strValue2.Format(_T("%d"), 3150/nRollSpeed2);
		((CStatic*)GetDlgItem(IDC_STATIC_ROLL2))->SetWindowText(strValue2);
		((CStatic*)GetDlgItem(IDC_EDIT_ROLL2))->SetWindowText(strValue2);
	}
	if (nRollSpeed3 != 0)
	{
		CString strValue3;
		strValue3.Format(_T("%d"), 3150/nRollSpeed3);
		((CStatic*)GetDlgItem(IDC_STATIC_ROLL3))->SetWindowText(strValue3);
		((CStatic*)GetDlgItem(IDC_EDIT_ROLL3))->SetWindowText(strValue3);
	}
}

void CDataByPollingDlg::QueryFlipSpeed(STComData &stComData)
{
	// 读取上来的数据是小端格式
	u8* pRealData = stComData.zData + 2;
	u32 nFlip1 = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);
	u32 nFlip2 = (pRealData[2]<<8 & 0xffff) | (pRealData[3]&0xffff);

	// 速度计算公式：3150/V （V为滚轮速度单位1m/s，默认入板9m/s，出板16m/s）速度取值范围3m/s-35m/s，
	// 对应写入值1050-90，值小于90则按90写入。（两字节采取大端格式）
	if (nFlip1 != 0)
	{
		CString strValue1;
		strValue1.Format(_T("%d"), 33720/nFlip1);
		((CStatic*)GetDlgItem(IDC_STATIC_FLIP1))->SetWindowText(strValue1);
		((CStatic*)GetDlgItem(IDC_EDIT_FLIP1))->SetWindowText(strValue1);
	}
	if (nFlip2 != 0)
	{
		CString strValue2;
		strValue2.Format(_T("%d"), 33720/nFlip2);
		((CStatic*)GetDlgItem(IDC_STATIC_FLIP2))->SetWindowText(strValue2);
		((CStatic*)GetDlgItem(IDC_EDIT_FLIP2))->SetWindowText(strValue2);
	}
}

void CDataByPollingDlg::QueryPulsesCount(STComData &stComData)
{
	// 读取上来的数据是小端格式
	u8* pRealData = stComData.zData + 2;
	u32 nRollSpeed1 = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);

	// 回板0.65为单位，翻版0.69为单位
	nRollSpeed1 = nRollSpeed1*MS_UINT_SPECIAL + DEF_PRECISION;

	// 回板脉冲用于板脱离传感器后，继续走的距离。默认100单位，按需要在0-250调整；翻板的快速脉冲数，以1°为单位，取值90-180
	CString strValue1, strValue2;
	strValue1.Format(_T("%d"), nRollSpeed1);
	((CStatic*)GetDlgItem(IDC_STATIC_PULSES1))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_EDIT_PULSES1))->SetWindowText(strValue1);
}

void CDataByPollingDlg::QueryActionTime(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u32 nAction1 = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);
	u32 nAction2 = (pRealData[2]<<8 & 0xffff) | (pRealData[3]&0xffff);
	u32 nAction3 = (pRealData[4]<<8 & 0xffff) | (pRealData[5]&0xffff);

	// 单位换算
	nAction1 = nAction1*MS_UINT + DEF_PRECISION;
	nAction2 = nAction2*MS_UINT + DEF_PRECISION;
	nAction3 = nAction3*MS_UINT + DEF_PRECISION;

	CString strValue1, strValue2, strValue3;
	strValue1.Format(_T("%d"), nAction1);
	strValue2.Format(_T("%d"), nAction2);
	strValue3.Format(_T("%d"), nAction3);
	((CStatic*)GetDlgItem(IDC_STATIC_ACTION1))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_ACTION2))->SetWindowText(strValue2);
	((CStatic*)GetDlgItem(IDC_STATIC_ACTION3))->SetWindowText(strValue3);

	((CStatic*)GetDlgItem(IDC_EDIT_ACTION1))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_EDIT_ACTION2))->SetWindowText(strValue2);
	((CStatic*)GetDlgItem(IDC_EDIT_ACTION3))->SetWindowText(strValue3);
}

void CDataByPollingDlg::QueryCompleteSignalDelay(STComData &stComData)
{
	// 读取上来的数据是小端格式
	u8* pRealData = stComData.zData + 2;
	u32 nDelay1 = (pRealData[0]<<8 &0xffff) | (pRealData[1]&0xffff);
	u32 nDelay2 = (pRealData[2]<<8 &0xffff) | (pRealData[3]&0xffff);

	nDelay1 = nDelay1*MS_UINT + DEF_PRECISION;
	nDelay2 = nDelay2*MS_UINT + DEF_PRECISION;
	//（均以1.31ms为单位，占两字节，取值0-4095）
	CString strValue1, strValue2;
	strValue1.Format(_T("%d"), nDelay1);
	strValue2.Format(_T("%d"), nDelay2);
	((CStatic*)GetDlgItem(IDC_STATIC_DELAY1))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_DELAY2))->SetWindowText(strValue2);

	((CStatic*)GetDlgItem(IDC_EDIT_DELAY1))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_EDIT_DELAY2))->SetWindowText(strValue2);
}


void CDataByPollingDlg::QueryLastTimeConsuming(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u32 nTimeCount = (pRealData[0]<<8 &0xffff) | (pRealData[1]&0xffff);
	u32 nTimeWait = (pRealData[2]<<8 &0xffff) | (pRealData[3]&0xffff);
	u32 nTimeOut = (pRealData[4]<<8 &0xffff) | (pRealData[5]&0xffff);
	u32 nTimeAction = nTimeCount - nTimeWait - nTimeOut;

	CString strValue1, strValue2, strValue3, strValue4;
	strValue1.Format(_T("%d"), nTimeCount);
	strValue2.Format(_T("%d"), nTimeWait);
	strValue3.Format(_T("%d"), nTimeAction);
	strValue4.Format(_T("%d"), nTimeOut);
	((CStatic*)GetDlgItem(IDC_STATIC_TIME_COUNT))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_TIME_WAIT))->SetWindowText(strValue2);
	((CStatic*)GetDlgItem(IDC_STATIC_TIME_ACTION))->SetWindowText(strValue3);
	((CStatic*)GetDlgItem(IDC_STATIC_TIME_OUT))->SetWindowText(strValue4);

}

void CDataByPollingDlg::QueryAlarmNum(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u32 nAlarmNum = int(pRealData[0]);

	CString strValue1;
	strValue1.Format(_T("%d"), nAlarmNum);
	((CStatic*)GetDlgItem(IDC_STATIC_ALARM_NUM))->SetWindowText(strValue1);
}

void CDataByPollingDlg::QueryAlarmLog(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;

	m_vAlarmLog.clear();
	// 告警数目写死是获取100条
	for (auto i = 0; i < 100; ++i)
	{
		int nAlarmIndex = int(pRealData[i]);
		m_vAlarmLog.push_back(nAlarmIndex);
	}
}

BOOL CDataByPollingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitControlPoint();

	////QueryPulsesCount(stComData);
	//ShkeHands(stComData);
	m_checkboxStatus.SetCheck(1);
	m_checkboxControl1.SetCheck(0);



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDataByPollingDlg::SendRoll(int nParam1, int nParam2, int nParam3, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ROLL_SPEED, nParam1) 
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ROLL_SPEED, nParam2)
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ROLL_SPEED, nParam3))
	{
		BoxCustom(L"EM_WRITE_ROLL_SPEED 检查参数范围", bDisBox);
		return;
	}

	// 数据按次序分3段速度，各占2字节：1.入板快速：当开始进板到碰到第2个有板感应器时，以及当开始出板到碰到出板感应器时；
	// 2.入板慢速：当碰到第2个感应器到板完全进入时；3.出板慢速：当板在流出翻板机时
	//	速度计算式：3150/V(m/s）（默认入板快速30m/s，入板慢速10m/s，出板慢速18m/s 建议设置范围：1-50m/s ）
	u32 nRoll1 = nParam1;
	u32 nRoll2 = nParam2;
	u32 nRoll3 = nParam3;

	// 速度计算公式：3150/V （V为滚轮速度单位1m/s，默认入板9m/s，出板16m/s）速度取值范围3m/s-35m/s，对应写入值1050-90，值小于90则按90写入。（两字节采取大端格式）
	if (nRoll1 == 0 || nRoll2 == 0 || nRoll3 == 0)
	{
		BoxCustom(L"参数数值不能为0", bDisBox);
		return;
	}

	nRoll1 = 3150/nRoll1;
	nRoll2 = 3150/nRoll2;
	nRoll3 = 3150/nRoll3;

	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nRoll1>>8&0x00ff;
	zData[nIndex++] = nRoll1&0x00ff;
	zData[nIndex++] = nRoll2>>8&0x00ff;
	zData[nIndex++] = nRoll2&0x00ff;
	zData[nIndex++] = nRoll3>>8&0x00ff;
	zData[nIndex++] = nRoll3&0x00ff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =  m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_ROLL_SPEED, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{	
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_ROLL_SPEED, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"参数设置成功", bDisBox);

			SetStaticValue(IDC_STATIC_ROLL1, nParam1);
			SetStaticValue(IDC_STATIC_ROLL2, nParam2);
			SetStaticValue(IDC_STATIC_ROLL3, nParam3);
		}
		else
		{
			MessageBox(L"参数设置失败");
		}
	}


}

void CDataByPollingDlg::RollEvent()
{
	CString strValue1, strValue2, strValue3;
	GetEditValue(IDC_EDIT_ROLL1, strValue1);
	GetEditValue(IDC_EDIT_ROLL2, strValue2);
	GetEditValue(IDC_EDIT_ROLL3, strValue3);
	int nEdit1 = _ttoi(strValue1);
	int nEdit2 = _ttoi(strValue2);
	int nEdit3 = _ttoi(strValue3);

	SendRoll(nEdit1, nEdit2, nEdit3);
}

void CDataByPollingDlg::OnBnClickedBtnRoll1()
{
	// TODO: 在此添加控件通知处理程序代码
	RollEvent();
}

void CDataByPollingDlg::SendFlip(int nParam1, int nParam2, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_FLIP_SPEED, nParam1) 
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_FLIP_SPEED, nParam2))
	{
		BoxCustom(L"EM_WRITE_FLIP_SPEED 检查参数范围", bDisBox);
		return;
	}

	// 据按次序分2段速度，各占2字节：1.翻转快速，从开始翻转到快速翻转完成；2.翻转慢速：
	// 从慢速翻转到翻转到位，或者发生翻转异常：慢速翻转超过60°或触碰翻转限位感应器。
	// 	速度计算式：33720/V（°/s)（默认翻转快速123°/s，翻转慢速25°/s   建议设置范围：1-180°）
	// 外部已经判断范围，就不判断0值
	int nFlip1 = 33720/nParam1;
	int nFlip2 = 33720/nParam2;

	int nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nFlip1>>8&0xff;
	zData[nIndex++] = nFlip1&0xff;
	zData[nIndex++] = nFlip2>>8&0xff;
	zData[nIndex++] = nFlip2&0xff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =   m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_FLIP_SPEED, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_FLIP_SPEED, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"参数设置成功", bDisBox);

			SetStaticValue(IDC_STATIC_FLIP1, nParam1);
			SetStaticValue(IDC_STATIC_FLIP2, nParam2);
		}
		else
		{
			MessageBox(L"EM_WRITE_FLIP_SPEED 参数设置失败");
		}
	}
}

void CDataByPollingDlg::FlipEvent()
{
	CString strValue1, strValue2;
	GetEditValue(IDC_EDIT_FLIP1, strValue1);
	GetEditValue(IDC_EDIT_FLIP2, strValue2);
	int nEdit1 = _ttoi(strValue1);
	int nEdit2 = _ttoi(strValue2);

	SendFlip(nEdit1, nEdit2);
}


void CDataByPollingDlg::OnBnClickedBtnFlip1()
{
	// TODO: 在此添加控件通知处理程序代码
	FlipEvent();
}


void CDataByPollingDlg::SentPulses(int nParam1, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_PULSES_COUNT, nParam1))
	{
		BoxCustom(L"EM_WRITE_PULSES_COUNT 检查参数范围", bDisBox);
		return;
	}

	// 占两字节，快速翻转完成后，平滑减速成翻转慢速。
	// 	以0.69°为单位(默认155°  建议设置范围：120-180°）
	int nPulses1 = nParam1/MS_UINT_SPECIAL + DEF_PRECISION;

	int nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nPulses1>>8&0xff;
	zData[nIndex++] = nPulses1&0xff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =   m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_PULSES_COUNT, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_PULSES_COUNT, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"参数设置成功", bDisBox);

			SetStaticValue(IDC_STATIC_PULSES1, nParam1);
			//SetStaticValue(IDC_STATIC_PULSES2, nParam2);
		}
		else
		{
			MessageBox(L"EM_WRITE_PULSES_COUNT 参数设置失败");
		}
	}
}

void CDataByPollingDlg::PulsesEvent()
{
	CString strValue1, strValue2;
	GetEditValue(IDC_EDIT_PULSES1, strValue1);
	int nEdit1 = _ttoi(strValue1);

	SentPulses(nEdit1);
}


void CDataByPollingDlg::OnBnClickedBtnPulses1()
{
	// TODO: 在此添加控件通知处理程序代码
	PulsesEvent();
}

void CDataByPollingDlg::SentAction(int nParam1, int nParam2, int nParam3, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ACTION_TIME, nParam1)
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ACTION_TIME, nParam2)
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ACTION_TIME, nParam3))
	{
		BoxCustom(L"EM_WRITE_ACTION_TIME 检查参数范围", bDisBox);
		return;
	}


	// 数据按次序分3段速度，各占2字节：1.判定回板完成时间；2.判定回板失败时间；3.判定气缸下压动作完成时间
	//	以0.65ms为单位（默认1：150ms；2：500ms 3：400ms  建议设置范围：1-2000ms )
	// 单位换算
	u32 nAction1 = nParam1/MS_UINT + DEF_PRECISION;
	u32 nAction2 = nParam2/MS_UINT + DEF_PRECISION;
	u32 nAction3 = nParam3/MS_UINT + DEF_PRECISION;

	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nAction1>>8&0xff;
	zData[nIndex++] = nAction1&0xff;
	zData[nIndex++] = nAction2>>8&0xff;
	zData[nIndex++] = nAction2&0xff;
	zData[nIndex++] = nAction3>>8&0xff;
	zData[nIndex++] = nAction3&0xff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =   m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_ACTION_TIME, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_ACTION_TIME, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"参数设置成功", bDisBox);

			SetStaticValue(IDC_STATIC_ACTION1, nParam1);
			SetStaticValue(IDC_STATIC_ACTION2, nParam2);
			SetStaticValue(IDC_STATIC_ACTION3, nParam3);
		}
		else
		{
			MessageBox(L"参数设置失败");
		}
	}
}

void CDataByPollingDlg::ActionEvent()
{
	CString strValue1, strValue2, strValue3;
	GetEditValue(IDC_EDIT_ACTION1, strValue1);
	GetEditValue(IDC_EDIT_ACTION2, strValue2);
	GetEditValue(IDC_EDIT_ACTION3, strValue3);
	if (strValue1.IsEmpty() || strValue2.IsEmpty(), strValue3.IsEmpty())
	{
		MessageBox(_T("参数不能为空"));
		return ;
	}

	int nEdit1 = _ttoi(strValue1);
	int nEdit2 = _ttoi(strValue2);
	int nEdit3 = _ttoi(strValue3);
	
	SentAction(nEdit1, nEdit2, nEdit3);
}

void CDataByPollingDlg::OnBnClickedBtnAction1()
{
	// TODO: 在此添加控件通知处理程序代码
	ActionEvent();
}

void CDataByPollingDlg::SentDelay(int nParam1, int nParam2, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_COMPLETE_SIGNAL_DELAY, nParam1)
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_COMPLETE_SIGNAL_DELAY, nParam2))
	{
		BoxCustom(L"EM_WRITE_COMPLETE_SIGNAL_DELAY 检查参数范围", bDisBox);
		return;
	}

	// 数据按次序分2段速度，各占2字节：1.入板传感器信号延迟过滤：2.出板命令信号延迟过滤
	// 以0.65ms为单位（默认1：200ms；2：400ms  建议设置范围：1-2000ms)

	// 单位换算
	u32 nDelay1 = nParam1/MS_UINT + DEF_PRECISION;
	u32 nDelay2 = nParam2/MS_UINT + DEF_PRECISION;

	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nDelay1>>8&0xff;
	zData[nIndex++] = nDelay1&0xff;
	zData[nIndex++] = nDelay2>>8&0xff;
	zData[nIndex++] = nDelay2&0xff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =   m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_COMPLETE_SIGNAL_DELAY, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_COMPLETE_SIGNAL_DELAY, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"参数设置成功", bDisBox);

			SetStaticValue(IDC_STATIC_DELAY1, nParam1);
			SetStaticValue(IDC_STATIC_DELAY2, nParam2);
		}
		else
		{
			MessageBox(L"参数设置失败");
		}
	}
}

void CDataByPollingDlg::DelayEvent()
{
	CString strValue1, strValue2;
	GetEditValue(IDC_EDIT_DELAY1, strValue1);
	GetEditValue(IDC_EDIT_DELAY2, strValue2);
	if (strValue1.IsEmpty() || strValue2.IsEmpty())
	{
		MessageBox(_T("参数不能为空"));
		return ;
	}
	int nEdit1 = _ttoi(strValue1);
	int nEdit2 = _ttoi(strValue2);

	SentDelay(nEdit1, nEdit2);
}

void CDataByPollingDlg::OnBnClickedBtnDelay1()
{
	// TODO: 在此添加控件通知处理程序代码
	DelayEvent();
}

void CDataByPollingDlg::SetStaticValue(unsigned int nControlID, unsigned int nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	((CButton*)GetDlgItem(nControlID))->SetWindowText(strValue);
}

void CDataByPollingDlg::GetEditValue(unsigned int nControlID, CString& strValue)
{
	((CEdit*)GetDlgItem(nControlID))->GetWindowText(strValue);
}



void CDataByPollingDlg::BoxCustom(CString strMsg, bool disBox /*= true*/)
{
	if (disBox)
	{
		MessageBox(strMsg, L"", MB_OK);
	}
}

HBRUSH CDataByPollingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  在此更改 DC 的任何特性
	//pDC->SetTextColor(RGB(255, 0, 0));
	//pDC->SetBkMode(TRANSPARENT);
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() >= IDC_CHECK2 && pWnd->GetDlgCtrlID() <= IDC_CHECK49)
		{
			if (((CButton*)pWnd)->GetCheck() == 1)
			{
				hbr = CreateSolidBrush(RGB(20, 150, 150));
			}
			
			return hbr;
		}
	}
	return hbr;
}


void CDataByPollingDlg::OnBnClickedCheckControl1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int nStatus = 0;
	nStatus = m_checkboxControl1.GetCheck();

	// 设置控制项协议开关
	if (m_pSerialThread)
	{
		m_pSerialThread->SetRunControlStatus(nStatus);
	}
}

void CDataByPollingDlg::OnBnClickedCheckStatus1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int nStatus = 0;
	nStatus = m_checkboxStatus.GetCheck();

	// 设置控制项协议开关
	if (m_pSerialThread)
	{
		m_pSerialThread->SetRunReadStatus(nStatus);
	}
}



void CDataByPollingDlg::OnBnClickedBtnRollRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_ROLL_SPEED);
	}
}


void CDataByPollingDlg::OnBnClickedBtnActionRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_ACTION_TIME);
	}
}


void CDataByPollingDlg::OnBnClickedBtnFlibRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_FLIP_SPEED);
	}
}


void CDataByPollingDlg::OnBnClickedBtnDelayRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_COMPLETE_SIGNAL_DELAY);
	}
}


void CDataByPollingDlg::OnBnClickedBtnPuleseRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_PULSES_COUNT);
	}
}


void CDataByPollingDlg::OnBnClickedButton4()
{
	//m_vAlarmLog.clear();
	//// 告警数目写死是获取100条
	//char zTemp[50] = {0};
	//int nIndex1 = 0;
	//zTemp[nIndex1++] = 0xaa;
	//zTemp[nIndex1++] = 0x23;
	//zTemp[nIndex1++] = 0x01;
	//zTemp[nIndex1++] = 0x01;
	//zTemp[nIndex1++] = 0x01;
	//zTemp[nIndex1++] = 0x01;
	//zTemp[nIndex1++] = 0x00;
	//zTemp[nIndex1++] = 0x00;
	//zTemp[nIndex1++] = 0x00;
	//zTemp[nIndex1++] = 0x00;
	//zTemp[nIndex1++] = 0x00;
	//zTemp[nIndex1++] = 0x00;
	//zTemp[nIndex1++] = 0x15;
	//zTemp[nIndex1++] = 0xee;

	//char* pTemp = zTemp+2;
	//int iNum1 = 10;
	//for (auto i = 0; i < iNum1; ++i)
	//{
	//	int nAlarmIndex = int(pTemp[i]);
	//	if (!nAlarmIndex)
	//	{
	//		continue;
	//	}
	//	m_vAlarmLog.push_back(nAlarmIndex);
	//}

	//CAlarmLog AlarmLog1;
	//AlarmLog1.SetAnalyzeProtocol(m_pAnalyzeProtocol);
	//AlarmLog1.SetAlarmLog(m_vAlarmLog);
	//AlarmLog1.DoModal();

	//return;


	// 获取当前告警次数，再获取所有告警
	CString strAlarmNum;
	((CButton*)GetDlgItem(IDC_STATIC_ALARM_NUM))->GetWindowTextW(strAlarmNum);
	int iNum = _ttoi(strAlarmNum);

	//iNum = 100;
	if (iNum < 1)
	{
		MessageBox(L"无告警");
		return;
	}
	if (iNum > 100)
	{
		MessageBox(L"异常,告警数目超出100");
		return;
	}
	
	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = iNum&0xff;


	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =   m_pAnalyzeProtocol->PackHexBuffer(EM_QUERY_ALARM_LOG, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{
		char zRevData[MAX_DATA_LEN] = {0};
		//int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_QUERY_ALARM_LOG, false);
		int nMaxRev = iNum + 4;
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{

			char* pRealData = zRevData + 2;

			m_vAlarmLog.clear();
			// 告警数目写死是获取100条
			for (auto i = 0; i < iNum; ++i)
			{
				int nAlarmIndex = int(pRealData[i]);
				if (!nAlarmIndex)
				{
					continue;
				}
				m_vAlarmLog.push_back(nAlarmIndex);
			}

			CAlarmLog AlarmLog;
			AlarmLog.SetAnalyzeProtocol(m_pAnalyzeProtocol);
			AlarmLog.SetAlarmLog(m_vAlarmLog);
			AlarmLog.DoModal();

		}
		else
		{
			MessageBox(L"获取告警失败");
		}
	}
	//// TODO: 在此添加控件通知处理程序代码
	//CAlarmLog AlarmLog;
	//AlarmLog.SetAnalyzeProtocol(m_pAnalyzeProtocol);
	//AlarmLog.SetAlarmLog(m_vAlarmLog);
	//AlarmLog.DoModal();
}


void CDataByPollingDlg::GetVersion()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_VERSION);
	}
}




void CDataByPollingDlg::OnBnClickedBtnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	PostMessageA(GetParent()->GetSafeHwnd(), WM_SAVE_CONFIG, 0, 0);
}


void CDataByPollingDlg::OnBnClickedBtnLoad()
{
	PostMessageA(GetParent()->GetSafeHwnd(), WM_LOAD_CONFIG, 0, 0);
}


void CDataByPollingDlg::OnBnClickedButtonRefresh()
{
	PostMessageA(GetParent()->GetSafeHwnd(), WM_REFRESH_CONTROL, 0, 0);
}


void CDataByPollingDlg::OnBnClickedBtnIoStatus()
{
	// 获取IO状态
	CString strCurStatus;
	((CStatic*)GetDlgItem(IDC_STATIC_WORK1))->GetWindowText(strCurStatus);
	if (strCurStatus != "停止状态")
	{
		MessageBox(L"当前状态需要为停止状态");
		return;
	}

	unsigned int nIoStatus = 0;
	for (int i = 0; i < m_vOutPutStatus.size(); ++i)
	{
		bool bCheck = m_vOutPutStatus.at(i)->GetChecked();
		nIoStatus = nIoStatus | bCheck << i;
	}

	CConfigByIoStatus configByIoStatus(nIoStatus, m_pSerialPort);
	configByIoStatus.DoModal();
}




void CDataByPollingDlg::OnBnClickedBtnClean()
{
	unsigned char zSendBuf[32] = { 0 };
	unsigned char zRevBuf[32] = { 0 };

	zSendBuf[0] = 0xAA;
	zSendBuf[1] = 0x24;
	zSendBuf[2] = CalcCrc8(&zSendBuf[1], 1);
	zSendBuf[3] = 0xEE;
	if (m_pSerialPort && m_pSerialPort->IsOpen())
	{
		char zRevData[32] = { 0 };
		int nMaxRev = 4;
		int nRev = m_pSerialPort->SendAndRev(zSendBuf, 4, zRevData, nMaxRev);
		if (nRev == 4)
		{
			MessageBox(L"报警清除成功");
			return ;
		}
	}
	MessageBox(L"报警清除失败");
	return;
}
